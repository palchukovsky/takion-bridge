#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef U_EXPORTS
#define U_API __declspec(dllexport)
#else
#define U_API __declspec(dllimport)
#endif

#ifdef _DEBUG
#define VERIFY_QUOTES
#define VERIFY_LOCK 1000000
#ifdef VERIFY_LOCK
#define VERIFY_LOG_DELAY 800
#endif
#endif

#include <afxmt.h>

const char* const UtilsHeaderVersion = "1.0.1.207";

#ifdef __cplusplus
extern "C"
{
#endif

/*
typedef LONGLONG (*InterlockedExchange64FunctionPtr)(LONGLONG volatile *Target, LONGLONG Value);

InterlockedExchange64FunctionPtr WINAPI U_GetInterlockedExchange64FunctionPtr();
InterlockedExchange64FunctionPtr WINAPI U_GetInterlockedExchangeAdd64FunctionPtr();
*/
typedef LONGLONG (WINAPI *InterlockedCompareExchange64FunctionPtr)(LONGLONG volatile *Destination, LONGLONG Exchange, LONGLONG Comparand);
InterlockedCompareExchange64FunctionPtr WINAPI U_GetInterlockedCompareExchange64FunctionPtr();

void WINAPI U_SetThreadName(DWORD dwThreadID, const char* threadName);

void WINAPI U_AppendPrintableChar(std::string& str, char c, char del = '\0');
bool WINAPI U_AppendPrintableCharIfValid(std::string& str, char c, char del = '\0');
void WINAPI U_AppendUChar(std::string& str, unsigned char number, char del = '\0');
void WINAPI U_AppendUCharHex(std::string& str, unsigned char number, char del = '\0');
void WINAPI U_AppendUShort(std::string& str, unsigned short number, char del = '\0');
void WINAPI U_AppendUShortHex(std::string& str, unsigned short number, char del = '\0');
void WINAPI U_AppendBool(std::string& str, bool val, char del = '\0');
void WINAPI U_AppendUInt(std::string& str, unsigned int number, char del = '\0');
void WINAPI U_AppendUIntHex(std::string& str, unsigned int number, char del = '\0');
void WINAPI U_AppendUInt64(std::string& str, unsigned __int64 number, char del = '\0');
void WINAPI U_AppendUInt64Hex(std::string& str, unsigned __int64 number, char del = '\0');
void WINAPI U_AppendInt(std::string& str, int number, char del = '\0');
void WINAPI U_AppendInt64(std::string& str, __int64 number, char del = '\0');
void WINAPI U_AppendTwoDigits(std::string& str, unsigned int number, char del = '\0');
char* WINAPI U_AppendTwoDigitsToBuf(char* buf, unsigned int buflen, unsigned int number, char del = '\0');

void WINAPI U_AppendTimeTokens(std::string& str, unsigned int hour, unsigned int minute, unsigned int second, char del = '\0', bool oneDigitLeftmost = false);
void WINAPI U_AppendMillisecond(std::string& str, unsigned int millisecond, bool appendMillisecond = true, char del = '\0', bool oneDigitLeftmost = false);
void WINAPI U_AppendMinute(std::string& str, unsigned short minute, char del = '\0');

char* WINAPI U_DollarFractionToStr(unsigned int fraction, unsigned char decDigits, char* cursor, bool truncate = true, char del = '\0');
void WINAPI U_DollarFractionToStdStr(unsigned int fraction, unsigned char decDigits, std::string& str, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_CompactDollarFractionToStdStr(unsigned int fraction, unsigned char decDigits, std::string& str, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_MoneyFractionToStdStr(short fraction, unsigned char decDigits, std::string& str, char del, bool removeTrailingZeros = false);
/*
unsigned int U_ConvertUIntHexToDec(unsigned int value);
unsigned __int64 U_ConvertUInt64HexToDec(unsigned __int64 value);

void WINAPI U_ConvertUShortToStr(std::string& str, unsigned short number, char del = '\0');
void WINAPI U_ConvertUIntToStr(std::string& str, unsigned int number, char del = '\0');
void WINAPI U_ConvertUInt64ToStr(std::string& str, unsigned __int64 number, char del = '\0');

const char* WINAPI U_GetStrFromUShort(unsigned short number, char del = '\0');
const char* WINAPI U_GetStrFromUInt(unsigned int number, char del = '\0');
const char* WINAPI U_GetStrFromUInt64(unsigned __int64 number, char del = '\0');
const std::string& WINAPI U_GetStringFromUShort(unsigned short number, char del = '\0');
const std::string& WINAPI U_GetStringFromUInt(unsigned int number, char del = '\0');
const std::string& WINAPI U_GetStringFromUInt64(unsigned __int64 number, char del = '\0');
*/
void WINAPI U_VersionNumToStr(unsigned __int64 versionNum, std::string& versionStr);
unsigned __int64 WINAPI U_VersionStrToNum(const char* versionStr);
unsigned int WINAPI U_Version64To32(unsigned __int64 version64);
unsigned __int64 WINAPI U_Version32To64(unsigned int version32);
unsigned __int64 WINAPI U_GetVersionFromResourceFile(HINSTANCE hInstance);
unsigned __int64 WINAPI U_GetFileVersion(const char* fileName);
unsigned __int64 WINAPI U_GetVersionFromTokens(unsigned short t1, unsigned short t2, unsigned short t3, unsigned short t4);

inline unsigned __int64 U_GetVersion64(const unsigned __int64& v1, const unsigned __int64& v2, const unsigned __int64& v3, const unsigned __int64& v4)
{
	return (v1 << 48) | (v2 << 32) | (v3 << 16) | v4;
}


bool WINAPI U_SkipToDelimiter(const char*& str, char del);
bool WINAPI U_ReadStrTokenToMandatoryDel(std::string& token, const char*& str, char del, char terminator);
bool WINAPI U_ReadStrToken(std::string& token, const char*& str, char del);
bool WINAPI U_ReadStrTokenWith2Delimiters(std::string& token, const char*& str, char del, char otherDel = '\n');
bool WINAPI U_ReadBoolToken(const char*& str, char del, bool defaultValue = false);
int WINAPI U_ReadIntToken(const char*& str, char del, int defaultValue = 0);
unsigned int WINAPI U_ReadUIntToken(const char*& str, char del, unsigned int defaultValue = 0);
unsigned int WINAPI U_ReadUIntHexToken(const char*& str, char del, unsigned int defaultValue = 0);
unsigned int WINAPI U_ReadUIntTokenWithDigitCount(const char*& str, unsigned char& decDigits, char del, unsigned int defaultValue = 0);
unsigned __int64 WINAPI U_ReadUInt64Token(const char*& str, char del, unsigned __int64 defaultValue = 0);
unsigned __int64 WINAPI U_ReadUInt64HexToken(const char*& str, char del, unsigned __int64 defaultValue = 0);

unsigned int WINAPI U_ReadMillisecondFromStr(const char*& cursor, char del, unsigned int defaultValue = 0);
unsigned int WINAPI U_ReadSecondFromStr(const char*& cursor, char del, unsigned int defaultValue = 0);

unsigned short WINAPI U_ReadStrAsUShortToken(const char*& str, char del, unsigned short defaultValue = 0);
unsigned int WINAPI U_ReadStrAsUIntToken(const char*& str, char del, unsigned int defaultValue = 0);
unsigned __int64 WINAPI U_ReadStrAsUInt64Token(const char*& str, char del, unsigned __int64 defaultValue = 0);

char WINAPI U_ReadCharToken(const char*& str, char del, char defaultValue = 0);
unsigned char WINAPI U_ReadUCharToken(const char*& str, char del, unsigned char defaultValue = 0);
unsigned char WINAPI U_ReadUCharHexToken(const char*& str, char del, unsigned char defaultValue = 0);
unsigned short WINAPI U_ReadUShortToken(const char*& str, char del, unsigned short defaultValue = 0);
unsigned short WINAPI U_ReadUShortHexToken(const char*& str, char del, unsigned short defaultValue = 0);
unsigned short WINAPI U_ReadUShortTokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', unsigned short defaultValue = 0);
unsigned short WINAPI U_ReadUShortTokenWithDigitCount(const char*& str, unsigned char& decDigits, char del, unsigned short defaultValue = 0);
__int64 WINAPI U_ReadInt64Token(const char*& str, char del, __int64 defaultValue = 0);
__int64 WINAPI U_ReadInt64TokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', __int64 defaultValue = 0);
unsigned int WINAPI U_ReadUIntTokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', unsigned int defaultValue = 0);
unsigned __int64 WINAPI U_ReadUInt64TokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', unsigned __int64 defaultValue = 0);
int WINAPI U_ReadIntTokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', int defaultValue = 0);

char* WINAPI U_MarkSectionEnd(char* str, char del, bool& changed);
void WINAPI U_CopyAndPad(char* dst, unsigned int len, const char* src, char pad);
void WINAPI U_CopyPlusOneCharAndPad(char* dst, unsigned int len, const char* src, char additionalChar, char pad);
unsigned int WINAPI U_StringHash(const std::string& str);

bool WINAPI U_GetModulePath(HINSTANCE hInstance, char* path, unsigned int bufsize);
void WINAPI U_GetModuleFileName(HINSTANCE hInstance, std::string& fileName);
void WINAPI U_GetPlatformStr(std::string& platform);
void WINAPI U_AppendVersion(std::string& versionStr, unsigned __int64 versionNum);
void WINAPI U_InitializeInstanceInfo(HINSTANCE hInstance, std::string& filePathAndName, std::string& fileDescription, std::string& platform, unsigned __int64& versionNum, std::string& versionStr);
void* WINAPI U_GetVersionBlockHandle(HINSTANCE hInstance);
//bool WINAPI U_QueryVersionResourceValue(HINSTANCE hInstance, const char* name, std::string& value);
bool WINAPI U_QueryVersionResourceValue(const char* fileName, const char* name, std::string& value);

const char* WINAPI U_GetModuleVersionStr();
unsigned __int64 WINAPI U_GetModuleVersionNum();
const char* WINAPI U_GetHeaderVersion();
unsigned __int64 WINAPI U_GetHeaderVersionNum();
const char* WINAPI U_GetFilePathAndName();
const char* WINAPI U_GetPlatform();
const char* WINAPI U_GetFileDescription();
void WINAPI U_GetDllBuildDescription(std::string& buildStr);

void WINAPI U_CopyUppercase(char* dest, unsigned short length, const char*& source, char del = '\0', bool pad = false);

bool WINAPI U_IsWinSockInitialized();
const char*  WINAPI U_GetWinSockStatus();
unsigned int WINAPI U_GetIpAddressCount();
const unsigned int* WINAPI U_GetIpAddressesNum();
const char* WINAPI U_GetIpAddressesStr();
bool WINAPI U_UpdateIpAddresses();
bool WINAPI U_FormatErrorMessage(DWORD errorCode, std::string& errorMessage, const char* unknown = NULL);
const char* WINAPI U_GetHostName();
bool WINAPI U_UpdateHostName();
const char* WINAPI U_ShellExecute(HWND hwnd, const char* filePath);

//unsigned short WINAPI U_GetQuoteDelay(unsigned int millisecond);

const char* WINAPI U_GetValidStockChars();
const char* WINAPI U_GetValidStockFirstChars();
bool WINAPI U_IsStockSymbolValid(const char* symbol);
bool WINAPI U_IsStockCharValid(char c, bool first);

#ifndef TAKION_NO_OPTIONS
const char* WINAPI U_GetValidOptionFirstChars();
const char* WINAPI U_GetValidOptionChars();
bool WINAPI U_IsOptionSymbolValid(const char* symbol);
bool WINAPI U_IsOptionCharValid(char c, bool first);
#endif

const char* WINAPI U_GetValidIndexChars();
const char* WINAPI U_GetValidIndexFirstChars();
bool WINAPI U_IsIndexSymbolValid(const char* symbol);
bool WINAPI U_IsIndexCharValid(char c, bool first);

const char* WINAPI U_GetValidMmidChars();
const char* WINAPI U_GetValidMmidFirstChars();
bool WINAPI U_IsMmidSymbolValid(const char* mmid);
bool WINAPI U_IsMmidCharValid(char c, bool first);

const char* WINAPI U_GetValidBasketChars();
const char* WINAPI U_GetValidBasketFirstChars();
bool WINAPI U_IsBasketSymbolValid(const char* symbol);
bool WINAPI U_IsBasketCharValid(char c, bool first);

unsigned __int64 WINAPI U_StringToUInt64(const char* str);
unsigned int WINAPI U_StringToUInt(const char* str);
unsigned short WINAPI U_StringToUShort(const char* str);

unsigned __int64 WINAPI U_StringOfLengthToUInt64(const char* str, unsigned int length);

unsigned __int64 WINAPI U_StringToUInt64Term0(const char* str);
unsigned __int64 WINAPI U_StringOfLengthToUInt64Term0(const char* str, unsigned int length);

void WINAPI U_GetRectInCenterRect(const RECT& center, RECT& rect);
void WINAPI U_GetRectInsideRect(const RECT& outer, RECT& inner);
void WINAPI U_EnumFontFamilies(HDC hdc, BYTE charSet, std::map<std::string, DWORD>& fontMap);
void WINAPI U_EnumFontSizes(HDC hdc, const char* fontName, BYTE charSet, std::set<unsigned int>& sizeSet);
const unsigned int* WINAPI U_GetTrueTypeFontSizes();

bool WINAPI U_GetPrivateProfileSection(std::map<std::string, std::string>& result, const char* sectionName, const char* filePathAndName, unsigned int guessSize = 1024, unsigned int maxSize = 0x10000);
bool WINAPI U_GetPrivateProfileString(std::string& result, const char* sectionName, const char* entryName, const char* defaultValue, const char* filePathAndName, unsigned int guessSize = 1024, unsigned int maxSize = 0x10000);
bool WINAPI U_ConvertIpToString(unsigned int ip, char* str, unsigned int length);
void WINAPI U_ConvertIpToStdString(unsigned int ip, std::string& str);
unsigned int WINAPI U_ConvertStringToIp(const char* str);
unsigned int WINAPI U_ConvertStringToIpAndReturnCursor(const char*& cursor, char delimiter = '\0');
char* WINAPI U_ConvertIpTokenString(char* cursor, unsigned char ipToken);
unsigned __int64 WINAPI U_CalculateIpPort(unsigned int ip, unsigned short port);

#ifdef __cplusplus
}
#endif

class TakionIterator
{
public:
	virtual ~TakionIterator(){}
	virtual void Reset() = 0;
	virtual unsigned int GetCount() const = 0;
	virtual void Skip(unsigned int count) = 0;
protected:
	TakionIterator(){}
};

class RingVectorBaseItem
{
public:
	virtual ~RingVectorBaseItem(){}
protected:
	RingVectorBaseItem(){}
};

class U_API TakionRingVectorBase
{
public:
	virtual ~TakionRingVectorBase(){}

	virtual void push_back(RingVectorBaseItem* const& val) = 0;
	virtual void push_front(RingVectorBaseItem* const& val) = 0;
	virtual void pop_back() = 0;
	virtual void pop_front() = 0;
	virtual void insert(size_t at, RingVectorBaseItem* const& val) = 0;

	virtual const RingVectorBaseItem* at(size_t pos) const = 0;
	virtual RingVectorBaseItem* at(size_t pos) = 0;
	const RingVectorBaseItem* operator[](size_t pos) const{return at(pos);}
	RingVectorBaseItem* operator[](size_t pos){return at(pos);}
	virtual const RingVectorBaseItem* fromBack(size_t pos) const = 0;
	virtual RingVectorBaseItem* fromBack(size_t pos) = 0;

	virtual const RingVectorBaseItem* front() const = 0;
	virtual RingVectorBaseItem* front() = 0;
	virtual const RingVectorBaseItem* back() const = 0;
	virtual RingVectorBaseItem* back() = 0;

	virtual void ReserveAdditional(size_t size) = 0;
	virtual void reserve(size_t capacity) = 0;
	virtual size_t capacity() const = 0;
	virtual size_t size() const = 0;
protected:
	TakionRingVectorBase(){}
};

class U_API TakionLockMultithread
{
public:
	TakionLockMultithread():m_threadId(0),m_count(0){}

	bool LockInquiry() const
	{
		LONG threadId = GetCurrentThreadId();
		LONG prior;
		while(true)
		{
			InterlockedIncrement(&m_count);
			prior = InterlockedCompareExchange(&m_threadId, threadId, 0);
			if(!prior || prior == threadId)
			{
				return true;
			}
			else if(!UnlockInquiry())
			{
				return false;
			}
		}
	}

	void LockInquiryWait() const
	{
		LONG threadId = GetCurrentThreadId();
		LONG prior;
		while(true)
		{
			InterlockedIncrement(&m_count);
			prior = InterlockedCompareExchange(&m_threadId, threadId, 0);
			if(!prior || prior == threadId)
			{
				break;
			}
			else if(!UnlockInquiry())
			{
				Sleep(0);
			}
		}
	}

	bool LockModification() const
	{
		LockInquiryWait();
		return true;
	}

	bool UnlockInquiry() const
	{
		if(!InterlockedDecrement(&m_count))
		{
			InterlockedExchange(&m_threadId, 0);
			return true;
		}
		return false;
	}

	bool UnlockModification() const
	{
		return UnlockInquiry();
	}

protected:
	mutable volatile LONG m_threadId;
	mutable volatile LONG m_count;
};

class U_API TakionLock
{
public:
	static const LONG modificationBit = 1 << 30;
	static const LONG modificationBitMultithread = 1 << 20;
	TakionLock():m_lock(0){}//,m_lockInquiryCount(0){}//,m_lockWaitCount(0){}//,m_lockModificationThread(NULL){}
#ifdef VERIFY_LOCK
	bool LockModification() const;
	void LockInquiryWait() const;//Use for inquiry
#else
	bool LockModification() const//use for making changes in the state of an object (like Security) //modifications can be done only in one thread //returns true if you need to unlock after modifications are done
	{
//		unsigned int val = InterlockedExchangeAdd(&m_lock, 0);
		if(m_lock & modificationBit)
		{
			return false;
		}
		if(InterlockedExchangeAdd(&m_lock, modificationBit) == modificationBit)return true;
		while(InterlockedExchangeAdd(&m_lock, 0) != modificationBit)Sleep(0);
		return true;
	}
	void LockInquiryWait() const//Use for inquiry
	{
//		while((m_lock & modificationBit) || !LockInquiry())Sleep(0);
		unsigned int val;
		while(true)
		{
			val = InterlockedIncrement(&m_lock);
			if(val & modificationBit)
			{
				if((val & ~modificationBit) == 1)
				{
					InterlockedDecrement(&m_lock);
					Sleep(0);
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}
	}
#endif
/*
	void LockModificationMultithread() const//use for making changes in the state of an object (like Security) //modifications can be done in multiple threads
	{
//		unsigned int val = InterlockedExchangeAdd(&m_lock, 0);
		while(true)
		{
			if(InterlockedExchangeAdd(&m_lock, modificationBitMultithread) >= modificationBitMultithread)
			{
				InterlockedExchangeAdd(&m_lock, -modificationBitMultithread);
				Sleep(0);
			}
			else
			{
				break;
			}
		}

		while(InterlockedCompareExchange(&m_lock, modificationBit, modificationBitMultithread) != modificationBitMultithread)Sleep(0);

	}
*/
	void UnlockModification() const
	{
//		InterlockedExchangeAdd(&m_lock, -(LONG)modificationBit);
		InterlockedExchangeAdd(&m_lock, -modificationBit);
	}

	bool LockInquiry() const
	{
		unsigned int val = InterlockedIncrement(&m_lock);
		if(val & modificationBit)
		{
			InterlockedDecrement(&m_lock);
			return false;
		}
		return true;
	}
	void UnlockInquiry() const
	{
		InterlockedDecrement(&m_lock);
	}
protected:
	mutable volatile LONG m_lock;
};

class U_API TakionLockReadWrite
{
public:
	TakionLockReadWrite():m_lock(0){}
	void LockWait() const
	{
		while(true)
		{
			if(InterlockedExchange(&m_lock, 1))
			{
				Sleep(0);
			}
			else
			{
				return;
			}
		}
	}

	void Unlock() const
	{
		InterlockedExchange(&m_lock, 0);
	}

	bool Lock() const
	{
		return !InterlockedExchange(&m_lock, 1);
	}
protected:
	mutable volatile LONG m_lock;
};

//IniValue hierarchy

class U_API IniValue
{
public:
	virtual ~IniValue(){}
	bool ExtractValue(){m_valid = DoExtractValue(); return m_valid;}
	virtual bool isModified() const{return true;}
	virtual bool isDefault() const{return false;}
	bool SaveValue() const{return !isModified() || (m_eraseIfDefault && isDefault() ? DoEraseValue() : DoSaveValue());}
	bool isValid() const{return m_valid;}
	virtual void UpdateInitialValue(){}
	void SaveValueAndUpdateInitialValue(){SaveValue(); UpdateInitialValue();}
	void SetSection(const char* section){m_section = section;}
	void SetEntry(const char* entry){m_entry = entry;}
	void SetFile(const char* file){m_file = file;}
	const char* GetSection() const{return m_section;}
	const char* GetEntry() const{return m_entry;}
	const char* GetFile() const{return m_file;}
protected:
	IniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault):
		m_section(section),
		m_entry(entry),
		m_file(file),
		m_eraseIfDefault(eraseIfDefault),
		m_valid(false)
	{}
	virtual bool DoSaveValue() const{return true;}
	virtual bool DoEraseValue() const;
	virtual bool DoExtractValue(){return true;}
	const char* m_section;
	const char* m_entry;
	const char* m_file;
	bool m_eraseIfDefault;
	bool m_valid;
};

template<class V>
class TypeIniValue : public IniValue
{
public:
	typedef V ValueType;
	void SetValue(const V& value){m_value = value;}
	const V& GetValue() const{return m_value;}
	virtual bool isModified() const{return !(m_value == m_initialValue);}
	virtual bool isDefault() const{return m_value == m_defaultValue;}
	virtual void UpdateInitialValue(){m_initialValue = m_value;}
protected:
	TypeIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const V& value):
		IniValue(section, entry, file, eraseIfDefault),
		m_value(value),
		m_initialValue(value),
		m_defaultValue(value)
	{}
	V m_value;
	V m_initialValue;
	V m_defaultValue;
};

class U_API StringIniValue : public TypeIniValue<std::string>
{
public:
	StringIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const std::string& value, unsigned int guessSize = 1024, unsigned int maxSize = 0x10000):
		TypeIniValue(section, entry, file, eraseIfDefault, value),
		m_guessSize(guessSize < 2 ? 2 : guessSize),
		m_maxSize(maxSize < m_guessSize ? m_guessSize : maxSize)
	{}
//	virtual ~StringIniValue(){SaveValue();}
protected:
	virtual bool DoExtractValue();
	virtual bool DoSaveValue() const;
	unsigned int m_guessSize;
	unsigned int m_maxSize;
};

class U_API IntIniValue : public TypeIniValue<int>
{
public:
	IntIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const int& value):TypeIniValue(section, entry, file, eraseIfDefault, value){}
//	virtual ~IntIniValue(){SaveValue();}
protected:
	virtual bool DoExtractValue();
	virtual bool DoSaveValue() const;
};

class U_API UIntIniValue : public TypeIniValue<unsigned int>
{
public:
	UIntIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const unsigned int& value):TypeIniValue(section, entry, file, eraseIfDefault, value){}
//	virtual ~UIntIniValue(){SaveValue();}
protected:
	virtual bool DoExtractValue();
	virtual bool DoSaveValue() const;
};

class U_API UIntHexIniValue : public UIntIniValue
{
public:
	UIntHexIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const unsigned int& value):UIntIniValue(section, entry, file, eraseIfDefault, value){}
//	virtual ~UIntHexIniValue(){SaveValue();}
protected:
	virtual bool DoExtractValue();
	virtual bool DoSaveValue() const;
};

class U_API IpIniValue : public UIntIniValue
{
public:
	IpIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const unsigned int& value):UIntIniValue(section, entry, file, eraseIfDefault, value){}
//	virtual ~IpIniValue(){SaveValue();}
protected:
	virtual bool DoExtractValue();
	virtual bool DoSaveValue() const;
};

class U_API BoolIniValue : public TypeIniValue<bool>
{
public:
	BoolIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const bool& value):TypeIniValue(section, entry, file, eraseIfDefault, value){}
//	virtual ~BoolIniValue(){SaveValue();}
protected:
	virtual bool DoExtractValue();
	virtual bool DoSaveValue() const;
};

class U_API MapIniValue : public TypeIniValue<std::map<std::string, std::string> >
{
public:
	typedef std::map<std::string, std::string> StringMap;
	MapIniValue(const char* section, const char* file, unsigned int guessSize = 1024, unsigned int maxSize = 0x10000):
		TypeIniValue(section, "", file, false, std::map<std::string, std::string>()),
		m_guessSize(guessSize < 3 ? 3 : guessSize),
		m_maxSize(maxSize < m_guessSize ? m_guessSize : maxSize)
	{}
//	virtual ~BoolIniValue(){SaveValue();}
	bool AddValue(const char* key, const char* value);
	bool RemoveValue(const char* key){return m_value.erase(std::string(key)) > 0;}
	bool RemoveValue(const std::string& key){return m_value.erase(key) > 0;}
	bool ClearValues(){if(m_value.empty())return false; m_value.clear(); return true;}
protected:
	virtual bool DoExtractValue();
	virtual bool DoSaveValue() const;
	unsigned int m_guessSize;
	unsigned int m_maxSize;
};

class ThermographVectorUShort;

class U_API Thermograph
{
public:
	Thermograph(unsigned short capacity);
	~Thermograph();
	void AddValue(unsigned short value);
	void AddValue(unsigned short value, unsigned short count);
	void clear();
	unsigned short capacity() const;
	unsigned short size() const;
	const unsigned short& operator[](unsigned short pos) const;
	unsigned short GetFirstValue() const;
	void ResetIterator() const;
	void ResetIterator(unsigned short skip) const;
	unsigned short GetNextValue() const;
	unsigned int GetSum() const;
protected:
	ThermographVectorUShort* m_vector;
};

template<class T>
class PointLocator
{
public:
	PointLocator(T start):
		m_start(start),
		m_end(start)
	{}
	PointLocator(T start, T end):
		m_start(start),
		m_end(end)
	{}
	inline const T& GetStart() const{return m_start;}
	inline const T& GetEnd() const{return m_end;}
	inline void SetStartOnly(const T& start){m_start = start;}
	inline void SetEndOnly(const T& end){m_end = end;}
	inline void SetStartEnd(const T& start, T end){m_start = start;m_end = end;}
	inline T GetSize() const{return m_end - m_start;}
	inline void SetSize(const T& size){m_end = m_start + size;}

	inline void SetStart(const T& start)
	{
		if(m_start != start)
		{
			if(m_start < start)
			{
				m_end += (start - m_start);
			}
			else
			{
				m_end -= (m_start - start);
			}
			m_start = start;
		}
	}
	inline void Increment(){++m_start; ++m_end;}
	inline void Decrement(){--m_start; --m_end;}
	inline void Increment(const T& diff){m_start += diff; m_end += diff;}
	inline void Decrement(const T& diff){m_start -= diff; m_end -= diff;}
	inline void IncrementEnd(){++m_end;}
	inline void DecrementEnd(){--m_end;}
	inline void IncrementEnd(const T& diff){m_end += diff;}
	inline void DecrementEnd(const T& diff){m_end -= diff;}
	inline void IncrementStart(){++m_start;}
	inline void DecrementStart(){--m_start;}
	inline void IncrementStart(const T& diff){m_start += diff;}
	inline void DecrementStart(const T& diff){m_start -= diff;}
protected:
	T m_start;
	T m_end;
};
/*
template<class C>//unsigned
struct lessNumberAsString : public std::binary_function<C, C, bool>
{	// functor for operator<
	bool operator()(const C& p1, const C& p2) const
	{	// apply operator< to operands
		const unsigned char* c1 = (const unsigned char*)&p1;
		const unsigned char* c2 = (const unsigned char*)&p2;
		unsigned char a1 = *c1;
		unsigned char a2 = *c2;
		for(unsigned char i = sizeof(C); i; --i, a1 = *++c1, a2 = *++c2)
		{
			if(a1 < a2)
			{
				return true;
			}
			if(a1 > a2 || !a1)
			{
				return false;
			}
		}
		return false;
	}
};
*/
template<class T>
struct lessPointLocator : public std::binary_function<PointLocator<T>, PointLocator<T>, bool>
{	// functor for operator<
	bool operator()(const PointLocator<T>& ra1, const PointLocator<T>& ra2) const
	{	// apply operator< to operands
		return ra1.GetEnd() < ra2.GetStart() || ra1.GetStart() < ra2.GetStart() && ra1.GetEnd() == ra2.GetStart();
	}
};

typedef PointLocator<size_t> PointLocatorSize;
typedef PointLocator<int> PointLocatorInt;

#ifdef _DEBUG
#include <assert.h>
//#define CHECK_CHAIN
#endif

template<class T, unsigned char N>
class TakionId
{
public:
	TakionId(const char* id)
	{
		char* dst = (char*)m_id;
		unsigned char i = 0;
		unsigned char j;
		for(; i < N; ++i)
		{
			if(!*id)
			{
				break;
			}
			for(j = 0; *id && j < sizeof(T); ++j, ++dst, ++id)
			{
				*dst = *id;
			}
			if(j < sizeof(T))
			{
				if(sizeof(T) >= sizeof(unsigned short))
				{
					if(j & 1)
					{
						*dst = 0;
						++dst;
						++j;
					}
					if(sizeof(T) >= sizeof(unsigned int))
					{
						j >>= 1;
						if(j & 1)
						{
							*(unsigned short*)dst = 0;
							dst += sizeof(unsigned short);
							++j;
						}
					}
					if(sizeof(T) >= sizeof(unsigned __int64))
					{
						j >>= 1;
						if(j & 1)
						{
							*(unsigned int*)dst = 0;
//							dst += sizeof(unsigned int);
//							++j;
						}
					}
				}
				++i;
				break;
			}
		}
		if(i < N)
		{
			T* cursor = m_id + i;
			for(; i < N; ++i)
			{
				*cursor = 0;
			}
		}
	}
	TakionId(const T* t)
	{
		T* cursor = m_id;
		for(unsigned char i = 0; i < N; ++i, ++cursor, ++t)
		{
			*cursor = *t;
		}
	}
	TakionId(const T* t, unsigned char length)
	{
		if(length > N)
		{
			length = N;
		}
		T* cursor = m_id;
		unsigned char i = 0;
		for(; i < length; ++i, ++cursor, ++t)
		{
			*cursor = *t;
		}
//		memcpy(m_id, t, sizeof(T) * length);
		if(i < N)
		{
			for(; i < N; ++i, ++cursor)
			{
				*cursor = 0;
			}
//			memset(m_id + length, 0, sizeof(T) * (N - length));
		}
	}
	const char* GetId() const{return (const char*)m_id;}
	const T& GetToken(unsigned char ordinal) const{return m_id[ordinal];}
	operator size_t() const{return *m_id;}
	bool operator<(const TakionId& other) const
	{
		const T* cursor = m_id;
		const T* cursorOther = other. m_id;
		for(unsigned char i = 0; i < N; ++i, ++cursor, ++cursorOther)
		{
			if(*cursor < *cursorOther)
			{
				return true;
			}
			if(*cursor > *cursorOther)
			{
				return false;
			}
		}
		return false;
	}
	bool operator==(const TakionId& other) const
	{
//		return m_first == other.m_first && m_second == other.m_second;
		const T* cursor = m_id;
		const T* cursorOther = other. m_id;
		for(unsigned char i = 0; i < N; ++i, ++cursor, ++cursorOther)
		{
			if(*cursor != *cursorOther)
			{
				return false;
			}
		}
		return true;
	}
	bool operator!=(const TakionId& other) const{return !operator==(other);}
protected:
	T m_id[N];
};

template<class T, unsigned short N>//unsigned short, int, __int64, size_t
class StrAsNumberArray
{
public:
	typedef T NumberType;
	StrAsNumberArray()//:m_length(0)
	{
		Initialize();
	}
	StrAsNumberArray(const char* cursor):m_wholeNumberCountPlusOneFraction(N)
	{
		DoSetString(cursor);
//		ClearTail();
	}
	StrAsNumberArray(const char*& cursor, const char& del):m_wholeNumberCountPlusOneFraction(N)
	{
		DoSetStringWithDelimiter(cursor, del);
//		ClearTail();
	}
/*
	StrAsNumberArray(const char* cursor, unsigned short length):m_wholeNumberCountPlusOneFraction(N)//length is how many chars max you want to get from cursor
	{
		DoSetString(cursor, length);
//		ClearTail();
	}
*/
	StrAsNumberArray(const char*& cursor, unsigned short length, const char& del):m_wholeNumberCountPlusOneFraction(N)//length is how many chars max you want to get from cursor
	{
		DoSetStringWithDelimiter(cursor, length, del);
//		ClearTail();
	}
	StrAsNumberArray(const std::string& str):m_wholeNumberCountPlusOneFraction(N)
	{
		DoSetString((const unsigned short&)str.length(), str.c_str());
	}
	StrAsNumberArray(const unsigned short& exactLength, const char* cursor):m_wholeNumberCountPlusOneFraction(N)
	{
		DoSetString(exactLength, cursor);
//		ClearTail();
	}
	StrAsNumberArray(const StrAsNumberArray& other):
		m_length(other.m_length),
		m_wholeNumberCount(other.m_wholeNumberCount),
		m_wholeNumberCountPlusOneFraction(other.m_wholeNumberCountPlusOneFraction)
//		m_wholeLength(other.m_wholeLength)
	{
		CopyArray(other.m_numberArray);
	}
	const StrAsNumberArray& operator=(const StrAsNumberArray& other)
	{
		CopyNormalizedArray(other);
		m_length = other.m_length;
		m_wholeNumberCount = other.m_wholeNumberCount;
		m_wholeNumberCountPlusOneFraction = other.m_wholeNumberCountPlusOneFraction;
//		m_wholeLength = other.m_wholeLength;
		return *this;
	}
	void SetString(const char* cursor)
	{
		DoSetString(cursor);
//		ClearNormalizedTail();
	}
	void SetStringWithDelimiter(const char*& cursor, const char& del)
	{
		DoSetStringWithDelimiter(cursor, del);
//		ClearNormalizedTail();
	}
	void AddString(const char* cursor)
	{
		DoAddString(cursor);
	}
	void AddString(const char*& cursor, const char& del)
	{
		DoAddString(cursor, del);
	}
	void SetString(const char* cursor, unsigned short length)
	{
		DoSetString(cursor, length);
//		ClearNormalizedTail();
	}
	void SetString(const char*& cursor, unsigned short length, const char& del)
	{
		DoSetStringWithDelimiter(cursor, length, del);
//		ClearNormalizedTail();
	}
	void SetString(const std::string& str)
	{
		DoSetString((const unsigned short&)str.length(), str.c_str());
	}
	void SetString(const unsigned short& exactLength, const char* cursor)//when the exact length of string is known
	{
		DoSetString(exactLength, cursor);
//		ClearNormalizedTail();
	}
	unsigned short GetLength() const{return m_length;}
	bool isEmpty() const{return !m_length;}
	bool operator==(const StrAsNumberArray& other) const{return m_length == other.m_length && isArrayOfLengthEqual(other.m_numberArray);}
	bool operator!=(const StrAsNumberArray& other) const{return !operator==(other);}
	short Compare(const StrAsNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray);}
	bool operator<(const StrAsNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray) < 0;}
	bool operator>(const StrAsNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray) > 0;}
	bool operator<=(const StrAsNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray) <= 0;}
	bool operator>=(const StrAsNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray) >= 0;}
	operator size_t() const{return (size_t)*m_numberArray;}
	operator int() const{return (int)*m_numberArray;}
	operator long() const{return (long)*m_numberArray;}
	void Initialize()
	{
		m_length = m_wholeNumberCount = m_wholeNumberCountPlusOneFraction = 0;//m_wholeLength = 0;
		NumberType* cursor = m_numberArray;
		for(unsigned short i = 0; i < N; ++i, ++cursor)
		{
			*cursor = 0;
		}
	}
	void Clear()
	{
		m_length = m_wholeNumberCount = 0;//m_wholeLength = 0;
		NumberType* cursor = m_numberArray;
		for(; m_wholeNumberCountPlusOneFraction; --m_wholeNumberCountPlusOneFraction, ++cursor)
		{
			*cursor = 0;
		}
	}
	const char* GetString() const{return (const char*)m_numberArray;}
protected:
	NumberType m_numberArray[N];
	unsigned short m_length;
	unsigned short m_wholeNumberCount;
	unsigned short m_wholeNumberCountPlusOneFraction;
//	unsigned short m_wholeLength;
	void DoSetString(const unsigned short& exactLength, const char* cursor)
	{
		const NumberType* numberCursorOther = (const NumberType*)cursor;

		m_wholeNumberCount = exactLength / sizeof(NumberType);
		unsigned short wholeNumberCountPlusOneFraction;
		unsigned short fraction = 0;
		char* fractionDst = NULL;
		if(m_wholeNumberCount > N)
		{
			m_wholeNumberCount = wholeNumberCountPlusOneFraction = N;
			cursor = NULL;
//			m_length = m_wholeLength = N * sizeof(NumberType);
			m_length = N * sizeof(NumberType);
		}
		else if(m_wholeNumberCount < N)
		{
			wholeNumberCountPlusOneFraction = m_wholeNumberCount;
//			m_wholeLength = m_wholeNumberCount * sizeof(NumberType);
//			if(m_wholeLength == exactLength)
			unsigned short wholeLength = m_wholeNumberCount * sizeof(NumberType);
			if(wholeLength == exactLength)
			{
				cursor = NULL;
			}
			else
			{
				++wholeNumberCountPlusOneFraction;
				fraction = exactLength - wholeLength;
				cursor += wholeLength;
				fractionDst = (char*)m_numberArray + wholeLength;
			}
			m_length = exactLength;
		}
		else
		{
			wholeNumberCountPlusOneFraction = m_wholeNumberCount;
//			m_wholeLength = m_wholeNumberCount * sizeof(NumberType);
			cursor = NULL;
			m_length = exactLength;
		}

		if(m_wholeNumberCountPlusOneFraction > m_wholeNumberCount)//m_wholeNumberCount already changed, m_wholeNumberCountPlusOneFraction is old
		{
			NumberType* nc = m_numberArray + m_wholeNumberCount;
			for(unsigned short i = m_wholeNumberCount; i < m_wholeNumberCountPlusOneFraction; ++i, ++nc)
			{
				*nc = 0;
			}
		}
		m_wholeNumberCountPlusOneFraction = wholeNumberCountPlusOneFraction;

		NumberType* numberCursor = m_numberArray;

		for(unsigned short wholeNumberCount = m_wholeNumberCount; wholeNumberCount; --wholeNumberCount, ++numberCursor, ++numberCursorOther)
		{
			*numberCursor = *numberCursorOther;
		}
		if(cursor)
		{
			for(; fraction; --fraction, ++cursor, ++fractionDst)
			{
				*fractionDst = *cursor;
			}
		}
	}
	void DoSetString(const char* cursor)
	{
		m_length = 0;
		char* dst = (char*)m_numberArray;
		char c = *cursor;
		for(unsigned short length = N * sizeof(NumberType); c && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		UpdateWholeNumbers();
	}
	void DoSetStringWithDelimiter(const char*& cursor, const char& del)
	{
		m_length = 0;
		char* dst = (char*)m_numberArray;
		char c = *cursor;
		for(unsigned short length = N * sizeof(NumberType); c && c != del && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		if(del == c && del)++cursor;

		UpdateWholeNumbers();
	}
	void DoAddString(const char* cursor)
	{
		char* dst = (char*)m_numberArray + m_length;
		char c = *cursor;
		for(unsigned short length = N * sizeof(NumberType) - m_length; c && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		UpdateWholeNumbers();
	}
	void DoAddString(const char*& cursor, const char& del)
	{
		char* dst = (char*)m_numberArray + m_length;
		char c = *cursor;
		for(unsigned short length = N * sizeof(NumberType) - m_length; c && c != del && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		if(del == c && del)++cursor;
		UpdateWholeNumbers();
	}
	void DoSetString(const char* cursor, unsigned short length)//length is how many chars max you want to get from cursor
	{
		if(length > N * sizeof(NumberType))
		{
			length = N * sizeof(NumberType);
		}
		m_length = 0;
		char* dst = (char*)m_numberArray;
		char c = *cursor;
		for(; c && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		UpdateWholeNumbers();
	}
	void DoSetStringWithDelimiter(const char*& cursor, unsigned short length, const char& del)//length is how many chars max you want to get from cursor
	{
		if(length > N * sizeof(NumberType))
		{
			length = N * sizeof(NumberType);
		}
		m_length = 0;
		char* dst = (char*)m_numberArray;
		char c = *cursor;
		for(; c && c != del && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		if(del == c && del)++cursor;
		UpdateWholeNumbers();
	}
	void UpdateWholeNumbers()
	{
		unsigned short wholeNumberCountPlusOneFraction;
		m_wholeNumberCount = wholeNumberCountPlusOneFraction = m_length / sizeof(NumberType);
//		m_wholeLength = m_wholeNumberCount * sizeof(NumberType);
		unsigned short wholeLength = m_wholeNumberCount * sizeof(NumberType);
//		if(m_wholeLength != m_length)
		if(wholeLength != m_length)
		{
			++wholeNumberCountPlusOneFraction;
//			unsigned short count = m_wholeLength + sizeof(NumberType) - m_length;
			unsigned short count = wholeLength + sizeof(NumberType) - m_length;
			for(char* cursor = (char*)m_numberArray + m_length; count; --count, ++cursor)
			{
				*cursor = '\0';
			}
		}

		if(m_wholeNumberCountPlusOneFraction > wholeNumberCountPlusOneFraction)
		{
			NumberType* nc = m_numberArray + wholeNumberCountPlusOneFraction;
			for(unsigned short i = wholeNumberCountPlusOneFraction; i < m_wholeNumberCountPlusOneFraction; ++i, ++nc)
			{
				*nc = 0;
			}
		}

		m_wholeNumberCountPlusOneFraction = wholeNumberCountPlusOneFraction;
	}
/*
	void ClearTail()
	{
		if(m_wholeNumberCount < N)
		{
			if(m_length != m_wholeLength)
			{
				unsigned short fractionLength = m_wholeLength + sizeof(NumberType) - m_length;
				for(char* cursor = (char*)m_numberArray + m_length; fractionLength; --fractionLength, ++cursor)
				{
					*cursor = '\0';
				}
			}
			if(m_wholeNumberCountPlusOneFraction < N)
			{
				unsigned short wholeNumberCount = m_wholeNumberCountPlusOneFraction;
				for(NumberType* numberCursor = m_numberArray + wholeNumberCount; wholeNumberCount < N; ++wholeNumberCount, ++numberCursor)
				{
					*numberCursor = 0;
				}
			}
		}
	}
*/
/*
	void ClearNormalizedTail()
	{
//		if(m_length < N * sizeof(NumberType))
		if(m_wholeNumberCount < N)
		{
			if(m_length != m_wholeLength)
			{
				char* cursor = (char*)m_numberArray + m_length;
				for(unsigned short fractionLength = m_wholeLength + sizeof(NumberType) - m_length; fractionLength; --fractionLength, ++cursor)
				{
					*cursor = '\0';
				}
			}
			if(m_wholeNumberCountPlusOneFraction < N)
			{
				unsigned short wholeNumberCount = m_wholeNumberCountPlusOneFraction;
				for(NumberType* numberCursor = m_numberArray + wholeNumberCount; wholeNumberCount < N; ++wholeNumberCount, ++numberCursor)
				{
					if(*numberCursor)
					{
						*numberCursor = 0;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
*/
private:
	void CopyArray(const NumberType* cursorOther)
	{
		NumberType* cursor = m_numberArray;
		for(unsigned short i = 0; i < N; ++i, ++cursor, ++cursorOther)
		{
			*cursor = *cursorOther;
		}
	}
	void CopyNormalizedArray(const StrAsNumberArray& other)
	{
		NumberType* cursor = m_numberArray;
		const NumberType* cursorOther = other.m_numberArray;
		unsigned short count = other.m_wholeNumberCountPlusOneFraction;
		unsigned short i = 0;
		for(; i < count; ++i, ++cursor, ++cursorOther)
		{
			if(*cursorOther)
			{
				*cursor = *cursorOther;
			}
		}
		for(; i < m_wholeNumberCountPlusOneFraction; ++i, ++cursor)
		{
			*cursor = 0;
		}
	}
	bool isArrayOfLengthEqual(const NumberType* cursorOther) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
		for(unsigned short length = N; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor != *cursorOther)
			{
				return false;
			}
			if(!*cursor)
			{
				break;
			}
		}
		return true;
	}
	short CompareArrayOfLength(const NumberType* cursorOther) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
		for(unsigned short length = N; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor < *cursorOther)
			{
				return -1;
			}
			else if(*cursor > *cursorOther)
			{
				return 1;
			}
			if(!*cursor)
			{
				break;
			}
		}
		return 0;
	}
};

template<class T>//unsigned short, int, __int64, size_t
class StrAsVarNumberArray
{
public:
	typedef T NumberType;
	StrAsVarNumberArray():m_numberArray(NULL), m_arraySize(0)//, m_length(0)
	{
		DoSetString("", 0);
//		ClearTail();
	}
	StrAsVarNumberArray(const char* cursor):m_numberArray(NULL), m_arraySize(0)
	{
		DoSetString(cursor);
//		ClearTail();
	}

	StrAsVarNumberArray(const char*& cursor, const char& del):m_numberArray(NULL), m_arraySize(0)
	{
		DoSetStringWithDelimiter(cursor, del);
//		ClearTail();
	}
/*
	StrAsVarNumberArray(const char* cursor, const unsigned short& length):m_numberArray(NULL), m_arraySize(0)//length is how many chars max you want to get from cursor
	{
		DoSetString(cursor, length);
	}
*/
	StrAsVarNumberArray(const char*& cursor, const unsigned short& length, const char& del):m_numberArray(NULL), m_arraySize(0)//length is how many chars max you want to get from cursor
	{
		DoSetStringWithDelimiter(cursor, length, del);
//		ClearTail();
	}
	StrAsVarNumberArray(const std::string& str):m_numberArray(NULL), m_arraySize(0)
	{
		DoSetString((const unsigned short&)str.length(), str.c_str());
	}
	StrAsVarNumberArray(const unsigned short& exactLength, const char* cursor):m_numberArray(NULL), m_arraySize(0)
	{
		DoSetString(exactLength, cursor);
//		ClearTail();
	}
	StrAsVarNumberArray(const StrAsVarNumberArray& other):
		m_numberArray(new NumberType[other.m_arraySize]),
		m_arraySize(other.m_arraySize),
		m_length(other.m_length),
		m_wholeNumberCount(other.m_wholeNumberCount),
		m_wholeNumberCountPlusOneFraction(other.m_wholeNumberCountPlusOneFraction)
//		m_wholeLength(other.m_wholeLength)
	{
		CopyArray(other.m_numberArray);
	}
	~StrAsVarNumberArray()
	{
		if(m_numberArray)delete[] m_numberArray;
	}
	const StrAsVarNumberArray& operator=(const StrAsVarNumberArray& other)
	{
		if(m_arraySize != other.m_arraySize)
		{
			if(m_numberArray)delete[] m_numberArray;
			m_arraySize = other.m_arraySize;
			m_numberArray = new NumberType[m_arraySize];
		}
		m_length = other.m_length;
		m_wholeNumberCount = other.m_wholeNumberCount;
		m_wholeNumberCountPlusOneFraction = other.m_wholeNumberCountPlusOneFraction;
//		m_wholeLength = other.m_wholeLength;
//		CopyNormalizedArray(other.m_numberArray);
		CopyArray(other.m_numberArray);
		return *this;
	}
	void SetString(const char* cursor)
	{
		DoSetString(cursor);
//		ClearTail();
	}
	void SetString(const char* cursor, const unsigned short& length)
	{
		DoSetString(cursor, length);
//		ClearTail();
	}
	void SetString(const std::string& str)
	{
		DoSetString((const unsigned short&)str.length(), str.c_str());
	}
	void SetString(const unsigned short& exactLength, const char* cursor)//when the exact length of string is known
	{
		DoSetString(exactLength, cursor);
//		ClearTail();
	}
	unsigned short GetLength() const{return m_length;}
	bool isEmpty() const{return !m_length;}
	bool operator==(const StrAsVarNumberArray& other) const{return isArrayOfLengthEqual(other.m_numberArray);}
	bool operator!=(const StrAsVarNumberArray& other) const{return !operator==(other);}
	short Compare(const StrAsVarNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray);}
	bool operator<(const StrAsVarNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray) < 0;}
	bool operator>(const StrAsVarNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray) > 0;}
	bool operator<=(const StrAsVarNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray) <= 0;}
	bool operator>=(const StrAsVarNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray) >= 0;}
	operator size_t() const{return (size_t)*m_numberArray + m_length;}
	operator int() const{return (int)*m_numberArray + m_length;}
	operator long() const{return (long)*m_numberArray + m_length;}
/*
	void Initialize()
	{
		m_length = m_wholeNumberCount = m_wholeLength = 0;
		if(m_numberArray)
		{
			NumberType* cursor = m_numberArray;
			for(unsigned short i = 0; i < m_arraySize; ++i, ++cursor)
			{
				*cursor = 0;
			}
		}
	}
*/
	void Clear()
	{
		DoSetString(0, "");
/*
		m_length = m_wholeNumberCount = m_wholeLength = 0;
		NumberType* cursor = m_numberArray;
		for(unsigned short i = 0; i < m_arraySize; ++i, ++cursor)
		{
			if(*cursor)
			{
				*cursor = 0;
			}
			else
			{
				break;
			}
		}
*/
	}
	const char* GetString() const{return (const char*)m_numberArray;}
protected:
	NumberType* m_numberArray;
	unsigned short m_arraySize;
	unsigned short m_length;
	unsigned short m_wholeNumberCount;
	unsigned short m_wholeNumberCountPlusOneFraction;
//	unsigned short m_wholeLength;
	void DoSetString(const unsigned short& exactLength, const char* cursor)
	{
		const NumberType* numberCursorOther = (const NumberType*)cursor;
//		m_length = exactLength;
		unsigned short wholeLength;
		unsigned short arraySize = 1;
		unsigned short fraction = 0;
		char* fractionDst = NULL;
		if(exactLength)
		{
			m_wholeNumberCount = m_wholeNumberCountPlusOneFraction = exactLength / sizeof(NumberType);
			arraySize = m_wholeNumberCount + 1;
			wholeLength = m_wholeNumberCount * sizeof(NumberType);
			if(wholeLength != exactLength)
			{
				++m_wholeNumberCountPlusOneFraction;
			}
//			m_wholeLength = m_wholeNumberCount * sizeof(NumberType);
		}
		else
		{
			m_wholeNumberCount = m_wholeNumberCountPlusOneFraction = wholeLength = 0;//m_wholeLength = 0;
			cursor = NULL;
		}
		if(m_arraySize != arraySize)
		{
			if(m_numberArray)delete[] m_numberArray;
			m_arraySize = arraySize;
			m_numberArray = new NumberType[m_arraySize];
		}

//		if(m_wholeLength == exactLength)
		if(wholeLength == exactLength)
		{
			cursor = NULL;
		}
		else
		{
			fraction = exactLength - wholeLength;//m_wholeLength;
			cursor += wholeLength;//m_wholeLength;
			fractionDst = (char*)m_numberArray + wholeLength;//m_wholeLength;
		}

		m_length = exactLength;
////
		if(m_arraySize > m_wholeNumberCount)//should be always true
		{
			*(m_numberArray + m_wholeNumberCount) = 0;
		}
		NumberType* numberCursor = m_numberArray;

		for(unsigned short wholeNumberCount = m_wholeNumberCount; wholeNumberCount; --wholeNumberCount, ++numberCursor, ++numberCursorOther)
		{
			*numberCursor = *numberCursorOther;
		}
		if(cursor)
		{
			for(; fraction; --fraction, ++cursor, ++fractionDst)
			{
				*fractionDst = *cursor;
			}
		}
	}
	void DoSetString(const char* cursor)
	{
		if(cursor)
		{
			DoSetString((unsigned short)strlen(cursor), cursor);
		}
		else
		{
			DoSetString(0, "");
		}
	}
	void DoSetStringWithDelimiter(const char*& cursor, const char& del)
	{
		if(cursor)
		{
			unsigned short len;
			if(del)
			{
				len = 0;
				char c = *cursor;
				for(const char* cur = cursor; c && c != del; c = *++cur, ++len);
			}
			else
			{
				len = (unsigned short)strlen(cursor);
			}
			DoSetString(len, cursor);
			cursor += len;
			if(del && del == *cursor)++cursor;
		}
		else
		{
			DoSetString(0, "");
		}
	}
	void DoSetString(const char* cursor, const unsigned short& length)//length is how many chars max you want to get from cursor
	{
		if(cursor)
		{
			unsigned short len = (unsigned short)strlen(cursor);
			if(len > length)len = length;

			DoSetString(len, cursor);
		}
		else
		{
			DoSetString(0, "");
		}
	}
	void DoSetStringWithDelimiter(const char*& cursor, const unsigned short& length, const char& del)//length is how many chars max you want to get from cursor
	{
		if(cursor)
		{
			unsigned short len;
			if(del)
			{
				len = 0;
				char c = *cursor;
				for(const char* cur = cursor; c && c != del; c = *++cur, ++len);
			}
			else
			{
				len = (unsigned short)strlen(cursor);
			}
			unsigned short lenToDelimiter = len;
			if(len > length)len = length;

			DoSetString(len, cursor);

			cursor += lenToDelimiter;
			if(del && del == *cursor)++cursor;
		}
		else
		{
			DoSetString(0, "");
		}
	}
/*
	void ClearTail()
	{
		if(m_length > m_wholeLength)
		{
			char* cursor = (char*)m_numberArray + m_length;
			for(unsigned short fractionLength = m_wholeLength + sizeof(NumberType) - m_length; fractionLength; --fractionLength, ++cursor)
			{
				*cursor = '\0';
			}
		}
		else if(m_wholeNumberCount < m_arraySize)
		{
			*(m_numberArray + m_wholeNumberCount) = 0;
		}
	}
*/
/*
	void ClearNormalizedTail()
	{
		if(m_length > m_wholeLength)
		{
				char* cursor = (char*)m_numberArray + m_length;
				for(unsigned short fractionLength = m_wholeLength + sizeof(NumberType) - m_length; fractionLength; --fractionLength, ++cursor)
				{
					*cursor = '\0';
				}
			if(wholeNumberCount < N)
			{
				for(NumberType* numberCursor = m_numberArray + wholeNumberCount; wholeNumberCount < N; ++wholeNumberCount, ++numberCursor)
				{
					if(*numberCursor)
					{
						*numberCursor = 0;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
*/
private:
	void CopyArray(const NumberType* cursorOther)
	{
		NumberType* cursor = m_numberArray;
		for(unsigned short i = 0; i < m_arraySize; ++i, ++cursor, ++cursorOther)
		{
			*cursor = *cursorOther;
		}
	}
/*
	void CopyNormalizedArray(const NumberType* cursorOther)
	{
		NumberType* cursor = m_numberArray;
		unsigned short i = 0;
		for(; i < m_arraySize; ++i, ++cursor, ++cursorOther)
		{
			if(*cursorOther)
			{
				*cursor = *cursorOther;
			}
			else
			{
				break;
			}
		}
		for(; i < m_arraySize; ++i, ++cursor)
		{
			if(*cursor)
			{
				*cursor = 0;
			}
			else
			{
				break;
			}
		}
	}
*/
	bool isArrayOfLengthEqual(const NumberType* cursorOther) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
		for(unsigned short length = m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor != *cursorOther)
			{
				return false;
			}
/*
			if(!*cursor)
			{
				break;
			}
*/
		}
		return true;
	}
	short CompareArrayOfLength(const NumberType* cursorOther) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
		for(unsigned short length = m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor < *cursorOther)
			{
				return -1;
			}
			else if(*cursor > *cursorOther)
			{
				return 1;
			}
/*
			if(!*cursor)
			{
				break;
			}
*/
		}
		return 0;
	}
};

class AccountId
{
public:
	AccountId(const char* id)
	{
		SetAccountId(id);
	}
	AccountId(const unsigned __int64& first = 0, const unsigned __int64& second = 0):m_first(first),m_second(second){}
	void SetAccountId(const unsigned __int64& first, const unsigned __int64& second)
	{
		m_first = first;
		m_second = second;
	}
	void Nullify(){m_first = m_second = 0;}
	void SetAccountId(const char* id)
	{
		m_first = m_second = 0;
		if(*id)
		{
			char* dst = (char*)&m_first;
			unsigned int i = 0;
			for(; *id && i < sizeof(m_first); ++i, ++id, ++dst)
			{
				*dst = *id;
			}
			if(*id)
			{
				i = 0;
				for(; *id && i < sizeof(m_second); ++i, ++id, ++dst)
				{
					*dst = *id;
				}
			}
		}
	}
	void SetAccountId(const char* id, unsigned int len)
	{
		m_first = m_second = 0;
		if(len && *id)
		{
			char* dst = (char*)&m_first;
			unsigned int i = 0;
			bool big = len > sizeof(m_first);
			unsigned int end = big ? sizeof(m_first) : len;

			for(; *id && i < end; ++i, ++id, ++dst)
			{
				*dst = *id;
			}
			if(*id && big)
			{
				end = len - sizeof(m_first);
				if(end > sizeof(m_second))end = sizeof(m_second);
				i = 0;
				for(; *id && i < end ; ++i, ++id, ++dst)
				{
					*dst = *id;
				}
			}
		}
	}
	const char* GetId() const{return (const char*)&m_first;}
	const unsigned __int64& GetFirst() const{return m_first;}
	const unsigned __int64& GetSecond() const{return m_second;}
	operator size_t() const{return (size_t)m_first;}
	bool operator<(const AccountId& other) const{return m_first < other.m_first || m_first == other.m_first && m_second < other.m_second;}
	bool operator==(const AccountId& other) const{return m_first == other.m_first && m_second == other.m_second;}
	bool operator!=(const AccountId& other) const{return m_first != other.m_first || m_second != other.m_second;}
protected:
	unsigned __int64 m_first;
	unsigned __int64 m_second;
};

template<class T>
class Chain
{
public:
	typedef std::list<T> List;
	typedef typename List::iterator ListIterator;
	typedef typename List::const_iterator ListConstIterator;
	typedef std::map<T, ListIterator> Map;
	typedef typename Map::iterator MapIterator;
	typedef typename Map::const_iterator MapConstIterator;

	Chain(unsigned int cap = 0xFFFFFFFF, bool rearrangeable = true):
		m_mapEnd(m_map.end()),
		m_mapConstEnd(m_map.end()),
#ifdef CHECK_CHAIN
		m_threadId(0),
#endif
		m_cap(cap),
		m_currentIt(m_list.end()),
		m_frozen(false),
		m_rearrangeable(rearrangeable)
	{
	}

	Chain(const Chain& other):
		m_list(other.m_list),
		m_mapEnd(m_map.end()),
		m_mapConstEnd(m_map.end()),
#ifdef CHECK_CHAIN
		m_threadId(other.m_threadId),
#endif
		m_cap(other.m_cap),
		m_currentIt(m_list.end()),
		m_frozen(other.m_frozen),
		m_rearrangeable(other.m_rearrangeable)
	{
		for(ListIterator it = m_list.begin(), itend = m_list.end(); it != itend;)
		{
			T& t = *it;
			if(m_map.find(t) == m_mapEnd)
			{
				m_map.insert(Map::value_type(t, it));
				++it;
			}
			else
			{
				it = m_list.erase(it);
				itend = m_list.end();
			}
		}
		SetCurrentValue(other.GetCurrent());
	}

	virtual ~Chain(){}

	const Chain& operator=(const Chain& other)
	{
		if(ChainLock())
		{
#ifdef CHECK_CHAIN
			m_threadId = other.m_threadId;
#endif
			m_map.clear();
			m_list = other.m_list;
			m_cap = other.m_cap;
			m_currentIt = m_list.end();
			m_frozen = other.m_frozen;
			m_rearrangeable = other.m_rearrangeable;
			for(ListIterator it = m_list.begin(), itend = m_list.end(); it != itend; ++it)
			{
				m_map.insert(Map::value_type(*it, it));
			}
			SetCurrentValue(other.GetCurrent());
			ChainUnlock();
		}
		return *this;
	}

	bool isAtEnd() const
	{
		bool ret = true;
		if(ChainLock())
		{
			ret = m_currentIt == m_list.end();
			ChainUnlock();
		}
		return ret;
	}
#ifdef CHECK_CHAIN
	void SetThreadId(unsigned int threadId)
	{
		m_threadId = threadId;
	}
	virtual void Verify() const
	{
		U_CheckUtilsThread(m_threadId, "Chain");
		assert(m_map.size() == m_list.size());
		ListConstIterator itend = m_list.end();
		MapConstIterator found;
		for(ListConstIterator it = m_list.begin(); it != itend; ++it)
		{
			found = m_map.find(*it);
			if(found == m_mapConstEnd)
			{
				assert(0);
				break;
			}
			else if(found->second != it)
			{
				assert(0);
				break;
			}
		}
	}
#endif

	bool operator==(const Chain& other) const
	{
		bool ret = false;
		if(ChainLock())
		{
			ret = m_cap == other.m_cap
				&& m_frozen == other.m_frozen
				&& m_rearrangeable == other.m_rearrangeable
				&& m_list == other.m_list;
			ChainUnlock();
		}
		return ret;
	}

	bool operator!=(const Chain& other) const
	{
		return !operator==(other);
	}

	bool SameList(const Chain& other) const
	{
		bool ret = false;
		if(ChainLock())
		{
			ret = m_list == other.m_list;
			ChainUnlock();
		}
		return ret;
	}
	bool isListIntersect(const Chain& other) const
	{
		bool ret = false;
		if(ChainLock())
		{
			const Map& map1 = m_map.size() <= other.m_map.size() ? m_map : other.m_map;
			const Map& map2 = m_map.size() > other.m_map.size() ? m_map : other.m_map;
			Map::const_iterator foundEnd = map2.end();
			for(Map::const_iterator it = map1.begin(), itend = map1.end(); it != itend; ++it)
			{
				if(map2.find(it->first) != foundEnd)
				{
					ret = true;
					break;
				}
			}
			ChainUnlock();
		}
		return ret;
	}
	const T* GetPrevious()
	{
		const T* ret = NULL;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				ListIterator itend = m_list.end();
				if(m_currentIt == itend)
				{
					m_currentIt = m_list.begin();
				}
				else
				{
					++m_currentIt;
					if(m_currentIt == itend)
					{
						m_currentIt = m_list.begin();
					}
				}
				ret = &(*m_currentIt);
			}
			ChainUnlock();
		}
		return ret;
	}
	const T* GetNext()
	{
		const T* ret = NULL;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				ListIterator itbegin = m_list.begin();
				if(m_currentIt == itbegin)
				{
					m_currentIt = m_list.end();
				}
				--m_currentIt;
				ret = &(*m_currentIt);
			}
			ChainUnlock();
		}
		return ret;
	}

	const T* GetCurrent() const
	{
		const T* ret = NULL;
		if(ChainLock())
		{
			ret = m_currentIt == m_list.end() ? NULL : &(*m_currentIt);
			ChainUnlock();
		}
		return ret;
	}

	T* GetCurrent()
	{
		T* ret = NULL;
		if(ChainLock())
		{
			ret = m_currentIt == m_list.end() ? NULL : &(*m_currentIt);
			ChainUnlock();
		}
		return ret;
	}

	void Reset()
	{
		if(ChainLock())
		{
			if(m_currentIt != m_list.end())
			{
				if(m_rearrangeable)
				{
					ListIterator itLast;
					Map::iterator found;
					for(ListIterator it = m_list.begin(); it != m_currentIt; it = m_list.begin())
					{
						T& t = *it;
						found = m_map.find(t);
						m_list.push_back(t);
						m_list.pop_front();
						itLast = m_list.end();
						--itLast;
						found->second = itLast;
					}
				}
				m_currentIt = m_list.end();
			}
			ChainUnlock();
		}
	}

	unsigned int GetCap() const{return m_cap;}
	void SetCap(unsigned int cap)
	{
		if(ChainLock())
		{
			if(m_cap != cap)
			{
				if(cap)
				{
					unsigned int count = GetCount();
					if(count > cap)
					{
						ListIterator it = m_list.end();
						bool currentInitialized = m_currentIt != it;
						ListIterator itBegin = m_list.begin();
						for(--it; count > cap; --count)
						{
							if(currentInitialized)
							{
								if(m_currentIt == it)
								{
									--m_currentIt;
								}
							}
							m_map.erase(*it);
							--it;
							m_list.pop_back();
						}
						if(!currentInitialized)
						{
							m_currentIt = m_list.end();
						}
					}
				}
				else
				{
					Clear();
				}
				m_cap = cap;
			}
			ChainUnlock();
		}
	}
	bool isFrozen() const{return m_frozen;}
	bool isRearrangeable() const{return m_rearrangeable;}
	void SetFrozen(bool frozen){m_frozen = frozen;}
	void SetRearrangeable(bool rearrangeable){m_rearrangeable = rearrangeable;}
	bool SetCurrentValue(const T* t)
	{
		bool ret = false;
		if(ChainLock())
		{
			if(t)
			{
				MapIterator found = m_map.find(*t);
				if(found != m_mapEnd)
				{
					m_currentIt = found->second;
					ret = true;
				}
			}
			else
			{
				m_currentIt = m_list.end();
				ret = true;
			}
			ChainUnlock();
		}
		return ret;
	}
	const T* PushFrontChainItem(const T& t)
	{
		const T* ret = NULL;
		if(ChainLock())
		{
			MapIterator found = m_map.find(t);
			if(found == m_mapEnd)
			{
				if(isFull())
				{
					++m_cap;
				}
				m_list.push_front(t);
				ListIterator lit = m_list.begin();
				m_map.insert(Map::value_type(*lit, lit));
//				ret = true;
			}
			else
			{
				ret = &*found->second;
			}
			ChainUnlock();
		}
		return ret;
	}
	const T* PushBackChainItem(const T& t)
	{
		const T* ret = NULL;
		if(ChainLock())
		{
			MapIterator found = m_map.find(t);
			if(found == m_mapEnd)
			{
				if(isFull())
				{
					++m_cap;
				}
				m_list.push_back(t);
				ListIterator lit = m_list.end();
				--lit;
				m_map.insert(Map::value_type(*lit, lit));
//				ret = true;
			}
			else
			{
				ret = &*found->second;
			}
			ChainUnlock();
		}
		return ret;
	}
	bool InsertChainItem(const T& t, bool after = false)
	{
		bool ret = false;
		if(ChainLock())
		{
			if(m_cap)
			{
				MapIterator found = m_map.find(t);
				if(m_frozen)
				{
					if(found != m_mapEnd)
					{
						m_currentIt = found->second;
					}
				}
				else
				{
					if(found == m_mapEnd)
					{
						bool full = isFull();
						if(full)
						{
							if(isEmpty())
							{
								ChainUnlock();
								return false;
							}
							ListIterator toErase;
							if(after)
							{
								if(m_currentIt == m_list.end())
								{
									toErase = m_list.begin();
								}
								else
								{
									toErase = m_currentIt;
									++toErase;
									if(toErase == m_list.end())
									{
										toErase = m_list.begin();
									}
								}
							}
							else
							{
								if(m_currentIt == m_list.end())
								{
									toErase = m_currentIt;
									--toErase;
								}
								else
								{
									toErase = m_currentIt;
									if(toErase == m_list.begin())
									{
										toErase = m_list.end();
									}
									--toErase;
								}
							}
							bool isAtEnd = m_currentIt == m_list.end() || m_currentIt == toErase;
					
							m_map.erase(*toErase);
							m_list.erase(toErase);
							if(isAtEnd)
							{
								m_currentIt = m_list.end();
							}
						}
						else
						{
							ret = true;
						}
					}
					else//found != m_mapEnd
					{

						if(m_currentIt == found->second)
						{
							ChainUnlock();
							return false;
						}
						if(m_currentIt == m_list.end())
						{
							ListIterator temp = found->second;
							++temp;
							if(temp == m_currentIt)
							{
								ChainUnlock();
								return false;
							}
						}
						else if(after)
						{
							ListIterator temp = m_currentIt;
							++temp;
							if(found->second == temp)
							{
								ChainUnlock();
								return false;
							}
						}
						else
						{
							ListIterator temp = found->second;
							++temp;
							if(temp == m_currentIt)
							{
								ChainUnlock();
								return false;
							}
						}
						m_list.erase(found->second);
					}
					if(after)
					{
						if(m_currentIt == m_list.end())
						{
							m_currentIt = m_list.insert(m_currentIt, t);
						}
						else
						{
							++m_currentIt;
							m_currentIt = m_list.insert(m_currentIt, t);
						}
					}
					else
					{
						m_currentIt = m_list.insert(m_currentIt, t);
					}
					if(found == m_mapEnd)
					{
						m_map.insert(Map::value_type(*m_currentIt, m_currentIt));
					}
					else
					{
						found->second = m_currentIt;
					}
				}
			}
		}
		ChainUnlock();
		return ret;
	}

	bool AddChainItem(const T& t, bool atEnd = false)
	{
		if(ChainLock())
		{
			if(m_cap)
			{
				if(m_frozen)
				{
					MapIterator found = m_map.find(t);
					if(found != m_mapEnd)
					{
						m_currentIt = found->second;
					}
				}
				else
				{
					Reset();
					MapIterator found = m_map.find(t);
					if(found == m_mapEnd)
					{
						bool full = isFull();
						if(full)
						{
							if(isEmpty())
							{
								ChainUnlock();
								return false;
							}
							if(atEnd)
							{
								m_map.erase(m_list.front());
								m_list.pop_front();
							}
							else
							{
								m_map.erase(m_list.back());
								m_list.pop_back();
							}
						}
						ListIterator lit;
						if(atEnd)
						{
							m_list.push_back(t);
							lit = m_list.end();
							--lit;
						}
						else
						{
							m_list.push_front(t);
							lit = m_list.begin();
						}
						m_map.insert(Map::value_type(*lit, lit));

						m_currentIt = m_list.end();

						ChainUnlock();
						return !full;
					}
					else//found != m_mapEnd
					{
//						m_map.erase(found->second);
						m_list.erase(found->second);
						if(atEnd)
						{
							m_list.push_back(found->first);
							found->second = m_list.end();
							--found->second;
						}
						else
						{
							m_list.push_front(found->first);
							found->second = m_list.begin();
						}

						m_currentIt = m_list.end();
					}
				}
			}
			ChainUnlock();
		}
		return false;
	}
	ListIterator GetListEnd()
	{
#ifdef CHECK_CHAIN
Verify();
#endif
		return m_list.end();
	}
	ListConstIterator GetListEnd() const
	{
#ifdef CHECK_CHAIN
Verify();
#endif
		return m_list.end();
	}
	ListIterator Remove(const T& t)
	{
		if(ChainLock())
		{
//			Reset();
			ListIterator ret;
			MapIterator found = m_map.find(t);
			if(found != m_mapEnd)
			{
				if(m_currentIt == found->second)
				{
					++m_currentIt;
					if(m_currentIt == m_list.end())
					{
						m_currentIt = m_list.begin();
						if(m_currentIt == found->second)
						{
							m_currentIt = m_list.end();
						}
					}
				}
				ret = m_list.erase(found->second);
				m_map.erase(found);
			}
			else
			{
				ret = m_list.end();//false;
			}
			ChainUnlock();			
			return ret;
		}
		return m_list.end();
	}
	void Clear()
	{
		if(ChainLock())
		{
			m_list.clear();
			m_map.clear();
			m_currentIt = m_list.end();
			ChainUnlock();			
		}
	}
	unsigned int GetCount() const{return (unsigned int)m_list.size();}
	bool isEmpty() const{return m_list.empty();}
	bool isFull() const{return GetCount() >= m_cap;}
	const List& GetList() const
	{
#ifdef CHECK_CHAIN
Verify();
#endif
		return m_list;
	}
	T* GetBorderItem(bool back)
	{
		T* ret = NULL;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				T& t = back ? *m_list.rbegin() : *m_list.begin();
				ret = &t;
			}
			ChainUnlock();
		}
		return ret;
	}
	const T* PeepBack() const
	{
		const T* ret = NULL;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				ret = &(*m_list.rbegin());
			}
			ChainUnlock();
		}
		return ret;
	}
	const T* PeepFront() const
	{
		const T* ret = NULL;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				ret = &(*m_list.begin());
			}
			ChainUnlock();
		}
		return ret;
	}
	T* PeepBack()
	{
		T* ret = NULL;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				ret = &(*m_list.rbegin());
			}
			ChainUnlock();
		}
		return ret;
	}
	T* PeepFront()
	{
		T* ret = NULL;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				ret = &(*m_list.begin());
			}
			ChainUnlock();
		}
		return ret;
	}
	bool PopBack(T& t)
	{
		bool ret = false;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				t = *m_list.rbegin();
				Remove(t);
				ret = true;
			}
			ChainUnlock();
		}
		return ret;
	}
	bool PopFront(T& t)
	{
		bool ret = false;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				t = *m_list.begin();
				Remove(t);
				ret = true;
			}
			ChainUnlock();
		}
		return ret;
	}

	const T* GetItemAt(unsigned int at) const
	{
		const T* ret = NULL;
		if(ChainLock())
		{
			if(at < GetCount())
			{
				List::const_iterator it = m_list.begin();
				for(; at; ++it, --at);

				ret = &(*it);
			}
			ChainUnlock();
		}
		return ret;
	}
//	const T* Find(const T& t) const
	bool Contains(const T& t) const
	{
		bool ret = false;
		if(ChainLock())
		{
			ret = m_map.find(t) != m_mapEnd;
			ChainUnlock();
		}
		return ret;
	}
	ListIterator Find(const T& t)
	{
		if(ChainLock())
		{
			Map::const_iterator found = m_map.find(t);
			ListIterator ret = found == m_mapEnd ? m_list.end() : found->second;
			ChainUnlock();
			return ret;
		}
		return m_list.end();
	}

	void CopyList(List& list) const
	{
		if(ChainLock())
		{
			for(ListConstIterator it = m_list.begin(), itend = m_list.end(); it != itend; ++it)
			{
				list.push_back(*it);
			}
			ChainUnlock();
		}
	}
	virtual bool ChainLock() const{return true;}
	virtual void ChainUnlock() const
	{
#ifdef CHECK_CHAIN
Verify();
#endif
	}
protected:
	List m_list;
	Map m_map;
	MapIterator m_mapEnd;
	MapConstIterator m_mapConstEnd;
#ifdef CHECK_CHAIN
	unsigned int m_threadId;
#endif
	unsigned int m_cap;
	mutable ListIterator m_currentIt;
	bool m_frozen;
	bool m_rearrangeable;
};

template<class T>
class ThreadSafeChain : public Chain<T>
{
public:
	ThreadSafeChain(unsigned int cap = 0xFFFFFFFF, bool rearrangeable = true):Chain(cap, rearrangeable){}
	ThreadSafeChain(const ThreadSafeChain& other):Chain(other){}
	const ThreadSafeChain& operator=(const ThreadSafeChain& other)
	{
		Chain::operator=(other);
		return *this;
	}
#ifdef CHECK_CHAIN
	virtual void Verify() const{}
#endif
	virtual bool ChainLock() const
	{
		return m_chainLock.Lock() == TRUE;
	}
	virtual void ChainUnlock() const
	{
		m_chainLock.Unlock();
	}
protected:
	mutable CCriticalSection m_chainLock;
};

template<class C>
struct lessPtr : public std::binary_function<C, C, bool>
{	// functor for operator<
	bool operator()(const C& p1, const C& p2) const
	{	// apply operator< to operands
		return *p1 < *p2;
	}
};

class U_API LineBuffer
{
public:
	LineBuffer(unsigned int length = 0, const char* buffer = NULL):m_length(length),m_buffer(buffer){}
	void Reset(){m_length = 0; m_buffer = NULL;}
	void SetBuffer(unsigned int length, const char* buffer){m_length = length; m_buffer = buffer;}
	bool isEmpty() const{return !m_length;}
	const char* GetLastChar() const{return m_buffer ? m_buffer + m_length : NULL;}
	unsigned int IncrementCursor(unsigned int length)
	{
		if(length < m_length)
		{
			m_length -= length;
			m_buffer += length;
			return 0;
		}
		else
		{
			unsigned int remaining = length - m_length;
			Reset();
			return remaining;
		}
	}
	unsigned int m_length;
	const char* m_buffer;
};

class LineBufferVector;

class U_API LineBufferArray
{
public:
	LineBufferArray(unsigned int bufferCount);
	LineBufferArray(const LineBufferArray& other);
	~LineBufferArray();
//	const LineBufferArray& operator=(const LineBufferArray& other);
//	void DoubleBufferCount();
//	void SetBufferCount(unsigned int bufferCount);
//	unsigned int GetBufferCount() const{return m_bufferCount;}
	unsigned int GetBufferCount() const;//{return (unsigned int)m_ringVector.capacity();}
//	LineBuffer* GetBufferArray(){return m_bufferArray;}
//	LineBuffer* GetLineBufferAt(unsigned int at){return at < m_bufferCount ? m_bufferArray + at : NULL;}
//	LineBuffer* GetLastFilledLineBuffer(){return m_filledBufferCount > 1 ? m_bufferArray + (m_filledBufferCount - 1) : m_bufferArray;}
	LineBuffer& GetLastFilledLineBuffer();

	unsigned int GetTotalSize() const{return m_totalSize;}
//	unsigned int GetFilledBufferCount() const{return m_filledBufferCount;}
	unsigned int GetFilledBufferCount() const;//{return (unsigned int)m_ringVector.size();}
	void IncrementLastFilledLineBufferLength(unsigned int length)
	{
//		LineBuffer* lineBuffer = GetLastFilledLineBuffer();
//		lineBuffer->m_length += length;
		LineBuffer& lineBuffer = GetLastFilledLineBuffer();
		lineBuffer.m_length += length;
		m_totalSize += length;
	}
	void IncrementTotalSize(unsigned int length){m_totalSize += length;}
	void DecrementTotalSize(unsigned int length)
	{
		if(m_totalSize >= length)
		{
			m_totalSize -= length;
		}
		else
		{
			m_totalSize = 0;
		}
	}
	void AddLineBuffer(const char* buffer, unsigned int length);
	void Clear();
/*
	{
		m_ringVector.clear();
		m_totalSize = 0;
	}
*/
	void IncrementCursor(unsigned int length);
/*
	{
		LineBuffer* cursor;
		while(!m_ringVector.empty())
		{
			cursor = &m_ringVector.front();
			m_totalSize -= cursor->m_length;
			length = cursor->IncrementCursor(length);
			if(!length)
			{
				if(cursor->isEmpty())
				{
					m_ringVector.pop_front();
				}
				else
				{
					m_totalSize += cursor->m_length;
				}
				break;
			}
		}
	}
*/
	LineBufferVector* GetRingVector(){return m_ringVector;}
	const LineBufferVector* GetRingVector() const{return m_ringVector;}
protected:
//	unsigned int m_bufferCount;
	unsigned int m_totalSize;
//	unsigned int m_filledBufferCount;
//	LineBuffer* m_bufferArray;

//	RingVector<LineBuffer> m_ringVector;
	LineBufferVector* m_ringVector;
};


//template<class L>//unsigned short or unsigned int
//class LineBufferArrayReader
class U_API LineBufferArrayReader
{
public:
	void SetLineBufferArray(const LineBufferArray* bufferArray){m_bufferArray = bufferArray;}
//	virtual bool ProcessDataToken(const char* cursor, L length) const = 0;
	virtual bool ProcessDataToken(const char* cursor, unsigned short length) const = 0;
//	bool ProcessAllData()
	unsigned int ProcessAllData() const;
protected:
	LineBufferArrayReader(const LineBufferArray* bufferArray = NULL, bool exitOnNoProcess = false):m_bufferArray(bufferArray), m_exitOnNoProcess(exitOnNoProcess){}
	const LineBufferArray* m_bufferArray;
	bool m_exitOnNoProcess;
};

typedef std::hash_map<std::string, std::string> StringHashMap;

template<class T>
char* WINAPI U_UnsignedNumberToStr(T n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0')
{
	if(size)
	{
		--size;
		char* cursor = num + size;
		*cursor = '\0';
		if(del)
		{
			--size;
			--cursor;
			*cursor = del;
		}
		T n10;
		if(decDigits)
		{
			do
			{
				--cursor;
				--decDigits;
				n10 = n / 10;
				*cursor = '0' + (char)(n - 10 * n10);
				n = n10;
			}
			while(decDigits);
			--cursor;
			*cursor = '.';
		}
		do
		{
			--cursor;
			n10 = n / 10;
			*cursor = '0' + (n - 10 * n10);
			n = n10;
		}
		while(n);
		return cursor;
	}
	return num;
}

template<class T>
char* WINAPI U_SignedNumberToStr(T n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0')
{
	if(n < 0)
	{
		num = U_UnsignedNumberToStr(-n, num, size, decDigits, del);
		--num;
		*num = '-';
		return num;
	}
	else
	{
		return U_UnsignedNumberToStr(n, num, size, decDigits, del);
	}
}

template<class T>
char* WINAPI U_UnsignedNumberToStrWithCommas(T n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0')
{
	char* cursor = num + (size - 1);
	*cursor = '\0';
	if(del)
	{
		--cursor;
		*cursor = del;
	}
	T n10;
	if(decDigits)
	{
		do
		{
			--cursor;
			--decDigits;
			n10 = n / 10;
			*cursor = '0' + (char)(n - 10 * n10);
			n = n10;
		}
		while(decDigits);
		--cursor;
		*cursor = '.';
	}
	unsigned char three = 0;
	do
	{
		if(three == 3)
		{
			three = 1;
			--cursor;
			*cursor = ',';
		}
		else
		{
			++three;
		}
		--cursor;
		n10 = n / 10;
		*cursor = '0' + (n - 10 * n10);
		n = n10;
	}
	while(n);
	return cursor;
}

template<class T>
char* WINAPI U_SignedNumberToStrWithCommas(int n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0')
{
	if(n < 0)
	{
		num = U_UnsignedNumberToStrWithCommas(-n, num, size, decDigits, del);
		--num;
		*num = '-';
		return num;
	}
	else
	{
		return U_UnsignedNumberToStrWithCommas(n, num, size, decDigits, del);
	}
}

template<class T>
void U_AppendNumberAsString(std::string& str, const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	const char* cursor = (const char*)&number;
	char c = *cursor;
	for(unsigned char i = sizeof(number); c && i; --i, c = *++cursor)
	{
		str += c;
	}
	if(del)str += del;
}

template<class T>
void U_AppendNumberAsStringTerm0(std::string& str, const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	const char* cursor = (const char*)&number;
	char c = *cursor;
	for(unsigned char i = sizeof(number) - 1; c && i; --i, c = *++cursor)
	{
		str += c;
	}
	if(del)str += del;
}

template<class T>
const char* U_GetStrFromNumber(const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	static std::string str;
	str.clear();
	U_AppendNumberAsString(str, number, del);
	return str.c_str();
}

template<class T>
const char* U_GetStrFromNumberTerm0(const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	static std::string str;
	str.clear();
	U_AppendNumberAsStringTerm0(str, number, del);
	return str.c_str();
}

template<class T>
const std::string& U_GetStringFromNumber(const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	static std::string str;
	str.clear();
	U_AppendNumberAsString(str, number, del);
	return str;
}

template<class T>
const std::string& U_GetStringFromNumberTerm0(const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	static std::string str;
	str.clear();
	U_AppendNumberAsStringTerm0(str, number, del);
	return str;
}

template<class T>
const char* U_ReadUnsignedNumberFromString(T& number, const char* str, const char& del = '\0', const T& defaultValue = 0)
{
	if(*str)
	{
		if(del == *str)
		{
			++str;
			number = defaultValue;
		}
		else
		{
			number = 0;
			for(char c = *str; c; c = *++str)
			{
				if(del == c)
				{
					++str;
					break;
				}
				number *= 10;
				number += c - '0';
			}
		}
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class ST>
const char* U_ReadSignedNumberFromString(ST& number, const char* str, const char& del = '\0', const ST& defaultValue = 0)
{
	if(*str)
	{
		bool negative = *str == '-';
		if(negative || *str == '+')
		{
			++str;
			if(!*str)
			{
				number = negative ? -defaultValue : defaultValue;
				return str;;
			}
		}
		std::make_unsigned<ST>::type positiveValue;
		str = U_ReadUnsignedNumberFromString(positiveValue, str, del);//, (unsigned int)0);
		number = negative ? -(ST)positiveValue : (ST)positiveValue;
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class T>
T U_GetUnsignedNumberFromString(const char* str, const char& del = '\0', const T& defaultValue = 0)
{
	T number;
	U_ReadUnsignedNumberFromString(number, str, del, defaultValue);
	return number;
}

template<class ST>
ST U_GetSignedNumberFromString(const char* str, const char& del = '\0', const ST& defaultValue = 0)
{
	ST number;
	U_ReadSignedNumberFromString(number, str, del, defaultValue);
	return number;
}
//Hex
template<class T>
const char* U_ReadHexUnsignedNumberFromString(T& number, const char* str, const char& del = '\0', const T& defaultValue = 0)
{
	if(*str)
	{
		if(del == *str)
		{
			++str;
			number = defaultValue;
		}
		else
		{
			number = 0;
			for(char c = *str; c; c = *++str)
			{
				if(del == c)
				{
					++str;
					break;
				}
				number <<= 4;
				if(c >= '0' && c <= '9')
				{
					number += c - '0';
				}
				else if(c >= 'A' && c <= 'F')
				{
					number += c - 'A' + 10;
				}
				else if(c >= 'a' && c <= 'f')
				{
					number += c - 'a' + 10;
				}
			}
		}
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class ST>
const char* U_ReadHexSignedNumberFromString(ST& number, const char* str, const char& del = '\0', const ST& defaultValue = 0)
{
	if(*str)
	{
		bool negative = *str == '-';
		if(negative || *str == '+')
		{
			++str;
			if(!*str)
			{
				number = negative ? -defaultValue : defaultValue;
				return str;;
			}
		}
		std::make_unsigned<ST>::type positiveValue;
		str = U_ReadHexUnsignedNumberFromString(positiveValue, str, del);//, (unsigned int)0);
		number = negative ? -(ST)positiveValue : (ST)positiveValue;
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class T>
T U_GetHexUnsignedNumberFromString(const char* str, const char& del = '\0', const T& defaultValue = 0)
{
	T number;
	U_ReadHexUnsignedNumberFromString(number, str, del, defaultValue);
	return number;
}

template<class ST>
ST U_GetHexSignedNumberFromString(const char* str, const char& del = '\0', const ST& defaultValue = 0)
{
	ST number;
	U_ReadHexSignedNumberFromString(number, str, del, defaultValue);
	return number;
}
//
template<class T>
T U_ConvertNumberHexToDec(T number)
{
	T retValue = 0;
	T multiplier = 1;
	for(; number; number >>= 4)
	{
		retValue += (number & 0xF) * multiplier;
		multiplier *= 10;
	}
	return retValue;
}

template<class T>
void U_UIntToBitCharArray(const T& value, char* buf, unsigned int bufsize)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	unsigned int bitCount = sizeof(T) << 3;
	if(bufsize < bitCount + 1)
	{
		for(T flag = (T)1 << (bitCount - 1); flag; flag >>= 1, ++buf)
		{
			*buf = value & flag ? '1' : '0';
		}
	}
	*buf = '\0';
}

template<class T>
void U_UIntToBitStr(const T& value, std::string& str)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	for(T flag = (T)1 << ((sizeof(T) << 3) - 1); flag; flag >>= 1)
	{
		str += value & flag ? '1' : '0';
	}
}

template<class T>
void U_UIntToBitCharArrayReverse(const T& value, char* buf, unsigned int bufsize)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	unsigned int bitCount = sizeof(T) << 3;
	if(bufsize < bitCount + 1)
	{
		for(T flag = 1; flag; flag <<= 1, ++buf)
		{
			*buf = value & flag ? '1' : '0';
		}
	}
	*buf = '\0';
}

template<class T>
void U_UIntToBitStrReverse(const T& value, std::string& str)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	for(T flag = 1; flag; flag <<= 1)
	{
		str += value & flag ? '1' : '0';
	}
}

template<class T>
void U_BitStrUInt(T& value, const char*& cursor, char delimiter = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	value = 0;
	T flag = (T)1 << ((sizeof(T) << 3) - 1);
	for(; flag && *cursor && *cursor != delimiter; flag >>= 1, ++cursor)
	{
		if(*cursor != '0')
		{
			value |= flag;
		}
	}
}

template<class C>
char U_CompareUIntAsString(const C& first, const C& second)
{
	const unsigned char* c1 = (const unsigned char*)&first;
	const unsigned char* c2 = (const unsigned char*)&second;
	unsigned char a1 = *c1;
	unsigned char a2 = *c2;
	for(unsigned char i = sizeof(C); i; --i, a1 = *++c1, a2 = *++c2)
	{
		if(a1 < a2)
		{
			return -1;
		}
		else if(a1 > a2)
		{
			return 1;
		}
		else if(!a1)
		{
			return 0;
		}
	}
	return 0;
/*
	const char* firstStr = (const char*)&first;
	const char* secondStr = (const char*)&second;
	for(unsigned int i = 0; i < sizeof(C); ++i, ++firstStr, ++secondStr)
	{
		if(*firstStr)
		{
			if(*secondStr)
			{
				if(*firstStr < *secondStr)
				{
					return -1;
				}
				if(*secondStr < *firstStr)
				{
					return 1;
				}
			}
			else
			{
				return 1;
			}
		}
		else if(*secondStr)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
*/
}

template<class C>
short U_CompareSets(const C& c1, const C& c2)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	C::const_iterator it1 = c1.begin(), it2 = c2.begin(), it1end = c1.end(), it2end = c2.end();
	while(true)
	{
		if(it1 == it1end)
		{
			return it2 == it2end ? 0 : -1;
		}
		else if(it2 == it2end)
		{
			return 1;
		}
		else if(*it1 < *it2)
		{
			return -1;
		}
		else if(*it2 < *it1)
		{
			return 1;
		}
		else
		{
			++it1;
			++it2;
		}
	}
	return 0;
}

template<class C>
bool U_SetsEqual(const C& c1, const C& c2)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	if(c1.size() == c2.size())
	{
		C::const_iterator it1 = c1.begin(), it2 = c2.begin(), it1end = c1.end(), it2end = c2.end();
		while(true)
		{
			if(it1 == it1end)
			{
				return it2 == it2end;
			}
			else if(it2 == it2end || *it1 != *it2)
			{
				return false;
			}
			else
			{
				++it1;
				++it2;
			}
		}
		return true;
	}
	return false;
}

template<class C>
short U_CompareMaps(const C& c1, const C& c2)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	C::const_iterator it1 = c1.begin(), it2 = c2.begin(), it1end = c1.end(), it2end = c2.end();
	while(true)
	{
		if(it1 == it1end)
		{
			return it2 == it2end ? 0 : -1;
		}
		else if(it2 == it2end)
		{
			return 1;
		}
		else if(it1->first < it2->first)
		{
			return -1;
		}
		else if(it2->first < it1->first)
		{
			return 1;
		}
		else if(it1->second < it2->second)
		{
			return -1
		}
		else if(it2->second < it1->second)
		{
			return 1
		}
		else
		{
			++it1;
			++it2;
		}
	}
	return 0;
}

template<class C>
short U_MapsEqual(const C& c1, const C& c2)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	if(c1.size() == c2.size())
	{
		C::const_iterator it1 = c1.begin(), it2 = c2.begin(), it1end = c1.end(), it2end = c2.end();
		while(true)
		{
			if(it1 == it1end)
			{
				return it2 == it2end;
			}
			else if(it2 == it2end || it1->first != it2->first || it1->second != it2->second)
			{
				return false;
			}
			else
			{
				++it1;
				++it2;
			}
		}
		return true;
	}
	return false;
}

template<class C>
struct lessUIntAsStr : public std::binary_function<C, C, bool>
{	// functor for operator<
	bool operator()(const C& p1, const C& p2) const
	{	// apply operator< to operands
//		return U_CompareUIntAsString(p1, p2) == -1;
		const unsigned char* c1 = (const unsigned char*)&p1;
		const unsigned char* c2 = (const unsigned char*)&p2;
		unsigned char a1 = *c1;
		unsigned char a2 = *c2;
		for(unsigned char i = sizeof(C); i; --i, a1 = *++c1, a2 = *++c2)
		{
			if(a1 < a2)
			{
				return true;
			}
			if(a1 > a2 || !a1)
			{
				return false;
			}
		}
		return false;
	}
};

template<class T>
void U_AdjustValueByDifference(T& oldValue, const T& newValue, T& valueToAdjust)
{
	if(newValue != oldValue)
	{
		valueToAdjust += newValue;
		valueToAdjust -= oldValue;
		oldValue = newValue;
	}
}

#ifdef __cplusplus
extern "C"
{
#endif

TakionRingVectorBase* WINAPI U_CreateTakionRingVector(unsigned int capacity, bool overwrite = true, bool keepLast = false);
TakionIterator* WINAPI U_CreateTakionRingVectorIterator(TakionRingVectorBase* ringVector);
RingVectorBaseItem* WINAPI U_GetNextTakionRingVectorItem(TakionIterator* iterator);
TakionIterator* WINAPI U_CreateReverseTakionRingVectorIterator(TakionRingVectorBase* ringVector);
RingVectorBaseItem* WINAPI U_GetNextReverseTakionRingVectorItem(TakionIterator* iterator);
/*
enum EcnBookId
{
	ECNBOOK_NSDQ = 1,
	ECNBOOK_ARCA,
	ECNBOOK_BATS,
	ECNBOOK_EDGA,
	ECNBOOK_EDGX,
	BOOK_LEVEL2,
	ECNBOOK_NQBX,
	ECNBOOK_CBSX,

	ECNBOOK_COUNT
};

void WINAPI U_ResetIterator(void* iterator);
void WINAPI U_DeleteIterator(void* iterator);
const Quote* WINAPI U_GetNextExpandedQuote(void* iterator);
const Quote* WINAPI U_GetNextAggregatedQuote(void* iterator);
const char* const* WINAPI U_GetEcnNames();
const char* WINAPI U_GetEcnName(unsigned char ecnId);
*/
void WINAPI U_CheckUtilsThread(unsigned int threadId, const char* text);

void WINAPI U_GetCrashDescription(std::string& crashDescription, const struct _EXCEPTION_RECORD* exceptionRecord);

char* WINAPI U_IntToStr(int n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_UIntToStr(unsigned int n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_UInt64ToStr(unsigned __int64 n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_Int64ToStr(__int64 n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');

char* WINAPI U_UIntToStrPad(unsigned int n, char* num, unsigned int size, unsigned int totalLength, bool removeTrailingZeros, char del = '\0');
//char* WINAPI U_UIntToStrWithDelimiter(unsigned int n, char* num, unsigned int size, char delimiter, unsigned char decDigits = 0);
char* WINAPI U_UIntHexToStr(unsigned int n, char* num, unsigned int size, char del = '\0');
char* WINAPI U_UInt64HexToStr(unsigned __int64 n, char* num, unsigned int size, char del = '\0');

char* WINAPI U_IntToStrWithCommas(int n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_UIntToStrWithCommas(unsigned int n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_Int64ToStrWithCommas(__int64 n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_UInt64ToStrWithCommas(unsigned __int64 n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');

char* WINAPI U_UIntToStrPrepended(unsigned int n, char* num, unsigned int size, char prepend, char del = '\0');
char* WINAPI U_UInt64ToStrPrepended(unsigned __int64 n, char* num, unsigned int size, char prepend, char del = '\0');
char* WINAPI U_UIntHexToStrPrepended(unsigned int n, char* num, unsigned int size, char prepend, char del = '\0');
char* WINAPI U_UInt64HexToStrPrepended(unsigned __int64 n, char* num, unsigned int size, char prepend, char del = '\0');

char* WINAPI U_UShortToStr(unsigned short n, char* num, unsigned int size, char del = '\0');
char* WINAPI U_UShortHexToStr(unsigned short n, char* num, unsigned int size, char del = '\0');
char* WINAPI U_ShortToStr(short n, char* num, unsigned int size, char del = '\0');
char* WINAPI U_UShortToStrWithCommas(unsigned short n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');

char* WINAPI U_UCharToStr(unsigned char n, char* num, unsigned int size, char del = '\0');
char* WINAPI U_UCharHexToStr(unsigned char n, char* num, unsigned int size, char del = '\0');
char* WINAPI U_CharAsIntToStr(char n, char* num, unsigned int size, char del = '\0');

unsigned int WINAPI U_GetTimeTokensFromMillisecond(unsigned int currentMillisecond, unsigned int& hour, unsigned int& minute, unsigned int& second);
char* WINAPI U_FormatMillisecond(unsigned int millisecond, char* cursor, unsigned int buflen, char del = '\0', bool appendMillisecond = true);
char* WINAPI U_FormatSecond(unsigned int second, char* cursor, unsigned int buflen, char del = '\0');
char* WINAPI U_FormatTimeTokens(unsigned int hour, unsigned int minute, unsigned int second, char* cursor, unsigned int buflen, char del = '\0');
char* WINAPI U_FormatTimeTokensAndMillisecond(unsigned int hour, unsigned int minute, unsigned int second, unsigned int millisecond, char* cursor, unsigned int buflen, char del = '\0');
char* WINAPI U_FormatMinute(unsigned short minute, char* cursor, unsigned int buflen, char del = '\0');
unsigned short WINAPI U_StringToMinute(const char*& cursor, char del);

const char* WINAPI U_GetMonthName(unsigned short month);
void WINAPI U_GetDateTokens(unsigned int date, unsigned short& year, unsigned short& month, unsigned short& day);
unsigned int WINAPI U_CombineTokensIntoDate(unsigned short year, unsigned short month, unsigned short day);
char* WINAPI U_FormatDate(unsigned int date, char* cursor, unsigned int buflen, char del, bool monthName, bool fullYear);
void WINAPI U_FormatDateStr(unsigned int date, std::string& str, char del, bool monthName, bool fullYear);

char* WINAPI U_FormatDateTokens(unsigned short month, unsigned short day, unsigned short year, char* cursor, unsigned int buflen, char del, bool monthName, bool fullYear);
void WINAPI U_FormatDateTokensStr(unsigned short month, unsigned short day, unsigned short year, std::string& str, char del, bool monthName, bool fullYear);

void WINAPI U_GetDateTimeTokensDateOnly(unsigned int date, unsigned short& year, unsigned char& month, unsigned char& day);
void WINAPI U_GetDateTimeTokensTimeOnly(unsigned int time, unsigned char& hour, unsigned char& minute, unsigned char& second, unsigned short& millisecond);
void WINAPI U_GetDateTimeTokens(unsigned __int64 dateTime, unsigned short& year, unsigned char& month, unsigned char& day, unsigned char& hour, unsigned char& minute, unsigned char& second, unsigned short& millisecond);
unsigned __int64 WINAPI U_ConvertDateTimeTokensToDate(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char second, unsigned short millisecond);
void WINAPI U_AppendDateTime(std::string& str, const unsigned __int64& dateTime, bool timeOnly, bool appendMillisecond, char del, bool oneDigitLeftmost, bool monthName, bool fullYear);
void WINAPI U_AppendThreeCharDateToStr(std::string& text, const unsigned int& date, char del, bool monthName, bool fullYear);

int WINAPI U_GetLogPixelsY();

void WINAPI U_CalculateMaxDelay(unsigned int sentTime, unsigned int receivedTime, short& delay);

const OSVERSIONINFOEX& WINAPI U_GetOsVersionInfo();
const SYSTEM_INFO& WINAPI U_GetSystemInfo();
void WINAPI U_GetSystemInfoAsString(std::string& info);
void WINAPI U_GetOsVersionStr(std::string& os);
void WINAPI U_GetServicePackVersionStr(std::string& os);
void WINAPI U_GetProcessorArchitectureStr(std::string& info);
unsigned int WINAPI U_GetMemoryPageSize();
unsigned int WINAPI U_GetMemoryAllocationGranularity();
unsigned __int64 WINAPI U_GetPhysicalMemorySize();
unsigned int WINAPI U_GetProcessorCount();
void WINAPI U_GetActiveProcessorMask(std::string& info);

void WINAPI U_ReplaceSubstring(const char* original, const char* what, const char* with, std::string& result);

enum ClipboardError : unsigned char
{
	CLIPBOARD_OK,
	CLIPBOARD_CLOSE,
	CLIPBOARD_SETDATA,
	CLIPBOARD_EMPTY,
	CLIPBOARD_OPEN,
	CLIPBOARD_MEMORY,

	CLIPBOARD_COUNT
};

unsigned int WINAPI U_CopyStringToClipboard(const std::string& info, HWND owner, unsigned char* errorCode = NULL);
unsigned int WINAPI U_CopyClipboardToString(std::string& str, HWND owner, unsigned char* errorCode = NULL);
unsigned int WINAPI U_CopyClipboardToStringList(std::list<std::string>& stringList, HWND owner, unsigned int* emptyCount = NULL, unsigned char* errorCode = NULL);
unsigned int WINAPI U_CopyClipboardToStringMap(std::map<std::string, std::string>& stringMap, HWND owner, char delimiter, unsigned int* duplicateCount = NULL, unsigned int* emptyCount = NULL, unsigned char* errorCode = NULL);
bool WINAPI U_ReadFileToStringMap(const char* filePath, std::map<std::string, std::string>& stringMap, char delimiter, char commentChar, unsigned int* duplicateCount, unsigned int* emptyCount);

//COLORREF WINAPI U_GetOppositeBlacAndWhiteColor(COLORREF color);

void WINAPI U_ConvertValueToPrintableString(const BYTE* cursor, unsigned int length, std::string& result);
BYTE* WINAPI U_RestoreValueFromPrintable(const char* cursor, DWORD& length);

bool WINAPI U_EncryptString(bool useIp, const char* traderId, const std::string& text, std::string& encryptedText, std::string& errorMessage, std::string& errorTitle);
bool WINAPI U_DecryptString(bool useIp, const char* traderId, const std::string& encryptedText, std::string& text, std::string& errorMessage, std::string& errorTitle);

short WINAPI U_CompareUIntStrs(unsigned int str1, unsigned int str2);
short WINAPI U_CompareUInt64Strs(unsigned __int64 str1, unsigned __int64 str2);

unsigned int WINAPI U_GetUIntStrLength(unsigned int str);
unsigned int WINAPI U_GetUInt64StrLength(unsigned __int64 str);

const char* WINAPI U_GetArgLine();
const StringHashMap& WINAPI U_GetLineArgs();
void WINAPI U_Initialize(unsigned __int64 exeVersion, const char* argLine);
unsigned __int64 WINAPI U_GetExeVersion();

bool WINAPI U_PatternMatch(const char *str, const char *pattern);
bool WINAPI U_HasWildCards(const char *str);
void WINAPI U_BreakStringIntoTokensBy2Chars(const char* originalString, char c1, char c2, std::list<std::string>& tokenList);
void WINAPI U_CombineTokensIntoString(const char* insertion, const std::list<std::string>& tokenList, std::string& result);

void WINAPI U_TextBreakLines(const std::string& text, std::vector<std::string>& result);
unsigned int WINAPI U_TextBreakWords(HDC dc, const int width, const std::string& text, std::vector<std::string>& result, unsigned int& maxWidth);

bool WINAPI U_ReadFileToString(const char* filePath, std::string& str);
bool WINAPI U_WriteStringToFile(const char* filePath, const std::string& str);

void WINAPI U_ReplaceText(char*& what, const char* with);
const char* WINAPI U_StriStr(const char* str, const char* substr);//substr must be uppercase

#ifdef __cplusplus
}
#endif

struct lessUIntStr : public std::binary_function<unsigned int, unsigned int, bool>
{
	bool operator()(const unsigned int& p1, const unsigned int& p2) const
	{
		return U_CompareUIntStrs(p1, p2) < 0;
	}
};
