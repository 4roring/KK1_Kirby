#include "stdafx.h"
#include "MetaKnight.h"
#include "Eff_Dash.h"
#include "InhailStar.h"

CMetaKnight::CMetaKnight()
	: m_dwIdleTime(3000)
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

	m_pFrameKey = TEXT("MetaKnight_Apper");
	m_dwStateTime = GetTickCount() + 1000;
	m_dwIdleTime = 200;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 15;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 60;

	m_pTarget = GameManager->GetPlayer();
	m_eInhailType = TYPE_BOSS;
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
				break;
			case 3: // 토네이도
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
			m_fVelocityX = m_bFlipX ? 2.5f : -2.5f;

			if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 100.f)
				m_iCondition = 2;
				//m_iCondition = rand() % 2 + 1;
			break;
		case 1: // 뒤로 빽
			m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
			m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_Right") : TEXT("MetaKnight_Left");
			m_fVelocityX = m_bFlipX ? -2.5f : 2.5f;
			m_fMaxBackMove = m_bFlipX ? 100.f : 600.f;
			if (m_bFlipX && m_tInfo.fX < m_fMaxBackMove
				|| !m_bFlipX && m_tInfo.fX > m_fMaxBackMove)
			{
				m_eCurState = IDLE;
				// IDLE 컨디션 상태를 지정하여 특수 공격 사용.
				m_iCondition = 1;
				m_fVelocityX = 0;
				m_dwStateTime = GetTickCount() + m_dwIdleTime;
			}
			break;
		case 2: // 점프로 넘어감.
			m_eCurState = JUMP;
			// 컨디션을 지정해줘서 일반점프와 빽점프를 하게한다.
			m_iCondition = 1;
			break;
		case 3: // 한 번 배기
			m_fVelocityX = 0;
			break;
		case 4: // 세 번 배기
			m_fVelocityX = 0;
			break;
		}
		break;
	case CMetaKnight::DASH:
		m_bFlipX = (m_tInfo.fX < m_pTarget->GetInfo().fX) ? true : false;
		m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_Right") : TEXT("MetaKnight_Left");
		m_fVelocityX = m_bFlipX ? 7.5f : -7.5f;

		if (abs(m_tInfo.fX - m_pTarget->GetInfo().fX) < 100.f)
			m_eCurState = DASHATTACK;
		break;
	case CMetaKnight::DASHATTACK:
		m_fVelocityX = m_bFlipX ? 1.5f : -1.5f;
		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			m_eCurState = JUMP;
			m_iCondition = 1;
		}

		break;
	case CMetaKnight::ATTACK_DOWN:
		if (m_tFrame.iStart == m_tFrame.iEnd)
			m_eCurState = ATTACK_UP;
		break;
	case CMetaKnight::ATTACK_UP:
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
				m_eCurState = JUMPDOWN_ATTACK;

				m_tFrame.dwSpeed = 5000;
				m_fVelocityY -= 0.81f;
			}
			else if (m_tFrame.iStart == 0)
			{
				m_tFrame.iStart = 1;
				m_fVelocityY = 8.f;
				m_fVelocityX = m_bFlipX ? 2.5f : -2.5f;
			}
			break;
		case 1: // 빽 점프
			if (m_tFrame.iStart == 9 && m_fVelocityY == 0.f)
			{
				m_eCurState = IDLE;
				// TODO: Condition 지정해서 스킬 사용하게 지정.
				// 0: MOVE, 1: 대시어택, 2: SKILL1, 3: SKILL2
				m_iCondition = 1;
				m_fVelocityX = 0;
			}
			else if (m_tFrame.iStart == 9)
			{
				m_tFrame.dwSpeed = 5000;
				m_fVelocityY -= 0.41f;
			}
			else if (m_tFrame.iStart == 0)
			{
				m_tFrame.iStart = 1;
				m_fVelocityY = 3.f;
				m_fVelocityX = m_bFlipX ? -5.5f : 5.5f;
			}
			break;
		}
		break;
	case CMetaKnight::JUMP_ATTACK:
		if(m_tFrame.iStart < 5)
			m_fVelocityY -= 0.61f;

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
		}
		else if (m_tFrame.iStart == 1)
		{
			m_tFrame.dwSpeed = 3000;
			m_fVelocityX = 0.f;
			m_fVelocityY -= 1.1f;
		}
		else if (m_tFrame.iStart == 2)
		{
			if (m_dwStateTime < GetTickCount())
			{
				m_eCurState = IDLE;
				m_iCondition = 0;
				m_fVelocityX = 0;
				m_dwStateTime = GetTickCount() + m_dwIdleTime;
			}
		}
		break;
	case CMetaKnight::SKILL1: // Slash Skill
		break;
	case CMetaKnight::SKILL2: // Tornado Skill
		break;
	case CMetaKnight::DEAD:
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
		m_tInfo.fX = 0;

	FrameMove();

	SceneChange();
	UpdateRect(m_fImageX, m_fImageY);

	//if (m_eCurState != DEAD)
	//	m_fVelocityY -= 0.5f;
}

void CMetaKnight::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);

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
	else
		CActor::ApplyDamage(iDamage);
}

void CMetaKnight::SceneChange()
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iStart = 0;

		m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_Right"):TEXT("MetaKnight_Left");

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
			break;
		case CMetaKnight::END:
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CMetaKnight::CreateInhailStar()
{
	float fX = m_bFlipX ? 130.f : -130.f;
	fX = m_tInfo.fX + fX;
	float fY = m_tInfo.fY + 10.f;

	GameManager->AddObject(CAbsFactory<CInhailStar>::CreateInhailStar(fX, fY, NORMAL), OBJ_ENEMY);
}