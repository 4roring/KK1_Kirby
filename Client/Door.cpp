#include "stdafx.h"
#include "Door.h"


CDoor::CDoor()
{
}


CDoor::~CDoor()
{
}

void CDoor::Initialize()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 120.f;

	m_pFrameKey = TEXT("Map_Door");
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 100;
}

void CDoor::LateInit()
{
}

OBJ_STATE CDoor::Update()
{
	return PLAY;
}

void CDoor::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CDoor::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CDoor::Release()
{
}
