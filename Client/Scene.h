#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize() PURE;
	virtual void LateInit() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

protected:
	void DrawBackground(HDC hDC, const TCHAR* szName);
	void DrawGround(HDC hDC, const TCHAR* szName);
};

