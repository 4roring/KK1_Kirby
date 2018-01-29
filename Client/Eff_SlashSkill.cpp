#include "stdafx.h"
#include "Eff_SlashSkill.h"
#include "InhailStar.h"


CEff_SlashSkill::CEff_SlashSkill()
{
}


CEff_SlashSkill::~CEff_SlashSkill()
{
	Release();
}

void CEff_SlashSkill::Initialize()
{
	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 210.f;

	m_iHitBoxCX = 90;
	m_iHitBoxCY = 180;

	m_iAtt = 10;
}

void CEff_SlashSkill::LateInit()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 30;
	m_fSpeed = 8.f;
	m_pFrameKey = m_bFlipX ? TEXT("MetaKnight_SlashSkill_Right") : TEXT("MetaKnight_SlashSkill_Left");
	
	m_pTarget = GameManager->GetPlayer();
	m_fAngle = CMath::DistanceAngle(this, m_pTarget);
}

OBJ_STATE CEff_SlashSkill::Update()
{
	if (m_tInfo.fX < 10.f || m_tInfo.fX > 700.f)
	{
		GameManager->AddObject(CAbsFactory<CInhailStar>::CreateInhailStar(m_tInfo.fX, m_tInfo.fY, NORMAL), OBJ_ENEMY);
		return DESTROY;
	}
		
	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle) * m_fSpeed;

	return PLAY;
}

void CEff_SlashSkill::LateUpdate()
{
	FrameMove();
	UpdateRect();
}

void CEff_SlashSkill::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
		DrawHitBox(hDC);
	DrawObject(hDC, m_pFrameKey);
}

void CEff_SlashSkill::Release()
{
}
