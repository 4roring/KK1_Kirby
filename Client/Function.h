#pragma once

template<typename T>
void SafeDelete(T& obj)
{
	if (obj)
	{
		delete obj;
		obj = nullptr;
	}
}

template <typename T>
class CSingleton
{
protected:
	CSingleton() {}
	virtual ~CSingleton() {}

public:
	static T* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new T;
		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static T* m_pInstance;
};

template <typename T> T * CSingleton<T>::m_pInstance = nullptr;