#include "stdafx.h"
#include "Math.h"
#include "GameObject.h"


CMath::CMath()
{
}


CMath::~CMath()
{
}

// �� ������Ʈ ������ �Ÿ��� ��ȯ
float CMath::Distance(CGameObject * pDst, CGameObject * pSrc)
{
	float fW = pSrc->GetInfo().fX - pDst->GetInfo().fX;
	float fH = pSrc->GetInfo().fY - pDst->GetInfo().fY;

	return sqrtf(fW * fW + fH * fH);
}

// �� ������Ʈ ������ ������ Radian���� ��ȯ
float CMath::DistanceAngle(CGameObject * pDst, CGameObject * pSrc)
{
	float fW = pSrc->GetInfo().fX - pDst->GetInfo().fX;
	float fH = pSrc->GetInfo().fY - pDst->GetInfo().fY;
	
	float fD = sqrtf(fW * fW + fH * fH);

	float fAngle = acosf(fD / fW);

	if (pSrc->GetInfo().fY < pDst->GetInfo().fY)
		fAngle *= -1.f;

	return fAngle;
}
