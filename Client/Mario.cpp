#include "stdafx.h"
#include "Mario.h"
#include "UI_BossHp.h"


CMario::CMario()
	: m_dwIdleTime(500)
{
}


CMario::~CMario()
{
}

void CMario::Initialize()
{
	// 상태 초기화
	m_iMaxHp = 700;
	m_iHp = m_iMaxHp;
	SetPosToStart();
	m_tInfo.fCX = 60;
	m_tInfo.fCY = 120;
	m_iHitBoxCX = 50;
	m_iHitBoxCY = 70;

	m_fImageX = 0.f;
	m_fImageY = 0.f;

	m_fVelocityX = 0.f;
	m_fVelocityY = -1.f;

	m_ePreState = END;
	m_eCurState = IDLE;

	m_iCondition = 0;
	m_iPatternCnt = 0;

	m_pFrameKey = TEXT("Mario_Left");
	m_dwStateTime = GetTickCount() + 3000;
	m_pTarget = GameManager->GetPlayer();

	m_eInhailType = TYPE_BOSS;

	GameManager->AddObject(CAbsFactory<CUI_BossHp>::CreateObject(this), OBJ_UI);
}

void CMario::LateInit()
{
}

OBJ_STATE CMario::Update()
{
	if (!m_bActive)
		return DESTROY;

	if (m_eInhailType == TYPE_BOSS)
		m_bInhail = false;
	else if (m_bInhail)
		m_eCurState = INHAIL;

	switch (m_eCurState)
	{
	case CMario::IDLE:
		m_fVelocityX = 0.f;
		m_iPatternCnt = 0;
		if (m_dwStateTime < GetTickCount())
		{
			// 다른 행동으로 전환.
			m_eCurState = MOVE;
			m_dwStateTime = GetTickCount() + m_dwIdleTime;
		}
		break;
	case CMario::MOVE:
		m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
		m_pFrameKey = m_bFlipX ? TEXT("Mario_Right") : TEXT("Mario_Left");

		m_fVelocityX = m_bFlipX ? 2.5f : -2.5f;

		m_iCondition = rand() % 2;

		switch (m_iCondition)
		{
		case 0: // 점프로 넘어감
			if (m_dwStateTime < GetTickCount() &&
				abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 200.f)
			{
				m_eCurState = JUMP;
				if(m_fVelocityY == 0.f)
				m_fVelocityY = 12.f;

				m_iCondition = rand() % 2; // 점프의 패턴을 결정
			}
			break;
		case 1: // 불꽃 발사.
			if (m_dwStateTime < GetTickCount() &&
				abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 300.f)
			{

			}
			break;
		}
		break;
	case CMario::JUMP:
		switch (m_iCondition)
		{
		case 0: // 플레이어랑 가까우면 찍기 공격.
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 10.f)
			{
				m_eCurState = DOWNATTACK;
			}
			break;
		case 1: // 불꽃 발사 2
			if (m_dwStateTime < GetTickCount())
			{
				m_eCurState = FIRE;
			}
			break;
		}

		break;
	case CMario::DOWNATTACK:
		if (m_fVelocityY == 0.f)
		{
			m_eCurState = MOVE;
			m_dwStateTime = GetTickCount() + m_dwIdleTime;
		}
		m_fVelocityX = 0.f;
		m_fVelocityY -= 0.61f;
		break;
	case CMario::FIRE:
		m_eCurState = MOVE;
		m_dwStateTime = GetTickCount() + m_dwIdleTime;
		break;
	case CMario::DEAD:
		break;
	case CMario::INHAIL:
		break;
	case CMario::END:
		break;
	default:
		break;
	}

	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY -= m_fVelocityY;

	return PLAY;
}

void CMario::LateUpdate()
{
	if (m_tInfo.fX < 0 + m_iHitBoxCX * 0.5f)
		m_tInfo.fX = (float)m_iHitBoxCX * 0.5f;

	FrameMove();
	SceneChange();
	UpdateRect(m_fImageX, m_fImageY);

	if (m_eCurState != DEAD && m_fVelocityY != 0.f)
		m_fVelocityY -= 0.5f;
}

void CMario::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);

	if (!m_bIsDamage)
		DrawObject(hDC, m_pFrameKey);
	else if (m_bIsDamage && g_iFrame % 3 == 0)
		DrawObject(hDC, m_pFrameKey);

	DrawUI(hDC, TEXT("BossName"), 430, 520, 120, 30, 2);
}

void CMario::Release()
{
}

void CMario::ApplyDamage(int iDamage)
{
}

void CMario::isInhail()
{
	if (m_pTarget == nullptr)
		m_pTarget = GameManager->GetPlayer();

	float fAngle = CMath::DistanceAngle(this, m_pTarget);

	m_fVelocityX += 0.5f;

	m_tInfo.fX += cosf(fAngle) * m_fVelocityX;
	m_tInfo.fY -= sinf(fAngle) * m_fVelocityX;

	if (m_bIsDamage)
	{
		m_bIsDamage = false;
		m_bActive = false;
	}
}

void CMario::SceneChange()
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iStart = 0;

		switch (m_eCurState)
		{
		case CMario::IDLE:
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 0;
			break;
		case CMario::MOVE:
			m_tFrame.iEnd = 2;
			m_tFrame.iScene = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case CMario::JUMP:
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 2;
			break;
		case CMario::DOWNATTACK:
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 3;
			break;
		case CMario::FIRE:
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 4;
			break;
		case CMario::DEAD:
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 5;
			break;
		case CMario::INHAIL:
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 6;
			break;
		case CMario::END:
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CMario::CreateInhailStar()
{
}
