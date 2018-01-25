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
	m_iHitBoxCX = 40;
	m_iHitBoxCY = 40;

	m_fImageX = 0.f;
	m_fImageY = -12.f;

	m_fSpeed = 3.8f;
	m_fJumpPow = 8.6f;

	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;
	m_fGravity = 0.0f;
	m_fDrag = 0.f;
	m_fAccX = 0.65f;
	m_fAccY = 1.2f;

	m_bFlipX = false;
	m_bIsDamage = false;

	// 애니메이션 초기화
	m_pFrameKey = TEXT("Wadorudi_Left");

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 7;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 130;
}

void CWadorudi::LateInit()
{
}

OBJ_STATE CWadorudi::Update()
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
		FrameMove();
		UpdateRect(m_fImageX, m_fImageY);

		m_fVelocityY -= 0.1f;
	}
}

void CWadorudi::Render(HDC hDC)
{
	if (m_bActive)
	{
		DrawHitBox(hDC);
		DrawObject(hDC, m_pFrameKey);
	}
}

void CWadorudi::Release()
{
}

void CWadorudi::ApplyDamage(int iDamage)
{
	if (!m_bIsDamage)
	{
		std::cout << m_iHp << std::endl;
		
		CActor::ApplyDamage(iDamage);
		m_bIsDamage = true;
	}
}

void CWadorudi::isDamage()
{
	float fAccX = m_bFlipX ? -0.1f : 0.1f;

	m_fVelocityX += fAccX;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 0;
	m_tFrame.iScene = 1;

	if (abs(m_fVelocityX) > 3.f)
	{
		m_bIsDamage = false;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 7;
		m_tFrame.iScene = 0;

		if (m_iHp <= 0)
			m_bActive = false;

		std::cout << m_bActive << std::endl;
	}
}

void CWadorudi::isInhail()
{
	if (m_pTarget == nullptr)
		m_pTarget = GameManager->GetPlayer();

	float fAngle = CMath::DistanceAngle(this, m_pTarget);
	float fDistance = CMath::Distance(this, m_pTarget);

	m_tInfo.fX += cosf(fAngle) * 2.f;
	m_tInfo.fY += sinf(fAngle) * 2.f;

	if (fDistance < 2.f)
	{
		m_bActive = false;
		m_iHp = 0;
	}
}

