#include "stdafx.h"
#include "InhailStar.h"


CInhailStar::CInhailStar()
{
}


CInhailStar::~CInhailStar()
{
	Release();
}

void CInhailStar::Initialize()
{
	m_iMaxHp = 5000;
	m_iHp = m_iMaxHp;
	m_iAtt = 60;

	m_tInfo.fCX = 120;
	m_tInfo.fCY = 120;
	m_iHitBoxCX = 80;
	m_iHitBoxCY = 80;

	m_bFlipX = false;
	m_bIsDamage = false;

	m_pFrameKey = TEXT("InhailStar");

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 30;

	m_bInhail = false;
	m_eInhailType = NORMAL;

	m_dwDestroyTime = GetTickCount() + 3000;
}

void CInhailStar::LateInit()
{
}

OBJ_STATE CInhailStar::Update()
{


	if (m_bInhail && !m_bActive || m_dwDestroyTime < GetTickCount())
		return DESTROY;

	if (m_bInhail)
	{
		
		isInhail();
	}

	return PLAY;
}

void CInhailStar::LateUpdate()
{
	FrameMove();
	UpdateRect(m_fImageX, m_fImageY);
}

void CInhailStar::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);
	DrawObject(hDC, m_pFrameKey);
}

void CInhailStar::Release()
{
}
