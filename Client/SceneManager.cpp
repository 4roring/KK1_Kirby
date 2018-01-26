#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Stage1_1.h"
#include "MidBoss.h"
#include "Boss.h"


CSceneManager::CSceneManager()
	: m_pScene(nullptr), m_ePreScene(SCENE_END), m_eCurScene(SCENE_END)
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
			break;
		case SCENE_STAGE1:
			m_pScene = new CStage1_1;
			break;
		case SCENE_MIDBOSS:
			m_pScene = new CMidBoss;
			break;
		case SCENE_BOSS:
			m_pScene = new CBoss;
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
	m_pScene->Update();
}

void CSceneManager::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneManager::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneManager::Release()
{
	SafeDelete<CScene*>(m_pScene);
}
