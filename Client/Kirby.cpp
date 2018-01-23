#include "stdafx.h"
#include "Kirby.h"
#include "Eff_Dash.h"

CKirby::CKirby()
{
}


CKirby::~CKirby()
{
}

void CKirby::Initialize()
{
	// 상태 초기화
	m_tInfo = { 50, 400, 96, 105 };
	m_iHitBoxCX = 40;
	m_iHitBoxCY = 40;

	m_fImageX = 0.f;
	m_fImageY = -9.f;

	m_fSpeed = 3.8f;
	m_fJumpPow = 15.6f;

	m_fVelocityX = 0.f;
	m_fVelocityY = -6.5f;
	m_fGravity = 0.0f;
	m_fDrag = 0.f;
	m_fAccX = 0.65f;
	m_fAccY = 1.2f;

	m_bFlipX = false; // Flip의 디폴트는 왼쪽(-방향)
	m_bJump = false;
	m_bIsGround = false;
	m_bDash = false;
	m_bAttack = false;

	m_iInputFrame = g_iFrame;
	m_iAttSquence = 0;

	// 비트맵 로딩
	BmpManager()->RegistBitmap(TEXT("Normal_Left"), TEXT("../Image/Normal_Kirby/Normal_Left.bmp"));
	BmpManager()->RegistBitmap(TEXT("Normal_Right"), TEXT("../Image/Normal_Kirby/Normal_Right.bmp"));

	// 애니메이션 초기화
	m_pFrameKey = TEXT("Normal_Left");
	m_eCurState = IDLE;
	m_ePreState = m_eCurState;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 34;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 100;
}

void CKirby::LateInit()
{
}

OBJ_STATE CKirby::Update()
{
	if (!m_bAttack)
	{
		Input();
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
	FrameMove();
	UpdateRect(m_fImageX, m_fImageY);

	if (!m_bIsGround)
	{
		m_bIsGround = CCollision::Ground(GameManager()->GetObjList(OBJ_PLAYER), GameManager()->GetObjList(OBJ_GROUND));
		if (m_bIsGround)
		{
			m_bJump = false;
			m_fVelocityY = 0.f;
		}
	}

	SceneChange();
}

void CKirby::Render(HDC hDC)
{
	//Rectangle(hDC, m_tHitBox.left, m_tHitBox.top, m_tHitBox.right, m_tHitBox.bottom);
	DrawObject(hDC, m_pFrameKey);
}

void CKirby::Release()
{
}

void CKirby::Input()
{
	if (m_bSlide) return;

	if (m_fVelocityX == 0 && m_fVelocityY == 0 && !m_bSlide && !m_bJump && !m_bAttack)
		m_eCurState = IDLE;

	// 7프레임 안에 연타시 대시 입력
	if (InputManager()->KeyDown(VK_LEFT) && m_iInputFrame > g_iFrame && !m_bFly)
	{
		m_bFlipX = false;
		m_bDash = true;
		CreateDashEffect();
	}
	else if (InputManager()->KeyUp(VK_LEFT) && m_iInputFrame < g_iFrame && !m_bFly)
	{
		m_iInputFrame = g_iFrame + 7;
		m_bDash = false;
	}

	if (InputManager()->KeyDown(VK_RIGHT) && m_iInputFrame > g_iFrame && !m_bFly)
	{
		m_bFlipX = true;
		m_bDash = true;
		CreateDashEffect();
	}
	else if (InputManager()->KeyUp(VK_RIGHT) && m_iInputFrame < g_iFrame && !m_bFly)
	{
		m_iInputFrame = g_iFrame + 7;
		m_bDash = false;
	}

	if (InputManager()->Key(VK_DOWN))
	{
		if (!m_bSlide && !m_bFly)
		{
			m_eCurState = DOWN;
			m_bDash = false;
			if (m_tFrame.iStart == 1)
				m_tFrame.dwSpeed = 100;
			else
				m_tFrame.dwSpeed = 2000;
		}

		// 슬라이딩
		if (InputManager()->KeyDown('Z') && !m_bJump && !m_bFly
			|| InputManager()->KeyDown('X') && !m_bJump && !m_bFly)
		{
			m_bSlide = true;
			CreateDashEffect();
		}
			

	}
	else if (InputManager()->KeyDown('Z'))
	{
		if (m_bIsGround && !m_bJump)
		{
			m_bIsGround = false;
			m_bJump = true;
		}
		else if(m_bJump)
			m_bFly = true;
	}
}

// 이동
void CKirby::Move()
{
	if (m_bSlide) return;

	if (m_bDash)
	{
		m_fAccX = 1.f;
		m_fSpeed = 5.1f;

		if(!m_bJump && !m_bFly)
			m_eCurState = DASH;

		if (m_tFrame.iStart == m_tFrame.iEnd)
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

	if (InputManager()->Key(VK_LEFT))
	{
		if (m_bFly)
			m_fVelocityX = -3.f;
		else if (m_eCurState != DOWN && !m_bAttack)
			m_fVelocityX -= m_fAccX + m_fAccY;
		
		m_bFlipX = false;
		m_pFrameKey = TEXT("Normal_Left");
	}
	else if (InputManager()->Key(VK_RIGHT))
	{
		if (m_bFly)
			m_fVelocityX = 3.f;
		else if (m_eCurState != DOWN && !m_bAttack)
			m_fVelocityX += m_fAccX + m_fAccY;
	
		m_bFlipX = true;
		m_pFrameKey = TEXT("Normal_Right");
	}

	// 최대 속도를 넘지 않음
	if (m_fVelocityX > m_fSpeed && m_fVelocityX > 0)
		m_fVelocityX = m_fSpeed;
	else if (m_fVelocityX < -m_fSpeed && m_fVelocityX < 0)
		m_fVelocityX = -m_fSpeed;

	//m_fVelocityX -= m_fVelocityX * 0.09f;

	m_fVelocityX -= m_fVelocityX * 0.05f;

	if (-0.1f < m_fVelocityX && m_fVelocityX < 0.2f)
	{
		m_fVelocityX = 0.f;
		m_fSpeed = 3.8f;
	}

	if (m_fVelocityX != 0.f && m_eCurState != DOWN && !m_bDash 
		&& !m_bJump && !m_bFly)
		m_eCurState = MOVE;
}

void CKirby::Attack()
{
	if (m_bAttack && m_eCurState == FLYATTACK)
	{
		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			// TODO: 공기뿜고 공격 종료
			m_bAttack = false;
		}
	}
	else if (InputManager()->Key('X') && m_bAttack)
	{
		// TODO: 흡수
		m_eCurState = ATTACK;
		m_bDash = false;

		if (m_iAttSquence < 10)
		{
			if (m_tFrame.iStart == 7)
			{
				m_tFrame.iStart = 6;
				++m_iAttSquence;
			}
		}

		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			m_bAttack = false;
		}
	}
	else if (InputManager()->KeyUp('X') && m_bAttack)
		m_bAttack = false;

	// 공격 입력
	if (InputManager()->KeyDown('X') && !m_bSlide)
	{
		if (m_bFly)
		{
			m_bFly = false;
			m_eCurState = FLYATTACK;
		}
		else
		{
			m_eCurState = ATTACK;
			m_iAttSquence = 0;
		}	
		m_bAttack = true;
	}
}

// 점프, 날기
void CKirby::Jump()
{
	if (InputManager()->Key('Z') && m_bJump)
	{
		if (m_bFly)
		{
			m_fVelocityY = 3.5f;
			m_bDash = false;
			if (m_iInputFrame < g_iFrame)
			{
				m_fGravity = 0.f;
				m_iInputFrame = g_iFrame + 5;
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
	else if (m_fVelocityY < 0 && m_bJump)
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

	if (!InputManager()->Key('Z') && m_bFly)
	{
		if (m_tFrame.iStart > 3)
			m_tFrame.dwSpeed = 150;
		if (m_tFrame.iStart > 4)
			m_tFrame.iStart = 3;
	}

	if (m_bIsGround)
	{
		if (m_eCurState == JUMP && m_bJump)
		{
			m_tFrame.iStart = m_tFrame.iEnd - 2;
			m_tFrame.dwSpeed = 10;
		}
		m_fGravity = 0.f;
		m_fVelocityY = 0.f;
	}
	else
	{
		m_fGravity += m_fAccY * 0.07f;
		m_tInfo.fY -= m_fVelocityY;

		if (m_fVelocityY < 0)
			m_fVelocityY -= m_fGravity * 0.5f;
		else
			m_fVelocityY -= m_fGravity;

		// 상태에 따른 낙하 속도 조절 (비행, 일반)
		if (m_fVelocityY < 0 && m_fVelocityY < -1.5f && m_bFly)
			m_fVelocityY = -3.f;
		else if(m_fVelocityY < 0 && m_fVelocityY < -6.5f)
			m_fVelocityY = -6.5f;
	}
}

// 이동과 점프의 조합 로직
// 속도는 더 빠르고 HitBox 발생.
// 소형 몬스터에게 데미지를 입힌다. 대형, 보스는 X
// TODO: HitBox 추가
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
}

void CKirby::SceneChange()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 34;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case DOWN:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iScene = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 1000;
			break;
		case SLIDE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iScene = 2;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case MOVE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.iScene = 3;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 70;
			break;
		case DASH:
			m_tFrame.iStart = 1;
			m_tFrame.iEnd = 7;
			m_tFrame.iScene = 5;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 40;
			break;
		case JUMP:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 11;
			m_tFrame.iScene = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case FLY:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 8;
			m_tFrame.iScene = 10;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 60;
			break;
		case FLYATTACK:
			m_tFrame.iStart = 2;
			m_tFrame.iEnd = 4;
			m_tFrame.iScene = 11;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 130;
			break;
		case ATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 11;
			m_tFrame.iScene = 12;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CKirby::CreateDashEffect()
{
	GameManager()->AddObject(CAbsFactory<CEff_Dash>::CreateObject(m_tInfo.fX, m_tInfo.fY - 10.f, m_bFlipX), OBJ_EFFECT);
}
