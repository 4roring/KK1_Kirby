#include "stdafx.h"
#include "Mario.h"
#include "UI_BossHp.h"
#include "MarioFire.h"
#include "InhailStar.h"
#include "Door.h"
#include "HpItem.h"


CMario::CMario()
	: m_dwIdleTime(700)
{
}


CMario::~CMario()
{
}

void CMario::Initialize()
{
	// 상태 초기화
	m_iMaxHp = 500;
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
	{
		GameManager->AddObject(CAbsFactory<CDoor>::CreateDoor(588.f, 172.f, SCENE_BOSS), OBJ_INTERECTION);
		GameManager->AddObject(CAbsFactory<CHpItem>::CreateObject(565.f, 465.f), OBJ_INTERECTION);
		return DESTROY;
	}
		
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

		
		m_fVelocityX = m_iHp > 300 ? 2.f : 2.8f;
		m_fVelocityX = m_bFlipX ? m_fVelocityX : -m_fVelocityX;

		m_iCondition = rand() % 2;
		if (m_dwStateTime < GetTickCount())
		{
			switch (m_iCondition)
			{
			case 0: // 점프로 넘어감
				if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 200.f)
				{
					m_eCurState = JUMP;
					m_iCondition = rand() % 2; // 점프의 패턴을 결정
					Shot();
				}
				break;
			case 1: // 불꽃 발사.
				if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 400.f)
				{
					m_eCurState = FIRE;
					m_iCondition = 0;
				}
				break;
			}
		}
		break;
	case CMario::JUMP:
		m_fVelocityY -= 0.41f;

		if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) > 150.f)
		{
			m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
			m_pFrameKey = m_bFlipX ? TEXT("Mario_Right") : TEXT("Mario_Left");
		}
			

		if (m_fVelocityY <= -0.11f && m_tInfo.fY > 200.f)
		{
			SoundManager->PlaySound(TEXT("Mario_Jump.wav"), CSoundManager::ENEMY);
			m_fVelocityY = 10.5f;
		}
			

		switch (m_iCondition)
		{
		case 0: // 플레이어랑 가까우면 찍기 공격.
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 10.f)
			{
				m_eCurState = DOWNATTACK;
				m_dwStateTime = GetTickCount() + m_dwIdleTime;
			}
			break;
		case 1: // 불꽃 발사 2
			if (m_dwStateTime < GetTickCount())
			{
				m_eCurState = FIRE;
				m_iCondition = 1;
				m_dwStateTime = GetTickCount() + m_dwIdleTime;
			}
			break;
		}

		break;
	case CMario::DOWNATTACK:
		if (m_fVelocityY == 0.f)
		{
			CreateInhailStar();
			m_eCurState = MOVE;
			m_dwStateTime = GetTickCount() + m_dwIdleTime;
			GameManager->CameraShakingStart(5.f, 500);
		}
		m_fVelocityX = 0.f;
		m_fVelocityY -= 0.61f;
		break;
	case CMario::FIRE:
		Shot();
		m_eCurState = m_iCondition ? MOVE : JUMP;
		m_dwStateTime = GetTickCount() + m_dwIdleTime;
		break;
	case CMario::DEAD:
		m_eInhailType = MARIO;
		m_fVelocityX = 0.f;
		m_fVelocityY -= 3.f;
		if (m_bInhail)
			m_eCurState = INHAIL;
		break;
	case CMario::INHAIL:
		isInhail();
		break;
	case CMario::END:
		break;
	default:
		break;
	}

	if (m_eCurState != INHAIL)
	{
		m_tInfo.fX += m_fVelocityX;
		m_tInfo.fY -= m_fVelocityY;
	}
	return PLAY;
}

void CMario::LateUpdate()
{
	if (m_tInfo.fX < 0 + m_iHitBoxCX * 0.5f)
		m_tInfo.fX = (float)m_iHitBoxCX * 0.5f;

	if (m_bIsDamage && m_dwDamageTime < GetTickCount())
		m_bIsDamage = false;

	FrameMove();
	SceneChange();
	UpdateRect(m_fImageX, m_fImageY);

	if (m_fVelocityY != 0.f)
		m_fVelocityY -= 0.11f;
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
	if (iDamage == 20 || iDamage == 10)
	{
		// 태클과 공기의 데미지는 무시
	}
	else if (!m_bIsDamage)
	{
		CActor::ApplyDamage(iDamage);
		m_dwDamageTime = GetTickCount() + 500;
		m_bIsDamage = true;

		if (m_iHp <= 0)
			m_eCurState = DEAD;
	}
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
	float fX = m_bFlipX ? 100.f : -100.f;
	fX = m_tInfo.fX + fX;
	float fY = m_tInfo.fY + 10.f;

	GameManager->AddObject(CAbsFactory<CInhailStar>::CreateInhailStar(fX, fY, NORMAL), OBJ_ENEMY);
	SoundManager->PlaySound(TEXT("GroundAttack.wav"), CSoundManager::ENEMY);
}

void CMario::Shot()
{
	float fX = m_bFlipX ? 10.f : -10.f;
	GameManager->AddObject(CAbsFactory<CMarioFire>::CreateObject(m_tInfo.fX + fX, m_tInfo.fY, m_bFlipX), ENEMY_ATT);
	SoundManager->PlaySound(TEXT("Mario_Fire.wav"), CSoundManager::ENEMY);


	if (m_iHp < 300)
		GameManager->AddObject(CAbsFactory<CMarioFire>::CreateObject(m_tInfo.fX - fX, m_tInfo.fY, !m_bFlipX), ENEMY_ATT);
}
