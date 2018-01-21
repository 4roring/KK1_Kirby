#pragma once
#include "Actor.h"
class CKirby :
	public CActor
{
public:
	enum STATE { IDLE, DOWN, SLIDE, MOVE, JUMP, ATTACK, END };

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
	void SceneChange();

private:
	TCHAR* m_pFrameKey;
	STATE m_eCurState;
	STATE m_ePreState;
};

