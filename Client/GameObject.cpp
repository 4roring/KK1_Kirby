#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_bActive(true), m_bFlipX(false), m_pTarget(nullptr), m_bInhail(false)
{
	m_tInfo = {};
	m_tRect = {};
	m_tHitBox = {};
}


CGameObject::~CGameObject()
{
}

void CGameObject::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2.f);
	m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2.f);
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2.f);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2.f);

	m_tHitBox.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2.f);
	m_tHitBox.top = LONG(m_tInfo.fY - m_iHitBoxCY / 2.f);
	m_tHitBox.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2.f);
	m_tHitBox.bottom = LONG(m_tInfo.fY + m_iHitBoxCY / 2.f);
}

// 비트맵의 Rect를 조작하기 위한 오버로딩
void CGameObject::UpdateRect(float fX, float fY)
{
	m_tRect.left = LONG(m_tInfo.fX + fX - m_tInfo.fCX / 2.f);
	m_tRect.top = LONG(m_tInfo.fY + fY - m_tInfo.fCY / 2.f);
	m_tRect.right = LONG(m_tInfo.fX + fX + m_tInfo.fCX / 2.f);
	m_tRect.bottom = LONG(m_tInfo.fY + fY + m_tInfo.fCY / 2.f);

	m_tHitBox.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2.f);
	m_tHitBox.top = LONG(m_tInfo.fY - m_iHitBoxCY / 2.f);
	m_tHitBox.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2.f);
	m_tHitBox.bottom = LONG(m_tInfo.fY + 20.f);
}

void CGameObject::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.dwTime = GetTickCount();
		++m_tFrame.iStart;
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
		m_tFrame.iStart = 0;
}

void CGameObject::DrawObject(HDC hDC, const TCHAR* szName)
{
	int iScrollX = (int)GameManager->GetScrollX();
	int iScrollY = (int)GameManager->GetScrollY();

	HDC hMemDC = BmpManager->GetMapBit()[szName]->GetMemDC();

	int iSizeX = (int)m_tInfo.fCX;
	int iSizeY = (int)m_tInfo.fCY;

	GdiTransparentBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		iSizeX, iSizeY, hMemDC,
		m_tFrame.iStart * iSizeX, m_tFrame.iScene * iSizeY,
		iSizeX, iSizeY, RGB(255, 0, 255));
}

void CGameObject::DrawHitBox(HDC hDC)
{
	int iScrollX = (int)GameManager->GetScrollX();
	int iScrollY = (int)GameManager->GetScrollY();

	Rectangle(hDC, m_tHitBox.left + iScrollX, m_tHitBox.top + iScrollY,
		m_tHitBox.right + iScrollX, m_tHitBox.bottom + iScrollY);
}

