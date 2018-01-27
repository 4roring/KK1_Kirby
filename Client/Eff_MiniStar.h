#pragma once
#include "GameObject.h"
class CEff_MiniStar :
	public CGameObject
{
public:
	CEff_MiniStar();
	virtual ~CEff_MiniStar();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

