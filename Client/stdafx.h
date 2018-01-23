// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <cmath>

#include "vld.h"

#include <iostream>
#pragma comment (linker, "/entry:wWinMainCRTStartup /subsystem:console")

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
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