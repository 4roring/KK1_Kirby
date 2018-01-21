#pragma once

#define WINCX 720
#define WINCY 600

#define PURE = 0

#define GameManager() CGameManager::GetInstance()
#define InputManager() CInputManager::GetInstance()
#define BmpManager() CBmpManager::GetInstance()

#define MAKE_PAIR(KEY, VALUE) MAPBIT::value_type(KEY, VALUE)
