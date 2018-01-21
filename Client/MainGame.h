#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void LateInit();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	void DrawBackground(HDC hDC, const TCHAR* szName);

private:
	HDC m_hDC;
};

