#pragma once
#include "GameObject.h"
class CEff_SlashSkill :
	public CGameObject
{
public:
	CEff_SlashSkill();
	virtual ~CEff_SlashSkill();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	float m_fAngle;
};

