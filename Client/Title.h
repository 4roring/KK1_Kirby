#pragma once
#include "Scene.h"
class CTitle :
	public CScene
{
public:
	CTitle();
	virtual ~CTitle();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
