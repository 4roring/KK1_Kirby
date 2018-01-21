#include "stdafx.h"
#include "BlackMetaKnight.h"


CBlackMetaKnight::CBlackMetaKnight()
{
}


CBlackMetaKnight::~CBlackMetaKnight()
{
}

void CBlackMetaKnight::Initialize()
{
	m_tInfo = { 500, 500, 150, 150 };
	m_iHitBoxCX = 40;
	m_iHitBoxCY = 40;

	m_fSpeed = 4.f;

	BmpManager()->RegistBitmap(TEXT("Black_1_Left"), 
		TEXT("../Image/Enemy/BlackMetaKnight/Left_Move_Attack.bmp"));
	BmpManager()->RegistBitmap(TEXT("Black_1_Right"), 
		TEXT("../Image/Enemy/BlackMetaKnight/Right_Move_Attack.bmp"));

	m_pFrameKey = TEXT("Black_1_Left");

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 7;
	m_tFrame.iScene = 1;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 100;
}

void CBlackMetaKnight::LateInit()
{
}

OBJ_STATE CBlackMetaKnight::Update()
{
	return OBJ_STATE();
}

void CBlackMetaKnight::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CBlackMetaKnight::Render(HDC hDC)
{
	Rectangle(hDC, m_tHitBox.left, m_tHitBox.top, m_tHitBox.right, m_tHitBox.bottom);
	DrawObject(hDC, m_pFrameKey);
}

void CBlackMetaKnight::Release()
{
}

void CBlackMetaKnight::ConditionChange()
{
}
