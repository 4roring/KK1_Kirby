#include "stdafx.h"
#include "Eff_MiniStar.h"


CEff_MiniStar::CEff_MiniStar()
{
}


CEff_MiniStar::~CEff_MiniStar()
{
}

void CEff_MiniStar::Initialize()
{
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 48.f;

	m_pFrameKey = TEXT("MiniStar");
}

void CEff_MiniStar::LateInit()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 30;
	m_fSpeed = rand() % 360;
}

OBJ_STATE CEff_MiniStar::Update()
{
	if (m_tFrame.iStart == m_tFrame.iEnd)
		return DESTROY;

	m_tInfo.fX += cosf(RAD(m_fSpeed)) * 5.f;
	m_tInfo.fY -= sinf(RAD(m_fSpeed)) * 5.f;

	return PLAY;
}

void CEff_MiniStar::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CEff_MiniStar::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CEff_MiniStar::Release()
{
}
