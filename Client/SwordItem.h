#pragma once
#include "GameObject.h"
class CSwordItem :
	public CGameObject
{
public:
	CSwordItem();
	virtual ~CSwordItem();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

