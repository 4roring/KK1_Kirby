#pragma once
#include "Enemy.h"
class CSwordKnight :
	public CEnemy
{
public:
	enum STATE {IDLE, ATTACK, DAMAGE, INHAIL, END};

public:
	CSwordKnight();
	virtual ~CSwordKnight();

	// CEnemy을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void SceneChange();

private:
	STATE m_eCurState;
	STATE m_ePreState;

	DWORD m_dwDelayTime;
};

