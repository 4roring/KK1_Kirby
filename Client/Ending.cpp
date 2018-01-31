#include "stdafx.h"
#include "Ending.h"


CEnding::CEnding()
{
}


CEnding::~CEnding()
{
	Release();
}

void CEnding::Initialize()
{

	SoundManager->PlayBGM(TEXT("Ending.mp3"));
}

void CEnding::LateInit()
{
}

void CEnding::Update()
{
	if (InputManager->KeyDown(VK_RETURN))
		DestroyWindow(g_hWnd);
}

void CEnding::LateUpdate()
{
}

void CEnding::Render(HDC hDC)
{
	DrawBackground(hDC, TEXT("Ending"));
}

void CEnding::Release()
{
}
