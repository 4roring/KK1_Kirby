#include "stdafx.h"
#include "UI_PlayerHp.h"
#include "Actor.h"


CUI_PlayerHp::CUI_PlayerHp()
{
}


CUI_PlayerHp::~CUI_PlayerHp()
{
}

void CUI_PlayerHp::Initialize()
{
	m_tInfo = { 114.f, 560.f, 75.f, 48.f };
}

void CUI_PlayerHp::LateInit()
{
	m_pTargetActor = dynamic_cast<CActor*>(m_pTarget);

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 0;
	m_tFrame.iScene = 0;
}

OBJ_STATE CUI_PlayerHp::Update()
{
	if (!m_bActive || m_pTarget == nullptr)
		return DESTROY;

	return PLAY;
}

void CUI_PlayerHp::LateUpdate()
{
	UpdateRect();
}

void CUI_PlayerHp::Render(HDC hDC)
{
	m_tFrame.iScene = 0;
	DrawUI(hDC, TEXT("PlayerHp"), -70.f, 0.f);

	m_tFrame.iScene = 2;
	DrawUI(hDC, TEXT("PlayerHp"), 0.f, 0.f);

	m_tFrame.iScene = 1;
	DrawUI(hDC, TEXT("PlayerHp"), m_pTargetActor->GetHpRatio());
}

void CUI_PlayerHp::Release()
{
}
