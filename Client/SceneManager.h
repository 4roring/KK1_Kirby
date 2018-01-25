#pragma once

class CScene;
class CSceneManager :
	public CSingleton<CSceneManager>
{
public:
	CSceneManager();
	~CSceneManager();

public:
	void SceneChange(SCENEID eID);
	void LateInit();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

private:
	CScene* m_pScene;
	SCENEID m_ePreScene;
	SCENEID m_eCurScene;
};

