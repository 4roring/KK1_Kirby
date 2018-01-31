#include "stdafx.h"
#include "SwordItem.h"
#include "Kirby.h"


CSwordItem::CSwordItem()
{
}


CSwordItem::~CSwordItem()
{
}

void CSwordItem::Initialize()
{
	m_tInfo.fCX = 165.f;
	m_tInfo.fCY = 282.f;

	m_iHitBoxCX = 30;
	m_iHitBoxCY = 50;

	m_fImageX = 0.f;
	m_fImageY = -90.f;

	m_pFrameKey = TEXT("SwordItem");

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 1;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 500;
}

void CSwordItem::LateInit()
{
}

OBJ_STATE CSwordItem::Update()
{
	RECT rc = {};

	if (IntersectRect(&rc, &m_tHitBox, &GameManager->GetPlayer()->GetRect()))
	{
		dynamic_cast<CKirby*>(GameManager->GetPlayer())->FormChange(CKirby::SWORD_FORM);
		return DESTROY;
	}

	return PLAY;
}

void CSwordItem::LateUpdate()
{
	FrameMove();
	UpdateRect(m_fImageX, m_fImageY);
}

void CSwordItem::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);

	DrawObject(hDC, m_pFrameKey);
}

void CSwordItem::Release()
{
}
