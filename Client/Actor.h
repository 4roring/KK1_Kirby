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

public:
	float GetVelocityX() { return m_fVelocityX; }
	float GetVelocityY() { return m_fVelocityY; }
	float GetStartX() { return m_fStartX; }
	float GetStartY() { return m_fStartY; }
	bool GetIsDamage() { return m_bIsDamage; }
	float GetHpRatio() { return m_iHp / (float)m_iMaxHp; }

public:
	void SetVelocityX(float fVelocityX) { m_fVelocityX = fVelocityX; }
	void SetVelocityY(float fVelocityY) { m_fVelocityY = fVelocityY; }
	void SetStartPos(float fX, float fY) { m_fStartX = fX, m_fStartY = fY; }
	void SetPosToStart() { m_tInfo.fX = m_fStartX, m_tInfo.fY = m_fStartY; }

	
public: // 전투 관련
	virtual void ApplyDamage(int iDamage) { m_iHp -= iDamage; }

protected:
	int m_iMaxHp;
	int m_iHp;
	
	float m_fStartX;
	float m_fStartY;

	float m_fJumpPow;

	float m_fGravity;
	float m_fDrag;

	float m_fVelocityX;
	float m_fVelocityY;
	float m_fAccX;
	float m_fAccY;

	bool m_bIsDamage;
};

