#pragma once
#include "Actor.h"
class CMetaKnight :
	public CActor
{
public:
	enum STATE
	{
		APPEAR1, APPEAR2, IDLE, MOVE, DASH, DASHATTACK, ATTACK_DOWN, ATTACK_UP,
		JUMP, JUMP_ATTACK, JUMPDOWN_ATTACK, SKILL1, SKILL2, DEAD, END
	};

public:
	CMetaKnight();
	virtual ~CMetaKnight();

	// CActor을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	
public:
	virtual void ApplyDamage(int iDamage);

private:
	void UpdateState();
	void SceneChange();
	void CreateInhailStar(int iCount);

private:
	void Idle();
	void Move();
	void Dash();
	void DashAttack();
	void Jump();
	void JumpAttack();
	void JumpDownAttack();
	void AttackDown();
	void AttackUp();
	void Skill_1();
	void Skill_2();
	void Dead();

private:
	void SetAnimFrame(int iEnd, int iScene, DWORD dwSpeed);

private:
	STATE m_eCurState;
	STATE m_ePreState;

	int m_iCondition;
	int m_iPatternCnt;

	float m_fMaxBackMove;

	DWORD m_dwStateTime;
	DWORD m_dwIdleTime;
	DWORD m_dwDamageTime;

	CGameObject* m_pTornado;
	CGameObject* m_pHitBox;

	bool m_bDashAttack;
	bool m_bSlashSkill;
	bool m_bTornadoSkill;
};

