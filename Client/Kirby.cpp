#include "stdafx.h"
#include "Kirby.h"
#include "Eff_Dash.h"
#include "Eff_Normal_FlyAtt.h"
#include "Eff_NormalAtt.h"
#include "Eff_ShootingStar.h"
#include "Eff_MiniStar.h"
#include "Eff_Transform.h"
#include "InhailStar.h"
#include "HitBox.h"
#include "UI_PlayerHp.h"
#include "MarioFire.h"

CKirby::CKirby()
{
}


CKirby::~CKirby()
{
	Release();
}

void CKirby::Initialize()
{
	// 상태 초기화
	m_iMaxHp = 60;
	m_iHp = m_iMaxHp;

	m_tInfo.fCX = 96;
	m_tInfo.fCY = 105;
	m_iHitBoxCX = 40;
	m_iHitBoxCY = 40;

	m_fImageX = 0.f;
	m_fImageY = -9.f;

	m_fSpeed = 3.8f;
	m_fJumpPow = 8.6f;

	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;
	m_fGravity = 0.0f;
	m_fDrag = 0.f;
	m_fAccX = 0.65f;
	m_fAccY = 1.2f;

	m_bFlipX = true; // Flip의 디폴트는 왼쪽(-방향)
	m_bJump = false;
	m_bIsGround = false;
	m_bDash = false;
	m_bAttack = false;
	m_bInhail = false;

	m_iInputFrame = g_iFrame;
	m_iAttSquence = 0;

	// 애니메이션 초기화
	m_pLeftKey = TEXT("Normal_Left");
	m_pRightKey = TEXT("Normal_Right");
	m_pFrameKey = m_pLeftKey;

	m_eCurState = IDLE;
	m_ePreState = END;
	m_eForm = NORMAL_FORM;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 34;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 100;

	m_iAtt = 10;

	GameManager->AddObject(CAbsFactory<CUI_PlayerHp>::CreateObject(this), OBJ_UI);
}

void CKirby::LateInit()
{
}

OBJ_STATE CKirby::Update()
{
	if (!m_bActive)
	{
		Dead();
		return PLAY;
	}

	if (m_eCurState == TRANSFORM) return PLAY;
	if (m_eCurState == DAMAGE) return PLAY;
	if (m_bEat) return PLAY;

	if (!m_bAttack)
	{
		MoveInput();
		Slide();
	}

	Move();
	Jump();
	Attack();

	m_tInfo.fX += m_fVelocityX;

	return PLAY;
}

void CKirby::LateUpdate()
{
	if (m_eCurState == DAMAGE) isDamage();

	FrameMove();

	KirbyUpdateRect();

	m_bIsGround = CCollision::PlayerToGround(this, GameManager->GetObjList(OBJ_GROUND));

	if (m_tInfo.fY + m_iHitBoxCY * 0.5f < m_iHitBoxCY)
		m_tInfo.fY += m_fVelocityY;

	if (m_tInfo.fX + m_iHitBoxCX *0.5f < m_iHitBoxCX)
		m_tInfo.fX -= m_fVelocityX;

	NoDamageState();
	Eat();
	SceneChange();
	ScrollMove();
}

void CKirby::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);

	if (m_eCurState == TRANSFORM)
	{
		GameManager->SetPause(true);
		SceneManager->DrawAlphaColor(hDC, 100, false);
		if (m_iInputFrame < g_iFrame)
		{
			GameManager->SetPause(false);
			m_eCurState = IDLE;
		}
	}

	if (!m_bNoDamage)
		DrawObject(hDC, m_pFrameKey);
	else if (m_bNoDamage && g_iFrame % 3 == 0)
		DrawObject(hDC, m_pFrameKey);
}

void CKirby::Release()
{
}

void CKirby::ApplyDamage(int iDamage)
{
	if (!m_bNoDamage)
	{
		CActor::ApplyDamage(10);
		if (m_eForm != NORMAL_FORM)
			DisTransform();
		SoundManager->StopSound(CSoundManager::PLAYER);
		if (m_pTarget)
		{
			m_pTarget->SetActive(false);
			m_pTarget = nullptr;
		}

		SoundManager->PlaySound(TEXT("Damage.wav"), CSoundManager::PLAYER);

		if (m_iHp <= 0)
		{
			m_bActive = false;
			m_bFlipX = false;
			m_fVelocityY = 8.f;
			SoundManager->StopAll();
			SoundManager->PlaySound(TEXT("Dead.wav"), CSoundManager::PLAYER);
		}
		else
		{
			m_eCurState = DAMAGE;
			m_bNoDamage = true;
		}
	}

	if (m_bSlide)
		m_bNoDamage = true;
}

void CKirby::FormChange(FORM eForm)
{
	if (eForm != NORMAL_FORM)
	{
		m_eForm = eForm;
		m_eCurState = TRANSFORM;
		m_iInputFrame = g_iFrame + 40;
		SoundManager->PlaySound(TEXT("Transform.wav"), CSoundManager::PLAYER);
		GameManager->AddObject(CAbsFactory<CEff_Transform>::CreateObject(m_tInfo.fX, m_tInfo.fY + 20.f), OBJ_EFFECT);
	}
}


void CKirby::MoveInput()
{
#ifdef _DEBUG
	if (InputManager->KeyDown('1'))
		SceneManager->SceneChange(SCENE_STAGE1);
	if (InputManager->KeyDown('2'))
		SceneManager->SceneChange(SCENE_MIDBOSS);
	if (InputManager->KeyDown('3'))
		SceneManager->SceneChange(SCENE_SPECIAL);
	if (InputManager->KeyDown('4'))
		SceneManager->SceneChange(SCENE_BOSS);

	if (InputManager->KeyDown('H'))
		m_iHp = m_iMaxHp;
#endif

	if (m_bSlide) return;

	if (InputManager->KeyDown(VK_UP))
		CCollision::InterectionDoor(this, GameManager->GetObjList(OBJ_INTERECTION));

	if (InputManager->KeyDown('A'))
	{
		if (m_eForm != NORMAL_FORM)
			DisTransform();
	}

	if (m_fVelocityX == 0 && m_fVelocityY == 0 && !m_bSlide && !m_bJump && !m_bAttack)
	{
		if (m_bInhail)
			m_eCurState = INHAILIDLE;
		else
			m_eCurState = IDLE;

		if (m_pTarget)
		{
			m_pTarget->SetActive(false);
			m_pTarget = nullptr;
		}
	}

	if (m_eCurState == INHAILIDLE && m_bInhail && !m_bAttack
		|| m_eForm != NORMAL_FORM && m_eCurState == IDLE)
	{
		if (m_tFrame.iStart == 1)
			m_tFrame.dwSpeed = 100;
		else
			m_tFrame.dwSpeed = 2000;
	}

	// 7프레임 안에 연타시 대시 입력
	if (InputManager->KeyDown(VK_LEFT) && m_iInputFrame > g_iFrame && !m_bFly)
	{
		if (!m_bAttack)
			m_bFlipX = false;
		m_bDash = true;
		SoundManager->PlaySound(TEXT("Dash.wav"), CSoundManager::PLAYER);
		CreateDashEffect();
	}
	else if (InputManager->KeyUp(VK_LEFT) && m_iInputFrame < g_iFrame && !m_bFly)
	{
		if (!m_bDash)
			m_iInputFrame = g_iFrame + 7;
		m_bDash = false;
	}

	if (InputManager->KeyDown(VK_RIGHT) && m_iInputFrame > g_iFrame && !m_bFly && !m_bDash)
	{
		if (!m_bAttack)
			m_bFlipX = true;
		m_bDash = true;
		SoundManager->PlaySound(TEXT("Dash.wav"), CSoundManager::PLAYER);
		CreateDashEffect();
	}
	else if (InputManager->KeyUp(VK_RIGHT) && m_iInputFrame < g_iFrame && !m_bFly)
	{
		if (!m_bDash)
			m_iInputFrame = g_iFrame + 7;
		m_bDash = false;
	}

	if (InputManager->Key(VK_DOWN) && !m_bNoDamage)
	{
		m_iHitBoxCY = 15;

		if (m_bInhail)
		{
			m_bEat = true;
			m_bInhail = false;
			SoundManager->PlaySound(TEXT("Eat.wav"), CSoundManager::PLAYER);
		}
		else if (!m_bSlide && !m_bFly && !m_bInhail)
		{
			m_eCurState = DOWN;
			m_bDash = false;
			if (m_tFrame.iStart == 1)
				m_tFrame.dwSpeed = 100;
			else
				m_tFrame.dwSpeed = 2000;
		}

		// 슬라이딩
		if (InputManager->KeyDown('Z') && !m_bJump && !m_bFly
			|| InputManager->KeyDown('X') && !m_bJump && !m_bFly)
		{
			m_bSlide = true;
			CreateDashEffect();
			SoundManager->PlaySound(TEXT("Slide.wav"), CSoundManager::PLAYER);
			m_iAtt = 20;

			if (m_eForm == SWORD_FORM)
				m_iAtt = 30;
		}
	}
	else if (InputManager->KeyDown('Z'))
	{
		if (m_bIsGround && !m_bJump)
		{
			m_bIsGround = false;
			m_bJump = true;
			m_fVelocityY = 1.f;
			SoundManager->PlaySound(TEXT("Jump.wav"), CSoundManager::PLAYER);
		}
		else if (m_bJump && !m_bInhail)
			m_bFly = true;
	}
	else
		m_iHitBoxCY = 40;
}

// 이동
void CKirby::Move()
{
	if (m_bSlide) return;

	if (m_bDash && !m_bAttack)
	{
		m_fAccX = 1.f;
		m_fSpeed = 5.1f;

		if (!m_bJump && !m_bFly && !m_bAttack)
			m_eCurState = DASH;

		if (m_tFrame.iStart == m_tFrame.iEnd && m_eForm == NORMAL_FORM)
			m_tFrame.iStart = 1;
	}
	else if (m_bJump)
	{
		m_fAccX = 2.f;
		m_fSpeed = 5.6f;
	}
	else if (!m_bSlide)
	{
		m_fAccX = 0.65f;
		m_fSpeed = 3.8f;
	}

	if (InputManager->Key(VK_LEFT))
	{
		if (m_bFly)
			m_fVelocityX = -3.f;
		else if (m_eCurState != DOWN && !m_bAttack)
			m_fVelocityX -= m_fAccX;

		if (!m_bAttack)
		{
			m_bFlipX = false;
			m_pFrameKey = m_pLeftKey;
		}
	}
	else if (InputManager->Key(VK_RIGHT))
	{
		if (m_bFly)
			m_fVelocityX = 3.f;
		else if (m_eCurState != DOWN && !m_bAttack)
			m_fVelocityX += m_fAccX;

		if (!m_bAttack)
		{
			m_bFlipX = true;
			m_pFrameKey = m_pRightKey;
		}
	}

	// 최대 속도를 넘지 않음
	if (m_fVelocityX > m_fSpeed && m_fVelocityX > 0)
		m_fVelocityX = m_fSpeed;
	else if (m_fVelocityX < -m_fSpeed && m_fVelocityX < 0)
		m_fVelocityX = -m_fSpeed;

	m_fVelocityX -= m_fVelocityX * 0.1f;

	if (-0.1f < m_fVelocityX && m_fVelocityX < 0.2f)
	{
		m_fVelocityX = 0.f;
		m_fSpeed = 3.8f;
	}

	if (m_fVelocityX != 0.f && m_eCurState != DOWN && !m_bDash
		&& !m_bJump && !m_bFly && m_eCurState != FLYATTACK && !m_bAttack)
		m_eCurState = MOVE;
}

void CKirby::Attack()
{
	// 공격 입력
	if (InputManager->KeyDown('X') && !m_bSlide)
	{
		if (m_bFly)
		{
			m_bFly = false;
			m_eCurState = FLYATTACK;
		}
		else if (m_bInhail)
			m_eCurState = SHOOTSTAR;
		else
		{
			if (m_eForm == NORMAL_FORM)
				SoundManager->PlaySound(TEXT("Inhail.wav"), CSoundManager::PLAYER);

			m_eCurState = ATTACK;
			m_iAttSquence = 0;
		}
		m_bAttack = true;
	}

	if (m_bAttack && m_eCurState == FLYATTACK)
	{
		m_eCurState = FLYATTACK;
		if (m_tFrame.iStart == 2)
		{
			++m_tFrame.iStart;
			float fX = m_bFlipX ? 50.f : -50.f;
			SoundManager->PlaySound(TEXT("FlyAttack.wav"), CSoundManager::PLAYER);
			GameManager->AddObject(CAbsFactory<CEff_Normal_FlyAtt>::CreateObject(m_tInfo.fX + fX, m_tInfo.fY, m_bFlipX), PLAYER_ATT);
		}
		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			m_bAttack = false;
			m_eCurState = IDLE;
		}
	}
	else if (m_bAttack && m_eCurState == SHOOTSTAR)
	{
		m_eCurState = SHOOTSTAR;
		if (m_tFrame.iStart == 0)
		{
			SoundManager->PlaySound(TEXT("ShootStar.wav"), CSoundManager::PLAYER);
			GameManager->AddObject(CAbsFactory<CEff_ShootingStar>::CreateObject(m_tInfo.fX, m_tInfo.fY - 10.f, m_bFlipX), PLAYER_ATT);
			m_eInhailType = EMPTY;
			++m_tFrame.iStart;
		}

		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			m_bAttack = false;
			m_bInhail = false;
			m_eCurState = IDLE;
		}
	}
	else if (InputManager->Key('X') && m_bAttack && m_eForm == NORMAL_FORM)
	{
		// 흡수
		if (m_bInhail)
			m_eCurState = INHAIL;
		else
			m_eCurState = ATTACK;
		m_bDash = false;

		if (m_pTarget == nullptr && m_iAttSquence == 0)
		{
			GameManager->AddObject(CAbsFactory<CEff_NormalAtt>::CreateObject(this), OBJ_EFFECT);
			m_pTarget = GameManager->GetObjList(OBJ_EFFECT).back();
		}

		if (m_iAttSquence < 10)
		{
			if (m_tFrame.iStart == 7)
			{
				m_tFrame.iStart = 6;
				++m_iAttSquence;
			}
		}

		if (m_iAttSquence == 10)
		{
			if (m_pTarget)
			{
				SoundManager->StopSound(CSoundManager::PLAYER);
				m_pTarget->SetActive(false);
				m_pTarget = nullptr;
			}
		}

		if (m_bInhail)
			m_iAttSquence = 10;

		if (m_tFrame.iStart == m_tFrame.iEnd)
			m_bAttack = false;
	}
	else if (InputManager->KeyUp('X') && m_bAttack && m_eForm == NORMAL_FORM)
	{
		SoundManager->StopSound(CSoundManager::PLAYER);
		m_bAttack = false;
		m_iAttSquence = 0;
		if (m_pTarget)
		{
			m_pTarget->SetActive(false);
			m_pTarget = nullptr;
		}
	}
	else if (m_eForm == SWORD_FORM && m_bAttack && !m_bFly) SwordAttack();
	else if (m_eForm == MARIO_FORM && m_bAttack && !m_bFly) MarioAttack();
}

// 점프, 날기
void CKirby::Jump()
{
	if (InputManager->Key('Z') && m_bJump)
	{
		if (m_bFly)
		{
			m_fVelocityY = 3.5f;
			m_bDash = false;
			if (m_iInputFrame < g_iFrame)
			{
				SoundManager->PlaySound(TEXT("Fly.wav"), CSoundManager::PLAYER);
				m_fGravity = 0.f;
				m_iInputFrame = g_iFrame + 15;
			}
		}
		else
			m_fVelocityY += m_fAccY;

		if (m_fVelocityY > m_fJumpPow && !m_bFly)
			m_fVelocityY = m_fJumpPow;
	}

	if (m_bFly)
	{
		// 날고있을 때 고정 애니메이션
		m_eCurState = FLY;

		m_bJump = true;

		if (m_tFrame.iStart > 3)
			m_tFrame.dwSpeed = 50;

		if (m_tFrame.iStart == m_tFrame.iEnd)
			m_tFrame.iStart = 4;
	}
	else if (m_fVelocityY > 0 && m_bJump && !m_bAttack)
	{
		// 점프 중일 때에는 1프레임의 애니메이션을 길게 재생
		m_eCurState = JUMP;
		m_tFrame.dwSpeed = 2000;
	}
	else if (m_fVelocityY < 0 && m_bJump && !m_bInhail && !m_bAttack)
	{
		// 떨어질 때에는 특정 프레임 애니메이션만 재생
		if (!m_bAttack)
		{
			m_eCurState = JUMP;
			m_tFrame.dwSpeed = 40;
		}

		if (m_tFrame.iStart == m_tFrame.iEnd - 3)
			m_tFrame.dwSpeed = 2000;
	}

	// 날기 애니메이션
	if (!InputManager->Key('Z') && m_bFly)
	{
		if (m_tFrame.iStart > 3)
			m_tFrame.dwSpeed = 150;
		if (m_tFrame.iStart > 4)
			m_tFrame.iStart = 3;
	}

	if (m_bIsGround)
	{
		// 착지 애니메이션
		if (m_eCurState == JUMP && m_bJump && !m_bAttack)
		{
			GameManager->AddObject(CAbsFactory<CEff_MiniStar>::CreateObject(m_tInfo.fX, m_tInfo.fY + 20.f), OBJ_EFFECT);
			m_tFrame.iStart = m_tFrame.iEnd - 2;
			m_tFrame.dwSpeed = 50;
			SoundManager->PlaySound(TEXT("JumpEnd.wav"), CSoundManager::PLAYER);
		}
		m_fGravity = -0.2f;
		m_fVelocityY = m_fGravity;
		m_bJump = false;
	}
	else
	{
		m_fGravity += m_fAccY * 0.07f;

		if (m_fVelocityY < 0)
			m_fVelocityY -= m_fGravity * 0.5f;
		else
			m_fVelocityY -= m_fGravity;

		// 상태에 따른 낙하 속도 조절 (비행, 일반)
		if (m_fVelocityY < 0 && m_fVelocityY < -1.5f && m_bFly)
			m_fVelocityY = -3.f;
		else if (m_fVelocityY < 0 && m_fVelocityY < -6.5f)
			m_fVelocityY = -6.5f;

		m_tInfo.fY -= m_fVelocityY;
	}
}

// 태클
// 이동과 점프의 조합 로직
// 소형 적에게 데미지를 입힌다. 대형, 보스는 X
// 공격력이 20이된다. 자신은 데미지를 입지 않게 된다.
void CKirby::Slide()
{
	if (m_bSlide)
	{
		m_fSpeed = 10.8f;

		if (m_tFrame.iStart == 1)
			m_tFrame.dwSpeed = 2000;

		if (!m_bFlipX)
			m_fVelocityX -= 3.f;
		else
			m_fVelocityX += 3.f;

		m_fDrag += m_fAccX * 0.04f;

		if (m_fVelocityX > m_fSpeed && m_fVelocityX > 0)
			m_fVelocityX = m_fSpeed;
		else if (m_fVelocityX < -m_fSpeed && m_fVelocityX < 0)
			m_fVelocityX = -m_fSpeed;

		m_fVelocityX -= m_fVelocityX * m_fDrag;

		m_eCurState = SLIDE;

		if (-0.3f < m_fVelocityX && m_fVelocityX < 0.3f)
		{
			m_fDrag = 0.f;
			m_fVelocityX = 0.f;
			m_fSpeed = 3.8f;
			m_bSlide = false;
		}
	}
	else
		m_iAtt = 10;
}

void CKirby::SceneChange()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eForm)
		{
		case NORMAL_FORM:
			NormalScene();
			break;
		case SWORD_FORM:
			SwordScene();
			break;
		case MARIO_FORM:
			MarioScene();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CKirby::SetAnimScene(int iStart, int iEnd, int iScene, DWORD dwSpeed)
{
	m_tFrame.iStart = iStart;
	m_tFrame.iEnd = iEnd;
	m_tFrame.iScene = iScene;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = dwSpeed;
}

void CKirby::NormalScene()
{
	m_tInfo.fCX = 96;
	m_tInfo.fCY = 105;

	m_pLeftKey = TEXT("Normal_Left");
	m_pRightKey = TEXT("Normal_Right");
	m_pFrameKey = m_bFlipX ? m_pRightKey : m_pLeftKey;

	switch (m_eCurState)
	{
	case IDLE:
		SetAnimScene(0, 34, 0, 100);
		break;
	case INHAILIDLE:
		SetAnimScene(0, 1, 14, 600);
		break;
	case DOWN:
		SetAnimScene(0, 1, 1, 1000);
		break;
	case SLIDE:
		SetAnimScene(0, 1, 2, 100);
		break;
	case MOVE:
		if (m_bInhail)
			SetAnimScene(0, 12, 15, 70);
		else
			SetAnimScene(0, 9, 3, 70);
		break;
	case DASH:
		if (m_bInhail)
			SetAnimScene(0, 12, 15, 40);
		else
			SetAnimScene(1, 7, 5, 40);
		break;
	case JUMP:
		if (m_bInhail)
			SetAnimScene(0, 4, 22, 100);
		else
			SetAnimScene(0, 11, 6, 100);
		break;
	case FLY:
		SetAnimScene(0, 8, 10, 60);
		break;
	case FLYATTACK:
		SetAnimScene(2, 4, 11, 130);
		break;
	case ATTACK:
		SetAnimScene(0, 11, 12, 100);
		break;
	case INHAIL:
		SetAnimScene(0, 4, 13, 80);
		break;
	case DAMAGE:
		SetAnimScene(0, 7, 18, 50);
		break;
	case EAT:
		SetAnimScene(0, 5, 16, 60);
		break;
	case SHOOTSTAR:
		SetAnimScene(0, 4, 17, 40);
		break;
	case DEAD:
		SetAnimScene(0, 15, 23, 40);
		break;
	}
}

void CKirby::SwordScene()
{
	m_tInfo.fCX = 213;
	m_tInfo.fCY = 180;

	m_pLeftKey = TEXT("Sword_Left");
	m_pRightKey = TEXT("Sword_Right");

	switch (m_eCurState)
	{
	case IDLE:
		SetAnimScene(0, 1, 0, 100);
		break;
	case DOWN:
		SetAnimScene(0, 0, 1, 1000);
		break;
	case SLIDE:
		SetAnimScene(0, 1, 2, 100);
		break;
	case MOVE:
		SetAnimScene(0, 11, 3, 60);
		break;
	case DASH:
		SetAnimScene(0, 7, 4, 40);
		break;
	case ATTACK:
		m_pLeftKey = TEXT("Sword_LeftAttack");
		m_pRightKey = TEXT("Sword_RightAttack");
		m_pFrameKey = m_bFlipX ? m_pRightKey : m_pLeftKey;
		m_tInfo.fCX = 300;
		m_tInfo.fCY = 180;
		SetAnimScene(0, 15, 0, 15);
		break;
	case JUMP:
		SetAnimScene(0, 11, 5, 100);
		break;
	case FLY:
		SetAnimScene(0, 8, 6, 60);
		break;
	case FLYATTACK:
		SetAnimScene(2, 4, 7, 130);
		break;
	case JUMPATTACK:
		SetAnimScene(0, 11, 8, 10);
		break;
	case TRANSFORM:
		SetAnimScene(0, 0, 11, 15);
		break;
	}

	m_pFrameKey = m_bFlipX ? m_pRightKey : m_pLeftKey;
}

void CKirby::MarioScene()
{
	m_tInfo.fCX = 96;
	m_tInfo.fCY = 105;

	m_pLeftKey = TEXT("Mario_Kirby_Left");
	m_pRightKey = TEXT("Mario_Kirby_Right");
	m_pFrameKey = m_bFlipX ? m_pRightKey : m_pLeftKey;

	switch (m_eCurState)
	{
	case IDLE:
		SetAnimScene(0, 1, 0, 100);
		break;
	case DOWN:
		SetAnimScene(0, 1, 1, 1000);
		break;
	case SLIDE:
		SetAnimScene(0, 1, 2, 100);
		break;
	case MOVE:
		SetAnimScene(0, 9, 3, 70);
		break;
	case DASH:
		SetAnimScene(1, 7, 5, 40);
		break;
	case JUMP:
		SetAnimScene(0, 11, 6, 100);
		break;
	case FLY:
		SetAnimScene(0, 8, 10, 60);
		break;
	case FLYATTACK:
		SetAnimScene(2, 4, 11, 130);
		break;
	case ATTACK:
		SetAnimScene(0, 1, 12, 50);
		break;
	case TRANSFORM:
		SetAnimScene(0, 0, 13, 15);
		break;
	}
}

void CKirby::ScrollMove()
{
	float fScrollX = GameManager->GetScrollX();

	if (WINCX * 0.5f < m_tInfo.fX + fScrollX && m_fVelocityX > 0)
		GameManager->SetScrollX(fScrollX - m_fVelocityX);

	if (WINCX * 0.5f > m_tInfo.fX + fScrollX && m_fVelocityX < 0)
		GameManager->SetScrollX(fScrollX - m_fVelocityX);
}

void CKirby::isDamage()
{
	m_fVelocityX = m_bFlipX ? -2.f : 2.f;
	m_bAttack = false;
	if (m_pTarget)
	{
		m_pTarget->SetActive(false);
		m_pTarget = nullptr;
	}

	if (m_bSlide)
	{
		m_fVelocityX = m_bFlipX ? -20.f : 20.f;
		m_fVelocityY = 5.f;
		m_bSlide = false;
	}
	else
	{
		m_fVelocityX = m_bFlipX ? -3.f : 3.f;
		m_fVelocityY -= 0.1f;
	}
	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY -= m_fVelocityY;

	if (m_tFrame.iStart == m_tFrame.iEnd)
	{
		m_eCurState = IDLE;
		m_bSlide = false;
	}
}

void CKirby::NoDamageState()
{
	if (m_eCurState == DAMAGE)
		m_dwDamageTime = GetTickCount() + 2000;

	if (m_dwDamageTime < GetTickCount())
		m_bNoDamage = false;
}

void CKirby::Eat()
{
	if (m_bEat)
	{
		m_iAttSquence = 11;
		m_eCurState = EAT;

		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			m_eCurState = IDLE;

			switch (m_eInhailType)
			{
			case SWORD:
				m_eForm = SWORD_FORM;
				break;
			case MARIO:
				m_eForm = MARIO_FORM;
				break;
			}

			FormChange(m_eForm);

			m_eInhailType = EMPTY;
			m_bEat = false;
			m_bInhail = false;
		}
	}
}

void CKirby::Dead()
{
	m_fVelocityX = 0;
	m_eCurState = DEAD;

	m_fVelocityY -= 0.2f;

	m_tInfo.fY -= m_fVelocityY;

	if (m_tInfo.fY > 800.f)
	{
		if (SceneManager->SceneEnd())
		{
			Initialize();
			m_bActive = true;
			SceneManager->SceneRestart();
		}
	}
}

void CKirby::KirbyUpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX + m_fImageX - m_tInfo.fCX / 2.f);
	m_tRect.top = LONG(m_tInfo.fY + m_fImageY - m_tInfo.fCY / 2.f);
	m_tRect.right = LONG(m_tInfo.fX + m_fImageX + m_tInfo.fCX / 2.f);
	m_tRect.bottom = LONG(m_tInfo.fY + m_fImageY + m_tInfo.fCY / 2.f);

	m_tHitBox.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2.f);
	m_tHitBox.top = LONG(m_tInfo.fY - m_iHitBoxCY + 20.f);
	m_tHitBox.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2.f);
	m_tHitBox.bottom = LONG(m_tInfo.fY + 20.f);
}

void CKirby::CreateDashEffect()
{
	GameManager->AddObject(CAbsFactory<CEff_Dash>::CreateObject(m_tInfo.fX, m_tInfo.fY - 10.f, m_bFlipX), OBJ_EFFECT);
}


void CKirby::SwordAttack()
{
	if (m_bJump) // 점프 어택
	{
		if (m_pTarget == nullptr)
		{
			GameManager->AddObject(CAbsFactory<CHitBox>::CreateHitBox(m_tInfo.fX, m_tInfo.fY - 15.f, 120, 120, 50, true, SLASH), PLAYER_ATT);
			m_pTarget = GameManager->GetObjList(PLAYER_ATT).back();
			SoundManager->PlaySound(TEXT("SwordKirbyAttack.wav"), CSoundManager::PLAYER);
		}
		else
			m_pTarget->SetPos(m_tInfo.fX, m_tInfo.fY - 15.f);

		m_eCurState = JUMPATTACK;
		if (m_tFrame.iStart == m_tFrame.iEnd - 1)
		{
			m_tFrame.iStart = 0;
			if (++m_iAttSquence > 1)
			{
				m_iAttSquence = 0;
				m_bAttack = false;
				m_eCurState = IDLE;
				m_tInfo.fCX = 213;
				m_tInfo.fCY = 180;
			}
			if (m_pTarget)
			{
				m_pTarget->SetActive(false);
				m_pTarget = nullptr;
			}
		}
	}
	else if (m_eCurState == JUMPATTACK && m_bIsGround)
	{
		m_iAttSquence = 0;
		m_bAttack = false;
		m_eCurState = IDLE;
		m_tInfo.fCX = 213;
		m_tInfo.fCY = 180;
		if (m_pTarget)
		{
			m_pTarget->SetActive(false);
			m_pTarget = nullptr;
		}
	}
	else // 일반 어택
	{
		m_eCurState = ATTACK;

		if (m_pTarget == nullptr && m_tFrame.iStart == 2)
		{
			float fX = m_bFlipX ? 30.f : -30.f;
			GameManager->AddObject(CAbsFactory<CHitBox>::CreateHitBox(m_tInfo.fX + fX, m_tInfo.fY - 15.f, 200, 130, 60, true, SLASH), PLAYER_ATT);
			m_pTarget = GameManager->GetObjList(PLAYER_ATT).back();
			SoundManager->PlaySound(TEXT("SwordKirbyAttack.wav"), CSoundManager::PLAYER);
		}

		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			m_bAttack = false;
			m_eCurState = IDLE;
			m_tInfo.fCX = 213;
			m_tInfo.fCY = 180;
			if (m_pTarget)
			{
				m_pTarget->SetActive(false);
				m_pTarget = nullptr;
			}
		}
	}
}

void CKirby::MarioAttack()
{
	if (m_tFrame.iStart == m_tFrame.iEnd)
	{
		// 불꽃 발사! 후 IDLE
		float fX = m_bFlipX ? 15.f : -15.f;
		GameManager->AddObject(CAbsFactory<CMarioFire>::CreateObject(m_tInfo.fX + fX, m_tInfo.fY, m_bFlipX), PLAYER_ATT);
		SoundManager->PlaySound(TEXT("Mario_Fire.wav"), CSoundManager::PLAYER);
		m_bAttack = false;
		m_eCurState = IDLE;
	}
}

void CKirby::DisTransform()
{
	ENEMYTYPE eType = NORMAL;

	switch (m_eForm)
	{
	case SWORD_FORM:
		eType = SWORD;
		break;
	case MARIO_FORM:
		eType = MARIO;
		break;
	}
	m_eForm = NORMAL_FORM;
	m_ePreState = END;
	m_eCurState = IDLE;

	GameManager->AddObject(CAbsFactory<CInhailStar>::CreateInhailStar(m_tInfo.fX, m_tInfo.fY, eType), OBJ_ENEMY);
}