#pragma once
#include "GameObject.h"
class CActor;
class CUI_BossHp :
	public CGameObject
{
public:
	CUI_BossHp();
	virtual ~CUI_BossHp();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CActor* m_pTargetActor;
};

