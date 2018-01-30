#include "stdafx.h"
#include "SoundManager.h"


CSoundManager::CSoundManager()
	: m_pSystem(nullptr)
{
	ZeroMemory(m_pChannelArr, sizeof(m_pChannelArr));
}


CSoundManager::~CSoundManager()
{
	Release();
}

void CSoundManager::Initialize()
{
	FMOD_RESULT res = FMOD_System_Create(&m_pSystem);

	if (FMOD_OK != res)
	{
		MessageBox(g_hWnd, TEXT("FOMD System Create Failed!"), TEXT("Error!!!"), MB_OK);
		return;
	}

	FMOD_System_Init(m_pSystem, END, FMOD_INIT_NORMAL, nullptr);
	LoadSoundFile();
}

void CSoundManager::LoadSoundFile()
{
	_finddata_t _fd;

	long handle = _findfirst("../Sound/*.*", &_fd);
	int iResult = 0;

	if (handle == 0)
	{
		MessageBox(g_hWnd, TEXT("Not found soundfile"), TEXT("Error!!!"), MB_OK);
		return;
	}

	while (iResult != -1)
	{
		char szFullPath[256] = "../Sound/";
		strcat_s(szFullPath, _fd.name);

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT res = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, nullptr, &pSound);

		if (FMOD_OK == res)
		{
			TCHAR* pSoundKey = new TCHAR[strlen(_fd.name) + 1];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * (strlen(_fd.name) + 1));

			MultiByteToWideChar(CP_ACP, 0, _fd.name, strlen(_fd.name), pSoundKey, strlen(_fd.name));
			m_MapSound.insert(SOUND_MAP_PAIR(pSoundKey, pSound));
		}
		iResult = _findnext(handle, &_fd);
	}
	_findclose(handle);

	FMOD_System_Update(m_pSystem);
}

void CSoundManager::Update()
{
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::PlaySound(const TCHAR * pSoundKey, ChannelID eID)
{
	auto iter_find = find_if(m_MapSound.begin(), m_MapSound.end(), 
		[&pSoundKey](auto& MyPair)->bool
	{
		if (!lstrcmp(pSoundKey, MyPair.first))
			return true;

		return false;
	});

	if (iter_find == m_MapSound.end())
	{
		MessageBox(g_hWnd, TEXT("Not found soundfile"), TEXT("Error!!!"), MB_OK);
		return;
	}

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE
		, iter_find->second, FALSE, &m_pChannelArr[eID]);
}

void CSoundManager::PlayBGM(const TCHAR * pSoundKey)
{
	auto iter_find = find_if(m_MapSound.begin(), m_MapSound.end(),
		[&pSoundKey](auto& MyPair)->bool
	{
		if (!lstrcmp(pSoundKey, MyPair.first))
			return true;

		return false;
	});

	if (iter_find == m_MapSound.end())
	{
		MessageBox(g_hWnd, TEXT("Not found soundfile"), TEXT("Error!!!"), MB_OK);
		return;
	}

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE,
		iter_find->second, FALSE, &m_pChannelArr[BGM]);

	FMOD_Channel_SetMode(m_pChannelArr[BGM], FMOD_LOOP_NORMAL);
}

void CSoundManager::StopSound(ChannelID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[eID]);
}

void CSoundManager::StopAll()
{
	for (int i = 0; i < END; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundManager::Release()
{
	for (auto& MyPair : m_MapSound)
	{
		delete[] MyPair.first;
		FMOD_Sound_Release(MyPair.second);
	}

	m_MapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}
