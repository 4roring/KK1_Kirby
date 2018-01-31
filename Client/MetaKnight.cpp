#include "stdafx.h"
#include "MetaKnight.h"
#include "Eff_Dash.h"
#include "InhailStar.h"
#include "Eff_SlashSkill.h"
#include "Eff_Tornado.h"
#include "UI_BossHp.h"

CMetaKnight::CMetaKnight()
	: m_dwIdleTime(3000), m_pTornado(nullptr)
{
}


CMetaKnight::~CMetaKnight()
{
}

void CMetaKnight::Initialize()
{
	m_iMaxHp = 1000;
	m_iHp = m_iMaxHp;
	SetPosToStart();
	m_tInfo.fCX = 480;
	m_tInfo.fCY = 480;
	m_iHitBoxCX = 50;
	m_iHitBoxCY = 50;

	m_fImageX = 0.f;
	m_fImageY = 0.f;

	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;

	m_ePreState = END;
	m_eCurState = APPEAR1;

	m_iCondition = 0;
	m_iPatternCnt = 0;
	m_fMaxBackMove = 0;

	m_dwStateTime = GetTickCount() + 1000;
	m_dwIdleTime = 200;
	m_dwDamageTime = GetTickCount();

	m_pFrameKey = TEXT("MetaKnight_Apper");
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 15;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 60;

	m_pTarget = GameManager->GetPlayer();
	m_eInhailType = TYPE_BOSS;

	GameManager->AddObject(CAbsFactory<CUI_BossHp>::CreateObject(this), OBJ_UI);
}

void CMetaKnight::LateInit()
{
}

OBJ_STATE CMetaKnight::Update()
{
	m_bInhail = false;
	switch (m_eCurState)
	{
	case CMetaKnight::APPEAR1:
		if (m_tFrame.iStart == m_tFrame.iEnd)
			m_eCurState = APPEAR2;
		break;
	case CMetaKnight::APPEAR2:
		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			m_eCurState = IDLE;
			m_dwStateTime = GetTickCount() + m_dwIdleTime;
		}
		break;
	case CMetaKnight::IDLE:
		if (m_dwStateTime + m_dwIdleTime < GetTickCount())
		{
			switch (m_iCondition)
			{
			case 0:
				m_eCurState = MOVE;
				m_iCondition = 0;
				break;
			case 1: // 대시 어택
				m_eCurState = DASH;
				GameManager->AddObject(CAbsFactory<CEff_Dash>::CreateObject(m_tInfo.fX, m_tInfo.fY - 10.f, m_bFlipX), OBJ_EFFECT);
				break;
			case 2: // 검기 발사
				m_eCurState = ATTACK_DOWN;
				break;
			case 3: // 토네이도
				m_eCurState = SKILL2;
				break;
			}
		}
		break;
	case CMetaKnight::MOVE:
		switch (m_iCondition)
		{
		case 0:
			m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
			m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_Right") : TEXT("MetaKnight_Left");
			m_fVelocityX = m_bFlipX ? 3.5f : -3.5f;

			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 150.f)
				m_iCondition = rand() % 3 + 1;
			break;
		case 1: // Back Move (대시 어택으로 변경)
			m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
			m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_Right") : TEXT("MetaKnight_Left");
			m_fVelocityX = m_bFlipX ? -3.5f : 3.5f;
			m_fMaxBackMove = m_bFlipX ? 100.f : 600.f;
			if (m_bFlipX && m_tInfo.fX < m_fMaxBackMove
				|| !m_bFlipX && m_tInfo.fX > m_fMaxBackMove)
			{
				m_eCurState = IDLE;
				m_iCondition = 1; // 대시 어택.
				m_fVelocityX = 0;
				m_dwStateTime = GetTickCount() + m_dwIdleTime;
			}
			break;
		case 2:
		case 3: // 점프로 넘어감.
			m_eCurState = JUMP;
			// 컨디션을 지정해줘서 일반점프와 빽점프를 하게한다.
			m_iCondition = rand() % 2;
			break;
		}
		break;
	case CMetaKnight::DASH:
		m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
		m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_Right") : TEXT("MetaKnight_Left");
		m_fVelocityX = m_bFlipX ? 7.5f : -7.5f;

		if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 100.f)
		{
			SoundManager->PlaySound(TEXT("MetaKnight_DashSlash.wav"), CSoundManager::ENEMY);
			m_eCurState = DASHATTACK;
		}
			
		break;
	case CMetaKnight::DASHATTACK:
		m_fVelocityX = m_bFlipX ? 1.5f : -1.5f;
		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			CreateInhailStar(1);
			m_eCurState = JUMP;
			m_iCondition = 1;
		}
		break;
	case CMetaKnight::JUMP:
		switch (m_iCondition)
		{
		case 0: // 일반 점프
			if (m_tFrame.iStart == 9 && m_fVelocityY == 0.f)
			{
				m_eCurState = IDLE;
				m_iCondition = 0;
				m_fVelocityX = 0;
				m_dwStateTime = GetTickCount() + m_dwIdleTime;
			}
			else if (m_tFrame.iStart == 9)
			{
				// TODO: 점프 어택 또는 점프 다운 어택으로 전환
				int iPattern = rand() % 3;

				switch (iPattern)
				{
				case 0: m_eCurState = JUMP_ATTACK;
					break;
				case 1: m_eCurState = JUMPDOWN_ATTACK;
					break;
				default:
					break;
				}
				m_tFrame.dwSpeed = 2000;
				m_fVelocityY -= 0.81f;
			}
			else if (m_tFrame.iStart == 0)
			{
				m_tFrame.iStart = 1;
				m_fVelocityY = 8.f;
				m_fVelocityX = m_bFlipX ? 2.8f : -2.8f;
			}
			break;
		case 1: // 빽 점프
			if (m_tFrame.iStart == 9 && m_fVelocityY == 0.f)
			{
				m_eCurState = IDLE;
				// TODO: Condition 지정해서 스킬 사용하게 지정.
				// 0: MOVE, 2: SKILL1, 3: SKILL2

				if (m_iHp < 500)
					while (m_iCondition == 1)
						m_iCondition = rand() % 4;
				else
					m_iCondition = 0;

				m_fVelocityX = 0;
			}
			else if (m_tFrame.iStart == 9)
			{
				m_tFrame.dwSpeed = 5000;
				m_fVelocityY -= 0.31f;
			}
			else if (m_tFrame.iStart == 0)
			{
				m_tFrame.iStart = 1;
				m_fVelocityY = 3.f;
				m_fVelocityX = m_bFlipX ? -10.5f : 10.5f;
			}
			break;
		}
		break;
	case CMetaKnight::JUMP_ATTACK:
		if (m_tFrame.iStart < 5)
			m_fVelocityY -= 0.61f;

		if(m_tFrame.iStart == 0)
			SoundManager->PlaySound(TEXT("MetaKnight_Slash.wav"), CSoundManager::ENEMY);

		if (m_tFrame.iStart == 4 && m_iPatternCnt < 1)
		{
			m_tFrame.iStart = 0;
			++m_iPatternCnt;
		}
		else if (m_tFrame.iStart == 6)
			m_tFrame.dwTime = 5000;

		if (m_fVelocityY == 0.f)
		{
			m_eCurState = IDLE;
			m_iCondition = 0;
			m_fVelocityX = 0;
			m_iPatternCnt = 0;
			m_dwStateTime = GetTickCount() + m_dwIdleTime;
		}
		break;
	case CMetaKnight::JUMPDOWN_ATTACK:
		if (m_fVelocityY == 0.f && m_tFrame.iStart == 1)
		{
			m_tFrame.iStart = 2;
			m_dwStateTime = GetTickCount() + 300;
			CreateInhailStar(2);
			SoundManager->PlaySound(TEXT("GroundAttack.wav"), CSoundManager::ENEMY);
		}
		else if (m_tFrame.iStart == 1)
		{
			m_tFrame.dwSpeed = 3000;
			m_fVelocityX = 0.f;
			m_fVelocityY -= 1.1f;
		}
		else if (m_tFrame.iStart == 2)
		{
			GameManager->CameraShakingStart(5.f);

			if (m_dwStateTime < GetTickCount())
			{
				GameManager->CameraShakingEnd();
				m_eCurState = IDLE;
				m_iCondition = 0;
				m_fVelocityX = 0;
				m_dwStateTime = GetTickCount() + m_dwIdleTime;
			}
		}
		break;
	case CMetaKnight::ATTACK_DOWN:
		if (m_tFrame.iStart == 0)
			SoundManager->PlaySound(TEXT("MetaKnight_Slash.wav"), CSoundManager::ENEMY);

		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			float fX = m_bFlipX ? 100.f : -100.f;
			GameManager->AddObject(CAbsFactory<CEff_SlashSkill>::CreateObject(m_tInfo.fX + fX, m_tInfo.fY, m_bFlipX), ENEMY_ATT);
			m_eCurState = ATTACK_UP;
		}
		break;
	case CMetaKnight::ATTACK_UP:
		if (m_tFrame.iStart == 0)
			SoundManager->PlaySound(TEXT("MetaKnight_Slash.wav"), CSoundManager::ENEMY);

		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			float fX = m_bFlipX ? 100.f : -100.f;
			GameManager->AddObject(CAbsFactory<CEff_SlashSkill>::CreateObject(m_tInfo.fX + fX, m_tInfo.fY, m_bFlipX), ENEMY_ATT);
			m_eCurState = SKILL1;
			m_dwStateTime = GetTickCount() + 200;
		}
		break;
	case CMetaKnight::SKILL1: // Slash Skill
		if (m_tFrame.iStart == 1)
			SoundManager->PlaySound(TEXT("MetaKnight_Slash.wav"), CSoundManager::ENEMY);

		if (m_tFrame.iStart == m_tFrame.iEnd - 1)
		{
			float fX = m_bFlipX ? 100.f : -100.f;

			if (m_iPatternCnt == 0)
			{
				GameManager->AddObject(CAbsFactory<CEff_SlashSkill>::CreateObject(m_tInfo.fX + fX, m_tInfo.fY, m_bFlipX), ENEMY_ATT);
				++m_iPatternCnt;
			}
		}

		if (m_tFrame.iStart == m_tFrame.iEnd)
			m_tFrame.dwSpeed = 500;
		else if (m_tFrame.iStart == 0 && m_tFrame.dwSpeed == 500)
		{
			m_eCurState = IDLE;
			// TODO: Condition 지정해서 스킬 사용하게 지정.
			// 0: MOVE, 1: 대시어택, 2: SKILL1, 3: SKILL2
			m_iCondition = 0;
			m_fVelocityX = 0;
			m_iPatternCnt = 0;
			m_dwStateTime = GetTickCount() + m_dwIdleTime + 500;
		}
		else if (m_dwStateTime > GetTickCount())
			m_tFrame.dwSpeed = 1000;
		else
			m_tFrame.dwSpeed = 30;

		break;
	case CMetaKnight::SKILL2: // Tornado Skill
		if (m_tFrame.iStart == 3)
		{
			++m_iPatternCnt;
			m_tFrame.iStart = 0;
			if (m_iPatternCnt > 4)
			{
				// 토네이도 발사!
				m_tFrame.iStart = 4;
				m_tFrame.dwSpeed = 5000;
				if (m_pTornado == nullptr)
				{
					GameManager->AddObject(CAbsFactory<CEff_Tornado>::CreateObject(m_tInfo.fX, m_tInfo.fY - 150, m_bFlipX), ENEMY_ATT);
					m_pTornado = GameManager->GetObjList(ENEMY_ATT).back();
				}

			}
		}

		if (m_tFrame.iStart == 4 && m_pTornado)
		{
			// 토네이도가 일정 위치에서 사라지면 IDLE로 전환
			if (m_pTornado->GetInfo().fX < 150.f && !m_bFlipX ||
				m_pTornado->GetInfo().fX > 600.f && m_bFlipX)
			{
				m_pTornado->SetActive(false);
				m_pTornado = nullptr;

				m_eCurState = IDLE;
				// TODO: Condition 지정해서 스킬 사용하게 지정.
				// 0: MOVE, 1: 대시어택, 2: SKILL1, 3: SKILL2
				m_iCondition = 0;
				m_fVelocityX = 0;
				m_iPatternCnt = 0;
				m_dwStateTime = GetTickCount() + m_dwIdleTime + 500;
			}
		}
		break;
	case CMetaKnight::DEAD:
		switch (m_tFrame.iScene)
		{
		case 0:
			m_fVelocityX = 0.f;
			m_fVelocityY = 0.f;

			if (m_tFrame.iStart == m_tFrame.iEnd)
			{
				m_tFrame.iScene = 1;
				m_tFrame.iStart = 0;
				m_tFrame.iEnd = 5;
			}
			break;
		case 1:
			if (m_tFrame.iStart == m_tFrame.iEnd)
			{
				m_tFrame.iScene = 2;
				m_tFrame.iStart = 0;
				m_tFrame.iEnd = 14;
			}
			break;
		case 2:
			if (m_tFrame.iStart == m_tFrame.iEnd)
			{
				m_tFrame.dwSpeed = 5000;
				m_fVelocityY = 20.f;
			}
			break;
		}
		break;
	case CMetaKnight::END:
		break;
	default:
		break;
	}

	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY -= m_fVelocityY;

	return PLAY;
}

void CMetaKnight::LateUpdate()
{
	if (m_tInfo.fX < 0 + m_iHitBoxCX * 0.5f)
		m_tInfo.fX = (float)m_iHitBoxCX * 0.5f;

	if (m_iHp <= 0)
		m_eCurState = DEAD;

	if (m_bIsDamage && m_dwDamageTime < GetTickCount())
		m_bIsDamage = false;

	FrameMove();
	SceneChange();
	UpdateRect(m_fImageX, m_fImageY);

	//if (m_eCurState != DEAD)
	//	m_fVelocityY -= 0.5f;
}

void CMetaKnight::Render(HDC hDC)
{
	if (!m_bIsDamage)
		DrawObject(hDC, m_pFrameKey);
	else if (m_bIsDamage && g_iFrame % 3 == 0)
		DrawObject(hDC, m_pFrameKey);

	DrawUI(hDC, TEXT("BossName"), 430, 520, 120, 30, 0);

	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);
}

void CMetaKnight::Release()
{
}

void CMetaKnight::ApplyDamage(int iDamage)
{
	if (iDamage == 20 || iDamage == 10)
	{
		// 태클과 공기의 데미지는 무시
	}
	else if (!m_bIsDamage)
	{
		CActor::ApplyDamage(iDamage);
		m_bIsDamage = true;
		m_dwDamageTime = GetTickCount() + 500;
	}
}

void CMetaKnight::SceneChange()
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iStart = 0;

		m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_Right") : TEXT("MetaKnight_Left");

		switch (m_eCurState)
		{
		case CMetaKnight::APPEAR1:
			m_pFrameKey = TEXT("MetaKnight_Apper");
			m_tFrame.iEnd = 15;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 80;
			break;
		case CMetaKnight::APPEAR2:
			m_pFrameKey = TEXT("MetaKnight_Apper");
			m_tFrame.iEnd = 5;
			m_tFrame.iScene = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 80;
			break;
		case CMetaKnight::IDLE:
			m_tFrame.iEnd = 0;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 60;
			break;
		case CMetaKnight::MOVE:
			m_tFrame.iEnd = 6;
			m_tFrame.iScene = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case CMetaKnight::DASH:
			m_tFrame.iEnd = 4;
			m_tFrame.iScene = 2;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 30;
			break;
		case CMetaKnight::DASHATTACK:
			m_tFrame.iEnd = 5;
			m_tFrame.iScene = 3;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 50;
			break;
		case CMetaKnight::ATTACK_DOWN:
			m_tFrame.iEnd = 7;
			m_tFrame.iScene = 4;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 30;
			break;
		case CMetaKnight::ATTACK_UP:
			m_tFrame.iEnd = 7;
			m_tFrame.iScene = 5;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 30;
			break;
		case CMetaKnight::JUMP:
			m_tFrame.iEnd = 9;
			m_tFrame.iScene = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 40;
			break;
		case CMetaKnight::JUMP_ATTACK:
			m_tFrame.iEnd = 6;
			m_tFrame.iScene = 7;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 30;
			break;
		case CMetaKnight::JUMPDOWN_ATTACK:
			m_tFrame.iEnd = 2;
			m_tFrame.iScene = 8;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case CMetaKnight::SKILL1:
			m_tFrame.iEnd = 7;
			m_tFrame.iScene = 4;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 30;
			break;
		case CMetaKnight::SKILL2:
			m_tFrame.iEnd = 4;
			m_tFrame.iScene = 9;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 80;
			break;
		case CMetaKnight::DEAD:
			m_pFrameKey = TEXT("MetaKnight_Dead");
			m_tFrame.iEnd = 11;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 80;
			break;
		case CMetaKnight::END:
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CMetaKnight::CreateInhailStar(int iCount)
{
	float fX = m_bFlipX ? 130.f : -130.f;
	float fY = m_tInfo.fY + 10.f;
	
	if (iCount == 1)
	{
		fX = m_tInfo.fX + fX;
		GameManager->AddObject(CAbsFactory<CInhailStar>::CreateInhailStar(fX, fY, NORMAL), OBJ_ENEMY);
	}
	else if (iCount == 2)
	{
		GameManager->AddObject(CAbsFactory<CInhailStar>::CreateInhailStar(m_tInfo.fX + fX, fY, NORMAL), OBJ_ENEMY);
		GameManager->AddObject(CAbsFactory<CInhailStar>::CreateInhailStar(m_tInfo.fX - fX, fY, NORMAL), OBJ_ENEMY);
	}

	

	
}