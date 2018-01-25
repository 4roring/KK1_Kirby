#include "stdafx.h"
#include "Collision.h"
#include "Actor.h"
#include "Ground.h"

CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

void CCollision::ActorToActor(OBJLIST & dstList, OBJLIST & srcList)
{
	for (auto pDst : dstList)
	{
		if (!pDst->GetActive())
			continue;

		for (auto pSrc : srcList)
		{
			if (!pSrc->GetActive())
				continue;

			RECT rc = {};

			if (IntersectRect(&rc, &(pDst->GetRect()), &(pSrc->GetRect())))
			{
				dynamic_cast<CActor*>(pDst)->ApplyDamage(10);
				dynamic_cast<CActor*>(pSrc)->ApplyDamage(10);
			}
		}
	}
}

bool CCollision::Ground(OBJLIST & dstList, OBJLIST & srcList)
{
	for (auto& pDst : dstList)
	{
		if (!pDst->GetActive())
			return false;

		for (auto& pSrc : srcList)
		{
			if (!pSrc->GetActive())
				return false;

			float fMoveX = 0.f;
			float fMoveY = 0.f;

			// FlipX로 지형의 상태를 Line과 Rect로 구분한다.
			// false = Rect, true = Line
			if (!pSrc->GetFlipX())
			{
				// Rect 벽 충돌
				RECT rc = {};

				if (IntersectRect(&rc, &(pDst->GetHitBox()), &(pSrc->GetRect())))
				{
					fMoveX = float(rc.right - rc.left);
					fMoveY = float(rc.bottom - rc.top);

					if (fMoveX < fMoveY)
					{
						if (pDst->GetInfo().fX < pSrc->GetRect().left)
							fMoveX *= -1.f;

						pDst->SetPos(pDst->GetInfo().fX + fMoveX, pDst->GetInfo().fY);
						dynamic_cast<CActor*>(pDst)->SetVelocityX(0.f);
					}
					else
					{
						if (pDst->GetInfo().fY + pDst->GetHitBoxCY() * 0.5f > pSrc->GetRect().bottom)
							pDst->SetPos(pDst->GetInfo().fX, pDst->GetInfo().fY + fMoveY * 0.49f);
						else
						{
							// 라인충돌.
							float x1 = float(pSrc->GetRect().left);
							float x2 = float(pSrc->GetRect().right);
							float y = float(pSrc->GetRect().top);

							float fGradient = (y - y) / (x2 - x1);
							fMoveY = fGradient * (pDst->GetInfo().fX - x1) + y;
							pDst->SetPos(pDst->GetInfo().fX, fMoveY - pDst->GetHitBoxCY() * 0.475f);
						}
							
						dynamic_cast<CActor*>(pDst)->SetVelocityY(0.f);

						return true;
					}
				}
			}
			else
			{
				// 라인 Ground 충돌
				float x1 = (float)dynamic_cast<CGround*>(pSrc)->GetPoint_1().x;
				float x2 = (float)dynamic_cast<CGround*>(pSrc)->GetPoint_2().x;

				if (x1 < pDst->GetInfo().fX && pDst->GetInfo().fX < x2)
				{
					float y1 = (float)dynamic_cast<CGround*>(pSrc)->GetPoint_1().y;
					float y2 = (float)dynamic_cast<CGround*>(pSrc)->GetPoint_2().y;
				
					float fGradient = (y2 - y1) / (x2 - x1);
					fMoveY = fGradient * (pDst->GetInfo().fX - x1) + y1;
					
					if (fMoveY - pDst->GetHitBoxCY() * 0.5f >= pDst->GetInfo().fY)
						return false;

					pDst->SetPos(pDst->GetInfo().fX, fMoveY - pDst->GetHitBoxCY() * 0.5f);
					dynamic_cast<CActor*>(pDst)->SetVelocityY(0.f);
					return true;
				}
			}
		}
	}
	return false;
}

bool CCollision::Screen(RECT & tScreen, CGameObject* pObj)
{
	RECT rc = {};

	if (IntersectRect(&rc, &tScreen, &pObj->GetHitBox()))
		return true;
	
	return false;
}

void CCollision::HitBox(OBJLIST & dstList, OBJLIST & srcList)
{
	for (auto pDst : dstList)
	{
		if (!pDst->GetActive())
			continue;

		for (auto pSrc : srcList)
		{
			if (!pSrc->GetActive())
				continue;

			RECT rc = {};
			if (IntersectRect(&rc, &(pDst->GetHitBox()), &(pSrc->GetHitBox())))
			{
				dynamic_cast<CActor*>(pDst)->ApplyDamage(pSrc->GetAtt());
				pSrc->SetActive(false);
			}
		}
	}
}

bool CCollision::InhailToEnemy(CGameObject * pObj, OBJLIST & EnemyList)
{
	for (auto pEnemy : EnemyList)
	{
		if (!pEnemy->GetActive())
			continue;

		RECT rc = {};
		if (IntersectRect(&rc, &(pObj->GetRect()), &(pEnemy->GetHitBox())))
		{
			pEnemy->SetInhail();
			return true;
		}
	}
	return false;
}
