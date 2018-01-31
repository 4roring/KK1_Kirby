#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Stage1_1.h"
#include "MidBoss.h"
#include "SpecialMap.h"
#include "Boss.h"
#include "Title.h"
#include "Ending.h"


CSceneManager::CSceneManager()
	: m_pScene(nullptr), m_ePreScene(SCENE_END), m_eCurScene(SCENE_END), m_Alpha(0), m_bFade(false)
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::SceneChange(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		SafeDelete<CScene*>(m_pScene);

		switch (m_eCurScene)
		{
		case SCENE_LOGO:
			break;
		case SCENE_TITLE:
			m_pScene = new CTitle;
			break;
		case SCENE_STAGE1:
			m_pScene = new CStage1_1;
			break;
		case SCENE_MIDBOSS:
			m_pScene = new CMidBoss;
			break;
		case SCENE_SPECIAL:
			m_pScene = new CSpecialMap;
			break;
		case SCENE_BOSS:
			m_pScene = new CBoss;
			break;
		case SCENE_END:
			m_pScene = new CEnding;
			break;
		}

		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneManager::LateInit()
{
	m_pScene->LateInit();
}

void CSceneManager::Update()
{
	if (!m_bFade)
		m_pScene->Update();
	else
		SceneStart();
}

void CSceneManager::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneManager::Render(HDC hDC)
{
	m_pScene->Render(hDC);
	DrawAlphaColor(hDC, m_Alpha, true);
}

void CSceneManager::Release()
{
	SafeDelete<CScene*>(m_pScene);
}

// Color이 true면 흰색, false면 검정색
void CSceneManager::DrawAlphaColor(HDC hDC, BYTE Alpha, bool bColor)
{
	HDC hMemDC;
	if(bColor)
		hMemDC = BmpManager->GetMapBit()[TEXT("BackWhite")]->GetMemDC();
	else
		hMemDC = BmpManager->GetMapBit()[TEXT("BackBlack")]->GetMemDC();

	BLENDFUNCTION bf = { 0, 0, Alpha, 0 };

	GdiAlphaBlend(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, WINCX, WINCY, bf);
}

bool CSceneManager::SceneStart()
{
	if (m_Alpha >= 10)
		m_Alpha -= 6;
	else
	{
		m_Alpha = 0;
		m_bFade = false;
		return true;
	}
	
	return false;
}

bool CSceneManager::SceneEnd()
{
	if (m_Alpha < 245)
		m_Alpha += 6;
	else
	{
		m_Alpha = 255;
		m_bFade = true;
		return true;
	}
		
	return false;
}
