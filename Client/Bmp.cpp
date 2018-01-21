#include "stdafx.h"
#include "Bmp.h"


CBmp::CBmp()
{
}


CBmp::~CBmp()
{
	Release();
}

CBmp * CBmp::LoadBmp(const TCHAR * pFilePath)
{
	m_hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(m_hDC);
	ReleaseDC(g_hWnd, m_hDC);

	m_hBitmap = (HBITMAP)LoadImage(0, pFilePath, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hBitOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	return this;
}

void CBmp::Release()
{
	SelectObject(m_hMemDC, m_hBitOld);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
