#pragma once

class CGameObject;
class CGameManager :
	public CSingleton<CGameManager>
{
public:
	CGameManager();
	virtual ~CGameManager();

public:
	CGameObject* GetPlayer() { return m_ObjectList[OBJ_PLAYER].back(); }
	OBJLIST& GetObjList(OBJID eID) { return m_ObjectList[eID]; }
	
	float GetScrollX() { return m_fScrollX; }
	float GetScrollY() { return m_fScrollY; }
	float GetMaxScrollX() { return m_fMaxScrollX; }
	float GetMaxScrollY() { return m_fMaxScrollY; }
	RECT& GetScreen() { return m_tScreenRect; }

public:
	void SetScrollX(float fX) { m_fScrollX -= fX; }
	void SetScrollY(float fY) { m_fScrollY -= fY; }
	void SetMaxScrollX(float fX) { m_fMaxScrollX = fX; }
	void SetMaxScrollY(float fY) { m_fMaxScrollY = fY; }

public:
	void AddObject(CGameObject* pObject, OBJID eID);
	void ReleaseObj(OBJID eID);

public:
	void LateInit();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();


private:
	OBJLIST m_ObjectList[OBJ_END];

	RECT m_tScreenRect;

	float m_fScrollX;
	float m_fScrollY;

	float m_fMaxScrollX;
	float m_fMaxScrollY;
};

