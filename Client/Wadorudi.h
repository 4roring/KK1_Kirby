#pragma once
#include "Enemy.h"
class CWadorudi :
	public CEnemy
{
public:
	CWadorudi();
	virtual ~CWadorudi();

	// CActor��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual OBJ_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};