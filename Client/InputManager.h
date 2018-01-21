#pragma once

#define VIR_KEY 0xff

class CInputManager :
	public CSingleton<CInputManager>
{
public:
	CInputManager();
	virtual ~CInputManager();

public:
	bool Key(int iKey)
	{
		if (GetAsyncKeyState(iKey) & 0x8000)
			return true;

		return false;
	}

	bool KeyDown(int iKey)
	{
		if (!m_bInput[iKey] && GetAsyncKeyState(iKey) & 0x8000)
		{
			m_bInput[iKey] = !m_bInput[iKey];
			return true;
		}
		return false;
	}

	bool KeyUp(int iKey)
	{
		if (m_bInput[iKey] && !(GetAsyncKeyState(iKey) & 0x8000))
		{
			m_bInput[iKey] = !m_bInput[iKey];
			return true;
		}
		return false;
	}

public:
	void Update()
	{
		for (int i = 0; i < VIR_KEY; ++i)
		{
			if (!m_bInput[i] && GetAsyncKeyState(i) & 0x8000)
				m_bInput[i] = !m_bInput[i];
				
			if (m_bInput[i] && !(GetAsyncKeyState(i) & 0x8000))
				m_bInput[i] = !m_bInput[i];
		}
	}

private:
	bool m_bInput[VIR_KEY];
};

