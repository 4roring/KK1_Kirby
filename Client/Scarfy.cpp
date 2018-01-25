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
	m_pFrameKey = TEXT("Scarfy_Right");

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 250;

	m_bInhail = false;
	m_eInhailType = NORMAL;

	m_pTarget = GameManager->GetPlayer();
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
			NormalState();

			if (m_bInhail)
				Transform();
		}
		else
			TransformState();
	
		return PLAY;
	}

	return WAIT;
}

void CScarfy::LateUpdate()
{
	if (m_bActive)
	{
		m_bFlipX = m_tInfo.fX < m_pTarget->GetInfo().fX ? true : false;
		m_pFrameKey = m_bFlipX ? TEXT("Scarfy_Right") : TEXT("Scarfy_Left");

		FrameMove();
		UpdateRect(m_fImageX, m_fImageY);
	}
}

void CScarfy::Render(HDC hDC)
{
	if (m_bActive)
	{
		//DrawHitBox(hDC);
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
	if (m_tFrame.iScene == 0)
	{
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.iScene = 2;
		m_tFrame.dwSpeed = 100;
	}

	if (m_tFrame.iStart == m_tFrame.iEnd)
	{
		m_bTransform = true;

		if (m_tFrame.iScene == 2)
		{
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 2;
			m_tFrame.iScene = 3;
			m_tFrame.dwSpeed = 150;
		}

		m_dwDeadTimer = GetTickCount() + 3000;
	}
}

void CScarfy::NormalState()
{
	if (!m_bInhail)
	{
		if (m_tFrame.iStart == 0)
			m_tInfo.fY -= 4.f;
		else
			m_tInfo.fY += 2.f;
	}
}

void CScarfy::TransformState()
{
	m_bInhail = false;

	float fAngle = CMath::DistanceAngle(this, m_pTarget);

	m_tInfo.fX += cosf(fAngle) * 4.f;
	m_tInfo.fY -= sinf(fAngle) * 4.f;

	if (m_dwDeadTimer < GetTickCount())
	{
		ApplyDamage(100);
		m_bActive = false;
	}
}
