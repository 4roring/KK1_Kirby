#pragma once

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;
}INFO;

typedef struct tagFrame
{
	int iStart;
	int iEnd;
	int iScene;

	DWORD dwTime;
	DWORD dwSpeed;
}FRAME;