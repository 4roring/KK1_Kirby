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
	BmpManager->RegistBitmap(TEXT("ShootingStar_Left"), TEXT("../Image/Effect/ShootingStar_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("ShootingStar_Right"), TEXT("../Image/Effect/ShootingStar_Right.bmp"));
	BmpManager->RegistBitmap(TEXT("InhailStar"), TEXT("../Image/Effect/InhailStar.bmp"));
	BmpManager->RegistBitmap(TEXT("Star"), TEXT("../Image/Effect/Star.bmp"));
	BmpManager->RegistBitmap(TEXT("MiniStar"), TEXT("../Image/Effect/MiniStar.bmp"));
	BmpManager->RegistBitmap(TEXT("ClearStar"), TEXT("../Image/Effect/ClearStar.bmp"));
	BmpManager->RegistBitmap(TEXT("Transform_Effect"), TEXT("../Image/Effect/Transform_Effect.bmp"));

	// 플레이어 로딩
	BmpManager->RegistBitmap(TEXT("Normal_Left"), TEXT("../Image/Kirby/Normal_Kirby/Normal_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Right"), TEXT("../Image/Kirby/Normal_Kirby/Normal_Right.bmp"));
	BmpManager->RegistBitmap(TEXT("Sword_Left"), TEXT("../Image/Kirby/Sword_Kirby/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Sword_Right"), TEXT("../Image/Kirby/Sword_Kirby/Right.bmp"));
	BmpManager->RegistBitmap(TEXT("Sword_LeftAttack"), TEXT("../Image/Kirby/Sword_Kirby/Left_Attack.bmp"));
	BmpManager->RegistBitmap(TEXT("Sword_RightAttack"), TEXT("../Image/Kirby/Sword_Kirby/Right_Attack.bmp"));



	// 적 캐릭터 로딩
	BmpManager->RegistBitmap(TEXT("Wadorudi_Left"), // 와도루디
		TEXT("../Image/Enemy/Wadorudi/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Wadorudi_Right"),
		TEXT("../Image/Enemy/Wadorudi/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("Scarfy_Left"), // 스컬피
		TEXT("../Image/Enemy/Scarfy/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Scarfy_Right"),
		TEXT("../Image/Enemy/Scarfy/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("SwordKnight_Left"), // 소드 나이트
		TEXT("../Image/Enemy/SwordKnight/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("SwordKnight_Right"),
		TEXT("../Image/Enemy/SwordKnight/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("DDD_Left"), // DDD
		TEXT("../Image/Enemy/DDD/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("DDD_Right"),
		TEXT("../Image/Enemy/DDD/RIght.bmp"));

	BmpManager->RegistBitmap(TEXT("MetaKnight_Apper"), // 메타나이트
		TEXT("../Image/Enemy/MetaKnight/Appear.bmp"));
	BmpManager->RegistBitmap(TEXT("MetaKnight_Dead"), 
		TEXT("../Image/Enemy/MetaKnight/Dead.bmp"));
	BmpManager->RegistBitmap(TEXT("MetaKnight_Left"), 
		TEXT("../Image/Enemy/MetaKnight/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("MetaKnight_Right"), 
		TEXT("../Image/Enemy/MetaKnight/Right.bmp"));

	SceneManager->SceneChange(SCENE_BOSS);
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
	SceneManager->DestroyInstance();
	GameManager->DestroyInstance();
	InputManager->DestroyInstance();
	BmpManager->DestroyInstance();


	ReleaseDC(g_hWnd, m_hDC);
}


