#pragma once
#include "Actor.h"
class CWadorudi :
	public CActor
{
public:
	CWadorudi();
	virtual ~CWadorudi();

	// CActor을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void ApplyDamage(int iDamage) override;

private:
	bool CheckScreen() { return CCollision::Screen(GameManager->GetScreen(), this); }

private:
	void isDamage();
	void isInhail();
};