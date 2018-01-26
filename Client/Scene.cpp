#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::DrawBackground(HDC hDC, const TCHAR* szName)
{
	HDC hMemDC = BmpManager->GetMapBit()[szName]->GetMemDC();

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CScene::DrawBackground(HDC hDC, const TCHAR * szName, float fScrollX, float fScrollY)
{
	HDC hMemDC = BmpManager->GetMapBit()[szName]->GetMemDC();

	int iSizeX = BmpManager->GetMapBit()[szName]->GetBmpCX();
	int iSizeY = BmpManager->GetMapBit()[szName]->GetBmpCY();

	BitBlt(hDC, (int)fScrollX, (int)fScrollY, iSizeX, iSizeY, hMemDC, 0, 0, SRCCOPY);
}

void CScene::DrawGround(HDC hDC, const TCHAR * szName)
{
	int iScrollX = (int)GameManager->GetScrollX();
	int iScrollY = (int)GameManager->GetScrollY();

	HDC hMemDC = BmpManager->GetMapBit()[szName]->GetMemDC();

	int iSizeX = BmpManager->GetMapBit()[szName]->GetBmpCX();
	int iSizeY = BmpManager->GetMapBit()[szName]->GetBmpCY();

	GdiTransparentBlt(hDC, iScrollX, iScrollY,
		iSizeX, iSizeY, hMemDC,
		0, 0, iSizeX, iSizeY, RGB(255, 0, 255));
}
