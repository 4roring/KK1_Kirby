#pragma once

class CGameObject;
class CCollision
{
public:
	CCollision();
	~CCollision();

public: // 상시 충돌
	static void HitRect(OBJLIST& dstList, OBJLIST& srcList);
	static void Circle(OBJLIST& dstList, OBJLIST& srcList);
	static bool Ground(OBJLIST& dstList, OBJLIST& srcList);

public:
	static bool CheckCircle(CGameObject* pDst, CGameObject *pSrc);
};

