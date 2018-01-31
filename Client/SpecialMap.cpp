#include "stdafx.h"
#include "Kirby.h"
#include "SpecialMap.h"
#include "Mario.h"
#include "Ground.h"


CSpecialMap::CSpecialMap()
{
}


CSpecialMap::~CSpecialMap()
{
	Release();
}

void CSpecialMap::Initialize()
{
	if (GameManager->GetObjList(OBJ_PLAYER).empty())
		GameManager->AddObject(CAbsFactory<CKirby>::CreateObject(100.f, 450.f), OBJ_PLAYER);
	else
		GameManager->GetPlayer()->SetPos(100.f, 510.f);

	GameManager->AddObject(CAbsFactory<CMario>::CreateObject(600.f, 450.f), OBJ_ENEMY);

	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ WINCX, 0, WINCX+50, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ -50, 505, 850, WINCY }), OBJ_GROUND);

	SoundManager->PlayBGM(TEXT("vsMario.mp3"));

	GameManager->SetScrollX(0.f);
	GameManager->SetMaxScrollX(-8.f);

	GameManager->SetScrollY(0.f);
	GameManager->SetMaxScrollY(0.f);
}

void CSpecialMap::LateInit()
{
	GameManager->LateInit();
}

void CSpecialMap::Update()
{
	GameManager->Update();
}

void CSpecialMap::LateUpdate()
{
	GameManager->LateUpdate();
}

void CSpecialMap::Render(HDC hDC)
{
	DrawBackground(hDC, TEXT("Map_Special_Background"));
	DrawGround(hDC, TEXT("Map_Special_Ground"));
	GameManager->Render(hDC);
}

void CSpecialMap::Release()
{
	SoundManager->StopSound(CSoundManager::BGM);
	GameManager->ReleaseObj(OBJ_GROUND);
	GameManager->ReleaseObj(OBJ_ENEMY);
	GameManager->GetObjList(OBJ_UI).back()->SetActive(false);
	GameManager->ReleaseObj(ENEMY_ATT);
}
