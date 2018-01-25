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
	DrawHitBox(hDC);
}

void CHitBox::Release()
{
}
