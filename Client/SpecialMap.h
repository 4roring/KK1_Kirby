#pragma once
#include "Scene.h"
class CSpecialMap :
	public CScene
{
public:
	CSpecialMap();
	virtual ~CSpecialMap();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

