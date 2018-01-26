#pragma once

class CActor;
class CGameObject;
class CCollision
{
public:
	CCollision();
	~CCollision();

public: // 상시 충돌
	static void ActorToActor(OBJLIST& dstList, OBJLIST& srcList);
	static void Ground(OBJLIST& dstList, OBJLIST& srcList);
	static bool PlayerToGround(CActor * pPlayer, OBJLIST & srcList);
	static bool Screen(RECT& tScreen, CGameObject* pObj);
	static void HitBox(OBJLIST& dstList, OBJLIST& srcList);
	static bool InhailToEnemy(CGameObject* pObj, OBJLIST& EnemyList);
	static void InterectionDoor(CGameObject* pObj, OBJLIST& InterectionList);
};

