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
	const int& GetAtt() { return m_iAtt; }
	bool GetActive() { return m_bActive; }
	bool GetFlipX() { return m_bFlipX; }


public:
	void SetPos(float fX, float fY) { m_tInfo.fX = fX, m_tInfo.fY = fY; }
	void SetHitBox(int iCX, int iCY) { m_iHitBoxCX = iCX, m_iHitBoxCY = iCY; }
	void SetActive(bool bActive) { m_bActive = bActive; }
	void SetFlipX(bool bFlipX) { m_bFlipX = bFlipX; }
	void SetTarget(CGameObject* pObj) { m_pTarget = pObj; }
	void SetInhail() { m_bInhail = true; }

public:
	virtual void Initialize() PURE;
	virtual void LateInit() PURE;
	virtual OBJ_STATE Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;
	void UpdateRect();

protected:
	
	void UpdateRect(float fX, float fY);
	void FrameMove();
	void DrawObject(HDC hDC, const TCHAR* szName);
	void DrawHitBox(HDC hDC);

protected:
	INFO m_tInfo;
	RECT m_tRect;
	RECT m_tHitBox;

	bool m_bActive;
	bool m_bFlipX;
	bool m_bInhail;

	int m_iAtt;
	float m_fSpeed;

	float m_fImageX;
	float m_fImageY;
	int m_iHitBoxCX;
	int m_iHitBoxCY;
	FRAME m_tFrame;
	TCHAR* m_pFrameKey;
	CGameObject* m_pTarget;
};

