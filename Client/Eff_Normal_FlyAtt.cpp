#include "stdafx.h"
#include "Eff_Normal_FlyAtt.h"


CEff_Normal_FlyAtt::CEff_Normal_FlyAtt()
{
}


CEff_Normal_FlyAtt::~CEff_Normal_FlyAtt()
{
}

void CEff_Normal_FlyAtt::Initialize()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_iHitBoxCX = 50;
	m_iHitBoxCY = 50;

	m_iAtt = 20;

	m_pFrameKey = TEXT("Normal_Effect");
}

void CEff_Normal_FlyAtt::LateInit()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.iScene = m_bFlipX ? 1 : 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 50;
	m_fSpeed = m_bFlipX ? 6.f : -6.f;
}

OBJ_STATE CEff_Normal_FlyAtt::Update()
{
	if (m_tFrame.iStart == m_tFrame.iEnd || !m_bActive)
		return DESTROY;

	m_tInfo.fX += m_fSpeed;

	return PLAY;
}

void CEff_Normal_FlyAtt::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CEff_Normal_FlyAtt::Render(HDC hDC)
{
	DrawHitBox(hDC);
	DrawObject(hDC, TEXT("Normal_Effect"));
}

void CEff_Normal_FlyAtt::Release()
{
}
