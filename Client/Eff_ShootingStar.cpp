#include "stdafx.h"
#include "Eff_ShootingStar.h"
#include "Eff_ClearStar.h"


CEff_ShootingStar::CEff_ShootingStar()
{
}


CEff_ShootingStar::~CEff_ShootingStar()
{
}

void CEff_ShootingStar::Initialize()
{
	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 120.f;

	m_iHitBoxCX = 70;
	m_iHitBoxCY = 70;

	m_iAtt = 100;
}

void CEff_ShootingStar::LateInit()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 30;
	m_fSpeed = m_bFlipX ? 15.f : -15.f;
	m_pFrameKey = m_bFlipX ? TEXT("ShootingStar_Right"):TEXT("ShootingStar_Left");
}

OBJ_STATE CEff_ShootingStar::Update()
{
	if (!m_bActive)
	{
		GameManager->AddObject(CAbsFactory<CEff_ClearStar>::CreateObject(m_tInfo.fX, m_tInfo.fY), OBJ_EFFECT);
		return DESTROY;
	}
	

	if (m_tInfo.fX < 0 || m_tInfo.fX > 10000.f)
		m_bActive = false;

	m_tInfo.fX += m_fSpeed;

	return PLAY;
}

void CEff_ShootingStar::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CEff_ShootingStar::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);
	DrawObject(hDC, m_pFrameKey);
}

void CEff_ShootingStar::Release()
{
}
