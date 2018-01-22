#pragma once

class CGameObject;

class CMath
{
public:
	CMath();
	~CMath();

public:
	static float Distance(CGameObject* pDst, CGameObject* pSrc);
};

