#pragma once
#include "GameObject.h"
class CDoor :
	public CGameObject
{
public:
	CDoor();
	virtual ~CDoor();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SetSceneID(SCENEID eID) { m_eSceneID = eID; }

private:
	SCENEID m_eSceneID;
};

