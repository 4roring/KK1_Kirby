#include "stdafx.h"
#include "Stage1_1.h"
#include "Kirby.h"
#include "Ground.h"
#include "Wadorudi.h"
#include "Scarfy.h"
#include "Door.h"

CStage1_1::CStage1_1()
{
}


CStage1_1::~CStage1_1()
{
}

void CStage1_1::Initialize()
{
	GameManager->AddObject(CAbsFactory<CKirby>::CreateObject(40.f, 440.f), OBJ_PLAYER);
	GameManager->AddObject(CAbsFactory<CDoor>::CreateObject(3970.f, 127.f), OBJ_INTERECTION);

	// 1-1 ���� BoxCollider
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 4120, 0, 4170, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 1376, 191, 1472, WINCY }), OBJ_GROUND);

	// �����޸� ��
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2414, 84, 2520, 302 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2310, 0, 2680, 84 }), OBJ_GROUND);
	
	// ������!
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(POINT{ 1472, 305 }, POINT{ 1580, 380 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(POINT{ 2190, 460 }, POINT{ 2400, 330 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 1472, 380, 1580, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 936, 406, 1034, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2640, 300, 2735, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2735, 410, 2845, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 3410, 410, 3506, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2400, 335, 2640, WINCY }), OBJ_GROUND);
	
	// ���� ����
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 3742, 135, 3838, 238 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 3838, 187, 4120, 238 }), OBJ_GROUND);

	// ���� �ٴ�
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 1810, 142, 2082, 170 }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 2965, 192, 3236, 226 }), OBJ_GROUND);

	// ���� �� �ٴ�
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 0, 460, 4170, WINCY }), OBJ_GROUND);

	// ����
	GameManager->AddObject(CAbsFactory<CWadorudi>::CreateEnemy(985.f, 350.f), OBJ_ENEMY);
	GameManager->AddObject(CAbsFactory<CScarfy>::CreateEnemy(730.f, 230.f), OBJ_ENEMY);

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
	GameManager->ReleaseObj(OBJ_ENEMY);
}

