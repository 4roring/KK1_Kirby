#include "stdafx.h"
#include "Wadorudi.h"


CWadorudi::CWadorudi()
{
}


CWadorudi::~CWadorudi()
{
}

void CWadorudi::Initialize()
{
	// 상태 초기화
	m_iMaxHp = 20;
	m_iHp = m_iMaxHp;
	SetPosToStart();
	m_tInfo.fCX = 69;
	m_tInfo.fCY = 69;
	m_iHitBoxCX = 50;
	m_iHitBoxCY = 50;

	m_fImageX = 0.f;
	m_fImageY = -12.f;

	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;

	m_bFlipX = false;
	m_bIsDamage = false;

	// 애니메이션 초기화
	m_pFrameKey = TEXT("Wadorudi_Left");

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 7;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 130;

	m_bInhail = false;
	m_eInhailType = NORMAL;
}

void CWadorudi::LateInit()
{
}

OBJ_STATE CWadorudi::Update()
{
	if (CheckScreen())
	{
		m_bActive = true;
		if (m_bActive && m_iHp <= 0 && !m_bIsDamage)
			m_bActive = false;
	}
	else
		Initialize();

	if (m_bActive)
	{
		if (m_bInhail) { isInhail(); return PLAY; }

		if (m_bIsDamage) isDamage();
		else m_fVelocityX = m_bFlipX ? 1.f : -1.f;
	
		m_tInfo.fX += m_fVelocityX;
		m_tInfo.fY -= m_fVelocityY;

		return PLAY;
	}

	return WAIT;
}

void CWadorudi::LateUpdate()
{
	if (m_bActive)
	{
		m_pFrameKey = m_bFlipX ? TEXT("Wadorudi_Right") : TEXT("Wadorudi_Left");

		if (m_bInhail)
		{
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 2;
		}
		else if (m_bIsDamage && m_tFrame.iScene == 0)
		{
			m_tFrame.iStart = 1;
			m_tFrame.iEnd = 1;
			m_tFrame.iScene = 1;
			m_tFrame.dwSpeed = 200;
		}
		else if(!m_bIsDamage && m_tFrame.iScene == 1)
		{
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 7;
			m_tFrame.iScene = 0;
			m_tFrame.dwSpeed = 130;
		}

		FrameMove();
		UpdateRect(m_fImageX, m_fImageY);

		m_fVelocityY -= 0.1f;
	}
}

void CWadorudi::Render(HDC hDC)
{
	if (m_bActive)
	{
		if (GameManager->GetDebugMode())
			DrawHitBox(hDC);
		DrawObject(hDC, m_pFrameKey);
	}
}

void CWadorudi::Release()
{
}


