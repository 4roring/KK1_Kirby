#pragma once
class CBmp
{
public:
	CBmp();
	~CBmp();

public:
	HDC GetMemDC() { return m_hMemDC; }

public:
	CBmp* LoadBmp(const TCHAR* pFilePath);
	void Release();

public:
	LONG GetBmpCX() { return m_tBitInfo.bmWidth; }
	LONG GetBmpCY() { return m_tBitInfo.bmHeight; }

private:
	HDC m_hDC;
	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hBitOld;

	BITMAP m_tBitInfo;
};

