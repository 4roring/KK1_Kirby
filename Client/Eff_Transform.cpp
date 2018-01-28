#include "stdafx.h"
#include "Eff_Transform.h"


CEff_Transform::CEff_Transform()
{
}


CEff_Transform::~CEff_Transform()
{
}

void CEff_Transform::Initialize()
{
	m_tInfo.fCX = 243.f;
	m_tInfo.fCY = 249.f;

	m_pFrameKey = TEXT("Transform_Effect");
}

void CEff_Transform::LateInit()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 40;
}

OBJ_STATE CEff_Transform::Update()
{
	if (m_tFrame.iStart == m_tFrame.iEnd)
		return DESTROY;

	return PLAY;
}

void CEff_Transform::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CEff_Transform::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CEff_Transform::Release()
{
}
