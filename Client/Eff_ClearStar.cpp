#include "stdafx.h"
#include "Eff_ClearStar.h"


CEff_ClearStar::CEff_ClearStar()
{
}


CEff_ClearStar::~CEff_ClearStar()
{
}

void CEff_ClearStar::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_pFrameKey = TEXT("ClearStar");
}

void CEff_ClearStar::LateInit()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
}

OBJ_STATE CEff_ClearStar::Update()
{
	if (m_tFrame.iStart == m_tFrame.iEnd)
		return DESTROY;

	return PLAY;
}

void CEff_ClearStar::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CEff_ClearStar::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CEff_ClearStar::Release()
{
}
