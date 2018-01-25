#pragma once

class CGameObject;
class CActor;
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

	static CGameObject* CreateObject(CGameObject* pTarget)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->SetTarget(pTarget);
		pObj->LateInit();

		return pObj;
	}

	static CGameObject* CreateHitBox(float fX, float fY , int iCX, int iCY, int iAtt)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetHitBox(iCX, iCY);
		pObj->SetAtt(iAtt);
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

	static CGameObject* CreateGround(POINT& p1, POINT& p2)
	{
		CGameObject* pObj = new T(p1, p2);
		pObj->Initialize();
		pObj->LateInit();

		return pObj;
	}

	static CGameObject* CreateEnemy(float fX, float fY)
	{
		CActor* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetStartPos(fX, fY);

		return dynamic_cast<CGameObject*>(pObj);
	}
};