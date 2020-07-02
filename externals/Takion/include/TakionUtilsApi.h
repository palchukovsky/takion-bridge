#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef TU_EXPORTS
#define TU_API __declspec(dllexport)
#else
#define TU_API __declspec(dllimport)
#endif

#include <UtilsApi.h>
#include <ObserverApi.h>
#include <TakionMemoryApi.h>
#include <TakionLogApi.h>

//#define VERIFY_QUOTES
//#ifdef _DEBUG
//#define PENDING_SHARES_VALIDITY
//#define BP_VALIDITY
//#endif

#define FIRM_VALUES
//#define USE_THRESHOLD_INDICATOR_AS_UNSHORTABLE

//#define SEND_LOCATE_INFO

#ifdef FIRM_VALUES
#define FIRM_VALUES_ALWAYS
#endif

#if defined(T_RELEASED)// || defined(_DEBUG)
#define LOG_UPDATE_STOCK
#endif

const char* const TakionUtilsHeaderVersion = "1.0.1.213";

enum CustomMessageIds : unsigned short
{
	TM_CUSTOM_INTERNAL = 65500,
	TM_CUSTOM_EXTERNAL,
};

class TMsgCustom : public Message
{
public:
	unsigned short m_customId;
protected:
	TMsgCustom(unsigned short customId, unsigned short type, unsigned short length):Message(type, length), m_customId(customId){}
};

class TMsgCustomExternal : public TMsgCustom
{
protected:
	TMsgCustomExternal(unsigned short customId, unsigned short length):TMsgCustom(customId, TM_CUSTOM_EXTERNAL, length){}
};

class TMsgCustomInternal : public TMsgCustom
{
protected:
	TMsgCustomInternal(unsigned short customId, unsigned short length):TMsgCustom(customId, TM_CUSTOM_INTERNAL, length){}
};

class TU_API QuoteCondition
{
public:
	QuoteCondition(char id, const char* description, bool slowBid, bool slowAsk, bool closed = false):
		m_slowSide(slowBid ? slowAsk ? 3 : 1 : slowAsk ? 2 : 0),
		m_description(description),
		m_closed(closed)
	{
		*m_id = id;
		*(m_id + 1) = '\0';
	}
	char GetId() const{return *m_id;}
	const char* GetIdStr() const{return m_id;}
	bool isSlowBid() const{return (m_slowSide & 1) != 0;}
	bool isSlowAsk() const{return (m_slowSide & 2) != 0;}
	bool isSideSlow(unsigned char side) const{return (m_slowSide & side) == side;}
	bool isClosed() const{return m_closed;}
	const std::string& GetDescription() const{return m_description;}
protected:
	char m_id[2];
	unsigned char m_slowSide;
	bool m_closed;
	std::string m_description;
};

class Security;
class Account;
class Position;
class Order;


#ifdef __cplusplus
extern "C"
{
#endif

const unsigned int luldNum =	0x444C554C;//*(unsigned int*)"LULD";
const unsigned int lrpNum =		0x50524C;//*(unsigned int*)"LRP";
const unsigned int nysNum =		0x4553594E;//*(unsigned int*)"NYSE";
const unsigned int nysTopNum =	0x53594E;//*(unsigned int*)"NYS";
const unsigned int amexNum =	0x58454D41;//*(unsigned int*)"AMEX";
const unsigned int amexTopNum =	0x584D41;//*(unsigned int*)"AMX";
const unsigned int nsdqNum =	0x5144534E;//*(unsigned int*)"NSDQ";
const unsigned int arcaNum =	0x41435241;//*(unsigned int*)"ARCA";
const unsigned int batsNum =	0x53544142;//*(unsigned int*)"BATS";
const unsigned int batyNum =	0x59544142;//*(unsigned int*)"BATY";
const unsigned int edgxNum =	0x58474445;//*(unsigned int*)"EDGX";
const unsigned int edgaNum =	0x41474445;//*(unsigned int*)"EDGA";
const unsigned int nsxxNum =	0x5858534E;//*(unsigned int*)"NSXX";
const unsigned int nsxNum =		0x58534E;//*(unsigned int*)"NSX";
const unsigned int ubsNum =		0x534255;//*(unsigned int*)"UBS";
const unsigned int jpmNum =		0x4D504A;//*(unsigned int*)"JPM";
const unsigned int iexNum =		0x584549;//*(unsigned int*)"IEX";
const unsigned int itgNum =		0x475449;//*(unsigned int*)"ITG";
const unsigned int pdqNum =		0x514450;//*(unsigned int*)"PDQ";
const unsigned int daxxNum =	0x58584144;//*(unsigned int*)"DAXX";
const unsigned int qsmtNum =	0x544D5351;//*(unsigned int*)"QSMT";
const unsigned int flowNum =	0x574F4C46;//*(unsigned int*)"FLOW";
const unsigned int niteNum =	0x4554494E;//*(unsigned int*)"NITE";
const unsigned int otcbNum =	0x4243544F;//*(unsigned int*)"OTCB";
const unsigned int othrNum =	0x5248544F;//*(unsigned int*)"OTHR";
const unsigned short nysShortNum =	0x594E;//*(unsigned short*)"NY";
const unsigned short amexShortNum =	0x5841;//*(unsigned short*)"AX";
const unsigned short nsdqShortNum =	0x514E;//*(unsigned short*)"NQ";

#ifndef TAKION_NO_OPTIONS
const unsigned int boxNum =		0x584F42;//"BOX";
const unsigned int c2Num =		0x3243;//"C2";
const unsigned int iseNum =		0x455349;//"ISE";
const unsigned int gemNum =		0x4D4547;//"GEM";
#endif

enum MarketCategory : char
{
	MC_OTHR		= ' ',
	MC_AMEX		= 'A',
	MC_NYSE		= 'N',
	MC_ARCA		= 'P',
	MC_NSDQ_SELECT		= 'Q',
	MC_NSDQ_GLOBAL		= 'G',
	MC_NSDQ_CAPITAL		= 'S',
	MC_OTCB = 'U',
	MC_BATS = 'Z',
};

enum PrimaryExchange : char
{
	PE_OTHR		= ' ',
	PE_AMEX		= 'A',
	PE_NYSE		= 'N',
	PE_ARCA		= 'P',
	PE_NSDQ		= 'Q',
	PE_OTCB		= 'U',
	PE_BATS		= 'Z',
};

enum OrderExchangeEntitlements : unsigned char
{
	OEE_NSDQ,
	OEE_NYSE,
	OEE_ARCA,
	OEE_AMEX,
	OEE_BATS,
#ifndef TAKION_NO_OPTIONS
	OEE_OPRA,
#endif
	OEE_Count
};

enum MdEntitlements : unsigned char
{
	MDE_NSDQ,
	MDE_ARCA,
	MDE_BATS,
	MDE_BATY,
	MDE_EDGA,
	MDE_EDGX,
	MDE_UQDF,
	MDE_UTDF,
	MDE_CQS,
	MDE_CTS,
	MDE_NYSE,
	MDE_AMEX,
	MDE_OPRA,

	MDE_Count
};

enum MarketCategoryFilter : unsigned char
{
	MCF_AMEX,
	MCF_NYSE,
	MCF_ARCA,
	MCF_NSDQ_SELECT,
	MCF_NSDQ_GLOBAL,
	MCF_NSDQ_CAPITAL,

	MCF_OTHER,

	MCF_BATS,

	MCF_OTCB,

	MCF_COUNT,

	MCF_OPTION = MCF_COUNT,

	MCF_ALL_Count
};

enum NyseMarketCenter : unsigned char
{
	NYS_AMEX				= 'A' - 'A',
	NYS_NASDAQ_OMX_BX		= 'B' - 'A',
	NYS_NSE					= 'C' - 'A',
	NYS_FINRA				= 'D' - 'A',
	NYS_MarketIndependent	= 'E' - 'A',
	NYS_JEFF				= 'F' - 'A',
	NYS_GEM					= 'H' - 'A',
	NYS_ISE					= 'I' - 'A',
	NYS_EDGA				= 'J' - 'A',
	NYS_EDGX				= 'K' - 'A',
	NYS_CSE					= 'M' - 'A',
	NYS_NYSE				= 'N' - 'A',
	NYS_ARCA				= 'P' - 'A',
	NYS_NASDAQ_OMX			= 'Q' - 'A',
	NYS_OTCB				= 'U' - 'A',
	NYS_CBOE				= 'W' - 'A',
	NYS_NASDAQ_OMX_PHLX		= 'X' - 'A',
	NYS_BATS_Y				= 'Y' - 'A',
	NYS_BATS				= 'Z' - 'A',

	MC_COUNT_NYS
};

enum NasdaqMarketCenter : unsigned char
{
	NSDQ_AMEX				= 'A' - 'A',
	NSDQ_NASDAQ_OMX_BX		= 'B' - 'A',
	NSDQ_NSE				= 'C' - 'A',
	NSDQ_FINRA				= 'D' - 'A',
	NSDQ_MarketIndependent	= 'E' - 'A',
	NSDQ_JEFF				= 'F' - 'A',
	NSDQ_GEM				= 'H' - 'A',
	NSDQ_ISE				= 'I' - 'A',
	NSDQ_EDGA				= 'J' - 'A',
	NSDQ_EDGX				= 'K' - 'A',
	NSDQ_CSE				= 'M' - 'A',
	NSDQ_NYSE				= 'N' - 'A',
	NSDQ_ARCA				= 'P' - 'A',
	NSDQ_NASDAQ_OMX			= 'T' - 'A',
	ConsolidatedTapeSystem	= 'S' - 'A',
	NSDQ_CBOE				= 'W' - 'A',
	NSDQ_NASDAQ_OMX_PHLX	= 'X' - 'A',
	NSDQ_BATS_Y				= 'Y' - 'A',
	NSDQ_BATS				= 'Z' - 'A',
	MC_COUNT_NSDQ
};

const unsigned int AllMarketCenterFilter = (1 << NYS_AMEX)
	| (1 << NYS_NASDAQ_OMX_BX)
	| (1 << NYS_NSE)
	| (1 << NYS_FINRA)
//	| (1 << NYS_MarketIndependent)
	| (1 << NYS_JEFF)
	| (1 << NYS_GEM)
	| (1 << NYS_ISE)
	| (1 << NYS_EDGA)
	| (1 << NYS_EDGX)
	| (1 << NYS_CSE)
	| (1 << NYS_NYSE)
	| (1 << NYS_ARCA)
	| (1 << NYS_NASDAQ_OMX)
//	| (1 << ConsolidatedTapeSystem)
	| (1 << NYS_OTCB)
	| (1 << NYS_CBOE)
	| (1 << NYS_NASDAQ_OMX_PHLX)
	| (1 << NYS_BATS_Y)
	| (1 << NYS_BATS)
	| (1 << NSDQ_NASDAQ_OMX);

enum SecurityTypes : char
{
	STYPE_UNDEFINED					= '?',
	STYPE_ETF						= '@',
	STYPE_COMMON_STOCK				= 'A',
	STYPE_PREFERRED_STOCK			= 'B',
	STYPE_WARRANT					= 'C',
	STYPE_RIGHT						= 'D',
	STYPE_CORPORATE_BOND			= 'E',
	STYPE_TREASURY_BOND				= 'F',
	STYPE_STRUCTURED_PRODUCT		= 'G',
	STYPE_ADR_COMMON				= 'H',
	STYPE_ADR_PREFERRED				= 'I',
	STYPE_ADR_WARRANT				= 'J',
	STYPE_ADR_RIGHT					= 'K',
	STYPE_ADR_CORPORATE_BOND		= 'L',
	STYPE_NY_REGISTERED_SHARE		= 'M',
	STYPE_GLOBAL_REGISTERED_SHARE	= 'N',
	STYPE_INDEX						= 'O',
	STYPE_FUND						= 'P',
	STYPE_BASKET					= 'Q',
	STYPE_UNIT						= 'R',
	STYPE_LIQUIDATING_TRUST			= 'S',
	STYPE_UNKNOWN					= 'U',
};

enum StockFlags : unsigned char
{
	SF_BANKRUPTCY		= 0x01,
	SF_EX_DISTRIBUTION	= 0x02,
	SF_EX_RIGHTS		= 0x04,
	SF_EX_DIVIDEND		= 0x08,
	SF_SPECIAL_DIVIDEND	= 0x10,
	SF_STOCK_SPLIT		= 0x20,
	SF_RULE_19C3		= 0x40,
	SF_ITS_ELIGIBLE		= 0x80,
};
 
unsigned int WINAPI TU_GetMemoryUsage();//a number from 0 to 4. Set it in Takion.ini file, section [TakionSystem] entry TuMemoryUsage=0 (or 1, or 2, or 3, or 4)
const char* WINAPI TU_GetModuleVersionStr();
unsigned __int64 WINAPI TU_GetModuleVersionNum();
const char* WINAPI TU_GetHeaderVersion();
unsigned __int64 WINAPI TU_GetHeaderVersionNum();
const char* WINAPI TU_GetFilePathAndName();
const char* WINAPI TU_GetPlatform();
const char* WINAPI TU_GetFileDescription();
void WINAPI TU_GetDllBuildDescription(std::string& buildStr);
short WINAPI TU_GetQuoteDelay(unsigned int millisecond);

void WINAPI TU_SetLogFile(void* logFile);
void* WINAPI TU_GetLogFile();

enum TifType : unsigned char
{
//Order TIFS - match with FIX
	TIF_DAY	= '0',		//Day (or session)
//	TIF_GTC = '1',		//Good Till Cancel (GTC)
	TIF_OPG = '2',		//At the Opening (OPG)
	TIF_IOC = '3',		//Immediate Or Cancel (IOC)
	TIF_FOK = '4',		//Fill Or Kill (FOK)
	TIF_GTX = '5',		//Good Till Crossing (GTX)
	TIF_GTD = '6',		//Good Till Date (GTD)
	TIF_ATC = '7',		//At the Close
//Non FIX TIFs
//	GT_XPR = 'X',	// Express
//	GT_DAY_PLUS = 'P',	// Day Plus (Day+)	//-> Added 07/26/2004.
	TIF_LAST
};

bool WINAPI TU_GetTifAsString(std::string& text, unsigned char tifType, bool monitorTif, const char* millisecondStr, unsigned int tifMillisecond, bool showMillisecond, const char* unknown, bool unknownValue);

enum PegType : unsigned char
{
	PEG_NONE,
	PEG_PRIMARY,
	PEG_MIDPOINT,
	PEG_MARKET,

	PEG_TYPE_COUNT
};

bool WINAPI TU_GetPegTypeAsString(std::string& text, unsigned char pegType, const char* none, const char* unknown, bool unknownValue);

//unsigned int WINAPI TU_GetNyseMarketCenterName(unsigned char mc);
//unsigned int WINAPI TU_GetNasdaqMarketCenterName(unsigned char mc);
//const char* WINAPI TU_GetMarketCenterName(unsigned char mc);

//const char* const* WINAPI TU_GetEcnNames();
const char* WINAPI TU_GetEcnLongName(unsigned char ecnId);
unsigned int WINAPI TU_GetEcnNumericLongName(unsigned char ecnId);
const char* WINAPI TU_GetEcnShortName(unsigned char ecnId);
const char* WINAPI TU_GetEcnShortNameLowercase(unsigned char ecnId);
unsigned int WINAPI TU_GetEcnNumericShortName(unsigned char ecnId);
const char* WINAPI TU_GetEcnDestination(unsigned char ecnId);
unsigned int WINAPI TU_GetEcnNumericDestination(unsigned char ecnId);

unsigned int WINAPI TU_GetMarketCenterNumericLongName(unsigned char mc);
unsigned int WINAPI TU_GetMarketCenterNumericShortName(unsigned char mc);

const QuoteCondition* const* WINAPI TU_GetQuoteConditions(bool nasdaq);
const QuoteCondition* const* WINAPI TU_GetPackedQuoteConditions(bool nasdaq);
const QuoteCondition* WINAPI TU_GetQuoteCondition(char qc, bool nasdaq);
const bool* WINAPI TU_GetSlowQuoteConditions(bool nasdaq, bool bid);
bool WINAPI TU_IsSlowQuoteCondition(char condition, bool nasdaq, bool bid);

unsigned char WINAPI TU_CanContinueSwipingOnOrderError(unsigned char orderError);//0 severe error, 1 - mild error, 2 - no error (OE_OK).

enum CancelOrdersWhenFlatFlags
{
	COWF_CLOSING,
	COWF_OPENING,

	COWF_COUNT
};

unsigned int WINAPI TU_GetCancelOrdersWhenFlat();
void WINAPI TU_SetCancelOrdersWhenFlat(unsigned int cancelOrdersWhenFlat);
unsigned char WINAPI TU_CopyClipboardToString(std::string& str, HWND owner);
unsigned int WINAPI TU_CopyClipboardToStringList(std::list<std::string>& stringList, HWND owner);
unsigned int WINAPI TU_CopyClipboardToStringMap(std::map<std::string, std::string>& stringMap, HWND owner, char delimiter, unsigned int* duplicateCount = NULL);
void WINAPI TU_CopyStringToClipboard(std::string& info, HWND owner);

const char* WINAPI TU_GetMarketCategoryName(unsigned char marketCategory);
unsigned int WINAPI TU_GetPrimaryExchangeNameByExchangeEntitlementFlag(unsigned char exchangeEntitlementFlag);

bool WINAPI TU_IsCancelOversellInsteadOfResize();
void WINAPI TU_SetCancelOversellInsteadOfResize(bool cancel);

bool WINAPI TU_IsCancelOvershortInsteadOfResize();
void WINAPI TU_SetCancelOvershortInsteadOfResize(bool cancel);

//News Api
typedef bool (WINAPI* ApiIs)();
typedef Observable* (WINAPI* ApiGetObservable)();
typedef void (WINAPI* ApiVoidPtr)(void* voidPtr);
typedef void (WINAPI* ApiObservable)(Observable* observable);
typedef bool (WINAPI* ApiIsObservable)(Observable* observable);
typedef bool (WINAPI* ApiIsObservableConst)(const Observable* observable);
typedef bool (WINAPI* ApiIsObservableUInt)(const Observable* observable, unsigned int updateOrdinal);
typedef bool (WINAPI* ApiIsUInt)(unsigned int updateOrdinal);
typedef Observable* (WINAPI* ApiGetObservableUInt64)(const Observable* newsCollection, const unsigned __int64& symbol);
typedef Observable* (WINAPI* ApiGetObservableCharPtr)(const Observable* newsCollection, const char* symbol);
typedef Observable* (WINAPI* ApiGetObservableString)(const Observable* newsCollection, const std::string& symbol);
typedef bool (WINAPI* ApiIsLong)(LONG lCount);
typedef TakionIterator* (WINAPI* ApiCreateIterator)();

//Extension API
typedef void (WINAPI* ApiVoid)();
typedef unsigned int (WINAPI *ApiGetUInt)();
typedef unsigned short (WINAPI *ApiGetUShort)();
typedef unsigned __int64 (WINAPI *ApiGetUInt64)();
typedef const char* (WINAPI *ApiGetString)();
typedef const std::string* (WINAPI *ApiGetStdString)();
typedef void (WINAPI *ApiCharPtr)(const char* ptr);
typedef bool (WINAPI *ApiIsCharPtr)(const char* ptr);
typedef void (WINAPI* ApiFillString)(std::string& str);
typedef void (WINAPI* ApiUShortCWnd)(unsigned short, CWnd* takionExtensionWindow);
typedef void (WINAPI* ApiIntInt)(int, int);
typedef CWnd* (WINAPI* ApiCreteTool)(const char* id, const CBitmap* bitmap, unsigned int workspace, bool pinned);

typedef void (WINAPI* ApiUCharUCharString)(unsigned char ascii, unsigned char modifier, bool repeat, const char* commandName, unsigned int commandExtensionCode, unsigned int commandUserExtensionCode);
typedef void (WINAPI* ApiStringBoolBool)(const char* symbol, bool valid, bool fromKeyboard, unsigned int ordinal);
typedef void (WINAPI* ApiStringSecurityBoolUInt)(const char* symbol, const Security* security, bool wasLoaded, unsigned int ordinal);
typedef bool (WINAPI* ApiUIntBool)(unsigned int idleCount, bool takionIdleDone);
typedef void (WINAPI* ApiAccount)(Account* account);
typedef void (WINAPI* ApiBool)(bool);

typedef void (WINAPI *ApiUCharMessageBool)(unsigned char connectionType, const Message* message, bool outgoing);

//ExtensionApi
unsigned int WINAPI GetExtensionCode();//must exist and return 1
void WINAPI ExtensionInitialize();
void WINAPI ExtensionTerminate();
unsigned __int64 WINAPI GetExtensionVersion();
unsigned __int64 WINAPI GetUtilsVersion();
unsigned __int64 WINAPI GetUtilsHeaderVersion();
unsigned __int64 WINAPI GetTakionUtilsVersion();
unsigned __int64 WINAPI GetTakionUtilsHeaderVersion();
unsigned __int64 WINAPI GetTakionGuiVersion();
unsigned __int64 WINAPI GetTakionGuiHeaderVersion();
unsigned __int64 WINAPI GetTakionDataVersion();
unsigned __int64 WINAPI GetTakionDataHeaderVersion();
unsigned __int64 WINAPI GetTakionLogVersion();
unsigned __int64 WINAPI GetTakionLogHeaderVersion();
unsigned __int64 WINAPI GetObserverVersion();
unsigned __int64 WINAPI GetObserverHeaderVersion();
const char* WINAPI GetTakionExtensionDescription();
void WINAPI GetTakionExtensionMenu(std::string& menuStr);
void WINAPI ExecuteTakionCommand(unsigned short commandId, CWnd* takionExtensionWindow);
void WINAPI TakionMoveWindows(int dx, int dy);
void WINAPI KeyStrokeAndCommand(unsigned char ascii, unsigned char modifier, bool repeat, const char* commandName, unsigned int commandExtensionCode, unsigned int commandUserExtensionCode);//commandName can be NULL;
void WINAPI SymbolEnteredInMmBox(const char* symbol, bool valid, bool fromKeyboard, unsigned int ordinal);
void WINAPI SecurityRefreshed(const char* symbol, const Security* security, bool wasLoaded, unsigned int ordinal);//security can be NULL;
void WINAPI ActiveMmBoxChanged(const char* symbol, const Security* security, bool wasLoaded, unsigned int ordinal);//symbol and security can be NULL;
void WINAPI CurrentAccountSet(Account* account);
void WINAPI AppActivated(bool activated);
void WINAPI OpenLayout();
void WINAPI SaveLayout();
void WINAPI SaveLayoutAs();
void WINAPI RestoreLayout();
const char* WINAPI GetLayoutFilePath();//returns NULL if does not exist
bool WINAPI MainThreadIdleState(unsigned int idleCount, bool takionIdleDone);
void WINAPI MainThreadAvailableDataProcessed();
void WINAPI MessageReport(unsigned char connectionType, const Message* message, bool outgoing);

///////////////

#ifdef __cplusplus
}
#endif

class ConstraintBase
{
public:
	ConstraintBase(bool simulation, unsigned char upper = 2)://0 - lower, 1 - upper, 2 - upper with 0 as no constraint
		m_simulation(simulation),
		m_upper(upper),
		m_custom(false)
	{
	}
	virtual ~ConstraintBase(){}
	unsigned char GetUpper() const{return m_upper;}
	bool isCustom() const{return m_custom;}
	void SetCustom(bool custom){m_custom = custom;}
	bool isSimulation() const{return m_simulation;}
	void SetSimulation(bool simulation){m_simulation = simulation;}
	virtual bool isCustomEqual(const ConstraintBase& other) const{return m_custom == other.m_custom;}
	virtual void SetCustomEqual(const ConstraintBase& other){m_custom = other.m_custom;}
	bool operator==(const ConstraintBase& other) const
	{
		return m_custom == other.m_custom;
	}
	ConstraintBase& operator=(const ConstraintBase& other)
	{
		m_custom = other.m_custom;
		m_simulation = other.m_simulation;
		return *this;
	}
	virtual bool isEqual(const ConstraintBase& other) const
	{
		return m_custom == other.m_custom;
	}
	virtual void SetEqual(const ConstraintBase& other)
	{
		m_custom = other.m_custom;//SetCustomEqual(other);
	}
	virtual void SetCustomZero(){m_custom = false;}
	virtual bool isCustomZero() const
	{
		return !m_custom;
	}
	virtual void SetZero(){m_custom = false;}
	virtual bool isZero() const{return !m_custom;}
	virtual bool HasValue() const{return m_upper != 2;}
protected:
	bool m_simulation;
	const unsigned char m_upper;
	bool m_custom;
};

template<class T>
class Constraint : public ConstraintBase
{
public:
	Constraint(const T& value, const T& zeroValue, bool simulation, unsigned char upper = 2):ConstraintBase(simulation, upper),m_value(value),m_customValue(value),m_zeroValue(zeroValue){}
	const T& GetValue() const{return m_value;}
	void SetValue(const T& value){m_value = value;}
	const T& GetCurrentValue() const{return m_custom && (m_simulation || (m_upper == 2 ? m_customValue < m_value && m_customValue != m_zeroValue || m_value == m_zeroValue : m_upper == 1 ? m_customValue < m_value : m_value < m_customValue)) ? m_customValue : m_value;}
	const T& GetCurrentValueLive() const{return m_custom && (m_upper == 2 ? m_customValue < m_value && m_customValue != m_zeroValue || m_value == m_zeroValue : m_upper == 1 ? m_customValue < m_value : m_value < m_customValue) ? m_customValue : m_value;}
	const T& GetCheckedValue() const{return m_custom ? m_customValue : m_value;}
	const T& GetCustomValue() const{return m_customValue;}
	T& GetCustomValue(){return m_customValue;}
	void SetCustomValue(const T& value){m_customValue = value;}
	void SetCustomValue(const T& value, bool custom){m_customValue = value; m_custom = custom;}
	virtual bool isCustomEqual(const ConstraintBase& other) const{return ConstraintBase::isCustomEqual(other) && m_customValue == ((const Constraint&)other).m_customValue;}
	virtual void SetCustomEqual(const ConstraintBase& other){ConstraintBase::SetCustomEqual(other); m_customValue = ((const Constraint&)other).m_customValue;}
	bool operator==(const Constraint& other) const
	{
		return ConstraintBase::operator==(other) && m_customValue == other.m_customValue;
	}
	Constraint& operator=(const Constraint& other)
	{
		ConstraintBase::operator=(other);
		m_value = other.m_value;
		m_customValue = other.m_customValue;
		return *this;
	}
	virtual bool isEqual(const ConstraintBase& other) const
	{
		if(!ConstraintBase::isEqual(other))
		{
			return false;
		}
		else
		{
			const Constraint& otherConstraint = (const Constraint&)other;
			return m_value == otherConstraint.m_value && m_customValue == otherConstraint.m_customValue;
		}
	}
	virtual void SetEqual(const ConstraintBase& other)
	{
		ConstraintBase::SetEqual(other);
//		SetCustomEqual(other);
		const Constraint& otherConstraint = (const Constraint&)other;
		m_value = otherConstraint.m_value;
		m_customValue = otherConstraint.m_customValue;
	}
	virtual void SetZero()
	{
		ConstraintBase::SetZero();
		m_value = m_customValue = m_zeroValue;
	}
	virtual bool isZero() const{return ConstraintBase::isZero() && m_value == m_zeroValue && m_customValue == m_zeroValue;}

	virtual void SetCustomZero()
	{
		ConstraintBase::SetCustomZero();
		m_customValue = m_zeroValue;
	}
	virtual bool isCustomZero() const
	{
		return m_customValue == m_zeroValue;
	}

	virtual bool HasValue() const{return ConstraintBase::HasValue() || m_value != m_zeroValue;}
	const T& GetZeroValue() const{return m_zeroValue;}
protected:
	T m_value;
	T m_customValue;
	const T m_zeroValue;
};
/*
template<class Comparable>
class Comparable
{
public:
	virtual ~Comparable(){}
	virtual bool operator<(const Comparable& other) const = 0;
	virtual bool operator==(const Comparable& other) const{return !operator<(other) && !(other < (*this));}
	bool operator!=(const Comparable& other) const{return !operator==(other);}
	bool operator>=(const Comparable& other) const{return !operator<(other);}
	bool operator<=(const Comparable& other) const{return operator<(other) || operator==(other);}
	bool operator>(const Comparable& other) const{return operator<(other) || operator==(other);}
};
*/

template<class D, class F, F N, unsigned char DEC>
class Monetary
{
public:
	typedef D DollarType;
	typedef F FractionType;
	static const F divider = N;//10000;
	static const unsigned char decDigits = DEC;
	void SetValue(const Monetary& other){operator=(other);}
	void SetValue(const D& dollars, const F& dollarFraction){m_dollars = dollars; m_dollarFraction = dollarFraction;}
	bool operator<(const D& value) const
	{
		return m_dollars < value || m_dollars == value && m_dollarFraction < 0;
	}
	bool operator<=(const D& value) const
	{
		return m_dollars < value || m_dollars == value && m_dollarFraction <= 0;
	}
	bool operator==(const D& value) const{return m_dollars == value && !m_dollarFraction;}
	bool operator!=(const D& value) const{return !operator==(value);}
	bool operator>=(const D& value) const{return !operator<(value);}
	bool operator>(const D& value) const{return !operator<=(value);}

	bool operator<(const Monetary& other) const
	{
		return m_dollars < other.m_dollars || m_dollars == other.m_dollars && m_dollarFraction < other.m_dollarFraction;
	}
	bool operator<=(const Monetary& other) const
	{
		return m_dollars < other.m_dollars || m_dollars == other.m_dollars && m_dollarFraction <= other.m_dollarFraction;
	}
	bool operator==(const Monetary& other) const{return m_dollars == other.m_dollars && m_dollarFraction == other.m_dollarFraction;}
	bool operator!=(const Monetary& other) const{return !operator==(other);}
	bool operator>=(const Monetary& other) const{return !operator<(other);}
	bool operator>(const Monetary& other) const{return !operator<=(other);}
	bool operator!() const{return isZero();}
	DollarType GetDollars() const{return m_dollars;}
	FractionType GetDollarFraction() const{return m_dollarFraction;}
	const DollarType& GetDollarsRef() const{return m_dollars;}
	const FractionType& GetDollarFractionRef() const{return m_dollarFraction;}
	bool isPositive() const{return m_dollars > 0 || m_dollarFraction > 0;}
	bool isNegative() const{return m_dollars < 0 || m_dollarFraction < 0;}
	bool isZero() const{return !m_dollars && !m_dollarFraction;}
	void SetZero(){m_dollars = m_dollarFraction = 0;}
//	operator double() const{return (double)m_dollars + (double)m_dollarFraction / divider;}
	double toDouble() const{return (double)m_dollars + (double)m_dollarFraction / divider;}
protected:
	explicit Monetary(const D& dollars = 0, const F& dollarFraction = 0):
		m_dollars(dollars),
		m_dollarFraction(dollarFraction)
	{
	}
	D m_dollars;
	F m_dollarFraction;
};

class Price;
class SignedPrice;

//http://www.zeuscmd.com/tutorials/cplusplus/53-OperatorOverloading.php
class TU_API Money : public Monetary<__int64, short, 10000, 4>// : public Comparable<Money>
{
public:
	Money():Monetary(0, 0){}
	Money(const __int64& dollars, const short& dollarFraction):Monetary(dollars, dollarFraction){}
	explicit Money(const Price& price);
	explicit Money(const SignedPrice& price);
	explicit Money(const unsigned int& compactPrice):Monetary(compactPrice >> 14, compactPrice & 0x3FFF){}
	operator Price() const;
	operator SignedPrice() const;
	void SetCompactMoney(const unsigned int& compactPrice){m_dollars = compactPrice >> 14; m_dollarFraction = compactPrice & 0x3FFF;}
	bool Round(unsigned int to, short direction);
	const Money& GetMoneyValue() const{return *this;}
	Money GetPercentChange(const Money& change) const;
	void Negate(){m_dollars = -m_dollars; m_dollarFraction = -m_dollarFraction;}
	Money operator-() const
	{
		return Money(-m_dollars, -m_dollarFraction);
	}
	Money& operator+=(const Money& other)
	{
		m_dollars += other.m_dollars;
		m_dollarFraction += other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Money& operator-=(const Money& other)
	{
		m_dollars -= other.m_dollars;
		m_dollarFraction -= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Money& operator*=(__int64 quantity)
	{
		m_dollars *= quantity;
		quantity *= m_dollarFraction;
		__int64 additionalDollars = quantity / divider;
		if(additionalDollars)
		{
			m_dollars += additionalDollars;
			m_dollarFraction = (short)(quantity - divider * additionalDollars);
		}
		else
		{
			m_dollarFraction = (short)quantity;
		}
		return *this;
	}
	Money& operator/=(__int64 quantity);
	Money operator+(const Money& other) const{return Money(*this) += other;}
	Money operator-(const Money& other) const{return Money(*this) -= other;}
	Money operator+(const SignedPrice& other) const{return Money(other) += *this;}
	Money operator-(const SignedPrice& other) const{return Money(*this) -= Money(other);}
	Money operator+(const Price& other) const{return Money(other) += *this;}
	Money operator-(const Price& other) const{return Money(*this) -= Money(other);}
	Money operator*(__int64 quantity) const{return Money(*this) *= quantity;}
	Money operator/(__int64 quantity) const{return Money(*this) /= quantity;}
	int operator/(const Money& other) const;
	void Canonicalize();
	size_t GetHashValue() const{return (size_t)(m_dollars << 16) | m_dollarFraction;}
};

class TU_API SignedPrice : public Monetary<int, int, 1000000000, 9>// : public Comparable<Price>
{
public:
	SignedPrice():Monetary(0, 0){}
	SignedPrice(const int& dollars, const int& dollarFraction):Monetary(dollars, dollarFraction){}
	explicit SignedPrice(const Price& price);
	explicit SignedPrice(const Money& money);
	explicit SignedPrice(const unsigned int& compactPrice):Monetary(compactPrice >> 14, (compactPrice & 0x3FFF) * (divider / 10000)){}
	explicit SignedPrice(const int& compactPrice):Monetary(compactPrice < 0 ? -compactPrice >> 14 : compactPrice >> 14, (compactPrice < 0 ? -compactPrice & 0x3FFF : compactPrice & 0x3FFF) * (divider / 10000))
	{
		if(compactPrice < 0)
		{
			m_dollars = -m_dollars;
			m_dollarFraction = -m_dollarFraction;
		}
	}

	operator Price() const;
	operator Money() const{return Money(*this);}
	const SignedPrice& GetSignedPriceValue() const{return *this;}
	SignedPrice GetPercentChange(const SignedPrice& change) const;
	void SetCompactPrice(const int& compactPrice)
	{
		if(compactPrice < 0)
		{
			m_dollars = -(-compactPrice >> 14);
			m_dollarFraction = -((-compactPrice & 0x3FFF) * (divider / 10000));
		}
		else
		{
			m_dollars = compactPrice >> 14;
			m_dollarFraction = (compactPrice & 0x3FFF) * (divider / 10000);
		}
	}
	unsigned int GetUIntCompactPrice() const{return (m_dollars << 14) | (m_dollarFraction / (divider / 10000));}
	int GetIntCompactPrice() const
	{
		return isNegative() ? -((-m_dollars << 14) | (-m_dollarFraction / (divider / 10000))):
			(m_dollars << 14) | (m_dollarFraction / (divider / 10000));
	}
	void Negate(){m_dollars = -m_dollars; m_dollarFraction = -m_dollarFraction;}
	SignedPrice operator-() const
	{
		return SignedPrice(-m_dollars, -m_dollarFraction);
	}
	bool Round(unsigned int to, short direction);
	SignedPrice& operator+=(const SignedPrice& other)
	{
		m_dollars += other.m_dollars;
		m_dollarFraction += other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPrice& operator-=(const SignedPrice& other)
	{
		m_dollars -= other.m_dollars;
		m_dollarFraction -= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPrice operator+(const SignedPrice& other) const{return SignedPrice(*this) += other;}
	SignedPrice operator-(const SignedPrice& other) const{return SignedPrice(*this) -= other;}
	SignedPrice operator+(const Price& other) const{return SignedPrice(other) += *this;}
	SignedPrice operator-(const Price& other) const{return SignedPrice(*this) -= SignedPrice(other);}
	SignedPrice operator+(const Money& other) const{return SignedPrice(other) += *this;}
	SignedPrice operator-(const Money& other) const{return SignedPrice(*this) -= SignedPrice(other);}
	bool isSamePrice(const SignedPrice& other) const{return operator==(other);}
	bool isLessPrice(const SignedPrice& other) const{return operator<(other);}
	bool isGreaterPrice(const SignedPrice& other) const{return !operator<=(other);}
	Money operator*(__int64 quantity) const;
	Money operator/(__int64 quantity) const;
	void Canonicalize();
	size_t GetHashValue() const{return ((size_t)m_dollars << 16) | (m_dollarFraction >> 16);}
	SignedPrice ConvertToServerFormat() const
	{
		if(isNegative() && m_dollarFraction)
		{
			return SignedPrice(m_dollars - 1, divider + m_dollarFraction);
		}
		else
		{
			return *this;
		}
	}
};

class TU_API Price : public Monetary<unsigned int, unsigned int, 1000000000, 9>// : public Comparable<Price>
{
public:
	Price():Monetary(0, 0){}
	Price(const unsigned int& dollars, const unsigned int& dollarFraction):Monetary(dollars, dollarFraction){}
	explicit Price(const SignedPrice& other):Monetary(other.isNegative() ? 0 : other.GetDollars(), other.isNegative() ? 0 : other.GetDollarFraction()){}
	explicit Price(const Money& money);
	explicit Price(const unsigned __int64& price):Monetary((unsigned int)(price >> 32), (unsigned int)(price & 0xFFFFFFFF)){}
	explicit Price(const unsigned int& compactPrice):Monetary(compactPrice >> 14, (compactPrice & 0x3FFF) * (divider / 10000)){}

	operator SignedPrice() const{return SignedPrice(*this);}
	operator Money() const{return Money(*this);}

	bool Round(unsigned int to, short direction);
	unsigned __int64 GetPriceAsUInt64() const{return (unsigned __int64)m_dollars << 32 | m_dollarFraction;}
	void SetPriceAsUInt64(const unsigned __int64& price){m_dollars = price >> 32; m_dollarFraction = price & 0xFFFFFFFF;}

	void SetCompactPrice(const unsigned int& compactPrice){m_dollars = compactPrice >> 14; m_dollarFraction = (compactPrice & 0x3FFF) * (divider / 10000);}
	unsigned int GetCompactPrice() const{return (m_dollars << 14) | (m_dollarFraction / (divider / 10000));}
	SignedPrice operator-() const
	{
		return SignedPrice(-(int)m_dollars, -(int)m_dollarFraction);
	}
	Price& operator+=(const Price& other)
	{
		m_dollars += other.m_dollars;
		m_dollarFraction += other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Price& operator-=(const Price& other)
	{
		if(operator<(other))
		{
			SetZero();
		}
		else
		{
			m_dollars -= other.m_dollars;
			if(m_dollarFraction < other.m_dollarFraction)
			{
				--m_dollars;
				m_dollarFraction = divider - (other.m_dollarFraction - m_dollarFraction);
			}
			else
			{
				m_dollarFraction -= other.m_dollarFraction;
			}
		}
		Canonicalize();
		return *this;
	}
	Price& operator+=(const SignedPrice& other)
	{
		if(other.isNegative())
		{
			return operator-=(Price(-other.GetDollars(), -other.GetDollarFraction()));
		}
		else
		{
			return operator+=(Price(other.GetDollars(), other.GetDollarFraction()));
		}
	}
	Price& operator-=(const SignedPrice& other)
	{
		if(other.isNegative())
		{
			return operator+=(Price(-other.GetDollars(), -other.GetDollarFraction()));
		}
		else
		{
			return operator-=(Price(other.GetDollars(), other.GetDollarFraction()));
		}
	}
	const Price& GetPriceValue() const{return *this;}
	SignedPrice GetPercentChange(const SignedPrice& change) const;
	Price GetPercentChange(const Price& change) const;
	Price operator+(const Price& other) const{return Price(*this) += other;}
	SignedPrice operator-(const Price& other) const{return SignedPrice(*this) -= SignedPrice(other);}
//	Price operator-(const Price& other) const{return Price(*this) -= other;}
	SignedPrice operator+(const SignedPrice& other) const{return SignedPrice(*this) += other;}
	SignedPrice operator-(const SignedPrice& other) const{return SignedPrice(*this) -= other;}
	SignedPrice operator+(const Money& other) const{return SignedPrice(*this) += SignedPrice(other);}
	SignedPrice operator-(const Money& other) const{return SignedPrice(*this) -= SignedPrice(other);}
	bool isSamePrice(const Price& other) const{return operator==(other);}
	bool isLessPrice(const Price& other) const{return operator<(other);}
	bool isGreaterPrice(const Price& other) const{return !operator<=(other);}
	void SetUInt64Price(const unsigned __int64& price){*(unsigned __int64*)&m_dollars = price;}
	Money operator*(__int64 quantity) const;
	Money operator/(__int64 quantity) const;
	Price operator*(const Price& multiplier) const;
	void Canonicalize();
	size_t GetHashValue() const{return ((size_t)m_dollars << 16) | (m_dollarFraction >> 16);}
};

template<> struct std::make_signed<Money>{typedef Money type;};
template<> struct std::make_signed<SignedPrice>{typedef SignedPrice type;};
template<> struct std::make_signed<Price>{typedef SignedPrice type;};
template<> struct std::make_unsigned<Money>{typedef Money type;};
template<> struct std::make_unsigned<SignedPrice>{typedef Price type;};
template<> struct std::make_unsigned<Price>{typedef Price type;};

class TU_API MoneyQuantity : public Money
{
public:
	MoneyQuantity(const __int64& dollars, const short& dollarFraction, const int& quantity):
		Money(dollars, dollarFraction),
		m_quantity(quantity)
	{
	}
	MoneyQuantity(const Money& money, const int& quantity):Money(money),m_quantity(quantity){}
	MoneyQuantity():m_quantity(0){}
	const int& GetQuantity() const{return m_quantity;}
	void SetQuantity(const int& quantity){m_quantity = quantity;}
	void IncrementQuantity(const int& quantity){m_quantity += quantity;}
	void DecrementQuantity(const int& quantity){m_quantity -= quantity;}
	void SetValues(const __int64& dollars, const short& dollarFraction, const int& quantity)
	{
		SetValue(dollars, dollarFraction);
		m_quantity = quantity;
	}
	bool SameQuantity(const MoneyQuantity& other) const{return m_quantity == other.m_quantity;}
protected:
	int m_quantity;
};

class TU_API PriceQuantity : public Price
{
public:
	PriceQuantity(const unsigned int& dollars, const unsigned int& dollarFraction, const unsigned int& quantity):
		Price(dollars, dollarFraction),
		m_quantity(quantity)
	{
	}
	PriceQuantity(const Price& price, const unsigned int& quantity):Price(price),m_quantity(quantity){}
	PriceQuantity():m_quantity(0){}
	const unsigned int& GetQuantity() const{return m_quantity;}
	void SetQuantity(const unsigned int& quantity){m_quantity = quantity;}
	void IncrementQuantity(const unsigned int& quantity){m_quantity += quantity;}
	bool DecrementQuantity(const unsigned int& quantity)
	{
		if(m_quantity > quantity)
		{
			m_quantity -= quantity;
			return true;
		}
		else
		{
			m_quantity = 0;
			return false;
		}
	}
	void SetValues(const unsigned int& dollars, const unsigned int& dollarFraction, const unsigned int& quantity)
	{
		SetValue(dollars, dollarFraction);
		m_quantity = quantity;
	}
	bool SameQuantity(const PriceQuantity& other) const{return m_quantity == other.m_quantity;}
protected:
	unsigned int m_quantity;
};

#ifdef __cplusplus
extern "C"
{
#endif

const SignedPrice& WINAPI TU_GetSignedPriceZero();
const Price& WINAPI TU_GetPriceZero();
const PriceQuantity& WINAPI TU_GetPriceQuantityZero();
const Money& WINAPI TU_GetMoneyZero();
const MoneyQuantity& WINAPI TU_GetMoneyQuantityZero();

const SignedPrice& WINAPI TU_GetSignedPriceOnePenny();
const Price& WINAPI TU_GetPriceOnePenny();

unsigned char WINAPI TU_GetTradeLevel1FromCompactPrice(unsigned int price, unsigned int bid, unsigned int ask);

void WINAPI TU_CompactPriceToStr(std::string& str, unsigned int compactPrice, unsigned char decDigits, bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI TU_CompactSignedPriceToStr(std::string& str, int compactPrice, unsigned char decDigits, bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI TU_PriceToStr(std::string& str, const Price& price, unsigned char decDigits, bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI TU_SignedPriceToStr(std::string& str, const SignedPrice& price, unsigned char decDigits, bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI TU_MoneyToStr(std::string& str, const Money& money, unsigned char decDigits, bool comma = true, char del = '\0', bool removeTrailingZeros = false);

void WINAPI TU_StrToPrice(Price& price, const char*& cursor, unsigned char decDigits, char del = '\0');
void WINAPI TU_StrToSignedPrice(SignedPrice& price, const char*& cursor, unsigned char decDigits, char del = '\0');
void WINAPI TU_StrToMoney(Money& money, const char*& cursor, unsigned char decDigits, char del = '\0');

void WINAPI TU_DoubleToPrice(Price& price, double value, unsigned char decDigits);
void WINAPI TU_DoubleToSignedPrice(SignedPrice& price, double value, unsigned char decDigits);
void WINAPI TU_DoubleToMoney(Money& money, double value, unsigned char decDigits);

double WINAPI TU_PriceToDouble(const Price& price);
double WINAPI TU_SignedPriceToDouble(const SignedPrice& price);
double WINAPI TU_MoneyToDouble(const Money& money);

#ifdef __cplusplus
}
#endif

class TU_API DelayedPriceQuantity : public PriceQuantity
{
public:
	virtual unsigned int GetMmid() const{return 0;}
	virtual unsigned short GetShortMmid() const{return 0;}
	unsigned int GetMillisecond() const{return m_millisecond;}
	short GetDelay() const{return m_delay;}
	bool isLessMillisecond(const DelayedPriceQuantity& other) const{return m_millisecond < other.m_millisecond;}
	bool isHistorical() const{return m_historical;}
	void SetHistorical(){m_historical = true;}
	void SetValues(unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned int millisecond, short delay, bool historical)
	{
		PriceQuantity::SetValues(dollars, dollarFraction, quantity);
		m_millisecond = millisecond;
		m_delay = delay;
		m_historical = historical;
	}
protected:
	DelayedPriceQuantity(unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned int millisecond, short delay):
		PriceQuantity(dollars, dollarFraction, quantity),
		m_millisecond(millisecond),
		m_delay(delay),
		m_historical(false)
	{}
	DelayedPriceQuantity(const Price& price, unsigned int quantity, unsigned int millisecond, short delay):
		PriceQuantity(price, quantity),
		m_millisecond(millisecond),
		m_delay(delay),
		m_historical(false)
	{}
	DelayedPriceQuantity():m_millisecond(0),m_delay(0),m_historical(false){}
	unsigned int m_millisecond;
	short m_delay;
	bool m_historical;
};

enum EcnBookId : unsigned char
{
	BOOK_MM_NSDQ,
	ECNBOOK_NSDQ = 1,
	ECNBOOK_ARCA,
	ECNBOOK_BATS,
	ECNBOOK_EDGA,
	ECNBOOK_EDGX,
	BOOK_LEVEL2,
	ECNBOOK_NYS,
	ECNBOOK_BATY,
	ECNBOOK_AMEX,
	ECNBOOK_NSX,
//	ECNBOOK_NQBX,
//	ECNBOOK_CBSX,
	ECNBOOK_FLOW,

	BOOK_MM_ARCA,
	BOOK_MM_BATS,
	BOOK_MM_BATY,
	BOOK_MM_NSX,

	ECNBOOK_COUNT,

	AllBooks = 0xff
};

class Quote;
//Used for remembering quotes that we already traded with
class TU_API TradedQuote : public PriceQuantity
{
public:
	TradedQuote(EcnBookId bookId, unsigned int mmid, unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned int millisecond):
		PriceQuantity(dollars, dollarFraction, quantity),
		m_mmid(mmid),
		m_millisecond(millisecond),
		m_bookId(bookId)
	{}
	TradedQuote(EcnBookId bookId, unsigned int mmid, const Price& price, unsigned int quantity, unsigned int millisecond, short delay):
		PriceQuantity(price, quantity),
		m_mmid(mmid),
		m_millisecond(millisecond),
		m_bookId(bookId)
	{}
	TradedQuote():m_mmid(0),m_millisecond(0),m_bookId(AllBooks){}
	unsigned int GetMmid() const{return m_mmid;}
	unsigned int GetMillisecond() const{return m_millisecond;}
	EcnBookId GetBookId() const{return m_bookId;}
	bool isLessMillisecond(const TradedQuote& other) const{return m_millisecond < other.m_millisecond;}
	bool operator<(const TradedQuote& other) const{return Price::operator<(other) || Price::operator==(other) && (m_mmid < other.m_mmid || m_mmid == other.m_mmid && m_bookId < other.m_bookId);}

	void SetParams(const Quote* quote);
	void SetMillisecond(unsigned int millisecond){m_millisecond = millisecond;}
protected:
	unsigned int m_mmid;
	unsigned int m_millisecond;
	EcnBookId m_bookId;
};

template<> AFX_INLINE UINT AFXAPI HashKey<Money>(Money key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<Price>(Price key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<TradedQuote>(TradedQuote key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<SignedPrice>(SignedPrice key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const Money&>(const Money& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const Price&>(const Price& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const TradedQuote&>(const TradedQuote& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const SignedPrice&>(const SignedPrice& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<Money&>(Money& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<Price&>(Price& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<TradedQuote&>(TradedQuote& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<SignedPrice&>(SignedPrice& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}
/*
template<> AFX_INLINE UINT AFXAPI HashKey<const std::string>(const std::string& key)
{
	return U_StringHash(key);
}

template<> AFX_INLINE UINT AFXAPI HashKey<std::string>(const std::string& key)
{
	return U_StringHash(key);
}
*/
//using std::hash_value;

template<> inline size_t std::hash_value<Money>(const Money& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value<Price>(const Price& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value<TradedQuote>(const TradedQuote& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value<SignedPrice>(const SignedPrice& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

enum TradeLevel1 : unsigned char
{
	TL1_LESS_BID,
	TL1_EQUAL_BID,
	TL1_BETWEEN_BIDASK,
	TL1_EQUAL_ASK,
	TL1_GREATER_ASK,
};

class TU_API Trade : public DelayedPriceQuantity
{
public:
	unsigned char GetSource() const{return m_source;}
	unsigned char GetLevel1() const{return m_level1;}
//	virtual unsigned int GetMmid() const{return 0;}
	virtual char GetLabel() const{return '\0';}
	virtual bool isPrint() const{return false;}
	virtual unsigned char GetSide() const{return 0;}//0 - unknown, 1 - buy, 2 - sell
	virtual bool isHidden() const{return false;}
	virtual char GetSaleCondition1() const{return '\0';}
	virtual char GetSaleCondition2() const{return '\0';}
	virtual char GetSaleCondition3() const{return '\0';}
	virtual char GetSaleCondition4() const{return '\0';}
	virtual char GetSaleCondition(unsigned int i) const{return '\0';}
	virtual bool isOddLot() const{return false;}
	bool operator<(const Trade& other) const
	{
		return m_millisecond > other.m_millisecond || 
			m_millisecond == other.m_millisecond && (isPrint() == other.isPrint() ? m_source < other.m_source : !isPrint());
	}
	bool isTradeLess(const Trade& other) const
	{
		if(operator<(other))return true;
		if(other < *this)return false;

		if(m_historical != other.m_historical)return !m_historical;

		if(m_delay < other.m_delay)return false;
		if(other.m_delay < m_delay)return true;

		if(isHidden() != other.isHidden())return isHidden(); 

//		if(m_source < other.m_source)return true;//done in operator<
//		if(other.m_source < m_source)return false;

		if(GetMmid() < other.GetMmid())return true;
		if(other.GetMmid() < GetMmid())return false;

		if(GetSide() < other.GetSide())return true;
		if(other.GetSide() < GetSide())return false;

		if(m_quantity < other.m_quantity)return true;
		if(other.m_quantity < m_quantity)return false;

		if(isLessPrice(other))return true;
		if(other.isLessPrice(*this))return false;

		if(m_level1 < other.m_level1)return true;
		if(other.m_level1 < m_level1)return false;

		if(isPrint())
		{
			if(GetSaleCondition1() < other.GetSaleCondition1())return true;
			if(other.GetSaleCondition1() < GetSaleCondition1())return false;
			if(GetSaleCondition2() < other.GetSaleCondition2())return true;
			if(other.GetSaleCondition2() < GetSaleCondition2())return false;
			if(GetSaleCondition3() < other.GetSaleCondition3())return true;
			if(other.GetSaleCondition3() < GetSaleCondition3())return false;
			if(GetSaleCondition4() < other.GetSaleCondition4())return true;
			if(other.GetSaleCondition4() < GetSaleCondition4())return false;
		}
		return false;
	}
	void SetValues(unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source, unsigned char level1, unsigned int millisecond, short delay, bool historical)
	{
		DelayedPriceQuantity::SetValues(dollars, dollarFraction, quantity, millisecond, delay, historical);
		m_source = source;
		m_level1 = level1;
	}
protected:
	Trade(unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source, unsigned char level1, unsigned int millisecond, short delay):// = 0xFFFF):
		DelayedPriceQuantity(dollars, dollarFraction, quantity, millisecond, delay),
		m_source(source),
		m_level1(level1)
		{}
	Trade(const Price& price, unsigned int quantity, unsigned char source, unsigned char level1, unsigned int millisecond, short delay):// = 0xFFFF):
		DelayedPriceQuantity(price, quantity, millisecond, delay),
		m_source(source),
		m_level1(level1)
		{}
	Trade():m_source(0),m_level1(0){}
	unsigned char m_source;
	unsigned char m_level1;
};

class TU_API Print : public Trade
{
public:
	Print(unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source, unsigned char level1,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		unsigned int millisecond, short delay):// = 0xFFFF):
		Trade(dollars, dollarFraction, quantity, source, level1, millisecond, delay),
		m_saleCondition1(saleCondition1),
		m_saleCondition2(saleCondition2),
		m_saleCondition3(saleCondition3),
		m_saleCondition4(saleCondition4)
		{}
	Print(const Price& price, unsigned int quantity, unsigned char source, unsigned char level1,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		unsigned int millisecond, short delay):// = 0xFFFF):
		Trade(price, quantity, source, level1, millisecond, delay),
		m_saleCondition1(saleCondition1),
		m_saleCondition2(saleCondition2),
		m_saleCondition3(saleCondition3),
		m_saleCondition4(saleCondition4)
		{}
	Print():
		m_saleCondition1('\0'),
		m_saleCondition2('\0'),
		m_saleCondition3('\0'),
		m_saleCondition4('\0')
	{}
	virtual bool isPrint() const{return true;}
	virtual unsigned int GetMmid() const;
	virtual unsigned short GetShortMmid() const;
	virtual char GetSaleCondition1() const{return m_saleCondition1;}
	virtual char GetSaleCondition2() const{return m_saleCondition2;}
	virtual char GetSaleCondition3() const{return m_saleCondition3;}
	virtual char GetSaleCondition4() const{return m_saleCondition4;}
	virtual char GetSaleCondition(unsigned int i) const{return i < 4 ? *(&m_saleCondition1 + i) : '\0';}
	virtual bool isOddLot() const{return m_saleCondition1 == 'I' || m_saleCondition4 == 'I';}
	void SetValues(unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source, unsigned char level1,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		unsigned int millisecond, short delay, bool historical)
	{
		Trade::SetValues(dollars, dollarFraction, quantity, source, level1, millisecond, delay, historical);
		m_saleCondition1 = saleCondition1;
		m_saleCondition2 = saleCondition2;
		m_saleCondition3 = saleCondition3;
		m_saleCondition4 = saleCondition4;
	}
protected:
	char m_saleCondition1;
	char m_saleCondition2;
	char m_saleCondition3;
	char m_saleCondition4;
};

class TU_API NamedPrint : public Print
{
public:
	NamedPrint(unsigned int mmid, unsigned short shortMmid, unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source, unsigned char level1,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		unsigned int millisecond, short delay):// = 0xFFFF):
		Print(dollars, dollarFraction, quantity, source, level1,
			saleCondition1,
			saleCondition2,
			saleCondition3,
			saleCondition4,
			millisecond, delay),
		m_mmid(mmid),
		m_shortMmid(shortMmid)
		{}
	NamedPrint(unsigned int mmid, unsigned short shortMmid, const Price& price, unsigned int quantity, unsigned char source, unsigned char level1,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		unsigned int millisecond, short delay):// = 0xFFFF):
		Print(price, quantity, source, level1,
			saleCondition1,
			saleCondition2,
			saleCondition3,
			saleCondition4,
			millisecond, delay),
		m_mmid(mmid),
		m_shortMmid(shortMmid)
		{}
	NamedPrint():m_mmid(0),m_shortMmid(0){}
	virtual unsigned int GetMmid() const{return m_mmid;}
	virtual unsigned short GetShortMmid() const{return m_shortMmid;}
	void SetValues(unsigned int mmid, unsigned short shortMmid, unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source, unsigned char level1,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		unsigned int millisecond, short delay, bool historical)
	{
		Print::SetValues(dollars, dollarFraction, quantity, source, level1, saleCondition1, saleCondition2, saleCondition3, saleCondition4, millisecond, delay, historical);
		m_mmid = mmid;
		m_shortMmid = shortMmid;
	}
protected:
	unsigned int m_mmid;
	unsigned short m_shortMmid;
};

class TU_API BookExecution : public Trade
{
public:
	BookExecution(unsigned char side, bool hidden, bool oddLot, unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source, unsigned char level1, unsigned int millisecond, short delay):// = 0xFFFF):
		Trade(dollars, dollarFraction, quantity, source, level1, millisecond, delay),
		m_side(side),
		m_hidden(hidden),
		m_oddLot(oddLot)
		{}
	BookExecution(unsigned char side, bool hidden, bool oddLot, const Price& price, unsigned int quantity, unsigned char source, unsigned char level1, unsigned int millisecond, short delay):// = 0xFFFF):
		Trade(price, quantity, source, level1, millisecond, delay),
		m_side(side),
		m_hidden(hidden),
		m_oddLot(oddLot)
		{}
	BookExecution():m_side(0), m_hidden(false), m_oddLot(false){}
	virtual unsigned char GetSide() const{return m_side;}//0 - unknown, 1 - buy, 2 - sell
	virtual bool isHidden() const{return m_hidden;}
	virtual unsigned int GetMmid() const;
	virtual unsigned short GetShortMmid() const;
	virtual bool isOddLot() const{return m_oddLot;}
	unsigned char m_side;
	bool m_hidden;
	bool m_oddLot;
};

class TU_API NamedBookExecution : public BookExecution
{
public:
	NamedBookExecution(char label, unsigned char side, bool hidden, bool oddLot, unsigned int mmid, unsigned short shortMmid, unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source, unsigned char level1, unsigned int millisecond, short delay):// = 0xFFFF):
		BookExecution(side, hidden, oddLot, dollars, dollarFraction, quantity, source, level1, millisecond, delay),
		m_mmid(mmid),
		m_shortMmid(shortMmid),
		m_label(label)
		{}
	NamedBookExecution(char label, unsigned char side, bool hidden, bool oddLot, unsigned int mmid, unsigned short shortMmid, const Price& price, unsigned int quantity, unsigned char source, unsigned char level1, unsigned int millisecond, short delay):// = 0xFFFF):
		BookExecution(side, hidden, oddLot, price, quantity, source, level1, millisecond, delay),
		m_mmid(mmid),
		m_shortMmid(shortMmid),
		m_label(label)
		{}
	NamedBookExecution():m_mmid(0), m_label('\0'){}
	virtual unsigned int GetMmid() const{return m_mmid;}
	virtual unsigned short GetShortMmid() const{return m_shortMmid;}
	virtual char GetLabel() const{return m_label;}
protected:
	unsigned int m_mmid;
	unsigned short m_shortMmid;
	char m_label;
};

class TU_API NamedBookExecutionCond : public NamedBookExecution
{
public:
	NamedBookExecutionCond(char label, unsigned char side, bool hidden, bool oddLot, unsigned int mmid, unsigned short shortMmid, unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source, unsigned char level1,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		unsigned int millisecond, short delay):// = 0xFFFF):
		NamedBookExecution(label, side, hidden, oddLot, mmid, shortMmid, dollars, dollarFraction, quantity, source, level1, millisecond, delay),
		m_saleCondition1(saleCondition1),
		m_saleCondition2(saleCondition2),
		m_saleCondition3(saleCondition3),
		m_saleCondition4(saleCondition4)
		{}
	NamedBookExecutionCond(char label, unsigned char side, bool hidden, bool oddLot, unsigned int mmid, unsigned short shortMmid, const Price& price, unsigned int quantity, unsigned char source, unsigned char level1,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		unsigned int millisecond, short delay):// = 0xFFFF):
		NamedBookExecution(label, side, hidden, oddLot, mmid, shortMmid, price, quantity, source, level1, millisecond, delay),
		m_saleCondition1(saleCondition1),
		m_saleCondition2(saleCondition2),
		m_saleCondition3(saleCondition3),
		m_saleCondition4(saleCondition4)
		{}
	NamedBookExecutionCond():
		m_saleCondition1('\0'),
		m_saleCondition2('\0'),
		m_saleCondition3('\0'),
		m_saleCondition4('\0')
		{}
	virtual char GetSaleCondition1() const{return m_saleCondition1;}
	virtual char GetSaleCondition2() const{return m_saleCondition2;}
	virtual char GetSaleCondition3() const{return m_saleCondition3;}
	virtual char GetSaleCondition4() const{return m_saleCondition4;}
	virtual char GetSaleCondition(unsigned int i) const{return i < 4 ? *(&m_saleCondition1 + i) : '\0';}
protected:
	char m_saleCondition1;
	char m_saleCondition2;
	char m_saleCondition3;
	char m_saleCondition4;
};

class TU_API DisplayPrint : public NamedBookExecutionCond
{
public:
	DisplayPrint(bool print,
		char label,
		unsigned char side,
		bool hidden,
		bool oddLot,
		bool priceWithCommas,
		bool sizeWithCommas,
		unsigned int mmid,
		unsigned short shortMmid,
		unsigned int dollars,
		unsigned int dollarFraction,
		unsigned int quantity,
		unsigned char source,
		unsigned char level1,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		unsigned int millisecond,
		short delay,
		unsigned int fractionDollar,
		unsigned int fractionDivider,
		unsigned char fractionDecDigits,
//		bool sizeInShares,
		unsigned int roundLot,
		COLORREF textColor,
		COLORREF bgColor,
		bool useBgColor,
		bool historical,
		bool truncate):
		NamedBookExecutionCond(label, side, hidden, oddLot, mmid, shortMmid, dollars, dollarFraction, quantity, source, level1,
			saleCondition1,
			saleCondition2,
			saleCondition3,
			saleCondition4,
			millisecond, delay),
		m_print(print),
//		m_priceWithCommas(priceWithCommas),
		m_useBgColor(useBgColor),
		m_textColor(textColor),
		m_bgColor(bgColor)
//		m_truncate(truncate)
	{
		if(historical)
		{
			m_historical = true;
		}
		CalculateDisplayPrice(fractionDollar, fractionDivider, fractionDecDigits, priceWithCommas, truncate);
		CalculateDisplaySize(roundLot, sizeWithCommas);
	}
	DisplayPrint()://empty display line
		NamedBookExecutionCond('\0', '\0', false, false, 0, 0, 0, 0, 0, '\0', TL1_BETWEEN_BIDASK, '\0', '\0', '\0', '\0', 0, 0),
		m_displayPriceDollar(0),
		m_displayPriceFraction(0),
		m_fractionDivider(Price::divider),
		m_displaySize(0),
		m_print(false),
//		m_priceWithCommas(true),
		m_useBgColor(false),
		m_truncate(true),
		m_textColor(0),
		m_bgColor(0),
		m_sizePtr(m_sizeBuffer),
		m_dollarPtr(m_dollarBuffer)
	{
		*m_sizeBuffer = '\0';
		*m_dollarBuffer = '\0';
		*m_dollarFractionBuffer = '\0';
	}
	DisplayPrint(const DisplayPrint& other):
		NamedBookExecutionCond(other),
		m_displayPriceDollar(other.m_displayPriceDollar),
		m_displayPriceFraction(other.m_displayPriceFraction),
		m_fractionDivider(other.m_fractionDivider),
		m_displaySize(other.m_displaySize),
		m_print(other.m_print),
//		m_priceWithCommas(other.m_priceWithCommas),
		m_useBgColor(other.m_useBgColor),
		m_truncate(other.m_truncate),
		m_textColor(other.m_textColor),
		m_bgColor(other.m_bgColor),
		m_sizePtr(m_sizeBuffer + (other.m_sizePtr - other.m_sizeBuffer)),
		m_dollarPtr(m_dollarBuffer + (other.m_dollarPtr - other.m_dollarBuffer))
	{
		memcpy(m_sizeBuffer, other.m_sizeBuffer, sizeof(m_sizeBuffer));
		memcpy(m_dollarBuffer, other.m_dollarBuffer, sizeof(m_dollarBuffer));
		memcpy(m_dollarFractionBuffer, other.m_dollarFractionBuffer, sizeof(m_dollarFractionBuffer));
	}
	DisplayPrint& operator=(const DisplayPrint& other)
	{
		NamedBookExecutionCond::operator=(other);
		m_displayPriceDollar = other.m_displayPriceDollar;
		m_displayPriceFraction = other.m_displayPriceFraction;
		m_fractionDivider = other.m_fractionDivider;
		m_displaySize = other.m_displaySize;
		m_print = other.m_print;
//		m_priceWithCommas = other.m_priceWithCommas;
		m_useBgColor = other.m_useBgColor;
		m_truncate = other.m_truncate;
		m_textColor = other.m_textColor;
		m_bgColor = other.m_bgColor;
		m_sizePtr = m_sizeBuffer + (other.m_sizePtr - other.m_sizeBuffer);
		m_dollarPtr = m_dollarBuffer + (other.m_dollarPtr - other.m_dollarBuffer);

		memcpy(m_sizeBuffer, other.m_sizeBuffer, sizeof(m_sizeBuffer));
		memcpy(m_dollarBuffer, other.m_dollarBuffer, sizeof(m_dollarBuffer));
		memcpy(m_dollarFractionBuffer, other.m_dollarFractionBuffer, sizeof(m_dollarFractionBuffer));
		return *this;
	}

	virtual bool isPrint() const{return m_print;}

	const char* GetQuantityStr() const{return m_sizePtr;}
	const char* GetDollarStr() const{return m_dollarPtr;}
	const char* GetDollarFractionStr() const{return m_dollarFractionBuffer;}

	void Refresh(const unsigned int fractionDollar,
		const unsigned int fractionDivider,
		unsigned char fractionDecDigits,
		bool priceWithCommas,
		bool sizeWithCommas,
		bool truncate,
		unsigned int roundLot,
		COLORREF textColor,
		COLORREF bgColor)
	{
//		m_priceWithCommas = priceWithCommas;
//		NamedBookExecutionCond::operator=(print);
		CalculateDisplayPrice(fractionDollar, fractionDivider, fractionDecDigits, priceWithCommas, truncate);
		CalculateDisplaySize(roundLot, sizeWithCommas);
		m_textColor = textColor;
		m_bgColor = bgColor;
	}

	bool isEmpty() const{return m_quantity == 0;}
	bool isUseBgColor() const{return m_useBgColor;}
	bool isTruncate() const{return m_truncate;}
	COLORREF GetBgColor() const{return m_bgColor;}
	COLORREF GetTextColor() const{return m_textColor;}
	unsigned int GetDisplaySize() const{return m_displaySize;}

	unsigned int GetFractionDivider() const{return m_fractionDivider;}
	unsigned int GetDisplayPriceDollar() const{return m_displayPriceDollar;}
	unsigned int GetDisplayPriceFraction() const{return m_displayPriceFraction;}
protected:
	void CalculateDisplaySize(unsigned int roundLot, bool sizeWithCommas);
	void CalculateDisplayPrice(unsigned int fractionDollar, unsigned int fractionDivider, unsigned char fractionDecDigits, bool priceWithCommas, bool truncate);
	unsigned int m_displayPriceDollar;
	unsigned int m_displayPriceFraction;
	unsigned int m_fractionDivider;
	unsigned int m_displaySize;
	bool m_print;
//	bool m_priceWithCommas;
	bool m_useBgColor;
	bool m_truncate;
	COLORREF m_textColor;
	COLORREF m_bgColor;
private:
	char m_sizeBuffer[11];
	char m_dollarBuffer[11];
	char m_dollarFractionBuffer[11];
	char* m_sizePtr;
	char* m_dollarPtr;
};

typedef unsigned __int64 quoteid;

class TU_API Quote : public DelayedPriceQuantity
{
public:
	virtual ~Quote(){}
	bool isBid() const{return m_bid;}
	virtual quoteid GetId() const{return 0;}
//	virtual unsigned int GetMmid() const{return 0;}
	virtual unsigned int GetMmid() const{return m_mmid;}
	virtual EcnBookId GetBookId() const{return m_bookId;}
	virtual unsigned char GetSource() const;
	virtual unsigned int GetOrderCount() const{return 1;}
	virtual char GetCondition() const{return '\0';}
	virtual bool GetRetailLiquidity() const{return false;}
	bool operator<(const Quote& other) const{return m_bid ? other.Price::operator<(*this) : Price::operator<(other);}
//	bool operator==(const Quote& other) const{return Price::operator==(other);}
	virtual bool isDirect() const{return true;}
	virtual bool isLessCrossBook(const Quote& other) const{return operator<(other) || operator==(other) && (m_mmid < other.m_mmid || m_mmid == other.m_mmid && (m_bookId < other.m_bookId || m_bookId == other.m_bookId && isDirect()));}
	virtual bool isTemp() const{return false;}
	virtual bool isAttributed() const{return false;}
//	virtual bool isOrder() const{return false;}
	virtual unsigned char GetOrder() const{return '\0';}
	bool isLrp() const{return m_mmid == lrpNum;}
	bool isLuld() const{return m_mmid == luldNum;}
	virtual bool isHidden() const{return false;}
//	virtual bool isLessCrossBook(const Quote& other) const{return Quote::operator<(other) || Quote::operator==(other) && (m_mmid < other.GetMmid() || m_mmid == other.GetMmid() && m_id < other.GetId());}
	bool isEmpty() const{return m_quantity == 0 && isZero();}
	bool isRegular() const{return GetOrder() != 1 && !isLrp() && !isLuld() && !isEmpty();}
protected:
	Quote(bool bid, unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, EcnBookId bookId, unsigned int mmid, unsigned int millisecond, short delay):// = 0xFFFF):
		DelayedPriceQuantity(dollars, dollarFraction, quantity, millisecond, delay),
		m_mmid(mmid),
		m_bid(bid),
		m_bookId(bookId)
		{}
	Quote(bool bid, const Price& price, unsigned int quantity, EcnBookId bookId, unsigned int mmid, unsigned int millisecond, short delay):// = 0xFFFF):
		DelayedPriceQuantity(price, quantity, millisecond, delay),
		m_mmid(mmid),
		m_bid(bid),
		m_bookId(bookId)
		{}
	Quote(bool bid = false):m_mmid(0),m_bid(bid),m_bookId(AllBooks){}
	unsigned int m_mmid;
	bool m_bid;
	EcnBookId m_bookId;
};

class TU_API TempQuote : public Quote
{
public:
	TempQuote(bool bid, unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, EcnBookId bookId, unsigned int mmid, unsigned int millisecond, short delay, bool attributed, bool retailLiquidity):// = 0xFFFF):
		Quote(bid, dollars, dollarFraction, quantity, bookId, mmid, millisecond, delay),
		m_condition('\0'),
		m_attributed(attributed),
		m_retailLiquidity(retailLiquidity)
		{}
	TempQuote(bool bid, const Price& price, unsigned int quantity, EcnBookId bookId, unsigned int mmid, unsigned int millisecond, short delay, bool attributed, bool retailLiquidity):// = 0xFFFF):
		Quote(bid, price, quantity, bookId, mmid, millisecond, delay),
		m_condition('\0'),
		m_attributed(attributed),
		m_retailLiquidity(retailLiquidity)
		{}
	TempQuote():Quote(),m_condition('\0'),m_attributed(false),m_retailLiquidity(false){}
	TempQuote(const Quote& quote):
		Quote(quote),
		m_condition(quote.GetCondition()),
		m_attributed(quote.isAttributed()),
		m_retailLiquidity(quote.GetRetailLiquidity())
		{}
	void InitQuote(const Quote& other)
	{
		Quote::operator=(other);
		m_condition = other.GetCondition();
		m_attributed = other.isAttributed();
		m_retailLiquidity = other.GetRetailLiquidity();
//		TU_IsSlowQuoteCondition(char condition, bool nasdaq, bool bid);
	}
	TempQuote& operator=(const TempQuote& other)
	{
		Quote::operator=(other);
		m_condition = other.GetCondition();
		m_attributed = other.isAttributed();
		m_retailLiquidity = other.GetRetailLiquidity();
		return *this;
	}

	void SetBookId(unsigned char bookId){m_bookId = (EcnBookId)bookId;}
	void SetCondition(char condition){m_condition = condition;}
	void SetMmid(unsigned int mmid){m_mmid = mmid;}
	void SetAttributed(bool attributed){m_attributed = attributed;}
	void SetRetailLiquidity(bool retailLiquidity){m_retailLiquidity = retailLiquidity;}
	void SetMillisecond(unsigned int millisecond){m_millisecond = millisecond;}
	void SetDelay(short delay){m_delay = delay;}

	virtual bool isTemp() const{return true;}
	virtual bool isAttributed() const{return m_attributed;}
	virtual char GetCondition() const{return m_condition;}
	virtual bool GetRetailLiquidity() const{return m_retailLiquidity;}
protected:
	char m_condition;
	bool m_attributed;
	bool m_retailLiquidity;
};

class TU_API Book
{
public:
	virtual ~Book(){}
	virtual TakionIterator* CreateBookIterator(bool bid, bool aggregated) const = 0;//{return NULL;}
	virtual void Clear() = 0;
	virtual void ClearSide(bool bid) = 0;
	virtual bool GetPriceForSize(bool bid, Price& price, unsigned int& size) const{return false;}
	virtual bool HasSizeForPrice(bool bid, const Price& price, unsigned int size, bool includePrice) const{return false;}
	virtual unsigned int GetSizeForSpecificPrice(bool bid, const Price& price) const{return 0;}
	virtual unsigned int GetName() const{return 0;}
	virtual unsigned short GetShortName() const{return 0;}
	virtual char GetLabel() const{return 0;}
	virtual EcnBookId GetBookId() const = 0;//{return AllBooks;}
	virtual unsigned char GetAttributedBookId() const{return 0xFF;}
	virtual unsigned char GetNativeBookId() const{return 0xFF;}
	virtual bool RemoveQuote(bool bid, unsigned int mmid, const Price& priceFromExclusive, const Price& priceToInclusive){return false;}
protected:
	Book(){}
};
/*
class TU_API MarketCenter
{
public:
	virtual ~MarketCenter(){}
	unsigned char GetId() const{return m_id;}
	const std::string& GetNameStr() const{return m_name;}
	const char* GetName() const{return m_name.c_str();}
	unsigned int GetNumericName() const{return m_numericName;}
	virtual TakionIterator* CreatePrintIterator() const = 0;
protected:
	MarketCenter(unsigned char id, const char* name):m_id(id),m_name(name),m_numericName(*(unsigned int*)name){}
	unsigned char m_id;
	std::string m_name;
	unsigned int m_numericName;
};
*/

class TU_API Exchange
{
public:
	virtual ~Exchange(){}
	const unsigned char& GetId() const{return m_id;}
	const char* GetLongName() const{return m_name;}
	const unsigned int& GetNumericLongName() const{return m_numericName;}
	const char* GetShortName() const{return m_shortName;}
	const char* GetShortNameLowercase() const{return m_shortNameLowercase;}
	const unsigned short& GetNumericShortName() const{return m_numericShortName;}
	const unsigned int& GetFilter() const{return m_filter;}
	void AddFilter(unsigned int filter){m_filter |= filter;}
	virtual TakionIterator* CreatePrintIterator() const{return NULL;}
	const bool& isProtected() const{return m_protectedQuote;}
protected:
	Exchange(const unsigned char& id, const char* name, const char* shortName, const bool& protectedQuote):
		m_numericName(*(unsigned int*)name),
		m_numericShortName(*(unsigned short*)shortName),
		m_filter(1 << id),
		m_id(id),
		m_protectedQuote(protectedQuote)
	{
		*(unsigned int*)m_name = m_numericName;
		m_name[sizeof(unsigned int)] = '\0';
		*(unsigned short*)m_shortName = m_numericShortName;
		m_shortName[sizeof(unsigned short)] = '\0';
		*(unsigned short*)m_shortNameLowercase = m_numericShortName + 0x2020;
		m_shortNameLowercase[sizeof(unsigned short)] = '\0';
	}
	Exchange(const unsigned char& id, const unsigned int& name, const unsigned short& shortName, const bool& protectedQuote):
		m_numericName(name),
		m_numericShortName(shortName),
		m_filter(1 << id),
		m_id(id),
		m_protectedQuote(protectedQuote)
	{
		*(unsigned int*)m_name = m_numericName;
		m_name[sizeof(unsigned int)] = '\0';
		*(unsigned short*)m_shortName = m_numericShortName;
		m_shortName[sizeof(unsigned short)] = '\0';
		*(unsigned short*)m_shortNameLowercase = m_numericShortName + 0x2020;
		m_shortNameLowercase[sizeof(unsigned short)] = '\0';
	}
	unsigned int m_numericName;
	unsigned int m_filter;
	char m_name[sizeof(unsigned int) + 1];
	char m_shortName[sizeof(unsigned short) + 1];
	char m_shortNameLowercase[sizeof(unsigned short) + 1];
	unsigned short m_numericShortName;
	unsigned char m_id;
	bool m_protectedQuote;
};

class TU_API MarketCenter : public Exchange
{
public:
	MarketCenter(const unsigned char& id, const char* name, const char* shortName, const unsigned char& ecnBookId, const unsigned char& mmBookId, const bool& protectedQuote
#ifndef TAKION_NO_OPTIONS
		, const char* optionName, const char* optionShortName
#endif
		):
		Exchange(id, name, shortName, protectedQuote),
		m_ecnBookId(ecnBookId),
		m_mmBookId(mmBookId)
#ifndef TAKION_NO_OPTIONS
//		,m_optionNumericName(optionName ? *(unsigned int*)optionName : 0),
		,m_optionNumericName(optionName ? U_StringToUInt(optionName) : 0),
		m_optionNumericShortName(optionShortName ? *(unsigned short*)optionShortName : 0)
#endif
	{
#ifndef TAKION_NO_OPTIONS
		*(unsigned int*)m_optionName = m_optionNumericName;
		m_optionName[sizeof(unsigned int)] = '\0';
		*(unsigned short*)m_optionShortName = m_optionNumericShortName;
		m_optionShortName[sizeof(unsigned short)] = '\0';
		*(unsigned short*)m_optionShortNameLowercase = m_optionNumericShortName + (c2Num == m_optionNumericName ? 0x20 : 0x2020);
		m_optionShortNameLowercase[sizeof(unsigned short)] = '\0';
#endif
	}
	MarketCenter(const unsigned char& id, const unsigned int& name, const unsigned short& shortName, const unsigned char& ecnBookId, const unsigned char& mmBookId, const bool& protectedQuote
#ifndef TAKION_NO_OPTIONS
		, const unsigned int& optionName, const unsigned short& optionShortName
#endif
		):
		Exchange(id, name, shortName, protectedQuote),
		m_ecnBookId(ecnBookId),
		m_mmBookId(mmBookId)
#ifndef TAKION_NO_OPTIONS
		,m_optionNumericName(optionName),
		m_optionNumericShortName(optionShortName)
#endif
	{
#ifndef TAKION_NO_OPTIONS
		*(unsigned int*)m_optionName = m_optionNumericName;
		m_optionName[sizeof(unsigned int)] = '\0';
		*(unsigned short*)m_optionShortName = m_optionNumericShortName;
		m_optionShortName[sizeof(unsigned short)] = '\0';
//		*(unsigned short*)m_optionShortNameLowercase = m_optionNumericShortName + 0x2020;
		*(unsigned short*)m_optionShortNameLowercase = m_optionNumericShortName + (c2Num == m_optionNumericName ? 0x20 : 0x2020);
		m_optionShortNameLowercase[sizeof(unsigned short)] = '\0';
#endif
	}
	const unsigned char& GetEcnBookId() const{return m_ecnBookId;}
	const unsigned char& GetMmBookId() const{return m_mmBookId;}
#ifndef TAKION_NO_OPTIONS
	const unsigned int& GetOptionNumericName() const{return m_optionNumericName;}
	const char* GetOptionName() const{return m_optionName;}
	const unsigned short& GetOptionNumericShortName() const{return m_optionNumericShortName;}
	const char* GetOptionShortName() const{return m_optionShortName;}
	const char* GetOptionShortNameLowercase() const{return m_optionShortNameLowercase;}
#endif
protected:
	unsigned char m_ecnBookId;
	unsigned char m_mmBookId;
#ifndef TAKION_NO_OPTIONS
	unsigned int m_optionNumericName;
	char m_optionName[sizeof(unsigned int) + 1];
	char m_optionShortName[sizeof(unsigned short) + 1];
	char m_optionShortNameLowercase[sizeof(unsigned short) + 1];
	unsigned short m_optionNumericShortName;
#endif
};

class TU_API Ecn : public Exchange
{
public:
	Ecn(unsigned char id, const char* name, const char* shortName, char label, bool direct, bool protectedQuote, const char* destinationName, unsigned char attributedBookId, unsigned char nativeBookId):
		Exchange(id, name, shortName, protectedQuote),
		m_numericDestinationName(destinationName ? *(unsigned int*)destinationName : m_numericName),
		m_label(label),
		m_direct(direct),
		m_attributedBookId(attributedBookId),
		m_nativeBookId(nativeBookId)
	{
		*(unsigned int*)m_destinationName = m_numericDestinationName;
		m_destinationName[sizeof(unsigned int)] = '\0';
	}
	Ecn(unsigned char id, unsigned int name, unsigned short shortName, char label, bool direct, bool protectedQuote, const char* destinationName, unsigned char attributedBookId, unsigned char nativeBookId):
		Exchange(id, name, shortName, protectedQuote),
		m_numericDestinationName(destinationName ? *(unsigned int*)destinationName : m_numericName),
		m_label(label),
		m_direct(direct),
		m_attributedBookId(attributedBookId),
		m_nativeBookId(nativeBookId)
	{
		*(unsigned int*)m_destinationName = m_numericDestinationName;
		m_destinationName[sizeof(unsigned int)] = '\0';
	}
	bool isMmBook() const{return m_numericName != m_numericDestinationName;}
	bool isDirect() const{return m_direct;}
	char GetLabel() const{return m_label;}
	unsigned int GetNumericDestinationName() const{return m_numericDestinationName;}
	const char* GetDestinationName() const{return m_destinationName;}
	unsigned char GetAttributedBookId() const{return m_attributedBookId;}
	unsigned char GetNativeBookId() const{return m_nativeBookId;}
protected:
	unsigned int m_numericDestinationName;
	char m_destinationName[sizeof(unsigned int) + 1];
	char m_label;
	bool m_direct;
	unsigned char m_attributedBookId;
	unsigned char m_nativeBookId;
};

class TU_API IndexChartPoint
{
public:
//#ifdef _DEBUG
	IndexChartPoint(const unsigned short& minute = 0):
		m_minute(minute),
//#else
//	IndexChartPoint():
//#endif
		m_initialized(false)
	{}
	IndexChartPoint(const SignedPrice& startValue,
		const SignedPrice& highValue,
		const SignedPrice& lowValue,
		const SignedPrice& endValue,
//		const Money& moneyTraded,
//#ifdef _DEBUG
		const unsigned short& minute
//#endif
		):

		m_startValue(startValue),
		m_highValue(highValue),
		m_lowValue(lowValue),
		m_endValue(endValue),
//		m_moneyTraded(moneyTraded),
//#ifdef _DEBUG
		m_minute(minute),
//#endif
		m_initialized(false)
	{
	}
	void AddValue(const SignedPrice& value)
	{
		if(m_initialized)
		{
			m_endValue = value;
			if(m_highValue < value)
			{
				m_highValue = value;
			}
			else if(m_lowValue > value)
			{
				m_lowValue = value;
			}
		}
		else
		{
			m_startValue = m_highValue = m_lowValue = m_endValue = value;
			m_initialized = true;
		}
	}
	const SignedPrice& GetStartValue() const{return m_startValue;}
	const SignedPrice& GetHighValue() const{return m_highValue;}
	const SignedPrice& GetLowValue() const{return m_lowValue;}
	const SignedPrice& GetEndValue() const{return m_endValue;}
	void Reset()
	{
		m_startValue.SetZero();
		m_highValue.SetZero();
		m_lowValue.SetZero();
		m_endValue.SetZero();
//#ifdef _DEBUG
		m_minute = 0;
//#endif
		m_initialized = false;
	}
	void AddPoint(const IndexChartPoint& other)
	{
		if(other.m_initialized)
		{
			if(m_initialized)
			{
				if(m_highValue < other.m_highValue)
				{
					m_highValue = other.m_highValue;
				}
				if(m_lowValue < other.m_lowValue)
				{
					m_lowValue = other.m_lowValue;
				}
				m_endValue = other.m_endValue;
			}
			else
			{
				m_startValue = other.m_startValue;
				m_highValue = other.m_highValue;
				m_lowValue = other.m_lowValue;
				m_endValue = other.m_endValue;
			}
		}
	}

//#ifdef _DEBUG
	const unsigned short& GetMinute() const{return m_minute;}
//#endif
	bool isInitialized() const{return m_initialized;}
	DECLARE_NED_NEW

protected:
	SignedPrice m_startValue;
	SignedPrice m_highValue;
	SignedPrice m_lowValue;
	SignedPrice m_endValue;
//	Money m_moneyTraded;
//#ifdef _DEBUG
	unsigned short m_minute;
//#endif
	bool m_initialized;
//	Price m_vwap;
};

/*
class TU_API PriceChartPoint
{
public:
#ifdef _DEBUG
	PriceChartPoint(unsigned short minute = 0):
		m_minute(minute)
#else
	PriceChartPoint()
#endif
	{}
	PriceChartPoint(const SignedPrice& startPrice,
		const SignedPrice& highPrice,
		const SignedPrice& lowPrice,
		const SignedPrice& endPrice
#ifdef _DEBUG
		,const unsigned short minute
#endif
		):

		m_startPrice(startPrice),
		m_highPrice(highPrice),
		m_lowPrice(lowPrice),
		m_endPrice(endPrice)
#ifdef _DEBUG
		,m_minute(minute)
#endif
	{
	}
	void NewValue(const SignedPrice& price);//, const Price& lastPrice);//4 - last; 8 - volume, 16 - high/low
	const SignedPrice& GetStartPrice() const{return m_startPrice;}
	const SignedPrice& GetHighPrice() const{return m_highPrice;}
	const SignedPrice& GetLowPrice() const{return m_lowPrice;}
	const SignedPrice& GetEndPrice() const{return m_endPrice;}
	void Reset()
	{
		m_startPrice.SetZero();
		m_highPrice.SetZero();
		m_lowPrice.SetZero();
		m_endPrice.SetZero();
#ifdef _DEBUG
		m_minute = 0;
#endif
	}
	void AddPoint(const PriceChartPoint& other);

#ifdef _DEBUG
	const unsigned short& GetMinute() const{return m_minute;}
#endif
	DECLARE_NED_NEW

protected:
	SignedPrice m_startPrice;
	SignedPrice m_highPrice;
	SignedPrice m_lowPrice;
	SignedPrice m_endPrice;
#ifdef _DEBUG
	unsigned short m_minute;
#endif
};
*/
class TU_API Index : public Observable
{
public:
	virtual ~Index(){}
	const char* GetSymbol() const{return m_symbolStr.c_str();}
	const std::string& GetSymbolStr() const{return m_symbolStr;}
//	const char* GetSymbol() const{return m_symbol;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
	const unsigned short& GetCode() const{return m_code;}

	const char* GetName() const{return m_name.c_str();}
	const std::string& GetNameStr() const{return m_name;}

	const SignedPrice& GetValue() const{return m_value;}
	const SignedPrice& GetStartValue() const{return  m_startValue;}
	const SignedPrice& GetLowValue() const{return m_lowValue;}
	const SignedPrice& GetHighValue() const{return m_highValue;}
	const SignedPrice& GetCloseValue() const{return m_closeValue;}
	const SignedPrice& GetTodaysCloseValue() const{return m_todaysCloseValue;}
	const SignedPrice& GetNetChange() const{return m_netChange;}
	const SignedPrice& GetTick() const{return m_tick;}

	typedef std::vector<IndexChartPoint> IndexChartPointVector;

	unsigned short GetChartStartMinute() const{return m_chartStartMinute;}
	unsigned short GetChartSize() const{return (unsigned short)m_chart.size();}
	const IndexChartPointVector* GetChart() const{return &m_chart;}//m_chart;}
	bool isChartLoaded() const{return m_chartLoaded;}

	bool LockInquiryValue() const{return m_lockValue.LockInquiry();}
	void LockInquiryWaitValue() const{m_lockValue.LockInquiryWait();}
	void UnlockInquiryValue() const{m_lockValue.UnlockInquiry();}

	bool LockInquiryChart() const{return m_lockChart.LockInquiry();}
	void LockInquiryWaitChart() const{m_lockChart.LockInquiryWait();}
	void UnlockInquiryChart() const{m_lockChart.UnlockInquiry();}

	bool isLoaded() const{return m_loaded;}
	void AddInThreadObserver(Observer* o) const;
//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;
	void RemoveInThreadObserver(Observer* o) const;
	virtual unsigned short GetLastNewMinuteFromMsServer() const{return 0;}

	virtual HANDLE GetThreadHandle() const{return NULL;}
	virtual unsigned int GetThreadId() const{return 0;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}
protected:
	Index(const char* symbol, unsigned short code);
//	char m_symbol[16];
	std::string m_symbolStr;
	std::string m_name;
	unsigned __int64 m_numericSymbol;
	SignedPrice m_value;
	SignedPrice m_startValue;
	SignedPrice m_lowValue;
	SignedPrice m_highValue;
	SignedPrice m_closeValue;
	SignedPrice m_todaysCloseValue;
	SignedPrice m_netChange;
	SignedPrice m_tick;
	IndexChartPointVector m_chart;
	unsigned short m_code;
	unsigned short m_chartStartMinute;
	bool m_chartLoaded;
	bool m_loaded;
	TakionLock m_lockValue;
	TakionLock m_lockChart;
	Observable m_inThreadObservable;
//	volatile LONG m_lockInThreadObservable;
	TakionLockMultithread m_lockInThreadObservable;
};


enum ImbalanceCrossType
{
	Opening			= 'O',
	Closing			= 'C',
	HaltOrIPO		= 'H',
	Market			= 'M',
	CrossUndefined	= ' ',
};

enum ImbalanceDirection
{
	ImbalanceBuy		= 'B',
	ImbalanceSell		= 'S',
	ImbalanceNone		= 'N',
	ImbalanceUndefined	= 'O',
};

class TU_API ImbalanceBase
{
public:
	const Price& GetFarPrice() const{return m_farPrice;}
	const Price& GetRegulatoryFarPrice() const{return m_regulatoryFarPrice;}
	const Price& GetNearPrice() const{return m_nearPrice;}
	const Price& GetRegulatoryNearPrice() const{return m_regulatoryNearPrice;}
	const Price& GetCurrentReferencePrice() const{return m_currentReferencePrice;}
	const Price& GetRegulatoryCurrentReferencePrice() const{return m_regulatoryCurrentReferencePrice;}
	const unsigned int& GetPairedShares() const{return m_pairedShares;}
	const unsigned int& GetRegulatoryPairedShares() const{return m_regulatoryPairedShares;}
	const int& GetImbalanceShares() const{return m_imbalanceShares;}
	const int& GetPrevImbalanceShares() const{return m_prevImbalanceShares;}
	const int& GetRegulatoryImbalanceShares() const{return m_regulatoryImbalanceShares;}
	const int& GetPrevRegulatoryImbalanceShares() const{return m_prevRegulatoryImbalanceShares;}
	const int& GetMarketImbalanceShares() const{return m_marketImbalanceShares;}
	const int& GetInitialImbalanceShares() const{return m_initialImbalanceShares;}
	const int& GetT926ImbalanceShares() const{return m_t926ImbalanceShares;}
	const unsigned int& GetImbalanceTime() const{return m_time;}
	const unsigned int& GetPrevImbalanceTime() const{return m_prevTime;}
	const unsigned int& GetRegulatoryImbalanceTime() const{return m_regulatoryTime;}
	const unsigned int& GetPrevRegulatoryImbalanceTime() const{return m_prevRegulatoryTime;}
	const unsigned int& GetAuctionTime() const{return m_auctionTime;}
//	const char& GetImbalanceDirection() const{return m_imbalanceDirection;}
	const char& GetCrossType() const{return m_crossType;}
	const char& GetPriceVariationIndicator() const{return m_priceVariationIndicator;}

	void SetParams(const Price& farPrice,
		const Price& nearPrice,
		const Price& currentReferencePrice,
		unsigned int pairedShares,
		unsigned int imbalanceShares,
		unsigned int marketImbalanceShares,
		unsigned int time,
		unsigned int auctionTime,
		char imbalanceDirection,
		char crossType,
		char priceVariationIndicator,
		bool regulatory)
	{
		int shares = imbalanceDirection == ImbalanceSell ? -(int)imbalanceShares : (int)imbalanceShares;
		if(!m_initialImbalanceShares)
		{
			m_initialImbalanceShares = shares;
		}
		if(time <= 33960000 || !m_t926ImbalanceShares && time < 43200000)//9:26
		{
			m_t926ImbalanceShares = shares;
		}
		if(regulatory && crossType == Closing)
		{
			m_crossType = crossType;
			m_regulatoryFarPrice = farPrice;
			m_regulatoryNearPrice = nearPrice;
			m_regulatoryCurrentReferencePrice = currentReferencePrice;
			m_regulatoryPairedShares = pairedShares;

			m_prevRegulatoryImbalanceShares = m_regulatoryImbalanceShares;
			m_regulatoryImbalanceShares = shares;

			m_prevRegulatoryTime = m_regulatoryTime;
			m_regulatoryTime = time;
		}
//		else 
		else if(!regulatory)
		{
/*
			if(!m_regulatoryImbalanceShares && shares && crossType == Opening)
			{
				m_regulatoryFarPrice = farPrice;
				m_regulatoryNearPrice = nearPrice;
				m_regulatoryCurrentReferencePrice = currentReferencePrice;
				m_regulatoryPairedShares = pairedShares;

				m_regulatoryImbalanceShares = shares;
				m_regulatoryTime = time;
			}
*/
			m_crossType = regulatory && crossType == Opening ? HaltOrIPO : crossType;
//		} //the brace is removed (and added below). If the brace is here, it causes the imbalances to disappear as the stocks open. The brace was added on 12/18/2013 and caused problems
			m_farPrice = farPrice;
			m_nearPrice = nearPrice;
			m_currentReferencePrice = currentReferencePrice;
			m_pairedShares = pairedShares;
			if(m_imbalanceShares != shares)
			{
				m_prevImbalanceShares = m_imbalanceShares;
				m_prevTime = m_time;
				m_imbalanceShares = shares;
			}
			m_time = time;
		}
		m_marketImbalanceShares = imbalanceDirection == ImbalanceSell ? -(int)marketImbalanceShares : (int)marketImbalanceShares;
		m_auctionTime = auctionTime;
//		m_imbalanceDirection = imbalanceDirection;
		m_priceVariationIndicator = priceVariationIndicator;
	}
//protected:
	ImbalanceBase()
		: m_pairedShares(0)
		, m_regulatoryPairedShares(0)
		, m_imbalanceShares(0)
		, m_prevImbalanceShares(0)
		, m_regulatoryImbalanceShares(0)
		, m_prevRegulatoryImbalanceShares(0)
		, m_marketImbalanceShares(0)
		, m_initialImbalanceShares(0)
		, m_t926ImbalanceShares(0)
		, m_time(0)
		, m_prevTime(0)
		, m_regulatoryTime(0)
		, m_prevRegulatoryTime(0)
		, m_auctionTime(0)
//		, m_imbalanceDirection(ImbalanceNone)
		, m_crossType(CrossUndefined)
		, m_priceVariationIndicator(' ')
	{}
	Price m_farPrice;
	Price m_regulatoryFarPrice;
	Price m_nearPrice;
	Price m_regulatoryNearPrice;
	Price m_currentReferencePrice;
	Price m_regulatoryCurrentReferencePrice;
	unsigned int m_pairedShares;
	unsigned int m_regulatoryPairedShares;
	int m_imbalanceShares;
	int m_prevImbalanceShares;
	int m_regulatoryImbalanceShares;
	int m_prevRegulatoryImbalanceShares;
	int m_marketImbalanceShares;
	int m_initialImbalanceShares;
	int m_t926ImbalanceShares;
	unsigned int m_time;
	unsigned int m_prevTime;
	unsigned int m_regulatoryTime;
	unsigned int m_prevRegulatoryTime;
	unsigned int m_auctionTime;
//	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
};

class TU_API Imbalance : public ImbalanceBase
{
public:
	virtual ~Imbalance(){}
	virtual void SetImbalance(const ImbalanceBase& other)
	{
		m_farPrice = other.GetFarPrice();
		m_regulatoryFarPrice = other.GetRegulatoryFarPrice();
		m_nearPrice = other.GetNearPrice();
		m_regulatoryNearPrice = other.GetRegulatoryNearPrice();
		m_currentReferencePrice = other.GetCurrentReferencePrice();
		m_regulatoryCurrentReferencePrice = other.GetRegulatoryCurrentReferencePrice();
		m_pairedShares = other.GetPairedShares();
		m_regulatoryPairedShares = other.GetRegulatoryPairedShares();
		m_imbalanceShares = other.GetImbalanceShares();
		m_prevImbalanceShares = other.GetPrevImbalanceShares();
		m_regulatoryImbalanceShares = other.GetRegulatoryImbalanceShares();
		m_prevRegulatoryImbalanceShares = other.GetPrevRegulatoryImbalanceShares();
		m_initialImbalanceShares = other.GetInitialImbalanceShares();
		m_t926ImbalanceShares = other.GetT926ImbalanceShares();
		m_marketImbalanceShares = other.GetMarketImbalanceShares();
		m_time = other.GetImbalanceTime();
		m_prevTime = other.GetPrevImbalanceTime();
		m_regulatoryTime = other.GetRegulatoryImbalanceTime();
		m_prevRegulatoryTime = other.GetPrevRegulatoryImbalanceTime();
		m_auctionTime = other.GetAuctionTime();
//		m_imbalanceDirection = other.GetImbalanceDirection();
		m_crossType = other.GetCrossType();
		m_priceVariationIndicator = other.GetPriceVariationIndicator();
	}
protected:
	Imbalance(){}
};

enum Tick : unsigned char
{
	NoTick			= 0x00,
	UpTick			= 0x01,
	DownTick		= 0x02,
};

enum SecurityType : unsigned char
{
	ST_STOCK,
	ST_OPTION,
//	ST_FUTURE,

	ST_COUNT,

	ST_MASK_ALL = (1 << ST_COUNT) - 1,
};

class TU_API ChartPoint
{
public:
//#ifdef _DEBUG
	ChartPoint(const unsigned short& minute = 0, 
		const unsigned int& date = 0):
		m_minute(minute),
//#else
//	ChartPoint():
//#endif
		m_date(date),
		m_volume(0)
	{}
	ChartPoint(const Price& startPrice,
		const Price& highPrice,
		const Price& lowPrice,
		const Price& endPrice,
		const Money& moneyTraded,
//#ifdef _DEBUG
		const unsigned short& minute,
//#endif
		const unsigned int& date,
		const unsigned int& volume
		);
	void AddPrint(const Price& price, unsigned int volume, unsigned char printFlags);//4 - last; 8 - volume, 16 - high/low
	void SetPriceAndVolume(const Price& price, unsigned int volume, unsigned char printFlags);//4 - last; 8 - volume, 16 - high/low
	void AddPrintVolumeOnly(const Price& price, unsigned int volume, unsigned char printFlags);//for prices far outside NBBO;//4 - last; 8 - volume, 16 - high/low
	const Price& GetStartPrice() const{return m_startPrice;}
	const Price& GetHighPrice() const{return m_highPrice;}
	const Price& GetLowPrice() const{return m_lowPrice;}
	const Price& GetEndPrice() const{return m_endPrice;}
	const Price& GetVWAP() const{return m_vwap;}
	const Money& GetMoneyTraded() const{return m_moneyTraded;}
	const unsigned int& GetVolume() const{return m_volume;}
	void ResetValues()
	{
		m_startPrice.SetZero();
		m_highPrice.SetZero();
		m_lowPrice.SetZero();
		m_endPrice.SetZero();
		m_moneyTraded.SetZero();
		m_volume = 0;
		m_vwap.SetZero();
	}
	void Reset()
	{
		ResetValues();
//#ifdef _DEBUG
		m_minute = 0;
//#endif
		m_date = 0;
	}
	void SetValues(const Price& startPrice,
		const Price& highPrice,
		const Price& lowPrice,
		const Price& endPrice,
		const Money& moneyTraded,
		const unsigned int& volume)
	{
		m_startPrice = startPrice;
		m_highPrice = highPrice;
		m_lowPrice = lowPrice;
		m_endPrice = endPrice;
		m_moneyTraded = moneyTraded;
		m_volume = volume;
		if(m_volume)
		{
			m_vwap = Price(m_moneyTraded.operator/(m_volume));
		}
		else
		{
			m_vwap.SetZero();
		}
	}
	void AddValues(const Price& startPrice,
		const Price& highPrice,
		const Price& lowPrice,
		const Price& endPrice,
		const Money& moneyTraded,
		const unsigned int& volume);
	void AddPoint(const ChartPoint& other);

	const unsigned int& GetDate() const{return m_date;}
	void SetDate(const unsigned int& date){m_date = date;}
//#ifdef _DEBUG
	const unsigned short& GetMinute() const{return m_minute;}
	void SetMinute(const unsigned short& minute){m_minute = minute;}
	void IncrementMinute(const unsigned short& diff){m_minute += diff;}
	void IncrementMinute(){++m_minute;}
	void DecrementMinute(const unsigned short& diff)
	{
		if(m_minute >= diff)
		{
			m_minute -= diff;
		}
		else
		{
			m_minute = 0;
		}
	}
	void DecrementMinute()
	{
		if(m_minute)
		{
			--m_minute;
		}
	}
//#endif
	DECLARE_NED_NEW

protected:
	Price m_startPrice;
	Price m_highPrice;
	Price m_lowPrice;
	Price m_endPrice;
	Money m_moneyTraded;
//#ifdef _DEBUG
	unsigned short m_minute;
//#endif
	unsigned int m_date;
	unsigned int m_volume;
	Price m_vwap;
};
/*
class TU_API HistoricalChartPoint : public ChartPoint
{
public:
	HistoricalChartPoint(unsigned int date, unsigned short minute = 0):
#ifdef _DEBUG
		ChartPoint(minute),
#else
		m_minute(minute),
#endif
		m_date(date)
	{}
	HistoricalChartPoint(const Price& startPrice,
		const Price& highPrice,
		const Price& lowPrice,
		const Price& endPrice,
		const Money& moneyTraded,
		const unsigned int& volume,
		const unsigned short& minute,
		const unsigned int& date,
		const Price& adjustedEndPrice):

		ChartPoint(startPrice,
			highPrice,
			lowPrice,
			endPrice,
			moneyTraded,
#ifdef _DEBUG
			minute,
#endif
			volume),
#ifndef _DEBUG
		m_minute(minute),
#endif
		m_date(date),
		m_adjustedEndPrice(adjustedEndPrice)
	{
	}
	const Price& GetAdjustedEndPrice() const{return m_adjustedEndPrice;}
	const unsigned int& GetDate() const{return m_date;}
#ifndef _DEBUG
	const unsigned short& GetMinute() const{return m_minute;}
#endif
protected:
#ifndef _DEBUG
	unsigned short m_minute;
#endif
	unsigned int m_date;
	Price m_adjustedEndPrice;
};
*/

class HistoricalPrint
{
public:
	HistoricalPrint(
//		unsigned __int64 referenceNumber,
		unsigned int compactPrice,
//		unsigned int time,
		unsigned int size,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		char marketCenterId):
		m_compactPrice(compactPrice),
//		m_time(time),
		m_size(size),
		m_saleCondition1(saleCondition1),
		m_saleCondition2(saleCondition2),
		m_saleCondition3(saleCondition3),
		m_saleCondition4(saleCondition4),
		m_marketCenterId(marketCenterId)
	{
	}
	const unsigned int& GetCompactPrice() const{return m_compactPrice;}
//	const unsigned int& GetTime() const{return m_time;}
	const unsigned int& GetSize() const{return m_size;}
	const char& GetSaleCondition1() const{return m_saleCondition1;}
	const char& GetSaleCondition2() const{return m_saleCondition2;}
	const char& GetSaleCondition3() const{return m_saleCondition3;}
	const char& GetSaleCondition4() const{return m_saleCondition4;}
	const char& GetMarketCenterId() const{return m_marketCenterId;}
protected:
//	unsigned __int64 m_referenceNumber;
	unsigned int m_compactPrice;
//	unsigned int m_time;
	unsigned int m_size;
	char m_saleCondition1;
	char m_saleCondition2;
	char m_saleCondition3;
	char m_saleCondition4;
	char m_marketCenterId;
};

class TU_API StockLoanInfo : public PriceQuantity
{
public:
	StockLoanInfo(unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char discountFlag):
		PriceQuantity(dollars, dollarFraction, quantity),
		m_discountFlag(discountFlag)
	{}
	StockLoanInfo(const Price& price, unsigned int quantity, unsigned char discountFlag):
		PriceQuantity(price, quantity),
		m_discountFlag(discountFlag)
	{}
	StockLoanInfo():m_discountFlag(0){}
	unsigned char GetDiscountFlag() const{return m_discountFlag;}
	void SetDiscountFlag(unsigned char discountFlag){m_discountFlag = discountFlag;}
protected:
	unsigned char m_discountFlag;
};

enum SymbolType : unsigned char
{
	EST_UNKNOWN,
	EST_STOCK,
	EST_BASKET,
#ifndef TAKION_NO_OPTIONS
	EST_OPTION,
#endif
};

class TU_API HTB
{
public:
	HTB(const char* symbol);
	static const unsigned char regularHtb;// = 'H';
//	const char* GetSymbol() const{return m_symbolStr.c_str();}
//	const std::string& GetSymbolStr() const{return m_symbolStr;}
	const char* GetSymbol() const{return (const char*)&m_numericSymbol;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}

	typedef std::vector<unsigned char> UCharVector;
	typedef std::vector<StockLoanInfo> StockLoanVector;
	const UCharVector& GetHTBVector() const{return m_htbVector;}
	const StockLoanVector& GetStockLoanInfoVector() const{return m_stockLoanVector;}
//	bool isHtb(unsigned int ordinal) const{return ordinal < (unsigned int)m_htbVector.size() ? m_htbVector[ordinal] : true;}

#ifndef TAKION_NO_OPTIONS
	virtual
#endif
	const unsigned char& isHTB(const unsigned int& ordinal) const{return ordinal < (unsigned int)m_htbVector.size() ? m_htbVector[ordinal] : regularHtb;}

	const Price* GetBorrowPrice(const unsigned int& ordinal) const{return ordinal < (unsigned int)m_stockLoanVector.size() ? &m_stockLoanVector[ordinal] : NULL;}
	unsigned int GetBorrowSize(const unsigned int& ordinal) const{return ordinal < (unsigned int)m_stockLoanVector.size() ? m_stockLoanVector[ordinal].GetQuantity() : 0;}
	unsigned char GetBorrowDiscountFlag(const unsigned int& ordinal) const{return ordinal < (unsigned int)m_stockLoanVector.size() ? m_stockLoanVector[ordinal].GetDiscountFlag() : 1;}

//	void SetHtb(unsigned int ordinal, bool htb);
	void SetHTB(const unsigned int& ordinal, const unsigned char& htb);
	void SetStockLoanInfo(const unsigned int& ordinal, const StockLoanInfo& info);
protected:
	unsigned __int64 m_numericSymbol;
//	BoolVector m_htbVector;
	UCharVector m_htbVector;
	StockLoanVector m_stockLoanVector;
};

class LineBufferArray;

const unsigned int MAX_SECURITY_NAME = 30;

enum MoveReportLevel : unsigned char//flags
{
	MRL_MOVES = 1,
	MRL_JOINS = 2,
};

enum GoodBadCode : unsigned char
{
	GBC_VERY_BAD,
	GBC_BAD,
	GBC_GOOD,
	GBC_VERY_GOOD,

	GBC_COUNT
};

#ifndef TAKION_NO_OPTIONS

enum OptionMarketCenter : unsigned char
{
	OPTION_NYS_AMEX				= 'A' - 'A',
	OPTION_BX					= 'B' - 'A',
	OPTION_CBOE					= 'C' - 'A',
	OPTION_GEM					= 'H' - 'A',
	OPTION_ISE					= 'I' - 'A',
	OPTION_MSE					= 'M' - 'A',//Miami
	OPTION_NYS_ARCA				= 'N' - 'A',
	OPTION_OPRA					= 'O' - 'A',
	OPTION_NASDAQ				= 'Q' - 'A',
	OPTION_NASDAQ_OMX_BX		= 'T' - 'A',
	OPTION_C2					= 'W' - 'A',
	OPTION_NASDAQ_OMX_PHLX		= 'X' - 'A',
	OPTION_BATS					= 'Z' - 'A',

	MC_COUNT_OPTION
};

enum OptionFlags : unsigned char
{
	OPTF_SUFFIX = 127,
	OPTF_CALL = 128,
};

enum OptionCallPutFlags : unsigned char
{
	OCPF_CALL,
	OCPF_PUT,

	OCPF_Count
};

enum OptionExpirationType : unsigned char
{
	OET_MONTHLY,
	OET_WEEKLY,
	OET_QUARTERLY,

	OET_Count
};

class TU_API OptionKey
{
public:
	static const unsigned int defaultContractSize;// = 100;
	explicit OptionKey(const unsigned int& strikePrice,
		const unsigned char& flags,
		const unsigned char& expirationDay,
		const unsigned char& expirationMonth,
		const unsigned char& expirationYear):
		m_strikePrice(strikePrice),
		m_flags(flags),
		m_expirationDay(expirationDay),
		m_expirationMonth(expirationMonth),
		m_expirationYear(expirationYear)
		{}
	explicit OptionKey(const unsigned int& strikePrice,
		const bool& call,
		const char& suffix,
		const unsigned char& expirationDay,
		const unsigned char& expirationMonth,
		const unsigned char& expirationYear):
		m_strikePrice(strikePrice),
		m_flags((call ? OPTF_CALL : '\0') | (suffix & OPTF_SUFFIX)),
		m_expirationDay(expirationDay),
		m_expirationMonth(expirationMonth),
		m_expirationYear(expirationYear)
		{}
	explicit OptionKey(const unsigned __int64& underlierSymbolNum,
		const unsigned __int64& rootSymbolNum,
		const unsigned __int64& optionBlock):
		m_strikePrice(0),
		m_flags((unsigned char)(optionBlock >> 48)),
		m_expirationDay((unsigned char)(optionBlock >> 40)),
		m_expirationMonth(m_flags),
		m_expirationYear((unsigned char)(optionBlock >> 56))
	{
		if(optionBlock)
		{
			unsigned int strikePrice = (unsigned int)optionBlock;
			unsigned int dollars = strikePrice / 1000;
			m_strikePrice = (dollars << 14) | (strikePrice - 1000 * dollars) * 10;
			if(m_flags < 'M')
			{
				m_flags = OPTF_CALL;
				m_expirationMonth -= 'A' - 1;
			}
			else
			{
				m_flags = '\0';
				m_expirationMonth -= 'L';
			}
			unsigned char suffix = CalculateSuffix(underlierSymbolNum, rootSymbolNum);
			m_flags |= (suffix & OPTF_SUFFIX);
		}
	}
	explicit OptionKey(const unsigned __int64& optionBlock,
		const unsigned char& suffix):
		m_strikePrice(0),
		m_flags(suffix & OPTF_SUFFIX),
		m_expirationDay((unsigned char)(optionBlock >> 40)),
		m_expirationMonth((unsigned char)(optionBlock >> 48)),
		m_expirationYear((unsigned char)(optionBlock >> 56))
	{
		if(optionBlock)
		{
			unsigned int strikePrice = (unsigned int)optionBlock;
			unsigned int dollars = strikePrice / 1000;
			m_strikePrice = (dollars << 14) | (strikePrice - 1000 * dollars) * 10;
			if(m_expirationMonth < 'M')
			{
				m_flags |= OPTF_CALL;
				m_expirationMonth -= 'A' - 1;
			}
			else
			{
				m_expirationMonth -= 'L';
			}
		}
	}
	explicit OptionKey(const char* str)
	{
		Parse(str);
	}
	explicit OptionKey(const unsigned __int64& optionKeyValue = 0):m_optionKeyValue(optionKeyValue){}
	virtual ~OptionKey(){}

	static unsigned char CalculateSuffix(const unsigned __int64& underlierSymbolNum, const unsigned __int64& rootSymbolNum)
	{
		if(underlierSymbolNum != rootSymbolNum)
		{
			const unsigned char* underlierCursor = (const unsigned char*)&underlierSymbolNum + 1;
			const unsigned char* rootCursor = (const unsigned char*)&rootSymbolNum + 1;
			for(unsigned char i = sizeof(underlierSymbolNum) - 1; i; --i, ++underlierCursor, ++rootCursor)
			{
				if(*underlierCursor != *rootCursor)
				{
//					m_flags |= (*rootCursor & OPTF_SUFFIX);
					return *rootCursor;
				}
			}
		}
		return '\0';
	}
	enum OptionParseError : unsigned char
	{
		OPE_OK,
		OPE_SUFFIX,
		OPE_MONTH,
		OPE_DAY,
		OPE_YEAR,
		OPE_CALLPUT,

		OPE_Count
	};
	virtual unsigned char Parse(const char* str)
	{
		m_optionKeyValue = 0;
		
		char flags = '\0';
		unsigned char month, day, year;

		char c = *str;
		if(c < ' ')return OPE_SUFFIX;
		if(c > ' ')flags |= (unsigned char)c & OPTF_SUFFIX;

		c = *++str;
		if(c < '0' || c > '9')return OPE_YEAR;
		year = (c - '0') * 10;

		c = *++str;
		if(c < '0' || c > '9')return OPE_YEAR;
		year += c - '0';

		c = *++str;
		if(c < '0' || c > '1')return OPE_MONTH;
		month = (c - '0') * 10;

		c = *++str;
		if(c < '0' || c > '9')return OPE_MONTH;
		month += c - '0';

		c = *++str;
		if(c < '0' || c > '3')return OPE_DAY;
		day = (c - '0') * 10;

		c = *++str;
		if(c < '0' || c > (day < 30 ? '9' : '1'))return OPE_DAY;
		day += c - '0';

		c = *++str;
		if(c == 'C' || c== 'c')flags |= OPTF_CALL;
		else if(c != 'P' && c != 'p')return OPE_CALLPUT;

		c = *++str;
		if(c)
		{
			Price price;
			TU_StrToPrice(price, str, 2);
			m_strikePrice = price.GetCompactPrice();
		}

		m_flags = flags;
		m_expirationMonth = month;
		m_expirationDay = day;
		m_expirationYear = year;
		return OPE_OK;
	}

	const unsigned char& GetFlags() const{return m_flags;}
//	bool isCall() const{return (m_flags & (1 << OPTF_CALL)) != '\0';}
	bool isCall() const{return (m_flags & OPTF_CALL) != '\0';}
	bool isPut() const{return !isCall();}
	unsigned char GetCallPutFlags() const{return isCall() ? 1 << OCPF_CALL : 1 << OCPF_PUT;}
//	bool isMini() const{return (m_flags & (1 << OPTF_MINI)) != '\0';}
	unsigned char GetSuffix() const{return m_flags & OPTF_SUFFIX;}
	static bool isSuffixValid(unsigned char suffix)
	{
		return !suffix || suffix >= 'A' && suffix <= 'Z' || suffix >= '0' && suffix <= '9';
	}
	static bool isDateValid(unsigned int year, unsigned int month, unsigned int day)
	{
		return TL_IsDateValid(year, month, day);// && !TL_IsDatePassed(year, month, day);
	}
	bool isValid() const
	{
		return isDateValid((unsigned int)m_expirationYear + 2000, m_expirationMonth, m_expirationDay) && isSuffixValid(GetSuffix()) && m_strikePrice > 0;
	}

	const unsigned int& GetStrikePrice() const{return m_strikePrice;}
//	unsigned char m_denominatorCode;
	const unsigned char& GetExpirationDay() const{return m_expirationDay;}
	const unsigned char& GetExpirationMonth() const{return m_expirationMonth;}
	const unsigned char& GetExpirationYear() const{return m_expirationYear;}

//	void SetCall(const bool& call){if(call)m_flags |= (1 << OPTF_CALL);else m_flags &= ~(1 << OPTF_CALL);}
	void SetCall(const bool& call){if(call)m_flags |= OPTF_CALL;else m_flags &= ~OPTF_CALL;}
	void SwapCall(){SetCall(!isCall());}
//	void SetMini(const bool& mini){if(mini)m_flags |= (1 << OPTF_MINI);else m_flags &= ~(1 << OPTF_MINI);}
	void SetSuffix(char suffix){m_flags = (m_flags & OPTF_CALL) | suffix;}
	void SetStrikePrice(const unsigned int& strikePrice){m_strikePrice = strikePrice;}
	void SetExpirationDay(const unsigned char& expirationDay){m_expirationDay = expirationDay;}
	void SetExpirationMonth(const unsigned char& expirationMonth){m_expirationMonth = expirationMonth;}
	void SetExpirationYear(const unsigned char& expirationYear){m_expirationYear = expirationYear;}

	bool operator==(const OptionKey& other) const{return m_optionKeyValue == other.m_optionKeyValue;}
	bool operator<(const OptionKey& other) const{return m_optionKeyValue < other.m_optionKeyValue;}
	bool operator>(const OptionKey& other) const{return m_optionKeyValue > other.m_optionKeyValue;}
	bool operator!=(const OptionKey& other) const{return m_optionKeyValue != other.m_optionKeyValue;}
	bool operator<=(const OptionKey& other) const{return m_optionKeyValue <= other.m_optionKeyValue;}
	bool operator>=(const OptionKey& other) const{return m_optionKeyValue >= other.m_optionKeyValue;}

	bool isEqualExceptCallPut(const OptionKey& other) const
	{
		return m_strikePrice == other.m_strikePrice
			&& GetExpirationDate() == other.GetExpirationDate()
			&& GetSuffix() == other.GetSuffix();
	}

	const unsigned __int64& GetOptionKeyValue() const{return m_optionKeyValue;}
	void SetOptionKeyValue(const unsigned __int64& keyValue){m_optionKeyValue = keyValue;}
//	bool isValid() const{return m_optionKeyValue != 0;}
	unsigned int GetHashKeyValue() const{return m_strikePrice * m_expirationMonth + ((unsigned int)m_expirationYear + m_expirationDay) * m_flags;}
	unsigned int GetExpirationDate() const{return (unsigned int)(m_optionKeyValue >> 40);}
	static const unsigned char defaultExpirationType = OET_MONTHLY;
	static const char defaultExpirationTypeChar = 'M';
//	static const unsigned int defaultExpirationDays = 0;
	virtual const unsigned char& GetExpirationType() const{return defaultExpirationType;}
	virtual const char& GetExpirationTypeChar() const{return defaultExpirationTypeChar;}
//	virtual const unsigned int& GetExpirationDays() const{return defaultExpirationDays;}
	void toString(std::string& str) const
	{
		char suffix = GetSuffix();
		if(suffix)
		{
			str += suffix;
			str += ' ';
		}
		str += isCall() ? "Call $" : "Put $";
		TU_PriceToStr(str, Price(m_strikePrice), 4, true, ' ', true);
		str += 'x';
		U_AppendTwoDigits(str, m_expirationMonth, '-');
		U_AppendTwoDigits(str, m_expirationDay, '-');
		U_AppendTwoDigits(str, m_expirationYear);
		const char& expirationTypeChar = GetExpirationTypeChar();
		if(expirationTypeChar != 'M')
		{
			str += ' ';
			str += expirationTypeChar;
		}
	}
	unsigned int CalculateContractSize() const
	{
		switch(m_flags & OPTF_SUFFIX)
		{
			case 0:
			return defaultContractSize;

			case '7':
			case '8':
			case '9':
			return 10;

			case 'J':
			return 1000;

			default:
			return defaultContractSize;
		}
	}
	unsigned __int64 CalculateOptionBlock() const
	{
		return (((unsigned __int64)m_expirationYear) << 56) | (((unsigned __int64)(m_expirationMonth + ((m_flags & OPTF_CALL) ? 'A' - 1 : 'L'))) << 48) | (((unsigned __int64)m_expirationDay) << 40) | ((m_strikePrice >> 14) * 1000 + (m_strikePrice & 0x3FFF) / 10);
	}
	static bool isOptionBlockValid(const unsigned __int64& optionBlock)
	{
		unsigned char monthCode = (unsigned char)(optionBlock >> 48);
		if(monthCode < 'A' || monthCode > 'X')return false;
		return isDateValid((unsigned int)(optionBlock >> 56) + 2000, monthCode < 'M' ? monthCode - ('A' - 1) : monthCode - 'L', (unsigned char)(optionBlock >> 40)) && (unsigned int)optionBlock > 0;
	}
	unsigned int CalculateExpirationDays() const
	{
		unsigned int today = TL_GetTodaysDate();
		unsigned int year1;
		unsigned int month1;
		unsigned int day1;
		TL_GetDateFrom1970(year1, month1, day1, today);
		int ret = TL_DateDiff(year1, month1, day1, (unsigned int)m_expirationYear + 2000, m_expirationMonth, m_expirationDay);
		return ret >= 0 ? ret : 0;
	}

	static void AddSuffixToSymbol(unsigned __int64& symbolNum, const char& suffix)
	{
		unsigned char i = sizeof(symbolNum) - 1;
		char* cursor = (char*)&symbolNum;
		for(++cursor; i; --i, ++cursor)
		{
			if(!*cursor)
			{
				*cursor = suffix;
				break;
			}
		}
	}
	static void RemoveSuffixFromSymbol(unsigned __int64& symbolNum)
	{
		unsigned char i = sizeof(symbolNum) - 1;
		char* cursor = (char*)&symbolNum;
		for(++cursor; i; --i, ++cursor)
		{
			if(!*cursor)
			{
				*(cursor - 1) = '\0';
				break;
			}
		}
	}

	static unsigned char CalculateExpirationTypeStatic(const unsigned char& expirationDay, const unsigned char& expirationMonth, const unsigned char& expirationYear)
	{
		unsigned int year = 2000 + expirationYear;
		unsigned int dayOfWeek = TL_GetDayOfWeek(year, expirationMonth, expirationDay);
		switch(dayOfWeek)
		{
			case 6:
			return OET_MONTHLY;

			case 5:
			switch(expirationMonth)
			{
				case 3:
				case 12:
				switch(TL_GetDayOfWeek(year, expirationMonth, 31))
				{
					case 0:
					return expirationDay == 29 ? OET_QUARTERLY : OET_WEEKLY;

					case 6:
					return expirationDay == 30 ? OET_QUARTERLY : OET_WEEKLY;

					case 5:
					return expirationDay == 31 ? OET_QUARTERLY : OET_WEEKLY;

					default:
					return OET_WEEKLY;
				}
				break;

				case 6:
				case 9:
				switch(TL_GetDayOfWeek(year, expirationMonth, 30))
				{
					case 0:
					return expirationDay == 28 ? OET_QUARTERLY : OET_WEEKLY;

					case 6:
					return expirationDay == 29 ? OET_QUARTERLY : OET_WEEKLY;

					case 5:
					return expirationDay == 30 ? OET_QUARTERLY : OET_WEEKLY;

					default:
					return OET_WEEKLY;
				}
				break;

				default:
				return OET_WEEKLY;
			}
			break;

			default:
			return OET_QUARTERLY;
		}
	}
	static unsigned char CalculateExpirationTypeAsCharStatic(const unsigned char& expirationType)
	{
		switch(expirationType)
		{
			case OET_MONTHLY:
			return 'M';

			case OET_WEEKLY:
			return 'W';

			default:
			return 'Q';
		}
	}
	unsigned char CalculateExpirationType() const
	{
		return CalculateExpirationTypeStatic(m_expirationDay, m_expirationMonth, m_expirationYear);
	}
	unsigned char CalculateExpirationTypeAsChar() const
	{
		return CalculateExpirationTypeAsCharStatic(CalculateExpirationTypeStatic(m_expirationDay, m_expirationMonth, m_expirationYear));
	}
	void GetOptionBlockAsString(std::string& optionSymbol, bool withSuffix) const
	{
		if(withSuffix)
		{
			unsigned char suffix = GetSuffix();
			optionSymbol += suffix ? (char)suffix : ' ';
		}
		U_AppendTwoDigits(optionSymbol, GetExpirationYear());
		U_AppendTwoDigits(optionSymbol, GetExpirationMonth());
		U_AppendTwoDigits(optionSymbol, GetExpirationDay());
		optionSymbol += isCall() ? 'C' : 'P';
		Price strikePrice(m_strikePrice);
		if(strikePrice.GetDollarFraction())
		{
			TU_PriceToStr(optionSymbol, strikePrice, 2, false);
		}
		else
		{
			char num[33];
			optionSymbol += U_UIntToStr(strikePrice.GetDollars(), num, sizeof(num));
		}
	}
protected:
	union
	{	
		unsigned __int64 m_optionKeyValue;
		struct
		{	
			unsigned int m_strikePrice;
//			bool m_call;
			unsigned char m_flags;
			unsigned char m_expirationDay;
			unsigned char m_expirationMonth;
			unsigned char m_expirationYear;
		};
	};
};

//AFX_INLINE UINT AFXAPI HashKey(ARG_KEY key)
/*
template<> AFX_INLINE UINT AFXAPI HashKey<OptionKey>(const OptionKey key)
{
	return key.GetHashKeyValue();
}
*/
template<> AFX_INLINE UINT AFXAPI HashKey<const OptionKey&>(const OptionKey& key)
{
	return key.GetHashKeyValue();
}

template<> inline size_t std::hash_value<OptionKey>(const OptionKey& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashKeyValue() ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value<const OptionKey>(const OptionKey& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashKeyValue() ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

class TU_API OptionSymbolKey : public OptionKey
{
public:
	explicit OptionSymbolKey(const unsigned __int64& symbolNum,
		const unsigned int& strikePrice,
		const bool& call,
		const char& suffix,
		const unsigned char& expirationDay,
		const unsigned char& expirationMonth,
		const unsigned char& expirationYear):
		OptionKey(strikePrice, (call ? OPTF_CALL : '\0') | (suffix & OPTF_SUFFIX), expirationDay, expirationMonth, expirationYear),
		m_symbolNum(symbolNum)
		{}
	explicit OptionSymbolKey(const unsigned __int64& symbolNum,
		const unsigned int& strikePrice,
		const bool& call,
		const unsigned char& expirationDay,
		const unsigned char& expirationMonth,
		const unsigned char& expirationYear):
		OptionKey(strikePrice, call ? OPTF_CALL : '\0', expirationDay, expirationMonth, expirationYear),
		m_symbolNum(symbolNum)
		{}
	explicit OptionSymbolKey(const unsigned __int64& symbolNum,
		const OptionKey& optionKey):
		OptionKey(optionKey),
		m_symbolNum(symbolNum)
		{}
	explicit OptionSymbolKey(const unsigned __int64& underlierSymbolNum,
		const unsigned __int64& rootSymbolNum,
		const unsigned __int64& optionBlock):
		OptionKey(underlierSymbolNum, rootSymbolNum, optionBlock),
		m_symbolNum(underlierSymbolNum)
		{}
	explicit OptionSymbolKey(const unsigned __int64& underlierSymbolNum,
		const unsigned __int64& optionBlock,
		const unsigned char& suffix):
		OptionKey(optionBlock, suffix),
		m_symbolNum(underlierSymbolNum)
		{}
	explicit OptionSymbolKey(const unsigned __int64& symbolNum = 0):m_symbolNum(symbolNum){}
	explicit OptionSymbolKey(const char* str)
	{
		Parse(str);
	}
//	virtual ~OptionSymbolKey(){}

	virtual unsigned char Parse(const char* str)
	{
		m_symbolNum = 0;
		char* dst = (char*)&m_symbolNum;
		char c = *str;
		for(unsigned int i = sizeof(m_symbolNum) - 1; c && c != ' ' && i; --i, ++dst, c = *++str)
		{
			*dst = c;
		}
		return !m_symbolNum ? OPE_Count : c == ' ' ? OptionKey::Parse(++str) : OPE_OK;
	}
	const unsigned __int64& GetSymbolNum() const{return m_symbolNum;}
	void SetSymbolNum(const unsigned __int64& symbolNum){m_symbolNum = symbolNum;}
	void AddSuffix(const char& suffix)
	{
		AddSuffixToSymbol(m_symbolNum, suffix);
	}

	static void AddSuffixToSymbolAt(unsigned __int64& symbolNum, const char& suffix, const unsigned char& at)
	{
		if(at < sizeof(symbolNum))
		{
			*((char*)&symbolNum + at) = suffix;
		}
	}

	void AddSuffixAt(const char& suffix, const unsigned char& at)
	{
		if(at < sizeof(m_symbolNum))
		{
			*((char*)&m_symbolNum + at) = suffix;
		}
	}
	unsigned char GetSymbolLength() const
	{
		unsigned char i = 1;//sizeof(m_symbolNum) - 1;
		char* cursor = (char*)&m_symbolNum;
		for(++cursor; i < sizeof(m_symbolNum); ++i, ++cursor)
		{
			if(!*cursor)
			{
				break;
			}
		}
		return i;
	}

	const char* GetSymbol() const{return (const char*)&m_symbolNum;}

//	bool isValid() const{return m_symbolNum != 0 && OptionKey::isValid();}

	bool operator==(const OptionSymbolKey& other) const{return m_symbolNum == other.m_symbolNum && OptionKey::operator==(other);}
	bool operator<(const OptionSymbolKey& other) const{return m_symbolNum < other.m_symbolNum || m_symbolNum == other.m_symbolNum && OptionKey::operator<(other);}
	bool operator>(const OptionSymbolKey& other) const{return m_symbolNum > other.m_symbolNum || m_symbolNum == other.m_symbolNum && OptionKey::operator>(other);}
	bool operator!=(const OptionSymbolKey& other) const{return !operator==(other);}
	bool operator<=(const OptionSymbolKey& other) const{return !operator>(other);}
	bool operator>=(const OptionSymbolKey& other) const{return !operator<(other);}

	unsigned int GetHashKeyValue() const{return m_strikePrice * m_expirationMonth + m_expirationYear + (unsigned short)m_symbolNum;}
	void toString(std::string& str) const
	{
		str += (const char*)&m_symbolNum;
		str += ' ';
		OptionKey::toString(str);
	}
	bool isValid() const
	{
		return OptionKey::isValid() && U_IsOptionSymbolValid((const char*)&m_symbolNum);
	}
protected:
	unsigned __int64 m_symbolNum;
};

template<> AFX_INLINE UINT AFXAPI HashKey<const OptionSymbolKey&>(const OptionSymbolKey& key)
{
	return key.GetHashKeyValue();
}

template<> inline size_t std::hash_value<OptionSymbolKey>(const OptionSymbolKey& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashKeyValue() ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

class OptionSymbolBlockKey//for Position collections
{
public:
	explicit OptionSymbolBlockKey(const unsigned __int64& rootSymbolNum, const unsigned __int64& optionBlock):
		m_rootSymbolNum(rootSymbolNum),
		m_optionBlock(optionBlock)
	{
	}

	explicit OptionSymbolBlockKey():
		m_rootSymbolNum(0),
		m_optionBlock(0)
	{
	}

	void SetValues(const unsigned __int64& rootSymbolNum, const unsigned __int64& optionBlock)
	{
		m_rootSymbolNum = rootSymbolNum;
		m_optionBlock = optionBlock;
	}

	explicit OptionSymbolBlockKey(const unsigned __int64& underlierSymbolNum, const OptionKey& key):
		m_rootSymbolNum(underlierSymbolNum)
	{
		SetOptionKey(key);
	}
	explicit OptionSymbolBlockKey(const OptionKey& key, const unsigned __int64& rootSymbolNum):
		m_rootSymbolNum(rootSymbolNum)
	{
		SetOptionKeyValue(key);
	}

	explicit OptionSymbolBlockKey(const char* cursor, const unsigned __int64& rootSymbolNum):
		m_rootSymbolNum(rootSymbolNum)
	{
		ParseOptionBlock(cursor);
	}

	explicit OptionSymbolBlockKey(const char* cursor)
	{
		Parse(cursor);
	}

	void Parse(const char* cursor)
	{
		m_rootSymbolNum = 0;
		char* cursorDest = (char*)&m_rootSymbolNum;
		char c = *cursor;

		for(unsigned char i = sizeof(m_rootSymbolNum) - 1; c != ' ' && i; --i, ++cursorDest, c = *++cursor)*cursorDest = c;

		if(c == ' ' && m_rootSymbolNum)ParseOptionBlock(++cursor);
		else m_optionBlock = 0;
	}

	void ParseOptionBlock(const char* cursor)
	{
		m_optionBlock = ParseOptionBlockStatic(cursor);
	}
	static unsigned __int64 ParseOptionBlockStatic(const char* cursor)
	{
		char c = *cursor;
		if(c < '0' || c > '9')return 0;

		unsigned char dateToken = (c - '0') * 10;

		c = *++cursor;
		if(c < '0' || c > '9')return 0;
		dateToken += c - '0';

		unsigned __int64 optionBlock = (unsigned __int64)dateToken << 56;//year

		c = *++cursor;
		if(c < '0' || c > '1')return 0;
		unsigned char monthToken = (c - '0') * 10;

		c = *++cursor;
		if(c < '0' || c > '9')return 0;
		monthToken += c - '0';

		c = *++cursor;
		if(c < '0' || c > '3')return 0;
		dateToken = (c - '0') * 10;

		c = *++cursor;
		if(c < '0' || c > (dateToken < 30 ? '9' : '1'))return 0;
		dateToken += c - '0';
		optionBlock |= (unsigned __int64)dateToken << 40;//day

		c = *++cursor;
		if(c == 'C' || c == 'c')monthToken += ('A' - 1);
		else if(c == 'P' || c == 'p')monthToken += 'L';
		else return 0;

		optionBlock |= (unsigned __int64)monthToken << 48;//month

		c = *++cursor;
		if(!c)return 0;

		Price price;
		TU_StrToPrice(price, cursor, 2);
		return optionBlock | (price.GetDollars() * 1000 + price.GetDollarFraction() / (Price::divider / 1000));
	}

	bool isValid() const
	{
		return OptionKey::isOptionBlockValid(m_optionBlock) && U_IsOptionSymbolValid((const char*)&m_rootSymbolNum);
	}
	void SetOptionKeyValue(const OptionKey& key)
	{
		m_optionBlock = key.CalculateOptionBlock();
	}

	void SetOptionKey(const OptionKey& key)
	{
		char suffix = key.GetSuffix();
		if(suffix)OptionSymbolKey::AddSuffixToSymbol(m_rootSymbolNum, suffix);
		SetOptionKeyValue(key);
	}

	void SetOptionKey(const OptionKey& key, const unsigned char& at)
	{
		OptionSymbolKey::AddSuffixToSymbolAt(m_rootSymbolNum, key.GetSuffix(), at);
		SetOptionKeyValue(key);
	}
	const unsigned __int64& GetRootSymbolNum() const{return m_rootSymbolNum;}
	const unsigned __int64& GetOptionBlock() const{return m_optionBlock;}
	bool operator==(const OptionSymbolBlockKey& other) const{return m_optionBlock == other.m_optionBlock && m_rootSymbolNum == other.m_rootSymbolNum;}
	bool operator<(const OptionSymbolBlockKey& other) const{return m_optionBlock < other.m_optionBlock || m_optionBlock == other.m_optionBlock && m_rootSymbolNum < other.m_rootSymbolNum;}
	bool operator>(const OptionSymbolBlockKey& other) const{return m_optionBlock > other.m_optionBlock || m_optionBlock == other.m_optionBlock && m_rootSymbolNum > other.m_rootSymbolNum;}
	bool operator!=(const OptionSymbolBlockKey& other) const{return !operator==(other);}
	bool operator<=(const OptionSymbolBlockKey& other) const{return !operator>(other);}
	bool operator>=(const OptionSymbolBlockKey& other) const{return !operator<(other);}
	unsigned int GetHashKeyValue() const{return (unsigned int)(m_optionBlock >> 32) + (unsigned int)m_optionBlock + (unsigned int)m_rootSymbolNum;}
	static void ConvertOptionBlockToString(std::string& str, const unsigned __int64& optionBlock)
	{
		unsigned char expMonth = (unsigned char)(optionBlock >> 48);
		bool call = expMonth < 'M';
		str += call ? "Call $" : "Put $";
		unsigned int strikePrice = (unsigned int)optionBlock;
		unsigned int dollars = strikePrice / 1000;
		TU_PriceToStr(str, Price(dollars, (strikePrice - 1000 * dollars) * (Price::divider / 1000)), 4, true, ' ', true);
		str += 'x';
		U_AppendTwoDigits(str, call ? expMonth - ('A' - 1) : expMonth - 'L', '-');
		U_AppendTwoDigits(str, (unsigned char)(optionBlock >> 40), '-');
		U_AppendTwoDigits(str, (unsigned char)(optionBlock >> 56));
	}
	void OptionBlockToString(std::string& str) const
	{
		ConvertOptionBlockToString(str, m_optionBlock);
	}
	void toString(std::string& str) const
	{
		str += (const char*)m_rootSymbolNum;
		str += ' ';
		OptionBlockToString(str);
	}
	static void ConvertOptionBlockToInstrumentString(std::string& str, const unsigned __int64& optionBlock)
	{
		unsigned char expMonth = (unsigned char)(optionBlock >> 48);
		bool call = expMonth < 'M';
		U_AppendTwoDigits(str, (unsigned char)(optionBlock >> 56));
		U_AppendTwoDigits(str, call ? expMonth - ('A' - 1) : expMonth - 'L');
		U_AppendTwoDigits(str, (unsigned char)(optionBlock >> 40));
		str += call ? 'C' : 'P';
		unsigned int strikePrice = (unsigned int)optionBlock;
		unsigned int dollars = strikePrice / 1000;
		TU_PriceToStr(str, Price(dollars, (strikePrice - 1000 * dollars) * (Price::divider / 1000)), 4, false, '\0', true);
	}
	void OptionBlockToInstrumentString(std::string& str) const
	{
		ConvertOptionBlockToInstrumentString(str, m_optionBlock);
	}
	void toInstrumentString(std::string& str) const
	{
		str += (const char*)m_rootSymbolNum;
		str += ' ';
		OptionBlockToInstrumentString(str);
	}
protected:
	unsigned __int64 m_rootSymbolNum;
	unsigned __int64 m_optionBlock;
};

template<> AFX_INLINE UINT AFXAPI HashKey<const OptionSymbolBlockKey&>(const OptionSymbolBlockKey& key)
{
	return key.GetHashKeyValue();
}

template<> inline size_t std::hash_value<OptionSymbolBlockKey>(const OptionSymbolBlockKey& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashKeyValue() ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

class TU_API UnderlierInfo
{
public:
	UnderlierInfo():
		m_callSharesSoldPotential(0),
		m_putSharesSoldPotential(0)
	{}
	const unsigned int& GetCallSharesSoldPotential() const{return m_callSharesSoldPotential;}
	const unsigned int& GetPutSharesSoldPotential() const{return m_putSharesSoldPotential;}
	void AddCallSharesSoldPotential(unsigned int shares){m_callSharesSoldPotential += shares;}
	void SubtractCallSharesSoldPotential(unsigned int shares)
	{
		if(m_callSharesSoldPotential >= shares)m_callSharesSoldPotential -= shares;
		else m_callSharesSoldPotential = 0;
	}
	void AddPutSharesSoldPotential(unsigned int shares){m_putSharesSoldPotential += shares;}
	void SubtractPutSharesSoldPotential(unsigned int shares)
	{
		if(m_putSharesSoldPotential >= shares)m_putSharesSoldPotential -= shares;
		else m_putSharesSoldPotential = 0;
	}
protected:
	unsigned int m_callSharesSoldPotential;
	unsigned int m_putSharesSoldPotential;
};

class TU_API OptionSymbolBlock : public OptionSymbolKey//for Position
{
public:
	explicit OptionSymbolBlock(const unsigned __int64& underlierSymbolNum,
//		const unsigned int& contractSize,
		const unsigned int& strikePrice,
		const bool& call,
		const char& suffix,
		const unsigned char& expirationDay,
		const unsigned char& expirationMonth,
		const unsigned char& expirationYear):
		OptionSymbolKey(underlierSymbolNum, strikePrice, call, suffix, expirationDay, expirationMonth, expirationYear),
		m_optionBlock(CalculateOptionBlock()),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_expirationDays(CalculateExpirationDays()),
		m_expirationType(CalculateExpirationType()),
		m_expirationTypeChar(CalculateExpirationTypeAsCharStatic(m_expirationType)),
		m_underlierPosition(NULL)
	{}
	explicit OptionSymbolBlock(const unsigned __int64& underlierSymbolNum,
//		const unsigned int& contractSize,
		const OptionKey& optionKey):
		OptionSymbolKey(underlierSymbolNum, optionKey),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_optionBlock(CalculateOptionBlock()),
		m_expirationDays(CalculateExpirationDays()),
		m_expirationType(CalculateExpirationType()),
		m_expirationTypeChar(CalculateExpirationTypeAsCharStatic(m_expirationType)),
		m_underlierPosition(NULL)
	{}
	explicit OptionSymbolBlock(const unsigned __int64& underlierSymbolNum,
//		const unsigned int& contractSize,
		const unsigned __int64& rootSymbolNum,
		const unsigned __int64& optionBlock):
		OptionSymbolKey(underlierSymbolNum, rootSymbolNum, optionBlock),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_optionBlock(optionBlock),
		m_expirationDays(CalculateExpirationDays()),
		m_expirationType(CalculateExpirationType()),
		m_expirationTypeChar(CalculateExpirationTypeAsCharStatic(m_expirationType)),
		m_underlierPosition(NULL)
	{}
	explicit OptionSymbolBlock(const unsigned __int64& underlierSymbolNum,
//		const unsigned int& contractSize,
		const unsigned __int64& optionBlock,
		const unsigned char& suffix):
		OptionSymbolKey(underlierSymbolNum, optionBlock, suffix),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_optionBlock(optionBlock),
		m_expirationDays(CalculateExpirationDays()),
		m_expirationType(CalculateExpirationType()),
		m_expirationTypeChar(CalculateExpirationTypeAsCharStatic(m_expirationType)),
		m_underlierPosition(NULL)
	{}
	explicit OptionSymbolBlock(const unsigned __int64& underlierSymbolNum = 0)://, const unsigned int& contractSize = 100):
		OptionSymbolKey(underlierSymbolNum),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_optionBlock(0),
		m_expirationDays(0),
		m_expirationType(0),
		m_expirationTypeChar(0),
		m_underlierPosition(NULL)
	{}
	const unsigned __int64& GetOptionBlock() const{return m_optionBlock;}

	virtual const unsigned char& GetExpirationType() const{return m_expirationType;}
	virtual const char& GetExpirationTypeChar() const{return m_expirationTypeChar;}
	const unsigned int& GetExpirationDays() const{return m_expirationDays;}
	const unsigned int& GetContractSize() const{return m_contractSize;}

	const Position* GetUnderlierPosition() const{return m_underlierPosition;}
	Position* GetUnderlierPosition(){return m_underlierPosition;}
	void SetUnderlierPosition(Position* underlierPosition){if(!m_underlierPosition && underlierPosition)m_underlierPosition = underlierPosition;}

	unsigned char SetUnderlierSymbol(const unsigned __int64& underlierSymbolNum)
	{
		unsigned char suffix = CalculateSuffix(underlierSymbolNum, m_symbolNum);
		unsigned int oldSuffix = m_flags & OPTF_SUFFIX;
		if(suffix != oldSuffix)
		{
			if(suffix)
			{
				m_flags |= (suffix & OPTF_SUFFIX);
			}
			else
			{
				m_flags &= ~OPTF_SUFFIX;
			}
			m_contractSize = CalculateContractSize();
			return suffix;
		}
		return 0xFF;
	}

protected:
	unsigned __int64 m_optionBlock;
	unsigned int m_contractSize;
	unsigned int m_expirationDays;
	unsigned char m_expirationType;
	char m_expirationTypeChar;
	Position* m_underlierPosition;
};

class Underlier;

class TU_API OptionInfo : public OptionKey, public Observable
{
friend class Security;
friend class SecurityDerived;
public:
	OptionInfo(Underlier* underlier,
//		Security* security,
		const unsigned int& strikePrice = 0,
		const unsigned char& flags = '\0',
		const unsigned char& expirationDay = '\0',
		const unsigned char& expirationMonth = '\0',
		const unsigned char& expirationYear = '\0',
		const unsigned int& openInterestVolume = 0,
		const unsigned int& impliedVolatility = 0,
		const int& delta = 0,
		const int& vega = 0,
		const int& theta = 0);

	OptionInfo(Underlier* underlier,
//		Security* security,
		const OptionKey& optionKey,
		const unsigned int& openInterestVolume = 0,
		const unsigned int& impliedVolatility = 0,
		const int& delta = 0,
		const int& vega = 0,
		const int& theta = 0);

	OptionInfo(const unsigned __int64& optionBlock,
		const unsigned __int64& underlierNumericSymbol,
		const unsigned char& suffix);
	Underlier* GetUnderlier(){return m_underlier;}
	const Underlier* GetUnderlier() const{return m_underlier;}

	Security* GetSecurity(){return m_security;}
	const Security* GetSecurity() const{return m_security;}

	const unsigned int& GetOpenInterestVolume() const{return m_openInterestVolume;}
	const unsigned int& GetImpliedVolatility() const{return m_impliedVolatility;}
	const int& GetDelta() const{return m_delta;}
	const int& GetVega() const{return m_vega;}
	const int& GetTheta() const{return m_theta;}

	void SetOpenInterestVolume(const unsigned int& openInterestVolume){m_openInterestVolume = openInterestVolume;}
	void SetImpliedVolatility(const unsigned int& impliedVolatility){m_impliedVolatility = impliedVolatility;}
	void SetDelta(const int& delta){m_delta = delta;}
	void SetVega(const int& vega){m_vega = vega;}
	void SetTheta(const int& theta){m_theta = theta;}
	virtual const unsigned char& GetExpirationType() const{return m_expirationType;}
	virtual const char& GetExpirationTypeChar() const{return m_expirationTypeChar;}
	const unsigned int& GetExpirationDays() const{return m_expirationDays;}
	LONG isUnsubscribable() const{return m_unsubscribable;}

	bool CanUnsubscribe() const
	{
		return m_unsubscribable <= 0;// && isObservableEmpty();
	}

	void AddInThreadObserver(Observer* o) const;

//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;

	void RemoveInThreadObserver(Observer* o) const;

	void NotifyInThreadObservers(const Message* message, const Message* info, const Observable* from) const
	{
		if(!m_inThreadObservable.isObservableEmpty())
		{
			m_lockInThreadObservable.LockInquiryWait();
			m_inThreadObservable.NotifyObservers(message, info, from);
			m_lockInThreadObservable.UnlockInquiry();
		}
	}

	LONG IncrementUnsubscribable() const{return InterlockedIncrement(&m_unsubscribable);}
//	LONG DecrementUnsubscribable(bool unsubscribeImmediately = false){return 1;}
	LONG DecrementUnsubscribable() const{return InterlockedDecrement(&m_unsubscribable);}
	void NullifyUnsubscribable() const{InterlockedExchange(&m_unsubscribable, 0);}

	const unsigned __int64& GetUnderlierNumericSymbol() const{return m_underlierNumericSymbol;}
	const unsigned __int64& GetOptionBlock() const{return m_optionBlock;}
//	const unsigned __int64& GetUnderlierNumericSymbol() const;
//	const char* GetUnderlierSymbol() const;
//	const std::string& GetUnderlierSymbolStr() const;
	const unsigned int& GetContractSize() const{return m_contractSize;}
protected:
	void SetSecurity(Security* security);
	void SetUnderlier(Underlier* underlier);
	bool SetUnderlierSymbol(const unsigned __int64& underlierSymbolNum);
	virtual void OnObserverAdded(Observer* o) const;
	virtual void OnObserverRemoved(Observer* o) const;
	Underlier* m_underlier;
	Security* m_security;
	unsigned __int64 m_underlierNumericSymbol;
	unsigned __int64 m_optionBlock;
	unsigned int m_contractSize;
	unsigned int m_expirationDays;
	unsigned int m_openInterestVolume;
	unsigned int m_impliedVolatility;
	int m_delta;
	int m_vega;
	int m_theta;
	unsigned char m_expirationType;
	char m_expirationTypeChar;

	Observable m_inThreadObservable;
	TakionLockMultithread m_lockInThreadObservable;
	mutable volatile LONG m_unsubscribable;
};

#endif

class TU_API Security : public HTB, public Observable
{
#ifndef TAKION_NO_OPTIONS
friend class OptionInfo;
#endif
public:
	virtual ~Security();

	static const Price zeroPrice;
	static const SignedPrice zeroSignedPrice;
	static const std::string stringZero;
	static const unsigned __int64 uint64Zero;
	static const unsigned int uintZero;
	static const unsigned int uintOne;
	static const unsigned char ucharZero;
	static const bool boolFalse;
	static const int intZero;
	static const char space;

	virtual bool CreateIsoSnapshot(std::string& isoSnapshot, bool buy, const Price& limitPrice, bool lock, bool stopIfOrderIsNotInside, bool& isInside, Price& topPrice) const{return false;}

	unsigned char GetPrintFlags(char saleCondition1, char saleCondition2, char saleCondition3, char saleCondition4, char marketCenter, bool firstMarketOpenPriceSet) const;//4 - last; 8 - volume, 16 - high/low, 1 and 2 - always set

	typedef std::multimap<unsigned int, HistoricalPrint> TimeHistoricalPrintMap;
//	typedef std::map<unsigned __int64, HistoricalPrint> HistoricalPrintMap;
	typedef std::map<unsigned __int64, TimeHistoricalPrintMap::iterator> HistoricalPrintMap;
	virtual const HistoricalPrintMap* GetHistoricalPrintMap() const{return NULL;}
	virtual const TimeHistoricalPrintMap* GetTimeHistoricalPrintMap() const{return NULL;}

	virtual unsigned int GetHistoricalPrintRequestId() const{return 0;}
	virtual void LoadHistoricalPrints(unsigned int& requestId) const{requestId = 0;}
	virtual void ClearHistoricalPrints(){}

	virtual bool isSubscribable() const{return false;}

	virtual HANDLE GetThreadHandle() const{return NULL;}
	virtual unsigned int GetThreadId() const{return 0;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}

//	virtual unsigned int GetInvalidateLevel1Ordinal() const{return 0;}
//	virtual unsigned int GetUpdateLevel1Ordinal() const{return 0;}

//	virtual unsigned int GetAttributionMask() const{return 0;}
//	virtual void SetAttributionMask(unsigned int mask){}

	virtual void GetProtectedMarketSnapshot(bool bid, std::string& snapshot) const{}

	virtual void NextDayStarted(){}

	virtual bool HasPrints() const{return m_lastPrice != 0;}

	const unsigned short& GetSecurityCode() const{return m_securityCode;}
	virtual bool isLoaded() const{return m_loaded;}
	virtual SecurityType GetSecurityType() const = 0;

	const char* GetName() const{return m_name.c_str();}
	const std::string& GetNameStr() const{return m_name;}
	const unsigned int& GetRoundLot() const{return m_roundLot;}
	const bool& isRoundLotsOnly() const{return m_roundLotsOnly;}

	virtual bool isMarketDataStock() const{return true;}
	virtual const unsigned int& GetTierSize() const{return m_roundLot;}

	virtual const LineBufferArray* GetUnappliedMessages() const{return NULL;}

//Level2 should be locked before you use the TakionIterator* returned by the 4 function below
	virtual TakionIterator* GetBidIterator(){return NULL;}
	virtual TakionIterator* GetAskIterator(){return NULL;}
	virtual TakionIterator* GetBidAllQuotesIterator(){return NULL;}
	virtual TakionIterator* GetAskAllQuotesIterator(){return NULL;}
//
	const char& GetMarketCategory() const{return m_marketCategory;}
	const unsigned int& GetMarketCategoryFilter() const{return m_marketCategoryFilter;}
	const char& GetFinancialStatus() const{return m_financialStatus;}
	const char& GetPrimaryExchange() const{return m_primaryExchange;}
	const unsigned char& GetPrimaryExchangeFlag() const{return m_primaryExchangeFlag;}

	const char* GetPrimaryExchangeName() const;
	const unsigned int& GetPrimaryExchangeNumericName() const;
	const unsigned int& GetTradingActionReason() const{return m_tradingActionReason;}
	const char& GetTradingState() const{return m_tradingState;}
	const unsigned __int64& GetVolume() const{return m_volume;}
	const unsigned __int64& GetPrimaryExchangeVolume() const{return m_primaryExchangeVolume;}
	const unsigned __int64& GetPrimaryExchangeMhVolume() const{return m_primaryExchangeMhVolume;}
	const unsigned __int64& GetYesterdaysVolume() const{return m_yesterdaysVolume;}

	const char& GetShortSaleThresholdIndicator() const{return m_shortSaleThresholdIndicator;}//'Y', 'N'
	const char& GetRegSHOTestIndicator() const{return m_regSHOTestIndicator;}//'0', '1', '2'
	const unsigned short& GetSplitNumerator() const{return m_splitNumerator;}
	const unsigned short& GetSplitDenominator() const{return m_splitDenominator;}
	const unsigned int& GetSplit() const{return m_split;}
	const Price& GetDividend() const{return m_dividend;}

	const Price& GetLrpLow() const{return m_lrpLow;}
	const Price& GetLrpHigh() const{return m_lrpHigh;}
	const unsigned int& GetLrpLowTime() const{return m_lrpLowTime;}
	const unsigned int& GetLrpHighTime() const{return m_lrpHighTime;}
	const short& GetLrpLowDelay() const{return m_lrpLowDelay;}
	const short& GetLrpHighDelay() const{return m_lrpHighDelay;}
	const bool& isLrpLowHistorical() const{return m_lrpLowHistorical;}
	const bool& isLrpHighHistorical() const{return m_lrpHighHistorical;}

	const Price& GetLuldLow() const{return m_luldLow;}
	const Price& GetLuldHigh() const{return m_luldHigh;}
	const unsigned int& GetLuldLowTime() const{return m_luldLowTime;}
	const unsigned int& GetLuldHighTime() const{return m_luldHighTime;}
	const short& GetLuldLowDelay() const{return m_luldLowDelay;}
	const short& GetLuldHighDelay() const{return m_luldHighDelay;}
	const bool& isLuldLowHistorical() const{return m_luldLowHistorical;}
	const bool& isLuldHighHistorical() const{return m_luldHighHistorical;}

	const bool& isOpenSaleCondition() const{return m_openSaleCondition;}
	const bool& isPrimaryOpenSaleCondition() const{return m_primaryOpenSaleCondition;}
	const bool& isPrimarySourceOpenPrint() const{return m_primarySourceOpenPrint;}

	const char& GetRpiIndicator() const{return m_rpiIndicator;}
	const unsigned int& GetTradeDisseminationTime() const{return m_tradeDisseminationTime;}

	const unsigned int& GetL2Bid() const{return m_l2Bid;}
	const unsigned int& GetL2Ask() const{return m_l2Ask;}
	const unsigned int& GetL2BidSize() const{return m_l2BidSize;}
	const unsigned int& GetL2AskSize() const{return m_l2AskSize;}

	const unsigned int& GetL1Bid() const{return m_l1Bid;}
	const unsigned int& GetL1Ask() const{return m_l1Ask;}

	const unsigned int& GetNysBid() const{return m_nysBid;}
	const unsigned int& GetNysAsk() const{return m_nysAsk;}
	const unsigned int& GetNysBidSize() const{return m_nysBidSize;}
	const unsigned int& GetNysAskSize() const{return m_nysAskSize;}
	const unsigned int& GetNysLastPrice() const{return m_nysLastPrice;}
	const unsigned int& GetNysLastTradeSize() const{return m_nysLastTradeSize;}
	const unsigned int& GetNysHighPrice() const{return m_nysHighPrice;}
	const unsigned int& GetNysLowPrice() const{return m_nysLowPrice;}

	const unsigned int& GetAmxBid() const{return m_amxBid;}
	const unsigned int& GetAmxAsk() const{return m_amxAsk;}
	const unsigned int& GetAmxBidSize() const{return m_amxBidSize;}
	const unsigned int& GetAmxAskSize() const{return m_amxAskSize;}
	const unsigned int& GetAmxLastPrice() const{return m_amxLastPrice;}
	const unsigned int& GetAmxLastTradeSize() const{return m_amxLastTradeSize;}

	const unsigned int& GetAmxOrNysBid() const{return m_primaryExchange == PE_AMEX ? m_amxBid : m_nysBid;}
	const unsigned int& GetAmxOrNysAsk() const{return m_primaryExchange == PE_AMEX ? m_amxAsk : m_nysAsk;}
	const unsigned int& GetAmxOrNysBidSize() const{return m_primaryExchange == PE_AMEX ? m_amxBidSize : m_nysBidSize;}
	const unsigned int& GetAmxOrNysAskSize() const{return m_primaryExchange == PE_AMEX ? m_amxAskSize : m_nysAskSize;}
	const unsigned int& GetAmxOrNysLastPrice() const{return m_primaryExchange == PE_AMEX ? m_amxLastPrice : m_nysLastPrice;}
	const unsigned int& GetAmxOrNysLastTradeSize() const{return m_primaryExchange == PE_AMEX ? m_amxLastTradeSize : m_nysLastTradeSize;}

	const unsigned int& GetNsdqLastPrice() const{return m_nsdqLastPrice;}
	const unsigned int& GetNsdqLastTradeSize() const{return m_nsdqLastTradeSize;}

	const unsigned int& GetLastPrice() const{return m_lastPrice;}
	const unsigned int& GetClosePriceCompact() const{return m_closePriceCompact;}
	const unsigned int& GetTodaysClosePriceCompact() const{return m_todaysClosePriceCompact;}
	const unsigned int& GetOpenPriceCompact() const{return m_openPriceCompact;}
//	const unsigned int& GetPrimaryOpenPriceCompact() const{return m_primaryOpenPriceCompact;}
	const unsigned int& GetQOpenPriceCompact() const{return m_openSaleCondition ? m_openPriceCompact : uintZero;}
	const unsigned int& GetPrimaryQOpenPriceCompact() const{return m_primaryOpenPriceCompact;}
	const unsigned int& GetPrimarySourceOpenPriceCompact() const{return m_primarySourceOpenPrint ? m_openPriceCompact : uintZero;}
	const unsigned int& GetLastOrClosePrice() const{return m_lastPrice ? m_lastPrice : m_closePriceCompact;}
	const unsigned int& GetLastNbboPrintPrice() const{return m_lastNbboPrintPrice;}
	const unsigned int& GetLastNbboPrintOrClosePrice() const{return m_lastNbboPrintPrice ? m_lastNbboPrintPrice : m_closePriceCompact;}
	bool isPriceNbbo(const Price& price) const{return Price(m_l1Bid) <= price && price <= Price(m_l1Ask);}
	const Price& GetPmiBid() const{return m_pmiBid;}
	const Price& GetPmiAsk() const{return m_pmiAsk;}
	const bool& isOpen() const{return m_open;}
	const Price& GetOpenPrice() const{return m_openPrice;}
	const Price& GetPrimaryQOpenPrice() const{return m_primaryOpenPrice;}
	const Price& GetQOpenPrice() const{return m_openSaleCondition ? m_openPrice : zeroPrice;}
	const Price& GetPrimarySourceOpenPrice() const{return m_primarySourceOpenPrint ? m_openPrice : zeroPrice;}
	const Price& GetClosePrice() const{return m_closePrice;}
	const SignedPrice& GetNetChange() const{return m_netChange;}
	const SignedPrice& GetNiteChange() const{return m_niteChange;}
	const SignedPrice& GetOpenChange() const{return m_openChange;}
	const SignedPrice& GetQOpenChange() const{return m_openSaleCondition ? m_openChange : zeroSignedPrice;}
	const SignedPrice& GetPrimarySourceOpenChange() const{return m_primarySourceOpenPrint ? m_openChange : zeroSignedPrice;}
	const SignedPrice& GetTodaysCloseChange() const{return m_todaysCloseChange;}
	const Price& GetHighPrice() const{return m_highPrice;}
	const Price& GetLowPrice() const{return m_lowPrice;}
//	const SignedPrice& GetLastPriceInRange() const{return m_lastPriceInRange;}
	const Price& GetPriceRange() const{return m_priceRange;}
	const Price& GetExtendedPriceRange() const{return m_extendedPriceRange;}

	const SignedPrice& GetLastPriceInRangePercent() const{return m_lastPriceInRangePercent;}
	const Price& GetPriceRangeAsClosePercent() const{return m_priceRangeAsClosePercent;}

	const unsigned int& GetFirstQualifyingPrintSourceMask() const{return m_firstQualifyingPrintPresent;}

	const Price& GetTodaysClosePrice() const{return m_todaysClosePrice;}
	const unsigned int& GetLevel1BidSize() const{return m_level1BidSize;}
	const unsigned int& GetLevel1AskSize() const{return m_level1AskSize;}
	const unsigned int& GetLastTradeSize() const{return m_lastTradeSize;}
	const unsigned int& GetLastTradeMillisecond() const{return m_lastTradeMillisecond;}
	const unsigned int& GetLevel1Millisecond() const{return m_level1Millisecond;}
	const unsigned int& GetPmiMillisecond() const{return m_pmiMillisecond;}
	const short& GetLevel1Delay() const{return m_level1Delay;}
	const TradeLevel1& GetLastTradeLevel1() const{return m_lastTradeLevel1;}
	const char& GetBidMarketCenter() const{return m_bidMarketCenter;}
	const char& GetAskMarketCenter() const{return m_askMarketCenter;}
	const char& GetQuoteCondition() const{return m_quoteCondition;}
	const bool& GetRetailLiquidity() const{return m_retailLiquidity;}
	const char& GetLastMarketCenter() const{return m_lastMarketCenter;}
	const unsigned int& GetQuoteSeqNumber() const{return m_quoteSeqNumber;}
	const unsigned int& GetTradeSeqNumber() const{return m_tradeSeqNumber;}
	const unsigned char& GetTick() const{return m_tick;}

//	virtual unsigned int RequestHistoricalChart(const char* symbol, unsigned int dateFrom, char frequency){return false;}

	virtual unsigned short GetLastNewMinuteFromMsServer() const{return 0;}

	virtual Book* GetBook(unsigned char bookId){return NULL;}
	virtual const Book* GetBook(unsigned char bookId) const{return NULL;}
	virtual Book* GetPrimaryBook(){return NULL;}
	virtual const Book* GetPrimaryBook() const{return NULL;}
	virtual const Imbalance* GetNasdaqImbalance() const{return NULL;}
	virtual const Imbalance* GetArcaImbalance() const{return NULL;}
	virtual const Imbalance* GetNyseImbalance() const{return NULL;}

	const Imbalance* GetExchImbalance() const
	{
		switch(m_primaryExchange)
		{
			case PE_NSDQ:
			return GetNasdaqImbalance();

			case PE_ARCA:
			return GetArcaImbalance();

			default://PE_AMEX;PE_NYSE
			return GetNyseImbalance();
		}
	}

	const Price& GetFarPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetFarPrice() : TU_GetPriceZero();}
	const Price& GetNearPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetNearPrice() : TU_GetPriceZero();}
	const Price& GetCurrentReferencePriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetCurrentReferencePrice() : TU_GetPriceZero();}
	const int& GetImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetImbalanceShares() : intZero;}
	const int& GetPrevImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPrevImbalanceShares() : intZero;}
	const int& GetMarketImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetMarketImbalanceShares() : intZero;}
	const unsigned int& GetPairedSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPairedShares() : uintZero;}
	const unsigned int& GetImbalanceTimeNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetImbalanceTime() : uintZero;}
	const unsigned int& GetPrevImbalanceTimeNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPrevImbalanceTime() : uintZero;}
	const unsigned int& GetAuctionTimeNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetAuctionTime() : uintZero;}
	const char& GetCrossTypeNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetCrossType() : space;}
	const char& GetPriceVariationIndicatorNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPriceVariationIndicator() : space;}
	const int& GetRegulatoryImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetRegulatoryImbalanceShares() : intZero;}
	const int& GetPrevRegulatoryImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPrevRegulatoryImbalanceShares() : intZero;}
	const int& GetInitialImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetInitialImbalanceShares() : intZero;}
	const int& GetT926ImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT926ImbalanceShares() : intZero;}//Imbalance at 9:26

	const Price& GetFarPriceArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetFarPrice() : TU_GetPriceZero();}
	const Price& GetNearPriceArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetNearPrice() : TU_GetPriceZero();}
	const Price& GetCurrentReferencePriceArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetCurrentReferencePrice() : TU_GetPriceZero();}
	const int& GetImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetImbalanceShares() : intZero;}
	const int& GetPrevImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPrevImbalanceShares() : intZero;}
	const int& GetMarketImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetMarketImbalanceShares() : intZero;}
	const unsigned int& GetPairedSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPairedShares() : uintZero;}
	const unsigned int& GetImbalanceTimeArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetImbalanceTime() : uintZero;}
	const unsigned int& GetPrevImbalanceTimeArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPrevImbalanceTime() : uintZero;}
	const unsigned int& GetAuctionTimeArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetAuctionTime() : uintZero;}
	const char& GetCrossTypeArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetCrossType() : space;}
	const char& GetPriceVariationIndicatorArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPriceVariationIndicator() : space;}
	const int& GetRegulatoryImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetRegulatoryImbalanceShares() : intZero;}
	const int& GetPrevRegulatoryImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPrevRegulatoryImbalanceShares() : intZero;}
	const int& GetInitialImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetInitialImbalanceShares() : intZero;}
	const int& GetT926ImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetT926ImbalanceShares() : intZero;}//Imbalance at 9:26

	const Price& GetFarPriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetFarPrice() : TU_GetPriceZero();}
	const Price& GetNearPriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetNearPrice() : TU_GetPriceZero();}
	const Price& GetCurrentReferencePriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetCurrentReferencePrice() : TU_GetPriceZero();}
	const int& GetImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetImbalanceShares() : intZero;}
	const int& GetPrevImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPrevImbalanceShares() : intZero;}
	const int& GetRegulatoryImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryImbalanceShares() : intZero;}
	const int& GetPrevRegulatoryImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPrevRegulatoryImbalanceShares() : intZero;}
	const int& GetInitialImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetInitialImbalanceShares() : intZero;}
	const int& GetT926ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT926ImbalanceShares() : intZero;}//Imbalance at 9:26
	const int& GetMarketImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetMarketImbalanceShares() : intZero;}
	const unsigned int& GetPairedSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPairedShares() : uintZero;}
	const unsigned int& GetImbalanceTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetImbalanceTime() : uintZero;}
	const unsigned int& GetPrevImbalanceTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPrevImbalanceTime() : uintZero;}
	const unsigned int& GetRegulatoryImbalanceTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryImbalanceTime() : uintZero;}
	const unsigned int& GetPrevRegulatoryImbalanceTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPrevRegulatoryImbalanceTime() : uintZero;}
	const unsigned int& GetAuctionTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetAuctionTime() : uintZero;}
	const char& GetCrossTypeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetCrossType() : space;}
	const char& GetPriceVariationIndicatorNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPriceVariationIndicator() : space;}

	const Price& GetRegulatoryFarPriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryFarPrice() : TU_GetPriceZero();}
	const Price& GetRegulatoryNearPriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryNearPrice() : TU_GetPriceZero();}
	const Price& GetRegulatoryCurrentReferencePriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryCurrentReferencePrice() : TU_GetPriceZero();}
	const unsigned int& GetRegulatoryPairedSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryPairedShares() : uintZero;}

	const Price& GetFarPriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetFarPrice() : TU_GetPriceZero();}
	const Price& GetNearPriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetNearPrice() : TU_GetPriceZero();}
	const Price& GetCurrentReferencePriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetCurrentReferencePrice() : TU_GetPriceZero();}
	const int& GetImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetImbalanceShares() : intZero;}
	const int& GetPrevImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetPrevImbalanceShares() : intZero;}
	const int& GetMarketImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetMarketImbalanceShares() : intZero;}
	const unsigned int& GetPairedSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetPairedShares() : uintZero;}
	const unsigned int& GetImbalanceTimeExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetImbalanceTime() : uintZero;}
	const unsigned int& GetPrevImbalanceTimeExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetPrevImbalanceTime() : uintZero;}
	const unsigned int& GetAuctionTimeExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetAuctionTime() : uintZero;}
	const char& GetCrossTypeExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetCrossType() : space;}
	const char& GetPriceVariationIndicatorExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetPriceVariationIndicator() : space;}
	const int& GetInitialImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetInitialImbalanceShares() : intZero;}
	const int& GetT926ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT926ImbalanceShares() : intZero;}//Imbalance at 9:26
//Only works in Market Sorter
	const Price& GetExtendedHighPrice() const{return m_extendedHigh;}
	const Price& GetExtendedLowPrice() const{return m_extendedLow;}
	const Price& GetMarketHoursHighPrice() const{return m_marketHoursHigh;}
	const Price& GetMarketHoursLowPrice() const{return m_marketHoursLow;}
	const unsigned short& GetExtendedHighMinute() const{return m_extendedHighMinute;}
	const unsigned short& GetExtendedLowMinute() const{return m_extendedLowMinute;}
	const unsigned short& GetMarketHoursHighMinute() const{return m_marketHoursHighMinute;}
	const unsigned short& GetMarketHoursLowMinute() const{return m_marketHoursLowMinute;}

	const Price& GetPostMarketHoursHighPrice() const{return m_postMarketHoursHigh;}
	const Price& GetPostMarketHoursLowPrice() const{return m_postMarketHoursLow;}
//
	virtual const Exchange* GetPrints(unsigned char id) const{return NULL;}
	virtual const Exchange* GetBookExecutions(unsigned char id) const{return NULL;}

	unsigned char GetTradeLevel1(const Price& price) const;
	unsigned char GetTradeLevel1FromCompactPrice(unsigned int price) const;

//	virtual void SetUpdated(){}
//	virtual bool isUpdated(unsigned int updateOrdinal) const{return false;}

//	virtual void SetUpdatedLevel1(){}
//	virtual bool isUpdatedLevel1(unsigned int updateOrdinal) const{return false;}

	virtual bool CanUnsubscribe() const;
	LONG isUnsubscribable() const{return m_unsubscribable;}
//	virtual void SetUnsubscribable(bool unsubscribable){m_unsubscribable = unsubscribable;}
	virtual LONG IncrementUnsubscribable() const{return 2;}//{return InterlockedIncrement(&m_unsubscribable);}
	virtual LONG DecrementUnsubscribable(bool unsubscribeImmediately = false) const{return 1;}
/*
	{
		LONG result = InterlockedDecrement(&m_unsubscribable);
		if(result < 0)
		{
			InterlockedExchange(&m_unsubscribable, 0);
//			result = 0;
		}
		return result;
	}
*/
	virtual void Destroy() const{}
	virtual void Resubscribe() const{}
	virtual bool Subscribe() const{return false;}
	virtual bool Unsubscribe() const{return false;}

	void AddInThreadObserver(Observer* o) const;//Call RemoveInThreadObserver in the destructor of the object that you pass to this function
	void RemoveInThreadObserver(Observer* o) const;
//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;

	bool LockInquiryLevel1() const{return m_lockLevel1.LockInquiry();}
	void LockInquiryWaitLevel1() const{m_lockLevel1.LockInquiryWait();}
	void UnlockInquiryLevel1() const{m_lockLevel1.UnlockInquiry();}

	bool LockInquiryLevel2() const{return m_lockLevel2.LockInquiry();}
	void LockInquiryWaitLevel2() const{m_lockLevel2.LockInquiryWait();}
	void UnlockInquiryLevel2() const{m_lockLevel2.UnlockInquiry();}

	bool LockInquiryPrints() const{return m_lockPrints.LockInquiry();}
	void LockInquiryWaitPrints() const{m_lockPrints.LockInquiryWait();}
	void UnlockInquiryPrints() const{m_lockPrints.UnlockInquiry();}

	bool LockInquiryChart() const{return m_lockChart.LockInquiry();}
	void LockInquiryWaitChart() const{m_lockChart.LockInquiryWait();}
	void UnlockInquiryChart() const{m_lockChart.UnlockInquiry();}

	bool LockInquiryHistPrints() const{return m_lockHistPrints.LockInquiry();}
	void LockInquiryWaitHistPrints() const{m_lockHistPrints.LockInquiryWait();}
	void UnlockInquiryHistPrints() const{m_lockHistPrints.UnlockInquiry();}

/*
	bool LockInquiryHistoricalChart() const{return m_lockHistoricalChart.LockInquiry();}
	void LockInquiryWaitHistoricalChart() const{m_lockHistoricalChart.LockInquiryWait();}
	void UnlockInquiryHistoricalChart() const{m_lockHistoricalChart.UnlockInquiry();}
	typedef std::vector<HistoricalChartPoint> HistoricalChartPointVector;
*/
	typedef std::vector<ChartPoint> ChartPointVector;

	virtual unsigned short GetChartStartMinute() const{return 0;}//m_chartStartMinute;}

	virtual unsigned short GetChartSize() const{return 0;}
	virtual const ChartPointVector* GetChart() const{return NULL;}//m_chart;}
	virtual bool isChartLoaded() const{return false;}
/*
	virtual unsigned short GetHistoricalChartSize() const{return 0;}
	virtual const HistoricalChartPointVector* GetHistoricalChart() const{return NULL;}
	virtual bool isHistoricalChartLoaded() const{return false;}
*/
	const Price& GetFirstPrice() const{return m_firstPrice;}
	const Price& GetFirstMarketOpenPrice() const{return m_firstMarketOpenPrice;}
	const Price& GetLastMarketOpenPrice() const{return m_lastMarketOpenPrice;}
	const unsigned __int64& GetMarketHoursVolume() const{return m_marketHoursVolume;}
	const unsigned __int64& GetPreMarketVolume() const{return m_preMarketVolume;}
	const unsigned __int64& GetPostMarketVolume() const{return m_postMarketVolume;}
	const Money& GetMoneyTraded() const{return m_moneyTraded;}
	const Money& GetMarketHoursMoneyTraded() const{return m_marketHoursMoneyTraded;}
	const Money& GetPreMarketMoneyTraded() const{return m_preMarketMoneyTraded;}
	const Money& GetPostMarketMoneyTraded() const{return m_postMarketMoneyTraded;}

	virtual unsigned char GetMoveCountQuoteGreenLocked() const{return 0;}
	virtual unsigned char GetMoveCountQuoteRedLocked() const{return 0;}
	virtual unsigned char GetMoveCountPrintGreenLocked() const{return 0;}
	virtual unsigned char GetMoveCountPrintRedLocked() const{return 0;}
	const bool& isTest() const{return m_test;}
	const bool& isIpo() const{return m_ipo;}
	const char& GetType() const{return m_type;}
	const bool& isBancruptcy() const{return m_bancruptcy;}
	const bool& isExDistribution() const{return m_exDistribution;}
	const bool& isExRights() const{return m_exRights;}
	const bool& isExDividend() const{return m_exDividend;}
	const bool& isSpecialDividend() const{return m_specialDividend;}
//	bool& isSplit() const{return m_split;}
	const bool& isRule19C3() const{return m_rule19C3;}
	const bool& isItsEligible() const{return m_itsEligible;}
/*
	virtual unsigned char GetMoveReportLevel() const{return 0;}
	virtual void SetMoveReportLevel(unsigned char level){}
	virtual void SetMoveReportLevelFlag(MoveReportLevel level){}
	virtual void UnsetMoveReportLevelFlag(MoveReportLevel level){}
*/
	virtual unsigned char GetPositionStatus() const{return 0;}//0 - flat, 1 long, 2 short
	virtual int GetCurrentPositionSize() const{return 0;}
	virtual unsigned int GetCurrentPositionPrice() const{return 0;}
	virtual unsigned int GetLastExecPrice() const{return 0;}
	virtual int GetLastExecSize() const{return 0;}
	virtual void GetEcnTopQuote(bool bid, Price& ecnTopQuote, bool lock) const{ecnTopQuote.SetZero();}//should be called only when Level2 is locked (or lock = true)

//	virtual void SkipUnappliedPrints(){}
#ifndef TAKION_NO_OPTIONS
	const OptionInfo* GetOptionInfo() const{return m_optionInfo;}
//	OptionInfo* GetOptionInfo(){return m_optionInfo;}
//	void SetOptionInfo(OptionInfo* optionInfo);
	const unsigned __int64& GetOptionBlock() const{return m_optionInfo ? m_optionInfo->GetOptionBlock() : uint64Zero;}
	const unsigned __int64& GetOptionKey() const{return m_optionInfo ? m_optionInfo->GetOptionKeyValue() : uint64Zero;}
	const unsigned __int64& GetUnderlierNumericSymbol() const{return m_optionInfo ? m_optionInfo->GetUnderlierNumericSymbol() : m_numericSymbol;}
//	const char* GetUnderlierSymbol() const{return m_optionInfo ? m_optionInfo->GetUnderlierSymbol() : NULL;}
//	const std::string& GetUnderlierSymbolStr() const{return m_optionInfo ? m_optionInfo->GetUnderlierSymbolStr() : stringZero;}
	bool isCall() const{return m_optionInfo && m_optionInfo->isCall();}
//	bool isMini() const{return m_optionInfo && m_optionInfo->isMini();}
	unsigned char GetSuffix() const{return m_optionInfo ? m_optionInfo->GetSuffix() : ucharZero;}
	unsigned char GetCallPutFlags() const{return m_optionInfo ? m_optionInfo->GetCallPutFlags() : ucharZero;}
	const unsigned char& GetOptionFlags() const{return m_optionInfo ? m_optionInfo->GetFlags() : ucharZero;}
	const unsigned int& GetStrikePrice() const{return m_optionInfo ? m_optionInfo->GetStrikePrice() : uintZero;}
	unsigned int GetExpirationDate() const{return m_optionInfo ? m_optionInfo->GetExpirationDate() : 0;}
	const unsigned char& GetExpirationType() const{return m_optionInfo ? m_optionInfo->GetExpirationType() : ucharZero;}
	const unsigned int& GetExpirationDays() const{return m_optionInfo ? m_optionInfo->GetExpirationDays() : uintZero;}
	const char& GetExpirationTypeChar() const{return m_optionInfo ? m_optionInfo->GetExpirationTypeChar() : space;}
	const unsigned int& GetOpenInterestVolume() const{return m_optionInfo ? m_optionInfo->GetOpenInterestVolume() : uintZero;}
	const unsigned int& GetImpliedVolatility() const{return m_optionInfo ? m_optionInfo->GetImpliedVolatility() : uintZero;}
	const int& GetDelta() const{return m_optionInfo ? m_optionInfo->GetDelta() : intZero;}
	const int& GetVega() const{return m_optionInfo ? m_optionInfo->GetVega() : intZero;}
	const int& GetTheta() const{return m_optionInfo ? m_optionInfo->GetTheta() : intZero;}
	const unsigned int& GetContractSize() const{return m_optionInfo ? m_optionInfo->GetContractSize() : uintOne;}
	void GetOptionBlockAsString(std::string& optionSymbol, bool withSuffix) const{if(m_optionInfo)m_optionInfo->GetOptionBlockAsString(optionSymbol, withSuffix);}
	bool GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const
	{
		if(m_optionInfo)
		{
			if(suffixSeparate)
			{
				const unsigned __int64& underlierSymbol = m_optionInfo->GetUnderlierNumericSymbol();
				if(underlierSymbol)optionSymbol += (const char*)&underlierSymbol;
				else return false;
			}
			else optionSymbol += (const char*)&m_numericSymbol;
			
			optionSymbol += ' ';
			m_optionInfo->GetOptionBlockAsString(optionSymbol, suffixSeparate);
		}
		else
			optionSymbol += (const char*)&m_numericSymbol;

		return true;
	}


	void SetOpenInterestVolume(const unsigned int& openInterestVolume){if(m_optionInfo)m_optionInfo->SetOpenInterestVolume(openInterestVolume);}

	Underlier* GetUnderlier(){return m_optionInfo ? m_optionInfo->GetUnderlier() : NULL;}
	const Underlier* GetUnderlier() const{return m_optionInfo ? m_optionInfo->GetUnderlier() : NULL;}

	void NotifyOptionLevel2Observers(const Message* message, const Message* info = NULL) const{if(m_optionInfo)m_optionInfo->NotifyObservers(message, info, this);}
	void AddOptionLevel2Observer(Observer* observer) const{if(m_optionInfo)m_optionInfo->AddObserver(observer);}
	void RemoveOptionLevel2Observer(Observer* observer) const{if(m_optionInfo)m_optionInfo->RemoveObserver(observer);}

	void NotifyOptionLevel2InThreadObservers(const Message* message, const Message* info = NULL) const{if(m_optionInfo)m_optionInfo->NotifyInThreadObservers(message, info, this);}
	void AddOptionLevel2InThreadObserver(Observer* o) const{if(m_optionInfo)m_optionInfo->AddInThreadObserver(o);}
//	void RemoveOptionLevel2InThreadObserverWithoutLocking(Observer* o) const{if(m_optionInfo)m_optionInfo->RemoveInThreadObserverWithoutLocking(o);}
	void RemoveOptionLevel2InThreadObserver(Observer* o) const{if(m_optionInfo)m_optionInfo->RemoveInThreadObserver(o);}
/*
	{
		if(m_optionInfo)
			if(isInThread())m_optionInfo->RemoveInThreadObserverWithoutLocking(o);
			else m_optionInfo->RemoveInThreadObserver(o);
	}
*/
	virtual bool CanOptionLevel2Unsubscribe() const{return !m_optionInfo || m_optionInfo->CanUnsubscribe();}
	LONG isOptionLevel2Unsubscribable() const{return m_optionInfo ? m_optionInfo->isUnsubscribable() : 0;}
	virtual void NullifyThread(){}
	virtual void RemoveFromPositions(bool notify){}
	virtual void ClearPositions(){}

	virtual const unsigned char& isHTB(const unsigned int& ordinal) const override{return m_optionInfo ? ucharZero : HTB::isHTB(ordinal);}
#endif
//	virtual void ReleaseNewPrints(){}//called from main thread
	virtual void ClearUnappliedPrints(){}
protected:
	Security(const char* symbol, unsigned short code
#ifndef TAKION_NO_OPTIONS
		, OptionInfo* optionInfo = NULL
#endif
		);
	unsigned short m_securityCode;
//	char m_name[MAX_SECURITY_NAME + 1];
	std::string m_name;

	unsigned int m_roundLot;
	bool m_roundLotsOnly;
	char m_marketCategory;
	char m_financialStatus;
	char m_primaryExchange;
	unsigned int m_marketCategoryFilter;
	unsigned int m_tradingActionReason;
	char m_tradingState;

	bool m_test;

	mutable bool m_loaded;
	unsigned char m_primaryExchangeFlag;

	mutable volatile LONG m_unsubscribable;

	unsigned __int64 m_volume;
	unsigned __int64 m_primaryExchangeVolume;
	unsigned __int64 m_primaryExchangeMhVolume;
	unsigned __int64 m_yesterdaysVolume;

	unsigned int m_l2Bid;
	unsigned int m_l2Ask;
	unsigned int m_l2BidSize;
	unsigned int m_l2AskSize;

	unsigned int m_l1Bid;
	unsigned int m_l1Ask;
	unsigned int m_nysBid;
	unsigned int m_nysAsk;
	unsigned int m_nysBidSize;
	unsigned int m_nysAskSize;
	unsigned int m_nysLastPrice;
	unsigned int m_nysLastTradeSize;
	unsigned int m_nysHighPrice;
	unsigned int m_nysLowPrice;

	unsigned int m_amxBid;
	unsigned int m_amxAsk;
	unsigned int m_amxBidSize;
	unsigned int m_amxAskSize;
	unsigned int m_amxLastPrice;
	unsigned int m_amxLastTradeSize;

	unsigned int m_nsdqLastPrice;
	unsigned int m_nsdqLastTradeSize;

	unsigned int m_lastPrice;
	unsigned int m_lastNbboPrintPrice;
	unsigned int m_closePriceCompact;
	unsigned int m_todaysClosePriceCompact;
	unsigned int m_openPriceCompact;
	unsigned int m_primaryOpenPriceCompact;
	Price m_pmiBid;
	Price m_pmiAsk;
	Price m_openPrice;
	Price m_primaryOpenPrice;
	Price m_closePrice;
	SignedPrice m_netChange;
	SignedPrice m_openChange;
	SignedPrice m_niteChange;
//	SignedPrice m_netChangePercent;
	Price m_highPrice;
	Price m_lowPrice;
	Price m_priceRange;
	Price m_extendedPriceRange;
	SignedPrice m_lastPriceInRangePercent;
	Price m_priceRangeAsClosePercent;
	Price m_todaysClosePrice;
	SignedPrice m_todaysCloseChange;

	Price m_firstPrice;
	Price m_firstMarketOpenPrice;
	Price m_lastMarketOpenPrice;
	unsigned __int64 m_marketHoursVolume;
	unsigned __int64 m_preMarketVolume;
	unsigned __int64 m_postMarketVolume;

	Money m_moneyTraded;
	Money m_marketHoursMoneyTraded;
	Money m_preMarketMoneyTraded;
	Money m_postMarketMoneyTraded;

//Only works in Market Sorter
	Price m_extendedHigh;
	Price m_extendedLow;
	Price m_marketHoursHigh;
	Price m_marketHoursLow;
	Price m_postMarketHoursHigh;
	Price m_postMarketHoursLow;
	unsigned short m_extendedHighMinute;
	unsigned short m_extendedLowMinute;
	unsigned short m_marketHoursHighMinute;
	unsigned short m_marketHoursLowMinute;
//
	unsigned int m_firstQualifyingPrintPresent;

	unsigned int m_level1BidSize;
	unsigned int m_level1AskSize;
	unsigned int m_lastTradeSize;
	unsigned int m_lastTradeMillisecond;
	unsigned int m_level1Millisecond;
	unsigned int m_pmiMillisecond;
	short m_level1Delay;
	TradeLevel1 m_lastTradeLevel1;
	char m_bidMarketCenter;
	char m_askMarketCenter;
	char m_quoteCondition;
	bool m_retailLiquidity;
	char m_lastMarketCenter;
	unsigned int m_quoteSeqNumber;
	unsigned int m_tradeSeqNumber;
	unsigned char m_tick;
	bool m_open;

	char m_shortSaleThresholdIndicator;//'Y', 'N'
	char m_regSHOTestIndicator;//'0', '1', '2'
    unsigned short m_splitNumerator;
    unsigned short m_splitDenominator;
    unsigned int m_split;
	Price m_dividend;

	Price m_lrpLow;
	Price m_lrpHigh;
	unsigned int m_lrpLowTime;
	unsigned int m_lrpHighTime;
	short m_lrpLowDelay;
	short m_lrpHighDelay;
	bool m_lrpLowHistorical;
	bool m_lrpHighHistorical;

	Price m_luldLow;
	Price m_luldHigh;
	unsigned int m_luldLowTime;
	unsigned int m_luldHighTime;
	short m_luldLowDelay;
	short m_luldHighDelay;
	bool m_luldLowHistorical;
	bool m_luldHighHistorical;

	bool m_openSaleCondition;
	bool m_primaryOpenSaleCondition;
	bool m_primarySourceOpenPrint;

	char m_rpiIndicator;

	unsigned int m_tradeDisseminationTime;

	bool m_ipo;
	char m_type;
	bool m_bancruptcy;
	bool m_exDistribution;
	bool m_exRights;
	bool m_exDividend;
	bool m_specialDividend;
//	bool m_split;
	bool m_rule19C3;
	bool m_itsEligible;

#ifndef TAKION_NO_OPTIONS
	virtual void OnOptionLevel2ObserverAdded(){}
	virtual void OnOptionLevel2ObserverRemoved(){}
	OptionInfo* m_optionInfo;
/*
	OptionCollection* m_optionCollection;
	void CreateOptionCollection();
	void DestroyOptionCollection();
*/
#endif

	TakionLock m_lockLevel1;
	TakionLock m_lockLevel2;
	TakionLock m_lockPrints;
	TakionLock m_lockChart;
	TakionLock m_lockHistPrints;

	Observable m_inThreadObservable;
	TakionLockMultithread m_lockInThreadObservable;
};

#ifndef TAKION_NO_OPTIONS

class TU_API Underlier : public Observable, public TakionLock
{
public:
	virtual ~Underlier(){ClearAndDestroy();}
	typedef CMap<OptionKey, const OptionKey&, Security*, Security*> StockOptionMap;
	const StockOptionMap& GetOptionMap() const{return m_optionMap;}
	StockOptionMap& GetOptionMap(){return m_optionMap;}
	unsigned int GetOptionCount() const{return (unsigned int)m_optionMap.GetCount();}
	Security* FindOption(const OptionKey& key)//Do lock when using this function
	{
		StockOptionMap::CPair* found = m_optionMap.PLookup(key);
		return found ? found->value : NULL;
	}
	const Security* FindOption(const OptionKey& key) const//Do lock when using this function
	{
		const StockOptionMap::CPair* found = m_optionMap.PLookup(key);
		return found ? found->value : NULL;
	}
	Security* FindOptionWithLocking(const OptionKey& key)//Do lock when using this function
	{
		Security* security = NULL;
		StockOptionMap::CPair* found;
		LockInquiryWait();
		found = m_optionMap.PLookup(key);
		if(found)security = found->value;
		UnlockInquiry();
		return security;
	}
	const Security* FindOptionWithLocking(const OptionKey& key) const//Do lock when using this function
	{
		const Security* security = NULL;
		const StockOptionMap::CPair* found;
		LockInquiryWait();
		found = m_optionMap.PLookup(key);
		if(found)security = found->value;
		UnlockInquiry();
		return security;
	}
	TakionIterator* CreateOptionIterator() const;//Do lock when iterating
//	const char* GetSymbol() const{return m_symbolStr.c_str();}
//	const std::string& GetSymbolStr() const{return m_symbolStr;}
	const char* GetSymbol() const{return (const char*)&m_numericSymbol;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
	bool isLoaded() const{return m_loaded;}
	virtual bool CanUnsubscribe() const;
	LONG isUnsubscribable() const{return m_unsubscribable;}
	virtual LONG IncrementUnsubscribable() const{return 2;}//{return InterlockedIncrement(&m_unsubscribable);}
	virtual LONG DecrementUnsubscribable(bool unsubscribeImmediately = false) const{return 1;}
	void AddInThreadObserver(Observer* o) const;//Call RemoveInThreadObserver in the destructor of the object that you pass to this function
	void RemoveInThreadObserver(Observer* o) const;
//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;
	virtual HANDLE GetThreadHandle() const{return NULL;}
	virtual unsigned int GetThreadId() const{return 0;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}
//	typedef std::set<char> CharSet;
//	const CharSet& GetSuffixSet() const{return m_suffixSet;}
	const unsigned int& GetSuffixAlphaFlags() const{return m_suffixAlphaFlags;}
	const unsigned int& GetSuffixNumFlags() const{return m_suffixNumFlags;}

//	virtual void Destroy(){}
	virtual void Resubscribe() const{}
	virtual bool Subscribe() const{return false;}
	virtual bool Unsubscribe() const{return false;}
protected:
	Underlier(const char* symbol);
	Underlier(const unsigned __int64& symbol);
	void Clear(){m_optionMap.RemoveAll();}//Do lock when using this function
	void ClearAndDestroy();//Do lock when using this function//{m_optionMap.RemoveAll();}
//	std::string m_symbolStr;
	unsigned __int64 m_numericSymbol;
	StockOptionMap m_optionMap;
	mutable volatile LONG m_unsubscribable;
	mutable bool m_loaded;
	Observable m_inThreadObservable;
	TakionLockMultithread m_lockInThreadObservable;
//	CharSet m_suffixSet;
	unsigned int m_suffixAlphaFlags;
	unsigned int m_suffixNumFlags;
};

#endif

enum OrderStatus : unsigned char
{
	TU_ORDER_STATUS_UNACKNOWLEDGED,
	TU_ORDER_STATUS_PENDING,
	TU_ORDER_STATUS_CANCELED,
	TU_ORDER_STATUS_FILLED,
	TU_ORDER_STATUS_REJECTED,

	TU_ORDER_STATUS_ALGORITHM,

	TU_ORDER_STATUS_COUNT
};

enum OrderSide : unsigned char
{
	TU_ORDER_SIDE_BUY,
	TU_ORDER_SIDE_SELL,
	TU_ORDER_SIDE_SHORT,

	TU_ORDER_SIDE_COUNT
};

enum OrderBorrow : unsigned char
{
	TU_ORDER_BORROW,
	TU_ORDER_TRADE,

	TU_ORDER_BORROW_COUNT
};

enum OrderCancelPick : unsigned char
{
	TU_ORDER_CANCEL_ALL,
	TU_ORDER_CANCEL_OLDEST,
	TU_ORDER_CANCEL_YOUNGEST,
	TU_ORDER_CANCEL_MOST_AGGRESSIVE,
	TU_ORDER_CANCEL_LEAST_AGGRESSIVE,

	TU_ORDER_CANCEL_COUNT
};

enum ExecutionOrigin : char
{
	EO_MY = '\0',
	EO_FOREIGN = 'F',
	EO_BUSTED = 'B',
	EO_HISTORICAL = 'H',
};

class ExecutionIdAsNumberArray : public StrAsNumberArray<size_t, 24 / sizeof(size_t)>
{
public:
	ExecutionIdAsNumberArray():StrAsNumberArray(){}
	ExecutionIdAsNumberArray(const char* str):StrAsNumberArray(str){}
	ExecutionIdAsNumberArray(const char*& str, const char& del):StrAsNumberArray(str, del){}
	ExecutionIdAsNumberArray(const char*& str, unsigned short length, const char& del):StrAsNumberArray(str, length, del){}
	ExecutionIdAsNumberArray(unsigned short exactLength, const char* str):StrAsNumberArray(exactLength, str){}
	ExecutionIdAsNumberArray(const std::string& str):StrAsNumberArray(str){}
	operator size_t() const{return m_numberArray[4 / sizeof(size_t)];}
	operator int() const{return (int)m_numberArray[4 / sizeof(size_t)];}
	operator long() const{return (long)m_numberArray[4 / sizeof(size_t)];}
	DECLARE_NED_NEW
};

class LocateContractId : public StrAsNumberArray<size_t, 16 / sizeof(size_t)>
{
public:
	LocateContractId():StrAsNumberArray(){}
	LocateContractId(const char* str):StrAsNumberArray(str){}
	LocateContractId(const char*& str, const char& del):StrAsNumberArray(str, del){}
	LocateContractId(const char*& str, unsigned short length, const char& del):StrAsNumberArray(str, length, del){}
	LocateContractId(unsigned short exactLength, const char* str):StrAsNumberArray(exactLength, str){}
	LocateContractId(const std::string& str):StrAsNumberArray(str){}
	operator size_t() const{return m_numberArray[4 / sizeof(size_t)];}
	operator int() const{return (int)m_numberArray[4 / sizeof(size_t)];}
	operator long() const{return (long)m_numberArray[4 / sizeof(size_t)];}
	DECLARE_NED_NEW
};

class TU_API Execution : public PriceQuantity
{
public:
	virtual ~Execution();
	const unsigned int& GetId() const{return m_id;}
	const unsigned int& GetMmid() const{return m_mmid;}
//	virtual unsigned int GetDestinationName() const{return 0;}
	const unsigned int& GetTimeSent() const{return m_timeSent;}
	const unsigned int& GetTimeReceived() const{return m_timeReceived;}
	const short& GetDelay() const{return m_delay;}
	const Money& GetClosedPnl() const{return m_closedPnl;}
	const Money& GetClosedPnlCost() const{return m_closedPnlCost;}
	const Money& GetPositionMarkedPnl() const{return m_positionMarkedPnl;}
	const Money& GetAccountMarkedPnl() const{return m_accountMarkedPnl;}
	const Money& GetPositionClosedPnl() const{return m_positionClosedPnl;}
	const Money& GetAccountClosedPnl() const{return m_accountClosedPnl;}
	const int& GetPositionSize() const{return m_positionSize;}
	const Price& GetPositionAveragePrice() const{return m_positionPrice;}

	bool operator<(const Execution& other) const
	{
		return m_timeSent != other.m_timeSent ? m_timeSent < other.m_timeSent:
			(m_origin == EO_HISTORICAL) != (other.m_origin == EO_HISTORICAL) ? m_origin == EO_HISTORICAL:
			GetSide() != other.GetSide() ? GetSide() < other.GetSide():
			m_id < other.m_id;
	}
//	const std::string& GetExecutionReferenceId() const{return m_executionReferenceId;}
	const char* GetExecutionReferenceIdAsString() const{return m_executionReferenceId.GetString();}
	const ExecutionIdAsNumberArray& GetExecutionReferenceId() const{return m_executionReferenceId;}

	Order* GetOrder(){return m_order;}
	const Order* GetOrder() const{return m_order;}
//OrderInfo
//	const std::string& GetSymbolStr() const;
	const char* GetSymbol() const;
	const unsigned __int64& GetNumericSymbol() const;
	SecurityType GetSecurityType() const;
	const char* GetAccountId() const;
	const char* GetAccountUserName() const;
	const char& GetSide() const;
#ifdef FIRM_VALUES
	const char& GetFirmSide() const;
#endif
	const bool& isBorrow() const;
	OrderSide GetOrderSide() const;
	const unsigned int& GetDestination() const;
	const unsigned int& GetRoutingName() const;
	const unsigned short& GetRoutingId() const;
	const unsigned int& GetMnemonic() const;

	const unsigned char& GetOrderType() const;
	const unsigned short& GetUserOrderType() const;
	const std::string& GetUserOrderTypeString() const;
	const unsigned __int64& GetUserOrderId() const;
	const char* const& GetUserOrderInfo() const;
	const unsigned int& GetParentId() const;
	const Price& GetLimitPrice() const;
	const Price& GetQuotePrice() const;
	const unsigned int& GetOrderQuantity() const;
	const unsigned int& GetOrderMnemonic() const;
	const unsigned int& GetPendingQuantity() const{return m_remainingQuantity;}
	const unsigned int& GetSharesTradedPosition() const{return m_sharesTradedPosition;}
	const unsigned int& GetSharesTradedAccount() const{return m_sharesTradedAccount;}
//	const unsigned int& GetOrderClientId() const;
	const unsigned int& GetOrderServerId() const;
	const unsigned int& GetTraderId() const;
	const unsigned int& GetClosedShares() const{return m_closedShares;}
	const unsigned int& GetErroneousShares() const{return m_erroneousShares;}

	const char& GetLiquidity() const{return m_liquidity;}
	const char& GetBillable() const{return m_billable;}
	bool isSharesAdded() const;

	const char& GetOrigin() const{return m_origin;}
	const bool& isDropcopy() const{return m_dropcopy;}
	const bool& isBusted() const{return m_busted;}
#ifndef TAKION_NO_OPTIONS
	const OptionSymbolBlock* GetOptionSymbolBlock() const;
//	OptionSymbolBlock* GetOptionSymbolBlock();
	const unsigned __int64& GetOptionBlock() const;
	const unsigned __int64& GetUnderlierNumericSymbol() const;
	bool isCall() const;
	unsigned char GetSuffix() const;
	unsigned char GetCallPutFlags() const;
	const unsigned char& GetOptionFlags() const;
	const unsigned int& GetStrikePrice() const;
	unsigned int GetExpirationDate() const;
	const unsigned char& GetExpirationType() const;
	const unsigned int& GetExpirationDays() const;
	const char& GetExpirationTypeChar() const;
	void GetOptionBlockAsString(std::string& optionSymbol, bool suffixSeparate) const;
	void GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const;
	const unsigned int& GetContractSize() const;
#endif
protected:
	Execution(Order* order,
		unsigned int id,
		const Price& price,
		unsigned int quantity,
		unsigned int mmid,
		unsigned int timeSent,
		unsigned int timeReceived,
		char liquidity,
		char billable,
		char origin,
		bool dropcopy,
		bool busted,
		const char* marketReferenceId,
		int positionSize,
		unsigned int positionSharesTraded,
		unsigned int accountSharesTraded);
	Order* m_order;
	unsigned int m_id;
	unsigned int m_mmid;
	unsigned int m_timeSent;
	unsigned int m_timeReceived;
	unsigned int m_closedShares;
	unsigned int m_erroneousShares;
	unsigned int m_remainingQuantity;
	short m_delay;
	char m_liquidity;
	char m_billable;
	char m_origin;
	bool m_dropcopy;
	bool m_busted;

	Money m_closedPnl;
	Money m_closedPnlCost;
	Money m_positionMarkedPnl;
	Money m_accountMarkedPnl;
	Money m_positionClosedPnl;
	Money m_accountClosedPnl;
	Price m_positionPrice;
	int m_positionSize;
	unsigned int m_sharesTradedPosition;
	unsigned int m_sharesTradedAccount;

//	std::string m_executionReferenceId;
	ExecutionIdAsNumberArray m_executionReferenceId;
};
/*
class TU_API StringHashKey
{
public:
	StringHashKey(const std::string& refId):m_refId(refId),m_hashValue(U_StringHash(m_refId)){}
	StringHashKey():m_hashValue(0){}
	inline operator int() const{return m_hashValue;}
	inline operator long() const{return m_hashValue;}
	inline operator size_t() const{return m_hashValue;}
	const unsigned int& GetHashValue() const{return m_hashValue;}
	const std::string& GetRefId() const{return m_refId;}
	bool operator==(const StringHashKey& other) const{return m_refId == other.m_refId;}
	bool operator<(const StringHashKey& other) const{return m_refId < other.m_refId;}
protected:
	std::string m_refId;
	unsigned int m_hashValue;
};

typedef CMap<StringHashKey, StringHashKey&, Execution*, Execution*> ExecutionRefMap;
*/

typedef CMap<ExecutionIdAsNumberArray, const ExecutionIdAsNumberArray&, Execution*, Execution*> ExecutionRefMap;

//typedef CMap<unsigned __int64, unsigned __int64, Execution*, Execution*> ExecutionMap;
typedef CMap<unsigned int, const unsigned int&, Execution*, Execution*> ExecutionMap;
//typedef std::list<Execution*> ExecutionList;

typedef std::set<Execution*, lessPtr<Execution*> > ExecutionChronologicalSet;

typedef CMap<unsigned __int64, const unsigned __int64&, Position*, Position*> PositionMap;
#ifndef TAKION_NO_OPTIONS
typedef CMap<OptionSymbolBlockKey, const OptionSymbolBlockKey&, Position*, Position*> OptionPositionMap;
#endif

typedef CMap<unsigned int, const unsigned int&, Order*, Order*> OrderMap;

typedef std::multimap<unsigned int, Order*> OrderChronologicalMap;

enum OrderError : unsigned char
{
	OE_OK,
	OE_TRADING_NOT_ALLOWED,
	OE_SIZE_ZERO,
	OE_PRICE_ZERO,
	OE_STOP_PRICE_ZERO,
	OE_ORDER_SIZE_EXCEEDED,
	OE_ORDER_VALUE_EXCEEDED,
	OE_POSITION_SIZE_EXCEEDED,

	OE_HISTORY_NOT_LOADED,
	OE_HISTORY_LOAD_ERROR,

	OE_SECURITY_NOT_LOADED,

	OE_BUYING_POWER,
	OE_HARD_BUYING_POWER,

	OE_POSITION_COUNT,
	OE_SHORT_PRICE,

	OE_STOCK_NOT_SHORTABLE,
	OE_HTB_STOCK_NOT_ENOUGH_BORROWED,
	OE_REGSHO_SHORT_VIOLATION,
	OE_HARD_TO_BORROW_SHORT_VIOLATION,

	OE_WASH_ORDERS,
	OE_ODD_LOT_VIOLATION,
	OE_SHORT_ORDER_FOR_LONG_POSITION,
	OE_SHORT_ORDER_AGGRESSIVE,

	OE_PRICE_AWAY_FROM_NBBO,

	OE_ORDER_TOO_AGGRESSIVE,

	OE_INVALID_ORDER_TYPE,
	OE_INVALID_TIF,
	OE_NO_CURRENT_ACCOUNT,

	OE_MAX_LOSS_MARKED_EXCEEDED,

	OE_MAX_SHARESTRADED_EXCEEDED,
	OE_MAX_SHARES_OPEN_EXCEEDED,//OE_MAX_SHARESTRADED_PLUS_OVERNIGHT_EXCEEDED,

	OE_NON_TRADABLE_STOCK,

	OE_OVERSELL,
	OE_OVERBUY,

	OE_MAX_POSITION_LOSS_MARKED_EXCEEDED,

	OE_LOCATE_NOT_REQUIRED,

	OE_NO_ORDERS_GENERATED,

	OE_NON_TRADABLE_POSITION,

	OE_WRONG_ACCOUNT,

	OE_WRONG_SIDE,
	OE_NOTHING_TO_CLOSE,

	OE_MAX_POSITION_BPU_EXCEEDED,

	OE_MAX_LONG_INVESTMENT_EXCEEDED,
	OE_MAX_SHORT_INVESTMENT_EXCEEDED,

	OE_NO_VENUE,
	OE_INVALID_STOP_TYPE,
	OE_INVALID_VISIBLE_SIZE,

	OE_NO_STOCK,

	OE_NO_EXCHANGE_ENTITLEMENT,

	OE_BORROW_TOO_EXPENSIVE,

	OE_TRIGGER_CONDITION_ALREADY_MET,

	OE_UNOPEN_IPO_MARKET_ORDER,

	OE_HTB_STOCK_NO_LOCATE_CONTRACT_NUMBER,

	OE_UNTRADEABLE_SYMBOL,
	OE_UNTRADEABLE_STATUS_NOT_LOADED,

	OE_WRONG_STOCK,
	OE_ORDER_TO_REPLACE_IS_BEING_CANCELED,
	OE_ORDER_TO_REPLACE_IS_DEAD,

	OE_NO_CANCEL_FOR_DROPCOPY_ORDERS,
	OE_CANNOT_CANCEL_ORDER_BEFORE_SENDING_NEW_ONE,

	OE_INVALID_PEG_TYPE,
#ifndef TAKION_NO_OPTIONS
	OE_NO_OPTION_VENUE,
	OE_INVALID_OPTION_VENUE,
	OE_OPTION_POSITION_COUNT,
	OE_NO_BORROW_FOR_INSTRUMENT,
	OE_OPTION_BUYING_POWER,
	OE_OPTION_NAKED,
	OE_UNDERLIER_OPTION_NAKED,
#endif
	OE_ERROR_Count
};

enum CancelError : unsigned char
{
	CE_OK,

	CE_TRADING_NOT_ALLOWED,
	CE_ERROR_ALREADY_SENT,
	CE_ORDER_NOT_FOUND,
	CE_TOO_LATE,
	CE_DROPCOPY_ORDER,
	CE_ORDER_NOT_SENT,
	CE_NON_CANCELABLE,

	CE_ERROR_Count
};

enum OrderState : unsigned char
{
	TU_OS_UNACKNOWLEDGED,
	TU_OS_ON_SERVER,
	TU_OS_ON_MARKET,
	TU_OS_CANCEL_SENT,
	TU_OS_REPLACE_SENT,
	TU_OS_CANCEL_ACKNOWLEDGED,
	TU_OS_REPLACE_ACKNOWLEDGED,
	TU_OS_DEAD,

	TU_OS_COUNT
};

enum YesNoMask : unsigned char
{
	YNM_YES,
	YNM_NO,

	YNM_Count,
	YNM_ALL = (1 << YNM_Count) - 1,
};

enum ExistingPrice : unsigned char
{
	EP_UNKNOWN,
	EP_PQOPEN,
	EP_TCLOSE,

	EP_Count
};

enum AlgorithmMask : unsigned char
{
	ALGORITHMMASK_YES,
	ALGORITHMMASK_LIMIT,
	ALGORITHMMASK_MARKET,
	ALGORITHMMASK_STOP,
	
	ALGORITHMMASK_COUNT,

	ALGORITHMMASKMASK_ALL = (1 << ALGORITHMMASK_COUNT) - 1,
};

enum TifMask : unsigned char
{
	TIFMASK_ON_OPEN,
	TIFMASK_ON_CLOSE,
	TIFMASK_DAY,
	TIFMASK_EXTENDED,
	TIFMASK_TIME,
	TIFMASK_IOC,
	TIFMASK_FOK,
	TIFMASK_OTHER,

	TIFMASK_COUNT,

	TIFMASK_ALL = (1 << TIFMASK_COUNT) - 1,
};

enum SideMask : unsigned char
{
	SIDEMASK_BUY,
	SIDEMASK_SELL,
	SIDEMASK_SHORT,

	SIDEMASK_COUNT
};

enum VisibleSizeMask : unsigned char
{
	VSM_HIDDEN,
	VSM_VISIBLE,

	VSM_COUNT
};

enum OddLotMask : unsigned char
{
	OLM_ODDLOT,
	OLM_EVENLOT,

	OLM_COUNT
};

enum OrderOrigin : char
{
	OO_MY = '\0',
	OO_FOREIGN = 'F',
	OO_HISTORICAL = 'H',
};

enum RoundLotPolicy : unsigned char
{
	RLP_REJECT,
	RLP_ROUND_DOWN,
	RLP_ROUND_UP,

	RLP_Count
};

enum OrderStopType : unsigned char
{
	OST_NONE,
	OST_NATIVE,
	OST_TRAILING,
	OST_SYNTHETIC,

	OST_COUNT
};

enum OrderStopBase : unsigned char
{
	OSB_BID,
	OSB_ASK,
	OSB_MIDPOINT,
	OSB_PRINT,

	OSB_COUNT
};

enum OrderProblems : unsigned char
{
	OP_STUCK,
	OP_CANCEL_REJECTED,
	OP_CANCEL_BLOCKED,

	OP_COUNT
};

enum CancelInProgress : unsigned char
{
	CIP_NONE,
	CIP_CANCEL,
	CIP_REPLACE
};

class TU_API Order : public Observable, public TakionLock
{
public:
	virtual ~Order();

	const unsigned int& GetTraderId() const{return m_traderId;}
	const unsigned int& GetClientId() const{return m_clientId;}
	const unsigned int& GetClientIdOriginal() const{return m_clientIdOriginal;}
	const unsigned int& GetClientIdChronological() const{return m_clientIdChronological;}
	const unsigned int& GetServerId() const{return m_serverId;}
	const unsigned int& GetParentId() const{return m_parentId;}
	const unsigned __int64& GetUserId() const{return m_userId;}
	const unsigned int& GetDestinationId() const{return m_destinationId;}
//	const std::string& GetSymbolStr() const;
	const char* GetSymbol() const;
	const unsigned __int64& GetNumericSymbol() const;
	SecurityType GetSecurityType() const;
	const char* GetAccountId() const;
	const char* GetAccountUserName() const;

	unsigned char GetExistingPrice() const;//enum ExistingPrice
	bool FilterByExistingPrice(unsigned char pqOpenMask, unsigned char tCloseMask) const;

	virtual bool isNotifyCancel() const{return true;}
	virtual bool isServerOrder() const{return false;}
	virtual bool isDummy() const{return false;}
	virtual bool isAlgorithm() const{return false;}
	virtual const char* GetAlgorithmName() const{return "";}
	virtual bool CanBeReplaced() const;

	virtual bool HasPrice() const{return true;}
	virtual bool HasSize() const{return true;}
	virtual unsigned int GetAlgorithmQuantity() const{return GetQuantity();}
	
	bool CanBeMassCanceled() const{return !m_noMassCancel && !m_beingCanceled;}
	bool CanBeMassCanceledOrReplaced(bool canceled) const{return CanBeMassCanceled() && (canceled || CanBeReplaced());}
/*
	bool Lock() const{return InterlockedExchange(&m_lockForObservingInMainThread, 1) == 0;}
	void Unlock() const{InterlockedExchange(&m_lockForObservingInMainThread, 0);}
	void LockWait() const{while(!Lock())Sleep(0);}
*/
/*
	bool LockExecutionStorage(){return InterlockedExchange(&m_lockExecutionStorage, 1) == 0;}
	void UnlockExecutionStorage(){InterlockedExchange(&m_lockExecutionStorage, 0);}
	void LockWaitExecutionStorage(){while(!LockExecutionStorage())Sleep(0);}
*/
	const char& GetSide() const{return m_side;}

#ifdef FIRM_VALUES
	const char& GetFirmSide() const{return m_firmSide;}
#endif

	OrderSide GetOrderSide() const{return m_orderSide;}

//	virtual unsigned int GetDestinationName() const{return 0;}

	void AddInThreadObserver(Observer* o) const;//Call RemoveInThreadObserver in the destructor of the object that you pass to this function
	void RemoveInThreadObserver(Observer* o) const;
//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;
	void ClearInThreadObservers() const;

	unsigned int GetExecutionCount() const{return (unsigned int)m_executionMap.GetCount();}

	bool isOrderNight() const;
	bool isOrderPassive() const;
	bool isStopOrder() const;
	bool isLimitOnClose() const;
	virtual bool isWashable() const;
	virtual bool isLimitDayToRemove() const;

	static const Price& GetOrderPricePerShare(const Price& limitPrice, const Price& level1Price, char side, bool borrow)
	{
		return (limitPrice.isZero() || side != 'B' && limitPrice < level1Price) && !borrow ? level1Price : limitPrice;
	}

	const unsigned char& GetOrderType() const{return m_orderType;}
	const unsigned short& GetUserOrderType() const{return m_userOrderType;}
	const std::string& GetUserOrderTypeString() const;
	const char* const& GetUserOrderInfo() const{return m_userOrderInfo;}
	const unsigned char& GetStopOrderType() const{return m_stopOrderType;}
	const unsigned char& GetStopOrderBase() const{return m_stopOrderBase;}
	const Price& GetLimitPrice() const{return m_limitPrice;}
	const Price& GetDiscretionaryPrice() const{return m_discretionaryPrice;}
	const SignedPrice& GetStopPrice() const{return m_stopPrice;}
	const Price& GetLevel1Price() const{return m_level1Price;}
	const Price& GetLevel1SameSidePrice() const{return m_level1SameSidePrice;}
	const Price& GetPricePerShare() const{return m_pricePerShare;}
	const Price& GetQuotePrice() const{return m_quotePrice;}//for displaying the order among quotes in the MmBox

	const unsigned int& GetQuantity() const{return m_quantity;}
	const unsigned int& GetDisplayQuantity() const{return m_displayQuantity;}
	const unsigned int& GetReserveQuantity() const{return m_reserveQuantity;}

	const unsigned int& GetFilledQuantity() const{return m_filledQuantity;}
	const unsigned int& GetCanceledQuantity() const{return m_canceledQuantity;}
	const unsigned int& GetExpiredQuantity() const{return m_expiredQuantity;}
	const unsigned int& GetRejectedQuantity() const{return m_rejectedQuantity;}

	const unsigned int& GetPendingQuantity() const{return m_pendingQuantity;}
	const unsigned int& GetQuantityBeingCanceled() const{return m_quantityBeingCanceled;}

	bool isRejected() const{return m_rejectedQuantity == m_quantity;}

	const unsigned char& GetTifType() const{return m_tifType;}
	const unsigned int& GetTifMillisecond() const{return m_tifMillisecond;}
	bool GetTifAsString(std::string& text, bool showMillisecond) const
	{
		return TU_GetTifAsString(text, m_tifType, m_monitorTif, NULL, m_tifMillisecond, showMillisecond, "ERROR", false);
/*
		bool ret = false;
		switch(m_tifType)
		{
			case TIF_DAY:
			text += "Day";
			break;
	
//			case TIF_GTC:		//Good Till Cancel (GTC)
//			text = "GTC";
//			break;
	
			case TIF_OPG:		//At the Opening (OPG)
			text += "OnOpen";
			break;

			case TIF_IOC:		//Immediate Or Cancel (IOC)
			text += "IOC";
			break;

			case TIF_FOK:		//Fill Or Kill (FOK)
			text += "FOK";
			break;

			case TIF_GTX:		//Good Till Crossing (GTX)
			text += "Extended";//"GTX";
			break;

			case TIF_GTD:		//Good Till Date (GTD)
			ret = true;
			if(m_monitorTif)
			{
				text += 't';
				text += '=';
			}
			U_AppendMillisecond(text, m_tifMillisecond, showMillisecond, '\0');
			break;

			case TIF_ATC:		//At the Close
			text += "OnClose";//"ATC";
			break;
	
//			case GT_XPR:	// Express
//			text += "XPR";
//			break;

//			case GT_DAY_PLUS:	// Day Plus (Day+)
//			text += "Day+";
//			break;

			default:
			text += "ERROR";
			break;
		}
		return ret;
*/
	}
	bool isOnOpen() const{return m_tifType == TIF_OPG;}
	bool isOnClose() const{return m_tifType == TIF_ATC;}
	
	unsigned char GetAlgorithmMask() const
	{
		return isAlgorithm() ? 1 << ALGORITHMMASK_YES :
			!m_stopPrice.isZero() || m_stopOrderType != 0 ? 1 << ALGORITHMMASK_STOP :
			m_limitPrice.isZero() ? 1 << ALGORITHMMASK_MARKET : 1 << ALGORITHMMASK_LIMIT;
	}

	unsigned char GetVisibleSizeMask() const{return m_displayQuantity == 0 ? 1 << VSM_HIDDEN : 1 << VSM_VISIBLE;}

	unsigned char GetOddLotMask() const{return m_oddLot ? 1 << OLM_ODDLOT : 1 << OLM_EVENLOT;}

	unsigned char GetTifMask() const
	{
		switch(m_tifType)
		{
			case TIF_DAY:
			return 1 << TIFMASK_DAY;

			case TIF_GTX:
			return 1 << TIFMASK_EXTENDED;

			case TIF_OPG:
			return 1 << TIFMASK_ON_OPEN;

			case TIF_ATC:
			return 1 << TIFMASK_ON_CLOSE;

			case TIF_GTD:
			return 1 << TIFMASK_TIME;

			case TIF_IOC:
			return 1 << TIFMASK_IOC;

			case TIF_FOK:
			return 1 << TIFMASK_FOK;

			default:
			return 1 << TIFMASK_OTHER;
		}
	}

	const unsigned int& GetTimeCreated() const{return m_timeCreated;}
	const unsigned int& GetTimeToExpire() const{return m_timeToExpire;}
	const unsigned int& GetTimeSent() const{return m_timeSent;}
	const unsigned int& GetTimeAcknowledged() const{return m_timeAcknowledged;}
	const unsigned int& GetTimeOnMarket() const{return m_timeOnMarket;}
	const unsigned int& GetTimeCancelCreated() const{return m_timeCancelCreated;}
	const unsigned int& GetTimeCancelSent() const{return m_timeCancelSent;}
	const unsigned int& GetTimeCancelAcknowledged() const{return m_timeCancelAcknowledged;}
	const unsigned int& GetTimeDead() const{return m_timeDead;}

	const unsigned int& GetTimeAcknowledgedReceived() const{return  m_timeAcknowledgedReceived;}
	const unsigned int& GetTimeOnMarketReceived() const{return  m_timeOnMarketReceived;}
	const unsigned int& GetTimeCancelAcknowledgedReceived() const{return  m_timeCancelAcknowledgedReceived;}
	const unsigned int& GetTimeCancelRejectReceived() const{return m_timeCancelRejectReceived;}
	const unsigned int& GetTimeDeadReceived() const{return  m_timeDeadReceived;}

	const short& GetServerDelay() const{return m_serverDelay;}
	const short& GetMarketDelay() const{return m_marketDelay;}

	const unsigned int& GetDestination() const{return m_destination;}

	const bool& isOpening() const{return m_opening;}

	const bool& isImbalanceOnly() const{return m_imbalanceOnly;}
//	const bool& isProactive() const{return m_proactive;}
	const bool& isNonCancelable() const{return m_nonCancelable;}
	const bool& isIso() const{return m_iso;}
	const bool& isAggressive() const{return m_aggressive;}
	const Price& GetAveragePrice() const{return m_averagePrice;}
	const Money& GetBpUsed() const{return m_bpUsed;}

	const Money& GetMoneyExecuted() const{return m_moneyExecuted;}
	const Money& GetClosedPnl() const{return m_closedPnl;}
	const Money& GetClosedPnlCost() const{return m_closedPnlCost;}
	const Money& GetPositionMarkedPnl() const{return m_positionMarkedPnl;}
	const Money& GetAccountMarkedPnl() const{return m_accountMarkedPnl;}
	const Money& GetPositionClosedPnl() const{return m_positionClosedPnl;}
	const Money& GetAccountClosedPnl() const{return m_accountClosedPnl;}

//	Position* GetPosition(){return m_position;}
	const Position* GetPosition() const{return m_position;}
	const Account* GetAccount() const;
	const ExecutionMap& GetExecutionMap() const{return m_executionMap;}

	const OrderState& GetOrderState() const{return m_orderState;}
	const std::string& GetOrderStateStr() const;
	virtual const std::string& GetStopOrderTypeStr() const;
	virtual const std::string& GetStopOrderBaseStr() const;

	const std::string& GetMarketReferenceId() const{return m_marketReferenceId;}

	unsigned char Cancel();
	const unsigned char& isBeingCanceled() const{return m_beingCanceled;}
	bool isDead() const{return m_orderState == TU_OS_DEAD;}
	bool isDeleted() const{return m_deleted;}

	virtual unsigned char ReplacePriceAndSize(bool replaceNative,
		const SignedPrice& replacePriceOffset,
		int replaceSizeOffset,
		const unsigned __int64& userId,
		unsigned char displaySizeMode,//0 - size fraction, 1 - round lot, 2 - no change
		unsigned int displaySize,
		unsigned int displaySizeFraction)
	{
		return OE_OK;
	}

	const unsigned char& GetPegType() const{return m_pegType;}
	const SignedPrice& GetPegOffset() const{return m_pegOffset;}

	const unsigned short& GetRejectCode() const{return m_rejectCode;}
	const char* const& GetRejectText() const{return m_rejectText;}

	void SetBeingCanceled(const unsigned char& canceled){m_beingCanceled = canceled;}
	void SetDeleted(){m_deleted = true;}
	virtual void EndAlgorithm()
	{
		m_deleted = true;
	}
	virtual void EndAlgorithmInThread(){}

	const char& GetOrigin() const{return m_origin;}
	const bool& isDropcopy() const{return m_dropcopy;}
	const bool& isBorrow() const{return m_borrow;}
	const bool& isResizeToClose() const{return m_resizeToClose;}
	const bool& isProAts() const{return m_proAts;}
	const bool& isOddLot() const{return m_oddLot;}
	const bool& isOddLotCreated() const{return m_oddLotCreated;}
	const bool& isNotSent() const{return m_notSent;}
	const unsigned int& GetRoundLot() const{return m_roundLot;}

	const unsigned int& GetRoutingName() const{return m_routingName;}
	const unsigned short& GetRoutingId() const{return m_routingId;}
	const unsigned short& GetRoutingSubType() const{return m_routingSubType;}
	const unsigned int& GetMnemonic() const{return m_mnemonic;}

	const int& GetPositionSize() const{return m_positionSize;}

	bool isDeadNotified() const{return m_deadNotified;}
	void SetDeadNotified(bool notified){m_deadNotified = notified;}//don't call this function

	const bool& isMonitorTif() const{return m_monitorTif;}
	const unsigned short& GetCancelRejectCode() const{return m_cancelRejectCode;}

	const bool& isNoMassCancel() const{return m_noMassCancel;}
	void SetNoMassCancel(bool noMassCancel){m_noMassCancel = noMassCancel;}

	const unsigned char& GetProblemFlags() const{return m_problemFlags;}

	bool isCancelRejected() const{return (m_problemFlags & (1 << OP_CANCEL_REJECTED)) != 0;}
	bool isCancelBlocked() const{return (m_problemFlags & (1 << OP_CANCEL_BLOCKED)) != 0;}

	bool isStuck() const{return (m_problemFlags & (1 << OP_STUCK)) != 0;}
	virtual void WriteStuckToAccountThread(bool stuck){}
	virtual void WriteOrderCancelToMainThread(){}
//	virtual void WriteOrderUpdateMessageToMainThread(bool killed, bool rejected, bool cancelAck){}
	virtual void WriteOrderUpdateMessageToMainThread(bool killed, bool rejected, unsigned char flags){}//1 - cancelAck, 2 - loaded order updated with an execution
	void NotifyInThreadObservers(const Message* message, const Message* info = NULL) const//should be called only from the worker thread
	{
		m_lockInThreadObservable.LockInquiryWait();
		m_inThreadObservable.NotifyObservers(message, info, this);
		m_lockInThreadObservable.UnlockInquiry();
	}
#ifndef TAKION_NO_OPTIONS
	const OptionSymbolBlock* GetOptionSymbolBlock() const;
//	OptionSymbolBlock* GetOptionSymbolBlock();
	const unsigned __int64& GetOptionBlock() const;
	const unsigned __int64& GetUnderlierNumericSymbol() const;
	bool isCall() const;
	unsigned char GetSuffix() const;
	unsigned char GetCallPutFlags() const;
	const unsigned char& GetOptionFlags() const;
	const unsigned int& GetStrikePrice() const;
	unsigned int GetExpirationDate() const;
	const unsigned char& GetExpirationType() const;
	const unsigned int& GetExpirationDays() const;
	const char& GetExpirationTypeChar() const;
	void GetOptionBlockAsString(std::string& optionSymbol, bool suffixSeparate) const;
	void GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const;
	unsigned char GetInstrumentMask() const{return 1 << GetSecurityType();}
	const unsigned int& GetContractSize() const;
#endif
	Order& operator=(const Order& other);
protected:
	Order(const Position* position,
		unsigned int traderId,
		unsigned int clientId,
		unsigned int clientIdOriginal,
		unsigned int clientIdChronological,
		unsigned int destinationId,
		unsigned int destinationName,

		char side,
#ifdef FIRM_VALUES
		char firmSide,
#endif

		unsigned char orderType,
		unsigned short userOrderType,//usually should be 0
		const char* userOrderInfo,//usually should be NULL
		const Price& limitPrice,

		const Price& discretionaryPrice,

		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const SignedPrice& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,

		unsigned int mnemonic,

		bool opening,
//		bool proactive,
		bool imbalanceOnly,
		bool nonCancelable,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		char origin,
		bool dropcopy,
		bool borrow,
		bool resizeToClose,
		bool proAts,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		unsigned char tifType,
		bool monitorTif,
		unsigned int tifMillisecond,
		unsigned int filledQuantity,// = 0,
		unsigned int expiredQuantity,// = 0,
		unsigned int canceledQuantity,// = 0,
		unsigned int rejectedQuantity,// = 0,
		unsigned int parentId,// = 0,
		const unsigned __int64& userId);// = 0);
	Order(const Order& other);
/*
	char m_symbol[16];
	unsigned __int64 m_numericSymbol;
	SecurityType m_securityType;
	Account* m_account;
*/
	Observable m_inThreadObservable;
	TakionLockMultithread m_lockInThreadObservable;

	const Position* m_position;

	unsigned int m_traderId;
	unsigned int m_clientId;
	unsigned int m_clientIdOriginal;
	unsigned int m_clientIdChronological;
	unsigned int m_serverId;
	unsigned int m_parentId;
	unsigned __int64 m_userId;
	unsigned int m_destinationId;

	unsigned int m_destination;

	unsigned short m_userOrderType;

	char m_side;
#ifdef FIRM_VALUES
	char m_firmSide;
#endif
	OrderSide m_orderSide;
	unsigned char m_orderType;
	unsigned char m_stopOrderType;
	unsigned char m_stopOrderBase;
	Price m_limitPrice;

	Price m_discretionaryPrice;
	SignedPrice m_stopPrice;

	Price m_level1Price;
	Price m_level1SameSidePrice;

	Price m_pricePerShare;

	int m_positionSize;

	unsigned int m_quantity;
	unsigned int m_displayQuantity;
	unsigned int m_reserveQuantity;

	unsigned int m_filledQuantity;
	unsigned int m_canceledQuantity;
	unsigned int m_expiredQuantity;
	unsigned int m_rejectedQuantity;

	unsigned int m_pendingQuantity;
	unsigned int m_quantityBeingCanceled;

	unsigned char m_tifType;
	unsigned int m_tifMillisecond;
	unsigned int m_timeCreated;
	unsigned int m_timeToExpire;
	unsigned int m_timeSent;
	unsigned int m_timeAcknowledged;
	unsigned int m_timeOnMarket;
	unsigned int m_timeCancelCreated;
	unsigned int m_timeCancelSent;
	unsigned int m_timeCancelAcknowledged;
	unsigned int m_timeDead;

	unsigned int m_timeAcknowledgedReceived;
	unsigned int m_timeOnMarketReceived;
	unsigned int m_timeCancelAcknowledgedReceived;
	unsigned int m_timeCancelRejectReceived;
	unsigned int m_timeDeadReceived;
	unsigned int m_roundLot;

	unsigned int m_mnemonic;
	unsigned int m_routingName;
	unsigned short m_routingId;
	unsigned short m_routingSubType;

	short m_serverDelay;
	short m_marketDelay;

	unsigned short m_cancelRejectCode;

	std::string m_marketReferenceId;

//	bool m_stuck;
//	bool m_proactive;
	OrderState m_orderState;
	unsigned char m_problemFlags;
	bool m_deadNotified;
	bool m_monitorTif;
	bool m_noMassCancel;
	bool m_opening;
	bool m_imbalanceOnly;
	bool m_nonCancelable;
	bool m_iso;
	bool m_aggressive;
	unsigned char m_beingCanceled;
	bool m_beingReplaced;
	bool m_deleted;
	bool m_oddLot;
	bool m_oddLotCreated;
	char m_origin;
	bool m_dropcopy;
	bool m_borrow;
	bool m_resizeToClose;
	bool m_proAts;
	bool m_notSent;
	unsigned char m_pegType;

	SignedPrice m_pegOffset;

	Price m_quotePrice;//for displaying the order among quotes in the MmBox

	Price m_averagePrice;
	Money m_bpUsed;

	Money m_moneyExecuted;
	Money m_closedPnl;
	Money m_closedPnlCost;

	Money m_positionMarkedPnl;
	Money m_accountMarkedPnl;

	Money m_positionClosedPnl;
	Money m_accountClosedPnl;

	unsigned short m_rejectCode;
	char* m_rejectText;

	char* m_userOrderInfo;

	ExecutionMap m_executionMap;
};

inline void RemoveOrderFromChronologicalMap(Order* order, OrderChronologicalMap& orderMap)
{
	std::pair<OrderChronologicalMap::iterator, OrderChronologicalMap::iterator> p = orderMap.equal_range(order->GetClientIdChronological());
	for(OrderChronologicalMap::iterator& it = p.first, itend = p.second; it != itend; ++it)
	{
		if(it->second == order)
		{
			orderMap.erase(it);
			break;
		}
	}
}

class TU_API DisplayGreenie : public Quote
{
public:
	DisplayGreenie(const Quote& quote, unsigned int fractionDollar, unsigned int fractionDivider):
		Quote(quote),
		m_paintDelay(0),
		m_quoteCondition(quote.GetCondition()),
		m_retailLiquidity(quote.GetRetailLiquidity())
	{
		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
	DisplayGreenie(bool bid, unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, EcnBookId bookId, unsigned int mmid, unsigned int millisecond, short delay, bool historical, unsigned int fractionDollar, unsigned int fractionDivider):
		Quote(bid, dollars, dollarFraction, quantity, bookId, mmid, millisecond, delay),
		m_paintDelay(0),
		m_quoteCondition('\0'),
		m_retailLiquidity(false)
	{
		CalculateDisplayPrice(fractionDollar, fractionDivider);
		m_historical = historical;
	}

	DisplayGreenie(bool bid, const Price& price, unsigned int quantity, EcnBookId bookId, unsigned int mmid, unsigned int millisecond, short delay, bool historical, unsigned int fractionDollar, unsigned int fractionDivider):
		Quote(bid, price, quantity, bookId, mmid, millisecond, delay),
		m_paintDelay(0),
		m_quoteCondition('\0'),
		m_retailLiquidity(false)
	{
		CalculateDisplayPrice(fractionDollar, fractionDivider);
		m_historical = historical;
	}

	DisplayGreenie()://empty display line
		Quote(true, 0, 0, 0, AllBooks, 0, 0, 0),
		m_displayPriceDollar(0),
		m_displayPriceFraction(0),
		m_fractionDivider(Price::divider),
		m_paintDelay(0),
		m_quoteCondition('\0'),
		m_retailLiquidity(false)
	{
	}
	void SetEmptyPrice()
	{
		SetZero();
		m_paintDelay = 0;
		m_displayPriceDollar = 0;
		m_displayPriceFraction = 0;
		m_quantity = 0;
		m_millisecond = 0;
		m_delay = 0;
		m_historical = true;
		m_quoteCondition = '\0';
		m_retailLiquidity = false;
	}
	void SetEmpty()
	{
		SetEmptyPrice();
		m_mmid = 0;
	}
//	bool isEmpty() const{return m_quantity == 0 && isZero();}
	inline void SetQuote(const Quote& quote, const unsigned int& fractionDollar, const unsigned int& fractionDivider)
	{
		Quote::operator=(quote);
		CalculateDisplayPrice(fractionDollar, fractionDivider);
		m_quoteCondition = quote.GetCondition();
		m_retailLiquidity = quote.GetRetailLiquidity();
	}
//	bool SameQuantity(const DisplayGreenie& other) const{return m_quantity == other.m_quantity;}
	void SetQuoteQuantity(const Quote& quote)
	{
		m_quantity = quote.GetQuantity();
		m_millisecond = quote.GetMillisecond();
		m_delay = quote.GetDelay();
		m_quoteCondition = quote.GetCondition();
		m_retailLiquidity = quote.GetRetailLiquidity();
//		m_bookId = quote.GetBookId();
	}
	virtual char GetCondition() const{return m_quoteCondition;}
	virtual bool GetRetailLiquidity() const{return m_retailLiquidity;}
	unsigned int GetFractionDivider() const{return m_fractionDivider;}
	unsigned int GetDisplayPriceDollar() const{return m_displayPriceDollar;}
	unsigned int GetDisplayPriceFraction() const{return m_displayPriceFraction;}
	short GetPaintDelay() const{return m_paintDelay;}
	void SetPaintDelay(short delay){m_paintDelay = delay;}
	void AddDisplayGreenie(const Quote& quote, const bool& updatePrice, const bool& millisecond, const bool& delay, const bool& quoteCondition, const unsigned int& roundLotToSubtract)
	{
		if(m_quantity)
		{
			if(updatePrice)
			{
				Price::operator=(quote);
			}
			if(millisecond && m_millisecond < quote.GetMillisecond())
			{
				m_millisecond = quote.GetMillisecond();
			}
			if(delay)
			{
				if(!quote.isHistorical())
				{
					if(m_historical)
					{
						m_historical = false;
						m_delay = quote.GetDelay();
					}
					else if(m_delay < quote.GetDelay())
					{
						m_delay = quote.GetDelay();
					}
				}
			}
			if(quoteCondition)
			{
				if(!m_quoteCondition)
				{
					m_quoteCondition = quote.GetCondition();
				}
				if(!m_retailLiquidity)
				{
					m_retailLiquidity = quote.GetRetailLiquidity();
				}
			}
		}
		else
		{
			Price::operator=(quote);
			if(millisecond)
			{
				m_millisecond = quote.GetMillisecond();
			}
			if(delay)
			{
				m_delay = quote.GetDelay();
				m_historical = quote.isHistorical();
			}
			if(quoteCondition)
			{
				m_quoteCondition = quote.GetCondition();
				m_retailLiquidity = quote.GetRetailLiquidity();
			}
		}
		if(roundLotToSubtract)
		{
			m_quantity += quote.GetQuantity() % roundLotToSubtract;
		}
		else
		{
			m_quantity += quote.GetQuantity();
		}
	}
	enum GreenieChangeFlags : unsigned char
	{
		GCF_PRICE,
		GCF_SIZE,
		GCF_TIMESTAMP,
		GCF_DELAY,
		GCF_QUOTE_CONDITION,

		GCF_Count
	};
	unsigned char SetDisplayGreenie(const DisplayGreenie& other, const bool& millisecond, const bool& delay, const bool& quoteCondition)
	{
		unsigned char changed = 0;
		Price::operator=(other);

		if(m_displayPriceDollar != other.m_displayPriceDollar)
		{
			m_displayPriceDollar = other.m_displayPriceDollar;
			changed |= 1 << GCF_PRICE;
		}
		if(m_displayPriceFraction != other.m_displayPriceFraction)
		{
			m_displayPriceFraction = other.m_displayPriceFraction;
			changed |= 1 << GCF_PRICE;
		}

		if(m_quantity != other.m_quantity)
		{
			if(!m_quantity != !other.m_quantity)
			{
				changed |= 1 << GCF_Count;
			}
			m_quantity = other.m_quantity;
			changed |= 1 << GCF_SIZE;
		}

		if(millisecond && m_millisecond != other.m_millisecond)
		{
			m_millisecond = other.m_millisecond;
			changed |= 1 << GCF_TIMESTAMP;
		}
		if(delay && (m_delay != other.m_delay || m_historical != other.m_historical))
		{
			m_delay = other.m_delay;
			m_historical = other.m_historical;
			changed |= 1 << GCF_DELAY;
		}

		if(quoteCondition)
		{
			if(m_quoteCondition != other.m_quoteCondition)
			{
				m_quoteCondition = other.m_quoteCondition;
				changed |= 1 << GCF_QUOTE_CONDITION;
			}
			if(m_retailLiquidity != other.m_retailLiquidity)
			{
				m_retailLiquidity = other.m_retailLiquidity;
				changed |= 1 << GCF_QUOTE_CONDITION;//GCF_RETAIL_LIQUIDITY;
			}
		}
/*
		else
		{
			SetZero();
			m_millisecond = 0;
			m_delay = 0;
			m_historical = true;

			m_displayPriceDollar = 0;
			m_displayPriceFraction = 0;
			m_quoteCondition = '\0';
			m_retailLiquidity = false
			if(m_quantity)
			{
				m_quantity = 0;
				changed = true;
			}
		}
*/
		return changed;
	}
	inline void CalculateDisplayPrice(const unsigned int& fractionDollar, const unsigned int& fractionDivider)
	{
		m_fractionDivider = fractionDivider;
		m_displayPriceDollar = m_dollars;
		m_displayPriceFraction = m_dollarFraction / fractionDivider;
		if(!m_bid && m_dollarFraction != m_displayPriceFraction * fractionDivider)
		{
			++m_displayPriceFraction;
			if(m_displayPriceFraction == fractionDollar)
			{
				m_displayPriceFraction = 0;
				++m_displayPriceDollar;
			}
		}
	}
protected:
	unsigned int m_displayPriceDollar;
	unsigned int m_displayPriceFraction;
	unsigned int m_fractionDivider;
	short m_paintDelay;
	char m_quoteCondition;
	bool m_retailLiquidity;
};

class TU_API DisplayQuote : public DisplayGreenie
{
public:
	DisplayQuote(const Quote& quote, unsigned int fractionDollar, unsigned int fractionDivider, COLORREF color):
		DisplayGreenie(quote, fractionDollar, fractionDivider),
		m_color(color),
		m_direct(quote.isDirect()),
		m_order('\0'),
		m_hidden(false),
		m_attributed(quote.isAttributed()),
		m_quoteId(quote.GetId())
	{
//		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
	DisplayQuote(const Order& order, unsigned int fractionDollar, unsigned int fractionDivider, COLORREF color):
		DisplayGreenie(order.GetSide() == 'B', order.GetQuotePrice(), order.GetPendingQuantity(), BOOK_LEVEL2, order.GetDestination(), order.GetTimeCreated(), order.GetMarketDelay(), order.GetOrigin() == OO_HISTORICAL, fractionDollar, fractionDivider),
		m_color(color),
		m_direct(true),
		m_order(1),
		m_hidden(!order.GetDisplayQuantity()),
		m_attributed(false),
		m_quoteId(order.GetClientId())
	{
//		m_historical = order.GetOrigin() == OO_HISTORICAL;
//		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
	DisplayQuote(unsigned int mmid, const Price& price, bool bid, unsigned int millisecond, short delay, bool historical, unsigned int fractionDollar, unsigned int fractionDivider, COLORREF color):
//		DisplayGreenie(bid, price, 0, BOOK_LEVEL2, lrpNum, millisecond, delay, historical, fractionDollar, fractionDivider),
		DisplayGreenie(bid, price, 0, BOOK_LEVEL2, mmid, millisecond, delay, historical, fractionDollar, fractionDivider),
		m_color(color),
		m_direct(true),
		m_order(0),
		m_hidden(false),
		m_attributed(false),
		m_quoteId(0)
	{
//		m_historical = historical;
//		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
	DisplayQuote()://empty display line
//		DisplayGreenie(true, 0, 0, 0, AllBooks, 0, 0, 0),
//		m_paintDelay(0),
//		m_displayPriceDollar(0),
//		m_displayPriceFraction(0),
//		m_fractionDivider(Price::divider),
		m_color(0),
		m_direct(true),
		m_order('\0'),
		m_hidden(false),
		m_attributed(false),
		m_quoteId(0)
	{}
	void SetEmpty()
	{
		DisplayGreenie::SetEmpty();
//		SetZero();
//		m_paintDelay = 0;
//		m_displayPriceDollar = 0;
//		m_displayPriceFraction = 0;

//		m_quantity = 0;
//		m_mmid = 0;

		m_quoteId = 0;

		m_order = '\0';//false;
//		m_hidden = false;
//		m_attributed = false;
//////////
		m_color = 0;
//		m_quoteCondition = '\0';
		m_direct = false;
	}
	void SetHasOrders(bool hasOrders){if(m_order != 1)m_order = hasOrders ? 2 : 0;}
	void SetHidden(bool hidden){m_hidden = hidden;}
	void SetAttributed(bool attributed){m_attributed = attributed;}
	void SetQuoteId(quoteid id){m_quoteId = id;}
	quoteid GetQuoteId() const{return m_quoteId;}
	COLORREF GetColor() const{return m_color;}
	void SetColor(COLORREF color){m_color = color;}
	inline void SetQuote(const Quote& quote, const unsigned int& fractionDollar, const unsigned int& fractionDivider, unsigned char orderMode, bool hidden)
	{
		DisplayGreenie::SetQuote(quote, fractionDollar, fractionDivider);
		m_direct = quote.isDirect();
		m_quoteId = quote.GetId();
		m_order = orderMode;//quote.GetOrder();
		m_hidden = hidden;
		m_attributed = quote.isAttributed();
//		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
	inline void SetQuote(const Order& order, const unsigned int& fractionDollar, const unsigned int& fractionDivider)
	{
		Price::operator=(order.GetQuotePrice());
		m_quantity = order.GetPendingQuantity();
		m_millisecond = order.GetTimeCreated();
		m_bid = order.GetSide() == 'B';
		m_mmid = order.GetDestination();
		m_bookId = BOOK_LEVEL2;
		m_delay = order.GetMarketDelay();
		m_historical = order.GetOrigin() == OO_HISTORICAL;
		m_quoteCondition = '\0';
		m_retailLiquidity = false;
		m_direct = true;
		m_quoteId = order.GetClientId();
		m_order = 1;//true;
		m_hidden = !order.GetDisplayQuantity();
		m_attributed = false;
		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
//	inline void SetLrp(const Price& price, bool bid, unsigned int millisecond, short delay, bool historical, const unsigned int& fractionDollar, const unsigned int& fractionDivider)
	inline void SetMmid(unsigned int mmid, const Price& price, bool bid, unsigned int millisecond, short delay, bool historical, const unsigned int& fractionDollar, const unsigned int& fractionDivider)
	{
		Price::operator=(price);
		m_quantity = 0;
		m_millisecond = millisecond;
		m_bid = bid;
		m_mmid = mmid;//lrpNum;
		m_bookId = BOOK_LEVEL2;
		m_delay = delay;
		m_historical = historical;
		m_quoteCondition = '\0';
		m_retailLiquidity = false;
		m_direct = true;
		m_quoteId = 0;
		m_order = 0;
		m_hidden = false;
		m_attributed = false;
		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
	bool isQuoteProper() const{return m_order != 1 && m_mmid != lrpNum && m_mmid != luldNum;}
	bool SamePriceMmidColor(const DisplayQuote& other) const{return m_displayPriceDollar == other.m_displayPriceDollar && m_displayPriceFraction == other.m_displayPriceFraction && m_mmid == other.m_mmid && m_color == other.m_color && m_direct == other.m_direct && m_order == other.m_order && m_hidden == other.m_hidden && m_attributed == other.m_attributed && m_bookId == other.m_bookId;}
//	bool SameQuantity(const DisplayQuote& other) const{return m_quantity == other.m_quantity;}
	void SetQuoteQuantity(const Quote& quote)
	{
		DisplayGreenie::SetQuoteQuantity(quote);
//		m_quantity = quote.GetQuantity();
//		m_millisecond = quote.GetMillisecond();
//		m_delay = quote.GetDelay();
		m_bookId = quote.GetBookId();

//		m_quoteCondition = quote.GetCondition();
		m_direct = quote.isDirect();
		m_quoteId = quote.GetId();
		m_order = quote.GetOrder();
		m_hidden = quote.isHidden();
		m_attributed = quote.isAttributed();
//		m_bookId = quote.GetBookId();
	}
	void SetOrderQuantity(const Order& order)
	{
		m_quantity = order.GetPendingQuantity();
		m_order = 1;//true;
		m_hidden = !order.GetDisplayQuantity();
		m_attributed = false;
		m_quoteCondition = '\0';
		m_retailLiquidity = false;
//		m_direct = false;
	}
	unsigned int GetOrderId() const{return m_order == 1 ? (unsigned int)m_quoteId : 0;}
//	virtual char GetCondition() const{return m_quoteCondition;}
	virtual bool isAttributed() const{return m_attributed;}
	virtual bool isDirect() const{return m_direct;}
	virtual quoteid GetId() const{return m_quoteId;}
	virtual unsigned char GetOrder() const{return m_order;}
	virtual bool isHidden() const{return m_hidden;}
/*
	unsigned int GetFractionDivider() const{return m_fractionDivider;}
	unsigned int GetDisplayPriceDollar() const{return m_displayPriceDollar;}
	unsigned int GetDisplayPriceFraction() const{return m_displayPriceFraction;}
	short GetPaintDelay() const{return m_paintDelay;}
	void SetPaintDelay(short delay){m_paintDelay = delay;}
*/
protected:
/*
	inline void CalculateDisplayPrice(const unsigned int& fractionDollar, const unsigned int& fractionDivider)
	{
		m_fractionDivider = fractionDivider;
		m_displayPriceDollar = m_dollars;
		m_displayPriceFraction = m_dollarFraction / fractionDivider;
		if(!m_bid && m_dollarFraction != m_displayPriceFraction * fractionDivider)
		{
			++m_displayPriceFraction;
			if(m_displayPriceFraction == fractionDollar)
			{
				m_displayPriceFraction = 0;
				++m_displayPriceDollar;
			}
		}
	}

	short m_paintDelay;
	unsigned int m_displayPriceDollar;
	unsigned int m_displayPriceFraction;
	unsigned int m_fractionDivider;
*/
	COLORREF m_color;
//	char m_quoteCondition;
	bool m_direct;
	unsigned char m_order;
	bool m_hidden;
	bool m_attributed;
	quoteid m_quoteId;
};

class TU_API OrderAlgorithm : public Order, public Observer
{
public:
	virtual bool isPriceValid() const{return !m_limitPrice.isZero();}
	virtual OrderAlgorithm* CloneAlgorithm() const = 0;
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual bool isAlgorithm() const{return true;}
	void SetPosition(const Position* position){m_position = position;}

	virtual bool SecurityMustBeLoaded() const{return false;}

	virtual void ProcessMainThreadNotification(unsigned short code){}
//	bool isProactive() const{return m_proactive;}
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual unsigned int GetAlgorithmId() const = 0;
	virtual bool isQuantityValid() const{return GetQuantity() > 0;}
	const unsigned int& GetGeneratedOrderCount() const{return m_generatedOrderCount;}
	const bool& isSecuritySameThreadAsAccount() const{return m_securitySameThreadAsAccount;}
	const bool& isUseSecurityNotification() const{return m_useSecurityNotification;}
	const unsigned int& GetSecurityUpdatedOrdinal() const{return m_securityUpdatedOrdinal;}
	const unsigned int& GetSecuritySentOrdinal() const{return m_securitySentOrdinal;}
	void SecurityUpdate();
	unsigned int CalculatePegPrice() const;
protected:
	OrderAlgorithm(const Position* position,
		unsigned int traderId,
		unsigned int clientId,
//		unsigned int clientIdOriginal,
		unsigned int destinationId,
		unsigned int destinationName,

		char side,

		unsigned char orderType,
		unsigned short userOrderType,//usually should be 0
		const char* userOrderInfo,//usually should be NULL
		const Price& limitPrice,

		const Price& discretionaryPrice,

		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const SignedPrice& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		bool resizeShortToBorrowed,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		unsigned char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,
		const unsigned __int64& userId,
		bool useSecurityNotification);
	OrderAlgorithm(const char*& fromString, bool useSecurityNotification);
	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL) override;
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = NULL){return false;}
	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = NULL) const{return false;}
	virtual void DoSecurityUpdate(){}
	virtual void NullifySecurity();
	const Security* m_security;
	Account* m_account;
	bool m_cancelWashOrders;
	unsigned char m_oversellSplitPolicy;//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
	bool m_resizeShortToBorrowed;
	bool m_noRedirect;
	bool m_closeOnly;
	unsigned char m_roundLotPolicy;

	bool m_securitySameThreadAsAccount;
	bool m_useSecurityNotification;
	unsigned int m_securityUpdatedOrdinal;
	unsigned int m_securitySentOrdinal;

	unsigned int m_generatedOrderCount;

//	bool m_proactive;
//	Position* m_position;
};

enum OrderAlgorithmId
{
	OA_ORDER_REPLACER,

	OA_COUNT
};

class TU_API OrderReplacer : public OrderAlgorithm
{
public:
	virtual bool isPriceValid() const{return true;}//!m_limitPrice.isZero();}

	void AddOrderClientId(unsigned int orderClientId){m_clientIdSet.insert(orderClientId);}
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual unsigned int GetAlgorithmId() const{return OA_ORDER_REPLACER;}
	typedef std::hash_set<Order*> OrderSet;
	typedef std::hash_set<unsigned int> UIntSet;
	virtual const char* GetAlgorithmName() const{return "Replacer";}
	virtual bool isQuantityValid() const;
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithmInThread();
	virtual unsigned int GetAlgorithmQuantity() const{return m_estimatedSize;}
protected:
	OrderReplacer(const Position* position,
		unsigned int orderToReplaceClientId,
		unsigned int traderId,
		unsigned int clientId,
//		unsigned int clientIdOriginal,
		unsigned int destinationId,
		unsigned int destinationName,

		char side,

		unsigned char orderType,
		unsigned short userOrderType,//usually should be 0
		const char* userOrderInfo,//usually should be NULL
		const Price& limitPrice,

		const Price& discretionaryPrice,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const SignedPrice& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,

		int replaceSizeOffset,
		unsigned int quantity,
		unsigned int estimatedQuantityToSend,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		bool resizeShortToBorrowed,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		unsigned char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,
		const unsigned __int64& userId);
	OrderReplacer(const char*& fromString);
	void SendReplacement();
	virtual void DoSendReplacement(){}
	OrderSet m_orderSet;
	UIntSet m_clientIdSet;
	unsigned int m_orderDestinationName;
	int m_replaceSizeOffset;
	unsigned int m_estimatedSize;
	unsigned int m_unexecutedShares;
	unsigned int m_clientIdChronologicalToSend;
};

struct lessOrderPrice : public std::binary_function<Order*, Order*, bool>
{	// functor for operator<
	bool operator()(const Order* const& o1, const Order* const& o2) const
	{	// apply operator< to operands
//		return o1->GetLimitPrice() < o2->GetLimitPrice() || o1->GetLimitPrice() == o2->GetLimitPrice() && o1->GetClientId() < o2->GetClientId();
		return o1->GetQuotePrice() < o2->GetQuotePrice() || o1->GetQuotePrice() == o2->GetQuotePrice() && o1->GetClientId() < o2->GetClientId();
	}
};

struct greaterOrderPrice : public std::binary_function<Order*, Order*, bool>
{	// functor for operator<
	bool operator()(const Order* const& o1, const Order* const& o2) const
	{	// apply operator< to operands
//		return o1->GetLimitPrice() > o2->GetLimitPrice() ?
//			!o2->GetLimitPrice().isZero() :
//			o1->GetLimitPrice() == o2->GetLimitPrice() && o1->GetClientId() < o2->GetClientId();
		return o1->GetQuotePrice() > o2->GetQuotePrice() ?
			!o2->GetQuotePrice().isZero() :
			o1->GetQuotePrice() < o2->GetQuotePrice() ?
				o1->GetQuotePrice().isZero() :
				o1->GetClientId() < o2->GetClientId();
	}
};

struct lessStopAndLimitOrderPrice : public std::binary_function<Order*, Order*, bool>
{
	bool operator()(const Order* const& o1, const Order* const& o2) const
	{
//		return o1->GetQuotePrice() < o2->GetQuotePrice() || o1->GetQuotePrice() == o2->GetQuotePrice() && o1->GetClientId() < o2->GetClientId();
		return o1->isStopOrder() ?
			!o2->isStopOrder() ||
				(o1->GetQuotePrice() > o2->GetQuotePrice() ?
					!o2->GetQuotePrice().isZero() :
				o1->GetQuotePrice() < o2->GetQuotePrice() ?
					o1->GetQuotePrice().isZero() :
					o1->GetClientId() < o2->GetClientId()):

			!o2->isStopOrder() &&
				(o1->GetQuotePrice() < o2->GetQuotePrice() || o1->GetQuotePrice() == o2->GetQuotePrice() && o1->GetClientId() < o2->GetClientId());
	}
};

struct greaterStopAndLimitOrderPrice : public std::binary_function<Order*, Order*, bool>
{
	bool operator()(const Order* const& o1, const Order* const& o2) const
	{
		return o1->isStopOrder() ?
			!o2->isStopOrder() ||
				(o1->GetQuotePrice() < o2->GetQuotePrice() || o1->GetQuotePrice() == o2->GetQuotePrice() && o1->GetClientId() < o2->GetClientId()):

			!o2->isStopOrder() &&
				(o1->GetQuotePrice() > o2->GetQuotePrice() ?
					!o2->GetQuotePrice().isZero() :
				o1->GetQuotePrice() < o2->GetQuotePrice() ?
					o1->GetQuotePrice().isZero() :
					o1->GetClientId() < o2->GetClientId());
	}
};

enum AutoCloseStatus : unsigned char
{
	ACS_NONE,
	ACS_AUTO_CLOSING_LONG,
	ACS_AUTO_CLOSING_SHORT,
	ACS_FLIPPED_TO_SHORT,
	ACS_FLIPPED_TO_LONG,
	ACS_NON_TRADABLE,

	ACS_COUNT
};

class TU_API BasePosition : public Observable, public TakionLock
{
public:
	virtual ~BasePosition(){}

	const char* GetSymbol() const{return (const char*)&m_numericSymbol;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
//	SecurityType GetSecurityType() const{return m_securityType;}

	const int& GetSize() const{return m_size;}
//	const unsigned int& GetAbsSize() const{return m_absSize;}
	const unsigned int& GetPendingSellPassiveShares() const{return m_pendingSellPassiveShares;}
	const unsigned int& GetPendingSellNonPassiveShares() const{return m_pendingSellNonPassiveShares;}

	const unsigned int& GetPendingShortPassiveShares() const{return m_pendingShortPassiveShares;}
	const unsigned int& GetPendingShortNonPassiveShares() const{return m_pendingShortNonPassiveShares;}

	const Security* GetASecurity() const{return m_security ? m_security : m_sortableSecurity;}//safe to call only from main thread
	const Security* GetSecurity() const{return m_security;}
	void SetSecurity(const Security* security){m_security = security;}
	const Security* GetSortableSecurity() const{return m_sortableSecurity;}//safe to call only from main thread
	void SetSortableSecurity(const Security* security){m_sortableSecurity = security;}

	void AddInThreadObserver(Observer* o) const;//Call RemoveInThreadObserver in the destructor of the object that you pass to this function
	void RemoveInThreadObserver(Observer* o) const;
//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;

	void NotifyInThreadObservers(const Message* message, const Message* info = NULL) const;
	virtual void WritePositionUpdateMessageToMainThread(unsigned char execution){}
	virtual void WriteMessageToPositionThread(const Message* message) const{}

	void NotifySecurityObservers(const Message* message, const Message* info);
	void AddSecurityObserver(Observer* o);
	void RemoveSecurityObserver(Observer* o);
	bool isSecurityObservable(Observable* o) const{return o == &m_securityObservable;}
	bool isNewPosition() const{return m_newPosition;}
	virtual unsigned int GetThreadId() const{return 0;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}
	virtual void Reset();
protected:
	BasePosition(const char* symbol);
	unsigned __int64 m_numericSymbol;
//	SecurityType m_securityType;
	const Security* m_security;
	const Security* m_sortableSecurity;
	int m_size;
	unsigned int m_pendingSellPassiveShares;
	unsigned int m_pendingSellNonPassiveShares;
	unsigned int m_pendingShortPassiveShares;
	unsigned int m_pendingShortNonPassiveShares;
	bool m_newPosition;

	Observable m_inThreadObservable;
	TakionLockMultithread m_lockInThreadObservable;
	Observable m_securityObservable;//main thread
};

#ifdef FIRM_VALUES

class AccountAggregator;

class TU_API FirmPosition : public BasePosition//public Observable, public TakionLock
{
public:
	virtual ~FirmPosition();
//	virtual void Destroy(){}
	bool SubscribeFirmPosition();
	bool UnsubscribeFirmPosition();
	const AccountAggregator* GetAccountAggregator() const{return m_accountAggregator;}
	const bool& isLoaded() const{return m_loaded;}
	const unsigned int& GetAvailableSellPassiveShares() const{return m_availableSellPassiveShares;}
	const unsigned int& GetAvailableSellNonPassiveShares() const{return m_availableSellNonPassiveShares;}
	const unsigned int& GetAvailableSellShares(bool passive) const{return passive ? m_availableSellPassiveShares : m_availableSellNonPassiveShares;}
	const unsigned int& GetSubscriptionCount() const{return m_subscriptionCount;}
	virtual void IncrementFirmSellShares(unsigned int shares, bool orderPassive){}
	virtual void DecrementFirmSellShares(unsigned int shares, bool orderPassive){}
	const char* GetClearingFirmName() const;
	const char* GetFirmName() const;
	const unsigned int& GetFirmNumericName() const;
	const short& GetDelay() const{return m_delay;}
	const unsigned int& GetTimeStamp() const{return m_timestamp;}
	const unsigned int& GetLoadedTimeStamp() const{return m_loadedTimestamp;}
	virtual unsigned int GetThreadId() const;
	const unsigned short& GetRejectCode() const{return m_rejectCode;}
	const char* const& GetRejectText() const{return m_rejectText;}
	const bool& isUntradeable() const{return m_untradeable;}
	virtual void Reset(){}
protected:
	FirmPosition(const AccountAggregator* accountAggregator, const char* symbol):
		BasePosition(symbol),
		m_accountAggregator(accountAggregator),
		m_availableSellPassiveShares(0),
		m_availableSellNonPassiveShares(0),
		m_subscriptionLock(0),
		m_subscriptionCount(0),
		m_timestamp(0),
		m_loadedTimestamp(0),
		m_delay(0),
		m_untradeable(false),
		m_loaded(false),
		m_rejectCode(0),
		m_rejectText(NULL)
		{}
	virtual void Resubscribe() const{}
	virtual bool Subscribe() const{return false;}
	virtual bool Unsubscribe() const{return false;}
	const AccountAggregator* m_accountAggregator;
	unsigned int m_availableSellPassiveShares;
	unsigned int m_availableSellNonPassiveShares;

//	mutable CCriticalSection m_subscriptionCriticalSection;
	volatile LONG m_subscriptionLock;

	unsigned int m_subscriptionCount;
	unsigned int m_timestamp;
	unsigned int m_loadedTimestamp;
	short m_delay;
	bool m_untradeable;
	mutable bool m_loaded;
	unsigned short m_rejectCode;
	char* m_rejectText;
};

//	const unsigned char& GetUntradeableLevel() const{return m_untradeableLevel;}//For Supervisor only. 0 - tradable; 1 - pending; 2 - untradeable.
enum UntradeableLevel : unsigned char
{
	UL_TRADABLE,
	UL_PENDING,
	UL_UNTRADEABLE,

	UL_Count
};

#endif

class TU_API PositionDataBase : public BasePosition
{
public:
	virtual Position* GetAccountPosition(){return NULL;}
	virtual const Position* GetAccountPosition() const{return NULL;}
	virtual Account* GetAccount() const{return NULL;}

	static const std::string stringZero;
	static const unsigned __int64 uint64Zero;
	static const unsigned int uintZero;
	static const unsigned int uintOne;
	static const unsigned char ucharZero;
	static const char charZero;
	static const bool boolFalse;
	static const int intZero;
	static const char space;

	static inline void DoDecrementNumber(unsigned int& number, const unsigned int& by)
	{
		if(number >= by)number -= by;
		else number = 0;
	}
	SecurityType GetSecurityType() const{return m_securityType;}
	bool isSizeOpening(bool buy, unsigned int size) const;

	const unsigned int& GetAbsSize() const{return m_absSize;}
	const unsigned int& GetAbsShareSize() const{return m_absShareSize;}
	const int& GetOvernightSize() const{return m_overnightSize;}
	const unsigned int& GetOvernightAbsSize() const{return m_overnightAbsSize;}
	const unsigned int& GetMinSize() const{return m_minSize;}
	const unsigned int& GetUnclosedOvernightSize() const{return m_unclosedOvernightSize;}
	const unsigned int& GetUnclosedOvernightShortSize() const{return m_overnightSize < 0 ? m_unclosedOvernightSize : uintZero;}
	const Price& GetOvernightAveragePrice() const{return m_overnightAveragePrice;}
	const Price& GetOvernightAverageCost() const{return m_overnightAverageCost;}

	const unsigned int& GetPositionEnterTime() const{return m_positionEnterTime;}
	const Price& GetAveragePrice() const{return m_averagePrice;}
	const unsigned int& GetCompactAveragePrice() const{return m_compactAveragePrice;}

	const Price& GetAverageCost() const{return m_averageCost;}
	const unsigned int& GetCompactAverageCost() const{return m_compactAverageCost;}

	const unsigned int& GetLastExecPrice() const{return m_lastExecPrice;}
	const int& GetLastExecSize() const{return m_lastExecSize;}

	const Money& GetClosedPnlCost() const{return m_closedPnlCost;}
	const Money& GetOpenPnlLevel1Cost() const{return m_openPnlLevel1Cost;}

	const __int64& GetClosedPnlDollars() const{return GetClosedPnl().GetDollarsRef();}

	const Money& GetClosedPnl() const{return m_closedPnl;}
	const Money& GetOpenPnlLevel1() const{return m_openPnlLevel1;}
	const Money& GetOpenPnlPrint() const{return m_openPnlPrint;}
	const Money& GetOpenPnlTClose() const{return m_openPnlTClose;}
	const Money& GetOpenPnlNbboPrint() const{return m_openPnlNbboPrint;}
	const Money& GetOpenPnlNbboPrintHi() const{return m_openPnlNbboPrintHi;}
	const Money& GetOpenPnlNbboPrintLo() const{return m_openPnlNbboPrintLo;}
	const Money& GetMarkedPnlNbboPrint() const{return m_markedPnlNbboPrint;}
	const Money& GetMarkedPnlNbboPrintHi() const{return m_markedPnlNbboPrintHi;}
	const Money& GetMarkedPnlNbboPrintLo() const{return m_markedPnlNbboPrintLo;}
	const SignedPrice& GetGpsLevel1() const{return m_gpsLevel1;}
	const SignedPrice& GetGpsPrint() const{return m_gpsPrint;}
	const SignedPrice& GetGpsPrintHi() const{return m_gpsPrintHi;}
	const SignedPrice& GetGpsPrintLo() const{return m_gpsPrintLo;}

	const Money& GetInvestment() const{return m_investment;}
	const Money& GetHardBpUsed() const{return m_hardBpUsed;}//can be different from m_investment if a retail account has overnight position.
	
	const Money& GetInvestmentCost() const{return m_investmentCost;}

	const Money& GetPendingBuyInvestment() const{return m_pendingBuyInvestment;}
	const Money& GetPendingSellAndShortInvestment() const{return m_pendingSellAndShortInvestment;}

	const Money& GetPendingBuyNightInvestment() const{return m_pendingBuyNightInvestment;}//all buy pending investment except in OPG orders
	const Money& GetPendingSellAndShortNightInvestment() const{return m_pendingSellAndShortNightInvestment;}//all sell and short pending investment except in OPG orders

	const unsigned int& GetPendingBuyShares() const{return m_pendingBuyShares;}
	const unsigned int& GetPendingSellAndShortShares() const{return m_pendingSellAndShortShares;}
	const unsigned int& GetPendingSellShares() const{return m_pendingSellShares;}

	const unsigned int& GetPendingBuyNightShares() const{return m_pendingBuyNightShares;}//all buy pending shares except in OPG orders
	const unsigned int& GetPendingSellAndShortNightShares() const{return m_pendingSellAndShortNightShares;}//all sell and short pending shares except in OPG orders

	const unsigned int& GetPendingBuyOnOpenShares() const{return m_pendingBuyOnOpenShares;}
	const unsigned int& GetPendingBuyOnCloseShares() const{return m_pendingBuyOnCloseShares;}

	const unsigned int& GetPendingSellOnOpenShares() const{return m_pendingSellOnOpenShares;}
	const unsigned int& GetPendingSellOnCloseShares() const{return m_pendingSellOnCloseShares;}

	const unsigned int& GetPendingBuyPassiveShares() const{return m_pendingBuyPassiveShares;}
	const unsigned int& GetPendingBuyNonPassiveShares() const{return m_pendingBuyNonPassiveShares;}

#ifdef FIRM_VALUES
	virtual const int& GetFirmSize() const{return intZero;}
	virtual const unsigned char& GetUntradeableLevel() const{return ucharZero;}//m_untradeableLevel;}//For Supervisor only. 0 - tradable; 1 - pending; 2 - untradeable.
	virtual const bool& isUntradeable() const{return boolFalse;}
#endif

	static const bool& GetFalseRef(){return boolFalse;}

	const unsigned int& GetPendingBuyRtcPassiveShares() const{return m_pendingBuyRtcPassiveShares;}
	const unsigned int& GetPendingBuyRtcNonPassiveShares() const{return m_pendingBuyRtcNonPassiveShares;}

	const unsigned int& GetBuySharesBeingCanceled() const{return m_buySharesBeingCanceled;}
	const unsigned int& GetSellAndShortSharesBeingCanceled() const{return m_sellAndShortSharesBeingCanceled;}
	const unsigned int& GetSellSharesBeingCanceled() const{return m_sellSharesBeingCanceled;}

	const unsigned int& GetBuyPassiveSharesBeingCanceled() const{return m_buyPassiveSharesBeingCanceled;}
	const unsigned int& GetBuyNonPassiveSharesBeingCanceled() const{return m_buyNonPassiveSharesBeingCanceled;}

	const unsigned int& GetSellPassiveSharesBeingCanceled() const{return m_sellPassiveSharesBeingCanceled;}
	const unsigned int& GetSellNonPassiveSharesBeingCanceled() const{return m_sellNonPassiveSharesBeingCanceled;}

	const unsigned int& GetShortPassiveSharesBeingCanceled() const{return m_shortPassiveSharesBeingCanceled;}
	const unsigned int& GetShortNonPassiveSharesBeingCanceled() const{return m_shortNonPassiveSharesBeingCanceled;}

	const unsigned int& GetBuyRtcPassiveSharesBeingCanceled() const{return m_buyRtcPassiveSharesBeingCanceled;}
	const unsigned int& GetBuyRtcNonPassiveSharesBeingCanceled() const{return m_buyRtcNonPassiveSharesBeingCanceled;}
//	unsigned int GetPendingSellAndShortSharesWithoutBeingCanceled() const;

	const Money& GetPendingBuyBorrowInvestment() const{return m_pendingBuyBorrowInvestment;}
	const Money& GetBpBorrowUsed() const{return m_bpBorrowUsed;}
	const unsigned int& GetPendingBuyBorrowShares() const{return m_pendingBuyBorrowShares;}
	const unsigned int& GetPendingSellBorrowShares() const{return m_pendingSellBorrowShares;}
	const unsigned int& GetBorrowSize() const{return m_borrowSize;}
#ifdef SEND_LOCATE_INFO
	const unsigned int& GetNewBorrowSize() const{return m_newBorrowSize;}//for sending it to the executor with the Locate Contract Id
#endif
	const Money& GetBorrowInvestment() const{return m_borrowInvestment;}
	const Price& GetBorrowAveragePrice() const{return m_borrowAveragePrice;}

	const unsigned int& GetPotentialLongSize() const{return m_potentialLongSize;}
	const unsigned int& GetPotentialShortSize() const{return m_potentialShortSize;}
	const unsigned int& GetPotentialSize() const{return m_potentialSize;}//max of m_potentialLongSize and m_potentialShortSize

	const unsigned int& GetPotentialLongNightSize() const{return m_potentialLongNightSize;}
	const unsigned int& GetPotentialShortNightSize() const{return m_potentialShortNightSize;}
	const unsigned int& GetPotentialNightSize() const{return m_potentialNightSize;}//max of m_potentialLongNightSize and m_potentialShortNightSize i.e. potential size without the OPG pending orders

	const Money& GetPotentialLongValue() const{return m_potentialLongValue;}
	const Money& GetPotentialShortValue() const{return m_potentialShortValue;}
	const Money& GetBpUsed() const{return m_bpUsed;}//max of m_potentialLongValue and m_potentialShortValue

	const Money& GetPotentialLongNightValue() const{return m_potentialLongNightValue;}
	const Money& GetPotentialShortNightValue() const{return m_potentialShortNightValue;}
	const Money& GetNightBpUsed() const{return m_nightBpUsed;}//max of m_potentialLongNightValue and m_potentialShortNightValue i.e. potential value without the OPG pending orders

	const unsigned int& GetSharesTraded() const{return m_sharesTraded;}
	const unsigned int& GetSharesAdded() const{return m_sharesAdded;}
	const unsigned int& GetSharesRemoved() const{return m_sharesRemoved;}
	const Money& GetTicketAverage() const{return m_ticketAverage;}
	const Money& GetMarkedTicketAverage() const{return m_markedTicketAverage;}
	const Money& GetMarkedTicketAverageHi() const{return m_markedTicketAverageHi;}
	const Money& GetMarkedTicketAverageLo() const{return m_markedTicketAverageLo;}
	const Money& GetClosedPnlNet() const{return m_closedPnlNet;}
	const Money& GetOpenCommissionFee() const{return m_openCommissionFee;}
	virtual void UpdateClosedPnlNet(){}

	const bool& isRestricted() const{return m_restricted;}
	const bool& isRestrictedInitialized() const{return m_restrictedInitialized;}


	virtual unsigned int GetOrdersPendingCount() const{return 0;}
	virtual unsigned int GetPendingOrdersLong() const{return 0;}
	virtual unsigned int GetPendingOrdersSell() const{return 0;}
	virtual unsigned int GetPendingOrdersShort() const{return 0;}
	unsigned int GetPendingOrdersSellAndShort() const
	{
		return GetPendingOrdersSell() + GetPendingOrdersShort();
	}
	virtual unsigned int GetOrdersStuckCount() const{return 0;}
	virtual unsigned int GetOrdersCancelRejectedCount() const{return 0;}
	virtual unsigned int GetOrdersCancelBlockedCount() const{return 0;}
	virtual unsigned int GetOrdersWithCancelProblemCount() const{return 0;}
	virtual const char* GetLocateContractIdAsString() const{return "";}
	virtual const char* GetLocateInfoAsString() const{return "";}

	bool isActive() const{return m_size || GetOrdersPendingCount();}

	virtual const char* GetAccountId() const{return "";}
	virtual const char* GetAccountUserName() const{return "";}
	virtual const char& GetPhantom() const{return charZero;}//+1 - long, -1 - short, 0 - flat
	virtual const unsigned char& GetAbsPhantom() const{return ucharZero;}//1 - has phantom, 0 - no phantom
	virtual const int& GetSizeOrPhantom() const{return m_size;}
	virtual const unsigned char& isHTB() const{return ucharZero;}
	virtual const bool& isHtbInitialized() const{return boolFalse;}
	virtual const unsigned int& GetCompactBorrowDiscountedPrice() const{return uintZero;}
	virtual const unsigned int& GetBorrowAvailableSize() const{return uintZero;}

	virtual const unsigned int& GetAccountCount() const{return uintOne;}

#ifndef TAKION_NO_OPTIONS
	virtual const unsigned int& GetCallSharesSoldPotential() const{return uintZero;}
	virtual const unsigned int& GetPutSharesSoldPotential() const{return uintZero;}
	const unsigned int& GetOptionContractsTraded() const{return m_optionContractsTraded;}
#endif

	virtual void Reset();

protected:
	PositionDataBase(const char* symbol, SecurityType securityType);
	SecurityType m_securityType;

	bool m_restricted;
	bool m_restrictedInitialized;

	int m_overnightSize;
	unsigned int m_overnightAbsSize;
	unsigned int m_minSize;
	unsigned int m_unclosedOvernightSize;
//	unsigned int m_unclosedOvernightShortSize;
	Price m_overnightAveragePrice;
	Price m_overnightAverageCost;

	unsigned int m_absSize;
	unsigned int m_absShareSize;//Same as m_absSize for stocks; for options = m_absSize * GetContractSize()

	unsigned int m_positionEnterTime;

	unsigned int m_compactAveragePrice;
	Price m_averagePrice;

	unsigned int m_compactAverageCost;
	Price m_averageCost;
	Money m_closedPnlCost;
	Money m_openPnlLevel1Cost;

	Money m_potentialLongValue;
	Money m_potentialShortValue;
	Money m_bpUsed;

	Money m_potentialLongNightValue;
	Money m_potentialShortNightValue;
	Money m_nightBpUsed;

	unsigned int m_lastExecPrice;
	int m_lastExecSize;

	Money m_closedPnl;
	Money m_openPnlLevel1;
	Money m_openPnlPrint;
	Money m_openPnlTClose;
	Money m_openPnlNbboPrint;
	Money m_openPnlNbboPrintHi;
	Money m_openPnlNbboPrintLo;
	Money m_markedPnlNbboPrint;
	Money m_markedPnlNbboPrintHi;
	Money m_markedPnlNbboPrintLo;
	SignedPrice m_gpsLevel1;
	SignedPrice m_gpsPrint;
	SignedPrice m_gpsPrintHi;
	SignedPrice m_gpsPrintLo;

	Money m_investment;
	Money m_hardBpUsed;//can be different from m_investment if a retail account has overnight position.
	Money m_investmentCost;

	Money m_pendingBuyInvestment;
	Money m_pendingSellAndShortInvestment;

	Money m_pendingBuyNightInvestment;//all buy pending investment except in OPG orders
	Money m_pendingSellAndShortNightInvestment;//all sell and short pending investment except in OPG orders

	Money m_pendingBuyBorrowInvestment;
	Money m_bpBorrowUsed;
	Money m_borrowInvestment;
	Price m_borrowAveragePrice;

	unsigned int m_pendingBuyShares;
	unsigned int m_pendingSellAndShortShares;
	unsigned int m_pendingSellShares;

	unsigned int m_pendingBuyNightShares;
	unsigned int m_pendingSellAndShortNightShares;

	unsigned int m_pendingBuyOnOpenShares;
	unsigned int m_pendingBuyOnCloseShares;

	unsigned int m_pendingSellOnOpenShares;
	unsigned int m_pendingSellOnCloseShares;

	unsigned int m_pendingBuyPassiveShares;
	unsigned int m_pendingBuyNonPassiveShares;

	unsigned int m_pendingBuyRtcPassiveShares;
	unsigned int m_pendingBuyRtcNonPassiveShares;

	unsigned int m_buySharesBeingCanceled;
	unsigned int m_sellAndShortSharesBeingCanceled;
	unsigned int m_sellSharesBeingCanceled;

	unsigned int m_buyPassiveSharesBeingCanceled;
	unsigned int m_buyNonPassiveSharesBeingCanceled;

	unsigned int m_sellPassiveSharesBeingCanceled;
	unsigned int m_sellNonPassiveSharesBeingCanceled;

	unsigned int m_shortPassiveSharesBeingCanceled;
	unsigned int m_shortNonPassiveSharesBeingCanceled;

	unsigned int m_buyRtcPassiveSharesBeingCanceled;
	unsigned int m_buyRtcNonPassiveSharesBeingCanceled;

	unsigned int m_potentialLongSize;
	unsigned int m_potentialShortSize;
	unsigned int m_potentialSize;

	unsigned int m_potentialLongNightSize;
	unsigned int m_potentialShortNightSize;
	unsigned int m_potentialNightSize;

	unsigned int m_pendingBuyBorrowShares;
	unsigned int m_pendingSellBorrowShares;
	unsigned int m_borrowSize;
#ifdef SEND_LOCATE_INFO
	unsigned int m_newBorrowSize;
#endif
#ifndef TAKION_NO_OPTIONS
	unsigned int m_optionContractsTraded;
#endif
	unsigned int m_sharesTraded;
	unsigned int m_sharesAdded;
	unsigned int m_sharesRemoved;
	Money m_ticketAverage;
	Money m_markedTicketAverage;
	Money m_markedTicketAverageHi;
	Money m_markedTicketAverageLo;
	Money m_openCommissionFee;
	Money m_closedPnlNet;
};

class TU_API PositionData : public PositionDataBase
{
public:
	virtual ~PositionData();

#ifndef TAKION_NO_OPTIONS
	const OptionSymbolBlock* GetOptionSymbolBlock() const{return m_optionSymbolBlock;}
	const unsigned __int64& GetOptionBlock() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetOptionBlock() : uint64Zero;}
	const unsigned __int64& GetUnderlierNumericSymbol() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetSymbolNum() : m_numericSymbol;}
	bool isCall() const{return m_optionSymbolBlock && m_optionSymbolBlock->isCall();}
	unsigned char GetSuffix() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetSuffix() : ucharZero;}
	unsigned char GetCallPutFlags() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetCallPutFlags() : ucharZero;}
	const unsigned char& GetOptionFlags() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetFlags() : ucharZero;}
	const unsigned int& GetStrikePrice() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetStrikePrice() : uintZero;}
	unsigned int GetExpirationDate() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationDate() : 0;}
	const unsigned char& GetExpirationType() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationType() : ucharZero;}
	const unsigned int& GetExpirationDays() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationDays() : uintZero;}
	const char& GetExpirationTypeChar() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationTypeChar() : space;}
	void GetOptionBlockAsString(std::string& optionSymbol, bool suffixSeparate) const{if(m_optionSymbolBlock)m_optionSymbolBlock->GetOptionBlockAsString(optionSymbol, suffixSeparate);}
	void GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const
	{
		optionSymbol += suffixSeparate ? (const char*)&GetUnderlierNumericSymbol() : (const char*)&m_numericSymbol;
		if(m_optionSymbolBlock)
		{
			optionSymbol += ' ';
			m_optionSymbolBlock->GetOptionBlockAsString(optionSymbol, suffixSeparate);
		}
	}
	const unsigned int& GetContractSize() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetContractSize() : uintOne;}
/*
	const Position* GetUnderlierPosition() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetUnderlierPosition() : NULL;}
	Position* GetUnderlierPosition(){return m_optionSymbolBlock ? m_optionSymbolBlock->GetUnderlierPosition() : NULL;}
*/
//	virtual const unsigned int& GetCallSharesSoldPotential() const{return uintZero;}
//	virtual const unsigned int& GetPutSharesSoldPotential() const{return uintZero;}
#endif
protected:
	PositionData(const char* symbol, SecurityType securityType
#ifndef TAKION_NO_OPTIONS
		,OptionSymbolBlock* optionSymbolBlock
#endif
/*
#ifdef FIRM_VALUES
		,FirmPosition* firmPosition
#endif
*/
		);
#ifndef TAKION_NO_OPTIONS
	OptionSymbolBlock* m_optionSymbolBlock;
	UnderlierInfo* m_underlierInfo;
#endif
};

class PositionGroup;

class TU_API PositionGroupObserver : public PositionDataBase, public Observer
{
public:
	PositionGroupObserver(const Position* position, PositionGroup* positionGroup);
	DECLARE_NED_NEW
	const Position* GetPosition() const{return m_position;}
	const PositionGroup* GetPositionGroup() const{return m_positionGroup;}
	const Money& GetOvernightMoney() const{return m_overnightMoney;}
	const Money& GetOvernightCost() const{return m_overnightCost;}
#ifndef TAKION_NO_OPTIONS
	virtual const unsigned int& GetCallSharesSoldPotential() const{return m_callSharesSoldPotential;}
	virtual const unsigned int& GetPutSharesSoldPotential() const{return m_putSharesSoldPotential;}
#endif
	virtual unsigned int GetOrdersPendingCount() const{return m_ordersPendingCount;}
	virtual unsigned int GetPendingOrdersLong() const{return m_ordersPendingLongCount;}
	virtual unsigned int GetPendingOrdersSell() const{return m_ordersPendingSellCount;}
	virtual unsigned int GetPendingOrdersShort() const{return m_ordersPendingShortCount;}
	virtual unsigned int GetOrdersStuckCount() const{return m_ordersStuckCount;}
	virtual unsigned int GetOrdersCancelRejectedCount() const{return m_ordersCancelRejectedCount;}
	virtual unsigned int GetOrdersCancelBlockedCount() const{return m_ordersCancelBlockedCount;}
	virtual unsigned int GetOrdersWithCancelProblemCount() const{return m_ordersWithCancelProblemCount;}
	virtual const unsigned int& GetAccountCount() const{return m_accountCount;}

	virtual void Reset();
protected:
	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL) override;//Notified in the main thread only
	void UpdatePosition();//PositionGroupObserver* positionGroupObserver);
	const Position* m_position;
	PositionGroup* m_positionGroup;
	Money m_overnightMoney;
	Money m_overnightCost;
#ifndef TAKION_NO_OPTIONS
	unsigned int m_callSharesSoldPotential;
	unsigned int m_putSharesSoldPotential;
#endif
	unsigned int m_ordersPendingCount;
	unsigned int m_ordersPendingLongCount;
	unsigned int m_ordersPendingSellCount;
	unsigned int m_ordersPendingShortCount;
	unsigned int m_ordersStuckCount;
	unsigned int m_ordersCancelRejectedCount;
	unsigned int m_ordersCancelBlockedCount;
	unsigned int m_ordersWithCancelProblemCount;
	unsigned int m_accountCount;
};

typedef CMap<const Position*, const Position* const&, PositionGroupObserver*, PositionGroupObserver*> PositionGroupObserverMap;

class TU_API PositionGroup : public PositionData
{
friend class PositionGroupObserver;
public:

	virtual ~PositionGroup(){DestroyPositionObservers();}

	DECLARE_NED_NEW
	const PositionGroupObserverMap& GetPositionGroupObserverMap() const{return m_positionGroupObserverMap;}

	PositionGroupObserver* FindPosition(const Position* position)//call only in main thread
	{
		PositionGroupObserverMap::CPair* found = m_positionGroupObserverMap.PLookup(position);
		return found ? found->value : NULL;
	}

	const PositionGroupObserver* FindPosition(const Position* position) const//call only in main thread
	{
		const PositionGroupObserverMap::CPair* found = m_positionGroupObserverMap.PLookup(position);
		return found ? found->value : NULL;
	}

	PositionGroupObserver* AddPosition(const Position* position);
	PositionGroupObserver* RemovePosition(const Position* position);
	void ClearPositions();

	virtual void Reset();
	bool isEmpty() const{return m_positionGroupObserverMap.IsEmpty() == TRUE;}

	virtual void NotifyPositionUpdated() const = 0;//{}

	const Money& GetOvernightMoney() const{return m_overnightMoney;}
	const Money& GetOvernightCost() const{return m_overnightCost;}
#ifndef TAKION_NO_OPTIONS
	virtual const unsigned int& GetCallSharesSoldPotential() const{return m_callSharesSoldPotential;}
	virtual const unsigned int& GetPutSharesSoldPotential() const{return m_putSharesSoldPotential;}
#endif
	virtual unsigned int GetOrdersPendingCount() const{return m_ordersPendingCount;}
	virtual unsigned int GetPendingOrdersLong() const{return m_ordersPendingLongCount;}
	virtual unsigned int GetPendingOrdersSell() const{return m_ordersPendingSellCount;}
	virtual unsigned int GetPendingOrdersShort() const{return m_ordersPendingShortCount;}
	virtual unsigned int GetOrdersStuckCount() const{return m_ordersStuckCount;}
	virtual unsigned int GetOrdersCancelRejectedCount() const{return m_ordersCancelRejectedCount;}
	virtual unsigned int GetOrdersCancelBlockedCount() const{return m_ordersCancelBlockedCount;}
	virtual unsigned int GetOrdersWithCancelProblemCount() const{return m_ordersWithCancelProblemCount;}
	virtual const unsigned int& GetAccountCount() const{return m_accountCount;}
protected:
	PositionGroup(const char* symbol, SecurityType securityType
#ifndef TAKION_NO_OPTIONS
		,OptionSymbolBlock* optionSymbolBlock
#endif
		):
		PositionData(symbol, securityType
#ifndef TAKION_NO_OPTIONS
			,optionSymbolBlock
#endif
			),
#ifndef TAKION_NO_OPTIONS
		m_callSharesSoldPotential(0),
		m_putSharesSoldPotential(0),
#endif
		m_ordersPendingCount(0),
		m_ordersPendingLongCount(0),
		m_ordersPendingSellCount(0),
		m_ordersPendingShortCount(0),
		m_ordersStuckCount(0),
		m_ordersCancelRejectedCount(0),
		m_ordersCancelBlockedCount(0),
		m_ordersWithCancelProblemCount(0),
		m_accountCount(0)
		{}
	void UpdateGps();
	void UpdateTicketAverage();

	void DestroyPositionObservers();
	PositionGroupObserverMap m_positionGroupObserverMap;

	Money m_overnightMoney;
	Money m_overnightCost;
#ifndef TAKION_NO_OPTIONS
	unsigned int m_callSharesSoldPotential;
	unsigned int m_putSharesSoldPotential;
#endif
	unsigned int m_ordersPendingCount;
	unsigned int m_ordersPendingLongCount;
	unsigned int m_ordersPendingSellCount;
	unsigned int m_ordersPendingShortCount;
	unsigned int m_ordersStuckCount;
	unsigned int m_ordersCancelRejectedCount;
	unsigned int m_ordersCancelBlockedCount;
	unsigned int m_ordersWithCancelProblemCount;

	unsigned int m_accountCount;
};

typedef CMap<unsigned __int64, const unsigned __int64&, PositionGroup*, PositionGroup*> PositionGroupMap;
#ifndef TAKION_NO_OPTIONS
typedef CMap<OptionSymbolBlockKey, const OptionSymbolBlockKey&, PositionGroup*, PositionGroup*> OptionPositionGroupMap;
#endif

class TU_API PositionGroupCollection
{
public:
	virtual ~PositionGroupCollection(){ClearAndDestroy();}
	const PositionGroupMap& GetStockPositionGroupMap() const{return m_stockPositionGroupMap;}
	PositionGroup* FindStockPosition(const unsigned __int64& symbol) const
	{
		const PositionGroupMap::CPair* found = m_stockPositionGroupMap.PLookup(symbol);
		return found ? found->value : NULL;
	}
	PositionGroup* RemoveStockPositionGroupIfEmpty(const unsigned __int64& symbol)
	{
		PositionGroup* pg = FindStockPosition(symbol);
		if(pg && pg->isEmpty())
		{
			m_stockPositionGroupMap.RemoveKey(symbol);
			return pg;
		}
		return NULL;
	}
	const PositionGroup* RemovePositionGroupIfEmpty(const PositionGroup* pg)
	{
		if(pg->isEmpty())
		{
#ifndef TAKION_NO_OPTIONS
			const OptionSymbolBlock* osb = pg->GetOptionSymbolBlock();//GetOptionBlock(
			if(osb)m_optionPositionGroupMap.RemoveKey(OptionSymbolBlockKey(pg->GetNumericSymbol(), osb->GetOptionBlock()));
			else
#endif
				m_stockPositionGroupMap.RemoveKey(pg->GetNumericSymbol());
			return pg;
		}
		return NULL;
	}
	PositionGroup* FindPosition(const PositionData* position) const;
	PositionGroupObserver* FindPositionGroupObserver(const Position* position) const;

#ifndef TAKION_NO_OPTIONS
	const OptionPositionGroupMap& GetOptionPositionGroupMap() const{return m_optionPositionGroupMap;}
	PositionGroup* FindOptionPosition(const OptionSymbolBlockKey& optionSymbolBlockKey) const
	{
		const OptionPositionGroupMap::CPair* found = m_optionPositionGroupMap.PLookup(optionSymbolBlockKey);
		return found ? found->value : NULL;
	}
	PositionGroup* FindPosition(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return optionBlock ? FindOptionPosition(OptionSymbolBlockKey(rootSymbol, optionBlock)) : FindStockPosition(rootSymbol);
	}
	const PositionGroup* RemoveOptionPositionGroupIfEmpty(const OptionSymbolBlockKey& optionSymbolBlockKey)
	{
		PositionGroup* pg = FindOptionPosition(optionSymbolBlockKey);
		if(pg && pg->isEmpty())
		{
			m_optionPositionGroupMap.RemoveKey(optionSymbolBlockKey);
			return pg;
		}
		return NULL;
	}
	const PositionGroup* RemovePositionGroupIfEmpty(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock)
	{
		return optionBlock ? RemoveOptionPositionGroupIfEmpty(OptionSymbolBlockKey(rootSymbol, optionBlock)) : RemoveStockPositionGroupIfEmpty(rootSymbol);
	}
#endif
	bool isEmpty() const{return m_stockPositionGroupMap.IsEmpty() == TRUE
#ifndef TAKION_NO_OPTIONS
		&& m_optionPositionGroupMap.IsEmpty() == TRUE
#endif
		;}
	PositionGroup* AddPosition(const Position* position, bool* newGroup);
	PositionGroupObserver* RemovePosition(const Position* position);
	bool ClearAndDestroy();

	virtual PositionGroup* CreatePositionGroup(const Position* position) = 0;

protected:
	PositionGroupCollection(unsigned int stockHashSize
#ifndef TAKION_NO_OPTIONS
		, unsigned int optionHashSize
#endif
		)
	{
		m_stockPositionGroupMap.InitHashTable(stockHashSize);
#ifndef TAKION_NO_OPTIONS
		m_optionPositionGroupMap.InitHashTable(optionHashSize);
#endif
	}

	PositionGroupMap m_stockPositionGroupMap;
#ifndef TAKION_NO_OPTIONS
	OptionPositionGroupMap m_optionPositionGroupMap;
#endif
};

class TU_API Position : public PositionData//public Observable, public TakionLock
{
public:
//	virtual ~Position();
	typedef std::hash_set<Order*> OrderSet;

	virtual Account* GetAccount() const{return m_account;}
	virtual Position* GetAccountPosition(){return this;}
	virtual const Position* GetAccountPosition() const{return this;}
	virtual const char* GetAccountId() const;
	virtual const char* GetAccountUserName() const;

	virtual unsigned int GetThreadId() const;//{return m_account->GetThreadId();}

	virtual const char& GetPhantom() const override{return m_phantom;}//+1 - long, -1 - short, 0 - flat
	virtual const unsigned char& GetAbsPhantom() const override{return m_absPhantom;}//1 - has phantom, 0 - no phantom

	virtual const int& GetSizeOrPhantom() const override{return m_sizeOrPhantom;}

	const Money& GetOpenPnlForLoss() const{return m_openPnlNbboPrint;}//m_openPnlPrint;}
	const __int64& GetOpenPnlForLossDollars() const{return GetOpenPnlForLoss().GetDollarsRef();}
	__int64 GetMarkedPnlForLossDollars() const{return GetOpenPnlForLossDollars() + GetClosedPnlDollars();}

#ifdef PENDING_SHARES_VALIDITY
	static void LogOrderShareValidityError(const Order* order, unsigned int quantiy, unsigned int pendingQuantity, const char* prefix) const;
//	void LogShareValidityError(unsigned int quantiy, unsigned int pendingQuantity, const char* prefix) const;
	bool ArePendingSharesValid(bool buy) const;
#endif
	static inline void DecrementNumber(unsigned int& number, const unsigned int& by, const Order* const& order, const char* const& prefix)
	{
		if(number >= by)
		{
			number -= by;
		}
		else
		{
#ifdef PENDING_SHARES_VALIDITY
LogOrderShareValidityError(order, number, by, prefix);
#endif
			number = 0;
		}
	}

#ifdef FIRM_VALUES
	virtual const int& GetFirmSize() const{return m_firmPosition ? m_firmPosition->GetSize() : intZero;}
	virtual const unsigned char& GetUntradeableLevel() const{return m_untradeableLevel;}//For Supervisor only. 0 - tradable; 1 - pending; 2 - untradeable.
	virtual const bool& isUntradeable() const{return m_firmPosition ? m_firmPosition->isUntradeable() : boolFalse;}

	const unsigned int& GetFirmPendingSellPassiveShares() const{return m_firmPosition ? m_firmPosition->GetPendingSellPassiveShares() : uintZero;}
	const unsigned int& GetFirmPendingSellNonPassiveShares() const{return m_firmPosition ? m_firmPosition->GetPendingSellNonPassiveShares() : uintZero;}
	const unsigned int& GetFirmAvailableSellPassiveShares() const{return m_firmPosition ? m_firmPosition->GetAvailableSellPassiveShares() : uintZero;}
	const unsigned int& GetFirmAvailableSellNonPassiveShares() const{return m_firmPosition ? m_firmPosition->GetAvailableSellNonPassiveShares() : uintZero;}
	const unsigned int& GetAvailableSellShares(bool passive) const{return m_firmPosition ? m_firmPosition->GetAvailableSellShares(passive) : uintZero;}
	void IncrementFirmSellShares(unsigned int shares, bool orderPassive){if(m_firmPosition)m_firmPosition->IncrementFirmSellShares(shares, orderPassive);}
	void DecrementFirmSellShares(unsigned int shares, bool orderPassive){if(m_firmPosition)m_firmPosition->DecrementFirmSellShares(shares, orderPassive);}
	const FirmPosition* GetFirmPosition() const{return m_firmPosition;}
	bool SubscribeFirmPosition();
	bool UnsubscribeFirmPosition();
	const bool& isFirmPositionSubscribed() const{return m_firmPositionSubscribed;}
	bool isFirmPositionLoaded() const{return !m_firmPosition || m_firmPosition->isLoaded();}
	void AddFirmPositionInThreadObserver(Observer* o) const{if(m_firmPosition)m_firmPosition->AddInThreadObserver(o);}
	void RemoveFirmPositionInThreadObserver(Observer* o) const{if(m_firmPosition)m_firmPosition->RemoveInThreadObserver(o);}
//	void RemoveFirmPositionInThreadObserverWithoutLocking(Observer* o) const{if(m_firmPosition)m_firmPosition->RemoveInThreadObserverWithoutLocking(o);}
#endif
//	bool HasPendingNonProblematicOrders() const{return GetPendingOrders() > m_ordersWithCancelProblem.GetCount();}
	bool HasPendingNonProblematicOrders() const{return GetOrdersPendingCount() > (unsigned int)m_ordersWithCancelProblem.GetCount();}

//	unsigned int GetPendingOrders() const{return GetPendingOrdersLong() + GetPendingOrdersSellAndShort();}
	virtual unsigned int GetPendingOrdersLong() const
	{
		return (unsigned int)m_orders[TU_ORDER_STATUS_UNACKNOWLEDGED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_BUY].GetCount()
			+ (unsigned int)m_orders[TU_ORDER_STATUS_PENDING * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_BUY].GetCount();
	}
	virtual unsigned int GetPendingOrdersSell() const
	{
		return (unsigned int)m_orders[TU_ORDER_STATUS_UNACKNOWLEDGED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SELL].GetCount()
			+ (unsigned int)m_orders[TU_ORDER_STATUS_PENDING * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SELL].GetCount();
	}
	virtual unsigned int GetPendingOrdersShort() const
	{
		return (unsigned int)m_orders[TU_ORDER_STATUS_UNACKNOWLEDGED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SHORT].GetCount()
			+ (unsigned int)m_orders[TU_ORDER_STATUS_PENDING * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SHORT].GetCount();
	}
/*
	virtual unsigned int GetPendingOrdersSellAndShort() const
	{
		return GetPendingOrdersSell() + GetPendingOrdersShort();
	}
*/
//	typedef std::map<unsigned int, Order*> OrderChronologicalMap;
	typedef std::set<Order*, greaterOrderPrice> OrderPriceBidSet;
	typedef std::set<Order*, lessOrderPrice> OrderPriceAskSet;

	typedef std::set<Order*, greaterStopAndLimitOrderPrice> AggrOrderPriceBidSet;
	typedef std::set<Order*, lessStopAndLimitOrderPrice> AggrOrderPriceAskSet;

	const OrderMap& GetOrdersUnacknowledged() const{return m_ordersUnacknowledged;}
	const OrderMap& GetOrdersAcknowledged() const{return m_ordersAcknowledged;}
	const OrderMap& GetOrdersRejected() const{return m_ordersRejected;}
	const OrderMap& GetOrdersAlgorithm() const{return m_ordersAlgorithm;}

	const OrderMap& GetOrdersPending() const{return m_ordersPending;}//Unacknowledged and Acknowledged
	virtual unsigned int GetOrdersPendingCount() const{return (unsigned int)m_ordersPending.GetCount();}

	const OrderMap& GetOrdersStuck() const{return m_ordersStuck;}
	const OrderMap& GetOrdersCancelRejected() const{return m_ordersCancelRejected;}
	const OrderMap& GetOrdersCancelBlocked() const{return m_ordersCancelBlocked;}
	const OrderMap& GetOrdersWithCancelProblem() const{return m_ordersWithCancelProblem;}

	virtual unsigned int GetOrdersStuckCount() const{return (unsigned int)m_ordersStuck.GetCount();}
	virtual unsigned int GetOrdersCancelRejectedCount() const{return (unsigned int)m_ordersCancelRejected.GetCount();}
	virtual unsigned int GetOrdersCancelBlockedCount() const{return (unsigned int)m_ordersCancelBlocked.GetCount();}
	virtual unsigned int GetOrdersWithCancelProblemCount() const{return (unsigned int)m_ordersWithCancelProblem.GetCount();}

	Order* FindOrderUnacknowledged(unsigned int clientId){OrderMap::CPair* found = m_ordersUnacknowledged.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderAcknowledged(unsigned int serverId){OrderMap::CPair* found = m_ordersAcknowledged.PLookup(serverId); return found ? found->value : NULL;}
	Order* FindOrderRejected(unsigned int clientId){OrderMap::CPair* found = m_ordersRejected.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderAlgorithm(unsigned int clientId){OrderMap::CPair* found = m_ordersAlgorithm.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderPending(unsigned int clientId){OrderMap::CPair* found = m_ordersPending.PLookup(clientId); return found ? found->value : NULL;}

	const OrderMap& GetOrders(OrderStatus orderStatus, OrderSide orderSide) const{return m_orders[orderStatus * TU_ORDER_SIDE_COUNT + orderSide];}
	OrderMap& GetOrders(OrderStatus orderStatus, OrderSide orderSide){return m_orders[orderStatus * TU_ORDER_SIDE_COUNT + orderSide];}
//	TakionIterator* CreateOrderIterator(OrderStatus orderStatus, OrderSide orderSide) const;
	TakionIterator* CreateOrderIterator(unsigned int orderStatusMask, unsigned int orderSideMask) const;
	void AddMaskToOrderIterator(TakionIterator* iterator, unsigned int orderStatusMask, unsigned int orderSideMask) const;

	const OrderChronologicalMap& GetChronologicalPendingOrders(OrderSide orderSide) const{return m_chronologicalPendingOrders[orderSide];}
	OrderChronologicalMap& GetChronologicalPendingOrders(OrderSide orderSide){return m_chronologicalPendingOrders[orderSide];}
	const OrderPriceBidSet& GetBuyPendingSortedOrders() const{return m_buyPendingSortedOrders;}
	OrderPriceBidSet& GetBuyPendingSortedOrders(){return m_buyPendingSortedOrders;}

	const OrderPriceAskSet& GetSellPendingSortedOrders() const{return m_sellPendingSortedOrders;}
	OrderPriceAskSet& GetSellPendingSortedOrders(){return m_sellPendingSortedOrders;}

	const AggrOrderPriceBidSet& GetBuyPassivePendingSortedOrders() const{return m_buyPassivePendingSortedOrders;}
	AggrOrderPriceBidSet& GetBuyPassivePendingSortedOrders(){return m_buyPassivePendingSortedOrders;}
	const AggrOrderPriceBidSet& GetBuyNonPassivePendingSortedOrders() const{return m_buyNonPassivePendingSortedOrders;}
	AggrOrderPriceBidSet& GetBuyNonPassivePendingSortedOrders(){return m_buyNonPassivePendingSortedOrders;}

	const AggrOrderPriceBidSet& GetBuyRtcPassivePendingSortedOrders() const{return m_buyRtcPassivePendingSortedOrders;}
	AggrOrderPriceBidSet& GetBuyRtcPassivePendingSortedOrders(){return m_buyRtcPassivePendingSortedOrders;}
	const AggrOrderPriceBidSet& GetBuyRtcNonPassivePendingSortedOrders() const{return m_buyRtcNonPassivePendingSortedOrders;}
	AggrOrderPriceBidSet& GetBuyRtcNonPassivePendingSortedOrders(){return m_buyRtcNonPassivePendingSortedOrders;}

	const AggrOrderPriceAskSet& GetSellPassivePendingSortedOrders() const{return m_sellPassivePendingSortedOrders;}
	AggrOrderPriceAskSet& GetSellPassivePendingSortedOrders(){return m_sellPassivePendingSortedOrders;}
	const AggrOrderPriceAskSet& GetSellNonPassivePendingSortedOrders() const{return m_sellNonPassivePendingSortedOrders;}
	AggrOrderPriceAskSet& GetSellNonPassivePendingSortedOrders(){return m_sellNonPassivePendingSortedOrders;}

	const AggrOrderPriceAskSet& GetShortPassivePendingSortedOrders() const{return m_shortPassivePendingSortedOrders;}
	AggrOrderPriceAskSet& GetShortPassivePendingSortedOrders(){return m_shortPassivePendingSortedOrders;}
	const AggrOrderPriceAskSet& GetShortNonPassivePendingSortedOrders() const{return m_shortNonPassivePendingSortedOrders;}
	AggrOrderPriceAskSet& GetShortNonPassivePendingSortedOrders(){return m_shortNonPassivePendingSortedOrders;}

	const OrderPriceAskSet& GetShortPendingSortedOrders() const{return m_shortPendingSortedOrders;}
	OrderPriceAskSet& GetShortPendingSortedOrders(){return m_shortPendingSortedOrders;}
	const OrderPriceAskSet& GetSellAndShortPendingSortedOrders() const{return m_sellAndShortPendingSortedOrders;}
	OrderPriceAskSet& GetSellAndShortPendingSortedOrders(){return m_sellAndShortPendingSortedOrders;}
	const OrderPriceBidSet& GetBuyOddLotOrders() const{return m_buyOddLotOrders;}
	OrderPriceBidSet& GetBuyOddLotOrders(){return m_buyOddLotOrders;}
	const OrderPriceAskSet& GetSellAndShortOddLotOrders() const{return m_sellAndShortOddLotOrders;}
	OrderPriceAskSet& GetSellAndShortOddLotOrders(){return m_sellAndShortOddLotOrders;}

//	const ExecutionMap& GetExecutionMap() const{return m_executionMap;}
	const ExecutionMap& GetExecutions(OrderSide orderSide) const{return m_executions[orderSide];}
	ExecutionMap& GetExecutions(OrderSide orderSide){return m_executions[orderSide];}
	TakionIterator* CreateExecutionIterator(unsigned int orderSideMask) const;
	void AddMaskToExecutionIterator(TakionIterator* iterator, unsigned int orderSideMask) const;

	const ExecutionChronologicalSet& GetChronologicalExecutions() const{return m_chronologicalExecutions;}
	ExecutionChronologicalSet& GetChronologicalExecutions(){return m_chronologicalExecutions;}
	const Execution* FindLastValidExecOnSide(bool buy) const;

	Execution* FindExecution(unsigned int id, OrderSide orderSide);

	unsigned int GetBuyExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_BUY].GetCount();}
	unsigned int GetSellExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_SELL].GetCount();}
	unsigned int GetShortExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_SHORT].GetCount();}

	typedef std::set<unsigned int> UIntSet;
//Safe to call from threads
	void CollectOrders(OrderSet& orderSet,
		bool forCancel,
		unsigned char sideMask,
		OrderCancelPick orderCancelPick,
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet) const;

	unsigned int CancelOrders(unsigned char sideMask,
		OrderCancelPick orderCancelPick,
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet);
	unsigned int ReplaceOrders(bool replaceNative,
		unsigned char sideMask,
		OrderCancelPick orderCancelPick,
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet,
		const SignedPrice& replacePriceOffset,
		bool replacePriceReverseForSell,
		int replaceSizeOffset,
		bool replaceSizeReverseForSell,
		const unsigned __int64& userId,
		unsigned char displaySizeMode,//0 - size fraction, 1 - round lot, 2 - no change
		unsigned int displaySize,
		unsigned int displaySizeFraction);
///////////////////////////
//Lock before calling: position->LockInquiryWait(); position->UnlockInquiry();
	unsigned int CancelOrdersByPrice(unsigned char sideMask,
		const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned char tifMask,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet);
	unsigned int CancelBuyOrdersByPrice(const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned char tifMask,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet);
	unsigned int CancelSellOrdersByPrice(const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned char tifMask,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet);
	unsigned int CancelShortOrdersByPrice(const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned char tifMask,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet);

	void GetOrdersByPrice(OrderSet& orderSet,
		unsigned char sideMask,
		const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned char tifMask,
		unsigned char visibleSizeMask,
		unsigned char oddLotMask,
		bool includeMidPointPeg,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet) const;
	unsigned int GetBuyOrdersByPrice(OrderSet& orderSet,
		const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned char tifMask,
		unsigned char visibleSizeMask,
		unsigned char oddLotMask,
		bool includeMidPointPeg,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet,
		unsigned int totalSize = 0xFFFFFFFF,
		bool washableOnly = false) const;
	unsigned int GetSellOrdersByPrice(OrderSet& orderSet,
		const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned char tifMask,
		unsigned char visibleSizeMask,
		unsigned char oddLotMask,
		bool includeMidPointPeg,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet,
		unsigned int totalSize = 0xFFFFFFFF,
		bool washableOnly = false) const;
	unsigned int GetShortOrdersByPrice(OrderSet& orderSet,
		const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned char tifMask,
		unsigned char visibleSizeMask,
		unsigned char oddLotMask,
		bool includeMidPointPeg,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet,
		unsigned int totalSize = 0xFFFFFFFF,
		bool washableOnly = false) const;
	unsigned int GetAllSideOrdersByPrice(OrderSet& orderSet,
		bool buy,
		const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned int totalSize) const;

	unsigned int GetFlippingBuyOrders(bool rtcOnly,
		OrderSet& orderSet,
		Order** orderToReplace,
		unsigned int& replaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		unsigned int orderQuantity,
		const Price& quotePrice,
		const Order* orderBeingReplaced) const;//if orderToReplace is not NULL it will try to find an Order that can be resized.
	unsigned int GetFlippingSellOrders(OrderSet& orderSet,
		Order** orderToReplace,
		Order** passiveSellOrderToReplace,
		unsigned int& replaceSize,
		unsigned int& passiveSellOrderReplaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		unsigned int orderQuantity,
		const Price& quotePrice,
		const Order* orderBeingReplaced) const;
	unsigned int GetFlippingOrders(bool buy,
		OrderSet& orderSet,
		Order** orderToReplace,
		Order** passiveSellOrderToReplace,
		unsigned int& replaceSize,
		unsigned int& passiveSellOrderReplaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		unsigned int orderQuantity,
		const Price& quotePrice,
		const Order* orderBeingReplaced) const;

	bool HasWashOrders(bool bids,
		const Price& price,
		Price& orderPrice,
		unsigned char tifMask,
		unsigned char visibleSizeMask,
		unsigned char oddLotMask,
		bool includeMidPointPeg,
		bool destinationExclude,
		const UIntSet& destinationSet) const;
/*
	const Security* GetASecurity() const{return m_security ? m_security : m_sortableSecurity;}//safe to call only from main thread
	const Security* GetSecurity() const{return m_security;}
	void SetSecurity(const Security* security){m_security = security;}
	const Security* GetSortableSecurity() const{return m_sortableSecurity;}//safe to call only from main thread
	void SetSortableSecurity(const Security* security){m_sortableSecurity = security;}

	void NotifySecurityObservers(const Message* message, const Message* info);
	void AddSecurityObserver(Observer* o);
	void RemoveSecurityObserver(Observer* o);
	bool isSecurityObservable(Observable* o) const{return o == &m_securityObservable;}
*/
	void RemoveCanceledOrRejectedOrder(Order* order);

	virtual unsigned int CancelOpeningOrders(){return 0;}
	unsigned char PanicClose(bool blockAggressiveOrders);//calls CancelOrders and account->SendPanicCloseOrder

	const unsigned int& GetClearingFirmOrdinal() const;
	const unsigned int& GetStockLoanFirmOrdinal() const;
	const Price& GetBorrowPriceMultiplier() const;

	const unsigned int& GetCompactBorrowPrice() const{return m_compactBorrowPrice;}
	virtual const unsigned int& GetCompactBorrowDiscountedPrice() const override{return m_compactBorrowDiscountedPrice;}
	virtual const unsigned int& GetBorrowAvailableSize() const override{return m_borrowAvailableSize;}
//	const bool& isHtb() const{return m_htb;}
	virtual const unsigned char& isHTB() const override{return m_htb;}
	const bool& isHtbInitialized() const override{return m_htbInitialized;}

	const unsigned char& GetAutoClose() const{return m_autoClose;}

	bool isCancelOrdersInitiated() const{return m_cancelOrdersInitiated;}
//	bool isClosePositionsInitiated() const{return m_closePositionsInitiated;}//use m_autoClose instead
	bool LockInquirySortedOrders() const{return m_lockSortedOrders.LockInquiry();}
	void LockInquiryWaitSortedOrders() const{m_lockSortedOrders.LockInquiryWait();}
	void UnlockInquirySortedOrders() const{m_lockSortedOrders.UnlockInquiry();}
/*
	void NotifyInThreadObservers(const Message* message, const Message* info = NULL);
	virtual void WritePositionUpdateMessageToMainThread(unsigned char execution){}
*/
	bool isLoser() const{return m_loser;}

	void CalculatePotentialPositionSize(char orderSide, unsigned int orderQuantity,
		unsigned int& pendingBuyShares,
		unsigned int& pendingSellShares,
		unsigned int& longSize,
		unsigned int& shortSize) const;
	unsigned int CalculateSizeToBorrow(char orderSide, unsigned int orderQuantity) const;
#ifdef LOG_UPDATE_STOCK
	unsigned __int64 FindStrayOrder(const Order* order) const;
#endif

#ifndef TAKION_NO_OPTIONS
/*
	const OptionSymbolBlock* GetOptionSymbolBlock() const{return m_optionSymbolBlock;}
	const unsigned __int64& GetOptionBlock() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetOptionBlock() : uint64Zero;}
	const unsigned __int64& GetUnderlierNumericSymbol() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetSymbolNum() : m_numericSymbol;}
	bool isCall() const{return m_optionSymbolBlock && m_optionSymbolBlock->isCall();}
	unsigned char GetSuffix() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetSuffix() : ucharZero;}
	unsigned char GetCallPutFlags() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetCallPutFlags() : ucharZero;}
	const unsigned char& GetOptionFlags() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetFlags() : ucharZero;}
	const unsigned int& GetStrikePrice() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetStrikePrice() : uintZero;}
	unsigned int GetExpirationDate() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationDate() : 0;}
	const unsigned char& GetExpirationType() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationType() : ucharZero;}
	const unsigned int& GetExpirationDays() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationDays() : uintZero;}
	const char& GetExpirationTypeChar() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationTypeChar() : space;}
	void GetOptionBlockAsString(std::string& optionSymbol, bool suffixSeparate) const{if(m_optionSymbolBlock)m_optionSymbolBlock->GetOptionBlockAsString(optionSymbol, suffixSeparate);}
	void GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const
	{
		optionSymbol += suffixSeparate ? (const char*)&GetUnderlierNumericSymbol() : (const char*)&m_numericSymbol;
		if(m_optionSymbolBlock)
		{
			optionSymbol += ' ';
			m_optionSymbolBlock->GetOptionBlockAsString(optionSymbol, suffixSeparate);
		}
	}
	const unsigned int& GetContractSize() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetContractSize() : uintOne;}
*/
	const Position* GetUnderlierPosition() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetUnderlierPosition() : NULL;}
	Position* GetUnderlierPosition(){return m_optionSymbolBlock ? m_optionSymbolBlock->GetUnderlierPosition() : NULL;}

	virtual const unsigned int& GetCallSharesSoldPotential() const{return m_underlierInfo ? m_underlierInfo->GetCallSharesSoldPotential() : uintZero;}
	virtual const unsigned int& GetPutSharesSoldPotential() const{return m_underlierInfo ? m_underlierInfo->GetPutSharesSoldPotential() : uintZero;}

#endif

#ifdef SEND_LOCATE_INFO
	virtual const char* GetLocateContractIdAsString() const{return m_locateContractId.GetString();}
	virtual const char* GetLocateInfoAsString() const{return m_locateInfo.GetString();}

	const LocateContractId& GetLocateContractId() const{return m_locateContractId;}
	const LocateContractId& GetLocateInfo() const{return m_locateInfo;}
#endif
protected:
	Position(const char* symbol, Account* account, SecurityType securityType
#ifndef TAKION_NO_OPTIONS
		,OptionSymbolBlock* optionSymbolBlock
#endif
#ifdef FIRM_VALUES
		,FirmPosition* firmPosition
#endif
		);

	Account* m_account;

	unsigned int m_compactBorrowPrice;
	unsigned int m_compactBorrowDiscountedPrice;
	unsigned int m_borrowAvailableSize;

	unsigned char m_discountFlag;
	unsigned char m_htb;
	bool m_htbInitialized;

	char m_phantom;//+1 - long, -1 - short, 0 - flat
	int m_sizeOrPhantom;
	unsigned char m_absPhantom;//1 - has phantom, 0 - no phantom

	unsigned char m_autoClose;//AutoCloseStatus; can be non zero for Supervisor trader Id only.
	bool m_cancelOrdersInitiated;
	bool m_loser;
//	bool m_closePositionsInitiated;//use m_autoClose instead

#ifdef FIRM_VALUES
	FirmPosition* m_firmPosition;
	bool m_firmPositionSubscribed;
	unsigned char m_untradeableLevel;//For Supervisor only. 0 - tradable; 1 - pending; 2 - untradeable.
#endif
#ifdef SEND_LOCATE_INFO
	LocateContractId m_locateContractId;
	LocateContractId m_locateInfo;
#endif
	OrderMap m_ordersAcknowledged;
	OrderMap m_ordersUnacknowledged;
	OrderMap m_ordersRejected;

	OrderMap m_ordersPending;

	OrderMap m_ordersStuck;
	OrderMap m_ordersCancelRejected;
	OrderMap m_ordersCancelBlocked;

	OrderMap m_ordersWithCancelProblem;

	OrderMap m_ordersAlgorithm;

	OrderMap m_orders[TU_ORDER_STATUS_COUNT * TU_ORDER_SIDE_COUNT];

	OrderChronologicalMap m_chronologicalPendingOrders[TU_ORDER_SIDE_COUNT];
	OrderPriceBidSet m_buyPendingSortedOrders;
	OrderPriceAskSet m_sellPendingSortedOrders;

	AggrOrderPriceBidSet m_buyPassivePendingSortedOrders;//All Buy passive orders
	AggrOrderPriceBidSet m_buyNonPassivePendingSortedOrders;//All Buy non passive orders

	AggrOrderPriceBidSet m_buyRtcPassivePendingSortedOrders;//Resize to close
	AggrOrderPriceBidSet m_buyRtcNonPassivePendingSortedOrders;//Resize to close

	AggrOrderPriceAskSet m_sellPassivePendingSortedOrders;//All sell orders are Resize to close
	AggrOrderPriceAskSet m_sellNonPassivePendingSortedOrders;//All sell orders are Resize to close

	AggrOrderPriceAskSet m_shortPassivePendingSortedOrders;//All Short passive orders
	AggrOrderPriceAskSet m_shortNonPassivePendingSortedOrders;//All Short non passive orders

	OrderPriceAskSet m_shortPendingSortedOrders;
	OrderPriceAskSet m_sellAndShortPendingSortedOrders;

	OrderPriceBidSet m_buyOddLotOrders;
	OrderPriceAskSet m_sellAndShortOddLotOrders;

	TakionLock m_lockSortedOrders;

//	ExecutionMap m_executionMap;

	ExecutionMap m_executions[TU_ORDER_SIDE_COUNT];
	ExecutionChronologicalSet m_chronologicalExecutions;
/*
#ifndef TAKION_NO_OPTIONS
	OptionSymbolBlock* m_optionSymbolBlock;
	UnderlierInfo* m_underlierInfo;
#endif
*/
};

class TU_API Firm
{
public:
	virtual ~Firm(){}
	const unsigned int& GetOrdinal() const{return m_ordinal;}
	void SetOrdinal(unsigned int ordinal){m_ordinal = ordinal;}
	const char* GetName() const{return m_name;}
	const unsigned int& GetNumericName() const{return m_numericName;}
	const bool& isLoaded() const{return m_loaded;}
	void SetLoaded(bool loaded) const{m_loaded = loaded;}
protected:
	Firm(const char* name, unsigned int ordinal):m_numericName(*(unsigned int*)name),m_ordinal(ordinal),m_loaded(false)
	{
		*(unsigned int*)m_name = m_numericName;
		m_name[sizeof(unsigned int)] = '\0';
	}
	unsigned int m_numericName;
	unsigned int m_ordinal;
//	unsigned int m_index;
	char m_name[sizeof(unsigned int) + 1];
	mutable bool m_loaded;
};

enum PositionUpdateFlags : unsigned char
{
	PUE_NONE = 0,
	PUE_EXECUTION = 1,
	PUE_PENDING_ORDERS_COUNT = 2,
	PUE_LONG_POSITION_CLOSED_OR_FLIPPED = 4,
	PUE_SHORT_POSITION_CLOSED_OR_FLIPPED = 8,
	PUE_HISTORICAL = 16,
};

enum PositionStatus : unsigned char
{
	TU_POSITION_STATUS_FLAT,
	TU_POSITION_STATUS_LONG,
	TU_POSITION_STATUS_SHORT,

	TU_POSITION_STATUS_COUNT,
};

#ifdef FIRM_VALUES

class AccountAggregatorId : public AccountId
{
public:
	AccountAggregatorId(const char* firmId, const char* clearingAccountName):AccountId(clearingAccountName),m_firmId(U_StringToUInt(firmId)){}
	AccountAggregatorId(const unsigned int& firmId = 0, const unsigned __int64& first = 0, const unsigned __int64& second = 0):AccountId(first, second), m_firmId(firmId){}
	AccountAggregatorId(const unsigned int& firmId, const AccountId& accountId):AccountId(accountId), m_firmId(firmId){}
	AccountAggregatorId(const char* str){fromString(str);}
	const unsigned int& GetFirmId() const{return m_firmId;}
	void SetFirmId(const unsigned int& firmId){m_firmId = firmId;}
	bool operator<(const AccountAggregatorId& other) const{return m_firmId < other.m_firmId || m_firmId == other.m_firmId && AccountId::operator<(other);}
	bool operator==(const AccountAggregatorId& other) const{return m_firmId == other.m_firmId && AccountId::operator==(other);}
	bool operator!=(const AccountAggregatorId& other) const{return m_firmId != other.m_firmId || AccountId::operator!=(other);}
	void SetAggregatorId(const unsigned int& firmId, const unsigned __int64& first, const unsigned __int64& second)
	{
		m_firmId = firmId;
		SetAccountId(first, second);
	}
	void Nullify(){AccountId::Nullify(); m_firmId = 0;}
	void toString(std::string& str) const
	{
		str += GetId();
		str += ' ';
		U_AppendNumberAsString(str, m_firmId);
	}
	void fromString(const char* str)
	{
		const char* p = strrchr(str, ' ');
		if(p)
		{
			m_firmId = U_StringToUInt(p + 1);
			SetAccountId(str, (unsigned int)(p - str));
		}
		else
		{
			m_firmId = 0;
			SetAccountId(str);
		}
	}
protected:
	unsigned int m_firmId;
};

class TU_API AccountAggregator : public Observable, public Firm, public TakionLockMultithread//TakionLock
{
public:
	virtual ~AccountAggregator(){ClearAndDestroyFirmPositions();}
	void ClearAndDestroyFirmPositions();
	typedef CMap<unsigned __int64, const unsigned __int64&, FirmPosition*, FirmPosition*> FirmPositionMap;
	typedef CMap<unsigned __int64, const unsigned __int64&, unsigned int, unsigned int> UntradeableSymbolMap;
//	typedef std::hash_map<unsigned __int64, volatile LONG> UntradeableSymbolMap;

	void GetUntradeableSymbolSet(std::hash_set<unsigned __int64>& untradeableSymbols) const;
	unsigned int FindUntradeableSymbol(const unsigned __int64& symbol) const;//return 1 if untradeable symbol exists, otherwise 0
	unsigned int FindSupervisorUntradeableSymbol(const unsigned __int64& symbol) const;

//	const FirmPositionMap& GetFirmPositionMap() const{return  m_firmPositionMap;}
	FirmPosition* FindFirmPosition(const unsigned __int64& symbol) const;
	FirmPosition* ObtainFirmPosition(const unsigned __int64& symbol, bool* newPosition = NULL);
	const AccountId& GetClearingAccountId() const{return m_clearingAccountName;}
	const unsigned __int64& GetClearingAccountNamePart1() const{return m_clearingAccountName.GetFirst();}
	const unsigned __int64& GetClearingAccountNamePart2() const{return m_clearingAccountName.GetSecond();}

	const char* GetClearingAccountName() const{return m_clearingAccountName.GetId();}
	const AccountAggregatorId& GetAccountAggregatorId() const{return m_accountAggregatorId;}
	const unsigned short GetRecoveryErrorCode() const{return m_recoveryErrorCode;}
	bool isHistoryLoaded() const{return !m_recoveryErrorCode;}
	void ResetRecoveryErrorCode(){m_recoveryErrorCode = 0xFFFF;}//history is not loaded

	virtual void WriteMessageToAccountAggregatorThread(const Message* message){}
	virtual bool WriteSupervisorUntradeableRequestToMainThread(const unsigned __int64& symbol, bool untradeable){return false;}
	virtual bool WriteSupervisorCheckUntradeableMessageToMainThread(const unsigned __int64& symbol, bool untradeable){return false;}

	virtual unsigned int GetThreadId() const{return 0;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}

	const FirmPositionMap& GetFirmPositions() const{return m_firmPositionMap;}
	TakionIterator* CreateFirmPositionIterator() const;

	const UntradeableSymbolMap& GetSupervisorUntradeablSymbols() const{return m_supervisorUntradeableSymbolMap;}
	TakionIterator* CreateSupervisorUntradeablSymbolIterator() const;

	void LockUntradeableSymbolInquiryWait() const{m_untradeableSymbolLock.LockInquiryWait();}
	bool LockUntradeableSymbolInquiry() const{return m_untradeableSymbolLock.LockInquiry();}
	void UnlockUntradeableSymbolInquiry() const{m_untradeableSymbolLock.UnlockInquiry();}
	bool LockUntradeableSymbolModification() const{return m_untradeableSymbolLock.LockModification();}
	void UnlockUntradeableSymbolModification() const{m_untradeableSymbolLock.UnlockModification();}

	const UntradeableSymbolMap& GetUntradeablSymbols() const{return m_untradeableSymbolMap;}
	TakionIterator* CreateUntradeablSymbolIterator() const;
/*
	const FirmPositionMap& GetSideFirmPositions(PositionStatus positionStatus) const{return m_firmSidePositionMap[positionStatus];}
	TakionIterator* CreateFirmPositionIterator(unsigned int positionStatusMask) const;
	void AddMaskToFirmPositionIterator(TakionIterator* iterator, unsigned int positionStatusMask) const;
	
	unsigned int GetFirmPositionCountLong() const{return (unsigned int)GetSideFirmPositions(TU_POSITION_STATUS_LONG).GetCount();}
	unsigned int GetFirmPositionCountShort() const{return (unsigned int)GetSideFirmPositions(TU_POSITION_STATUS_SHORT).GetCount();}
	unsigned int GetFirmPositionCount() const{return GetFirmPositionCountLong() + GetFirmPositionCountShort();}
*/
	bool LockFirmPositions() const{return m_firmPositionCriticalSection.Lock() == TRUE;}
	void UnlockFirmPositions() const{m_firmPositionCriticalSection.Unlock();}

	bool isUntradeableLoaded() const{return m_untradeableLoaded;}
protected:
	AccountAggregator(const char* firmName, const char* clearingAccountName):
		Firm(firmName, nextOrdinal++),
		m_clearingAccountName(clearingAccountName),
		m_accountAggregatorId(m_numericName, m_clearingAccountName),
		m_recoveryErrorCode(0xFFFF),
		m_untradeableLoaded(false)
//		m_untradeableSymbolMapEnd(m_untradeableSymbolMap.end())
	{
		m_firmPositionMap.InitHashTable(9001);
	}
	virtual FirmPosition* CreateFirmPosition(const char* symbol) const = 0;
	AccountId m_clearingAccountName;
	AccountAggregatorId m_accountAggregatorId;
	FirmPositionMap m_firmPositionMap;
//	FirmPositionMap m_firmSidePositionMap[TU_POSITION_STATUS_COUNT];
	mutable CCriticalSection m_firmPositionCriticalSection;
	unsigned short m_recoveryErrorCode;
	bool m_untradeableLoaded;

	UntradeableSymbolMap m_supervisorUntradeableSymbolMap;
	
	UntradeableSymbolMap m_untradeableSymbolMap;
	TakionLock m_untradeableSymbolLock;
//	UntradeableSymbolMap::const_iterator m_untradeableSymbolMapEnd;
private:
	static unsigned int nextOrdinal;
};
#endif

class TU_API ClearingFirm : public Firm
{
public:
	ClearingFirm(const char* name):
		Firm(name, nextOrdinal++)
	{
		m_stockMap.InitHashTable(9001);
	}
//02/19/2014
//	typedef CMap<unsigned __int64, unsigned __int64, bool, bool> StockMap;
	typedef CMap<unsigned __int64, const unsigned __int64&, unsigned char, unsigned char> StockMap;
	const StockMap& GetStockMap() const{return  m_stockMap;}
//	bool isHtb(unsigned __int64 symbol) const{const StockMap::CPair* found = m_stockMap.PLookup(symbol); return !found || !found->value;}
	const unsigned char& isHTB(const unsigned __int64& symbol) const{const StockMap::CPair* found = m_stockMap.PLookup(symbol); return found ? found->value : HTB::regularHtb;}
//	bool isEtb(const unsigned __int64& symbol) const{const StockMap::CPair* found = m_stockMap.PLookup(symbol); return found && !found->value;}
	bool isETB(const unsigned __int64& symbol) const{const StockMap::CPair* found = m_stockMap.PLookup(symbol); return found && !found->value;}
/*
	void AddEtb(unsigned __int64 symbol, bool etb = true)
	{
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		if(found)found->value = etb;
		else m_stockMap.SetAt(symbol, etb);
	}
	void SetEtb(unsigned __int64 symbol, bool etb)
	{
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		if(found)found->value = etb;
		else if(etb)m_stockMap.SetAt(symbol, etb);
	}
	void ClearEtbs()
	{
		m_stockMap.RemoveAll();
	}
*/
	void AddETB(const unsigned __int64& symbol, const unsigned char& htb = '\0')
	{
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		if(found)found->value = htb;
		else m_stockMap.SetAt(symbol, htb);
	}
	void SetETB(const unsigned __int64& symbol, const unsigned char& htb)
	{
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		if(found)found->value = htb;
		else if(htb != HTB::regularHtb)m_stockMap.SetAt(symbol, htb);
	}
	void ClearETBs()
	{
		for(StockMap::CPair* p = m_stockMap.PGetFirstAssoc(); p; p = m_stockMap.PGetNextAssoc(p))
		{
			if(!p->value)p->value = HTB::regularHtb;
		}
/*
		bool etb;
		unsigned __int64 symbol;
		for(StockMap::CPair* p = m_stockMap.PGetFirstAssoc(); p; )
		{
			symbol = p->key;
			etb = !p->value;
			p = m_stockMap.PGetNextAssoc(p);
			if(etb)
			{
				m_stockMap.RemoveKey(symbol);
			}
		}
*/
	}
protected:
	StockMap m_stockMap;
private:
	static unsigned int nextOrdinal;
};

class TU_API StockLoanFirm : public Firm
{
public:
	StockLoanFirm(const char* name):
		Firm(name, nextOrdinal++)
	{
	}
	typedef CMap<unsigned __int64, unsigned __int64, StockLoanInfo, StockLoanInfo&> StockMap;
	const StockMap& GetStockMap() const{return  m_stockMap;}
	const StockLoanInfo* GetStockLoanInfo(unsigned __int64 symbol) const{const StockMap::CPair* found = m_stockMap.PLookup(symbol); return found ? &found->value : NULL;}
	void AddStockLoanInfo(unsigned __int64 symbol, const StockLoanInfo& info)
	{
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		if(found)
		{
			found->value = info;
		}
		else
		{
			m_stockMap.SetAt(symbol, (StockLoanInfo&)info);
		}
	}
	void SetStockLoanInfo(unsigned __int64 symbol, const StockLoanInfo& info)
	{
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		if(found)
		{
			found->value = info;
		}
		else
		{
			m_stockMap.SetAt(symbol, (StockLoanInfo&)info);
		}
	}
protected:
	StockMap m_stockMap;
private:
	static unsigned int nextOrdinal;
};

class TU_API ConstraintCollection
{
public:
	ConstraintCollection(const char* id, bool simulation);
	virtual ~ConstraintCollection(){}
//	const char* const& GetId() const{return m_id;}
	const char* GetId() const{return m_id;}
	bool isSimulation() const{return m_simulation;}
	virtual void SetSimulation(bool simulation);
	bool isCustomEqual(const ConstraintCollection& other) const;
	virtual void SetCustomEqual(const ConstraintCollection& other);

	virtual void SetCustomZero();

	Constraint<Money>& GetBuyingPowerConstraint(){return m_buyingPower;}
	const Constraint<Money>& GetBuyingPowerConstraint() const{return m_buyingPower;}
	const Money& GetBuyingPower() const{return m_buyingPower.GetCurrentValue();}

	Constraint<Money>& GetHardBuyingPowerConstraint(){return m_hardBuyingPower;}
	const Constraint<Money>& GetHardBuyingPowerConstraint() const{return m_hardBuyingPower;}
	const Money& GetHardBuyingPower() const{return m_hardBuyingPower.GetCurrentValue();}

	Constraint<Money>& GetDayMaxPosInvestmentConstraint(){return m_dayMaxPosInvestment;}
	const Constraint<Money>& GetDayMaxPosInvestmentConstraint() const{return m_dayMaxPosInvestment;}
	const Money& GetDayMaxPosInvestment() const{return m_dayMaxPosInvestment.GetCurrentValue();}

	Constraint<Money>& GetNightMaxPosInvestmentConstraint(){return m_nightMaxPosInvestment;}
	const Constraint<Money>& GetNightMaxPosInvestmentConstraint() const{return m_nightMaxPosInvestment;}
	const Money& GetNightMaxPosInvestment() const{return m_nightMaxPosInvestment.GetCurrentValue();}

	Constraint<Money>& GetDayMaxLongInvestmentConstraint(){return m_dayMaxLongInvestment;}
	const Constraint<Money>& GetDayMaxLongInvestmentConstraint() const{return m_dayMaxLongInvestment;}
	const Money& GetDayMaxLongInvestment() const{return m_dayMaxLongInvestment.GetCurrentValue();}

	Constraint<Money>& GetNightMaxLongInvestmentConstraint(){return m_nightMaxLongInvestment;}
	const Constraint<Money>& GetNightMaxLongInvestmentConstraint() const{return m_nightMaxLongInvestment;}
	const Money& GetNightMaxLongInvestment() const{return m_nightMaxLongInvestment.GetCurrentValue();}

	Constraint<Money>& GetDayMaxShortInvestmentConstraint(){return m_dayMaxShortInvestment;}
	const Constraint<Money>& GetDayMaxShortInvestmentConstraint() const{return m_dayMaxShortInvestment;}
	const Money& GetDayMaxShortInvestment() const{return m_dayMaxShortInvestment.GetCurrentValue();}

	Constraint<Money>& GetNightMaxShortInvestmentConstraint(){return m_nightMaxShortInvestment;}
	const Constraint<Money>& GetNightMaxShortInvestmentConstraint() const{return m_nightMaxShortInvestment;}
	const Money& GetNightMaxShortInvestment() const{return m_nightMaxShortInvestment.GetCurrentValue();}

	Constraint<Money>& GetNightMaxInvestmentConstraint(){return m_nightMaxInvestment;}
	const Constraint<Money>& GetNightMaxInvestmentConstraint() const{return m_nightMaxInvestment;}
	const Money& GetNightMaxInvestment() const{return m_nightMaxInvestment.GetCurrentValue();}

	Constraint<Money>& GetMaxLossConstraint(){return m_maxLoss;}
	const Constraint<Money>& GetMaxLossConstraint() const{return m_maxLoss;}
	const Money& GetMaxLoss() const{return m_maxLoss.GetCurrentValue();}

	Constraint<Money>& GetMaxLossSlackConstraint(){return m_maxLossSlack;}
	const Constraint<Money>& GetMaxLossSlackConstraint() const{return m_maxLossSlack;}
	const Money& GetMaxLossSlack() const{return m_maxLossSlack.GetCurrentValue();}

	Constraint<Money>& GetMaxLossCloseConstraint(){return m_maxLossClose;}
	const Constraint<Money>& GetMaxLossCloseConstraint() const{return m_maxLossClose;}
	const Money& GetMaxLossClose() const{return m_maxLossClose.GetCurrentValue();}

	const Money& GetMaxLoss90Percent() const{return m_maxLoss90Percent;}

	Constraint<Money>& GetMaxLossPerPositionConstraint(){return m_maxLossPerPosition;}
	const Constraint<Money>& GetMaxLossPerPositionConstraint() const{return m_maxLossPerPosition;}
	const Money& GetMaxLossPerPosition() const{return m_maxLossPerPosition.GetCurrentValue();}

	Constraint<Money>& GetMaxLossPerPositionSlackConstraint(){return m_maxLossPerPositionSlack;}
	const Constraint<Money>& GetMaxLossPerPositionSlackConstraint() const{return m_maxLossPerPositionSlack;}
	const Money& GetMaxLossPerPositionSlack() const{return m_maxLossPerPositionSlack.GetCurrentValue();}

	Constraint<Money>& GetMaxLossPerPositionCloseConstraint(){return m_maxLossPerPositionClose;}
	const Constraint<Money>& GetMaxLossPerPositionCloseConstraint() const{return m_maxLossPerPositionClose;}
	const Money& GetMaxLossPerPositionClose() const{return m_maxLossPerPositionClose.GetCurrentValue();}

	Constraint<Money>& GetMaxOpenLossPerPositionConstraint(){return m_maxOpenLossPerPosition;}
	const Constraint<Money>& GetMaxOpenLossPerPositionConstraint() const{return m_maxOpenLossPerPosition;}
	const Money& GetMaxOpenLossPerPosition() const{return m_maxOpenLossPerPosition.GetCurrentValue();}

	Constraint<Money>& GetMaxTradedMoneyConstraint(){return m_maxTradedMoney;}
	const Constraint<Money>& GetMaxTradedMoneyConstraint() const{return m_maxTradedMoney;}
	const Money& GetMaxTradedMoney() const{return m_maxTradedMoney.GetCurrentValue();}

	Constraint<Money>& GetMaxOrderValueConstraint(){return m_maxOrderValue;}
	const Constraint<Money>& GetMaxOrderValueConstraint() const{return m_maxOrderValue;}
	const Money& GetMaxOrderValue() const{return m_maxOrderValue.GetCurrentValue();}

	Constraint<Money>& GetCommissionPer1000SharesConstraint(){return m_commissionPer1000Shares;}
	const Constraint<Money>& GetCommissionPer1000SharesConstraint() const{return m_commissionPer1000Shares;}
	const Money& GetCommissionPer1000Shares() const{return m_commissionPer1000Shares.GetCheckedValue();}

	Constraint<Price>& GetMinShortPriceConstraint(){return m_minShortPrice;}
	const Constraint<Price>& GetMinShortPriceConstraint() const{return m_minShortPrice;}
	const Price& GetMinShortPrice() const{return m_minShortPrice.GetCurrentValue();}

	Constraint<unsigned int>& GetMaxSharesTotalConstraint(){return m_maxSharesTotal;}
	const Constraint<unsigned int>& GetMaxSharesTotalConstraint() const{return m_maxSharesTotal;}
	const unsigned int& GetMaxSharesTotal() const{return m_maxSharesTotal.GetCurrentValue();}

	Constraint<unsigned int>& GetMaxSharesTradedConstraint(){return m_maxSharesTraded;}
	const Constraint<unsigned int>& GetMaxSharesTradedConstraint() const{return m_maxSharesTraded;}
	const unsigned int& GetMaxSharesTraded() const{return m_maxSharesTraded.GetCurrentValue();}

	Constraint<unsigned int>& GetDayMaxPosSharesConstraint(){return m_dayMaxPosShares;}
	const Constraint<unsigned int>& GetDayMaxPosSharesConstraint() const{return m_dayMaxPosShares;}
	const unsigned int& GetDayMaxPosShares() const{return m_dayMaxPosShares.GetCurrentValue();}

	Constraint<unsigned int>& GetNightMaxPosSharesConstraint(){return m_nightMaxPosShares;}
	const Constraint<unsigned int>& GetNightMaxPosSharesConstraint() const{return m_nightMaxPosShares;}
	const unsigned int& GetNightMaxPosShares() const{return m_nightMaxPosShares.GetCurrentValue();}

	Constraint<unsigned int>& GetMaxPosPendingOrderConstraint(){return m_maxPosPendingOrders;}
	const Constraint<unsigned int>& GetMaxPosPendingOrderConstraint() const{return m_maxPosPendingOrders;}
	const unsigned int& GetMaxPosPendingOrder() const{return m_maxPosPendingOrders.GetCurrentValue();}

	Constraint<unsigned int>& GetMaxOpenPositionsConstraint(){return m_maxOpenPositions;}
	const Constraint<unsigned int>& GetMaxOpenPositionsConstraint() const{return m_maxOpenPositions;}
	const unsigned int& GetMaxOpenPositions() const{return m_maxOpenPositions.GetCurrentValue();}

	Constraint<unsigned int>& GetMaxOrderSizeConstraint(){return m_maxOrderSize;}
	const Constraint<unsigned int>& GetMaxOrderSizeConstraint() const{return m_maxOrderSize;}
	const unsigned int& GetMaxOrderSize() const{return m_maxOrderSize.GetCurrentValue();}
/*
	Constraint<int>& GetAutoCloseStartDelayConstraint(){return m_autoCloseStartDelaySecond;}
	const Constraint<int>& GetAutoCloseStartDelayConstraint() const{return m_autoCloseStartDelaySecond;}
	const int& GetAutoCloseStartDelay() const{return m_autoCloseStartDelaySecond.GetCurrentValue();}

	Constraint<int>& GetAutoCloseEndDelayConstraint(){return m_autoCloseEndDelaySecond;}
	const Constraint<int>& GetAutoCloseEndDelayConstraint() const{return m_autoCloseEndDelaySecond;}
	const int& GetAutoCloseEndDelay() const{return m_autoCloseEndDelaySecond.GetCurrentValue();}
*/
#ifndef TAKION_NO_OPTIONS
	Constraint<Money>& GetOptionBuyingPowerConstraint(){return m_optionBuyingPower;}
	const Constraint<Money>& GetOptionBuyingPowerConstraint() const{return m_optionBuyingPower;}
	const Money& GetOptionBuyingPower() const{return m_optionBuyingPower.GetCurrentValue();}

	Constraint<unsigned int>& GetMaxOptionSharesTradedConstraint(){return m_maxOptionSharesTraded;}
	const Constraint<unsigned int>& GetMaxOptionSharesTradedConstraint() const{return m_maxOptionSharesTraded;}
	const unsigned int& GetMaxOptionSharesTraded() const{return m_maxOptionSharesTraded.GetCurrentValue();}

	Constraint<unsigned int>& GetMaxOptionContractsOpenConstraint(){return m_maxOptionContractsOpen;}
	const Constraint<unsigned int>& GetMaxOptionContractsOpenConstraint() const{return m_maxOptionContractsOpen;}
	const unsigned int& GetMaxOptionContractsOpen() const{return m_maxOptionContractsOpen.GetCurrentValue();}

	Constraint<unsigned int>& GetMaxOptionOrderSizeConstraint(){return m_maxOptionOrderSize;}
	const Constraint<unsigned int>& GetMaxOptionOrderSizeConstraint() const{return m_maxOptionOrderSize;}
	const unsigned int& GetMaxOptionOrderSize() const{return m_maxOptionOrderSize.GetCurrentValue();}

	Constraint<Money>& GetMaxOptionOrderValueConstraint(){return m_maxOptionOrderValue;}
	const Constraint<Money>& GetMaxOptionOrderValueConstraint() const{return m_maxOptionOrderValue;}
	const Money& GetMaxOptionOrderValue() const{return m_maxOptionOrderValue.GetCurrentValue();}

	Constraint<unsigned char>& GetOptionNakedConstraint(){return m_optionNaked;}
	const Constraint<unsigned char>& GetOptionNakedConstraint() const{return m_optionNaked;}
	const unsigned char& GetOptionNaked() const{return m_optionNaked.GetCurrentValue();}
#endif
	void UpdateMaxLoss90Percent()
	{
		m_maxLoss90Percent = m_maxLoss.GetCurrentValue();
		if(!m_maxLoss90Percent.isZero())
		{
			m_maxLoss90Percent *= 90;
			m_maxLoss90Percent /= 100;
		}
	}
	const AccountId& GetAccountId() const{return m_accountId;}
protected:
	AccountId m_accountId;
	char m_id[16];
	bool m_simulation;

	Money m_maxLoss90Percent;

	Constraint<Money> m_buyingPower;
	Constraint<Money> m_hardBuyingPower;

	Constraint<Money> m_dayMaxPosInvestment;
	Constraint<Money> m_nightMaxPosInvestment;
	Constraint<Money> m_dayMaxLongInvestment;
	Constraint<Money> m_nightMaxLongInvestment;
	Constraint<Money> m_dayMaxShortInvestment;
	Constraint<Money> m_nightMaxShortInvestment;
	Constraint<Money> m_nightMaxInvestment;

	Constraint<Money> m_maxLoss;
	Constraint<Money> m_maxLossSlack;
	Constraint<Money> m_maxLossClose;
	Constraint<Money> m_maxLossPerPosition;
	Constraint<Money> m_maxLossPerPositionSlack;
	Constraint<Money> m_maxLossPerPositionClose;
	Constraint<Money> m_maxOpenLossPerPosition;
	Constraint<Money> m_maxTradedMoney;
	Constraint<Money> m_maxOrderValue;
	Constraint<Price> m_minShortPrice;

	Constraint<Money> m_commissionPer1000Shares;

	Constraint<unsigned int> m_maxSharesTotal;
	Constraint<unsigned int> m_maxSharesTraded;

	Constraint<unsigned int> m_dayMaxPosShares;
	Constraint<unsigned int> m_nightMaxPosShares;
	Constraint<unsigned int> m_maxPosPendingOrders;
	Constraint<unsigned int> m_maxOpenPositions;
	Constraint<unsigned int> m_maxOrderSize;

	Constraint<int> m_autoCloseStartDelaySecond;
	Constraint<int> m_autoCloseEndDelaySecond;

#ifndef TAKION_NO_OPTIONS
	Constraint<Money> m_optionBuyingPower;
	Constraint<unsigned int> m_maxOptionSharesTraded;
	Constraint<unsigned int> m_maxOptionOrderSize;
	Constraint<Money> m_maxOptionOrderValue;
	Constraint<unsigned char> m_optionNaked;
	Constraint<unsigned int> m_maxOptionContractsOpen;
#endif
/*
//	DWORD				IntradayMaxPosShares;
	double				IntradayMaxPosValue;
	double				IntradayMaxLongValue;
	double				IntradayMaxShortValue;
//	DWORD				OvernightMaxPosShares;
	double				OvernightMaxPosValue;
	double				OvernightMaxLongValue;
	double				OvernightMaxShortValue;
//	DWORD				MaxOpenPositions;
	double				MaxLoss;
	double				MaxLossPerPosition;
	double				MaxOpenLossPerPosition;
	double				MaxTradedMoney;
	double				MinShortPrice;
//	unsigned int		MaxOrderSize;
//	unsigned int		MaxPendingOrdersPerPosition;
//	unsigned int		MaxSharesTotal;
//	unsigned int		MaxSharesTraded;
*/
};

enum SwipeType : unsigned char
{
	SWIPE_MEGA,
	SWIPE_DUMB,
	SWIPE_SMART,
	SWIPE_SPIDER,

	SWIPE_TYPE_COUNT
};
/*
enum ActOnMaxLossMode : unsigned char
{
	MLM_NONE,
	MLM_CANCEL_OPENING_ORDERS,
	MLM_CANCEL_ORDERS_AND_CLOSE_POSITIONS
};
*/
enum OversellOrderPolicy : unsigned char
{
	OOP_RESIZE,
	OOP_SPLIT,
	OOP_REJECT,
	OOP_SHORT,

	OOP_Count
};

class TU_API Account : public ConstraintCollection, public Observable, public TakionLock
{
public:
	virtual ~Account();
//	unsigned __int64 GetNumericId() const{return m_numericId;}
	typedef std::hash_set<Order*> OrderSet;
	typedef std::hash_set<Position*> PositionSet;

	virtual const char* GetDestinationById(unsigned int destinationId) const{return "";}
	virtual const char* GetOrderTypeById(unsigned int id) const{return "";}
	static void GetSideAsString(std::string& str, char side);
	void GetOrderErrorAsString(std::string& error, const char* symbol, char side, bool borrow, unsigned int orderSize, unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint) const;
	void GetCancelErrorAsString(std::string& error, const char* symbol, char side, unsigned int clientId, unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint) const;
	const char* GetUserName() const{return m_userName;}
	const char* GetClearingAccountName() const{return m_clearingAccountName;}
	const unsigned __int64& GetClearingAccountNamePart1() const{return *(unsigned __int64*)m_clearingAccountName;}
	const unsigned __int64& GetClearingAccountNamePart2() const{return *(unsigned __int64*)(m_clearingAccountName + sizeof(unsigned __int64));}

	const char* GetClearingFirmId() const{return m_firmId;}
	const unsigned int& GetClearingFirmIdNum() const{return m_firmIdNum;}
	const unsigned int& GetClearingFirmOrdinal() const{return m_clearingFirmOrdinal;}

	const char* GetStockLoanFirmId() const{return m_stockLoanFirmId;}
	const unsigned int& GetStockLoanFirmIdNum() const{return m_stockLoanFirmIdNum;}
	const unsigned int& GetStockLoanFirmOrdinal() const{return m_stockLoanFirmOrdinal;}

	virtual bool isDefaultAccount() const{return false;}
	virtual bool isSupervisor() const{return false;}
	virtual bool CanAutoCancel() const{return true;}

	virtual HANDLE GetThreadHandle() const{return NULL;}
	virtual unsigned int GetThreadId() const{return 0;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}

	virtual unsigned int GetOrderProcessingFlags() const{return 0;}//some entitlements coming from the server

	virtual void SetSimulation(bool simulation);
	virtual void SetCustomEqual(const ConstraintCollection& other);
/*
	bool Lock() const{return InterlockedExchange(&m_lockForObservingInMainThread, 1) == 0;}
	void Unlock() const{InterlockedExchange(&m_lockForObservingInMainThread, 0);}
	void LockWait() const{while(!Lock())Sleep(0);}
*/
	void AddInThreadObserver(Observer* o) const;//Call RemoveInThreadObserver in the destructor of the object that you pass to this function
	void RemoveInThreadObserver(Observer* o) const;
//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;
/*
	bool LockPositionStorage(){return InterlockedExchange(&m_lockPositionStorage, 1) == 0;}
	void UnlockPositionStorage(){InterlockedExchange(&m_lockPositionStorage, 0);}
	void LockWaitPositionStorage(){while(!LockPositionStorage())Sleep(0);}

	bool LockOrderStorage(){return InterlockedExchange(&m_lockOrderStorage, 1) == 0;}
	void UnlockOrderStorage(){InterlockedExchange(&m_lockOrderStorage, 0);}
	void LockWaitOrderStorage(){while(!LockOrderStorage())Sleep(0);}

	bool LockExecutionStorage(){return InterlockedExchange(&m_lockExecutionStorage, 1) == 0;}
	void UnlockExecutionStorage(){InterlockedExchange(&m_lockExecutionStorage, 0);}
	void LockWaitExecutionStorage(){while(!LockExecutionStorage())Sleep(0);}
*/
	virtual unsigned char SendOrder(unsigned int* orderClientId,//output parameter; can be NULL
		Order* orderToReplace,
		bool replaceNative,
		int replaceSizeOffset,
		const Security* security,

		unsigned int destinationName,
		unsigned int destinationId,

		char side,

		unsigned char orderType,
		unsigned short userOrderType,//usually should be 0
		const char* userOrderInfo,//usually should be NULL
		const Price& limitPrice,
		const Price& discretionaryPrice,

		const SignedPrice& stopPrice,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,

		Price& level1Bid,
		Price& level1Ask,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
//		bool proactive,
		bool iso,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		unsigned char tifType,
		unsigned int tifMillisecond,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,
		const std::string* isoAttachment,
		const unsigned __int64& userId,
		unsigned int parentId = 0
		) = 0;

	typedef std::set<unsigned int> UIntSet;

	virtual unsigned char SendSwipeOrder(unsigned int* orderClientId,//output parameter; can be NULL
//		Position* position,
		const Security* security,
		unsigned char swipeType,
		const UIntSet& destinations,
		bool excludeDestinations,
		const UIntSet& filter,
		char side,
		unsigned short userOrderType,//usually should be 0
		const char* userOrderInfo,//usually should be NULL
		const Price& price,
		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,
		unsigned short routingId,
		unsigned int routingName,

//		bool proactive,
		unsigned char tifType,
		unsigned int tifMilliseconds,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,
		bool hideSlowQuotes,

		bool postRemainder,
		unsigned int postDestination,
		unsigned int postDestinationName,
		unsigned int postRoutingName,
		unsigned short postRoutingId,
		unsigned short postRoutingSubType,
		unsigned int postMnemonic,
		unsigned char postTifType,
		unsigned int postTif,
		bool postRemainderOnIsoViolation,
		bool iterate,
		const unsigned __int64& userId,
		unsigned int parentId = 0,
		unsigned char pegType = PEG_NONE,//For Spider SmartSwipe only
		const SignedPrice& pegOffset = SignedPrice(0, 0)//For Spider SmartSwipe only
		) = 0;
//	const ExecutionMap& GetExecutionMap() const{return m_executionMap;}

	virtual unsigned char SendOrderAlgorithm(const Security* security, OrderAlgorithm* orderAlgorithm) = 0;

	virtual unsigned char SendPanicCloseOrder(unsigned int* orderClientId,//output parameter; can be NULL
		Position* position, bool blockAggressiveOrders) = 0;

	const OrderMap& GetAllOrders() const{return m_allOrders;}//key is clientId
	const OrderMap& GetOrdersUnacknowledged() const{return m_ordersUnacknowledged;}
	const OrderMap& GetOrdersAcknowledged() const{return m_ordersAcknowledged;}
	const OrderMap& GetOrdersRejected() const{return m_ordersRejected;}
	const OrderMap& GetOrdersAlgorithm() const{return m_ordersAlgorithm;}

	const OrderMap& GetOrdersPending() const{return m_ordersPending;}//Unacknowledged and Acknowledged
	unsigned int GetOrdersPendingCount() const{return (unsigned int)m_ordersPending.GetCount();}

	const OrderMap& GetOrdersActive() const{return m_ordersActive;}//Pending orders with no cancel sent and acknowledgwed
	unsigned int GetOrdersActiveCount() const{return (unsigned int)m_ordersActive.GetCount();}

	bool HasPendingNonProblematicOrders() const{return GetOrdersPendingCount() > (unsigned int)m_ordersWithCancelProblem.GetCount();}
	bool HasActiveNonProblematicOrders() const{return GetOrdersActiveCount() > (unsigned int)m_ordersWithCancelProblem.GetCount();}

	const OrderMap& GetOrdersStuck() const{return m_ordersStuck;}
	unsigned int GetOrdersStuckCount() const{return (unsigned int)m_ordersStuck.GetCount();}
	const OrderMap& GetOrdersCancelRejected() const{return m_ordersCancelRejected;}
	unsigned int GetOrdersCancelRejectedCount() const{return (unsigned int)m_ordersCancelRejected.GetCount();}
	const OrderMap& GetOrdersCancelBlocked() const{return m_ordersCancelBlocked;}
	unsigned int GetOrdersCancelBlockedCount() const{return (unsigned int)m_ordersCancelBlocked.GetCount();}

	const OrderMap& GetOrdersWithCancelProblem() const{return m_ordersWithCancelProblem;}
	unsigned int GetOrdersWithCancelProblemCount() const{return (unsigned int)m_ordersWithCancelProblem.GetCount();}

	const Order* FindOrderByClientId(unsigned int clientId) const{const OrderMap::CPair* found = m_allOrders.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderUnacknowledged(unsigned int clientId) const{const OrderMap::CPair* found = m_ordersUnacknowledged.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderAcknowledged(unsigned int serverId) const{const OrderMap::CPair* found = m_ordersAcknowledged.PLookup(serverId); return found ? found->value : NULL;}
	const Order* FindOrderRejected(unsigned int clientId) const{const OrderMap::CPair* found = m_ordersRejected.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderAlgorithm(unsigned int clientId) const{const OrderMap::CPair* found = m_ordersAlgorithm.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderPending(unsigned int clientId) const{const OrderMap::CPair* found = m_ordersPending.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderActive(unsigned int clientId) const{const OrderMap::CPair* found = m_ordersActive.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindDummyOrder(unsigned int serverId) const{const OrderMap::CPair* found = m_dummyOrders.PLookup(serverId); return found ? found->value : NULL;}

	Order* FindOrderByClientId(unsigned int clientId){OrderMap::CPair* found = m_allOrders.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderUnacknowledged(unsigned int clientId){OrderMap::CPair* found = m_ordersUnacknowledged.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderAcknowledged(unsigned int serverId){OrderMap::CPair* found = m_ordersAcknowledged.PLookup(serverId); return found ? found->value : NULL;}
	Order* FindOrderRejected(unsigned int clientId){OrderMap::CPair* found = m_ordersRejected.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderAlgorithm(unsigned int clientId){OrderMap::CPair* found = m_ordersAlgorithm.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderPending(unsigned int clientId){OrderMap::CPair* found = m_ordersPending.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderActive(unsigned int clientId){OrderMap::CPair* found = m_ordersActive.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindDummyOrder(unsigned int serverId){OrderMap::CPair* found = m_dummyOrders.PLookup(serverId); return found ? found->value : NULL;}

	void SetPhantomPosition(const unsigned __int64& rootSymbol,//const char* symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		char phantom);
	void BuyPhantom(const unsigned __int64& rootSymbol//const char* symbol
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
#endif
		);
	void SellPhantom(const unsigned __int64& rootSymbol//const char* symbol
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
#endif
		);
	void FlipPhantomPosition(const unsigned __int64& rootSymbol//const char* symbol
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
#endif
		);
	void SetAllPhantomPositionsFlat();

//	unsigned int GetPendingOrders() const{return GetPendingOrdersLong() + GetPendingOrdersSellAndShort();}
	unsigned int GetPendingOrdersLong() const
	{
		return (unsigned int)m_orders[TU_ORDER_STATUS_UNACKNOWLEDGED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_BUY].GetCount()
			+ (unsigned int)m_orders[TU_ORDER_STATUS_PENDING * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_BUY].GetCount();
	}
	unsigned int GetPendingOrdersSell() const
	{
		return (unsigned int)m_orders[TU_ORDER_STATUS_UNACKNOWLEDGED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SELL].GetCount()
			+ (unsigned int)m_orders[TU_ORDER_STATUS_PENDING * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SELL].GetCount();
	}
	unsigned int GetPendingOrdersShort() const
	{
		return (unsigned int)m_orders[TU_ORDER_STATUS_UNACKNOWLEDGED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SHORT].GetCount()
			+ (unsigned int)m_orders[TU_ORDER_STATUS_PENDING * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SHORT].GetCount();
	}

	unsigned int GetPendingOrdersSellAndShort() const
	{
		return GetPendingOrdersSell() + GetPendingOrdersShort();
	}

	bool HasCanceledOrRejectedOrders() const
	{
		return m_orders[TU_ORDER_STATUS_CANCELED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_BUY].GetCount() > 0
			|| m_orders[TU_ORDER_STATUS_CANCELED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SELL].GetCount() > 0
			|| m_orders[TU_ORDER_STATUS_CANCELED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SHORT].GetCount() > 0
			|| m_orders[TU_ORDER_STATUS_REJECTED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_BUY].GetCount() > 0
			|| m_orders[TU_ORDER_STATUS_REJECTED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SELL].GetCount() > 0
			|| m_orders[TU_ORDER_STATUS_REJECTED * TU_ORDER_SIDE_COUNT + TU_ORDER_SIDE_SHORT].GetCount() > 0;
	}

//	typedef std::map<unsigned int, Order*> OrderChronologicalMap;

	const OrderChronologicalMap& GetChronologicalPendingOrders(OrderSide orderSide) const{return m_chronologicalPendingOrders[orderSide];}
	OrderChronologicalMap& GetChronologicalPendingOrders(OrderSide orderSide){return m_chronologicalPendingOrders[orderSide];}

	const OrderMap& GetOrders(OrderStatus orderStatus, OrderSide orderSide) const{return m_orders[orderStatus * TU_ORDER_SIDE_COUNT + orderSide];}
	OrderMap& GetOrders(OrderStatus orderStatus, OrderSide orderSide){return m_orders[orderStatus * TU_ORDER_SIDE_COUNT + orderSide];}
//	TakionIterator* CreateOrderIterator(OrderStatus orderStatus, OrderSide orderSide) const;
	TakionIterator* CreateOrderIterator(unsigned int orderStatusMask, unsigned int orderSideMask) const;
	void AddMaskToOrderIterator(TakionIterator* iterator, unsigned int orderStatusMask, unsigned int orderSideMask) const;

	const ExecutionRefMap& GetExecutionRefMap() const{return m_executionRefMap;}
//	const Execution* FindExecutionByRefId(const char* refId) const{const ExecutionRefMap::CPair* found = m_executionRefMap.PLookup(StringHashKey(std::string(refId))); return found ? found->value : NULL;}
	const Execution* FindExecutionByRefId(const ExecutionIdAsNumberArray& id) const{const ExecutionRefMap::CPair* found = m_executionRefMap.PLookup(id); return found ? found->value : NULL;}
	const Execution* FindExecutionByRefId(const char* refId) const{return FindExecutionByRefId(ExecutionIdAsNumberArray(refId));}
	const Execution* FindExecutionByRefId(const std::string& refId) const{return FindExecutionByRefId(ExecutionIdAsNumberArray(refId));}
//	bool ExecutionExists(const char* refId) const{return m_executionRefMap.PLookup(StringHashKey(std::string(refId))) != NULL;}
	bool ExecutionExists(const ExecutionIdAsNumberArray& id) const{return m_executionRefMap.PLookup(id) != NULL;}
	bool ExecutionExists(const char* refId) const{return ExecutionExists(ExecutionIdAsNumberArray(refId));}
	bool ExecutionExists(const std::string& refId) const{return ExecutionExists(ExecutionIdAsNumberArray(refId));}

	const ExecutionMap& GetExecutions(OrderSide orderSide) const{return m_executions[orderSide];}
	ExecutionMap& GetExecutions(OrderSide orderSide){return m_executions[orderSide];}
	TakionIterator* CreateExecutionIterator(unsigned int orderSideMask) const;
	void AddMaskToExecutionIterator(TakionIterator* iterator, unsigned int orderSideMask) const;

	const ExecutionChronologicalSet& GetChronologicalExecutions() const{return m_chronologicalExecutions;}
	ExecutionChronologicalSet& GetChronologicalExecutions(){return m_chronologicalExecutions;}

	Execution* FindExecution(unsigned int id, OrderSide orderSide);

#ifndef TAKION_NO_OPTIONS
//	typedef CMap<OptionSymbolBlockKey, const OptionSymbolBlockKey&, Position*, Position*> OptionPositionMap;

	const OptionPositionMap& GetOptionPositionsAll() const{return m_optionPositionsAll;}
	const OptionPositionMap& GetOptionPositions(PositionStatus positionStatus) const{return m_optionPositions[positionStatus];}
	const OptionPositionMap& GetOptionActivePositions() const{return m_optionActivePositions;}//non flat or flat with pending orders
	unsigned int GetOptionActivePositionCount() const{return (unsigned int)m_optionActivePositions.GetCount();}

	OptionPositionMap& GetOptionPositions(PositionStatus positionStatus){return m_optionPositions[positionStatus];}
	TakionIterator* CreateOptionPositionIterator(unsigned int positionStatusMask) const;
	void AddMaskToOptionPositionIterator(TakionIterator* iterator, unsigned int positionStatusMask) const;

	unsigned int GetOptionPositionCountLong() const{return (unsigned int)GetOptionPositions(TU_POSITION_STATUS_LONG).GetCount();}
	unsigned int GetOptionPositionCountShort() const{return (unsigned int)GetOptionPositions(TU_POSITION_STATUS_SHORT).GetCount();}
	unsigned int GetOptionPositionCount() const{return GetOptionPositionCountLong() + GetOptionPositionCountShort();}

	Position* FindOptionPosition(const OptionSymbolBlockKey& key) const{const OptionPositionMap::CPair* positionPair = m_optionPositionsAll.PLookup(key); return positionPair ? positionPair->value : NULL;}
	Position* FindOptionPositionWithLock(const OptionSymbolBlockKey& key) const
	{
		Position* position;
		const OptionPositionMap::CPair* positionPair;
		LockInquiryWait();
		positionPair = m_optionPositionsAll.PLookup(key);
		position = positionPair ? positionPair->value : NULL;
		UnlockInquiry();
		return position;
	}

	Position* FindOptionPosition(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const{return FindOptionPosition(OptionSymbolBlockKey(rootSymbol, optionBlock));}
	Position* FindOptionPositionWithLock(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const{return FindOptionPositionWithLock(OptionSymbolBlockKey(rootSymbol, optionBlock));}

	Position* FindPosition(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return optionBlock ? FindOptionPosition(OptionSymbolBlockKey(rootSymbol, optionBlock)) : FindStockPosition(rootSymbol);
	}
	Position* FindPositionWithLock(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return optionBlock ? FindOptionPositionWithLock(OptionSymbolBlockKey(rootSymbol, optionBlock)) : FindStockPositionWithLock(rootSymbol);
	}

	const Money& GetOptionBuyingPowerUsed() const{return m_optionBuyingPowerUsed;}
	const Money& GetOptionBuyingPowerAvailable() const{return m_optionBuyingPowerAvailable;}
	const Money& GetMaxOptionBpUsed() const{return m_maxOptionBpUsed;}
	const unsigned int& GetOptionContractsTraded() const{return m_optionContractsTraded;}
	const unsigned int& GetOptionSharesTraded() const{return m_optionSharesTraded;}
	const unsigned int& GetStockSharesTraded() const{return m_stockSharesTraded;}
//	const unsigned int& GetOptionSharesAdded() const{return m_optionSharesAdded;}
//	const unsigned int& GetOptionSharesRemoved() const{return m_optionSharesRemoved;}
	const unsigned int& GetOptionPotentialLongSize() const{return m_optionPotentialLongSize;}//in contracts
	const unsigned int& GetOptionPotentialShortSize() const{return m_optionPotentialShortSize;}//in contracts
	const unsigned int& GetOptionPotentialSize() const{return m_optionPotentialSize;}//in contracts
#endif

	const PositionMap& GetStockPositionsAll() const{return m_stockPositionsAll;}
	const PositionMap& GetStockPositions(PositionStatus positionStatus) const{return m_stockPositions[positionStatus];}
//	const PositionMap& GetStockPhantomPositions(bool longPhantom) const{return longPhantom ? m_stockPhantomLongPositions : m_stockPhantomShortPositions;}
	const PositionMap& GetStockActivePositions() const{return m_stockActivePositions;}//non flat or flat with pending orders
	unsigned int GetStockActivePositionCount() const{return (unsigned int)m_stockActivePositions.GetCount();}

	PositionMap& GetStockPositions(PositionStatus positionStatus){return m_stockPositions[positionStatus];}
	TakionIterator* CreatePositionIterator(unsigned int positionStatusMask) const;
	void AddMaskToPositionIterator(TakionIterator* iterator, unsigned int positionStatusMask) const;
	
	unsigned int GetStockPositionCountLong() const{return (unsigned int)GetStockPositions(TU_POSITION_STATUS_LONG).GetCount();}
	unsigned int GetStockPositionCountShort() const{return (unsigned int)GetStockPositions(TU_POSITION_STATUS_SHORT).GetCount();}
	unsigned int GetStockPositionCount() const{return GetStockPositionCountLong() + GetStockPositionCountShort();}

	Position* FindPosition(const Security* security) const
	{
#ifndef TAKION_NO_OPTIONS
		const OptionInfo* optionInfo = security->GetOptionInfo();
		if(optionInfo)
		{		
			const OptionPositionMap::CPair* positionPair = m_optionPositionsAll.PLookup(OptionSymbolBlockKey(security->GetNumericSymbol(), optionInfo->GetOptionBlock()));
			return positionPair ? positionPair->value : NULL;
		}
		else
		{
#endif
			const PositionMap::CPair* positionPair = m_stockPositionsAll.PLookup(security->GetNumericSymbol());
			return positionPair ? positionPair->value : NULL;
#ifndef TAKION_NO_OPTIONS
		}
#endif
	}
	Position* FindPositionWithLock(const Security* security) const
	{
		Position* position;
		LockInquiryWait();
		position = FindPosition(security);
		UnlockInquiry();
		return position;
	}

	Position* FindStockPosition(const unsigned __int64& symbol) const{const PositionMap::CPair* positionPair = m_stockPositionsAll.PLookup(symbol); return positionPair ? positionPair->value : NULL;}
	Position* FindStockPositionWithLock(const unsigned __int64& symbol) const
	{
		Position* position;
		const PositionMap::CPair* positionPair;
		LockInquiryWait();
		positionPair = m_stockPositionsAll.PLookup(symbol);
		position = positionPair ? positionPair->value : NULL;
		UnlockInquiry();
		return position;
	}

	const Money& GetPotentialLongValue() const{return m_potentialLongValue;}
	const Money& GetPotentialShortValue() const{return m_potentialShortValue;}

	const Money& GetPotentialLongNightValue() const{return m_potentialLongNightValue;}
	const Money& GetPotentialShortNightValue() const{return m_potentialShortNightValue;}

	const Money& GetNightBuyingPowerUsed() const{return m_nightBuyingPowerUsed;}

	const Money& GetBuyingPowerUsed() const{return m_buyingPowerUsed;}
	const Money& GetBuyingPowerAvailable() const{return m_buyingPowerAvailable;}
	const Money& GetMaxBpUsed() const{return m_maxBpUsed;}

	const Money& GetHardBuyingPowerAvailable() const{return m_hardBuyingPowerAvailable;}

	const Money& GetClosedPnlCost() const{return m_closedPnlCost;}
	const Money& GetOpenPnlLevel1Cost() const{return m_openPnlLevel1Cost;}

	const Money& GetClosedPnl() const{return m_closedPnl;}
	const Money& GetOpenPnlLevel1() const{return m_openPnlLevel1;}
	const Money& GetOpenPnlPrint() const{return m_openPnlPrint;}
	const Money& GetOpenPnlTClose() const{return m_openPnlTClose;}
	const Money& GetOpenPnlNbboPrint() const{return m_openPnlNbboPrint;}
	const Money& GetOpenPnlNbboPrintHi() const{return m_openPnlNbboPrintHi;}
	const Money& GetOpenPnlNbboPrintLo() const{return m_openPnlNbboPrintLo;}
	const Money& GetMarkedPnlNbboPrint() const{return m_markedPnlNbboPrint;}
	const Money& GetMarkedPnlNbboPrintHi() const{return m_markedPnlNbboPrintHi;}
	const Money& GetMarkedPnlNbboPrintLo() const{return m_markedPnlNbboPrintLo;}
	const Money& GetOpenPnlForLoss() const{return m_openPnlNbboPrint;}//m_openPnlPrint;}

	const __int64& GetOpenPnlForLossDollars() const{return GetOpenPnlForLoss().GetDollarsRef();}
	const __int64& GetClosedPnlDollars() const{return GetClosedPnl().GetDollarsRef();}
	__int64 GetMarkedPnlForLossDollars() const{return GetOpenPnlForLossDollars() + GetClosedPnlDollars();}

	const Money& GetInvestmentLong() const{return m_investmentLong;}
	const Money& GetInvestmentShort() const{return m_investmentShort;}
	const Money& GetInvestment() const{return m_investment;}
	const Money& GetHardBpUsed() const{return m_hardBpUsed;}//can be different from m_investment if a retail account has overnight position.

	const Money& GetInvestmentCostLong() const{return m_investmentCostLong;}
	const Money& GetInvestmentCostShort() const{return m_investmentCostShort;}
	const Money& GetInvestmentCost() const{return m_investmentCost;}

	const Money& GetPendingBuyInvestment() const{return m_pendingBuyInvestment;}
	const Money& GetPendingSellInvestment() const{return m_pendingSellInvestment;}

	const Money& GetMaxInvestmentLong() const{return m_maxInvestmentLong;}
	const Money& GetMaxInvestmentShort() const{return m_maxInvestmentShort;}
	const Money& GetMaxInvestment() const{return m_maxInvestment;}

	const Money& GetEstimatedBeginningEquity() const{return m_estimatedBeginningEquity;}

	const unsigned int GetBuyExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_BUY].GetCount();}
	const unsigned int GetSellExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_SELL].GetCount();}
	const unsigned int GetShortExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_SHORT].GetCount();}

	const unsigned int& GetSharesTraded() const{return m_sharesTraded;}
	const unsigned int& GetSharesAdded() const{return m_sharesAdded;}
	const unsigned int& GetSharesRemoved() const{return m_sharesRemoved;}
	const unsigned int& GetPendingBuyShares() const{return m_pendingBuyShares;}
	const unsigned int& GetPendingSellShares() const{return m_pendingSellShares;}

	const unsigned int& GetPotentialLongSize() const{return m_potentialLongSize;}
	const unsigned int& GetPotentialShortSize() const{return m_potentialShortSize;}
	const unsigned int& GetPotentialSize() const{return m_potentialSize;}

	const unsigned int& GetPotentialLongNightSize() const{return m_potentialLongNightSize;}
	const unsigned int& GetPotentialShortNightSize() const{return m_potentialShortNightSize;}
	const unsigned int& GetPotentialNightSize() const{return m_potentialNightSize;}

	const unsigned int& GetLongSize() const{return m_longSize;}
	const unsigned int& GetShortSize() const{return m_shortSize;}
	const unsigned int& GetSize() const{return m_size;}

	const Money& GetTicketAverage() const{return m_ticketAverage;}
	const Money& GetMarkedTicketAverage() const{return m_markedTicketAverage;}
	const Money& GetMarkedTicketAverageHi() const{return m_markedTicketAverageHi;}
	const Money& GetMarkedTicketAverageLo() const{return m_markedTicketAverageLo;}
	const Money& GetClosedPnlNet() const{return m_closedPnlNet;}
	const Money& GetOpenCommissionFee() const{return m_openCommissionFee;}

	const Money& GetBorrowInvestment() const{return m_borrowInvestment;}
	const Money& GetPendingBuyBorrowInvestment() const{return m_pendingBuyBorrowInvestment;}
	const unsigned int& GetPendingBuyBorrowShares() const{return m_pendingBuyBorrowShares;}
	const unsigned int& GetPendingSellBorrowShares() const{return m_pendingSellBorrowShares;}
	const unsigned int& GetBorrowSize() const{return m_borrowSize;}

	const unsigned int& GetOvernightLongSize() const{return m_overnightLongSize;}
	const unsigned int& GetOvernightShortSize() const{return m_overnightShortSize;}
	const unsigned int& GetOvernightSize() const{return m_overnightSize;}
	const Money& GetOvernightLongInvestment() const{return m_overnightLongInvestment;}
	const Money& GetOvernightShortInvestment() const{return m_overnightShortInvestment;}
	const Money& GetOvernightInvestment() const{return m_overnightInvestment;}

	virtual unsigned char CancelOrder(Order* order){return CE_OK;}
	void CollectOrders(OrderSet& orderSet,
		bool forCancel,
		bool eachPosition,
		unsigned char sideMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		OrderCancelPick orderCancelPick,
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet) const;

	unsigned int CancelOrders(bool eachPosition,
		unsigned char sideMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		OrderCancelPick orderCancelPick,
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet);

	unsigned int ReplaceOrders(bool eachPosition,
		bool replaceNative,
		unsigned char sideMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		OrderCancelPick orderCancelPick,
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet,
		const SignedPrice& replacePriceOffset,
		bool replacePriceReverseForSell,
		int replaceSizeOffset,
		bool replaceSizeReverseForSell,
		const unsigned __int64& userId,
		unsigned char displaySizeMode,//0 - size fraction, 1 - round lot, 2 - no change
		unsigned int displaySize,
		unsigned int displaySizeFraction);
	const bool& isTradingAllowed() const{return m_tradingAllowed;}

	virtual bool CanTrade() const{return m_tradingAllowed;}
	
	const bool& isExecutionsLoaded() const{return m_executionsLoaded;}
	virtual bool LoadExecutions() const{return false;}

	const bool& isOrdersLoaded() const{return m_ordersLoaded;}
	virtual bool LoadOrders() const{return false;}

	const char& GetAccountType() const{return m_accountType;}
	const char& GetFirmType() const{return m_firmType;}

	const bool& isRetail() const{return m_retail;}

	const unsigned short& GetRecoveryErrorCode() const{return m_recoveryErrorCode;}
	bool isHistoryLoaded() const{return !m_recoveryErrorCode;}
	void ResetRecoveryErrorCode(bool simulation){m_recoveryErrorCode = simulation ? 0 : 0xFFFF;}//history is not loaded

	void CalculateOrderImpact(char side,
		unsigned int quantity,
		int posSize,
		unsigned int absPosSize,//absPosSize in contracts for options
#ifndef TAKION_NO_OPTIONS
		unsigned int contractSize,
#endif
		const Price& orderPrice,
		const Position* position,
//		const Money& posInvestment,
//		const Money& posBpBorrowUsed,
		Money& posPendingBuyInvestment,
		Money& posPendingSellInvestment,
		unsigned int& posPendingBuyShares,
		unsigned int& posPendingSellShares,
		Money& posBpUsed,
		Money& posLongValue,
		Money& posShortValue,
		unsigned int& posLongSize,
		unsigned int& posShortSize);

	static void CalculatePotentialPositionSize(char side, unsigned int quantity, int posSize, unsigned int absPosSize,
		unsigned int& pendingBuyShares,
		unsigned int& pendingSellShares,
		unsigned int& longSize,
		unsigned int& shortSize);

	static unsigned int CalculateSizeToBorrow(char side, unsigned int quantity, int posSize, unsigned int absPosSize, unsigned int borrowSize);

	void CollectOrdersInEachPosition(OrderSet& orderSet,
		bool forCancel,
		unsigned char sideMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		OrderCancelPick orderCancelPick,
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet) const;
	unsigned int CancelOrdersInEachPosition(unsigned char sideMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		OrderCancelPick orderCancelPick,
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet);
	
	void CollectAllOrdersInCategory(OrderSet& orderSet,
		bool forCancel,
		unsigned char sideMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet) const;
	unsigned int CancelAllOrdersInCategory(
		unsigned char sideMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		unsigned char tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude,
		const UIntSet& destinationSet);

	unsigned int CancelAllAlgorithmsAndActiveOrders();

	virtual unsigned char DoWriteCancelOrderToSocket(const Order* order){return CE_OK;}
	virtual unsigned char DoWriteMultipleCancelsToSocket(Position* position, OrderSet& orderSet, unsigned int* notCanceledClientId = NULL){return CE_OK;}
	virtual void WritePhantomMessageToAccountThread(const unsigned __int64& underlierSymbol,//const char* symbol,
//		unsigned char securityType,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		char phantom){}//(-1 <= phantom <= +1) - set value, -2 - sell, +2 - buy, +3 flip
	virtual void WriteAllPhantomMessageToAccountThread(unsigned int code){}
	virtual void WriteMessageToAccountThread(const Message* message){}

	virtual void WriteSecurityUpdateMessageToAccountThread(unsigned int algoClientId){}
	virtual void WriteNotificationMessageToMainThread(unsigned int algoClientId, unsigned short code){}

//	virtual ActOnMaxLossMode GetActOnMaxLossMode() const{return MLM_NONE;}
	bool isCancelOrdersInitiated() const{return m_cancelOrdersInitiated;}
	bool isClosePositionsInitiated() const{return m_closePositionsInitiated;}

	const unsigned char& GetItgAccount() const{return m_itgAccount;}

	const Price& GetBorrowPriceMultiplier() const{return m_borrowPriceMultiplier;}

	unsigned int GetExchangeEntitlements() const{return m_exchangeEntitlements;}
	virtual bool isEntitled(unsigned char primaryExchangeFlag) const{return (m_exchangeEntitlements & (1 << primaryExchangeFlag)) != 0;}

	bool isLoadingHistory() const{return m_loadingHistory;}
#ifdef LOG_UPDATE_STOCK
	unsigned __int64 FindStrayOrder(const Order* order) const;
#endif
#ifdef FIRM_VALUES
	const AccountAggregator* GetAccountAggregator() const{return m_accountAggregator;}
	AccountAggregator* GetAccountAggregator(){return m_accountAggregator;}
	const AccountAggregatorId& GetAccountAggregatorId() const{return m_accountAggregatorId;}
	const bool& isPositionAggregation() const{return m_positionAggregation;}
	const bool& isBorrowToCoverOvernightShortInitialized() const{return m_borrowToCoverOvernightShortInitialized;}
#endif
protected:
	Account(const char* id, bool simulation);
//	unsigned __int64 m_numericId;

	void AddPosition(Position* position);//called in the worker thread only. Account must be locked for modification before the call

//	virtual void DoSetPhantomPositionInThread(const char* symbol,
	virtual void DoSetPhantomPositionInThread(const unsigned __int64& underlierSymbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		char phantom){}
	virtual void DoSetAllPhantomPositionsFlatInThread(){}
//	virtual void DoIncrementPhantomPositionInThread(const char* symbol, unsigned char securityType, bool decrement){}

	char m_userName[16];
	char m_clearingAccountName[16];
	char m_firmId[8];
	unsigned int m_firmIdNum;
	unsigned int m_clearingFirmOrdinal;

	char m_stockLoanFirmId[8];
	unsigned int m_stockLoanFirmIdNum;
	unsigned int m_stockLoanFirmOrdinal;

#ifdef FIRM_VALUES
	AccountAggregator* m_accountAggregator;
	AccountAggregatorId m_accountAggregatorId;
	bool m_positionAggregation;
	bool m_borrowToCoverOvernightShortInitialized;
#endif

	unsigned int m_exchangeEntitlements;

//	mutable volatile LONG m_lockForObservingInMainThread;
	Observable m_inThreadObservable;
	TakionLockMultithread m_lockInThreadObservable;
/*
	volatile LONG m_lockPositionStorage;
	volatile LONG m_lockOrderStorage;
	volatile LONG m_lockExecutionStorage;
*/
	static void ClearAndDestroyOrders(OrderMap& orderMap);
	void ClearAndDestroyOrders();

	OrderMap m_allOrders;//key is clientId

	OrderMap m_ordersAcknowledged;
	OrderMap m_ordersUnacknowledged;
	OrderMap m_ordersRejected;

	OrderMap m_ordersPending;
	OrderMap m_ordersActive;//Pending orders with no cancel sent and acknowledgwed

	OrderMap m_ordersStuck;
	OrderMap m_ordersCancelRejected;
	OrderMap m_ordersCancelBlocked;

	OrderMap m_ordersWithCancelProblem;

	OrderMap m_ordersAlgorithm;

	OrderMap m_dummyOrders;

	OrderChronologicalMap m_chronologicalPendingOrders[TU_ORDER_SIDE_COUNT];

	OrderMap m_orders[TU_ORDER_STATUS_COUNT * TU_ORDER_SIDE_COUNT];

	static void ClearAndDestroyExecutions(ExecutionMap& executionMap);
	void ClearAndDestroyExecutions();
	ExecutionRefMap m_executionRefMap;
	ExecutionMap m_executions[TU_ORDER_SIDE_COUNT];
	ExecutionChronologicalSet m_chronologicalExecutions;

	void ClearAndDestroyPositions();

#ifndef TAKION_NO_OPTIONS
	OptionPositionMap m_optionPositionsAll;
	OptionPositionMap m_optionPositions[TU_POSITION_STATUS_COUNT];
	OptionPositionMap m_optionActivePositions;//non flat or flat with pending orders
#endif

	PositionMap m_stockPositionsAll;
	PositionMap m_stockPositions[TU_POSITION_STATUS_COUNT];
	PositionMap m_stockActivePositions;//non flat or flat with pending orders
//	PositionMap m_stockPhantomLongPositions;
//	PositionMap m_stockPhantomShortPositions;

//	Money m_buyingPower;
	Money m_potentialLongValue;
	Money m_potentialShortValue;

	Money m_potentialLongNightValue;
	Money m_potentialShortNightValue;

	Money m_nightBuyingPowerUsed;

	Money m_buyingPowerUsed;
	Money m_buyingPowerAvailable;
	Money m_maxBpUsed;

	Money m_hardBuyingPowerAvailable;
#ifndef TAKION_NO_OPTIONS
	Money m_optionBuyingPowerUsed;
	Money m_optionBuyingPowerAvailable;
	Money m_maxOptionBpUsed;
	unsigned int m_optionContractsTraded;
	unsigned int m_optionSharesTraded;
	unsigned int m_stockSharesTraded;
//	unsigned int m_optionSharesAdded;
//	unsigned int m_optionSharesRemoved;
	unsigned int m_optionPotentialLongSize;//in contracts
	unsigned int m_optionPotentialShortSize;//in contracts
	unsigned int m_optionPotentialSize;//in contracts
#endif
	Money m_closedPnlCost;
	Money m_openPnlLevel1Cost;

	Money m_closedPnl;
	Money m_openPnlLevel1;
	Money m_openPnlPrint;
	Money m_openPnlTClose;
	Money m_openPnlNbboPrint;
	Money m_openPnlNbboPrintHi;
	Money m_openPnlNbboPrintLo;
	Money m_markedPnlNbboPrint;
	Money m_markedPnlNbboPrintHi;
	Money m_markedPnlNbboPrintLo;

	unsigned int m_sharesTraded;
	unsigned int m_sharesAdded;
	unsigned int m_sharesRemoved;

	unsigned int m_pendingBuyShares;
	unsigned int m_pendingSellShares;

	unsigned int m_potentialLongSize;
	unsigned int m_potentialShortSize;
	unsigned int m_potentialSize;

	unsigned int m_potentialLongNightSize;
	unsigned int m_potentialShortNightSize;
	unsigned int m_potentialNightSize;

	unsigned int m_longSize;
	unsigned int m_shortSize;
	unsigned int m_size;
	unsigned int m_pendingBuyBorrowShares;
	unsigned int m_pendingSellBorrowShares;
	unsigned int m_borrowSize;
	Money m_ticketAverage;
	Money m_markedTicketAverage;
	Money m_markedTicketAverageHi;
	Money m_markedTicketAverageLo;
	Money m_closedPnlNet;
	Money m_openCommissionFee;

	Money m_investmentLong;
	Money m_investmentShort;
	Money m_investment;
	Money m_hardBpUsed;//can be different from m_investment if a retail account has overnight position.
	Money m_investmentCostLong;
	Money m_investmentCostShort;
	Money m_investmentCost;
	Money m_pendingBuyInvestment;
	Money m_pendingSellInvestment;

	Money m_pendingBuyBorrowInvestment;
	Money m_borrowInvestment;

	Money m_maxInvestmentLong;
	Money m_maxInvestmentShort;
	Money m_maxInvestment;

	unsigned int m_overnightLongSize;
	unsigned int m_overnightShortSize;
	unsigned int m_overnightSize;
	Money m_overnightLongInvestment;
	Money m_overnightShortInvestment;
	Money m_overnightInvestment;

	Money m_estimatedBeginningEquity;

	unsigned short m_recoveryErrorCode;

	char m_accountType;
	char m_firmType;
	bool m_retail;
	bool m_tradingAllowed;
	bool m_executionsLoaded;
	bool m_ordersLoaded;

	bool m_cancelOrdersInitiated;
	bool m_closePositionsInitiated;

	bool m_loadingHistory;

	unsigned char m_itgAccount;

	Price m_borrowPriceMultiplier;
};

/*
typedef CMap<AccountId, const AccountId&, Account*, Account*> AccountMap;

class TU_API AccountGroup : public Account
{
public:
	AccountGroup(const char* id);
//	virtual ~AccountGroup();
	DECLARE_NED_NEW
	const AccountMap& GetAccountMap() const{return m_accountMap;}
	Account* FindAccount(const AccountId& accountId) const
	{
		const AccountMap::CPair* found = m_accountMap.PLookup(accountId);
		return found ? found->value : NULL;
	}
	Account* AddAccount(Account* account);//returns NULL if account successfully added; returns non-NULL if an Account is already in m_accountMap; may return a different account if the m_accountMap already contains a different account with the same id.
	Account* RemoveAccount(const AccountId& accountId);
	void ClearAccounts();
protected:
	AccountMap m_accountMap;
};
*/
class TU_API FontDescription
{
public:
	FontDescription(const char* name, unsigned int size, bool hasMaxSize, unsigned int maxSize, bool bold, bool italic = false):
		m_fontName(name),
		m_fontSize(size),
		m_hasMaxSize(hasMaxSize),
		m_fontMaxSize(hasMaxSize ? maxSize : 0),
		m_fontBold(bold),
		m_fontItalic(italic)
	{}
	FontDescription():
		m_fontName(""),
		m_fontSize(0),
		m_hasMaxSize(false),
		m_fontMaxSize(0),
		m_fontBold(false),
		m_fontItalic(false)
	{}
	const char* GetFontName() const{return m_fontName.c_str();}
	const std::string& GetFontNameStr() const{return m_fontName;}
	unsigned int GetFontSize() const{return m_fontSize;}
	unsigned int GetFontMaxSize() const{return m_fontMaxSize;}
	bool isFontBold() const{return m_fontBold;}
	bool isFontItalic() const{return m_fontItalic;}

	void SetFontName(const char* name){m_fontName = name;}
	void SetFontSize(unsigned int size){m_fontSize = size;}
	void SetFontMaxSize(unsigned int size){m_fontMaxSize = size;}
	void SetFontBold(bool bold){m_fontBold = bold;}
	void SetFontItalic(bool italic){m_fontItalic = italic;}
/*
	void Copy(const FontDescription& other)
	{
		m_fontName = other.m_fontName;
		m_fontSize = other.m_fontSize;
		m_fontMaxSize = other.m_fontMaxSize;
		m_fontBold = other.m_fontBold;
		m_fontItalic = other.m_fontItalic;
	}
*/
	bool operator==(const FontDescription& other) const
	{
		return m_fontName == other.m_fontName
			&& m_fontSize == other.m_fontSize
			&& m_fontMaxSize == other.m_fontMaxSize
			&& m_fontBold == other.m_fontBold
			&& m_fontItalic == other.m_fontItalic;
	}
	bool operator!=(const FontDescription& other) const
	{
		return !operator==(other);
	}
	bool GetHasMaxSize() const{return m_hasMaxSize;}
	void SetHasMaxSize(bool hasMaxSize){m_hasMaxSize = hasMaxSize;}
	void toString(std::string& str, char delimiter) const;
	void fromString(const char*& cursor, char delimiter);
protected:
	std::string m_fontName;
	unsigned int m_fontSize;
	bool m_hasMaxSize;
	unsigned int m_fontMaxSize;
	bool m_fontBold;
	bool m_fontItalic;
};

enum ExtensionError : unsigned char
{
	EE_OK,
	EE_NOT_LOADED,
	EE_TAKION_EXTENSION_WRONG_CODE,
	EE_NOT_TAKION_EXTENSION,
	EE_PATH_AND_NAME_NOT_APPENDABLE,
	EE_PATH_OR_NAME_INVALID,
	EE_NAME_NOT_RETRIEVABLE,

	EE_TRADER_ID_NOT_VALID,

	EE_COUNT
};

class TU_API BaseDll
{
public:
	virtual ~BaseDll()
	{
		DoUnload();
	}
//	virtual unsigned int GetValidExtensionCode() const = 0;
	virtual bool Load();
	virtual bool Unload();

	virtual bool isCustomExtension() const{return false;}

	const std::string& GetName() const{return m_name;}
	const char* GetPath() const{return m_path;}
	const std::string& GetAbsolutePath() const{return m_absolutePath;}
	const std::string& GetOriginalName() const{return m_originalName;}
	const std::string& GetOriginalPath() const{return m_originalPath;}
	const unsigned char& GetError() const{return m_error;}
	bool isLoaded() const{return m_error == EE_OK;}
	HMODULE GetDllHandle() const{return m_dllHandle;}
	const std::string& GetLoadErrorMessage() const{return m_loadErrorMessage;}
	DWORD GetLoadErrorCode() const{return m_loadErrorCode;}
	bool FileExists() const;

	const std::string& GetUnloadErrorMessage() const{return m_unloadErrorMessage;}
	DWORD GetUnloadErrorCode() const{return m_unloadErrorCode;}

	const unsigned int& GetLoadTime() const{return m_loadTime;}
	const unsigned int& GetUnloadTime() const{return m_unloadTime;}

	ApiGetUInt64 GetExtensionVersionFunction() const{return m_ExtensionVersionFunction;}
	ApiGetUInt64 GetUtilsVersionFunction() const{return m_UtilsVersionFunction;}
	ApiGetUInt64 GetUtilsHeaderVersionFunction() const{return m_UtilsHeaderVersionFunction;}
	ApiGetUInt64 GetTakionUtilsVersionFunction() const{return m_TakionUtilsVersionFunction;}
	ApiGetUInt64 GetTakionUtilsHeaderVersionFunction() const{return m_TakionUtilsHeaderVersionFunction;}
	ApiGetUInt64 GetTakionGuiVersionFunction() const{return m_TakionGuiVersionFunction;}
	ApiGetUInt64 GetTakionGuiHeaderVersionFunction() const{return m_TakionGuiHeaderVersionFunction;}
	ApiGetUInt64 GetTakionDataVersionFunction() const{return m_TakionDataVersionFunction;}
	ApiGetUInt64 GetTakionDataHeaderVersionFunction() const{return m_TakionDataHeaderVersionFunction;}

	ApiGetUInt64 GetTakionLogVersionFunction() const{return m_TakionLogVersionFunction;}
	ApiGetUInt64 GetTakionLogHeaderVersionFunction() const{return m_TakionLogHeaderVersionFunction;}
	ApiGetUInt64 GetObserverVersionFunction() const{return m_ObserverVersionFunction;}
	ApiGetUInt64 GetObserverHeaderVersionFunction() const{return m_ObserverHeaderVersionFunction;}

	ApiGetString GetExtensionDescriptionFunction() const{return m_ExtensionDescriptionFunction;}

	const unsigned __int64& GetExtensionVersionValue() const{return m_extensionVersion;}
	const unsigned __int64& GetUtilsVersionValue() const{return m_utilsVersion;}
	const unsigned __int64& GetUtilsHeaderVersionValue() const{return m_utilsHeaderVersion;}
	const unsigned __int64& GetTakionUtilsVersionValue() const{return m_takionUtilsVersion;}
	const unsigned __int64& GetTakionUtilsHeaderVersionValue() const{return m_takionUtilsHeaderVersion;}
	const unsigned __int64& GetTakionGuiVersionValue() const{return m_guiVersion;}
	const unsigned __int64& GetTakionGuiHeaderVersionValue() const{return m_guiHeaderVersion;}
	const unsigned __int64& GetTakionDataVersionValue() const{return m_dataVersion;}
	const unsigned __int64& GetTakionDataHeaderVersionValue() const{return m_dataHeaderVersion;}
	const unsigned __int64& GetTakionLogVersionValue() const{return m_takionLogVersion;}
	const unsigned __int64& GetTakionLogHeaderVersionValue() const{return m_takionLogHeaderVersion;}
	const unsigned __int64& GetObserverVersionValue() const{return m_observerVersion;}
	const unsigned __int64& GetObserverHeaderVersionValue() const{return m_observerHeaderVersion;}
	const std::string& GetExtensionDescriptionValue() const{return m_extensionDescription;}
protected:
	BaseDll(const char* absolutePath);
	BaseDll(const char* name, const char* path);
	virtual bool DoLoad();
	bool DoUnload();

	virtual void Reset();
	virtual void ResetValues();
	void Canonicalize();
	std::string m_absolutePath;
	char m_path[MAX_PATH];
	std::string m_name;
	HMODULE m_dllHandle;
	std::string m_originalName;
	std::string m_originalPath;
	DWORD m_loadErrorCode;
	std::string m_loadErrorMessage;
	DWORD m_unloadErrorCode;
	std::string m_unloadErrorMessage;
	unsigned char m_error;

	ApiGetUInt64 m_ExtensionVersionFunction;
	ApiGetUInt64 m_UtilsVersionFunction;
	ApiGetUInt64 m_UtilsHeaderVersionFunction;
	ApiGetUInt64 m_TakionUtilsVersionFunction;
	ApiGetUInt64 m_TakionUtilsHeaderVersionFunction;
	ApiGetUInt64 m_TakionGuiVersionFunction;
	ApiGetUInt64 m_TakionGuiHeaderVersionFunction;
	ApiGetUInt64 m_TakionDataVersionFunction;
	ApiGetUInt64 m_TakionDataHeaderVersionFunction;
	ApiGetUInt64 m_TakionLogVersionFunction;
	ApiGetUInt64 m_TakionLogHeaderVersionFunction;
	ApiGetUInt64 m_ObserverVersionFunction;
	ApiGetUInt64 m_ObserverHeaderVersionFunction;
	ApiGetString m_ExtensionDescriptionFunction;

	unsigned int m_loadTime;
	unsigned int m_unloadTime;
	unsigned __int64 m_extensionVersion;
	unsigned __int64 m_utilsVersion;
	unsigned __int64 m_utilsHeaderVersion;
	unsigned __int64 m_takionUtilsVersion;
	unsigned __int64 m_takionUtilsHeaderVersion;
	unsigned __int64 m_guiVersion;
	unsigned __int64 m_guiHeaderVersion;
	unsigned __int64 m_dataVersion;
	unsigned __int64 m_dataHeaderVersion;
	unsigned __int64 m_takionLogVersion;
	unsigned __int64 m_takionLogHeaderVersion;
	unsigned __int64 m_observerVersion;
	unsigned __int64 m_observerHeaderVersion;
	std::string m_extensionDescription;
};

class TU_API BaseExtensionDll : public BaseDll
{
public:
	virtual ~BaseExtensionDll()
	{
		DoUnload();
	}
	ApiVoid GetExtensionInitializeFunction() const{return m_ExtensionInitializeFunction;}
	ApiVoid GetExtensionTerminateFunction() const{return m_ExtensionTerminateFunction;}
	virtual bool Unload();
	virtual bool Load();
protected:
	BaseExtensionDll(const char* absolutePath);
	BaseExtensionDll(const char* name, const char* path);
	virtual bool DoLoad();
	virtual void Reset()
	{
		BaseDll::Reset();
		m_ExtensionInitializeFunction = NULL;
		m_ExtensionTerminateFunction = NULL;
	}
	bool AdditionalUnload();
	ApiVoid m_ExtensionInitializeFunction;
	ApiVoid m_ExtensionTerminateFunction;
};

class TU_API ExtensionDll : public BaseExtensionDll
{
public:
	virtual unsigned int GetValidExtensionCode() const = 0;
	virtual bool isCustomExtension() const{return true;}
	ApiGetUInt GetExtensionCodeFunction() const{return m_ExtensionCodeFunction;}
	const unsigned int& GetExtensionCode() const{return m_extensionCode;}
	ApiFillString GetExtensionMenuFunction() const{return m_ExtensionMenuFunction;}
	ApiUShortCWnd GetExtensionCommandFunction() const{return m_ExtensionCommandFunction;}
	ApiIntInt GetMoveWindowsFunction() const{return m_MoveWindowsFunction;}
	void GetExtensionMenu(std::string& menu) const{if(m_ExtensionMenuFunction)m_ExtensionMenuFunction(menu);}
	void ExecuteCommand(unsigned short commandId, CWnd* takionExtensionWindow) const{if(m_ExtensionCommandFunction)m_ExtensionCommandFunction(commandId, takionExtensionWindow);}
	void MoveWindows(int dx, int dy){if(m_MoveWindowsFunction)m_MoveWindowsFunction(dx, dy);}

	ApiCreteTool GetCreateExtensionToolFunction() const{return m_CreateExtensionToolFunction;}
	CWnd* CreateExtensionTool(const char* id, const CBitmap* bitmap, unsigned int workspace, bool pinned){return m_CreateExtensionToolFunction ? m_CreateExtensionToolFunction(id, bitmap, workspace, pinned) : NULL;}

	ApiUCharUCharString GetExtensionKeyStrokeAndCommandFunction() const{return m_ExtensionKeyStrokeAndCommandFunction;}
	ApiStringBoolBool GetExtensionSymbolEnteredInMmBoxFunction() const{return m_ExtensionSymbolEnteredInMmBoxFunction;}
	ApiStringSecurityBoolUInt GetExtensionSecurityRefreshedFunction() const{return m_ExtensionSecurityRefreshedFunction;}
	ApiStringSecurityBoolUInt GetExtensionActiveMmBoxChangedFunction() const{return m_ExtensionActiveMmBoxChangedFunction;}

	ApiUIntBool GetExtensionMainThreadIdleStateFunction() const{return m_ExtensionMainThreadIdleStateFunction;}
	ApiVoid GetExtensionMainThreadAvailableDataProcessedFunction() const{return m_ExtensionMainThreadAvailableDataProcessedFunction;}

	ApiAccount GetExtensionCurrentAccountSetFunction() const{return  m_ExtensionCurrentAccountSetFunction;}
	ApiBool GetExtensionAppActivatedFunction() const{return m_ExtensionAppActivated;}
	ApiVoid GetExtensionOpenLayoutFunction() const{return m_ExtensionOpenLayout;}
	ApiVoid GetExtensionSaveLayoutFunction() const{return m_ExtensionSaveLayout;}
	ApiVoid GetExtensionSaveAsLayoutFunction() const{return m_ExtensionSaveAsLayout;}
	ApiVoid GetExtensionRestoreLayoutFunction() const{return m_ExtensionRestoreLayout;}
	ApiGetString GetExtensionGetLayoutFilePathFunction() const{return m_ExtensionGetLayoutFilePath;}

	ApiUCharMessageBool GetExtensionMessageReportFunction() const{return m_ExtensionMessageReport;}

	void CallKeyStrokeAndCommand(unsigned char ascii, unsigned char modifier, bool repeat, const char* commandName, unsigned int commandExtensionCode, unsigned int commandUserExtensionCode) const{if(m_ExtensionKeyStrokeAndCommandFunction)m_ExtensionKeyStrokeAndCommandFunction(ascii, modifier, repeat, commandName, commandExtensionCode, commandUserExtensionCode);}
	void CallSymbolEnteredInMmBox(const char* symbol, bool valid, bool fromKeyboard, unsigned int ordinal) const{if(m_ExtensionSymbolEnteredInMmBoxFunction)m_ExtensionSymbolEnteredInMmBoxFunction(symbol, valid, fromKeyboard, ordinal);}
	void CallSecurityRefreshed(const char* symbol, const Security* security, bool wasLoaded, unsigned int ordinal) const{if(m_ExtensionSecurityRefreshedFunction)m_ExtensionSecurityRefreshedFunction(symbol, security, wasLoaded, ordinal);}
	void CallActiveMmBoxChanged(const char* symbol, const Security* security, bool wasLoaded, unsigned int ordinal) const{if(m_ExtensionActiveMmBoxChangedFunction)m_ExtensionActiveMmBoxChangedFunction(symbol, security, wasLoaded, ordinal);}

	bool CallMainThreadIdleState(unsigned int idleCount, bool takionIdleDone) const{return m_ExtensionMainThreadIdleStateFunction && m_ExtensionMainThreadIdleStateFunction(idleCount, takionIdleDone);}
	void CallMainThreadAvailableDataProcessed() const{if(m_ExtensionMainThreadAvailableDataProcessedFunction)m_ExtensionMainThreadAvailableDataProcessedFunction();}

	void CallCurrentAccountSet(Account* account) const{if(m_ExtensionCurrentAccountSetFunction)m_ExtensionCurrentAccountSetFunction(account);}
	void CallAppActivated(bool appActivated) const{if(m_ExtensionAppActivated)m_ExtensionAppActivated(appActivated);}
	void CallOpenLayout() const{if(m_ExtensionOpenLayout)m_ExtensionOpenLayout();}
	void CallSaveLayout() const{if(m_ExtensionSaveLayout)m_ExtensionSaveLayout();}
	void CallSaveAsLayout() const{if(m_ExtensionSaveAsLayout)m_ExtensionSaveAsLayout();}
	void CallRestoreLayout() const{if(m_ExtensionRestoreLayout)m_ExtensionRestoreLayout();}
	const char* CallGetLayoutFilePath(){return m_ExtensionGetLayoutFilePath ? m_ExtensionGetLayoutFilePath() : NULL;}
	void CallMessageReportFunction(unsigned char connectionType, const Message* message, bool outgoing) const{if(m_ExtensionMessageReport)m_ExtensionMessageReport(connectionType, message, outgoing);}
protected:
	ExtensionDll(const char* absolutePath):
		BaseExtensionDll(absolutePath)
	{
		AdditionalReset();
		AdditionalResetValues();
	}

	ExtensionDll(const char* name, const char* path):
		BaseExtensionDll(name, path)
	{
		AdditionalReset();
		AdditionalResetValues();
	}
	
	virtual bool DoLoad();

	virtual void Reset()
	{
		BaseExtensionDll::Reset();
		AdditionalReset();
	}
	virtual void ResetValues()
	{
		BaseExtensionDll::ResetValues();
		AdditionalResetValues();
	}

	void AdditionalReset()
	{
		m_ExtensionCodeFunction = NULL;
		m_ExtensionMenuFunction = NULL;
		m_ExtensionCommandFunction = NULL;
		m_MoveWindowsFunction = NULL;
		m_CreateExtensionToolFunction = NULL;

		m_ExtensionKeyStrokeAndCommandFunction = NULL;
		m_ExtensionSymbolEnteredInMmBoxFunction = NULL;
		m_ExtensionSecurityRefreshedFunction = NULL;
		m_ExtensionActiveMmBoxChangedFunction = NULL;
		m_ExtensionCurrentAccountSetFunction = NULL;
		m_ExtensionAppActivated = NULL;
		m_ExtensionOpenLayout = NULL;
		m_ExtensionSaveLayout = NULL;
		m_ExtensionSaveAsLayout = NULL;
		m_ExtensionRestoreLayout = NULL;
		m_ExtensionGetLayoutFilePath = NULL;
		m_ExtensionMessageReport = NULL;
		m_ExtensionMainThreadIdleStateFunction = NULL;
		m_ExtensionMainThreadAvailableDataProcessedFunction = NULL;
	}

	void AdditionalResetValues()
	{
		m_extensionCode = 0;
	}

	ApiGetUInt m_ExtensionCodeFunction;
	ApiFillString m_ExtensionMenuFunction;
	ApiUShortCWnd m_ExtensionCommandFunction;
	ApiIntInt m_MoveWindowsFunction;
	ApiCreteTool m_CreateExtensionToolFunction;
	ApiUCharUCharString m_ExtensionKeyStrokeAndCommandFunction;
	ApiStringBoolBool m_ExtensionSymbolEnteredInMmBoxFunction;
	ApiStringSecurityBoolUInt m_ExtensionSecurityRefreshedFunction;
	ApiStringSecurityBoolUInt m_ExtensionActiveMmBoxChangedFunction;
	ApiAccount m_ExtensionCurrentAccountSetFunction;
	ApiBool m_ExtensionAppActivated;
	ApiVoid m_ExtensionOpenLayout;
	ApiVoid m_ExtensionSaveLayout;
	ApiVoid m_ExtensionSaveAsLayout;
	ApiVoid m_ExtensionRestoreLayout;
	ApiGetString m_ExtensionGetLayoutFilePath;
	ApiUIntBool m_ExtensionMainThreadIdleStateFunction;
	ApiVoid m_ExtensionMainThreadAvailableDataProcessedFunction;
	ApiUCharMessageBool m_ExtensionMessageReport;

	unsigned int m_extensionCode;
};

class ExecuteCommandInfo
{
public:
	ExecuteCommandInfo(const char* commandName, bool post):
		m_commandName(commandName),
		m_post(post)
	{}
	const std::string& GetCommandName() const{return m_commandName;}
	bool isPost() const{return m_post;}
protected:
	std::string m_commandName;
	bool m_post;
};

class ExecuteCommandForSecurityInfo : public ExecuteCommandInfo
{
public:
	ExecuteCommandForSecurityInfo(const char* commandName, bool post, const Security* security, Account* account, const Position* position, unsigned int tierSize, int count, bool closeout, bool closeOnly, bool passiveOnly):
		ExecuteCommandInfo(commandName, post),
		m_security(security),
		m_account(account),
		m_position(position),
		m_tierSize(tierSize),
		m_count(count),
		m_closeout(closeout),
		m_closeOnly(closeOnly),
		m_passiveOnly(passiveOnly)
	{}
	const Security* GetSecurity() const{return m_security;}
	Account* GetAccount() const{return m_account;}
//	Account* GetAccount(){return m_account;}
	const Position* GetPosition() const{return m_position;}
	unsigned int GetTierSize() const{return m_tierSize;}
	int GetCount() const{return m_count;}
	bool isCloseout() const{return m_closeout;}
	bool isCloseOnly() const{return m_closeOnly;}
	bool isPassiveOnly() const{return m_passiveOnly;}
protected:
	const Security* m_security;
	Account* m_account;
	const Position* m_position;
	unsigned int m_tierSize;
	int m_count;
	bool m_closeout;
	bool m_closeOnly;
	bool m_passiveOnly;
};

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef FIRM_VALUES
FirmPosition* WINAPI TU_GetNextFirmPosition(TakionIterator* iterator);
//For both AccountAggregator::CreateSupervisorUntradeablSymbolIterator and AccountAggregator::CreateUntradeablSymbolIterator
const unsigned __int64* WINAPI TU_GetNextUntradeableSymbol(TakionIterator* iterator, unsigned int* count = NULL);
#endif

void WINAPI TU_ResetIterator(TakionIterator* iterator);
void WINAPI TU_DeleteIterator(TakionIterator* iterator);
const Quote* WINAPI TU_GetNextQuote(TakionIterator* iterator);

TakionIterator* WINAPI TU_CreateMarketCenterIterator();
const MarketCenter* WINAPI TU_GetNextMarketCenter(TakionIterator* iterator);
const MarketCenter* WINAPI TU_FindMarketCenter(unsigned int marketCenterName);
unsigned int WINAPI TU_GetMarketCenterCount();
const MarketCenter* WINAPI TU_FindOptionMarketCenter(unsigned int marketCenterName);
TakionIterator* WINAPI TU_CreateOptionMarketCenterIterator();
const MarketCenter* WINAPI TU_GetNextOptionMarketCenter(TakionIterator* iterator);
unsigned int WINAPI TU_GetOptionMarketCenterCount();
unsigned int WINAPI TU_GetAllMarketCenterFilter();
const MarketCenter* WINAPI TU_GetMarketCenter(unsigned char id);
const MarketCenter* WINAPI TU_GetMarketCenterByIndex(unsigned char index);

TakionIterator* WINAPI TU_CreateEcnIterator();
TakionIterator* WINAPI TU_CreateDirectEcnIterator();
const Ecn* WINAPI TU_GetNextEcn(TakionIterator* iterator);
const Ecn* WINAPI TU_FindEcn(unsigned int ecnName);
unsigned int WINAPI TU_GetDirectEcnCount();
unsigned int WINAPI TU_GetAllDirectEcnFilter();
unsigned int WINAPI TU_GetAllAttributedEcnFilter();
const Ecn* WINAPI TU_GetEcn(unsigned char id);
const Ecn* WINAPI TU_GetDirectEcnByIndex(unsigned char index);

Order* WINAPI TU_GetNextOrder(TakionIterator* iterator);
Order* WINAPI TU_GetNextOrderWithId(TakionIterator* iterator, const unsigned int*& id);
Execution* WINAPI TU_GetNextExecution(TakionIterator* iterator);
Position* WINAPI TU_GetNextPosition(TakionIterator* iterator);

const Quote* WINAPI TU_GetNextBookQuote(TakionIterator* bookIterator);

#ifndef TAKION_NO_OPTIONS
//Security* WINAPI TU_GetNextOption(TakionIterator* optionIterator);
Security* WINAPI TU_GetNextUnderlierOption(TakionIterator* iterator);
unsigned __int64 WINAPI TU_ParseOptionBlockWithSuffixSeparate(const char* symbol, unsigned __int64& rootSymbol, unsigned __int64& underlierSymbol, unsigned __int64& optionKey, unsigned char& suffix);
unsigned __int64 WINAPI TU_ParseOptionBlock(const char* symbol, unsigned __int64& rootSymbol);
Position* WINAPI TU_GetNextOptionPosition(TakionIterator* iterator);
#endif

const SignedPrice& WINAPI TU_GetSignedPriceZero();
const Price& WINAPI TU_GetPriceZero();
const PriceQuantity& WINAPI TU_GetPriceQuantityZero();
const Money& WINAPI TU_GetMoneyZero();
const MoneyQuantity& WINAPI TU_GetMoneyQuantityZero();

const SignedPrice& WINAPI TU_GetSignedPriceOnePenny();
const Price& WINAPI TU_GetPriceOnePenny();

bool WINAPI TU_GetIsoSnapshot(bool bid, TakionIterator* iterator, const Price& orderPrice, std::string& info, Price& topPrice, bool stopIfOrderIsNotInside);//should be called only when the security is locked for info
bool WINAPI TU_GetTopLevelInfoAsString(TakionIterator* iterator, const Price& orderPrice, std::string& info, Price& topPrice);//should be called only when the security is locked for info
void WINAPI TU_GetMmidSizeAsString(const Quote* quote, std::string& info);//should be called only when the security is locked for info

const MarketCenter* const* WINAPI TU_GetProtectedMarketCenterIds();
const Ecn* const* WINAPI TU_GetProtectedEcnBookIds();
const Ecn* const* WINAPI TU_GetAttributedEcnBookIds();
const Ecn* const* WINAPI TU_GetEcnBookIds();

TakionIterator* WINAPI TU_CreateMultiBookIterator(bool bid, bool aggregated, bool sortBySize, unsigned int bookFilter = ((1 << ECNBOOK_COUNT) - 1) & ~(1 << BOOK_LEVEL2), const Security* stock = NULL);
//const Quote* WINAPI TU_GetMultiBookNextQuote(TakionIterator* multiBookIterator);
void WINAPI TU_MultiBookIteratorSetSecurity(TakionIterator* multiBookIterator, const Security* stock);
void WINAPI TU_MultiBookIteratorSetAggregated(TakionIterator* multiBookIterator, bool aggregated);
bool WINAPI TU_MultiBookIteratorSetBookFilter(TakionIterator* multiBookIterator, unsigned int bookFilter);
bool WINAPI TU_MultiBookIteratorSetSortBySize(TakionIterator* multiBookIterator, bool sortBySize);
const Quote* WINAPI TU_MultiBookIteratorGetNextQuoteAndBook(TakionIterator* multiBookIterator, unsigned char& bookId);

TakionIterator* WINAPI TU_CreateMmAggregatedIterator(bool bid, bool sortBySize, bool hideSlowQuotes, const unsigned int* lineCount, unsigned int exchangeMask, unsigned int attributionMask, const unsigned char* bookSortRank, const Security* stock = NULL, bool oddSize = false);
//const Quote* WINAPI TU_GetMmAggregatedNextQuote(TakionIterator* mmAggregatedIterator);
void WINAPI TU_MmAggregatedIteratorSetSecurity(TakionIterator* mmAggregatedIterator, const Security* stock);
bool WINAPI TU_MmAggregatedIteratorSecurityRefreshed(TakionIterator* mmAggregatedIterator, const Security* stock);
bool WINAPI TU_MmAggregatedIteratorSetBookFilter(TakionIterator* mmAggregatedIterator, const unsigned int* lineCount, unsigned int exchangeMask);
bool WINAPI TU_MmAggregatedIteratorSetAttributionMask(TakionIterator* multiBookIterator, unsigned int attributionMask);
bool WINAPI TU_MmAggregatedIteratorSetSortBySize(TakionIterator* mmAggregatedIterator, bool sortBySize);
bool WINAPI TU_MmAggregatedIteratorSetHideSlowQuotes(TakionIterator* multiBookIterator, bool hide);
bool WINAPI TU_MmAggregatedIteratorSetBookSortRank(TakionIterator* mmAggregatedIterator, const unsigned char* bookSortRank);

TakionIterator* WINAPI TU_CreateMultiPrintIterator(unsigned int printFilter = AllMarketCenterFilter, bool printShowOddLot = true, unsigned int bookFilter = ((1 << ECNBOOK_COUNT) - 1) & ~(1 << BOOK_LEVEL2), bool ecnExecShowOddLot = true, const Security* stock = NULL);
const Trade* WINAPI TU_GetMultiPrintNextTrade(TakionIterator* multiPrintIterator);
void WINAPI TU_MultiPrintIteratorSetSecurity(TakionIterator* multiPrintIterator, const Security* stock);
bool WINAPI TU_MultiPrintIteratorSetBookFilter(TakionIterator* multiPrintIterator, unsigned int bookFilter, bool ecnExecShowOddLot);
bool WINAPI TU_MultiPrintIteratorSetPrintFilter(TakionIterator* multiPrintIterator, unsigned int printFilter, bool printShowOddLot);

unsigned short WINAPI TU_GetUserOrderTypeCount();
const std::string& WINAPI TU_GetUserOrderType(unsigned short i);
unsigned short WINAPI TU_AddUserOrderType(const char* orderTypeName);
TakionIterator* WINAPI TU_CreateUserOrderTypeIterator();
const std::string* WINAPI TU_GetNextUserOrderType(TakionIterator* iterator);

TakionIterator* WINAPI TU_CreatePositionPendingOrderIterator(const Position* position, bool buy);
TakionIterator* WINAPI TU_CreatePositionBuyPendingOrderIterator(const Position* position);
TakionIterator* WINAPI TU_CreatePositionSellPendingOrderIterator(const Position* position);
const Order* WINAPI TU_GetNextPositionPendingOrder(TakionIterator* iterator, bool buy);
const Order* WINAPI TU_GetNextPositionBuyPendingOrder(TakionIterator* iterator);
const Order* WINAPI TU_GetNextPositionSellPendingOrder(TakionIterator* iterator);

unsigned int WINAPI TU_GetEntitlementBookFilter();

void WINAPI TU_SetMainWnd(HWND hwnd);
bool WINAPI TU_ExecuteCommand(const char* commandName, bool post);
bool WINAPI TU_ExecuteCommandForSecurity(const char* commandName, bool post, const Security* security, Account* account, const Position* position, unsigned int tierSize, int count, bool closeout, bool closeOnly, bool passiveOnly);

const std::string& WINAPI TU_GetTriggerTypeStr(unsigned char triggerType);

enum PriceBaseEnum : unsigned char
{
	PB_OPPOSITE_SIDE,
	PB_SAME_SIDE,
	PB_CLOSE_PRICE,
	PB_TODAYS_CLOSE_PRICE,
	PB_NYSE_OPPOSITE_SIDE,
	PB_NYSE_SAME_SIDE,
	PB_AVG_POSITION_PRICE,
	PB_ECN_OPPOSITE_SIDE,
	PB_ECN_SAME_SIDE,
	PB_LAST_PRINT,

	PB_Count
};

void WINAPI TU_GetPriceByPriceBase(unsigned char priceBase, SignedPrice& price, const Security* security, const Price& positionPrice, const Price& insideBid, const Price& insideAsk, const Price& ecnPrice, char side);
const char* WINAPI TU_GetPriceBaseName(unsigned char priceBase);

void WINAPI TU_GetOrderErrorMessage(unsigned char errorCode, std::string& errorMessage);
void WINAPI TU_GetCancelErrorMessage(unsigned char errorCode, std::string& errorMessage);

#ifdef __cplusplus
}
#endif

enum TriggerType : unsigned char
{
	TT_SECURITY_PRINT,
	TT_SECURITY_BID,
	TT_SECURITY_ASK,

	TT_SECURITY_PQOPEN,
	TT_SECURITY_TCLOSE,

	TT_SECURITY_BOOK_BID_SIZE_ACC_GREATER,
	TT_SECURITY_BOOK_ASK_SIZE_ACC_GREATER,
	TT_SECURITY_BOOK_ANY_SIZE_ACC_GREATER,
	TT_SECURITY_BOOK_BID_SIZE_ACC_LESS,
	TT_SECURITY_BOOK_ASK_SIZE_ACC_LESS,
	TT_SECURITY_BOOK_ANY_SIZE_ACC_LESS,

	TT_SECURITY_BOOK_BID_SIZE_QUOTE_GREATER,
	TT_SECURITY_BOOK_ASK_SIZE_QUOTE_GREATER,
	TT_SECURITY_BOOK_ANY_SIZE_QUOTE_GREATER,
	TT_SECURITY_BOOK_BID_SIZE_QUOTE_LESS,
	TT_SECURITY_BOOK_ASK_SIZE_QUOTE_LESS,
	TT_SECURITY_BOOK_ANY_SIZE_QUOTE_LESS,

	TT_POSITION_LONG_GREATER,
	TT_POSITION_SHORT_GREATER,
	TT_POSITION_ANY_GREATER,
	TT_POSITION_LONG_LESS,
	TT_POSITION_SHORT_LESS,
	TT_POSITION_ANY_LESS,

	TT_IMB_RI_POSITIVE_GREATER,
	TT_IMB_RI_NEGATIVE_GREATER,
	TT_IMB_RI_ANY_GREATER,
	TT_IMB_RI_POSITIVE_LESS,
	TT_IMB_RI_NEGATIVE_LESS,
	TT_IMB_RI_ANY_LESS,

	TT_IMB_NY_INF_POSITIVE_GREATER,
	TT_IMB_NY_INF_NEGATIVE_GREATER,
	TT_IMB_NY_INF_ANY_GREATER,
	TT_IMB_NY_INF_POSITIVE_LESS,
	TT_IMB_NY_INF_NEGATIVE_LESS,
	TT_IMB_NY_INF_ANY_LESS,

	TT_Count
};

enum AlertType : unsigned char
{
	AT_SECURITY_PRINT,
	AT_SECURITY_BID,
	AT_SECURITY_ASK,
	AT_SECURITY_VOLUME,
	AT_TIME,
	AT_INDEX,

	AT_COUNT
};

enum AlertStatus : unsigned char
{
	AS_LIVE,
	AS_TRIGGERED,

	AS_COUNT
};

class TU_API Alert
{
public:
	virtual ~Alert(){}
//	virtual const char* GetSymbol() const = 0;
	virtual void DisconnectMarketSorter(){}
	virtual AlertType GetAlertType() const = 0;
	virtual bool isValid() const{return false;}
	virtual __int64 GetValue() const = 0;
	virtual __int64 GetValueFrom() const{return 0;}
	virtual void SetValue(__int64 value) = 0;
	virtual void SetValueFrom(__int64 value){}
	virtual unsigned int GetDateTriggered() const{return 0;}
	virtual bool SetDateTriggered(unsigned int dateTriggered){return false;}
	
	const unsigned int& GetExpirationDate() const{return m_expirationDate;}
	bool SetExpirationDate(unsigned int date){if(m_expirationDate != date){m_expirationDate = date; return true;} return false;}

	const unsigned int& GetTimeTriggered() const{return m_timeTriggered;}
	bool SetTimeTriggered(unsigned int t){if(m_timeTriggered != t){m_timeTriggered = t; return true;} return false;}

	const unsigned int& GetDateCreated() const{return m_dateCreated;}
	bool SetDateCreated(unsigned int d){if(m_dateCreated != d){m_dateCreated = d; return true;} return false;}

	const unsigned int& GetTimeCreated() const{return m_timeCreated;}
	bool SetTimeCreated(unsigned int t){if(m_timeCreated != t){m_timeCreated = t; return true;} return false;}

	const COLORREF& GetColor() const{return m_color;}
	bool SetColor(COLORREF color){if(m_color != color){m_color = color; return true;} return false;}

	const std::string& GetSymbol() const{return m_symbol;}

	const std::string& GetNote() const{return m_note;}
	bool SetNote(const std::string& note){if(m_note != note){m_note = note; return true;} return false;}

	bool operator==(const Alert& other) const
	{
		return m_symbol == other.m_symbol
			&& GetAlertType() == other.GetAlertType()
			&& GetValue() == other.GetValue()
			&& m_timeTriggered < other.m_timeTriggered;
	}
	bool operator<(const Alert& other) const
	{
		return m_symbol != other.m_symbol ? m_symbol < other.m_symbol:
			GetAlertType() != other.GetAlertType() ? GetAlertType() < other.GetAlertType():
			GetValue() != other.GetValue() ? GetValue() < other.GetValue():
			m_timeTriggered < other.m_timeTriggered;
	}
	bool isSame(const Alert& other) const
	{
		return operator==(other) && m_color == other.m_color && m_expirationDate == other.m_expirationDate && m_note == other.m_note && m_timeTriggered == other.m_timeTriggered;
	}
	virtual void GetValueAsString(std::string& str) const{}
	virtual void GetValueFromAsString(std::string& str) const{}
	static void GetPriceFromValue(Price& price, const __int64& value)
	{
		price.SetValue((unsigned int)(value >> 32), (unsigned int)(value & 0xFFFFFFFF));
	}
	static __int64 GetValueFromPrice(const Price& price){return ((unsigned __int64)price.GetDollars() << 32) | (unsigned __int64)price.GetDollarFraction();}

	static void GetSignedPriceFromValue(SignedPrice& price, __int64 value)
	{
		if(value < 0)
		{
			value = -value;
			price.SetValue((int)(value >> 32), (int)(value & 0xFFFFFFFF));
			price = -price;
		}
		else
		{
			price.SetValue((int)(value >> 32), (int)(value & 0xFFFFFFFF));
		}
	}
	static __int64 GetValueFromSignedPrice(const SignedPrice& price)
	{
		int dollars = price.GetDollars();
		int fraction = price.GetDollarFraction();
		bool negative = dollars < 0 || fraction < 0;
		__int64 ret = (unsigned __int64)price.GetDollars() << 32;
		if(negative)
		{
			ret |= (unsigned __int64)((unsigned int)-fraction);
			ret = -ret;
//			ret |= 1ui64 << 63;
		}
		else
		{
			ret |= fraction;
		}
		return ret;//((unsigned __int64)price.GetDollars() << 32) | (unsigned __int64)((unsigned int)price.GetDollarFraction() & ~(1 << 31));
	}
	virtual bool Initialize(){return false;}
	bool isInitialized() const{return m_initialized;}
	void SetInitialized(bool initialized){m_initialized = initialized;}
	virtual const Price* GetPrice() const{return NULL;}
	virtual const Price* GetPriceFrom() const{return NULL;}
	virtual const unsigned __int64* GetVolumePtr() const{return NULL;}
	virtual const unsigned int* GetTimePtr() const{return NULL;}
	virtual const SignedPrice* GetIndexValue() const{return NULL;}
	virtual const SignedPrice* GetIndexValueFrom() const{return NULL;}
	const Price& GetPriceOrZero() const{const Price* price = GetPrice(); return price ? *price : TU_GetPriceZero();}
	const Price& GetPriceFromOrZero() const{const Price* price = GetPriceFrom(); return price ? *price : TU_GetPriceZero();}
	const unsigned __int64& GetVolumeOrZero() const{const unsigned __int64* volume = GetVolumePtr(); return volume ? *volume : volumeZero;}
	const unsigned int& GetTimeOrZero() const{const unsigned int* time = GetTimePtr(); return time ? *time : timeZero;}
	const SignedPrice& GetIndexValueOrZero() const{const SignedPrice* price = GetIndexValue(); return price ? *price : TU_GetSignedPriceZero();}
	const SignedPrice& GetIndexValueFromOrZero() const{const SignedPrice* price = GetIndexValueFrom(); return price ? *price : TU_GetSignedPriceZero();}
protected:
	Alert(const char* symbol,
		const char* note,
		unsigned int timeTriggered,
		unsigned int dateCreated,
		unsigned int timeCreated,
		bool initialized,
		COLORREF color = 255,
		unsigned int expirationDate = 0):
		m_symbol(symbol),
		m_note(note),
		m_color(color),
		m_expirationDate(expirationDate),
		m_timeTriggered(timeTriggered),
		m_dateCreated(dateCreated),
		m_timeCreated(timeCreated),
		m_initialized(initialized)
	{}
	std::string m_symbol;
	std::string m_note;
	COLORREF m_color;
	unsigned int m_expirationDate;
	unsigned int m_timeTriggered;
	unsigned int m_dateCreated;
	unsigned int m_timeCreated;
	bool m_initialized;
	static const unsigned __int64 volumeZero;
	static const unsigned int timeZero;
//	bool m_triggered;
};

class TU_API AlertFinder : public Alert
{
public:
	AlertFinder(const Alert& alert):
		Alert(alert),
		m_value(alert.GetValue()),
		m_type(alert.GetAlertType())
	{
	}
	AlertFinder(const char* symbol,
		const char* note,
		unsigned int timeTriggered,
		unsigned int dateCreated,
		unsigned int timeCreated,
		__int64 value,
		bool initialized,
		unsigned char type,
		COLORREF color = 255,
		unsigned int expirationDate = 0):
		Alert(symbol,
			note,
			timeTriggered,
			dateCreated,
			timeCreated,
			initialized,
			color,
			expirationDate),
		m_value(value),
		m_type((AlertType)type)
	{
	}
	virtual AlertType GetAlertType() const{return m_type;}
	virtual __int64 GetValue() const{return m_value;}
	virtual void SetValue(__int64 value){m_value = value;}
	void SetType(unsigned char type){m_type = (AlertType)type;}
	void SetSymbol(const std::string& symbol){m_symbol = symbol;}
	void ValueToStr(std::string& str, __int64 value) const
	{
		switch(m_type)
		{
			case AT_SECURITY_PRINT:
			case AT_SECURITY_BID:
			case AT_SECURITY_ASK:
			{
				Price price;
				GetPriceFromValue(price, value);
				TU_PriceToStr(str, price, 3);//, true, '\0', true);
			}
			break;

			case AT_SECURITY_VOLUME:
			{
				char num[33];
				str += U_UInt64ToStrWithCommas(value, num, sizeof(num));
			}
			break;

			case AT_TIME:
			U_AppendMillisecond(str, (unsigned int)value, false);
			break;

			case AT_INDEX:
			{
				SignedPrice price;
				GetSignedPriceFromValue(price, value);
				TU_SignedPriceToStr(str, price, 3);//, true, '\0', true);
			}
			break;
		}
	}
	bool GetPriceValue(Price& price) const
	{
		switch(m_type)
		{
			case AT_SECURITY_PRINT:
			case AT_SECURITY_BID:
			case AT_SECURITY_ASK:
			GetPriceFromValue(price, m_value);
			return true;

		}
		return false;
	}

	bool GetVolumeValue(unsigned __int64& volume) const
	{
		switch(m_type)
		{
			case AT_SECURITY_VOLUME:
			case AT_TIME:
			volume = m_value;
			return true;
		}
		return false;
	}

	bool GetIndexValue(SignedPrice& price) const
	{
		switch(m_type)
		{
			case AT_INDEX:
			GetSignedPriceFromValue(price, m_value);
			return true;
		}
		return false;
	}
	virtual void GetValueAsString(std::string& str) const{ValueToStr(str, m_value);}
//	virtual void GetValueFromAsString(std::string& str) const{ValueToStr(str, GetValueFrom());}
protected:
	__int64 m_value;
	AlertType m_type;
};

enum ValueType : unsigned char
{
	NVT_SECURITY,
	NVT_SECURITY_L2,
	NVT_POSITION,
	NVT_ACCOUNT,
	NVT_INDEX,
	NVT_MARKET,

	NVT_COUNT
};

class NamedValueCollection;

class TU_API NamedValue
{
public:
	virtual ~NamedValue(){}
//	CWnd* GetWnd() const{return m_wnd;}
	void SetTop(int top)
	{
		if(m_rectValue.top != top)
		{
			m_rectName.top = m_rectValue.top = m_rectNameText.top = m_rectValueText.top = top;
			m_rectName.bottom = m_rectValue.bottom = m_rectNameText.bottom = m_rectValueText.bottom = m_rectName.top + m_height;
		}
	}
	void SetHeight(int height)
	{
		if(m_height != height)
		{
			m_height = height;
			m_rectName.bottom = m_rectValue.bottom = m_rectNameText.bottom = m_rectValueText.bottom = m_rectName.top + m_height;
		}
	}
	void SetValueLeft(int left){m_rectValue.left = m_rectValueText.left = left;}
	void SetGap(int gap)
	{
		if(m_gap != gap)
		{
			m_gap = gap;
			m_rectName.left = m_rectValue.right + m_gap;
			if(m_rectName.left > m_rectName.right)
			{
				m_rectName.left = m_rectName.right;
			}
			m_rectNameText.left = m_rectName.left + m_nameOffset;
			if(m_rectNameText.left > m_rectNameText.right)
			{
				m_rectNameText.left = m_rectNameText.right;
			}
		}
	}
	void SetWidth(int width)
	{
		if(m_width != width)
		{
			m_width = width;
			int right = m_rectValue.left + width;
			if(m_rectValue.right > right)
			{
				m_rectValue.right = right;
				m_rectValueText.right = right - m_valueOffset;
				if(m_rectValueText.right < m_rectValueText.left)
				{
					m_rectValueText.right = m_rectValueText.left;
				}
				m_rectName.left = m_rectName.right = m_rectValue.right + m_gap;
				if(m_rectName.left > m_rectName.right)
				{
					m_rectName.left = m_rectName.right;
				}
				m_rectNameText.left = m_rectName.left + m_nameOffset;
				if(m_rectNameText.left > m_rectNameText.right)
				{
					m_rectNameText.left = m_rectNameText.right;
				}
			}
			else
			{
				m_rectName.right = m_rectNameText.right = right;
			}
		}
	}
/////
	void SetNameLeft(int left);
	int SetNameWidth(int width);

	int GetNameWidth() const{return m_rectName.Width();}//right - m_rectName.left;}
//	void SetValueLeft(int left)
	void SetValueWidthOnly(int width)
	{
		m_rectValue.right = m_rectValue.left + width;
		m_rectValueText.right = m_rectValue.right;// - m_valueOffset;
/*
		if(m_rectValueText.right < m_rectValueText.left)
		{
			m_rectValueText.right = m_rectValueText.left;
		}

		m_rectName.left = m_rectValue.right + m_gap;
		if(m_rectName.left > m_rectName.right)
		{
			m_rectName.left = m_rectName.right;
		}
		m_rectNameText.left = m_rectName.left + m_nameOffset;
		if(m_rectNameText.left > m_rectNameText.right)
		{
			m_rectNameText.left = m_rectNameText.right;
		}
*/
	}
/////
	void SetValueWidth(int width)
	{
		if(width > m_width)
		{
			width = m_width;
		}
		m_rectValue.right = m_rectValue.left + width;
		m_rectValueText.right = m_rectValue.right - m_valueOffset;
		if(m_rectValueText.right < m_rectValueText.left)
		{
			m_rectValueText.right = m_rectValueText.left;
		}
		m_rectName.left = m_rectValue.right + m_gap;
		if(m_rectName.left > m_rectName.right)
		{
			m_rectName.left = m_rectName.right;
		}
		m_rectNameText.left = m_rectName.left + m_nameOffset;
		if(m_rectNameText.left > m_rectNameText.right)
		{
			m_rectNameText.left = m_rectNameText.right;
		}
	}
	int GetValueWidth() const{return m_rectValue.Width();}
	int GetValueTextWidth() const{return m_rectValueText.Width();}

	int GetGap() const{return m_gap;}
	int GetValueOffset() const{return m_valueOffset;}
	int GetNameOffset() const{return m_nameOffset;}

	void SetValueOffset(int offset)
	{
		if(m_valueOffset != offset)
		{
			m_valueOffset = offset;
			m_rectValueText.right = m_rectValue.right - m_valueOffset;
			if(m_rectValueText.right < m_rectValueText.left)
			{
				m_rectValueText.right = m_rectValueText.left;
			}
		}
	}

	void SetNameOffset(int offset);

	virtual void SetWindow(CWnd* wnd){}

	virtual void toString(std::string& str) const{}

	virtual UINT GetValueJustification() const{return DT_RIGHT;}
/*
	void Paint(CDC& dc, const RECT& rcRect)
	{
	}
*/
	const std::string& GetNameStr() const{return m_name;}
	const std::string& GetDisplayNameStr() const{return m_displayName;}
	const std::string& GetSampleStr() const{return m_sample;}
	const std::string& GetTipStr() const{return m_tip;}
	void PaintName(CDC& dc);
	void PaintValue(CDC& dc);
	void OffsetVertical(int y)
	{
		m_rectName.top += y;
		m_rectName.bottom += y;
		m_rectValue.top += y;
		m_rectValue.bottom += y;

		m_rectNameText.top += y;
		m_rectNameText.bottom += y;
		m_rectValueText.top += y;
		m_rectValueText.bottom += y;
	}
	void SetBottom(int bottom)
	{
		m_rectName.bottom = m_rectValue.bottom = m_rectNameText.bottom = m_rectValueText.bottom = bottom;
	}
	void OffsetHorizontal(int x)
	{
		m_rectName.left += x;
		m_rectName.right += x;
		m_rectValue.left += x;
		m_rectValue.right += x;

		m_rectNameText.left += x;
		m_rectNameText.right += x;
		m_rectValueText.left += x;
		m_rectValueText.right += x;
	}
	void SetTopAndHeight(int top, int height)
	{
		m_height = height;
		m_rectName.top = m_rectNameText.top = m_rectValue.top = m_rectValueText.top = top;
		m_rectName.bottom = m_rectNameText.bottom = m_rectValue.bottom = m_rectValueText.bottom = top + height;
	}
	virtual COLORREF GetBgColor() const{return 0xFFFFFFFF;}
//	virtual COLORREF GetNameColor() const{return 0xFFFFFFFF;}
	virtual COLORREF GetValueColor() const;
	virtual NamedValue* Clone() const = 0;
	void SetParent(NamedValueCollection* parent);

	bool isValid() const{return m_valid;}
	bool SetValid(bool valid);

	bool isFit() const{return m_fit;}
//	virtual bool isValuePositive() const{return false;}
//	virtual bool isValueNegative() const{return false;}
	virtual void UpdateValue(){}
	virtual void UpdateValueFirstTime(){UpdateValue();}
	const Index* GetIndex() const{return m_index;}
	const Security* GetSecurity() const{return m_security;}
	const Position* GetPosition() const{return m_position;}
	const Account* GetAccount() const{return m_account;}

	virtual const char* GetIndexSymbol() const{return NULL;}

	void SetIndex(const Index*);
	void SetSecurity(const Security*);
	void SetPosition(const Position*);
	void SetAccount(const Account*);
	ValueType GetType() const{return m_type;}
	void SetFontValue(CFont* font, unsigned int fontSize, bool fit){m_fontValue = font; m_fontValueSize = fontSize; m_fit = fit;}
	unsigned int GetFontValueSize() const{return m_fontValueSize;}
	CFont* GetFontValue() const{return m_fontValue;}

	const CRect& GetRectName() const{return m_rectName;}
	const CRect& GetRectValue() const{return m_rectValue;}
	const CRect& GetRectNameText() const{return m_rectNameText;}
	const CRect& GetRectValueText() const{return m_rectValueText;}
	int GetTop() const{return m_rectValue.top;}
	int GetBottom() const{return m_rectValue.bottom;}

	virtual bool SetShowSeconds(bool showSeconds){return false;}

	virtual bool SetDecDigits(unsigned char decDigits){return false;}
	virtual bool SetTruncate(bool truncate){return false;}
	virtual bool SetCommaPrice(bool comma){return false;}
	virtual bool SetCommaSize(bool comma){return false;}
	virtual bool SetSizeInShares(bool sizeInShares){return false;}

	virtual const unsigned char& GetDecDigits() const{return defaultDecDigits;}
	virtual const bool& isTruncate() const{return defaultTruncate;}
	virtual const bool& isCommaPrice() const{return defaultCommaPrice;}
	virtual const bool& isCommaSize() const{return defaultCommaSize;}
	virtual const bool& isSizeInShares() const{return defaultSizeInShares;}

	virtual bool DependsOnAccount() const{return m_type == NVT_ACCOUNT;}
	virtual bool DependsOnPosition() const{return m_type == NVT_POSITION;}
	virtual bool DependsOnSecurity() const{return m_type == NVT_SECURITY;}
	virtual bool DependsOnINDEX() const{return m_type == NVT_INDEX;}
	virtual bool DependsOnSecurityLevel2() const{return m_type == NVT_SECURITY_L2;}
	virtual bool DependsOnMarket() const{return m_type == NVT_SECURITY_L2;}

	virtual void SetRef(const void* ref){}

	static const unsigned char defaultDecDigits = 3;
	static const bool defaultTruncate = false;
	static const bool defaultCommaPrice = true;
	static const bool defaultCommaSize = true;
	static const bool defaultSizeInShares = true;
protected:
//	NamedValue(CWnd* wnd, const char* name, const char* sample, FontDescription& fontValueDescription, CFont* fontName, const char* displayName = NULL);
	NamedValue(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL);
/*
	void IncrementValueWidthOnly(int diff)
	{
		m_rectValue.right += diff;
		m_rectValueText.right = m_rectValue.right;// - m_valueOffset;
	}
*/
	virtual void OnParentSet(){}
	ValueType m_type;
	NamedValueCollection* m_parent;
//	CWnd* m_wnd;
	std::string m_name;
	std::string m_displayName;
	std::string m_sample;
	std::string m_tip;
	CFont* m_fontValue;
	unsigned int m_fontValueSize;
	CRect m_rectName;
	CRect m_rectValue;

	CRect m_rectNameText;
	CRect m_rectValueText;
	int m_valueOffset;
	int m_nameOffset;

	const Index* m_index;
	const Security* m_security;
	const Position* m_position;
	const Account* m_account;

	int m_width;
	int m_height;
	int m_gap;
	bool m_valid;
	bool m_fit;
};

class TU_API NamedValueCollection
{
public:
	virtual ~NamedValueCollection(){DestroyValues();}
	typedef std::vector<NamedValue*> NamedValueVector;
	typedef std::hash_set<NamedValue*> NamedValueSet;
	CWnd* GetWnd() const{return m_wnd;}
	void DestroyValues();
	virtual void ClearValues();
	virtual bool RemoveLastValues(unsigned int leaveTopValuesCount);
	virtual void Paint(CDC& dc, const RECT& rcRect) = 0;
//	void PaintNames(CDC& dc, const RECT& rcRect);
//	void PaintValues(CDC& dc, const RECT& rcRect);
	virtual void InvalidateNames() = 0;
	virtual void InvalidateValues() = 0;

	const CRect& GetRect() const{return m_rect;}
//	COLORREF GetBgColor() const{return m_bgColor;}
	COLORREF GetNameColor() const{return m_nameColor;}
	COLORREF GetValueColorNeutral() const{return m_valueColorNeutral;}
	COLORREF GetValueColorPositive() const{return m_valueColorPositive;}
	COLORREF GetValueColorNegative() const{return m_valueColorNegative;}
	COLORREF GetValueColorPositiveBg() const{return m_valueColorPositiveBg;}
	COLORREF GetValueColorNegativeBg() const{return m_valueColorNegativeBg;}
	COLORREF GetValueColorPositiveBgText() const{return m_valueColorPositiveBgText;}
	COLORREF GetValueColorNegativeBgText() const{return m_valueColorNegativeBgText;}
	COLORREF GetValueColorWarning() const{return m_valueColorWarning;}
/*
	void SetBgColor(COLORREF color)
	{
		if(m_bgColor != color)
		{
			m_bgColor = color;
			m_wnd->InvalidateRect(&m_rect, FALSE);
		}
	}
*/
	void SetNameColor(COLORREF color)
	{
		if(m_nameColor != color)
		{
			m_nameColor = color;
			InvalidateNames();
		}
	}
	void SetValueColorNeutral(COLORREF color)
	{
		if(m_valueColorNeutral != color)
		{
			m_valueColorNeutral = color;
			InvalidateValues();
		}
	}

	void SetValueColorPositive(COLORREF color)
	{
		if(m_valueColorPositive != color)
		{
			m_valueColorPositive = color;
			InvalidateValues();
		}
	}

	void SetValueColorNegative(COLORREF color)
	{
		if(m_valueColorNegative != color)
		{
			m_valueColorNegative = color;
			InvalidateValues();
		}
	}

	void SetValueColorPositiveBg(COLORREF color)
	{
		if(m_valueColorPositiveBg != color)
		{
			m_valueColorPositiveBg = color;
			InvalidateValues();
		}
	}

	void SetValueColorNegativeBg(COLORREF color)
	{
		if(m_valueColorNegativeBg != color)
		{
			m_valueColorNegativeBg = color;
			InvalidateValues();
		}
	}

	void SetValueColorPositiveBgText(COLORREF color)
	{
		if(m_valueColorPositiveBgText != color)
		{
			m_valueColorPositiveBgText = color;
			InvalidateValues();
		}
	}

	void SetValueColorNegativeBgText(COLORREF color)
	{
		if(m_valueColorNegativeBgText != color)
		{
			m_valueColorNegativeBgText = color;
			InvalidateValues();
		}
	}

	void SetValueColorWarning(COLORREF color)
	{
		if(m_valueColorWarning != color)
		{
			m_valueColorWarning = color;
			InvalidateValues();
		}
	}

	const FontDescription& GetFontDescription() const{return m_fontValueDescription;}
	void SetFontDescription(const FontDescription& fontDescription){m_fontValueDescription = fontDescription;}

	void SetFontName(CFont* font);

	virtual void AddValue(NamedValue* value);
	virtual void InsertValue(unsigned int index, NamedValue* value) = 0;
//	virtual NamedValue* RemoveValue(const std::string& name) = 0;
	NamedValue* RemoveValueAt(unsigned int at);
	void SetTop(int top, bool force = false)
	{
		if(m_rect.top != top || force)
		{
			OffsetVertical(0, top - m_rect.top);
			m_rect.top = top;
		}
	}
	void SetLeftOnly(int left, bool force = false)
	{
		if(m_rect.left != left || force)
		{
			OffsetHorizontalLeftOnly(left);
			m_rect.left = left;
		}
	}
	void SetLeft(int left, bool force = false)
	{
		if(m_rect.left != left || force)
		{
			int diff = left - m_rect.left;
			OffsetHorizontal(diff);
			m_rect.right += diff;
			m_rect.left = left;
		}
	}
	virtual void OffsetVertical(NamedValueVector::iterator it, int y){}
	virtual void OffsetVertical(unsigned int startIndex, int y){}
	virtual void OffsetHorizontal(int x){}
	virtual void OffsetHorizontalLeftOnly(int x){}
	
	const bool& isSizeInShares() const{return m_sizeInShares;}
	bool SetSizeInShares(bool sizeInShares)
	{
		if(m_sizeInShares != sizeInShares)
		{
			m_sizeInShares = sizeInShares;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetSizeInShares(m_sizeInShares);
			}
			return true;
		}
		return false;
	}

	const unsigned char& GetDecDigits() const{return m_decDigits;}
	bool SetDecDigits(unsigned char decDigits)
	{
		if(m_decDigits != decDigits)
		{
			m_decDigits = decDigits;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetDecDigits(m_decDigits);
			}
			return true;
		}
		return false;
	}

	const bool& isTruncate() const{return m_truncate;}
	bool SetTruncate(bool truncate)
	{
		if(m_truncate != truncate)
		{
			m_truncate = truncate;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetTruncate(m_truncate);
			}
			return true;
		}
		return false;
	}

	const bool& isCommaPrice() const{return m_commaPrice;}
	bool SetCommaPrice(bool comma)
	{
		if(m_commaPrice != comma)
		{
			m_commaPrice = comma;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetCommaPrice(m_commaPrice);
			}
			return true;
		}
		return false;
	}

	const bool& isCommaSize() const{return m_commaSize;}
	bool SetCommaSize(bool comma)
	{
		if(m_commaSize != comma)
		{
			m_commaSize = comma;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetCommaSize(m_commaSize);
			}
			return true;
		}
		return false;
	}

	const Security* GetSecurity() const{return m_security;}
	const Position* GetPosition() const{return m_position;}
	const Account* GetAccount() const{return m_account;}

	void SetSecurity(const Security* security)
	{
		if(m_security != security)
		{
			m_security = security;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetSecurity(security);
			}
		}
	}

	void SetAccount(const Account* account)
	{
		if(m_account != account)
		{
			m_account = account;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetAccount(account);
			}
		}
	}

	void SetPosition(const Position* position)
	{
		if(m_position != position)
		{
			m_position = position;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetPosition(position);
			}
		}
	}
	void UpdateValues()
	{
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			(*it)->UpdateValue();
		}
	}
	void UpdateAccountValues()
	{
		NamedValue* value;
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			value = *it;
			if(value->DependsOnAccount())
			{
				value->UpdateValue();
			}
		}
	}
	void UpdateValues(ValueType valueType)
	{
		NamedValueSet* valueSet = GetNamedValueSet(valueType);
		if(valueSet)
		{
			for(NamedValueSet::iterator it = valueSet->begin(), itend = valueSet->end(); it != itend; ++it)
			{
				if((*it)->GetType() == valueType)
				{
					(*it)->UpdateValue();
				}
			}
		}
	}

	void UpdateValues(const char* name)
	{
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			if(!strcmp((*it)->GetNameStr().c_str(), name))
			{
				(*it)->UpdateValue();
			}
		}
	}
	virtual void SetWidth(int width, bool force = false){}
	virtual void SetBottom(int bottom)
	{
		m_rect.bottom = bottom;
	}
	
//	virtual void SetCellHeight(int height){}
	int GetCellHeight() const{return m_rect.Height();}
	int GetLeft() const{return m_rect.left;}
	int GetTop() const{return m_rect.top;}
	int GetBottom() const{return m_rect.bottom;}
	int GetWidth() const{return m_rect.Width();}

//	int GetValueWidth() const{return m_valueWidth;}
	int GetGap() const{return m_gap;}
	int GetValueOffset() const{return m_valueOffset;}
	int GetNameOffset() const{return m_nameOffset;}

	virtual bool SetValueOffset(int offset, bool force = false)
	{
		if(m_valueOffset != offset || force)
		{
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetValueOffset(offset);
			}
			m_valueOffset = offset;
			return true;
		}
		return false;
	}

	virtual void SetNameOffset(int offset, bool force = false)
	{
		if(m_nameOffset != offset || force)
		{
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetNameOffset(offset);
			}
			m_nameOffset = offset;
		}
	}

	void SetGap(int gap)
	{
		if(m_gap != gap)
		{
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetGap(gap);
			}
			m_gap = gap;
		}
	}
	void SetRect(const RECT& rect)
	{
		SetTop(rect.top);
		SetLeft(rect.left);
		SetWidth(rect.right - rect.left);
		SetBottom(rect.bottom);
	}
/*
	bool isValid() const{return m_valid;}
	void SetValid(bool valid)
	{
		if(m_valid != valid)
		{
			m_valid = valid;
			for(NamedValueVector::iterator it = m_namedValueVector.begin(), itend = m_namedValueVector.end(); it != itend; ++it)
			{
				(*it)->SetValid(m_valid);
			}
		}
	}
*/
	NamedValueVector& GetValueVector(){return m_namedValueVector;}
	const NamedValueVector& GetValueVector() const{return m_namedValueVector;}
	NamedValueSet* GetNamedValueSet(unsigned char type){return type <= NVT_COUNT ? m_namedValueSet + type : NULL;}
	const NamedValueSet* GetNamedValueSet(unsigned char type) const{return type <= NVT_COUNT ? m_namedValueSet + type : NULL;}
	const NamedValue* GetFirstNamedValue() const{return m_namedValueVector.empty() ? NULL : m_namedValueVector[0];}
	virtual void InitNamedValue(NamedValue& value){}
	virtual UINT GetValueJustification(const NamedValue* nv) const{return nv->GetValueJustification();}
	virtual UINT GetNameJustification() const{return DT_LEFT;}
	virtual UINT GetValueVerticalJustification() const{return DT_VCENTER;}
	virtual UINT GetNameVerticalJustification() const{return DT_VCENTER;}

	virtual bool isVertical() const{return true;}
	NamedValue* GetNamedValueAt(unsigned int at){return at < (unsigned int)m_namedValueVector.size() ? m_namedValueVector[at] : NULL;}
	const NamedValue* GetNamedValueAt(unsigned int at) const{return at < (unsigned int)m_namedValueVector.size() ? m_namedValueVector[at] : NULL;}
protected:
	NamedValueCollection(CWnd* wnd,
		FontDescription& fontValueDescription,
		CFont* fontName,
		int gap,
//		int cellHeight,
		COLORREF nameColor = RGB(255, 255, 0),
		COLORREF valueColorNeutral = RGB(255, 255, 255),
		COLORREF valueColorPositive = RGB(128, 255, 128),
		COLORREF valueColorNegative = RGB(255, 128, 128),
		COLORREF valueColorPositiveBg = RGB(128, 255, 128),
		COLORREF valueColorNegativeBg = RGB(255, 128, 128),
		COLORREF valueColorPositiveBgText = RGB(0, 255, 0),
		COLORREF valueColorNegativeBgText = RGB(255, 0, 0),
		COLORREF valueColorWarning = RGB(255, 255, 0)):
		m_wnd(wnd),
//		m_bgColor(bgColor),
		m_nameColor(nameColor),
		m_valueColorNeutral(valueColorNeutral),
		m_valueColorPositive(valueColorPositive),
		m_valueColorNegative(valueColorNegative),
		m_valueColorPositiveBg(valueColorPositiveBg),
		m_valueColorNegativeBg(valueColorNegativeBg),
		m_valueColorPositiveBgText(valueColorPositiveBgText),
		m_valueColorNegativeBgText(valueColorNegativeBgText),
		m_valueColorWarning(valueColorWarning),
		m_fontValueDescription(fontValueDescription),
		m_fontName(fontName),
		m_namedValueBegin(m_namedValueVector.begin()),
		m_namedValueEnd(m_namedValueVector.end()),
		m_namedValueCount(0),
		m_rect(0, 0, 0, 0),
//		m_cellHeight(cellHeight),
		m_gap(gap),
		m_valueOffset(0),
		m_nameOffset(0),
//		m_lastCellBottom(m_rect.top),
		m_decDigits(NamedValue::defaultDecDigits),
		m_truncate(NamedValue::defaultTruncate),
		m_commaPrice(NamedValue::defaultCommaPrice),
		m_commaSize(NamedValue::defaultCommaSize),
		m_sizeInShares(NamedValue::defaultSizeInShares),
//		m_valid(false)
		m_security(NULL),
		m_position(NULL),
		m_account(NULL)
	{}

	bool AddToSet(NamedValue* nv)
	{
		unsigned char type = nv->GetType();
		if(type <= NVT_COUNT)
		{
			m_namedValueSet[type].insert(nv);
			return true;
		}
		return false;
	}
	bool RemoveFromSet(NamedValue* nv)
	{
		unsigned char type = nv->GetType();
		if(type <= NVT_COUNT)
		{
			m_namedValueSet[type].erase(nv);
			return true;
		}
		return false;
	}
	void ClearSet()
	{
		NamedValueSet* cursor = m_namedValueSet;
		for(unsigned char i = 0; i <= NVT_COUNT; ++i, ++cursor)
		{
			cursor->clear();
		}
	}

	virtual NamedValue* RemoveValue(NamedValueVector::iterator it) = 0;

	virtual void FontNameChanged(){}

	void UpdateIterators()
	{
		m_namedValueBegin = m_namedValueVector.begin();
		m_namedValueEnd = m_namedValueVector.end();
		m_namedValueCount = (unsigned int)m_namedValueVector.size();
	}

	CWnd* m_wnd;
//	COLORREF m_bgColor;
	COLORREF m_nameColor;
	COLORREF m_valueColorNeutral;
	COLORREF m_valueColorPositive;
	COLORREF m_valueColorNegative;
	COLORREF m_valueColorPositiveBg;
	COLORREF m_valueColorNegativeBg;
	COLORREF m_valueColorPositiveBgText;
	COLORREF m_valueColorNegativeBgText;
	COLORREF m_valueColorWarning;
	FontDescription m_fontValueDescription;
	CFont* m_fontName;
	NamedValueVector m_namedValueVector;
	NamedValueVector::iterator m_namedValueBegin;
	NamedValueVector::iterator m_namedValueEnd;
	unsigned int m_namedValueCount;
	NamedValueSet m_namedValueSet[NVT_COUNT + 1];
	CRect m_rect;
//	int m_cellHeight;
//	int m_valueWidth;
	int m_valueOffset;
	int m_gap;
	int m_nameOffset;
//	int m_lastCellBottom;
	unsigned char m_decDigits;
	bool m_truncate;
	bool m_commaPrice;
	bool m_commaSize;
	bool m_sizeInShares;
//	bool m_valid;
	const Security* m_security;
	const Position* m_position;
	const Account* m_account;
};

class TU_API NamedValueCollectionVertical : public NamedValueCollection
{
public:
//	NamedValueCollection(CWnd* wnd, COLORREF bgColor = 0, COLORREF nameColor = RGB(255, 255, 0), COLORREF valueColor = RGB(255, 255, 255)):
	NamedValueCollectionVertical(CWnd* wnd,
		FontDescription& fontValueDescription,
		CFont* fontName,
		int gap,
		int cellHeight,
		COLORREF nameColor = RGB(255, 255, 0),
		COLORREF valueColorNeutral = RGB(255, 255, 255),
		COLORREF valueColorPositive = RGB(128, 255, 128),
		COLORREF valueColorNegative = RGB(255, 128, 128),
		COLORREF valueColorPositiveBg = RGB(128, 255, 128),
		COLORREF valueColorNegativeBg = RGB(255, 128, 128),
		COLORREF valueColorPositiveBgText = RGB(255, 255, 255),
		COLORREF valueColorNegativeBgText = RGB(255, 255, 255)):

		NamedValueCollection(wnd,
			fontValueDescription,
			fontName,
			gap,
//			cellHeight,
			nameColor,
			valueColorNeutral,
			valueColorPositive,
			valueColorNegative,
			valueColorPositiveBg,
			valueColorNegativeBg,
			valueColorPositiveBgText,
			valueColorNegativeBgText),
		m_cellHeight(cellHeight),
		m_lastCellBottom(m_rect.top),
		m_valueWidth(0)
	{
		FontNameChanged();
	}

	virtual void InitNamedValue(NamedValue& value);
	virtual void AddValue(NamedValue* value);
	virtual void InsertValue(unsigned int index, NamedValue* value);
//	virtual NamedValue* RemoveValue(const std::string& name);
//	virtual NamedValue* RemoveValueAt(unsigned int at);

	virtual void Paint(CDC& dc, const RECT& rcRect);
	void PaintNames(CDC& dc, const RECT& rcRect);
	void PaintValues(CDC& dc, const RECT& rcRect);
	virtual void InvalidateNames();
	virtual void InvalidateValues();
	virtual void ClearValues();
	virtual bool RemoveLastValues(unsigned int leaveTopValuesCount);

	virtual void OffsetVertical(NamedValueVector::iterator it, int y)
	{
		if(it != m_namedValueEnd)
		{
			for(; it != m_namedValueEnd; ++it)
			{
				(*it)->OffsetVertical(y);
			}
			m_lastCellBottom += y;
		}
		else if(it == m_namedValueBegin)
		{
			m_lastCellBottom += y;
		}
	}
	virtual void OffsetVertical(unsigned int startIndex, int y)
	{
		if(startIndex < m_namedValueCount)
		{
			NamedValueVector::iterator it = m_namedValueBegin;
			it += startIndex;
			OffsetVertical(it, y);
		}
		else if(!startIndex)
		{
			m_lastCellBottom += y;
		}
	}
	virtual void OffsetHorizontalLeftOnly(int x)
	{
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			(*it)->SetValueLeft(x);
		}
	}
	virtual void OffsetHorizontal(int x)
	{
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			(*it)->OffsetHorizontal(x);
		}
	}
	virtual void SetWidth(int width, bool force = false)
	{
		if(m_rect.Width() != width || force)
		{
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetWidth(width);
			}
			m_rect.right = m_rect.left + width;
			if(m_valueWidth > m_rect.Width())
			{
				m_valueWidth = m_rect.Width();
			}
		}
	}

/*
	virtual void SetBottom(int bottom)
	{
		m_rect.bottom = bottom;
	}
*/
	void SetCellHeight(int height, bool force = false)
	{
		if(m_cellHeight != height || force)
		{
			int top = m_rect.top;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it, top += height)
			{
				(*it)->SetTopAndHeight(top, height);
			}
			m_cellHeight = height;
			m_lastCellBottom = m_rect.top + m_cellHeight * (int)m_namedValueCount;
		}
	}
	virtual int GetCellHeight() const{return m_cellHeight;}
	int GetValueWidth() const{return m_valueWidth;}
	void SetValueWidth(int width, bool force = false)
	{
		if(width > m_rect.Width())
		{
			width = m_rect.Width();
		}
		if(m_valueWidth != width || force)
		{
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetValueWidth(width);
			}
			m_valueWidth = width;
		}
	}
	int GetLastCellBottom() const{return m_lastCellBottom;}
protected:
	virtual NamedValue* RemoveValue(NamedValueVector::iterator it);
	virtual void FontNameChanged();
	int m_cellHeight;
	int m_lastCellBottom;
//	int m_valueOffset;
	int m_valueWidth;
};

class TU_API NamedValueCollectionHorizontal : public NamedValueCollection
{
public:
//	NamedValueCollection(CWnd* wnd, COLORREF bgColor = 0, COLORREF nameColor = RGB(255, 255, 0), COLORREF valueColor = RGB(255, 255, 255)):
	NamedValueCollectionHorizontal(CWnd* wnd,
		FontDescription& fontValueDescription,
		CFont* fontName,
		CFont* fontValue,
		unsigned int fontSize,
		bool fit,
		int gap,
//		int cellHeight,
		COLORREF nameColor = RGB(255, 255, 0),
		COLORREF valueColorNeutral = RGB(255, 255, 255),
		COLORREF valueColorPositive = RGB(128, 255, 128),
		COLORREF valueColorNegative = RGB(255, 128, 128),
		COLORREF valueColorPositiveBg = RGB(128, 255, 128),
		COLORREF valueColorNegativeBg = RGB(255, 128, 128),
		COLORREF valueColorPositiveBgText = RGB(255, 255, 255),
		COLORREF valueColorNegativeBgText = RGB(255, 255, 255)):

		NamedValueCollection(wnd,
			fontValueDescription,
			fontName,
			gap,
//			cellHeight,
			nameColor,
			valueColorNeutral,
			valueColorPositive,
			valueColorNegative,
			valueColorPositiveBg,
			valueColorNegativeBg,
			valueColorPositiveBgText,
			valueColorNegativeBgText),
		m_fontValue(fontValue),
		m_fontSize(fontSize),
		m_fit(fit)

//		m_cellHeight(cellHeight),
//		m_lastCellBottom(m_rect.top),
//		m_valueWidth(0)
	{
		FontNameChanged();
	}

	virtual bool isVertical() const{return false;}

	virtual void AddValue(NamedValue* value);
	virtual void InsertValue(unsigned int index, NamedValue* value);
//	virtual NamedValue* RemoveValue(const std::string& name);

	virtual void Paint(CDC& dc, const RECT& rcRect);
	virtual void InvalidateNames();
	virtual void InvalidateValues();
//	void PaintNames(CDC& dc, const RECT& rcRect);
//	void PaintValues(CDC& dc, const RECT& rcRect);
//	virtual void ClearValues();

	void OffsetTop(int y)
	{
		m_rect.top += y;
		m_rect.bottom += y;
		OffsetVertical(0, y);
	}

	virtual void OffsetVertical(NamedValueVector::iterator it, int y)
	{
		if(it != m_namedValueEnd)
		{
			for(; it != m_namedValueEnd; ++it)
			{
				(*it)->OffsetVertical(y);
			}
//			m_lastCellBottom += y;
		}
/*
		else if(it == m_namedValueBegin)
		{
			m_lastCellBottom += y;
		}
*/
	}
	virtual void OffsetVertical(unsigned int startIndex, int y)
	{
		if(startIndex < m_namedValueCount)
		{
			NamedValueVector::iterator it = m_namedValueBegin;
			it += startIndex;
			OffsetVertical(it, y);
		}
/*
		else if(!startIndex)
		{
			m_lastCellBottom += y;
		}
*/
	}
	virtual void OffsetHorizontal(int x)
	{
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			(*it)->OffsetHorizontal(x);
		}
	}
	virtual void OffsetHorizontalLeftOnly(int x)
	{
		//TBD
/*
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			(*it)->OffsetHorizontal(x);
		}
*/
	}
	virtual void SetWidth(int width, bool force = false)
	{
		if(m_rect.Width() != width)
		{
/*
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetWidth(width);
			}
*/
			m_rect.right = m_rect.left + width;
/*
			if(m_valueWidth > m_rect.Width())
			{
				m_valueWidth = m_rect.Width();
			}
*/
		}
	}

	virtual bool SetValueOffset(int offset, bool force = false);

	virtual void SetBottom(int bottom);
	void SetFontValue(CFont* font, unsigned int fontSize, bool fit);
	void Arrange(CDC* dc);
	virtual UINT GetValueJustification(const NamedValue* nv) const{return DT_LEFT;}
	virtual UINT GetNameJustification() const{return DT_RIGHT;}
	virtual UINT GetValueVerticalJustification() const{return DT_TOP;}
	virtual UINT GetNameVerticalJustification() const{return DT_TOP;}
protected:
	virtual NamedValue* RemoveValue(NamedValueVector::iterator it);
	virtual void FontNameChanged();
	virtual void InitNamedValue(NamedValue& value);
	CFont* m_fontValue;
	unsigned int m_fontSize;
	bool m_fit;
};

template<class T>
class NamedValueType : public NamedValue
{
public:
	typedef T VType;
	void SetValue(const T& value)
	{
		if(m_value != value)
		{
			m_value = value;
			m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
		}
	}
	const VType& GetValue() const{return m_value;}
	virtual const VType& GetObjectValue() const{return m_value;}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue(GetObjectValue());
		}
	}
protected:
	NamedValueType(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValue(type, name, sample, tip, displayName, parent)
	{}
	T m_value;
};

class TU_API NamedValueString : public NamedValueType<std::string>
{
public:
	virtual void toString(std::string& str) const{str = m_value;}
protected:
	NamedValueString(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample, tip, displayName, parent)
	{}
};

class TU_API NamedValueCharPtr : public NamedValueType<const char*>
{
public:
	virtual void toString(std::string& str) const{str = m_value;}
protected:
	NamedValueCharPtr(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample, tip, displayName, parent)
	{
		m_value = NULL;
	}
};

class TU_API NamedValueChar : public NamedValueType<char>
{
public:
	virtual void toString(std::string& str) const{str.clear(); if(m_value != m_emptyValue)U_AppendPrintableCharIfValid(str, m_value);}//if(m_value && m_value != m_emptyValue)str += m_value;}
	virtual COLORREF GetValueColor() const{return m_value == m_negativeValue ? m_parent->GetValueColorNegative() : NamedValueType::GetValueColor();}
protected:
	NamedValueChar(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, char emptyValue = '\0', char negativeValue = '\0'):
		NamedValueType(type, name, sample, tip, displayName, parent),
		m_emptyValue(emptyValue),
		m_negativeValue(negativeValue)
	{
		m_value = '\0';
	}
	char m_emptyValue;
	char m_negativeValue;
};

class TU_API NamedValueUChar : public NamedValueType<unsigned char>
{
public:
	virtual void toString(std::string& str) const;
protected:
	NamedValueUChar(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample, tip, displayName, parent)
	{
		m_value = '\0';
	}
};

class TU_API NamedValueUCharAsChar : public NamedValueUChar
{
public:
	virtual void toString(std::string& str) const;
protected:
	NamedValueUCharAsChar(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUChar(type, name, sample, tip, displayName, parent)
	{
	}
};

class TU_API NamedValueBool : public NamedValueType<bool>
{
public:
	virtual void toString(std::string& str) const;
	virtual COLORREF GetValueColor() const;
protected:
	NamedValueBool(ValueType type, const char* name, const char* sample, const char* tip, const char* yesValue = "Yes", const char* noValue = "No", bool useColor = false, bool reverse = false, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample, tip, displayName, parent),
		m_yesValue(yesValue),
		m_noValue(noValue),
		m_useColor(useColor),
		m_reverse(reverse)
	{
		m_value = false;
	}
	std::string m_yesValue;
	std::string m_noValue;
	bool m_useColor;
	bool m_reverse;
};

template<class T>
class NamedValueNumberWithComma : public NamedValueType<T>
{
public:
	NamedValueNumberWithComma(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample, tip, displayName, parent),
		m_comma(defaultCommaSize)
	{
		m_value = 0;
	}
	virtual bool SetCommaSize(bool comma)
	{
		if(m_comma != comma)
		{
			m_comma = comma;
			m_parent->GetWnd()->InvalidateRect(&m_rectValueText, FALSE);
			return true;
		}
		return false;
	}
	virtual const bool& isCommaSize() const{return m_comma;}
protected:
	bool m_comma;
};

class TU_API NamedValueUInt : public NamedValueNumberWithComma<unsigned int>
{
public:
	virtual void toString(std::string& str) const;
protected:
	NamedValueUInt(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueNumberWithComma(type, name, sample, tip, displayName, parent){}
};

class TU_API NamedValueUIntZeroEmpty : public NamedValueUInt
{
public:
	virtual void toString(std::string& str) const{if(m_value)NamedValueUInt::toString(str);}
protected:
	NamedValueUIntZeroEmpty(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(type, name, sample, tip, displayName, parent)
	{
	}
};

class TU_API ValueUIntRef : public NamedValueUInt
{
public:
	ValueUIntRef(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, const VType* ref = NULL):
		NamedValueUInt(type, name, sample, tip, displayName, parent),
		m_ref(ref),
		m_zero(0)
	{
	}
	virtual const VType& GetObjectValue() const{return m_ref ? *m_ref : m_zero;}
	virtual NamedValue* Clone() const;
	virtual void SetRef(const void* ref);
protected:
	const VType* m_ref;
	VType m_zero;
};

class TU_API ValueBoolRef : public NamedValueBool
{
public:
	ValueBoolRef(ValueType type, const char* name, const char* sample, const char* tip, const char* yesValue = "Yes", const char* noValue = "No", bool useColor = false, bool reverse = false, const char* displayName = NULL, NamedValueCollection* parent = NULL, const VType* ref = NULL):
		NamedValueBool(type, name, sample, tip, yesValue, noValue, useColor, reverse, displayName, parent),
		m_ref(ref),
		m_zero(false)
	{
	}
	virtual const VType& GetObjectValue() const{return m_ref ? *m_ref : m_zero;}
	virtual NamedValue* Clone() const;
	virtual void SetRef(const void* ref);
protected:
	const VType* m_ref;
	VType m_zero;
};

class TU_API NamedValueLoadCount : public NamedValueUInt
{
public:
	NamedValueLoadCount(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(type, name, sample, tip, displayName, parent),
		m_loadedBkColor(0xFFFFFFFF),
		m_loadedFgColor(0xFFFFFFFF),
		m_unloadedBkColor(0xFFFFFFFF),
		m_unloadedFgColor(0xFFFFFFFF),
		m_disconnectedBkColor(0xFFFFFFFF),
		m_disconnectedFgColor(0xFFFFFFFF),
		m_loaded(false),
		m_connected(false)
	{
	}
	virtual NamedValue* Clone() const;
	bool isLoaded() const{return m_loaded;}
	bool isConnected() const{return m_connected;}
	virtual COLORREF GetBgColor() const
	{
		return m_connected ? m_loaded ? m_loadedBkColor : m_unloadedBkColor : m_disconnectedBkColor;
	}
	virtual COLORREF GetValueColor() const
	{
		return m_connected ? m_loaded ? m_loadedFgColor : m_unloadedFgColor : m_disconnectedFgColor;
	}
	void SetLoadedBkColor(COLORREF color)
	{
		if(m_loadedBkColor != color)
		{
			m_loadedBkColor = color;
			if(m_loaded)
			{
				CWnd* wnd = m_parent->GetWnd();
				if(wnd)
				{
					wnd->InvalidateRect(m_rectValue, FALSE);
				}
			}
		}
	}
	void SetLoadedFgColor(COLORREF color)
	{
		if(m_loadedFgColor != color)
		{
			m_loadedFgColor = color;
			if(m_loaded)
			{
				CWnd* wnd = m_parent->GetWnd();
				if(wnd)
				{
					wnd->InvalidateRect(m_rectValue, FALSE);
				}
			}
		}
	}
	void SetUnloadedBkColor(COLORREF color)
	{
		if(m_unloadedBkColor != color)
		{
			m_unloadedBkColor = color;
			if(!m_loaded && m_connected)
			{
				CWnd* wnd = m_parent->GetWnd();
				if(wnd)
				{
					wnd->InvalidateRect(m_rectValue, FALSE);
				}
			}
		}
	}
	void SetUnloadedFgColor(COLORREF color)
	{
		if(m_unloadedFgColor != color)
		{
			m_unloadedFgColor = color;
			if(!m_loaded && m_connected)
			{
				CWnd* wnd = m_parent->GetWnd();
				if(wnd)
				{
					wnd->InvalidateRect(m_rectValue, FALSE);
				}
			}
		}
	}
	void SetDisconnectedBkColor(COLORREF color)
	{
		if(m_disconnectedBkColor != color)
		{
			m_disconnectedBkColor = color;
			if(!m_connected)
			{
				CWnd* wnd = m_parent->GetWnd();
				if(wnd)
				{
					wnd->InvalidateRect(m_rectValue, FALSE);
				}
			}
		}
	}
	void SetDisconnectedFgColor(COLORREF color)
	{
		if(m_disconnectedFgColor != color)
		{
			m_disconnectedFgColor = color;
			if(!m_connected)
			{
				CWnd* wnd = m_parent->GetWnd();
				if(wnd)
				{
					wnd->InvalidateRect(m_rectValue, FALSE);
				}
			}
		}
	}
protected:
	COLORREF m_loadedBkColor;
	COLORREF m_loadedFgColor;
	COLORREF m_unloadedBkColor;
	COLORREF m_unloadedFgColor;
	COLORREF m_disconnectedBkColor;
	COLORREF m_disconnectedFgColor;
	bool m_loaded;
	bool m_connected;
};

class TU_API NamedValueTime : public NamedValueUInt
{
public:
	NamedValueTime(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool showSeconds = true):
		NamedValueUInt(type, name, sample, tip, displayName, parent),
		m_showSeconds(showSeconds)
	{}
	virtual void toString(std::string& str) const;
	virtual NamedValue* Clone() const;
	virtual bool SetShowSeconds(bool showSeconds)//{m_showSeconds = showSeconds;}
	{
		if(m_showSeconds != showSeconds)
		{
			m_showSeconds = showSeconds;
			unsigned int len = (unsigned int)m_sample.size();
			if(m_showSeconds)
			{
				m_sample += ":00";
//				m_sample.resize(len + (decDigits - m_decDigits), '9');
			}
			else
			{
				unsigned int diff = 3;
				m_sample.resize(len > diff ? len - diff : 0, '9');
			}
			m_parent->GetWnd()->InvalidateRect(&m_rectValueText, FALSE);
			return true;
		}
		return false;
	}
protected:
	bool m_showSeconds;
};

class TU_API ValueTimeRef : public NamedValueTime
{
public:
	ValueTimeRef(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, const VType* ref = NULL):
		NamedValueTime(type, name, sample, tip, displayName, parent),
		m_ref(ref),
		m_zero(0)
	{
	}
	virtual const VType& GetObjectValue() const{return m_ref ? *m_ref : m_zero;}
	virtual NamedValue* Clone() const;
	virtual void SetRef(const void* ref);
protected:
	const VType* m_ref;
	VType m_zero;
};

class TU_API NamedValueDate : public NamedValueUInt
{
public:
	NamedValueDate(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool monthName = true, bool fullYear = false):
		NamedValueUInt(type, name, sample, tip, displayName, parent),
		m_monthName(monthName),
		m_fullYear(fullYear)
	{}
	virtual void toString(std::string& str) const;
	virtual NamedValue* Clone() const;
protected:
	bool m_monthName;
	bool m_fullYear;
};

class TU_API NamedValueUShort : public NamedValueType<unsigned short>
{
public:
	virtual void toString(std::string& str) const;
protected:
	NamedValueUShort(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample, tip, displayName, parent)
	{
		m_value = 0;
	}
};

class TU_API NamedValueShort : public NamedValueType<short>
{
public:
	virtual void toString(std::string& str) const;
protected:
	NamedValueShort(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample, tip, displayName, parent)
	{
		m_value = 0;
	}
};

class TU_API ValueShortRef : public NamedValueShort
{
public:
	ValueShortRef(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, const VType* ref = NULL):
		NamedValueShort(type, name, sample, tip, displayName, parent),
		m_ref(ref),
		m_zero(0)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return m_ref ? *m_ref : m_zero;}
	virtual void SetRef(const void* ref);
protected:
	const VType* m_ref;
	VType m_zero;
};

class TU_API NamedValueInt : public NamedValueNumberWithComma<int>
{
public:
	virtual void toString(std::string& str) const;
	virtual COLORREF GetValueColor() const;
protected:
	NamedValueInt(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueNumberWithComma(type, name, sample, tip, displayName, parent){}
};

class TU_API NamedValueUInt64 : public NamedValueNumberWithComma<unsigned __int64>
{
public:
	virtual void toString(std::string& str) const;
	NamedValueUInt64(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueNumberWithComma(type, name, sample, tip, displayName, parent){}
	virtual NamedValue* Clone() const;
protected:
};

template<class T>
class NamedValueMonetary : public NamedValueType<T>
{
public:
	NamedValueMonetary(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample, tip, displayName, parent),
		m_decDigits(defaultDecDigits),
		m_truncate(defaultTruncate),
		m_comma(defaultCommaPrice)
	{}
	virtual bool SetDecDigits(unsigned char decDigits)
	{
		if(m_decDigits != decDigits)
		{
			unsigned int len = (unsigned int)m_sample.size();
			if(m_decDigits < decDigits)
			{
				m_sample.resize(len + (decDigits - m_decDigits), '9');
			}
			else
			{
				unsigned int diff = m_decDigits - decDigits;
				m_sample.resize(len > diff ? len - diff : 0, '9');
			}
			m_decDigits = decDigits;
			m_parent->GetWnd()->InvalidateRect(&m_rectValueText, FALSE);
			return true;
		}
		return false;
	}
	virtual bool SetTruncate(bool truncate)
	{
		if(m_truncate != truncate)
		{
			m_truncate = truncate;
			m_parent->GetWnd()->InvalidateRect(&m_rectValueText, FALSE);
			return true;
		}
		return false;
	}
	virtual bool SetCommaPrice(bool comma)
	{
		if(m_comma != comma)
		{
			m_comma = comma;
			m_parent->GetWnd()->InvalidateRect(&m_rectValueText, FALSE);
			return true;
		}
		return false;
	}
	virtual const unsigned char& GetDecDigits() const{return m_decDigits;}
	virtual const bool& isTruncate() const{return m_truncate;}
	virtual const bool& isCommaPrice() const{return m_comma;}
protected:
	unsigned char m_decDigits;
	bool m_truncate;
	bool m_comma;
};

class TU_API NamedValuePrice : public NamedValueMonetary<Price>
{
public:
	NamedValuePrice(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMonetary(type, name, sample, tip, displayName, parent)
	{}
	virtual NamedValue* Clone() const;
	virtual void toString(std::string& str) const;
};

class TU_API ColoredNamedValuePrice : public NamedValuePrice
{
public:
	ColoredNamedValuePrice(ValueType type, COLORREF bkColor, COLORREF fgColor, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePrice(type, name, sample, tip, displayName, parent),
		m_bkColor(bkColor),
		m_fgColor(fgColor)
	{}
	virtual NamedValue* Clone() const;
	void SetBkColor(COLORREF color){m_bkColor = color;}
	void SetFgColor(COLORREF color){m_fgColor = color;}
	virtual COLORREF GetBgColor() const{return m_bkColor;}
	virtual COLORREF GetValueColor() const{return m_fgColor;}
protected:
	COLORREF m_bkColor;
	COLORREF m_fgColor;
};

class TU_API NamedValuePriceAsUInt64 : public NamedValueMonetary<unsigned __int64>
{
public:
	virtual void toString(std::string& str) const;
protected:
	NamedValuePriceAsUInt64(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMonetary(type, name, sample, tip, displayName, parent)
	{
		m_value = 0;
	}
};

class TU_API NamedValuePriceAsUInt : public NamedValueMonetary<unsigned int>
{
public:
	virtual void toString(std::string& str) const;
protected:
	NamedValuePriceAsUInt(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMonetary(type, name, sample, tip, displayName, parent)
	{
		m_value = 0;
	}
};

class TU_API NamedValuePriceAsUIntZeroEmpty : public NamedValuePriceAsUInt
{
public:
	virtual void toString(std::string& str) const;
protected:
	NamedValuePriceAsUIntZeroEmpty(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePriceAsUInt(type, name, sample, tip, displayName, parent)
	{
	}
};

class TU_API NamedValueSignedPrice : public NamedValueMonetary<SignedPrice>
{
public:
	virtual void toString(std::string& str) const;
	virtual COLORREF GetValueColor() const;
protected:
	NamedValueSignedPrice(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMonetary(type, name, sample, tip, displayName, parent)
	{}
};

class TU_API NamedValueMoney : public NamedValueMonetary<Money>
{
public:
	virtual void toString(std::string& str) const;
	virtual COLORREF GetValueColor() const;
protected:
	NamedValueMoney(ValueType type, bool valueColorCoded, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMonetary(type, name, sample, tip, displayName, parent),
		m_valueColorCoded(valueColorCoded)
	{}
	bool m_valueColorCoded;
};

class TU_API SecurityValuePrice : public NamedValuePrice
{
public:
	typedef const VType& (Security::*PriceFunction)() const;
	SecurityValuePrice(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePrice(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API SecurityValuePricePercent : public SecurityValuePrice
{
public:
	SecurityValuePricePercent(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValuePrice(name, priceFunction, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void toString(std::string& str) const
	{
		SecurityValuePrice::toString(str);
		str += '%';
	}
};

class TU_API SecurityValuePriceAsUInt64 : public NamedValuePriceAsUInt64
{
public:
	typedef VType (Security::*PriceFunction)() const;
	SecurityValuePriceAsUInt64(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePriceAsUInt64(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			unsigned __int64 price = (m_security->*m_priceFunction)();
//			const TradeLevel1& level1 = m_security->GetLastTradeLevel1();
			if(m_value != price)
			{
				m_value = price;
				m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
			}
		}
	}
protected:
	PriceFunction m_priceFunction;
};

class TU_API SecurityValuePriceAsUInt : public NamedValuePriceAsUInt
{
public:
	typedef const VType& (Security::*PriceFunction)() const;
	SecurityValuePriceAsUInt(ValueType type, const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePriceAsUInt(type, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API SecurityValuePriceAsUIntZeroEmpty : public NamedValuePriceAsUIntZeroEmpty
{
public:
	typedef const VType& (Security::*PriceFunction)() const;
	SecurityValuePriceAsUIntZeroEmpty(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePriceAsUIntZeroEmpty(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API SecurityValuePriceAsUIntVal : public NamedValuePriceAsUInt
{
public:
	typedef VType (Security::*PriceFunction)() const;
	SecurityValuePriceAsUIntVal(ValueType type, const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePriceAsUInt(type, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			unsigned int price = (m_security->*m_priceFunction)();
//			const TradeLevel1& level1 = m_security->GetLastTradeLevel1();
			if(m_value != price)
			{
				m_value = price;
				m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
			}
		}
	}
protected:
	PriceFunction m_priceFunction;
};

class TU_API SecurityValueSignedPrice : public NamedValueSignedPrice
{
public:
	typedef const VType& (Security::*PriceFunction)() const;
	SecurityValueSignedPrice(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API SecurityValueColoredPercent : public SecurityValueSignedPrice
{
public:
	SecurityValueColoredPercent(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValueSignedPrice(name, priceFunction, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const;
	virtual COLORREF GetBgColor() const
	{
		if(m_value.isZero())
		{
			return m_parent->GetValueColorNegativeBg();
		}
		else if(m_value.GetDollars() == 100)
		{
			return m_parent->GetValueColorPositiveBg();
		}
		else
		{
			return 0xFFFFFFFF;
		}
	}
	virtual COLORREF GetValueColor() const
	{
		if(m_value.isZero())
		{
			return m_parent->GetValueColorNegativeBgText();
		}
		else if(m_value.GetDollars() == 100)
		{
			return m_parent->GetValueColorPositiveBgText();
		}
		else
		{
			return m_parent->GetValueColorNeutral();
		}
	}
};

//class TU_API SecurityLastPrintPrice : public NamedValuePriceAsUInt64
class TU_API SecurityLastPrintPrice : public NamedValuePriceAsUInt
{
public:
//	typedef VType (Security::*UIntFunction)() const;
	typedef const VType& (Security::*UIntFunction)() const;
	SecurityLastPrintPrice(const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
//		NamedValuePriceAsUInt64(NVT_SECURITY, name, sample, tip, displayName, parent),
		NamedValuePriceAsUInt(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction),
		m_level1(TL1_BETWEEN_BIDASK)
	{
	}
//	virtual const VType& GetObjectValue() const{return TU_GetPriceZero();}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
//			unsigned int price = m_security->GetLastPrice();
			unsigned int price = (m_security->*m_uintFunction)();
			const TradeLevel1& level1 = m_security->GetLastTradeLevel1();
			if(m_value != price || m_level1 != level1)
			{
				m_value = price;
				m_level1 = level1;
				m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
			}
		}
	}
	virtual COLORREF GetBgColor() const
	{
		switch(m_level1)
		{
			case TL1_LESS_BID:
			return m_parent->GetValueColorNegativeBg();

			case TL1_GREATER_ASK:
			return m_parent->GetValueColorPositiveBg();

			default:
			return 0xFFFFFFFF;
		}
	}
	virtual COLORREF GetValueColor() const
	{
		switch(m_level1)
		{
			case TL1_EQUAL_BID:
			return m_parent->GetValueColorNegative();

			case TL1_EQUAL_ASK:
			return m_parent->GetValueColorPositive();

			case TL1_LESS_BID:
			return m_parent->GetValueColorNegativeBgText();

			case TL1_GREATER_ASK:
			return m_parent->GetValueColorPositiveBgText();

			default:
			return m_parent->GetValueColorNeutral();
		}
	}
protected:
	UIntFunction m_uintFunction;
	TradeLevel1 m_level1;
};

class TU_API IndexValueSignedPrice : public NamedValueSignedPrice
{
public:
	typedef const VType& (Index::*SignedPriceFunction)() const;
	IndexValueSignedPrice(const char* name, SignedPriceFunction signedPriceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_INDEX, name, sample, tip, displayName, parent),
		m_signedPriceFunction(signedPriceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_index->*m_signedPriceFunction)();}
protected:
	SignedPriceFunction m_signedPriceFunction;
};

class TU_API IndexLastValue : public IndexValueSignedPrice
{
public:
	IndexLastValue(const char* indexSymbol, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		IndexValueSignedPrice(name ? name : indexSymbol, &Index::GetValue, sample, tip, displayName, parent),
		m_diff(0)
	{
	}
//	virtual const VType& GetObjectValue() const{return TU_GetPriceZero();}
	virtual NamedValue* Clone() const;
/*
	virtual COLORREF GetBgColor() const
	{
		switch(m_level1)
		{
			case TL1_LESS_BID:
			return m_parent->GetValueColorNegativeBg();

			case TL1_GREATER_ASK:
			return m_parent->GetValueColorPositiveBg();

			default:
			return 0xFFFFFFFF;
		}
	}
*/
	virtual COLORREF GetValueColor() const
	{
		switch(m_diff)
		{
			case -1:
			return m_parent->GetValueColorNegative();

			case 1:
			return m_parent->GetValueColorPositive();

			default:
			return m_parent->GetValueColorNeutral();
		}
	}
/*
	void SetValue(const SignedPrice& value)
	{
		m_diff = 0;
		if(m_value != value)
		{
			m_value = value;
			m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
		}
	}
*/
	virtual void UpdateValueFirstTime()
	{
		UpdateValue();
		m_diff = 0;
	}

	virtual void UpdateValue()
	{
		if(m_valid)
		{
			const VType& value = GetObjectValue();
			if(m_value != value)
			{
//			SetValue(GetObjectValue());
				m_diff = m_value < value ? 1 : -1;
				m_value = value;
				m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
			}
			else if(m_diff)
			{
				m_diff = 0;
				m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
			}
		}
	}
	virtual const char* GetIndexSymbol() const{return m_indexSymbol.c_str();}
protected:
	std::string m_indexSymbol;
	char m_diff;
};

class TU_API SecurityValueUInt64 : public NamedValueUInt64
{
public:
	typedef const VType& (Security::*UInt64Function)() const;
	SecurityValueUInt64(const char* name, UInt64Function uint64Function, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt64(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_uint64Function(uint64Function)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_uint64Function)();}
protected:
	UInt64Function m_uint64Function;
};

class TU_API SecurityValueStringAsUInt64 : public SecurityValueUInt64
{
public:
	typedef const VType& (Security::*UInt64Function)() const;
	SecurityValueStringAsUInt64(const char* name, UInt64Function uint64Function, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValueUInt64(name, uint64Function, sample, tip, displayName, parent)
	{
	}
	virtual void toString(std::string& str) const;
	virtual NamedValue* Clone() const;
};

class TU_API SecurityValueUInt : public NamedValueUInt
{
public:
	typedef const VType& (Security::*UIntFunction)() const;
	SecurityValueUInt(ValueType type, const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(type, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_uintFunction)();}
protected:
	UIntFunction m_uintFunction;
};

class TU_API SecurityValueUIntZeroEmpty : public NamedValueUIntZeroEmpty
{
public:
	typedef const VType& (Security::*UIntFunction)() const;
	SecurityValueUIntZeroEmpty(ValueType type, const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUIntZeroEmpty(type, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_uintFunction)();}
protected:
	UIntFunction m_uintFunction;
};

class TU_API SecurityValueUIntVal : public NamedValueUInt
{
public:
	typedef VType (Security::*UIntFunction)() const;
	SecurityValueUIntVal(ValueType type, const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(type, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			unsigned int value = (m_security->*m_uintFunction)();
			if(m_value != value)
			{
				m_value = value;
				m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
			}
		}
	}
protected:
	UIntFunction m_uintFunction;
};

class TU_API SecurityValueDateVal : public SecurityValueUIntVal
{
public:
	SecurityValueDateVal(ValueType type, const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValueUIntVal(type, name, uintFunction, sample, tip, displayName, parent)
	{
	}
	virtual void toString(std::string& str) const;
	virtual NamedValue* Clone() const;
};

class TU_API SecurityValueInt : public NamedValueInt
{
public:
	typedef const VType& (Security::*IntFunction)() const;
	SecurityValueInt(const char* name, IntFunction intFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueInt(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_intFunction(intFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_intFunction)();}
protected:
	IntFunction m_intFunction;
};

class TU_API SecurityPrintSize : public SecurityValueUInt
{
public:
	SecurityPrintSize(const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValueUInt(NVT_SECURITY, name, uintFunction, sample, tip, displayName, parent),
		m_sizeInShares(true)
	{}
	virtual void toString(std::string& str) const;
	virtual NamedValue* Clone() const;

	virtual bool SetSizeInShares(bool sizeInShares)
	{
		if(m_sizeInShares != sizeInShares)
		{
			m_sizeInShares = sizeInShares;
			unsigned int len = (unsigned int)m_sample.size();
			if(m_sizeInShares)
			{
				m_sample.resize(len + 2, '9');
			}
			else
			{
				m_sample.resize(len > 2 ? len - 2 : 0, '9');
			}
			m_parent->GetWnd()->InvalidateRect(&m_rectValue, FALSE);
			return true;
		}
		return false;
	}
	virtual const bool& isSizeInShares() const{return m_sizeInShares;}
protected:
	bool m_sizeInShares;
};

class TU_API SecurityValueTime : public NamedValueTime
{
public:
	typedef const VType& (Security::*UIntFunction)() const;
	SecurityValueTime(const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueTime(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_uintFunction)();}
protected:
	UIntFunction m_uintFunction;
};

class TU_API SecurityValueUShort : public NamedValueUShort
{
public:
	typedef const VType& (Security::*UShortFunction)() const;
	SecurityValueUShort(const char* name, UShortFunction ushortFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUShort(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_ushortFunction(ushortFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_ushortFunction)();}
protected:
	UShortFunction m_ushortFunction;
};

class TU_API SecurityValueShort : public NamedValueShort
{
public:
	typedef const VType& (Security::*ShortFunction)() const;
	SecurityValueShort(const char* name, ShortFunction shortFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueShort(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_shortFunction(shortFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_shortFunction)();}
protected:
	ShortFunction m_shortFunction;
};

class TU_API SecurityValueString : public NamedValueString
{
public:
	typedef const VType& (Security::*StringFunction)() const;
	SecurityValueString(const char* name, StringFunction stringFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueString(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_stringFunction(stringFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_stringFunction)();}
protected:
	StringFunction m_stringFunction;
};

class TU_API SecurityValueChar : public NamedValueChar
{
public:
	typedef const VType& (Security::*CharFunction)() const;
	SecurityValueChar(const char* name, CharFunction charFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, char emptyValue = '\0', char negativeValue = '\0'):
		NamedValueChar(NVT_SECURITY, name, sample, tip, displayName, parent, emptyValue, negativeValue),
		m_charFunction(charFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_charFunction)();}
protected:
	CharFunction m_charFunction;
};

class TU_API SecurityValueCB : public SecurityValueChar
{
public:
	SecurityValueCB(NamedValueCollection* parent = NULL):
		SecurityValueChar("RegSho", &Security::GetRegSHOTestIndicator, "2", "Circuit Breaker", "CB", parent, '0')
	{
	}
	virtual COLORREF GetValueColor() const;
	virtual NamedValue* Clone() const;
};

class TU_API SecurityValueRpi : public SecurityValueChar
{
public:
	SecurityValueRpi(NamedValueCollection* parent = NULL):
		SecurityValueChar("Rpi", &Security::GetRpiIndicator, "2", "RPI Indicator", NULL, parent, '0')
	{
	}
//	virtual COLORREF GetValueColor() const;
	virtual NamedValue* Clone() const;
};

class TU_API SecurityValueUChar : public NamedValueUChar
{
public:
	typedef const VType& (Security::*UCharFunction)() const;
	SecurityValueUChar(const char* name, UCharFunction ucharFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUChar(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_ucharFunction(ucharFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_ucharFunction)();}
protected:
	UCharFunction m_ucharFunction;
};

class TU_API SecurityExchange : public SecurityValueChar
{
public:
	SecurityExchange():SecurityValueChar("Exch", &Security::GetPrimaryExchange, "WWWW", "Security Primaty Exchange"){}
	virtual NamedValue* Clone() const;
	virtual void toString(std::string& str) const;
};

class TU_API SecurityTick : public SecurityValueUChar
{
public:
	SecurityTick():SecurityValueUChar("Tick", &Security::GetTick, "W", "Security Bid Tick"){}
	virtual NamedValue* Clone() const;
	virtual void toString(std::string& str) const;
};

#ifndef TAKION_NO_OPTIONS
class TU_API NamedValueSecurityCallPut : public NamedValueChar
{
public:
	NamedValueSecurityCallPut(NamedValueCollection* parent = NULL):NamedValueChar(NVT_SECURITY, "C/P", "C", "Option Call / Put", NULL, parent){}
	virtual void toString(std::string& str) const
	{
		if(m_value)str += m_value;
	}
	virtual void UpdateValue()
	{
		if(m_security)
		{
			const OptionInfo* optionInfo = m_security->GetOptionInfo();
			SetValue(optionInfo ? optionInfo->isCall() ? 'C' : 'P' : '\0');
		}
	}
	virtual NamedValue* Clone() const;
};

class TU_API NamedValueSecuritySuffix : public NamedValueChar
{
public:
	NamedValueSecuritySuffix(NamedValueCollection* parent = NULL):NamedValueChar(NVT_SECURITY, "Suffix", "W", "Option Suffix", NULL, parent){}
	virtual void toString(std::string& str) const
	{
		if(m_value)str += m_value;
	}
	virtual void UpdateValue()
	{
		if(m_security)
		{
			const OptionInfo* optionInfo = m_security->GetOptionInfo();
			SetValue(optionInfo ? optionInfo->GetSuffix() : '\0');
		}
	}
	virtual NamedValue* Clone() const;
};
#endif

class TU_API NamedValueSecurityIsLoaded : public NamedValueBool
{
public:
	NamedValueSecurityIsLoaded():NamedValueBool(NVT_SECURITY, "Loaded", "Yes", "Security is loaded")
	{
		m_value = false;
	}
//	virtual const VType& GetObjectValue() const{return m_value;}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue(m_security->isLoaded());
		}
	}
	virtual COLORREF GetValueColor() const;
	virtual NamedValue* Clone() const;
};

class TU_API SecurityValueBool : public NamedValueBool
{
public:
	typedef const VType& (Security::*BoolFunction)() const;
	SecurityValueBool(const char* name, BoolFunction boolFunction, bool reverseColor, const char* sample, const char* tip, const char* yesValue = "Yes", const char* noValue = "No", bool useColor = true, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueBool(NVT_SECURITY, name, sample, tip, yesValue, noValue, useColor, reverseColor, displayName, parent),
		m_boolFunction(boolFunction)
	{
	}
	virtual NamedValue* Clone() const;
//	virtual COLORREF GetValueColor() const;
	virtual const VType& GetObjectValue() const{return (m_security->*m_boolFunction)();}
protected:
	BoolFunction m_boolFunction;
};

//class TU_API NamedValueSecurityHtb : public NamedValueBool
class TU_API NamedValueSecurityHtb : public NamedValueUCharAsChar
{
public:
	NamedValueSecurityHtb(const unsigned int& ordinal, NamedValueCollection* parent = NULL):NamedValueUCharAsChar(NVT_SECURITY, "HTB", "H", "Hard to Borrow", NULL, parent),m_ordinal(ordinal),m_borrowSize(0){}
	NamedValueSecurityHtb(const NamedValueSecurityHtb& other):NamedValueUCharAsChar(other),m_ordinal(other.m_ordinal),m_borrowSize(other.m_borrowSize){}
	virtual bool DependsOnAccount() const{return true;}
	virtual void UpdateValue()
	{
		if(m_security)
		{
			unsigned int borrowSize = m_security->GetBorrowSize(m_ordinal);
			if(m_borrowSize != borrowSize)
			{
				m_borrowSize = borrowSize;
				m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
			}
			SetValue(m_security->isHTB(m_ordinal));
		}
//		UpdateColor();
	}
	virtual COLORREF GetValueColor() const;
	virtual NamedValue* Clone() const;
protected:
//	void UpdateColor();
//	virtual void OnParentSet();
	const unsigned int& m_ordinal;
	unsigned int m_borrowSize;
//	COLORREF m_color;
};

class TU_API NamedValueSecurityBorrowPrice : public NamedValuePrice
{
public:
	NamedValueSecurityBorrowPrice(const unsigned int& ordinal):NamedValuePrice(NVT_SECURITY, "$Borrow", "99.9999", "Borrow Price in cents", "cBorrow"),m_ordinal(ordinal)
	{
	}
	NamedValueSecurityBorrowPrice(const NamedValueSecurityBorrowPrice& other):NamedValuePrice(other),m_ordinal(other.m_ordinal){}
	virtual bool DependsOnAccount() const{return true;}
	virtual void UpdateValue()
	{
		if(m_security && m_account)
		{
			const Price* price = m_security->GetBorrowPrice(m_ordinal);
			unsigned char discountFlag = m_security->GetBorrowDiscountFlag(m_ordinal);
			SetValue(price ? m_account && discountFlag == 0 ? *price * m_account->GetBorrowPriceMultiplier() : *price : TU_GetPriceZero());
		}
	}
	virtual NamedValue* Clone() const;
	virtual void toString(std::string& str) const
	{
		str += 'c';
		NamedValuePrice::toString(str);
	}
protected:
	const unsigned int& m_ordinal;
};

class TU_API NamedValueSecuritySplit : public NamedValueUInt
{
public:
	NamedValueSecuritySplit():NamedValueUInt(NVT_SECURITY, "Split", "20/20", "Security Split")
	{
		m_value = (1 << 16) | 1;
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_security->GetSplitNumerator()) << 16 | m_security->GetSplitDenominator());
		}
	}
	virtual void toString(std::string& str) const;
	virtual COLORREF GetValueColor() const;
	virtual NamedValue* Clone() const;
};

class TU_API SecurityValuePriceDiff : public NamedValueSignedPrice
{
public:
	typedef const Price& (Security::*PriceFunction)() const;
	SecurityValuePriceDiff(const char* name, PriceFunction priceFunction, PriceFunction priceFunction2, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction),
		m_priceFunction2(priceFunction2),
		m_canBeNegative(canBeNegative)
	{
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue(SignedPrice((m_security->*m_priceFunction)()) - SignedPrice((m_security->*m_priceFunction2)()));
		}
	}
	virtual NamedValue* Clone() const;
	virtual COLORREF GetValueColor() const;
protected:
	PriceFunction m_priceFunction;
	PriceFunction m_priceFunction2;
	bool m_canBeNegative;
};

class TU_API SecurityValuePriceDiffNoZero : public SecurityValuePriceDiff
{
public:
	SecurityValuePriceDiffNoZero(const char* name, PriceFunction priceFunction, PriceFunction priceFunction2, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValuePriceDiff(name, priceFunction, priceFunction2, canBeNegative, sample, tip, displayName, parent)
	{
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			const Price& price1 = (m_security->*m_priceFunction)();
			const Price& price2 = (m_security->*m_priceFunction2)();
			if(!price1.isZero() && !price2.isZero())
			{
//				SetValue(price1 - price2);
				SetValue(SignedPrice(price1) - SignedPrice(price2));
			}
			else
			{
				SetValue(SignedPrice(0, 0));
			}
		}
	}
	virtual NamedValue* Clone() const;
};

class TU_API SecurityValueMoneyDividedByUInt64 : public NamedValueMoney
{
public:
	typedef const Money& (Security::*MoneyFunction)() const;
	typedef const unsigned __int64& (Security::*UInt64Function)() const;
	SecurityValueMoneyDividedByUInt64(const char* name, MoneyFunction moneyFunction, UInt64Function uint64Function, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, !canBeNegative, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction),
		m_uint64Function(uint64Function),
		m_canBeNegative(canBeNegative)
	{
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			unsigned __int64 number = (m_security->*m_uint64Function)();
			Money val;
			if(number)
			{
				val = (m_security->*m_moneyFunction)();
				if(!m_canBeNegative && val.isNegative())
				{
					val = -val;
				}
				val /= number;
			}
			SetValue(val);
//			SetValue(number ? (m_security->*m_moneyFunction)().operator/(number) : Money(0, 0));
		}
	}
	virtual NamedValue* Clone() const;
//	virtual COLORREF GetValueColor() const;
protected:
	MoneyFunction m_moneyFunction;
	UInt64Function m_uint64Function;
	bool m_canBeNegative;
};

class TU_API SecurityValueIntDividedByUInt64 : public NamedValueMoney
{
public:
	typedef const int& (Security::*IntFunction)() const;
	typedef const unsigned __int64& (Security::*UInt64Function)() const;
	SecurityValueIntDividedByUInt64(const char* name, IntFunction intFunction, UInt64Function uint64Function, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, !canBeNegative, name, sample, tip, displayName, parent),
		m_intFunction(intFunction),
		m_uint64Function(uint64Function),
		m_canBeNegative(canBeNegative)
	{
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			Money val;
			unsigned __int64 number = (m_security->*m_uint64Function)();
			if(number)
			{
				int num = (m_security->*m_intFunction)();
				if(num)
				{
					if(!m_canBeNegative && num < 0)
					{
						num = -num;
					}
					val = Money(num * 100, 0);
					val /= number;
				}
			}
			SetValue(val);
		}
	}
	virtual void toString(std::string& str) const
	{
		NamedValueMoney::toString(str);
		str += '%';
	}
	virtual NamedValue* Clone() const;
//	virtual COLORREF GetValueColor() const;
protected:
	IntFunction m_intFunction;
	UInt64Function m_uint64Function;
	bool m_canBeNegative;
};

class TU_API SecurityValueIntByIntDivisionFraction : public NamedValueMoney
{
public:
	typedef const int& (Security::*IntFunction)() const;
	SecurityValueIntByIntDivisionFraction(const char* name, IntFunction intFunction, IntFunction intFunction2, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, !canBeNegative, name, sample, tip, displayName, parent),
		m_intFunction(intFunction),
		m_intFunction2(intFunction2),
		m_canBeNegative(canBeNegative)
	{
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			Money val;
			int number = (m_security->*m_intFunction2)();
			if(number)
			{
				int num = (m_security->*m_intFunction)();
				if(!m_canBeNegative)
				{
					if(num < 0)num = -num;
					if(number < 0)val = -val;
				}
				val = Money(num, 0);
				val /= number;
			}
			SetValue(val);
		}
	}
/*
	virtual void toString(std::string& str) const
	{
		NamedValueMoney::toString(str);
		str += '%';
	}
*/
	virtual NamedValue* Clone() const;
//	virtual COLORREF GetValueColor() const;
protected:
	IntFunction m_intFunction;
	IntFunction m_intFunction2;
	bool m_canBeNegative;
};

class TU_API SecurityValueMoneyDividedByUInt64PriceAsUIntDiff : public NamedValueMoney
{
public:
	typedef const Money& (Security::*MoneyFunction)() const;
	typedef const unsigned __int64& (Security::*UInt64Function)() const;
//	typedef unsigned int (Security::*UIntFunction)() const;
	typedef const unsigned int& (Security::*UIntFunction)() const;
	SecurityValueMoneyDividedByUInt64PriceAsUIntDiff(const char* name,
		MoneyFunction moneyFunction,
		UInt64Function uint64Function,
		UIntFunction uintFunction,
//		bool canBeNegative,
		const char* sample,
		const char* tip,
		const char* displayName = NULL,
		NamedValueCollection* parent = NULL):
//		NamedValueMoney(NVT_SECURITY, !canBeNegative, name, sample, tip, displayName, parent),
		NamedValueMoney(NVT_SECURITY, true, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction),
		m_uint64Function(uint64Function),
		m_uintFunction(uintFunction)
//		m_canBeNegative(canBeNegative)
	{
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			unsigned __int64 number = (m_security->*m_uint64Function)();
			unsigned int price = (m_security->*m_uintFunction)();
			Money money = (m_security->*m_moneyFunction)();
			SetValue(number && price && !money.isZero() ? Money(price) - money.operator/(number) : Money(0, 0));
		}
	}
	virtual NamedValue* Clone() const;
//	virtual COLORREF GetValueColor() const;
protected:
	MoneyFunction m_moneyFunction;
	UInt64Function m_uint64Function;
	UIntFunction m_uintFunction;
//	bool m_canBeNegative;
};

class TU_API SecurityValueMoneyDividedByUInt64PriceAsUIntDiffPercent : public NamedValueMoney
{
public:
	typedef const Money& (Security::*MoneyFunction)() const;
	typedef const unsigned __int64& (Security::*UInt64Function)() const;
//	typedef unsigned int (Security::*UIntFunction)() const;
	typedef const unsigned int& (Security::*UIntFunction)() const;
	SecurityValueMoneyDividedByUInt64PriceAsUIntDiffPercent(const char* name,
		MoneyFunction moneyFunction,
		UInt64Function uint64Function,
		UIntFunction uintFunction,
//		bool canBeNegative,
		const char* sample,
		const char* tip,
		const char* displayName = NULL,
		NamedValueCollection* parent = NULL):
//		NamedValueMoney(NVT_SECURITY, !canBeNegative, name, sample, tip, displayName, parent),
		NamedValueMoney(NVT_SECURITY, true, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction),
		m_uint64Function(uint64Function),
		m_uintFunction(uintFunction)
//		m_canBeNegative(canBeNegative)
	{
	}
	virtual void toString(std::string& str) const
	{
		NamedValueMoney::toString(str);
		str += '%';
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			unsigned __int64 number = (m_security->*m_uint64Function)();
			unsigned int price = (m_security->*m_uintFunction)();
			Money money = (m_security->*m_moneyFunction)();
			if(number && price && !money.isZero())
			{
				Money vwap = money.operator/(number);
				SetValue(vwap.GetPercentChange(Money(price) - vwap));
			}
			else
			{
				return SetValue(Money(0, 0));
			}
		}
	}
	virtual NamedValue* Clone() const;
//	virtual COLORREF GetValueColor() const;
protected:
	MoneyFunction m_moneyFunction;
	UInt64Function m_uint64Function;
	UIntFunction m_uintFunction;
//	bool m_canBeNegative;
};

class TU_API NamedValueSecurityPercentChange : public NamedValueSignedPrice
{
public:
	NamedValueSecurityPercentChange():NamedValueSignedPrice(NVT_SECURITY, "%Net", "-99.999%", "% Net Change (from Yesterday's Close)")
	{
	}
	NamedValueSecurityPercentChange(const NamedValueSecurityPercentChange& other):NamedValueSignedPrice(other){}
	virtual void toString(std::string& str) const
	{
		NamedValueSignedPrice::toString(str);
		str += '%';
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			const SignedPrice& netChange = m_security->GetNetChange();
			if(m_netChange != netChange)
			{
				m_netChange = netChange;
				SetValue(m_security->GetClosePrice().GetPercentChange(m_netChange));
			}
		}
	}
	virtual NamedValue* Clone() const;
protected:
	SignedPrice m_netChange;
};

class TU_API NamedValueSecurityNitePercentChange : public NamedValueSignedPrice
{
public:
	NamedValueSecurityNitePercentChange():NamedValueSignedPrice(NVT_SECURITY, "%Nite", "-99.999%", "% Nite Change (difference between the Open price and Yesterday's Close price)")
	{
	}
	NamedValueSecurityNitePercentChange(const NamedValueSecurityNitePercentChange& other):NamedValueSignedPrice(other){}
	virtual void toString(std::string& str) const
	{
		NamedValueSignedPrice::toString(str);
		str += '%';
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			const SignedPrice& niteChange = m_security->GetNiteChange();
			if(m_niteChange != niteChange)
			{
				m_niteChange = niteChange;
				SetValue(m_security->GetClosePrice().GetPercentChange(m_niteChange));
			}
		}
	}
	virtual NamedValue* Clone() const;
protected:
	SignedPrice m_niteChange;
};

class TU_API NamedValueSecurityOpenPercentChange : public NamedValueSignedPrice
{
public:
	NamedValueSecurityOpenPercentChange():NamedValueSignedPrice(NVT_SECURITY, "%NetOpen", "-99.999%", "% Net Open Change (from Today's Open)")
	{
	}
	NamedValueSecurityOpenPercentChange(const NamedValueSecurityOpenPercentChange& other):NamedValueSignedPrice(other){}
	virtual void toString(std::string& str) const
	{
		NamedValueSignedPrice::toString(str);
		str += '%';
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			const SignedPrice& openChange = m_security->GetOpenChange();
			if(m_openChange != openChange)
			{
				m_openChange = openChange;
				SetValue(m_security->GetOpenPrice().GetPercentChange(m_openChange));
			}
		}
	}
	virtual NamedValue* Clone() const;
protected:
	SignedPrice m_openChange;
};

class TU_API NamedValueSecurityQOpenPercentChange : public NamedValueSignedPrice
{
public:
	NamedValueSecurityQOpenPercentChange():NamedValueSignedPrice(NVT_SECURITY, "%QNetOpen", "-99.999%", "% Net Open Change (from Today's Open, initialized by real opening print with sale condition O or Q))")
	{
	}
	NamedValueSecurityQOpenPercentChange(const NamedValueSecurityQOpenPercentChange& other):NamedValueSignedPrice(other){}
	virtual void toString(std::string& str) const
	{
		NamedValueSignedPrice::toString(str);
		str += '%';
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			const SignedPrice& openChange = m_security->GetQOpenChange();
			if(m_openChange != openChange)
			{
				m_openChange = openChange;
				SetValue(m_security->GetQOpenPrice().GetPercentChange(m_openChange));
			}
		}
	}
	virtual NamedValue* Clone() const;
protected:
	SignedPrice m_openChange;
};

class TU_API NamedValueSecurityTClosePercentChange : public NamedValueSignedPrice
{
public:
	NamedValueSecurityTClosePercentChange():NamedValueSignedPrice(NVT_SECURITY, "%NetTClose", "-99.999%", "% Net Todays Close Change (from Today's Close)")
	{
	}
	NamedValueSecurityTClosePercentChange(const NamedValueSecurityTClosePercentChange& other):NamedValueSignedPrice(other){}
	virtual void toString(std::string& str) const
	{
		NamedValueSignedPrice::toString(str);
		str += '%';
	}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			const SignedPrice& todaysCloseChange = m_security->GetTodaysCloseChange();
			if(m_todaysCloseChange != todaysCloseChange)
			{
				m_todaysCloseChange = todaysCloseChange;
				SetValue(m_security->GetTodaysClosePrice().GetPercentChange(m_todaysCloseChange));
			}
		}
	}
	virtual NamedValue* Clone() const;
protected:
	SignedPrice m_todaysCloseChange;
};

class TU_API NamedValueSecuritySpread : public NamedValueSignedPrice
{
public:
	NamedValueSecuritySpread():NamedValueSignedPrice(NVT_SECURITY, "Spread", "-99.999", "Level1 Spread (Ask - Bid)")
	{
	}
	NamedValueSecuritySpread(const NamedValueSecuritySpread& other):NamedValueSignedPrice(other){}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue(SignedPrice(m_security->GetL1Ask()) - SignedPrice(m_security->GetL1Bid()));
		}
	}
	virtual NamedValue* Clone() const;
};

class TU_API PositionValuePrice : public NamedValuePrice
{
public:
	typedef const VType& (Position::*PriceFunction)() const;
	PositionValuePrice(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePrice(NVT_POSITION, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_position->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API PositionValueColoredPrice : public PositionValuePrice
{
public:
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			const Price& price = (m_position->*m_priceFunction)();
//			const TradeLevel1& level1 = m_security->GetLastTradeLevel1();
			if(m_value != price)
			{
				m_value = price;
				m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
			}
			const Money& pnl = GetPnl();
			if(m_pnl != pnl)
			{
				if(m_pnl.isPositive() != pnl.isPositive() || m_pnl.isNegative() != pnl.isNegative())
				{
					m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
				}
				m_pnl = pnl;
			}
		}
	}
	virtual COLORREF GetValueColor() const
	{
		return m_colored ?
			m_pnl.isPositive() ? m_parent->GetValueColorPositive():
			m_pnl.isNegative() ? m_parent->GetValueColorNegative():
			m_parent->GetValueColorNeutral():
			m_parent->GetValueColorNeutral();
	}
//	virtual const VType& GetObjectValue() const{return (m_position->*m_priceFunction)();}
	virtual const Money& GetPnl() const = 0;
protected:
	PositionValueColoredPrice(bool colored, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValuePrice(name, &Position::GetAveragePrice, sample, tip, displayName, parent),
		m_colored(colored)
	{
	}
//	PriceFunction m_priceFunction;
	Money m_pnl;
	bool m_colored;
};

class TU_API PositionValueColoredPricePrint : public PositionValueColoredPrice
{
public:
	PositionValueColoredPricePrint(bool colored, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueColoredPrice(colored, name, sample, tip, displayName, parent)
	{
	}
	virtual const Money& GetPnl() const{return m_position->GetOpenPnlPrint();}
	virtual NamedValue* Clone() const;
};

class TU_API PositionValueColoredPriceNbboPrint : public PositionValueColoredPrice
{
public:
	PositionValueColoredPriceNbboPrint(bool colored, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueColoredPrice(colored, name, sample, tip, displayName, parent)
	{
	}
	virtual const Money& GetPnl() const{return m_position->GetOpenPnlNbboPrint();}
	virtual NamedValue* Clone() const;
};

class TU_API PositionValueColoredPriceLevel1 : public PositionValueColoredPrice
{
public:
	PositionValueColoredPriceLevel1(bool colored, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueColoredPrice(colored, name, sample, tip, displayName, parent)
	{
	}
	virtual const Money& GetPnl() const{return m_position->GetOpenPnlLevel1();}
	virtual NamedValue* Clone() const;
};

class TU_API PositionValueSignedPrice : public NamedValueSignedPrice
{
public:
	typedef const VType& (Position::*PriceFunction)() const;
	PositionValueSignedPrice(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_POSITION, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_position->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API PositionValueMoney : public NamedValueMoney
{
public:
	typedef const VType& (Position::*MoneyFunction)() const;
	PositionValueMoney(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_POSITION, valueColorCoded, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_position->*m_moneyFunction)();}
protected:
	MoneyFunction m_moneyFunction;
};

class TU_API PositionValuePriceAsUInt : public NamedValuePriceAsUInt
{
public:
	typedef const VType& (Position::*UIntFunction)() const;
	PositionValuePriceAsUInt(const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePriceAsUInt(NVT_POSITION, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_position->*m_uintFunction)();}
protected:
	UIntFunction m_uintFunction;
};

class TU_API PositionValueBool : public NamedValueBool
{
public:
	typedef const VType& (Position::*BoolFunction)() const;
	PositionValueBool(const char* name, BoolFunction boolFunction, const char* sample, const char* tip, const char* yesValue = "Yes", const char* noValue = "No", bool useColor = false, bool reverse = false, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueBool(NVT_POSITION, name, sample, tip, yesValue, noValue, useColor, reverse, displayName, parent),
		m_boolFunction(boolFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_position->*m_boolFunction)();}
protected:
	BoolFunction m_boolFunction;
};

class TU_API PositionValueInt : public NamedValueInt
{
public:
	typedef const VType& (Position::*IntFunction)() const;
	PositionValueInt(const char* name, IntFunction intFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueInt(NVT_POSITION, name, sample, tip, displayName, parent),
		m_intFunction(intFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_position->*m_intFunction)();}
protected:
	IntFunction m_intFunction;
};

class TU_API PositionValueUInt : public NamedValueUInt
{
public:
	typedef const VType& (Position::*UIntFunction)() const;
	PositionValueUInt(const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(NVT_POSITION, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_position->*m_uintFunction)();}
protected:
	UIntFunction m_uintFunction;
};

class TU_API PositionValueUIntCount : public NamedValueUInt
{
public:
	typedef VType (Position::*UIntFunction)() const;
	PositionValueUIntCount(const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(NVT_POSITION, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const;
//	virtual const VType& GetObjectValue() const{return (m_position->*m_uintFunction)();}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_position->*m_uintFunction)());
		}
	}
protected:
	UIntFunction m_uintFunction;
};

class TU_API PositionValueMoney2 : public PositionValueMoney
{
public:
	PositionValueMoney2(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueMoney(valueColorCoded, name, moneyFunction, sample, tip, displayName, parent),
		m_moneyFunction2(moneyFunction2)
	{
	}
	virtual NamedValue* Clone() const;
//	virtual const VType& GetObjectValue() const{return (m_position->*m_moneyFunction)();}
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_position->*m_moneyFunction)() + (m_position->*m_moneyFunction2)());
		}
	}
protected:
	MoneyFunction m_moneyFunction2;
};

class TU_API PositionValueMoney3 : public PositionValueMoney2
{
public:
	PositionValueMoney3(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueMoney2(valueColorCoded, name, moneyFunction, moneyFunction2, sample, tip, displayName, parent),
		m_moneyFunction3(moneyFunction3)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_position->*m_moneyFunction)() + (m_position->*m_moneyFunction2)() + (m_position->*m_moneyFunction3)());
		}
	}
protected:
	MoneyFunction m_moneyFunction3;
};

class TU_API PositionValueMoney3Minus : public PositionValueMoney3
{
public:
	PositionValueMoney3Minus(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueMoney3(valueColorCoded, name, moneyFunction, moneyFunction2, moneyFunction3, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_position->*m_moneyFunction)() + (m_position->*m_moneyFunction2)() - (m_position->*m_moneyFunction3)());
		}
	}
};

class TU_API AccountValueBool : public NamedValueBool
{
public:
	typedef const VType& (Account::*BoolFunction)() const;
	AccountValueBool(const char* name, BoolFunction boolFunction, const char* sample, const char* tip, const char* yesValue = "Yes", const char* noValue = "No", bool useColor = false, bool reverse = false, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueBool(NVT_ACCOUNT, name, sample, tip, yesValue, noValue, useColor, reverse, displayName, parent),
		m_boolFunction(boolFunction)
	{
	}
	virtual NamedValue* Clone() const;
//	virtual COLORREF GetValueColor() const;
	virtual const VType& GetObjectValue() const{return (m_account->*m_boolFunction)();}
protected:
	BoolFunction m_boolFunction;
};

class TU_API AccountValueChar : public NamedValueChar
{
public:
	typedef const VType& (Account::*CharFunction)() const;
	AccountValueChar(const char* name, CharFunction charFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, char emptyValue = '\0', char negativeValue = '\0'):
		NamedValueChar(NVT_ACCOUNT, name, sample, tip, displayName, parent, emptyValue, negativeValue),
		m_charFunction(charFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_account->*m_charFunction)();}
protected:
	CharFunction m_charFunction;
};

class TU_API AccountValueMoney : public NamedValueMoney
{
public:
	typedef const VType& (Account::*MoneyFunction)() const;
	AccountValueMoney(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_ACCOUNT, valueColorCoded, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_account->*m_moneyFunction)();}
protected:
	MoneyFunction m_moneyFunction;
};

class TU_API AccountValuePrice : public NamedValuePrice
{
public:
	typedef const VType& (Account::*PriceFunction)() const;
	AccountValuePrice(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePrice(NVT_ACCOUNT, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_account->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API AccountValueCharPtr : public NamedValueCharPtr
{
public:
//	typedef const char* const& (Account::*CharPtrFunction)() const;
	typedef const char* (Account::*CharPtrFunction)() const;
	AccountValueCharPtr(const char* name, CharPtrFunction charPtrFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueCharPtr(NVT_ACCOUNT, name, sample, tip, displayName, parent),
		m_charPtrFunction(charPtrFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_account->*m_charPtrFunction)());
		}
	}
protected:
	CharPtrFunction m_charPtrFunction;
};

class TU_API AccountValueMoney2 : public AccountValueMoney
{
public:
	AccountValueMoney2(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueMoney(valueColorCoded, name, moneyFunction, sample, tip, displayName, parent),
		m_moneyFunction2(moneyFunction2)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_account->*m_moneyFunction)() + (m_account->*m_moneyFunction2)());
		}
	}
protected:
	MoneyFunction m_moneyFunction2;
};

class TU_API AccountValueMoneyDiff : public AccountValueMoney
{
public:
	AccountValueMoneyDiff(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueMoney(valueColorCoded, name, moneyFunction, sample, tip, displayName, parent),
		m_moneyFunction2(moneyFunction2)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_account->*m_moneyFunction)() - (m_account->*m_moneyFunction2)());
		}
	}
protected:
	MoneyFunction m_moneyFunction2;
};

class TU_API AccountValueMoney3 : public AccountValueMoney2
{
public:
	AccountValueMoney3(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueMoney2(valueColorCoded, name, moneyFunction, moneyFunction2, sample, tip, displayName, parent),
		m_moneyFunction3(moneyFunction3)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_account->*m_moneyFunction)() + (m_account->*m_moneyFunction2)() + (m_account->*m_moneyFunction3)());
		}
	}
protected:
	MoneyFunction m_moneyFunction3;
};

class TU_API AccountValueMoney3Minus : public AccountValueMoney3
{
public:
	AccountValueMoney3Minus(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueMoney3(valueColorCoded, name, moneyFunction, moneyFunction2, moneyFunction3, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
			SetValue((m_account->*m_moneyFunction)() + (m_account->*m_moneyFunction2)() - (m_account->*m_moneyFunction3)());
		}
	}
};

/*
class TU_API AccountMPNLNet : public NamedValueMoney
{
public:
	AccountMPNLNet(bool valueColorCoded, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_ACCOUNT, valueColorCoded, name, sample, tip, displayName, parent),
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return m_account->GetClosedPnl() + m_account->GetOpenPnlLevel1() - m_account->GetCommissionPer1000Shares().Money::operator*(m_account->GetSharesTraded()).Money::operator/(1000);}
};
*/
class TU_API AccountValueUShort : public NamedValueUShort
{
public:
	typedef const VType& (Account::*UShortFunction)() const;
	AccountValueUShort(const char* name, UShortFunction ushortFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUShort(NVT_ACCOUNT, name, sample, tip, displayName, parent),
		m_ushortFunction(ushortFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_account->*m_ushortFunction)();}
protected:
	UShortFunction m_ushortFunction;
};

class TU_API AccountValueUInt : public NamedValueUInt
{
public:
	typedef const VType& (Account::*UIntFunction)() const;
	AccountValueUInt(const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(NVT_ACCOUNT, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual const VType& GetObjectValue() const{return (m_account->*m_uintFunction)();}
protected:
	UIntFunction m_uintFunction;
};

class TU_API AccountValueCount : public NamedValueUInt
{
public:
	typedef unsigned int (Account::*CountFunction)() const;
	AccountValueCount(const char* name, CountFunction countFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(NVT_ACCOUNT, name, sample, tip, displayName, parent),
		m_countFunction(countFunction)
	{
	}
	virtual NamedValue* Clone() const;
	virtual void UpdateValue()
	{
		if(m_valid)
		{
//			unsigned int count = (m_account->*m_countFunction)();
			SetValue((m_account->*m_countFunction)());
/*
			if(m_value != count)
			{
				m_value = count;
				m_parent->GetWnd()->InvalidateRect(m_rectValue, FALSE);
			}
*/
		}
	}
protected:
	CountFunction m_countFunction;
};

class TU_API AccountRecoveryErrorCode : public AccountValueUShort
{
public:
	AccountRecoveryErrorCode(const char* name, UShortFunction ushortFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueUShort(name, ushortFunction, sample, tip, displayName, parent)
	{
	}
	static const char* const okText;
	static const char* const notLoadedText;
	virtual NamedValue* Clone() const;
	virtual COLORREF GetValueColor() const;
	virtual void toString(std::string& str) const;
};

class DestinationRouting
{
public:
	DestinationRouting(const char* name, unsigned short id, unsigned short subType, char label, const char* description, unsigned int minReserveQuantity, unsigned int maxReserveQuantity, const char* reserveName):
		m_name(name),
		m_description(description ? description : m_name),
		m_id(id),
		m_subType(subType),
		m_superId(((unsigned int)m_subType << 16) | (unsigned int)m_id),
		m_minReserveQuantity(minReserveQuantity),
		m_maxReserveQuantity(maxReserveQuantity),
		m_reserveName(reserveName ? reserveName : ""),
		m_label(label)
	{
		m_numericName = U_StringToUInt(m_name.c_str());//*(unsigned int*)m_name.c_str();
	}
	const std::string& GetName() const{return m_name;}
	const char* GetNameStr() const{return m_name.c_str();}
	const std::string& GetDescription() const{return m_description;}
	unsigned int GetNumericName() const{return m_numericName;}
	unsigned short GetId() const{return m_id;}
	unsigned short GetSubType() const{return m_subType;}
	unsigned int GetSuperId() const{return m_superId;}
	char GetLabel() const{return m_label;}
	unsigned int GetMinReserveQuantity() const{return m_minReserveQuantity;}
	unsigned int GetMaxReserveQuantity() const{return m_maxReserveQuantity;}
	const std::string& GetReserveName() const{return m_reserveName;}
protected:
	std::string m_name;
	std::string m_description;
	unsigned int m_numericName;
	unsigned short m_id;
	unsigned short m_subType;
	unsigned int m_superId;
	unsigned int m_minReserveQuantity;
	unsigned int m_maxReserveQuantity;
	std::string m_reserveName;
	char m_label;
};

enum SupportHidden : unsigned char
{
	SH_NEVER = 0,
	SH_NON_IOC = 1,
	SH_IOC = 2,
	SH_ALWAYS = 3,
};

enum SupportExpiration : unsigned char
{
	SE_YES = 0,
	SE_NO = 1,
	SE_TAKION = 2,
};

enum SupportTifExtended : unsigned char
{
	STE_NO = 0,
	STE_YES = 1,
};

enum MnemonicType : unsigned char
{
	MT_NONE = 0,
	MT_MNEMONIC,
	MT_MM,
};

class TU_API Destination
{
public:
	static const unsigned char nameCount = 3;
	Destination(const char* name,
#ifndef TAKION_NO_OPTIONS
		const char* optionName,
		unsigned char optionSource,
#endif
		unsigned int id,
		unsigned char source,
		unsigned char hasMnemonic,
		bool borrow,
		unsigned char supportsHidden,
		unsigned char supportsExpiration,
		unsigned char supportsTifExtended,
		bool qsmtReplaceable,
		unsigned short noRoutingReplacementId,
		unsigned short proActiveReplacementId,
		const char* altName1,
		const char* altName2);
//		const char* noRoutingReplacementName,
//		const char* proActiveReplacementName);
	Destination(const Destination& other);
	~Destination(){ClearRoutings();}
	Destination& operator=(const Destination& other);

	const char* GetMainName() const{return m_name->c_str();}
	const std::string& GetMainNameStr() const{return *m_name;}
	unsigned int GetMainNumericName() const
	{
		return
#ifndef TAKION_NO_OPTIONS
			!*m_numericName ? m_optionNumericName:
#endif
			*m_numericName;
	}
/*
	const char* GetAltName() const{return m_altName.c_str();}
	const std::string& GetAltNameStr() const{return m_altName;}
	unsigned int GetNumericAltName() const{return m_numericAltName;}
*/
	const std::string& GetProperNameStr(unsigned char itg) const
	{
		if(itg >= nameCount)itg = 0;
		return
#ifndef TAKION_NO_OPTIONS
			m_name->empty() ? m_optionName:
#endif
			itg && m_numericName[itg] ? m_name[itg] : *m_name;
	}
	const char* GetProperName(unsigned char itg) const{return GetProperNameStr(itg).c_str();}
	unsigned int GetNumericProperName(unsigned char itg) const
	{
		if(itg >= nameCount)itg = 0;
		return
#ifndef TAKION_NO_OPTIONS
			!*m_numericName ? m_optionNumericName:
#endif
			itg && m_numericName[itg] ? m_numericName[itg] : *m_numericName;
	}

#ifndef TAKION_NO_OPTIONS
	const std::string& GetOptionNameStr() const{return m_optionName;}
	const char* GetOptionName() const{return m_optionName.c_str();}
	unsigned int GetOptionNumericName() const{return m_optionNumericName;}
	unsigned char GetOptionSource() const{return m_optionSource;}
	unsigned int GetApplicability() const{return (m_numericName[0] ? 1 << ST_STOCK : 0) | (m_optionNumericName ? 1 << ST_OPTION : 0);}
#endif
	unsigned int GetId() const{return m_id;}
	unsigned char GetSource() const{return m_source;}
	bool isBorrow() const{return m_borrow;}
	unsigned char HasMnemonic() const{return m_hasMnemonic;}
	unsigned char GetSupportHidden() const{return m_supportsHidden;}
	unsigned char GetSupportExpiration() const{return m_supportsExpiration;}
	unsigned char GetSupportTifExtended() const{return m_supportsTifExtended;}
	char GetExpirationTif() const
	{
		return m_supportsExpiration == SE_YES ? TIF_GTD : m_supportsTifExtended ? TIF_GTX : TIF_DAY;
	}
	bool SetSupportTakionExpiration(bool support)
	{
		if(!(m_supportsExpiration & SE_NO))
		{
			if(support)
			{
				m_supportsExpiration |= SE_TAKION;
			}
			else
			{
				m_supportsExpiration &= ~SE_TAKION;
			}
			return true;
		}
		return false;
	}

	bool isQsmtReplaceable() const{return m_qsmtReplaceable;}

	typedef std::map<unsigned int, const DestinationRouting*> RoutingMap;
	DestinationRouting* AddRouting(const char* name, unsigned short id, unsigned short subtype, char label, const char* description, unsigned int minReserveQuantity = 0, unsigned int maxReserveQuantity = 0, const char* reserveName = NULL);
	void ClearRoutings();
	unsigned int GetRoutingCount() const{return (unsigned int)m_routingMap.size();}
	const RoutingMap& GetRoutingMap() const{return m_routingMap;}
	const DestinationRouting* FindRouting(unsigned short id, unsigned short subtype) const{RoutingMap::const_iterator found = m_routingMap.find(((unsigned int)subtype << 16) | (unsigned int)id); return found == m_routingMap.end() ? NULL : found->second;}
	const DestinationRouting* FindRoutingBySuperId(unsigned int superId) const{RoutingMap::const_iterator found = m_routingMap.find(superId); return found == m_routingMap.end() ? NULL : found->second;}

	const RoutingMap& GetRoutingNameMap() const{return m_routingNameMap;}
	const DestinationRouting* FindRoutingByNumericName(unsigned int numericName) const{RoutingMap::const_iterator found = m_routingNameMap.find(numericName); return found == m_routingNameMap.end() ? NULL : found->second;}
	const DestinationRouting* FindRoutingByName(const char* name) const{return FindRoutingByNumericName(U_StringToUInt(name));}

	void CopyRoutings(const Destination& other);
	const DestinationRouting* GetNoRoutingReplacement() const{return m_noRoutingReplacement;}
	const DestinationRouting* GetProActiveReplacement() const{return m_proActiveReplacement;}
//	const std::string& GetNoRoutingReplacementName() const{return m_noRoutingReplacementName;}
//	const std::string& GetProActiveReplacementName() const{return m_proActiveReplacementName;}
	unsigned short GetNoRoutingReplacementId() const{return m_noRoutingReplacementId;}
	unsigned short GetProActiveReplacementId() const{return m_proActiveReplacementId;}
protected:
	std::string m_name[nameCount];
//	std::string m_altName;
	unsigned int m_numericName[nameCount];
#ifndef TAKION_NO_OPTIONS
	std::string m_optionName;
	unsigned int m_optionNumericName;
	unsigned char m_optionSource;
#endif
//	unsigned int m_numericAltName;
	unsigned int m_id;
	unsigned char m_source;
	bool m_borrow;
	unsigned char m_hasMnemonic;//MnemonicType: 1 - MT_MNEMONIC; 2 - MT_MM;
	unsigned char m_supportsHidden;
	unsigned char m_supportsExpiration;
	unsigned char m_supportsTifExtended;
	bool m_qsmtReplaceable;
	RoutingMap m_routingMap;
	RoutingMap m_routingNameMap;
//	std::string m_noRoutingReplacementName;
//	std::string m_proActiveReplacementName;
	unsigned short m_noRoutingReplacementId;
	unsigned short m_proActiveReplacementId;
	const DestinationRouting* m_noRoutingReplacement;
	const DestinationRouting* m_proActiveReplacement;
};

class DestinationRoutingPair
{
public:
	DestinationRoutingPair(const Destination* destination, const DestinationRouting* routing, bool own):
		m_destination(destination),
		m_routing(routing),
		m_nameId(((unsigned __int64)routing->GetNumericName() << 32) | destination->GetMainNumericName()),
		m_superId(((unsigned __int64)routing->GetSuperId() << 32) | destination->GetId()),
		m_own(own)
	{
	}
	DestinationRoutingPair(const DestinationRoutingPair& other):
		m_destination(other.m_destination),
		m_routing(other.m_own && other.m_routing ? new DestinationRouting(*other.m_routing) : other.m_routing),
		m_nameId(other.m_nameId),
		m_superId(other.m_superId),
		m_own(other.m_own)
	{}
	~DestinationRoutingPair(){if(m_own && m_routing)delete m_routing;}
	DestinationRoutingPair& operator=(const DestinationRoutingPair& other)
	{
		m_destination = other.m_destination;
		if(m_own && m_routing)delete m_routing;
		m_routing = other.m_own && other.m_routing ? new DestinationRouting(*other.m_routing) : other.m_routing;
		m_nameId = other.m_nameId;
		m_superId = other.m_superId;
		m_own = other.m_own;
		return *this;
	}
	const Destination* GetDestination() const{return m_destination;}
	const DestinationRouting* GetRouting() const{return m_routing;}
	const unsigned __int64& GetNameId() const{return m_nameId;}
	const unsigned __int64& GetSuperId() const{return m_superId;}
protected:
	const Destination* m_destination;
	const DestinationRouting* m_routing;
	unsigned __int64 m_nameId;
	unsigned __int64 m_superId;
	bool m_own;
};

class DestinationRoutingPairAndMnemonic : public DestinationRoutingPair
{
public:
	DestinationRoutingPairAndMnemonic(const Destination* destination, const DestinationRouting* routing, bool own, unsigned int mnemonic, bool ignorePeg):
		DestinationRoutingPair(destination, routing, own),
		m_mnemonic(mnemonic),
		m_ignorePeg(ignorePeg)
	{
	}
	DestinationRoutingPairAndMnemonic(const DestinationRoutingPair& other, unsigned int mnemonic, bool ignorePeg):
		DestinationRoutingPair(other),
		m_mnemonic(mnemonic),
		m_ignorePeg(ignorePeg)
	{
	}
	const unsigned int& GetMnemonic() const{return m_mnemonic;}
	void SetMnemonic(const unsigned int& mnemonic){m_mnemonic = mnemonic;}
	const bool& isIgnorePeg() const{return m_ignorePeg;}
	void SetIgnorePeg(const bool& ignorePeg){m_ignorePeg = ignorePeg;}
protected:
	unsigned int m_mnemonic;
	bool m_ignorePeg;
};

////////////////////
/*
class TMsgExitMessageThread : public Message
{
public:
	TMsgExitMessageThread():Message(0, sizeof(TMsgExitMessageThread)){}
};
*/
class RingBufferListEventNotification;

class TU_API MessageThread
{
friend class MessageReader;
friend unsigned int __stdcall MessageThreadFunction(void* data);
public:
	virtual ~MessageThread();
	DWORD Start() const{return ResumeThread(m_threadHandle);}
	DWORD Suspend() const{return SuspendThread(m_threadHandle);}
	HANDLE GetThreadHandle() const{return m_threadHandle;}
	const unsigned int& GetThreadId() const{return m_threadId;}
	void WriteMessage(const Message* message);//called from main thread
//	void WriteControlMessage(const Message* message);//called from main thread
	void WriteBuffers(WSABUF* data, unsigned int count);//called from main thread
	const bool& isDataOk() const{return m_dataOk;}
	const std::string& GetName() const{return m_name;}
	const int& GetPriority() const{return m_priority;}
protected:
	MessageThread(const char* name, int priority = 0, unsigned int waitToTerminate = INFINITE, unsigned int padSize = 0);
	virtual void OnThreadFunctionStarted(){}
	virtual bool ProcessDataMessage(const Message* message) = 0;
	virtual bool DoIdle(unsigned int idleCount){return false;}
//	virtual bool ProcessControlMessage(const Message* message) = 0;
	virtual void NotifyOverflow(){}
	void LogThreadInfo(const char* prefix) const;
	void InvalidateData();
	void Terminate()//Call this function in the derived class Destructor to finish all data processing
	{
		m_dataOk = false;
		SetEvent(m_event);
		WaitForSingleObject(m_threadHandle, m_waitToTerminate);
	}
	void FlushIdle(){for(unsigned int idleCount = 0; DoIdle(idleCount); ++idleCount);}

	HANDLE m_threadHandle;
	unsigned int m_threadId;
//	HANDLE m_threadReadyEvent;
	int m_priority;
	unsigned int m_waitToTerminate;

	void ReadMessage();//called from this thread
	HANDLE m_event;
	RingBufferListEventNotification* m_ringBuffer;
	MessageReader* m_messageReader;
//	LineBufferArray m_bufferArray;
/*	
	bool ReadControlMessage();//called from this thread
	HANDLE m_controlEvent;
	RingBufferListEventNotification* m_controlRingBuffer;
	MessageReader* m_controlMessageReader;
*/
	bool m_dataOk;
	std::string m_name;
/*
	CCriticalSection m_dataCriticalSection;
*/
};

////////////////////
