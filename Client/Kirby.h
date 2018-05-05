#pragma once
#include "Actor.h"
class CKirby :
	public CActor
{
public:
	enum STATE { 
		IDLE, INHAILIDLE, DOWN, SLIDE, MOVE, DASH, 
		JUMP, JUMPATTACK, FLY, FLYATTACK, ATTACK, INHAIL, DAMAGE, 
		EAT, SHOOTSTAR, TRANSFORM, DEAD, END 
	};
	enum FORM { NORMAL_FORM, SWORD_FORM, MARIO_FORM, FORM_END};

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
	void FormChange(FORM eForm);

private:
	void MoveInput();
	void Move();
	void Attack();
	void Jump();
	void Slide();
	void ScrollMove();
	void isDamage();
	void NoDamageState();
	void Eat();
	void Dead();

private:
	void KirbyUpdateRect();
	void SceneChange();
	void SetAnimScene(int iStart, int iEnd, int iScene, DWORD dwSpeed);
	void NormalScene();
	void SwordScene();
	void MarioScene();

private:
	void CreateDashEffect();

private: // 폼 관련 함수
	void SwordAttack();
	void MarioAttack();
	void DisTransform();

private:
	STATE m_eCurState;
	STATE m_ePreState;

	FORM m_eForm;

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
	
	TCHAR* m_pLeftKey;
	TCHAR* m_pRightKey;
};

