#pragma once
#include "GameObject.h"
class CHpItem :
	public CGameObject
{
public:
	CHpItem();
	virtual ~CHpItem();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

