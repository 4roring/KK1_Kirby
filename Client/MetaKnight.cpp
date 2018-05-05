#include "stdafx.h"
#include "MetaKnight.h"
#include "Eff_Dash.h"
#include "InhailStar.h"
#include "Eff_SlashSkill.h"
#include "Eff_Tornado.h"
#include "UI_BossHp.h"
#include "Door.h"
#include "HitBox.h"

CMetaKnight::CMetaKnight()
	: m_dwIdleTime(3000), m_pTornado(nullptr), m_pHitBox(nullptr)
{
}


CMetaKnight::~CMetaKnight()
{
	Release();
}

void CMetaKnight::Initialize()
{
	m_iMaxHp = 2000;
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

	m_bDashAttack = false;
	m_bSlashSkill = false;
	m_bTornadoSkill = false;

	GameManager->AddObject(CAbsFactory<CUI_BossHp>::CreateObject(this), OBJ_UI);
}

void CMetaKnight::LateInit()
{
}

OBJ_STATE CMetaKnight::Update()
{
	if (!m_bActive)
	{
		GameManager->AddObject(CAbsFactory<CDoor>::CreateDoor(588.f, 172.f, SCENE_END), OBJ_INTERECTION);
		return DESTROY;
	}

	m_bInhail = false;
	
	UpdateState();

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
	if (m_pHitBox)
	{
		m_pHitBox->SetActive(false);
		m_pHitBox = false;
	}
}

void CMetaKnight::ApplyDamage(int iDamage)
{
	if (iDamage == 20 || iDamage == 10)	return;
	
	if (!m_bIsDamage)
	{
		CActor::ApplyDamage(iDamage);
		m_bIsDamage = true;
		m_dwDamageTime = GetTickCount() + 500;
	}
}

void CMetaKnight::UpdateState()
{
	switch (m_eCurState)
	{
	case STATE::APPEAR1:
		if (m_tFrame.iStart == m_tFrame.iEnd)
			m_eCurState = APPEAR2;
		break;
	case STATE::APPEAR2:
		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			m_eCurState = IDLE;
			m_dwStateTime = GetTickCount() + m_dwIdleTime;
		}
		break;
	case STATE::IDLE: Idle();
		break;
	case STATE::MOVE: Move();
		break;
	case STATE::DASH: Dash();
		break;
	case STATE::DASHATTACK:	DashAttack();
		break;
	case STATE::JUMP: Jump();
		break;
	case STATE::JUMP_ATTACK: JumpAttack();
		break;
	case STATE::JUMPDOWN_ATTACK: JumpDownAttack();
		break;
	case STATE::ATTACK_DOWN: AttackDown();
		break;
	case STATE::ATTACK_UP: AttackUp();
		break;
	case STATE::SKILL1: Skill_1(); // Slash Skill
		break;
	case STATE::SKILL2: Skill_2(); // Tornado Skill
		break;
	case STATE::DEAD: Dead();
		break;
	case STATE::END:
		break;
	default:
		break;
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
		case STATE::APPEAR1:
			m_pFrameKey = TEXT("MetaKnight_Apper");
			SetAnimFrame(15, 0, 80);
			break;
		case STATE::APPEAR2:
			m_pFrameKey = TEXT("MetaKnight_Apper");
			SetAnimFrame(5, 1, 80);
			break;
		case STATE::IDLE:
			SetAnimFrame(0, 0, 60);
			break;
		case STATE::MOVE:
			SetAnimFrame(6, 1, 100);
			break;
		case STATE::DASH:
			SetAnimFrame(4, 2, 30);
			break;
		case STATE::DASHATTACK:
			SetAnimFrame(5, 3, 50);
			break;
		case STATE::ATTACK_DOWN:
			SetAnimFrame(7, 4, 30);
			break;
		case STATE::ATTACK_UP:
			SetAnimFrame(7, 5, 30);
			break;
		case STATE::JUMP:
			SetAnimFrame(9, 6, 40);
			break;
		case STATE::JUMP_ATTACK:
			SetAnimFrame(6, 7, 30);
			break;
		case STATE::JUMPDOWN_ATTACK:
			SetAnimFrame(2, 8, 100);
			break;
		case STATE::SKILL1:
			SetAnimFrame(7, 4, 30);
			break;
		case STATE::SKILL2:
			SetAnimFrame(4, 9, 80);
			break;
		case STATE::DEAD:
			m_pFrameKey = TEXT("MetaKnight_Dead");
			SetAnimFrame(11, 0, 80);
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
	constexpr float StarLocalPosX = 130.f;
	constexpr float StarLocalPosY = 10.f;
	float fX = m_bFlipX ? StarLocalPosX : -StarLocalPosX;
	const float fY = m_tInfo.fY + StarLocalPosY;
	
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

void CMetaKnight::Idle()
{
	if (m_dwStateTime + m_dwIdleTime < GetTickCount())
	{
		switch (m_iCondition)
		{
		case 0:
			m_eCurState = MOVE;
			m_iCondition = 0;
			break;
		case 1: // 대시 어택
			if (m_bDashAttack && m_iHp < 1000)
				m_iCondition = rand() % 6;
			else if (m_bDashAttack)
				m_iCondition = 0;
			else
			{
				m_eCurState = DASH;
				GameManager->AddObject(CAbsFactory<CEff_Dash>::CreateObject(m_tInfo.fX, m_tInfo.fY - 10.f, m_bFlipX), OBJ_EFFECT);
			}
			break;
		case 2:
		case 3: // 검기 발사
			if (m_bSlashSkill)
				m_iCondition = rand() % 6;
			else
			{
				m_eCurState = ATTACK_DOWN;
				m_bTornadoSkill = false;
			}
			break;
		case 4:
		case 5: // 토네이도
			if (m_bTornadoSkill)
				m_iCondition = rand() % 6;
			else
			{
				m_eCurState = SKILL2;
				m_bDashAttack = false;
				m_bSlashSkill = false;
			}
			break;
		}
	}
}

void CMetaKnight::Move()
{
	switch (m_iCondition)
	{
	case 0:
		m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
		m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_Right") : TEXT("MetaKnight_Left");
		m_fVelocityX = m_bFlipX ? 3.5f : -3.5f;

		if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 150.f)
			m_iCondition = rand() % 4 + 1;

		break;
	case 1:
	case 2: // Back Move (대시 어택으로 변경)
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
	case 3:
	case 4: // 점프로 넘어감.
		m_eCurState = JUMP;
		// 컨디션을 지정해줘서 일반점프와 빽점프를 하게한다.
		m_iCondition = rand() % 3;

		break;
	}
}

void CMetaKnight::Dash()
{
	m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
	m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_Right") : TEXT("MetaKnight_Left");
	m_fVelocityX = m_bFlipX ? 7.5f : -7.5f;

	if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 100.f)
	{
		if (abs(m_tInfo.fY - m_pTarget->GetInfo().fX) > 200.f)
		{
			m_eCurState = JUMP;
			m_iCondition = 1; // 대시 어택.
		}
		else
		{
			SoundManager->PlaySound(TEXT("MetaKnight_DashSlash.wav"), CSoundManager::ENEMY);
			m_eCurState = DASHATTACK;
		}
	}
}

void CMetaKnight::DashAttack()
{
	m_fVelocityX = m_bFlipX ? 1.5f : -1.5f;

	if (m_tFrame.iStart == 3)
	{
		if (m_pHitBox == nullptr)
		{
			float fX = m_bFlipX ? 90.f : -90.f;
			GameManager->AddObject(CAbsFactory<CHitBox>::CreateHitBox(m_tInfo.fX + fX, m_tInfo.fY, 130, 40, 10, true, SLASH), ENEMY_ATT);
			m_pHitBox = GameManager->GetObjList(ENEMY_ATT).back();
		}
	}

	if (m_tFrame.iStart == m_tFrame.iEnd)
	{
		if (m_pHitBox)
		{
			m_pHitBox->SetActive(false);
			m_pHitBox = false;
		}

		CreateInhailStar(1);
		m_eCurState = JUMP;
		m_iCondition = 2;
		m_bDashAttack = true;
	}
}

void CMetaKnight::Jump()
{
	switch (m_iCondition)
	{
	case 0:
	case 1: // 일반 점프
		if (m_tFrame.iStart == 9 && m_fVelocityY == 0.f)
		{
			m_eCurState = IDLE;
			m_iCondition = 0;
			m_fVelocityX = 0;
			m_dwStateTime = GetTickCount() + m_dwIdleTime;
		}
		else if (m_tFrame.iStart == 9)
		{
			// 점프 어택 또는 점프 다운 어택으로 전환
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
			m_bDashAttack = false;
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
	case 2: // 빽 점프
		if (m_tFrame.iStart == 9 && m_fVelocityY == 0.f)
		{
			m_eCurState = IDLE;
			// TODO: Condition 지정해서 스킬 사용하게 지정.
			// 0: MOVE, 2: SKILL1, 3: SKILL2

			if (m_iHp < 1000)
				while (m_iCondition == 1)
					m_iCondition = rand() % 7;
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
}

void CMetaKnight::JumpAttack()
{
	if (m_tFrame.iStart < 5)
		m_fVelocityY -= 0.61f;

	if (m_tFrame.iStart == 0)
		SoundManager->PlaySound(TEXT("MetaKnight_Slash.wav"), CSoundManager::ENEMY);

	if (m_tFrame.iStart == 4 && m_iPatternCnt < 1)
	{
		if (m_pHitBox == nullptr)
		{
			GameManager->AddObject(CAbsFactory<CHitBox>::CreateHitBox(m_tInfo.fX, m_tInfo.fY, 140, 140, 10, true, SLASH), ENEMY_ATT);
			m_pHitBox = GameManager->GetObjList(ENEMY_ATT).back();
		}
		else
			m_pHitBox->SetPos(m_tInfo.fX, m_tInfo.fY);

		m_tFrame.iStart = 0;
		++m_iPatternCnt;
	}
	else if (m_tFrame.iStart == 6)
	{
		if (m_pHitBox)
		{
			m_pHitBox->SetActive(false);
			m_pHitBox = false;
		}
		m_tFrame.dwTime = 5000;
	}

	if (m_fVelocityY == 0.f)
	{
		if (m_pHitBox)
		{
			m_pHitBox->SetActive(false);
			m_pHitBox = false;
		}
		m_eCurState = IDLE;
		m_iCondition = 0;
		m_fVelocityX = 0;
		m_iPatternCnt = 0;
		m_dwStateTime = GetTickCount() + m_dwIdleTime;
	}
}

void CMetaKnight::JumpDownAttack()
{
	if (m_fVelocityY == 0.f && m_tFrame.iStart == 1)
	{
		if (m_pHitBox)
		{
			m_pHitBox->SetActive(false);
			m_pHitBox = false;
		}
		m_tFrame.iStart = 2;
		m_dwStateTime = GetTickCount() + 300;
		CreateInhailStar(2);
		SoundManager->PlaySound(TEXT("GroundAttack.wav"), CSoundManager::ENEMY);
	}
	else if (m_tFrame.iStart == 1)
	{
		if (m_pHitBox == nullptr)
		{
			GameManager->AddObject(CAbsFactory<CHitBox>::CreateHitBox(m_tInfo.fX, m_tInfo.fY + 50, 50, 130, 10, true, SLASH), ENEMY_ATT);
			m_pHitBox = GameManager->GetObjList(ENEMY_ATT).back();
		}
		else
			m_pHitBox->SetPos(m_tInfo.fX, m_tInfo.fY + 50);

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
}

void CMetaKnight::AttackDown()
{
	if (m_tFrame.iStart == 0)
		SoundManager->PlaySound(TEXT("MetaKnight_Slash.wav"), CSoundManager::ENEMY);

	if (m_tFrame.iStart == m_tFrame.iEnd)
	{
		float fX = m_bFlipX ? 100.f : -100.f;
		GameManager->AddObject(CAbsFactory<CEff_SlashSkill>::CreateObject(m_tInfo.fX + fX, m_tInfo.fY, m_bFlipX), ENEMY_ATT);
		m_eCurState = ATTACK_UP;
	}
}

void CMetaKnight::AttackUp()
{
	if (m_tFrame.iStart == 0)
		SoundManager->PlaySound(TEXT("MetaKnight_Slash.wav"), CSoundManager::ENEMY);

	if (m_tFrame.iStart == m_tFrame.iEnd)
	{
		float fX = m_bFlipX ? 100.f : -100.f;
		GameManager->AddObject(CAbsFactory<CEff_SlashSkill>::CreateObject(m_tInfo.fX + fX, m_tInfo.fY, m_bFlipX), ENEMY_ATT);
		m_eCurState = SKILL1;
		m_dwStateTime = GetTickCount() + 200;
	}
}

void CMetaKnight::Skill_1()
{
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
		m_bSlashSkill = true;
	}
	else if (m_dwStateTime > GetTickCount())
		m_tFrame.dwSpeed = 1000;
	else
		m_tFrame.dwSpeed = 30;
}

void CMetaKnight::Skill_2()
{
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
			m_bTornadoSkill = true;
		}
	}
}

void CMetaKnight::Dead()
{
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

			if (m_tInfo.fY < -100.f)
				m_bActive = false;
		}
		break;
	}
}

void CMetaKnight::SetAnimFrame(int iEnd, int iScene, DWORD dwSpeed)
{
	m_tFrame.iEnd = iEnd;
	m_tFrame.iScene = iScene;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = dwSpeed;
}