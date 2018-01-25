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


	// 스테이지 1 배경, 땅 로딩
	BmpManager->RegistBitmap(TEXT("Map_Stage1_Background"), TEXT("../Image/Map/Stage1_Background.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Stage1_1_Ground"), TEXT("../Image/Map/Stage1-1.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Stage1_2_Ground"), TEXT("../Image/Map/Stage1-2.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Stage1_3_Ground"), TEXT("../Image/Map/Stage1-3.bmp"));

	// 보스 스테이지 배경, 땅 로딩
	BmpManager->RegistBitmap(TEXT("Map_Boss_Background"), TEXT("../Image/Map/Boss_Background.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Boss_Ground"), TEXT("../Image/Map/Boss_Ground.bmp"));

	// 중간 보스 스테이지 배경, 땅 로딩
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_1"), TEXT("../Image/Map/MidBoss_Background_1.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_2"), TEXT("../Image/Map/MidBoss_Background_2.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_3"), TEXT("../Image/Map/MidBoss_Background_3.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_4"), TEXT("../Image/Map/MidBoss_Background_4.bmp"));

	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Ground"), TEXT("../Image/Map/MidBoss_Ground.bmp"));

	// 기타 맵 소스
	BmpManager->RegistBitmap(TEXT("Map_Door"), TEXT("../Image/Map/Door.bmp"));

	// 이펙트 로딩
	BmpManager->RegistBitmap(TEXT("Normal_Effect"), TEXT("../Image/Effect/Normal_Effect.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Attack_Left"), TEXT("../Image/Effect/NormalAttack_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Attack_Right"), TEXT("../Image/Effect/NormalAttack_Right.bmp"));
	BmpManager->RegistBitmap(TEXT("ShootingStar_Effect"), TEXT("../Image/Effect/ShootingStar_Effect.bmp"));

	// 플레이어 로딩
	BmpManager->RegistBitmap(TEXT("Normal_Left"), TEXT("../Image/Normal_Kirby/Normal_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Right"), TEXT("../Image/Normal_Kirby/Normal_Right.bmp"));

	// 적 캐릭터 로딩
	BmpManager->RegistBitmap(TEXT("Wadorudi_Left"), // 와도루디
		TEXT("../Image/Enemy/Wadorudi/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Wadorudi_Right"),
		TEXT("../Image/Enemy/Wadorudi/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("Scarfy_Left"), // 스컬피
		TEXT("../Image/Enemy/Scarfy/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Scarfy_Right"),
		TEXT("../Image/Enemy/Scarfy/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("Black_1_Left"), // 블랙 메타나이트
		TEXT("../Image/Enemy/BlackMetaKnight/Left_Move_Attack.bmp"));
	BmpManager->RegistBitmap(TEXT("Black_1_Right"),
		TEXT("../Image/Enemy/BlackMetaKnight/Right_Move_Attack.bmp"));

	SceneManager->SceneChange(SCENE_STAGE1);
}

void CMainGame::LateInit()
{
	SceneManager->LateInit();
}

void CMainGame::Update()
{
	SceneManager->Update();

	InputManager->Update();
}

void CMainGame::LateUpdate()
{
	SceneManager->LateUpdate();
}

void CMainGame::Render()
{
	HDC hBackBuffer = BmpManager->GetMapBit()[TEXT("BackBuffer")]->GetMemDC();

	SceneManager->Render(hBackBuffer);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	GameManager->DestroyInstance();
	InputManager->DestroyInstance();
	BmpManager->DestroyInstance();
	SceneManager->DestroyInstance();

	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::DrawBackground(HDC hDC, const TCHAR* szName)
{
	HDC hMemDC = BmpManager->GetMapBit()[szName]->GetMemDC();

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CMainGame::DrawGround(HDC hDC, const TCHAR * szName)
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


