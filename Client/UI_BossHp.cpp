#include "stdafx.h"
#include "UI_BossHp.h"
#include "Actor.h"


CUI_BossHp::CUI_BossHp()
{
}


CUI_BossHp::~CUI_BossHp()
{
}

void CUI_BossHp::Initialize()
{
	m_tInfo = { 538.f, 565.f, 240.f, 30.f };
}

void CUI_BossHp::LateInit()
{
	m_pTargetActor = dynamic_cast<CActor*>(m_pTarget);

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 0;
	m_tFrame.iScene = 0;
}

OBJ_STATE CUI_BossHp::Update()
{
	if (!m_bActive || m_pTarget == nullptr)
		return DESTROY;

	return PLAY;
}

void CUI_BossHp::LateUpdate()
{
	UpdateRect();
}

void CUI_BossHp::Render(HDC hDC)
{
	m_tFrame.iScene = 1;
	DrawUI(hDC, TEXT("BossHp"), 0.f, 0.f);

	m_tFrame.iScene = 0;
	DrawUI(hDC, TEXT("BossHp"), m_pTargetActor->GetHpRatio());
}

void CUI_BossHp::Release()
{
}