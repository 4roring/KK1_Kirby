#include "stdafx.h"
#include "BmpManager.h"


CBmpManager::CBmpManager()
{
}


CBmpManager::~CBmpManager()
{
	Release();
}

void CBmpManager::RegistBitmap(const TCHAR * szName, TCHAR * szRoot)
{
	CBmp* pBmp = new CBmp;
	m_MapBit.insert(MAKE_PAIR(szName, pBmp->LoadBmp(szRoot)));
}

void CBmpManager::Release()
{
	for_each(m_MapBit.begin(), m_MapBit.end(), 
		[](auto& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	});
}
