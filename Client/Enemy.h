#pragma once
#include "Actor.h"
class CEnemy :
	public CActor
{
public:
	CEnemy();
	virtual ~CEnemy();

	// CActor을(를) 통해 상속됨
	virtual void Initialize() PURE;
	virtual void LateInit() PURE;
	virtual OBJ_STATE Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

public:
	virtual void ApplyDamage(int iDamage) override;

protected:
	bool CheckScreen() { return CCollision::Screen(GameManager->GetScreen(), this); }
	void isDamage();
	void isInhail();

protected:
	bool m_bIsDead;
	DWORD m_dwDeadTimer;
	DWORD m_ewKnockBackTimer;
};

