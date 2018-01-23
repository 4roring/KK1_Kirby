#include "stdafx.h"
#include "MainGame.h"
#include "Kirby.h"
#include "BlackMetaKnight.h"
#include "Ground.h"

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
	
	// 배경 로딩
	BmpManager()->RegistBitmap(TEXT("BackBuffer"), TEXT("../Image/BackBuffer.bmp"));
	BmpManager()->RegistBitmap(TEXT("Map_Boss_Background"), TEXT("../Image/Map/Boss_Background.bmp"));
	BmpManager()->RegistBitmap(TEXT("Map_Boss_Ground"), TEXT("../Image/Map/Boss_Ground.bmp"));
	
	// 이펙트 로딩
	BmpManager()->RegistBitmap(TEXT("Normal_Effect"), TEXT("../Image/Effect/Normal_Effect.bmp"));
	BmpManager()->RegistBitmap(TEXT("Normal_Attack_Left"), TEXT("../Image/Effect/NormalAttack_Left.bmp"));
	BmpManager()->RegistBitmap(TEXT("Normal_Attack_Right"), TEXT("../Image/Effect/NormalAttack_Right.bmp"));

	GameManager()->AddObject(CAbsFactory<CKirby>::CreateObject(), OBJ_PLAYER);
	GameManager()->AddObject(CAbsFactory<CBlackMetaKnight>::CreateObject(), OBJ_ENEMY);
	
	GameManager()->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 0, 484, WINCX, WINCY }), OBJ_GROUND);
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

	DrawBackground(hBackBuffer, TEXT("Map_Boss_Background"));
	DrawGround(hBackBuffer, TEXT("Map_Boss_Ground"));
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

void CMainGame::DrawGround(HDC hDC, const TCHAR * szName)
{
	int iScrollX = (int)GameManager()->GetScrollX();
	int iScrollY = (int)GameManager()->GetScrollY();

	HDC hMemDC = BmpManager()->GetMapBit()[szName]->GetMemDC();

	int iSizeX = BmpManager()->GetMapBit()[szName]->GetBmpCX();
	int iSizeY = BmpManager()->GetMapBit()[szName]->GetBmpCY();

	GdiTransparentBlt(hDC, iScrollX, iScrollY,
		iSizeX, iSizeY, hMemDC,
		0, 0, iSizeX, iSizeY, RGB(255, 0, 255));
}


