#include "stdafx.h"
#include "DDD.h"
#include "InhailStar.h"
#include "Door.h"
#include "UI_BossHp.h"

CDDD::CDDD()
	: m_dwIdleTime(2000)
{
}


CDDD::~CDDD()
{
	Release();
}

void CDDD::Initialize()
{
	// 상태 초기화
	m_iMaxHp = 600;
	m_iHp = m_iMaxHp;
	SetPosToStart();
	m_tInfo.fCX = 330;
	m_tInfo.fCY = 330;
	m_iHitBoxCX = 100;
	m_iHitBoxCY = 120;

	m_fImageX = 0.f;
	m_fImageY = -105.f;

	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;

	m_ePreState = END;
	m_eCurState = IDLE;

	m_iCondition = 0;
	m_iPatternCnt = 0;

	m_pFrameKey = TEXT("DDD_Left");
	m_dwStateTime = GetTickCount() + 3000;
	m_pTarget = GameManager->GetPlayer();

	m_eInhailType = TYPE_BOSS;

	GameManager->AddObject(CAbsFactory<CUI_BossHp>::CreateObject(this), OBJ_UI);
}

void CDDD::LateInit()
{
}

OBJ_STATE CDDD::Update()
{
	m_bInhail = false;

	switch (m_eCurState)
	{
	case IDLE:
		m_fVelocityX = 0.f;
		m_iPatternCnt = 0;
		if (m_dwStateTime < GetTickCount())
		{
			// 다른 행동으로 전환.
			m_eCurState = MOVE;
			m_dwStateTime = GetTickCount() + m_dwIdleTime;
			if (++m_iCondition > 10)
				m_iCondition = 1;
		}
		break;
	case MOVE:
		m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
		m_pFrameKey = m_bFlipX ? TEXT("DDD_Right") : TEXT("DDD_Left");

		m_fVelocityX = m_bFlipX ? 1.f : -1.f;

		if (m_tFrame.iStart & 1)
			m_fVelocityY = 1.5f;

		switch (m_iCondition)
		{
		case 1:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 200.f)
				m_eCurState = JUMP;
			break;
		case 2:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 400.f)
				m_eCurState = HAMMER_RUN;
			break;
		case 3:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 150.f)
				m_eCurState = HAMMER_JUMP;
			break;
		case 4:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 400.f)
				m_eCurState = HAMMER_RUN;
			break;
		case 5:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 400.f)
				m_eCurState = JUMP;
			break;
		case 6:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 150.f)
				m_eCurState = HAMMER_JUMP;
			break;
		case 7:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 400.f)
				m_eCurState = HAMMER_RUN;
			break;
		case 8:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 400.f)
				m_eCurState = HAMMER_RUN;
			break;
		case 9:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 400.f)
				m_eCurState = JUMP;
			break;
		case 10:
			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 150.f)
				m_eCurState = HAMMER_JUMP;
			break;
		}
		break;
	case JUMP:
		if (m_tFrame.iStart == 0)
		{
			m_fVelocityY = 10.f;
			m_tFrame.iStart = 1;
		}
		else if (m_tFrame.iStart == 2 && m_fVelocityY == 0)
		{
			if (m_iPatternCnt == 0)
			{
				m_tFrame.iStart = 0;
				++m_iPatternCnt;
			}
			else if (m_dwStateTime < GetTickCount()) // 패턴 종료
			{
				GameManager->CameraShakingStart(5.f, 500);
				CreateInhailStar();
				m_eCurState = IDLE;
				m_dwStateTime = GetTickCount() + m_dwIdleTime;
			}
		}
		
		if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 10)
		{
			m_tFrame.iStart = 2;
			m_fVelocityX = 0.f;
			m_dwStateTime = GetTickCount() + 500;
		}
		else if (m_tFrame.iStart == 1)
		{
			m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
			m_pFrameKey = m_bFlipX ? TEXT("DDD_Right") : TEXT("DDD_Left");
			m_tFrame.iStart = 1;
			m_fVelocityY += 0.3f;
			m_fVelocityX = m_bFlipX ? 7.f : -7.f;
		}
		break;
	case HAMMER_RUN:
		m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
		m_pFrameKey = m_bFlipX ? TEXT("DDD_Right") : TEXT("DDD_Left");

		m_fVelocityX = m_bFlipX ? 2.f : -2.f;
		if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 150.f)
		{
			m_eCurState = HAMMER_ATTACK;
			m_dwStateTime = GetTickCount() + 400;
		}
		break;
	case HAMMER_JUMP:
		if (m_tFrame.iStart == 1)
		{
			m_fVelocityY += 2.f;
			m_tFrame.dwSpeed = 5000;
		}
		
		if (m_fVelocityY > 13.f)
		{
			m_iPatternCnt = 1;
			m_eCurState = HAMMER_ATTACK;
		}
		break;
	case HAMMER_ATTACK:
		switch (m_iPatternCnt)
		{
		case 0: // 지상 해머 공격
			if (m_tFrame.iStart == 0)
			{
				m_fVelocityX = 0;
				m_tFrame.dwSpeed = 5000;
				if (m_dwStateTime < GetTickCount())
				{
					m_tFrame.dwSpeed = 100;
					// TODO: HITBOX 생성
				}
			}
			break;
		case 1: // 점프 해머 공격
			if (m_fVelocityY == 0.f)
				m_tFrame.dwSpeed = 100;
			else
			{
				m_tFrame.dwSpeed = 5000;
				m_fVelocityY -= 0.5f;
			}
			break;
		}
		if (m_tFrame.iStart == m_tFrame.iEnd) // 패턴 종료
		{
			CreateInhailStar();
			m_eCurState = IDLE;
			m_dwStateTime = GetTickCount() + m_dwIdleTime;
		}
		break;
	case DAMAGE:
		if (m_dwStateTime < GetTickCount()) // 패턴 종료
		{
			m_eCurState = IDLE;
			m_dwStateTime = GetTickCount() + m_dwIdleTime - 200;

			if (m_iHp <= 0)
			{
				GameManager->AddObject(CAbsFactory<CDoor>::CreateDoor(588.f, 172.f, SCENE_SPECIAL), OBJ_INTERECTION);
				m_eCurState = DEAD;
			}
		}
		break;
	case DEAD:
		m_fVelocityX = 0.f;
		m_fVelocityY = 0.f;
		m_bActive = false;
		if (m_tFrame.iStart == m_tFrame.iEnd)
			m_tFrame.iStart = 1;
		break;
	}

	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY -= m_fVelocityY;

	return PLAY;
}

void CDDD::LateUpdate()
{
	if (m_bIsDamage && m_dwDamageTime < GetTickCount())
		m_bIsDamage = false;

	FrameMove();
	SceneChange();
	UpdateRect(m_fImageX, m_fImageY);

	if(m_eCurState != DEAD)
		m_fVelocityY -= 0.5f;
}

void CDDD::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);

	if (!m_bIsDamage)
		DrawObject(hDC, m_pFrameKey);
	else if (m_bIsDamage && g_iFrame % 3 == 0)
		DrawObject(hDC, m_pFrameKey);

	DrawUI(hDC, TEXT("BossName"), 430, 520, 120, 30, 1);
}

void CDDD::Release()
{
}

void CDDD::ApplyDamage(int iDamage)
{
	if (iDamage == 20 || iDamage == 10)
	{
		// 태클과 공기의 데미지는 무시
	}
	else if(!m_bIsDamage)
	{
		CActor::ApplyDamage(iDamage);
		m_eCurState = DAMAGE;
		m_dwStateTime = GetTickCount() + 300;
		m_dwDamageTime = GetTickCount() + 3000;
		m_bIsDamage = true;
	}
}

void CDDD::SceneChange()
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iStart = 0;

		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iEnd = 3;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			break;
		case MOVE:
			m_tFrame.iEnd = 3;
			m_tFrame.iScene = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			break;
		case JUMP:
			m_tFrame.iEnd = 2;
			m_tFrame.iScene = 2;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 3000;
			break;
		case HAMMER_RUN:
			m_tFrame.iEnd = 3;
			m_tFrame.iScene = 3;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case HAMMER_JUMP:
			m_tFrame.iEnd = 1;
			m_tFrame.iScene = 4;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case HAMMER_ATTACK:
			m_tFrame.iEnd = 3;
			m_tFrame.iScene = 5;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case DAMAGE:
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 1000;
			break;
		case DEAD:
			m_tFrame.iEnd = 2;
			m_tFrame.iScene = 7;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 1000;
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CDDD::CreateInhailStar()
{
	float fX = m_bFlipX ? 130.f : -130.f;
	fX = m_tInfo.fX + fX;
	float fY = m_tInfo.fY + 10.f;

	GameManager->AddObject(CAbsFactory<CInhailStar>::CreateInhailStar(fX, fY, NORMAL), OBJ_ENEMY);
	SoundManager->PlaySound(TEXT("GroundAttack.wav"), CSoundManager::ENEMY);
}