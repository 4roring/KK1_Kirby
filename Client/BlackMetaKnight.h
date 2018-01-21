#pragma once
#include "Actor.h"
class CBlackMetaKnight :
	public CActor
{
public:
	enum STATE{IDLE, MOVE, ATTACK, JUMP, SPECIAL1, SPECIAL2, END};

public:
	CBlackMetaKnight();
	virtual ~CBlackMetaKnight();

	// CActor을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void ConditionChange();

private:
	TCHAR* m_pFrameKey;
	int m_iCondition;
};

