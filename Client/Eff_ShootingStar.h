#pragma once
#include "GameObject.h"
class CEff_ShootingStar :
	public CGameObject
{
public:
	CEff_ShootingStar();
	virtual ~CEff_ShootingStar();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

