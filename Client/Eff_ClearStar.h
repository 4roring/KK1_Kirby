#pragma once
#include "GameObject.h"
class CEff_ClearStar :
	public CGameObject
{
public:
	CEff_ClearStar();
	virtual ~CEff_ClearStar();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

