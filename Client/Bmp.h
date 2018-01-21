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

private:
	HDC m_hDC;
	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hBitOld;
};

