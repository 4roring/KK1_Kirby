#include "stdafx.h"
#include "HpItem.h"
#include "Actor.h"


CHpItem::CHpItem()
{
}


CHpItem::~CHpItem()
{
}

void CHpItem::Initialize()
{
	m_tInfo.fCX = 52.f;
	m_tInfo.fCY = 52.f;

	m_pFrameKey = TEXT("HpItem");
}

void CHpItem::LateInit()
{
}

OBJ_STATE CHpItem::Update()
{
	RECT rc = {};

	if (IntersectRect(&rc, &m_tRect, &GameManager->GetPlayer()->GetRect()))
	{
		dynamic_cast<CActor*>(GameManager->GetPlayer())->SetHp(60);
		return DESTROY;
	}

	return PLAY;
}

void CHpItem::LateUpdate()
{
	UpdateRect();
}

void CHpItem::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CHpItem::Release()
{
}
