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


	// �������� 1 ���, �� �ε�
	BmpManager->RegistBitmap(TEXT("Map_Stage1_Background"), TEXT("../Image/Map/Stage1_Background.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Stage1_1_Ground"), TEXT("../Image/Map/Stage1-1.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Stage1_2_Ground"), TEXT("../Image/Map/Stage1-2.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Stage1_3_Ground"), TEXT("../Image/Map/Stage1-3.bmp"));

	// ���� �������� ���, �� �ε�
	BmpManager->RegistBitmap(TEXT("Map_Boss_Background"), TEXT("../Image/Map/Boss_Background.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Boss_Ground"), TEXT("../Image/Map/Boss_Ground.bmp"));

	// �߰� ���� �������� ���, �� �ε�
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_1"), TEXT("../Image/Map/MidBoss_Background_1.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_2"), TEXT("../Image/Map/MidBoss_Background_2.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_3"), TEXT("../Image/Map/MidBoss_Background_3.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_4"), TEXT("../Image/Map/MidBoss_Background_4.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Ground"), TEXT("../Image/Map/MidBoss_Ground.bmp"));

	// ��Ÿ �� �ҽ�
	BmpManager->RegistBitmap(TEXT("Map_Door"), TEXT("../Image/Map/Door.bmp"));

	// ����Ʈ �ε�
	BmpManager->RegistBitmap(TEXT("Normal_Effect"), TEXT("../Image/Effect/Normal_Effect.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Attack_Left"), TEXT("../Image/Effect/NormalAttack_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Attack_Right"), TEXT("../Image/Effect/NormalAttack_Right.bmp"));
	BmpManager->RegistBitmap(TEXT("ShootingStar_Left"), TEXT("../Image/Effect/ShootingStar_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("ShootingStar_Right"), TEXT("../Image/Effect/ShootingStar_Right.bmp"));
	BmpManager->RegistBitmap(TEXT("InhailStar"), TEXT("../Image/Effect/InhailStar.bmp"));

	// �÷��̾� �ε�
	BmpManager->RegistBitmap(TEXT("Normal_Left"), TEXT("../Image/Normal_Kirby/Normal_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Right"), TEXT("../Image/Normal_Kirby/Normal_Right.bmp"));

	// �� ĳ���� �ε�
	BmpManager->RegistBitmap(TEXT("Wadorudi_Left"), // �͵����
		TEXT("../Image/Enemy/Wadorudi/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Wadorudi_Right"),
		TEXT("../Image/Enemy/Wadorudi/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("Scarfy_Left"), // ������
		TEXT("../Image/Enemy/Scarfy/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Scarfy_Right"),
		TEXT("../Image/Enemy/Scarfy/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("DDD_Left"), // DDD
		TEXT("../Image/Enemy/DDD/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("DDD_Right"),
		TEXT("../Image/Enemy/DDD/RIght.bmp"));

	BmpManager->RegistBitmap(TEXT("Black_1_Left"), // �� ��Ÿ����Ʈ
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
	SceneManager->DestroyInstance();
	GameManager->DestroyInstance();
	InputManager->DestroyInstance();
	BmpManager->DestroyInstance();


	ReleaseDC(g_hWnd, m_hDC);
}


