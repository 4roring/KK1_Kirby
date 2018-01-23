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
		pObj->SetPos(fX, fY);
		pObj->LateInit();
	

		return pObj;
	}

	static CGameObject* CreateObject(float fX, float fY, bool bFlipX)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetFlipX(bFlipX);
		pObj->LateInit();
	
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