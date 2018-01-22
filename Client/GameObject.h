#pragma once
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	const INFO& GetInfo() { return m_tInfo; }
	const RECT& GetRect() { return m_tRect; }
	const RECT& GetHitBox() { return m_tHitBox; }
	const int& GetHitBoxCX() { return m_iHitBoxCX; }
	const int& GetHitBoxCY() { return m_iHitBoxCY; }
	bool GetActive() { return m_bActive; }

public:
	void SetPos(float fX, float fY) { m_tInfo.fX = fX, m_tInfo.fY = fY; }
	void SetActive(bool bActive) { m_bActive = bActive; }

public:
	virtual void Initialize() PURE;
	virtual void LateInit() PURE;
	virtual OBJ_STATE Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

protected:
	void UpdateRect();
	void UpdateRect(float fX, float fY);
	void FrameMove();
	void DrawObject(HDC hDC, const TCHAR* szName);

protected:
	INFO m_tInfo;
	RECT m_tRect;
	RECT m_tHitBox;

	bool m_bActive;
	bool m_bFlipX;

	int m_iHitBoxCX;
	int m_iHitBoxCY;
	FRAME m_tFrame;

	float m_fGravity;
};

