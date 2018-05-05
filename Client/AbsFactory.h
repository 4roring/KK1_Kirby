#pragma once

class CGameObject;
class CActor;
class CDoor;
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

	// HitBoxType에 따라 한방에 사라질지 생성자가 직접 삭제할지 결정, 사운드 타입 선택
	static CGameObject* CreateHitBox(float fX, float fY , int iCX, int iCY, int iAtt, bool bHitBoxType, HIT_SOUNDTYPE eType)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetHitBox(iCX, iCY);
		pObj->SetAtt(iAtt);
		pObj->SetHitBoxType(bHitBoxType);
		pObj->LateInit();
		pObj->SetHitSoundType(eType);

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

		return pObj;
	}

	static CGameObject* CreateInhailStar(float fX, float fY, ENEMYTYPE eType)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetInhailType(eType);
		pObj->LateInit();

		return pObj;
	}

	static CGameObject* CreateDoor(float fX, float fY, SCENEID eID)
	{
		CGameObject* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->LateInit();
		dynamic_cast<CDoor*>(pObj)->SetSceneID(eID);

		return pObj;
	}
};