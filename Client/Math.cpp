#include "stdafx.h"
#include "Math.h"
#include "GameObject.h"


CMath::CMath()
{
}


CMath::~CMath()
{
}

float CMath::Distance(CGameObject * pDst, CGameObject * pSrc)
{
	float fW = pSrc->GetInfo().fX - pDst->GetInfo().fX;
	float fH = pSrc->GetInfo().fY - pDst->GetInfo().fY;

	return sqrtf(fW * fW + fH * fH);
}
