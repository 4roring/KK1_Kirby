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

	void DrawAlphaColor(HDC hDC, BYTE Alpha, bool bColor);
	bool SceneStart();
	bool SceneEnd();
	void SceneRestart() { m_ePreScene = SCENE_END; SceneChange(m_eCurScene); }

private:
	CScene* m_pScene;
	SCENEID m_ePreScene;
	SCENEID m_eCurScene;

	int m_Alpha;
	bool m_bFade;
};

