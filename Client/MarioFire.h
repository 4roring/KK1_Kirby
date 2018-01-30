#pragma once
#include "GameObject.h"
class CMarioFire :
	public CGameObject
{
public:
	CMarioFire();
	virtual ~CMarioFire();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	float m_fVelocityY;
};

