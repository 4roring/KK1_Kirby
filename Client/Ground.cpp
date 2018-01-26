#include "stdafx.h"
#include "Ground.h"


CGround::CGround()
{
}


CGround::~CGround()
{
}

void CGround::Initialize()
{
	m_bActive = true;
}

void CGround::LateInit()
{
}

OBJ_STATE CGround::Update()
{
	return OBJ_STATE();
}

void CGround::LateUpdate()
{
}

void CGround::Render(HDC hDC)
{
	if (GameManager->GetDebugMode())
	{
		int iScrollX = (int)GameManager->GetScrollX();
		int iScrollY = (int)GameManager->GetScrollY();

		if(!m_bFlipX)
			Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		else
		{
			MoveToEx(hDC, m_tP1.x + iScrollX, m_tP1.y + iScrollY, nullptr);
			LineTo(hDC, m_tP2.x + iScrollX, m_tP2.y + iScrollY);
		}
	}


}

void CGround::Release()
{
}
