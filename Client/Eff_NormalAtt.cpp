#include "stdafx.h"
#include "Eff_NormalAtt.h"

CEff_NormalAtt::CEff_NormalAtt()
{
}


CEff_NormalAtt::~CEff_NormalAtt()
{
	Release();
}

void CEff_NormalAtt::Initialize()
{
	m_tInfo.fCX = 210.f;
	m_tInfo.fCY = 210.f;
	m_iHitBoxCX = 170;
	m_iHitBoxCY = 120;	
}

void CEff_NormalAtt::LateInit()
{
	m_bFlipX = m_pTarget->GetFlipX();

	m_pFrameKey = m_bFlipX ? TEXT("Normal_Attack_Right") : TEXT("Normal_Attack_Left");

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 13;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 30;
}

OBJ_STATE CEff_NormalAtt::Update()
{
	if (!m_bActive)
		return DESTROY;

	m_bFlipX = m_pTarget->GetFlipX();

	float fX = m_bFlipX ? 110.f : -110.f;
	m_pFrameKey = m_bFlipX ? TEXT("Normal_Attack_Right") : TEXT("Normal_Attack_Left");

	m_tInfo.fX = m_pTarget->GetInfo().fX + fX;
	m_tInfo.fY = m_pTarget->GetInfo().fY - 10.f;

	return PLAY;
}

void CEff_NormalAtt::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CEff_NormalAtt::Render(HDC hDC)
{
	//DrawHitBox(hDC);
	DrawObject(hDC, m_pFrameKey);
}

void CEff_NormalAtt::Release()
{
}
