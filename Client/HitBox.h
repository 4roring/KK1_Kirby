#pragma once
#include "GameObject.h"
class CHitBox :
	public CGameObject
{
public:
	CHitBox();
	virtual ~CHitBox();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

