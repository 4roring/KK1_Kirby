#pragma once
#include "GameObject.h"
class CEff_Dash :
	public CGameObject
{
public:
	CEff_Dash();
	virtual ~CEff_Dash();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

