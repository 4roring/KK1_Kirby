#pragma once
#include "GameObject.h"
class CActor :
	public CGameObject
{
public:
	CActor();
	virtual ~CActor();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() PURE;
	virtual void LateInit() PURE;
	virtual OBJ_STATE Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

protected:
	int iMaxHp;
	int iHp;
	
	float m_fSpeed;
	float m_fJumpPow;

	float m_fVelocityX;
	float m_fVelocityY;
	float m_fAccX;
	float m_fAccY;
};

