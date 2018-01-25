#include "stdafx.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Scene.h"


CGameManager::CGameManager()
{
	m_fScrollX = 0;
	m_fScrollY = 0;
	m_fMaxScrollX = 0;
	m_fMaxScrollY = 0;
}


CGameManager::~CGameManager()
{
	Release();
}

void CGameManager::AddObject(CGameObject * pObject, OBJID eID)
{
	m_ObjectList[eID].push_back(pObject);
}

void CGameManager::ReleaseObj(OBJID eID)
{
	std::for_each(m_ObjectList[eID].begin(), m_ObjectList[eID].end(), SafeDelete<CGameObject*>);
	m_ObjectList[eID].clear();
}

void CGameManager::LateInit()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObject : m_ObjectList[i])
			pObject->LateInit();
	}
}

void CGameManager::Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			if ((*iter)->Update() == DESTROY)
			{
				SafeDelete<CGameObject*>(*iter);
				iter = m_ObjectList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	if (m_fScrollX > 0)
		m_fScrollX = 0;

	if (m_fScrollY > 0)
		m_fScrollY = 0;

	if (m_fScrollX < m_fMaxScrollX)
		m_fScrollX = m_fMaxScrollX;
}

void CGameManager::LateUpdate()
{
	m_tScreenRect = { LONG(-400 - m_fScrollX), LONG(0 - m_fScrollY),
		LONG(WINCX - m_fScrollX), LONG(WINCY - m_fScrollY) };

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObject : m_ObjectList[i])
			pObject->LateUpdate();
	}

	CCollision::Ground(m_ObjectList[OBJ_ENEMY], m_ObjectList[OBJ_GROUND]);
	CCollision::ActorToActor(m_ObjectList[OBJ_PLAYER], m_ObjectList[OBJ_ENEMY]);
	CCollision::HitBox(m_ObjectList[OBJ_PLAYER], m_ObjectList[ENEMY_ATT]);
	CCollision::HitBox(m_ObjectList[OBJ_ENEMY], m_ObjectList[PLAYER_ATT]);
}

void CGameManager::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObject : m_ObjectList[i])
			pObject->Render(hDC);
	}
}

void CGameManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		std::for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}
