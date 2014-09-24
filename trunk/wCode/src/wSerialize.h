

// wSerializer.h
//

#ifndef W_SERIALIZE_H
#define W_SERIALIZE_H

#include "wCppExt.h"

namespace w
{

class MySerializer
{
	// data.
	std::auto_ptr<char> m_rawData;
	int m_iRawDataSize = 0;
	int m_iReadPos = 0, m_iWritePos = 0;

	const static int msc_iCtrlMask = 1 << (sizeof(int)*8 - 1);

public:
	enum Ctrl
	{
		CTRL_DEFAULT = 0,
	};

public:
	void *GetRawData() const { return (void *)m_rawData.get(); }
	int GetRawDataSize() const { return m_iWritePos; }

	bool SetRawData(void *p, int size)
	{
		char *pRaw = new char[size];
		if (pRaw == NULL)
		{
			return FALSE;
		}
		m_rawData.reset(pRaw);
		memset(pRaw, 0, size);

		memcpy(pRaw, p, size);
		m_iRawDataSize = size;
		m_iReadPos = 0;
		m_iWritePos = size;

		return TRUE;
	}

	/////////////// PUSH //////////////////
	// POD.
	template <typename T>
	bool Push(const T &t)
	{
		return Push(&t, sizeof(t));
	}
	// Pointer.
	bool Push(const void *p, int iSize)
	{
		// Push the SIZE and VALUE in order.
		return doPush(&iSize, sizeof(iSize)) && doPush(p, iSize);
	}
	// Specified type.
	template <>
	bool Push(const std::string &str)
	{
		return Push(str.c_str(), str.size());
	}
	template <>
	bool Push(const std::wstring &wstr)
	{
		return Push(wstr.c_str(), wstr.size() * sizeof(wchar_t));
	}
	template <>
	bool Push(const MySerializer &ms)
	{
		if (this == &ms)
		{
			// Can NOT push self, which will
			// cause internal state goes wrong.
			return FALSE;
		}

		return Push(ms.GetRawData(), ms.GetRawDataSize());
	}

private:
	//
	bool doPush(const void *p, int iSize)
	{
		if (m_iRawDataSize < m_iWritePos + iSize)
		{
			// Need reallocate memory.
			int iNewMemSize = max(m_iRawDataSize * 2, m_iWritePos + iSize);
			char *pNewMem = new char[iNewMemSize];
			if (pNewMem == NULL)
			{
				return FALSE;
			}
			memset(pNewMem, 0, iNewMemSize);

			char *pOldMem = m_rawData.get();
			if (pOldMem != NULL)
			{
				memcpy(pNewMem, pOldMem, m_iRawDataSize);	// Copy old data `m_rawData` to new area.
			}

			// Update internal storage state.
			m_rawData.reset(pNewMem);
			m_iRawDataSize = iNewMemSize;
		}

		// Copy new data `p` to internal storage.
		char *pRaw = m_rawData.get();
		memcpy(pRaw + m_iWritePos, p, iSize);
		m_iWritePos += iSize;

		return TRUE;
	}

	/////////////// POP //////////////////
	/**
	 *		All Pop operation assume that the 
	 *	container is NOT empty.
	 */
public:
	// POD.
	template <typename T>
	T Pop()
	{
		T t;
		doPopSizeValue(&t, sizeof(t));

		return t;
	}
	// Pointer.
	void Pop(void *p, int iSize)
	{
		doPopSizeValue(p, iSize);
	}
	// Specified type.
	template <>
	std::string Pop<std::string>()
	{
		// Get SIZE at first.
		int iSize = 0;
		doPop(&iSize, sizeof(iSize));
		// Get variable length value.
		char *pValue = new char[iSize];
		if (pValue == NULL)
		{
			return "";
		}
		std::auto_ptr<char> memGuard(pValue);
		memset(pValue, 0, iSize);

		doPop(pValue, iSize);
		std::string str(pValue, iSize);
		return str;
	}
	template <>
	std::wstring Pop<std::wstring>()
	{
		// Get SIZE at first.
		int iSize = 0;
		doPop(&iSize, sizeof(iSize));
		// Get variable length value.
		char *pValue = new char[iSize];
		if (pValue == NULL)
		{
			return L"";
		}
		std::auto_ptr<char> memGuard(pValue);
		memset(pValue, 0, iSize);

		doPop(pValue, iSize);
		std::wstring wstr((wchar_t *)pValue, iSize / sizeof(wchar_t));
		return wstr;
	}

private:
	bool doPopSizeValue(void *p, int iSize)
	{
		// Get data SIZE first.
		int iValueSize = 0;
		doPop(&iValueSize, sizeof(int));
		// Get data VALUE.
		doPop(p, iSize);

		return TRUE;
	}
	bool doPop(void *p, int iSize)
	{
		char *pRawData = m_rawData.get();
		memcpy(p, pRawData + m_iReadPos, iSize);

		// Update internal state.
		m_iReadPos += iSize;

		return TRUE;
	}

	////////////////////
public:
	bool PushCtrl(short sCtrl)
	{
		int iCtrl = toCtrl(sCtrl);
		return doPush(&iCtrl, sizeof(int));
	}
	bool IsEmpty() const { return m_iReadPos == m_iRawDataSize; }
	/**
	 *		If it is a control value, we pop it; otherwise, keep
	 *	unchanged.
	 *
	 *	@return	`0` if fail.
	 */
	bool PopCtrlIfItIs(short *p)
	{
		bool bIsCtrl = FALSE;

		char *pRawData = m_rawData.get();
		int iPeek = *(int *)(pRawData + m_iReadPos);
		if (isCtrl(iPeek))
		{
			// Pop the control flag out.
			int iCtrl = 0;
			doPop(&iCtrl, sizeof(int));

			// Return value.
			bIsCtrl = TRUE;
			if (p != nullptr)
			{
				*p = static_cast<short>(iCtrl);
			}
		}

		return bIsCtrl;
	}
private:
	/**
	 *		Transform user value to control flag.
	 */
	int toCtrl(short s)
	{
		// Set the most signifant bit.
		return s | msc_iCtrlMask;
	}
	bool isCtrl(int i)
	{
		// Judge if the value is a control flag.
		return (i & (msc_iCtrlMask)) != 0;
	}
};

// Testing case:
//int main(/*int argc, char *argv[]*/)
//{
//	MySerializer msPush;
//	msPush.Push<int>(1);
//	msPush.Push<char>('a');
//	msPush.Push<bool>(true);
//	msPush.Push<std::string>("std::string");
//	msPush.Push<std::wstring>(L"std::string");
//	msPush.Push("12345", 6);
//
//	msPush.PushCtrl(1);
//
//	// --- Check memory here ---
//	int iSize = msPush.GetRawDataSize();
//	char *p = new char[iSize];
//	auto_ptr<char> memGuard(p);
//	memcpy(p, msPush.GetRawData(), iSize);
//	// --- Check memory here ---
//
//	MySerializer msPop;
//	msPop.SetRawData(p, iSize);
//	cout << msPop.Pop<int>() << endl;
//	cout << msPop.Pop<char>() << endl;
//	cout << msPop.Pop<bool>() << endl;
//	cout << msPop.Pop<std::string>() << endl;
//	wcout << msPop.Pop<std::wstring>() << endl;
//	char szStr[6] = {};
//	msPop.Pop(szStr, 6);
//	cout << szStr << endl;
//
//	short sCtrl = MySerializer::CTRL_DEFAULT;
//	msPop.PopCtrlIfItIs(&sCtrl);
//	cout << "ctrl: " << sCtrl << endl;
//
//	if (msPop.IsEmpty())
//	{
//		cout << "memory balanced" << endl;
//	}
//
//	return 0;
//}

}

#endif // W_SERIALIZE_H