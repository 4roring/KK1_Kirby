#include "stdafx.h"
#include "MarioFire.h"
#include "Eff_ClearStar.h"

CMarioFire::CMarioFire()
{
}


CMarioFire::~CMarioFire()
{
	Release();
}

void CMarioFire::Initialize()
{
	m_tInfo.fCX = 45.f;
	m_tInfo.fCY = 45.f;

	m_iHitBoxCX = 25;
	m_iHitBoxCY = 25;

	m_fVelocityY = -1.f;

	m_iAtt = 3;
}

void CMarioFire::LateInit()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 30;
	m_fSpeed = m_bFlipX ? 3.f : -3.f;
	m_pFrameKey = TEXT("MarioFire");
}

OBJ_STATE CMarioFire::Update()
{
	if (!m_bActive)
	{
		GameManager->AddObject(CAbsFactory<CEff_ClearStar>::CreateObject(m_tInfo.fX, m_tInfo.fY), OBJ_EFFECT);
		return DESTROY;
	}

	m_tInfo.fY -= m_fVelocityY;

	return PLAY;
}

void CMarioFire::LateUpdate()
{
	for (auto& pGround : GameManager->GetObjList(OBJ_GROUND))
	{
		RECT rc = {};

		if (IntersectRect(&rc, &m_tHitBox, &pGround->GetRect()))
		{
			m_fVelocityY = 3.f;
		}
	}

	m_fVelocityY -= 0.1f;

	FrameMove();
	UpdateRect();
}

void CMarioFire::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);
	DrawObject(hDC, m_pFrameKey);
}

void CMarioFire::Release()
{
}
