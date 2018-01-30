#pragma once
#include "Actor.h"
class CDDD :
	public CActor
{
public:
	enum STATE 
	{
		IDLE, MOVE, JUMP, 
		HAMMER_RUN, HAMMER_JUMP, HAMMER_ATTACK, 
		DAMAGE, DEAD, END
	};

public:
	CDDD();
	virtual ~CDDD();

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

	DWORD m_dwStateTime;
	DWORD m_dwIdleTime;
	DWORD m_dwDamageTime;
};

