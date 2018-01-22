#pragma once

class CGameObject;

template <typename T>
class CAbsFactory
{
public:
	static CGameObject* CreateObject()
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->LateInit();

		return pObj;
	}

	static CGameObject* CreateObject(float fX, float fY)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->LateInit();
		pObj->SetPos(fX, fY);

		return pObj;
	}

	static CGameObject* CreateGround(RECT& rc)
	{
		CGameObject* pObj = new T(rc);
		pObj->Initialize();
		pObj->LateInit();

		return pObj;
	}
};