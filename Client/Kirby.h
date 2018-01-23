#pragma once
#include "Actor.h"
class CKirby :
	public CActor
{
public:
	enum STATE { IDLE, DOWN, SLIDE, MOVE, DASH, JUMP, FLY, FLYATTACK, ATTACK, END };

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

private:
	void Input();
	void Move();
	void Attack();
	void Jump();
	void Slide();
	void SceneChange();

private:
	void CreateDashEffect();

private:

	STATE m_eCurState;
	STATE m_ePreState;

	bool m_bSlide;
	bool m_bJump;
	bool m_bIsGround;
	bool m_bDash;
	bool m_bFly;
	bool m_bAttack;

	int m_iInputFrame;
	int m_iAttSquence;
};

