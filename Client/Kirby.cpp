#include "stdafx.h"
#include "Kirby.h"


CKirby::CKirby()
{
}


CKirby::~CKirby()
{
}

void CKirby::Initialize()
{
	// 상태 초기화
	m_tInfo = { 50, 450, 96, 105 };
	m_iHitBoxCX = 40;
	m_iHitBoxCY = 40;

	m_fSpeed = 3.8f;
	m_fJumpPow = 9.0f;

	m_fVelocityX = 0.f;
	m_fVelocityY = 0.f;
	m_fGravity = 0.0f;
	m_fAccX = 0.65f;
	m_fAccY = 1.1f;

	m_bIsGround = false;
	m_bIsDash = true;

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
	Move();
	Jump();
	if (m_fVelocityX == 0 && m_fVelocityY == 0)
		m_eCurState = IDLE;
	
	if (InputManager()->Key('X'))
	{
		m_eCurState = ATTACK;
	}
	
	if (InputManager()->Key(VK_DOWN))
	{
		m_eCurState = DOWN;
		if (m_tFrame.iStart == 1)
			m_tFrame.dwSpeed = 100;
		else
			m_tFrame.dwSpeed = 2000;
	}

	return PLAY;
}

void CKirby::LateUpdate()
{
	FrameMove();
	UpdateRect(0.f, -9.f);

	m_bIsGround = CCollision::Ground(GameManager()->GetObjList(OBJ_PLAYER), GameManager()->GetObjList(OBJ_GROUND));

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
		case JUMP:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 11;
			m_tFrame.iScene = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
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

void CKirby::Move()
{
	if (InputManager()->Key(VK_LEFT))
	{
		m_fVelocityX -= m_fAccX;
		m_pFrameKey = TEXT("Normal_Left");
	}
	else if (InputManager()->Key(VK_RIGHT))
	{
		m_fVelocityX += m_fAccX;
		m_pFrameKey = TEXT("Normal_Right");
	}

	// 최대 속도를 넘지 않음
	if (m_fVelocityX > m_fSpeed && m_fVelocityX > 0)
		m_fVelocityX = m_fSpeed;
	else if(m_fVelocityX < -m_fSpeed && m_fVelocityX < 0)
		m_fVelocityX = -m_fSpeed;

	m_eCurState = MOVE;

	m_fVelocityX -= m_fVelocityX * 0.09f;

	if (-0.1f < m_fVelocityX && m_fVelocityX < 0.1f)
	{
		m_fVelocityX = 0.f;
		m_fSpeed = 3.8f;
	}
	

	m_tInfo.fX += m_fVelocityX;
}

void CKirby::Attack()
{
}

void CKirby::Jump()
{
	if (InputManager()->Key('Z') && !m_bIsGround)
	{
		m_bIsGround = false;

		m_fVelocityY += m_fAccY;
		m_fGravity += m_fAccY * 0.1f;

		if (m_fVelocityY > m_fJumpPow)
		{
			m_fVelocityY = m_fJumpPow;
		}

		m_fVelocityY += m_fVelocityY * 0.1f;
	}

	if (m_fVelocityY > 0)
	{
		m_eCurState = JUMP;
		m_tFrame.dwSpeed = 2000;
	}
	else if (m_fVelocityY < 0)
	{
		m_eCurState = JUMP;
		m_tFrame.dwSpeed = 40;

		if (m_tFrame.iStart == m_tFrame.iEnd - 3)
			m_tFrame.dwSpeed = 2000;
	}

	if (m_bIsGround)
	{
		if (m_eCurState = JUMP)
		{
			m_tFrame.iStart = m_tFrame.iEnd - 2;
			m_tFrame.dwSpeed = 10;
		}
		m_fGravity = 0.f;
		m_fVelocityY = 0.f;
	}
	else
	{
		m_tInfo.fY -= m_fVelocityY;
		m_fVelocityY -= m_fGravity;

		if (m_fVelocityY < 0 && m_fVelocityY < -7.8f)
			m_fVelocityY = -6.0f;
	}
}
