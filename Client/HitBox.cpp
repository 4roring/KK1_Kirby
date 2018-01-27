#include "stdafx.h"
#include "HitBox.h"


CHitBox::CHitBox()
{
}


CHitBox::~CHitBox()
{
}

void CHitBox::Initialize()
{
}

void CHitBox::LateInit()
{
}

OBJ_STATE CHitBox::Update()
{
	if (m_bFlipX) // 시전자가 직접 제거하는 히트박스
		m_bActive = true;

	if (!m_bActive)
		return DESTROY;

	return PLAY;
}

void CHitBox::LateUpdate()
{
	UpdateRect();
}

void CHitBox::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);
}

void CHitBox::Release()
{
}
