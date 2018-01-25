#include "stdafx.h"
#include "Boss.h"
#include "Kirby.h"
#include "BlackMetaKnight.h"
#include "Ground.h"

CBoss::CBoss()
{
}


CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	GameManager->AddObject(CAbsFactory<CKirby>::CreateObject(), OBJ_PLAYER);
	GameManager->AddObject(CAbsFactory<CBlackMetaKnight>::CreateObject(), OBJ_ENEMY);

	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 0, 484, WINCX, WINCY }), OBJ_GROUND);
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
