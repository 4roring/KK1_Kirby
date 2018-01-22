#pragma once
#include "GameObject.h"
class CGround :
	public CGameObject
{
public:
	CGround();
	CGround(RECT& rc)
	{
		m_tRect.left = rc.left;
		m_tRect.top = rc.top;
		m_tRect.right = rc.right;
		m_tRect.bottom = rc.bottom;
	}
	virtual ~CGround();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

