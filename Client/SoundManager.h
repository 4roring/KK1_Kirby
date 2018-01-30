#pragma once
#include "Function.h"
class CSoundManager :
	public CSingleton<CSoundManager>
{
public:
	enum ChannelID { BGM, PLAYER, ENEMY, EFFECT, END };

public:
	CSoundManager();
	virtual ~CSoundManager();

public:
	void Initialize();
	void LoadSoundFile();
	void Update();
	void PlaySound(const TCHAR* pSoundKey, ChannelID eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(ChannelID eID);
	void StopAll();
	void Release();

private:
	FMOD_SYSTEM* m_pSystem;
	FMOD_CHANNEL* m_pChannelArr[END];
	MAPSOUND m_MapSound;
};

