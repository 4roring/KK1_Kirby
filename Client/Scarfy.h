#pragma once
#include "Enemy.h"
class CScarfy :
	public CEnemy
{
public:
	CScarfy();
	virtual ~CScarfy();

	// CEnemy을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void ApplyDamage(int iDamage) override;

private:
	void Transform();
	void NormalState();
	void TransformState();

private:
	bool m_bTransform;
};

