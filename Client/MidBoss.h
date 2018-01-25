#pragma once
#include "Scene.h"
class CMidBoss :
	public CScene
{
public:
	CMidBoss();
	virtual ~CMidBoss();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

