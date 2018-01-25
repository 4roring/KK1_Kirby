#pragma once
#include "GameObject.h"
class CGround :
	public CGameObject
{
public:
	CGround();
	CGround(RECT& rc)
		: m_tP1{}, m_tP2{}
	{
		m_tRect.left = rc.left;
		m_tRect.top = rc.top;
		m_tRect.right = rc.right;
		m_tRect.bottom = rc.bottom;

		m_bFlipX = false;
	}
	CGround(POINT& tP1, POINT& tP2)
	{
		m_tRect = {};
		m_tP1 = tP1, m_tP2 = tP2;

		m_bFlipX = true;
	}
	virtual ~CGround();

public:
	POINT& GetPoint_1() { return m_tP1; }
	POINT& GetPoint_2() { return m_tP2; }

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	POINT m_tP1;
	POINT m_tP2;
};

