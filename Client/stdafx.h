// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <io.h>

#ifdef _DEBUG
#include "vld.h"
#include <iostream>
#pragma comment (linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#include "../FMOD/fmod.h"
#include "../FMOD/fmod.hpp"

#pragma comment(lib, "fmodex_vc.lib")


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Typedef.h"
#include "Define.h"
#include "Enum.h"
#include "Extern.h"
#include "Function.h"
#include "Struct.h"
#include "Math.h"
#include "Collision.h"

#include "AbsFactory.h"
#include "GameManager.h"
#include "InputManager.h"
#include "BmpManager.h"
#include "SceneManager.h"
#include "SoundManager.h"