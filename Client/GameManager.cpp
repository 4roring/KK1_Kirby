#include "stdafx.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Scene.h"


CGameManager::CGameManager()
	: m_bPause(false), m_bDebugBox(false), m_fScrollX(0.f), m_fScrollY(0.f),
	m_fMaxScrollX(0.f), m_fMaxScrollY(0.f), m_fShakingPow(0.f), m_bCameraShaking(false)
{
	m_dwShakingTime = GetTickCount();
}

CGameManager::~CGameManager()
{
	Release();
}

void CGameManager::CameraShakingStart(float fShakePow)
{
	if (!m_bCameraShaking)
	{
		m_bCameraShaking = true;
		m_fShakingPow = fShakePow;
		m_dwShakingTime = GetTickCount() + 10000;
	}
}

void CGameManager::CameraShakingStart(float fShakePow, DWORD dwShakeEndTime)
{
	if (!m_bCameraShaking)
	{
		m_bCameraShaking = true;
		m_fShakingPow = fShakePow;
		m_dwShakingTime = GetTickCount() + dwShakeEndTime;
	}
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
		if (m_bPause) // 변신중에는 몬스터는 못움직임.
			if (i == OBJ_ENEMY)
				continue;

		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			OBJ_STATE eEvent = (*iter)->Update();

			if (eEvent == DESTROY)
			{
				SafeDelete<CGameObject*>(*iter);
				iter = m_ObjectList[i].erase(iter);
			}
			else if (eEvent == WAIT)
			{
				if (iter == m_ObjectList[i].end())
					continue;
				else
					++iter;
			}
			else
				++iter;
		}
	}

	if (m_bCameraShaking)
	{
		m_fShakingPow *= -1.f;
		m_fScrollY = m_fShakingPow;
		if (m_dwShakingTime < GetTickCount())
			CameraShakingEnd();
	}

	if (InputManager->KeyDown('D'))
		m_bDebugBox = !m_bDebugBox;

	if (m_fScrollX > 0.f)
		m_fScrollX = 0.f;

	if (m_fScrollY > 0.f)
		m_fScrollY = 0.f;

	if (m_fScrollX < m_fMaxScrollX)
		m_fScrollX = m_fMaxScrollX;
}

void CGameManager::LateUpdate()
{
	m_tScreenRect = { LONG(-400 - m_fScrollX), LONG(0 - m_fScrollY),
		LONG(WINCX - m_fScrollX), LONG(WINCY - m_fScrollY) };

	for (int i = 0; i < OBJ_END; ++i)
	{
		if (m_bPause) // 변신중에는 몬스터는 못움직임.
			if (i == OBJ_ENEMY)
				continue;

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
