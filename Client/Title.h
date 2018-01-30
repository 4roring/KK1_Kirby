#pragma once
#include "Scene.h"
class CTitle :
	public CScene
{
public:
	CTitle();
	virtual ~CTitle();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void FileLoad();

private:
	bool m_bTitle;
	bool m_bNextScene;
	bool m_bFileLoad;
};

