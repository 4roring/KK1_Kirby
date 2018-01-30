#pragma once
#include "GameObject.h"

class CActor;

class CUI_PlayerHp :
	public CGameObject
{
public:
	CUI_PlayerHp();
	virtual ~CUI_PlayerHp();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CActor* m_pTargetActor;
};

