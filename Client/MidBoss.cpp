#include "stdafx.h"
#include "MidBoss.h"
#include "Ground.h"
#include "Kirby.h"
#include "Wadorudi.h"
#include "DDD.h"

CMidBoss::CMidBoss()
{
}


CMidBoss::~CMidBoss()
{
	Release();
}

void CMidBoss::Initialize()
{
	if (GameManager->GetObjList(OBJ_PLAYER).empty())
		GameManager->AddObject(CAbsFactory<CKirby>::CreateObject(300.f, 400.f), OBJ_PLAYER);
	else
		GameManager->GetPlayer()->SetPos(300.f, 400.f);
	
	// º®
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 0, 0, 190, WINCY }), OBJ_GROUND);
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 1000, 0, 1178, WINCY }), OBJ_GROUND);

	// ¹Ù´Ú
	GameManager->AddObject(CAbsFactory<CGround>::CreateGround(RECT{ 0, 445, 1178, WINCY }), OBJ_GROUND);

	m_pBackgroundKey[0] = TEXT("Map_MidBoss_Background_1");
	m_pBackgroundKey[1] = TEXT("Map_MidBoss_Background_2");
	m_pBackgroundKey[2] = TEXT("Map_MidBoss_Background_3");
	m_pBackgroundKey[3] = TEXT("Map_MidBoss_Background_4");

	m_iBackgroundIdx = 0;
	m_dwBackgroundTime = GetTickCount() + 100;

	// DDD
	GameManager->AddObject(CAbsFactory<CDDD>::CreateObject(900.f, 245.f), OBJ_ENEMY);

	GameManager->SetScrollX(0.f);
	GameManager->SetMaxScrollX(-456.f);

	GameManager->SetScrollY(0.f);
	GameManager->SetMaxScrollY(0.f);
}

void CMidBoss::LateInit()
{
	GameManager->LateInit();
}

void CMidBoss::Update()
{
	GameManager->Update();
}

void CMidBoss::LateUpdate()
{
	GameManager->LateUpdate();

	if (m_dwBackgroundTime < GetTickCount())
	{
		++m_iBackgroundIdx;
		m_dwBackgroundTime = GetTickCount() + 100;

		if (m_iBackgroundIdx > 3)
			m_iBackgroundIdx = 0;
	}
}

void CMidBoss::Render(HDC hDC)
{
	DrawBackground(hDC, m_pBackgroundKey[m_iBackgroundIdx]);
	DrawGround(hDC, TEXT("Map_MidBoss_Ground"));
	GameManager->Render(hDC);
}

void CMidBoss::Release()
{
	GameManager->ReleaseObj(OBJ_GROUND);
	GameManager->ReleaseObj(OBJ_ENEMY);
}
