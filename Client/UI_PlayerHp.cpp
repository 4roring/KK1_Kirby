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
	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 48.f;
}

void CUI_PlayerHp::LateInit()
{
	m_pTargetActor = dynamic_cast<CActor*>(m_pTarget);
}

OBJ_STATE CUI_PlayerHp::Update()
{
	if (!m_bActive || m_pTarget == nullptr)
		return DESTROY;

	return PLAY;
}

void CUI_PlayerHp::LateUpdate()
{
}

void CUI_PlayerHp::Render(HDC hDC)
{
	//DrawObject
}

void CUI_PlayerHp::Release()
{
}
