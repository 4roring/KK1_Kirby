#include "stdafx.h"
#include "Scarfy.h"


CScarfy::CScarfy()
{
}


CScarfy::~CScarfy()
{
}

void CScarfy::Initialize()
{
	// 상태 초기화
	m_iMaxHp = 20;
	m_iHp = m_iMaxHp;
	SetPosToStart();
	m_tInfo.fCX = 120;
	m_tInfo.fCY = 120;
	m_iHitBoxCX = 40;
	m_iHitBoxCY = 40;

	m_fImageX = 2.f;
	m_fImageY = -5.f;

	m_fSpeed = 3.8f;
	m_fJumpPow = 8.6f;

	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;

	m_bFlipX = false;
	m_bIsDamage = false;

	// 애니메이션 초기화
	m_pFrameKey = TEXT("Scarfy_Left");

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 250;

	m_bInhail = false;
	m_eInhailType = NORMAL;
}

void CScarfy::LateInit()
{
}

OBJ_STATE CScarfy::Update()
{
	if (CheckScreen())
	{
		m_bActive = true;
		if (m_bActive && m_iHp <= 0)
			m_bActive = false;
	}
	else
	{
		Initialize();
	}

	if (m_bActive)
	{
		if (!m_bTransform)
		{
			if (m_bInhail)
				m_bTransform = true;
		}
		else
			m_bInhail = false;

		if (m_tFrame.iStart == 0)
			m_tInfo.fY -= 4.f;
		else
			m_tInfo.fY += 2.f;

		return PLAY;
	}

	return WAIT;
}

void CScarfy::LateUpdate()
{
	if (m_bActive)
	{

		FrameMove();
		UpdateRect(m_fImageX, m_fImageY);
	}
}

void CScarfy::Render(HDC hDC)
{
	if (m_bActive)
	{
		DrawHitBox(hDC);
		DrawObject(hDC, m_pFrameKey);
	}
}

void CScarfy::Release()
{
}

void CScarfy::ApplyDamage(int iDamage)
{
	if (!m_bIsDamage)
	{
		CEnemy::ApplyDamage(iDamage);
		m_bIsDamage = true;
	}
}

void CScarfy::Transform()
{
}
