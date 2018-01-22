#include "stdafx.h"
#include "Collision.h"
#include "GameObject.h"

CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

void CCollision::HitRect(OBJLIST & dstList, OBJLIST & srcList)
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
				// TODO: ������ ó�� ��
			}
		}
	}
}

void CCollision::Circle(OBJLIST & dstList, OBJLIST & srcList)
{
}

bool CCollision::Ground(OBJLIST & dstList, OBJLIST & srcList)
{
	for (auto pDst : dstList)
	{
		// �̹� ���� ��ü��� �浹 ������ �ǳ� �پ��!
		if (!pDst->GetActive())
			return false;

		for (auto pSrc : srcList)
		{
			// �̹� ���� ��ü��� �浹 ������ �ǳ� �پ��!
			if (!pSrc->GetActive())
				return false;

			float fMoveX = 0.f;
			float fMoveY = 0.f;

			RECT rc = {};

			if (IntersectRect(&rc, &(pDst->GetHitBox()), &(pSrc->GetRect())))
			{
				fMoveX = rc.right - rc.left;
				fMoveY = rc.top - rc.bottom;

				if (fMoveX > fMoveY)
				{
					if (pDst->GetInfo().fY < pSrc->GetInfo().fY)
						fMoveY *= -1.f;

					pDst->SetPos(pDst->GetInfo().fX, pDst->GetInfo().fY + fMoveY);
				}
				else // x������ �о ��
				{
					if (pDst->GetInfo().fX < pSrc->GetInfo().fX)
						fMoveX *= -1.f;

					pDst->SetPos(pDst->GetInfo().fX + fMoveX, pDst->GetInfo().fY);
				}

				return true;
			}
			else
				return false;
		}
	}
}

bool CCollision::CheckCircle(CGameObject * pDst, CGameObject * pSrc)
{
	return false;
}
