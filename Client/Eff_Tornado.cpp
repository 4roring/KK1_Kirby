#include "stdafx.h"
#include "Eff_Tornado.h"


CEff_Tornado::CEff_Tornado()
{
}


CEff_Tornado::~CEff_Tornado()
{
	Release();
}

void CEff_Tornado::Initialize()
{
	m_tInfo.fCX = 180.f;
	m_tInfo.fCY = 450.f;

	m_iHitBoxCX = 80;
	m_iHitBoxCY = 400;

	m_iAtt = 10;

	m_bHitBoxType = true;
}

void CEff_Tornado::LateInit()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 13;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 40;
	m_fSpeed = m_bFlipX ? 5.f : -5.f;
	m_pFrameKey = TEXT("MetaKnight_Tornado");
}

OBJ_STATE CEff_Tornado::Update()
{
	if (!m_bActive)
	{
		GameManager->CameraShakingEnd();
		m_iHitBoxCX = 50;
		m_iHitBoxCY = 50;

		if(m_tFrame.iStart == m_tFrame.iEnd)
			return DESTROY;
	}
	else
	{
		if (m_tFrame.iStart == 8)
			m_tFrame.iStart = 0;
		m_tInfo.fX += m_fSpeed;

		GameManager->CameraShakingStart(10.f);
	}
	
	return PLAY;
}

void CEff_Tornado::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CEff_Tornado::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);
	DrawObject(hDC, m_pFrameKey);
}

void CEff_Tornado::Release()
{
}
