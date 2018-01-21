#pragma once
#include "Bmp.h"

class CBmpManager :
	public CSingleton<CBmpManager>
{
public:
	CBmpManager();
	virtual ~CBmpManager();

public:
	MAPBIT& GetMapBit() { return m_MapBit; }

public:
	void RegistBitmap(const TCHAR* szName, TCHAR* szRoot);

public:
	void Release();

private:
	MAPBIT m_MapBit;
};

