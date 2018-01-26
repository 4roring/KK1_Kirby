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

			if (IntersectRect(&rc, &(pDst->GetHitBox()), &(pSrc->GetHitBox())))
			{
				if (pSrc->GetInhail())
				{
					if (rc.right - rc.left)
					{
						pDst->SetInhail();
						pDst->SetInhailType(pSrc->GetInhailType());
						dynamic_cast<CActor*>(pSrc)->ApplyDamage(100);
					}
				}
				else if(pSrc->GetAtt() != 60)
				{
					if (pDst->GetInfo().fX < pSrc->GetInfo().fX)
					{
						pDst->SetFlipX(true);
						pSrc->SetFlipX(false);
					}
					else
					{
						pDst->SetFlipX(false);
						pSrc->SetFlipX(true);
					}

					dynamic_cast<CActor*>(pDst)->ApplyDamage(10);
					dynamic_cast<CActor*>(pSrc)->ApplyDamage(pDst->GetAtt());
				}
			}
		}
	}
}

void CCollision::Ground(OBJLIST & dstList, OBJLIST & srcList)
{
	for (auto& pDst : dstList)
	{
		if (!pDst->GetActive() || pDst->GetAtt() == 60)
			continue;

		for (auto& pSrc : srcList)
		{
			if (!pSrc->GetActive())
				continue;

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
							pDst->SetPos(pDst->GetInfo().fX, fMoveY - pDst->GetHitBoxCY() * 0.49f);
						}

						dynamic_cast<CActor*>(pDst)->SetVelocityY(0.f);
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

					if (fMoveY - pDst->GetHitBoxCY() >= pDst->GetInfo().fY)
						continue;

					pDst->SetPos(pDst->GetInfo().fX, fMoveY - pDst->GetHitBoxCY() * 0.45f);
					dynamic_cast<CActor*>(pDst)->SetVelocityY(0.f);
				}
			}
		}
	}

}

bool CCollision::PlayerToGround(CActor* pPlayer, OBJLIST & srcList)
{
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

			if (IntersectRect(&rc, &(pPlayer->GetHitBox()), &(pSrc->GetRect())))
			{
				fMoveX = float(rc.right - rc.left);
				fMoveY = float(rc.bottom - rc.top);

				if (fMoveX < fMoveY)
				{
					if (pPlayer->GetInfo().fX < pSrc->GetRect().left)
						fMoveX *= -1.f;

					pPlayer->SetPos(pPlayer->GetInfo().fX + fMoveX, pPlayer->GetInfo().fY);
					pPlayer->SetVelocityX(0.f);
				}
				else
				{
					if (pPlayer->GetInfo().fY + pPlayer->GetHitBoxCY() * 0.5f > pSrc->GetRect().bottom)
						pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY + fMoveY * 0.45f);
					else
					{
						// 라인충돌.
						float x1 = float(pSrc->GetRect().left);
						float x2 = float(pSrc->GetRect().right);
						float y = float(pSrc->GetRect().top);

						float fGradient = (y - y) / (x2 - x1);
						fMoveY = fGradient * (pPlayer->GetInfo().fX - x1) + y;
						pPlayer->SetPos(pPlayer->GetInfo().fX, fMoveY - pPlayer->GetHitBoxCY() * 0.45f);
					}

					dynamic_cast<CActor*>(pPlayer)->SetVelocityY(0.f);

					return true;
				}
			}
		}
		else
		{
			// 라인 Ground 충돌
			float x1 = (float)dynamic_cast<CGround*>(pSrc)->GetPoint_1().x;
			float x2 = (float)dynamic_cast<CGround*>(pSrc)->GetPoint_2().x;

			if (x1 < pPlayer->GetInfo().fX && pPlayer->GetInfo().fX < x2)
			{
				float y1 = (float)dynamic_cast<CGround*>(pSrc)->GetPoint_1().y;
				float y2 = (float)dynamic_cast<CGround*>(pSrc)->GetPoint_2().y;

				float fGradient = (y2 - y1) / (x2 - x1);
				fMoveY = fGradient * (pPlayer->GetInfo().fX - x1) + y1;

				if (fMoveY - pPlayer->GetHitBoxCY() * 0.5f >= pPlayer->GetInfo().fY)
					return false;

				pPlayer->SetPos(pPlayer->GetInfo().fX, fMoveY - pPlayer->GetHitBoxCY() * 0.45f);
				pPlayer->SetVelocityY(0.f);
				return true;
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
		if (!pDst->GetActive() || pDst->GetAtt() == 60)
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
		if (pEnemy->GetInhailType() == TYPE_BOSS || !pEnemy->GetActive())
			continue;

		RECT rc = {};
		if (IntersectRect(&rc, &(pObj->GetHitBox()), &(pEnemy->GetHitBox())))
		{
			pObj->SetInhail();
			pEnemy->SetInhail();
			return true;
		}
	}
	return false;
}

void CCollision::InterectionDoor(CGameObject * pObj, OBJLIST & InterectionList)
{
	for (auto pInter : InterectionList)
	{
		if (!pInter->GetActive())
			continue;

		RECT rc = {};
		if (IntersectRect(&rc, &(pObj->GetRect()), &(pInter->GetRect())))
			pInter->SetActive(false);
	}
}
