#pragma once
#include "GameObject.h"
class CEff_Transform :
	public CGameObject
{
public:
	CEff_Transform();
	virtual ~CEff_Transform();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

