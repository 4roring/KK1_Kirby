#include "stdafx.h"
#include "Eff_Dash.h"


CEff_Dash::CEff_Dash()
{
}


CEff_Dash::~CEff_Dash()
{
}

void CEff_Dash::Initialize()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_pFrameKey = TEXT("Normal_Effect");
}

void CEff_Dash::LateInit()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 34;
	m_tFrame.iScene = m_bFlipX ? 3 : 2;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 30;
	m_fSpeed = m_bFlipX ? -3.f : 3.f;
}

OBJ_STATE CEff_Dash::Update()
{
	if (m_tFrame.iStart == m_tFrame.iEnd)
		return DESTROY;

	m_tInfo.fX += m_fSpeed;

	return PLAY;
}

void CEff_Dash::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CEff_Dash::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CEff_Dash::Release()
{
}
