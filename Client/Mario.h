#pragma once
#include "Actor.h"
class CMario :
	public CActor
{
public:
	enum STATE { IDLE, MOVE, JUMP, DOWNATTACK, FIRE, DEAD, INHAIL, END };

public:
	CMario();
	virtual ~CMario();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void ApplyDamage(int iDamage);
	void isInhail();
	void SceneChange();
	void CreateInhailStar();
	void Shot();

private:
	STATE m_eCurState;
	STATE m_ePreState;

	int m_iCondition;
	int m_iPatternCnt;

	DWORD m_dwStateTime;
	DWORD m_dwIdleTime;
	DWORD m_dwDamageTime;
};

