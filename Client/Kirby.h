#pragma once
#include "Actor.h"
class CKirby :
	public CActor
{
public:
	enum STATE { 
		IDLE, INHAILIDLE, DOWN, SLIDE, MOVE, DASH, 
		JUMP, FLY, FLYATTACK, ATTACK, INHAIL, DAMAGE, 
		EAT, SHOOTSTAR, END 
	};

public:
	CKirby();
	virtual ~CKirby();

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
	void Input();
	void Move();
	void Attack();
	void Jump();
	void Slide();
	void SceneChange();
	void ScrollMove();
	void isDamage();
	void NoDamageState();
	void Eat();

private:
	void CreateDashEffect();
	void DrawAlphaBlack(HDC hDC, int iAlpha);

private:
	STATE m_eCurState;
	STATE m_ePreState;

	bool m_bSlide;
	bool m_bJump;
	bool m_bIsGround;
	bool m_bDash;
	bool m_bFly;
	bool m_bAttack;

	bool m_bNoDamage;
	bool m_bEat;

	DWORD m_dwDamageTime;
	int m_iInputFrame;
	int m_iAttSquence;
};

