#include "stdafx.h"
#include "MainGame.h"


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
	srand((unsigned)time(nullptr));
	BmpManager->RegistBitmap(TEXT("BackBuffer"), TEXT("../Image/BackBuffer.bmp"));
	BmpManager->RegistBitmap(TEXT("BackBlack"), TEXT("../Image/BackBlack.bmp"));
	BmpManager->RegistBitmap(TEXT("BackWhite"), TEXT("../Image/BackWhite.bmp"));
	BmpManager->RegistBitmap(TEXT("Title_1"), TEXT("../Image/Title_1.bmp"));
	BmpManager->RegistBitmap(TEXT("Title_2"), TEXT("../Image/Title_2.bmp"));
	BmpManager->RegistBitmap(TEXT("Title_Load"), TEXT("../Image/Title_Load.bmp"));

	SceneManager->SceneChange(SCENE_TITLE);
}

void CMainGame::LateInit()
{
	SceneManager->LateInit();
}

void CMainGame::Update()
{


	SceneManager->Update();
}

void CMainGame::LateUpdate()
{
	SceneManager->LateUpdate();
	InputManager->Update();
	SoundManager->Update(); // »ç¿îµå
}

void CMainGame::Render()
{
	HDC hBackBuffer = BmpManager->GetMapBit()[TEXT("BackBuffer")]->GetMemDC();

	SceneManager->Render(hBackBuffer);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	SceneManager->DestroyInstance();
	GameManager->DestroyInstance();
	InputManager->DestroyInstance();
	BmpManager->DestroyInstance();
	SoundManager->DestroyInstance();

	ReleaseDC(g_hWnd, m_hDC);
}


