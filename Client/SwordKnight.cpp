#include "stdafx.h"
#include "SwordKnight.h"


CSwordKnight::CSwordKnight()
{
}


CSwordKnight::~CSwordKnight()
{
}

void CSwordKnight::Initialize()
{
	m_iMaxHp = 40;
	m_iHp = m_iMaxHp;
	SetPosToStart();
	m_tInfo.fCX = 240;
	m_tInfo.fCY = 105;
	m_iHitBoxCX = 50;
	m_iHitBoxCY = 50;

	m_fImageX = 3.5f;
	m_fImageY = -16.f;

	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;

	m_bFlipX = false;
	m_bIsDamage = false;

	m_pFrameKey = TEXT("SwordKnight_Left");
	m_ePreState = END;
	m_eCurState = IDLE;

	m_bInhail = false;
	m_eInhailType = SWORD;
	m_dwDelayTime = GetTickCount() + 3000;

	m_pTarget = GameManager->GetPlayer();
}

void CSwordKnight::LateInit()
{
}

OBJ_STATE CSwordKnight::Update()
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
		switch (m_eCurState)
		{
		case IDLE:
			if(m_tFrame.iStart == 0)
				m_fVelocityX = m_bFlipX ? -0.5f : 0.5f;
			else if(m_tFrame.iStart == 4)
				m_fVelocityX = m_bFlipX ? 0.5f : -0.5f;

			if (CMath::Distance(this, m_pTarget) < 250.f && m_dwDelayTime < GetTickCount())
				m_eCurState = ATTACK;
			break;
		case ATTACK:
			m_bIsDamage = true;
			m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
			m_pFrameKey = m_bFlipX ? TEXT("SwordKnight_Right") : TEXT("SwordKnight_Left");

			if (m_tFrame.iStart < 3)
				m_fVelocityX = m_bFlipX ? 8.f : -8.f;
			else if (m_tFrame.iStart == m_tFrame.iEnd)
			{
				m_iHitBoxCX = 50;
				m_bIsDamage = false;
				m_dwDelayTime = GetTickCount() + 3000;
				m_eCurState = IDLE;
			}
			else
				m_iHitBoxCX = 150;
			break;
		case DAMAGE:
			if (!m_bIsDamage)
				m_eCurState = IDLE;
			break;
		case INHAIL:
			isInhail();
			break;
		}

		if (!m_bInhail)
		{
			m_tInfo.fX += m_fVelocityX;
			m_tInfo.fY -= m_fVelocityY;
		}

		return PLAY;
	}

	return WAIT;
}

void CSwordKnight::LateUpdate()
{
	if (m_bActive)
	{
		if (m_bInhail)
			m_eCurState = INHAIL;

		if (m_bIsDamage && m_eCurState != ATTACK)
		{
			m_eCurState = DAMAGE;
			isDamage();
		}

		SceneChange();
		FrameMove();
		UpdateRect(m_fImageX, m_fImageY);

		m_fVelocityY -= 0.1f;
	}
}

void CSwordKnight::Render(HDC hDC)
{
	if (m_bActive)
	{
		if (GameManager->GetDebugMode())
			DrawHitBox(hDC);
		DrawObject(hDC, m_pFrameKey);
	}
}

void CSwordKnight::Release()
{
}

void CSwordKnight::SceneChange()
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iStart = 0;

		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iEnd = 7;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 120;
			break;
		case ATTACK:
			m_tFrame.iEnd = 5;
			m_tFrame.iScene = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 40;
			break;
		case DAMAGE:
			m_tFrame.iStart = 1;
			m_tFrame.iEnd = 1;
			m_tFrame.iScene = 2;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			break;
		case INHAIL:
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 3;
			m_tFrame.dwSpeed = 1000;
			break;
		}
		m_ePreState = m_eCurState;
	}
}
