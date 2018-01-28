#include "stdafx.h"
#include "Title.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
}

void CTitle::Initialize()
{
	m_bTitle = false;
	m_bNextScene = false;
}

void CTitle::LateInit()
{
}

void CTitle::Update()
{
	if (InputManager->KeyDown(VK_RETURN))
		m_bNextScene = true;


	if (m_bNextScene)
		if (SceneManager->SceneEnd())
			SceneManager->SceneChange(SCENE_STAGE1);
}

void CTitle::LateUpdate()
{
}

void CTitle::Render(HDC hDC)
{
	if (g_iFrame % 20 == 0)
		m_bTitle = !m_bTitle;

	if(m_bTitle)
		DrawBackground(hDC, TEXT("Title_1"));
	else
		DrawBackground(hDC, TEXT("Title_2"));
}

void CTitle::Release()
{
}
