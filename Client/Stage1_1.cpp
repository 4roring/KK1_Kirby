#include "stdafx.h"
#include "Stage1_1.h"
#include "Kirby.h"
#include "Ground.h"
#include "Wadorudi.h"
#include "Scarfy.h"
#include "Door.h"
#include "SwordKnight.h"

CStage1_1::CStage1_1()
{
}


CStage1_1::~CStage1_1()
{
	Release();
}

void CStage1_1::Initialize()
{
	GameManager->AddObject(CAbsFactory<CKirby>::CreateObject(100.f, 440.f), OBJ_PLAYER);
	GameManager->AddObject(CAbsFactory<CDoor>::CreateDoor(3970.f, 127.f, SCENE_MIDBOSS), OBJ_INTERECTION);

	// 1-1 지형 BoxCollider
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 4120, 0, 4170, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 1376, 191, 1472, WINCY }), OBJ_GROUND);

	// 구름달린 벽
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2414, 84, 2520, 310 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2310, 0, 2680, 84 }), OBJ_GROUND);
	
	// 지형들!
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(POINT{ 1472, 305 }, POINT{ 1580, 380 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(POINT{ 2190, 460 }, POINT{ 2400, 340 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 1472, 380, 1580, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 936, 406, 1034, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2640, 300, 2735, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2735, 410, 2845, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 3410, 410, 3506, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2400, 340, 2640, WINCY }), OBJ_GROUND);
	
	// 공중 구름
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 3742, 135, 3838, 238 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 3838, 187, 4120, 238 }), OBJ_GROUND);

	// 공중 바닥
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 1810, 142, 2082, 170 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2965, 192, 3236, 226 }), OBJ_GROUND);

	// 가장 밑 바닥
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 0, 460, 4170, WINCY }), OBJ_GROUND);

	// 몬스터
	GameManager->AddObject(CAbsFactory<CWadorudi>::CreateEnemy(985.f, 350.f), OBJ_ENEMY);
	GameManager->AddObject(CAbsFactory<CScarfy>::CreateEnemy(1540.f, 105.f), OBJ_ENEMY);
	GameManager->AddObject(CAbsFactory<CWadorudi>::CreateEnemy(2010.f, 60.f), OBJ_ENEMY);
	GameManager->AddObject(CAbsFactory<CWadorudi>::CreateEnemy(2050.f, 315.f), OBJ_ENEMY);
	GameManager->AddObject(CAbsFactory<CSwordKnight>::CreateEnemy(2090.f, 330.f), OBJ_ENEMY);
	GameManager->AddObject(CAbsFactory<CScarfy>::CreateEnemy(2800.f, 180.f), OBJ_ENEMY);
	GameManager->AddObject(CAbsFactory<CSwordKnight>::CreateEnemy(3050.f, 140.f), OBJ_ENEMY);
	GameManager->AddObject(CAbsFactory<CWadorudi>::CreateEnemy(3150.f, 140.f), OBJ_ENEMY);
	GameManager->AddObject(CAbsFactory<CWadorudi>::CreateEnemy(3300.f, 400.f), OBJ_ENEMY);

	SoundManager->PlayBGM(TEXT("Stage1.mp3"));

	GameManager->SetScrollX(0.f);
	GameManager->SetMaxScrollX(-3450.f);

	GameManager->SetScrollY(0.f);
	GameManager->SetMaxScrollY(0.f);
}

void CStage1_1::LateInit()
{
	GameManager->LateInit();
}

void CStage1_1::Update()
{
	GameManager->Update();
}

void CStage1_1::LateUpdate()
{
	GameManager->LateUpdate();
}

void CStage1_1::Render(HDC hDC)
{
	DrawBackground(hDC, TEXT("Map_Stage1_Background"));
	DrawGround(hDC, TEXT("Map_Stage1_1_Ground"));
	GameManager->Render(hDC);
}

void CStage1_1::Release()
{
	SoundManager->StopSound(CSoundManager::BGM);
	GameManager->ReleaseObj(OBJ_GROUND);
	GameManager->ReleaseObj(OBJ_ENEMY);
}

