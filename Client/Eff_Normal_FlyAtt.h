#pragma once
#include "GameObject.h"
class CEff_Normal_FlyAtt :
	public CGameObject
{
public:
	CEff_Normal_FlyAtt();
	virtual ~CEff_Normal_FlyAtt();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

