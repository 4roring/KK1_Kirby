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
	m_tInfo = { 50, 500, 96, 104 };
	m_iHitBoxCX = 40;
	m_iHitBoxCY = 40;

	m_fSpeed = 4.f;

	BmpManager()->RegistBitmap(TEXT("Normal_Left"), TEXT("../Image/Normal_Kirby/Normal_Left.bmp"));
	BmpManager()->RegistBitmap(TEXT("Normal_Right"), TEXT("../Image/Normal_Kirby/Normal_Right.bmp"));

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
	if (InputManager()->Key(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = TEXT("Normal_Left");
		m_eCurState = MOVE;
	}
	else if (InputManager()->Key(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = TEXT("Normal_Right");
		m_eCurState = MOVE;
	}
	else if (InputManager()->Key(VK_DOWN))
	{
		m_eCurState = DOWN;
		if (m_tFrame.iStart == 1)
			m_tFrame.dwSpeed = 100;
		else
			m_tFrame.dwSpeed = 2000;
	}
	else if (InputManager()->Key('Z'))
	{

	}
	else if (InputManager()->Key('X'))
	{

	}
	else
		m_eCurState = IDLE;
		



	return PLAY;
}

void CKirby::LateUpdate()
{
	FrameMove();
	UpdateRect();
	SceneChange();
}

void CKirby::Render(HDC hDC)
{
	Rectangle(hDC, m_tHitBox.left, m_tHitBox.top, m_tHitBox.right, m_tHitBox.bottom);
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
