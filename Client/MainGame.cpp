#include "stdafx.h"
#include "MainGame.h"
#include "Kirby.h"
#include "BlackMetaKnight.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	BmpManager()->RegistBitmap(TEXT("BackBuffer"), TEXT("../Image/BackBuffer.bmp"));
	BmpManager()->RegistBitmap(TEXT("Boss_Background"), TEXT("../Image/Map/Boss_Background.bmp"));
	GameManager()->AddObject(CAbsFactory<CKirby>::CreateObject(), OBJ_PLAYER);
	GameManager()->AddObject(CAbsFactory<CBlackMetaKnight>::CreateObject(), OBJ_ENEMY);
}

void CMainGame::LateInit()
{
	GameManager()->LateInit();
}

void CMainGame::Update()
{
	GameManager()->Update();

	InputManager()->Update();
}

void CMainGame::LateUpdate()
{
	GameManager()->LateUpdate();
}

void CMainGame::Render()
{
	HDC hBackBuffer = BmpManager()->GetMapBit()[TEXT("BackBuffer")]->GetMemDC();

	DrawBackground(hBackBuffer, TEXT("Boss_Background"));
	GameManager()->Render(hBackBuffer);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	GameManager()->DestroyInstance();
	InputManager()->DestroyInstance();
	BmpManager()->DestroyInstance();

	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::DrawBackground(HDC hDC, const TCHAR* szName)
{
	HDC hMemDC = BmpManager()->GetMapBit()[szName]->GetMemDC();

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}


