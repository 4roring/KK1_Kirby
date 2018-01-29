#include "stdafx.h"
#include "Boss.h"
#include "Kirby.h"
#include "MetaKnight.h"
#include "SwordKnight.h"
#include "Ground.h"

CBoss::CBoss()
{
}


CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	GameManager->AddObject(CAbsFactory<CKirby>::CreateObject(150.f, 500.f), OBJ_PLAYER);
	
	GameManager->AddObject(CAbsFactory<CMetaKnight>::CreateObject(600.f, 500.f), OBJ_ENEMY);

	GameManager->AddObject(CAbsFactory<CSwordKnight>::CreateEnemy(500.f, 400.f), OBJ_ENEMY);

	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ WINCX, 0, WINCX + 50, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ -50, 450, WINCX, WINCY }), OBJ_GROUND);

	GameManager->SetScrollX(77.f);
	GameManager->SetMaxScrollX(-38.f);

	GameManager->SetScrollY(0.f);
	GameManager->SetMaxScrollY(0.f);
}

void CBoss::LateInit()
{
	GameManager->LateInit();
}

void CBoss::Update()
{
	GameManager->Update();
}

void CBoss::LateUpdate()
{
	GameManager->LateUpdate();
}

void CBoss::Render(HDC hDC)
{
	DrawBackground(hDC, TEXT("Map_Boss_Background"));
	DrawGround(hDC, TEXT("Map_Boss_Ground"));
	GameManager->Render(hDC);
}

void CBoss::Release()
{
}
