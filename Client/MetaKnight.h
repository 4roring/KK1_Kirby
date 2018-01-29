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
	void SceneChange();
	void CreateInhailStar();

private:
	STATE m_eCurState;
	STATE m_ePreState;

	int m_iCondition;
	int m_iPatternCnt;

	float m_fMaxBackMove;

	DWORD m_dwStateTime;
	DWORD m_dwIdleTime;
};

