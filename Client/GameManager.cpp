#include "stdafx.h"
#include "GameManager.h"
#include "GameObject.h"


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
}

void CGameManager::LateUpdate()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObject : m_ObjectList[i])
			pObject->LateUpdate();
	}

	CCollision::Ground(m_ObjectList[OBJ_ENEMY], m_ObjectList[OBJ_GROUND]);
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
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}
