#pragma once

#define WINCX 720
#define WINCY 600

#define PURE = 0

#define GameManager CGameManager::GetInstance()
#define InputManager CInputManager::GetInstance()
#define BmpManager CBmpManager::GetInstance()
#define SceneManager CSceneManager::GetInstance()

#define MAKE_PAIR(KEY, VALUE) MAPBIT::value_type(KEY, VALUE)

#define RAD(degree) degree * 3.14f * 0.005555f
#define DEG(radian) radian * 180.f * 0.318471f
