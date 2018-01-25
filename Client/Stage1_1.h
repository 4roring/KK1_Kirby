#pragma once
#include "Scene.h"
class CStage1_1 :
	public CScene
{
public:
	CStage1_1();
	virtual ~CStage1_1();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

