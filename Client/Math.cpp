#include "stdafx.h"
#include "Math.h"
#include "GameObject.h"


CMath::CMath()
{
}


CMath::~CMath()
{
}

// 두 오브젝트 사이의 거리를 반환
float CMath::Distance(CGameObject * pDst, CGameObject * pSrc)
{
	float fW = pSrc->GetInfo().fX - pDst->GetInfo().fX;
	float fH = pSrc->GetInfo().fY - pDst->GetInfo().fY;

	return sqrtf(fW * fW + fH * fH);
}

// 두 오브젝트 사이의 각도를 Radian으로 반환
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
