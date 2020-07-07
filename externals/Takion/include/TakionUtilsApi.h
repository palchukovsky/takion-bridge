#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef TU_EXPORTS
#define TU_API __declspec(dllexport)
#else
#define TU_API __declspec(dllimport)
#endif

#include <TakionMemoryApi.h>
#include <UtilsApi.h>
#include <ObserverApi.h>
#include <TakionLogApi.h>

#include <afxtempl.h>
#include <list>
#include <vector>

//#define VERIFY_QUOTES
//#ifdef _DEBUG
//#define PENDING_SHARES_VALIDITY
//#define BP_VALIDITY
//#endif

#define FIRM_VALUES

//#define LRPS
//#define USE_THRESHOLD_INDICATOR_AS_UNSHORTABLE

//#define SEND_LOCATE_INFO

#ifdef FIRM_VALUES
#define FIRM_VALUES_ALWAYS
#endif

#if defined(T_RELEASED)// || defined(_DEBUG)
#define LOG_UPDATE_STOCK
#endif

#define PILLAR_MIGRATION_NOT_COMPLETE

//#define EXCH_OPEN_PRICE

const char* const TakionUtilsHeaderVersion = "1.0.4.222";

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
	TMsgCustom(const unsigned short& customId, const unsigned short& type, const unsigned short& length):Message(type, length), m_customId(customId){}
};

class TMsgCustomExternal : public TMsgCustom
{
protected:
	TMsgCustomExternal(const unsigned short& customId, const unsigned short& length):TMsgCustom(customId, TM_CUSTOM_EXTERNAL, length){}
};

class TMsgCustomInternal : public TMsgCustom
{
protected:
	TMsgCustomInternal(const unsigned short& customId, const unsigned short& length):TMsgCustom(customId, TM_CUSTOM_INTERNAL, length){}
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

#define Chars2ToUInt(Char1, Char2) Char1|(Char2 << 8)
#define Chars3ToUInt(Char1, Char2, Char3) Char1|(Char2 << 8)|(Char3 << 16)
#define Chars4ToUInt(Char1, Char2, Char3, Char4) Char1|(Char2 << 8)|(Char3 << 16)|(Char4 << 24)

#ifdef __cplusplus
extern "C"
{
#endif

const unsigned int inetNum =	Chars4ToUInt('I', 'N', 'E', 'T');//0x54454E49;//*(unsigned int*)"INET";
const unsigned int edgeNum =	Chars4ToUInt('E', 'D', 'G', 'E');//0x45474445;//*(unsigned int*)"EDGE";
const unsigned int luldNum =	Chars4ToUInt('L', 'U', 'L', 'D');//0x444C554C;//*(unsigned int*)"LULD";
#ifdef LRPS
const unsigned int lrpNum =		Chars3ToUInt('L', 'R', 'P');//0x50524C;//*(unsigned int*)"LRP";
#endif
const unsigned int nysNum =		Chars4ToUInt('N', 'Y', 'S', 'E');//0x4553594E;//*(unsigned int*)"NYSE";
const unsigned int nysTopNum =	Chars3ToUInt('N', 'Y', 'S');//0x53594E;//*(unsigned int*)"NYS";
const unsigned int amexNum =	Chars4ToUInt('A', 'M', 'E', 'X');//0x58454D41;//*(unsigned int*)"AMEX";
const unsigned int amexTopNum = Chars3ToUInt('A', 'M', 'X');//0x584D41;//*(unsigned int*)"AMX";
const unsigned int nsdqNum =	Chars4ToUInt('N', 'S', 'D', 'Q');//0x5144534E;//*(unsigned int*)"NSDQ";
const unsigned int arcaNum =	Chars4ToUInt('A', 'R', 'C', 'A');//0x41435241;//*(unsigned int*)"ARCA";
const unsigned int batsNum =	Chars4ToUInt('B', 'A', 'T', 'S');//0x53544142;//*(unsigned int*)"BATS";
const unsigned int batyNum =	Chars4ToUInt('B', 'A', 'T', 'Y');//0x59544142;//*(unsigned int*)"BATY";
const unsigned int edgxNum =	Chars4ToUInt('E', 'D', 'G', 'X');//0x58474445;//*(unsigned int*)"EDGX";
const unsigned int edgaNum =	Chars4ToUInt('E', 'D', 'G', 'A');//0x41474445;//*(unsigned int*)"EDGA";
const unsigned int phlxNum =	Chars4ToUInt('P', 'H', 'L', 'X');//0x584C4850;//*(unsigned int*)"PHLX";
const unsigned int bosxNum =	Chars4ToUInt('B', 'O', 'S', 'X');//0x58534F42;//*(unsigned int*)"BOSX";
const unsigned int chsxNum =	Chars4ToUInt('C', 'H', 'S', 'X');//0x58534843;//*(unsigned int*)"CHSX";
//const unsigned int nsxxNum =	Chars4ToUInt('N', 'S', 'X', 'X');//0x5858534E;//*(unsigned int*)"NSXX";
const unsigned int nsxNum =		Chars3ToUInt('N', 'S', 'X');//0x58534E;//*(unsigned int*)"NSX";
const unsigned int nsexNum =	Chars4ToUInt('N', 'S', 'E', 'X');//0x5845534E;//*(unsigned int*)"NSEX";
const unsigned int ubsNum =		Chars3ToUInt('U', 'B', 'S');//0x534255;//*(unsigned int*)"UBS";
const unsigned int jpmNum =		Chars3ToUInt('J', 'P', 'M');//0x4D504A;//*(unsigned int*)"JPM";
const unsigned int iexNum =		Chars3ToUInt('I', 'E', 'X');//0x584549;//*(unsigned int*)"IEX";
const unsigned int poolNum =	Chars4ToUInt('P', 'O', 'O', 'L');//0x4C4F4F50;//*(unsigned int*)"POOL";
const unsigned int cscfNum =	Chars4ToUInt('C', 'S', 'C', 'F');//0x46435343;//*(unsigned int*)"CSCF";
//const unsigned int itgNum =		Chars3ToUInt('I', 'T', 'G');//0x475449;//*(unsigned int*)"ITG";
const unsigned int pdqNum =		Chars3ToUInt('P', 'D', 'Q');//0x514450;//*(unsigned int*)"PDQ";
//const unsigned int daxxNum =	Chars4ToUInt('D', 'A', 'X', 'X');//0x58584144;//*(unsigned int*)"DAXX";
const unsigned int qsmtNum =	Chars4ToUInt('Q', 'S', 'M', 'T');//0x544D5351;//*(unsigned int*)"QSMT";
//const unsigned int flowNum =	Chars4ToUInt('F', 'L', 'O', 'W');//0x574F4C46;//*(unsigned int*)"FLOW";
//const unsigned int niteNum =	Chars4ToUInt('N', 'I', 'T', 'E');//0x4554494E;//*(unsigned int*)"NITE";
const unsigned int virtNum =	Chars4ToUInt('V', 'I', 'R', 'T');
const unsigned int apexNum =	Chars4ToUInt('A', 'P', 'E', 'X');//0x58455041;//*(unsigned int*)"APEX";
const unsigned int lynxNum =	Chars4ToUInt('L', 'Y', 'N', 'X');//0x584E594C;//*(unsigned int*)"LYNX";
const unsigned int dashNum =	Chars4ToUInt('D', 'A', 'S', 'H');//0x48534144;//*(unsigned int*)"DASH";
const unsigned int otcbNum =	Chars4ToUInt('O', 'T', 'C', 'B');//0x4243544F;//*(unsigned int*)"OTCB";
const unsigned int othrNum =	Chars4ToUInt('O', 'T', 'H', 'R');//0x5248544F;//*(unsigned int*)"OTHR";
const unsigned short nysShortNum = Chars2ToUInt('N', 'Y');//0x594E;//*(unsigned short*)"NY";
const unsigned short amexShortNum = Chars2ToUInt('A', 'X');//0x5841;//*(unsigned short*)"AX";
const unsigned short nsdqShortNum = Chars2ToUInt('N', 'Q');//0x514E;//*(unsigned short*)"NQ";

#ifndef TAKION_NO_OPTIONS
const unsigned int boxNum =		Chars3ToUInt('B', 'O', 'X');//0x584F42;//"BOX";
const unsigned int c2Num =		Chars2ToUInt('C', '2');//0x3243;//"C2";
const unsigned int iseNum =		Chars3ToUInt('I', 'S', 'E');//0x455349;//"ISE";
const unsigned int gemNum =		Chars3ToUInt('G', 'E', 'M');//0x4D4547;//"GEM";

const unsigned int opraNum =	Chars4ToUInt('O', 'P', 'R', 'A');//0x4152504F;//*(unsigned int*)"OPRA";

const unsigned short eoNum =	Chars2ToUInt('E', 'U');//0x5545;//*(unsigned short*)"EU";//equity option
const unsigned short ioNum =	Chars2ToUInt('I', 'U');//0x5549;//*(unsigned short*)"IU";//equity option
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
	MC_IEX = 'V',
	MC_BATS = 'Z',
//#ifndef TAKION_NO_OPTIONS
	MC_OPRA = 'o',
//#endif
};

enum PrimaryExchange : char
{
	PE_OTHR	= ' ',
	PE_AMEX	= 'A',
	PE_NYSE	= 'N',
	PE_ARCA	= 'P',
	PE_NSDQ	= 'Q',
	PE_OTCB	= 'U',
	PE_BATS	= 'Z',
	PE_IEX = 'V',
};

enum PrimaryExchangeEnum : unsigned char
{
	PEE_OTHR,
	PEE_AMEX,
	PEE_NYSE,
	PEE_ARCA,
	PEE_NSDQ,
	PEE_OTCB,
	PEE_BATS,
	PEE_IEX,
#ifndef TAKION_NO_OPTIONS
	PEE_OPRA,
#endif

	PEE_Count
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

const char* WINAPI TU_GetOrderEntitlementName(unsigned char entitlementId);

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

const unsigned __int64 mdeStockFlags =
	  (1ui64 << MDE_NSDQ)
	| (1ui64 << MDE_ARCA)
	| (1ui64 << MDE_BATS)
	| (1ui64 << MDE_BATY)
	| (1ui64 << MDE_EDGA)
	| (1ui64 << MDE_EDGX)
	| (1ui64 << MDE_NYSE)
	| (1ui64 << MDE_AMEX);

const char* WINAPI TU_GetEntitlementName(unsigned char entitlementId);

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

	MCF_IEX,

	MCF_COUNT,

#ifdef TAKION_NO_OPTIONS
	MCF_Count = MCF_COUNT,
#endif

	MCF_OPTION = MCF_COUNT,

	MCF_ALL_Count,

#ifndef TAKION_NO_OPTIONS
	MCF_Count = MCF_ALL_Count,
#endif
};

enum TradingStateFilter : unsigned char
{
	TSF_T,
	TSF_H,
	TSF_E,
	TSF_3,
	TSF_2,
	TSF_1,
	TSF_P,
	TSF_OTHER,

	TSF_Count
};

enum CircuitBreakerFilter : unsigned char
{
	CBF_E,
	CBF_3,
	CBF_2,
	CBF_1,
	CBF_0,
	CBF_D,
	CBF_SPACE,
	CBF_OTHER,

	CBF_Count
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
	NYS_IEX					= 'V' - 'A',
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
	NSDQ_IEX				= 'V' - 'A',
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
	| (1 << NYS_IEX)
	| (1 << NYS_CBOE)
	| (1 << NYS_NASDAQ_OMX_PHLX)
	| (1 << NYS_BATS_Y)
	| (1 << NYS_BATS)
	| (1 << NSDQ_NASDAQ_OMX);
/*
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
	STYPE_TEST						= 'T',
	STYPE_UNKNOWN					= 'U',
	STYPE_NSDQ_WARRANT				= 'W',
};
*/
enum SecurityTypes : char
{
	STYPE_UNDEFINED = '?',
	STYPE_ETF = '@',
	STYPE_ADR = 'A',
#ifdef PILLAR_MIGRATION_NOT_COMPLETE
	STYPE_PREFERRED_STOCK = 'B',
#endif
	STYPE_COMMON_STOCK = 'C',
	STYPE_DEBENTURES = 'D',
	STYPE_ETFE = 'E',
	STYPE_FOREIGN = 'F',
#ifdef PILLAR_MIGRATION_NOT_COMPLETE
	STYPE_STRUCTURED_PRODUCT = 'G',
#endif
	STYPE_US_DEPOSITARY_SHARES = 'H',
	STYPE_UNITS = 'I',
#ifdef PILLAR_MIGRATION_NOT_COMPLETE
	STYPE_ADR_WARRANT = 'J',
	STYPE_ADR_RIGHT = 'K',
#endif
	STYPE_INDEX_LINKED_NOTES = 'L',
	STYPE_MISC_LIQUID_TRUST = 'M',
#ifdef PILLAR_MIGRATION_NOT_COMPLETE
	STYPE_GLOBAL_REGISTERED_SHARE = 'N',
#endif
	STYPE_ORDINARY_SHARES = 'O',
	STYPE_PREF_STOCK = 'P',
#ifdef PILLAR_MIGRATION_NOT_COMPLETE
	STYPE_BASKET = 'Q',
#endif
	STYPE_RIGHTS = 'R',
	STYPE_SHARES_OF_BENEFICIARY_INTEREST = 'S',
	STYPE_TEST = 'T',
	STYPE_CLOSED_END_FUND = 'U',
	STYPE_WARRANT = 'W',
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

enum LiquidityType : unsigned char
{
	LT_REMOVED,
	LT_ADDED,

	LT_NEUTRAL,//For example, borrow

	LT_Count
};

enum TifType : unsigned char
{
//Order TIFS - match with FIX
	TIF_DAY	= '0',		//Day (or session)
	TIF_GTC = '1',		//Good Till Cancel (Should not be sent to the server. Send TIF_GTX instead. The order should be saved on the client machine and resent on start up)
	TIF_OPG = '2',		//At the Opening (OPG)
	TIF_IOC = '3',		//Immediate Or Cancel (IOC)
	TIF_FOK = '4',		//Fill Or Kill (FOK)
	TIF_GTX = '5',		//Good Till Crossing (GTX)
	TIF_GTD = '6',		//Good Till Date (GTD) - Milliseconds
	TIF_ATC = '7',		//At the Close
	TIF_GTT = '8',		//Good Till Time (Should not be sent to the server. Send TIF_GTD instead with calculated Milliseconds)
//Non FIX TIFs
//	GT_XPR = 'X',	// Express
//	GT_DAY_PLUS = 'P',	// Day Plus (Day+)	//-> Added 07/26/2004.
	TIF_LAST
};

enum RoundPriceMode : unsigned char
{
	RPM_PASSIVE,
	RPM_AGGRESSIVE,
	RPM_NEAREST,

	RPM_Count
};

enum MarketState : unsigned char
{
	MSTATE_PREMARKET,
	MSTATE_MARKET,
	MSTATE_POSTMARKET,

	MSTATE_Count
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

bool WINAPI TU_GetTifAsString(std::string& text, unsigned char tifType, bool monitorTif, const char* millisecondStr, unsigned int tifMillisecond, bool showMillisecond, const char* unknown, bool unknownValue);

enum PegType : unsigned char
{
	PEG_NONE,
	PEG_PRIMARY,
	PEG_MIDPOINT,
	PEG_MARKET,
	PEG_MIDPOINT_DISCRETIONARY,

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
const bool* WINAPI TU_GetClosedQuoteConditions(bool nasdaq);
bool WINAPI TU_IsClosedQuoteCondition(char condition, bool nasdaq);
unsigned int WINAPI TU_GetNasdaqQcFilterAll();
unsigned int WINAPI TU_GetListedQcFilterAll();

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
unsigned char WINAPI TU_CopyStringToClipboard(const std::string& info, HWND owner);

const char* WINAPI TU_GetMarketCategoryName(unsigned char marketCategory);
unsigned char WINAPI TU_GetMarketCategoryCount();
char WINAPI TU_GetMarketCategoryCharByMarketCategoryId(unsigned char id);

unsigned int WINAPI TU_GetPrimaryExchangeNameByExchangeEntitlementFlag(unsigned char exchangeEntitlementFlag);
char WINAPI TU_GetPrimaryExchangeCode(unsigned char ordinal);
const char* WINAPI TU_GetPrimaryExchangeNameByCode(char code);
const char* WINAPI TU_GetPrimaryExchangeNameByEnum(unsigned char ordinal);
unsigned char WINAPI TU_GetPrimaryExchangeCount();
char WINAPI TU_GetPrimaryExchangeByMarketCategory(char marketCategory);
char WINAPI TU_GetPrimaryExchangeByImbalanceId(unsigned char bookId);

bool WINAPI TU_IsCancelOversellInsteadOfResize();
void WINAPI TU_SetCancelOversellInsteadOfResize(bool cancel);

bool WINAPI TU_IsCancelOvershortInsteadOfResize();
void WINAPI TU_SetCancelOvershortInsteadOfResize(bool cancel);

unsigned int WINAPI TU_GetDQuoteMnemonicCount();
unsigned int WINAPI TU_GetDQuoteMnemonics(unsigned int* buffer, const unsigned int countOfUIntsThatFitsInBuffer);//returns the count of mnemonics placed in buffer.
bool WINAPI TU_AddDQuoteMnemonic(const unsigned int mnemonic);//call only from main thread
bool WINAPI TU_RemoveDQuoteMnemonic(const unsigned int mnemonic);//call only from main thread
bool WINAPI TU_ClearDQuoteMnemonics();//call only from main thread
bool WINAPI TU_SetDQuoteMnemonics(const unsigned int* cursor, unsigned int count);//call only from main thread

bool WINAPI TU_IsDQuoteMnemonic(const unsigned int mnemonic);

bool  WINAPI TU_LockInquiryDQuoteMnemonics();
void  WINAPI TU_LockInquiryWaitDQuoteMnemonics();
void  WINAPI TU_UnlockInquiryDQuoteMnemonics();
TakionIterator* WINAPI TU_CreateDQuoteMnemonicIterator();
const unsigned int* WINAPI TU_GetNextDQuoteMnemonic(TakionIterator* iterator);

//News Api
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

//EmailApi
typedef void* (WINAPI* ApiCreateEmail)(const char* serverName,//"Smtp.live.com";//hotmail; "Smtp.gmail.com"
	unsigned short serverPort,
	bool allowInvalidCertificate,
	unsigned int eSecurity,//TakionEmailSecurity
	const char* fromEmailAddress,
	const char* fromUser,
	const char* fromPassword,
	const char* fromName,//Can be NULL
	const char* subject,//Can be NULL
	const char* contents,//Can be NULL
	const char* replyTo,//Can be NULL
	const char* returnPath,//Can be NULL
	const char* organization,//Can be NULL
	const char* userAgent);//Can be NULL

typedef void (WINAPI* ApiVoidPtrCharPtr2)(void* email, const char* name, const char* address);
typedef void (WINAPI* ApiVoidPtrCharPtr3)(void* email, const char* path, const char* mimeType, const char* fileName);

//Extension API
typedef void (WINAPI* ApiVoid)();
typedef bool (WINAPI* ApiIs)();
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
typedef void (WINAPI* ApiUInt)(unsigned int);
typedef CWnd* (WINAPI* ApiCreteTool)(const char* id, const CBitmap* bitmap, unsigned int workspace, bool pinned);

typedef void (WINAPI* ApiUCharUCharString)(unsigned char ascii, unsigned char modifier, bool repeat, const char* commandName, unsigned int commandExtensionCode, unsigned int commandUserExtensionCode);
typedef void (WINAPI* ApiSymbolEntered)(const char* symbol, unsigned char securityType, bool valid, bool fromKeyboard, unsigned int ordinal);
typedef void (WINAPI* ApiStringSecurityBoolUInt)(const char* symbol, const Security* security, bool wasLoaded, unsigned int ordinal);
typedef bool (WINAPI* ApiUIntBool)(unsigned int idleCount, bool takionIdleDone);
typedef void (WINAPI* ApiAccount)(Account* account);
typedef void (WINAPI* ApiBool)(bool);

typedef void (WINAPI *ApiUCharMessageBool)(unsigned char connectionType, const Message* message, bool outgoing);

typedef void (WINAPI *ApiHwndCharPtr)(HWND hwnd, const char* prefix);
typedef void (WINAPI *ApiHwndCharPtr2)(HWND hwnd, const char* prefix, const char* symbol);
typedef void (WINAPI *ApiHwndCharPtrSecurity)(HWND hwnd, const char* prefix, const Security* security);
typedef void (WINAPI *ApiHwndCharPtrSecurityBool)(HWND hwnd, const char* prefix, const Security* security, bool added);

//ExtensionApi
unsigned int WINAPI GetExtensionCode();//must exist and return 1
void WINAPI ExtensionInitialize();
void WINAPI ExtensionTerminate();
unsigned __int64 WINAPI GetExtensionVersion();
unsigned __int64 WINAPI GetUtilsVersion();
unsigned __int64 WINAPI GetUtilsHeaderVersion();
unsigned __int64 WINAPI GetTakionUtilsVersion();
unsigned __int64 WINAPI GetTakionUtilsHeaderVersion();
unsigned __int64 WINAPI GetUtilsGuiVersion();
unsigned __int64 WINAPI GetUtilsGuiHeaderVersion();
unsigned __int64 WINAPI GetTakionGuiVersion();
unsigned __int64 WINAPI GetTakionGuiHeaderVersion();
unsigned __int64 WINAPI GetTakionDataVersion();
unsigned __int64 WINAPI GetTakionDataHeaderVersion();
unsigned __int64 WINAPI GetTakionLogVersion();
unsigned __int64 WINAPI GetTakionLogHeaderVersion();
unsigned __int64 WINAPI GetObserverVersion();
unsigned __int64 WINAPI GetObserverHeaderVersion();
unsigned __int64 WINAPI GetReceiverVersion();
unsigned __int64 WINAPI GetReceiverHeaderVersion();
bool WINAPI ExtensionIsDebug();
const char* WINAPI GetTakionExtensionDescription();
void WINAPI GetTakionExtensionMenu(std::string& menuStr);
void WINAPI ExecuteTakionCommand(unsigned short commandId, CWnd* takionExtensionWindow);
void WINAPI TakionMoveWindows(int dx, int dy);
void WINAPI KeyStrokeAndCommand(unsigned char ascii, unsigned char modifier, bool repeat, const char* commandName, unsigned int commandExtensionCode, unsigned int commandUserExtensionCode);//commandName can be NULL;
void WINAPI CommandWindowRemoved(unsigned int ordinal);
void WINAPI LayoutChanged();
void WINAPI SymbolEnteredInMmBox(const char* symbol, unsigned char securityType, bool valid, bool fromKeyboard, unsigned int ordinal);
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
void WINAPI NewSecondStarted();
void WINAPI LineDoubleClicked();
void WINAPI NextDayStarted();
void WINAPI MarketSorterNotifyAdded(HWND hwnd, const char* prefix);
void WINAPI MarketSorterContents(HWND hwnd, const char* prefix, const Security* security);
void WINAPI MarketSorterContentsDone(HWND hwnd, const char* prefix);
void WINAPI MarketSorterNotifyRemoved(HWND hwnd, const char* prefix);
void WINAPI MarketSorterNotifyPrefixChanged(HWND hwnd, const char* oldPrefix, const char* prefix);
void WINAPI NotifyMarketSorterSymbol(HWND hwnd, const char* prefix, const Security* security, bool added);
void WINAPI MarketSorterNotifyAllRowsRemoved(HWND hwnd, const char* prefix);

const char* WINAPI GetExtensionInfo();
bool WINAPI ExtensionIsStarted();//Function called from extension window menu
void WINAPI ExtensionStart(bool start);//Function called from extension window menu //false for stop
///////////////

unsigned char WINAPI TU_GetTradeLevel1FromCompactPrice(unsigned int price, unsigned int bid, unsigned int ask);

#ifdef __cplusplus
}
#endif


class TU_API ConstraintBase
{
public:
	ConstraintBase(bool simulation, unsigned char upper = 2, bool flags = false)://0 - lower, 1 - upper, 2 - upper with 0 as no constraint
		m_simulation(simulation),
		m_upper(upper),
		m_custom(false),
		m_flags(flags)
	{
	}
	virtual ~ConstraintBase(){}
	const unsigned char& GetUpper() const{return m_upper;}
	const bool& isFlags() const{return m_flags;}
	const bool& isCustom() const{return m_custom;}
	void SetCustom(const bool& custom){m_custom = custom;}
	const bool& isSimulation() const{return m_simulation;}
	void SetSimulation(const bool& simulation){m_simulation = simulation;}
	virtual bool isCustomEqual(const ConstraintBase& other) const{return m_custom == other.m_custom;}
	virtual void SetCustomEqual(const ConstraintBase& other){m_custom = other.m_custom;}
	virtual bool isCustomValueUsed() const{return true;}
	virtual bool isCustomValueNotUsed() const{return false;}
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
	bool isSimulationEqual(const ConstraintBase& other)
	{
		return m_simulation == other.m_simulation;
	}
	void SetSimulationEqual(const ConstraintBase& other)
	{
		m_simulation = other.m_simulation;
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
	bool m_flags;
};

template<class T>
class Constraint : public ConstraintBase
{
public:
	Constraint(const T& value, const T& zeroValue, bool simulation, unsigned char upper = 2, bool flags = false)://0 - lower, 1 - upper, 2 - upper with 0 as no constraint, 3 - always database value if no simulation
		ConstraintBase(simulation, upper, flags),
		m_value(value),
		m_customValue(value),
		m_zeroValue(zeroValue){}
	const T& GetValue() const{return m_value;}
	void SetValue(const T& value){m_value = value;}
	virtual bool isCustomValueUsed() const{return m_flags || GetCurrentValue() != m_value;}
	virtual bool isCustomValueNotUsed() const{return !m_flags && GetCurrentValue() != m_customValue;}
	const T& GetCurrentValue() const
	{
		return m_custom && (m_simulation || (m_upper == 2 ? m_customValue < m_value && m_customValue != m_zeroValue || m_value == m_zeroValue : m_upper == 1 ? m_customValue < m_value : m_value < m_customValue && !m_upper)) ? m_customValue : m_value;
	}
	const T& GetCurrentValueLive() const
	{
		return m_custom && (m_upper == 2 ? m_customValue < m_value && m_customValue != m_zeroValue || m_value == m_zeroValue : m_upper == 1 ? m_customValue < m_value : m_value < m_customValue && !m_upper) ? m_customValue : m_value;
	}
	T GetCurrentFlagsValue() const
	{
		return m_custom ? m_upper && m_upper != 3 && (m_upper == 1 || m_value != m_zeroValue) && !m_simulation ? m_customValue & m_value : m_customValue | m_value : m_value;
	}
	T GetCurrentFlagsValueLive() const
	{
		return m_custom ? m_upper && m_upper != 3 && (m_upper == 1 || m_value != m_zeroValue) ? m_customValue & m_value : m_customValue | m_value : m_value;
	}
	const T& GetCheckedValue() const{return m_custom ? m_customValue : m_value;}
	const T& GetCustomValue() const{return m_customValue;}
	T& GetCustomValue(){return m_customValue;}
	void SetCustomValue(const T& value){m_customValue = value;}
	void SetCustomValue(const T& value, bool custom){m_customValue = value; m_custom = custom;}
	void SetCurrentValue(const T& value)
	{
		if(m_simulation)
		{
			if(value != m_customValue)
			{
				m_customValue = value;
				m_custom = true;
			}
		}
		else m_value = value;
	}
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

class TU_API ConstraintCollection
{
public:
	ConstraintCollection(const char* id, bool simulation);
	virtual ~ConstraintCollection(){}
//	const char* const& GetId() const{return m_id;}

	const char* GetId() const{return m_id;}
	const AccountId& GetAccountId() const{return m_accountId;}

	const bool& isSimulation() const{return m_simulation;}
	virtual void SetSimulation(bool simulation);
	bool isCustomEqual(const ConstraintCollection& other) const;
	virtual void SetCustomEqual(const ConstraintCollection& other);

	virtual void SetCustomZero();

	Constraint<Money>& GetMarginExcessConstraint(){return m_marginExcess;}
	const Constraint<Money>& GetMarginExcessConstraint() const{return m_marginExcess;}
	const Money& GetMarginExcess() const{return m_marginExcess.GetCurrentValue();}

	Constraint<Money>& GetHardMarginExcessConstraint(){return m_hardMarginExcess;}
	const Constraint<Money>& GetHardMarginExcessConstraint() const{return m_hardMarginExcess;}
	const Money& GetHardMarginExcess() const{return m_hardMarginExcess.GetCurrentValue();}

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

	Constraint<Money>& GetMorningMaxPosInvestmentConstraint(){return m_morningMaxPosInvestment;}
	const Constraint<Money>& GetMorningMaxPosInvestmentConstraint() const{return m_morningMaxPosInvestment;}
	const Money& GetMorningMaxPosInvestment() const{return m_morningMaxPosInvestment.GetCurrentValue();}

	Constraint<Money>& GetDayMaxLongInvestmentConstraint(){return m_dayMaxLongInvestment;}
	const Constraint<Money>& GetDayMaxLongInvestmentConstraint() const{return m_dayMaxLongInvestment;}
	const Money& GetDayMaxLongInvestment() const{return m_dayMaxLongInvestment.GetCurrentValue();}

	Constraint<Money>& GetNightMaxLongInvestmentConstraint(){return m_nightMaxLongInvestment;}
	const Constraint<Money>& GetNightMaxLongInvestmentConstraint() const{return m_nightMaxLongInvestment;}
	const Money& GetNightMaxLongInvestment() const{return m_nightMaxLongInvestment.GetCurrentValue();}

	Constraint<Money>& GetMorningMaxLongInvestmentConstraint(){return m_morningMaxLongInvestment;}
	const Constraint<Money>& GetMorningMaxLongInvestmentConstraint() const{return m_morningMaxLongInvestment;}
	const Money& GetMorningMaxLongInvestment() const{return m_morningMaxLongInvestment.GetCurrentValue();}

	Constraint<Money>& GetDayMaxShortInvestmentConstraint(){return m_dayMaxShortInvestment;}
	const Constraint<Money>& GetDayMaxShortInvestmentConstraint() const{return m_dayMaxShortInvestment;}
	const Money& GetDayMaxShortInvestment() const{return m_dayMaxShortInvestment.GetCurrentValue();}

	Constraint<Money>& GetNightMaxShortInvestmentConstraint(){return m_nightMaxShortInvestment;}
	const Constraint<Money>& GetNightMaxShortInvestmentConstraint() const{return m_nightMaxShortInvestment;}
	const Money& GetNightMaxShortInvestment() const{return m_nightMaxShortInvestment.GetCurrentValue();}

	Constraint<Money>& GetMorningMaxShortInvestmentConstraint(){return m_morningMaxShortInvestment;}
	const Constraint<Money>& GetMorningMaxShortInvestmentConstraint() const{return m_morningMaxShortInvestment;}
	const Money& GetMorningMaxShortInvestment() const{return m_morningMaxShortInvestment.GetCurrentValue();}

	Constraint<Money>& GetNightMaxInvestmentConstraint(){return m_nightMaxInvestment;}
	const Constraint<Money>& GetNightMaxInvestmentConstraint() const{return m_nightMaxInvestment;}
	const Money& GetNightMaxInvestment() const{return m_nightMaxInvestment.GetCurrentValue();}

	Constraint<Money>& GetMorningMaxInvestmentConstraint(){return m_morningMaxInvestment;}
	const Constraint<Money>& GetMorningMaxInvestmentConstraint() const{return m_morningMaxInvestment;}
	const Money& GetMorningMaxInvestment() const{return m_morningMaxInvestment.GetCurrentValue();}

	Constraint<Money>& GetMaxLossConstraint(){return m_maxLoss;}
	const Constraint<Money>& GetMaxLossConstraint() const{return m_maxLoss;}
	const Money& GetMaxLoss() const{return m_maxLoss.GetCurrentValue();}

	Constraint<Money>& GetNightMaxLossConstraint(){return m_nightMaxLoss;}
	const Constraint<Money>& GetNightMaxLossConstraint() const{return m_nightMaxLoss;}
	const Money& GetNightMaxLoss() const{return m_nightMaxLoss.GetCurrentValue();}

	Constraint<Money>& GetMorningMaxLossConstraint(){return m_morningMaxLoss;}
	const Constraint<Money>& GetMorningMaxLossConstraint() const{return m_morningMaxLoss;}
	const Money& GetMorningMaxLoss() const{return m_morningMaxLoss.GetCurrentValue();}

	Constraint<Money>& GetMaxLossSlackConstraint(){return m_maxLossSlack;}
	const Constraint<Money>& GetMaxLossSlackConstraint() const{return m_maxLossSlack;}
	const Money& GetMaxLossSlack() const{return m_maxLossSlack.GetCurrentValue();}

	Constraint<Money>& GetMaxLossCloseConstraint(){return m_maxLossClose;}
	const Constraint<Money>& GetMaxLossCloseConstraint() const{return m_maxLossClose;}
	const Money& GetMaxLossClose() const{return m_maxLossClose.GetCurrentValue();}

	Constraint<Money>& GetNightMaxLossCloseConstraint(){return m_nightMaxLossClose;}
	const Constraint<Money>& GetNightMaxLossCloseConstraint() const{return m_nightMaxLossClose;}
	const Money& GetNightMaxLossClose() const{return m_nightMaxLossClose.GetCurrentValue();}

	Constraint<Money>& GetMorningMaxLossCloseConstraint(){return m_morningMaxLossClose;}
	const Constraint<Money>& GetMorningMaxLossCloseConstraint() const{return m_morningMaxLossClose;}
	const Money& GetMorningMaxLossClose() const{return m_morningMaxLossClose.GetCurrentValue();}

	const Money& GetMaxLoss90Percent() const{return m_maxLoss90Percent;}
	const Money& GetMaxLoss80Percent() const{return m_maxLoss80Percent;}

	Constraint<Money>& GetMaxLossPerPositionConstraint(){return m_maxLossPerPosition;}
	const Constraint<Money>& GetMaxLossPerPositionConstraint() const{return m_maxLossPerPosition;}
	const Money& GetMaxLossPerPosition() const{return m_maxLossPerPosition.GetCurrentValue();}

	Constraint<Money>& GetNightMaxLossPerPositionConstraint(){return m_nightMaxLossPerPosition;}
	const Constraint<Money>& GetNightMaxLossPerPositionConstraint() const{return m_nightMaxLossPerPosition;}
	const Money& GetNightMaxLossPerPosition() const{return m_nightMaxLossPerPosition.GetCurrentValue();}

	Constraint<Money>& GetMorningMaxLossPerPositionConstraint(){return m_morningMaxLossPerPosition;}
	const Constraint<Money>& GetMorningMaxLossPerPositionConstraint() const{return m_morningMaxLossPerPosition;}
	const Money& GetMorningMaxLossPerPosition() const{return m_morningMaxLossPerPosition.GetCurrentValue();}

	Constraint<Money>& GetMaxLossPerPositionSlackConstraint(){return m_maxLossPerPositionSlack;}
	const Constraint<Money>& GetMaxLossPerPositionSlackConstraint() const{return m_maxLossPerPositionSlack;}
	const Money& GetMaxLossPerPositionSlack() const{return m_maxLossPerPositionSlack.GetCurrentValue();}

	Constraint<Money>& GetMaxLossPerPositionCloseConstraint(){return m_maxLossPerPositionClose;}
	const Constraint<Money>& GetMaxLossPerPositionCloseConstraint() const{return m_maxLossPerPositionClose;}
	const Money& GetMaxLossPerPositionClose() const{return m_maxLossPerPositionClose.GetCurrentValue();}

	Constraint<Money>& GetNightMaxLossPerPositionCloseConstraint(){return m_nightMaxLossPerPositionClose;}
	const Constraint<Money>& GetNightMaxLossPerPositionCloseConstraint() const{return m_nightMaxLossPerPositionClose;}
	const Money& GetNightMaxLossPerPositionClose() const{return m_nightMaxLossPerPositionClose.GetCurrentValue();}

	Constraint<Money>& GetMorningMaxLossPerPositionCloseConstraint(){return m_morningMaxLossPerPositionClose;}
	const Constraint<Money>& GetMorningMaxLossPerPositionCloseConstraint() const{return m_morningMaxLossPerPositionClose;}
	const Money& GetMorningMaxLossPerPositionClose() const{return m_morningMaxLossPerPositionClose.GetCurrentValue();}

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

	Constraint<Price>& GetMinSharePriceConstraint(){return m_minSharePrice;}
	const Constraint<Price>& GetMinSharePriceConstraint() const{return m_minSharePrice;}
	const Price& GetMinSharePrice() const{return m_minSharePrice.GetCurrentValue();}

	Constraint<Price>& GetMaxSharePriceConstraint(){return m_maxSharePrice;}
	const Constraint<Price>& GetMaxSharePriceConstraint() const{return m_maxSharePrice;}
	const Price& GetMaxSharePrice() const{return m_maxSharePrice.GetCurrentValue();}

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

	Constraint<unsigned int>& GetMorningMaxPosSharesConstraint(){return m_morningMaxPosShares;}
	const Constraint<unsigned int>& GetMorningMaxPosSharesConstraint() const{return m_morningMaxPosShares;}
	const unsigned int& GetMorningMaxPosShares() const{return m_morningMaxPosShares.GetCurrentValue();}

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

	Constraint<unsigned int>& GetMaxOptionOpenPositionsConstraint(){return m_maxOptionOpenPositions;}
	const Constraint<unsigned int>& GetMaxOptionOpenPositionsConstraint() const{return m_maxOptionOpenPositions;}
	const unsigned int& GetMaxOptionOpenPositions() const{return m_maxOptionOpenPositions.GetCurrentValue();}

#endif

	Constraint<unsigned char>& GetIsoAllowedConstraint(){return m_isoAllowed;}
	const Constraint<unsigned char>& GetIsoAllowedConstraint() const{return m_isoAllowed;}
	const unsigned char& GetIsoAllowed() const{return m_isoAllowed.GetCurrentValue();}

	Constraint<unsigned char>& GetHtbTborrowOrdersAllowedConstraint(){return m_htbTborrowOrdersAllowed;}
	const Constraint<unsigned char>& GetHtbTborrowOrdersAllowedConstraint() const{return m_htbTborrowOrdersAllowed;}
	const unsigned char& GetHtbTborrowOrdersAllowed() const{return m_htbTborrowOrdersAllowed.GetCurrentValue();}

	Constraint<unsigned char>& GetConservativeOrderMarkingConstraint(){return m_conservativeOrderMarking;}
	const Constraint<unsigned char>& GetConservativeOrderMarkingConstraint() const{return m_conservativeOrderMarking;}
	const unsigned char& GetConservativeOrderMarking() const{return m_conservativeOrderMarking.GetCurrentValue();}

	Constraint<unsigned char>& GetLocalSideMarkingConstraint(){return m_localSideMarking;}
	const Constraint<unsigned char>& GetLocalSideMarkingConstraint() const{return m_localSideMarking;}
	const unsigned char& GetLocalSideMarking() const{return m_localSideMarking.GetCurrentValue();}

	Constraint<unsigned char>& GetPoolLocatesConstraint(){return m_poolLocates;}
	const Constraint<unsigned char>& GetPoolLocatesConstraint() const{return m_poolLocates;}
	const unsigned char& GetPoolLocates() const{return m_poolLocates.GetCurrentValue();}

	static const Price spoofingOffset;//(0, 100000000);
	static const Price layeringOffset;//(0, 30000000);

	Constraint<Price>& GetSpoofingBigPriceOffsetConstraint(){return m_spoofingBigPriceOffset;}
	const Constraint<Price>& GetSpoofingBigPriceOffsetConstraint() const{return m_spoofingBigPriceOffset;}
	const Price& GetSpoofingBigPriceOffset() const{return m_spoofingBigPriceOffset.GetCurrentValue();}

	Constraint<Price>& GetSpoofingSmallPriceOffsetConstraint(){return m_spoofingSmallPriceOffset;}
	const Constraint<Price>& GetSpoofingSmallPriceOffsetConstraint() const{return m_spoofingSmallPriceOffset;}
	const Price& GetSpoofingSmallPriceOffset() const{return m_spoofingSmallPriceOffset.GetCurrentValue();}

	Constraint<unsigned int>& GetSpoofingOrderCountRatioConstraint(){return m_spoofingOrderCountRatio;}
	const Constraint<unsigned int>& GetSpoofingOrderCountRatioConstraint() const{return m_spoofingOrderCountRatio;}
	const unsigned int& GetSpoofingOrderCountRatio() const{return m_spoofingOrderCountRatio.GetCurrentValue();}

	Constraint<unsigned int>& GetSpoofingOrderSizeRatioConstraint(){return m_spoofingOrderSizeRatio;}
	const Constraint<unsigned int>& GetSpoofingOrderSizeRatioConstraint() const{return m_spoofingOrderSizeRatio;}
	const unsigned int& GetSpoofingOrderSizeRatio() const{return m_spoofingOrderSizeRatio.GetCurrentValue();}

	Constraint<unsigned int>& GetAdvOrderCountConstraint(){return m_advOrderCount;}
	const Constraint<unsigned int>& GetAdvOrderCountConstraint() const{return m_advOrderCount;}
	const unsigned int& GetAdvOrderCount() const{return m_advOrderCount.GetCurrentValue();}

	Constraint<unsigned int>& GetAdvOrderSizePercentConstraint(){return m_advOrderSizePercent;}
	const Constraint<unsigned int>& GetAdvOrderSizePercentConstraint() const{return m_advOrderSizePercent;}
	const unsigned int& GetAdvOrderSizePercent() const{return m_advOrderSizePercent.GetCurrentValue();}

	Constraint<unsigned int>& GetAdvBorderConstraint(){return m_advBorder;}
	const Constraint<unsigned int>& GetAdvBorderConstraint() const{return m_advBorder;}
	const unsigned int& GetAdvBorder() const{return m_advBorder.GetCurrentValue();}

	Constraint<unsigned int>& GetAdvForceHiddenConstraint(){return m_advForceHidden;}
	const Constraint<unsigned int>& GetAdvForceHiddenConstraint() const{return m_advForceHidden;}
	const unsigned int& GetAdvForceHidden() const{return m_advForceHidden.GetCurrentValue();}

	Constraint<unsigned int>& GetAdvForceHiddenCloseConstraint(){return m_advForceHiddenClose;}
	const Constraint<unsigned int>& GetAdvForceHiddenCloseConstraint() const{return m_advForceHiddenClose;}
	const unsigned int& GetAdvForceHiddenClose() const{return m_advForceHiddenClose.GetCurrentValue();}

	Constraint<unsigned int>& GetAdvRejectConstraint(){return m_advReject;}
	const Constraint<unsigned int>& GetAdvRejectConstraint() const{return m_advReject;}
	const unsigned int& GetAdvReject() const{return m_advReject.GetCurrentValue();}

	Constraint<unsigned int>& GetBlockAggrPricePercentConstraint(){return m_blockAggrPricePercent;}
	const Constraint<unsigned int>& GetBlockAggrPricePercentConstraint() const{return m_blockAggrPricePercent;}
	const unsigned int& GetBlockAggrPricePercent() const{return m_blockAggrPricePercent.GetCurrentValue();}

	Constraint<unsigned int>& GetTimeFrameVenuesConstraint(){return m_timeFrameVenues;}
	const Constraint<unsigned int>& GetTimeFrameVenuesConstraint() const{return m_timeFrameVenues;}
	const unsigned int& GetTimeFrameVenues() const{return m_timeFrameVenues.GetCurrentValue();}

	Constraint<unsigned int>& GetOrderTimeFrameConstraint(){return m_orderTimeFrame;}
	const Constraint<unsigned int>& GetOrderTimeFrameConstraint() const{return m_orderTimeFrame;}
	const unsigned int& GetOrderTimeFrame() const{return m_orderTimeFrame.GetCurrentValue();}

	Constraint<unsigned int>& GetTimeFrameOrderCountConstraint(){return m_timeFrameOrderCount;}
	const Constraint<unsigned int>& GetTimeFrameOrderCountConstraint() const{return m_timeFrameOrderCount;}
	const unsigned int& GetTimeFrameOrderCount() const{return m_timeFrameOrderCount.GetCurrentValue();}

	Constraint<unsigned int>& GetOrderSizeNbboVenuesConstraint(){return m_orderSizeNbboVenues;}
	const Constraint<unsigned int>& GetOrderSizeNbboVenuesConstraint() const{return m_orderSizeNbboVenues;}
	const unsigned int& GetOrderSizeNbboVenues() const{return m_orderSizeNbboVenues.GetCurrentValue();}

	Constraint<unsigned int>& GetOrderSizeNbboMultiplierConstraint(){return m_orderSizeNbboMultiplier;}
	const Constraint<unsigned int>& GetOrderSizeNbboMultiplierConstraint() const{return m_orderSizeNbboMultiplier;}
	const unsigned int& GetOrderSizeNbboMultiplier() const{return m_orderSizeNbboMultiplier.GetCurrentValue();}

	const Money& GetCurrentMaxLoss() const{return GetMaxLoss();}
	const Money& GetCurrentMaxLossClose() const{return GetMaxLossClose();}
	const Money& GetCurrentMaxPositionLoss() const{return GetMaxLossPerPosition();}
	const Money& GetCurrentMaxPositionLossClose() const{return GetMaxLossPerPositionClose();}

	void UpdateMaxLoss90Percent()
	{
		m_maxLoss80Percent = m_maxLoss90Percent = m_maxLoss.GetCurrentValue();
		if(!m_maxLoss90Percent.isZero())
		{
			m_maxLoss90Percent *= 90;
			m_maxLoss90Percent /= 100;

			m_maxLoss80Percent *= 80;
			m_maxLoss80Percent /= 100;
		}
	}
protected:
	AccountId m_accountId;
	char m_id[16];
	bool m_simulation;

	Money m_maxLoss80Percent;
	Money m_maxLoss90Percent;

	Constraint<Money> m_marginExcess;
	Constraint<Money> m_hardMarginExcess;

	Constraint<Money> m_buyingPower;
	Constraint<Money> m_hardBuyingPower;

	Constraint<Money> m_dayMaxPosInvestment;
	Constraint<Money> m_nightMaxPosInvestment;
	Constraint<Money> m_morningMaxPosInvestment;

	Constraint<Money> m_dayMaxLongInvestment;
	Constraint<Money> m_nightMaxLongInvestment;
	Constraint<Money> m_morningMaxLongInvestment;

	Constraint<Money> m_dayMaxShortInvestment;
	Constraint<Money> m_nightMaxShortInvestment;
	Constraint<Money> m_morningMaxShortInvestment;

	Constraint<Money> m_nightMaxInvestment;
	Constraint<Money> m_morningMaxInvestment;

	Constraint<Money> m_maxLoss;
	Constraint<Money> m_nightMaxLoss;
	Constraint<Money> m_morningMaxLoss;

	Constraint<Money> m_maxLossSlack;

	Constraint<Money> m_maxLossClose;
	Constraint<Money> m_nightMaxLossClose;
	Constraint<Money> m_morningMaxLossClose;

	Constraint<Money> m_maxLossPerPosition;
	Constraint<Money> m_nightMaxLossPerPosition;
	Constraint<Money> m_morningMaxLossPerPosition;
	Constraint<Money> m_maxLossPerPositionSlack;
	Constraint<Money> m_maxLossPerPositionClose;
	Constraint<Money> m_nightMaxLossPerPositionClose;
	Constraint<Money> m_morningMaxLossPerPositionClose;
	Constraint<Money> m_maxOpenLossPerPosition;
	Constraint<Money> m_maxTradedMoney;
	Constraint<Money> m_maxOrderValue;
	Constraint<Price> m_minShortPrice;

	Constraint<Price> m_minSharePrice;
	Constraint<Price> m_maxSharePrice;

	Constraint<Money> m_commissionPer1000Shares;

	Constraint<unsigned int> m_maxSharesTotal;
	Constraint<unsigned int> m_maxSharesTraded;

	Constraint<unsigned int> m_dayMaxPosShares;
	Constraint<unsigned int> m_nightMaxPosShares;
	Constraint<unsigned int> m_morningMaxPosShares;
	Constraint<unsigned int> m_maxPosPendingOrders;
	Constraint<unsigned int> m_maxOpenPositions;
	Constraint<unsigned int> m_maxOrderSize;

//	Constraint<int> m_autoCloseStartDelaySecond;
//	Constraint<int> m_autoCloseEndDelaySecond;

#ifndef TAKION_NO_OPTIONS
	Constraint<Money> m_optionBuyingPower;
	Constraint<unsigned int> m_maxOptionSharesTraded;
	Constraint<unsigned int> m_maxOptionOrderSize;
	Constraint<Money> m_maxOptionOrderValue;
	Constraint<unsigned char> m_optionNaked;
	Constraint<unsigned int> m_maxOptionContractsOpen;
	Constraint<unsigned int> m_maxOptionOpenPositions;
#endif
	Constraint<unsigned char> m_isoAllowed;
	Constraint<unsigned char> m_htbTborrowOrdersAllowed;
	Constraint<unsigned char> m_conservativeOrderMarking;
	Constraint<unsigned char> m_localSideMarking;
	Constraint<unsigned char> m_poolLocates;

	Constraint<Price> m_spoofingBigPriceOffset;//min
	Constraint<Price> m_spoofingSmallPriceOffset;//max

	Constraint<unsigned int> m_spoofingOrderCountRatio;
	Constraint<unsigned int> m_spoofingOrderSizeRatio;

	Constraint<unsigned int> m_advOrderCount;
	Constraint<unsigned int> m_advOrderSizePercent;
	Constraint<unsigned int> m_advBorder;
	Constraint<unsigned int> m_advForceHidden;
	Constraint<unsigned int> m_advForceHiddenClose;
	Constraint<unsigned int> m_advReject;
	Constraint<unsigned int> m_blockAggrPricePercent;

	Constraint<unsigned int> m_timeFrameVenues;
	Constraint<unsigned int> m_orderTimeFrame;
	Constraint<unsigned int> m_timeFrameOrderCount;
	
	Constraint<unsigned int> m_orderSizeNbboVenues;
	Constraint<unsigned int> m_orderSizeNbboMultiplier;

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


class TU_API DelayedPriceQuantity : public PriceQuantity
{
public:
	virtual unsigned int GetMmid() const{return 0;}
	virtual unsigned short GetShortMmid() const{return 0;}
	const unsigned int& GetMillisecond() const{return m_millisecond;}
	const short& GetDelay() const{return m_delay;}
	bool isLessMillisecond(const DelayedPriceQuantity& other) const{return m_millisecond < other.m_millisecond;}
	const bool& isHistorical() const{return m_historical;}
	void SetHistorical(){m_historical = true;}
	void SetValues(const unsigned int& dollars, const unsigned int& dollarFraction, const unsigned int& quantity, const unsigned int& millisecond, const short& delay, const bool& historical)
	{
		PriceQuantity::SetValues(dollars, dollarFraction, quantity);
		m_millisecond = millisecond;
		m_delay = delay;
		m_historical = historical;
	}
protected:
	DelayedPriceQuantity(const unsigned int& dollars, const unsigned int& dollarFraction, const unsigned int& quantity, const unsigned int& millisecond, const short& delay):
		PriceQuantity(dollars, dollarFraction, quantity),
		m_millisecond(millisecond),
		m_delay(delay),
		m_historical(false)
	{}
	DelayedPriceQuantity(const Price& price, const unsigned int& quantity, const unsigned int& millisecond, const short& delay):
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
//	ECNBOOK_NSX,

//	ECNBOOK_FLOW = 11,
	ECNBOOK_IEX = 11,

	BOOK_MM_ARCA = 12,
	BOOK_MM_BATS,
	BOOK_MM_BATY,
	BOOK_MM_EDGX,
//	BOOK_MM_NSX,

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
	size_t GetHashValue() const{return ((size_t)m_dollars << 16) | (((size_t)m_dollarFraction >> 16) + m_quantity + m_bookId);}
protected:
	unsigned int m_mmid;
	unsigned int m_millisecond;
	EcnBookId m_bookId;
};

template<> AFX_INLINE UINT AFXAPI HashKey<TradedQuote>(TradedQuote key)
{
#ifdef _WIN64
	const size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const TradedQuote&>(const TradedQuote& key)
{
#ifdef _WIN64
	const size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<TradedQuote&>(TradedQuote& key)
{
#ifdef _WIN64
	const size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> inline size_t std::hash_value<TradedQuote>(const TradedQuote& key)
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
	Quote(const bool& bid, const unsigned int& dollars, const unsigned int& dollarFraction, const unsigned int& quantity, const EcnBookId& bookId, const unsigned int& mmid, const unsigned int& millisecond, const short& delay):// = 0xFFFF):
		DelayedPriceQuantity(dollars, dollarFraction, quantity, millisecond, delay),
		m_mmid(mmid),
		m_bid(bid),
		m_bookId(bookId)
		{}
	Quote(const bool& bid, const Price& price, const unsigned int& quantity, const EcnBookId& bookId, const unsigned int& mmid, const unsigned int& millisecond, const short& delay):// = 0xFFFF):
		DelayedPriceQuantity(price, quantity, millisecond, delay),
		m_mmid(mmid),
		m_bid(bid),
		m_bookId(bookId)
		{}
	Quote(const bool& bid = false):m_mmid(0),m_bid(bid),m_bookId(AllBooks){}

	bool EqualPriceSideAndDestination(const Quote& other) const
	{
		return Price::operator==(other) && m_mmid == other.m_mmid && m_bookId == other.m_bookId && m_bid == other.m_bid;
	}
	void SetPriceSideAndDestination(const Quote& other)
	{
		Price::operator=(other);
		m_mmid = other.m_mmid;
		m_bookId = other.m_bookId;
		m_bid = other.m_bid;
	}

	virtual ~Quote(){}
	const bool& isBid() const{return m_bid;}
	virtual quoteid GetId() const{return 0;}
//	virtual unsigned int GetMmid() const{return 0;}
	virtual unsigned int GetMmid() const{return m_mmid;}
	virtual EcnBookId GetBookId() const{return m_bookId;}
	virtual unsigned char GetSource() const;
	virtual unsigned int GetOrderCount() const{return 1;}
	virtual unsigned char GetCondition() const{return '\0';}
	virtual bool GetRetailLiquidity() const{return false;}
	bool operator<(const Quote& other) const{return m_bid ? other.Price::operator<(*this) : Price::operator<(other);}
//	bool operator==(const Quote& other) const{return Price::operator==(other);}
	virtual bool isDirect() const{return true;}
	virtual bool isLessCrossBook(const Quote& other) const{return operator<(other) || operator==(other) && (m_mmid < other.m_mmid || m_mmid == other.m_mmid && (m_bookId < other.m_bookId || m_bookId == other.m_bookId && isDirect()));}
	virtual bool isTemp() const{return false;}
	virtual bool isAttributed() const{return false;}
//	virtual bool isOrder() const{return false;}
	virtual unsigned char GetOrder() const{return '\0';}
#ifdef LRPS
	bool isLrp() const{return m_mmid == lrpNum;}
#endif
	bool isLuld() const{return m_mmid == luldNum;}
	virtual bool isHidden() const{return false;}
	virtual bool isStop() const{return false;}
	virtual bool isPostponed() const{return false;}
	virtual bool isGtc() const{return false;}
//	virtual bool isLessCrossBook(const Quote& other) const{return Quote::operator<(other) || Quote::operator==(other) && (m_mmid < other.GetMmid() || m_mmid == other.GetMmid() && m_id < other.GetId());}
	virtual bool isEmpty() const{return m_quantity == 0 && isZero();}
	void SetEmpty(){SetZero(); m_quantity = 0;}
	bool isRegular() const
	{
		return GetOrder() != 1
#ifdef LRPS
			&& !isLrp()
#endif
			&& !isLuld()
			&& !isEmpty();}
protected:
	unsigned int m_mmid;
	bool m_bid;
	EcnBookId m_bookId;
};

class TU_API TempQuote : public Quote
{
public:
	TempQuote(const bool& bid, const unsigned int& dollars, const unsigned int& dollarFraction, const unsigned int& quantity, const EcnBookId& bookId, const unsigned int& mmid, const unsigned int& millisecond, const short& delay, const bool& attributed, const bool& retailLiquidity):// = 0xFFFF):
		Quote(bid, dollars, dollarFraction, quantity, bookId, mmid, millisecond, delay),
		m_condition('\0'),
		m_attributed(attributed),
		m_retailLiquidity(retailLiquidity)
		{}
	TempQuote(const bool& bid, const Price& price, const unsigned int& quantity, const EcnBookId& bookId, const unsigned int& mmid, const unsigned int& millisecond, const short& delay, const bool& attributed, const bool& retailLiquidity):// = 0xFFFF):
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

	void SetBookId(const unsigned char& bookId){m_bookId = (EcnBookId)bookId;}
	void SetCondition(const unsigned char& condition){m_condition = condition;}
	void SetMmid(const unsigned int& mmid){m_mmid = mmid;}
	void SetAttributed(const bool& attributed){m_attributed = attributed;}
	void SetRetailLiquidity(const bool& retailLiquidity){m_retailLiquidity = retailLiquidity;}
	void SetMillisecond(const unsigned int& millisecond){m_millisecond = millisecond;}
	void SetDelay(const short& delay){m_delay = delay;}

	virtual bool isTemp() const{return true;}
	virtual bool isAttributed() const{return m_attributed;}
	virtual unsigned char GetCondition() const override{return m_condition;}
	virtual bool GetRetailLiquidity() const override{return m_retailLiquidity;}
protected:
	unsigned char m_condition;
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
	virtual unsigned int GetTotalSizeForPrice(bool bid, const Price& price, bool includePrice) const{return 0;}
	virtual unsigned int GetMaxSizeForPrice(bool bid, const Price& price, bool includePrice, Price* maxPrice = NULL, unsigned int filterSize = 0) const{if(maxPrice)maxPrice->SetZero(); return 0;}
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
	Exchange(const unsigned char& id, const char* const& name, const char* const& shortName, const bool& protectedQuote):
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
	MarketCenter(const unsigned char& id, const char* const& name, const char* const& shortName, const unsigned char& ecnBookId, const unsigned char& mmBookId, const bool& protectedQuote,
#ifndef TAKION_NO_OPTIONS
		const char* const& optionName, const char* const& optionShortName,
#endif
		const bool& canHaveLevel1):
		Exchange(id, name, shortName, protectedQuote),
		m_ecnBookId(ecnBookId),
		m_mmBookId(mmBookId),
#ifndef TAKION_NO_OPTIONS
//		m_optionNumericName(optionName ? *(unsigned int*)optionName : 0),
		m_optionNumericName(optionName ? U_RepresentStringAsUnsignedNumber<unsigned int>(optionName) : 0),
		m_optionNumericShortName(optionShortName ? *(unsigned short*)optionShortName : 0),
#endif
		m_canHaveLevel1(canHaveLevel1 && ecnBookId < ECNBOOK_COUNT)
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
	MarketCenter(const unsigned char& id, const unsigned int& name, const unsigned short& shortName, const unsigned char& ecnBookId, const unsigned char& mmBookId, const bool& protectedQuote,
#ifndef TAKION_NO_OPTIONS
		const unsigned int& optionName, const unsigned short& optionShortName,
#endif
		const bool& canHaveLevel1):
		Exchange(id, name, shortName, protectedQuote),
		m_ecnBookId(ecnBookId),
		m_mmBookId(mmBookId),
#ifndef TAKION_NO_OPTIONS
		m_optionNumericName(optionName),
		m_optionNumericShortName(optionShortName),
#endif
		m_canHaveLevel1(canHaveLevel1 && ecnBookId < ECNBOOK_COUNT)
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
	const bool& CanHaveLevel1() const{return m_canHaveLevel1;}
protected:
	unsigned char m_ecnBookId;
	unsigned char m_mmBookId;
	bool m_canHaveLevel1;
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
	Ecn(const unsigned char& id, const char* const& name, const char* const& shortName, const char& label, const bool& direct, const bool& protectedQuote, const char* const& destinationName, const unsigned char& attributedBookId, const unsigned char& nativeBookId):
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
	Ecn(const unsigned char& id, const unsigned int& name, const unsigned short& shortName, const char& label, const bool& direct, const bool& protectedQuote, const char* const& destinationName, const unsigned char& attributedBookId, const unsigned char& nativeBookId):
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
	const bool& isDirect() const{return m_direct;}
	const char& GetLabel() const{return m_label;}
	const unsigned int& GetNumericDestinationName() const{return m_numericDestinationName;}
	const char* GetDestinationName() const{return m_destinationName;}
	const unsigned char& GetAttributedBookId() const{return m_attributedBookId;}
	const unsigned char& GetNativeBookId() const{return m_nativeBookId;}
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
//	const char* GetSymbol() const{return m_symbolStr.c_str();}
//	const std::string& GetSymbolStr() const{return m_symbolStr;}

	const char* GetSymbol() const{return (const char*)&m_numericSymbol;}
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

	const unsigned int& GetLastTime() const{return m_lastTime;}

	typedef std::vector<IndexChartPoint> IndexChartPointVector;

	const unsigned short& GetChartStartMinute() const{return m_chartStartMinute;}
	unsigned short GetChartSize() const{return (unsigned short)m_chart.size();}
	const IndexChartPointVector* GetChart() const{return &m_chart;}//m_chart;}
	const bool& isChartLoaded() const{return m_chartLoaded;}
	const IndexChartPoint* GetChartPointAtMinute(unsigned short minute) const//LockInquiryWaitChart / UnlockInquiryChart
	{
		if(minute >= m_chartStartMinute)
		{
			minute -= m_chartStartMinute;
			if(minute < GetChartSize())
			{
				return &m_chart[minute];
			}
		}
		return NULL;
	}
	const IndexChartPoint* GetLastChartPoint() const//LockInquiryWaitChart / UnlockInquiryChart
	{
		const unsigned short chartSize = GetChartSize();
		return chartSize ? &m_chart[chartSize - 1] : NULL;
	}
	const IndexChartPoint* GetLastButOneChartPoint() const//LockInquiryWaitChart/UnlockInquiryChart
	{
		const unsigned short chartSize = GetChartSize();
		return chartSize > 1 ? &m_chart[chartSize - 2] : NULL;
	}

	bool LockInquiryValue() const{return m_lockValue.LockInquiry();}
	void LockInquiryWaitValue() const{m_lockValue.LockInquiryWait();}
	void UnlockInquiryValue() const{m_lockValue.UnlockInquiry();}

	bool LockInquiryChart() const{return m_lockChart.LockInquiry();}
	void LockInquiryWaitChart() const{m_lockChart.LockInquiryWait();}
	void UnlockInquiryChart() const{m_lockChart.UnlockInquiry();}

	const bool& isLoaded() const{return m_loaded;}
	const bool& isReloaded() const{return m_reloaded;}

	void AddInThreadObserver(Observer* o) const;
	void RemoveInThreadObserver(Observer* o) const;

//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;
	virtual unsigned short GetLastNewMinuteFromMsServer() const{return 0;}

//	virtual HANDLE GetThreadHandle() const{return NULL;}
	const unsigned int& GetThreadId() const{return m_threadId;}
	virtual bool isCalculatable() const{return false;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}
protected:
	Index(const char* symbol, unsigned short code);
//	char m_symbol[16];
//	std::string m_symbolStr;
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
	unsigned int m_lastTime;
	unsigned int m_threadId;
	unsigned short m_code;
	unsigned short m_chartStartMinute;
	bool m_chartLoaded;
	bool m_loaded;
	bool m_reloaded;
	TakionLock m_lockValue;
	TakionLock m_lockChart;
	Observable m_inThreadObservable;
//	volatile LONG m_lockInThreadObservable;
	TakionLockSingleThreadAccess m_lockInThreadObservable;
};


enum ImbalanceCrossType : unsigned char//ARCA
{
	Opening			= 'O',
	Closing			= 'C',//Same for NYSE
	HaltOrIPO		= 'H',//Reopening auction (Halt Resume) for NYSE
	Market			= 'M',//Opening for NYSE
	Regulatory		= 'R',//NYSE only
	CrossUndefined	= ' ',
	IPO				= 'I',
};

enum ImbalanceDirection : unsigned char
{
	ImbalanceBuy		= 'B',
	ImbalanceSell		= 'S',
	ImbalanceNone		= 'N',
	ImbalanceUndefined	= 'O',
};

class TU_API ImbalanceBase
{
public:
	static const int intZero;//= 0;
	const Price& GetFarPrice() const{return m_farPrice;}
	const Price& Get1stFarPrice() const{return m_1stFarPrice;}
	const Price& Get2ndFarPrice() const{return m_2ndFarPrice;}
	const SignedPrice& GetFarPriceDiff() const{return m_farPriceDiff;}
	const SignedPrice& GetInitRefFarPriceDiff() const{return m_initRefFarPriceDiff;}
	const Price& GetRegulatoryFarPrice() const{return m_regulatoryFarPrice;}
	const Price& GetNearPrice() const{return m_nearPrice;}
	const unsigned int& GetNearPriceCompact() const{return m_nearPriceCompact;}
	const Price& GetRegulatoryNearPrice() const{return m_regulatoryNearPrice;}
	const Price& GetCurrentReferencePrice() const{return m_currentReferencePrice;}
	const Price& GetInitialCurrentReferencePrice() const{return m_initialCurrentReferencePrice;}
	const bool& isCurrentReferencePriceChanged() const{return m_currentReferencePriceChanged;}
	const Price& GetRegulatoryCurrentReferencePrice() const{return m_regulatoryCurrentReferencePrice;}
	const unsigned int& GetPairedShares() const{return m_pairedShares;}
	const unsigned int& GetRegulatoryPairedShares() const{return m_regulatoryPairedShares;}
	const int& GetImbalanceShares() const{return m_imbalanceShares;}
	const int& GetPrevImbalanceShares() const{return m_prevImbalanceShares;}
	const int& GetRegulatoryImbalanceShares() const{return m_regulatoryImbalanceShares;}
	const int& GetPrevRegulatoryImbalanceShares() const{return m_prevRegulatoryImbalanceShares;}
	const int& GetMarketImbalanceShares() const{return m_marketImbalanceShares;}
	const int& GetInitialImbalanceShares() const{return m_initialImbalanceShares;}

//	const SignedPrice& GetImbalanceRatio() const{return m_imbalanceRatio;}
	const int& GetImbalanceChange() const{return m_imbalanceChange;}

	const unsigned int& GetOpeningPairedShares() const{return m_openingPairedShares;}
	const int& GetOpeningImbalanceShares() const{return m_openingImbalanceShares;}
	const Price& GetOpeningCurrentReferencePrice() const{return m_openingCurrentReferencePrice;}

	const int& GetT830ImbalanceShares() const{return m_t830ImbalanceShares;}
	const int& GetT845ImbalanceShares() const{return m_t845ImbalanceShares;}
	const int& GetT900ImbalanceShares() const{return m_t900ImbalanceShares;}
	const int& GetT915ImbalanceShares() const{return m_t915ImbalanceShares;}
	const int& GetT920ImbalanceShares() const{return m_t920ImbalanceShares;}
	const int& GetT925ImbalanceShares() const{return m_t925ImbalanceShares;}
	const int& GetT926ImbalanceShares() const{return m_t926ImbalanceShares;}
	const int& GetT928ImbalanceShares() const{return m_t928ImbalanceShares;}

	const int& GetT1545ImbalanceShares() const{return m_t1545ImbalanceShares;}
	const int& GetT1550ImbalanceShares() const{return m_t1550ImbalanceShares;}
	const int& GetT1555ImbalanceShares() const{return m_t1555ImbalanceShares;}
	const int& GetT1556ImbalanceShares() const{return m_t1556ImbalanceShares;}
	const int& GetT1557ImbalanceShares() const{return m_t1557ImbalanceShares;}
	const int& GetT1558ImbalanceShares() const{return m_t1558ImbalanceShares;}
	const int& GetT1559ImbalanceShares() const{return m_t1559ImbalanceShares;}

	const Price& GetT1555CurrentReferencePrice() const{return m_t1555CurrentReferencePrice;}
	const Price& GetT1555FarPrice() const{return m_t1555FarPrice;}
	const Price& GetT1555NearPrice() const{return m_t1555NearPrice;}

	const Price& GetT1558CurrentReferencePrice() const{return m_t1558CurrentReferencePrice;}
	const Price& GetT1558FarPrice() const{return m_t1558FarPrice;}
	const Price& GetT1558NearPrice() const{return m_t1558NearPrice;}

	const unsigned int& GetImbalanceTime() const{return m_time;}
	const unsigned int& GetPrevImbalanceTime() const{return m_prevTime;}
	const unsigned int& GetRegulatoryImbalanceTime() const{return m_regulatoryTime;}
	const unsigned int& GetPrevRegulatoryImbalanceTime() const{return m_prevRegulatoryTime;}
	const unsigned int& GetAuctionTime() const{return m_auctionTime;}
//	const char& GetImbalanceDirection() const{return m_imbalanceDirection;}
	const short& GetDelay() const{return m_delay;}
	const char& GetCrossType() const{return m_crossType;}
	const char& GetPriceVariationIndicator() const{return m_priceVariationIndicator;}
	const bool& isFrozen() const{return m_freezeStatus;}

	bool isImbalanceClosing() const
	{
		switch(m_crossType)
		{
			case Closing:
			case Regulatory:
			return true;

			default:
			return false;
		}
	}
	const int& GetRegulatoryImbalanceSharesIfClosing() const
	{
/*
		switch(m_crossType)
		{
			case Closing:
			case Regulatory:
			return m_regulatoryImbalanceShares;

			default:
			return intZero;
		}
*/
		return m_regulatoryImbalanceShares;
	}
	static bool SetTimeImbalance(const unsigned int& time, const unsigned int& timeThreshold, int& imbalanceShares, const int& shares)
	{
		if(time <= timeThreshold)// || !imbalanceShares)
		{
			imbalanceShares = shares;
			return true;
		}
		return false;
	}
	static bool SetTimeImbalancePrice(const unsigned int& time, const unsigned int& timeThreshold, Price& imbalancePrice, const Price& price)
	{
		if (time <= timeThreshold)
		{
			imbalancePrice = price;
			return true;
		}
		return false;
	}
	inline static short CalculateDelay(const unsigned int& millisecond)
	{
		unsigned int delay = TL_GetCurrentMillisecond();
		if(millisecond < delay)
		{
			delay -= millisecond;
			return delay > 0x7FFF ? 0x7FFF : (short)delay;
		}
		else
		{
			delay = millisecond - delay;
			return delay > 0x7FFF ? -0x7FFF : -(short)delay;
		}
	}

	//	void SetParams(const Price& farPrice,
	void SetImbalanceValues(const Price& farPrice,
		const Price& nearPrice,
		const Price& currentReferencePrice,
		const unsigned int& pairedShares,
		const unsigned int& imbalanceShares,
		const unsigned int& marketImbalanceShares,
		const unsigned int& time,
		const unsigned int& auctionTime,
		const char& imbalanceDirection,
		const char& crossType,
		const char& priceVariationIndicator,
		const bool& regulatory,
		const bool& freezeStatus,
		const bool& stockOpen)
	{
		m_delay = CalculateDelay(time);
		const bool none = imbalanceDirection != ImbalanceBuy && imbalanceDirection != ImbalanceSell;
		const int shares = none ? 0:
			imbalanceDirection == ImbalanceSell ? -(int)imbalanceShares:
			(int)imbalanceShares;
		if(!m_initialImbalanceShares)
		{
			m_initialImbalanceShares = shares;
		}
		if(time < 43200000)//12:00
		{
			if(!stockOpen)
			{
				m_openingPairedShares = pairedShares;
				m_openingImbalanceShares = shares;
				m_openingCurrentReferencePrice = currentReferencePrice;
			}
			else if(shares)
			{
				m_openingPairedShares = pairedShares;
				m_openingImbalanceShares = shares;
				m_openingCurrentReferencePrice = currentReferencePrice;
			}

			if(SetTimeImbalance(time, 34080500, m_t928ImbalanceShares, shares))//9:28:00-500
			{
				if(SetTimeImbalance(time, 33960500, m_t926ImbalanceShares, shares))//9:26:00-500
				{
					if(SetTimeImbalance(time, 33900500, m_t925ImbalanceShares, shares))//9:25:00-500
					{
						if(SetTimeImbalance(time, 33600500, m_t920ImbalanceShares, shares))//9:20:00-500
						{
							if(SetTimeImbalance(time, 33300500, m_t915ImbalanceShares, shares))//9:15:00-500
							{
								if(SetTimeImbalance(time, 32400500, m_t900ImbalanceShares, shares))//9:00:00-500
								{
									if(SetTimeImbalance(time, 31500500, m_t845ImbalanceShares, shares))//8:45:00-500
									{
										SetTimeImbalance(time, 30600500, m_t830ImbalanceShares, shares);//8:30:00-500
									}
								}
							}
						}
					}
				}
			}
		}
		else if(time > 50400000)//14:00
		{
			if(SetTimeImbalance(time, 57540500, m_t1559ImbalanceShares, shares))//15:59:00-500
			{
				if(SetTimeImbalance(time, 57480500, m_t1558ImbalanceShares, shares))//15:58:00-500
				{
					m_t1558CurrentReferencePrice = currentReferencePrice;
					m_t1558FarPrice = farPrice;
					m_t1558NearPrice = nearPrice;

					if(SetTimeImbalance(time, 57420500, m_t1557ImbalanceShares, shares))//15:57:00-500
					{
						if(SetTimeImbalance(time, 57360500, m_t1556ImbalanceShares, shares))//15:56:00-500
						{
							if(SetTimeImbalance(time, 57300500, m_t1555ImbalanceShares, shares))//15:55:00-500
							{
								m_t1555CurrentReferencePrice = currentReferencePrice;
								m_t1555FarPrice = farPrice;
								m_t1555NearPrice = nearPrice;
								if(SetTimeImbalance(time, 57000500, m_t1550ImbalanceShares, shares))//15:50:00-500
								{
									SetTimeImbalance(time, 56700500, m_t1545ImbalanceShares, shares);//15:45:00-500
								}
							}
						}
					}
				}
			}
		}
		if(regulatory)// && crossType == Regulatory)//Closing)
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
		else// if(!regulatory)
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
/*08/08/2018
			if(m_1stFarPrice.isZero())
			{
				m_1stFarPrice = farPrice;
				if(!m_initialCurrentReferencePrice.isZero() && !m_1stFarPrice.isZero())
				{
					m_initRefFarPriceDiff = m_initialCurrentReferencePrice - m_1stFarPrice;
				}
				else
				{
					m_initRefFarPriceDiff.SetZero();
				}
			}
			else if(m_2ndFarPrice.isZero() && !farPrice.isZero())
			{
				if(farPrice != m_1stFarPrice || time != m_time)
				{
					m_2ndFarPrice = farPrice;
					m_farPriceDiff = m_2ndFarPrice - m_1stFarPrice;
				}
			}
*/
			m_nearPriceCompact = nearPrice.GetCompactPrice();
			m_nearPrice = nearPrice;

			if(currentReferencePrice != m_currentReferencePrice)
			{
				if(m_currentReferencePrice.isZero())
				{
/*08/08/2018
					m_initialCurrentReferencePrice = currentReferencePrice;
					if(!m_initialCurrentReferencePrice.isZero() && !m_1stFarPrice.isZero())
					{
						m_initRefFarPriceDiff = m_initialCurrentReferencePrice - m_1stFarPrice;
					}
					else
					{
						m_initRefFarPriceDiff.SetZero();
					}
*/
				}
				else
				{
					if(currentReferencePrice.isZero())
					{
						m_currentReferencePriceChanged = false;
					}
					else
					{
						m_currentReferencePriceChanged = true;
					}
				}
				m_currentReferencePrice = currentReferencePrice;
			}
			m_pairedShares = pairedShares;
			if(m_imbalanceShares != shares)
			{
				m_prevImbalanceShares = m_imbalanceShares;
				m_prevTime = m_time;
				m_imbalanceShares = shares;
				if(m_prevImbalanceShares)
				{
					m_imbalanceChange = shares - m_prevImbalanceShares;
//					m_imbalanceRatio.SetValue(shares, 0);
//					m_imbalanceRatio /= m_prevImbalanceShares;
				}
				else
				{
//					m_imbalanceRatio.SetZero();
					m_imbalanceChange = 0;
				}
			}
			m_time = time;
		}
//08/08/2018
		if(m_1stFarPrice.isZero())
		{
			m_1stFarPrice = farPrice;
			if(!m_initialCurrentReferencePrice.isZero() && !m_1stFarPrice.isZero())
			{
				m_initRefFarPriceDiff = m_initialCurrentReferencePrice - m_1stFarPrice;
			}
			else
			{
				m_initRefFarPriceDiff.SetZero();
			}
		}
		else if(m_2ndFarPrice.isZero() && !farPrice.isZero())
		{
			if(farPrice != m_1stFarPrice || time != m_time)
			{
				m_2ndFarPrice = farPrice;
				m_farPriceDiff = m_2ndFarPrice - m_1stFarPrice;
			}
		}
		UpdateInitialCurrentReferencePrice(currentReferencePrice);
////
		m_marketImbalanceShares = none ? 0:
			imbalanceDirection == ImbalanceSell ? -(int)marketImbalanceShares : (int)marketImbalanceShares;
		m_auctionTime = auctionTime;
//		m_imbalanceDirection = imbalanceDirection;
		m_priceVariationIndicator = priceVariationIndicator;
		m_freezeStatus = freezeStatus;
	}
	void toString(std::string& info, const unsigned char& decDigits = 4) const
	{
		char num[33];
		U_AppendMillisecond(info, GetImbalanceTime(), true, ' ');
		info += U_SignedNumberToStrNoDecDigits(GetDelay(), num, sizeof(num), ' ');
		if(GetRegulatoryImbalanceTime())
		{
			U_AppendMillisecond(info, GetRegulatoryImbalanceTime(), true, ' ');
		}
		info += U_SignedNumberToStrNoDecDigits(GetImbalanceShares(), num, sizeof(num), ' ');
		info += U_SignedNumberToStrNoDecDigits(GetPrevImbalanceShares(), num, sizeof(num), ' ');
		info += U_SignedNumberToStrNoDecDigits(GetImbalanceChange(), num, sizeof(num), ' ');
//		U_SignedPriceToStr(info, GetImbalanceRatio(), decDigits, '\0', false, ' ', true);
		U_PriceToStr(info, GetFarPrice(), decDigits, '\0', false, ' ', true);
		U_PriceToStr(info, Get1stFarPrice(), decDigits, '\0', false, ' ', true);
		U_PriceToStr(info, Get2ndFarPrice(), decDigits, '\0', false, ' ', true);
		U_PriceToStr(info, GetNearPrice(), decDigits, '\0', false, ' ', true);
		U_PriceToStr(info, GetCurrentReferencePrice(), decDigits, '\0', false, ' ', true);
		info += U_UnsignedNumberToStrNoDecDigits(GetPairedShares(), num, sizeof(num), ' ');

		U_AppendPrintableChar(info, GetCrossType(), ' ');
		info += U_UnsignedNumberToStrNoDecDigits(GetPriceVariationIndicator(), num, sizeof(num), ' ');

		if(isFrozen())info += " FROZEN";

		U_AppendMillisecond(info, GetAuctionTime(), true);

		if(GetMarketImbalanceShares())
		{
			info += " MKT=";
			info += U_SignedNumberToStrNoDecDigits(GetMarketImbalanceShares(), num, sizeof(num));
		}

		if(GetRegulatoryImbalanceShares())
		{
			info += " REG=";
			info += U_SignedNumberToStrNoDecDigits(GetRegulatoryImbalanceShares(), num, sizeof(num), ' ');
			info += '@';
			U_AppendMillisecond(info, GetRegulatoryImbalanceTime(), true, ' ');
			U_PriceToStr(info, GetRegulatoryFarPrice(), decDigits, '\0', false, ' ', true);
			U_PriceToStr(info, GetRegulatoryNearPrice(), decDigits, '\0', false, ' ', true);
			U_PriceToStr(info, GetRegulatoryCurrentReferencePrice(), decDigits, '\0', false, ' ', true);
			info += U_UnsignedNumberToStrNoDecDigits(GetRegulatoryPairedShares(), num, sizeof(num));
		}
	}
protected:
	ImbalanceBase():
		m_pairedShares(0),
		m_regulatoryPairedShares(0),
		m_imbalanceShares(0),
		m_prevImbalanceShares(0),
		m_imbalanceChange(0),
		m_regulatoryImbalanceShares(0),
		m_prevRegulatoryImbalanceShares(0),
		m_marketImbalanceShares(0),
		m_initialImbalanceShares(0),
		m_openingPairedShares(0),
		m_openingImbalanceShares(0),

		m_t830ImbalanceShares(0),
		m_t845ImbalanceShares(0),
		m_t900ImbalanceShares(0),
		m_t915ImbalanceShares(0),
		m_t920ImbalanceShares(0),
		m_t925ImbalanceShares(0),
		m_t926ImbalanceShares(0),
		m_t928ImbalanceShares(0),

		m_t1545ImbalanceShares(0),
		m_t1550ImbalanceShares(0),
		m_t1555ImbalanceShares(0),
		m_t1556ImbalanceShares(0),
		m_t1557ImbalanceShares(0),
		m_t1558ImbalanceShares(0),
		m_t1559ImbalanceShares(0),

		m_time(0),
		m_prevTime(0),
		m_regulatoryTime(0),
		m_prevRegulatoryTime(0),
		m_auctionTime(0),
		m_delay(0),
		m_crossType(CrossUndefined),
		m_priceVariationIndicator(' '),
		m_freezeStatus(false),
		m_currentReferencePriceChanged(false)
	{}
	void UpdateInitialCurrentReferencePrice(const Price& price)
	{
		if(m_initialCurrentReferencePrice.isZero() && !price.isZero())
		{
			m_initialCurrentReferencePrice = price;
			if(!m_1stFarPrice.isZero())
			{
				m_initRefFarPriceDiff = m_initialCurrentReferencePrice - m_1stFarPrice;
			}
			else
			{
				m_initRefFarPriceDiff.SetZero();
			}
		}
	}
	Price m_farPrice;
	Price m_1stFarPrice;
	Price m_2ndFarPrice;
	SignedPrice m_farPriceDiff;
	SignedPrice m_initRefFarPriceDiff;
	Price m_regulatoryFarPrice;
	Price m_nearPrice;
	Price m_regulatoryNearPrice;
	Price m_currentReferencePrice;
	Price m_initialCurrentReferencePrice;
	Price m_regulatoryCurrentReferencePrice;

	Price m_t1555CurrentReferencePrice;
	Price m_t1555FarPrice;
	Price m_t1555NearPrice;

	Price m_t1558CurrentReferencePrice;
	Price m_t1558FarPrice;
	Price m_t1558NearPrice;

//	SignedPrice m_imbalanceRatio;//(m_imbalanceShares / m_prevImbalanceShares)

	unsigned int m_nearPriceCompact;

	unsigned int m_pairedShares;
	unsigned int m_regulatoryPairedShares;
	int m_imbalanceShares;
	int m_prevImbalanceShares;
	int m_imbalanceChange;//(m_imbalanceShares - m_prevImbalanceShares)
	int m_regulatoryImbalanceShares;
	int m_prevRegulatoryImbalanceShares;
	int m_marketImbalanceShares;
	int m_initialImbalanceShares;

	unsigned int m_openingPairedShares;
	int m_openingImbalanceShares;
	Price m_openingCurrentReferencePrice;

	int m_t830ImbalanceShares;
	int m_t845ImbalanceShares;
	int m_t900ImbalanceShares;
	int m_t915ImbalanceShares;
	int m_t920ImbalanceShares;
	int m_t925ImbalanceShares;
	int m_t926ImbalanceShares;
	int m_t928ImbalanceShares;

	int m_t1545ImbalanceShares;
	int m_t1550ImbalanceShares;
	int m_t1555ImbalanceShares;
	int m_t1556ImbalanceShares;
	int m_t1557ImbalanceShares;
	int m_t1558ImbalanceShares;
	int m_t1559ImbalanceShares;

	unsigned int m_time;
	unsigned int m_prevTime;
	unsigned int m_regulatoryTime;
	unsigned int m_prevRegulatoryTime;
	unsigned int m_auctionTime;
//	char m_imbalanceDirection;
	short m_delay;
	char m_crossType;
	char m_priceVariationIndicator;
	bool m_freezeStatus;
	bool m_currentReferencePriceChanged;
};

class TU_API Imbalance : public ImbalanceBase
{
public:
	virtual ~Imbalance(){}
	virtual void SetImbalance(const ImbalanceBase& other)
	{
		m_farPrice = other.GetFarPrice();
		m_1stFarPrice = other.Get1stFarPrice();
		m_2ndFarPrice = other.Get2ndFarPrice();
		m_farPriceDiff = other.GetFarPriceDiff();
		m_initRefFarPriceDiff = other.GetInitRefFarPriceDiff();
		m_regulatoryFarPrice = other.GetRegulatoryFarPrice();
		m_nearPrice = other.GetNearPrice();
		m_nearPriceCompact = other.GetNearPriceCompact();
		m_regulatoryNearPrice = other.GetRegulatoryNearPrice();
		m_currentReferencePrice = other.GetCurrentReferencePrice();
		m_initialCurrentReferencePrice = other.GetInitialCurrentReferencePrice();
		m_currentReferencePriceChanged = other.isCurrentReferencePriceChanged();
		m_regulatoryCurrentReferencePrice = other.GetRegulatoryCurrentReferencePrice();
		m_pairedShares = other.GetPairedShares();
		m_regulatoryPairedShares = other.GetRegulatoryPairedShares();
		m_imbalanceShares = other.GetImbalanceShares();
		m_prevImbalanceShares = other.GetPrevImbalanceShares();
		m_regulatoryImbalanceShares = other.GetRegulatoryImbalanceShares();
		m_prevRegulatoryImbalanceShares = other.GetPrevRegulatoryImbalanceShares();
		m_initialImbalanceShares = other.GetInitialImbalanceShares();

//		m_imbalanceRatio = other.GetImbalanceRatio();
		m_imbalanceChange = other.GetImbalanceChange();

		m_t1555CurrentReferencePrice = other.GetT1555CurrentReferencePrice();
		m_t1555FarPrice = other.GetT1555FarPrice();
		m_t1555NearPrice = other.GetT1555NearPrice();

		m_t1558CurrentReferencePrice = other.GetT1558CurrentReferencePrice();
		m_t1558FarPrice = other.GetT1558FarPrice();
		m_t1558NearPrice = other.GetT1558NearPrice();

		m_openingImbalanceShares = other.GetOpeningImbalanceShares();
		m_openingPairedShares = other.GetOpeningPairedShares();
		m_openingCurrentReferencePrice = other.GetOpeningCurrentReferencePrice();

		m_t830ImbalanceShares = other.GetT830ImbalanceShares();
		m_t845ImbalanceShares = other.GetT845ImbalanceShares();
		m_t900ImbalanceShares = other.GetT900ImbalanceShares();
		m_t915ImbalanceShares = other.GetT915ImbalanceShares();
		m_t920ImbalanceShares = other.GetT920ImbalanceShares();
		m_t925ImbalanceShares = other.GetT925ImbalanceShares();
		m_t926ImbalanceShares = other.GetT926ImbalanceShares();
		m_t928ImbalanceShares = other.GetT928ImbalanceShares();

		m_t1545ImbalanceShares = other.GetT1545ImbalanceShares();
		m_t1550ImbalanceShares = other.GetT1550ImbalanceShares();
		m_t1555ImbalanceShares = other.GetT1555ImbalanceShares();
		m_t1556ImbalanceShares = other.GetT1556ImbalanceShares();
		m_t1557ImbalanceShares = other.GetT1557ImbalanceShares();
		m_t1558ImbalanceShares = other.GetT1558ImbalanceShares();
		m_t1559ImbalanceShares = other.GetT1559ImbalanceShares();

		m_marketImbalanceShares = other.GetMarketImbalanceShares();
		m_time = other.GetImbalanceTime();
		m_prevTime = other.GetPrevImbalanceTime();
		m_regulatoryTime = other.GetRegulatoryImbalanceTime();
		m_prevRegulatoryTime = other.GetPrevRegulatoryImbalanceTime();
		m_auctionTime = other.GetAuctionTime();
		m_delay = other.GetDelay();
//		m_imbalanceDirection = other.GetImbalanceDirection();
		m_crossType = other.GetCrossType();
		m_priceVariationIndicator = other.GetPriceVariationIndicator();
		m_freezeStatus = other.isFrozen();
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
	ST_STOCK_Count,
	ST_OPTION = ST_STOCK_Count,
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
	ChartPoint(const Price& price,
		const unsigned short& minute,
//#endif
		const unsigned int& date):
		m_startPrice(price),
		m_highPrice(price),
		m_lowPrice(price),
		m_endPrice(price),
		m_minute(minute),
		m_date(date),
		m_volume(0)
	{
	}
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
	void SetPrices(const Price& startPrice,
		const Price& highPrice,
		const Price& lowPrice,
		const Price& endPrice)
	{
		m_startPrice = startPrice;
		m_highPrice = highPrice;
		m_lowPrice = lowPrice;
		m_endPrice = endPrice;
	}
	void SetPrice(const Price& price)
	{
		m_startPrice =
		m_highPrice =
		m_lowPrice =
		m_endPrice = price;
	}
	void SetPriceAndVolume(const Price& price, const unsigned int& volume)
	{
		SetPrice(price);
		m_volume = volume;
		m_moneyTraded = price * volume;
		if(m_volume)
		{
			m_vwap = Price(m_moneyTraded / m_volume);
		}
		else
		{
			m_vwap.SetZero();
		}
	}
	void AddPriceAndVolume(const Price& price, const unsigned int& volume)
	{
		if(!price.isZero())
		{
			if(m_startPrice.isZero())
			{
				m_startPrice = price;
			}
			if(m_highPrice < price)
			{
				m_highPrice = price;
			}
			if(m_lowPrice > price || m_lowPrice.isZero())
			{
				m_lowPrice = price;
			}
			m_endPrice = price;
		}
		if(volume)
		{
			m_volume += volume;
			m_moneyTraded += price * volume;
			m_vwap = Price(m_moneyTraded / m_volume);
		}
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
			m_vwap = Price(m_moneyTraded / m_volume);
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

class TU_API StockLoanInfo// : public PriceQuantity
{
public:
	static const unsigned int uintZero;// = 0;
	static const unsigned char regularHtb;// = 'H';
	static const int defaultCompactBeta;// = 0;
	static const unsigned char defaultMargin;// = 100;

	static const unsigned char default_PM_EL_Rate;// = 15,
	static const unsigned char default_PM_ES_Rate;// = 15,
	static const unsigned char default_PM_HL_Rate;// = 15,
	static const unsigned char default_PM_HS_Rate;// = 15,
	static const unsigned char default_EL_Rate;// = 25,
	static const unsigned char default_ES_Rate;// = 30,
	static const unsigned char default_HL_Rate;// = 30,
	static const unsigned char default_HS_Rate;//30,
	static const unsigned char default_Fed_Req;//50,
	static const unsigned char default_Asset_Type;// = 'E',
	static const bool default_Marginable;// = true,
	static const unsigned char default_Sec_Type;// = 'C',
	static const unsigned char default_Status;// = 0,

	StockLoanInfo(const unsigned int& dollars,
		const unsigned int& dollarFraction,
		const unsigned int& quantity,
		const unsigned char& discountFlag,
		const unsigned char& margin,
		const int& betaDollars,
		const int& betaFraction,
		const unsigned char& htb,//= HTB::regularHtb) :

		const unsigned char& PM_EL_Rate,// = 15,
		const unsigned char& PM_ES_Rate,// = 15,
		const unsigned char& PM_HL_Rate,// = 15,
		const unsigned char& PM_HS_Rate,// = 15,
		const unsigned char& EL_Rate,// = 25,
		const unsigned char& ES_Rate,// = 30,
		const unsigned char& HL_Rate,// = 30,
		const unsigned char& HS_Rate,// = 30,
		const unsigned char& Fed_Req,// = 50,
		const unsigned char& Asset_Type,// = 'E',
		const bool& Marginable,// = true,
		const unsigned char& Sec_Type,// = 'C',
		const unsigned char& Status):// = 0):

		m_timestampHtb(0),
		m_compactBorrowPrice(Price::CalculateCompactPrice(dollars, dollarFraction)),
		m_availableQuantity(quantity),
		m_compactBeta(SignedPrice::CalculatIntCompactPrice(betaDollars, betaFraction)),
		m_margin(margin),
		m_discountFlag(discountFlag),
		m_htb(htb),

		m_PM_EL_Rate(PM_EL_Rate),
		m_PM_ES_Rate(PM_ES_Rate),
		m_PM_HL_Rate(PM_HL_Rate),
		m_PM_HS_Rate(PM_HS_Rate),
		m_EL_Rate(EL_Rate),
		m_ES_Rate(ES_Rate),
		m_HL_Rate(HL_Rate),
		m_HS_Rate(HS_Rate),
		m_Fed_Req(Fed_Req),
		m_Asset_Type(Asset_Type),
		m_Marginable(Marginable),
		m_Sec_Type(Sec_Type),
		m_Status(Status),

		m_valid(true)
	{}
	StockLoanInfo(
//		const Price& price,
		const unsigned int& compactPrice,
		const unsigned int& quantity,
		const unsigned char& discountFlag,
		const int& compactBeta,
		const unsigned char& margin,
		const unsigned char& htb,// = HTB::regularHtb):
		const unsigned char& PM_EL_Rate,// = 15,
		const unsigned char& PM_ES_Rate,// = 15,
		const unsigned char& PM_HL_Rate,// = 15,
		const unsigned char& PM_HS_Rate,// = 15,
		const unsigned char& EL_Rate,// = 25,
		const unsigned char& ES_Rate,// = 30,
		const unsigned char& HL_Rate,// = 30,
		const unsigned char& HS_Rate,// = 30,
		const unsigned char& Fed_Req,// = 50,
		const unsigned char& Asset_Type,// = 'E',
		const bool& Marginable,// = true,
		const unsigned char& Sec_Type,// = 'C',
		const unsigned char& Status):// = 0):

		m_timestampHtb(0),
		m_compactBorrowPrice(compactPrice),
		m_availableQuantity(quantity),
		m_compactBeta(compactBeta),
		m_margin(margin),
		m_discountFlag(discountFlag),
		m_htb(htb),

		m_PM_EL_Rate(PM_EL_Rate),
		m_PM_ES_Rate(PM_ES_Rate),
		m_PM_HL_Rate(PM_HL_Rate),
		m_PM_HS_Rate(PM_HS_Rate),
		m_EL_Rate(EL_Rate),
		m_ES_Rate(ES_Rate),
		m_HL_Rate(HL_Rate),
		m_HS_Rate(HS_Rate),
		m_Fed_Req(Fed_Req),
		m_Asset_Type(Asset_Type),
		m_Marginable(Marginable),
		m_Sec_Type(Sec_Type),
		m_Status(Status),

		m_valid(true)
	{}
	StockLoanInfo():
		m_timestampHtb(0),
		m_compactBorrowPrice(0),
		m_availableQuantity(0),
		m_compactBeta(defaultCompactBeta),
		m_margin(defaultMargin),
		m_discountFlag(0),
		m_htb(regularHtb),

		m_PM_EL_Rate(default_PM_EL_Rate),//15),
		m_PM_ES_Rate(default_PM_ES_Rate),
		m_PM_HL_Rate(default_PM_HL_Rate),
		m_PM_HS_Rate(default_PM_HS_Rate),
		m_EL_Rate(default_EL_Rate),
		m_ES_Rate(default_ES_Rate),
		m_HL_Rate(default_HL_Rate),
		m_HS_Rate(default_HS_Rate),
		m_Fed_Req(default_Fed_Req),
		m_Asset_Type(default_Asset_Type),
		m_Marginable(default_Marginable),
		m_Sec_Type(default_Sec_Type),
		m_Status(m_Status),

		m_valid(false)
	{}
	StockLoanInfo(const unsigned char& htb):
		m_timestampHtb(0),
		m_compactBorrowPrice(0),
		m_availableQuantity(0),
		m_compactBeta(defaultCompactBeta),
		m_margin(defaultMargin),
		m_discountFlag(0),
		m_htb(htb),

		m_PM_EL_Rate(default_PM_EL_Rate),//15),
		m_PM_ES_Rate(default_PM_ES_Rate),
		m_PM_HL_Rate(default_PM_HL_Rate),
		m_PM_HS_Rate(default_PM_HS_Rate),
		m_EL_Rate(default_EL_Rate),
		m_ES_Rate(default_ES_Rate),
		m_HL_Rate(default_HL_Rate),
		m_HS_Rate(default_HS_Rate),
		m_Fed_Req(default_Fed_Req),
		m_Asset_Type(default_Asset_Type),
		m_Marginable(default_Marginable),
		m_Sec_Type(default_Sec_Type),
		m_Status(m_Status),

		m_valid(true)
	{}
	const unsigned char& GetHTB() const{return m_htb;}
	void SetHTB(const unsigned char& htb)
	{
		if(htb != m_htb)
		{
#ifdef _DEBUG
if(htb == 0xFF)
{
printf("X");
}
#endif
			m_htb = htb;//m_valid = true;}
			m_timestampHtb = TL_GetCurrentMillisecond();
		}
	}
	const unsigned int& GetTimestampHtb() const{return m_timestampHtb;}
	const unsigned int& GetCompactBorrowPrice() const{return m_compactBorrowPrice;}
	const unsigned int& GetAvailableQuantity() const{return m_availableQuantity;}
	const unsigned char& GetDiscountFlag() const{return m_discountFlag;}
	void SetDiscountFlag(const unsigned char& discountFlag){m_discountFlag = discountFlag; m_valid = true;}
	const bool& isValid() const{return m_valid;}
//	void SetStockLoanInfoValid(const bool& valid){m_valid = valid;}
//	const SignedPrice& GetBeta() const{return m_beta;}
	const int& GetCompactBeta() const{return m_compactBeta;}
//	void SetBeta(const SignedPrice& beta){m_beta = beta;}
	void SetCompactBeta(const int& beta){m_compactBeta = beta;}// m_valid = true;}
	const unsigned char& GetMargin() const{return m_margin;}
	void SetMargin(const unsigned char& margin){m_margin = margin;}// m_valid = true;}

	const unsigned char& GetPmElRate() const{return m_PM_EL_Rate;}
	const unsigned char& GetPmEsRate() const{return m_PM_ES_Rate;}
	const unsigned char& GetPmHlRate() const{return m_PM_HL_Rate;}
	const unsigned char& GetPmHsRate() const{return m_PM_HS_Rate;}
	const unsigned char& GetElRate() const{return m_EL_Rate;}
	const unsigned char& GetEsRate() const{return m_ES_Rate;}
	const unsigned char& GetHlRate() const{return m_HL_Rate;}
	const unsigned char& GetHsRate() const{return m_HS_Rate;}
	const unsigned char& GetFedReq() const{return m_Fed_Req;}
	const unsigned char& GetAssetType() const{return m_Asset_Type;}
	const bool& isMarginable() const{return m_Marginable;}
	const unsigned char& GetSecType() const{return m_Sec_Type;}
	const unsigned char& GetStatus() const{return m_Status;}

	const unsigned char& ObtainMarginExcessRate(const bool& buy, const bool& portfolio) const
	{
		return portfolio ?
			buy ? m_PM_HL_Rate : m_PM_HS_Rate:
			buy ? m_HL_Rate : m_HS_Rate;
	}
	static const unsigned char& ObtainDefaultMarginExcessRate(const bool& buy, const bool& portfolio)
	{
		return portfolio ?
			buy ? default_PM_HL_Rate : default_PM_HS_Rate:
			buy ? default_HL_Rate : default_HS_Rate;
	}

	void SetPmElRate(const unsigned char& rate){m_PM_EL_Rate = rate;}
	void SetPmEsRate(const unsigned char& rate){m_PM_ES_Rate = rate;}
	void SetPmHlRate(const unsigned char& rate){m_PM_HL_Rate = rate;}
	void SetPmHsRate(const unsigned char& rate){m_PM_HS_Rate = rate;}
	void SetElRate(const unsigned char& rate){m_EL_Rate = rate;}
	void SetEsRate(const unsigned char& rate){m_ES_Rate = rate;}
	void SetHlRate(const unsigned char& rate){m_HL_Rate = rate;}
	void SetHsRate(const unsigned char& rate){m_HS_Rate = rate;}
	void SetFedReq(const unsigned char& rate){m_Fed_Req = rate;}
	void SetAssetType(const unsigned char& type){m_Asset_Type = type;}
	void SetMarginable(const bool& marginable){m_Marginable = marginable;}
	void SetSecType(const unsigned char& type){m_Sec_Type = type;}
	void SetStatus(const unsigned char& status){m_Status = status;}

	bool SetRetailParams(const StockLoanInfo& other)
	{
		bool changed = other.m_PM_EL_Rate != m_PM_EL_Rate;
		if(changed)m_PM_EL_Rate = other.m_PM_EL_Rate;
		if(other.m_PM_ES_Rate != m_PM_ES_Rate)
		{
			m_PM_ES_Rate = other.m_PM_ES_Rate;
			changed = true;
		}
		if(other.m_PM_HL_Rate != m_PM_HL_Rate)
		{
			m_PM_HL_Rate = other.m_PM_HL_Rate;
			changed = true;
		}
		if(other.m_PM_HS_Rate != m_PM_HS_Rate)
		{
			m_PM_HS_Rate = other.m_PM_HS_Rate;
			changed = true;
		}
		if(other.m_EL_Rate != m_EL_Rate)
		{
			m_EL_Rate = other.m_EL_Rate;
			changed = true;
		}
		if(other.m_ES_Rate != m_ES_Rate)
		{
			m_ES_Rate = other.m_ES_Rate;
			changed = true;
		}
		if(other.m_HL_Rate != m_HL_Rate)
		{
			m_HL_Rate = other.m_HL_Rate;
			changed = true;
		}
		if(other.m_HS_Rate != m_HS_Rate)
		{
			m_HS_Rate = other.m_HS_Rate;
			changed = true;
		}
		if(other.m_Fed_Req != m_Fed_Req)
		{
			m_Fed_Req = other.m_Fed_Req;
			changed = true;
		}
		if(other.m_Asset_Type != m_Asset_Type)
		{
			m_Asset_Type = other.m_Asset_Type;
			changed = true;
		}
		if(other.m_Marginable != m_Marginable)
		{
			m_Marginable = other.m_Marginable;
			changed = true;
		}
		if(other.m_Sec_Type != m_Sec_Type)
		{
			m_Sec_Type = other.m_Sec_Type;
			changed = true;
		}
		if(other.m_Status != m_Status)
		{
			m_Status = other.m_Status;
			changed = true;
		}
		return changed;
	}

	bool SetStockLoanInfo(const StockLoanInfo& other)
	{
		bool changed = SetStockLoanInfoOnly(other);
		if(other.m_compactBeta || other.m_margin)
		{
			if(other.m_compactBeta != m_compactBeta)
			{
				m_compactBeta = other.m_compactBeta;
				changed = true;
			}
			if(other.m_margin != m_margin)
			{
				m_margin = other.m_margin;
				changed = true;
			}
		}
		if(other.m_htb != 0xFF)
		{
			if(other.m_htb != m_htb)
			{
				m_htb = other.m_htb;
				m_timestampHtb = TL_GetCurrentMillisecond();
				changed = true;
			}
		}
		if(SetRetailParams(other))
		{
			changed = true;
		}
		return changed;
	}
	bool SetStockLoanInfoOnly(const unsigned int& price, const unsigned int& size, const unsigned char& discountFlag)
	{
		bool changed = price != m_compactBorrowPrice;
		if(changed)m_compactBorrowPrice = price;
		if(size != m_availableQuantity)
		{
			m_availableQuantity = size;
			changed = true;
		}
		if(discountFlag != m_discountFlag)
		{
			m_discountFlag = discountFlag;
			changed = true;
		}
		m_valid = true;
		return changed;
	}
	bool SetStockLoanInfoOnly(const StockLoanInfo& other)
	{
		return SetStockLoanInfoOnly(other.m_compactBorrowPrice, other.m_availableQuantity, other.m_discountFlag);
/*
		bool changed = other.m_compactBorrowPrice != m_compactBorrowPrice;
		if(changed)m_compactBorrowPrice = other.m_compactBorrowPrice;
		if(other.m_availableQuantity != m_availableQuantity)
		{
			m_availableQuantity = other.m_availableQuantity;
			changed = true;
		}
		if(other.m_discountFlag != m_discountFlag)
		{
			m_discountFlag = other.m_discountFlag;
			changed = true;
		}
		m_valid = true;
		return changed;
*/
	}
/*
	bool SetStockLoanInfoAndBeta(const StockLoanInfo& other)
	{
		bool changed = SetStockLoanInfoOnly(other);
		if(other.m_compactBeta != m_compactBeta)
		{
			m_compactBeta = other.m_compactBeta;
			changed = true;
		}
		if(other.m_margin != m_margin)
		{
			m_margin = other.m_margin;
			changed = true;
		}
		if(SetRetailParams(other))
		{
			changed = true;
		}
		return changed;
	}
*/
	bool SetBetaAndRetailInfo(const StockLoanInfo& other)
	{
		bool changed = other.m_compactBeta != m_compactBeta;
		if(changed)
		{
			m_compactBeta = other.m_compactBeta;
			changed = true;
		}
		if(other.m_margin != m_margin)
		{
			m_margin = other.m_margin;
			changed = true;
		}
		if(SetRetailParams(other))
		{
			changed = true;
		}
		return changed;
	}

	bool operator==(const StockLoanInfo& other) const
	{
		return other.m_compactBorrowPrice == m_compactBorrowPrice
			&& other.m_availableQuantity == m_availableQuantity
			&& other.m_compactBeta == m_compactBeta
			&& other.m_margin == m_margin
			&& other.m_discountFlag == m_discountFlag
			&& other.m_htb == m_htb

			&& other.m_PM_EL_Rate == m_PM_EL_Rate
			&& other.m_PM_ES_Rate == m_PM_ES_Rate
			&& other.m_PM_HL_Rate == m_PM_HL_Rate
			&& other.m_PM_HS_Rate == m_PM_HS_Rate
			&& other.m_EL_Rate == m_EL_Rate
			&& other.m_ES_Rate == m_ES_Rate
			&& other.m_HL_Rate == m_HL_Rate
			&& other.m_HS_Rate == m_HS_Rate
			&& other.m_Fed_Req == m_Fed_Req
			&& other.m_Asset_Type == m_Asset_Type
			&& other.m_Marginable == m_Marginable
			&& other.m_Sec_Type == m_Sec_Type
			&& other.m_Status == m_Status;
	}
	bool operator!=(const StockLoanInfo& other) const{return !operator==(other);}

protected:
	unsigned int m_timestampHtb;
	unsigned int m_compactBorrowPrice;
	unsigned int m_availableQuantity;
	int m_compactBeta;
	unsigned char m_margin;
	unsigned char m_discountFlag;
	unsigned char m_htb;
//07/02/2019
	unsigned char m_PM_EL_Rate;
	unsigned char m_PM_ES_Rate;
	unsigned char m_PM_HL_Rate;
	unsigned char m_PM_HS_Rate;
	unsigned char m_EL_Rate;
	unsigned char m_ES_Rate;
	unsigned char m_HL_Rate;
	unsigned char m_HS_Rate;
	unsigned char m_Fed_Req;
	unsigned char m_Asset_Type;
	bool m_Marginable;
	unsigned char m_Sec_Type;
	unsigned char m_Status;

	bool m_valid;
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

enum HtbEnum : unsigned char
{
	HTB_ETB,
	HTB_HTB,//Available
	HTB_htb,//Unavailable

	HTB_Count
};

enum HtbFilterEnum : unsigned int
{
	HTBF_ETB = 1 << HTB_ETB,
	HTBF_HTB = 1 << HTB_HTB,//Available
	HTBF_htb = 1 << HTB_htb,//Unavailable

	HTBF_All = (1 << HTB_Count) - 1
};

class TU_API HTB
{
public:
	HTB(const char* symbol);
//	static const unsigned char regularHtb;// = 'H';
	const char* GetSymbol() const{return (const char*)&m_numericSymbol;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}

//	static const unsigned char htbCapacity = 16;
	static const unsigned char stockLoanCapacity = 16;

//	typedef std::vector<unsigned char> UCharVector;
//	typedef std::vector<StockLoanInfo> StockLoanVector;
//	const UCharVector& GetHTBVector() const{return m_htbVector;}
//	const StockLoanVector& GetStockLoanInfoVector() const{return m_stockLoanVector;}

#ifndef TAKION_NO_OPTIONS
	virtual
#endif
//	const unsigned char& isHTB(const unsigned int& ordinal) const{return ordinal < (unsigned int)m_htbVector.size() ? m_htbVector[ordinal] : regularHtb;}
	const unsigned char& isHTB(const unsigned char& slOrdinal) const{return slOrdinal < stockLoanCapacity ? m_stockLoanArray[slOrdinal].GetHTB() : StockLoanInfo::regularHtb;}

	unsigned int GetHtbFilter(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& slInfo = m_stockLoanArray[slOrdinal];
			if(slInfo.GetHTB())
			{
				const unsigned int* borrowSize = GetBorrowSize(slOrdinal);
				return borrowSize && *borrowSize ? HTBF_HTB : HTBF_htb;
			}
			return HTBF_ETB;
		}
		return HTBF_htb;
/*
		if(isHTB(slOrdinal))
		{
			const unsigned int* borrowSize = GetBorrowSize(slOrdinal);
			return borrowSize && *borrowSize ? HTBF_HTB : HTBF_htb;
		}
		else return HTBF_ETB;
//		return isHTB(ordinal) ? GetBorrowSize(ordinal) ? HTBF_HTB : HTBF_htb : HTBF_ETB;
*/
	}

	const unsigned int* GetTimestampHtb(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return &stockLoanInfo.GetTimestampHtb();
		}
		return NULL;
	}
	const unsigned int& ObtainTimestampHtb(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.GetTimestampHtb();
		}
		return StockLoanInfo::uintZero;
	}

/*
	const Price* GetBorrowPrice(const unsigned char& slOrdinal) const
	{
//		if(slOrdinal < (unsigned int)m_stockLoanVector.size())
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo : NULL;
		}
		return NULL;
	}
*/
	const unsigned int* GetCompactBorrowPrice(const unsigned char& slOrdinal) const
	{
//		if(slOrdinal < (unsigned int)m_stockLoanVector.size())
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetCompactBorrowPrice() : NULL;
		}
		return NULL;
	}
/*
	const unsigned int ObtainCompactBorrowPrice(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetCompactBorrowPrice() : 0;
		}
		return 0;
	}
*/
	const unsigned int* GetBorrowSize(const unsigned char& slOrdinal) const
	{
//		if(slOrdinal < (unsigned int)m_stockLoanVector.size())
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
//			return stockLoanInfo.isValid() ? &stockLoanInfo.GetQuantity() : NULL;
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetAvailableQuantity() : NULL;
		}
		return NULL;
	}
	const unsigned int& ObtainBorrowSize(const unsigned char& slOrdinal) const
	{
//		if(slOrdinal < (unsigned int)m_stockLoanVector.size())
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
//			return stockLoanInfo.isValid() ? stockLoanInfo.GetQuantity() : 0;
			return stockLoanInfo.isValid() ? stockLoanInfo.GetAvailableQuantity() : StockLoanInfo::uintZero;
		}
		return StockLoanInfo::uintZero;
	}
//	unsigned char GetBorrowDiscountFlag(const unsigned int& slOrdinal) const{return ordinal < (unsigned int)m_stockLoanVector.size() ? m_stockLoanVector[slOrdinal].GetDiscountFlag() : 1;}
	unsigned char GetBorrowDiscountFlag(const unsigned char& slOrdinal) const
	{
		return slOrdinal < stockLoanCapacity ? m_stockLoanArray[slOrdinal].GetDiscountFlag() : 1;
	}

//	const SignedPrice* GetBeta(const unsigned char& slOrdinal) const
	const int* GetCompactBeta(const unsigned char& slOrdinal) const
	{
//		if(slOrdinal < (unsigned int)m_stockLoanVector.size())
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetCompactBeta() : NULL;
		}
		return NULL;
	}
	const int& ObtainCompactBeta(const unsigned char& slOrdinal) const
	{
//		if(slOrdinal < (unsigned int)m_stockLoanVector.size())
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
//			return stockLoanInfo.isValid() ? stockLoanInfo.GetBeta().GetIntCompactPrice() : 0;
			return stockLoanInfo.isValid() ? stockLoanInfo.GetCompactBeta() : StockLoanInfo::defaultCompactBeta;
		}
		return StockLoanInfo::defaultCompactBeta;
	}
	const unsigned char* GetMargin(const unsigned char& slOrdinal) const
	{
//		if(slOrdinal < (unsigned int)m_stockLoanVector.size())
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetMargin() : NULL;
		}
		return NULL;
	}
	const unsigned char& ObtainMargin(const unsigned char& slOrdinal) const
	{
//		if(slOrdinal < (unsigned int)m_stockLoanVector.size())
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetMargin() : StockLoanInfo::defaultMargin;
		}
		return StockLoanInfo::defaultMargin;
	}

	const unsigned char* GetPmElRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetPmElRate() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetPmEsRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetPmEsRate() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetPmHlRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetPmHlRate() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetPmHsRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetPmHsRate() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetElRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetElRate() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetEsRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetEsRate() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetHlRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetHlRate() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetHsRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetHsRate() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetFedReq(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetFedReq() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetAssetType(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetAssetType() : NULL;
		}
		return NULL;
	}
	const bool* isMarginable(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.isMarginable() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetSecType(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetSecType() : NULL;
		}
		return NULL;
	}
	const unsigned char* GetStatus(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? &stockLoanInfo.GetStatus() : NULL;
		}
		return NULL;
	}

//////
	const unsigned char& ObtainPmElRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetPmElRate() : StockLoanInfo::default_PM_EL_Rate;
		}
		return StockLoanInfo::default_PM_EL_Rate;
	}
	const unsigned char& ObtainPmEsRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetPmEsRate() : StockLoanInfo::default_PM_ES_Rate;
		}
		return StockLoanInfo::default_PM_ES_Rate;
	}
	const unsigned char& ObtainPmHlRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetPmHlRate() : StockLoanInfo::default_PM_HL_Rate;
		}
		return StockLoanInfo::default_PM_HL_Rate;
	}
	const unsigned char& ObtainPmHsRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetPmHsRate() : StockLoanInfo::default_PM_HS_Rate;
		}
		return StockLoanInfo::default_PM_HS_Rate;
	}
	const unsigned char& ObtainElRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];//m_stockLoanVector[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetElRate() : StockLoanInfo::default_EL_Rate;
		}
		return StockLoanInfo::default_EL_Rate;
	}
	const unsigned char& ObtainEsRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetEsRate() : StockLoanInfo::default_ES_Rate;
		}
		return StockLoanInfo::default_ES_Rate;
	}
	const unsigned char& ObtainHlRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetHlRate() : StockLoanInfo::default_HL_Rate;
		}
		return StockLoanInfo::default_HL_Rate;
	}
	const unsigned char& ObtainHsRate(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetHsRate() : StockLoanInfo::default_HS_Rate;
		}
		return StockLoanInfo::default_HS_Rate;
	}
	const unsigned char& ObtainMarginExcessRate(const unsigned char& slOrdinal, const bool& buy, const bool& portfolio) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.ObtainMarginExcessRate(buy, portfolio) : StockLoanInfo::ObtainDefaultMarginExcessRate(buy, portfolio);
		}
		return StockLoanInfo::default_HS_Rate;
	}
	const unsigned char& ObtainFedReq(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetFedReq() : StockLoanInfo::default_Fed_Req;
		}
		return StockLoanInfo::default_Fed_Req;
	}
	const unsigned char& ObtainAssetType(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetAssetType() : StockLoanInfo::default_Asset_Type;
		}
		return StockLoanInfo::default_Asset_Type;
	}
	const bool& ObtainMarginable(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.isMarginable() : StockLoanInfo::default_Marginable;
		}
		return StockLoanInfo::default_Marginable;
	}
	const unsigned char& ObtainSecType(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetSecType() : StockLoanInfo::default_Sec_Type;
		}
		return StockLoanInfo::default_Sec_Type;
	}
	const unsigned char& ObtainStatus(const unsigned char& slOrdinal) const
	{
		if(slOrdinal < stockLoanCapacity)
		{
			const StockLoanInfo& stockLoanInfo = m_stockLoanArray[slOrdinal];
			return stockLoanInfo.isValid() ? stockLoanInfo.GetStatus() : StockLoanInfo::default_Status;
		}
		return StockLoanInfo::default_Status;
	}
//////

//	void SetHtb(unsigned int ordinal, bool htb);
//	bool SetHTB(const unsigned char& htbOrdinal, const unsigned char& htb);
	bool SetHTB(const unsigned char& slOrdinal, const unsigned char& htb);
	bool SetStockLoanInfo(const unsigned char& slOrdinal, const StockLoanInfo& info);
	bool SetBorrowInfo(const unsigned char& slOrdinal, const unsigned int& price, const unsigned int& size, const unsigned char& discountFlag);
	bool SetBorrowInfo(const unsigned char& slOrdinal, const StockLoanInfo& info)
	{
		return SetBorrowInfo(slOrdinal, info.GetCompactBorrowPrice(), info.GetAvailableQuantity(), info.GetDiscountFlag());
	}
	bool SetBetaAndRetailInfo(const unsigned char& slOrdinal, const StockLoanInfo& info);
protected:
	unsigned __int64 m_numericSymbol;
//	unsigned char m_htbArray[htbCapacity];
	StockLoanInfo m_stockLoanArray[stockLoanCapacity];
//	unsigned char m_htbSize;
	unsigned char m_slSize;
//	UCharVector m_htbVector;
//	StockLoanVector m_stockLoanVector;
};

class LineBufferArray;

const unsigned int MAX_SECURITY_NAME = 30;

enum MoveReportLevel : unsigned char//flags
{
	MRL_MOVES = 1,
	MRL_JOINS = 2,
	MRL_PRINTS = 4,
	MRL_PRINTS_ODD = 8,
};

enum GoodBadCode : unsigned char
{
	GBC_VERY_BAD,
	GBC_BAD,
	GBC_GOOD,
	GBC_VERY_GOOD,

	GBC_PRINT_BAD,
	GBC_PRINT_GOOD,
	GBC_PRINT_SAME,

	GBC_PRINT_ODD_BAD,
	GBC_PRINT_ODD_GOOD,
	GBC_PRINT_ODD_SAME,

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

enum OptionParseError : unsigned char
{
	OPE_OK,
	OPE_SUFFIX,
	OPE_MONTH,
	OPE_DAY,
	OPE_YEAR,
	OPE_CALLPUT,
	OPE_STRIKE,

	OPE_Count
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
	explicit OptionKey(const unsigned int& strikePrice,
		const unsigned int& date,
		const bool& call):
		m_strikePrice(strikePrice),
		m_flags(call ? OPTF_CALL : '\0'),
		m_expirationDay((unsigned char)(date & 0xFF)),
		m_expirationMonth((unsigned char)((date >> 8) & 0xFF)),
		m_expirationYear((unsigned char)((date >> 16) & 0xFF))
	{}
	explicit OptionKey(const unsigned __int64& underlierSymbolNum,
		const unsigned __int64& rootSymbolNum,
		const unsigned int& strikePrice,
		const unsigned int& date,
		const bool& call):
		m_strikePrice(strikePrice),
		m_flags(call ? OPTF_CALL : '\0'),
		m_expirationDay((unsigned char)(date & 0xFF)),
		m_expirationMonth((unsigned char)((date >> 8) & 0xFF)),
		m_expirationYear((unsigned char)((date >> 16) & 0xFF))
	{
		const unsigned char suffix = CalculateSuffix(underlierSymbolNum, rootSymbolNum);
		m_flags |= (suffix & OPTF_SUFFIX);
	}

	explicit OptionKey(const bool& call,
		const unsigned char& expirationDay,
		const unsigned char& expirationMonth,
		const unsigned char& expirationYear,
		const unsigned int& strikePrice):
		m_strikePrice(strikePrice),
		m_flags(call ? OPTF_CALL : '\0'),
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
//			unsigned int strikePrice = (unsigned int)optionBlock;
//			unsigned int dollars = strikePrice / 1000;
//			m_strikePrice = (dollars << 14) | (strikePrice - 1000 * dollars) * 10;
			m_strikePrice = Price::CalculateCompactPriceFromStrikePrice((unsigned int)optionBlock);
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
			const unsigned char suffix = CalculateSuffix(underlierSymbolNum, rootSymbolNum);
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
//			unsigned int strikePrice = (unsigned int)optionBlock;
//			unsigned int dollars = strikePrice / 1000;
//			m_strikePrice = (dollars << 14) | (strikePrice - 1000 * dollars) * 10;
//			m_strikePrice = Price::CalculateCompactPrice(dollars, (strikePrice - 1000 * dollars) * 10);
			m_strikePrice = Price::CalculateCompactPriceFromStrikePrice((unsigned int)optionBlock);
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
	explicit OptionKey(const char* str, const bool& withSuffix = true)
	{
		Parse(str, withSuffix);
	}
	explicit OptionKey(const unsigned __int64& optionKeyValue = 0):m_optionKeyValue(optionKeyValue){}
	virtual ~OptionKey(){}

	static unsigned char CalculateSuffix(const unsigned __int64& underlierSymbolNum, const unsigned __int64& rootSymbolNum)
	{
		if(underlierSymbolNum != rootSymbolNum)
		{
			const unsigned char* underlierCursor = (const unsigned char*)&underlierSymbolNum;
			const unsigned char* rootCursor = (const unsigned char*)&rootSymbolNum;
			for(unsigned char i = sizeof(underlierSymbolNum); i; --i, ++underlierCursor, ++rootCursor)
			{
				if(*underlierCursor != *rootCursor)
				{
					if(!*underlierCursor && !*(rootCursor + 1))//suffix
					{
						return *rootCursor;
					}
/*
					else//Option Symbol is different from the underlierSymbol (Old Symbology)
					{
					}
*/
					break;
				}
			}
		}
		return '\0';
	}
	static unsigned __int64 CalculateRootSymbol(const unsigned __int64& underlierSymbolNum, const unsigned char& suffix)
	{
		if(suffix)
		{
			unsigned __int64 rootSymbolNum = underlierSymbolNum;
			unsigned char* rootCursor = (unsigned char*)&rootSymbolNum;
			for(unsigned char i = 0; i < sizeof(rootSymbolNum) - 1; ++i, ++rootCursor)
			{
				if(!*rootCursor)
				{
					*rootCursor = suffix;
					return rootSymbolNum;
				}
			}
		}
		return underlierSymbolNum;
	}
	static unsigned __int64 CalculateUnderlierSymbol(const unsigned __int64& rootSymbolNum, const unsigned char& suffix)
	{
		if(suffix)
		{
			unsigned __int64 underlierSymbolNum = rootSymbolNum;
			unsigned char* underlierCursor = (unsigned char*)&underlierSymbolNum;
			for(unsigned char i = 0; i < sizeof(rootSymbolNum); ++i, ++underlierCursor)
			{
				if(!*underlierCursor)
				{
					if(i > 1)
					{
						--underlierCursor;
						if(*underlierCursor == suffix)
						{
							*underlierCursor = '\0';
							return underlierSymbolNum;
						}
					}
					break;
				}
			}
		}
		return rootSymbolNum;
	}
	virtual unsigned char Parse(const char* str, const bool withSuffix)
	{
		m_optionKeyValue = 0;
		
		char flags = '\0';
		unsigned char month, day, year;

		char c = *str;
		if(withSuffix)
		{
			if(c < ' ')return OPE_SUFFIX;
			if(c > ' ')flags |= (unsigned char)c & OPTF_SUFFIX;

			c = *++str;
		}
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
			U_StrToPrice(price, str, 2);
			m_strikePrice = price.GetCompactPrice();
		}
		if(!m_strikePrice)return OPE_STRIKE;

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
		U_PriceToStr(str, Price(m_strikePrice), 4, '\0', true, ' ', true);
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
//		return (((unsigned __int64)m_expirationYear) << 56) | (((unsigned __int64)(m_expirationMonth + ((m_flags & OPTF_CALL) ? 'A' - 1 : 'L'))) << 48) | (((unsigned __int64)m_expirationDay) << 40) | ((m_strikePrice >> 14) * 1000 + (m_strikePrice & 0x3FFF) / 10);
		return (((unsigned __int64)m_expirationYear) << 56) | (((unsigned __int64)(m_expirationMonth + ((m_flags & OPTF_CALL) ? 'A' - 1 : 'L'))) << 48) | (((unsigned __int64)m_expirationDay) << 40) | Price::CalculateStrikePriceFromCompactPrice(m_strikePrice);
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
	unsigned char CalculateExpirationDayOfWeek() const{return (unsigned char)TL_GetDayOfWeek(2000 + m_expirationYear, m_expirationMonth, m_expirationDay);}
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
			if(expirationDay >= 15 && expirationDay <= 21)
			{
				return OET_MONTHLY;
			}
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
//02/08/2019
		else
		{
			optionSymbol += ' ';
		}
		U_AppendTwoDigits(optionSymbol, GetExpirationYear());
		U_AppendTwoDigits(optionSymbol, GetExpirationMonth());
		U_AppendTwoDigits(optionSymbol, GetExpirationDay());
		optionSymbol += isCall() ? 'C' : 'P';
		Price strikePrice(m_strikePrice);
		if(strikePrice.GetDollarFraction())
		{
			U_PriceToStr(optionSymbol, strikePrice, 2, -1, false);
		}
		else
		{
			char num[33];
			optionSymbol += U_UnsignedNumberToStrNoDecDigits(strikePrice.GetDollars(), num, sizeof(num));
		}
	}
	void GetExpirationTokens(unsigned char& expirationDay, unsigned char& expirationMonth, unsigned char& expirationYear) const
	{
		expirationDay = m_expirationDay;
		expirationMonth = m_expirationMonth;
		expirationYear = m_expirationYear;
	}

	static unsigned char GetFlagsFromNumber(const unsigned __int64& optionKeyValue){return (unsigned char)(optionKeyValue >> 32);}
	static bool isPutFromNumber(const unsigned __int64& optionKeyValue){return !(GetFlagsFromNumber(optionKeyValue) & OPTF_CALL);}
	static bool isCallFromNumber(const unsigned __int64& optionKeyValue){return !isPutFromNumber(optionKeyValue);}
	static unsigned char GetSuffixFromNumber(const unsigned __int64& optionKeyValue){return GetFlagsFromNumber(optionKeyValue) & OPTF_SUFFIX;}
	static unsigned char GetExpirationDayFromNumber(const unsigned __int64& optionKeyValue){return (unsigned char)(optionKeyValue >> 40);}
	static unsigned char GetExpirationMonthFromNumber(const unsigned __int64& optionKeyValue){return (unsigned char)(optionKeyValue >> 48);}
	static unsigned int GetExpirationYearFromNumber(const unsigned __int64& optionKeyValue){return (unsigned int)(unsigned char)(optionKeyValue >> 56) + 2000;}
	static unsigned int GetExpirationDateFromNumber(const unsigned __int64& optionKeyValue){return GetExpirationYearFromNumber(optionKeyValue) * 10000 + (unsigned int)GetExpirationMonthFromNumber(optionKeyValue) * 100 + GetExpirationDayFromNumber(optionKeyValue);}
	static unsigned int GetStrikePriceCompactFromNumber(const unsigned __int64& optionKeyValue){return (unsigned int)optionKeyValue;}
protected:
	union
	{
		unsigned __int64 m_optionKeyValue;
		struct
		{
			unsigned int m_strikePrice;
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
		const unsigned int& date,
		const bool& call):
		OptionKey(strikePrice, date, call),
		m_symbolNum(symbolNum)
	{}

	explicit OptionSymbolKey(const unsigned __int64& underlierSymbolNum,
		const unsigned __int64& rootSymbolNum,
		const unsigned int& strikePrice,
		const unsigned int& date,
		const bool& call):
		OptionKey(underlierSymbolNum, rootSymbolNum, strikePrice, date, call),
		m_symbolNum(rootSymbolNum)//underlierSymbolNum)
	{
//		if(!(m_flags & OPTF_SUFFIX))m_symbolNum = rootSymbolNum;
	}

	explicit OptionSymbolKey(const unsigned __int64& symbolNum,
		const unsigned char& flags,
		const unsigned int& strikePrice,
//		const bool& call,
//		const char& suffix,
		const unsigned char& expirationDay,
		const unsigned char& expirationMonth,
		const unsigned char& expirationYear):
		OptionKey(strikePrice, flags, expirationDay, expirationMonth, expirationYear),
		m_symbolNum(symbolNum)
	{}
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
	explicit OptionSymbolKey(const unsigned __int64& symbolNum,
		const unsigned __int64& optionKey):
		OptionKey(optionKey),
		m_symbolNum(symbolNum)
	{}
	explicit OptionSymbolKey(const unsigned __int64& underlierSymbolNum,
		const unsigned __int64& rootSymbolNum,
		const unsigned __int64& optionBlock):
		OptionKey(underlierSymbolNum, rootSymbolNum, optionBlock),
		m_symbolNum(rootSymbolNum)//underlierSymbolNum)
	{
//		if(!(m_flags & OPTF_SUFFIX))m_symbolNum = rootSymbolNum;
	}
	explicit OptionSymbolKey(const unsigned __int64& rootSymbolNum,
		const unsigned char& suffix,
		const unsigned __int64& optionBlock):
		OptionKey(optionBlock, suffix),
		m_symbolNum(rootSymbolNum)//CalculateUnderlierSymbol(rootSymbolNum, suffix))
	{}
	explicit OptionSymbolKey(const unsigned __int64& underlierSymbolNum,
		const unsigned __int64& optionBlock,
		const unsigned char& suffix):
		OptionKey(optionBlock, suffix),
		m_symbolNum(CalculateRootSymbol(underlierSymbolNum, suffix))//underlierSymbolNum)
	{
	}
	explicit OptionSymbolKey(const unsigned __int64& symbolNum = 0):m_symbolNum(symbolNum){}
	explicit OptionSymbolKey(const char* str, const bool& withSuffix = true)
	{
		Parse(str, withSuffix);
	}
//	virtual ~OptionSymbolKey(){}

	virtual unsigned char Parse(const char* str, const bool withSuffix) override
	{
		m_symbolNum = 0;
		m_optionKeyValue = 0;
		char* dst = (char*)&m_symbolNum;
		char c = *str;
		for(unsigned int i = sizeof(m_symbolNum) - 1; c && c != ' ' && i; --i, ++dst, c = *++str)
		{
			*dst = c;
		}
		return !m_symbolNum ? OPE_Count : c == ' ' ? OptionKey::Parse(++str, withSuffix) : OPE_OK;
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
/*
	enum OptionParseError : unsigned char
	{
		OPE_OK,
		OPE_SUFFIX,
		OPE_MONTH,
		OPE_DAY,
		OPE_YEAR,
		OPE_CALLPUT,
		OPE_STRIKE,

		OPE_Count
	};
*/
	unsigned char Parse(const char* cursor)
	{
		m_rootSymbolNum = 0;
		char* cursorDest = (char*)&m_rootSymbolNum;
		char c = *cursor;

		for(unsigned char i = sizeof(m_rootSymbolNum) - 1; c && c != ' ' && i; --i, ++cursorDest, c = *++cursor)*cursorDest = c;

		if(m_rootSymbolNum)
		{
			if(c == ' ')
			{
				return ParseOptionBlock(++cursor);
			}
			else
			{
				m_optionBlock = 0;
				return OPE_OK;
			}
		}
		else
		{
			m_optionBlock = 0;
			return OPE_Count;
		}
	}

	unsigned char ParseOptionBlock(const char* cursor)
	{
		unsigned char error = OPE_OK;
		m_optionBlock = ParseOptionBlockStatic(cursor, error);
		return error;
	}
	static unsigned __int64 ParseOptionBlockStatic(const char* cursor, unsigned char& error)
	{
		char c = *cursor;
		
		if(c == ' ')c = *++cursor;

		if(c < '0' || c > '9')
		{
			error = OPE_YEAR;
			return 0;
		}
		unsigned char dateToken = (c - '0') * 10;

		c = *++cursor;
		if(c < '0' || c > '9')
		{
			error = OPE_YEAR;
			return 0;
		}
		dateToken += c - '0';

		unsigned __int64 optionBlock = (unsigned __int64)dateToken << 56;//year

		c = *++cursor;
		if(c < '0' || c > '1')
		{
			error = OPE_MONTH;
			return 0;
		}
		unsigned char monthToken = (c - '0') * 10;

		c = *++cursor;
		if(c < '0' || c > '9')
		{
			error = OPE_MONTH;
			return 0;
		}
		monthToken += c - '0';
		if(!monthToken || monthToken > 12)
		{
			error = OPE_MONTH;
			return 0;
		}
		c = *++cursor;
		if(c < '0' || c > '3')
		{
			error = OPE_DAY;
			return 0;
		}
		dateToken = (c - '0') * 10;

		c = *++cursor;
		if(c < '0' || c > (dateToken < 30 ? '9' : '1'))
		{
			error = OPE_DAY;
			return 0;
		}
		dateToken += c - '0';
		if(!dateToken || dateToken > 31)
		{
			error = OPE_DAY;
			return 0;
		}
		optionBlock |= (unsigned __int64)dateToken << 40;//day

		c = *++cursor;
		if(c == 'C' || c == 'c')monthToken += ('A' - 1);
		else if(c == 'P' || c == 'p')monthToken += 'L';
		else
		{
			error = OPE_CALLPUT;
			return 0;
		}
		optionBlock |= (unsigned __int64)monthToken << 48;//month

		c = *++cursor;
		if(!c)
		{
			error = OPE_STRIKE;
			return 0;
		}
		Price price;
		U_StrToPrice(price, cursor, 2);
		if(price.isZero())
		{
			error = OPE_STRIKE;
			return 0;
		}
//		error = OPE_OK;
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
		if(optionBlock)
		{
			unsigned char expMonth = (unsigned char)(optionBlock >> 48);
			bool call = expMonth < 'M';
			str += call ? "Call $" : "Put $";
			unsigned int strikePrice = (unsigned int)optionBlock;
			unsigned int dollars = strikePrice / 1000;

			unsigned int fraction = strikePrice - 1000 * dollars;
			if(fraction)
			{
				U_PriceToStr(str, Price(dollars, fraction * (Price::divider / 1000)), 2, -1, false, ' ', true);
			}
			else
			{
				char num[33];
				str += U_UnsignedNumberToStrNoDecDigits(dollars, num, sizeof(num));
	//			str += ".00";
			}

	//		TU_PriceToStr(str, Price(dollars, (strikePrice - 1000 * dollars) * (Price::divider / 1000)), 4, true, ' ', true);

			str += 'x';
			U_AppendTwoDigits(str, call ? expMonth - ('A' - 1) : expMonth - 'L', '-');
			U_AppendTwoDigits(str, (unsigned char)(optionBlock >> 40), '-');
			U_AppendTwoDigits(str, (unsigned char)(optionBlock >> 56));
		}
	}
	void OptionBlockToString(std::string& str) const
	{
		ConvertOptionBlockToString(str, m_optionBlock);
	}
	void toString(std::string& str) const
	{
		str += (const char*)&m_rootSymbolNum;
		str += ' ';
		OptionBlockToString(str);
	}
	static void ConvertOptionBlockToInstrumentString(std::string& str, const unsigned __int64& optionBlock)
	{
		if(optionBlock)
		{
			unsigned char expMonth = (unsigned char)(optionBlock >> 48);
			bool call = expMonth < 'M';
			U_AppendTwoDigits(str, (unsigned char)(optionBlock >> 56));
			U_AppendTwoDigits(str, call ? expMonth - ('A' - 1) : expMonth - 'L');
			U_AppendTwoDigits(str, (unsigned char)(optionBlock >> 40));
			str += call ? 'C' : 'P';
			unsigned int strikePrice = (unsigned int)optionBlock;
			unsigned int dollars = strikePrice / 1000;
			unsigned int fraction = strikePrice - 1000 * dollars;
			if(fraction)
			{
				U_PriceToStr(str, Price(dollars, fraction * (Price::divider / 1000)), 2, -1, false, '\0', true);
			}
			else
			{
				char num[33];
				str += U_UnsignedNumberToStrNoDecDigits(dollars, num, sizeof(num));
			}
		}
	}
	void OptionBlockToInstrumentString(std::string& str) const
	{
		ConvertOptionBlockToInstrumentString(str, m_optionBlock);
	}
	void toInstrumentString(std::string& str) const
	{
		str += (const char*)&m_rootSymbolNum;
		if(m_optionBlock)
		{
			str += ' ';
			OptionBlockToInstrumentString(str);
		}
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
		const unsigned char& expirationYear,
		const unsigned short& optionType):
		OptionSymbolKey(underlierSymbolNum, strikePrice, call, suffix, expirationDay, expirationMonth, expirationYear),
		m_rootSymbolNum(CalculateRootSymbol(underlierSymbolNum, suffix)),
		m_optionBlock(CalculateOptionBlock()),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_expirationDays(CalculateExpirationDays()),
		m_expirationType(CalculateExpirationType()),
		m_expirationTypeChar(CalculateExpirationTypeAsCharStatic(m_expirationType)),
		m_optionType(optionType),
		m_underlierPosition(NULL)
	{}
	explicit OptionSymbolBlock(const unsigned __int64& underlierSymbolNum,
//		const unsigned int& contractSize,
		const OptionKey& optionKey,
		const unsigned short& optionType):
		OptionSymbolKey(underlierSymbolNum, optionKey),
		m_rootSymbolNum(CalculateRootSymbol(underlierSymbolNum, optionKey.GetSuffix())),
		m_optionBlock(CalculateOptionBlock()),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_expirationDays(CalculateExpirationDays()),
		m_expirationType(CalculateExpirationType()),
		m_expirationTypeChar(CalculateExpirationTypeAsCharStatic(m_expirationType)),
		m_optionType(optionType),
		m_underlierPosition(NULL)
	{}
	explicit OptionSymbolBlock(const unsigned __int64& underlierSymbolNum,
		const unsigned __int64& rootSymbolNum,
		const unsigned __int64& optionBlock,
		const unsigned short& optionType):
		OptionSymbolKey(underlierSymbolNum, rootSymbolNum, optionBlock),
		m_rootSymbolNum(rootSymbolNum),
		m_optionBlock(optionBlock),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_expirationDays(CalculateExpirationDays()),
		m_expirationType(CalculateExpirationType()),
		m_expirationTypeChar(CalculateExpirationTypeAsCharStatic(m_expirationType)),
		m_optionType(optionType),
		m_underlierPosition(NULL)
	{}
//
	explicit OptionSymbolBlock(const unsigned __int64& rootSymbolNum,
		const unsigned char& suffix,
		const unsigned __int64& optionBlock,
		const unsigned short& optionType):
		OptionSymbolKey(rootSymbolNum, suffix, optionBlock),
		m_rootSymbolNum(rootSymbolNum),
		m_optionBlock(optionBlock),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_expirationDays(CalculateExpirationDays()),
		m_expirationType(CalculateExpirationType()),
		m_expirationTypeChar(CalculateExpirationTypeAsCharStatic(m_expirationType)),
		m_optionType(optionType),
		m_underlierPosition(NULL)
	{}
	explicit OptionSymbolBlock(const unsigned __int64& underlierSymbolNum,
//		const unsigned int& contractSize,
		const unsigned __int64& optionBlock,
		const unsigned char& suffix,
		const unsigned short& optionType):
		OptionSymbolKey(underlierSymbolNum, optionBlock, suffix),
		m_rootSymbolNum(CalculateRootSymbol(underlierSymbolNum, suffix)),
		m_optionBlock(optionBlock),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_expirationDays(CalculateExpirationDays()),
		m_expirationType(CalculateExpirationType()),
		m_expirationTypeChar(CalculateExpirationTypeAsCharStatic(m_expirationType)),
		m_optionType(optionType),
		m_underlierPosition(NULL)
	{}
	explicit OptionSymbolBlock(const unsigned __int64& underlierSymbolNum = 0)://, const unsigned int& contractSize = 100):
		OptionSymbolKey(underlierSymbolNum),
		m_rootSymbolNum(underlierSymbolNum),
		m_optionBlock(0),
		m_contractSize(CalculateContractSize()),//contractSize),
		m_expirationDays(0),
		m_expirationType(0),
		m_expirationTypeChar(0),
		m_optionType(0),
		m_underlierPosition(NULL)
	{}
	const unsigned __int64& GetOptionBlock() const{return m_optionBlock;}

	virtual const unsigned char& GetExpirationType() const{return m_expirationType;}
	virtual const char& GetExpirationTypeChar() const{return m_expirationTypeChar;}
	const unsigned int& GetExpirationDays() const{return m_expirationDays;}
	const unsigned int& GetContractSize() const{return m_contractSize;}

	const Position* GetUnderlierPosition() const{return m_underlierPosition;}
	Position* GetUnderlierPosition(){return m_underlierPosition;}
	bool SetUnderlierPosition(Position* underlierPosition)
	{
		if(!m_underlierPosition && underlierPosition)
		{
			m_underlierPosition = underlierPosition;
			return true;
		}
		return false;
	}

	unsigned char SetUnderlierSymbol(const unsigned __int64& underlierSymbolNum)
	{
//		m_underlierSymbolNum = underlierSymbolNum;
//		unsigned char suffix = CalculateSuffix(underlierSymbolNum, m_symbolNum);
		unsigned char suffix = CalculateSuffix(underlierSymbolNum, m_rootSymbolNum);
		unsigned char oldSuffix = m_flags & OPTF_SUFFIX;
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
//			m_contractSize = CalculateContractSize();
			return suffix;
		}
		return 0xFF;
	}

	unsigned int UpdateContractSize()
	{
		const unsigned int contractSize = CalculateContractSize();
		if(contractSize != m_contractSize)
		{
			unsigned int oldContractSize = m_contractSize;
			m_contractSize = contractSize;
			return oldContractSize;
		}
		return 0;
	}

	const unsigned __int64& GetRootSymbolNum() const{return m_rootSymbolNum;}

	const unsigned short& GetOptionType() const{return m_optionType;}
	void SetOptionType(const unsigned short& optionType){m_optionType = optionType;}
protected:
	unsigned __int64 m_rootSymbolNum;
	unsigned __int64 m_optionBlock;
	unsigned int m_contractSize;
	unsigned int m_expirationDays;
	unsigned char m_expirationType;
	char m_expirationTypeChar;
	unsigned short m_optionType;
	Position* m_underlierPosition;
};

class Underlier;

//class TU_API OptionInfo : public OptionKey, public Observable
class TU_API OptionInfo : public OptionSymbolKey, public Observable
{
friend class Security;
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
		const unsigned char& suffix,
		const unsigned short& optionType);

	OptionInfo(const unsigned __int64& optionBlock,
		const unsigned char& suffix,
		const unsigned __int64& optionNumericSymbol,
		const unsigned short& optionType);

	static const unsigned __int64 uint64Zero;

	Underlier* GetUnderlier(){return m_underlier;}
	const Underlier* GetUnderlier() const{return m_underlier;}

	Security* GetSecurity(){return m_security;}
	const Security* GetSecurity() const{return m_security;}

	const unsigned int& GetOpenInterestVolume() const{return m_openInterestVolume;}
	const unsigned int& GetImpliedVolatility() const{return m_impliedVolatility;}
	const int& GetDelta() const{return m_delta;}
	const int& GetVega() const{return m_vega;}
	const int& GetTheta() const{return m_theta;}
/////
	virtual const unsigned char& GetExpirationType() const{return m_expirationType;}
	virtual const char& GetExpirationTypeChar() const{return m_expirationTypeChar;}
	const unsigned int& GetExpirationDays() const{return m_expirationDays;}
	const unsigned int& GetExpirationOrdinal() const{return m_expirationOrdinal;}
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
			m_lockInThreadObservable.LockWait();
			m_inThreadObservable.NotifyObservers(message, info, from);
			m_lockInThreadObservable.Unlock();
		}
	}

	LONG IncrementUnsubscribable() const{return InterlockedIncrement(&m_unsubscribable);}
//	LONG DecrementUnsubscribable(bool unsubscribeImmediately = false){return 1;}
	LONG DecrementUnsubscribable(const bool& unsubscribeImmediately) const{return InterlockedDecrement(&m_unsubscribable);}
	void NullifyUnsubscribable() const{InterlockedExchange(&m_unsubscribable, 0);}

	const unsigned __int64& GetUnderlierNumericSymbol() const{return m_underlierNumericSymbol;}
//	const unsigned __int64& GetOptionNumericSymbol() const{return m_optionNumericSymbol;}
//	bool isOptionSymbolDifferentFromUnderlier() const{return m_optionNumericSymbol != m_underlierNumericSymbol && m_underlierNumericSymbol;}
	bool isOptionSymbolDifferentFromUnderlier() const{return m_symbolNum != m_underlierNumericSymbol && m_underlierNumericSymbol;}
//	const unsigned __int64& GetOptionNumericSymbolIfDifferent() const{return isOptionSymbolDifferentFromUnderlier() ? m_optionNumericSymbol : uint64Zero;}
	const unsigned __int64& GetOptionNumericSymbolIfDifferent() const{return isOptionSymbolDifferentFromUnderlier() ? m_symbolNum : uint64Zero;}
//	const char* GetOptionSymbolIfDifferent() const{return isOptionSymbolDifferentFromUnderlier() ? (const char*)&m_optionNumericSymbol : "";}
	const char* GetOptionSymbolIfDifferent() const{return isOptionSymbolDifferentFromUnderlier() ? (const char*)&m_symbolNum : "";}
	const unsigned __int64& GetUnderlierNumericSymbolIfDifferent() const{return isOptionSymbolDifferentFromUnderlier() ? m_underlierNumericSymbol : uint64Zero;}
	const char* GetUnderlierSymbolIfDifferent() const{return isOptionSymbolDifferentFromUnderlier() ? (const char*)&m_underlierNumericSymbol : "";}
	const unsigned __int64& GetOptionBlock() const{return m_optionBlock;}
//	const unsigned __int64& GetUnderlierNumericSymbol() const;
//	const char* GetUnderlierSymbol() const;
//	const std::string& GetUnderlierSymbolStr() const;
	const unsigned int& GetContractSize() const{return m_contractSize;}
	const unsigned short& GetOptionType() const{return m_optionType;}
	const unsigned char& GetExpirationDayOfWeek() const{return m_expirationDayOfWeek;}
protected:
	void SetOpenInterestVolume(const unsigned int& openInterestVolume){m_openInterestVolume = openInterestVolume;}
	void SetImpliedVolatility(const unsigned int& impliedVolatility){m_impliedVolatility = impliedVolatility;}
	void SetDelta(const int& delta){m_delta = delta;}
	void SetVega(const int& vega){m_vega = vega;}
	void SetTheta(const int& theta){m_theta = theta;}

	void SetSecurity(Security* security);
	void SetUnderlier(Underlier* underlier);
	bool SetUnderlierSymbol(const unsigned __int64& underlierSymbolNum);
	void SetOptionType(const unsigned short& optionType){m_optionType = optionType;}
	void SetExpirationOrdinal(const unsigned int& ordinal){m_expirationOrdinal = ordinal;}

	void UpdateSuffix();
	virtual void OnObserverAdded(Observer* o) const;
	virtual void OnObserverRemoved(Observer* o) const;
	Underlier* m_underlier;
	Security* m_security;
	unsigned __int64 m_underlierNumericSymbol;
//	unsigned __int64 m_optionNumericSymbol;
	unsigned __int64 m_optionBlock;
	unsigned int m_contractSize;
	unsigned int m_expirationOrdinal;
	unsigned int m_expirationDays;
	unsigned int m_openInterestVolume;
	unsigned int m_impliedVolatility;
	int m_delta;
	int m_vega;
	int m_theta;
	unsigned char m_expirationType;
	char m_expirationTypeChar;
	unsigned short m_optionType;

	unsigned char m_expirationDayOfWeek;

	Observable m_inThreadObservable;
	TakionLockSingleThreadAccess m_lockInThreadObservable;
	mutable volatile LONG m_unsubscribable;
};

#endif

//#define SEC_OBS

class TU_API Security : public HTB, public Observable
{
#ifndef TAKION_NO_OPTIONS
friend class OptionInfo;
friend class OptionCallPut;
#endif
public:
	virtual ~Security();

//	static const Price zeroPrice;
//	static const SignedPrice zeroSignedPrice;
	static const std::string stringZero;
	static const unsigned __int64 uint64Zero;
	static const unsigned int uintZero;
	static const unsigned int uintOne;
	static const unsigned int uintMinusOne;//0xFFFFFFFF
	static const unsigned short ushortZero;
	static const short shortZero;
	static const unsigned char ucharZero;
	static const char charZero;
	static const bool boolFalse;
	static const bool boolTrue;
	static const int intZero;
	static const char space;
	static const unsigned char neutralTradeLevel1;//TL1_BETWEEN_BIDASK

	virtual bool CreateIsoSnapshot(std::string& isoSnapshot, bool buy, const Price& limitPrice, bool lock, bool stopIfOrderIsNotInside, bool& isInside, Price& topPrice) const{return false;}

	unsigned char GetPrintFlags(char saleCondition1, char saleCondition2, char saleCondition3, char saleCondition4, char marketCenter, bool firstMarketOpenPriceSet) const;//4 - last; 8 - volume, 16 - high/low, 1 and 2 - always set

	typedef std::multimap<unsigned int, HistoricalPrint> TimeHistoricalPrintMap;
//	typedef std::map<unsigned __int64, HistoricalPrint> HistoricalPrintMap;
	typedef std::map<unsigned __int64, TimeHistoricalPrintMap::iterator> HistoricalPrintMap;
	virtual const HistoricalPrintMap* GetHistoricalPrintMap() const{return NULL;}
	virtual const TimeHistoricalPrintMap* GetTimeHistoricalPrintMap() const{return NULL;}

	virtual unsigned int GetHistoricalPrintRequestId() const{return 0;}
	virtual bool LoadHistoricalPrints(unsigned int& requestId) const{requestId = 0; return false;}
	virtual void ClearHistoricalPrints(){}

	virtual bool isPreMarket() const{return false;}
	virtual bool isMarketOpen() const{return false;}
	virtual bool isMarketClosedForTheDay() const{return false;}
	virtual unsigned char GetMarketState() const{return MSTATE_MARKET;}

	virtual bool isDoomed() const{return false;}

	const bool& isSubscribable() const{return m_subscribable;}
	bool isSubscribed() const{return m_subscribable && m_loaded;}

//	virtual HANDLE GetThreadHandle() const{return NULL;}
	const unsigned int& GetThreadId() const{return m_threadId;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}

	virtual bool isExcludedFromPosManMessages() const{return false;}
	virtual void SetExcludedFromPosManMessages(bool excluded){}

//	virtual unsigned int GetInvalidateLevel1Ordinal() const{return 0;}
//	virtual unsigned int GetUpdateLevel1Ordinal() const{return 0;}

//	virtual unsigned int GetAttributionMask() const{return 0;}
//	virtual void SetAttributionMask(unsigned int mask){}

	virtual void GetProtectedMarketSnapshot(bool bid, std::string& snapshot) const{}

	virtual bool HasPrints() const{return false;}

	const unsigned short& GetSecurityCode() const{return m_securityCode;}
	virtual const bool& isLoaded() const{return m_loaded;}//true if loading of all chunks is successfully done
	virtual const bool& isReloaded() const{return m_reloaded;}
	virtual const bool& isValid() const{return m_valid;}//true if loading of the first chunk is successfully done
	virtual const bool& isLoadFailed() const{return m_loadFailed;}//true if loading of the first chunk came with flag Failed
	virtual const bool& isLevel2Invalid() const{return boolFalse;}
	virtual const bool& isLevel2Subscribed() const{return boolFalse;}
	virtual SecurityType GetSecurityType() const = 0;

	const char* GetName() const{return m_name.c_str();}
	const std::string& GetNameStr() const{return m_name;}
	const unsigned int& GetRoundLot() const{return m_roundLot;}
	const bool& isRoundLotsOnly() const{return m_roundLotsOnly;}

	const bool& isOption() const
	{
		return
#ifndef TAKION_NO_OPTIONS
			m_optionInfo ? boolTrue:
#endif
			boolFalse;
	}
	bool isMarketDataStockNotOption() const
	{
		return
#ifndef TAKION_NO_OPTIONS
			!m_optionInfo &&
#endif
			isMarketDataStock();
	}
	virtual bool isMarketDataStock() const{return true;}
	char GetDataSource() const
	{
		return
#ifndef TAKION_NO_OPTIONS
			m_optionInfo ? 'O' :
#endif
			isMarketDataStock() ? 'D' : 'S';
	}
	virtual const unsigned int& GetTierSize() const{return m_roundLot;}
	virtual const unsigned int& GetTemporaryTierSize() const{return uintMinusOne;}//This value is set only in the main thread; 0xFFFFFFFF is for empty value
	
	const unsigned int& GetCustomPriceBaseCompact() const{return m_customPriceBaseCompact;}
	const unsigned int& GetCustomDate() const{return m_customDate;}//Format: (yearLast2Digits << 16) | (month << 8) | day
	const unsigned int& GetCustomDateDiff() const{return m_customDateDiff;}

	virtual const LineBufferArray* GetUnappliedMessages() const{return NULL;}

//Level2 should be locked before you use the TakionIterator* returned by the 10 function below
	virtual TakionIterator* GetBidIterator(){return NULL;}
	virtual TakionIterator* GetAskIterator(){return NULL;}
//	virtual TakionIterator* GetBidAllQuotesIterator(){return NULL;}
//	virtual TakionIterator* GetAskAllQuotesIterator(){return NULL;}
	virtual TakionIterator* GetBidIteratorWithoutNyseAmexBook(){return NULL;}
	virtual TakionIterator* GetAskIteratorWithoutNyseAmexBook(){return NULL;}
	virtual TakionIterator* GetBidOddIterator(){return NULL;}
	virtual TakionIterator* GetAskOddIterator(){return NULL;}
	virtual TakionIterator* GetEcnBidIterator(){return NULL;}
	virtual TakionIterator* GetEcnAskIterator(){return NULL;}
	virtual TakionIterator* GetEcnBidOddIterator(){return NULL;}
	virtual TakionIterator* GetEcnAskOddIterator(){return NULL;}
//
	const char& GetMarketCategory() const{return m_marketCategory;}
	const unsigned int& GetMarketCategoryFilter() const{return m_marketCategoryFilter;}
	const char& GetFinancialStatus() const{return m_financialStatus;}
	const char& GetPrimaryExchange() const{return m_primaryExchange;}
	const unsigned char& GetPrimaryExchangeEntitlementFlag() const{return m_primaryExchangeEntitlementFlag;}
	const unsigned char& GetPrimaryExchangeEnum() const{return m_primaryExchangeEnum;}

	bool isCloseAuction(const bool& buy) const//true if Primary Exchange imbalance is negative for buy and positive for sell; false otherwise
	{
		const Imbalance* imb = GetExchImbalance();
		if(imb && imb->GetAuctionTime() > 43200000)//noon
		{
			const int imbalanceShares = imb->GetImbalanceShares();
			return imbalanceShares && (buy == (imbalanceShares < 0));
		}
		return false;
	}
	unsigned char GetCloseAuctionFilter(const bool& buy) const//1 if Primary Exchange imbalance is negative for buy and positive for sell; 2 otherwise
	{
		return isCloseAuction(buy) ? 1 : 2;
	}

	static const bool& isNasdaq(const char& primaryExchange)
	{
		switch(primaryExchange)
		{
			case PE_NSDQ:
			case PE_OTCB:
			return boolTrue;

			default:
			return boolFalse;
		}
//		return PE_NSDQ == m_primaryExchange;
	}

	static const bool& isNasdaqByPeEnum(const unsigned char& primaryExchangeEnum)
	{
		switch(primaryExchangeEnum)
		{
			case PEE_NSDQ:
			case PEE_OTCB:
			return boolTrue;

			default:
			return boolFalse;
		}
	}

	const bool& isNasdaq() const{return isNasdaq(m_primaryExchange);}

	const char* GetPrimaryExchangeName() const;
	const unsigned int& GetPrimaryExchangeNumericName() const{return m_primaryExchangeNumericName;}
	const unsigned int& GetQuoteConditionFilterAll() const{return m_quoteConditionFilterAll;}

	virtual unsigned int GetTradingStateFilter() const{return uintZero;}
	virtual char GetTradingState() const{return charZero;}
	virtual bool isHalted() const{return boolFalse;}

	const unsigned __int64& GetYesterdaysVolume() const{return m_yesterdaysVolume;}

	const unsigned __int64& GetAverageDailyVolume() const{return m_averageDailyVolume;}
	const Price& GetYesterdaysHighPrice() const{return m_yesterdaysHighPrice;}
	const Price& GetYesterdaysLowPrice() const{return m_yesterdaysLowPrice;}
	const Price& GetYesterdaysPriceRange() const{return m_yesterdaysPriceRange;}
	const Price& GetYesterdaysPriceRangePercent() const{return m_yesterdaysPriceRangePercent;}

	virtual const char& GetShortSaleThresholdIndicator() const{return charZero;}//'Y', 'N'

	virtual const unsigned int& GetCircuitBreakerFilter() const{return uintZero;}
	virtual const char& GetRegSHOTestIndicator() const{return charZero;}//'0', '1', '2'//CircuitBreaker
	virtual const bool& isCircuitBreaker() const{return boolFalse;}

	const unsigned short& GetSplitNumerator() const{return m_splitNumerator;}
	const unsigned short& GetSplitDenominator() const{return m_splitDenominator;}
	const unsigned int& GetSplit() const{return m_split;}
	const Price& GetDividend() const{return m_dividend;}

////////////
	virtual const unsigned int& GetQuoteConditionFilter() const{return uintZero;}
	virtual const unsigned int& GetQuoteConditionTime() const{return uintZero;}
	virtual const unsigned int& GetTradingActionReason() const{return uintZero;}
	virtual const unsigned int& GetTradingStateTime() const{return uintZero;}

	virtual const unsigned __int64& GetVolume() const{return uint64Zero;}
	virtual const unsigned __int64& GetPrimaryExchangeVolume() const{return uint64Zero;}
	virtual const unsigned __int64& GetPrimaryExchangeMhVolume() const{return uint64Zero;}

	virtual const unsigned int& GetCircuitBreakerTime() const{return uintZero;}

#ifdef LRPS
	virtual const Price& GetLrpLow() const{return Price::priceZero;}
	virtual const Price& GetLrpHigh() const{return Price::priceZero;}
	const Price& GetLrp(const bool& bid) const{return bid ? GetLrpLow() : GetLrpHigh();}
	virtual const unsigned int& GetLrpLowTime() const{return uintZero;}
	virtual const unsigned int& GetLrpHighTime() const{return uintZero;}
	const unsigned int& GetLrpTime(const bool& bid) const{return bid ? GetLrpLowTime() : GetLrpHighTime();}
	virtual const short& GetLrpLowDelay() const{return shortZero;}
	virtual const short& GetLrpHighDelay() const{return shortZero;}
	const short& GetLrpDelay(const bool& bid) const{return bid ? GetLrpLowDelay() : GetLrpHighDelay();}
	virtual const bool& isLrpLowHistorical() const{return boolFalse;}
	virtual const bool& isLrpHighHistorical() const{return boolFalse;}
	const bool& isLrpHistorical(const bool& bid) const{return bid ? isLrpLowHistorical() : isLrpHighHistorical();}
#endif
	virtual const Price& GetLuldLow() const{return Price::priceZero;}
	virtual const Price& GetLuldHigh() const{return Price::priceZero;}
	const Price& GetLuld(const bool& bid) const{return bid ? GetLuldLow() : GetLuldHigh();}

	virtual const unsigned int& GetLuldLowCompact() const{return uintZero;}
	virtual const unsigned int& GetLuldHighCompact() const{return uintZero;}
	const unsigned int& GetLuldCompact(const bool& bid) const{return bid ? GetLuldLowCompact() : GetLuldHighCompact();}

	virtual const unsigned int& GetLuldLowTime() const{return uintZero;}
	virtual const unsigned int& GetLuldHighTime() const{return uintZero;}
	const unsigned int& GetLuldTime(const bool& bid) const{return bid ? GetLuldLowTime() : GetLuldHighTime();}

	virtual const short& GetLuldLowDelay() const{return shortZero;}
	virtual const short& GetLuldHighDelay() const{return shortZero;}
	const short& GetLuldDelay(const bool& bid) const{return bid ? GetLuldLowDelay() : GetLuldHighDelay();}

	virtual const bool& isLuldLowHistorical() const{return boolFalse;}
	virtual const bool& isLuldHighHistorical() const{return boolFalse;}
	const bool& isLuldHistorical(const bool& bid) const{return bid ? isLuldLowHistorical() : isLuldHighHistorical();}

	virtual const bool& isOpenSaleCondition() const{return boolFalse;}
	virtual const bool& isPrimaryOpenSaleCondition() const{return boolFalse;}
	virtual const bool& isPrimarySourceOpenPrint() const{return boolFalse;}

	virtual const char& GetRpiIndicator() const{return charZero;}
	virtual const unsigned int& GetTradeDisseminationTime() const{return uintZero;}

	virtual const unsigned int& GetL2Bid() const{return uintZero;}
	virtual const unsigned int& GetL2Ask() const{return uintZero;}
	virtual const unsigned int& GetL2BidSize() const{return uintZero;}
	virtual const unsigned int& GetL2AskSize() const{return uintZero;}
	
	virtual const unsigned int& GetEcnBid() const{return uintZero;}
	virtual const unsigned int& GetEcnAsk() const{return uintZero;}
	virtual const unsigned int& GetEcnBidSize() const{return uintZero;}
	virtual const unsigned int& GetEcnAskSize() const{return uintZero;}

	virtual const unsigned int& GetL1Bid() const{return uintZero;}
	virtual const unsigned int& GetL1Ask() const{return uintZero;}

	virtual const unsigned int& GetLastNbboPrintPrice() const{return uintZero;}
	virtual const unsigned int& GetLastNbboPrintOrClosePrice() const{return m_closePriceCompact;}//uintZero

	virtual const unsigned int& GetMidPoint() const{return uintZero;}//(Bid + Ask) / 2;
	virtual const unsigned int& GetMidPointOrLastOrClosePrice() const{return GetLastNbboPrintOrClosePrice();}

	virtual const unsigned int& GetLastPrice() const{return uintZero;}
	virtual const unsigned int& GetLastPriceIncludingOddLot() const{return uintZero;}

	virtual const int& GetLastPriceDiff() const{return intZero;}
	virtual const int& GetLastPriceDiffIncludingOddLot() const{return intZero;}

	virtual const Price& GetTodaysClosePrice() const{return Price::priceZero;}

	virtual const unsigned int& GetNysBid() const{return uintZero;}
	virtual const unsigned int& GetNysAsk() const{return uintZero;}
	virtual const unsigned int& GetNysBidSize() const{return uintZero;}
	virtual const unsigned int& GetNysAskSize() const{return uintZero;}
	virtual const unsigned int& GetNysLastPrice() const{return uintZero;}
	virtual const unsigned int& GetNysLastTradeSize() const{return uintZero;}
	virtual const unsigned int& GetNysHighPrice() const{return uintZero;}
	virtual const unsigned int& GetNysLowPrice() const{return uintZero;}

	virtual const unsigned int& GetAmxBid() const{return uintZero;}
	virtual const unsigned int& GetAmxAsk() const{return uintZero;}
	virtual const unsigned int& GetAmxBidSize() const{return uintZero;}
	virtual const unsigned int& GetAmxAskSize() const{return uintZero;}
	virtual const unsigned int& GetAmxLastPrice() const{return uintZero;}
	virtual const unsigned int& GetAmxLastTradeSize() const{return uintZero;}

	virtual const unsigned int& GetBidAt730() const{return uintZero;}
	virtual const unsigned int& GetAskAt730() const{return uintZero;}
	virtual bool isBidAsk730Uninitialized() const{return boolTrue;}

	virtual const unsigned int& GetBidAt830() const{return uintZero;}
	virtual const unsigned int& GetAskAt830() const{return uintZero;}
	virtual bool isBidAsk830Uninitialized() const{return boolTrue;}

	virtual const SignedPrice& GetBidNetPercent730() const{return SignedPrice::signedPriceZero;}
	virtual const SignedPrice& GetAskNetPercent730() const{return SignedPrice::signedPriceZero;}
	virtual const SignedPrice& GetBidNetPercent830() const{return SignedPrice::signedPriceZero;}
	virtual const SignedPrice& GetAskNetPercent830() const{return SignedPrice::signedPriceZero;}

	virtual const unsigned int& GetNsdqLastPrice() const{return uintZero;}
	virtual const unsigned int& GetNsdqLastTradeSize() const{return uintZero;}

	virtual const unsigned int& GetTodaysClosePriceCompact() const{return uintZero;}
	virtual const unsigned int& GetOpenPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetQOpenPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetPrimaryQOpenPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetPrimaryQOpenTime() const{return uintZero;}
	virtual const unsigned int& GetPrimarySourceOpenPriceCompact() const{return uintZero;}

	virtual const unsigned int& GetLastOrClosePrice() const{return m_closePriceCompact;}
//	virtual const unsigned int& GetLastOrClosePrice() const{return uintZero;}
	virtual const unsigned int& GetTCloseLastOrClosePrice(bool includePreMarket, bool includeAfterMarket) const{return uintZero;}

	virtual const unsigned int& GetNbboPrintPriceAfter945() const{return uintZero;}
	virtual const unsigned int& GetNbboPrintPriceAfter1000() const{return uintZero;}
	virtual const unsigned int& GetNbboPrintPriceAfter1400() const{return uintZero;}

	virtual const unsigned int& GetPriceCompactAfter845() const{return uintZero;}
	virtual const unsigned int& GetPriceCompactAfter900() const{return uintZero;}
	virtual const unsigned int& GetPriceCompactAfter915() const{return uintZero;}
	virtual const unsigned int& GetPriceCompactAfter920() const{return uintZero;}
	virtual const unsigned int& GetPriceCompactAfter925() const{return uintZero;}
	virtual const unsigned int& GetPriceCompactAfter926() const{return uintZero;}
	virtual const unsigned int& GetPriceCompactAfter928() const{return uintZero;}

	virtual bool isPriceNbbo(const Price& price) const{return boolFalse;}
	virtual const Price& GetPmiBid() const{return Price::priceZero;}
	virtual const Price& GetPmiAsk() const{return Price::priceZero;}
	virtual const Price& GetOpenPrice() const{return Price::priceZero;}
	virtual const Price& GetPrimaryQOpenPrice() const{return Price::priceZero;}
#ifdef EXCH_OPEN_PRICE
	virtual const Price& GetNsdqOpenPrice() const{return Price::priceZero;}
	virtual const Price& GetArcaOpenPrice() const{return Price::priceZero;}
	virtual const unsigned int& GetNsdqOpenPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetArcaOpenPriceCompact() const{return uintZero;}
#endif
	virtual const Price& GetQOpenPrice() const{return Price::priceZero;}
	virtual const Price& GetPrimarySourceOpenPrice() const{return Price::priceZero;}
	virtual const SignedPrice& GetNetChange() const{return SignedPrice::signedPriceZero;}

	virtual const SignedPrice& GetNiteChange() const{return SignedPrice::signedPriceZero;}
	virtual const SignedPrice& GetNiteChangePercent() const{return SignedPrice::signedPriceZero;}

	virtual const SignedPrice& GetPQNiteChange() const{return SignedPrice::signedPriceZero;}
	virtual const SignedPrice& GetPQNiteChangePercent() const{return SignedPrice::signedPriceZero;}

	virtual const SignedPrice& GetTCloseNet() const{return SignedPrice::signedPriceZero;}//TodaysClosPrice - YesterdaysClosePrice
	virtual const SignedPrice& GetTCloseNetPercent() const{return SignedPrice::signedPriceZero;}//TodaysClosPrice - YesterdaysClosePrice
	virtual const SignedPrice& GetOpenChange() const{return SignedPrice::signedPriceZero;}
	virtual const SignedPrice& GetQOpenChange() const{return SignedPrice::signedPriceZero;}
	virtual const SignedPrice& GetPrimarySourceOpenChange() const{return SignedPrice::signedPriceZero;}
	virtual const SignedPrice& GetTodaysCloseChange() const{return SignedPrice::signedPriceZero;}//LastPrice - TodaysClosPrice
	virtual const SignedPrice& GetOpenChangePercent945() const{return SignedPrice::signedPriceZero;}
	virtual const SignedPrice& GetOpenChangePercent1000() const{return SignedPrice::signedPriceZero;}
	virtual const Price& GetHighPrice() const{return Price::priceZero;}
	virtual const Price& GetLowPrice() const{return Price::priceZero;}
	virtual const Price& GetPriceRange() const{return Price::priceZero;}
	virtual const Price& GetExtendedPriceRange() const{return Price::priceZero;}

	virtual const SignedPrice& GetLastPriceInRangePercent() const{return SignedPrice::signedPriceZero;}
	virtual const Price& GetPriceRangeAsClosePercent() const{return Price::priceZero;}

	virtual const unsigned int& GetFirstQualifyingPrintSourceMask() const{return uintZero;}

	virtual const unsigned int& GetLevel1BidSize() const{return uintZero;}
	virtual const unsigned int& GetLevel1AskSize() const{return uintZero;}

	virtual const unsigned int& GetLastTradeSize() const{return uintZero;}
	virtual const unsigned int& GetLastTradeSizeIncludingOddLot() const{return uintZero;}
	virtual const unsigned int& GetLastTradeMillisecond() const{return uintZero;}
	virtual const unsigned int& GetLevel1BidMillisecond() const{return uintZero;}
	virtual const unsigned int& GetLevel1AskMillisecond() const{return uintZero;}
	virtual const unsigned int& GetPmiMillisecond() const{return uintZero;}
	virtual const short& GetLevel1Delay() const{return shortZero;}
	virtual const short& GetPrintDelay() const{return shortZero;}//not implemented, not used
	virtual const unsigned char& GetLastTradeLevel1() const{return neutralTradeLevel1;}//TradeLevel1
	virtual const char& GetBidMarketCenter() const{return charZero;}
	virtual const char& GetAskMarketCenter() const{return charZero;}
	virtual const char& GetQuoteCondition() const{return charZero;}
	virtual const bool& GetRetailLiquidity() const{return boolFalse;}
	virtual const char& GetLastMarketCenter() const{return charZero;}
	virtual const unsigned int& GetQuoteSeqNumber() const{return uintZero;}
	virtual const unsigned int& GetTradeSeqNumber() const{return uintZero;}
	virtual const unsigned char& GetTick() const{return ucharZero;}

	virtual const Price& GetFirstPrice() const{return Price::priceZero;}
	virtual const Price& GetFirstMarketOpenPrice() const{return Price::priceZero;}
	virtual const Price& GetLastMarketOpenPrice() const{return Price::priceZero;}
	virtual const Price& GetPeLastMarketOpenPrice() const{return Price::priceZero;}
	virtual const unsigned __int64& GetMarketHoursVolume() const{return uint64Zero;}

	virtual const unsigned __int64& GetPreMarketVolume() const{return uint64Zero;}
	virtual const unsigned __int64& GetPostMarketVolume() const{return uint64Zero;}

	virtual const unsigned __int64& GetPreMarketVolumeNoFINR() const{return uint64Zero;}//excluding FINR Prints
	virtual const unsigned __int64& GetPostMarketVolumeNoFINR() const{return uint64Zero;}//excluding FINR Prints

	virtual const Money& GetPreMarketVolumeByADV() const{return Money::moneyZero;}
	virtual const Money& GetMoneyTraded() const{return Money::moneyZero;}
	virtual const Money& GetMarketHoursMoneyTraded() const{return Money::moneyZero;}
	virtual const Money& GetPreMarketMoneyTraded() const{return Money::moneyZero;}
	virtual const Money& GetPostMarketMoneyTraded() const{return Money::moneyZero;}

//Only works in Market Sorter
	virtual const Price& GetExtendedHighPrice() const{return Price::priceZero;}
	virtual const Price& GetExtendedLowPrice() const{return Price::priceZero;}
	virtual const Price& GetMarketHoursHighPrice() const{return Price::priceZero;}
	virtual const Price& GetMarketHoursLowPrice() const{return Price::priceZero;}
	virtual const unsigned short& GetExtendedHighMinute() const{return ushortZero;}
	virtual const unsigned short& GetExtendedLowMinute() const{return ushortZero;}
	virtual const unsigned short& GetMarketHoursHighMinute() const{return ushortZero;}
	virtual const unsigned short& GetMarketHoursLowMinute() const{return ushortZero;}

	virtual const Price& GetPostMarketHoursHighPrice() const{return Price::priceZero;}
	virtual const Price& GetPostMarketHoursLowPrice() const{return Price::priceZero;}

	virtual const Price& GetPreMarketHoursHighPrice() const{return Price::priceZero;}
	virtual const Price& GetPreMarketHoursLowPrice() const{return Price::priceZero;}

	virtual const unsigned int& GetExtendedHighPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetExtendedLowPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetMarketHoursHighPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetMarketHoursLowPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetPostMarketHoursHighPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetPostMarketHoursLowPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetPreMarketHoursHighPriceCompact() const{return uintZero;}
	virtual const unsigned int& GetPreMarketHoursLowPriceCompact() const{return uintZero;}
//
	virtual unsigned char GetTradeLevel1FromCompactPrice(unsigned int price) const{return TL1_BETWEEN_BIDASK;}

	virtual const unsigned int& GetLatestClosePriceCompact() const{return m_closePriceCompact;}
	virtual const Price& GetLatestClosePrice() const{return m_closePrice;}
	////////////////
	const unsigned int& GetClosePriceCompact() const{return m_closePriceCompact;}
//	const bool& isOpen() const{return m_entitledPrint ? m_open : boolFalse;}
	virtual const bool& isOpen() const{return boolFalse;}
	const Price& GetClosePrice() const{return m_closePrice;}
//	const unsigned int& GetPrimaryOpenPriceCompact() const{return m_primaryOpenPriceCompact;}

	const unsigned int& GetL2Quote(const bool& bid) const{return bid ? GetL2Bid() : GetL2Ask();}
	const unsigned int& GetL2QuoteSize(const bool& bid) const{return bid ? GetL2BidSize() : GetL2AskSize();}
	const unsigned int& GetEcnQuote(const bool& bid) const{return bid ? GetEcnBid() : GetEcnAsk();}
	const unsigned int& GetEcnQuoteSize(const bool& bid) const{return bid ? GetEcnBidSize() : GetEcnAskSize();}
	const unsigned int& GetL1Quote(const bool& bid) const{return bid ? GetL1Bid() : GetL1Ask();}

	const unsigned int& GetNysQuote(const bool& bid) const{return bid ? GetNysBid() : GetNysAsk();}
	const unsigned int& GetNysQuoteSize(const bool& bid) const{return bid ? GetNysBidSize() : GetNysAskSize();}
	const unsigned int& GetAmxQuote(const bool& bid) const{return bid ? GetAmxBid() : GetAmxAsk();}
	const unsigned int& GetAmxQuoteSize(const bool& bid) const{return bid ? GetAmxBidSize() : GetAmxAskSize();}

	const unsigned int& GetAmxOrNysBid() const{return m_primaryExchange == PE_AMEX ? GetAmxBid() : GetNysBid();}
	const unsigned int& GetAmxOrNysAsk() const{return m_primaryExchange == PE_AMEX ? GetAmxAsk() : GetNysAsk();}
	const unsigned int& GetAmxOrNysBidSize() const{return m_primaryExchange == PE_AMEX ? GetAmxBidSize() : GetNysBidSize();}
	const unsigned int& GetAmxOrNysAskSize() const{return m_primaryExchange == PE_AMEX ? GetAmxAskSize() : GetNysAskSize();}
	const unsigned int& GetAmxOrNysLastPrice() const{return m_primaryExchange == PE_AMEX ? GetAmxLastPrice() : GetNysLastPrice();}
	const unsigned int& GetAmxOrNysLastTradeSize() const{return m_primaryExchange == PE_AMEX ? GetAmxLastTradeSize() : GetNysLastTradeSize();}

	const unsigned int& GetAmxOrNysQuote(const bool& bid) const{return bid ? GetAmxOrNysBid() : GetAmxOrNysAsk();}
	const unsigned int& GetAmxOrNysQuoteSize(const bool& bid) const{return bid ? GetAmxOrNysBidSize() : GetAmxOrNysAskSize();}

	const unsigned int& GetQuoteAt730(const bool& bid) const{return bid ? GetBidAt730() : GetAskAt730();}
	const unsigned int& GetQuoteAt830(const bool& bid) const{return bid ? GetBidAt830() : GetAskAt830();}
	const SignedPrice& GetQuoteNetPercent730(const bool& bid) const{return bid ? GetBidNetPercent730() : GetAskNetPercent730();}

	const Price& GetPmiQuote(const bool& bid) const{return bid ? GetPmiBid() : GetPmiAsk();}
	const SignedPrice& GetQuoteNetPercent830(const bool& bid) const{return bid ? GetBidNetPercent830() : GetAskNetPercent830();}
	const unsigned int& GetLevel1QuoteSize(const bool& bid) const{return bid ? GetLevel1BidSize() : GetLevel1AskSize();}
	const char& GetQuoteMarketCenter(const bool& bid) const{return bid ? GetBidMarketCenter() : GetAskMarketCenter();}
///////////////
	unsigned char GetTradeLevel1(const Price& price) const{return GetTradeLevel1FromCompactPrice(price.GetCompactPrice());}

//	virtual unsigned int RequestHistoricalChart(const char* symbol, unsigned int dateFrom, char frequency){return false;}

	virtual unsigned short GetLastNewMinuteFromMsServer() const{return 0;}

	virtual Book* GetBook(unsigned char bookId){return NULL;}
	virtual const Book* GetBook(unsigned char bookId) const{return NULL;}

	virtual Book* GetPrimaryBook(){return NULL;}
	virtual const Book* GetPrimaryBook() const{return NULL;}

	virtual Book* GetPrimaryAttributedBook(){return NULL;}
	virtual const Book* GetPrimaryAttributedBook() const{return NULL;}

	virtual const Imbalance* GetNasdaqImbalance() const{return NULL;}
	virtual const Imbalance* GetArcaImbalance() const{return NULL;}
	virtual const Imbalance* GetNyseImbalance() const{return NULL;}

	unsigned char GetPrimaryBookId() const
	{
		switch(m_primaryExchange)
		{
			case PE_AMEX:
			return ECNBOOK_AMEX;

			case PE_NYSE:
			return ECNBOOK_NYS;

			case PE_ARCA:
			return ECNBOOK_ARCA;

			case PE_NSDQ:
			return ECNBOOK_NSDQ;

			case PE_BATS:
			return ECNBOOK_BATS;

			case PE_IEX:
			return ECNBOOK_IEX;

//		case PE_OTCB://AddOTCB
			default:
			return ECNBOOK_COUNT;
		}
	}
	unsigned char GetPrimaryAttributedBookId() const
	{
		switch(m_primaryExchange)
		{
			case PE_ARCA:
			return BOOK_MM_ARCA;

			case PE_NSDQ:
			return BOOK_MM_NSDQ;

			case PE_BATS:
			return BOOK_MM_BATS;

			default:
			return ECNBOOK_COUNT;
		}
	}

	const Imbalance* GetExchImbalance() const
	{
		switch(m_primaryExchange)
		{
			case PE_NSDQ:
			return GetNasdaqImbalance();

			case PE_ARCA:
			return GetArcaImbalance();

			default://PE_AMEX;PE_NYSEPE_BATS
			return GetNyseImbalance();
		}
	}

//	const SignedPrice& GetImbalanceRatioNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetImbalanceRatio() : SignedPrice::signedPriceZero;}
	const int& GetImbalanceChangeNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetImbalanceChange() : intZero;}
	const Price& GetFarPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetFarPrice() : Price::priceZero;}
	const Price& Get1stFarPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->Get1stFarPrice() : Price::priceZero;}
	const Price& Get2ndFarPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->Get2ndFarPrice() : Price::priceZero;}
	const SignedPrice& GetFarPriceDiffNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetFarPriceDiff() : SignedPrice::signedPriceZero;}
	const SignedPrice& GetInitRefFarPriceDiffNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetInitRefFarPriceDiff() : SignedPrice::signedPriceZero;}
	const Price& GetNearPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetNearPrice() : Price::priceZero;}
	const unsigned int& GetNearPriceCompactNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetNearPriceCompact() : uintZero;}
	const Price& GetCurrentReferencePriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetCurrentReferencePrice() : Price::priceZero;}
	const int& GetImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetImbalanceShares() : intZero;}
	const int& GetPrevImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPrevImbalanceShares() : intZero;}
	const int& GetMarketImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetMarketImbalanceShares() : intZero;}
	const unsigned int& GetPairedSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPairedShares() : uintZero;}
	const unsigned int& GetImbalanceTimeNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetImbalanceTime() : uintZero;}
	const unsigned int& GetPrevImbalanceTimeNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPrevImbalanceTime() : uintZero;}
	const short& GetImbalanceDelayNsdq() const {const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetDelay() : shortZero;}
	const unsigned int& GetAuctionTimeNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetAuctionTime() : uintZero;}
	const char& GetCrossTypeNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetCrossType() : space;}
	const char& GetPriceVariationIndicatorNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPriceVariationIndicator() : space;}
//	const bool& isFrozenNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->isFrozen() : boolFalse;}
	const int& GetRegulatoryImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetRegulatoryImbalanceShares() : intZero;}
	const int& GetPrevRegulatoryImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetPrevRegulatoryImbalanceShares() : intZero;}
	const int& GetInitialImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetInitialImbalanceShares() : intZero;}
	const unsigned int& GetOpeningPairedSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetOpeningPairedShares() : uintZero;}
	const int& GetOpeningImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetOpeningImbalanceShares() : intZero;}
	const Price& GetOpeningCurrentReferencePriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetOpeningCurrentReferencePrice() : Price::priceZero;}
	const int& GetT926ImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT926ImbalanceShares() : intZero;}//Imbalance at 9:26
	const int& GetT830ImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT830ImbalanceShares() : intZero;}//Imbalance at 8:30

	const Price& GetInitialCurrentReferencePriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetInitialCurrentReferencePrice() : Price::priceZero;}
	const int& GetT1555ImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT1555ImbalanceShares() : intZero;}//Imbalance at 15:55
	const int& GetT1558ImbalanceSharesNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT1558ImbalanceShares() : intZero;}//Imbalance at 15:58

	const Price& GetT1555CurrentReferencePriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT1555CurrentReferencePrice() : Price::priceZero;}
	const Price& GetT1555FarPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT1555FarPrice() : Price::priceZero;}
	const Price& GetT1555NearPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT1555NearPrice() : Price::priceZero;}

	const Price& GetT1558CurrentReferencePriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT1558CurrentReferencePrice() : Price::priceZero;}
	const Price& GetT1558FarPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT1558FarPrice() : Price::priceZero;}
	const Price& GetT1558NearPriceNsdq() const{const Imbalance* imb = GetNasdaqImbalance(); return imb ? imb->GetT1558NearPrice() : Price::priceZero;}

//	const SignedPrice& GetImbalanceRatioArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetImbalanceRatio() : SignedPrice::signedPriceZero;}
	const int& GetImbalanceChangeArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetImbalanceChange() : intZero;}
	const Price& GetFarPriceArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetFarPrice() : Price::priceZero;}
	const Price& GetNearPriceArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetNearPrice() : Price::priceZero;}
	const unsigned int& GetNearPriceCompactArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetNearPriceCompact() : uintZero;}
	const Price& GetCurrentReferencePriceArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetCurrentReferencePrice() : Price::priceZero;}
	const int& GetImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetImbalanceShares() : intZero;}
	const int& GetPrevImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPrevImbalanceShares() : intZero;}
	const int& GetMarketImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetMarketImbalanceShares() : intZero;}
	const unsigned int& GetPairedSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPairedShares() : uintZero;}
	const unsigned int& GetImbalanceTimeArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetImbalanceTime() : uintZero;}
	const unsigned int& GetPrevImbalanceTimeArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPrevImbalanceTime() : uintZero;}
	const short& GetImbalanceDelayArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetDelay() : shortZero;}
	const unsigned int& GetAuctionTimeArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetAuctionTime() : uintZero;}
	const char& GetCrossTypeArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetCrossType() : space;}
	const char& GetPriceVariationIndicatorArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPriceVariationIndicator() : space;}
//	const bool& isFrozenArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->isFrozen() : boolFalse;}
	const int& GetRegulatoryImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetRegulatoryImbalanceShares() : intZero;}
	const int& GetPrevRegulatoryImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetPrevRegulatoryImbalanceShares() : intZero;}
	const int& GetInitialImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetInitialImbalanceShares() : intZero;}
	const unsigned int& GetOpeningPairedSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetOpeningPairedShares() : uintZero;}
	const int& GetOpeningImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetOpeningImbalanceShares() : intZero;}
	const Price& GetOpeningCurrentReferencePriceArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetOpeningCurrentReferencePrice() : Price::priceZero;}
	const int& GetT926ImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetT926ImbalanceShares() : intZero;}//Imbalance at 9:26
	const int& GetT830ImbalanceSharesArca() const{const Imbalance* imb = GetArcaImbalance(); return imb ? imb->GetT830ImbalanceShares() : intZero;}//Imbalance at 8:30

//	const SignedPrice& GetImbalanceRatioNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetImbalanceRatio() : SignedPrice::signedPriceZero;}
	const int& GetImbalanceChangeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetImbalanceChange() : intZero;}
	const Price& GetFarPriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetFarPrice() : Price::priceZero;}
	const Price& GetNearPriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetNearPrice() : Price::priceZero;}
	const unsigned int& GetNearPriceCompactNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetNearPriceCompact() : uintZero;}
	const Price& GetCurrentReferencePriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetCurrentReferencePrice() : Price::priceZero;}
	const int& GetImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetImbalanceShares() : intZero;}
	const int& GetPrevImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPrevImbalanceShares() : intZero;}
	const int& GetRegulatoryImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryImbalanceShares() : intZero;}
	const int& GetPrevRegulatoryImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPrevRegulatoryImbalanceShares() : intZero;}
	const int& GetInitialImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetInitialImbalanceShares() : intZero;}
	const unsigned int& GetOpeningPairedSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetOpeningPairedShares() : uintZero;}
	const int& GetOpeningImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetOpeningImbalanceShares() : intZero;}
	const Price& GetOpeningCurrentReferencePriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetOpeningCurrentReferencePrice() : Price::priceZero;}
	const int& GetMarketImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetMarketImbalanceShares() : intZero;}
	const unsigned int& GetPairedSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPairedShares() : uintZero;}
	const unsigned int& GetImbalanceTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetImbalanceTime() : uintZero;}
	const unsigned int& GetPrevImbalanceTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPrevImbalanceTime() : uintZero;}
	const short& GetImbalanceDelayNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetDelay() : shortZero;}
	const unsigned int& GetRegulatoryImbalanceTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryImbalanceTime() : uintZero;}
	const unsigned int& GetPrevRegulatoryImbalanceTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPrevRegulatoryImbalanceTime() : uintZero;}
	const unsigned int& GetAuctionTimeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetAuctionTime() : uintZero;}
	const char& GetCrossTypeNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetCrossType() : space;}
	bool isNyseImbalanceClosing() const{const Imbalance* imb = GetNyseImbalance(); return imb && imb->isImbalanceClosing();}
	const int& GetRegulatoryImbalanceSharesNyseIfClosing() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryImbalanceSharesIfClosing() : intZero;}
	const char& GetPriceVariationIndicatorNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetPriceVariationIndicator() : space;}
	const bool& isFrozenNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->isFrozen() : boolFalse;}

	const Price& GetRegulatoryFarPriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryFarPrice() : Price::priceZero;}
	const Price& GetRegulatoryNearPriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryNearPrice() : Price::priceZero;}
	const Price& GetRegulatoryCurrentReferencePriceNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryCurrentReferencePrice() : Price::priceZero;}
	const unsigned int& GetRegulatoryPairedSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetRegulatoryPairedShares() : uintZero;}

	const int& GetT926ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT926ImbalanceShares() : intZero;}//Imbalance at 9:26
	const int& GetT830ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT830ImbalanceShares() : intZero;}//Imbalance at 8:30
	const int& GetT845ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT845ImbalanceShares() : intZero;}//Imbalance at 8:45
	const int& GetT900ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT900ImbalanceShares() : intZero;}//Imbalance at 9:00
	const int& GetT915ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT915ImbalanceShares() : intZero;}//Imbalance at 9:15
	const int& GetT920ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT920ImbalanceShares() : intZero;}//Imbalance at 9:20
	const int& GetT925ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT925ImbalanceShares() : intZero;}//Imbalance at 9:25
	const int& GetT928ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT928ImbalanceShares() : intZero;}//Imbalance at 9:28

	const int& GetT1550ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT1550ImbalanceShares() : intZero;}//Imbalance at 15:50
	const int& GetT1555ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT1555ImbalanceShares() : intZero;}//Imbalance at 15:55
	const int& GetT1556ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT1556ImbalanceShares() : intZero;}//Imbalance at 15:56
	const int& GetT1557ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT1557ImbalanceShares() : intZero;}//Imbalance at 15:57
	const int& GetT1558ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT1558ImbalanceShares() : intZero;}//Imbalance at 15:58
	const int& GetT1559ImbalanceSharesNyse() const{const Imbalance* imb = GetNyseImbalance(); return imb ? imb->GetT1559ImbalanceShares() : intZero;}//Imbalance at 15:59

//	const SignedPrice& GetImbalanceRatioExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetImbalanceRatio() : SignedPrice::signedPriceZero;}
	const int& GetImbalanceChangeExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetImbalanceChange() : intZero;}
	const Price& GetFarPriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetFarPrice() : Price::priceZero;}
	const Price& Get1stFarPriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->Get1stFarPrice() : Price::priceZero;}
	const Price& Get2ndFarPriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->Get2ndFarPrice() : Price::priceZero;}
	const SignedPrice& GetFarPriceDiffExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetFarPriceDiff() : SignedPrice::signedPriceZero;}
	const SignedPrice& GetInitRefFarPriceDiffExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetInitRefFarPriceDiff() : SignedPrice::signedPriceZero;}
	const Price& GetNearPriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetNearPrice() : Price::priceZero;}
	const unsigned int& GetNearPriceCompactExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetNearPriceCompact() : uintZero;}
	const Price& GetCurrentReferencePriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetCurrentReferencePrice() : Price::priceZero;}
	const Price& GetInitialCurrentReferencePriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetInitialCurrentReferencePrice() : Price::priceZero;}
	const bool& isCurrentReferencePriceExchChanged() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->isCurrentReferencePriceChanged() : boolFalse;}
	const int& GetImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetImbalanceShares() : intZero;}
	const int& GetPrevImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetPrevImbalanceShares() : intZero;}
	const int& GetMarketImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetMarketImbalanceShares() : intZero;}
	const unsigned int& GetPairedSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetPairedShares() : uintZero;}
	const unsigned int& GetImbalanceTimeExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetImbalanceTime() : uintZero;}
	const unsigned int& GetPrevImbalanceTimeExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetPrevImbalanceTime() : uintZero;}
	const unsigned int& GetAuctionTimeExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetAuctionTime() : uintZero;}
	const char& GetCrossTypeExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetCrossType() : space;}
	const char& GetPriceVariationIndicatorExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetPriceVariationIndicator() : space;}
//	const bool& isFrozenExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->isFrozen() : boolFalse;}
	const int& GetInitialImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetInitialImbalanceShares() : intZero;}
	const unsigned int& GetOpeningPairedSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetOpeningPairedShares() : uintZero;}
	const int& GetOpeningImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetOpeningImbalanceShares() : intZero;}
	const Price& GetOpeningCurrentReferencePriceExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetOpeningCurrentReferencePrice() : Price::priceZero;}

	const int& GetT830ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT830ImbalanceShares() : intZero;}//Imbalance at 8:30
	const int& GetT845ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT845ImbalanceShares() : intZero;}//Imbalance at 8:45
	const int& GetT900ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT900ImbalanceShares() : intZero;}//Imbalance at 9:00
	const int& GetT915ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT915ImbalanceShares() : intZero;}//Imbalance at 9:15
	const int& GetT920ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT920ImbalanceShares() : intZero;}//Imbalance at 9:20
	const int& GetT925ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT925ImbalanceShares() : intZero;}//Imbalance at 9:25
	const int& GetT926ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT926ImbalanceShares() : intZero;}//Imbalance at 9:26
	const int& GetT928ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT928ImbalanceShares() : intZero;}//Imbalance at 9:28

	const int& GetT1545ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT1545ImbalanceShares() : intZero;}//Imbalance at 15:45
	const int& GetT1550ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT1550ImbalanceShares() : intZero;}//Imbalance at 15:50
	const int& GetT1555ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT1555ImbalanceShares() : intZero;}//Imbalance at 15:55
	const int& GetT1556ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT1556ImbalanceShares() : intZero;}//Imbalance at 15:56
	const int& GetT1557ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT1557ImbalanceShares() : intZero;}//Imbalance at 15:57
	const int& GetT1558ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT1558ImbalanceShares() : intZero;}//Imbalance at 15:58
	const int& GetT1559ImbalanceSharesExch() const{const Imbalance* imb = GetExchImbalance(); return imb ? imb->GetT1559ImbalanceShares() : intZero;}//Imbalance at 15:59

	virtual const Exchange* GetPrints(unsigned char marketCenterId) const{return NULL;}
	virtual const Exchange* GetBookExecutions(unsigned char bookId) const{return NULL;}

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

//	virtual const Price& GetChartExtendedHigh() const{return Price::priceZero;}
//	virtual const Price& GetChartExtendedLow() const{return Price::priceZero;}

	virtual unsigned short GetChartStartMinute() const{return 0;}//m_chartStartMinute;}

	virtual unsigned short GetChartSize() const{return 0;}
	virtual const ChartPointVector* GetChart() const{return NULL;}//m_chart;}
	virtual const bool& isChartLoaded() const{return boolFalse;}
	virtual const ChartPoint* GetChartPointAtMinute(unsigned short minute) const{return NULL;}//LockInquiryWaitChart/UnlockInquiryChart
	virtual const ChartPoint* GetLastChartPoint() const{return NULL;}//LockInquiryWaitChart/UnlockInquiryChart
	virtual const ChartPoint* GetLastButOneChartPoint() const{return NULL;}//LockInquiryWaitChart/UnlockInquiryChart
/*
	virtual unsigned short GetHistoricalChartSize() const{return 0;}
	virtual const HistoricalChartPointVector* GetHistoricalChart() const{return NULL;}
	virtual bool isHistoricalChartLoaded() const{return false;}
*/

	virtual unsigned short GetMoveCountQuoteGreenLocked() const{return 0;}
	virtual unsigned short GetMoveCountQuoteRedLocked() const{return 0;}
	virtual unsigned short GetMoveCountPrintGreenLocked() const{return 0;}
	virtual unsigned short GetMoveCountPrintRedLocked() const{return 0;}
	virtual const bool& isTest() const{return boolFalse;}
	virtual const bool& isIpo() const{return boolFalse;}
	virtual const char& GetType() const{return charZero;}
	virtual const bool& isRule19C3() const{return boolFalse;}
	virtual const bool& isItsEligible() const{return boolFalse;}
	virtual const char& GetTickPilotGroup() const{return charZero;}

	const char* const& GetTypeDescription() const;
	bool HasLuld() const
	{
		switch(GetType())
		{
			case STYPE_WARRANT:
			case STYPE_RIGHTS:
			return false;

			default:
			return true;
		}
	}
	const bool& isBancruptcy() const{return m_bancruptcy;}
	const bool& isExDistribution() const{return m_exDistribution;}
	const bool& isExRights() const{return m_exRights;}
	const bool& isExDividend() const{return m_exDividend;}
	const bool& isSpecialDividend() const{return m_specialDividend;}
//	bool& isSplit() const{return m_split;}
/*
	virtual unsigned char GetMoveReportLevel() const{return 0;}
	virtual void SetMoveReportLevel(unsigned char level){}
	virtual void SetMoveReportLevelFlag(MoveReportLevel level){}
	virtual void UnsetMoveReportLevelFlag(MoveReportLevel level){}
*/
	virtual unsigned char GetPositionStatus() const{return 0;}//0 - flat, 1 long, 2 short
	virtual int GetCurrentPositionSize() const{return 0;}
	virtual unsigned int GetCurrentPositionPrice() const{return 0;}

	virtual unsigned char GetPositionInventoryStatus() const{return 0;}//0 - flat, 1 long, 2 short
	virtual int GetCurrentPositionInventorySize() const{return 0;}
	virtual unsigned int GetCurrentPositionInventoryPrice() const{return 0;}

	virtual unsigned int GetLastExecPrice() const{return 0;}
	virtual int GetLastExecSize() const{return 0;}
//	virtual void GetEcnTopQuote(bool bid, Price& ecnTopQuote, bool lock) const{ecnTopQuote.SetZero();}//should be called only when Level2 is locked (or lock = true)

//	virtual void SkipUnappliedPrints(){}
	virtual const bool& isSubscriptionSent() const{return boolFalse;}

#ifndef TAKION_NO_OPTIONS
	const OptionInfo* const& GetOptionInfo() const{return m_optionInfo;}
//	OptionInfo* GetOptionInfo(){return m_optionInfo;}
//	void SetOptionInfo(OptionInfo* optionInfo);
	const unsigned __int64& GetOptionBlock() const{return m_optionInfo ? m_optionInfo->GetOptionBlock() : uint64Zero;}
	const unsigned __int64& GetOptionKey() const{return m_optionInfo ? m_optionInfo->GetOptionKeyValue() : uint64Zero;}
	const unsigned __int64& GetUnderlierNumericSymbol() const{return m_optionInfo ? m_optionInfo->GetUnderlierNumericSymbol() : uint64Zero;}//m_numericSymbol;}
//	const char* GetUnderlierSymbol() const{return m_optionInfo ? m_optionInfo->GetUnderlierSymbol() : NULL;}
//	const std::string& GetUnderlierSymbolStr() const{return m_optionInfo ? m_optionInfo->GetUnderlierSymbolStr() : stringZero;}
	bool isCall() const{return m_optionInfo && m_optionInfo->isCall();}
//	bool isMini() const{return m_optionInfo && m_optionInfo->isMini();}
	unsigned char GetSuffix() const{return m_optionInfo ? m_optionInfo->GetSuffix() : ucharZero;}
	unsigned char GetCallPutFlags() const{return m_optionInfo ? m_optionInfo->GetCallPutFlags() : ucharZero;}
	const unsigned char& GetOptionFlags() const{return m_optionInfo ? m_optionInfo->GetFlags() : ucharZero;}
	const unsigned int& GetStrikePrice() const{return m_optionInfo ? m_optionInfo->GetStrikePrice() : uintZero;}
	const unsigned int& GetExpirationOrdinal() const{return m_optionInfo ? m_optionInfo->GetExpirationOrdinal() : uintMinusOne;}
	unsigned int GetExpirationDate() const{return m_optionInfo ? m_optionInfo->GetExpirationDate() : uintZero;}
	const unsigned char& GetExpirationType() const{return m_optionInfo ? m_optionInfo->GetExpirationType() : ucharZero;}
	bool GetExpirationTokens(unsigned char& expirationDay, unsigned char& expirationMonth, unsigned char& expirationYear) const
	{
		if(m_optionInfo)
		{
			m_optionInfo->GetExpirationTokens(expirationDay, expirationMonth, expirationYear);
			return true;
		}
		else
		{
			expirationDay = expirationMonth = expirationYear = '\0';
			return false;
		}
	}
	const unsigned int& GetExpirationDays() const{return m_optionInfo ? m_optionInfo->GetExpirationDays() : uintZero;}
	const char& GetExpirationTypeChar() const{return m_optionInfo ? m_optionInfo->GetExpirationTypeChar() : space;}

	virtual const unsigned int& GetOpenInterestVolume() const{return uintZero;}
	virtual const unsigned int& GetImpliedVolatility() const{return uintZero;}
	virtual const int& GetDelta() const{return intZero;}
	virtual const int& GetVega() const{return intZero;}
	virtual const int& GetTheta() const{return intZero;}

	const unsigned int& GetContractSize() const{return m_optionInfo ? m_optionInfo->GetContractSize() : uintOne;}
	const unsigned short& GetOptionType() const{return m_optionInfo ? m_optionInfo->GetOptionType() : ushortZero;}
	const unsigned char& GetExpirationDayOfWeek() const{return m_optionInfo ? m_optionInfo->GetExpirationDayOfWeek() : ucharZero;}
	void GetOptionBlockAsString(std::string& optionSymbol, bool withSuffix) const{if(m_optionInfo)m_optionInfo->GetOptionBlockAsString(optionSymbol, withSuffix);}
	bool GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const
	{
		if(m_numericSymbol)
		{
			if(m_optionInfo)
			{
				if(suffixSeparate)
				{
					const unsigned char suffix = m_optionInfo->GetSuffix();
					if(suffix)
					{
						unsigned __int64 underlierSymbol = m_optionInfo->GetUnderlierNumericSymbol();
						if(!underlierSymbol)underlierSymbol = OptionKey::CalculateUnderlierSymbol(m_numericSymbol, suffix);
						optionSymbol += (const char*)&underlierSymbol;
					}
					else optionSymbol += (const char*)&m_numericSymbol;
				}
				else optionSymbol += (const char*)&m_numericSymbol;
			
				optionSymbol += ' ';
				m_optionInfo->GetOptionBlockAsString(optionSymbol, suffixSeparate);
			}
			else
				optionSymbol += (const char*)&m_numericSymbol;

			return true;
		}
		return false;
	}


//	void SetOpenInterestVolume(const unsigned int& openInterestVolume){if(m_optionInfo)m_optionInfo->SetOpenInterestVolume(openInterestVolume);}

	Underlier* GetUnderlier(){return m_optionInfo ? m_optionInfo->GetUnderlier() : NULL;}
	const Underlier* GetUnderlier() const{return m_optionInfo ? m_optionInfo->GetUnderlier() : NULL;}

	void NotifyOptionLevel2Observers(const Message* message, const Message* info = NULL) const
	{
//#ifdef SEC_OBS
		if(m_optionInfo)m_optionInfo->NotifyObservers(message, info, this);
//#endif
	}
	void AddOptionLevel2Observer(Observer* observer) const{if(m_optionInfo)m_optionInfo->AddObserver(observer);}
	void RemoveOptionLevel2Observer(Observer* observer) const{if(m_optionInfo)m_optionInfo->RemoveObserver(observer);}

	void NotifyOptionLevel2InThreadObservers(const Message* message, const Message* info = NULL) const
	{
//#ifdef SEC_OBS
		if(m_optionInfo)m_optionInfo->NotifyInThreadObservers(message, info, this);
//#endif
	}
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
	virtual const unsigned char& isHTB(const unsigned char& ordinal) const override{return m_optionInfo ? ucharZero : HTB::isHTB(ordinal);}

//The following 5 functions are about the Option Positions that have this Security as an Underlier
	virtual void RemoveFromUnderlierPositions(bool notify){}//, const Security* replaceSecurity = NULL) override;
//	virtual void ClearUnderlierPositions(bool notify){}//Included in ClearPositions
//	bool LockUnderlierPositions() const{return InterlockedExchange(&m_lockUnderlierPositions, 1) == 0;}
//	void UnlockUnderlierPositions() const{InterlockedExchange(&m_lockUnderlierPositions, 0);}
//	void LockWaitUnderlierPositions() const{while(!LockUnderlierPositions())Sleep(0);}

//Use LockUnderlierPositions/LockWaitUnderlierPositions - UnlockUnderlierPositions around using the next 2 functions don't forget to "delete iterator" when it's no longer needed
//Use LockPositions/LockWaitPositions - UnlockPositions around using the next 2 functions don't forget to "delete iterator" when it's no longer needed
	virtual TakionIterator* CreateUnderlierPositionIterator() const{return NULL;}
//Use GetNextPosition with CreateUnderlierPositionIterator()
//	static const Position* GetNextUnderlierPosition(TakionIterator* iterator, unsigned char* status);//status can be NULL if you don't want the value: 0 - flat, 1 - long, 2 - short
	const unsigned int& GetStockPositionCount() const{return m_stockPositionCount;}//Stock (or Option) Position (Position in this Security) count from all Accounts. Can be 0 or 1 Position per Account
	const unsigned int& GetOptionPositionCount() const{return m_optionPositionCount;}//Option Position count from all Accounts for this Security as an Underlier. Can be 0 or more Positions per Account
#else
	const unsigned int& GetStockPositionCount() const{return m_positionCount;}
#endif
	const unsigned int& GetPositionCount() const{return m_positionCount;}//m_stockPositionCount + m_optionPositionCount

	virtual void NullifyThread(){}
	virtual void RemoveFromPositions(bool notify){}//, const Security* replaceSecurity = NULL){}
	virtual void ClearPositions(bool notify){}
//	virtual void ReleaseNewPrints(){}//called from main thread
	virtual void ClearUnappliedPrints(){}

	bool LockInquiryPositions() const{return m_lockPositions.LockInquiry();}//InterlockedExchange(&m_lockPositions, 1) == 0;}
	void UnlockInquiryPositions() const{m_lockPositions.UnlockInquiry();}//InterlockedExchange(&m_lockPositions, 0);}
	void LockInquiryWaitPositions() const{m_lockPositions.LockInquiryWait();}

//Use LockPositions/LockWaitPositions - UnlockPositions around using the next 2 functions don't forget to "delete iterator" when it's no longer needed
	virtual TakionIterator* CreatePositionIterator() const{return NULL;}
	static const Position* GetNextPosition(TakionIterator* iterator, unsigned char* status);//status can be NULL if you don't want the value: 0 - flat, 1 - long, 2 - short
/*
	Position* position;
	unsigned char status;
	TakionIterator* iterator = CreatePositionIterator();
	if(iterator)
	{
		LockWaitPositions();
		iterator->Reset();
		while(position = GetNextPosition(iterator, &status))
		{
//do something with position
		}
		UlockPositions();
		delete iterator;
	}
*/
	const unsigned int& GetHeadlineCount() const{return m_headlineCount;}
	const unsigned __int64& GetLatestHeadlineDateTime() const{return m_latestHeadlineDateTime;}

	const unsigned int& GetYestAfterMarketHeadlineCount() const{return m_yestAfterMarketHeadlineCount;}
	const unsigned __int64& GetYestLatestHeadlineDateTime() const{return m_yestLatestHeadlineDateTime;}

	virtual bool isEntitledExpandedBookByFlag(const unsigned int& flag) const{return false;}
	virtual bool isEntitledTopOfBookByFlag(const unsigned int& flag) const{return false;}
	virtual bool isEntitledExpandedBook(const unsigned char& bookId) const{return false;}
	virtual bool isEntitledTopOfBook(const unsigned char& bookId) const{return false;}

	virtual bool isExtensionEntitledBookByFlag(const unsigned int& flag) const{return false;}
	virtual bool isExtensionEntitledTopOfBookByFlag(const unsigned int& flag) const{return false;}
	virtual bool isExtensionEntitledBook(const unsigned char& bookId) const{return false;}
	virtual bool isExtensionEntitledTopOfBook(const unsigned char& bookId) const{return false;}

	virtual const bool& isEntitledL1() const{return boolFalse;}
	virtual const bool& isEntitledPrint() const{return boolFalse;}
	virtual const unsigned int& GetExpandedBookEntitlement() const{return uintZero;}
	virtual const unsigned int& GetTopOfBookEntitlement() const{return uintZero;}

	virtual const bool& isEntitledExtensionL1() const{return boolFalse;}
	virtual const bool& isEntitledExtensionPrint() const{return boolFalse;}
	virtual const unsigned int& GetExtensionBookEntitlement() const{return uintZero;}
	virtual const unsigned int& GetExtensionTopOfBookEntitlement() const{return uintZero;}
/*
	virtual const unsigned int& GetExtensionExpandedBookEntitlement() const{return m_extensionExpandedBookEntitlement;}
	virtual const unsigned int& GetExtensionTopOfBookEntitlement() const{return m_extensionTopOfBookEntitlement;}
	bool isExtensionEntitledExpandedBookByFlag(const unsigned int& flag) const{return (GetExtensionExpandedBookEntitlement() & flag) != 0;}
	bool isExtensionEntitledTopOfBookByFlag(const unsigned int& flag) const{return (GetExtensionTopOfBookEntitlement & flag) != 0;}
	bool isExtensionEntitledExpandedBook(const unsigned char& bookId) const{return isExtensionEntitledExpandedBookByFlag(1 << bookId);}
	bool isExtensionEntitledTopOfBook(const unsigned char& bookId) const{return isExtensionEntitledTopOfBookByFlag(1 << bookId) != 0;}
*/

	const unsigned char& GetSymbolMappingMode() const{return m_symbolMappingMode;}//1 - no symbol mapping; 2 - symbol mapping; 0 - not initialized
protected:
	Security(const char* symbol, unsigned short code, bool subscribable
#ifndef TAKION_NO_OPTIONS
		, OptionInfo* optionInfo = NULL
#endif
		);

	virtual void InThreadObserverAdded() const
	{
		IncrementUnsubscribable();
	}
	virtual void InThreadObserverRemoved() const
	{
		DecrementUnsubscribable();
	}

	mutable unsigned short m_securityCode;
//	char m_name[MAX_SECURITY_NAME + 1];
	std::string m_name;

	unsigned int m_threadId;
	unsigned int m_roundLot;
	bool m_roundLotsOnly;
	char m_marketCategory;
	char m_financialStatus;
	char m_primaryExchange;
	unsigned int m_primaryExchangeNumericName;
	unsigned int m_marketCategoryFilter;
	unsigned int m_quoteConditionFilterAll;

	unsigned int m_customPriceBaseCompact;
	unsigned int m_customDate;
	unsigned int m_customDateDiff;

	bool m_subscribable;

	mutable bool m_loaded;
	mutable bool m_reloaded;
	mutable bool m_valid;
	mutable bool m_loadFailed;

	unsigned char m_primaryExchangeEntitlementFlag;
	unsigned char m_primaryExchangeEnum;

	mutable volatile LONG m_unsubscribable;

	unsigned __int64 m_yesterdaysVolume;
	unsigned __int64 m_averageDailyVolume;

	Price m_yesterdaysHighPrice;
	Price m_yesterdaysLowPrice;
	Price m_yesterdaysPriceRange;
	Price m_yesterdaysPriceRangePercent;

	unsigned __int64 m_latestHeadlineDateTime;
	unsigned int m_headlineCount;

	unsigned __int64 m_yestLatestHeadlineDateTime;
	unsigned int m_yestAfterMarketHeadlineCount;
/*
	static bool SetTimePrintPrice(const unsigned int& time, const unsigned int& timeThreshold, unsigned int& timePrice, const unsigned int& price)
	{
		if(time >= timeThreshold)// || !imbalanceShares)
		{
			timePrice = price;
		}
	}
*/
	unsigned int m_closePriceCompact;
	Price m_closePrice;
    unsigned short m_splitNumerator;
    unsigned short m_splitDenominator;
    unsigned int m_split;
	Price m_dividend;

	unsigned int m_positionCount;

	bool m_bancruptcy;
	bool m_exDistribution;
	bool m_exRights;
	bool m_exDividend;
	bool m_specialDividend;
//	bool m_split;

	unsigned char m_symbolMappingMode;//1 - no symbol mapping; 2 - symbol mapping; 0 - not initialized

#ifndef TAKION_NO_OPTIONS
	void SetOpenInterestVolume(const unsigned int& openInterestVolume){if(m_optionInfo)m_optionInfo->SetOpenInterestVolume(openInterestVolume);}
	void SetUnderlier(Underlier* underlier){if(m_optionInfo)m_optionInfo->SetUnderlier(underlier);}
	void InitOptionDescription();
	void SetUnderlierSymbol(const unsigned __int64& underlierSymbolNum)
	{
		if(m_optionInfo)
		{
			if(m_optionInfo->SetUnderlierSymbol(underlierSymbolNum) || m_name.empty())
			{
				InitOptionDescription();
			}
		}
	}
	void SetOptionType(const unsigned short& optionType){if(m_optionInfo)m_optionInfo->SetOptionType(optionType);}
	void SetExpirationOrdinal(const unsigned int& ordinal){if(m_optionInfo)m_optionInfo->SetExpirationOrdinal(ordinal);}
///////////
	virtual void OnOptionLevel2ObserverAdded() const{}
	virtual void OnOptionLevel2ObserverRemoved(bool unsubscribeImmediately) const{}
	OptionInfo* m_optionInfo;
/*
	OptionCollection* m_optionCollection;
	void CreateOptionCollection();
	void DestroyOptionCollection();
*/
//	mutable volatile LONG m_lockUnderlierPositions;
	unsigned int m_stockPositionCount;//Stock Position count from all Accounts. Can be 0 or 1 Position per Account
	unsigned int m_optionPositionCount;//Option Position count from all Accounts for this Security as an Underlier. Can be 0 or more Position per Account
#endif

	TakionLock m_lockLevel1;
	TakionLock m_lockLevel2;
	TakionLock m_lockPrints;
	TakionLock m_lockChart;
	TakionLock m_lockHistPrints;

	Observable m_inThreadObservable;
	TakionLockSingleThreadAccess m_lockInThreadObservable;

//	mutable volatile LONG m_lockPositions;
	TakionLockMultithread m_lockPositions;
private:
	Security(const Security& other);
	Security& operator=(const Security& other);
};

#ifndef TAKION_NO_OPTIONS

class OptionCallPut
{
public:
	OptionCallPut(Security* const& call = NULL, Security* const& put = NULL):
		m_call(call),
		m_put(put)
	{
	}
	Security* const& GetCall() const{return m_call;}
	Security* const& GetPut() const{return m_put;}
	Security* const& GetCallPut(const bool& call) const{return call ? m_call : m_put;}
	bool isEmpty() const{return !m_call && !m_put;}

//	Security* const& GetCall(){return m_call;}
//	Security* const& GetPut(){return m_put;}
	void SetCall(Security* const& call){m_call = call;}
	void SetPut(Security* const& put){m_put = put;}
	void SetCallPut(const bool& call, Security* const& callput){(call ? m_call : m_put) = callput;}
	void SetCallPut(Security* const& callput)
	{
		if(callput)
		{
			const OptionInfo* optionInfo = callput->GetOptionInfo();
			if(optionInfo)
			{
				if(optionInfo->isCall())m_call = callput;
				else m_put = callput;
			}
		}
	}
	void SetExpirationOrdinal(const unsigned int& ordinal)
	{
		if(m_call)m_call->SetExpirationOrdinal(ordinal);
		if(m_put)m_put->SetExpirationOrdinal(ordinal);
	}
protected:
	Security* m_call;
	Security* m_put;
};

class TU_API Underlier : public Observable, public TakionLockMultithread
{
public:
	virtual ~Underlier()
	{
		ClearAndDestroy();
//		NullifyStock();
	}
	typedef std::map<unsigned int, OptionCallPut> StrikeMap;
	typedef std::map<unsigned int, StrikeMap> ExpirationMap;
	typedef std::map<unsigned __int64, ExpirationMap> RootSymbolExpirationMap;

	typedef std::map<unsigned int, OptionCallPut> ExpirationMap1;
	typedef std::map<unsigned int, ExpirationMap1> StrikeMap1;
	typedef std::map<unsigned __int64, StrikeMap1> RootSymbolStrikeMap;

	const RootSymbolExpirationMap& GetSortedExpirationMap() const{return m_sortedExpirationMap;}//Do lock when using this function
	RootSymbolExpirationMap& GetSortedExpirationMap(){return m_sortedExpirationMap;}//Do lock when using this function
	const ExpirationMap* FindExpirationMap(const unsigned __int64& rootSymbol) const//Do lock when using this function
	{
		RootSymbolExpirationMap::const_iterator found = m_sortedExpirationMap.find(rootSymbol);
		return found == m_sortedExpirationMapEnd ? NULL : &found->second;
	}
	ExpirationMap* FindExpirationMap(const unsigned __int64& rootSymbol)//Do lock when using this function
	{
		RootSymbolExpirationMap::iterator found = m_sortedExpirationMap.find(rootSymbol);
		return found == m_sortedExpirationMapEnd ? NULL : &found->second;
	}

	const RootSymbolStrikeMap& GetSortedStrikeMap() const{return m_sortedStrikeMap;}//Do lock when using this function
	RootSymbolStrikeMap& GetSortedStrikeMap(){return m_sortedStrikeMap;}//Do lock when using this function
	const StrikeMap1* FindStrikeMap(const unsigned __int64& rootSymbol) const//Do lock when using this function
	{
		RootSymbolStrikeMap::const_iterator found = m_sortedStrikeMap.find(rootSymbol);
		return found == m_sortedStrikeMapEnd ? NULL : &found->second;
	}
	StrikeMap1* FindStrikeMap(const unsigned __int64& rootSymbol)//Do lock when using this function
	{
		RootSymbolStrikeMap::iterator found = m_sortedStrikeMap.find(rootSymbol);
		return found == m_sortedStrikeMapEnd ? NULL : &found->second;
	}

	typedef std::list<const Security*> SecurityList;
	bool GetOptionsAroundStrikeAndExpiration(bool call,
		const unsigned __int64& rootSymbol,
		const unsigned int expirationDate,
		const unsigned int strikePrice,
		const unsigned int expirationCountDown,
		const unsigned int expirationCountUp,
		const unsigned int strikePriceCountDown,
		const unsigned int strikePriceCountUp,
		SecurityList& securityList) const;//LockInquiryWait(); / UnlockInquiry around the function call (and using the securityList if not in the main thread).

	typedef CMap<OptionSymbolKey, const OptionSymbolKey&, Security*, Security* const&> StockOptionMap;//different rootSymbols possible
	const StockOptionMap& GetOptionMap() const{return m_optionMap;}//Do lock when using this function
	StockOptionMap& GetOptionMap(){return m_optionMap;}//Do lock when using this function
	unsigned int GetOptionCount() const{return (unsigned int)m_optionMap.GetCount();}
	Security* FindOption(const OptionSymbolKey& key)//Do lock when using this function
	{
		StockOptionMap::CPair* found = m_optionMap.PLookup(key);
		return found ? found->value : NULL;
	}
	const Security* FindOption(const OptionSymbolKey& key) const//Do lock when using this function
	{
		const StockOptionMap::CPair* found = m_optionMap.PLookup(key);
		return found ? found->value : NULL;
	}
	Security* FindOptionWithLocking(const OptionSymbolKey& key)//Do lock when using this function
	{
		Security* security = NULL;
		StockOptionMap::CPair* found;
		LockInquiryWait();
		found = m_optionMap.PLookup(key);
		if(found)security = found->value;
		UnlockInquiry();
		return security;
	}
	const Security* FindOptionWithLocking(const OptionSymbolKey& key) const//Do lock when using this function
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
	const char* GetSymbol() const{return (const char*)&m_numericSymbol;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
	const bool& isLoaded() const{return m_loaded;}
	const bool& isReloaded() const{return m_reloaded;}
	const bool& isValid() const{return m_valid;}
	const bool& isLoadFailed() const{return m_loadFailed;}

	virtual bool isLoadable() const{return true;}
	virtual bool CanUnsubscribe() const;
	LONG isUnsubscribable() const{return m_unsubscribable;}
	virtual LONG IncrementUnderlierUnsubscribable() const{return 2;}//{return InterlockedIncrement(&m_unsubscribable);}
	virtual LONG DecrementUnderlierUnsubscribable(bool unsubscribeImmediately = false) const{return 1;}

	virtual bool CanRemove() const;
	LONG isRemovable() const{return m_removable;}
	virtual LONG IncrementUnderlierRemovable() const{return 2;}//{return InterlockedIncrement(&m_unsubscribable);}
	virtual LONG DecrementUnderlierRemovable(bool removeImmediately = false) const{return 1;}

	void AddInThreadObserver(Observer* o) const;//Call RemoveInThreadObserver in the destructor of the object that you pass to this function
	void RemoveInThreadObserver(Observer* o) const;
//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;
//	virtual HANDLE GetThreadHandle() const{return NULL;}
	const unsigned int& GetThreadId() const{return m_threadId;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}
//	typedef std::set<char> CharSet;
//	const CharSet& GetSuffixSet() const{return m_suffixSet;}
	const unsigned int& GetSuffixAlphaFlags() const{return m_suffixAlphaFlags;}
	const unsigned int& GetSuffixNumFlags() const{return m_suffixNumFlags;}

//	virtual void Destroy(){}
	virtual void Resubscribe() const{}
	virtual bool Subscribe(bool snapshotsOnly) const{return false;}
	virtual bool Unsubscribe() const{return false;}
	const bool& isSnapshotsOnly() const{return m_snapshotsOnly;}

//	const Security* GetStock() const{return m_stock;}

	const unsigned short& GetOptionType() const{return m_optionType;}
	Underlier& operator=(const Underlier& other);
protected:
	Underlier(const char* const& symbol, const unsigned short& optionType = 0);
	Underlier(const unsigned __int64& symbol, const unsigned short& optionType = 0);
	Underlier(const Underlier& other);

	void Clear()//Do lock when using this function
	{
		m_sortedExpirationMap.clear();
		m_sortedStrikeMap.clear();
		m_optionMap.RemoveAll();
	}
	void ClearAndDestroy();//Do lock when using this function//{m_optionMap.RemoveAll();}
//	std::string m_symbolStr;
	unsigned __int64 m_numericSymbol;
//	void NullifyStock();
//	void SetStock(const Security* stock);
//	const Security* m_stock;

	void UpdateOptionExpirationOrdinals();

	StockOptionMap m_optionMap;

	RootSymbolExpirationMap m_sortedExpirationMap;
	RootSymbolExpirationMap::const_iterator m_sortedExpirationMapEnd;

	RootSymbolStrikeMap m_sortedStrikeMap;
	RootSymbolStrikeMap::const_iterator m_sortedStrikeMapEnd;

	mutable volatile LONG m_unsubscribable;
	mutable volatile LONG m_removable;
	mutable bool m_loaded;
	mutable bool m_reloaded;
	mutable bool m_valid;
	mutable bool m_loadFailed;
	mutable bool m_snapshotsOnly;
	Observable m_inThreadObservable;
	TakionLockSingleThreadAccess m_lockInThreadObservable;
//	CharSet m_suffixSet;
	unsigned int m_threadId;
	unsigned int m_suffixAlphaFlags;
	unsigned int m_suffixNumFlags;
	unsigned short m_optionType;
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

	TU_ORDER_STATUS_BLOCKED,

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

enum OrderPostponed : unsigned char
{
	TU_ORDER_NOT_POSTPONED,
	TU_ORDER_POSTPONED,

	TU_ORDER_POSTPONED_COUNT
};

enum OrderUserType : unsigned char
{
	TU_ORDER_USER_TYPE_IS_0,
	TU_ORDER_USER_TYPE_GREATER_0,

	TU_ORDER_USER_TYPE_COUNT
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
	explicit ExecutionIdAsNumberArray(const char* str):StrAsNumberArray(str){}
	ExecutionIdAsNumberArray(const char*& str, const char& del):StrAsNumberArray(str, del){}
	ExecutionIdAsNumberArray(const char*& str, unsigned short length, const char& del):StrAsNumberArray(str, length, del){}
	ExecutionIdAsNumberArray(unsigned short exactLength, const char* str):StrAsNumberArray(exactLength, str){}
	explicit ExecutionIdAsNumberArray(const std::string& str):StrAsNumberArray(str){}
//	operator size_t() const{return m_numberArray[4 / sizeof(size_t)];}
//	operator int() const{return (int)m_numberArray[4 / sizeof(size_t)];}
//	operator long() const{return (long)m_numberArray[4 / sizeof(size_t)];}
	size_t GetHashValue() const{return m_numberArray[4 / sizeof(size_t)];}
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
//	operator size_t() const{return m_numberArray[4 / sizeof(size_t)];}
//	operator int() const{return (int)m_numberArray[4 / sizeof(size_t)];}
//	operator long() const{return (long)m_numberArray[4 / sizeof(size_t)];}
	size_t GetHashValue() const{return m_numberArray[4 / sizeof(size_t)];}
	DECLARE_NED_NEW
};

class PositionInventoryData;

class TU_API ExecutionOrderInventory
{
friend class Execution;
friend class Order;
public:
	ExecutionOrderInventory(const int& positionSize, const unsigned int& positionPrice):
		m_closedShares(0),
		m_positionSize(positionSize),
		m_positionPrice(positionPrice)
	{}
	DECLARE_NED_NEW
	const Money& GetClosedPnl() const{return m_closedPnl;}
	const Money& GetClosedPnlCost() const{return m_closedPnlCost;}
	const Money& GetPositionMarkedPnl() const{return m_positionMarkedPnl;}
	const Money& GetAccountMarkedPnl() const{return m_accountMarkedPnl;}
	const Money& GetPositionClosedPnl() const{return m_positionClosedPnl;}
	const Money& GetAccountClosedPnl() const{return m_accountClosedPnl;}
	const unsigned int& GetClosedShares() const{return m_closedShares;}
	const int& GetPositionSize() const{return m_positionSize;}
//	const Price& GetPositionAveragePrice() const{return m_positionPrice;}
	const unsigned int& GetPositionAveragePrice() const{return m_positionPrice;}
protected:
	void SetPositionInfo(const PositionInventoryData& position);

	void AddClosedPnl(const Money& closedPnl, const Money& closedPnlCost, const unsigned int& closedShares){m_closedPnl += closedPnl; m_closedPnlCost += closedPnlCost; m_closedShares += closedShares;}
	void SetClosedPnl(const Money& closedPnl, const Money& closedPnlCost, const unsigned int& closedShares){m_closedPnl = closedPnl; m_closedPnlCost = closedPnlCost; m_closedShares = closedShares;}
	void SetPositionMarkedPnl(const Money& markedPnl, const Money& closedPnl){m_positionMarkedPnl = markedPnl; m_positionClosedPnl = closedPnl;}
	void SetAccountMarkedPnl(const Money& markedPnl, const Money& closedPnl){m_accountMarkedPnl = markedPnl; m_accountClosedPnl = closedPnl;}

	Money m_closedPnl;
	Money m_closedPnlCost;
	Money m_positionMarkedPnl;
	Money m_accountMarkedPnl;
	Money m_positionClosedPnl;
	Money m_accountClosedPnl;
	unsigned int m_closedShares;
	int m_positionSize;
	unsigned int m_positionPrice;
};

class TU_API Execution : public PriceQuantity, public ExecutionOrderInventory
{
public:
	static const unsigned int uintZero;
	virtual ~Execution();
	const unsigned int& GetId() const{return m_id;}
	const unsigned int& GetMmid() const{return m_mmid;}
//	virtual unsigned int GetDestinationName() const{return 0;}
	const unsigned int& GetTimeSent() const{return m_timeSent;}
	const unsigned int& GetTimeReceived() const{return m_timeReceived;}
	const short& GetDelay() const{return m_delay;}
	const Money& GetClosedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnl() : m_closedPnl;}
	const Money& GetClosedPnlCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlCost() : m_closedPnlCost;}
	const Money& GetPositionMarkedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPositionMarkedPnl() : m_positionMarkedPnl;}
	const Money& GetAccountMarkedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAccountMarkedPnl() : m_accountMarkedPnl;}
	const Money& GetPositionClosedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPositionClosedPnl() : m_positionClosedPnl;}
	const Money& GetAccountClosedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAccountClosedPnl() : m_accountClosedPnl;}
	const unsigned int& GetClosedSharesInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedShares() : m_closedShares;}
	const int& GetPositionSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPositionSize() : m_positionSize;}
	const unsigned int& GetPositionAveragePriceInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPositionAveragePrice() : m_positionPrice;}

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
	const unsigned short& GetRoutingId() const;

	const unsigned int& GetRoutingName() const{return m_routingName;}
	const unsigned int& GetOrderMnemonic() const{return m_mnemonic;}
	const unsigned int& GetRealOrderMnemonic() const{return m_realMnemonic;}

	const bool& isSupervisorAutoClose() const{return m_supervisorAutoClose;}
	const unsigned char& GetOrderType() const;
	const unsigned short& GetUserOrderType() const;
	const std::string& GetUserOrderTypeString() const;
	const unsigned __int64& GetUserOrderId() const;
	const char* const& GetUserOrderInfo() const;
	const unsigned int& GetParentId() const;
	const unsigned int& GetReplacedClientId() const;
	const unsigned int& GetSendId() const;
	const Price& GetLimitPrice() const;
//	const Price& GetQuotePrice() const;
	const unsigned int& GetOrderQuantity() const;
	const unsigned int& GetPendingQuantity() const{return m_remainingQuantity;}
	const unsigned int& GetSharesTradedPosition() const{return m_sharesTradedPosition;}
	const unsigned int& GetSharesTradedAccount() const{return m_sharesTradedAccount;}
	const unsigned int& GetOrderClientId() const;
	const unsigned int& GetOrderServerId() const;
	const unsigned int& GetTraderId() const;
	const unsigned int& GetIpOrderSentFrom() const;
	const unsigned int& GetErroneousShares() const{return m_erroneousShares;}

//	const char& GetLiquidity() const{return m_liquidity;}
//	const char& GetBillable() const{return m_billable;}
	const unsigned int& GetLiquidity() const{return m_liquidity;}
	unsigned char isSharesAdded(const unsigned int mmid, const unsigned int liquidity) const;// const char liquidity, const char billable);//returns LiquidityType
	static unsigned char isSharesAdded4Chars(const unsigned int liquidity);//LT_ADDED, LT_REMOVED, LT_NEUTRAL(old 1 - added; 2 - removed; 3 - LT_NEUTRAL; 0 - liquidity is not found among possible values)
	const unsigned char& isAddedLiquidity() const{return m_addedLiquidity;}//LT_ADDED, LT_REMOVED, LT_NEUTRAL
	const bool& is2LetterLiquidityFormat() const{return m_2LetterLiquidityFormat;}

	const unsigned int& GetAddedShares() const{return m_addedLiquidity == LT_ADDED ? m_quantity : uintZero;}
	const unsigned int& GetRemovedShares() const{return m_addedLiquidity == LT_REMOVED ? m_quantity : uintZero;}
	const unsigned int& GetNeutralShares() const{return m_addedLiquidity == LT_NEUTRAL ? m_quantity : uintZero;}

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
	const unsigned short& GetOptionType() const;
	void GetOptionBlockAsString(std::string& optionSymbol, bool suffixSeparate) const;
	void GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const;
	const unsigned int& GetContractSize() const;
#endif
	const ExecutionOrderInventory* GetInventory() const{return m_inventory;}
	const SignedPrice& GetExecNetPercent() const{return m_execNetPercent;}
protected:
	Execution(Order* order,
		unsigned int id,
		const Price& price,
		unsigned int quantity,
		unsigned int mmid,
		unsigned int timeSent,
		unsigned int timeReceived,
		unsigned int liquidity,
		bool twoLetterLiquidityFormat,
//		char liquidity,
//		char billable,
		char origin,
		bool dropcopy,
		bool busted,
		const char* marketReferenceId,
		int positionSize,
//		unsigned int positionPrice,
		int inventoryPositionSize,
//		unsigned int inventoryPositionPrice,
		unsigned int positionSharesTraded,
		unsigned int accountSharesTraded,
		const SignedPrice& execNetPercent);

	void SetInventoryPositionSize(const int& inventorySize);
	void SetInventoryClosedPnl(const Money& closedPnl, const Money& closedPnlCost, unsigned int closedShares);
	void SetInventoryPositionInfo(const Position& position);
	void SetInventoryAccountMarkedPnl(const Money& markedPnl, const Money& closedPnl);
	Order* m_order;
	SignedPrice m_execNetPercent;
	unsigned int m_id;
	unsigned int m_mmid;
	unsigned int m_timeSent;
	unsigned int m_timeReceived;
	unsigned int m_erroneousShares;
	unsigned int m_remainingQuantity;
	unsigned int m_liquidity;
	short m_delay;

//	char m_liquidity;
//	char m_billable;
	bool m_2LetterLiquidityFormat;
	unsigned char m_addedLiquidity;//LiquidityType

	char m_origin;
	bool m_dropcopy;
	bool m_busted;
	bool m_supervisorAutoClose;

	unsigned int m_routingName;
	unsigned int m_mnemonic;
	unsigned int m_realMnemonic;
/*
	unsigned int m_closedShares;
	Money m_closedPnl;
	Money m_closedPnlCost;
	Money m_positionMarkedPnl;
	Money m_accountMarkedPnl;
	Money m_positionClosedPnl;
	Money m_accountClosedPnl;
	Price m_positionPrice;
	int m_positionSize;
*/
	unsigned int m_sharesTradedPosition;
	unsigned int m_sharesTradedAccount;

//	std::string m_executionReferenceId;
	ExecutionIdAsNumberArray m_executionReferenceId;

	ExecutionOrderInventory* m_inventory;
private:
	Execution(const Execution& other);
	Execution& operator=(const Execution& other);
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
typedef CMap<unsigned int, const unsigned int&, Execution*, Execution* const&> ExecutionMap;
//typedef std::list<Execution*> ExecutionList;

typedef std::set<Execution*, lessPtr<Execution*> > ExecutionChronologicalSet;

typedef CMap<unsigned __int64, const unsigned __int64&, Position*, Position* const&> PositionMap;
#ifndef TAKION_NO_OPTIONS
typedef CMap<OptionSymbolBlockKey, const OptionSymbolBlockKey&, Position*, Position* const&> OptionPositionMap;
#endif

typedef CMap<unsigned int, const unsigned int&, Order*, Order* const&> OrderMap;

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
	OE_BORROW_NO_INVENTORY,

	OE_TRIGGER_CONDITION_ALREADY_MET,

	OE_UNOPEN_IPO_MARKET_ORDER,

	OE_HTB_STOCK_NO_LOCATE_CONTRACT_NUMBER,

	OE_UNTRADEABLE_SYMBOL,
	OE_UNTRADEABLE_STATUS_NOT_LOADED,

	OE_WRONG_STOCK,

	OE_NO_REPLACE_FOR_DROPCOPY_ORDERS,
	OE_CANNOT_CANCEL_ORDER_BEFORE_SENDING_NEW_ONE,

	OE_INVALID_PEG_TYPE,

	OE_PRE_BORROW_REQUIRED,

	OE_SPOOFING_ORDER_COUNT_RATIO_EXCEEDED,
	OE_SPOOFING_ORDER_SIZE_RATIO_EXCEEDED,

	OE_RESTRICTED_SYMBOL_LIST_NOT_LOADED,

	OE_MIN_SHARE_PRICE_EXCEEDED,
	OE_MAX_SHARE_PRICE_EXCEEDED,

	OE_ADV_ORDER_COUNT_EXCEEDED,
	OE_ADV_ORDER_SIZE_RATIO_EXCEEDED,
	OE_ADV_TOO_LOW,

	OE_ORDER_TOO_PASSIVE,

	OE_MAX_ORDERS_PER_POSITION_EXCEEDED,

	OE_ORDER_TO_REPLACE_IS_BEING_CANCELED,
	OE_ORDER_TO_REPLACE_IS_DEAD,
	OE_TOO_LATE_TO_REPLACE,
	OE_REPLACE_ALREADY_SENT,
	OE_ORDER_TO_REPLACE_NOT_FOUND,

	OE_ORDERS_PER_TIME_FRAME_EXCEEDED,
	OE_NBBO_ORDER_SIZE_EXCEEDED,

	OE_NOTHING_TO_REPLACE,
	OE_NO_CHANGE_IN_REPLACE,

	OE_EXPIRED,

	OE_NOT_FULLY_EXECUTED,

	OE_NO_NASDAQ_MD_ENTITLEMENT,
	OE_NO_LISTED_MD_ENTITLEMENT,

	OE_TOO_LATE_TO_SEND,

	OE_SIZE_SMALLER_THAN_ROUND_LOT,

	OE_NO_MARKET_DATA_ENTITLEMENTS,

	OE_MARGIN_EXCESS,
	OE_HARD_MARGIN_EXCESS,

	OE_MARKET_STATUS_UNKNOWN,

	OE_PRE_BORROW_FAILED,

#ifndef TAKION_NO_OPTIONS
	OE_NO_OPTION_VENUE,
	OE_INVALID_OPTION_VENUE,
	OE_OPTION_POSITION_COUNT,
	OE_NO_BORROW_FOR_INSTRUMENT,
	OE_OPTION_BUYING_POWER,
	OE_OPTION_NAKED,
	OE_UNDERLIER_OPTION_NAKED,
	OE_NO_OPTION_MD_ENTITLEMENT,
#endif
	OE_ERROR_Count
};

enum CancelError : unsigned char
{
	CE_OK,

	CE_TRADING_NOT_ALLOWED,
	CE_CANCEL_ALREADY_SENT,
	CE_ORDER_NOT_FOUND,
	CE_TOO_LATE,
	CE_DROPCOPY_ORDER,
	CE_ORDER_NOT_SENT,
	CE_NON_CANCELABLE,

	CE_SPOOFING_ORDER_COUNT_RATIO_EXCEEDED,
	CE_SPOOFING_ORDER_SIZE_RATIO_EXCEEDED,

	CE_NO_CURRENT_ACCOUNT,

//	CE_ADV_ORDER_COUNT_RATIO_EXCEEDED,
//	CE_ADV_ORDER_SIZE_RATIO_EXCEEDED,

	CE_NO_ORDER,

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
	YNM_ALL = (1 << YNM_Count) - 1
};

enum ExistingPrice : unsigned char
{
	EP_UNKNOWN,
	EP_PQOPEN,
	EP_TCLOSE,

	EP_Count,

	EP_ALL = (1 << EP_Count) - 1
};

enum AlgorithmMask : unsigned char
{
	ALGORITHMMASK_YES,
	ALGORITHMMASK_LIMIT,
	ALGORITHMMASK_MARKET,
	ALGORITHMMASK_STOP,
	
	ALGORITHMMASK_COUNT,

	ALGORITHMMASK_ALL = (1 << ALGORITHMMASK_COUNT) - 1
};

enum TifMask : unsigned int
{
	TIFMASK_ON_OPEN,
	TIFMASK_ON_CLOSE,
	TIFMASK_DAY,
	TIFMASK_EXTENDED,
	TIFMASK_TIME,
	TIFMASK_IOC,
	TIFMASK_FOK,
	TIFMASK_OTHER,
	TIFMASK_GTC,
	TIFMASK_GTT,

	TIFMASK_COUNT,

	TIFMASK_ALL = (1 << TIFMASK_COUNT) - 1
};

enum SideMask : unsigned char
{
	SIDEMASK_BUY,
	SIDEMASK_SELL,
	SIDEMASK_SHORT,

	SIDEMASK_COUNT,

	SIDEMASK_ALL = (1 << SIDEMASK_COUNT) - 1
};

enum VisibleSizeMask : unsigned char
{
	VSM_HIDDEN,
	VSM_VISIBLE,

	VSM_COUNT,

	VSM_ALL = (1 << VSM_COUNT) - 1
};

enum OddLotMask : unsigned char
{
	OLM_ODDLOT,
	OLM_EVENLOT,

	OLM_COUNT,

	OLM_ALL = (1 << OLM_COUNT) - 1
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
	CIP_REPLACE,

	CIP_Count
};

enum OrderDirection : unsigned char
{
	ODIR_CLOSE,
	ODIR_OPEN,
	ODIR_ADD,

	ODIR_NONE,

	ODIR_Count,

	ODIR_LIVE_MASK = (1 << ODIR_NONE) - 1
};

class TU_API Order : public Observable, public ExecutionOrderInventory, public TakionLock
{
friend class Account;
friend class Position;
public:
	static const unsigned __int64 uint64Zero;
	static const unsigned int uintZero;
	static const int intZero;
	static const unsigned int uint100;
	static const unsigned short ushortZero;
	static const unsigned char ucharZero;
	static const char charZero;
	static const bool boolFalse;

#if (_MSC_VER > 1600)
	typedef std::unordered_set<Order*> OrderSet;
#else
	typedef std::hash_set<Order*> OrderSet;
#endif

	virtual ~Order();

	const unsigned int& GetSendId() const{return m_sendId;}
	const unsigned int& GetSplitParentClientId() const{return m_splitParentClientId;}
	const unsigned int& GetSplitChildClientId() const{return m_splitChildClientId;}

	unsigned int GetThreadId() const;
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}

	const unsigned int& GetIpSentFrom() const{return m_ipSentFrom;}
	const unsigned int& GetIpCancelFrom() const{return m_ipCancelFrom;}
	const unsigned int& GetTraderId() const{return m_traderId;}
	const unsigned int& GetClientId() const{return m_clientId;}
	const unsigned int& GetClientIdOriginal() const{return m_clientIdOriginal;}
	const unsigned int& GetClientIdChronological() const{return m_clientIdChronological;}
	const unsigned int& GetServerId() const{return m_serverId;}
	const unsigned int& GetParentId() const{return m_parentId;}
	const unsigned int& GetReplacedClientId() const{return m_replacedClientId;}
	const unsigned int& GetReplacedByClientId() const{return m_replacedByClientId;}
	const unsigned int& GetReplacedBySendId() const{return m_replacedBySendId;}
	const unsigned __int64& GetUserId() const{return m_userId;}
	const unsigned __int64& GetDestinationId() const{return m_destinationId;}
//	const std::string& GetSymbolStr() const;
	bool SetReplacedByClientId(const unsigned int& replacedByClientId, const unsigned int& replacedBySendId, bool notify)
	{
		if(replacedByClientId != m_replacedByClientId || replacedBySendId != m_replacedBySendId)
		{
			m_replacedByClientId = replacedByClientId;
			m_replacedBySendId = replacedBySendId;
//			if(notify)WriteOrderUpdateMessageToMainThread(GetReplacingQuantity(), false, false, 0);
			if(notify)WriteOrderUpdateMessageToMainThread(GetReplacingQuantity(), false, 0, TU_OS_COUNT);//GetOrderState()
			return true;
		}
		return false;
	}

	virtual const char* GetSymbol() const;
	virtual const unsigned __int64& GetNumericSymbol() const;
	virtual SecurityType GetSecurityType() const;
	virtual const char* GetAccountId() const;
	virtual const char* GetAccountUserName() const;
	virtual const Account* GetAccount() const;
//	Position* GetPosition(){return m_position;}
	const Position* GetPosition() const{return m_position;}

	unsigned char GetExistingPrice() const;//enum ExistingPrice
	bool FilterByExistingPrice(unsigned char pqOpenMask, unsigned char tCloseMask) const;

	unsigned char GetMeRate() const;

	virtual bool isNotifyCancel() const{return true;}
	virtual bool isServerOrder() const{return false;}
	virtual bool isDummy() const{return false;}
	virtual bool isAlgorithm() const{return false;}
	virtual const char* GetAlgorithmName() const{return "";}
	virtual bool CanBeReplaced() const;

	virtual bool HasPrice() const{return true;}
	virtual bool HasSize() const{return true;}
	virtual unsigned int GetAlgorithmQuantity() const{return GetQuantity();}
	virtual bool CanBeWashOrder() const{return !isBorrow();}
	virtual bool isQuoteOrder() const{return !isBorrow();}
	virtual bool HasDirection() const{return isQuoteOrder();}
	virtual bool isArcaPlo() const{return false;}
	virtual bool CanShowInPosMan() const{return !m_blocked;}
	
	virtual unsigned int GetAlgorithmId() const{return 0xFFFFFFFF;}
	virtual unsigned int GetGtcAlgoId() const{return 0;}
	virtual bool isOrderVariation() const{return true;}
/*
	unsigned int GetGtcAlgoIdOrClientId() const
	{
		const unsigned int gtcAlgoId = GetGtcAlgoId();
		return gtcAlgoId ? gtcAlgoId : m_clientId;
	}
*/
	const unsigned int& GetLastExecutionTime() const{return m_lastExecutionTime;}

	virtual void GetAlgoLiveOrders(OrderSet& orderSet) const{}
	virtual void GetAlgoOrders(OrderSet& orderSet) const{}
/*
	virtual const Order* GetAlgoSentOrder() const{return NULL;}
	virtual const Order* GetAlgoFirmSplitOrder() const{return NULL;}
	virtual const Order* GetAlgoSplitOrder() const{return NULL;}
*/
	bool CanBeMassCanceled() const{return !m_noMassCancel && !m_beingCanceled;}
	bool CanBeMassCanceledOrReplaced(const bool& canceled) const{return CanBeMassCanceled() && (canceled || CanBeReplaced());}
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

//	virtual bool isOrderPassive() const;
	const bool& isCreatedPassive() const{return m_passive;}
	bool isOrderPassive() const;
	bool isStopOrder() const{return m_stopOrderType != 0 || !m_stopPrice.isZero();}
	bool isStopTrailingOrder() const{return m_stopOrderType == OST_TRAILING;}
	bool isPotentialSpoofingOrder() const;
	bool isPotentialAdvOrder() const;
	bool isLimitOnClose() const{return m_tifType == TIF_ATC && !m_limitPrice.isZero();}
//	virtual bool isAdvOrderType(const unsigned char orderType) const{return true;}
	virtual bool isWashable() const;
	virtual bool isLimitDayToRemove() const;

	static const Price& GetOrderPricePerShare(const Price& limitPrice, const Price& stopPrice, const Price& level1Price, char side, bool borrow)
	{
//		return !borrow && (limitPrice.isZero() || side != 'B' && limitPrice < level1Price) ? level1Price : limitPrice;
		if(borrow)return limitPrice;
		else if(limitPrice.isZero())
		{
			return stopPrice.isZero() ? level1Price : stopPrice;
		}
		else
		{
			return side != 'B' && limitPrice < level1Price ? level1Price : limitPrice;
		}
	}

	virtual bool isMarketOrder() const{return false;}

	virtual void WriteAlgorithmNotifyMessageToAccountThread(unsigned short code, unsigned short eventCode){}

	const unsigned char& GetOrderType() const{return m_orderType;}
	const unsigned short& GetUserOrderType() const{return m_userOrderType;}
	const std::string& GetUserOrderTypeString() const;
	const char* const& GetUserOrderInfo() const{return m_userOrderInfo;}
	const unsigned char& GetStopOrderType() const{return m_stopOrderType;}
	const unsigned char& GetStopOrderBase() const{return m_stopOrderBase;}
	const Price& GetLimitPrice() const{return m_limitPrice;}
	const Price& GetDiscretionaryPrice() const{return m_discretionaryPrice;}
	const Price& GetStopPrice() const{return m_stopPrice;}
	const Price& GetInitialStopPrice() const{return m_initialStopPrice;}
	const Price& GetLevel1Price() const{return m_level1Price;}
	const Price& GetLevel1SameSidePrice() const{return m_level1SameSidePrice;}
	const Price& GetBidPrice() const{return m_side == 'B' ? m_level1SameSidePrice : m_level1Price;}
	const Price& GetAskPrice() const{return m_side == 'B' ? m_level1Price : m_level1SameSidePrice;}
	const Price& GetLastPrintPrice() const{return m_lastPrintPrice;}
	const Price& GetPricePerShare() const{return m_pricePerShare;}
	const Price& GetQuotePrice() const{return m_quotePrice;}//for displaying the order among quotes in the MmBox
	const unsigned int& GetLevel1PriceCompact() const{return m_level1PriceCompact;}
	const unsigned int& GetQuotePriceCompact() const{return m_quotePriceCompact;}//for displaying the order among quotes in the MmBox
	const unsigned int& GetStopPriceCompact() const{return m_stopPriceCompact;}//for displaying the order among quotes in the MmBox
	const unsigned int& GetOrderPriceCompact() const{return m_quotePriceCompact ? m_quotePriceCompact : m_level1PriceCompact;}
	const Price& GetOrderPrice() const{return m_quotePriceCompact ? m_quotePrice : m_level1Price;}

	const unsigned int& GetQuantity() const{return m_quantity;}
	const unsigned int& GetDisplayQuantity() const{return m_displayQuantity;}
	const unsigned int& GetReserveQuantity() const{return m_reserveQuantity;}

	const unsigned int& GetOcoId() const{return m_ocoId;}
	virtual bool CanBeOco() const{return true;}

	virtual bool isDone() const{return !m_pendingQuantity && !m_expiredQuantity;}

	const unsigned int& GetMaxDisplayLimit() const{return m_maxDisplayLimit;}//0 for some destinations that are always hidden; 0xFFFFFFFF for the others
	const unsigned int& GetMaxDisplayQuantity() const{return m_maxDisplayQuantity;}//0 for some destinations that are always hidden; 0xFFFFFFFF for the others; no more than m_quantity

	const unsigned int& GetMinDisplayLimit() const{return m_minDisplayLimit;}//100 for ARCA, 0 for NSDQ
	const unsigned int& GetMinDisplayQuantity() const{return m_minDisplayQuantity;}//100 for ARCA, 0 for NSDQ; no more than m_quantity
	unsigned int GetRemainingVisibleSize() const
	{
		const unsigned int replacingQuantity = GetReplacingQuantity();

		return m_displayQuantity > m_maxDisplayQuantity ?
			m_maxDisplayQuantity < replacingQuantity ? m_maxDisplayQuantity : replacingQuantity:

			m_displayQuantity < m_minDisplayQuantity ?
			m_minDisplayQuantity < replacingQuantity ? m_minDisplayQuantity : replacingQuantity:

			m_displayQuantity < replacingQuantity ? m_displayQuantity : replacingQuantity;
	}
	const unsigned int& GetInitialVisibleSize() const
	{
		return m_displayQuantity > m_maxDisplayQuantity ?
			m_maxDisplayQuantity < m_quantity ? m_maxDisplayQuantity : m_quantity:

			m_displayQuantity < m_minDisplayQuantity ?
			m_minDisplayQuantity < m_quantity ? m_minDisplayQuantity : m_quantity:
			
			m_displayQuantity < m_quantity ? m_displayQuantity : m_quantity;
	}
	const unsigned int& GetFilledQuantity() const{return m_filledQuantity;}
	const unsigned int& GetInheritedFilledQuantity() const{return m_inheritedFilledQuantity;}
	const unsigned int& GetCanceledQuantity() const{return m_canceledQuantity;}
	const unsigned int& GetExpiredQuantity() const{return m_expiredQuantity;}
	const unsigned int& GetRejectedQuantity() const{return m_rejectedQuantity;}

	const unsigned int& GetPendingQuantity() const{return m_pendingQuantity;}
	const unsigned int& GetPendingQuantityInitial() const{return m_pendingQuantityInitial;}
	const unsigned int& GetRemainingQuantityInitialFromServer() const{return m_remainingQuantityInitialFromServer;}
	unsigned int GetUnfilledQuantity() const{return m_pendingQuantityInitial > m_filledQuantity ? m_pendingQuantityInitial - m_filledQuantity : 0;}
	const unsigned int& GetQuantityBeingCanceled() const{return m_quantityBeingCanceled;}
	const unsigned int& GetQuantityLastKilled() const{return m_quantityLastKilled;}
	unsigned int GetReplacingQuantity() const{return m_pendingQuantity + m_expiredQuantity;}

	bool isRejected() const{return m_rejectedQuantity >= m_quantity;}

	const unsigned char& GetTifType() const{return m_tifType;}
//	const unsigned char GetSentTifType() const{return m_tifType == TIF_GTC ? TIF_GTX : m_tifType;}
	const unsigned char& GetSentTifType() const{return m_sentTifType;}
	const unsigned char& GetInitialTifType() const{return m_initialTifType;}
	const unsigned int& GetTifMillisecond() const{return m_tifMillisecond;}
	const unsigned int& GetSentTifMillisecond() const{return m_sentTifMillisecond;}
	bool GetTifAsString(std::string& text, const bool& showMillisecond) const
	{
		return TU_GetTifAsString(text, m_tifType, m_monitorTif, NULL, m_tifMillisecond, showMillisecond, "ERROR", false);
	}
	bool GetSentTifAsString(std::string& text, const bool& showMillisecond) const
	{
		return TU_GetTifAsString(text, m_sentTifType, m_monitorTif, NULL, m_sentTifMillisecond, showMillisecond, "ERROR", false);
	}
	bool GetInitialTifAsString(std::string& text, const bool& showMillisecond) const
	{
		return TU_GetTifAsString(text, m_initialTifType, m_monitorTif, NULL, m_tifMillisecond, showMillisecond, "ERROR", false);
	}
	bool isOnOpen() const{return m_tifType == TIF_OPG;}
	bool isOnClose() const{return m_tifType == TIF_ATC;}
	bool isOnOpenOnClose() const
	{
		switch(m_tifType)
		{
			case TIF_OPG:
			case TIF_ATC:
			return true;

			default:
			return false;
		}
	}

	const bool& HasOnOpenShares() const{return m_hasOnOpenShares;}
	const bool& HasOnCloseShares() const{return m_hasOnCloseShares;}

	virtual bool CanBeDQuote() const{return false;}//Only NYSE and AMEX orders
	bool isDQuoteOrder() const;
	bool isOrderDelayedToMarketOpenClose() const{return isOnOpenOnClose() || isCreatedDQuote();}//isDQuoteOrder(); }
	const bool& isCreatedDQuote() const{return m_dQuote;}
	virtual bool isTreatDQuoteAndOnOpenOnCloseAsAggressive() const{return false;}

	virtual unsigned char GetAlgorithmMask() const
	{
		return isAlgorithm() ? 1 << ALGORITHMMASK_YES :
			!m_stopPrice.isZero() || m_stopOrderType != 0 ? 1 << ALGORITHMMASK_STOP :
			m_limitPrice.isZero() ? 1 << ALGORITHMMASK_MARKET : 1 << ALGORITHMMASK_LIMIT;
	}

	unsigned char GetVisibleSizeMask() const{return m_displayQuantity == 0 ? 1 << VSM_HIDDEN : 1 << VSM_VISIBLE;}

	unsigned char GetOddLotMask() const{return m_oddLot ? 1 << OLM_ODDLOT : 1 << OLM_EVENLOT;}

	unsigned int GetTifMask() const
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

			case TIF_GTC:
			return 1 << TIFMASK_GTC;

			case TIF_GTT:
			return 1 << TIFMASK_GTT;

			default:
			return 1 << TIFMASK_OTHER;
		}
	}

	virtual bool isPostponed() const{return false;}
	virtual void Postpone(const bool postpone){}
	virtual void Fire(){}
	virtual bool CanBeFired() const{return false;}
	virtual bool isWaiting() const{return isPostponed();}

	static bool CanTifBeConvertedToGtc(const unsigned char& tifType)
	{
		switch(tifType)
		{
			case TIF_GTX:
			case TIF_DAY:
			return true;
		}
		return false;
	}
	virtual bool CanBeMadeGtc() const{return CanTifBeConvertedToGtc(m_tifType);}
	virtual bool isGtc() const{return TIF_GTC == m_tifType;}

	unsigned int GetOriginalDateCreated() const;//{return m_gtcDateCreated ? m_gtcDateCreated : todaysDate;}
	const unsigned int& GetOriginalTimeCreated() const{return m_gtcTimeCreated ? m_gtcTimeCreated : m_timeCreated;}
	const unsigned int& GetTimeToActivate() const{return m_timeToActivate;}
	const unsigned int& GetGtcDateCreated() const{return m_gtcDateCreated;}
	const unsigned int& GetGtcTimeCreated() const{return m_gtcTimeCreated;}
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

	const bool& isReplacingNatively() const{return m_replacingNatively;}
	const bool& isOpening() const{return m_opening;}
	const bool& isDma() const{return m_dma;}

	OrderDirection GetOrderPositionDirection() const;
	OrderDirection GetOrderDirection() const
	{
		return isDead() || !HasDirection() ? ODIR_NONE : GetOrderPositionDirection();
	}

	unsigned char GetOrderDirectionMask() const{return 1 << GetOrderDirection();}
	bool OrderDirectionBelongsToMask(const unsigned char directionMask) const
	{
		return ((1 << GetOrderPositionDirection()) & directionMask) != 0 || !HasDirection();
	}


	const OrderDirection& GetInitialOrderDirection() const{return m_initialOrderDirection;}
	const unsigned char& GetInitialOrderDirectionMask() const{return m_initialOrderDirectionMask;}

	const bool& isBlocked() const{return m_blocked;}
	const bool& isSupervisorAutoClose() const{return m_supervisorAutoClose;}
	const bool& isFromExtension() const{return m_fromExtension;}

	const bool& isImbalanceOnly() const{return m_imbalanceOnly;}
//	const bool& isProactive() const{return m_proactive;}
	const bool& isNonCancelable() const{return m_nonCancelable;}
	const bool& isIso() const{return m_iso;}
	const bool& isAggressive() const{return m_aggressive;}
	const Price& GetAveragePrice() const{return m_averagePrice;}
	const Money& GetBpUsed() const{return m_bpUsed;}
	const Money& GetBpBetaUsed() const{return m_bpBetaUsed;}
	const Money& GetMeUsed() const{return m_meUsed;}

	virtual bool isNonCancelableByTrader() const{return m_nonCancelable;}//Supervisor is allowed to cancel the order
	virtual unsigned int GetCancelCutoffTime() const{return 0;}
	virtual bool isTooLateToCancel() const;
/*
	unsigned char IllegalOrderCanNotBeCanceled() const
	{
		return isTooLateToCancel() ? CE_TOO_LATE:
			isDropcopy() ? CE_DROPCOPY_ORDER:
			isNonCancelableByTrader() ? CE_NON_CANCELABLE:
			CE_OK;
	}
	unsigned char CanNotBeCanceled() const
	{
		switch(isBeingCanceled())
		{
			case CIP_CANCEL:
			return CE_CANCEL_ALREADY_SENT:

			case CIP_REPLACE:
			return CE_REPLACE_ALREADY_SENT:

			default:
			return IllegalOrderCanNotBeCanceled();
		}
//		return isBeingCanceled() ? CE_CANCEL_ALREADY_SENT:
//			IllegalOrderCanNotBeCanceled();
	}
*/
	unsigned char ShouldCancelBeBlocked() const
	{
		return isDropcopy() ? CE_DROPCOPY_ORDER :
			isNonCancelableByTrader() ? CE_NON_CANCELABLE :
			CE_OK;
	}
	unsigned char CanNotBeCanceled() const
	{
		return isTooLateToCancel() ? CE_TOO_LATE : ShouldCancelBeBlocked();
	}
	unsigned char IllegalOrderCanNotBeCanceled() const
	{
		return CanNotBeCanceled();
/*
			isTooLateToCancel() ? CE_TOO_LATE:
			isDropcopy() ? CE_DROPCOPY_ORDER:
			isNonCancelableByTrader() ? CE_NON_CANCELABLE:
			CE_OK;
*/
	}
	bool isSlow() const;//D-Quote ordes are slow
	bool ShouldIllegalOrderBeCanceled() const;
//	{
//		return !IllegalOrderCanNotBeCanceled() && !isSlow();
//	}
	bool ShouldRtcOrderBeCanceled() const;

	const Money& GetMoneyExecuted() const{return m_moneyExecuted;}

	const unsigned int& GetStockLatestClosePriceCompact() const{return m_stockLatestClosePriceCompact;}
	const int& GetOrderNetPercentCompact() const{return m_orderNetPercentCompact;}//(Order Price - Close Price)/Close Price  * 100%

	const Money& GetClosedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnl() : m_closedPnl;}
	const Money& GetClosedPnlCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlCost() : m_closedPnlCost;}
	const Money& GetPositionMarkedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPositionMarkedPnl() : m_positionMarkedPnl;}
	const Money& GetAccountMarkedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAccountMarkedPnl() : m_accountMarkedPnl;}
	const Money& GetPositionClosedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPositionClosedPnl() : m_positionClosedPnl;}
	const Money& GetAccountClosedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAccountClosedPnl() : m_accountClosedPnl;}
	const int& GetPositionSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPositionSize() : m_positionSize;}
	const int& GetDynamicPositionSizeInv(const bool& inventoryView) const;
	const int& GetDynamicPositionSizeOrZeroForDeadInv(const bool& inventoryView) const{return isDead() ? intZero : GetDynamicPositionSizeInv(inventoryView);}
	const unsigned int& GetPositionAveragePriceInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPositionAveragePrice() : m_positionPrice;}
	const unsigned int& GetClosedSharesInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedShares() : m_closedShares;}

	const ExecutionMap& GetExecutionMap() const{return m_executionMap;}

//	const OrderState& GetOrderState() const{return m_orderState;}
	const unsigned char& GetOrderState() const{return m_orderState;}
	const std::string& GetOrderStateStr() const;
	virtual const std::string& GetStopOrderTypeStr() const;
	virtual const std::string& GetStopOrderBaseStr() const;

	const std::string& GetMarketReferenceId() const{return m_marketReferenceId;}

	unsigned char Cancel();
	const bool& isCancelSolicited() const{return m_cancelSolicited;}//Order is dead after cancel wa requested (by this instance of Takion or another instance)
	const unsigned char& isBeingCanceled() const{return m_beingCanceled;}
	const bool& isReplaceDone() const{return m_replaceDone;}
	const bool& isReplacedDone() const{return m_replacedDone;}
	bool isDead() const{return m_orderState == TU_OS_DEAD;}
	const bool& isKicked() const{return m_kicked;}
	const bool& isDeleted() const{return m_deleted;}

	virtual unsigned char ReplacePriceAndSize(unsigned int* const& sendId,//output parameter; can be NULL
		const bool& replaceNative,
		const bool& marketOrder,
		const SignedPrice& replacePriceOffset,
		const bool& replacePriceOffsetPercent,
		const int& replaceSizeOffset,
		const bool& preBorrow,
		const Price& preBorrowPrice,
		const unsigned __int64& userId,
		const unsigned char& displaySizeMode,//0 - size fraction, 1 - round lot, 2 - no change
		const unsigned int& displaySize,
		const unsigned int& displaySizeFraction,
		const unsigned int& remainingSize = 0){return OE_OK;}// = 0;

	const unsigned char& GetPegType() const{return m_pegType;}
	const SignedPrice& GetPegOffset() const{return m_pegOffset;}

	const bool& isPreBorrow() const{return m_preBorrow;}
	const Price& GetBorrowPrice() const{return m_borrowPrice;}

	const unsigned __int64& GetAverageDailyVolume() const{return m_averageDailyVolume;}
	const unsigned __int64& GetYesterdaysVolume() const{return m_yesterdaysVolume;}
	const unsigned __int64& GetTodaysVolume() const{return m_todaysVolume;}

	const unsigned short& GetRejectCode() const{return m_rejectCode;}
	const unsigned short& GetCancelRejectCode() const{return m_cancelRejectCode;}

	const char* const& GetRejectText() const{return m_rejectText;}
	const char* const& GetCancelRejectText() const{return m_cancelRejectText;}

//	void SetBeingCanceled(const unsigned char& canceled){m_beingCanceled = canceled;}
//	void SetDeleted(){m_deleted = true;}
	virtual void EndAlgorithm()
	{
		m_deleted = true;
	}
	virtual void EndAlgorithmInThread(){}

	const char& GetOrigin() const{return m_origin;}
	const bool& isDropcopy() const{return m_dropcopy;}
	const bool& isBorrow() const{return m_borrow;}
	const bool& isCloseOnly() const{return m_closeOnly;}
	const bool& isResizeToClose() const{return m_resizeToClose;}
//	const bool& isProAts() const{return m_proAts;}
//	virtual bool isOrderNight() const;
	const bool& isOrderNight() const{return m_nightOrder;}
	const bool& isOddLot() const{return m_oddLot;}
	const bool& isOddLotCreated() const{return m_oddLotCreated;}
	const bool& isNotSent() const{return m_notSent;}
	const unsigned int& GetRoundLot() const{return m_roundLot;}

	const unsigned int& GetRoutingName() const{return m_routingName;}
	const unsigned short& GetRoutingId() const{return m_routingId;}
	const unsigned short& GetRoutingSubType() const{return m_routingSubType;}
	const unsigned int& GetMnemonic() const{return m_mnemonic;}
	const unsigned int& GetRealMnemonic() const{return m_realMnemonic;}

	const bool& isDeadNotified() const{return m_deadNotified;}
	void SetDeadNotified(const bool& notified){m_deadNotified = notified;}//don't call this function

	const bool& isMonitorTif() const{return m_monitorTif;}

	const bool& isNoMassCancel() const{return m_noMassCancel;}
	void SetNoMassCancel(const bool& noMassCancel){m_noMassCancel = noMassCancel;}

	const unsigned char& GetProblemFlags() const{return m_problemFlags;}

	bool isCancelRejected() const{return (m_problemFlags & (1 << OP_CANCEL_REJECTED)) != 0;}
	bool isCancelBlocked() const{return (m_problemFlags & (1 << OP_CANCEL_BLOCKED)) != 0;}

	bool isStuck() const{return (m_problemFlags & (1 << OP_STUCK)) != 0;}
	virtual void WriteStuckToAccountThread(bool stuck){}
	virtual void WriteOrderCancelToMainThread(bool deleteUntradedPosition = false){}
//	virtual void WriteOrderUpdateMessageToMainThread(unsigned int pendingShares, bool killed, bool rejected, unsigned char flags){}//1 - cancelAck, 2 - loaded order updated with an execution
	virtual void WriteOrderUpdateMessageToMainThread(unsigned int pendingShares, bool rejected, unsigned char flags, unsigned char orderState) const{}//enum OrderState
	void NotifyInThreadObservers(const Message* message, const Message* info = NULL) const//should be called only from the worker thread
	{
		m_lockInThreadObservable.LockWait();
		m_inThreadObservable.NotifyObservers(message, info, this);
		m_lockInThreadObservable.Unlock();
	}
#ifndef TAKION_NO_OPTIONS
	virtual const OptionSymbolBlock* GetOptionSymbolBlock() const;
	virtual const unsigned short& GetOptionType() const;
//	virtual OptionSymbolBlock* GetOptionSymbolBlock();
	virtual const unsigned __int64& GetOptionBlock() const;
	virtual const unsigned __int64& GetUnderlierNumericSymbol() const;
	virtual bool isCall() const;
	virtual unsigned char GetSuffix() const;
	virtual unsigned char GetCallPutFlags() const;
	virtual const unsigned char& GetOptionFlags() const;
	virtual const unsigned int& GetStrikePrice() const;
	virtual unsigned int GetExpirationDate() const;
	virtual const unsigned char& GetExpirationType() const;
	virtual const unsigned int& GetExpirationDays() const;
	virtual const char& GetExpirationTypeChar() const;
	virtual void GetOptionBlockAsString(std::string& optionSymbol, bool suffixSeparate) const;
	virtual void GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const;
	virtual const unsigned int& GetContractSize() const;

	unsigned char GetInstrumentMask() const{return 1 << GetSecurityType();}
#endif
	const ExecutionOrderInventory* GetInventory() const{return m_inventory;}

	TakionIterator* CreateExecutionIterator() const;//call iterator->Reset() before using. Enclose the usage in locking. Call GetNextExecution to iterate until it returns NULL; Call delete iterator when no longer needed.
	static Execution* GetNextExecution(TakionIterator* iterator);//Enclose the usage in locking

	virtual void SecurityUpdate(){}//used in OrderAlgorithm
	virtual void InThreadUpdate(unsigned short code, unsigned short eventCode){}//used in OrderAlgorithm

	bool isOrderReplacementSame(const Order& other) const;

	bool UpdateBetaBpUsed();

	void UpdateMeUsed();

	Price CalculateQuotePrice() const;

	unsigned __int64 CalculateOrderSynchKey() const{return ((unsigned __int64)GetClientId() << 32) | GetTimeCreated();}

	Order& operator=(const Order& other);
protected:
	Order(const Position* position,
		unsigned int timeToActivate,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		unsigned int sendId,
		unsigned int splitParentClientId,
		unsigned int splitChildClientId,
		unsigned int ipSentFrom,
		unsigned int traderId,
		unsigned int clientId,
		unsigned int clientIdOriginal,
		unsigned int clientIdChronological,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
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
		const Price& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,
//		const Price& stockClosePrice,
		unsigned int stockLatestClosePrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		unsigned int maxDisplayQuantity,
		unsigned int minDisplayQuantity,

		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,

		unsigned int mnemonic,

		bool replacingNatively,
		bool opening,
		bool dma,
		bool imbalanceOnly,
		bool nonCancelable,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		char origin,
		bool dropcopy,
		bool borrow,
		bool closeOnly,
		bool resizeToClose,
		bool nightOrder,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		unsigned char tifType,
		unsigned char sentTifType,
		unsigned char initialTifType,
		bool monitorTif,
		unsigned int tifMillisecond,
		unsigned int sentTifMillisecond,
		unsigned int filledQuantity,// = 0,
		unsigned int expiredQuantity,// = 0,
		unsigned int canceledQuantity,// = 0,
		unsigned int rejectedQuantity,// = 0,
		unsigned int parentId,// = 0,
		unsigned int replacedClientId,
		const unsigned __int64& userId,
		bool blocked,
		bool supervisorAutoClose,
		bool fromExtension);// = 0);
	Order(const Order& other);
/*
	char m_symbol[16];
	unsigned __int64 m_numericSymbol;
	SecurityType m_securityType;
	Account* m_account;
*/
#ifndef TAKION_NO_OPTIONS
	void AdjustOptionShortMeUsed();
#endif
	void UpdateQuotePrice();
	void UpdateOrderNetPercent();//LockModification

	void SetBeingCanceled(const unsigned char& canceled){m_beingCanceled = canceled;}
	void SetDeleted(){m_deleted = true;}
	void SetCancelTime(){if(!m_timeCancelCreated && m_origin != OO_HISTORICAL)m_timeCancelCreated = TL_GetCurrentMillisecond();}
	void UnsetCancelTime(){m_timeCancelCreated = 0;}

	virtual void UpdateMarketDataEntitlements(){}//Called only from account thread

	bool MakeGtc(bool gtc){return (gtc ? CanBeMadeGtc() : isGtc()) && DoMakeGtc(gtc);}
	virtual bool DoMakeGtc(bool gtc);
	void AddOrderValues(const unsigned int quantity);

	bool UpdateTrailingStopPrice(const Price& currentPrice, const Price& basePrice, const Message* message);
	bool UpdatePrintTrailingStopPrice(const Price& printPrice, const Message* const& message)
	{
		return OSB_PRINT == m_stopOrderBase && UpdateTrailingStopPrice(printPrice, m_lastPrintPrice, message);
	}
	bool UpdateLevel1TrailingStopPrice(const Price& bid,
		const Price& ask,
		const unsigned char& sideMask,//1 bid, 2 ask, 3 both
		const Message* const& message)
	{
		switch(m_stopOrderBase)
		{
			case OSB_BID:
			if(sideMask & 1)
			{
				return UpdateTrailingStopPrice(bid, 'B' == m_side ? m_level1SameSidePrice : m_level1Price, message);
			}
			break;

			case OSB_ASK:
			if(sideMask & 2)
			{
				return UpdateTrailingStopPrice(ask, 'B' == m_side ? m_level1Price : m_level1SameSidePrice, message);
			}
			break;

			case OSB_MIDPOINT:
			return UpdateTrailingStopPrice((bid + ask) / 2, (m_level1SameSidePrice + m_level1Price) / 2, message);
			break;
		}
		return false;
	}
	void SetInventoryPositionSize(const int& inventorySize);
	void SetInventoryClosedPnl(const Money& closedPnl, const Money& closedPnlCost, const unsigned int& closedShares);
	void AddInventoryClosedPnl(const Money& closedPnl, const Money& closedPnlCost, const unsigned int& closedShares);
	void SetInventoryPositionMarkedPnl(const Money& markedPnl, const Money& closedPnl);
	void SetInventoryAccountMarkedPnl(const Money& markedPnl, const Money& closedPnl);

	Observable m_inThreadObservable;
	TakionLockSingleThreadAccess m_lockInThreadObservable;

	const Position* m_position;

	unsigned int m_sendId;
	unsigned int m_splitParentClientId;
	unsigned int m_splitChildClientId;

	unsigned int m_ipSentFrom;
	unsigned int m_ipCancelFrom;
	unsigned int m_traderId;
	unsigned int m_clientId;
	unsigned int m_clientIdOriginal;
	unsigned int m_clientIdChronological;
	unsigned int m_serverId;
	unsigned int m_parentId;
	unsigned int m_replacedClientId;
	unsigned int m_replacedByClientId;
	unsigned int m_replacedBySendId;
	unsigned __int64 m_userId;
	unsigned __int64 m_destinationId;

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
	Price m_stopPrice;
	Price m_initialStopPrice;

	Price m_level1Price;
	Price m_level1SameSidePrice;
	Price m_lastPrintPrice;

	Price m_pricePerShare;

//	Price m_stockClosePrice;
//	SignedPrice m_orderNetPercent;//(Order Price - Close Price)/Close Price  * 100%

	unsigned int m_stockLatestClosePriceCompact;
	int m_orderNetPercentCompact;//(Order Price - Close Price)/Close Price  * 100%

/*
	Money m_closedPnl;
	Money m_closedPnlCost;
	Money m_positionMarkedPnl;
	Money m_accountMarkedPnl;
	Money m_positionClosedPnl;
	Money m_accountClosedPnl;
	Price m_positionPrice;
	int m_positionSize;
*/
	bool SetOco(const unsigned int& ocoId)
	{
		if(ocoId != m_ocoId)
		{
			m_ocoId = ocoId;
//			WriteOrderUpdateMessageToMainThread(GetReplacingQuantity(), false, false, 0);
			WriteOrderUpdateMessageToMainThread(GetReplacingQuantity(), false, 0, TU_OS_COUNT);//GetOrderState()
			return true;
		}
		return false;
	}
	unsigned int m_ocoId;
	unsigned int m_quantity;
	unsigned int m_displayQuantity;
	unsigned int m_reserveQuantity;

	unsigned int m_maxDisplayLimit;
	unsigned int m_maxDisplayQuantity;

	unsigned int m_minDisplayLimit;
	unsigned int m_minDisplayQuantity;

	unsigned int m_filledQuantity;
	unsigned int m_inheritedFilledQuantity;
	unsigned int m_canceledQuantity;
	unsigned int m_expiredQuantity;
	unsigned int m_rejectedQuantity;

	unsigned int m_pendingQuantity;
	unsigned int m_pendingQuantityInitial;

	unsigned int m_remainingQuantityInitialFromServer;

	unsigned int m_quantityBeingCanceled;

	unsigned int m_quantityLastKilled;

	unsigned char m_tifType;
	unsigned char m_sentTifType;
	bool m_monitorTif;
	bool m_noMassCancel;
	unsigned int m_tifMillisecond;
	unsigned int m_sentTifMillisecond;
	unsigned int m_timeToActivate;
	unsigned int m_gtcDateCreated;
	unsigned int m_gtcTimeCreated;
	unsigned int m_timeCreated;
	unsigned int m_timeToExpire;
	unsigned int m_timeSent;
	unsigned int m_timeAcknowledged;
	unsigned int m_timeOnMarket;
	unsigned int m_timeCancelCreated;
	unsigned int m_timeCancelSent;
	unsigned int m_timeCancelAcknowledged;
	unsigned int m_timeDead;
	unsigned int m_lastExecutionTime;

	unsigned int m_timeAcknowledgedReceived;
	unsigned int m_timeOnMarketReceived;
	unsigned int m_timeCancelAcknowledgedReceived;
	unsigned int m_timeCancelRejectReceived;
	unsigned int m_timeDeadReceived;
	unsigned int m_roundLot;

	unsigned int m_mnemonic;
	unsigned int m_realMnemonic;
	unsigned int m_routingName;
	unsigned short m_routingId;
	unsigned short m_routingSubType;

	short m_serverDelay;
	short m_marketDelay;

	std::string m_marketReferenceId;

//	bool m_stuck;
//	bool m_proactive;

	unsigned char m_initialTifType;
	OrderDirection m_initialOrderDirection;
	unsigned char m_initialOrderDirectionMask;

	unsigned char m_orderState;
//	OrderState m_orderState;

	unsigned char m_problemFlags;
//	bool m_postponed;
	bool m_deadNotified;
	bool m_replacingNatively;
	bool m_opening;
	bool m_dma;
	bool m_dQuote;
	bool m_passive;
	bool m_imbalanceOnly;
	bool m_blocked;
	bool m_supervisorAutoClose;
	bool m_fromExtension;
	bool m_nonCancelable;
	bool m_iso;
	bool m_aggressive;
	bool m_cancelSolicited;
	unsigned char m_beingCanceled;
	bool m_replaceDone;//this replacing order successfully replaced another order
	bool m_replacedDone;//this order being replaced is successfully replaced by another order
	bool m_kicked;
	bool m_deleted;
	bool m_oddLot;
	bool m_oddLotCreated;
	char m_origin;
	bool m_dropcopy;
	bool m_borrow;
	bool m_closeOnly;
	bool m_resizeToClose;
//	bool m_proAts;
	bool m_nightOrder;
	bool m_notSent;
	bool m_hasOnOpenShares;
	bool m_hasOnCloseShares;
	unsigned char m_pegType;
//For GTC orders, to recreate them with or without preBorrow
	bool m_preBorrow;
	Price m_borrowPrice;
//
	SignedPrice m_pegOffset;

	bool SetQuotePrice(const Price& quotePrice);
	Price m_quotePrice;//for displaying the order among quotes in the MmBox

	Price m_averagePrice;

	void AddBp(const Money& bp);//{m_bpUsed += bp;}
	Money m_bpUsed;

//	void AddBpBeta(const Money& bp){m_bpBetaUsed += bp;}//done in AddBp
	Money m_bpBetaUsed;

//	void AddMe(const Money& me){m_meUsed += me;}//done in AddBp
	Money m_meUsed;

	Money m_moneyExecuted;

	unsigned __int64 m_averageDailyVolume;
	unsigned __int64 m_yesterdaysVolume;
	unsigned __int64 m_todaysVolume;

	unsigned int m_level1PriceCompact;
	unsigned int m_quotePriceCompact;
	unsigned int m_stopPriceCompact;

	unsigned short m_rejectCode;
	unsigned short m_cancelRejectCode;

	char* m_rejectText;
	char* m_cancelRejectText;

	char* m_userOrderInfo;

	ExecutionOrderInventory* m_inventory;

	ExecutionMap m_executionMap;
/*
private:
	Order(const Order& other);
	Order& operator=(const Order& other);
*/
};

struct lessOrderReplace : public std::binary_function<Order*, Order*, bool>
{
	bool operator()(const Order* const& o1, const Order* const& o2) const
	{
		const char side1 = o1->GetSide();
		const char side2 = o2->GetSide();
		const bool buy2 = side2 == 'B';
		const Price& price2 = o2->GetQuotePrice();
		return (side1 == 'B') != buy2 ? buy2 ://sell/short side first
			(side1 == 'S') != (side2 == 'S') ? side2 == 'S' ://short orders before sell orders
			o1->GetQuotePrice() == price2 ? o1->GetClientId() < o2->GetClientId() :
			buy2 ? o1->GetQuotePrice() < price2 ://less aggressive orders first
			o1->GetQuotePrice() > price2 || price2.isZero();//less aggressive orders first
	}
};

typedef std::set<Order*, lessOrderReplace> OrderReplaceSet;

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
		Quote::SetEmpty();
//		SetZero();
//		m_quantity = 0;
		m_paintDelay = 0;
		m_displayPriceDollar = 0;
		m_displayPriceFraction = 0;
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
	virtual unsigned char GetCondition() const override{return m_quoteCondition;}
	virtual bool GetRetailLiquidity() const override{return m_retailLiquidity;}
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
		m_stop(false),
		m_hidden(false),
		m_postponed(false),
		m_gtc(false),
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
		m_stop(order.isStopOrder()),
		m_hidden(!order.GetDisplayQuantity()),
		m_postponed(order.isPostponed()),
		m_gtc(order.isGtc()),
		m_attributed(false),
		m_quoteId(order.GetClientId())
	{
//		m_historical = order.GetOrigin() == OO_HISTORICAL;
//		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
	DisplayQuote(unsigned int mmid, const Price& price, bool bid, unsigned int millisecond, short delay, bool historical, unsigned int fractionDollar, unsigned int fractionDivider, COLORREF color):
		DisplayGreenie(bid, price, 0, BOOK_LEVEL2, mmid, millisecond, delay, historical, fractionDollar, fractionDivider),
		m_color(color),
		m_direct(true),
		m_order(0),
		m_stop(false),
		m_hidden(false),
		m_postponed(false),
		m_gtc(false),
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
		m_order(0),
		m_stop(false),
		m_hidden(false),
		m_postponed(false),
		m_gtc(false),
		m_attributed(false),
		m_quoteId(0)
	{}
	virtual bool isEmpty() const override{return DisplayGreenie::isEmpty() && !m_order;}
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
		m_stop = false;

		m_order = '\0';//false;
//		m_hidden = false;
//		m_attributed = false;
//////////
		m_color = 0;
//		m_quoteCondition = '\0';
		m_direct = false;
	}
	bool EqualPriceSideIdStopAndDestination(const DisplayQuote& other) const
	{
		return EqualPriceSideAndDestination(other) && m_quoteId == other.m_quoteId && m_stop == other.m_stop && m_order == other.m_order;
	}
	void SetPriceSideIdStopAndDestination(const DisplayQuote& other)
	{
		SetPriceSideAndDestination(other);
		m_quoteId = other.m_quoteId;
		m_stop = other.m_stop;
		m_order = other.m_order;
	}

	void SetHasOrders(const bool& hasOrders){if(m_order != 1)m_order = hasOrders ? 2 : 0;}
	void SetHidden(const bool& hidden){m_hidden = hidden;}
	void SetStop(const bool& stop){m_stop = stop;}
	void SetPostponed(const bool& postponed){m_postponed = postponed;}
	void SetGtc(const bool& gtc){m_gtc = gtc;}
	void SetAttributed(const bool& attributed){m_attributed = attributed;}
	void SetQuoteId(const quoteid& id){m_quoteId = id;}
	quoteid GetQuoteId() const{return m_quoteId;}
	COLORREF GetColor() const{return m_color;}
	void SetColor(const COLORREF& color){m_color = color;}
	inline void SetQuote(const Quote& quote, const unsigned int& fractionDollar, const unsigned int& fractionDivider, const unsigned char& orderMode, const bool& stop, const bool& hidden)
	{
		DisplayGreenie::SetQuote(quote, fractionDollar, fractionDivider);
		m_direct = quote.isDirect();
		m_quoteId = quote.GetId();
		m_order = orderMode;//quote.GetOrder();
		m_stop = stop;
		m_hidden = hidden;
		m_postponed = false;
		m_gtc = false;
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
		m_stop = order.isStopOrder();
		m_hidden = !order.GetDisplayQuantity();
		m_postponed = order.isPostponed();
		m_gtc = order.isGtc();
		m_attributed = false;
		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
	inline void SetMmid(unsigned int mmid, const Price& price, bool bid, unsigned int millisecond, short delay, bool historical, const unsigned int& fractionDollar, const unsigned int& fractionDivider)
	{
		Price::operator=(price);
		m_quantity = 0;
		m_millisecond = millisecond;
		m_bid = bid;
		m_mmid = mmid;
		m_bookId = BOOK_LEVEL2;
		m_delay = delay;
		m_historical = historical;
		m_quoteCondition = '\0';
		m_retailLiquidity = false;
		m_direct = true;
		m_quoteId = 0;
		m_order = 0;
		m_stop = false;
		m_hidden = false;
		m_postponed = false;
		m_gtc = false;
		m_attributed = false;
		CalculateDisplayPrice(fractionDollar, fractionDivider);
	}
	bool isQuoteProper() const
	{
		return m_order != 1
#ifdef LRPS
			&& m_mmid != lrpNum
#endif
			&& m_mmid != luldNum;
	}
	bool SamePriceMmidColor(const DisplayQuote& other) const
	{
		return m_displayPriceDollar == other.m_displayPriceDollar
			&& m_displayPriceFraction == other.m_displayPriceFraction
			&& m_mmid == other.m_mmid
			&& m_color == other.m_color
			&& m_direct == other.m_direct
			&& m_order == other.m_order
			&& m_hidden == other.m_hidden
			&& m_stop == other.m_stop
			&& m_postponed == other.m_postponed
			&& m_gtc == other.m_gtc
			&& m_attributed == other.m_attributed
			&& m_bookId == other.m_bookId;
	}
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
		m_stop = quote.isStop();
		m_postponed = false;
		m_gtc = false;
		m_attributed = quote.isAttributed();
//		m_bookId = quote.GetBookId();
	}
	void SetOrderQuantity(const Order& order)
	{
		m_quantity = order.GetPendingQuantity();
		m_order = 1;//true;
		m_stop = order.isStopOrder();
		m_hidden = !order.GetDisplayQuantity();
		m_postponed = order.isPostponed();
		m_gtc = order.isGtc();
		m_attributed = false;
		m_quoteCondition = '\0';
		m_retailLiquidity = false;
//		m_direct = false;
	}
	unsigned int GetOrderId() const{return m_order == 1 ? (unsigned int)m_quoteId : 0;}
//	virtual char GetCondition() const{return m_quoteCondition;}
	virtual bool isAttributed() const override{return m_attributed;}
	virtual bool isDirect() const override{return m_direct;}
	virtual quoteid GetId() const override{return m_quoteId;}
	virtual unsigned char GetOrder() const override{return m_order;}
	virtual bool isStop() const override{return m_stop;}
	virtual bool isHidden() const override{return m_hidden;}
	virtual bool isPostponed() const override{return m_postponed;}
	virtual bool isGtc() const override{return m_gtc;}
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
	bool m_stop;
	bool m_hidden;
	bool m_postponed;
	bool m_gtc;
	bool m_attributed;
	quoteid m_quoteId;
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

/*
struct lessStopAndLimitOrderPrice : public std::binary_function<Order*, Order*, bool>
{
	bool operator()(const Order* const& o1, const Order* const& o2) const
	{
		return
			o1->isStopOrder() != o2->isStopOrder() ? o1->isStopOrder():

			o1->GetQuotePrice() == o2->GetQuotePrice() ? o1->GetClientId() < o2->GetClientId():

			o1->GetQuotePrice().isZero() || !o2->GetQuotePrice().isZero() && o2->GetQuotePrice() < o1->GetQuotePrice();
	}
};

struct greaterStopAndLimitOrderPrice : public std::binary_function<Order*, Order*, bool>
{
	bool operator()(const Order* const& o1, const Order* const& o2) const
	{
		return
			o1->isStopOrder() != o2->isStopOrder() ? o1->isStopOrder():

			o1->GetQuotePrice() == o2->GetQuotePrice() ? o1->GetClientId() < o2->GetClientId():

//			o1->GetQuotePrice().isZero() || !o2->GetQuotePrice().isZero() && o1->GetQuotePrice() < o2->GetQuotePrice();
			o1->GetQuotePrice() < o2->GetQuotePrice();
	}
};
*/
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

class TU_API BasePosition : public TakionLock
{
public:
	virtual ~BasePosition(){}

	const char* GetSymbol() const{return (const char*)&m_numericSymbol;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}

	const Security* const& GetSecurity() const{return m_security;}//safe to call only from main thread
	const Security* const& GetSortableSecurity() const{return m_sortableSecurity;}//safe to call only from main thread
	const Security* const& GetSecurity(const bool& subscribable) const{return subscribable ? m_security : m_sortableSecurity;}//safe to call only from main thread
	const Security* const& GetASecurity() const{return m_security ? m_security : m_sortableSecurity;}//safe to call only from main thread
#ifndef TAKION_NO_OPTIONS
	const Security* const& GetUnderlierSecurity() const{return m_underlierSecurity;}//safe to call only from main thread
	const Security* const& GetUnderlierSortableSecurity() const{return m_underlierSortableSecurity;}//safe to call only from main thread
	const Security* const& GetUnderlierSecurity(const bool& subscribable) const {return subscribable ? m_underlierSecurity : m_underlierSortableSecurity;}//safe to call only from main thread
	const Security* const& GetAUnderlierSecurity() const {return m_underlierSecurity ? m_underlierSecurity : m_underlierSortableSecurity;}//safe to call only from main thread
#endif
	virtual void WritePositionUpdateMessageToMainThread(unsigned char execution) const{}
	virtual void WriteMessageToPositionThread(const Message* message) const{}

	bool isNewPosition() const{return m_newPosition;}
	virtual unsigned int GetThreadId() const{return 0;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}
	virtual void Reset();
protected:
	BasePosition(const char* symbol);

//	virtual void SecuritySet(){}
//	virtual void SortableSecuritySet(){}
////
	void SetSecurity(const Security* const& security)
	{
		m_security = security;
	}
	void SetSortableSecurity(const Security* const& security)
	{
		m_sortableSecurity = security;
	}
	void SetSecurity(const bool& subscribable, const Security* const& security)
	{
		if(subscribable)SetSecurity(security);
		else SetSortableSecurity(security);
	}

	unsigned __int64 m_numericSymbol;
//	SecurityType m_securityType;
	const Security* m_security;
	const Security* m_sortableSecurity;
#ifndef TAKION_NO_OPTIONS
	void SetUnderlierSecurity(const Security* const& security)
	{
		m_underlierSecurity = security;
	}
	void SetUnderlierSortableSecurity(const Security* const& security)
	{
		m_underlierSortableSecurity = security;
	}
	void SetUnderlierSecurity(const bool& subscribable, const Security* const& security)
	{
		if(subscribable)SetUnderlierSecurity(security);
		else SetUnderlierSortableSecurity(security);
	}
	const Security* m_underlierSecurity;
	const Security* m_underlierSortableSecurity;
#endif
	bool m_newPosition;
//////
};

#ifdef FIRM_VALUES

class AccountAggregator;

class TU_API FirmPosition : public BasePosition//public Observable, public TakionLock
{
friend class Position;
public:
	static const int intZero;
	static const int intMinusOne;
	static const int intPlusOne;

	virtual ~FirmPosition();

	typedef CMap<const Account*, const Account* const&, Position*, Position* const&> PositionMap;

//	virtual void Destroy(){}
	const AccountAggregator* GetAccountAggregator() const{return m_accountAggregator;}
	const bool& isLoaded() const{return m_loaded;}
	const unsigned int& GetSubscriptionCount() const{return m_subscriptionCount;}

	const short& GetAdvDelay() const{return m_advDelay;}
	const unsigned int& GetAdvTimeStamp() const{return m_advTimestamp;}
	const unsigned int& GetAdvLoadedTimeStamp() const{return m_advLoadedTimestamp;}

	const char* GetClearingFirmName() const;
	const char* GetFirmName() const;
	const unsigned int& GetFirmNumericName() const;
	const short& GetDelay() const{return m_delay;}
	const unsigned int& GetTimeStamp() const{return m_timestamp;}
	const unsigned int& GetLoadedTimeStamp() const{return m_loadedTimestamp;}
	virtual unsigned int GetThreadId() const;

	const unsigned short& GetRejectCode() const{return m_rejectCode;}
	const char* const& GetRejectText() const{return m_rejectText;}

	const unsigned char& GetUntradeable() const{return m_untradeable;}
	virtual void Reset(){}

	bool LockInquiryPositionMap() const{return m_lockPositionMap.LockInquiry();}
	void LockInquiryWaitPositionMap() const{m_lockPositionMap.LockInquiryWait();}
	void UnlockInquiryPositionMap() const{m_lockPositionMap.UnlockInquiry();}
	const PositionMap& GetPositionMap() const{return m_positionMap;}//lock/unlock

	const int& GetMainThreadSize() const{return m_mainThreadSize;}
	const int& GetMainThreadPotentialShortSize() const{return m_mainThreadPotentialShortSize;}
	const unsigned char& GetMainThreadUntradeable() const{return m_mainThreadUntradeable;}
protected:
	FirmPosition(const AccountAggregator* accountAggregator, const char* symbol):
		BasePosition(symbol),
		m_accountAggregator(accountAggregator),
		m_subscriptionLock(0),
		m_subscriptionCount(0),
		m_timestamp(0),
		m_advTimestamp(0),
		m_loadedTimestamp(0),
		m_advLoadedTimestamp(0),
		m_delay(0),
		m_advDelay(0),
		m_untradeable(0),//US_TRADEABLE),
		m_loaded(false),
		m_rejectCode(0),
		m_rejectText(NULL),
		m_mainThreadSize(0),
		m_mainThreadPotentialShortSize(0),
		m_mainThreadUntradeable(0)//US_TRADEABLE)
	{
		m_positionMap.InitHashTable(53);
	}
	virtual void Resubscribe() const{}
	virtual bool Subscribe() const{return false;}
	virtual bool Unsubscribe() const{return false;}
	const AccountAggregator* m_accountAggregator;

//	mutable CCriticalSection m_subscriptionCriticalSection;
	volatile LONG m_subscriptionLock;

	unsigned int m_subscriptionCount;
	unsigned int m_timestamp;
	unsigned int m_advTimestamp;
	unsigned int m_loadedTimestamp;
	unsigned int m_advLoadedTimestamp;
	short m_delay;
	short m_advDelay;
	unsigned char m_untradeable;
	mutable bool m_loaded;
	unsigned short m_rejectCode;
	char* m_rejectText;
	
	int m_mainThreadSize;
	int m_mainThreadPotentialShortSize;
	unsigned char m_mainThreadUntradeable;

	TakionLockMultithread m_lockPositionMap;
	PositionMap m_positionMap;
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

class TU_API InventoryData
{
public:
	virtual ~InventoryData(){}

	virtual bool isPreMarket() const{return false;}
	virtual bool isMarketOpen() const{return false;}
	virtual bool isMarketClosedForTheDay() const{return false;}
	virtual unsigned char GetMarketState() const{return MSTATE_MARKET;}

	static const std::string stringZero;
	static const unsigned __int64 uint64Zero;
	static const unsigned int uintZero;
	static const unsigned int uintOne;
	static const unsigned short ushortZero;
	static const unsigned char ucharZero;
	static const char charZero;
	static const bool boolFalse;
	static const bool boolTrue;
	static const int intZero;
	static const int intMinusOne;
	static const int intPlusOne;
	static const char space;

	const unsigned int& GetAbsSize() const{return m_absSize;}//For Account, m_absSize is same as m_absShareSize (Position's m_absShareSize is used to modify Account's m_absSize)
//#ifndef TAKION_NO_OPTIONS
//	const unsigned int& GetAbsShareSize() const{return m_absShareSize;}
//#endif
	const unsigned int& GetAbsOvernightSize() const{return m_absOvernightSize;}

	Money GetOvernightInvestment() const{return m_overnightInvestment;}
	Money GetOvernightInvestmentMe() const{return m_overnightInvestmentMe;}
	Money GetOvernightInvestmentBeta() const{return m_overnightInvestmentBeta;}

//	const Money& GetInventoryInvestment() const{return m_inventoryInvestment;}
//	const Money& GetInventoryNbboPrintOpenPnl() const{return m_inventoryNbboPrintOpenPnl;}

	Money GetInvestment() const{return m_investment;}
	Money GetInvestmentMe() const{return m_investmentMe;}
	Money GetInvestmentBeta() const{return m_investmentBeta;}
	Money GetInvestmentCost() const{return m_investmentCost;}

	const Money& GetMaxInvestment() const{return m_maxInvestment;}
	const Money& GetMaxInvestmentLong() const{return m_maxInvestmentLong;}
	const Money& GetMaxInvestmentShort() const{return m_maxInvestmentShort;}

	const Money& GetMaxInvestmentMe() const{return m_maxInvestmentMe;}
	const Money& GetMaxInvestmentLongMe() const{return m_maxInvestmentLongMe;}
	const Money& GetMaxInvestmentShortMe() const{return m_maxInvestmentShortMe;}

	const Money& GetMaxInvestmentBeta() const{return m_maxInvestmentBeta;}
	const Money& GetMaxInvestmentLongBeta() const{return m_maxInvestmentLongBeta;}
	const Money& GetMaxInvestmentShortBeta() const{return m_maxInvestmentShortBeta;}

	virtual Money GetInvestmentLong() const{return Money::moneyZero;}
	virtual Money GetInvestmentShort() const{return Money::moneyZero;}
	virtual Money GetInvestmentMeLong() const{return Money::moneyZero;}
	virtual Money GetInvestmentMeShort() const{return Money::moneyZero;}
	virtual Money GetInvestmentBetaLong() const{return Money::moneyZero;}
	virtual Money GetInvestmentBetaShort() const{return Money::moneyZero;}
	virtual Money GetInvestmentCostLong() const{return Money::moneyZero;}
	virtual Money GetInvestmentCostShort() const{return Money::moneyZero;}

	virtual const Money& GetInventoryInvestment() const{return Money::moneyZero;}
	virtual const Money& GetInventoryNbboPrintOpenPnl() const{return Money::moneyZero;}

	virtual void Reset()
	{
		m_absSize = 0;
//#ifndef TAKION_NO_OPTIONS
//		m_absShareSize = 0;//Same as m_absSize for stocks; for options = m_absSize * GetContractSize()
//#endif
		m_absOvernightSize = 0;

		m_potentialLongSize = 0;
		m_potentialShortSize = 0;
		m_potentialSize = 0;
		m_potentialLongNightSize = 0;
		m_potentialShortNightSize = 0;
		m_potentialNightSize = 0;
		m_investment.SetZero();
		m_investmentMe.SetZero();
		m_investmentBeta.SetZero();
		m_investmentCost.SetZero();

		m_overnightInvestment.SetZero();
		m_overnightInvestmentMe.SetZero();
		m_overnightInvestmentBeta.SetZero();

//		m_inventoryInvestment.SetZero();
//		m_inventoryNbboPrintOpenPnl.SetZero();

		m_maxInvestment.SetZero();
		m_maxInvestmentLong.SetZero();
		m_maxInvestmentShort.SetZero();

		m_maxInvestmentMe.SetZero();
		m_maxInvestmentLongMe.SetZero();
		m_maxInvestmentShortMe.SetZero();

		m_maxInvestmentBeta.SetZero();
		m_maxInvestmentLongBeta.SetZero();
		m_maxInvestmentShortBeta.SetZero();

		m_potentialLongValue.SetZero();
		m_potentialShortValue.SetZero();
		m_potentialLongMe.SetZero();
		m_potentialShortMe.SetZero();
		m_potentialBetaLongValue.SetZero();
		m_potentialBetaShortValue.SetZero();
		m_potentialLongNightValue.SetZero();
		m_potentialShortNightValue.SetZero();
		m_averagePriceLoadedLong.SetZero();
		m_averagePriceLoadedShort.SetZero();
		m_closedPnl.SetZero();
		m_closedPnlCost.SetZero();
		m_openPnlLevel1Cost.SetZero();
		m_openPnlPrintCost.SetZero();

		m_openPnlLevel1.SetZero();
		m_openPnlLevel1Valid = true;

		m_openPnlPrint.SetZero();
		m_openPnlImbExNear.SetZero();
		m_openPnlTClose.SetZero();
		m_openPnlActionPrint.SetZero();//used for remembering m_openPnlNbboPrint for comparing it with m_openPnlLevel1 later for picking the most optimistic Pnl for m_openPnlAction
		m_openPnlAction.SetZero();
		m_openPnlNbboPrint.SetZero();
		m_openPnlNbboPrintHi.SetZero();
		m_openPnlNbboPrintLo.SetZero();
		m_markedPnlNbboPrint.SetZero();
		m_markedPnlNbboPrintHi.SetZero();
		m_markedPnlNbboPrintLo.SetZero();
		m_openCommissionFee.SetZero();
		m_closedPnlNet.SetZero();

		m_rtEquity.SetZero();
		m_leverage.SetZero();

		m_openPnlNbboPrintPreMarket.SetZero();
		m_openPnlNbboPrintMarket.SetZero();
		m_openPnlNbboPrintPostMarket.SetZero();

		m_closedPnlPreMarket.SetZero();
		m_closedPnlMarket.SetZero();
		m_closedPnlPostMarket.SetZero();

		m_markedPnlNbboPrintPreMarket.SetZero();
		m_markedPnlNbboPrintMarket.SetZero();
		m_markedPnlNbboPrintPostMarket.SetZero();
	}

	const unsigned int& GetPotentialLongSize() const{return m_potentialLongSize;}
	const unsigned int& GetPotentialShortSize() const{return m_potentialShortSize;}
	const unsigned int& GetPotentialSize() const{return m_potentialSize;}//max of m_potentialLongSize and m_potentialShortSize

	const unsigned int& GetPotentialLongNightSize() const{return m_potentialLongNightSize;}
	const unsigned int& GetPotentialShortNightSize() const{return m_potentialShortNightSize;}
	const unsigned int& GetPotentialNightSize() const{return m_potentialNightSize;}//max of m_potentialLongNightSize and m_potentialShortNightSize i.e. potential size without the OPG pending orders

	const Money& GetPotentialLongValue() const{return m_potentialLongValue;}
	const Money& GetPotentialShortValue() const{return m_potentialShortValue;}
	const Money& GetPotentialLongMe() const{return m_potentialLongMe;}
	const Money& GetPotentialShortMe() const{return m_potentialShortMe;}
	const Money& GetPotentialBetaLongValue() const{return m_potentialBetaLongValue;}
	const Money& GetPotentialBetaShortValue() const{return m_potentialBetaShortValue;}
	const Money& GetPotentialLongNightValue() const{return m_potentialLongNightValue;}
	const Money& GetPotentialShortNightValue() const{return m_potentialShortNightValue;}

	Money GetClosedPnl() const{return m_closedPnl;}

	const Money& GetAveragePriceLoadedLong() const{return m_averagePriceLoadedLong;}
	const Money& GetAveragePriceLoadedShort() const{return m_averagePriceLoadedShort;}

	Money GetClosedPnlCost() const{return m_closedPnlCost;}

	Money GetOpenPnlLevel1Cost() const{return m_openPnlLevel1Cost;}
	Money GetOpenPnlPrintCost() const{return m_openPnlPrintCost;}

	Money GetOpenPnlLevel1() const{return m_openPnlLevel1;}
	const bool& isOpenPnlLevel1Valid() const{return m_openPnlLevel1Valid;}

	Money GetOpenPnlPrint() const{return m_openPnlPrint;}
	Money GetOpenPnlImbExNear() const{return m_openPnlImbExNear;}
	Money GetOpenPnlTClose() const{return m_openPnlTClose;}
	Money GetOpenPnlActionPrint() const{return m_openPnlActionPrint;}
	Money GetOpenPnlAction() const{return m_openPnlAction;}
	Money GetOpenPnlNbboPrint() const{return m_openPnlNbboPrint;}
	const Money& GetOpenPnlNbboPrintHi() const{return m_openPnlNbboPrintHi;}
	const Money& GetOpenPnlNbboPrintLo() const{return m_openPnlNbboPrintLo;}
	Money GetMarkedPnlNbboPrint() const{return m_markedPnlNbboPrint;}
	const Money& GetMarkedPnlNbboPrintHi() const{return m_markedPnlNbboPrintHi;}
	const Money& GetMarkedPnlNbboPrintLo() const{return m_markedPnlNbboPrintLo;}

	Money GetRTEquity() const{return m_rtEquity;}
	Money GetLeverage() const{return m_leverage;}

	Money GetOpenPnlNbboPrintPreMarket() const{return m_openPnlNbboPrintPreMarket;}
	Money GetOpenPnlNbboPrintMarket() const{return m_openPnlNbboPrintMarket;}
	Money GetOpenPnlNbboPrintPostMarket() const{return m_openPnlNbboPrintPostMarket;}

	Money GetClosedPnlPreMarket() const{return m_closedPnlPreMarket;}
	Money GetClosedPnlMarket() const{return m_closedPnlMarket;}
	Money GetClosedPnlPostMarket() const{return m_closedPnlPostMarket;}

	Money GetMarkedPnlNbboPrintPreMarket() const{return m_markedPnlNbboPrintPreMarket;}
	Money GetMarkedPnlNbboPrintMarket() const{return m_markedPnlNbboPrintMarket;}
	Money GetMarkedPnlNbboPrintPostMarket() const{return m_markedPnlNbboPrintPostMarket;}

	Money GetClosedPnlNet() const{return m_closedPnlNet;}
	Money GetOpenCommissionFee() const{return m_openCommissionFee;}
	void AdjustLevel1OpenPnl(const Money& diff, const Money& costDiff)
	{
		m_openPnlLevel1Cost += costDiff;
		m_openPnlLevel1 += diff;
	}
	void AdjustPrintOpenPnl(const Money& diff, const Money& costDiff)
	{
		m_openPnlPrintCost += costDiff;
		m_openPnlPrint += diff;
	}
	void AdjustImbExNearOpenPnl(const Money& diff)//, const Money& costDiff)
	{
//		m_openPnlImbExNearCost += costDiff;
		m_openPnlImbExNear += diff;
	}
	void AdjustTCloseOpenPnl(const Money& diff)
	{
		m_openPnlTClose += diff;
	}
	void AdjustActionPrintOpenPnl(const Money& diff)
	{
		m_openPnlActionPrint += diff;
	}
	void AdjustActionOpenPnl(const Money& diff)
	{
		m_openPnlAction += diff;
	}
	inline void AdjustClosedPnlForMarketState(const Money& diff, const unsigned char& marketState)
	{
		switch(marketState)
		{
			case MSTATE_MARKET:
			m_closedPnlMarket += diff;
			break;

			case MSTATE_PREMARKET:
			m_closedPnlPreMarket += diff;
			break;

//			case MSTATE_POSTMARKET:
			default:
			m_closedPnlPostMarket += diff;
			break;
/*
			default:
			m_closedPnlMarket += diff;
			m_closedPnlPreMarket += diff;
			m_closedPnlPostMarket += diff;
			break;
*/
		}
	}
	inline bool UpdateNbboPrintOpenPnlForMarketState(const unsigned char& marketState, Money& preMarketDiff, Money& marketDiff, Money& postMarketDiff)
	{
		switch(marketState)
		{
			case MSTATE_MARKET:
			marketDiff = m_openPnlNbboPrint - m_openPnlNbboPrintMarket;
			m_openPnlNbboPrintMarket = m_openPnlNbboPrint;
			if(m_openPnlNbboPrintPreMarket.isZero())
			{
				return false;
			}
			else if(!m_openPnlNbboPrintPreMarket.isZero())
			{
				preMarketDiff = -m_openPnlNbboPrintPreMarket;
				m_openPnlNbboPrintPreMarket.SetZero();
			}
			break;

			case MSTATE_PREMARKET:
			preMarketDiff = m_openPnlNbboPrint - m_openPnlNbboPrintPreMarket;
			m_openPnlNbboPrintPreMarket = m_openPnlNbboPrint;
			return false;

//			case MSTATE_POSTMARKET:
			default:
			postMarketDiff = m_openPnlNbboPrint - m_openPnlNbboPrintPostMarket;
			m_openPnlNbboPrintPostMarket = m_openPnlNbboPrint;
			if(m_openPnlNbboPrintMarket.isZero())
			{
				if(m_openPnlNbboPrintPreMarket.isZero())
				{
					return false;
				}
				else
				{
					preMarketDiff = -m_openPnlNbboPrintPreMarket;
					m_openPnlNbboPrintPreMarket.SetZero();
				}
			}
			else
			{
				marketDiff = -m_openPnlNbboPrintMarket;
				m_openPnlNbboPrintMarket.SetZero();

				if(!m_openPnlNbboPrintPreMarket.isZero())
				{
					preMarketDiff = -m_openPnlNbboPrintPreMarket;
					m_openPnlNbboPrintPreMarket.SetZero();
				}
			}
			break;
/*
			default:
			m_openPnlNbboPrintMarket = m_openPnlNbboPrint;
			m_openPnlNbboPrintPreMarket = m_openPnlNbboPrint;
			m_openPnlNbboPrintPostMarket = m_openPnlNbboPrint;
			break;
*/
		}
		return true;
	}
/*
	inline void AdjustNbboPrintOpenPnlForMarketState(const Money& diff, const unsigned char& marketState)
	{
		switch(marketState)
		{
			case MSTATE_MARKET:
			m_openPnlNbboPrintMarket += diff;
			break;

			case MSTATE_PREMARKET:
			m_openPnlNbboPrintPreMarket += diff;
			break;

//			case MSTATE_POSTMARKET:
			default:
			m_openPnlNbboPrintPostMarket += diff;
			break;
		}
	}
*/
	inline void AdjustNbboPrintOpenPnlPreMarket(const Money& diff)
	{
		m_openPnlNbboPrintPreMarket += diff;
		UpdateMarkedPnlNbboPrintPreMarket();
	}
	inline void AdjustNbboPrintOpenPnlMarket(const Money& diff)
	{
		m_openPnlNbboPrintMarket += diff;
		UpdateMarkedPnlNbboPrintMarket();
	}
	inline void AdjustNbboPrintOpenPnlPostMarket(const Money& diff)
	{
		m_openPnlNbboPrintPostMarket += diff;
		UpdateMarkedPnlNbboPrintPostMarket();
	}
	inline void AdjustNbboPrintOpenPnl(const Money& diff)//, const unsigned char& marketState)
	{
		m_openPnlNbboPrint += diff;
//		AdjustNbboPrintOpenPnlForMarketState(diff, marketState);
		UpdateOpenPnlNbboPrintHiLo();
		UpdateMarkedPnlNbboPrint();//marketState);
	}
	virtual Money GetEstimatedBeginningEquity() const{return Money::moneyZero;}
	virtual Money GetAccountMarkedPnlNbboPrint() const{return m_markedPnlNbboPrint;}
protected:
	InventoryData():
		m_absSize(0),
		m_absOvernightSize(0),

//#ifndef TAKION_NO_OPTIONS
//		m_absShareSize(0),
//#endif
		m_potentialLongSize(0),
		m_potentialShortSize(0),
		m_potentialSize(0),
		m_potentialLongNightSize(0),
		m_potentialShortNightSize(0),
		m_potentialNightSize(0),
		m_openPnlLevel1Valid(true)
	{}

#ifndef TAKION_NO_OPTIONS
	virtual void MultiplyContractValuesByCoefficient(const unsigned int& coefficient){}
	virtual void DivideContractValuesByCoefficient(const unsigned int& coefficient){}
#endif
	void SetOpenPnlNbboPrintHi(const Money& pnl){m_openPnlNbboPrintHi = pnl;}
	void SetOpenPnlNbboPrintLo(const Money& pnl){m_openPnlNbboPrintLo = pnl;}
	void SetMarkedPnlNbboPrintHi(const Money& pnl){m_markedPnlNbboPrintHi = pnl;}
	void SetMarkedPnlNbboPrintLo(const Money& pnl){m_markedPnlNbboPrintLo = pnl;}

	void SetMaxInvestment(const Money& investment){m_maxInvestment = investment;}
	void SetMaxInvestmentLong(const Money& investment){m_maxInvestmentLong = investment;}
	void SetMaxInvestmentShort(const Money& investment){m_maxInvestmentShort = investment;}

	void SetMaxInvestmentMe(const Money& investment){m_maxInvestmentMe = investment;}
	void SetMaxInvestmentLongMe(const Money& investment){m_maxInvestmentLongMe = investment;}
	void SetMaxInvestmentShortMe(const Money& investment){m_maxInvestmentShortMe = investment;}

	void SetMaxInvestmentBeta(const Money& investment){m_maxInvestmentBeta = investment;}
	void SetMaxInvestmentLongBeta(const Money& investment){m_maxInvestmentLongBeta = investment;}
	void SetMaxInvestmentShortBeta(const Money& investment){m_maxInvestmentShortBeta = investment;}

	void SetConditionallyOpenPnlNbboPrintHi(const Money& pnl){if(pnl > m_openPnlNbboPrintHi)m_openPnlNbboPrintHi = pnl;}
	void SetConditionallyOpenPnlNbboPrintLo(const Money& pnl){if(pnl < m_openPnlNbboPrintLo)m_openPnlNbboPrintLo = pnl;}
	void SetConditionallyMarkedPnlNbboPrintHi(const Money& pnl){if(pnl > m_markedPnlNbboPrintHi)m_markedPnlNbboPrintHi = pnl;}
	void SetConditionallyMarkedPnlNbboPrintLo(const Money& pnl){if(pnl < m_markedPnlNbboPrintLo)m_markedPnlNbboPrintLo = pnl;}

	void SetConditionallyMaxInvestment(const Money& investment){if(investment > m_maxInvestment)m_maxInvestment = investment;}
	void SetConditionallyMaxInvestmentLong(const Money& investment){if(investment > m_maxInvestmentLong)m_maxInvestmentLong = investment;}
	void SetConditionallyMaxInvestmentShort(const Money& investment){if(investment > m_maxInvestmentShort)m_maxInvestmentShort = investment;}

	void SetConditionallyMaxInvestmentMe(const Money& investment){if(investment > m_maxInvestmentMe)m_maxInvestmentMe = investment;}
	void SetConditionallyMaxInvestmentLongMe(const Money& investment){if(investment > m_maxInvestmentLongMe)m_maxInvestmentLongMe = investment;}
	void SetConditionallyMaxInvestmentShortMe(const Money& investment){if(investment > m_maxInvestmentShortMe)m_maxInvestmentShortMe = investment;}

	void SetConditionallyMaxInvestmentBeta(const Money& investment){if(investment > m_maxInvestmentBeta)m_maxInvestmentBeta = investment;}
	void SetConditionallyMaxInvestmentLongBeta(const Money& investment){if(investment > m_maxInvestmentLongBeta)m_maxInvestmentLongBeta = investment;}
	void SetConditionallyMaxInvestmentShortBeta(const Money& investment){if(investment > m_maxInvestmentShortBeta)m_maxInvestmentShortBeta = investment;}

	void UpdateOpenPnlNbboPrintHiLo()
	{
		if(m_openPnlNbboPrintHi < m_openPnlNbboPrint)m_openPnlNbboPrintHi = m_openPnlNbboPrint;
		if(m_openPnlNbboPrint < m_openPnlNbboPrintLo)m_openPnlNbboPrintLo = m_openPnlNbboPrint;
	}

	void UpdateMarkedPnlNbboPrintPreMarket()
	{
		m_markedPnlNbboPrintPreMarket = m_closedPnlPreMarket + m_openPnlNbboPrintPreMarket;
	}
	void UpdateMarkedPnlNbboPrintMarket()
	{
		m_markedPnlNbboPrintMarket = m_closedPnlMarket + m_openPnlNbboPrintMarket;
	}
	void UpdateMarkedPnlNbboPrintPostMarket()
	{
		m_markedPnlNbboPrintPostMarket = m_closedPnlPostMarket + m_openPnlNbboPrintPostMarket;
	}

//	void SetRTEquity(const Money& rtEquity){m_rtEquity = rtEquity;}//Set Position's RTEquity to be equal to Account's RTEquity
	virtual bool UpdateLeverage()
	{
		Money leverage(m_investment);
		leverage.DivideByMoney(m_rtEquity);
		if(leverage != m_leverage)
		{
			m_leverage = leverage;
//			NotifyLeverageChange();
			return true;
		}
		return false;
	}
	bool UpdateRTEquity()
	{
		m_rtEquity = GetAccountMarkedPnlNbboPrint() + GetEstimatedBeginningEquity();
		return UpdateLeverage();
	}
	bool NullifyLeverage()
	{
		if(!m_leverage.isZero())
		{
			m_leverage.SetZero();
			return true;
		}
		return false;
	}

	virtual void UpdateMarkedPnlNbboPrint()//const unsigned char marketState)
	{
/*
		switch(marketState)
		{
			case MSTATE_MARKET:
			m_markedPnlNbboPrintMarket = m_closedPnlMarket + m_openPnlNbboPrintMarket;
			break;

			case MSTATE_PREMARKET:
			m_markedPnlNbboPrintPreMarket = m_closedPnlPreMarket + m_openPnlNbboPrintPreMarket;
			break;

			case MSTATE_POSTMARKET:
			m_markedPnlNbboPrintPostMarket = m_closedPnlPostMarket + m_openPnlNbboPrintPostMarket;
			break;

			default:
			m_markedPnlNbboPrintMarket = m_closedPnlMarket + m_openPnlNbboPrintMarket;
			m_markedPnlNbboPrintPreMarket = m_closedPnlPreMarket + m_openPnlNbboPrintPreMarket;
			m_markedPnlNbboPrintPostMarket = m_closedPnlPostMarket + m_openPnlNbboPrintPostMarket;
			break;
		}
*/
		m_markedPnlNbboPrint = m_closedPnl + m_openPnlNbboPrint;
		if(m_markedPnlNbboPrintHi < m_markedPnlNbboPrint)m_markedPnlNbboPrintHi = m_markedPnlNbboPrint;
		if(m_markedPnlNbboPrint < m_markedPnlNbboPrintLo)m_markedPnlNbboPrintLo = m_markedPnlNbboPrint;

		UpdateRTEquity();
	}

	unsigned int m_absSize;
//#ifndef TAKION_NO_OPTIONS
//For Account, m_absSize is same as m_absShareSize (Position's m_absShareSize is used to modify Account's m_absSize)
//	unsigned int m_absShareSize;//Same as m_absSize for stocks; for options = m_absSize * GetContractSize()
//#endif
	unsigned int m_absOvernightSize;

	unsigned int m_potentialLongSize;
	unsigned int m_potentialShortSize;
	unsigned int m_potentialSize;

	unsigned int m_potentialLongNightSize;
	unsigned int m_potentialShortNightSize;
	unsigned int m_potentialNightSize;

	void SetInvestment(const Money& investment)
	{
		m_investment = investment;
		UpdateLeverage();
	}
	void IncrementInvestment(const Money& investment)
	{
		m_investment += investment;
		UpdateLeverage();
	}
	void DecrementInvestment(const Money& investment)
	{
		m_investment -= investment;
		UpdateLeverage();
	}
	void MultiplyInvestment(const unsigned int& coefficient)
	{
		m_investment *= coefficient;
		UpdateLeverage();
	}
	void DivideInvestment(const unsigned int& coefficient)
	{
		m_investment /= coefficient;
		UpdateLeverage();
	}
	void NullifyInvestment()
	{
		m_investment.SetZero();
		m_leverage.SetZero();
	}

	Money m_overnightInvestment;
	Money m_overnightInvestmentMe;
	Money m_overnightInvestmentBeta;

//	Money m_inventoryInvestment;
//	Money m_inventoryNbboPrintOpenPnl;

	Money m_investment;
	Money m_investmentMe;
	Money m_investmentBeta;
	Money m_investmentCost;

	Money m_maxInvestment;
	Money m_maxInvestmentLong;
	Money m_maxInvestmentShort;

	Money m_maxInvestmentMe;
	Money m_maxInvestmentLongMe;
	Money m_maxInvestmentShortMe;

	Money m_maxInvestmentBeta;
	Money m_maxInvestmentLongBeta;
	Money m_maxInvestmentShortBeta;

	Money m_potentialLongValue;
	Money m_potentialShortValue;
	Money m_potentialLongMe;
	Money m_potentialShortMe;
	Money m_potentialBetaLongValue;
	Money m_potentialBetaShortValue;
	Money m_potentialLongNightValue;
	Money m_potentialShortNightValue;

	Money m_closedPnl;
	Money m_closedPnlCost;

	Money m_averagePriceLoadedLong;
	Money m_averagePriceLoadedShort;

	Money m_openPnlLevel1Cost;
	Money m_openPnlPrintCost;

	Money m_openPnlLevel1;
	bool m_openPnlLevel1Valid;

	Money m_openPnlPrint;
	Money m_openPnlImbExNear;
	Money m_openPnlTClose;
	Money m_openPnlActionPrint;//used for remembering m_openPnlNbboPrint for comparing it with m_openPnlLevel1 later for picking the most optimistic Pnl for m_openPnlAction
	Money m_openPnlAction;

	Money m_openPnlNbboPrint;
	Money m_openPnlNbboPrintHi;
	Money m_openPnlNbboPrintLo;
	Money m_markedPnlNbboPrint;
	Money m_markedPnlNbboPrintHi;
	Money m_markedPnlNbboPrintLo;

	Money m_rtEquity;
	Money m_leverage;

	Money m_openPnlNbboPrintPreMarket;
	Money m_openPnlNbboPrintMarket;
	Money m_openPnlNbboPrintPostMarket;

	Money m_closedPnlPreMarket;
	Money m_closedPnlMarket;
	Money m_closedPnlPostMarket;

	Money m_markedPnlNbboPrintPreMarket;
	Money m_markedPnlNbboPrintMarket;
	Money m_markedPnlNbboPrintPostMarket;

	Money m_openCommissionFee;
	Money m_closedPnlNet;
};

class TU_API PositionInventoryData : public InventoryData
{
friend class PositionData;
friend class Account;
friend class AccountInventoryData;
public:
	virtual void Reset()
	{
		InventoryData::Reset();
#ifndef TAKION_NO_OPTIONS
		m_shareSize = 0;//Same as m_size for stocks; for options = m_size * GetContractSize()
		m_absShareSize = 0;//Same as m_absSize for stocks; for options = m_absSize * GetContractSize()
		m_underlierValue.SetZero();//StrikePrice * m_absShareSize;
#endif
		m_size = 0;
		m_overnightSize = 0;
		m_overnightAveragePriceCompact = 0;
		m_overnightAveragePrice.SetZero();
//		m_overnightAbsSize = 0;
		m_minSize = 0;
		m_maxSize = 0;
		m_sizeOrPhantom = 0;
		m_positionEnterTime = 0;
		m_compactAveragePrice = 0;
		m_averagePrice.SetZero();
		m_compactAverageCost = 0;
		m_averageCost.SetZero();

		m_buyMoney.SetZero();
		m_sellMoney.SetZero();
		m_averageBuyPrice.SetZero();
		m_averageSellPrice.SetZero();
		m_buyShares = 0;
		m_sellShares = 0;

		m_gpsLevel1.SetZero();
		m_gpsPrint.SetZero();
		m_gpsPrintHi.SetZero();
		m_gpsPrintLo.SetZero();
		m_openPnlForLossUpdated = false;
		m_invalidSecurity = false;
	}
	const bool& isInvalidSecurity() const{return m_invalidSecurity;}
	const bool& isOpenPnlForLossUpdated() const{return m_openPnlForLossUpdated;}
//	const unsigned int& GetAbsSizeLong() const{return GetSize() > 0 ? m_absSize : uintZero;}
//	const unsigned int& GetAbsSizeShort() const{return GetSize() < 0 ? m_absSize : uintZero;}
	const unsigned int& GetAbsSizeLong() const{return m_size > 0 ? m_absSize : uintZero;}
	const unsigned int& GetAbsSizeShort() const{return m_size < 0 ? m_absSize : uintZero;}
#ifndef TAKION_NO_OPTIONS
	const int& GetShareSize() const{return m_shareSize;}
	const unsigned int& GetAbsShareSize() const{return m_absShareSize;}
	const unsigned int& GetAbsShareSizeLong() const{return m_shareSize > 0 ? m_absShareSize : uintZero;}
	const unsigned int& GetAbsShareSizeShort() const{return m_shareSize < 0 ? m_absShareSize : uintZero;}
	const Money& GetUnderlierValue() const{return m_underlierValue;}
	const Money& GetUnderlierValueLong() const{return m_shareSize > 0 ? m_underlierValue : Money::moneyZero;}
	const Money& GetUnderlierValueShort() const{return m_shareSize < 0 ? m_underlierValue : Money::moneyZero;}
	virtual const unsigned int& GetStrikePrice() const = 0;
	virtual bool isOption() const = 0;
	virtual bool isCall() const = 0;
#endif
	const int& GetOvernightSize() const{return m_overnightSize;}
	const unsigned int& GetOvernightAveragePriceCompact() const{return m_overnightAveragePriceCompact;}
	const Price& GetOvernightAveragePrice() const{return m_overnightAveragePrice;}
//	const unsigned int& GetOvernightAbsSize() const{return m_overnightAbsSize;}
	const unsigned int& GetMinSize() const{return m_minSize;}
	const int& GetMaxSize() const{return m_maxSize;}
	const int& GetSizeOrPhantom() const{return m_sizeOrPhantom;}
	const unsigned int& GetPositionEnterTime() const{return m_positionEnterTime;}

	const Price& GetAveragePrice() const{return m_averagePrice;}
	const Price& GetAverageCost() const{return m_averageCost;}
	const unsigned int& GetCompactAveragePrice() const{return m_compactAveragePrice;}
	const unsigned int& GetCompactAverageCost() const{return m_compactAverageCost;}

	const Money& GetBuyMoney() const{return m_buyMoney;}
	const Money& GetSellMoney() const{return m_sellMoney;}
	const Price& GetAverageBuyPrice() const{return m_averageBuyPrice;}
	const Price& GetAverageSellPrice() const{return m_averageSellPrice;}
	const unsigned int& GetBuyShares() const{return m_buyShares;}
	const unsigned int& GetSellShares() const{return m_sellShares;}

	virtual void UpdateClosedPnlNet(){}

	const SignedPrice& GetGpsLevel1() const{return m_gpsLevel1;}
	const SignedPrice& GetGpsPrint() const{return m_gpsPrint;}
	const SignedPrice& GetGpsPrintHi() const{return m_gpsPrintHi;}
	const SignedPrice& GetGpsPrintLo() const{return m_gpsPrintLo;}

//	virtual const int& GetSize() const{return intZero;}
	const int& GetSize() const{return m_size;}
//	virtual const int& GetPositionInventorySize() const{return intZero;}
//	virtual bool isLoaded() const{return false;}
	virtual const Price& GetActionPrintPrice() const{return Price::priceZero;}

	virtual Money GetInvestmentLong() const override{return m_size > 0 ? m_investment : Money::moneyZero;}
	virtual Money GetInvestmentShort() const override{return m_size < 0 ? m_investment : Money::moneyZero;}
	virtual Money GetInvestmentMeLong() const override{return m_size > 0 ? m_investmentMe : Money::moneyZero;}
	virtual Money GetInvestmentMeShort() const override{return m_size < 0 ? m_investmentMe : Money::moneyZero;}
	virtual Money GetInvestmentBetaLong() const override{return m_size > 0 ? m_investmentBeta : Money::moneyZero;}
	virtual Money GetInvestmentBetaShort() const override{return m_size < 0 ? m_investmentBeta : Money::moneyZero;}
	virtual Money GetInvestmentCostLong() const override{return m_size > 0 ? m_investmentCost : Money::moneyZero;}
	virtual Money GetInvestmentCostShort() const override{return m_size < 0 ? m_investmentCost : Money::moneyZero;}
protected:
	PositionInventoryData():
//		m_absSize(0),
#ifndef TAKION_NO_OPTIONS
		m_shareSize(0),
		m_absShareSize(0),
#endif
		m_size(0),
		m_overnightSize(0),
		m_overnightAveragePriceCompact(0),
//		m_overnightAbsSize(0),
		m_minSize(0),
		m_maxSize(0),
		m_sizeOrPhantom(0),
		m_positionEnterTime(0),
		m_compactAveragePrice(0),
		m_compactAverageCost(0),
		m_buyShares(0),
		m_sellShares(0),
		m_openPnlForLossUpdated(false),
		m_invalidSecurity(false)
	{}

	virtual void WriteInventoryToAccountThread(int size, const Price& cost, bool inventoryFloating, bool leaveInLayout){}
	virtual void WriteInventoryToMainThread(int size, const Price& cost, bool inventoryFloating, bool leaveInLayout){}
	void UpdateMaxInvestment()
	{
		if(m_maxInvestment < m_investment)m_maxInvestment = m_investment;
		if(m_maxInvestmentMe < m_investmentMe)m_maxInvestmentMe = m_investmentMe;
		if(m_maxInvestmentBeta < m_investmentBeta)m_maxInvestmentBeta = m_investmentBeta;
//		if(GetSize() > 0)
		if(m_size > 0)
		{
			if(m_maxInvestmentLong < m_investment)m_maxInvestmentLong = m_investment;
			if(m_maxInvestmentLongMe < m_investmentMe)m_maxInvestmentLongMe = m_investmentMe;
			if(m_maxInvestmentLongBeta < m_investmentBeta)m_maxInvestmentLongBeta = m_investmentBeta;
		}
		else
		{
			if(m_maxInvestmentShort < m_investment)m_maxInvestmentShort = m_investment;
			if(m_maxInvestmentShortMe < m_investmentMe)m_maxInvestmentShortMe = m_investmentMe;
			if(m_maxInvestmentShortBeta < m_investmentBeta)m_maxInvestmentShortBeta = m_investmentBeta;
		}
	}
	void UpdateMaxInvestmentMe()
	{
		if(m_maxInvestmentMe < m_investmentMe)m_maxInvestmentMe = m_investmentMe;
//		if(GetSize() > 0)
		if(m_size > 0)
		{
			if(m_maxInvestmentLongMe < m_investmentMe)m_maxInvestmentLongMe = m_investmentMe;
		}
		else
		{
			if(m_maxInvestmentShortMe < m_investmentMe)m_maxInvestmentShortMe = m_investmentMe;
		}
	}
	void UpdateMaxInvestmentBeta()
	{
		if(m_maxInvestmentBeta < m_investmentBeta)m_maxInvestmentBeta = m_investmentBeta;
//		if(GetSize() > 0)
		if(m_size > 0)
		{
			if(m_maxInvestmentLongBeta < m_investmentBeta)m_maxInvestmentLongBeta = m_investmentBeta;
		}
		else
		{
			if(m_maxInvestmentShortBeta < m_investmentBeta)m_maxInvestmentShortBeta = m_investmentBeta;
		}
	}


#ifndef TAKION_NO_OPTIONS
	virtual void MultiplyContractValuesByCoefficient(const unsigned int& coefficient) override;
	virtual void DivideContractValuesByCoefficient(const unsigned int& coefficient) override;
#endif

	virtual void SetActionPrintPrice(const Price& printPrice){}

	Money UpdateLevel1OpenPnl(const Price& level1Price, bool bid, Money& costDiff, Money& diffAction);
	Money UpdatePrintOpenPnl(const Price& printPrice, Money& costDiff);
	Money UpdateImbExNearOpenPnl(const Price& nearPrice);
	Money UpdateNbboPrintOpenPnl(const Price& printPrice, bool actionPrint, Money& diffActionPrint, Money& diffAction, Money& preMarketDiff, Money& marketDiff, Money& postMarketDiff, const unsigned char marketState);
	Money UpdateTCloseOpenPnl(const Price& tclosePrice);

	void DoUpdateClosedPnlNet(const Money& commissionPer1000Shares, const unsigned int& sharesTraded)
	{
		m_closedPnlNet = m_closedPnl - commissionPer1000Shares * sharesTraded / 1000;
//		m_closedPnlNet = m_closedPnl - commissionPer1000Shares * (m_sharesTraded
//#ifndef TAKION_NO_OPTIONS
//			* GetContractSize()
//#endif
//			) / 1000;
		m_openCommissionFee = commissionPer1000Shares *
#ifndef TAKION_NO_OPTIONS
			m_absShareSize
#else
			m_absSize
#endif
			/ 1000;
	}
//	unsigned int m_absSize;
#ifndef TAKION_NO_OPTIONS
	Money m_underlierValue;
	int m_shareSize;//Same as m_size for stocks; for options = m_size * GetContractSize()
	unsigned int m_absShareSize;//Same as m_absSize for stocks; for options = m_absSize * GetContractSize()
#endif
	int m_size;
	int m_overnightSize;
	unsigned int m_overnightAveragePriceCompact;
	Price m_overnightAveragePrice;
//	unsigned int m_overnightAbsSize;
	unsigned int m_minSize;
	int m_maxSize;
	int m_sizeOrPhantom;

	unsigned int m_positionEnterTime;

	unsigned int m_compactAveragePrice;
	Price m_averagePrice;

	unsigned int m_compactAverageCost;
	Price m_averageCost;

	Money m_buyMoney;
	Money m_sellMoney;
	Price m_averageBuyPrice;
	Price m_averageSellPrice;
	unsigned int m_buyShares;
	unsigned int m_sellShares;

	SignedPrice m_gpsLevel1;
	SignedPrice m_gpsPrint;
	SignedPrice m_gpsPrintHi;
	SignedPrice m_gpsPrintLo;

	virtual void IncrementUpdatedPnlPositionCount(const bool openPnlForLossUpdated){}
	virtual bool SetOpenPnlForLossUpdated(const bool updated);
	virtual bool SetInvalidSecurity(const bool invalid);
	bool m_openPnlForLossUpdated;
	bool m_invalidSecurity;
};

enum PositionStatus : unsigned char
{
	TU_POSITION_STATUS_FLAT,
	TU_POSITION_STATUS_LONG,
	TU_POSITION_STATUS_SHORT,

	TU_POSITION_STATUS_COUNT,
};

enum PositionOrderStatus : unsigned char
{
	TU_POSITION_ORDER_STATUS_PENDING = (TU_POSITION_STATUS_COUNT - 1) << 1,
	TU_POSITION_ORDER_STATUS_PENDING_STOP_TRAILING = TU_POSITION_ORDER_STATUS_PENDING << 1,

	TU_POSITION_ORDER_STATUS_COUNT,
};

class TU_API PositionDataBase : public BasePosition, public PositionInventoryData, public Observable
{
public:
//	static const int defaultCompactBeta;//Price(100, 0).GetCompactValue();
	virtual Position* GetAccountPosition(){return NULL;}
	virtual const Position* GetAccountPosition() const{return NULL;}
	virtual Account* GetAccount() const{return NULL;}

	void AddInThreadObserver(Observer* o) const;//Call RemoveInThreadObserver in the destructor of the object that you pass to this function
	void RemoveInThreadObserver(Observer* o) const;
//	void RemoveInThreadObserverWithoutLocking(Observer* o) const;
	void NotifyInThreadObservers(const Message* message, const Message* info = NULL) const;

//	virtual const int& GetSize() const override{return m_size;}
//	virtual const int& GetSize() const{return m_size;}
	const unsigned int& GetPendingSellPassiveShares() const{return m_pendingSellPassiveShares;}
	const unsigned int& GetPendingSellNonPassiveShares() const{return m_pendingSellNonPassiveShares;}
	const unsigned int& GetPendingSellShares(const bool& passive) const{return passive ? m_pendingSellPassiveShares : m_pendingSellNonPassiveShares;}

	const unsigned int& GetPendingShortPassiveShares() const{return m_pendingShortPassiveShares;}
	const unsigned int& GetPendingShortNonPassiveShares() const{return m_pendingShortNonPassiveShares;}
	const unsigned int& GetPendingShortShares(const bool& passive) const{return passive ? m_pendingShortPassiveShares : m_pendingShortNonPassiveShares;}

	unsigned int GetPendingSellAndShortPassiveShares() const{return m_pendingSellPassiveShares + m_pendingShortPassiveShares;}
	unsigned int GetPendingSellAndShortNonPassiveShares() const{return m_pendingSellNonPassiveShares + m_pendingShortNonPassiveShares;}
	unsigned int GetPendingSellAndShortShares(const bool& passive) const{return passive ? GetPendingSellAndShortPassiveShares() : GetPendingSellAndShortNonPassiveShares();}
/*
	unsigned int GetSharesAvailableToSell(const bool& passive, const int& additionalPositionSize) const
	{
		const int size = GetSize() + additionalPositionSize;
		if(size > 0)
		{
			const unsigned int uintSize = (unsigned int)size;
			const unsigned int pendingSellAndShortShares = GetPendingSellAndShortShares(passive);
			if(uintSize > pendingSellAndShortShares)return uintSize - pendingSellAndShortShares;
		}
		return 0;
	}
*/
	const unsigned int& GetAdvPassiveShares() const{return m_advPassiveShares;}
	const unsigned int& GetAdvOrderCount() const{return m_advOrderCount;}
/*
	static inline void DoDecrementNumber(unsigned int& number, const unsigned int& by)
	{
		if(number >= by)number -= by;
		else number = 0;
	}
*/
	SecurityType GetSecurityType() const{return m_securityType;}
	bool isSizeOpening(bool buy, unsigned int size) const;

	const unsigned int& GetTimeLoaded() const{return m_timeLoaded;}
//	virtual bool isLoaded() const override{return m_timeLoaded != 0;}
	bool isLoaded() const{return m_timeLoaded != 0;}

	const unsigned int& GetUnclosedOvernightSize() const{return m_unclosedOvernightSize;}
	const unsigned int& GetUnclosedOvernightShortSize() const{return m_overnightSize < 0 ? m_unclosedOvernightSize : uintZero;}
	const unsigned int& GetUnclosedOvernightLongSize() const{return m_overnightSize > 0 ? m_unclosedOvernightSize : uintZero;}
//	const unsigned int& GetOvernightAveragePriceCompact() const{return m_overnightAveragePriceCompact;}
//	const Price& GetOvernightAveragePrice() const{return m_overnightAveragePrice;}
	const Price& GetOvernightAverageCost() const{return m_overnightAverageCost;}

	const Price& GetClosingPrice() const{return m_closingPrice;}
	const Price& GetOvernightOrClosingPrice() const{return m_overnightAveragePrice.isZero() ? m_closingPrice : m_overnightAveragePrice;}

	const Price& GetTodaysClosingPrice() const{return m_todaysClosingPrice;}

	const Price& GetLoadedAveragePrice() const{return m_loadedAveragePrice;}

	const unsigned int& GetLastExecPrice() const{return m_lastExecPrice;}
	const int& GetLastExecSize() const{return m_lastExecSize;}

	__int64 GetClosedPnlDollars() const{return GetClosedPnl().GetDollars();}

	virtual Money GetHardBpUsed() const{return Money::moneyZero;}//can be different from m_investment if a retail account has overnight position.
	virtual Money GetHardMeUsed() const{return Money::moneyZero;}//can be different from m_investment if a retail account has overnight position.
	
	virtual Money GetBpUsed() const{return Money::moneyZero;}//max of m_potentialLongValue and m_potentialShortValue
	virtual Money GetMeUsed() const{return Money::moneyZero;}//max of m_potentialLongMe and m_potentialShortMe
	virtual Money GetNightBpUsed() const{return Money::moneyZero;}//max of m_potentialLongNightValue and m_potentialShortNightValue i.e. potential value without the OPG pending orders
	virtual Money GetBpBetaUsed() const{return Money::moneyZero;}//max of m_potentialLongBetaValue and m_potentialShortBetaValue

	const Money& GetPendingBuyInvestment() const{return m_pendingBuyInvestment;}
	const Money& GetPendingSellAndShortInvestment() const{return m_pendingSellAndShortInvestment;}

	const Money& GetPendingMeBuyInvestment() const{return m_pendingMeBuyInvestment;}
	const Money& GetPendingMeSellAndShortInvestment() const{return m_pendingMeSellAndShortInvestment;}

	const Money& GetPendingBetaBuyInvestment() const{return m_pendingBetaBuyInvestment;}
	const Money& GetPendingBetaSellAndShortInvestment() const{return m_pendingBetaSellAndShortInvestment;}

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
	virtual int GetFirmSize() const{return intZero;}
	virtual int GetFirmPotentialShortSize() const{return intZero;}
	virtual const unsigned char& GetUntradeableLevel() const{return ucharZero;}//m_untradeableLevel;}//For Supervisor only. 0 - tradable; 1 - pending; 2 - untradeable.
	virtual const unsigned char& GetUntradeable() const{return ucharZero;}
#endif

	static const bool& GetFalseRef(){return boolFalse;}

	const unsigned int& GetPendingBuyRtcPassiveShares() const{return m_pendingBuyRtcPassiveShares;}
	const unsigned int& GetPendingBuyRtcNonPassiveShares() const{return m_pendingBuyRtcNonPassiveShares;}

	const unsigned int& GetBuySharesBeingCanceled() const{return m_buySharesBeingCanceled;}
	const unsigned int& GetSellAndShortSharesBeingCanceled() const{return m_sellAndShortSharesBeingCanceled;}
	const unsigned int& GetSellSharesBeingCanceled() const{return m_sellSharesBeingCanceled;}

	const unsigned int& GetBuyPassiveSharesBeingCanceled() const{return m_buyPassiveSharesBeingCanceled;}
	const unsigned int& GetBuyNonPassiveSharesBeingCanceled() const{return m_buyNonPassiveSharesBeingCanceled;}
	const unsigned int& GetBuySharesBeingCanceled(const bool& passive) const{return passive ? m_buyPassiveSharesBeingCanceled : m_buyNonPassiveSharesBeingCanceled;}

	const unsigned int& GetSellPassiveSharesBeingCanceled() const{return m_sellPassiveSharesBeingCanceled;}
	const unsigned int& GetSellNonPassiveSharesBeingCanceled() const{return m_sellNonPassiveSharesBeingCanceled;}
	const unsigned int& GetSellSharesBeingCanceled(const bool& passive) const{return passive ? m_sellPassiveSharesBeingCanceled : m_sellNonPassiveSharesBeingCanceled;}

	const unsigned int& GetShortPassiveSharesBeingCanceled() const{return m_shortPassiveSharesBeingCanceled;}
	const unsigned int& GetShortNonPassiveSharesBeingCanceled() const{return m_shortNonPassiveSharesBeingCanceled;}
	const unsigned int& GetShortSharesBeingCanceled(const bool& passive) const{return passive ? m_shortPassiveSharesBeingCanceled : m_shortNonPassiveSharesBeingCanceled;}

	unsigned int GetSellAndShortPassiveSharesBeingCanceled() const{return m_sellPassiveSharesBeingCanceled + m_shortPassiveSharesBeingCanceled;}
	unsigned int GetSellAndShortNonPassiveSharesBeingCanceled() const{return m_sellNonPassiveSharesBeingCanceled + m_shortNonPassiveSharesBeingCanceled;}
	unsigned int GetSellAndShortPassiveSharesBeingCanceled(const bool& passive) const{return passive ? GetSellAndShortPassiveSharesBeingCanceled() : GetSellAndShortNonPassiveSharesBeingCanceled();}

	const unsigned int& GetBuyRtcPassiveSharesBeingCanceled() const{return m_buyRtcPassiveSharesBeingCanceled;}
	const unsigned int& GetBuyRtcNonPassiveSharesBeingCanceled() const{return m_buyRtcNonPassiveSharesBeingCanceled;}
	const unsigned int& GetBuyRtcSharesBeingCanceled(const bool& passive) const{return passive ? m_buyRtcPassiveSharesBeingCanceled : m_buyRtcNonPassiveSharesBeingCanceled;}
//	unsigned int GetPendingSellAndShortSharesWithoutBeingCanceled() const;

	const Money& GetPendingBuyBorrowInvestment() const{return m_pendingBuyBorrowInvestment;}
	const Money& GetBpBorrowUsed() const{return m_bpBorrowUsed;}
	const unsigned int& GetPendingBuyBorrowShares() const{return m_pendingBuyBorrowShares;}
	const unsigned int& GetPendingSellBorrowShares() const{return m_pendingSellBorrowShares;}
	const unsigned int& GetBorrowSize() const{return m_borrowSize;}
#ifdef SEND_LOCATE_INFO
	const unsigned int& GetNewBorrowSize() const{return m_newBorrowSize;}//for sending it to the executor with the Locate Contract Id
#endif
	Money GetBorrowInvestment() const{return m_borrowInvestment;}
	Price GetBorrowAveragePrice() const{return m_borrowAveragePrice;}

//	const int& GetOvernightSize() const{return m_overnightSize;}
	const int& GetLoadedSize() const{return m_loadedSize;}
//	const unsigned int& GetOvernightAbsSize() const{return m_overnightAbsSize;}
	const unsigned int& GetLoadedAbsSize() const{return m_loadedAbsSize;}

	const unsigned int& GetSharesTraded() const{return m_sharesTraded;}
	const unsigned int& GetSharesAdded() const{return m_sharesAdded;}
	const unsigned int& GetSharesRemoved() const{return m_sharesRemoved;}
	const Money& GetTicketAverage() const{return m_ticketAverage;}
	const Money& GetMarkedTicketAverage() const{return m_markedTicketAverage;}
	const Money& GetMarkedTicketAverageHi() const{return m_markedTicketAverageHi;}
	const Money& GetMarkedTicketAverageLo() const{return m_markedTicketAverageLo;}
//	Money GetClosedPnlNet() const{return m_closedPnlNet;}
//	Money GetOpenCommissionFee() const{return m_openCommissionFee;}
//	virtual void UpdateClosedPnlNet(){}

	const int& GetCompactBeta() const{return m_compactBeta;}
	const unsigned char& GetMargin() const{return m_margin;}

	const unsigned char& GetPmElRate() const{return m_PM_EL_Rate;}
	const unsigned char& GetPmEsRate() const{return m_PM_ES_Rate;}
	const unsigned char& GetPmHlRate() const{return m_PM_HL_Rate;}
	const unsigned char& GetPmHsRate() const{return m_PM_HS_Rate;}
	const unsigned char& GetElRate() const{return m_EL_Rate;}
	const unsigned char& GetEsRate() const{return m_ES_Rate;}
	const unsigned char& GetHlRate() const{return m_HL_Rate;}
	const unsigned char& GetHsRate() const{return m_HS_Rate;}
	const unsigned char& GetFedReq() const{return m_Fed_Req;}
	const unsigned char& GetAssetType() const{return m_Asset_Type;}
	const bool& isMarginable() const{return m_Marginable;}
	const unsigned char& GetSecType() const{return m_Sec_Type;}
	const unsigned char& GetStatus() const{return m_Status;}

	const bool& isPortfolioManaged() const{return m_PortfolioManaged;}
//	const unsigned char& GetMeRate(const bool buy) const;
//	const unsigned char& GetMeLongRate() const;
//	const unsigned char& GetMeShortRate() const;
	const unsigned char& GetMeLongRate(const bool& portfolio) const
	{
		return portfolio ? m_PM_HL_Rate : m_HL_Rate;
	}

	const unsigned char& GetMeShortRate(const bool& portfolio) const
	{
		return portfolio ? m_PM_HS_Rate : m_HS_Rate;
	}

	const unsigned char& GetMeRate(const bool& buy, const bool& portfolio) const
	{
//		return portfolio ? buy ? m_PM_HL_Rate : m_PM_HS_Rate : buy ? m_HL_Rate : m_HS_Rate;
		return buy ? GetMeLongRate(portfolio) : GetMeShortRate(portfolio);
	}

	static inline void GetMeByRate(Money& money, const unsigned char& rate)
	{
		if(rate != 100)
		{
			money *= rate;
			money /= 100;
		}
	}
	static inline void GetMeStatic(Money& money, const bool& buy, const unsigned char& rate, const Price& price, const unsigned int& size)
	{
		static const Price twoAndHalf(2, 500000000);
		static const Price five(5, 0);
		if(buy)
		{
			if(price > twoAndHalf)
			{
				GetMeByRate(money, rate);
			}
		}
		else
		{
			if(price > five)
			{
				GetMeByRate(money, rate);
			}
			else if(price <= twoAndHalf)
			{
				money = twoAndHalf * size;
			}
		}
	}
	void GetMe(Money& money, const bool& buy, const bool& portfolio, const Price& price, const unsigned int& size) const
	{
		GetMeStatic(money, buy, GetMeRate(buy, portfolio), price, size);
/*
		static const Price twoAndHalf(2, 500000000);
		static const Price five(5, 0);
		if(buy)
		{
			if(price > twoAndHalf)
			{
				GetMeByRate(money, GetMeLongRate(portfolio));
			}
		}
		else
		{
			if(price > five)
			{
				GetMeByRate(money, GetMeShortRate(portfolio));
			}
			else if(price <= twoAndHalf)
			{
				money = twoAndHalf * size;
			}
		}
*/
	}

	const unsigned int& GetCompactBorrowDiscountedPrice() const{return m_compactBorrowDiscountedPrice;}
	const unsigned int& GetBorrowAvailableSize() const{return m_borrowAvailableSize;}

	const bool& isRestricted() const{return m_restricted;}
	const bool& isRestrictedInitialized() const{return m_restrictedInitialized;}

	virtual bool isStockLoanInitialized() const{return false;}

	virtual unsigned int GetOrdersPendingCount() const{return 0;}
	virtual unsigned int GetPendingOrdersLong() const{return 0;}
	virtual unsigned int GetPendingOrdersSell() const{return 0;}
	virtual unsigned int GetPendingOrdersShort() const{return 0;}
	unsigned int GetPendingOrdersSellAndShort() const
	{
		return GetPendingOrdersSell() + GetPendingOrdersShort();
	}
	virtual unsigned int GetOrdersStuckCount() const{return 0;}
	virtual unsigned int GetOrdersBlockedCount() const{return 0;}
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
//	virtual const int& GetSizeOrPhantom() const{return m_size;}
	virtual const unsigned int& GetTimestampHtb() const{return uintZero;}
	virtual const unsigned char& isHTB() const{return ucharZero;}
	virtual const bool& isHtbInitialized() const{return boolFalse;}
	virtual bool HasHTB() const{return true;}
	virtual unsigned int GetHtbString() const{return 0;}
//	virtual const unsigned int& GetCompactBorrowDiscountedPrice() const{return uintZero;}
//	virtual const unsigned int& GetBorrowAvailableSize() const{return uintZero;}

	virtual const unsigned int& GetAccountCount() const{return uintOne;}

	virtual void Reset();

//	virtual const int& GetPositionInventorySize() const override{return m_size;}
	void NotifySecurityObservers(const Message* message, const Message* info) const;
	void AddSecurityObserver(Observer* o) const;
	void RemoveSecurityObserver(Observer* o) const;
	bool isSecurityObservable(Observable* o) const{return o == &m_securityObservable;}
#ifndef TAKION_NO_OPTIONS
	virtual const unsigned int& GetCallSharesSoldPotential() const{return uintZero;}
	virtual const unsigned int& GetPutSharesSoldPotential() const{return uintZero;}
	const unsigned int& GetOptionContractsTraded() const{return m_optionContractsTraded;}

	void NotifyUnderlierSecurityObservers(const Message* message, const Message* info) const;
	void AddUnderlierSecurityObserver(Observer* o) const;
	void RemoveUnderlierSecurityObserver(Observer* o) const;
	bool isUnderlierSecurityObservable(Observable* o) const{return o == &m_underlierSecurityObservable;}
	bool AdjustOptionShortMeUsed(Money& meUsed, const unsigned int shares) const;
#endif
	virtual Money GetEstimatedBeginningEquity() const;
	virtual Money GetAccountMarkedPnlNbboPrint() const;
protected:
	PositionDataBase(const char* symbol,
		SecurityType securityType,
		int compactBeta,
		unsigned char margin,
		unsigned char PM_EL_Rate,// = 15,
		unsigned char PM_ES_Rate,// = 15,
		unsigned char PM_HL_Rate,// = 15,
		unsigned char PM_HS_Rate,// = 15,
		unsigned char EL_Rate,// = 25,
		unsigned char ES_Rate,// = 30,
		unsigned char HL_Rate,// = 30,
		unsigned char HS_Rate,// = 30,
		unsigned char Fed_Req,// = 50,
		unsigned char Asset_Type,// = 'E',
		bool Marginable,// = true,
		unsigned char Sec_Type,// = 'C',
		unsigned char Status,// = 0):
		bool PortfolioManaged,
		unsigned int timeLoaded);//0 if not loaded from the database

	virtual void ClosingPriceSet(){}
	virtual void TodaysClosingPriceSet(){}

	void UpdateBetaInvestment()
	{
		m_investmentBeta = m_investment;
		if(!m_investmentBeta.isZero() && m_margin != 100)
		{
			m_investmentBeta *= m_margin;
			m_investmentBeta /= 100;
		}
	}

	void UpdateMeInvestment(const bool& portfolio)
	{
		m_investmentMe = m_investment;
		if(!m_investmentMe.isZero())
		{
#ifndef TAKION_NO_OPTIONS
			if(isOption())
			{
				if(m_size < 0)
				{
					AdjustOptionShortMeUsed(m_investmentMe, -m_size);
				}
			}
			else
			{
#endif
				GetMe(m_investmentMe, m_size > 0, portfolio, m_averagePrice, m_absSize);
/*
				const unsigned char rate = GetMeRate(m_size > 0, portfolio);
				if(rate != 100)
				{
					m_investmentMe *= rate;
					m_investmentMe /= 100;
				}
*/
#ifndef TAKION_NO_OPTIONS
			}
#endif
		}
	}

	void SetClosingPrice(const Price& price)
	{
		if(price != m_closingPrice)
		{
			m_closingPrice = price;
			ClosingPriceSet();
		}
	}
	void SetTodaysClosingPrice(const Price& price)
	{
		if(price != m_todaysClosingPrice)
		{
			m_todaysClosingPrice = price;
			TodaysClosingPriceSet();
		}
	}

/*	
	virtual void SecuritySet()
	{
		if(m_security)SetClosingPrice(Price(m_security->GetClosePriceCompact()));
	}
	
	virtual void SortableSecuritySet()
	{
		if(m_sortableSecurity)SetClosingPrice(Price(m_sortableSecurity->GetClosePriceCompact()));
	}
*/
	virtual void UpdateMarkedPnlNbboPrint() override;//const unsigned char marketState) override;

	SecurityType m_securityType;

//	int m_size;
	unsigned int m_pendingSellPassiveShares;
	unsigned int m_pendingSellNonPassiveShares;
	unsigned int m_pendingShortPassiveShares;
	unsigned int m_pendingShortNonPassiveShares;

	unsigned int m_advPassiveShares;
	unsigned int m_advOrderCount;

	unsigned int m_compactBorrowDiscountedPrice;
	unsigned int m_borrowAvailableSize;

	int m_compactBeta;
	unsigned char m_margin;

//07/02/2019
	unsigned char m_PM_EL_Rate;
	unsigned char m_PM_ES_Rate;
	unsigned char m_PM_HL_Rate;
	unsigned char m_PM_HS_Rate;
	unsigned char m_EL_Rate;
	unsigned char m_ES_Rate;
	unsigned char m_HL_Rate;
	unsigned char m_HS_Rate;
	unsigned char m_Fed_Req;
	unsigned char m_Asset_Type;
	bool m_Marginable;
	unsigned char m_Sec_Type;
	unsigned char m_Status;
//
	bool m_PortfolioManaged;
//
	bool m_restricted;
	bool m_restrictedInitialized;

	unsigned int m_timeLoaded;

	unsigned int m_unclosedOvernightSize;
//	unsigned int m_unclosedOvernightShortSize;
//	unsigned int m_overnightAveragePriceCompact;
//	Price m_overnightAveragePrice;
	Price m_overnightAverageCost;

	Price m_loadedAveragePrice;

	Price m_closingPrice;
	Price m_todaysClosingPrice;

/*
	Money m_potentialLongValue;
	Money m_potentialShortValue;

	Money m_potentialLongNightValue;
	Money m_potentialShortNightValue;
*/

	unsigned int m_lastExecPrice;
	int m_lastExecSize;

//	Money m_closedPnl;
//	Money m_closedPnlCost;
/*
	Money m_openPnlLevel1Cost;
	Money m_openPnlLevel1;
	Money m_openPnlPrint;
	Money m_openPnlTClose;
	Money m_openPnlNbboPrint;
	Money m_openPnlNbboPrintHi;
	Money m_openPnlNbboPrintLo;
	Money m_markedPnlNbboPrint;
	Money m_markedPnlNbboPrintHi;
	Money m_markedPnlNbboPrintLo;
*/
/*
	SignedPrice m_gpsLevel1;
	SignedPrice m_gpsPrint;
	SignedPrice m_gpsPrintHi;
	SignedPrice m_gpsPrintLo;
*/
	Money m_pendingBuyInvestment;
	Money m_pendingSellAndShortInvestment;

	Money m_pendingMeBuyInvestment;
	Money m_pendingMeSellAndShortInvestment;

	Money m_pendingBetaBuyInvestment;
	Money m_pendingBetaSellAndShortInvestment;

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
/*
	unsigned int m_potentialLongSize;
	unsigned int m_potentialShortSize;
	unsigned int m_potentialSize;

	unsigned int m_potentialLongNightSize;
	unsigned int m_potentialShortNightSize;
	unsigned int m_potentialNightSize;
*/
	unsigned int m_pendingBuyBorrowShares;
	unsigned int m_pendingSellBorrowShares;
	unsigned int m_borrowSize;
#ifdef SEND_LOCATE_INFO
	unsigned int m_newBorrowSize;
#endif
#ifndef TAKION_NO_OPTIONS
	unsigned int m_optionContractsTraded;
#endif
//	int m_overnightSize;
	int m_loadedSize;
//	unsigned int m_overnightAbsSize;
	unsigned int m_loadedAbsSize;
	unsigned int m_sharesTraded;
	unsigned int m_sharesAdded;
	unsigned int m_sharesRemoved;
	Money m_ticketAverage;
	Money m_markedTicketAverage;
	Money m_markedTicketAverageHi;
	Money m_markedTicketAverageLo;
//	Money m_openCommissionFee;
//	Money m_closedPnlNet;
	Observable m_inThreadObservable;
	TakionLockSingleThreadAccess m_lockInThreadObservable;
	Observable m_securityObservable;//main thread
#ifndef TAKION_NO_OPTIONS
	Observable m_underlierSecurityObservable;//main thread
#endif
};

class PositionData;

class TU_API PositionInventory : public PositionInventoryData
{
friend class Account;
friend class PositionData;
public:
	PositionInventory(PositionData* position, int inventorySize, const Price& inventoryCost, bool inventoryFloating, bool hiddenAlways);
	PositionInventory(PositionData* position, bool hiddenAlways);
	PositionInventory(PositionData* position);

	DECLARE_NED_NEW
	const int& GetInventorySize() const{return m_inventorySize;}
	bool SetInventorySize(const int inventorySize, const Security* security);
	const bool& isPositionHidden() const{return m_positionHidden;}
	const bool& isHiddenAlways() const{return m_hiddenAlways;}
	bool SetHiddenAlways(bool hiddenAlways, const Security* security);
	const int& GetPermanentInventorySize() const{return m_permanentInventorySize;}

	const Price& GetInventoryCost() const{return m_inventoryCost;}
	bool SetInventoryCost(const Price& inventoryCost);
	const Price& GetPermanentInventoryCost() const{return m_permanentInventoryCost;}

	const bool& isInventoryFloating() const{return m_inventoryFloating;}
	bool SetInventoryFloating(const bool inventoryFloating);

	bool isHidden() const{return m_hiddenAlways || m_positionHidden;}

	const Price& GetInventoryPrice() const{return m_inventoryPrice;}
	void SetInventoryPrice(const Price& price, const unsigned char marketState);

	virtual const Money& GetInventoryInvestment() const override{return m_inventoryInvestment;}
	virtual const Money& GetInventoryNbboPrintOpenPnl() const override{return m_inventoryNbboPrintOpenPnl;}

	void UpdatePotentialValues();// const bool includeNight);
	void UpdatePotentialBetaValues();
	void UpdatePotentialMeValues();

//	void OrderPartiallyCancelled(const Order* order, unsigned int quantityCanceled);
	void OrderExecuted(const Order* order, const Execution* execution, const Security* security, unsigned int& closedShares, const unsigned char marketState);
	void AdjustPosition(const unsigned int quantity,
		const Price& price,
		const bool side,
		const bool busted,
		const bool includeNight,
		const Security* security,
		unsigned int& closedShares,
		const unsigned char marketState,
		const unsigned char altMarketState);
//		const unsigned char margin);

	bool AdjustOvernightInventory();
	bool AdjustInventorySize(const Security* security);

//	virtual const int& GetSize() const{return m_size;}
/*
	const Price& GetAveragePrice() const{return m_averagePrice;}
	const Price& GetAverageCost() const{return m_averageCost;}
	const unsigned int& GetCompactAveragePrice() const{return m_compactAveragePrice;}
	const unsigned int& GetCompactAverageCost() const{return m_compactAverageCost;}
*/
	virtual void Reset() override
	{
		PositionInventoryData::Reset();
//		m_hidden = false;
//		m_inventoryPrice.SetZero();
		m_permanentInventorySize = 0;
		m_permanentInventoryCost.SetZero();
		m_inventorySize = 0;
		m_inventoryCost.SetZero();
		m_inventoryFloating = false;
		m_inventoryInvestment.SetZero();
		m_inventoryNbboPrintOpenPnl.SetZero();
//		m_size = 0;
	}
//	virtual const int& GetPositionInventorySize() const override{return m_size;}
//	virtual const int& GetSize() const override{return m_size;}
#ifndef TAKION_NO_OPTIONS
	virtual const unsigned int& GetStrikePrice() const override;
	virtual bool isOption() const override;
	virtual bool isCall() const override;
#endif
protected:
	bool DoSetInventorySize(const int inventorySize, const Security* security);
//	bool DoSetHiddenAlways(bool hiddenAlways);

	bool AdjustInventoryOvernightPrice();
#ifndef TAKION_NO_OPTIONS
	virtual void MultiplyContractValuesByCoefficient(const unsigned int& coefficient)
	{
		PositionInventoryData::MultiplyContractValuesByCoefficient(coefficient);
		m_inventoryInvestment *= coefficient;
		m_inventoryNbboPrintOpenPnl *= coefficient;
	}
	virtual void DivideContractValuesByCoefficient(const unsigned int& coefficient)
	{
		PositionInventoryData::DivideContractValuesByCoefficient(coefficient);
		m_inventoryInvestment /= coefficient;
		m_inventoryNbboPrintOpenPnl /= coefficient;
	}
#endif

	virtual void WriteInventoryToAccountThread(int size, const Price& cost, bool inventoryFloating, bool leaveInLayout) override;
	virtual void WriteInventoryToMainThread(int size, const Price& cost, bool inventoryFloating, bool leaveInLayout) override;

	Money UpdateInventoryNbboPrintOpenPnl(const Price& printPrice);

	PositionData* m_position;
	bool m_positionHidden;
	bool m_hiddenAlways;
	Price m_inventoryPrice;
	int m_permanentInventorySize;
	int m_inventorySize;
	Price m_inventoryCost;
	Price m_permanentInventoryCost;
	Money m_inventoryInvestment;
	Money m_inventoryNbboPrintOpenPnl;
	bool m_inventoryFloating;
//	int m_size;
/*
	Price m_averagePrice;
	Price m_averageCost;
	unsigned int m_compactAveragePrice;
	unsigned int m_compactAverageCost;
*/
};

class TU_API PositionData : public PositionDataBase
{
friend class Account;
friend class PositionInventory;
public:
	virtual ~PositionData();

	static const int removeInventorySize;//-0x80000000;
	static const int inventoryEqualsPositionSize;//0x7FFFFFFF;

#ifndef TAKION_NO_OPTIONS
	const OptionSymbolBlock* GetOptionSymbolBlock() const{return m_optionSymbolBlock;}
	virtual bool isOption() const override{return m_optionSymbolBlock != NULL;}
	const unsigned __int64& GetOptionBlock() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetOptionBlock() : uint64Zero;}
	const unsigned __int64& GetUnderlierNumericSymbol() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetSymbolNum() : uint64Zero;}//m_numericSymbol;}
	virtual bool isCall() const override{return m_optionSymbolBlock && m_optionSymbolBlock->isCall();}
	unsigned char GetSuffix() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetSuffix() : ucharZero;}
	unsigned char GetCallPutFlags() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetCallPutFlags() : ucharZero;}
	const unsigned char& GetOptionFlags() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetFlags() : ucharZero;}
	virtual const unsigned int& GetStrikePrice() const override{return m_optionSymbolBlock ? m_optionSymbolBlock->GetStrikePrice() : uintZero;}
	unsigned int GetExpirationDate() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationDate() : 0;}
	bool GetExpirationTokens(unsigned char& expirationDay, unsigned char& expirationMonth, unsigned char& expirationYear) const
	{
		if(m_optionSymbolBlock)
		{
			m_optionSymbolBlock->GetExpirationTokens(expirationDay, expirationMonth, expirationYear);
			return true;
		}
		else
		{
			expirationDay = expirationMonth = expirationYear = '\0';
			return false;
		}
	}
	const unsigned char& GetExpirationType() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationType() : ucharZero;}
	const unsigned int& GetExpirationDays() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationDays() : uintZero;}
	const char& GetExpirationTypeChar() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetExpirationTypeChar() : space;}
	void GetOptionBlockAsString(std::string& optionSymbol, bool suffixSeparate) const{if(m_optionSymbolBlock)m_optionSymbolBlock->GetOptionBlockAsString(optionSymbol, suffixSeparate);}
/*
	void GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const
	{
		optionSymbol += suffixSeparate ? (const char*)&GetUnderlierNumericSymbol() : (const char*)&m_numericSymbol;
		if(m_optionSymbolBlock)
		{
			optionSymbol += ' ';
			m_optionSymbolBlock->GetOptionBlockAsString(optionSymbol, suffixSeparate);
		}
	}
*/
	bool GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const
	{
		if(m_numericSymbol)
		{
			if(m_optionSymbolBlock)
			{
				if(suffixSeparate)
				{
					const unsigned char suffix = m_optionSymbolBlock->GetSuffix();
					if(suffix)
					{
						unsigned __int64 underlierSymbol = GetUnderlierNumericSymbol();
						if(!underlierSymbol)underlierSymbol = OptionKey::CalculateUnderlierSymbol(m_numericSymbol, suffix);
						optionSymbol += (const char*)&underlierSymbol;
					}
					else optionSymbol += (const char*)&m_numericSymbol;
				}
				else optionSymbol += (const char*)&m_numericSymbol;
			
				optionSymbol += ' ';
				m_optionSymbolBlock->GetOptionBlockAsString(optionSymbol, suffixSeparate);
			}
			else
				optionSymbol += (const char*)&m_numericSymbol;

			return true;
		}
		return false;
	}
	const unsigned int& GetContractSize() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetContractSize() : uintOne;}
	const unsigned short& GetOptionType() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetOptionType() : ushortZero;}
/*
	const Position* GetUnderlierPosition() const{return m_optionSymbolBlock ? m_optionSymbolBlock->GetUnderlierPosition() : NULL;}
	Position* GetUnderlierPosition(){return m_optionSymbolBlock ? m_optionSymbolBlock->GetUnderlierPosition() : NULL;}
*/
//	virtual const unsigned int& GetCallSharesSoldPotential() const{return uintZero;}
//	virtual const unsigned int& GetPutSharesSoldPotential() const{return uintZero;}
#endif

	typedef std::set<unsigned int> UIntSet;

	virtual unsigned int CancelOrders(unsigned char sideMask,
		unsigned char directionMask,
		OrderCancelPick orderCancelPick,
		unsigned int tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL){return 0;}
////
	const bool& hasInventory() const{return !m_inventory ? boolFalse : boolTrue;}
	
//When calling from main thread Use LockInquiry (LockInquiryWait) before calling the function, and UnlockInquiry after you are done using PositionInventory*
	const PositionInventory* GetInventory() const{return m_inventory;}
//	const PositionInventory* GetConstInventory(){return m_inventory;}

//Inventory Inquiry functions called from main thread must be surounded with LockInquiry (LockInquiryWait) / UnlockInquiry
	const bool& isPositionHidden() const{return m_inventory ? m_inventory->isPositionHidden() : boolFalse;}
	const bool& isHiddenAlways() const{return m_inventory ? m_inventory->isHiddenAlways() : boolFalse;}
	bool isHidden() const{return m_inventory != NULL && m_inventory->isHidden();}
	const int& GetInventorySize() const{return m_inventory ? m_inventory->GetInventorySize() : intZero;}
	const Price& GetInventoryCost() const{return m_inventory ? m_inventory->GetInventoryCost() : Price::priceZero;}
	virtual const Money& GetInventoryInvestment() const override{return m_inventory ? m_inventory->GetInventoryInvestment() : Money::moneyZero;}
	virtual const Money& GetInventoryNbboPrintOpenPnl() const override{return m_inventory ? m_inventory->GetInventoryNbboPrintOpenPnl() : Money::moneyZero;}
	const bool& isInventoryFloating() const{return m_inventory ? m_inventory->isInventoryFloating() : boolFalse;}

//size = 0 - makes position hidden.
//size = removeInventorySize - remove inventory.
//size = inventoryEqualsPositionSize - makes inventory equal to position size.
//If isInThread, sets inventory immediately and returns true if inventory change; otherwise posts a message to the account thread and returs false.
	virtual bool SetInventory(int size, const Price& cost, bool inventoryFloating, bool leaveInLayout){return false;}

	bool hasPosition() const{return m_size || m_inventoryAdjustedSize;}

	const int& GetInventoryAdjustedSize() const{return m_inventory ? m_inventoryAdjustedSize : m_size;}
	const unsigned int& GetInventoryAdjustedPrice() const{return m_inventory ? m_inventoryAdjustedPrice : m_compactAveragePrice;}

	const int& GetSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventoryAdjustedSize : m_size;}

//	const int& GetInventoryAdjustedOvernightSize() const{return m_inventory ? m_inventoryAdjustedOvernightSize : m_overnightSize;}
//	const unsigned int& GetInventoryAdjustedOvernightPrice() const{return m_inventory ? m_inventoryAdjustedOvernightPrice : m_overnightAveragePriceCompact;}

//	const int& GetOvernightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventoryAdjustedOvernightSize : m_overnightSize;}
	const int& GetOvernightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightSize() : m_overnightSize;}
//	unsigned int GetAbsOvernightSizeInv(const bool& inventoryView) const
//	{
//		const int size = inventoryView && m_inventory ? m_inventoryAdjustedOvernightSize : m_overnightSize;
//		return size < 0 ? -size : size;
//	}
//	const unsigned int& GetOvernightCompactAveragePriceInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventoryAdjustedOvernightPrice : m_overnightAveragePriceCompact;}
	const unsigned int& GetOvernightCompactAveragePriceInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightAveragePriceCompact() : m_overnightAveragePriceCompact;}
	const Price& GetOvernightAveragePriceInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightAveragePrice() : m_overnightAveragePrice;}

	const unsigned int& GetAbsOvernightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAbsOvernightSize() : m_absOvernightSize;}

//	const int& GetSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetSize() : m_size;}
//	const unsigned int& GetCompactAveragePriceInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetCompactAveragePrice() : m_compactAveragePrice;}

//When calling from main thread Use LockInquiry (LockInquiryWait) before calling the function, and UnlockInquiry after you are done using PositionInventory*
	const unsigned int& GetAbsSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAbsSize() : m_absSize;}
#ifndef TAKION_NO_OPTIONS
	const Money& GetUnderlierValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetUnderlierValue() : m_underlierValue;}
	const Money& GetUnderlierValueLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetUnderlierValueLong() : GetUnderlierValueLong();}
	const Money& GetUnderlierValueShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetUnderlierValueShort() : GetUnderlierValueShort();}
	const unsigned int& GetAbsShareSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAbsShareSize() : m_absShareSize;}
	const unsigned int& GetAbsShareSizeLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAbsShareSizeLong() : m_absShareSize;}
	const unsigned int& GetAbsShareSizeShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAbsShareSizeShort() : m_absShareSize;}
	const int& GetShareSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetShareSize() : m_shareSize;}
#endif
//Position
	const int& GetSizeOrPhantomInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetSizeOrPhantom() : m_sizeOrPhantom;}
//	const int& GetOvernightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightSize() : m_overnightSize;}

	Money GetOvernightInvestmentInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightInvestment() : m_overnightInvestment;}
	Money GetOvernightInvestmentMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightInvestmentMe() : m_overnightInvestmentMe;}
	Money GetOvernightInvestmentBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightInvestmentBeta() : m_overnightInvestmentBeta;}

	Money GetInvestmentInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestment() : m_investment;}
	Money GetInvestmentMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentMe() : m_investmentMe;}
	Money GetInvestmentBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentBeta() : m_investmentBeta;}
	Money GetInvestmentCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentCost() : m_investmentCost;}

	const Money& GetMaxInvestmentLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentLong() : m_maxInvestmentLong;}
	const Money& GetMaxInvestmentShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentShort() : m_maxInvestmentShort;}
	const Money& GetMaxInvestmentInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestment() : m_maxInvestment;}

	const Money& GetMaxInvestmentLongMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentLongMe() : m_maxInvestmentLongMe;}
	const Money& GetMaxInvestmentShortMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentShortMe() : m_maxInvestmentShortMe;}
	const Money& GetMaxInvestmentMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentMe() : m_maxInvestmentMe;}

	const Money& GetMaxInvestmentLongBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentLongBeta() : m_maxInvestmentLongBeta;}
	const Money& GetMaxInvestmentShortBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentShortBeta() : m_maxInvestmentShortBeta;}
	const Money& GetMaxInvestmentBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentBeta() : m_maxInvestmentBeta;}

	Money GetLongInvestmentInv(const bool& inventoryView) const{return GetSizeInv(inventoryView) > 0 ? GetInvestmentInv(inventoryView) : Money::moneyZero;}
	Money GetShortInvestmentInv(const bool& inventoryView) const{return GetSizeInv(inventoryView) < 0 ? GetInvestmentInv(inventoryView) : Money::moneyZero;}

	Money GetLongInvestmentMeInv(const bool& inventoryView) const{return GetSizeInv(inventoryView) > 0 ? GetInvestmentMeInv(inventoryView) : Money::moneyZero;}
	Money GetShortInvestmentMeInv(const bool& inventoryView) const{return GetSizeInv(inventoryView) < 0 ? GetInvestmentMeInv(inventoryView) : Money::moneyZero;}

	Money GetLongInvestmentBetaInv(const bool& inventoryView) const{return GetSizeInv(inventoryView) > 0 ? GetInvestmentBetaInv(inventoryView) : Money::moneyZero;}
	Money GetShortInvestmentBetaInv(const bool& inventoryView) const{return GetSizeInv(inventoryView) < 0 ? GetInvestmentBetaInv(inventoryView) : Money::moneyZero;}

	Money GetSignedInvestmentInv(const bool& inventoryView) const{return GetSizeInv(inventoryView) >= 0 ? GetInvestmentInv(inventoryView) : -GetInvestmentInv(inventoryView);}

	const Price& GetAveragePriceInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAveragePrice() : m_averagePrice;}
	const unsigned int& GetCompactAveragePriceInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventoryAdjustedPrice : m_compactAveragePrice;}
	const Price& GetAverageCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAverageCost() : m_averageCost;}
	const unsigned int& GetCompactAverageCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetCompactAverageCost() : m_compactAverageCost;}

	const unsigned int& GetPotentialLongSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongSize() : m_potentialLongSize;}
	const unsigned int& GetPotentialShortSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortSize() : m_potentialShortSize;}
	const unsigned int& GetPotentialSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialSize() : m_potentialSize;}

	const unsigned int& GetPotentialLongNightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongNightSize() : m_potentialLongNightSize;}
	const unsigned int& GetPotentialShortNightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortNightSize() : m_potentialShortNightSize;}
	const unsigned int& GetPotentialNightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialNightSize() : m_potentialNightSize;}

	const Money& GetPotentialLongValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongValue() : m_potentialLongValue;}
	const Money& GetPotentialShortValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortValue() : m_potentialShortValue;}
	const Money& GetPotentialLongMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongMe() : m_potentialLongMe;}
	const Money& GetPotentialShortMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortMe() : m_potentialShortMe;}
	const Money& GetPotentialBetaLongValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialBetaLongValue() : m_potentialBetaLongValue;}
	const Money& GetPotentialBetaShortValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialBetaShortValue() : m_potentialBetaShortValue;}
	const Money& GetPotentialLongNightValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongNightValue() : m_potentialLongNightValue;}
	const Money& GetPotentialShortNightValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortNightValue() : m_potentialShortNightValue;}

	Money GetClosedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnl() : m_closedPnl;}
	Money GetClosedPnlCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlCost() : m_closedPnlCost;}

	Money GetOpenPnlLevel1CostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlLevel1Cost() : m_openPnlLevel1Cost;}
	Money GetOpenPnlPrintCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlPrintCost() : m_openPnlPrintCost;}
	Money GetOpenPnlLevel1Inv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlLevel1() : m_openPnlLevel1;}
	Money GetOpenPnlPrintInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlPrint() : m_openPnlPrint;}
	Money GetOpenPnlImbExNearInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlImbExNear() : m_openPnlImbExNear;}
	Money GetOpenPnlTCloseInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlTClose() : m_openPnlTClose;}
	Money GetOpenPnlActionPrintInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlActionPrint() : m_openPnlActionPrint;}
	Money GetOpenPnlActionInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlAction() : m_openPnlAction;}
	Money GetOpenPnlNbboPrintInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrint() : m_openPnlNbboPrint;}
	const Money& GetOpenPnlNbboPrintHiInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintHi() : m_openPnlNbboPrintHi;}
	const Money& GetOpenPnlNbboPrintLoInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintLo() : m_openPnlNbboPrintLo;}
	Money GetMarkedPnlNbboPrintInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrint() : m_markedPnlNbboPrint;}
	const Money& GetMarkedPnlNbboPrintHiInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintHi() : m_markedPnlNbboPrintHi;}
	const Money& GetMarkedPnlNbboPrintLoInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintLo() : m_markedPnlNbboPrintLo;}
	Money GetClosedPnlNetInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlNet() : m_closedPnlNet;}
	Money GetOpenCommissionFeeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenCommissionFee() : m_openCommissionFee;}

	Money GetAccountRTEquityInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetRTEquity() : m_rtEquity;}
	Money GetLeverageInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetLeverage() : m_leverage;}

	Money GetOpenPnlNbboPrintPreMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintPreMarket() : m_openPnlNbboPrintPreMarket;}
	Money GetOpenPnlNbboPrintMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintMarket() : m_openPnlNbboPrintMarket;}
	Money GetOpenPnlNbboPrintPostMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintPostMarket() : m_openPnlNbboPrintPostMarket;}

	Money GetClosedPnlPreMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlPreMarket() : m_closedPnlPreMarket;}
	Money GetClosedPnlMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlMarket() : m_closedPnlMarket;}
	Money GetClosedPnlPostMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlPostMarket() : m_closedPnlPostMarket;}

	Money GetMarkedPnlNbboPrintPreMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintPreMarket() : m_markedPnlNbboPrintPreMarket;}
	Money GetMarkedPnlNbboPrintMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintMarket() : m_markedPnlNbboPrintMarket;}
	Money GetMarkedPnlNbboPrintPostMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintPostMarket() : m_markedPnlNbboPrintPostMarket;}

	const SignedPrice& GetGpsLevel1Inv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetGpsLevel1() : m_gpsLevel1;}
	const SignedPrice& GetGpsPrintInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetGpsPrint() : m_gpsPrint;}
	const SignedPrice& GetGpsPrintHiInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetGpsPrintHi() : m_gpsPrintHi;}
	const SignedPrice& GetGpsPrintLoInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetGpsPrintLo() : m_gpsPrintLo;}
	const unsigned int& GetMinSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMinSize() : m_minSize;}
	const int& GetMaxSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxSize() : m_maxSize;}
	const unsigned int& GetPositionEnterTimeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPositionEnterTime() : m_positionEnterTime;}

protected:
	PositionData(const char* symbol,
		SecurityType securityType,
		int compactBeta,
		unsigned char margin,
		unsigned char PM_EL_Rate,// = 15,
		unsigned char PM_ES_Rate,// = 15,
		unsigned char PM_HL_Rate,// = 15,
		unsigned char PM_HS_Rate,// = 15,
		unsigned char EL_Rate,// = 25,
		unsigned char ES_Rate,// = 30,
		unsigned char HL_Rate,// = 30,
		unsigned char HS_Rate,// = 30,
		unsigned char Fed_Req,// = 50,
		unsigned char Asset_Type,// = 'E',
		bool Marginable,// = true,
		unsigned char Sec_Type,// = 'C',
		unsigned char Status,// = 0):
		bool PortfolioManaged,
#ifndef TAKION_NO_OPTIONS
		OptionSymbolBlock* optionSymbolBlock,
#endif
/*
#ifdef FIRM_VALUES
		,FirmPosition* firmPosition
#endif
*/
		unsigned int timeLoaded);//0 if not loaded from the database

	virtual void WritePositionUpdateLeverageMessageToMainThread() const{}
/*
	virtual void UpdateLeverage() override
	{
		PositionDataBase::UpdateLeverage();
		WritePositionUpdateLeverageMessageToMainThread();
	}
*/
#ifndef TAKION_NO_OPTIONS
	virtual void MultiplyContractValuesByCoefficient(const unsigned int& coefficient)
	{
		PositionDataBase::MultiplyContractValuesByCoefficient(coefficient);
		if(m_inventory)m_inventory->MultiplyContractValuesByCoefficient(coefficient);
	}
	virtual void DivideContractValuesByCoefficient(const unsigned int& coefficient)
	{
		PositionDataBase::DivideContractValuesByCoefficient(coefficient);
		if(m_inventory)m_inventory->DivideContractValuesByCoefficient(coefficient);
	}
	OptionSymbolBlock* m_optionSymbolBlock;
	UnderlierInfo* m_underlierInfo;
#endif
//	PositionInventory* GetInventory(){return m_inventory;}

//	bool DoSetInventory(int size, bool hiddenAlways);
	bool DoSetInventory(int size, const Price& cost, bool inventoryFloating, bool hiddenAlways);
	
	bool DoRemoveInventory();

	bool DoSetHiddenAlways(bool hiddenAlways);

//	void AdjustOvernightInventory();

	virtual void ClosingPriceSet() override;
	virtual void TodaysClosingPriceSet() override;

	void SetOpenPnlNbboPrintHiInv(const Money& pnl){if(m_inventory)m_inventory->SetOpenPnlNbboPrintHi(pnl);}
	void SetOpenPnlNbboPrintLoInv(const Money& pnl){if(m_inventory)m_inventory->SetOpenPnlNbboPrintLo(pnl);}
	void SetMarkedPnlNbboPrintHiInv(const Money& pnl){if(m_inventory)m_inventory->SetMarkedPnlNbboPrintHi(pnl);}
	void SetMarkedPnlNbboPrintLoInv(const Money& pnl){if(m_inventory)m_inventory->SetMarkedPnlNbboPrintLo(pnl);}

	void SetMaxInvestmentInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestment(investment);}
	void SetMaxInvestmentLongInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentLong(investment);}
	void SetMaxInvestmentShortInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentShort(investment);}

	void SetMaxInvestmentMeInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentMe(investment);}
	void SetMaxInvestmentLongMeInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentLongMe(investment);}
	void SetMaxInvestmentShortMeInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentShortMe(investment);}

	void SetMaxInvestmentBetaInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentBeta(investment);}
	void SetMaxInvestmentLongBetaInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentLongBeta(investment);}
	void SetMaxInvestmentShortBetaInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentShortBeta(investment);}

	void SetConditionallyOpenPnlNbboPrintHiInv(const Money& pnl){if(m_inventory)m_inventory->SetConditionallyOpenPnlNbboPrintHi(pnl);}
	void SetConditionallyOpenPnlNbboPrintLoInv(const Money& pnl){if(m_inventory)m_inventory->SetConditionallyOpenPnlNbboPrintLo(pnl);}
	void SetConditionallyMarkedPnlNbboPrintHiInv(const Money& pnl){if(m_inventory)m_inventory->SetConditionallyMarkedPnlNbboPrintHi(pnl);}
	void SetConditionallyMarkedPnlNbboPrintLoInv(const Money& pnl){if(m_inventory)m_inventory->SetConditionallyMarkedPnlNbboPrintLo(pnl);}

	void SetConditionallyMaxInvestmentInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestment(investment);}
	void SetConditionallyMaxInvestmentLongInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentLong(investment);}
	void SetConditionallyMaxInvestmentShortInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentShort(investment);}

	void SetConditionallyMaxInvestmentMeInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentMe(investment);}
	void SetConditionallyMaxInvestmentLongMeInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentLongMe(investment);}
	void SetConditionallyMaxInvestmentShortMeInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentShortMe(investment);}

	void SetConditionallyMaxInvestmentBetaInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentBeta(investment);}
	void SetConditionallyMaxInvestmentLongBetaInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentLongBeta(investment);}
	void SetConditionallyMaxInvestmentShortBetaInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentShortBeta(investment);}

	PositionInventory* m_inventory;
	int m_inventoryAdjustedSize;
	unsigned int m_inventoryAdjustedPrice;
//	int m_inventoryAdjustedOvernightSize;
//	unsigned int m_inventoryAdjustedOvernightPrice;
};

class PositionGroup;

class TU_API PositionGroupObserver : public PositionDataBase, public Observer
{
friend class PositionGroup;
public:
	PositionGroupObserver(const Position* position, PositionGroup* positionGroup);
	DECLARE_NED_NEW
	const Position* GetPosition() const{return m_position;}
	const PositionGroup* GetPositionGroup() const{return m_positionGroup;}
	const Money& GetLoadedMoney() const{return m_loadedMoney;}//loaded from the database
	const Money& GetOvernightCost() const{return m_overnightCost;}
#ifndef TAKION_NO_OPTIONS
	virtual const unsigned int& GetCallSharesSoldPotential() const{return m_callSharesSoldPotential;}
	virtual const unsigned int& GetPutSharesSoldPotential() const{return m_putSharesSoldPotential;}
	virtual const unsigned int& GetStrikePrice() const override{return m_strikePrice;}
	virtual bool isCall() const override{return m_isCall;}
	virtual bool isOption() const override{return m_isOption;}
#endif
	virtual unsigned int GetOrdersPendingCount() const override{return m_ordersPendingCount;}
	virtual unsigned int GetPendingOrdersLong() const override{return m_ordersPendingLongCount;}
	virtual unsigned int GetPendingOrdersSell() const override{return m_ordersPendingSellCount;}
	virtual unsigned int GetPendingOrdersShort() const override{return m_ordersPendingShortCount;}
	virtual unsigned int GetOrdersStuckCount() const override{return m_ordersStuckCount;}
	virtual unsigned int GetOrdersBlockedCount() const override{return m_ordersBlockedCount;}
	virtual unsigned int GetOrdersCancelRejectedCount() const override{return m_ordersCancelRejectedCount;}
	virtual unsigned int GetOrdersCancelBlockedCount() const override{return m_ordersCancelBlockedCount;}
	virtual unsigned int GetOrdersWithCancelProblemCount() const override{return m_ordersWithCancelProblemCount;}
	virtual bool isStockLoanInitialized() const override{return m_stockLoanInitialized;}//
	virtual const unsigned int& GetAccountCount() const override{return m_accountCount;}
	virtual const unsigned char& isHTB() const override{return m_htb;}
	virtual const bool& isHtbInitialized() const override{return m_htbInitialized;}
	virtual const Money& GetInventoryInvestment() const override{return m_inventoryInvestment;}
	virtual const Money& GetInventoryNbboPrintOpenPnl() const override{return m_inventoryNbboPrintOpenPnl;}
	virtual Money GetHardBpUsed() const override{return m_hardBpUsed;}//can be different from m_investment if a retail account has overnight position.
	virtual Money GetHardMeUsed() const override{return m_hardMeUsed;}//can be different from m_investment if a retail account has overnight position.
	virtual Money GetBpUsed() const override{return m_bpUsed;}//max of m_potentialLongValue and m_potentialShortValue
	virtual Money GetMeUsed() const override{return m_meUsed;}//max of m_potentialLongMe and m_potentialShortMe
	virtual Money GetNightBpUsed() const override{return m_nightBpUsed;}//max of m_potentialLongNightValue and m_potentialShortNightValue i.e. potential value without the OPG pending orders
	virtual Money GetBpBetaUsed() const override{return m_bpBetaUsed;}//max of m_potentialLongBetaValue and m_potentialShortBetaValue
	virtual void Reset();
protected:
	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL) override;//Notified in the main thread only
	void UpdatePosition();//PositionGroupObserver* positionGroupObserver);
//	void UpdateSecurity(const Message* message, const Message* info);
	const Position* m_position;
	PositionGroup* m_positionGroup;
//	Money m_overnightMoney;
	Money m_loadedMoney;
	Money m_overnightCost;
#ifndef TAKION_NO_OPTIONS
	unsigned int m_callSharesSoldPotential;
	unsigned int m_putSharesSoldPotential;
	unsigned int m_strikePrice;
	bool m_isCall;
	bool m_isOption;
#endif
	unsigned int m_ordersPendingCount;
	unsigned int m_ordersPendingLongCount;
	unsigned int m_ordersPendingSellCount;
	unsigned int m_ordersPendingShortCount;
	unsigned int m_ordersStuckCount;
	unsigned int m_ordersBlockedCount;
	unsigned int m_ordersCancelRejectedCount;
	unsigned int m_ordersCancelBlockedCount;
	unsigned int m_ordersWithCancelProblemCount;
	unsigned int m_accountCount;
	unsigned char m_htb;
	bool m_htbInitialized;
	bool m_stockLoanInitialized;
	Money m_inventoryInvestment;
	Money m_inventoryNbboPrintOpenPnl;
	Money m_hardBpUsed;//can be different from m_investment if a retail account has overnight position.
	Money m_hardMeUsed;//can be different from m_investment if a retail account has overnight position.
	Money m_bpUsed;
	Money m_nightBpUsed;
	Money m_bpBetaUsed;
	Money m_meUsed;
};

typedef CMap<const Position*, const Position* const&, PositionGroupObserver*, PositionGroupObserver* const&> PositionGroupObserverMap;

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

#ifdef FIRM_VALUES
	const FirmPosition* GetFirmPosition() const{return m_firmPosition;}
	virtual int GetFirmSize() const override;
	virtual int GetFirmPotentialShortSize() const override;
	virtual const unsigned char& GetUntradeableLevel() const override{return m_untradeableLevel;}//For Supervisor only. 0 - tradable; 1 - pending; 2 - untradeable.
	virtual const unsigned char& GetUntradeable() const override{return m_firmPosition ? m_firmPosition->GetMainThreadUntradeable() : ucharZero;}
#endif

	PositionGroupObserver* AddPosition(const Position* position);
	PositionGroupObserver* RemovePosition(const Position* position);
	void ClearPositions();

	virtual void Reset();
	bool isEmpty() const{return m_positionGroupObserverMap.IsEmpty() == TRUE;}

	virtual void NotifyPositionUpdated() const = 0;//{}

	const Money& GetLoadedMoney() const{return m_loadedMoney;}//loaded from the database
	const Money& GetOvernightCost() const{return m_overnightCost;}
#ifndef TAKION_NO_OPTIONS
	virtual const unsigned int& GetCallSharesSoldPotential() const{return m_callSharesSoldPotential;}
	virtual const unsigned int& GetPutSharesSoldPotential() const{return m_putSharesSoldPotential;}
#endif
	virtual unsigned int GetOrdersPendingCount() const override{return m_ordersPendingCount;}
	virtual unsigned int GetPendingOrdersLong() const override{return m_ordersPendingLongCount;}
	virtual unsigned int GetPendingOrdersSell() const override{return m_ordersPendingSellCount;}
	virtual unsigned int GetPendingOrdersShort() const override{return m_ordersPendingShortCount;}
	virtual unsigned int GetOrdersStuckCount() const override{return m_ordersStuckCount;}
	virtual unsigned int GetOrdersBlockedCount() const override{return m_ordersBlockedCount;}
	virtual unsigned int GetOrdersCancelRejectedCount() const override{return m_ordersCancelRejectedCount;}
	virtual unsigned int GetOrdersCancelBlockedCount() const override{return m_ordersCancelBlockedCount;}
	virtual unsigned int GetOrdersWithCancelProblemCount() const override{return m_ordersWithCancelProblemCount;}
	virtual const Money& GetInventoryInvestment() const override{return m_inventoryInvestment;}
	virtual const Money& GetInventoryNbboPrintOpenPnl() const override{return m_inventoryNbboPrintOpenPnl;}

	virtual Money GetHardBpUsed() const override{return m_hardBpUsed;}//can be different from m_investment if a retail account has overnight position.
	virtual Money GetHardMeUsed() const override{return m_hardMeUsed;}//can be different from m_investment if a retail account has overnight position.
	virtual Money GetBpUsed() const override{return m_bpUsed;}//max of m_potentialLongValue and m_potentialShortValue
	virtual Money GetMeUsed() const override{return m_meUsed;}//max of m_potentialLongMe and m_potentialShortMe
	virtual Money GetNightBpUsed() const override{return m_nightBpUsed;}//max of m_potentialLongNightValue and m_potentialShortNightValue i.e. potential value without the OPG pending orders
	virtual Money GetBpBetaUsed() const override{return m_bpBetaUsed;}//max of m_potentialLongBetaValue and m_potentialShortBetaValue

	virtual bool isStockLoanInitialized() const override{return m_stockLoanInitializedCount != 0;}

	virtual const unsigned int& GetAccountCount() const override{return m_accountCount;}

//	virtual const unsigned char& isHTB() const override{return m_htb;}
//	virtual const bool& isHtbInitialized() const override{return m_htbInitialized;}

	virtual unsigned int GetHtbString() const override{return m_htbString;}
	virtual bool HasHTB() const override{return 'E' != m_htbString;}
//	virtual const unsigned int& GetBorrowAvailableSize() const{return m_borrowAvailableSize;}

	typedef std::map<unsigned int, unsigned short> UIntUShortMap;
	typedef std::map<int, unsigned short> IntUShortMap;
	typedef std::map<unsigned char, unsigned short> UCharUShortMap;
	static bool UpdateMaxUInt(const UIntUShortMap& uintMap, unsigned int& maxValue)
	{
		if(uintMap.empty())
		{
			if(maxValue)
			{
				maxValue = 0;
				return true;
			}
		}
		else
		{
			const unsigned int val = uintMap.rbegin()->first;
			if(val != maxValue)
			{
				maxValue = val;
				return true;
			}
		}
		return false;
	}
protected:
	PositionGroup(const char* const& symbol,
		const SecurityType& securityType,
		const int& compactBeta,
		const unsigned char& margin,
		const unsigned char& PM_EL_Rate,// = 15,
		const unsigned char& PM_ES_Rate,// = 15,
		const unsigned char& PM_HL_Rate,// = 15,
		const unsigned char& PM_HS_Rate,// = 15,
		const unsigned char& EL_Rate,// = 25,
		const unsigned char& ES_Rate,// = 30,
		const unsigned char& HL_Rate,// = 30,
		const unsigned char& HS_Rate,// = 30,
		const unsigned char& Fed_Req,// = 50,
		const unsigned char& Asset_Type,// = 'E',
		const bool& Marginable,// = true,
		const unsigned char& Sec_Type,// = 'C',
		const unsigned char& Status,// = 0):
		const bool& PortfolioManaged// = true,
#ifndef TAKION_NO_OPTIONS
		,OptionSymbolBlock* const& optionSymbolBlock
#endif
		):
		PositionData(symbol,
			securityType,
			compactBeta,
			margin,
			PM_EL_Rate,// = 15,
			PM_ES_Rate,// = 15,
			PM_HL_Rate,// = 15,
			PM_HS_Rate,// = 15,
			EL_Rate,// = 25,
			ES_Rate,// = 30,
			HL_Rate,// = 30,
			HS_Rate,// = 30,
			Fed_Req,// = 50,
			Asset_Type,// = 'E',
			Marginable,// = true,
			Sec_Type,// = 'C',
			Status,// = 0):
			PortfolioManaged,
#ifndef TAKION_NO_OPTIONS
			optionSymbolBlock,
#endif
			0),
#ifndef TAKION_NO_OPTIONS
		m_callSharesSoldPotential(0),
		m_putSharesSoldPotential(0),
#endif
		m_ordersPendingCount(0),
		m_ordersPendingLongCount(0),
		m_ordersPendingSellCount(0),
		m_ordersPendingShortCount(0),
		m_ordersStuckCount(0),
		m_ordersBlockedCount(0),
		m_ordersCancelRejectedCount(0),
		m_ordersCancelBlockedCount(0),
		m_ordersWithCancelProblemCount(0),
		m_stockLoanInitializedCount(0),
		m_accountCount(0),
#ifdef FIRM_VALUES
		m_firmPosition(NULL),
		m_untradeableLevel(UL_TRADABLE),
#endif
//		m_htb(ucharZero),
/*
		m_timeLoadedMapEnd(m_timeLoadedMap.end()),
		m_timePositionEnterMapEnd(m_timePositionEnterMap.end()),
		m_borrowAvailableSizeMapEnd(m_borrowAvailableSizeMap.end()),
		m_compactBorrowDiscountedPriceMapEnd(m_compactBorrowDiscountedPriceMap.end()),
		m_compactBetaMapEnd(m_compactBetaMap.end()),
		m_marginMapEnd(m_marginMap.end()),
*/
		m_htbAccountCountMapEnd(m_htbAccountCountMap.end()),
		m_htbString(0),
		m_marginableCount(0)
//		m_borrowAvailableSize(0)
	{
		UpdateHtbString();
	}
	void UpdateGps();
	void UpdateTicketAverage();

	virtual void NotificationFromPosition(PositionGroupObserver* pgo, const Message* message, const Observable* from, const Message* info);

	void DestroyPositionObservers();
	PositionGroupObserverMap m_positionGroupObserverMap;

	Money m_inventoryInvestment;
	Money m_inventoryNbboPrintOpenPnl;
	Money m_hardBpUsed;//can be different from m_investment if a retail account has overnight position.
	Money m_hardMeUsed;//can be different from m_investment if a retail account has overnight position.
	Money m_bpUsed;
	Money m_nightBpUsed;
	Money m_bpBetaUsed;
	Money m_meUsed;

//	Money m_overnightMoney;
	Money m_loadedMoney;
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
	unsigned int m_ordersBlockedCount;
	unsigned int m_ordersCancelRejectedCount;
	unsigned int m_ordersCancelBlockedCount;
	unsigned int m_ordersWithCancelProblemCount;

	unsigned int m_stockLoanInitializedCount;

	unsigned int m_accountCount;
#ifdef FIRM_VALUES
	const FirmPosition* m_firmPosition;
//	bool m_firmPositionSubscribed;
	unsigned char m_untradeableLevel;//For Supervisor only. 0 - tradable; 1 - pending; 2 - untradeable.
#endif
//	unsigned char m_htb;
//	bool m_htbInitialized;

	template<class T>
	static void UpdateVal(const T& oldVal, const T& newVal, std::map<T, unsigned short>& valMap, T& val)
	{
		if(oldVal != newVal)
		{
			typedef std::map<T, unsigned short> MapType;
			bool changed = false;
			MapType::iterator found;
			MapType::iterator end = valMap.end();
			if(oldVal)
			{
				found = valMap.find(oldVal);
				if(found != end)
				{
					if(found->second > 1)--found->second;
					else
					{
						valMap.erase(found);
						changed = true;
					}
				}
			}
			if(newVal)
			{
				found = valMap.find(newVal);
				if(found == end)
				{
					valMap.insert(MapType::value_type(newVal, 1));
					changed = true;
				}
				else ++found->second;
			}
			if(changed)val = valMap.empty() ? 0 : valMap.begin()->first;
		}
	}
	template<class T>
	static void UpdateValReversed(const T& oldVal, const T& newVal, std::map<T, unsigned short>& valMap, T& val)
	{
		if(oldVal != newVal)
		{
			typedef std::map<T, unsigned short> MapType;
			bool changed = false;
			MapType::iterator found;
			MapType::iterator end = valMap.end();
			if(oldVal)
			{
				found = valMap.find(oldVal);
				if(found != end)
				{
					if(found->second > 1)--found->second;
					else
					{
						valMap.erase(found);
						changed = true;
					}
				}
			}
			if(newVal)
			{
				found = valMap.find(newVal);
				if(found == end)
				{
					valMap.insert(MapType::value_type(newVal, 1));
					changed = true;
				}
				else ++found->second;
			}
			if(changed)val = valMap.empty() ? 0 : valMap.rbegin()->first;
		}
	}

	void UpdateTimeLoaded(const unsigned int& oldTimeLoaded, const unsigned int& newTimeLoaded)
	{
		UpdateValReversed(oldTimeLoaded, newTimeLoaded, m_timeLoadedMap, m_timeLoaded);
	}
	UIntUShortMap m_timeLoadedMap;
//	UIntUShortMap::const_iterator m_timeLoadedMapEnd;

	void UpdatePositionEnterTime(const unsigned int& oldTime, const unsigned int& newTime)
	{
		UpdateValReversed(oldTime, newTime, m_timePositionEnterMap, m_positionEnterTime);
	}
	UIntUShortMap m_timePositionEnterMap;
//	UIntUShortMap::const_iterator m_timePositionEnterMapEnd;

	void UpdateBorrowAvailableSize(const unsigned int& oldSize, const unsigned int& newSize)
	{
		UpdateValReversed(oldSize, newSize, m_borrowAvailableSizeMap, m_borrowAvailableSize);
	}
	UIntUShortMap m_borrowAvailableSizeMap;
//	UIntUShortMap::const_iterator m_borrowAvailableSizeMapEnd;

	void UpdateCompactBorrowDiscountedPrice(const unsigned int& oldPrice, const unsigned int& newPrice)
	{
		UpdateValReversed(oldPrice, newPrice, m_compactBorrowDiscountedPriceMap, m_compactBorrowDiscountedPrice);
	}
	UIntUShortMap m_compactBorrowDiscountedPriceMap;
//	UIntUShortMap::const_iterator m_compactBorrowDiscountedPriceMapEnd;

	void UpdateCompactBeta(const int& oldBeta, const int& newBeta)
	{
		UpdateVal(oldBeta, newBeta, m_compactBetaMap, m_compactBeta);
	}
	IntUShortMap m_compactBetaMap;
//	IntUShortMap::const_iterator m_compactBetaMapEnd;

	void UpdateMargin(const unsigned char& oldMargin, const unsigned char& newMargin)
	{
		UpdateVal(oldMargin, newMargin, m_marginMap, m_margin);
	}
	UCharUShortMap m_marginMap;
//	UCharUShortMap::const_iterator m_marginMapEnd;

	void UpdatePmElRate(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_PmElRateMap, m_PM_EL_Rate);
	}
	UCharUShortMap m_PmElRateMap;

	void UpdatePmEsRate(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_PmEsRateMap, m_PM_ES_Rate);
	}
	UCharUShortMap m_PmEsRateMap;

	void UpdatePmHlRate(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_PmHlRateMap, m_PM_HL_Rate);
	}
	UCharUShortMap m_PmHlRateMap;

	void UpdatePmHsRate(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_PmHsRateMap, m_PM_HS_Rate);
	}
	UCharUShortMap m_PmHsRateMap;
//
	void UpdateElRate(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_ElRateMap, m_EL_Rate);
	}
	UCharUShortMap m_ElRateMap;

	void UpdateEsRate(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_EsRateMap, m_ES_Rate);
	}
	UCharUShortMap m_EsRateMap;

	void UpdateHlRate(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_HlRateMap, m_HL_Rate);
	}
	UCharUShortMap m_HlRateMap;

	void UpdateHsRate(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_HsRateMap, m_HS_Rate);
	}
	UCharUShortMap m_HsRateMap;

	void UpdateFedReq(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_FedReqMap, m_Fed_Req);
	}
	UCharUShortMap m_FedReqMap;

	void UpdateAssetType(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_AssetTypeMap, m_Asset_Type);
	}
	UCharUShortMap m_AssetTypeMap;

	void UpdateSecType(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_SecTypeMap, m_Sec_Type);
	}
	UCharUShortMap m_SecTypeMap;

	void UpdateStatus(const unsigned char& oldVal, const unsigned char& newVal)
	{
		UpdateVal(oldVal, newVal, m_StatusMap, m_Status);
	}
	UCharUShortMap m_StatusMap;

	void UpdateMarginable(const bool& oldVal, const bool& newVal)
	{
		if(oldVal != newVal)
		{
			if(oldVal)
			{
				if(m_marginableCount > 1)--m_marginableCount;
				else if(m_marginableCount)
				{
					--m_marginableCount;
					m_Marginable = false;
				}
			}
			else
			{
				if(!m_Marginable)m_Marginable = true;
				++m_marginableCount;
			}
		}
	}
	unsigned short m_marginableCount;
//
	void UpdatePortfolioManaged(const bool& oldVal, const bool& newVal)
	{
		if(oldVal != newVal)
		{
			if(oldVal)
			{
				if(m_portfolioManagedCount > 1)--m_portfolioManagedCount;
				else if(m_portfolioManagedCount)
				{
					--m_portfolioManagedCount;
					m_PortfolioManaged = false;
				}
			}
			else
			{
				if(!m_PortfolioManaged)m_PortfolioManaged = true;
				++m_portfolioManagedCount;
			}
		}
	}
	unsigned short m_portfolioManagedCount;
//
	UCharUShortMap m_htbAccountCountMap;
	UCharUShortMap::iterator m_htbAccountCountMapEnd;
	unsigned int m_htbString;

	void UpdateHtb(unsigned char& htb, bool& htbInitialized, unsigned char htbNew, const bool htbInitializedNew);
	void AddHtb(const unsigned char htbOld, const unsigned char htbNew);
	void RemoveHtb(const unsigned char htbNew);
	void UpdateHtbString();
	void UpdateStockLoanInitializedCount(bool& stockLoanInitialized, const bool stockLoanInitializedNew);
private:
	PositionGroup(const PositionGroup& other);
	PositionGroup& operator=(const PositionGroup& other);
};

typedef CMap<unsigned __int64, const unsigned __int64&, PositionGroup*, PositionGroup* const&> PositionGroupMap;
#ifndef TAKION_NO_OPTIONS
typedef CMap<OptionSymbolBlockKey, const OptionSymbolBlockKey&, PositionGroup*, PositionGroup* const&> OptionPositionGroupMap;
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

	PositionGroup* FindPosition(const unsigned __int64& rootSymbol
#ifndef TAKION_NO_OPTIONS
		, const unsigned __int64& optionBlock
#endif
		) const
	{
		return
#ifndef TAKION_NO_OPTIONS
			optionBlock ? FindOptionPosition(OptionSymbolBlockKey(rootSymbol, optionBlock)):
#endif
			FindStockPosition(rootSymbol);
	}
	const PositionGroup* RemovePositionGroupIfEmpty(const unsigned __int64& rootSymbol
#ifndef TAKION_NO_OPTIONS
		, const unsigned __int64& optionBlock
#endif
		)
	{
		return
#ifndef TAKION_NO_OPTIONS
			optionBlock ? RemoveOptionPositionGroupIfEmpty(OptionSymbolBlockKey(rootSymbol, optionBlock)):
#endif
			RemoveStockPositionGroupIfEmpty(rootSymbol);
	}
#ifndef TAKION_NO_OPTIONS
	const OptionPositionGroupMap& GetOptionPositionGroupMap() const{return m_optionPositionGroupMap;}
	PositionGroup* FindOptionPosition(const OptionSymbolBlockKey& optionSymbolBlockKey) const
	{
		const OptionPositionGroupMap::CPair* found = m_optionPositionGroupMap.PLookup(optionSymbolBlockKey);
		return found ? found->value : NULL;
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

//Order Hash Tables for each Position are initialized only when the first Order gets into the Position.
//It can save some memory when loading Accounts which are not going to be active for the rest of the day.
//#define DELAY_POSITION_INIT_HASH_TABLES

class TU_API Position : public PositionData//public Observable, public TakionLock
{
friend class AccountInventoryData;
friend class Account;
friend class Order;
friend class PositionInventory;
public:
//	virtual ~Position();
#if (_MSC_VER > 1600)
	typedef std::unordered_set<Order*> OrderSet;
#else
	typedef std::hash_set<Order*> OrderSet;
#endif
	typedef std::list<Order*> OrderList;
//	typedef std::set<Order*, lessOrderReplace> OrderReplaceSet;

	virtual Account* GetAccount() const{return m_account;}
	virtual Position* GetAccountPosition(){return this;}
	virtual const Position* GetAccountPosition() const{return this;}
	virtual const char* GetAccountId() const;
	virtual const char* GetAccountUserName() const;

	virtual unsigned int GetThreadId() const;//{return m_account->GetThreadId();}

	virtual const char& GetPhantom() const override{return m_phantom;}//+1 - long, -1 - short, 0 - flat
	virtual const unsigned char& GetAbsPhantom() const override{return m_absPhantom;}//1 - has phantom, 0 - no phantom

	virtual bool isPreMarket() const override;
	virtual bool isMarketOpen() const override;
	virtual bool isMarketClosedForTheDay() const override;
	virtual unsigned char GetMarketState() const override;

//	virtual const int& GetSizeOrPhantom() const override{return m_sizeOrPhantom;}

	unsigned int CalculateOrderSizeByClosePositionPercent(const bool& buy,
		const bool& inventoryView,
		const unsigned int& absPositionSize,
		const unsigned int& closePositionSize,
		const unsigned int& openPositionSize) const
	{
		unsigned int orderSize = openPositionSize;
		if(closePositionSize && absPositionSize)
		{
			int size = GetSizeInv(inventoryView);
			if(size)
			{
				if(buy == (size < 0))//closes
				{
					unsigned int absSize = size < 0 ? (unsigned int)-size : (unsigned int)size;
					if(absPositionSize == closePositionSize)orderSize += absSize;
					else orderSize += absSize * closePositionSize / absPositionSize;
				}
			}
		}
		return orderSize;
	}


	Money GetOpenPnlForLoss() const{return m_openPnlAction;}
//	Money GetMarkedPnlForLoss() const{return m_markedPnlNbboPrint;}
	__int64 GetOpenPnlForLossDollars() const{return GetOpenPnlForLoss().GetDollars();}
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

	bool HasCancelledOrRejectedOrders() const
	{
		unsigned char i = TU_ORDER_STATUS_CANCELED * TU_ORDER_SIDE_COUNT;
		unsigned char end = i + TU_ORDER_SIDE_COUNT;
		for(; i < end; ++i)
		{
			if(!m_orders[i].IsEmpty())return true;
		}
		i = TU_ORDER_STATUS_REJECTED * TU_ORDER_SIDE_COUNT;
		end = i + TU_ORDER_SIDE_COUNT;
		for(; i < end; ++i)
		{
			if(!m_orders[i].IsEmpty())return true;
		}
		return false;
	}

	bool isDeletable() const//Call between LockInquiryWait and UnlockIquiry 
	{
		return !m_sharesTraded
			&& !m_size
			&& !m_overnightSize
			&& !m_borrowSize
			&& m_ordersPending.IsEmpty()
			&& m_ordersAlgorithm.IsEmpty()
			&& !HasCancelledOrRejectedOrders()
			&& !m_inventory
			&& !m_phantom
#ifndef TAKION_NO_OPTIONS
			&& !GetOptionPositionCount()
#endif
			;
	}
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
	const OrderMap& GetOrdersBlocked() const{return m_ordersBlocked;}
	const OrderMap& GetOrdersAlgorithm() const{return m_ordersAlgorithm;}
	const OrderMap& GetGtcOrdersAlgorithm() const{return m_gtcOrdersAlgorithm;}

	unsigned int GetOrdersAlgorithmCount() const{return (unsigned int)m_ordersAlgorithm.GetCount();}
	unsigned int GetGtcOrdersAlgorithmCount() const{return (unsigned int)m_gtcOrdersAlgorithm.GetCount();}
	unsigned int GetOrdersAlgorithmCount(const bool& exceptGtc) const
	{
		unsigned int ret = GetOrdersAlgorithmCount();
		if(exceptGtc)
		{
			const unsigned int gtcCount = GetGtcOrdersAlgorithmCount();
			if(gtcCount)
			{
				if(ret > gtcCount)ret -= gtcCount;
				else ret = 0;
			}
		}
		return ret;
	}

	const OrderMap& GetOrdersPending() const{return m_ordersPending;}//Unacknowledged and Acknowledged
	virtual unsigned int GetOrdersPendingCount() const override{return (unsigned int)m_ordersPending.GetCount();}

	const OrderMap& GetOrdersPendingStopTrailing() const{return m_ordersPendingStopTrailing;}//Unacknowledged and Acknowledged
	unsigned int GetOrdersPendingStopTrailingCount() const{return (unsigned int)m_ordersPendingStopTrailing.GetCount();}

	const OrderMap& GetOrdersStuck() const{return m_ordersStuck;}
	const OrderMap& GetOrdersCancelRejected() const{return m_ordersCancelRejected;}
	const OrderMap& GetOrdersCancelBlocked() const{return m_ordersCancelBlocked;}
	const OrderMap& GetOrdersWithCancelProblem() const{return m_ordersWithCancelProblem;}

	virtual unsigned int GetOrdersStuckCount() const override{return (unsigned int)m_ordersStuck.GetCount();}
	virtual unsigned int GetOrdersBlockedCount() const override{return (unsigned int)m_ordersBlocked.GetCount();}
	virtual unsigned int GetOrdersCancelRejectedCount() const override{return (unsigned int)m_ordersCancelRejected.GetCount();}
	virtual unsigned int GetOrdersCancelBlockedCount() const override{return (unsigned int)m_ordersCancelBlocked.GetCount();}
	virtual unsigned int GetOrdersWithCancelProblemCount() const override{return (unsigned int)m_ordersWithCancelProblem.GetCount();}

	Order* FindOrderUnacknowledged(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersUnacknowledged.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderAcknowledged(const unsigned int& serverId) const{const OrderMap::CPair* found = m_ordersAcknowledged.PLookup(serverId); return found ? found->value : NULL;}
	Order* FindOrderRejected(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersRejected.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderBlocked(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersBlocked.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderAlgorithm(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersAlgorithm.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindGtcOrderAlgorithm(const unsigned int& clientId) const{const OrderMap::CPair* found = m_gtcOrdersAlgorithm.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderPending(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersPending.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderPendingStopTrailing(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersPendingStopTrailing.PLookup(clientId); return found ? found->value : NULL;}

	const OrderMap& GetOrders(OrderStatus orderStatus, OrderSide orderSide) const{return m_orders[orderStatus * TU_ORDER_SIDE_COUNT + orderSide];}
	OrderMap& GetOrders(OrderStatus orderStatus, OrderSide orderSide){return m_orders[orderStatus * TU_ORDER_SIDE_COUNT + orderSide];}
//	TakionIterator* CreateOrderIterator(OrderStatus orderStatus, OrderSide orderSide) const;
	TakionIterator* CreateOrderIterator(unsigned int orderStatusMask, unsigned int orderSideMask) const;
	void AddMaskToOrderIterator(TakionIterator* iterator, unsigned int orderStatusMask, unsigned int orderSideMask) const;

	const OrderChronologicalMap& GetChronologicalPendingOrders(OrderSide orderSide) const{return m_chronologicalPendingOrders[orderSide];}
	OrderChronologicalMap& GetChronologicalPendingOrders(OrderSide orderSide){return m_chronologicalPendingOrders[orderSide];}

	const OrderPriceBidSet& GetBuyPotentialSpoofingSortedOrders() const{return m_buyPotentialSpoofingSortedOrders;}
	const OrderPriceAskSet& GetSellPotentialSpoofingSortedOrders() const{return m_sellPotentialSpoofingSortedOrders;}
	unsigned int GetBuyPotentialSpoofingOrderCount() const{return (unsigned int)m_buyPotentialSpoofingSortedOrders.size();}
	unsigned int GetSellPotentialSpoofingOrderCount() const{return (unsigned int)m_sellPotentialSpoofingSortedOrders.size();}
	unsigned int GetPotentialSpoofingOrderCount(const bool& bid) const{return bid ? GetBuyPotentialSpoofingOrderCount() : GetSellPotentialSpoofingOrderCount();}

	unsigned int GetBuySpoofingOrderCount(const Order* orderBeingCancelled, const Price& price, bool priceInclusive, unsigned int& size, unsigned int& hiddenCount) const;//, bool displayOnly) const;
	unsigned int GetSellSpoofingOrderCount(const Order* orderBeingCancelled, const Price& price, bool priceInclusive, unsigned int& size, unsigned int& hiddenCount) const;//, bool displayOnly) const;
	unsigned int GetSpoofingOrderCount(const bool& bid, const Order* const& orderBeingCancelled, const Price& price, const bool& priceInclusive, unsigned int& size, unsigned int& hiddenCount) const//, bool displayOnly) const
	{
		return bid ?
			GetBuySpoofingOrderCount(orderBeingCancelled, price, priceInclusive, size, hiddenCount)://, displayOnly):
			GetSellSpoofingOrderCount(orderBeingCancelled, price, priceInclusive, size, hiddenCount);//, displayOnly);
	}

	bool GetSpoofingBasePrice(bool bid, const Price& nbbo, const Price& priceOffset, Price& basePrice) const;
	unsigned char ShouldBlockCancelSpoofingOrder(const Order* order, const Price& bid, const Price& ask) const;//returns CE_SPOOFING_ORDER_COUNT_RATIO_EXCEEDED, CE_SPOOFING_ORDER_SIZE_RATIO_EXCEEDED, or CE_OK
	void CollectBuySpoofingOrders(OrderReplaceSet& orderSet) const;
	void CollectSellSpoofingOrders(OrderReplaceSet& orderSet) const;
	void CollectSpoofingOrders(OrderReplaceSet& orderSet, const bool& buy) const
	{
		if(buy)CollectBuySpoofingOrders(orderSet);
		else CollectSellSpoofingOrders(orderSet);
	}
	unsigned int CancelBuySpoofingOrders();
	unsigned int CancelSellSpoofingOrders();
	unsigned int CancelSpoofingOrders(const bool& buy){return buy ? CancelBuySpoofingOrders() : CancelSellSpoofingOrders();}

	const OrderPriceBidSet& GetBuyPendingQuoteOrders() const{return m_buyPendingQuoteOrders;}//visible in MmBox
	const OrderPriceAskSet& GetSellAndShortPendingQuoteOrders() const{return m_sellAndShortPendingQuoteOrders;}//visible in MmBox

	const OrderPriceBidSet& GetBuyPendingSortedOrders() const{return m_buyPendingSortedOrders;}
	const OrderPriceAskSet& GetSellPendingSortedOrders() const{return m_sellPendingSortedOrders;}

	const OrderPriceBidSet& GetBuyAdvPassiveSortedOrders() const{return m_buyAdvPassiveSortedOrders;}
	const OrderPriceAskSet& GetSellAdvPassiveSortedOrders() const{return m_sellAdvPassiveSortedOrders;}
	unsigned int GetBuyAdvPassiveOrdersCount() const{return (unsigned int)m_buyAdvPassiveSortedOrders.size();}
	unsigned int GetSellAdvPassiveOrdersCount() const{return (unsigned int)m_sellAdvPassiveSortedOrders.size();}
	unsigned int GetAdvPassiveOrdersCount() const{return GetBuyAdvPassiveOrdersCount() + GetSellAdvPassiveOrdersCount();}

	const AggrOrderPriceBidSet& GetBuyPassivePendingSortedOrders() const{return m_buyPassivePendingSortedOrders;}
	const AggrOrderPriceBidSet& GetBuyNonPassivePendingSortedOrders() const{return m_buyNonPassivePendingSortedOrders;}

	const AggrOrderPriceBidSet& GetBuyRtcPassivePendingSortedOrders() const{return m_buyRtcPassivePendingSortedOrders;}
	const AggrOrderPriceBidSet& GetBuyRtcNonPassivePendingSortedOrders() const{return m_buyRtcNonPassivePendingSortedOrders;}

	const AggrOrderPriceAskSet& GetSellPassivePendingSortedOrders() const{return m_sellPassivePendingSortedOrders;}
	const AggrOrderPriceAskSet& GetSellNonPassivePendingSortedOrders() const{return m_sellNonPassivePendingSortedOrders;}

	const AggrOrderPriceAskSet& GetShortPassivePendingSortedOrders() const{return m_shortPassivePendingSortedOrders;}
	const AggrOrderPriceAskSet& GetShortNonPassivePendingSortedOrders() const{return m_shortNonPassivePendingSortedOrders;}

	bool HasMoreAggressiveShortOrder(bool passive, bool stopOrder, const Price& quotePrice, Price& mostAggressiveShortOrderPrice) const;//Locks Position inside the function if necessary

	const OrderPriceAskSet& GetShortPendingSortedOrders() const{return m_shortPendingSortedOrders;}
	const OrderPriceAskSet& GetSellAndShortPendingSortedOrders() const{return m_sellAndShortPendingSortedOrders;}

	const OrderPriceBidSet& GetBuyOddLotOrders() const{return m_buyOddLotOrders;}
	const OrderPriceAskSet& GetSellAndShortOddLotOrders() const{return m_sellAndShortOddLotOrders;}

	const ExecutionMap& GetExecutions(OrderSide orderSide) const{return m_executions[orderSide];}

	TakionIterator* CreateExecutionIterator(unsigned int orderSideMask) const;
	void AddMaskToExecutionIterator(TakionIterator* iterator, unsigned int orderSideMask) const;

	const ExecutionChronologicalSet& GetChronologicalExecutions() const{return m_chronologicalExecutions;}//Lock
	ExecutionChronologicalSet& GetChronologicalExecutions(){return m_chronologicalExecutions;}

	const ExecutionChronologicalSet& GetChronologicalExecutionsSinceLoad() const{return m_chronologicalExecutionsSinceLoad;}//Lock
	ExecutionChronologicalSet& GetChronologicalExecutionsSinceLoad(){return m_chronologicalExecutionsSinceLoad;}
	const Execution* FindLastValidExecOnSide(bool buy, unsigned int& size, Money& investment) const;

	Execution* FindExecution(unsigned int id, OrderSide orderSide);

	unsigned int GetBuyExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_BUY].GetCount();}
	unsigned int GetSellExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_SELL].GetCount();}
	unsigned int GetShortExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_SHORT].GetCount();}


//Safe to call from threads
	void CollectSideOrders(OrderReplaceSet& orderSet, unsigned char sideMask);
	void CollectOrders(OrderReplaceSet& orderSet,
		bool forCancel,
		unsigned char sideMask,
		unsigned char directionMask,
		OrderCancelPick orderCancelPick,
		unsigned int tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL) const;

	virtual unsigned int CancelOrders(unsigned char sideMask,
		unsigned char directionMask,
		OrderCancelPick orderCancelPick,
		unsigned int tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL);
	virtual unsigned int ReplaceOrders(const bool& replaceNative,
		const unsigned char& sideMask,
		const unsigned char& directionMask,
		const OrderCancelPick& orderCancelPick,
		const unsigned int& tifMask,
		const unsigned char& algoMask,
		const unsigned char& pqOpenMask,
		const unsigned char& tCloseMask,
		const bool& destinationExclude,
		const UIntSet* const& destinationSet,
		const bool& mnemonicExclude,
		const UIntSet* const& mnemonicSet,
		const SignedPrice& replacePriceOffset,
		const bool& replacePriceOffsetPercent,
		const bool& replacePriceReverseForSell,
		const bool& marketOrder,
		const int& replaceSizeOffset,
		const bool& replaceSizeReverseForSell,
		const bool& preBorrow,
		const Price& preBorrowPrice,
		const unsigned __int64& userId,
		const unsigned char& displaySizeMode,//0 - size fraction, 1 - round lot, 2 - no change
		const unsigned int& displaySize,
		const unsigned int& displaySizeFraction,
		Order** const& oneOrder = NULL,//Output param; Provide a non-NULL ptr to get an Order* if there is only one order to replace (to be able to adjust the replacement in the UI)
		OrderReplaceSet* const& orderCollection = NULL//Output param; Provide a non-NULL ptr to get a collection of Orders instead of replacing them (to be able to adjust the replacement in the UI)
		) = 0;
///////////////////////////
	unsigned int CancelOrdersByPrice(unsigned char sideMask,
		unsigned char directionMask,
		bool mostAggressive,
		const Price& price,
		bool priceInclusive = true,
		bool washableOnly = true,
		bool includeMidPointPeg = true,
		bool includeNoMassCancel = false,
		unsigned int tifMask = (1 << TIFMASK_DAY)|(1 << TIFMASK_EXTENDED)|(1 << TIFMASK_TIME)|(1 << TIFMASK_GTC)|(1 << TIFMASK_GTT)|(1 << TIFMASK_OTHER),
		unsigned char visibleSizeMask = VSM_ALL,
		unsigned char oddLotMask = OLM_ALL,
		unsigned char algoMask = 1 << ALGORITHMMASK_LIMIT,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL,
		unsigned int totalSize = 0xFFFFFFFF) const;
/*
	unsigned int CancelBuyOrdersByPrice(const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned int tifMask,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL) const;
*/
	unsigned int CancelBuyOrdersByPrice(bool mostAggressive,
		const Price& price,
		bool priceInclusive = true,
		bool washableOnly = true,
		bool includeMidPointPeg = true,
		bool includeNoMassCancel = false,
		unsigned char directionMask = ODIR_LIVE_MASK,
		unsigned int tifMask = (1 << TIFMASK_DAY)|(1 << TIFMASK_EXTENDED)|(1 << TIFMASK_TIME)|(1 << TIFMASK_GTC)|(1 << TIFMASK_GTT)|(1 << TIFMASK_OTHER),
		unsigned char visibleSizeMask = VSM_ALL,
		unsigned char oddLotMask = OLM_ALL,
		unsigned char algoMask = 1 << ALGORITHMMASK_LIMIT,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL,
		unsigned int totalSize = 0xFFFFFFFF) const;

	unsigned int CancelSellOrdersByPrice(bool mostAggressive,
		const Price& price,
		bool priceInclusive = true,
		bool washableOnly = true,
		bool includeMidPointPeg = true,
		bool includeNoMassCancel = false,
		unsigned char directionMask = ODIR_LIVE_MASK,
		unsigned int tifMask = (1 << TIFMASK_DAY)|(1 << TIFMASK_EXTENDED)|(1 << TIFMASK_TIME)|(1 << TIFMASK_GTC)|(1 << TIFMASK_GTT)|(1 << TIFMASK_OTHER),
		unsigned char visibleSizeMask = VSM_ALL,
		unsigned char oddLotMask = OLM_ALL,
		unsigned char algoMask = 1 << ALGORITHMMASK_LIMIT,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL,
		unsigned int totalSize = 0xFFFFFFFF) const;

	unsigned int CancelShortOrdersByPrice(bool mostAggressive,
		const Price& price,
		bool priceInclusive = true,
		bool washableOnly = true,
		bool includeMidPointPeg = true,
		bool includeNoMassCancel = false,
		unsigned char directionMask = ODIR_LIVE_MASK,
		unsigned int tifMask = (1 << TIFMASK_DAY)|(1 << TIFMASK_EXTENDED)|(1 << TIFMASK_TIME)|(1 << TIFMASK_GTC)|(1 << TIFMASK_GTT)|(1 << TIFMASK_OTHER),
		unsigned char visibleSizeMask = VSM_ALL,
		unsigned char oddLotMask = OLM_ALL,
		unsigned char algoMask = 1 << ALGORITHMMASK_LIMIT,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL,
		unsigned int totalSize = 0xFFFFFFFF) const;

	void GetOrdersByPrice(OrderReplaceSet& orderSet,
		unsigned char sideMask,
		unsigned char directionMask,
		bool mostAggressive,
		const Price& price,
		bool priceInclusive = true,
		bool washableOnly = true,
		bool includeMidPointPeg = true,
		bool includeNoMassCancel = false,
		unsigned int tifMask = (1 << TIFMASK_DAY)|(1 << TIFMASK_EXTENDED)|(1 << TIFMASK_TIME)|(1 << TIFMASK_GTC)|(1 << TIFMASK_GTT)|(1 << TIFMASK_OTHER),
		unsigned char visibleSizeMask = VSM_ALL,
		unsigned char oddLotMask = OLM_ALL,
		unsigned char algoMask = 1 << ALGORITHMMASK_LIMIT,
		bool addOnOpen = true,
		bool addOnClose = true,
		bool addArcaPlo = true,
		unsigned int onOpenOnCloseDestinationName = 0,//0xFFFFFFFF,
		unsigned int limitDestinationName = 0,
		unsigned int excludeExpireBeforeTime = 0,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL,
		unsigned int totalSize = 0xFFFFFFFF) const;
/*
	unsigned int GetBuyOrdersByPrice(OrderSet& orderSet,
		const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned int tifMask,
		unsigned char visibleSizeMask,
		unsigned char oddLotMask,
		bool includeMidPointPeg,
		unsigned char algoMask,
		bool destinationExclude,
		const UIntSet& destinationSet,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL,
		unsigned int totalSize = 0xFFFFFFFF,
		bool washableOnly = false) const;
*/
	unsigned int GetBuyOrdersByPrice(OrderReplaceSet& orderSet,
		bool mostAggressive,
		const Price& price,
		bool priceInclusive = true,
		bool washableOnly = true,
		bool includeMidPointPeg = true,
		bool includeNoMassCancel = false,
		unsigned char directionMask = ODIR_LIVE_MASK,
		unsigned int tifMask = (1 << TIFMASK_DAY)|(1 << TIFMASK_EXTENDED)|(1 << TIFMASK_TIME)|(1 << TIFMASK_GTC)|(1 << TIFMASK_GTT)|(1 << TIFMASK_OTHER),
		unsigned char visibleSizeMask = VSM_ALL,
		unsigned char oddLotMask = OLM_ALL,
		unsigned char algoMask = 1 << ALGORITHMMASK_LIMIT,
		bool addOnOpen = true,
		bool addOnClose = true,
		bool addArcaPlo = true,
		unsigned int onOpenOnCloseDestinationName = 0,//0xFFFFFFFF,
		unsigned int limitDestinationName = 0,
		unsigned int excludeExpireBeforeTime = 0,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL,
		unsigned int totalSize = 0xFFFFFFFF) const;

	unsigned int GetSellOrdersByPrice(OrderReplaceSet& orderSet,
		bool mostAggressive,
		const Price& price,
		bool priceInclusive = true,
		bool washableOnly = true,
		bool includeMidPointPeg = true,
		bool includeNoMassCancel = false,
		unsigned char directionMask = ODIR_LIVE_MASK,
		unsigned int tifMask = (1 << TIFMASK_DAY)|(1 << TIFMASK_EXTENDED)|(1 << TIFMASK_TIME)|(1 << TIFMASK_GTC)|(1 << TIFMASK_GTT)|(1 << TIFMASK_OTHER),
		unsigned char visibleSizeMask = VSM_ALL,
		unsigned char oddLotMask = OLM_ALL,
		unsigned char algoMask = 1 << ALGORITHMMASK_LIMIT,
		bool addOnOpen = true,
		bool addOnClose = true,
		bool addArcaPlo = true,
		unsigned int onOpenOnCloseDestinationName = 0,//0xFFFFFFFF,
		unsigned int limitDestinationName = 0,
		unsigned int excludeExpireBeforeTime = 0,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL,
		unsigned int totalSize = 0xFFFFFFFF) const;

	unsigned int GetShortOrdersByPrice(OrderReplaceSet& orderSet,
		bool mostAggressive,
		const Price& price,
		bool priceInclusive = true,
		bool washableOnly = true,
		bool includeMidPointPeg = true,
		bool includeNoMassCancel = false,
		unsigned char directionMask = ODIR_LIVE_MASK,
		unsigned int tifMask = (1 << TIFMASK_DAY)|(1 << TIFMASK_EXTENDED)|(1 << TIFMASK_TIME)|(1 << TIFMASK_GTC)|(1 << TIFMASK_GTT)|(1 << TIFMASK_OTHER),
		unsigned char visibleSizeMask = VSM_ALL,
		unsigned char oddLotMask = OLM_ALL,
		unsigned char algoMask = 1 << ALGORITHMMASK_LIMIT,
		bool addOnOpen = true,
		bool addOnClose = true,
		bool addArcaPlo = true,
		unsigned int onOpenOnCloseDestinationName = 0,//0xFFFFFFFF,
		unsigned int limitDestinationName = 0,
		unsigned int excludeExpireBeforeTime = 0,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL,
		unsigned int totalSize = 0xFFFFFFFF) const;

	unsigned int GetAllSideOrdersByPrice(OrderReplaceSet& orderSet,
		bool buy,
		const Price& price,
		bool priceInclusive,
		bool mostAggressive,
		unsigned int totalSize) const;

	unsigned int GetLessAggressiveOrders(bool side,
		OrderReplaceSet& orderSet,
		Order** orderToReplace,
		unsigned int& replaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		unsigned int size,
		const Price& quotePrice,
		const Order* orderBeingReplaced) const;

	unsigned int GetLessAggressiveBuyOrders(OrderReplaceSet& orderSet,
		Order** orderToReplace,
		unsigned int& replaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		unsigned int size,
		const Price& quotePrice,
		const Order* orderBeingReplaced) const;

	unsigned int GetLessAggressiveSellOrders(OrderReplaceSet& orderSet,
		Order** orderToReplace,
		unsigned int& replaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		unsigned int size,
		const Price& quotePrice,
		const Order* orderBeingReplaced) const;

	unsigned int GetOrderSizeByPositionCap(unsigned int positionCap,
		bool bidSide,
		OrderReplaceSet& orderSet,
		bool resizeAllowed,
		Order** orderToReplace,
		unsigned int& replaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		const unsigned int orderQuantity,
		const Price& quotePrice,
		const Order* orderBeingReplaced) const;

	unsigned int GetFlippingBuyOrders(bool rtcOnly,
		OrderReplaceSet& orderSet,
		Order** orderToReplace,
		unsigned int& replaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		bool includeOnOpenOnClose,
		const unsigned int orderQuantity,
		const Price& quotePrice,
		const Order* orderBeingReplaced,//if orderToReplace is not NULL it will try to find an Order that can be resized.
		bool includeBeingCancelled = false) const;
	unsigned int GetFlippingSellOrders(OrderReplaceSet& orderSet,
		Order** orderToReplace,
		Order** passiveSellOrderToReplace,
		unsigned int& replaceSize,
		unsigned int& passiveSellOrderReplaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		bool includeOnOpenOnClose,
		const unsigned int orderQuantity,
		const Price& quotePrice,
		const Order* orderBeingReplaced,
		bool includeBeingCancelled = false) const;//if orderToReplace is not NULL it will try to find an Order that can be resized.
	unsigned int GetFlippingOrders(bool buy,
		OrderReplaceSet& orderSet,
		Order** orderToReplace,
		Order** passiveSellOrderToReplace,
		unsigned int& replaceSize,
		unsigned int& passiveSellOrderReplaceSize,
		bool orderPassive,
		bool stopOrder,
		bool orderCrossingMarket,
		bool includeOnOpenOnClose,
		const unsigned int orderQuantity,
		const Price& quotePrice,
		const Order* orderBeingReplaced,
		bool includeBeingCancelled = false) const;//if orderToReplace is not NULL it will try to find an Order that can be resized.

	bool HasWashOrders(bool bids,
		const Price& price,
		Price& orderPrice,
		unsigned int tifMask,
		unsigned char visibleSizeMask,
		unsigned char oddLotMask,
		bool includeMidPointPeg,
		bool addOnOpen = true,
		bool addOnClose = true,
		bool addArcaPlo = true,
		unsigned int onOpenOnCloseDestinationName = 0,
		unsigned int limitDestinationName = 0,
		unsigned int excludeExpireBeforeTime = 0,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL) const;
/*
	const Security* GetASecurity() const{return m_security ? m_security : m_sortableSecurity;}//safe to call only from main thread
	const Security* GetSecurity() const{return m_security;}
	void SetSecurity(const Security* security){m_security = security;}
	const Security* GetSortableSecurity() const{return m_sortableSecurity;}//safe to call only from main thread
	void SetSortableSecurity(const Security* security){m_sortableSecurity = security;}

	void NotifySecurityObservers(const Message* message, const Message* info);
	void AddSecurityObserver(Observer* o) const;
	void RemoveSecurityObserver(Observer* o) const;
	bool isSecurityObservable(Observable* o) const{return o == &m_securityObservable;}
*/
	void RemoveBlockedOrder(Order* order);
	void RemoveCanceledOrRejectedOrder(Order* order);

	virtual unsigned char PanicClose(const bool& blockAggressiveOrders) = 0;//calls CancelOrders and account->SendPanicCloseOrder

	const unsigned char& GetClearingFirmOrdinal() const;
	const unsigned char& GetStockLoanFirmOrdinal() const;
	const Price& GetBorrowPriceMultiplier() const;

	const unsigned int& GetCompactBorrowPrice() const{return m_compactBorrowPrice;}

//	const unsigned int& GetCompactBeta() const{return m_compactBeta;}
//	const unsigned char& GetMargin() const{return m_margin;}

//	virtual const unsigned int& GetCompactBorrowDiscountedPrice() const override{return m_compactBorrowDiscountedPrice;}
//	virtual const unsigned int& GetBorrowAvailableSize() const override{return m_borrowAvailableSize;}
	virtual bool isStockLoanInitialized() const override{return m_stockLoanInitialized;}
//	const bool& isHtb() const{return m_htb;}
	virtual const unsigned int& GetTimestampHtb() const{return m_timestampHtb;}
	virtual const unsigned char& isHTB() const override{return m_htb;}
	virtual const bool& isHtbInitialized() const override{return m_htbInitialized;}
	virtual bool HasHTB() const override{return '\0' != m_htb;}
	virtual unsigned int GetHtbString() const override{return m_htb;}

	const unsigned char& GetAutoClose() const{return m_autoClose;}

	const bool& isCancelOrdersInitiated() const{return m_cancelOrdersInitiated;}
//	bool isClosePositionsInitiated() const{return m_closePositionsInitiated;}//use m_autoClose instead
	bool LockInquirySortedOrders() const{return m_lockSortedOrders.LockInquiry();}
	void LockInquiryWaitSortedOrders() const{m_lockSortedOrders.LockInquiryWait();}
	void UnlockInquirySortedOrders() const{m_lockSortedOrders.UnlockInquiry();}

/*
	void NotifyInThreadObservers(const Message* message, const Message* info = NULL);
	virtual void WritePositionUpdateMessageToMainThread(unsigned char execution){}
*/
	const bool& isLoser() const{return m_loser;}

	void CalculatePotentialPositionSize(char orderSide, unsigned int orderQuantity,
		unsigned int& pendingBuyShares,
		unsigned int& pendingSellShares,
		unsigned int& longSize,
		unsigned int& shortSize) const;
	unsigned int CalculateSizeToBorrow(char orderSide, unsigned int orderQuantity) const;
#ifdef LOG_UPDATE_STOCK
	unsigned __int64 FindStrayOrder(const Order* order) const;
#endif

//	virtual unsigned int CancelOpeningOrders(){return 0;}
	unsigned int CancelOpeningOrders();
//	unsigned int CancelOpeningOrdersWorthValue(Money& value);

	virtual void CancelIllegalOrdersOnExecution(const bool& buy) = 0;

	virtual void CancelIllegalShortOrders() = 0;
	virtual void CancelIllegalSellOrders() = 0;
	virtual void CancelResizeBuyOrders() = 0;

	void CancelAllShortOrders(bool includeSlowOrders);

#ifndef TAKION_NO_OPTIONS
	virtual void CancelIllegalBuyToOpenOrders() = 0;
	virtual void CancelIllegalSellToOpenOrders() = 0;
	virtual void CancelIllegalBuyToCloseOrders() = 0;
	virtual void CancelIllegalSellToCloseOrders() = 0;
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

	bool LockInquiryOptionPositions() const{return m_lockOptionPositions.LockInquiry();}
	void LockInquiryWaitOptionPositions() const{m_lockOptionPositions.LockInquiryWait();}
	void UnlockInquiryOptionPositions() const{m_lockOptionPositions.UnlockInquiry();}

	const OptionPositionMap& GetOptionPositions() const{return m_optionPositions;}//Enclose the usage in locking
	unsigned int GetOptionPositionCount() const{return (unsigned int)m_optionPositions.GetCount();}
	Position* FindOptionPosition(const OptionSymbolBlockKey& key) const
	{
		const OptionPositionMap::CPair* positionPair = m_optionPositions.PLookup(key);
		return positionPair ? positionPair->value : NULL;
	}
	Position* FindOptionPosition(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return FindOptionPosition(OptionSymbolBlockKey(rootSymbol, optionBlock));
	}

	TakionIterator* CreateOptionPositionIterator() const;//call iterator->Reset() before using. Enclose the usage in locking. Call GetNextOptionPosition to iterate until it returns NULL; Call delete iterator when no longer needed.
	static Position* GetNextOptionPosition(TakionIterator* iterator);//Enclose the usage in locking
//Don't call 3 function below
	void AddOptionPosition(Position* position);
	void RemoveOptionPosition(Position* position);
	void ClearOptionPositions();
#endif

#ifdef SEND_LOCATE_INFO
	virtual const char* GetLocateContractIdAsString() const{return m_locateContractId.GetString();}
	virtual const char* GetLocateInfoAsString() const{return m_locateInfo.GetString();}

	const LocateContractId& GetLocateContractId() const{return m_locateContractId;}
	const LocateContractId& GetLocateInfo() const{return m_locateInfo;}
#endif
	const unsigned int& GetAutoCloseCount() const{return m_autoCloseCount;}
	const unsigned int& GetAutoClosePreMarketCount() const{return m_autoClosePreMarketCount;}
	const unsigned int& GetAutoClosePostMarketCount() const{return m_autoClosePostMarketCount;}

	virtual const Price& GetActionPrintPrice() const override{return m_actionPrintPrice;}

#ifdef FIRM_VALUES
	virtual bool isFirmPositionLoaded() const{return true;}
	virtual const unsigned char& GetUntradeableLevel() const{return m_untradeableLevel;}//For Supervisor only. 0 - tradable; 1 - pending; 2 - untradeable.
#endif

	bool CancelOpeningOrdersUpTo(unsigned int clientId,
		UIntSet& orderClientIdsCancelled,
		const Money& overConstraint,
		const Money& currentPosBpUsed,
		Money& bpReturned);//Cancel less aggressive orders on both sides to reduce bpUsed until the Order with "clientId" is cancelled

	const bool& isHashTablesInitialized() const{return m_hashTablesInitialized;}

protected:

	Position(const char* symbol,
		Account* account,
		SecurityType securityType,
		int compactBeta,
		unsigned char margin,
		unsigned char PM_EL_Rate,// = 15,
		unsigned char PM_ES_Rate,// = 15,
		unsigned char PM_HL_Rate,// = 15,
		unsigned char PM_HS_Rate,// = 15,
		unsigned char EL_Rate,// = 25,
		unsigned char ES_Rate,// = 30,
		unsigned char HL_Rate,// = 30,
		unsigned char HS_Rate,// = 30,
		unsigned char Fed_Req,// = 50,
		unsigned char Asset_Type,// = 'E',
		bool Marginable,// = true,
		unsigned char Sec_Type,// = 'C',
		unsigned char Status,// = 0):
		bool PortfolioManaged,
#ifndef TAKION_NO_OPTIONS
		OptionSymbolBlock* optionSymbolBlock,
#endif
		unsigned int timeLoaded);//0 if not loaded from the database

	virtual void IncrementUpdatedPnlPositionCount(const bool openPnlForLossUpdated) override;

//	virtual void ClosingPriceSet();

//	void UpdatePotentialValues();// const bool includeNight);
//	void UpdatePotentialBetaValues();
//	void UpdateBpUsed();
//	void UpdateBpBetaUsed();
	void CalculateBpBetaUsed(const Money& potentialBetaLongValue, const Money& potentialBetaShortValue, Money& bpBetaUsed) const;

	void CalculateMeUsed(const Money& potentialLongMe, const Money& potentialShortMe, Money& meUsed) const;

	virtual void WriteInventoryToAccountThread(int size, const Price& cost, bool inventoryFloating, bool leaveInLayout) override;
	virtual void WriteInventoryToMainThread(int size, const Price& cost, bool inventoryFloating, bool leaveInLayout) override;

	Account* m_account;

	virtual void SetActionPrintPrice(const Price& printPrice) override{m_actionPrintPrice = printPrice;}
	Price m_actionPrintPrice;

	unsigned int m_compactBorrowPrice;
//	unsigned int m_compactBorrowDiscountedPrice;
//	unsigned int m_borrowAvailableSize;

	unsigned int m_autoCloseCount;
	unsigned int m_autoClosePreMarketCount;
	unsigned int m_autoClosePostMarketCount;

	unsigned int m_timestampHtb;
	unsigned char m_htb;
	unsigned char m_discountFlag;
	bool m_htbInitialized;
	bool m_stockLoanInitialized;

	char m_phantom;//+1 - long, -1 - short, 0 - flat
//	int m_sizeOrPhantom;
	unsigned char m_absPhantom;//1 - has phantom, 0 - no phantom

	unsigned char m_autoClose;//AutoCloseStatus; can be non zero for Supervisor trader Id only.
	bool m_cancelOrdersInitiated;
	bool m_loser;
//	bool m_closePositionsInitiated;//use m_autoClose instead

//	unsigned int m_advPassiveOrderCumulativeSize;
	void InitHashTables();
#ifdef DELAY_POSITION_INIT_HASH_TABLES
	void InitOrderHashTable(OrderMap& orderMap, unsigned int hashSize, const char* tableName, unsigned char index = 0xFF);
	void InitExecutionHashTable(ExecutionMap& executionMap, unsigned int hashSize, const char* tableName, unsigned char index = 0xFF);
#endif
	bool m_hashTablesInitialized;

#ifdef FIRM_VALUES
//	FirmPosition* m_firmPosition;
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
	OrderMap m_ordersBlocked;

	OrderMap m_ordersPending;

	bool UpdatePrintTrailingOrders(const Price& printPrice, const Message* message);
	bool UpdateLevel1TrailingOrders(const Price& bid, const Price& ask, const unsigned char sideMask, const Message* message);
	OrderMap m_ordersPendingStopTrailing;

	OrderMap m_ordersStuck;
	OrderMap m_ordersCancelRejected;
	OrderMap m_ordersCancelBlocked;

	OrderMap m_ordersWithCancelProblem;

	OrderMap m_ordersAlgorithm;
	OrderMap m_gtcOrdersAlgorithm;

	OrderMap m_orders[TU_ORDER_STATUS_COUNT * TU_ORDER_SIDE_COUNT];

	OrderChronologicalMap m_chronologicalPendingOrders[TU_ORDER_SIDE_COUNT];

	bool LockModificationSortedOrders() const{return m_lockSortedOrders.LockModification();}
	void UnlockModificationSortedOrders() const{m_lockSortedOrders.UnlockModification();}

	OrderPriceBidSet m_buyPotentialSpoofingSortedOrders;
	OrderPriceAskSet m_sellPotentialSpoofingSortedOrders;

	OrderPriceBidSet m_buyPendingQuoteOrders;//visible in MmBox
	OrderPriceAskSet m_sellAndShortPendingQuoteOrders;//visible in MmBox

	OrderPriceBidSet m_buyPendingSortedOrders;
	OrderPriceAskSet m_sellPendingSortedOrders;

	OrderPriceBidSet m_buyAdvPassiveSortedOrders;
	OrderPriceAskSet m_sellAdvPassiveSortedOrders;

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
	ExecutionChronologicalSet m_chronologicalExecutionsSinceLoad;
/*
#ifndef TAKION_NO_OPTIONS
	OptionSymbolBlock* m_optionSymbolBlock;
	UnderlierInfo* m_underlierInfo;
#endif
*/
#ifndef TAKION_NO_OPTIONS
	OptionPositionMap m_optionPositions;
	TakionLock m_lockOptionPositions;
#endif
private:
	Position(const Position& other);
	Position& operator=(const Position& other);
};

class TU_API FirmBase
{
public:
	virtual ~FirmBase(){}
	const unsigned int& GetOrdinal() const{return m_ordinal;}
	void SetOrdinal(const unsigned int& ordinal){m_ordinal = ordinal;}
	const bool& isLoaded() const{return m_loaded;}
	void SetLoaded(const bool& loaded)// const
	{
		if(loaded != m_loaded)
		{
			m_loaded = loaded;
			OnLoaded(loaded);
		}
	}
	virtual const char* GetName() const = 0;
protected:
	FirmBase(const unsigned int& ordinal):
		m_ordinal(ordinal),
		m_loaded(false)
	{
	}
	virtual void OnLoaded(bool loaded){}
	unsigned int m_ordinal;
	bool m_loaded;
};

class TU_API Firm : public FirmBase//names of 4 chars or less
{
public:
	virtual const char* GetName() const override{return m_name;}
	const unsigned int& GetNumericName() const{return m_numericName;}
protected:
	Firm(const char* const& name, const unsigned int& ordinal):
		FirmBase(ordinal),
		m_numericName(*(unsigned int*)name)
	{
		*(unsigned int*)m_name = m_numericName;
		m_name[sizeof(unsigned int)] = '\0';
	}
	Firm(const unsigned int& numericName, const unsigned int& ordinal):
		FirmBase(ordinal),
		m_numericName(numericName)
	{
		*(unsigned int*)m_name = numericName;
		m_name[sizeof(unsigned int)] = '\0';
	}
	unsigned int m_numericName;
	char m_name[sizeof(unsigned int) + 1];
};

class TU_API AccountFirm : public FirmBase//names of 16 chars or less
{
public:
	virtual const char* GetName() const override{return m_firmId.GetId();}
	const AccountId& GetFirmId() const{return m_firmId;}
protected:
	AccountFirm(const char* const& name, const unsigned int& ordinal):
		FirmBase(ordinal),
		m_firmId(name)
	{
	}
	AccountFirm(const AccountId& firmId, const unsigned int& ordinal):
		FirmBase(ordinal),
		m_firmId(firmId)
	{
	}
	AccountId m_firmId;
};


enum PositionUpdateFlags : unsigned char
{
	PUE_NONE = 0,
	PUE_EXECUTION = 1,
	PUE_PENDING_ORDERS_COUNT = 2,
	PUE_LONG_POSITION_CLOSED_OR_FLIPPED = 4,
	PUE_SHORT_POSITION_CLOSED_OR_FLIPPED = 8,
	PUE_HISTORICAL = 16,
	PUE_INVENTORY_LONG_POSITION_CLOSED_OR_FLIPPED = 32,
	PUE_INVENTORY_SHORT_POSITION_CLOSED_OR_FLIPPED = 64,
	PUE_TRAILING_STOP_UPDATED = 128,
};

typedef AccountNumberId<unsigned __int64> AccountSymbolKey;

#ifdef FIRM_VALUES

typedef AccountNumberId<unsigned int> AccountAggregatorId;

/*
class AccountAggregatorId : public AccountId
{
public:
	AccountAggregatorId(const char* firmId, const char* clearingAccountName):AccountId(clearingAccountName),m_firmId(U_RepresentStringAsUnsignedNumber<unsigned int>(firmId)){}
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
		U_AppendUnsignedNumberAsString(str, m_firmId);
	}
	void fromString(const char* str)
	{
		const char* p = strrchr(str, ' ');
		if(p)
		{
			m_firmId = U_RepresentStringAsUnsignedNumber<unsigned int>(p + 1);
			SetAccountId(str, (unsigned int)(p - str));
		}
		else
		{
			m_firmId = 0;
			SetAccountId(str);
		}
	}
//	size_t GetHashValue() const{return (size_t)m_first;}
protected:
	unsigned int m_firmId;
};
*/
template<> AFX_INLINE UINT AFXAPI HashKey<const AccountAggregatorId&>(const AccountAggregatorId& key)
{
#ifdef _WIN64
	const size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const AccountSymbolKey&>(const AccountSymbolKey& key)
{
#ifdef _WIN64
	const size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

enum UntradeableStatus : unsigned char
{
	US_TRADEABLE,
	US_UNTRADEABLE_FULL,
	US_UNTRADEABLE_PARTIAL,//Can trade within borrowed size

	US_Count
};

class TU_API AccountAggregator : public Observable, public Firm, public TakionLockMultithread//TakionLock
{
friend class TakionUtils;
public:
	virtual ~AccountAggregator(){ClearAndDestroyFirmPositions();}
	void ClearAndDestroyFirmPositions();
	typedef CMap<unsigned __int64, const unsigned __int64&, FirmPosition*, FirmPosition* const&> FirmPositionMap;
	typedef CMap<unsigned __int64, const unsigned __int64&, unsigned int, const unsigned int&> UntradeableCountMap;
	typedef CMap<unsigned __int64, const unsigned __int64&, unsigned char, const unsigned char&> UntradeableStatusMap;//Untradeable Status. US_TRADEABLE = 0 - tradeable; US_UNTRADEABLE_FULL = 1 - untradeable full; US_UNTRADEABLE_PARTIAL = 2 - untradeable partial (Can trade within borrowed size).
//	typedef std::hash_map<unsigned __int64, volatile LONG> UntradeableSymbolMap;

	typedef
#if (_MSC_VER > 1600)
		std::unordered_map<unsigned __int64, unsigned char>
#else
		std::hash_map<unsigned __int64, unsigned char>
#endif
		SymbolMap;

	void GetUntradeableSymbolMap(SymbolMap& untradeableSymbols) const;
/*
#if (_MSC_VER > 1600)
		std::unordered_set<unsigned __int64, >&
#else
		std::hash_set<unsigned __int64>&
#endif
		untradeableSymbols) const;
*/
	unsigned char FindUntradeableSymbol(const unsigned __int64& symbol) const;//return 1 if untradeable symbol exists, otherwise 0
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
	virtual bool WriteSupervisorUntradeableRequestToMainThread(const unsigned __int64& symbol, bool untradeable) const{return false;}
	virtual bool WriteSupervisorCheckUntradeableMessageToMainThread(const unsigned __int64& symbol, unsigned char untradeable) const{return false;}

//	virtual unsigned int GetThreadId() const{return 0;}
	const unsigned int& GetThreadId() const{return m_threadId;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}

	const FirmPositionMap& GetFirmPositions() const{return m_firmPositionMap;}
	TakionIterator* CreateFirmPositionIterator() const;

	const UntradeableCountMap& GetSupervisorUntradeablSymbols() const{return m_supervisorUntradeableSymbolMap;}
	TakionIterator* CreateSupervisorUntradeablSymbolIterator() const;

	void LockUntradeableSymbolInquiryWait() const{m_untradeableSymbolLock.LockInquiryWait();}
	bool LockUntradeableSymbolInquiry() const{return m_untradeableSymbolLock.LockInquiry();}
	void UnlockUntradeableSymbolInquiry() const{m_untradeableSymbolLock.UnlockInquiry();}
	bool LockUntradeableSymbolModification() const{return m_untradeableSymbolLock.LockModification();}
	void UnlockUntradeableSymbolModification() const{m_untradeableSymbolLock.UnlockModification();}

	const UntradeableStatusMap& GetUntradeablSymbols() const{return m_untradeableSymbolMap;}
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
	AccountAggregator(const char* const& firmName, const char* const& clearingAccountName):
		Firm(firmName, nextOrdinal++),
		m_clearingAccountName(clearingAccountName),
		m_accountAggregatorId(m_numericName, m_clearingAccountName),
		m_threadId(0),
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
	unsigned int m_threadId;
	unsigned short m_recoveryErrorCode;
	bool m_untradeableLoaded;

	UntradeableCountMap m_supervisorUntradeableSymbolMap;
	
	UntradeableStatusMap m_untradeableSymbolMap;
	TakionLock m_untradeableSymbolLock;
//	UntradeableSymbolMap::const_iterator m_untradeableSymbolMapEnd;
private:
	static unsigned int nextOrdinal;
};
#endif

enum SwipeType : unsigned char
{
	SWIPE_MEGA,
	SWIPE_DUMB,
	SWIPE_SMART,
	SWIPE_SPIDER,

	SWIPE_TYPE_COUNT
};

enum OversellOrderPolicy : unsigned char
{
	OOP_RESIZE,
	OOP_SPLIT,
	OOP_REJECT,
	OOP_SHORT,

	OOP_Count
};

enum WashOrderPolicy : unsigned char
{
	WOP_KEEP,
	WOP_CANCEL,
	WOP_CANCEL_AND_WAIT,

	WOP_Count
};

#ifndef TAKION_NO_OPTIONS
enum OptionVenueEnum : unsigned int
{
	OV_NONE,
	OV_RESERVED,//OV_NITE,
	OV_APEX,
	OV_DASH,

	OV_Count
};
#endif

enum LocateVenueEnum : unsigned int
{
	LV_NONE,
	LV_QSTK,
	LV_BROADRIDGE,

	LV_Count
};

class TU_API AccountInventoryData : public InventoryData
{
public:
	virtual const int& GetPositionSize(const PositionData* position) const{return position->GetSize();}

	virtual void Reset()
	{
		InventoryData::Reset();
#ifndef TAKION_NO_OPTIONS
		m_optionInvestment.SetZero();
		m_optionInvestmentLong.SetZero();
		m_optionInvestmentShort.SetZero();
		m_maxOptionInvestment.SetZero();
		m_maxOptionInvestmentLong.SetZero();
		m_maxOptionInvestmentShort.SetZero();

		m_underlierValueLong.SetZero();
		m_underlierValueShort.SetZero();
		m_optionPotentialLongSize = 0;//in contracts
		m_optionPotentialShortSize = 0;//in contracts
		m_optionPotentialSize = 0;//in contracts
#endif
		m_longSize = 0;
		m_shortSize = 0;
		m_investmentLong.SetZero();
		m_investmentShort.SetZero();
		m_investmentMeLong.SetZero();
		m_investmentMeShort.SetZero();
		m_investmentBetaLong.SetZero();
		m_investmentBetaShort.SetZero();
		m_investmentCostLong.SetZero();
		m_investmentCostShort.SetZero();
//		m_maxInvestmentLong.SetZero();
//		m_maxInvestmentShort.SetZero();
//		m_maxInvestment.SetZero();
	}

	const unsigned int& GetLongSize() const{return m_longSize;}
	const unsigned int& GetShortSize() const{return m_shortSize;}

	virtual Money GetInvestmentLong() const override{return m_investmentLong;}
	virtual Money GetInvestmentShort() const override{return m_investmentShort;}
	virtual Money GetInvestmentMeLong() const override{return m_investmentMeLong;}
	virtual Money GetInvestmentMeShort() const override{return m_investmentMeShort;}
	virtual Money GetInvestmentBetaLong() const override{return m_investmentBetaLong;}
	virtual Money GetInvestmentBetaShort() const override{return m_investmentBetaShort;}
	virtual Money GetInvestmentCostLong() const override{return m_investmentCostLong;}
	virtual Money GetInvestmentCostShort() const override{return m_investmentCostShort;}

//	const Money& GetMaxInvestmentLong() const{return m_maxInvestmentLong;}
//	const Money& GetMaxInvestmentShort() const{return m_maxInvestmentShort;}
//	const Money& GetMaxInvestment() const{return m_maxInvestment;}

#ifndef TAKION_NO_OPTIONS
	Money GetOptionInvestment() const{return m_optionInvestment;}
	Money GetOptionInvestmentLong() const{return m_optionInvestmentLong;}
	Money GetOptionInvestmentShort() const{return m_optionInvestmentShort;}
	const Money& GetMaxOptionInvestment() const{return m_maxOptionInvestment;}
	const Money& GetMaxOptionInvestmentLong() const{return m_maxOptionInvestmentLong;}
	const Money& GetMaxOptionInvestmentShort() const{return m_maxOptionInvestmentShort;}

	void SetMaxOptionInvestment(const Money& investment){m_maxOptionInvestment = investment;}
	void SetMaxOptionInvestmentLong(const Money& investment){m_maxOptionInvestmentLong = investment;}
	void SetMaxOptionInvestmentShort(const Money& investment){m_maxOptionInvestmentShort = investment;}

	void SetConditionallyMaxOptionInvestment(const Money& investment){if(m_maxOptionInvestment < investment)m_maxOptionInvestment = investment;}
	void SetConditionallyMaxOptionInvestmentLong(const Money& investment){if(m_maxOptionInvestmentLong < investment)m_maxOptionInvestmentLong = investment;}
	void SetConditionallyMaxOptionInvestmentShort(const Money& investment){if(m_maxOptionInvestmentShort < investment)m_maxOptionInvestmentShort = investment;}

	Money GetUnderlierValueLong() const{return m_underlierValueLong;}
	Money GetUnderlierValueShort() const{return m_underlierValueShort;}
	const unsigned int& GetOptionPotentialLongSize() const{return m_optionPotentialLongSize;}//in contracts
	const unsigned int& GetOptionPotentialShortSize() const{return m_optionPotentialShortSize;}//in contracts
	const unsigned int& GetOptionPotentialSize() const{return m_optionPotentialSize;}//in contracts

	const OptionPositionMap& GetOptionPositionsAll() const{return m_optionPositionsAll;}

	unsigned int GetAllOptionPositionCount() const{return (unsigned int)m_optionPositionsAll.GetCount();}
	unsigned int GetAllPositionCount() const{return GetAllOptionPositionCount() + GetAllStockPositionCount();}

	const OptionPositionMap& GetOptionPositions(PositionStatus positionStatus) const{return m_optionPositions[positionStatus];}
	const OptionPositionMap& GetOptionActivePositions() const{return m_optionActivePositions;}//non flat or flat with pending orders
	unsigned int GetOptionActivePositionCount() const{return (unsigned int)m_optionActivePositions.GetCount();}

	OptionPositionMap& GetOptionPositions(PositionStatus positionStatus){return m_optionPositions[positionStatus];}
	TakionIterator* CreateOptionPositionIterator(unsigned int positionStatusMask) const;
	void AddMaskToOptionPositionIterator(TakionIterator* iterator, unsigned int positionStatusMask) const;

	unsigned int GetOptionPositionCountLong() const{return (unsigned int)GetOptionPositions(TU_POSITION_STATUS_LONG).GetCount();}
	unsigned int GetOptionPositionCountShort() const{return (unsigned int)GetOptionPositions(TU_POSITION_STATUS_SHORT).GetCount();}
	unsigned int GetOptionPositionCount() const{return GetOptionPositionCountLong() + GetOptionPositionCountShort();}

	Position* FindOptionPosition(const OptionSymbolBlockKey& key) const
	{
		const OptionPositionMap::CPair* positionPair = m_optionPositionsAll.PLookup(key);
		return positionPair ? positionPair->value : NULL;
	}
	Position* FindOptionPosition(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return FindOptionPosition(OptionSymbolBlockKey(rootSymbol, optionBlock));
	}
	Position* FindPosition(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return optionBlock ? FindOptionPosition(OptionSymbolBlockKey(rootSymbol, optionBlock)) : FindStockPosition(rootSymbol);
	}

	Position* FindOptionActivePosition(const OptionSymbolBlockKey& key) const
	{
		const OptionPositionMap::CPair* positionPair = m_optionActivePositions.PLookup(key);
		return positionPair ? positionPair->value : NULL;
	}
	Position* FindOptionActivePosition(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return FindOptionActivePosition(OptionSymbolBlockKey(rootSymbol, optionBlock));
	}
	Position* FindActivePosition(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return optionBlock ? FindOptionActivePosition(OptionSymbolBlockKey(rootSymbol, optionBlock)) : FindStockActivePosition(rootSymbol);
	}
#endif
	Position* FindStockPosition(const unsigned __int64& symbol) const
	{
		const PositionMap::CPair* positionPair = m_stockPositionsAll.PLookup(symbol);
		return positionPair ? positionPair->value : NULL;
	}

	Position* FindPosition(const Position* position) const
	{
#ifndef TAKION_NO_OPTIONS
		return FindPosition(position->GetNumericSymbol(), position->GetOptionBlock());
#else
		return FindStockPosition(position->GetNumericSymbol());
#endif
	}

	Position* FindStockActivePosition(const unsigned __int64& symbol) const
	{
		const PositionMap::CPair* positionPair = m_stockActivePositions.PLookup(symbol);
		return positionPair ? positionPair->value : NULL;
	}

	Position* FindActivePosition(const Position* position) const
	{
#ifndef TAKION_NO_OPTIONS
		return FindActivePosition(position->GetNumericSymbol(), position->GetOptionBlock());
#else
		return FindStockActivePosition(position->GetNumericSymbol());
#endif
	}

	const PositionMap& GetStockPositionsAll() const{return m_stockPositionsAll;}
	PositionMap& GetStockPositionsAll(){return m_stockPositionsAll;}
	unsigned int GetAllStockPositionCount() const{return (unsigned int)m_stockPositionsAll.GetCount();}

	const PositionMap& GetStockPositions(PositionStatus positionStatus) const{return m_stockPositions[positionStatus];}
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
		if(security)
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
		return NULL;
	}
	Position* FindActivePosition(const Security* security) const
	{
		if(security)
		{
#ifndef TAKION_NO_OPTIONS
			const OptionInfo* optionInfo = security->GetOptionInfo();
			if(optionInfo)
			{		
				const OptionPositionMap::CPair* positionPair = m_optionActivePositions.PLookup(OptionSymbolBlockKey(security->GetNumericSymbol(), optionInfo->GetOptionBlock()));
				return positionPair ? positionPair->value : NULL;
			}
			else
			{
#endif
				const PositionMap::CPair* positionPair = m_stockActivePositions.PLookup(security->GetNumericSymbol());
				return positionPair ? positionPair->value : NULL;
#ifndef TAKION_NO_OPTIONS
			}
#endif
		}
		return NULL;
	}
//	virtual HANDLE GetThreadHandle() const{return NULL;}
	virtual unsigned int GetThreadId() const{return 0;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}
	AccountInventoryData& operator=(const AccountInventoryData& other)
	{
		InventoryData::operator=(other);
		m_longSize = other.m_longSize;
		m_shortSize = other.m_shortSize;
		m_investmentLong = other.m_investmentLong;
		m_investmentShort = other.m_investmentShort;
		m_investmentMeLong = other.m_investmentMeLong;
		m_investmentMeShort = other.m_investmentMeShort;
		m_investmentBetaLong = other.m_investmentBetaLong;
		m_investmentBetaShort = other.m_investmentBetaShort;
		m_investmentCostLong = other.m_investmentCostLong;
		m_investmentCostShort = other.m_investmentCostShort;
//		m_maxInvestmentLong = other.m_maxInvestmentLong;
//		m_maxInvestmentShort = other.m_maxInvestmentShort;
//		m_maxInvestment = other.m_maxInvestment;
		unsigned char i;
#ifndef TAKION_NO_OPTIONS
		m_optionInvestment = other.m_optionInvestment;
		m_optionInvestmentLong = other.m_optionInvestmentLong;
		m_optionInvestmentShort = other.m_optionInvestmentShort;
		m_maxOptionInvestment = other.m_maxOptionInvestment;
		m_maxOptionInvestmentLong = other.m_maxOptionInvestmentLong;
		m_maxOptionInvestmentShort = other.m_maxOptionInvestmentShort;
		m_underlierValueLong = other.m_underlierValueLong;
		m_underlierValueShort = other.m_underlierValueShort;
		m_optionPotentialLongSize = other.m_optionPotentialLongSize;//in contracts
		m_optionPotentialShortSize = other.m_optionPotentialShortSize;//in contracts
		m_optionPotentialSize = other.m_optionPotentialSize;//in contracts

		U_CopyCMap(m_optionPositionsAll, other.m_optionPositionsAll);
		for(i = 0; i < TU_POSITION_STATUS_COUNT; ++i)
		{
			U_CopyCMap(m_optionPositions[i], other.m_optionPositions[i]);
		}
		U_CopyCMap(m_optionActivePositions, other.m_optionActivePositions);
#endif
		U_CopyCMap(m_stockPositionsAll, other.m_stockPositionsAll);
		for(i = 0; i < TU_POSITION_STATUS_COUNT; ++i)
		{
			U_CopyCMap(m_stockPositions[i], other.m_stockPositions[i]);
		}
		U_CopyCMap(m_stockActivePositions, other.m_stockActivePositions);

		return *this;
	}
protected:
	AccountInventoryData():
#ifndef TAKION_NO_OPTIONS
		m_optionPotentialLongSize(0),//in contracts
		m_optionPotentialShortSize(0),//in contracts
		m_optionPotentialSize(0),//in contracts
#endif
		m_longSize(0),
		m_shortSize(0)
//		m_size(0)
	{}
	AccountInventoryData(const AccountInventoryData& other):
		InventoryData(other),
#ifndef TAKION_NO_OPTIONS
		m_optionInvestment(other.m_optionInvestment),
		m_optionInvestmentLong(other.m_optionInvestmentLong),
		m_optionInvestmentShort(other.m_optionInvestmentShort),
		m_maxOptionInvestment(other.m_maxOptionInvestment),
		m_maxOptionInvestmentLong(other.m_maxOptionInvestmentLong),
		m_maxOptionInvestmentShort(other.m_maxOptionInvestmentShort),

		m_underlierValueLong(other.m_underlierValueLong),
		m_underlierValueShort(other.m_underlierValueLong),
		m_optionPotentialLongSize(other.m_optionPotentialLongSize),//in contracts
		m_optionPotentialShortSize(other.m_optionPotentialShortSize),//in contracts
		m_optionPotentialSize(other.m_optionPotentialSize),//in contracts
#endif
		m_longSize(other.m_longSize),
		m_shortSize(other.m_shortSize),
		m_investmentLong(other.m_investmentLong),
		m_investmentShort(other.m_investmentShort),
		m_investmentMeLong(other.m_investmentMeLong),
		m_investmentMeShort(other.m_investmentMeShort),
		m_investmentBetaLong(other.m_investmentBetaLong),
		m_investmentBetaShort(other.m_investmentBetaShort),
		m_investmentCostLong(other.m_investmentCostLong),
		m_investmentCostShort(other.m_investmentCostShort)
//		m_maxInvestmentLong(other.m_maxInvestmentLong),
//		m_maxInvestmentShort(other.m_maxInvestmentShort)
//		m_maxInvestment(other.m_maxInvestment)
	{
		unsigned char i;
#ifndef TAKION_NO_OPTIONS
		U_CopyCMap(m_optionPositionsAll, other.m_optionPositionsAll);
		for(i = 0; i < TU_POSITION_STATUS_COUNT; ++i)
		{
			U_CopyCMap(m_optionPositions[i], other.m_optionPositions[i]);
		}
		U_CopyCMap(m_optionActivePositions, other.m_optionActivePositions);
#endif
		U_CopyCMap(m_stockPositionsAll, other.m_stockPositionsAll);
		for(i = 0; i < TU_POSITION_STATUS_COUNT; ++i)
		{
			U_CopyCMap(m_stockPositions[i], other.m_stockPositions[i]);
		}
		U_CopyCMap(m_stockActivePositions, other.m_stockActivePositions);
	}

	virtual void StockPositionAdded(Position* position){}
	void CalculateAllPositionLeverage();
	void NullifyAllPositionLeverage();
	virtual bool UpdateLeverage() override;

	virtual void AddPosition(Position* position);//called in the worker thread only. Account must be locked for modification before the call
	virtual void RemovePosition(Position* position);//called in the worker thread only. Account must be locked for modification before the call
	virtual void RemovePositionTemporarily(Position* position);//called in the worker thread only. Account must be locked for modification before the call
	virtual void ReAddPosition(Position* position);//Add after temporarily RemovePosition(Position* position); //called in the worker thread only. Account must be locked for modification before the call
	virtual void AddActivePosition(Position* position);
	virtual void RemoveActivePosition(Position* position);
	void PlacePosition(Position* position, int prevSize, int currentSize);
	virtual void ClearPositions();

	virtual void DoAddActiveStockPosition(const unsigned __int64& symbol, Position* position);
#ifndef TAKION_NO_OPTIONS
	virtual void DoAddActiveOptionPosition(const OptionSymbolBlockKey& key, Position* position);
	OptionPositionMap m_optionPositionsAll;
	OptionPositionMap m_optionPositions[TU_POSITION_STATUS_COUNT];
	OptionPositionMap m_optionActivePositions;//non flat or flat with pending orders

	Money m_optionInvestment;
	Money m_optionInvestmentLong;
	Money m_optionInvestmentShort;
	Money m_maxOptionInvestment;
	Money m_maxOptionInvestmentLong;
	Money m_maxOptionInvestmentShort;

	Money m_underlierValueLong;
	Money m_underlierValueShort;
	unsigned int m_optionPotentialLongSize;//in contracts
	unsigned int m_optionPotentialShortSize;//in contracts
	unsigned int m_optionPotentialSize;//in contracts
#endif

	PositionMap m_stockPositionsAll;
	PositionMap m_stockPositions[TU_POSITION_STATUS_COUNT];
	PositionMap m_stockActivePositions;//non flat or flat with pending orders

	unsigned int m_longSize;
	unsigned int m_shortSize;
//	unsigned int m_size;
	Money m_investmentLong;
	Money m_investmentShort;
	Money m_investmentMeLong;
	Money m_investmentMeShort;
	Money m_investmentBetaLong;
	Money m_investmentBetaShort;
	Money m_investmentCostLong;
	Money m_investmentCostShort;
//	Money m_maxInvestmentLong;
//	Money m_maxInvestmentShort;
//	Money m_maxInvestment;
	void UpdateMaxInvestmentBeta()
	{
		if(m_maxInvestmentLongBeta < m_investmentBetaLong)m_maxInvestmentLongBeta = m_investmentBetaLong;
		if(m_maxInvestmentShortBeta < m_investmentBetaShort)m_maxInvestmentShortBeta = m_investmentBetaShort;
		if(m_maxInvestmentBeta < m_investmentBeta)m_maxInvestmentBeta = m_investmentBeta;
	}
	void UpdateMaxInvestmentMe()
	{
		if(m_maxInvestmentLongMe < m_investmentMeLong)m_maxInvestmentLongMe = m_investmentMeLong;
		if(m_maxInvestmentShortMe < m_investmentMeShort)m_maxInvestmentShortBeta = m_investmentBetaShort;
		if(m_maxInvestmentMe < m_investmentMe)m_maxInvestmentMe = m_investmentMe;
	}

#ifndef TAKION_NO_OPTIONS
	void UpdateMaxOptionInvestment()
	{
		if(m_maxOptionInvestmentLong < m_optionInvestmentLong)m_maxOptionInvestmentLong = m_optionInvestmentLong;
		if(m_maxOptionInvestmentShort < m_optionInvestmentShort)m_maxOptionInvestmentShort = m_optionInvestmentShort;
		if(m_maxOptionInvestment < m_optionInvestment)m_maxOptionInvestment = m_optionInvestment;
	}
#endif
	void UpdateMaxInvestment()
	{
		if(m_maxInvestmentLong < m_investmentLong)m_maxInvestmentLong = m_investmentLong;
		if(m_maxInvestmentShort < m_investmentShort)m_maxInvestmentShort = m_investmentShort;
		if(m_maxInvestment < m_investment)m_maxInvestment = m_investment;
#ifndef TAKION_NO_OPTIONS
		UpdateMaxOptionInvestment();
#endif
		UpdateMaxInvestmentBeta();
		UpdateMaxInvestmentMe();
	}

	bool SetPositionOpenPnlForLossUpdated(PositionInventoryData* position, const bool& updated)
	{
		return position->SetOpenPnlForLossUpdated(updated);
	}
	bool SetPositionInvalidSecurity(PositionInventoryData* position, const bool& invalid)
	{
		return position->SetInvalidSecurity(invalid);
	}

	virtual void IncrementUpdatedPnlPositionCount(const bool openPnlForLossUpdated){}
	virtual void DecrementUpdatedPnlPositionCountWithoutLock(){}
	virtual void DecrementLoadedPositionCountWithoutLock(){}
};

class TU_API AccountInventory : public AccountInventoryData
{
friend class Account;
public:
	AccountInventory(const Account* account);

	DECLARE_NED_NEW
	virtual const int& GetPositionSize(const PositionData* position) const{return position->GetSizeInv(true);}
	const unsigned int& GetInventoryLongSize() const{return m_inventoryLongSize;}
	const unsigned int& GetInventoryShortSize() const{return m_inventoryShortSize;}
	const unsigned int& GetInventorySize() const{return m_inventorySize;}

	virtual const Money& GetInventoryInvestment() const override{return m_inventoryInvestment;}
	virtual const Money& GetInventoryNbboPrintOpenPnl() const override{return m_inventoryNbboPrintOpenPnl;}

	const PositionMap& GetStockPositionsInventory() const{return m_stockPositionsInventory;}
	unsigned int GetStockPositionInventoryCount() const{return (unsigned int)m_stockPositionsInventory.GetCount();}

	const PositionMap& GetStockPositionsHidden() const{return m_stockPositionsHidden;}
	unsigned int GetStockPositionHiddenCount() const{return (unsigned int)m_stockPositionsHidden.GetCount();}
/*
	const PositionMap& GetStockPositionsInventoryLong() const{return m_stockPositionsInventoryLong;}
	const PositionMap& GetStockPositionsInventoryShort() const{return m_stockPositionsInventoryShort;}
	unsigned int GetStockPositionInventoryLongCount() const{return (unsigned int)m_stockPositionsInventoryLong.GetCount();}
	unsigned int GetStockPositionInventoryShortCount() const{return (unsigned int)m_stockPositionsInventoryShort.GetCount();}
	unsigned int GetStockPositionInventoryCount() const{return GetStockPositionInventoryLongCount() + GetStockPositionInventoryShortCount();}
*/
#ifndef TAKION_NO_OPTIONS
	const OptionPositionMap& GetOptionPositionsInventory() const{return m_optionPositionsInventory;}
	unsigned int GetOptionPositionInventoryCount() const{return (unsigned int)m_optionPositionsInventory.GetCount();}
	unsigned int GetPositionInventoryCount() const{return GetStockPositionInventoryCount() + GetOptionPositionInventoryCount();}

	const OptionPositionMap& GetOptionPositionsHidden() const{return m_optionPositionsHidden;}
	unsigned int GetOptionPositionHiddenCount() const{return (unsigned int)m_optionPositionsHidden.GetCount();}
	unsigned int GetPositionHiddenCount() const{return GetStockPositionHiddenCount() + GetOptionPositionHiddenCount();}
/*
	const OptionPositionMap& GetOptionPositionsInventoryLong() const{return m_optionPositionsInventoryLong;}
	const OptionPositionMap& GetOptionPositionsInventoryShort() const{return m_optionPositionsInventoryShort;}
	unsigned int GetOptionPositionInventoryLongCount() const{return (unsigned int)m_optionPositionsInventoryLong.GetCount();}
	unsigned int GetOptionPositionInventoryShortCount() const{return (unsigned int)m_optionPositionsInventoryShort.GetCount();}
	unsigned int GetOptionPositionInventoryCount() const{return GetOptionPositionInventoryLongCount() + GetOptionPositionInventoryShortCount();}
	unsigned int GetPositionInventoryCount() const{return GetStockPositionInventoryCount() + GetOptionPositionInventoryCount();}
*/
#endif
	virtual unsigned int GetThreadId() const override;

	virtual Money GetEstimatedBeginningEquity() const override;
	virtual void Reset() override
	{
		AccountInventoryData::Reset();
		m_inventoryLongSize = 0;
		m_inventoryShortSize = 0;
		m_inventorySize = 0;
		m_inventoryInvestment.SetZero();
		m_inventoryNbboPrintOpenPnl.SetZero();
	}
	void AdjustInventoryNbboPrintOpenPnl(const Money& diff)
	{
		m_inventoryNbboPrintOpenPnl += diff;
	}
protected:
	virtual void ClearPositions() override
	{
		AccountInventoryData::ClearPositions();
		m_stockPositionsInventory.RemoveAll();
		m_stockPositionsHidden.RemoveAll();
#ifndef TAKION_NO_OPTIONS
		m_optionPositionsInventory.RemoveAll();
		m_optionPositionsHidden.RemoveAll();
#endif
	}
	virtual void RemovePosition(Position* position) override
	{
		AccountInventoryData::RemovePosition(position);
/*
#ifndef TAKION_NO_OPTIONS
typedef CMap<OptionSymbolBlockKey, const OptionSymbolBlockKey&, Position*, Position*> OptionPositionMap;
#endif
*/
		const unsigned __int64& numericSymbol = position->GetNumericSymbol();
		m_stockPositionsInventory.RemoveKey(numericSymbol);
		m_stockPositionsHidden.RemoveKey(numericSymbol);
#ifndef TAKION_NO_OPTIONS
		OptionSymbolBlockKey optionSymbolBlock(numericSymbol, position->GetOptionBlock());
		m_optionPositionsInventory.RemoveKey(optionSymbolBlock);
		m_optionPositionsHidden.RemoveKey(optionSymbolBlock);
#endif
	}
	void DecrementInventorySize(int size);
	void IncrementInventorySize(int size);
	void AdjustInventory(Position* position, const PositionInventory& prevInventory);//, const unsigned char marketState);
	void AdjustOvernightInventory(Position* position, const PositionInventory& prevInventory);
	void AdjustInventoryPotentialValues(Position* position, const PositionInventory& prevInventory);
	void AddInventoryPosition(Position* position);
	void RemoveInventoryPosition(Position* position);
	void AddHiddenPosition(Position* position);
	void RemoveHiddenPosition(Position* position);
/*
	virtual void AddPosition(Position* position);//called in the worker thread only. Account must be locked for modification before the call
	virtual void RemovePosition(Position* position);//called in the worker thread only. Account must be locked for modification before the call
	virtual void ReAddPosition(Position* position);//Add after temporarily RemovePosition(Position* position); //called in the worker thread only. Account must be locked for modification before the call
	virtual void PlacePosition(Position* position, int prevSize, int currentSize);//called in the worker thread only. Account must be locked for modification before the call
*/
	void AddPositionUnconditionally(Position* position);
	const Account* m_account;
	unsigned int m_inventoryLongSize;
	unsigned int m_inventoryShortSize;
	unsigned int m_inventorySize;
	Money m_inventoryInvestment;
	Money m_inventoryNbboPrintOpenPnl;
	virtual void DoAddActiveStockPosition(const unsigned __int64& symbol, Position* position);
#ifndef TAKION_NO_OPTIONS
	virtual void DoAddActiveOptionPosition(const OptionSymbolBlockKey& key, Position* position);
//	OptionPositionMap m_optionPositionsInventoryLong;
//	OptionPositionMap m_optionPositionsInventoryShort;
	OptionPositionMap m_optionPositionsInventory;
	OptionPositionMap m_optionPositionsHidden;
#endif
//	PositionMap m_stockPositionsInventoryLong;
//	PositionMap m_stockPositionsInventoryShort;
	PositionMap m_stockPositionsInventory;
	PositionMap m_stockPositionsHidden;
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
		m_numericName = U_RepresentStringAsUnsignedNumber<unsigned int>(m_name.c_str());//*(unsigned int*)m_name.c_str();
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
//	static const unsigned char nameCount = 3;
	Destination(const char* name,
#ifndef TAKION_NO_OPTIONS
		const char* optionName,
		unsigned char optionSource,
#endif
		const unsigned __int64& id,
		unsigned char source,
		unsigned char hasMnemonic,
		bool borrow,
		unsigned char supportsHidden,
		unsigned char supportsExpiration,
		unsigned char supportsTifExtended,
		bool qsmtReplaceable,
		unsigned short noRoutingReplacementId,
		unsigned short proActiveReplacementId,
//		unsigned short dmaReplacementId,
		unsigned short noRoutingReplacementSubtype,
		unsigned short proActiveReplacementSubtype,
//		const char* altName1,
//		const char* altName2,
		unsigned char supportsIoc = SE_YES,
		unsigned int locateVenue = 0);
//		const char* noRoutingReplacementName,
//		const char* proActiveReplacementName);
	Destination(const Destination& other);
	~Destination(){ClearRoutings();}
	Destination& operator=(const Destination& other);

	const char* GetMainName() const{return m_name.c_str();}
	const std::string& GetMainNameStr() const{return m_name;}
	unsigned int GetMainNumericName() const
	{
		return
#ifndef TAKION_NO_OPTIONS
			!m_numericName ? m_optionNumericName:
#endif
			m_numericName;
	}
/*
	const char* GetAltName() const{return m_altName.c_str();}
	const std::string& GetAltNameStr() const{return m_altName;}
	unsigned int GetNumericAltName() const{return m_numericAltName;}
*/
/*
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
*/
	const std::string& GetProperNameStr() const
	{
		return
#ifndef TAKION_NO_OPTIONS
			m_name.empty() ? m_optionName:
#endif
			m_name;
	}
	const char* GetProperName() const{return GetProperNameStr().c_str();}
	unsigned int GetNumericProperName() const
	{
		return
#ifndef TAKION_NO_OPTIONS
			!m_numericName ? m_optionNumericName:
#endif
			m_numericName;
	}
#ifndef TAKION_NO_OPTIONS
	const std::string& GetOptionNameStr() const{return m_optionName.empty() ? m_name : m_optionName;}
	const char* GetOptionName() const{return m_optionName.empty() ? m_name.c_str() : m_optionName.c_str();}
	unsigned int GetOptionNumericName() const{return m_optionNumericName ? m_optionNumericName : m_numericName;}

	const std::string& GetOptionNameStrProper() const{return m_optionName;}
	const char* GetOptionNameProper() const{return m_optionName.c_str();}
	const unsigned int& GetOptionNumericNameProper() const{return m_optionNumericName;}

	const unsigned char& GetOptionSource() const{return m_optionSource;}
//	unsigned int GetApplicability() const{return (m_numericName[0] ? 1 << ST_STOCK : 0) | (m_optionNumericName ? 1 << ST_OPTION : 0);}
	unsigned int GetApplicability() const{return (m_numericName ? 1 << ST_STOCK : 0) | (m_optionNumericName ? 1 << ST_OPTION : 0);}
#endif
	const unsigned __int64& GetId() const{return m_id;}
	const unsigned char& GetSource() const{return m_source;}
	const bool& isBorrow() const{return m_borrow;}
	const unsigned char& HasMnemonic() const{return m_hasMnemonic;}
	const unsigned char& GetSupportHidden() const{return m_supportsHidden;}
	const unsigned char& GetSupportExpiration() const{return m_supportsExpiration;}
	const unsigned char& GetSupportIoc() const{return m_supportsIoc;}
	unsigned char GetSupportExpirationAndIoc() const{return m_supportsExpiration | m_supportsIoc;}
	bool isSupportMonitoring(const char& tif) const
	{
		switch(tif)
		{
			case TIF_IOC:
			return (m_supportsIoc & SE_TAKION) != 0;

			case TIF_GTD:
			return (m_supportsExpiration & SE_TAKION) != 0;

			default:
			return false;
		}
	}
//	unsigned char GetSupportExpirationAndIoc() const{return m_supportsExpiration & m_supportsIoc;}
	const unsigned char& GetSupportTifExtended() const{return m_supportsTifExtended;}
	char GetExpirationTif(const char& tif) const// = TIF_GTD) const
	{
//		return m_supportsExpiration == SE_YES ? TIF_GTD : m_supportsTifExtended ? TIF_GTX : TIF_DAY;
//		return (tif == TIF_IOC ? m_supportsIoc == SE_YES : m_supportsExpiration == SE_YES) ? tif : m_supportsTifExtended ? TIF_GTX : TIF_DAY;
		switch(tif)
		{
			case TIF_IOC:
			if(m_supportsIoc & SE_NO)
			{
				return m_supportsTifExtended ? TIF_GTX : TIF_DAY;
			}
			break;

			case TIF_GTD:
			if(m_supportsExpiration & SE_NO)
			{
				return m_supportsTifExtended ? TIF_GTX : TIF_DAY;
			}
			break;
		}
		return tif;
	}
	bool SetSupportTakionExpiration(const bool& support)
	{
		bool ret = false;
//		if(!(m_supportsExpiration & SE_NO))
		if(m_supportsExpiration & SE_NO)
		{
			if(support)
			{
				m_supportsExpiration |= SE_TAKION;
			}
			else
			{
				m_supportsExpiration &= ~SE_TAKION;
			}
			ret = true;
		}
//		if(!(m_supportsIoc & SE_NO))
		if(m_supportsIoc & SE_NO)
		{
			if(support)
			{
				m_supportsIoc |= SE_TAKION;
			}
			else
			{
				m_supportsIoc &= ~SE_TAKION;
			}
			ret = true;
		}
		return ret;
	}

	const bool& isQsmtReplaceable() const{return m_qsmtReplaceable;}

	typedef std::map<unsigned int, const DestinationRouting*> RoutingMap;
	DestinationRouting* AddRouting(const char* name, unsigned short id, unsigned short subtype, char label, const char* description, unsigned int minReserveQuantity = 0, unsigned int maxReserveQuantity = 0, const char* reserveName = NULL);
	void ClearRoutings();
	unsigned int GetRoutingCount() const{return (unsigned int)m_routingMap.size();}
	const RoutingMap& GetRoutingMap() const{return m_routingMap;}
	const DestinationRouting* FindRouting(unsigned short id, unsigned short subtype) const{RoutingMap::const_iterator found = m_routingMap.find(((unsigned int)subtype << 16) | (unsigned int)id); return found == m_routingMap.end() ? NULL : found->second;}
	const DestinationRouting* FindRoutingBySuperId(unsigned int superId) const{RoutingMap::const_iterator found = m_routingMap.find(superId); return found == m_routingMap.end() ? NULL : found->second;}

	const RoutingMap& GetRoutingNameMap() const{return m_routingNameMap;}
	const DestinationRouting* FindRoutingByNumericName(unsigned int numericName) const{RoutingMap::const_iterator found = m_routingNameMap.find(numericName); return found == m_routingNameMap.end() ? NULL : found->second;}
	const DestinationRouting* FindRoutingByName(const char* name) const{return FindRoutingByNumericName(U_RepresentStringAsUnsignedNumber<unsigned int>(name));}

	void CopyRoutings(const Destination& other);
	const DestinationRouting* const& GetNoRoutingReplacement() const{return m_noRoutingReplacement;}
	const DestinationRouting* const& GetProActiveReplacement() const{return m_proActiveReplacement;}
//	const DestinationRouting* GetDmaReplacement() const{return m_dmaReplacement;}
	const unsigned short& GetNoRoutingReplacementId() const{return m_noRoutingReplacementId;}
	const unsigned short& GetNoRoutingReplacementSubtype() const{return m_noRoutingReplacementSubtype;}

	const unsigned short& GetProActiveReplacementId() const{return m_proActiveReplacementId;}
	const unsigned short& GetProActiveReplacementSubtype() const{return m_proActiveReplacementSubtype;}
//	unsigned short GetDmaReplacementId() const{return m_dmaReplacementId;}
	const unsigned int& GetLocateVenue() const{return m_locateVenue;}

protected:
//	std::string m_name[nameCount];
//	unsigned int m_numericName[nameCount];

	std::string m_name;
	unsigned int m_numericName;

	unsigned int m_locateVenue;

#ifndef TAKION_NO_OPTIONS
	std::string m_optionName;
	unsigned int m_optionNumericName;
	unsigned char m_optionSource;
#endif
//	unsigned int m_numericAltName;
	unsigned __int64 m_id;
	unsigned char m_source;
	bool m_borrow;
	unsigned char m_hasMnemonic;//MnemonicType: 1 - MT_MNEMONIC; 2 - MT_MM;
	unsigned char m_supportsHidden;
	unsigned char m_supportsExpiration;
	unsigned char m_supportsIoc;
	unsigned char m_supportsTifExtended;
	bool m_qsmtReplaceable;
	RoutingMap m_routingMap;
	RoutingMap m_routingNameMap;
//	std::string m_noRoutingReplacementName;
//	std::string m_proActiveReplacementName;

	unsigned short m_noRoutingReplacementId;
	unsigned short m_noRoutingReplacementSubtype;

	unsigned short m_proActiveReplacementId;
	unsigned short m_proActiveReplacementSubtype;
//	unsigned short m_dmaReplacementId;
	const DestinationRouting* m_noRoutingReplacement;
	const DestinationRouting* m_proActiveReplacement;
//	const DestinationRouting* m_dmaReplacement;
};

enum PostponedEnum : unsigned char
{
	PE_NOT_POSTPONED,
	PE_CHECK_TIME,
	PE_POSTPONED,
};

class OrderAlgorithm;

class TU_API Account : public AccountInventoryData, public Observable, public TakionLock
{
friend class Position;
friend class PositionInventory;
friend class ClearingFirm;
public:
	virtual ~Account();

//	static const unsigned int uintZero;

#if (_MSC_VER > 1600)
	typedef std::unordered_set<Order*> OrderSet;
	typedef std::unordered_set<Position*> PositionSet;
#else
	typedef std::hash_set<Order*> OrderSet;
	typedef std::hash_set<Position*> PositionSet;
#endif
//	typedef std::set<Order*, lessOrderReplace> OrderReplaceSet;

	typedef CMap<unsigned __int64, const unsigned __int64&, unsigned __int64, const unsigned __int64&> UInt64UInt64Map;
	unsigned int GetRestrictedSymbolCount() const{return (unsigned int)m_restrictedSymbolMap.GetCount();}
	const UInt64UInt64Map& GetRestrictedSymbolMap() const{return m_restrictedSymbolMap;}
	const bool& isRestrictedSymbolMapLoaded() const{return m_restrictedSymbolMapLoaded;}
	unsigned __int64 FindRetrictedSymbol(const unsigned __int64& symbol) const
	{
		unsigned __int64 ret = 0xFFFFFFFFFFFFFFFF;
		LockRestrictedSymbolInquiryWait();
		const UInt64UInt64Map::CPair* found = m_restrictedSymbolMap.PLookup(symbol);
		if(found)ret = found->value;
		UnlockRestrictedSymbolInquiry();
		return ret;
	}

/*
	bool isSymbolRetricted(const unsigned __int64& symbol) const
	{
		bool ret = false;
		LockRestrictedSymbolInquiryWait();
		if(m_restrictedSymbolMap.PLookup(symbol))ret = true;
		UnlockRestrictedSymbolInquiry();
		return ret;
	}
*/
	bool LockRestrictedSymbolInquiry() const{return m_restrictedSymbolLock.LockInquiry();}
	void LockRestrictedSymbolInquiryWait() const{return m_restrictedSymbolLock.LockInquiryWait();}
	void UnlockRestrictedSymbolInquiry() const{m_restrictedSymbolLock.UnlockInquiry();}

//	virtual bool isAutoCloseActive() const{return false;}
	virtual unsigned char GetOversellSplitPolicy() const{return OOP_RESIZE;}

	bool isDestinationQsmtReplaceable(const Destination* destination,
#ifndef TAKION_NO_OPTIONS
		bool option,
#endif
		char primaryExchange) const
	{
		return destination->isQsmtReplaceable() && 
#ifndef TAKION_NO_OPTIONS
			(option ||
#endif
			isDestinationQsmtReplaceableInAccount(destination, primaryExchange)
#ifndef TAKION_NO_OPTIONS
			)
#endif
			;
	}
	virtual const char* GetDestinationNameById(const unsigned __int64& destinationId) const{return "";}
	virtual const char* GetOrderTypeNameByOrderType(unsigned int orderType) const{return "";}
	static void GetSideAsString(std::string& str, char side);
	void GetOrderErrorAsString(std::string& error,
		const char* symbol,
		char side,
#ifdef FIRM_VALUES
		char firmSide,
#endif
		bool borrow,
		unsigned int orderSize,
		unsigned char errorCode,
		const Money& moneyValue,
		const Money& moneyConstraint,
		unsigned int uintValue,
		unsigned int uintConstraint) const;

	void GetCancelErrorAsString(std::string& error,
		const char* symbol,
		char side,
#ifdef FIRM_VALUES
		char firmSide,
#endif
		unsigned int clientId,
		unsigned char errorCode,
		const Money& moneyValue,
		const Money& moneyConstraint,
		unsigned int uintValue,
		unsigned int uintConstraint) const;
	const char* GetUserName() const{return m_userName.GetId();}
	const AccountId& GetUserNameId() const{return m_userName;}
	const char* GetClearingAccountName() const{return m_clearingAccountId.GetId();}
	const AccountId& GetClearingAccountId() const{return m_clearingAccountId;}
	const unsigned __int64& GetClearingAccountNamePart1() const{return m_clearingAccountId.GetFirst();}//*(unsigned __int64*)m_clearingAccountName;}
	const unsigned __int64& GetClearingAccountNamePart2() const{return m_clearingAccountId.GetSecond();}//*(unsigned __int64*)(m_clearingAccountName + sizeof(unsigned __int64));}
	const unsigned char& GetClearingFirmOrdinal() const{return m_clearingFirmOrdinal;}

	const char* GetFirmId() const{return m_firmId;}
	const unsigned int& GetFirmIdNum() const{return m_firmIdNum;}

	const char* GetStockLoanFirmId() const{return m_stockLoanFirmId;}
	const unsigned int& GetStockLoanFirmIdNum() const{return m_stockLoanFirmIdNum;}
	const unsigned char& GetStockLoanFirmOrdinal() const{return m_stockLoanFirmOrdinal;}

	virtual bool isAdvOrderType(const unsigned char orderType) const{return true;}

	virtual bool isDefaultAccount() const{return false;}
	virtual bool isSupervisor() const{return false;}
	virtual bool CanAutoCancel() const{return true;}

//	virtual unsigned int GetOrderProcessingFlags() const{return 0;}//some entitlements coming from the server
	const unsigned int& GetLocateVenue() const{return m_locateVenue;}
	const unsigned int& GetOrderProcessingFlags() const{return m_orderProcessingFlags;}//some entitlements coming from the server
	const unsigned int& GetAccountProcessingFlags() const{return m_accountProcessingFlags;}
	virtual const unsigned int& GetDisplayableOrderProcessingFlags() const{return uintZero;}
	virtual const unsigned int& GetDisplayableAccountProcessingFlags() const{return uintZero;}

/*
	bool Lock() const{return InterlockedExchange(&m_lockForObservingInMainThread, 1) == 0;}
	void Unlock() const{InterlockedExchange(&m_lockForObservingInMainThread, 0);}
	void LockWait() const{while(!Lock())Sleep(0);}
*/
	void AddInThreadObserver(Observer* o) const;//Call RemoveInThreadObserver in the destructor of the object that you pass to this function
	void RemoveInThreadObserver(Observer* o) const;
	void NotifyInThreadObservers(const Message* message, const Message* info = NULL) const;
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
	virtual unsigned char SendOrder(unsigned int* const& sendId,//output parameter; can be NULL. Is assigned to m_sendId of all orders resulting from this function call. If only one order, then it also will be the client id of the order
		Order* const& orderToReplace,
		const bool& replaceNative,
		const int& replaceSizeOffset,
		const Security* const& security,

		const unsigned char& postponed,//PE_NOT_POSTPONED - not postponed, PE_CHECK_TIME - determine by timeToActivate, PE_POSTPONED - postponed (PostponedEnum)
		const unsigned int& timeToActivate,//postpone until millisecond since midnight, 0 if not postponed

		const unsigned int& destinationName,
		const unsigned __int64& destinationId,

		const char& side,

		const unsigned char& orderType,
		const unsigned short& userOrderType,//usually should be 0
		const char* const& userOrderInfo,//usually should be NULL
		const Price& limitPrice,
		const Price& discretionaryPrice,

		const Price& stopPrice,
		const unsigned char& stopOrderType,
		const unsigned char& stopOrderBase,

		Price& level1Bid,
		Price& level1Ask,
		Price& lastPrint,

		const unsigned int& quantity,
		const unsigned int& displayQuantity,
		const unsigned int& reserveQuantity,

		const unsigned short& routingId,
		const unsigned short& routingSubType,
		const unsigned int& routingName,
		const unsigned int& mnemonic,
		//		const bool& proactive,
		const bool& iso,

		const unsigned char& pegType,
		const SignedPrice& pegOffset,

		const unsigned char& tifType,
		const unsigned int& tifMillisecond,
		const unsigned char& washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		const unsigned char& oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		const bool& resizeShortToBorrowed,
		const bool& preBorrow,
		const Price& preBorrowPrice,
		const bool& noRedirect,
		const bool& closeOnly,
		const bool& resizeToClose,
		const bool& imbalanceOnly,
		//		const bool& proAts,
		const bool& blockAggressiveOrders,
		const unsigned char& roundLotPolicy,
		const std::string* const& isoAttachment,
		const unsigned __int64& userId,
		const unsigned int& parentId,// = 0
		const unsigned int& ocoId,//0 - none; 0xFFFFFFFF - m_currentOcoId of the Account
		const unsigned int& renewMillisecond = 0) = 0;

	typedef std::set<unsigned int> UIntSet;

	virtual unsigned char SendSwipeOrder(unsigned int* const& orderClientId,//output parameter; can be NULL
//		Position* position,
		const Security* const security,
		const unsigned char& postponed,//PE_NOT_POSTPONED - not postponed, PE_CHECK_TIME - determine by timeToActivate, PE_POSTPONED - postponed (PostponedEnum)
		const unsigned int& timeToActivate,//postpone until millisecond since midnight, 0 if not postponed
		const unsigned char& swipeType,
		const UIntSet& destinations,
		const bool& excludeDestinations,
		const UIntSet& filter,
		const char& side,
		const unsigned short& userOrderType,//usually should be 0
		const char* const& userOrderInfo,//usually should be NULL
		const Price& price,
		const unsigned int& quantity,
		const unsigned int& displayQuantity,
		const unsigned int& reserveQuantity,
		const unsigned short& routingId,
		const unsigned int& routingName,

		const unsigned char& tifType,
		const unsigned int& tifMilliseconds,
		const unsigned char& washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		const unsigned char& oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		const bool& resizeShortToBorrowed,
		const bool& preBorrow,
		const Price& preBorrowPrice,
		const bool& noRedirect,
		const bool& closeOnly,
		const bool& resizeToClose,
		const bool& blockAggressiveOrders,
		const unsigned char& roundLotPolicy,
		const bool& hideSlowQuotes,

		const bool& postRemainder,
		const unsigned __int64& postDestinationId,
		const unsigned int& postDestinationName,
		const unsigned int& postRoutingName,
		const unsigned short& postRoutingId,
		const unsigned short& postRoutingSubType,
		const unsigned int& postMnemonic,
		const unsigned char& postTifType,
		const unsigned int& postTif,
		const bool& postRemainderOnIsoViolation,
		const bool& iterate,
		const bool& forceAlgo,
		const unsigned __int64& userId,
		const unsigned int& parentId = 0,
		const unsigned char& pegType = PEG_NONE,//For Spider SmartSwipe only
		const SignedPrice& pegOffset = SignedPrice::signedPriceZero//For Spider SmartSwipe only
		) = 0;
//	const ExecutionMap& GetExecutionMap() const{return m_executionMap;}

	virtual unsigned char SendOrderAlgorithm(const Security* const& security, OrderAlgorithm* const& orderAlgorithm) = 0;

	virtual unsigned char SendPanicCloseOrder(unsigned int* const& orderClientId,//output parameter; can be NULL
		Position* const& position,
		const bool& blockAggressiveOrders,
		const bool& usePanicCommand,
		const unsigned char& marketState,//MSTATE_PREMARKET, MSTATE_MARKET, MSTATE_POSTMARKET
		const bool& proActive,
		const bool& delayProactiveOrderIfStockNotOpen) = 0;// is used only if the trader is a supervisor.

	unsigned char isNewOrderSpoofing(bool buy,
		const Position* position,
		const Price& bestBid,
		const Price& bestAsk,
		const Price& limitPrice,
		const unsigned int size,
		const unsigned int displaySize,
		unsigned int& layeringNumber,
		unsigned int& spoofingNumber) const;

	bool isNewOrderAdvPassive(bool buy,
		const Price& bestBid,
		const Price& bestAsk,
		const Price& lastPrice,
		const Price& limitPrice,
		const unsigned char orderType,
		const unsigned char pegType,
		const unsigned char tifType,
		const unsigned int displaySize) const;

	unsigned char isNewOrderAdv(bool buy,
		const Position* position,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		const Price& bestBid,
		const Price& bestAsk,
		const Price& lastPrice,
		const Price& limitPrice,
		unsigned __int64 averageDailyVolume,
		const unsigned __int64& todaysVolume,
		const unsigned char orderType,
		const unsigned char pegType,
		const unsigned char tifType,
		const unsigned int displaySize,
		unsigned int& constrainingValue) const;

	const OrderMap& GetAllOrders() const{return m_allOrders;}//key is clientId
	const OrderMap& GetOrdersUnacknowledged() const{return m_ordersUnacknowledged;}
	const OrderMap& GetOrdersAcknowledged() const{return m_ordersAcknowledged;}
#if (_MSC_VER > 1600)
	typedef std::unordered_set<Order*> OrderSet;
#else
	typedef std::hash_set<Order*> OrderSet;
#endif
	const OrderSet& GetOrdersFailedToAcknowledge() const{return m_ordersFailedToAcknowledge;}
	const OrderMap& GetOrdersRejected() const{return m_ordersRejected;}
	const OrderMap& GetOrdersBlocked() const{return m_ordersBlocked;}
	const OrderMap& GetOrdersAlgorithm() const{return m_ordersAlgorithm;}
	const OrderMap& GetGtcOrdersAlgorithm() const{return m_gtcOrdersAlgorithm;}

	unsigned int GetOrdersAlgorithmCount() const{return (unsigned int)m_ordersAlgorithm.GetCount();}
	unsigned int GetGtcOrdersAlgorithmCount() const{return (unsigned int)m_gtcOrdersAlgorithm.GetCount();}
	unsigned int GetOrdersAlgorithmCount(const bool& exceptGtc) const
	{
		unsigned int ret = GetOrdersAlgorithmCount();
		if(exceptGtc)
		{
			const unsigned int gtcCount = GetGtcOrdersAlgorithmCount();
			if(gtcCount)
			{
				if(ret > gtcCount)ret -= gtcCount;
				else ret = 0;
			}
		}
		return ret;
	}

	const OrderMap& GetOrdersPending() const{return m_ordersPending;}//Unacknowledged and Acknowledged
	unsigned int GetOrdersPendingCount() const{return (unsigned int)m_ordersPending.GetCount();}

	const OrderMap& GetOrdersActive() const{return m_ordersActive;}//Pending orders with no cancel sent and acknowledged
	unsigned int GetOrdersActiveCount() const{return (unsigned int)m_ordersActive.GetCount();}

	void MakeOrderGtc(Order* order, bool gtc);

	const OrderMap& GetGtcOrders() const{return m_gtcOrders;}//Pending GTC orders
	unsigned int GetGtcOrdersCount() const{return (unsigned int)m_gtcOrders.GetCount();}

	bool HasPendingNonProblematicOrders() const{return GetOrdersPendingCount() > GetOrdersWithCancelProblemCount();}
	bool HasActiveNonProblematicOrders(const bool& exceptGtc, const bool& includeAlgos) const{return GetOrdersActiveCount() > GetOrdersWithCancelProblemCount() + (exceptGtc ? GetGtcOrdersCount() : 0) || includeAlgos && GetOrdersAlgorithmCount(exceptGtc);}

	const OrderMap& GetOrdersStuck() const{return m_ordersStuck;}
	unsigned int GetOrdersStuckCount() const{return (unsigned int)m_ordersStuck.GetCount();}
	unsigned int GetOrdersBlockedCount() const{return (unsigned int)m_ordersBlocked.GetCount();}
	const OrderMap& GetOrdersCancelRejected() const{return m_ordersCancelRejected;}
	unsigned int GetOrdersCancelRejectedCount() const{return (unsigned int)m_ordersCancelRejected.GetCount();}
	const OrderMap& GetOrdersCancelBlocked() const{return m_ordersCancelBlocked;}
	unsigned int GetOrdersCancelBlockedCount() const{return (unsigned int)m_ordersCancelBlocked.GetCount();}

	const OrderMap& GetOrdersWithCancelProblem() const{return m_ordersWithCancelProblem;}
	unsigned int GetOrdersWithCancelProblemCount() const{return (unsigned int)m_ordersWithCancelProblem.GetCount();}

	const Order* FindOrderByClientId(const unsigned int& clientId) const{const OrderMap::CPair* found = m_allOrders.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderUnacknowledged(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersUnacknowledged.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderAcknowledged(const unsigned int& serverId) const{const OrderMap::CPair* found = m_ordersAcknowledged.PLookup(serverId); return found ? found->value : NULL;}
	const Order* FindOrderRejected(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersRejected.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderBlocked(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersBlocked.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderAlgorithm(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersAlgorithm.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindGtcOrderAlgorithm(const unsigned int& clientId) const{const OrderMap::CPair* found = m_gtcOrdersAlgorithm.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderPending(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersPending.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindOrderActive(const unsigned int& clientId) const{const OrderMap::CPair* found = m_ordersActive.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindGtcOrder(const unsigned int& clientId) const{const OrderMap::CPair* found = m_gtcOrders.PLookup(clientId); return found ? found->value : NULL;}
	const Order* FindDummyOrder(const unsigned int& serverId) const{const OrderMap::CPair* found = m_dummyOrders.PLookup(serverId); return found ? found->value : NULL;}

	Order* FindOrderByClientId(const unsigned int& clientId){const OrderMap::CPair* found = m_allOrders.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderUnacknowledged(const unsigned int& clientId){const OrderMap::CPair* found = m_ordersUnacknowledged.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderAcknowledged(const unsigned int& serverId){const OrderMap::CPair* found = m_ordersAcknowledged.PLookup(serverId); return found ? found->value : NULL;}
	Order* FindOrderRejected(const unsigned int& clientId){const OrderMap::CPair* found = m_ordersRejected.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderBlocked(const unsigned int& clientId){const OrderMap::CPair* found = m_ordersBlocked.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderAlgorithm(const unsigned int& clientId){const OrderMap::CPair* found = m_ordersAlgorithm.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindGtcOrderAlgorithm(const unsigned int& clientId){const OrderMap::CPair* found = m_gtcOrdersAlgorithm.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderPending(const unsigned int& clientId){const OrderMap::CPair* found = m_ordersPending.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindOrderActive(const unsigned int& clientId){const OrderMap::CPair* found = m_ordersActive.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindGtcOrder(const unsigned int& clientId){OrderMap::CPair* found = m_gtcOrders.PLookup(clientId); return found ? found->value : NULL;}
	Order* FindDummyOrder(const unsigned int& serverId){const OrderMap::CPair* found = m_dummyOrders.PLookup(serverId); return found ? found->value : NULL;}

	unsigned int CalculateOrderSizeByClosePositionPercent(const Security* const security,
		const bool buy,
		const bool inventoryView,
		const unsigned int absPositionSize,
		const unsigned int closePositionSize,
		const unsigned int openPositionSize,
		const Position** position//if not NULL, found position is placed here
		) const;

	void SetPhantomPosition(const unsigned __int64& rootSymbol,//const char* symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& underlierSymbol,
		const unsigned __int64& optionBlock,
		const unsigned short optionType,
#endif
		const char phantom,
		bool onlyIfNoPhantom = false);
	void BuyPhantom(const unsigned __int64& rootSymbol//const char* symbol
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& underlierSymbol
		,const unsigned __int64& optionBlock
		,const unsigned short optionType
#endif
		);
	void SellPhantom(const unsigned __int64& rootSymbol//const char* symbol
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& underlierSymbol
		,const unsigned __int64& optionBlock
		,const unsigned short optionType
#endif
		);
	void FlipPhantomPosition(const unsigned __int64& rootSymbol//const char* symbol
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& underlierSymbol
		,const unsigned __int64& optionBlock
		,const unsigned short optionType
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

	unsigned int GetBlockedOrderCount() const{return (unsigned int)m_ordersBlocked.GetCount();}

	bool HasCanceledOrRejectedOrders() const
	{
		unsigned char i = TU_ORDER_STATUS_CANCELED * TU_ORDER_SIDE_COUNT;
		unsigned char end = i + TU_ORDER_SIDE_COUNT;
		for(; i < end; ++i)
		{
			if(!m_orders[i].IsEmpty())return true;
		}
		i = TU_ORDER_STATUS_REJECTED * TU_ORDER_SIDE_COUNT;
		end = i + TU_ORDER_SIDE_COUNT;
		for(; i < end; ++i)
		{
			if(!m_orders[i].IsEmpty())return true;
		}
		return false;
	}

	const OrderChronologicalMap& GetChronologicalPendingOrders(OrderSide orderSide) const{return m_chronologicalPendingOrders[orderSide];}
	OrderChronologicalMap& GetChronologicalPendingOrders(OrderSide orderSide){return m_chronologicalPendingOrders[orderSide];}

	const OrderMap& GetOrders(OrderStatus orderStatus, OrderSide orderSide) const{return m_orders[orderStatus * TU_ORDER_SIDE_COUNT + orderSide];}
	OrderMap& GetOrders(OrderStatus orderStatus, OrderSide orderSide){return m_orders[orderStatus * TU_ORDER_SIDE_COUNT + orderSide];}
//	TakionIterator* CreateOrderIterator(OrderStatus orderStatus, OrderSide orderSide) const;
	TakionIterator* CreateOrderIterator(unsigned int orderStatusMask, unsigned int orderSideMask) const;
	void AddMaskToOrderIterator(TakionIterator* iterator, unsigned int orderStatusMask, unsigned int orderSideMask) const;

	const ExecutionRefMap& GetExecutionRefMap() const{return m_executionRefMap;}
	const Execution* FindExecutionByRefId(const ExecutionIdAsNumberArray& id) const
	{
		const Execution* execution;
		const ExecutionRefMap::CPair* found;
		LockInquiryWait();
		found = m_executionRefMap.PLookup(id);
		execution = found ? found->value : NULL;
		UnlockInquiry();
		return execution;
	}
	const Execution* FindExecutionByRefId(const char* refId) const{return FindExecutionByRefId(ExecutionIdAsNumberArray(refId));}
	const Execution* FindExecutionByRefId(const std::string& refId) const{return FindExecutionByRefId(ExecutionIdAsNumberArray(refId));}
	bool ExecutionExists(const ExecutionIdAsNumberArray& id) const
	{
		bool exists;
		LockInquiryWait();
		exists = m_executionRefMap.PLookup(id) != NULL;
		UnlockInquiry();
		return exists;
	}
	bool ExecutionExists(const char* refId) const{return ExecutionExists(ExecutionIdAsNumberArray(refId));}
	bool ExecutionExists(const std::string& refId) const{return ExecutionExists(ExecutionIdAsNumberArray(refId));}

	const ExecutionRefMap& GetBustedExecutionRefMap() const{return m_bustedExecutionRefMap;}
	const Execution* FindBustedExecutionByRefId(const ExecutionIdAsNumberArray& id) const
	{
		const Execution* execution;
		const ExecutionRefMap::CPair* found;
		LockInquiryWait();
		found = m_bustedExecutionRefMap.PLookup(id);
		execution = found ? found->value : NULL;
		UnlockInquiry();
		return execution;
	}
	const Execution* FindBustedExecutionByRefId(const char* refId) const{return FindBustedExecutionByRefId(ExecutionIdAsNumberArray(refId));}
	const Execution* FindBustedExecutionByRefId(const std::string& refId) const{return FindBustedExecutionByRefId(ExecutionIdAsNumberArray(refId));}
	bool BustedExecutionExists(const ExecutionIdAsNumberArray& id) const
	{
		bool exists;
		LockInquiryWait();
		exists = m_bustedExecutionRefMap.PLookup(id) != NULL;
		UnlockInquiry();
		return exists;
	}
	bool BustedExecutionExists(const char* refId) const{return BustedExecutionExists(ExecutionIdAsNumberArray(refId));}
	bool BustedExecutionExists(const std::string& refId) const{return BustedExecutionExists(ExecutionIdAsNumberArray(refId));}

	const ExecutionMap& GetExecutions(OrderSide orderSide) const{return m_executions[orderSide];}
	ExecutionMap& GetExecutions(OrderSide orderSide){return m_executions[orderSide];}
	TakionIterator* CreateExecutionIterator(unsigned int orderSideMask) const;
	void AddMaskToExecutionIterator(TakionIterator* iterator, unsigned int orderSideMask) const;

	const ExecutionChronologicalSet& GetChronologicalExecutions() const{return m_chronologicalExecutions;}
	ExecutionChronologicalSet& GetChronologicalExecutions(){return m_chronologicalExecutions;}

	Execution* FindExecution(unsigned int id, OrderSide orderSide);

#ifndef TAKION_NO_OPTIONS
	Position* FindOptionPositionWithLock(const OptionSymbolBlockKey& key) const
	{
		LockInquiryWait();
		Position* position = FindOptionPosition(key);
		UnlockInquiry();
		return position;
	}
	Position* FindOptionPositionWithLock(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return FindOptionPositionWithLock(OptionSymbolBlockKey(rootSymbol, optionBlock));
	}
	Position* FindPositionWithLock(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return optionBlock ? FindOptionPositionWithLock(OptionSymbolBlockKey(rootSymbol, optionBlock)) : FindStockPositionWithLock(rootSymbol);
	}

	Position* FindOptionActivePositionWithLock(const OptionSymbolBlockKey& key) const
	{
		LockInquiryWait();
		Position* position = FindOptionActivePosition(key);
		UnlockInquiry();
		return position;
	}
	Position* FindOptionActivePositionWithLock(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return FindOptionActivePositionWithLock(OptionSymbolBlockKey(rootSymbol, optionBlock));
	}
	Position* FindActivePositionWithLock(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock) const
	{
		return optionBlock ? FindOptionActivePositionWithLock(OptionSymbolBlockKey(rootSymbol, optionBlock)) : FindStockActivePositionWithLock(rootSymbol);
	}

	Money GetOptionBuyingPowerUsed() const{return m_optionBuyingPowerUsed;}
	Money GetOptionBuyingPowerAvailable() const{return m_optionBuyingPowerAvailable;}
	Money GetMaxOptionBpUsed() const{return m_maxOptionBpUsed;}
	unsigned int GetOptionContractsTraded() const{return m_optionContractsTraded;}
	unsigned int GetOptionSharesTraded() const{return m_optionSharesTraded;}
	unsigned int GetStockSharesTraded() const{return m_stockSharesTraded;}

//	const unsigned int& GetOptionSharesAdded() const{return m_optionSharesAdded;}
//	const unsigned int& GetOptionSharesRemoved() const{return m_optionSharesRemoved;}
/*
	const unsigned int& GetOptionPotentialLongSize() const{return m_optionPotentialLongSize;}//in contracts
	const unsigned int& GetOptionPotentialShortSize() const{return m_optionPotentialShortSize;}//in contracts
	const unsigned int& GetOptionPotentialSize() const{return m_optionPotentialSize;}//in contracts
*/
	Money GetUnderlierValueLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetUnderlierValueLong() : m_underlierValueLong;}
	Money GetUnderlierValueShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetUnderlierValueShort() : m_underlierValueShort;}

	const unsigned int& GetOptionPotentialLongSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionPotentialLongSize() : m_optionPotentialLongSize;}
	const unsigned int& GetOptionPotentialShortSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionPotentialShortSize() : m_optionPotentialShortSize;}
	const unsigned int& GetOptionPotentialSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionPotentialSize() : m_optionPotentialSize;}

	const unsigned int& GetOptionVenue() const{return m_optionVenue;}
//LockInquiryWait/UnlockInquiry if called outside of the Account thread
	unsigned int GetOptionPositionInventoryCount() const{return m_inventory ? m_inventory->GetOptionPositionInventoryCount() : 0;}
	unsigned int GetPositionInventoryCount() const{return m_inventory ? m_inventory->GetPositionInventoryCount() : 0;}
	unsigned int GetOptionPositionHiddenCount() const{return m_inventory ? m_inventory->GetOptionPositionHiddenCount() : 0;}
	unsigned int GetPositionHiddenCount() const{return m_inventory ? m_inventory->GetPositionHiddenCount() : 0;}

	unsigned int GetOptionPositionCountLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionPositionCountLong() : GetOptionPositionCountLong();}
	unsigned int GetOptionPositionCountShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionPositionCountShort() : GetOptionPositionCountShort();}
	unsigned int GetOptionPositionCountInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionPositionCount() : GetOptionPositionCount();}
	unsigned int GetOptionActivePositionCountInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionActivePositionCount() : GetOptionActivePositionCount();}

////
	Money GetOptionInvestmentInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionInvestment() : m_optionInvestment;}
	Money GetOptionInvestmentLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionInvestmentLong() : m_optionInvestmentLong;}
	Money GetOptionInvestmentShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionInvestmentShort() : m_optionInvestmentShort;}
	const Money& GetMaxOptionInvestmentLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxOptionInvestmentLong() : m_maxOptionInvestmentLong;}
	const Money& GetMaxOptionInvestmentShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxOptionInvestmentShort() : m_maxOptionInvestmentShort;}
	const Money& GetMaxOptionInvestmentInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxOptionInvestment() : m_maxOptionInvestment;}

	const OptionPositionMap& GetOptionPositionsAllInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionPositionsAll() : GetOptionPositionsAll();}

	unsigned int GetAllOptionPositionCountInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAllOptionPositionCount() : GetAllOptionPositionCount();}
	unsigned int GetAllPositionCountInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAllPositionCount() : GetAllPositionCount();}

	const OptionPositionMap& GetOptionPositionsInv(PositionStatus positionStatus, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionPositions(positionStatus) : GetOptionPositions(positionStatus);}
	const OptionPositionMap& GetOptionActivePositionsInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOptionActivePositions() : GetOptionActivePositions();}

	OptionPositionMap& GetOptionPositionsInv(PositionStatus positionStatus, const bool& inventoryView){return inventoryView && m_inventory ? m_inventory->GetOptionPositions(positionStatus) : GetOptionPositions(positionStatus);}
	TakionIterator* CreateOptionPositionIteratorInv(unsigned int positionStatusMask, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->CreateOptionPositionIterator(positionStatusMask) : CreateOptionPositionIterator(positionStatusMask);}
	void AddMaskToOptionPositionIteratorInv(TakionIterator* iterator, unsigned int positionStatusMask, const bool& inventoryView) const{if(inventoryView && m_inventory)m_inventory->AddMaskToOptionPositionIterator(iterator, positionStatusMask); else AddMaskToOptionPositionIterator(iterator, positionStatusMask);}

	Position* FindOptionPositionInv(const OptionSymbolBlockKey& key, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindOptionPosition(key) : FindOptionPosition(key);}
	Position* FindOptionPositionInv(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindOptionPosition(rootSymbol, optionBlock) : FindOptionPosition(rootSymbol, optionBlock);}
	Position* FindPositionInv(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindPosition(rootSymbol, optionBlock) : FindPosition(rootSymbol, optionBlock);}

	Position* FindOptionActivePositionInv(const OptionSymbolBlockKey& key, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindOptionActivePosition(key) : FindOptionActivePosition(key);}
	Position* FindOptionActivePositionInv(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindOptionActivePosition(rootSymbol, optionBlock) : FindOptionActivePosition(rootSymbol, optionBlock);}
	Position* FindActivePositionInv(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindActivePosition(rootSymbol, optionBlock) : FindActivePosition(rootSymbol, optionBlock);}
////
#endif
	Position* FindPositionWithLock(const Security* security) const
	{
		Position* position;
		LockInquiryWait();
		position = FindPosition(security);
		UnlockInquiry();
		return position;
	}

//	Position* FindStockPosition(const unsigned __int64& symbol) const{const PositionMap::CPair* positionPair = m_stockPositionsAll.PLookup(symbol); return positionPair ? positionPair->value : NULL;}
	Position* FindStockPositionWithLock(const unsigned __int64& symbol) const
	{
		LockInquiryWait();
		Position* position = FindStockPosition(symbol);
		UnlockInquiry();
		return position;
	}

	Position* FindActivePositionWithLock(const Security* security) const
	{
		Position* position;
		LockInquiryWait();
		position = FindActivePosition(security);
		UnlockInquiry();
		return position;
	}

	Position* FindStockActivePositionWithLock(const unsigned __int64& symbol) const
	{
		LockInquiryWait();
		Position* position = FindStockActivePosition(symbol);
		UnlockInquiry();
		return position;
	}
/*
	const Money& GetPotentialLongValue() const{return m_potentialLongValue;}
	const Money& GetPotentialShortValue() const{return m_potentialShortValue;}

	const Money& GetPotentialLongNightValue() const{return m_potentialLongNightValue;}
	const Money& GetPotentialShortNightValue() const{return m_potentialShortNightValue;}
*/
	Money GetMaxBpUsed() const{return m_maxBpUsed;}
	Money GetMaxMeUsed() const{return m_maxMeUsed;}
	Money GetMaxBpBetaUsed() const{return m_maxBpBetaUsed;}

	virtual Money GetNightBuyingPowerUsed() const{return Money::moneyZero;}

	virtual Money GetBuyingPowerUsed() const{return Money::moneyZero;}
	virtual Money GetBuyingPowerAvailable() const{return Money::moneyZero;}

	virtual Money GetMarginExcessUsed() const{return Money::moneyZero;}
	virtual Money GetMarginExcessAvailable() const{return Money::moneyZero;}

	virtual Money GetBuyingPowerBetaUsed() const{return Money::moneyZero;}

//	virtual Money GetEstimatedBeginningEquity() const override{return m_estimatedBeginningEquity;}

	virtual Money GetHardBuyingPowerAvailable() const{return Money::moneyZero;}
	virtual Money GetHardMarginExcessAvailable() const{return Money::moneyZero;}

	virtual Money GetOpenPnlForLoss() const{return m_openPnlAction;}
	__int64 GetOpenPnlForLossDollars() const{return GetOpenPnlForLoss().GetDollars();}
	__int64 GetClosedPnlDollars() const{return GetClosedPnl().GetDollars();}
	__int64 GetMarkedPnlForLossDollars() const{return GetOpenPnlForLossDollars() + GetClosedPnlDollars();}

	virtual Money GetHardBpUsed() const{return Money::moneyZero;}//can be different from m_investment if a retail account has overnight position.
	virtual Money GetHardMeUsed() const{return Money::moneyZero;}//can be different from m_investment if a retail account has overnight position.

	Money GetPendingBuyInvestment() const{return m_pendingBuyInvestment;}
	Money GetPendingSellInvestment() const{return m_pendingSellInvestment;}

	Money GetPendingMeBuyInvestment() const{return m_pendingMeBuyInvestment;}
	Money GetPendingMeSellInvestment() const{return m_pendingMeSellInvestment;}

	Money GetPendingBetaBuyInvestment() const{return m_pendingBetaBuyInvestment;}
	Money GetPendingBetaSellInvestment() const{return m_pendingBetaSellInvestment;}

	const unsigned int GetBuyExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_BUY].GetCount();}
	const unsigned int GetSellExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_SELL].GetCount();}
	const unsigned int GetShortExecutionCount() const{return (unsigned int)m_executions[TU_ORDER_SIDE_SHORT].GetCount();}

	const unsigned int& GetSharesTraded() const{return m_sharesTraded;}
	const unsigned int& GetSharesAdded() const{return m_sharesAdded;}
	const unsigned int& GetSharesRemoved() const{return m_sharesRemoved;}
	const unsigned int& GetPendingBuyShares() const{return m_pendingBuyShares;}
	const unsigned int& GetPendingSellShares() const{return m_pendingSellShares;}

	const unsigned int& GetPotentialLongSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongSize() : m_potentialLongSize;}
	const unsigned int& GetPotentialShortSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortSize() : m_potentialShortSize;}
	const unsigned int& GetPotentialSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialSize() : m_potentialSize;}

	const unsigned int& GetPotentialLongNightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongNightSize() : m_potentialLongNightSize;}
	const unsigned int& GetPotentialShortNightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortNightSize() : m_potentialShortNightSize;}
	const unsigned int& GetPotentialNightSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialNightSize() : m_potentialNightSize;}

	const Money& GetPotentialLongValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongValue() : m_potentialLongValue;}
	const Money& GetPotentialShortValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortValue() : m_potentialShortValue;}
	const Money& GetPotentialLongMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongMe() : m_potentialLongMe;}
	const Money& GetPotentialShortMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortMe() : m_potentialShortMe;}
	const Money& GetPotentialBetaLongValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialBetaLongValue() : m_potentialBetaLongValue;}
	const Money& GetPotentialBetaShortValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialBetaShortValue() : m_potentialBetaShortValue;}
	const Money& GetPotentialLongNightValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialLongNightValue() : m_potentialLongNightValue;}
	const Money& GetPotentialShortNightValueInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetPotentialShortNightValue() : m_potentialShortNightValue;}

	Money GetClosedPnlInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnl() : m_closedPnl;}
	Money GetClosedPnlCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlCost() : m_closedPnlCost;}

	Money GetOpenPnlLevel1CostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlLevel1Cost() : m_openPnlLevel1Cost;}
	Money GetOpenPnlPrintCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlPrintCost() : m_openPnlPrintCost;}
	Money GetOpenPnlLevel1Inv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlLevel1() : m_openPnlLevel1;}
	Money GetOpenPnlPrintInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlPrint() : m_openPnlPrint;}
	Money GetOpenPnlImbExNearInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlImbExNear() : m_openPnlImbExNear;}
	Money GetOpenPnlTCloseInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlTClose() : m_openPnlTClose;}
	Money GetOpenPnlActionPrintInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlActionPrint() : m_openPnlActionPrint;}
	Money GetOpenPnlActionInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlAction() : m_openPnlAction;}
	Money GetOpenPnlNbboPrintInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrint() : m_openPnlNbboPrint;}
	const Money& GetOpenPnlNbboPrintHiInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintHi() : m_openPnlNbboPrintHi;}
	const Money& GetOpenPnlNbboPrintLoInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintLo() : m_openPnlNbboPrintLo;}
	Money GetMarkedPnlNbboPrintInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrint() : m_markedPnlNbboPrint;}
	const Money& GetMarkedPnlNbboPrintHiInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintHi() : m_markedPnlNbboPrintHi;}
	const Money& GetMarkedPnlNbboPrintLoInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintLo() : m_markedPnlNbboPrintLo;}
	Money GetClosedPnlNetInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlNet() : m_closedPnlNet;}
	Money GetOpenCommissionFeeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenCommissionFee() : m_openCommissionFee;}

	Money GetRTEquityInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetRTEquity() : m_rtEquity;}
	Money GetLeverageInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetLeverage() : m_leverage;}

	Money GetOpenPnlNbboPrintPreMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintPreMarket() : m_openPnlNbboPrintPreMarket;}
	Money GetOpenPnlNbboPrintMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintMarket() : m_openPnlNbboPrintMarket;}
	Money GetOpenPnlNbboPrintPostMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOpenPnlNbboPrintPostMarket() : m_openPnlNbboPrintPostMarket;}

	Money GetClosedPnlPreMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlPreMarket() : m_closedPnlPreMarket;}
	Money GetClosedPnlMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlMarket() : m_closedPnlMarket;}
	Money GetClosedPnlPostMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetClosedPnlPostMarket() : m_closedPnlPostMarket;}

	Money GetMarkedPnlNbboPrintPreMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintPreMarket() : m_markedPnlNbboPrintPreMarket;}
	Money GetMarkedPnlNbboPrintMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintMarket() : m_markedPnlNbboPrintMarket;}
	Money GetMarkedPnlNbboPrintPostMarketInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMarkedPnlNbboPrintPostMarket() : m_markedPnlNbboPrintPostMarket;}

	unsigned int GetStockPositionCountLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetStockPositionCountLong() : GetStockPositionCountLong();}
	unsigned int GetStockPositionCountShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetStockPositionCountShort() : GetStockPositionCountShort();}
	unsigned int GetStockPositionCountInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetStockPositionCount() : GetStockPositionCount();}
	unsigned int GetStockActivePositionCountInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetStockActivePositionCount() : GetStockActivePositionCount();}

///
	Position* FindStockPositionInv(const unsigned __int64& symbol, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindStockPosition(symbol) : FindStockPosition(symbol);}
	Position* FindPositionWithLockInv(const Security* security, const bool& inventoryView) const
	{
		Position* position;
		LockInquiryWait();
		position = FindPositionInv(security, inventoryView);
		UnlockInquiry();
		return position;
	}

	Position* FindStockPositionWithLockInv(const unsigned __int64& symbol, const bool& inventoryView) const
	{
		LockInquiryWait();
		Position* position = FindStockPositionInv(symbol, inventoryView);
		UnlockInquiry();
		return position;
	}


	Position* FindStockActivePositionInv(const unsigned __int64& symbol, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindStockActivePosition(symbol) : FindStockActivePosition(symbol);}
	Position* FindActivePositionWithLockInv(const Security* security, const bool& inventoryView) const
	{
		Position* position;
		LockInquiryWait();
		position = FindActivePositionInv(security, inventoryView);
		UnlockInquiry();
		return position;
	}

	Position* FindStockActivePositionWithLockInv(const unsigned __int64& symbol, const bool& inventoryView) const
	{
		LockInquiryWait();
		Position* position = FindStockActivePositionInv(symbol, inventoryView);
		UnlockInquiry();
		return position;
	}

	const PositionMap& GetStockPositionsAllInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetStockPositionsAll() : GetStockPositionsAll();}
	PositionMap& GetStockPositionsAllInv(const bool& inventoryView){return inventoryView && m_inventory ? m_inventory->GetStockPositionsAll() : GetStockPositionsAll();}
	unsigned int GetAllStockPositionCountInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAllStockPositionCount() : GetAllStockPositionCount();}

	const PositionMap& GetStockPositionsInv(PositionStatus positionStatus, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetStockPositions(positionStatus) : GetStockPositions(positionStatus);}
	const PositionMap& GetStockActivePositionsInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetStockActivePositions() : GetStockActivePositions();}
//	unsigned int GetStockActivePositionCountInv() const{return (unsigned int)m_stockActivePositions.GetCount();}

	PositionMap& GetStockPositionsInv(PositionStatus positionStatus, const bool& inventoryView){return inventoryView && m_inventory ? m_inventory->GetStockPositions(positionStatus) : GetStockPositions(positionStatus);}
	TakionIterator* CreatePositionIteratorInv(unsigned int positionStatusMask, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->CreatePositionIterator(positionStatusMask) : CreatePositionIterator(positionStatusMask);}
	void AddMaskToPositionIteratorInv(TakionIterator* iterator, unsigned int positionStatusMask, const bool& inventoryView) const{if(inventoryView && m_inventory)m_inventory->AddMaskToPositionIterator(iterator, positionStatusMask); else AddMaskToPositionIterator(iterator, positionStatusMask);}
	
	Position* FindPositionInv(const Security* security, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindPosition(security) : FindPosition(security);}
	Position* FindActivePositionInv(const Security* security, const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->FindActivePosition(security) : FindActivePosition(security);}

	const Money& GetTicketAverage() const{return m_ticketAverage;}
	const Money& GetMarkedTicketAverage() const{return m_markedTicketAverage;}
	const Money& GetMarkedTicketAverageHi() const{return m_markedTicketAverageHi;}
	const Money& GetMarkedTicketAverageLo() const{return m_markedTicketAverageLo;}

	Money GetBorrowInvestment() const{return m_borrowInvestment;}
	const Money& GetPendingBuyBorrowInvestment() const{return m_pendingBuyBorrowInvestment;}
	const unsigned int& GetPendingBuyBorrowShares() const{return m_pendingBuyBorrowShares;}
	const unsigned int& GetPendingSellBorrowShares() const{return m_pendingSellBorrowShares;}
	const unsigned int& GetBorrowSize() const{return m_borrowSize;}

	const unsigned int& GetOvernightLongSize() const{return m_overnightLongSize;}
	const unsigned int& GetOvernightShortSize() const{return m_overnightShortSize;}

	const unsigned int& GetUnclosedOvernightLongSize() const{return m_unclosedOvernightLongSize;}
	const unsigned int& GetUnclosedOvernightShortSize() const{return m_unclosedOvernightShortSize;}

	const unsigned int& GetLoadedLongSize() const{return m_loadedLongSize;}
	const unsigned int& GetLoadedShortSize() const{return m_loadedShortSize;}
	const unsigned int& GetLoadedSize() const{return m_loadedSize;}
	Money GetOvernightLongInvestment() const{return m_overnightLongInvestment;}
	Money GetOvernightShortInvestment() const{return m_overnightShortInvestment;}

	virtual unsigned char CancelOrder(Order* order){return CE_OK;}
	void CollectOrders(OrderReplaceSet& orderSet,
		bool forCancel,
		bool eachPosition,
		unsigned char sideMask,
		unsigned char directionMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		OrderCancelPick orderCancelPick,
		unsigned int tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL) const;

	unsigned int CancelOrders(bool eachPosition,
		unsigned char sideMask,
		unsigned char directionMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		OrderCancelPick orderCancelPick,
		unsigned int tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL);

	virtual unsigned int ReplaceOrders(const bool& eachPosition,
		const bool& replaceNative,
		const unsigned char& sideMask,
		const unsigned char& directionMask,
#ifndef TAKION_NO_OPTIONS
		const unsigned char& instrumentMask,
#endif
		const OrderCancelPick& orderCancelPick,
		const unsigned int& tifMask,
		const unsigned char& algoMask,
		const unsigned char& pqOpenMask,
		const unsigned char& tCloseMask,
		const bool& destinationExclude,
		const UIntSet* const& destinationSet,
		const bool& mnemonicExclude,
		const UIntSet* const& mnemonicSet,
		const SignedPrice& replacePriceOffset,
		const bool& replacePriceOffsetPercent,
		const bool& replacePriceReverseForSell,
		const bool& marketOrder,
		const int& replaceSizeOffset,
		const bool& replaceSizeReverseForSell,
		const bool& preBorrow,
		const Price& preBorrowPrice,
		const unsigned __int64& userId,
		const unsigned char& displaySizeMode,//0 - size fraction, 1 - round lot, 2 - no change
		const unsigned int& displaySize,
		const unsigned int& displaySizeFraction,
		Order** const& oneOrder = NULL,//Output param; Provide a non-NULL ptr to get an Order* if there is only one order to replace (to be able to adjust the replacement in the UI)
		OrderReplaceSet* const& orderCollection = NULL//Output param; Provide a non-NULL ptr to get a collection of Orders instead of replacing them (to be able to adjust the replacement in the UI)
		) = 0;

	void CancelOpeningOrders();
	void CancelOpeningOrdersWorthValue(const Money& value, Money& accumulatedValue);
//Protected Values
	virtual const char* GetId() const{return NULL;}
	virtual const AccountId& GetAccountId() const = 0;
	virtual bool isSimulation() const{return false;}
	virtual bool isTradingAllowed() const{return false;}
	virtual bool CanTrade() const{return false;}
	virtual bool CanAutoTrade() const{return false;}
	virtual bool CanAutoCancelOrder(const Order* order) const{return CanAutoCancel();}//01/01/2020

	virtual Money GetCurrentMaxLoss() const{return Money::moneyZero;}
	virtual Money GetCurrentMaxLossClose() const{return Money::moneyZero;}
	virtual Money GetCurrentMaxPositionLoss() const{return Money::moneyZero;}
	virtual Money GetCurrentMaxPositionLossClose() const{return Money::moneyZero;}

	virtual Price GetSpoofingSmallPriceOffset() const{return Price::priceZero;}
	virtual Price GetSpoofingBigPriceOffset() const{return Price::priceZero;}
	virtual unsigned int GetSpoofingOrderCountRatio() const{return 0;}
	virtual unsigned int GetSpoofingOrderSizeRatio() const{return 0;}
	virtual Money GetCommissionPer1000Shares() const{return Money::moneyZero;}
	virtual Money GetMarginExcess() const{return Money::moneyZero;}
	virtual Money GetHardMarginExcess() const{return Money::moneyZero;}
	virtual Money GetBuyingPower() const{return Money::moneyZero;}
	virtual Money GetHardBuyingPower() const{return Money::moneyZero;}
	virtual Money GetDayMaxPosInvestment() const{return Money::moneyZero;}
	virtual Money GetNightMaxPosInvestment() const{return Money::moneyZero;}
	virtual Money GetMorningMaxPosInvestment() const{return Money::moneyZero;}
	virtual Money GetDayMaxLongInvestment() const{return Money::moneyZero;}
	virtual Money GetNightMaxLongInvestment() const{return Money::moneyZero;}
	virtual Money GetMorningMaxLongInvestment() const{return Money::moneyZero;}
	virtual Money GetDayMaxShortInvestment() const{return Money::moneyZero;}
	virtual Money GetNightMaxShortInvestment() const{return Money::moneyZero;}
	virtual Money GetMorningMaxShortInvestment() const{return Money::moneyZero;}
	virtual Money GetNightMaxInvestment() const{return Money::moneyZero;}
	virtual Money GetMorningMaxInvestment() const{return Money::moneyZero;}
	virtual Money GetMaxLoss() const{return Money::moneyZero;}
	virtual Money GetNightMaxLoss() const{return Money::moneyZero;}
	virtual Money GetMorningMaxLoss() const{return Money::moneyZero;}
	virtual Money GetMaxLossSlack() const{return Money::moneyZero;}
	virtual Money GetMaxLossClose() const{return Money::moneyZero;}
	virtual Money GetNightMaxLossClose() const{return Money::moneyZero;}
	virtual Money GetMorningMaxLossClose() const{return Money::moneyZero;}

	virtual Money GetMaxLoss90Percent() const{return Money::moneyZero;}
	virtual Money GetMaxLoss80Percent() const{return Money::moneyZero;}

	virtual Money GetMaxLossPerPosition() const{return Money::moneyZero;}
	virtual Money GetNightMaxLossPerPosition() const{return Money::moneyZero;}
	virtual Money GetMorningMaxLossPerPosition() const{return Money::moneyZero;}
	virtual Money GetMaxLossPerPositionSlack() const{return Money::moneyZero;}
	virtual Money GetMaxLossPerPositionClose() const{return Money::moneyZero;}
	virtual Money GetNightMaxLossPerPositionClose() const{return Money::moneyZero;}
	virtual Money GetMorningMaxLossPerPositionClose() const{return Money::moneyZero;}
	virtual Money GetMaxOpenLossPerPosition() const{return Money::moneyZero;}
	virtual Money GetMaxTradedMoney() const{return Money::moneyZero;}
	virtual Money GetMaxOrderValue() const{return Money::moneyZero;}
	virtual Price GetMinShortPrice() const{return Money::moneyZero;}
	virtual Price GetMinSharePrice() const{return Money::moneyZero;}
	virtual Price GetMaxSharePrice() const{return Money::moneyZero;}
	virtual unsigned int GetMaxSharesTotal() const{return 0;}
	virtual unsigned int GetMaxSharesTraded() const{return 0;}
	virtual unsigned int GetDayMaxPosShares() const{return 0;}
	virtual unsigned int GetNightMaxPosShares() const{return 0;}
	virtual unsigned int GetMorningMaxPosShares() const{return 0;}
	virtual unsigned int GetMaxPosPendingOrder() const{return 0;}
	virtual unsigned int GetMaxOpenPositions() const{return 0;}
	virtual unsigned int GetMaxOrderSize() const{return 0;}
#ifndef TAKION_NO_OPTIONS
	virtual Money GetOptionBuyingPower() const{return Money::moneyZero;}
	virtual unsigned int GetMaxOptionSharesTraded() const{return 0;}
	virtual unsigned int GetMaxOptionContractsOpen() const{return 0;}
	virtual unsigned int GetMaxOptionOrderSize() const{return 0;}
	virtual Money GetMaxOptionOrderValue() const{return Money::moneyZero;}
	virtual unsigned char GetOptionNaked() const{return 0;}
	virtual unsigned int GetMaxOptionOpenPositions() const{return 0;}
#endif
	virtual unsigned char GetIsoAllowed() const{return 0;}
	virtual unsigned char GetHtbTborrowOrdersAllowed() const{return 0;}
	virtual unsigned char GetConservativeOrderMarking() const{return 0;}
	virtual unsigned char GetLocalSideMarking() const{return 0;}
	virtual unsigned char GetPoolLocates() const{return 0;}
	virtual unsigned int GetAdvOrderCount() const{return 0;}
	virtual unsigned int GetAdvOrderSizePercent() const{return 0;}
	virtual unsigned int GetAdvBorder() const{return 0;}
	virtual unsigned int GetAdvForceHidden() const{return 0;}
	virtual unsigned int GetAdvForceHiddenClose() const{return 0;}
	virtual unsigned int GetAdvReject() const{return 0;}
	virtual unsigned int GetBlockAggrPricePercent() const{return 0;}
	virtual unsigned int GetTimeFrameVenues() const{return 0;}
	virtual unsigned int GetOrderTimeFrame() const{return 0;}
	virtual unsigned int GetTimeFrameOrderCount() const{return 0;}
	virtual unsigned int GetOrderSizeNbboVenues() const{return 0;}
	virtual unsigned int GetOrderSizeNbboMultiplier() const{return 0;}

/////
	virtual bool CanLoadExecutions() const{return !m_executionsLoaded && !m_loadExecutionRequestSent && !isSimulation() && isHistoryLoaded();}
	const bool& isExecutionsLoaded() const{return m_executionsLoaded;}
	virtual bool LoadExecutions() const{return false;}

	virtual bool CanLoadOrders() const{return !m_ordersLoaded && !m_loadOrderRequestSent && !isSimulation() && isHistoryLoaded();}
	const bool& isOrdersLoaded() const{return m_ordersLoaded;}
	virtual bool LoadOrders() const{return false;}

	const char& GetAccountType() const{return m_accountType;}
	const char& GetFirmType() const{return m_firmType;}

	const bool& isRetail() const{return m_retail;}
	const bool& isMarginExcessManaged() const{return m_marginExcessManaged;}
	const bool& isPortfolioManaged() const{return m_portfolioManaged;}

	const unsigned short& GetRecoveryErrorCode() const{return m_recoveryErrorCode;}
	bool isHistoryLoaded() const{return !m_recoveryErrorCode;}
	const bool& isHistoryLoadingStarted() const{return m_historyLoadingStarted;}
	void ResetRecoveryErrorCode(bool simulation){m_recoveryErrorCode = simulation ? 0 : 0xFFFF; m_historyLoadingStarted = false;}//history is not loaded

	void CalculateOrderImpact(char side,
		unsigned int quantity,
		int posSize,
		unsigned int absPosSize,//absPosSize in contracts for options
#ifndef TAKION_NO_OPTIONS
		unsigned int contractSize,
#endif
		const Price& orderPrice,
		const Money& additionalReplaceBp,
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
		Price& averageLongPrice,
		Price& averageShortPrice,
		unsigned int& posLongSize,
		unsigned int& posShortSize);

	static void CalculatePotentialPositionSize(char side, unsigned int quantity, int posSize, unsigned int absPosSize,
		unsigned int& pendingBuyShares,
		unsigned int& pendingSellShares,
		unsigned int& longSize,
		unsigned int& shortSize);

//	static unsigned int CalculateSizeToBorrow(char side, unsigned int quantity, int posSize, unsigned int absPosSize, unsigned int borrowAndUnclosedSize);

	void CollectOrdersInEachPosition(OrderReplaceSet& orderSet,
		bool forCancel,
		unsigned char sideMask,
		unsigned char directionMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		OrderCancelPick orderCancelPick,
		unsigned int tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL) const;
	unsigned int CancelOrdersInEachPosition(unsigned char sideMask,
		unsigned char directionMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		OrderCancelPick orderCancelPick,
		unsigned int tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL);
	
	void CollectAllOrdersInCategory(OrderReplaceSet& orderSet,
		bool forCancel,
		unsigned char sideMask,
		unsigned char directionMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		unsigned int tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL) const;

	unsigned int CancelAllOrdersInCategory(
		unsigned char sideMask,
		unsigned char directionMask,
#ifndef TAKION_NO_OPTIONS
		unsigned char instrumentMask,
#endif
		unsigned int tifMask,
		unsigned char algoMask,
		unsigned char pqOpenMask,
		unsigned char tCloseMask,
		bool destinationExclude = true,
		const UIntSet* destinationSet = NULL,
		bool mnemonicExclude = true,
		const UIntSet* mnemonicSet = NULL);

	unsigned int CancelAllAlgorithmsAndActiveOrders(bool exceptGtc);

	virtual unsigned char DoWriteCancelOrderToSocket(const Order* order){return CE_OK;}
	virtual unsigned char DoWriteMultipleCancelsToSocket(Position* position, OrderReplaceSet& orderSet, unsigned int* notCanceledClientId = NULL){return CE_OK;}
	virtual void WritePhantomMessageToAccountThread(const unsigned __int64& rootSymbol,//const char* symbol,
//		unsigned char securityType,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& underlierSymbol,
		const unsigned __int64& optionBlock,
		const unsigned short optionType,
#endif
		const char phantom,//(-1 <= phantom <= +1) - set value, -2 - sell, +2 - buy, +3 flip
		bool onlyIfNoPhantom = false){}
	virtual void WriteAllPhantomMessageToAccountThread(unsigned int code){}
	virtual void WriteMessageToAccountThread(const Message* message){}
	virtual void WriteBuffersToAccountThread(WSABUF* data, unsigned int count, unsigned int totalLength){}

	virtual void WriteSecurityUpdateMessageToAccountThread(unsigned int algoClientId){}
	virtual void WriteAlgorithmNotificationMessageToMainThread(unsigned int algoClientId, unsigned short code, unsigned short eventCode){}
	virtual void WriteAlgorithmNotifyMessageToAccountThread(unsigned int algoClientId, unsigned short code, unsigned short eventCode){}
	void WriteAllAlgoNotifyMessageToAccountThread(unsigned short code, unsigned short eventCode, unsigned int algoType = 0xFFFFFFFF);//lock for inquiry if not account thread
	void NotifyAllAlgosInThread(unsigned short code, unsigned short eventCode, unsigned int algoType);//Account thread
	void WriteAllAlgoNotifyMessageToAccountThread(unsigned short code, unsigned short eventCode, unsigned int algoTypeStart, unsigned int algoTypeEnd);//lock for inquiry if not account thread
	void NotifyAllAlgosInThread(unsigned short code, unsigned short eventCode, unsigned int algoTypeStart, unsigned int algoTypeEnd);//Account thread

//	virtual ActOnMaxLossMode GetActOnMaxLossMode() const{return MLM_NONE;}
	const bool& isCancelOrdersInitiated() const{return m_cancelOrdersInitiated;}
	const bool& isClosePositionsInitiated() const{return m_closePositionsInitiated;}

//	const unsigned char& GetItgAccount() const{return m_itgAccount;}
	const bool& isConstraintsInitialized() const{return m_constraintsInitialized;}

	const unsigned char& GetSecurityTypeHidden() const{return m_securityTypeHidden;}//0 - none, 1 << ST_STOCK, 1 << ST_OPTION
	bool SetSecurityTypeHidden(unsigned char securityTypeHidden);

	const Price& GetBorrowPriceMultiplier() const{return m_borrowPriceMultiplier;}

	const unsigned int& GetExchangeEntitlements() const{return m_exchangeEntitlements;}
	virtual bool isEntitled(unsigned char primaryExchangeFlag) const{return (m_exchangeEntitlements & (1 << primaryExchangeFlag)) != 0;}

	const bool& isLoadingHistory() const{return m_loadingHistory;}
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

//When calling from main thread Use LockInquiry (LockInquiryWait) before calling the function, and UnlockInquiry after you are done using AccountInventory*
	const AccountInventory* GetInventory() const{return m_inventory;}
//Inventory Inquiry functions called from main thread must be surounded with LockInquiry (LockInquiryWait) / UnlockInquiry
	const unsigned int& GetInventoryLongSize() const{return m_inventory ? m_inventory->GetInventoryLongSize() : uintZero;}
	const unsigned int& GetInventoryShortSize() const{return m_inventory ? m_inventory->GetInventoryShortSize() : uintZero;}
	const unsigned int& GetInventorySize() const{return m_inventory ? m_inventory->GetInventorySize() : uintZero;}
	virtual const Money& GetInventoryInvestment() const override{return m_inventory ? m_inventory->GetInventoryInvestment() : Money::moneyZero;}
	virtual const Money& GetInventoryNbboPrintOpenPnl() const override{return m_inventory ? m_inventory->GetInventoryNbboPrintOpenPnl() : Money::moneyZero;}

//
	const bool& hasInventory() const{return !m_inventory ? boolFalse : boolTrue;}
	unsigned int GetStockPositionInventoryCount() const{return m_inventory ? m_inventory->GetStockPositionInventoryCount() : 0;}
	unsigned int GetStockPositionHiddenCount() const{return m_inventory ? m_inventory->GetStockPositionHiddenCount() : 0;}

	bool SetInventory(Position* position, int size, const Price& cost, bool inventoryFloating, bool leaveInLayout);
	bool SetInventory(int size, bool leaveInLayout);//for all positions

//When calling from main thread Use LockInquiry (LockInquiryWait) before calling the function, and UnlockInquiry after you are done using PositionInventory*
	const unsigned int& GetLongSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetLongSize() : m_longSize;}
	const unsigned int& GetShortSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetShortSize() : m_shortSize;}
	const unsigned int& GetAbsSizeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetAbsSize() : m_absSize;}
	Money GetInvestmentInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestment() : m_investment;}
	Money GetInvestmentMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentMe() : m_investmentMe;}
//	Money GetMaxInvestmentInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestment() : m_maxInvestment;}
	Money GetInvestmentBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentBeta() : m_investmentBeta;}
	Money GetInvestmentCostInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentCost() : m_investmentCost;}

	Money GetOvernightInvestmentInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightInvestment() : m_overnightInvestment;}
	Money GetOvernightInvestmentMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightInvestmentMe() : m_overnightInvestmentMe;}
	Money GetOvernightInvestmentBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetOvernightInvestmentBeta() : m_overnightInvestmentBeta;}

	Money GetInvestmentLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentLong() : m_investmentLong;}
	Money GetInvestmentMeLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentMeLong() : m_investmentMeLong;}
	Money GetInvestmentBetaLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentBetaLong() : m_investmentBetaLong;}
	Money GetInvestmentCostLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentCostLong() : m_investmentCostLong;}

	Money GetInvestmentShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentShort() : m_investmentShort;}
	Money GetInvestmentMeShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentMeShort() : m_investmentMeShort;}
	Money GetInvestmentBetaShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentBetaShort() : m_investmentBetaShort;}
	Money GetInvestmentCostShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetInvestmentCostShort() : m_investmentCostShort;}

	const Money& GetMaxInvestmentLongInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentLong() : m_maxInvestmentLong;}
	const Money& GetMaxInvestmentShortInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentShort() : m_maxInvestmentShort;}
	const Money& GetMaxInvestmentInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestment() : m_maxInvestment;}

	const Money& GetMaxInvestmentLongMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentLongMe() : m_maxInvestmentLongMe;}
	const Money& GetMaxInvestmentShortMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentShortMe() : m_maxInvestmentShortMe;}
	const Money& GetMaxInvestmentMeInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentMe() : m_maxInvestmentMe;}

	const Money& GetMaxInvestmentLongBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentLongBeta() : m_maxInvestmentLongBeta;}
	const Money& GetMaxInvestmentShortBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentShortBeta() : m_maxInvestmentShortBeta;}
	const Money& GetMaxInvestmentBetaInv(const bool& inventoryView) const{return inventoryView && m_inventory ? m_inventory->GetMaxInvestmentBeta() : m_maxInvestmentBeta;}

	bool DestroyUntradedPositions()
	{
		if(isInThread())return DoDestroyUntradedPositions();
		else return WriteDestroyUntradedPositionsToAccountThread();
	}

	bool DestroyUntradedPosition(Position* position)
	{
		if(isInThread())return DoDestroyUntradedPosition(position);
		else return WriteDestroyUntradedPositionToAccountThread(position->GetNumericSymbol()
#ifndef TAKION_NO_OPTIONS
			, position->GetOptionBlock()
#endif
			);
	}

	bool DestroyUntradedPosition(const unsigned __int64& symbol
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
#endif
		)
	{
		if(isInThread())
		{
			Position* position = 
#ifndef TAKION_NO_OPTIONS
				FindPosition(symbol, optionBlock);
#else
				FindStockPosition(symbol);
#endif
			return position && DoDestroyUntradedPosition(position);
		}
		else
		{
			return WriteDestroyUntradedPositionToAccountThread(symbol
#ifndef TAKION_NO_OPTIONS
				, optionBlock
#endif
				);
		}
	}
//
	typedef CMap<unsigned int, const unsigned int&, OrderSet, const OrderSet&> OcoMap;
	const unsigned int& GetCurrentOcoId() const{return m_currentOcoId;}
	const unsigned int& GetNextOcoId() const{return m_nextOcoId;}
	bool LockOcoInquiry() const{return m_ocoLock.LockInquiry();}
	void LockOcoInquiryWait() const{return m_ocoLock.LockInquiryWait();}
	void UnlockOcoInquiry() const{m_ocoLock.UnlockInquiry();}
	unsigned int GetOcoOrderCount(const unsigned int& id) const;
	bool GetOcoOrders(const unsigned int& id, OrderSet& orderSetCopy) const;
#if (_MSC_VER > 1600)
	typedef std::unordered_set<unsigned int> UIntHashSet;
#else
	typedef std::hash_set<unsigned int> UIntHashSet;
#endif
	bool AddOcoOrder(const unsigned int& ocoId, Order* order);
	bool AddOcoOrders(const unsigned int& ocoId, const OrderSet& orderSet);
	bool RemoveOcoOrder(Order* order, bool clearOcoFromOrder);
	bool RemoveOcoOrders(const unsigned int& ocoId, const OrderSet& orderSet, bool clearOcoFromOrder);
	bool ClearOcoOrders(const unsigned int& ocoId, bool clearOcoFromOrder)
	{
		if(!ocoId)return false;
		if(isInThread())return DoClearOcoOrders(ocoId, clearOcoFromOrder);
		else return WriteClearOcoOrdersToAccountThread(ocoId, clearOcoFromOrder);
	}
	bool ClearAllOcoOrders(bool clearOcoFromOrder)
	{
		if(isInThread())return DoClearAllOcoOrders(clearOcoFromOrder);
		else return WriteClearAllOcoOrdersToAccountThread(clearOcoFromOrder);
	}
	bool SetCurrentOcoId(const unsigned int& ocoId)
	{
		if(isInThread())return DoSetCurrentOcoId(ocoId);
		else return WriteSetCurrentOcoIdToAccountThread(ocoId);
	}
	bool ResetCurrentOcoId()
	{
		if(isInThread())return DoResetCurrentOcoId();
		else return WriteResetCurrentOcoIdToAccountThread();
	}
	const unsigned int& GetUpdatedPnlPositionCount() const{return m_updatedPnlPositionCount;}
	const unsigned int& GetLoadedPositionCount() const{return m_loadedPositionCount;}
	bool isPnlUpdated() const{return m_loadedPositionCount <= m_updatedPnlPositionCount;}
	bool isReadyToBeSupervised() const{return isHistoryLoaded() && isPnlUpdated();}

//	virtual unsigned char WriteBorrowOrderToSocket(const Security* security, unsigned int sizeToBorrow, Order** orderSent, const char* userOrderInfo){return OE_OK;}//from Account thread only

	virtual unsigned int GetThreadId() const{return m_threadId;}

	const bool& isLoadExecutionRequestSent() const{return m_loadExecutionRequestSent;}
	const bool& isLoadOrderRequestSent() const{return m_loadOrderRequestSent;}

	const bool& isCurrentAccount() const{return m_currentAccount;}

	void EnforceNiteBpConstraint();
protected:
	Account(const char* id, bool simulation);

#ifdef DELAY_POSITION_INIT_HASH_TABLES
	void InitPositionHashTable(Position* position){position->InitHashTables();}
#endif
	OrderMap& GetOrdersPendingMap(){return m_ordersPending;}//Unacknowledged and Acknowledged

	virtual bool isDestinationQsmtReplaceableInAccount(const Destination* destination, char primaryExchange) const
	{
		return true;
	}

	virtual void WriteUpdateMessageToMainThread(bool constraintsChanged){}

	void DoCancelStockOpeningOrders();

	void SetOrderFromExtension(Order* const& order, const bool& fromExtension)
	{
		order->m_fromExtension = fromExtension;
	}

	void SetMaxBpUsed(const Money& bpUsed){m_maxBpUsed = bpUsed;}
	void SetMaxMeUsed(const Money& meUsed){m_maxMeUsed = meUsed;}
	void SetMaxBpBetaUsed(const Money& bpBetaUsed){m_maxBpBetaUsed = bpBetaUsed;}

	void SetConditionallyMaxBpUsed(const Money& bpUsed){if(m_maxBpUsed < bpUsed)m_maxBpUsed = bpUsed;}
	void SetConditionallyMaxMeUsed(const Money& meUsed){if(m_maxMeUsed < meUsed)m_maxMeUsed = meUsed;}
	void SetConditionallyMaxBpBetaUsed(const Money& bpBetaUsed){if(m_maxBpBetaUsed < bpBetaUsed)m_maxBpBetaUsed = bpBetaUsed;}

	inline void SetOrderBeingCanceled(Order* const& order, const unsigned char& canceled){order->SetBeingCanceled(canceled);}
	inline void SetOrderDeleted(Order* const& order){order->SetDeleted();}
	inline void SetOrderCancelTime(Order* const& order){order->SetCancelTime();}
	inline void UnsetOrderCancelTime(Order* const& order){order->UnsetCancelTime();}

	void UpdateMarketDataEntitlements();//Called only from account thread

	void AddOrderValues(Order* order, const unsigned int quantity)
	{
		bool unlock = order->LockModification();
		order->AddOrderValues(quantity);
		if(unlock)order->UnlockModification();
	}

	void AdjustInventoryPosition(Position* position, const int& prevSize, const Price& prevPrice);

	void RemoveAndDestroyPosition(Position* position);
	virtual bool DestroyPositionOrders(const Position* position){return false;}

	virtual void AddPosition(Position* position)//called in the worker thread only. Account must be locked for modification before the call
	{
		AccountInventoryData::AddPosition(position);
		if(m_inventory)m_inventory->AddPosition(position);
	}

	virtual void RemovePosition(Position* position)//called in the worker thread only. Account must be locked for modification before the call
	{
		AccountInventoryData::RemovePosition(position);
		if(m_inventory)m_inventory->RemovePosition(position);
	}

	virtual void RemovePositionTemporarily(Position* position)//called in the worker thread only. Account must be locked for modification before the call
	{
		AccountInventoryData::RemovePositionTemporarily(position);
		if(m_inventory)m_inventory->RemovePositionTemporarily(position);
	}

	virtual void ReAddPosition(Position* position)//Add after RemovePositionTemporarily(Position* position); //called in the worker thread only. Account must be locked for modification before the call
	{
		AccountInventoryData::ReAddPosition(position);
		if(m_inventory)m_inventory->ReAddPosition(position);
	}

	virtual void AddActivePosition(Position* position)
	{
		AccountInventoryData::AddActivePosition(position);
		if(m_inventory)m_inventory->AddActivePosition(position);
	}

	virtual void RemoveActivePosition(Position* position)
	{
		AccountInventoryData::RemoveActivePosition(position);
		if(m_inventory)m_inventory->RemoveActivePosition(position);
	}
/*
	virtual void PlacePosition(Position* position, int prevSize, int currentSize)
	{
		AccountInventoryData::PlacePosition(position, prevSize, currentSize);
		if(m_inventory)m_inventory->PlacePosition(position, prevSize, currentSize);
	}
*/
	void AdjustInventory(Position* const& position, const PositionInventory& prevInventory)
	{
		if(m_inventory)m_inventory->AdjustInventory(position, prevInventory);
	}
	void AdjustInventoryPotentialValues(Position* const& position, const PositionInventory& prevInventory)
	{
		if(m_inventory)m_inventory->AdjustInventoryPotentialValues(position, prevInventory);
	}
	
	Money UpdatePositionLevel1OpenPnl(PositionInventoryData* const& position, const Price& level1Price, const bool& bid, Money& costDiff, Money& diffAction)
	{
		return position->UpdateLevel1OpenPnl(level1Price, bid, costDiff, diffAction);
	}
	Money UpdatePositionPrintOpenPnl(PositionInventoryData* const& position, const Price& printPrice, Money& costDiff)
	{
		return position->UpdatePrintOpenPnl(printPrice, costDiff);
	}
	Money UpdatePositionImbExNearOpenPnl(PositionInventoryData* const& position, const Price& nearPrice)
	{
		return position->UpdateImbExNearOpenPnl(nearPrice);
	}
	Money UpdatePositionNbboPrintOpenPnl(PositionInventoryData* const& position, const Price& printPrice, bool actionPrint, Money& diffActionPrint, Money& diffAction, Money& preMarketDiff, Money& marketDiff, Money& postMarketDiff, const unsigned char& marketState)
	{
		return position->UpdateNbboPrintOpenPnl(printPrice, actionPrint, diffActionPrint, diffAction, preMarketDiff, marketDiff, postMarketDiff, marketState);
	}
	Money UpdatePositionInventoryNbboPrintOpenPnl(PositionInventory* const& positionInventory, const Price& printPrice)
	{
		return positionInventory->UpdateInventoryNbboPrintOpenPnl(printPrice);
	}
	bool UpdatePositionPrintTrailingOrders(Position* const& position, const Price& printPrice, const Message* message)
	{
		return position->UpdatePrintTrailingOrders(printPrice, message);
	}
	bool UpdatePositionLevel1TrailingOrders(Position* const & position, const Price& bid, const Price& ask, const unsigned char& sideMask, const Message* message)
	{
		return position->UpdateLevel1TrailingOrders(bid, ask, sideMask, message);
	}
	Money UpdatePositionTCloseOpenPnl(PositionInventoryData* const& position, const Price& closePrice)
	{
		return position->UpdateTCloseOpenPnl(closePrice);
	}
	PositionInventory* GetPositionInventory(PositionData* const& position)
	{
		return position->m_inventory;// GetInventory();
	}
/*
	Money UpdateInventoryPositionLevel1OpenPnl(PositionInventoryData* position, const Price& level1Price, bool bid, Money& costDiff)
	{
		return position->UpdateLevel1OpenPnl(level1Price, bid, costDiff);
	}
*/
	virtual void UpdateMarkedPnlNbboPrint() override;//const unsigned char marketState) override;
	
//	virtual unsigned char WriteBorrowOrderToSocket(const Security* security, unsigned int sizeToBorrow, Order** orderSent, const char* userOrderInfo){}
	virtual void WriteInventoryToAccountThread(const PositionData* position, int size, const Price& cost, bool inventoryFloating, bool leaveInLayout){}
	virtual void WriteInventoryToMainThread(const PositionData* position, int size, const Price& cost, bool inventoryFloating, bool leaveInLayout){}
	virtual void WriteAllPositionInventoryToAccountThread(int size, bool leaveInLayout){}
	bool DoSetInventory(Position* position, int size, const Price& cost, bool inventoryFloating, bool leaveInLayout);
	bool DoRemoveInventory();
	bool DoSetHiddenAlways(Position* position, bool hiddenAlways);
//Moved to AccountInventoryData
//	void AddPosition(Position* position);//called in the worker thread only. Account must be locked for modification before the call

	virtual void DoSetPhantomPositionInThread(const unsigned __int64& rootSymbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& underlierSymbol,
		const unsigned __int64& optionBlock,
		const unsigned short optionType,
#endif
		const char phantom,
		bool onlyIfNoPhantom = false){}
	virtual void DoSetAllPhantomPositionsFlatInThread(){}
//	virtual void DoIncrementPhantomPositionInThread(const char* symbol, unsigned char securityType, bool decrement){}

//	char m_userName[16];
	AccountId m_userName;

//	char m_clearingAccountName[16];
	AccountId m_clearingAccountId;

	char m_firmId[8];
	unsigned int m_firmIdNum;

	char m_stockLoanFirmId[8];
	unsigned int m_stockLoanFirmIdNum;

	unsigned char m_clearingFirmOrdinal;
	unsigned char m_stockLoanFirmOrdinal;

	bool m_currentAccount;

#ifdef FIRM_VALUES
	AccountAggregator* m_accountAggregator;
	AccountAggregatorId m_accountAggregatorId;
	bool m_positionAggregation;
	bool m_borrowToCoverOvernightShortInitialized;
#endif

	unsigned int m_threadId;

	unsigned int m_exchangeEntitlements;

	Observable m_inThreadObservable;
	TakionLockSingleThreadAccess m_lockInThreadObservable;
/*
	volatile LONG m_lockPositionStorage;
	volatile LONG m_lockOrderStorage;
	volatile LONG m_lockExecutionStorage;
*/
	static void ClearAndDestroyOrders(OrderMap& orderMap);
	static void ClearAndDestroyOrders(OrderSet& orderSet);
	void ClearAndDestroyOrders();

	UInt64UInt64Map m_restrictedSymbolMap;
	TakionLock m_restrictedSymbolLock;
	bool m_restrictedSymbolMapLoaded;

	OrderMap m_allOrders;//key is clientId

	OrderMap m_ordersAcknowledged;
	OrderSet m_ordersFailedToAcknowledge;
	OrderMap m_ordersUnacknowledged;
	OrderMap m_ordersRejected;
	OrderMap m_ordersBlocked;

	OrderMap m_ordersPending;
	OrderMap m_ordersActive;//Pending orders with no cancel sent and acknowledged
	OrderMap m_gtcOrders;//Pending GTC orders

	OrderMap m_ordersStuck;
	OrderMap m_ordersCancelRejected;
	OrderMap m_ordersCancelBlocked;

	OrderMap m_ordersWithCancelProblem;

	OrderMap m_ordersAlgorithm;
	OrderMap m_gtcOrdersAlgorithm;

	OrderMap m_dummyOrders;

	OrderChronologicalMap m_chronologicalPendingOrders[TU_ORDER_SIDE_COUNT];

	OrderMap m_orders[TU_ORDER_STATUS_COUNT * TU_ORDER_SIDE_COUNT];

	static void ClearAndDestroyExecutions(ExecutionMap& executionMap);
	void ClearAndDestroyExecutions();
	ExecutionRefMap m_executionRefMap;
	ExecutionRefMap m_bustedExecutionRefMap;
	ExecutionMap m_executions[TU_ORDER_SIDE_COUNT];
	ExecutionChronologicalSet m_chronologicalExecutions;

	void ClearAndDestroyPositions();
/*
#ifndef TAKION_NO_OPTIONS
	OptionPositionMap m_optionPositionsAll;
	OptionPositionMap m_optionPositions[TU_POSITION_STATUS_COUNT];
	OptionPositionMap m_optionActivePositions;//non flat or flat with pending orders
#endif

	PositionMap m_stockPositionsAll;
	PositionMap m_stockPositions[TU_POSITION_STATUS_COUNT];
	PositionMap m_stockActivePositions;//non flat or flat with pending orders
*/
/*
	Money m_potentialLongValue;
	Money m_potentialShortValue;

	Money m_potentialLongNightValue;
	Money m_potentialShortNightValue;
*/
	Money m_maxBpUsed;
	Money m_maxMeUsed;
	Money m_maxBpBetaUsed;

#ifndef TAKION_NO_OPTIONS
	void SetMaxOptionInvestmentInv(const Money& pnl){if(m_inventory)m_inventory->SetMaxOptionInvestment(pnl);}
	void SetMaxOptionInvestmentLongInv(const Money& pnl){if(m_inventory)m_inventory->SetMaxOptionInvestmentLong(pnl);}
	void SetMaxOptionInvestmentShortInv(const Money& pnl){if(m_inventory)m_inventory->SetMaxOptionInvestmentShort(pnl);}

	void SetConditionallyMaxOptionInvestmentInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxOptionInvestment(investment);}
	void SetConditionallyMaxOptionInvestmentLongInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxOptionInvestmentLong(investment);}
	void SetConditionallyMaxOptionInvestmentShortInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxOptionInvestmentShort(investment);}

	Money m_optionBuyingPowerUsed;
	Money m_optionBuyingPowerAvailable;
	Money m_maxOptionBpUsed;
	unsigned int m_optionContractsTraded;
	unsigned int m_optionSharesTraded;
	unsigned int m_stockSharesTraded;
//	unsigned int m_optionSharesAdded;
//	unsigned int m_optionSharesRemoved;
/*
	unsigned int m_optionPotentialLongSize;//in contracts
	unsigned int m_optionPotentialShortSize;//in contracts
	unsigned int m_optionPotentialSize;//in contracts
*/
	unsigned int m_optionVenue;
#endif

	unsigned int m_locateVenue;
	unsigned int m_orderProcessingFlags;
	unsigned int m_accountProcessingFlags;
//	Money m_closedPnl;
//	Money m_closedPnlCost;
/*
	Money m_openPnlLevel1Cost;
	Money m_openPnlLevel1;
	Money m_openPnlPrint;
	Money m_openPnlTClose;
	Money m_openPnlNbboPrint;
	Money m_openPnlNbboPrintHi;
	Money m_openPnlNbboPrintLo;
	Money m_markedPnlNbboPrint;
	Money m_markedPnlNbboPrintHi;
	Money m_markedPnlNbboPrintLo;
*/
	unsigned int m_sharesTraded;
	unsigned int m_sharesAdded;
	unsigned int m_sharesRemoved;

	unsigned int m_pendingBuyShares;
	unsigned int m_pendingSellShares;
/*
	unsigned int m_potentialLongSize;
	unsigned int m_potentialShortSize;
	unsigned int m_potentialSize;

	unsigned int m_potentialLongNightSize;
	unsigned int m_potentialShortNightSize;
	unsigned int m_potentialNightSize;
*/
//	unsigned int m_longSize;
//	unsigned int m_shortSize;
//	unsigned int m_size;
	unsigned int m_pendingBuyBorrowShares;
	unsigned int m_pendingSellBorrowShares;
	unsigned int m_borrowSize;
	Money m_ticketAverage;
	Money m_markedTicketAverage;
	Money m_markedTicketAverageHi;
	Money m_markedTicketAverageLo;
//	Money m_closedPnlNet;
//	Money m_openCommissionFee;

//	Money m_investmentLong;
//	Money m_investmentShort;
//	Money m_investment;
//	Money m_investmentCost;
//	Money m_investmentCostLong;
//	Money m_investmentCostShort;
	Money m_pendingBuyInvestment;
	Money m_pendingSellInvestment;

	Money m_pendingMeBuyInvestment;
	Money m_pendingMeSellInvestment;

	Money m_pendingBetaBuyInvestment;
	Money m_pendingBetaSellInvestment;

	Money m_pendingBuyBorrowInvestment;
	Money m_borrowInvestment;

//	Money m_maxInvestmentLong;
//	Money m_maxInvestmentShort;
//	Money m_maxInvestment;

	unsigned int m_overnightLongSize;
	unsigned int m_overnightShortSize;
//	unsigned int m_overnightSize;

	unsigned int m_unclosedOvernightLongSize;
	unsigned int m_unclosedOvernightShortSize;

	unsigned int m_loadedLongSize;
	unsigned int m_loadedShortSize;
	unsigned int m_loadedSize;
	Money m_overnightLongInvestment;
	Money m_overnightShortInvestment;
//	Money m_overnightInvestment;

	unsigned short m_recoveryErrorCode;
	bool m_historyLoadingStarted;

	char m_accountType;
	char m_firmType;
	bool m_retail;
	bool m_marginExcessManaged;
	bool m_portfolioManaged;
	bool m_executionsLoaded;
	bool m_ordersLoaded;

	bool m_cancelOrdersInitiated;
	bool m_closePositionsInitiated;

	bool m_loadingHistory;

//	unsigned char m_itgAccount;

	bool m_constraintsInitialized;

	unsigned char m_securityTypeHidden;//0 - none, 1 << ST_STOCK, 1 << ST_OPTION

	mutable bool m_loadExecutionRequestSent;
	mutable bool m_loadOrderRequestSent;

	Price m_borrowPriceMultiplier;

	void SetClearingFirm(ClearingFirm* const& clearingFirm){m_clearingFirm = clearingFirm;}
	ClearingFirm* m_clearingFirm;

	virtual void IncrementUpdatedPnlPositionCount(const bool openPnlForLossUpdated) override;
	virtual void DecrementUpdatedPnlPositionCountWithoutLock() override{--m_updatedPnlPositionCount;}
	virtual void DecrementLoadedPositionCountWithoutLock() override{--m_loadedPositionCount;}
	unsigned int m_updatedPnlPositionCount;
	unsigned int m_loadedPositionCount;

	virtual unsigned char ActOnMaxLoss(){return 0;}//2 - close positions initiated, 1 - cancel orders initiated, 0 - no action done
	virtual bool CheckAllPositionsMaxLoss(unsigned char accountAction, bool constraintsChanged){return false;}
	virtual bool ActOnPositionMaxLoss(Position* position, unsigned char accountAction){return false;}

	void SetOpenPnlNbboPrintHiInv(const Money& pnl){if(m_inventory)m_inventory->SetOpenPnlNbboPrintHi(pnl);}
	void SetOpenPnlNbboPrintLoInv(const Money& pnl){if(m_inventory)m_inventory->SetOpenPnlNbboPrintLo(pnl);}
	void SetMarkedPnlNbboPrintHiInv(const Money& pnl){if(m_inventory)m_inventory->SetMarkedPnlNbboPrintHi(pnl);}
	void SetMarkedPnlNbboPrintLoInv(const Money& pnl){if(m_inventory)m_inventory->SetMarkedPnlNbboPrintLo(pnl);}

	void SetMaxInvestmentInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestment(investment);}
	void SetMaxInvestmentLongInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentLong(investment);}
	void SetMaxInvestmentShortInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentShort(investment);}

	void SetMaxInvestmentMeInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentMe(investment);}
	void SetMaxInvestmentLongMeInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentLongMe(investment);}
	void SetMaxInvestmentShortMeInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentShortMe(investment);}

	void SetMaxInvestmentBetaInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentBeta(investment);}
	void SetMaxInvestmentLongBetaInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentLongBeta(investment);}
	void SetMaxInvestmentShortBetaInv(const Money& investment){if(m_inventory)m_inventory->SetMaxInvestmentShortBeta(investment);}

	void SetConditionallyOpenPnlNbboPrintHiInv(const Money& pnl){if(m_inventory)m_inventory->SetConditionallyOpenPnlNbboPrintHi(pnl);}
	void SetConditionallyOpenPnlNbboPrintLoInv(const Money& pnl){if(m_inventory)m_inventory->SetConditionallyOpenPnlNbboPrintLo(pnl);}
	void SetConditionallyMarkedPnlNbboPrintHiInv(const Money& pnl){if(m_inventory)m_inventory->SetConditionallyMarkedPnlNbboPrintHi(pnl);}
	void SetConditionallyMarkedPnlNbboPrintLoInv(const Money& pnl){if(m_inventory)m_inventory->SetConditionallyMarkedPnlNbboPrintLo(pnl);}

	void SetConditionallyMaxInvestmentInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestment(investment);}
	void SetConditionallyMaxInvestmentLongInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentLong(investment);}
	void SetConditionallyMaxInvestmentShortInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentShort(investment);}

	void SetConditionallyMaxInvestmentBetaInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentBeta(investment);}
	void SetConditionallyMaxInvestmentLongBetaInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentLongBeta(investment);}
	void SetConditionallyMaxInvestmentShortBetaInv(const Money& investment){if(m_inventory)m_inventory->SetConditionallyMaxInvestmentShortBeta(investment);}

	AccountInventory* m_inventory;

	bool DoDestroyUntradedPositions();
	virtual bool WriteDestroyUntradedPositionsToAccountThread(){return false;}

	bool DoDestroyUntradedPosition(Position* position);
	virtual bool WriteDestroyUntradedPositionToAccountThread(const unsigned __int64& symbol
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
#endif
		){return false;}
	virtual void WriteDeletePositionToMainThread(Position* position){}

	TakionLock m_ocoLock;//Order canceles Order
	bool LockOcoModification() const{return m_ocoLock.LockModification();}
	void UnlockOcoModification() const{m_ocoLock.UnlockModification();}

	OcoMap m_ocoMap;
	unsigned int m_currentOcoId;
	unsigned int m_nextOcoId;
	virtual bool WriteAddOcoOrdersToAccountThread(const unsigned int& ocoId, const UIntHashSet& orderClientIdSet){return false;}
	virtual bool WriteRemoveOcoOrdersToAccountThread(const unsigned int& ocoId, const UIntHashSet& orderClientIdSet, bool clearOcoFromOrder){return false;}
	virtual bool WriteClearOcoOrdersToAccountThread(const unsigned int& ocoId, bool clearOcoFromOrder){return false;}
	virtual bool WriteClearAllOcoOrdersToAccountThread(bool clearOcoFromOrder){return false;}
	virtual bool WriteSetCurrentOcoIdToAccountThread(const unsigned int& ocoId){return false;}
	virtual bool WriteResetCurrentOcoIdToAccountThread(){return false;}
	virtual void WriteSetCurrentOcoIdToMainThread(const unsigned int& ocoId){}
	virtual void WriteResetCurrentOcoIdToMainThread(){}
/*
	bool CollectOrdersToAddToOco(OrderSet& orderSet, unsigned int ocoId, const UIntHashSet& orderClientIdSet)
	{
		if(!ocoId)ocoId = m_currentOcoId;
		unsigned int orderOcoId;
		Order* order;
		OrderSet orderSet;
		for(UIntHashSet::const_iterator it = orderClientIdSet.begin(), itend = orderClientIdSet.end(); it != itend; ++it)
		{
			order = FindOrderActive(*it);
			if(order && order->CanBeOco() && !order->isDead() && order->GetAccount() == this)
			{
				orderOcoId = order->GetOcoId();
				if(orderOcoId)
				{
					if(ocoId)
					{
						if(ocoId != orderOcoId)return false;
					}
					else
					{
						ocoId = orderOcoId;
					}
				}
				else
				{
					orderSet.insert(order);
				}
			}
		}
		return true;
	}
*/
	bool DoAddOcoOrder(unsigned int ocoId, Order* order);//?//Should be called only from the account thread
	bool DoAddOcoOrders(unsigned int ocoId, const OrderSet& orderSetOriginal);//?//const UIntHashSet& orderClientIdSet)//Should be called only from the account thread
	bool DoRemoveOcoOrder(Order* order, bool clearOcoFromOrder);//Should be called only from the account thread
	bool DoRemoveOcoOrders(unsigned int ocoId, const OrderSet& orderSetOriginal, bool clearOcoFromOrder);//, const UIntHashSet& orderClientIdSet)//Should be called only from the account thread
	bool GetAndClearOcoOrders(const unsigned int& ocoId, OrderSet& orderSet);//Should be called only from the account thread
	bool DoClearOcoOrders(const unsigned int& ocoId, bool clearOcoFromOrder);//Should be called only from the account thread
	bool DoClearAllOcoOrders(bool clearOcoFromOrder);//Should be called only from the account thread
	bool DoSetCurrentOcoId(const unsigned int& ocoId);//Should be called only from the account thread
	bool DoResetCurrentOcoId();//Should be called only from the account thread
private:
	Account(const Account& other);
	Account& operator=(const Account& other);
};

#define CLEARING_FIRM_IN_WORKER_THREAD

class TU_API ClearingFirm : public AccountFirm, public Observable, public TakionLockMultithread
/*
#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	TakionLock
#else
	TakionLockMultithread
#endif
*/
{
friend class TakionUtils;
public:
	virtual ~ClearingFirm()
	{
		WaitForExitEnforceThread();
		ClearEnforceThreadHandle();
//#ifndef CLEARING_FIRM_IN_WORKER_THREAD
		ClearAccounts();
//#endif
	}
	const bool& isEnforceFirm() const{return m_enforceFirm;}
	const bool& isEnforceFirmInitialized() const{return m_enforceFirmInitialized;}
	const bool& isConservativeOrderMarking() const{return m_conservativeOrderMarking;}
	const bool& isLocalSideMarking() const{return m_localSideMarking;}
#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	virtual
#endif
	void SetEnforceFirm(const bool& enforceFirm)
	{
		bool changed = false;
		const bool unlock = LockModification();// Accounts();
		m_enforceFirmInitialized = true;
		if(enforceFirm != m_enforceFirm)
		{
			m_enforceFirm = enforceFirm;
			changed = true;
		}
		if(unlock)UnlockModification();// Accounts();
		if(changed)
		{
			WriteUpdateConstraintsMessageToMainThread();
		}
	}
#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	virtual
#endif
	void SetBoolParams(const bool& enforceFirm, const bool& conservativeOrderMarking, const bool& localSideMarking)
	{
		bool changed = false;
		const bool unlock = LockModification();// Accounts();
		m_enforceFirmInitialized = true;
		if(enforceFirm != m_enforceFirm)
		{
			m_enforceFirm = enforceFirm;
			changed = true;
		}
		if(conservativeOrderMarking != m_conservativeOrderMarking)
		{
			m_conservativeOrderMarking = conservativeOrderMarking;
			changed = true;
		}
		if(localSideMarking != m_localSideMarking)
		{
			m_localSideMarking = localSideMarking;
			changed = true;
		}
		if(unlock)UnlockModification();// Accounts();
		if(changed)
		{
			WriteUpdateConstraintsMessageToMainThread();
		}
	}

//For Supervisor only
	const unsigned int& GetNiteBetaEnforcementStartTime() const{return m_niteBetaEnforcementStartTime;}

	virtual Money GetNiteBetaBuyingPower() const{return Money::moneyZero;}
	virtual Money GetBetaInvestment() const{return Money::moneyZero;}
	virtual Money GetBetaBpUsed() const{return Money::moneyZero;}
	virtual Money GetNiteBetaBpAvailable() const{return Money::moneyZero;}

	Money GetMarginExcessMultiplier() const{return m_marginExcessMultiplier;}
	Money GetMarginExcess() const{return m_marginExcess;}
	Money GetHardMarginExcess() const{return m_hardMarginExcess;}
	Money GetTotalEquity() const{return m_totalEquity;}

#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	virtual
#endif
	void IncrementBetaBpUsed(const Money& bpUsed)
	{
		if(!bpUsed.isZero())
		{
			const bool unlock = LockModification();// Accounts();
			DoIncrementBetaBpUsed(bpUsed);
			if(unlock)UnlockModification();//Accounts();
			WriteUpdateMessageToMainThread();
		}
	}
#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	virtual
#endif
	void IncrementBetaInvestment(const Money& investment)
	{
		if(!investment.isZero())
		{
			const bool unlock = LockModification();// Accounts();
			DoIncrementBetaInvestment(investment);
			if(unlock)UnlockModification();//Accounts();
			WriteUpdateMessageToMainThread();
		}
	}

#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	virtual
#endif
	void SetRetailParams(const Money& marginExcessMultiplier, const Money& marginExcess, const Money& totalEquity)
	{
		bool changed = false;
		const bool unlock = LockModification();// Accounts();
		if(marginExcessMultiplier != m_marginExcessMultiplier)
		{
			m_marginExcessMultiplier = marginExcessMultiplier;
			changed = true;
		}
		if(marginExcess != m_hardMarginExcess)
		{
			m_hardMarginExcess = marginExcess;
			changed = true;
		}
		if(changed)
		{
			if(marginExcessMultiplier.GetDollarFraction())
			{
				m_marginExcess = m_hardMarginExcess * (marginExcessMultiplier.GetDollars() * Money::divider + marginExcessMultiplier.GetDollarFraction()) / Money::divider;
			}
			else
			{
				m_marginExcess = m_hardMarginExcess * marginExcessMultiplier.GetDollars();
			}
		}
		if(totalEquity != m_totalEquity)
		{
			m_totalEquity = totalEquity;
			changed = true;
		}
		if(unlock)UnlockModification();// Accounts();
		if(changed)
		{
			WriteUpdateRetailMessageToMainThread();
		}
	}

	virtual void SetBetaParams(const unsigned int& niteBetaEnforcementStartTime, const Money& niteBetaBuyingPower){}

	virtual void WriteUpdateMessageToMainThread(){}
	virtual void WriteUpdateConstraintsMessageToMainThread(){}
	virtual void WriteUpdateRetailMessageToMainThread(){}
	typedef std::set<Account*> AccountSet;

#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	virtual
#endif
	bool AddAccount(Account* account)
	{
		const Money& bp = account->GetBuyingPowerBetaUsed();
		const Money& investment = account->GetInvestmentBeta();
		LockAccountStorageModification();
		bool ret = m_accountSet.insert(account).second;
		UnlockAccountStorageModification();
		if(ret)
		{
			account->SetClearingFirm(this);
//We don't have to lock the Account for inquiry because these functions, modifying the total values, are called in the account thread
//			account->LockInquiryWait();

			const bool unlock = LockModification();
			DoIncrementBetaBpUsed(bp);
			DoIncrementBetaInvestment(investment);
			if(unlock)UnlockModification();

//			account->UnlockInquiry();
		}
		if(ret)
		{
			WriteUpdateConstraintsMessageToMainThread();
		}
		return ret;
	}
#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	virtual
#endif
	bool RemoveAccount(Account* account)
	{
		bool ret = false;
		const bool unlockStorage = LockAccountStorageModification();
		AccountSet::iterator found = m_accountSet.find(account);
		if(found != m_accountSetEnd)
		{
			ret = true;
			m_accountSet.erase(found);
			if(unlockStorage)UnlockAccountStorageModification();

			const bool unlock = LockModification();
			DoIncrementBetaBpUsed(-account->GetBuyingPowerBetaUsed());
			DoIncrementBetaInvestment(-account->GetInvestmentBeta());
			if (unlock)UnlockModification();//Accounts();
			account->SetClearingFirm(NULL);
		}
		else if(unlockStorage)UnlockAccountStorageModification();

		if(ret)
		{
			WriteUpdateConstraintsMessageToMainThread();
		}
		return ret;
	}
	virtual void ResetBetaParams(){}
#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	virtual
#endif
	bool ClearAccounts()
	{
		bool ret = false;
		Account* account;
		const bool unlockStorage = LockAccountStorageModification();
		if(!m_accountSet.empty())
		{
			for(AccountSet::iterator it = m_accountSet.begin(); it != m_accountSetEnd; ++it)
			{
				account = *it;// accountPair->key;
				account->SetClearingFirm(NULL);
			}
			m_accountSet.clear();
			if(unlockStorage)UnlockAccountStorageModification();

			ResetBetaParams();

			ret = true;
		}
		else if(unlockStorage)UnlockAccountStorageModification();

		if(ret)
		{
			WriteUpdateConstraintsMessageToMainThread();
		}
		return ret;
	}
	bool LockAccountStorageInquiry(){return m_accountStorageLock.LockInquiry();}
	void LockAccountStorageInquiryWait(){m_accountStorageLock.LockInquiryWait();}
	void UnlockAccountStorageInquiry(){m_accountStorageLock.UnlockInquiry();}

//LockAccountStorageInquiryWait //UnlockAccountStorageInquiry
	unsigned int GetAccountCount() const{return (unsigned int)m_accountSet.size();}
	const AccountSet& GetAccountSet() const{return m_accountSet;}

	virtual bool isNiteBetaEnforcementTriggered() const{return false;}
	const bool& isSupervisor() const{return m_supervisor;}
#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	const unsigned int& GetThreadId() const{return m_threadId;}
	bool isInThread() const{return GetCurrentThreadId() == GetThreadId();}
#endif
protected:
	ClearingFirm(const AccountId& name,
		const bool& supervisor,
		const bool& enforceFirm = false,
		const bool& conservativeOrderMarking = false,
		const bool& localSideMarking = false,
		const unsigned int& niteBetaEnforcementStartTime = 0,
		const Money& niteBetaBuyingPower = Money::moneyZero):
		AccountFirm(name, nextOrdinal++),
		m_supervisor(supervisor),
		m_enforceFirm(enforceFirm),
		m_enforceFirmInitialized(false),
		m_conservativeOrderMarking(conservativeOrderMarking),
		m_localSideMarking(localSideMarking),
		m_niteBetaEnforcementStartTime(niteBetaEnforcementStartTime),
		m_accountSetEnd(m_accountSet.end()),
#ifdef CLEARING_FIRM_IN_WORKER_THREAD
		m_threadId(0),
#endif
		m_enforceThreadHandle(NULL),
		m_enforceThreadId(0)
	{
	}
	virtual void DoIncrementBetaBpUsed(const Money& bpUsed){}
	virtual void DoIncrementBetaInvestment(const Money& investment){}

	virtual void OnEnforcementTimeChange(unsigned int niteBetaEnforcementStartTime){}

	void EnforceNiteBetaConstraint()
	{
		if(m_loaded && isNiteBetaEnforcementTriggered())
		{
			DoEnforceNiteBetaConstraint();
		}
	}

	virtual void DoEnforceNiteBetaConstraint(){}

	bool m_supervisor;
	bool m_enforceFirm;
	bool m_enforceFirmInitialized;
	bool m_conservativeOrderMarking;
	bool m_localSideMarking;

//For Supervisor only
	unsigned int m_niteBetaEnforcementStartTime;

	Money m_marginExcessMultiplier;
	Money m_marginExcess;
	Money m_hardMarginExcess;
	Money m_totalEquity;

	AccountSet m_accountSet;
	AccountSet::iterator m_accountSetEnd;

	void ClearEnforceThreadHandle()
	{
		if(m_enforceThreadHandle)
		{
			CloseHandle(m_enforceThreadHandle);
			m_enforceThreadHandle = NULL;
			m_enforceThreadId = 0;
		}
	}

	void WaitForExitEnforceThread()
	{
		if(m_enforceThreadHandle)
		{
			WaitForSingleObject(m_enforceThreadHandle, INFINITE);
		}
	}

#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	unsigned int m_threadId;
#endif

	HANDLE m_enforceThreadHandle;//Thread created for the DoEnforceNiteBetaConstraint call
	unsigned int m_enforceThreadId;

	bool LockAccountStorageModification(){return m_accountStorageLock.LockModification();}
	void UnlockAccountStorageModification(){m_accountStorageLock.UnlockModification();}

	TakionLockMultithread m_accountStorageLock;

private:
	static unsigned int nextOrdinal;
	ClearingFirm(const ClearingFirm& other);
	ClearingFirm* operator=(const ClearingFirm& other);
};

class TU_API StockLoanFirm : public Firm, public TakionLock
{
friend class TakionUtils;
public:
	StockLoanFirm(const char* const& name):
		Firm(name, nextOrdinal++)
	{
		m_stockMap.InitHashTable(9001);
	}
	typedef CMap<unsigned __int64, const unsigned __int64&, StockLoanInfo, const StockLoanInfo&> StockMap;
//	const StockMap& GetStockMap() const{return  m_stockMap;}//LockInquiryWait/UnlockInquiry
	const StockLoanInfo* GetStockLoanInfo(unsigned __int64 symbol) const//LockInquiryWait/UnlockInquiry
	{
		const StockMap::CPair* found = m_stockMap.PLookup(symbol);
		return found ? &found->value : NULL;
	}

	unsigned char isHTB(const unsigned __int64& symbol) const
	{
		unsigned char ret = StockLoanInfo::regularHtb;
		LockInquiryWait();
		const StockMap::CPair* found = m_stockMap.PLookup(symbol);
		if(found)ret = found->value.GetHTB();
		UnlockInquiry();
		return ret;
	}
	bool isETB(const unsigned __int64& symbol) const
	{
		bool ret;
		LockInquiryWait();
		const StockMap::CPair* found = m_stockMap.PLookup(symbol);
		ret = found && !found->value.GetHTB();
		UnlockInquiry();
		return ret;
	}
//Do not call AddETB
	void AddETB(const unsigned __int64& symbol, const unsigned char& htb = '\0')//LockModification/Unlock
	{
#ifdef _DEBUG
if(htb == 0xFF)
{
printf("X");
}
#endif
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		if(found)found->value.SetHTB(htb);
		else
		{
			bool unlock = LockModification();
			m_stockMap.SetAt(symbol, StockLoanInfo(htb));
			if(unlock)UnlockModification();
		}
	}
//Do not call SetETB
	void SetETB(const unsigned __int64& symbol, const unsigned char& htb)
	{
#ifdef _DEBUG
if(htb == 0xFF)
{
printf("X");
}
#endif
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		if(found)found->value.SetHTB(htb);
		else if(htb != StockLoanInfo::regularHtb)
		{
			bool unlock = LockModification();
			m_stockMap.SetAt(symbol, StockLoanInfo(htb));
			if(unlock)UnlockModification();
		}
	}
//Do not call ClearETB
	void ClearETBs()
	{
		for(StockMap::CPair* p = m_stockMap.PGetFirstAssoc(); p; p = m_stockMap.PGetNextAssoc(p))
		{
			if(!p->value.GetHTB())p->value.SetHTB(StockLoanInfo::regularHtb);
		}
	}

/*
//Do not call AddStockLoanInfo
	void AddStockLoanInfo(const unsigned __int64& symbol, const StockLoanInfo& info)
	{
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		const bool unlock = LockModification();
		if(found)found->value = info;
		else
		{
			m_stockMap.SetAt(symbol, info);
		}
		if(unlock)UnlockModification();
	}
*/
//Do not call SetStockLoanInfo
/*
	bool SetStockLoanInfo(const unsigned __int64& symbol, const StockLoanInfo& info)
	{
		bool ret = false;
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		bool unlock = LockModification();
		if(found)
		{
//			if(!info.GetMargin() && info.GetBeta().isZero())found->value.SetStockLoanInfoOnly(info);
			if(!info.GetMargin() && !info.GetCompactBeta())ret = found->value.SetStockLoanInfoOnly(info);
			else if(info != found->value)
			{
				found->value = info;
				ret = true;
			}
		}
		else
		{
			ret = true;
//			m_stockMap.SetAt(symbol, (StockLoanInfo&)info);
//			if(!info.GetMargin() && info.GetBeta().isZero())
			if(!info.GetMargin() && !info.GetCompactBeta())
			{
				StockLoanInfo infoModified(info);
//				infoModified.SetBeta(SignedPrice(100, 0));
				infoModified.SetCompactBeta(StockLoanInfo::defaultCompactBeta);
				infoModified.SetMargin(StockLoanInfo::defaultMargin);
				m_stockMap.SetAt(symbol, infoModified);
			}
			else m_stockMap.SetAt(symbol, info);
		}
		if(unlock)UnlockModification();

		return ret;
	}
*/
//Do not call SetStockLoanInfoOnly
	bool SetStockLoanInfoOnly(const unsigned __int64& symbol, const StockLoanInfo& info)
	{
		bool ret = false;
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		bool unlock = LockModification();
		if(found)
		{
			ret = found->value.SetStockLoanInfoOnly(info);
		}
		else
		{
			ret = true;
			StockLoanInfo adjustedInfo(info);
			adjustedInfo.SetHTB(StockLoanInfo::regularHtb);
			adjustedInfo.SetCompactBeta(StockLoanInfo::defaultCompactBeta);
			adjustedInfo.SetMargin(StockLoanInfo::defaultMargin);

			adjustedInfo.SetPmElRate(StockLoanInfo::default_PM_EL_Rate);
			adjustedInfo.SetPmEsRate(StockLoanInfo::default_PM_ES_Rate);
			adjustedInfo.SetPmHlRate(StockLoanInfo::default_PM_HL_Rate);
			adjustedInfo.SetPmHsRate(StockLoanInfo::default_PM_HS_Rate);
			adjustedInfo.SetElRate(StockLoanInfo::default_EL_Rate);
			adjustedInfo.SetEsRate(StockLoanInfo::default_ES_Rate);
			adjustedInfo.SetHlRate(StockLoanInfo::default_HL_Rate);
			adjustedInfo.SetHsRate(StockLoanInfo::default_HS_Rate);
			adjustedInfo.SetFedReq(StockLoanInfo::default_Fed_Req);
			adjustedInfo.SetAssetType(StockLoanInfo::default_Asset_Type);
			adjustedInfo.SetMarginable(StockLoanInfo::default_Marginable);
			adjustedInfo.SetSecType(StockLoanInfo::default_Sec_Type);
			adjustedInfo.SetStatus(StockLoanInfo::default_Status);

			m_stockMap.SetAt(symbol, adjustedInfo);
		}
		if(unlock)UnlockModification();

		return ret;
	}

//Do not call SetBetaAndRetailInfo
	bool SetBetaAndRetailInfo(const unsigned __int64& symbol, const StockLoanInfo& info)
	{
		bool ret = false;
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
		bool unlock = LockModification();
		if(found)
		{
			ret = found->value.SetBetaAndRetailInfo(info);
		}
		else
		{
			ret = true;
			StockLoanInfo adjustedInfo(info);
			adjustedInfo.SetHTB(StockLoanInfo::regularHtb);
//			adjustedInfo.SetCompactBeta(StockLoanInfo::defaultCompactBeta);
//			adjustedInfo.SetMargin(StockLoanInfo::defaultMargin);
			m_stockMap.SetAt(symbol, adjustedInfo);
		}
		if(unlock)UnlockModification();

		return ret;
	}

//Do not call SetStockLoanInfoAndBeta
//	bool SetStockLoanInfoAndBeta(const unsigned __int64& symbol, const StockLoanInfo& info)
	bool SetStockLoanInfo(const unsigned __int64& symbol, const StockLoanInfo& info)
	{
		bool ret = false;
		StockMap::CPair* found = m_stockMap.PLookup(symbol);
#ifdef _DEBUG
if(info.GetHTB() == 0xFF)
{
printf("X");
}
#endif
		bool unlock = LockModification();
		if(found)
		{
			ret = found->value.SetStockLoanInfo(info);
		}
		else
		{
			ret = true;
			StockLoanInfo adjustedInfo(info);
			adjustedInfo.SetHTB(StockLoanInfo::regularHtb);
			m_stockMap.SetAt(symbol, adjustedInfo);
//			m_stockMap.SetAt(symbol, info);
		}
		if(unlock)UnlockModification();

		return ret;
	}

protected:
	StockMap m_stockMap;
private:
	static unsigned int nextOrdinal;
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

class TU_API OrderAlgorithm : public Order, public Observer
{
public:
#if (_MSC_VER > 1600)
	typedef std::unordered_map<Order*, unsigned int> OrderCancelRejectMap;
	typedef std::unordered_set<unsigned int> UIntSet;
#else
	typedef std::hash_map<Order*, unsigned int> OrderCancelRejectMap;
	typedef std::hash_set<unsigned int> UIntSet;
#endif
//	typedef std::set<Order*, lessOrderReplace> OrderCancelSet;

	virtual bool isPriceValid() const{return !m_limitPrice.isZero() || isMarketOrder();}
	virtual OrderAlgorithm* CloneAlgorithm() const = 0;
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual bool isAlgorithm() const override{return true;}
	virtual bool isOrderVariation() const override{return false;}
	virtual bool isQuoteOrder() const override{return false;}
	virtual bool CanBeReplaced() const override{return false;}
	virtual bool CanBeOco() const override{return false;}
	void SetPosition(const Position* position){m_position = position;}

	const bool& isFailed() const{return m_failed;}

	virtual bool isPostponed() const override{return m_postponed;}
	virtual void Postpone(const bool postpone) override;
	virtual bool CanBeMadeGtc() const override{return false;}
	virtual bool isGtc() const override{return false;}

	virtual bool SecurityMustBeLoaded() const{return false;}

	virtual void ProcessMainThreadNotification(unsigned short code){}
//	bool isProactive() const{return m_proactive;}
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual unsigned int GetAlgorithmId() const = 0;
	virtual bool isQuantityValid() const{return GetQuantity() > 0;}
	const unsigned int& GetGeneratedOrderCount() const{return m_generatedOrderCount;}
/*
	const bool& isSecuritySameThreadAsAccount() const{return m_securitySameThreadAsAccount;}
	const bool& isUseSecurityNotification() const{return m_useSecurityNotification;}
	const unsigned int& GetSecurityUpdatedOrdinal() const{return m_securityUpdatedOrdinal;}
	const unsigned int& GetSecuritySentOrdinal() const{return m_securitySentOrdinal;}
	void SecurityUpdate();
	unsigned int CalculatePegPrice() const;
*/
//	virtual void SecurityUpdate(){}
	virtual const char* GetSymbol() const override{return m_position ? m_position->GetSymbol() : "";}
	virtual const unsigned __int64& GetNumericSymbol() const override{return m_position ? m_position->GetNumericSymbol() : uint64Zero;}
	virtual SecurityType GetSecurityType() const override{return m_position ? m_position->GetSecurityType() : ST_STOCK;}
	virtual const char* GetAccountId() const override{return m_account ? m_account->GetId() : "";}
	virtual const char* GetAccountUserName() const override{return m_account ? m_account->GetUserName() : "";}
	virtual const Account* GetAccount() const override{return m_account;}
	virtual void WriteAlgorithmNotifyMessageToAccountThread(unsigned short code, unsigned short eventCode) override;

#ifndef TAKION_NO_OPTIONS
	virtual const OptionSymbolBlock* GetOptionSymbolBlock() const override{return m_position ? m_position->GetOptionSymbolBlock() : NULL;}
	virtual const unsigned short& GetOptionType() const override{return m_position ? m_position->GetOptionType() : ushortZero;}
	virtual const unsigned __int64& GetOptionBlock() const override{return m_position ? m_position->GetOptionBlock() : uint64Zero;}
	virtual const unsigned __int64& GetUnderlierNumericSymbol() const override{return m_position ? m_position->GetUnderlierNumericSymbol() : uint64Zero;}
	virtual bool isCall() const override{return m_position ? m_position->isCall() : false;}
	virtual unsigned char GetSuffix() const override{return m_position ? m_position->GetSuffix() : 0;}
	virtual unsigned char GetCallPutFlags() const override{return m_position ? m_position->GetCallPutFlags() : 0;}
	virtual const unsigned char& GetOptionFlags() const override{return m_position ? m_position->GetOptionFlags() : ucharZero;}
	virtual const unsigned int& GetStrikePrice() const override{return m_position ? m_position->GetStrikePrice() : uintZero;}
	virtual unsigned int GetExpirationDate() const override{return m_position ? m_position->GetExpirationDate() : 0;}
	virtual const unsigned char& GetExpirationType() const override{return m_position ? m_position->GetExpirationType() : ucharZero;}
	virtual const unsigned int& GetExpirationDays() const override{return m_position ? m_position->GetExpirationDays() : uintZero;}
	virtual const char& GetExpirationTypeChar() const override{return m_position ? m_position->GetExpirationTypeChar() : charZero;}
	virtual void GetOptionBlockAsString(std::string& optionSymbol, bool suffixSeparate) const override{if(m_position)m_position->GetOptionBlockAsString(optionSymbol, suffixSeparate);}
	virtual void GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const override{if(m_position)m_position->GetOptionSymbol(optionSymbol, suffixSeparate);}
	virtual const unsigned int& GetContractSize() const override{return m_position ? m_position->GetContractSize() : uint100;}
#endif
	void AddOrderToCancel(Order* const& order)
	{
		m_ordersToCancel.insert(order);
		m_orderIdsToCancel.insert(order->GetClientId());
	}
	void AddOrderClientIdToCancel(const unsigned int& clientId)
	{
		m_orderIdsToCancel.insert(clientId);
	}
	void ClearOrdersToCancel()
	{
		m_orderIdsToCancel.clear();
		m_ordersToCancel.clear();
	}
	OrderAlgorithm& operator=(const OrderAlgorithm& other)
	{
		Order::operator=(other),
		m_account = other.m_account;
		m_washOrderPolicy = other.m_washOrderPolicy;//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		m_oversellSplitPolicy = other.m_oversellSplitPolicy;//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		m_resizeShortToBorrowed = other.m_resizeShortToBorrowed;
		m_noRedirect = other.m_noRedirect;
//		m_closeOnly = other.m_closeOnly;
		m_roundLotPolicy = other.m_roundLotPolicy;
		m_postponed = other.m_postponed;
		m_failed = other.m_failed;

		m_generatedOrderCount = other.m_generatedOrderCount;

		m_orderIdsToCancel = other.m_orderIdsToCancel;
		m_ordersToCancel = other.m_ordersToCancel;

		m_ordersBeingCanceled = other.m_ordersBeingCanceled;
//		m_ordersBeingCanceledEnd = m_ordersBeingCanceled.end();
		return *this;
	}
	const unsigned int& GetGtcId() const{return m_gtcId;}//similar to m_clientId / m_serverId, used for finding the GTC Algos
	void SetGtcId(const unsigned int& gtcId){m_gtcId = gtcId;}
protected:
	OrderAlgorithm(const Position* position,
		bool postponed,
		unsigned int timeToActivate,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		unsigned int traderId,
		unsigned int sendId,
		unsigned int ocoId,
		unsigned int clientId,
//		unsigned int clientIdOriginal,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
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
		const Price& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool dma,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool borrow,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		bool resizeShortToBorrowed,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
//		bool proAts,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		unsigned char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,
		const unsigned __int64& userId);
//		bool useSecurityNotification);
	OrderAlgorithm(const char*& fromString);//, bool useSecurityNotification);
	OrderAlgorithm(const OrderAlgorithm& other):
		Order(other),
		m_account(other.m_account),
		m_washOrderPolicy(other.m_washOrderPolicy),//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		m_oversellSplitPolicy(other.m_oversellSplitPolicy),//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		m_resizeShortToBorrowed(other.m_resizeShortToBorrowed),
		m_noRedirect(other.m_noRedirect),
//		m_closeOnly(other.m_closeOnly),
		m_roundLotPolicy(other.m_roundLotPolicy),
		m_postponed(other.m_postponed),
		m_failed(other.m_failed),

		m_gtcId(other.m_gtcId),
		m_generatedOrderCount(other.m_generatedOrderCount),

		m_orderIdsToCancel(other.m_orderIdsToCancel),
		m_ordersToCancel(other.m_ordersToCancel),

		m_ordersBeingCanceled(other.m_ordersBeingCanceled),
		m_ordersBeingCanceledEnd(m_ordersBeingCanceled.end())
	{
	}
/*
	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL) override;
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = NULL){return false;}
	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = NULL) const{return false;}
	const Security* m_security;
*/
	virtual void DoSecurityUpdate(){}
	virtual void NullifySecurity(){}
	Account* m_account;
	unsigned char m_washOrderPolicy;//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
	unsigned char m_oversellSplitPolicy;//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
	bool m_resizeShortToBorrowed;
	bool m_noRedirect;
//	bool m_closeOnly;
	unsigned char m_roundLotPolicy;
	bool m_postponed;
	bool m_failed;

	unsigned int m_gtcId;//similar to m_clientId, used for finding the GTC Algos

	unsigned int m_generatedOrderCount;

	void ProcessOrderDead(Order* order);
	void ProcessCancelRejected(Order* order);
	virtual void OrderDeadProcessed(Order* order){}
	virtual void AllOrdersCanceled(){}
	UIntSet m_orderIdsToCancel;
//	OrderCancelSet m_ordersToCancel;
	OrderReplaceSet m_ordersToCancel;

	OrderCancelRejectMap m_ordersBeingCanceled;
	OrderCancelRejectMap::const_iterator m_ordersBeingCanceledEnd;

//	bool m_proactive;
//	Position* m_position;
/*
private:
	OrderAlgorithm(const OrderAlgorithm& other);
	OrderAlgorithm& operator=(const OrderAlgorithm& other);
*/
};

class TU_API SecurityAlgorithm : public OrderAlgorithm
{
public:
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
//	virtual void EndAlgorithm() override;
	virtual void SecurityUpdate() override;
	const bool& isSecuritySameThreadAsAccount() const{return m_securitySameThreadAsAccount;}
	const bool& isUseSecurityNotification() const{return m_useSecurityNotification;}
	const unsigned int& GetSecurityUpdatedOrdinal() const{return m_securityUpdatedOrdinal;}
	const unsigned int& GetSecuritySentOrdinal() const{return m_securitySentOrdinal;}
	unsigned int CalculatePegPrice() const;
	virtual const char* GetSymbol() const override{return m_security ? m_security->GetSymbol() : OrderAlgorithm::GetSymbol();}
	virtual const unsigned __int64& GetNumericSymbol() const override{return m_security ? m_security->GetNumericSymbol() : OrderAlgorithm::GetNumericSymbol();}
#ifndef TAKION_NO_OPTIONS
//	virtual const OptionSymbolBlock* GetOptionSymbolBlock() const{return m_security ? m_security->GetOptionSymbolBlock() : NULL;}
	virtual const unsigned short& GetOptionType() const override{return m_security ? m_security->GetOptionType() : OrderAlgorithm::GetOptionType();}
	virtual const unsigned __int64& GetOptionBlock() const override{return m_security ? m_security->GetOptionBlock() : OrderAlgorithm::GetOptionBlock();}
	virtual const unsigned __int64& GetUnderlierNumericSymbol() const override{return m_security ? m_security->GetUnderlierNumericSymbol() : OrderAlgorithm::GetUnderlierNumericSymbol();}
	virtual bool isCall() const override{return m_security ? m_security->isCall() : OrderAlgorithm::isCall();}
	virtual unsigned char GetSuffix() const override{return m_security ? m_security->GetSuffix() : OrderAlgorithm::GetSuffix();}
	virtual unsigned char GetCallPutFlags() const override{return m_security ? m_security->GetCallPutFlags() : OrderAlgorithm::GetCallPutFlags();}
	virtual const unsigned char& GetOptionFlags() const override{return m_security ? m_security->GetOptionFlags() : OrderAlgorithm::GetOptionFlags();}
	virtual const unsigned int& GetStrikePrice() const override{return m_security ? m_security->GetStrikePrice() : OrderAlgorithm::GetStrikePrice();}
	virtual unsigned int GetExpirationDate() const override{return m_security ? m_security->GetExpirationDate() : OrderAlgorithm::GetExpirationDate();}
	virtual const unsigned char& GetExpirationType() const override{return m_security ? m_security->GetExpirationType() : OrderAlgorithm::GetExpirationType();}
	virtual const unsigned int& GetExpirationDays() const override{return m_security ? m_security->GetExpirationDays() : OrderAlgorithm::GetExpirationDays();}
	virtual const char& GetExpirationTypeChar() const override{return m_security ? m_security->GetExpirationTypeChar() : OrderAlgorithm::GetExpirationTypeChar();}
	virtual void GetOptionBlockAsString(std::string& optionSymbol, bool suffixSeparate) const override{if(m_security)m_security->GetOptionBlockAsString(optionSymbol, suffixSeparate); else OrderAlgorithm::GetOptionBlockAsString(optionSymbol, suffixSeparate);}
	virtual void GetOptionSymbol(std::string& optionSymbol, bool suffixSeparate) const override{if(m_security)m_security->GetOptionSymbol(optionSymbol, suffixSeparate); else OrderAlgorithm::GetOptionSymbol(optionSymbol, suffixSeparate);}
	virtual const unsigned int& GetContractSize() const override{return m_security ? m_security->GetContractSize() : OrderAlgorithm::GetContractSize();}
#endif
protected:
	SecurityAlgorithm(const Position* position,
		bool postponed,
		unsigned int timeToActivate,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		unsigned int traderId,
		unsigned int sendId,
		unsigned int ocoId,
		unsigned int clientId,
//		unsigned int clientIdOriginal,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
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
		const Price& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool dma,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool borrow,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		bool resizeShortToBorrowed,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
//		bool proAts,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		unsigned char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,
		const unsigned __int64& userId,
		bool useSecurityNotification):

		OrderAlgorithm(position,
			postponed,
			timeToActivate,
			gtcDateCreated,
			gtcTimeCreated,
			traderId,
			sendId,
			ocoId,
			clientId,
			averageDailyVolume,
			yesterdaysVolume,
			todaysVolume,
			destinationId,
			destinationName,

			side,
#ifdef FIRM_VALUES
			firmSide,
#endif

			orderType,
			userOrderType,//usually should be 0
			userOrderInfo,//usually should be NULL
			limitPrice,

			discretionaryPrice,

			stopOrderType,
			stopOrderBase,
			stopPrice,

			level1Price,
			level1SameSidePrice,
			lastPrintPrice,

			quantity,
			displayQuantity,
			reserveQuantity,

	//		bool proactive,
			routingId,
			routingSubType,
			routingName,
			mnemonic,
			dma,
			imbalanceOnly,
			iso,
			aggressive,
			roundLot,
			borrow,
			washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
			oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
			resizeShortToBorrowed,
			noRedirect,
			closeOnly,
			resizeToClose,
//			proAts,
			roundLotPolicy,
			pegType,
			pegOffset,

			tifType,
			tifMillisecond,
			parentId,
			userId),
		m_security(NULL),
		m_securitySameThreadAsAccount(false),
		m_useSecurityNotification(useSecurityNotification),
		m_securityUpdatedOrdinal(0),
		m_securitySentOrdinal(0)
#ifdef _DEBUG
		,m_swiping(false)
#endif
	{}
	SecurityAlgorithm(const char*& fromString, bool useSecurityNotification):
		OrderAlgorithm(fromString),
		m_security(NULL),
		m_securitySameThreadAsAccount(false),
		m_useSecurityNotification(useSecurityNotification),
		m_securityUpdatedOrdinal(0),
		m_securitySentOrdinal(0)
	{}

	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL) override;
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = NULL){return false;}
	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = NULL) const{return false;}
//	virtual void DoSecurityUpdate(){}
	virtual void NullifySecurity();
	const Security* m_security;

	bool m_securitySameThreadAsAccount;
	bool m_useSecurityNotification;
	unsigned int m_securityUpdatedOrdinal;
	unsigned int m_securitySentOrdinal;
#ifdef _DEBUG
	bool m_swiping;
#endif
};

#ifndef TAKION_NO_OPTIONS
class TU_API UnderlierAlgorithm : public OrderAlgorithm
{
public:
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
//	virtual void EndAlgorithm() override;
//	virtual void SecurityUpdate() override;
//	const bool& isSecuritySameThreadAsAccount() const{return m_securitySameThreadAsAccount;}
//	const bool& isUseSecurityNotification() const{return m_useSecurityNotification;}
//	const unsigned int& GetSecurityUpdatedOrdinal() const{return m_securityUpdatedOrdinal;}
//	const unsigned int& GetSecuritySentOrdinal() const{return m_securitySentOrdinal;}
//	unsigned int CalculatePegPrice() const;
	virtual const char* GetSymbol() const override{return m_underlier ? m_underlier->GetSymbol() : OrderAlgorithm::GetSymbol();}
	virtual const unsigned __int64& GetNumericSymbol() const override{return m_underlier ? m_underlier->GetNumericSymbol() : OrderAlgorithm::GetNumericSymbol();}
protected:
	UnderlierAlgorithm(const Position* position,
		unsigned int traderId,
		unsigned int sendId,
		unsigned int ocoId,
		unsigned int clientId,
//		unsigned int clientIdOriginal,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
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
		const Price& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool dma,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		bool resizeShortToBorrowed,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
//		bool proAts,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		unsigned char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,
		const unsigned __int64& userId):
//		bool useSecurityNotification):

		OrderAlgorithm(position,
			false,//postponed
			0,//timeToActivate
			0,//unsigned int gtcDateCreated,
			0,//unsigned int gtcTimeCreated,
			traderId,
			sendId,
			ocoId,
			clientId,
			averageDailyVolume,
			yesterdaysVolume,
			todaysVolume,
			destinationId,
			destinationName,

			side,
#ifdef FIRM_VALUES
			firmSide,
#endif

			orderType,
			userOrderType,//usually should be 0
			userOrderInfo,//usually should be NULL
			limitPrice,

			discretionaryPrice,

			stopOrderType,
			stopOrderBase,
			stopPrice,

			level1Price,
			level1SameSidePrice,
			lastPrintPrice,

			quantity,
			displayQuantity,
			reserveQuantity,

	//		bool proactive,
			routingId,
			routingSubType,
			routingName,
			mnemonic,
			dma,
			imbalanceOnly,
			iso,
			aggressive,
			roundLot,
			false,//borrow
			washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
			oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
			resizeShortToBorrowed,
			noRedirect,
			closeOnly,
			resizeToClose,
//			proAts,
			roundLotPolicy,
			pegType,
			pegOffset,

			tifType,
			tifMillisecond,
			parentId,
			userId),
		m_underlier(NULL)
//		m_securitySameThreadAsAccount(false),
//		m_useSecurityNotification(useSecurityNotification),
//		m_securityUpdatedOrdinal(0),
//		m_securitySentOrdinal(0)
	{}
	UnderlierAlgorithm(const char*& fromString)://, bool useSecurityNotification):
		OrderAlgorithm(fromString),
		m_underlier(NULL)
//		m_securitySameThreadAsAccount(false),
//		m_useSecurityNotification(useSecurityNotification),
//		m_securityUpdatedOrdinal(0),
//		m_securitySentOrdinal(0)
	{}

	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL) override;
	virtual bool PreProcessUnderlierNotification(const Message* message, const Message* info = NULL){return false;}
//	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = NULL) const{return false;}
	virtual void OnUnderlierLoaded(){}
	virtual void NullifySecurity();
	const Underlier* m_underlier;

//	bool m_securitySameThreadAsAccount;
//	bool m_useSecurityNotification;
//	unsigned int m_securityUpdatedOrdinal;
//	unsigned int m_securitySentOrdinal;
};
#endif

enum OrderAlgorithmId : unsigned int
{
	OA_ORDER_REPLACER,

	OA_COUNT
};

class TU_API OrderReplacer : public SecurityAlgorithm
{
public:
	virtual bool isPriceValid() const{return true;}//!m_limitPrice.isZero();}
	virtual bool CanBeWashOrder() const{return false;}

	void AddOrderClientId(unsigned int orderClientId){m_clientIdSet.insert(orderClientId);}
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual unsigned int GetAlgorithmId() const{return OA_ORDER_REPLACER;}
//	typedef std::hash_set<Order*> OrderSet;
	virtual const char* GetAlgorithmName() const{return "Replacer";}
	virtual bool isQuantityValid() const;
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithmInThread();
	virtual unsigned int GetAlgorithmQuantity() const{return m_estimatedSize;}
	OrderReplacer& operator=(const OrderReplacer& other)
	{
		SecurityAlgorithm::operator=(other),
		m_orderMap = other.m_orderMap;
		m_orderMapEnd = m_orderMap.end();
		m_clientIdSet = other.m_clientIdSet;
		m_orderDestinationName = other.m_orderDestinationName;
		m_replaceSizeOffset = other.m_replaceSizeOffset;
		m_estimatedSize = other.m_estimatedSize;
		m_unexecutedShares = other.m_unexecutedShares;
		m_executedShares = other.m_executedShares;
		m_clientIdChronologicalToSend = other.m_clientIdChronologicalToSend;
		m_clientIdReplacing = other.m_clientIdReplacing;
		m_orderToReplaceClientIdNatively = other.m_orderToReplaceClientIdNatively;//Client Id of the Order that is to be replaced natively
		m_noReplaceIfRejected = other.m_noReplaceIfRejected;
		return *this;
	}
protected:
	OrderReplacer(const Position* position,
		unsigned int orderToReplaceClientId,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		unsigned int traderId,
		unsigned int sendId,
		unsigned int ocoId,
		unsigned int clientId,
//		unsigned int clientIdOriginal,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
		unsigned int destinationName,

		char side,

		unsigned char orderType,
		unsigned short userOrderType,//usually should be 0
		const char* userOrderInfo,//usually should be NULL
		const Price& limitPrice,

		const Price& discretionaryPrice,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const Price& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

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
		bool noReplaceIfRejected,
		bool dma,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		bool resizeShortToBorrowed,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
//		bool proAts,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool preBorrow,
		const Price& preBorrowPrice,

		unsigned char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,
		const unsigned __int64& userId,
		bool nativeReplace = false);
	OrderReplacer(const char*& fromString);
	OrderReplacer(const OrderReplacer& other):
		SecurityAlgorithm(other),
		m_orderMap(other.m_orderMap),
		m_orderMapEnd(m_orderMap.end()),
		m_clientIdSet(other.m_clientIdSet),
		m_orderDestinationName(other.m_orderDestinationName),
		m_replaceSizeOffset(other.m_replaceSizeOffset),
		m_estimatedSize(other.m_estimatedSize),
		m_unexecutedShares(other.m_unexecutedShares),
		m_executedShares(other.m_executedShares),
		m_clientIdChronologicalToSend(other.m_clientIdChronologicalToSend),
		m_clientIdReplacing(other.m_clientIdReplacing),
		m_orderToReplaceClientIdNatively(other.m_orderToReplaceClientIdNatively),
		m_noReplaceIfRejected(other.m_noReplaceIfRejected)
	{
	}
	void SendReplacement();
	virtual void DoSendReplacement(){}
	virtual unsigned int GetNextClientId() const{return 0;}

	virtual void AllOrdersCanceled() override;//base in OrderAlgorithm
//	OrderSet m_orderSet;
	OrderCancelRejectMap m_orderMap;
	OrderCancelRejectMap::iterator m_orderMapEnd;
	UIntSet m_clientIdSet;
	unsigned int m_orderDestinationName;
	int m_replaceSizeOffset;
	unsigned int m_estimatedSize;
	unsigned int m_unexecutedShares;
	unsigned int m_executedShares;
	unsigned int m_clientIdChronologicalToSend;
	unsigned int m_clientIdReplacing;
	unsigned int m_orderToReplaceClientIdNatively;//Client Id of the Order that is to be replaced natively
	bool m_noReplaceIfRejected;
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

class TU_API TakionDll
{
public:
	virtual ~TakionDll()
	{
		DoUnload();
	}
	virtual bool Load();
	virtual bool Unload();
	virtual bool isCustomExtension() const{return false;}

	ApiGetString GetExtensionInfoFunction() const{return m_ExtensionInfoFunction;}
	ApiGetUInt64 GetExtensionVersionFunction() const{return m_ExtensionVersionFunction;}

	const char* CallExtensionInfoFunction() const{return m_ExtensionInfoFunction ? m_ExtensionInfoFunction() : "";}

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

	const unsigned __int64& GetExtensionVersionValue() const{return m_extensionVersion;}
protected:
	TakionDll(const char* absolutePath);
	TakionDll(const char* name, const char* path);
	virtual void Reset()
	{
		m_dllHandle = NULL;
		m_ExtensionInfoFunction = NULL;
		m_ExtensionVersionFunction = NULL;
	}
	virtual void ResetValues()
	{
		m_extensionVersion = 0;
	}
	virtual bool DoLoad();
	bool DoUnload();
	void Canonicalize();

	HMODULE m_dllHandle;

	ApiGetString m_ExtensionInfoFunction;
	ApiGetUInt64 m_ExtensionVersionFunction;

	std::string m_absolutePath;
	char m_path[MAX_PATH];
	std::string m_name;
	std::string m_originalName;
	std::string m_originalPath;
	DWORD m_loadErrorCode;
	std::string m_loadErrorMessage;
	DWORD m_unloadErrorCode;
	std::string m_unloadErrorMessage;
	unsigned char m_error;

	unsigned int m_loadTime;
	unsigned int m_unloadTime;

	unsigned __int64 m_extensionVersion;
};

class TU_API BaseDll : public TakionDll
{
public:
//	virtual ~BaseDll(){DoUnload();}
//	virtual unsigned int GetValidExtensionCode() const = 0;

//	ApiGetString GetExtensionInfoFunction() const{return m_ExtensionInfoFunction;}
//	ApiGetUInt64 GetExtensionVersionFunction() const{return m_ExtensionVersionFunction;}
	ApiGetUInt64 GetUtilsVersionFunction() const{return m_UtilsVersionFunction;}
	ApiGetUInt64 GetUtilsHeaderVersionFunction() const{return m_UtilsHeaderVersionFunction;}
	ApiGetUInt64 GetTakionUtilsVersionFunction() const{return m_TakionUtilsVersionFunction;}
	ApiGetUInt64 GetTakionUtilsHeaderVersionFunction() const{return m_TakionUtilsHeaderVersionFunction;}
	ApiGetUInt64 GetUtilsGuiVersionFunction() const{return m_UtilsGuiVersionFunction;}
	ApiGetUInt64 GetUtilsGuiHeaderVersionFunction() const{return m_UtilsGuiHeaderVersionFunction;}
	ApiGetUInt64 GetTakionGuiVersionFunction() const{return m_TakionGuiVersionFunction;}
	ApiGetUInt64 GetTakionGuiHeaderVersionFunction() const{return m_TakionGuiHeaderVersionFunction;}
	ApiGetUInt64 GetTakionDataVersionFunction() const{return m_TakionDataVersionFunction;}
	ApiGetUInt64 GetTakionDataHeaderVersionFunction() const{return m_TakionDataHeaderVersionFunction;}

	ApiGetUInt64 GetTakionLogVersionFunction() const{return m_TakionLogVersionFunction;}
	ApiGetUInt64 GetTakionLogHeaderVersionFunction() const{return m_TakionLogHeaderVersionFunction;}
	ApiGetUInt64 GetObserverVersionFunction() const{return m_ObserverVersionFunction;}
	ApiGetUInt64 GetObserverHeaderVersionFunction() const{return m_ObserverHeaderVersionFunction;}
	ApiGetUInt64 GetReceiverVersionFunction() const{return m_ReceiverVersionFunction;}
	ApiGetUInt64 GetReceiverHeaderVersionFunction() const{return m_ReceiverHeaderVersionFunction;}
	ApiIs GetExtensionDebugFunction() const{return m_ExtensionDebugFunction;}

	ApiGetString GetExtensionDescriptionFunction() const{return m_ExtensionDescriptionFunction;}

//	const char* CallExtensionInfoFunction() const{return m_ExtensionInfoFunction ? m_ExtensionInfoFunction() : "";}

	const unsigned __int64& GetUtilsVersionValue() const{return m_utilsVersion;}
	const unsigned __int64& GetUtilsHeaderVersionValue() const{return m_utilsHeaderVersion;}
	const unsigned __int64& GetTakionUtilsVersionValue() const{return m_takionUtilsVersion;}
	const unsigned __int64& GetTakionUtilsHeaderVersionValue() const{return m_takionUtilsHeaderVersion;}
	const unsigned __int64& GetUtilsGuiVersionValue() const{return m_utilsGuiVersion;}
	const unsigned __int64& GetUtilsGuiHeaderVersionValue() const{return m_utilsGuiHeaderVersion;}
	const unsigned __int64& GetTakionGuiVersionValue() const{return m_guiVersion;}
	const unsigned __int64& GetTakionGuiHeaderVersionValue() const{return m_guiHeaderVersion;}
	const unsigned __int64& GetTakionDataVersionValue() const{return m_dataVersion;}
	const unsigned __int64& GetTakionDataHeaderVersionValue() const{return m_dataHeaderVersion;}
	const unsigned __int64& GetTakionLogVersionValue() const{return m_takionLogVersion;}
	const unsigned __int64& GetTakionLogHeaderVersionValue() const{return m_takionLogHeaderVersion;}
	const unsigned __int64& GetObserverVersionValue() const{return m_observerVersion;}
	const unsigned __int64& GetObserverHeaderVersionValue() const{return m_observerHeaderVersion;}
	const unsigned __int64& GetReceiverVersionValue() const{return m_receiverVersion;}
	const unsigned __int64& GetReceiverHeaderVersionValue() const{return m_receiverHeaderVersion;}

	const unsigned __int64& GetLoaderUtilsHeaderVersionValue() const{return m_loaderUtilsHeaderVersion;}
	const unsigned __int64& GetLoaderTakionUtilsHeaderVersionValue() const{return m_loaderTakionUtilsHeaderVersion;}
	const unsigned __int64& GetLoaderGuiHeaderVersionValue() const{return m_loaderGuiHeaderVersion;}
	const unsigned __int64& GetLoaderUtilsGuiHeaderVersionValue() const{return m_loaderUtilsGuiHeaderVersion;}
	const unsigned __int64& GetLoaderDataHeaderVersionValue() const{return m_loaderDataHeaderVersion;}
	const unsigned __int64& GetLoaderLogHeaderVersionValue() const{return m_loaderLogHeaderVersion;}
	const unsigned __int64& GetLoaderObserverHeaderVersionValue() const{return m_loaderObserverHeaderVersion;}

	const char& isDebug() const{return m_extensionDebug;}//1 - yes; -1 - no; 0 - unknown (the isExtensionDebug function is missing from the Extension DLL).
	const bool& isHeadersCompatible() const{return m_headersCompatible;}
	void UpdateHeaderCompatible()
	{
		m_headersCompatible = (!m_UtilsHeaderVersionFunction || m_utilsHeaderVersion == m_loaderUtilsHeaderVersion)
			&& (!m_TakionUtilsHeaderVersionFunction || m_takionUtilsHeaderVersion == m_loaderTakionUtilsHeaderVersion)
			&& (!m_TakionGuiHeaderVersionFunction || m_guiHeaderVersion == m_loaderGuiHeaderVersion)
			&& (!m_TakionDataHeaderVersionFunction || m_dataHeaderVersion == m_loaderDataHeaderVersion)
			&& (!m_TakionLogHeaderVersionFunction || m_takionLogHeaderVersion == m_loaderLogHeaderVersion)
			&& (!m_ObserverHeaderVersionFunction || m_observerHeaderVersion == m_loaderObserverHeaderVersion)
			&& (!m_UtilsGuiHeaderVersionFunction || m_utilsGuiHeaderVersion == m_loaderUtilsGuiHeaderVersion);
	}

	const std::string& GetExtensionDescriptionValue() const{return m_extensionDescription;}
protected:
	BaseDll(const char* absolutePath,
		const unsigned __int64& loaderUtilsHeaderVersion,
		const unsigned __int64& loaderTakionUtilsHeaderVersion,
		const unsigned __int64& loaderGuiHeaderVersion,
		const unsigned __int64& loaderUtilsGuiHeaderVersion,
		const unsigned __int64& loaderDataHeaderVersion,
		const unsigned __int64& loaderLogHeaderVersion,
		const unsigned __int64& loaderObserverHeaderVersion);
	BaseDll(const char* name, const char* path,
		const unsigned __int64& loaderUtilsHeaderVersion,
		const unsigned __int64& loaderTakionUtilsHeaderVersion,
		const unsigned __int64& loaderGuiHeaderVersion,
		const unsigned __int64& loaderUtilsGuiHeaderVersion,
		const unsigned __int64& loaderDataHeaderVersion,
		const unsigned __int64& loaderLogHeaderVersion,
		const unsigned __int64& loaderObserverHeaderVersion);
	virtual bool DoLoad() override;

	virtual void Reset() override;
	virtual void ResetValues() override;

//	ApiGetString m_ExtensionInfoFunction;
//	ApiGetUInt64 m_ExtensionVersionFunction;
	ApiGetUInt64 m_UtilsVersionFunction;
	ApiGetUInt64 m_UtilsHeaderVersionFunction;
	ApiGetUInt64 m_TakionUtilsVersionFunction;
	ApiGetUInt64 m_TakionUtilsHeaderVersionFunction;
	ApiGetUInt64 m_UtilsGuiVersionFunction;
	ApiGetUInt64 m_UtilsGuiHeaderVersionFunction;
	ApiGetUInt64 m_TakionGuiVersionFunction;
	ApiGetUInt64 m_TakionGuiHeaderVersionFunction;
	ApiGetUInt64 m_TakionDataVersionFunction;
	ApiGetUInt64 m_TakionDataHeaderVersionFunction;
	ApiGetUInt64 m_TakionLogVersionFunction;
	ApiGetUInt64 m_TakionLogHeaderVersionFunction;
	ApiGetUInt64 m_ObserverVersionFunction;
	ApiGetUInt64 m_ObserverHeaderVersionFunction;
	ApiGetUInt64 m_ReceiverVersionFunction;
	ApiGetUInt64 m_ReceiverHeaderVersionFunction;
	ApiIs m_ExtensionDebugFunction;
	ApiGetString m_ExtensionDescriptionFunction;

	unsigned __int64 m_utilsVersion;
	unsigned __int64 m_utilsHeaderVersion;
	unsigned __int64 m_takionUtilsVersion;
	unsigned __int64 m_takionUtilsHeaderVersion;
	unsigned __int64 m_utilsGuiVersion;
	unsigned __int64 m_utilsGuiHeaderVersion;
	unsigned __int64 m_guiVersion;
	unsigned __int64 m_guiHeaderVersion;
	unsigned __int64 m_dataVersion;
	unsigned __int64 m_dataHeaderVersion;
	unsigned __int64 m_takionLogVersion;
	unsigned __int64 m_takionLogHeaderVersion;
	unsigned __int64 m_observerVersion;
	unsigned __int64 m_observerHeaderVersion;
	unsigned __int64 m_receiverVersion;
	unsigned __int64 m_receiverHeaderVersion;

	unsigned __int64 m_loaderUtilsHeaderVersion;
	unsigned __int64 m_loaderTakionUtilsHeaderVersion;
	unsigned __int64 m_loaderGuiHeaderVersion;
	unsigned __int64 m_loaderUtilsGuiHeaderVersion;
	unsigned __int64 m_loaderDataHeaderVersion;
	unsigned __int64 m_loaderLogHeaderVersion;
	unsigned __int64 m_loaderObserverHeaderVersion;

	bool m_headersCompatible;

	char m_extensionDebug;

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
	BaseExtensionDll(const char* absolutePath,
		const unsigned __int64& loaderUtilsHeaderVersion,
		const unsigned __int64& loaderTakionUtilsHeaderVersion,
		const unsigned __int64& loaderGuiHeaderVersion,
		const unsigned __int64& loaderUtilsGuiHeaderVersion,
		const unsigned __int64& loaderDataHeaderVersion,
		const unsigned __int64& loaderLogHeaderVersion,
		const unsigned __int64& loaderObserverHeaderVersion);
	BaseExtensionDll(const char* name, const char* path,
		const unsigned __int64& loaderUtilsHeaderVersion,
		const unsigned __int64& loaderTakionUtilsHeaderVersion,
		const unsigned __int64& loaderGuiHeaderVersion,
		const unsigned __int64& loaderUtilsGuiHeaderVersion,
		const unsigned __int64& loaderDataHeaderVersion,
		const unsigned __int64& loaderLogHeaderVersion,
		const unsigned __int64& loaderObserverHeaderVersion);
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


enum TakionEmailSecurity
{
    Takion_Secur_Normal,    // on normal port (default SMTP:  25, POP3: 110, IMAP: 143) unencrypted
    Takion_Secur_SSL,       // on secure port (default SMTP: 465, POP3: 995, IMAP: 993) using SSL
    Takion_Secur_TLS_opt,   // on normal port (default SMTP:  25, POP3: 110, IMAP: 143) using TLS if possible
    Takion_Secur_TLS_force, // on normal port (default SMTP: 587, POP3: 110, IMAP: 143) demands TLS otherwise fails
};

class TU_API EmailDll : public BaseExtensionDll//, public Observable
{
public:
	EmailDll(const char* absolutePath);
	EmailDll(const char* name, const char* path);
	virtual ~EmailDll();
	virtual bool Unload();
	virtual bool Load();

	ApiVoidPtr GetEmailSetLogFileFunction() const{return m_EmailSetLogFileFunction;}
	void SetLogFile(void* logFileHandle) const{if(m_EmailSetLogFileFunction)m_EmailSetLogFileFunction(logFileHandle);}

	ApiCreateEmail GetCreateEmailFunction() const{return m_CreateEmailFunction;}
	void* CreateEmail(const char* serverName,//"Smtp.live.com";//hotmail; "Smtp.gmail.com"
		unsigned short serverPort,
		bool allowInvalidCertificate,
		unsigned int eSecurity,//TakionEmailSecurity
		const char* fromEmailAddress,
		const char* fromUser,
		const char* fromPassword,
		const char* fromName,//Can be NULL
		const char* subject,//Can be NULL
		const char* contents,//Can be NULL
		const char* replyTo,//Can be NULL
		const char* returnPath,//Can be NULL
		const char* organization,//Can be NULL
		const char* userAgent)//Can be NULL
	{
		return m_CreateEmailFunction ?
			m_CreateEmailFunction(serverName,
				serverPort,
				allowInvalidCertificate,
				eSecurity,//TakionEmailSecurity
				fromEmailAddress,
				fromUser,
				fromPassword,
				fromName,//Can be NULL
				subject,//Can be NULL
				contents,//Can be NULL
				replyTo,//Can be NULL
				returnPath,//Can be NULL
				organization,//Can be NULL
				userAgent):
			NULL;
	}
	ApiVoidPtrCharPtr2 GetEmailAddToFunction() const{return m_EmailAddToFunction;}
	void EmailAddTo(void* email, const char* name, const char* address){if(m_EmailAddToFunction)m_EmailAddToFunction(email, name, address);}

	ApiVoidPtrCharPtr2 GetEmailAddCcFunction() const{return m_EmailAddCcFunction;}
	void EmailAddCc(void* email, const char* name, const char* address){if(m_EmailAddCcFunction)m_EmailAddCcFunction(email, name, address);}

	ApiVoidPtrCharPtr2 GetEmailAddBccFunction() const{return m_EmailAddBccFunction;}
	void EmailAddBcc(void* email, const char* name, const char* address){if(m_EmailAddBccFunction)m_EmailAddBccFunction(email, name, address);}

	ApiVoidPtrCharPtr3 GetEmailAddAttachmentFunction() const{return m_EmailAddAttachmentFunction;}
	void EmailAddAttachment(void* email, const char* path, const char* mimeType, const char* fileName){if(m_EmailAddAttachmentFunction)m_EmailAddAttachmentFunction(email, path, mimeType, fileName);}

	ApiVoidPtrCharPtr3 GetEmailAddEmbeddedObjectFunction() const{return m_EmailAddEmbeddedObjectFunction;}
	void EmailAddEmbeddedObject(void* email, const char* path, const char* mimeType, const char* CID){if(m_EmailAddEmbeddedObjectFunction)m_EmailAddEmbeddedObjectFunction(email, path, mimeType, CID);}

	ApiVoidPtr GetEmailSendFunction() const{return m_EmailSend;}
	void SendEmail(void* email){if(m_EmailSend)m_EmailSend(email);}

	ApiVoidPtr GetEmailDestroyFunction() const{return m_EmailDestroy;}
	void DestroyEmail(void* email){if(m_EmailDestroy)m_EmailDestroy(email);}

//	bool DoIdle(LONG count) const{return m_EmailDoIdle && m_EmailDoIdle(count);}

//	void AdjustToChangedScreen(int dx, int dy) const{if(m_EmailAdjustToChangedScreen)m_EmailAdjustToChangedScreen(dx, dy);}

protected:
	virtual bool DoLoad();
	virtual void Reset()
	{
		BaseExtensionDll::Reset();
		NullifyFunctions();
	}
	void NullifyFunctions();
	bool AdditionalUnload();
	ApiVoidPtr m_EmailSetLogFileFunction;
	ApiCreateEmail m_CreateEmailFunction;
	ApiVoidPtrCharPtr2 m_EmailAddToFunction;
	ApiVoidPtrCharPtr2 m_EmailAddCcFunction;
	ApiVoidPtrCharPtr2 m_EmailAddBccFunction;
	ApiVoidPtrCharPtr3 m_EmailAddAttachmentFunction;
	ApiVoidPtrCharPtr3 m_EmailAddEmbeddedObjectFunction;
	ApiVoidPtr m_EmailSend;
	ApiVoidPtr m_EmailDestroy;
/*
//typedef void (WINAPI* ApiVoidPtr)(void* voidPtr);
typedef void (WINAPI* ApiVoidPtrCharPtr2)(void* email, const char* name, const char* address);
typedef void (WINAPI* ApiVoidPtrCharPtr3)(void* email, const char* path, const char* mimeType, const char* fileName);

//	ApiIsLong m_EmailDoIdle;

void WINAPI TE_AddTo(void* email, const char* toName, const char* toEmailAddress);
void WINAPI TE_AddCc(void* email, const char* ccName, const char* ccEmailAddress);
void WINAPI TE_AddBcc(void* email, const char* bccName, const char* bccEmailAddress);

void WINAPI TE_AddAttachment(void* email, const char* path, const char* mimeType = "", const char* fileName = "");
void WINAPI TE_AddEmbeddedObject(void* email, const char* path, const char* mimeType = "", const char* CID = "");

void WINAPI TE_SendEmail(void* email);
void WINAPI TE_DestroyEmail(void* email);//Do not call if TE_SendEmail was called
*/
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
	ApiUInt GetExtensionCommandWindowRemovedFunction() const{return m_ExtensionCommandWindowRemovedFunction;}
	ApiVoid GetExtensionLayoutChangedFunction() const{return m_ExtensionLayoutChangedFunction;}
	ApiSymbolEntered GetExtensionSymbolEnteredInMmBoxFunction() const{return m_ExtensionSymbolEnteredInMmBoxFunction;}
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

	ApiVoid GetExtensionNewSecondStartedFunction() const{return m_ExtensionNewSecondStartedFunction;}
	ApiVoid GetExtensionLineDoubleClickedFunction() const{return m_ExtensionLineDoubleClickedFunction;}
	ApiVoid GetExtensionNextDayStartedFunction() const{return m_ExtensionNextDayStartedFunction;}

	ApiIs GetExtensionIsStartedFunction() const{return m_ExtensionIsStartedFunction;}
	ApiBool GetExtensionStartFunction() const{return m_ExtensionStartFunction;}

	ApiHwndCharPtr GetExtensionMarketSorterNotifyAddedFunction() const{return m_ExtensionMarketSorterNotifyAdded;}
	ApiHwndCharPtrSecurity GetExtensionMarketSorterContentsFunction() const{return m_ExtensionMarketSorterContents;}
	ApiHwndCharPtr GetExtensionMarketSorterContentsDoneFunction() const{return m_ExtensionMarketSorterContentsDone;}
	ApiHwndCharPtr GetExtensionMarketSorterNotifyRemovedFunction() const{return m_ExtensionMarketSorterNotifyRemoved;}
	ApiHwndCharPtr2 GetExtensionMarketSorterNotifyPrefixChangedFunction() const{return m_ExtensionMarketSorterNotifyPrefixChanged;}
	ApiHwndCharPtrSecurityBool GetExtensionNotifyMarketSorterSymbolFunction() const{return m_ExtensionNotifyMarketSorterSymbol;}
	ApiHwndCharPtr GetExtensionMarketSorterNotifyAllRowsRemovedFunction() const{return m_ExtensionMarketSorterNotifyAllRowsRemoved;}

	void CallKeyStrokeAndCommand(unsigned char ascii, unsigned char modifier, bool repeat, const char* commandName, unsigned int commandExtensionCode, unsigned int commandUserExtensionCode) const{if(m_ExtensionKeyStrokeAndCommandFunction)m_ExtensionKeyStrokeAndCommandFunction(ascii, modifier, repeat, commandName, commandExtensionCode, commandUserExtensionCode);}
	void CallCommandWindowRemoved(unsigned int ordinal) const{if(m_ExtensionCommandWindowRemovedFunction)m_ExtensionCommandWindowRemovedFunction(ordinal);}
	void CallLayoutChanged() const{if(m_ExtensionLayoutChangedFunction)m_ExtensionLayoutChangedFunction();}
	void CallSymbolEnteredInMmBox(const char* symbol, unsigned char securityType, bool valid, bool fromKeyboard, unsigned int ordinal) const{if(m_ExtensionSymbolEnteredInMmBoxFunction)m_ExtensionSymbolEnteredInMmBoxFunction(symbol, securityType, valid, fromKeyboard, ordinal);}
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
	const char* CallGetLayoutFilePath() const{return m_ExtensionGetLayoutFilePath ? m_ExtensionGetLayoutFilePath() : NULL;}
	void CallMessageReportFunction(unsigned char connectionType, const Message* message, bool outgoing) const{if(m_ExtensionMessageReport)m_ExtensionMessageReport(connectionType, message, outgoing);}
	void CallNewSecondStarted() const{if(m_ExtensionNewSecondStartedFunction)m_ExtensionNewSecondStartedFunction();}
	void CallLineDoubleClicked() const{if(m_ExtensionLineDoubleClickedFunction)m_ExtensionLineDoubleClickedFunction();}
	void CallNextDayStarted() const{if(m_ExtensionNextDayStartedFunction)m_ExtensionNextDayStartedFunction();}

	bool CallExtensionIsStarted() const{return !m_ExtensionIsStartedFunction || m_ExtensionIsStartedFunction();}
	bool CallExtensionIsStopped() const{return !m_ExtensionIsStartedFunction || !m_ExtensionIsStartedFunction();}
	void CallExtensionStart(bool start) const{if(m_ExtensionStartFunction)m_ExtensionStartFunction(start);}

	void CallMarketSorterNotifyAdded(HWND hwnd, const char* prefix) const{if(m_ExtensionMarketSorterNotifyAdded)m_ExtensionMarketSorterNotifyAdded(hwnd, prefix);}
	void CallMarketSorterContents(HWND hwnd, const char* prefix, const Security* security) const{if(m_ExtensionMarketSorterContents)m_ExtensionMarketSorterContents(hwnd, prefix, security);}
	void CallMarketSorterContentsDone(HWND hwnd, const char* prefix) const{if(m_ExtensionMarketSorterContentsDone)m_ExtensionMarketSorterContentsDone(hwnd, prefix);}
	void CallMarketSorterNotifyRemoved(HWND hwnd, const char* prefix) const{if(m_ExtensionMarketSorterNotifyRemoved)m_ExtensionMarketSorterNotifyRemoved(hwnd, prefix);}
	void CallMarketSorterNotifyPrefixChanged(HWND hwnd, const char* oldPrefix, const char* prefix) const{if(m_ExtensionMarketSorterNotifyPrefixChanged)m_ExtensionMarketSorterNotifyPrefixChanged(hwnd, oldPrefix, prefix);}
	void CallNotifyMarketSorterSymbol(HWND hwnd, const char* prefix, const Security* security, const bool added) const{if(m_ExtensionNotifyMarketSorterSymbol)m_ExtensionNotifyMarketSorterSymbol(hwnd, prefix, security, added);}
	void CallMarketSorterNotifyAllRowsRemoved(HWND hwnd, const char* prefix) const{if(m_ExtensionMarketSorterNotifyAllRowsRemoved)m_ExtensionMarketSorterNotifyAllRowsRemoved(hwnd, prefix);}
protected:
	ExtensionDll(const char* absolutePath,
		const unsigned __int64& loaderUtilsHeaderVersion,
		const unsigned __int64& loaderTakionUtilsHeaderVersion,
		const unsigned __int64& loaderGuiHeaderVersion,
		const unsigned __int64& loaderUtilsGuiHeaderVersion,
		const unsigned __int64& loaderDataHeaderVersion,
		const unsigned __int64& loaderLogHeaderVersion,
		const unsigned __int64& loaderObserverHeaderVersion):
		BaseExtensionDll(absolutePath,
			loaderUtilsHeaderVersion,
			loaderTakionUtilsHeaderVersion,
			loaderGuiHeaderVersion,
			loaderUtilsGuiHeaderVersion,
			loaderDataHeaderVersion,
			loaderLogHeaderVersion,
			loaderObserverHeaderVersion)
	{
		AdditionalReset();
		AdditionalResetValues();
	}

	ExtensionDll(const char* name, const char* path,
		const unsigned __int64& loaderUtilsHeaderVersion,
		const unsigned __int64& loaderTakionUtilsHeaderVersion,
		const unsigned __int64& loaderGuiHeaderVersion,
		const unsigned __int64& loaderUtilsGuiHeaderVersion,
		const unsigned __int64& loaderDataHeaderVersion,
		const unsigned __int64& loaderLogHeaderVersion,
		const unsigned __int64& loaderObserverHeaderVersion):
		BaseExtensionDll(name, path,
			loaderUtilsHeaderVersion,
			loaderTakionUtilsHeaderVersion,
			loaderGuiHeaderVersion,
			loaderUtilsGuiHeaderVersion,
			loaderDataHeaderVersion,
			loaderLogHeaderVersion,
			loaderObserverHeaderVersion)
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
		m_ExtensionCommandWindowRemovedFunction = NULL;
		m_ExtensionLayoutChangedFunction = NULL;
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
		m_ExtensionNewSecondStartedFunction = NULL;
		m_ExtensionLineDoubleClickedFunction = NULL;
		m_ExtensionNextDayStartedFunction = NULL;

		m_ExtensionIsStartedFunction = NULL;
		m_ExtensionStartFunction = NULL;

		m_ExtensionMarketSorterNotifyAdded = NULL;
		m_ExtensionMarketSorterContents = NULL;
		m_ExtensionMarketSorterContentsDone = NULL;
		m_ExtensionMarketSorterNotifyRemoved = NULL;
		m_ExtensionMarketSorterNotifyPrefixChanged = NULL;
		m_ExtensionNotifyMarketSorterSymbol = NULL;
		m_ExtensionMarketSorterNotifyAllRowsRemoved = NULL;
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
	ApiUInt m_ExtensionCommandWindowRemovedFunction;
	ApiVoid m_ExtensionLayoutChangedFunction;
	ApiSymbolEntered m_ExtensionSymbolEnteredInMmBoxFunction;
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
	ApiVoid m_ExtensionNewSecondStartedFunction;
	ApiVoid m_ExtensionLineDoubleClickedFunction;
	ApiVoid m_ExtensionNextDayStartedFunction;

	ApiIs m_ExtensionIsStartedFunction;
	ApiBool m_ExtensionStartFunction;

	ApiHwndCharPtr m_ExtensionMarketSorterNotifyAdded;
	ApiHwndCharPtrSecurity m_ExtensionMarketSorterContents;
	ApiHwndCharPtr m_ExtensionMarketSorterContentsDone;
	ApiHwndCharPtr m_ExtensionMarketSorterNotifyRemoved;
	ApiHwndCharPtr2 m_ExtensionMarketSorterNotifyPrefixChanged;
	ApiHwndCharPtrSecurityBool m_ExtensionNotifyMarketSorterSymbol;
	ApiHwndCharPtr m_ExtensionMarketSorterNotifyAllRowsRemoved;

	unsigned int m_extensionCode;
};

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef FIRM_VALUES
FirmPosition* WINAPI TU_GetNextFirmPosition(TakionIterator* iterator);
//For AccountAggregator::CreateSupervisorUntradeablSymbolIterator
const unsigned __int64* WINAPI TU_GetNextUntradeableCount(TakionIterator* iterator, unsigned int* count = NULL);
//For AccountAggregator::CreateUntradeablSymbolIterator
const unsigned __int64* WINAPI TU_GetNextUntradeableStatus(TakionIterator* iterator, unsigned char* status = NULL);
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

unsigned int WINAPI TU_GetVenueFromQuote(const Quote& quote);

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

void WINAPI TU_CalculateCloseAndOpenTradeSize(const unsigned int shares, const bool buy, const int positionSize, unsigned int& closePositionSize, unsigned int& openPositionSize);

#ifndef TAKION_NO_OPTIONS
//Security* WINAPI TU_GetNextOption(TakionIterator* optionIterator);
Security* WINAPI TU_GetNextUnderlierOption(TakionIterator* iterator);
unsigned __int64 WINAPI TU_ParseOptionBlockWithSuffixSeparate(const char* symbol, unsigned __int64& rootSymbol, unsigned __int64& underlierSymbol, unsigned __int64& optionKey, unsigned char& suffix);
unsigned __int64 WINAPI TU_ParseOptionBlock(const char* symbol, unsigned __int64& rootSymbol, unsigned char& error);
Position* WINAPI TU_GetNextOptionPosition(TakionIterator* iterator);
#endif

bool WINAPI TU_GetIsoSnapshot(bool bid, TakionIterator* iterator, const Price& orderPrice, std::string& info, Price& topPrice, bool stopIfOrderIsNotInside);//should be called only when the security is locked for info
bool WINAPI TU_GetTopLevelInfoAsString(TakionIterator* iterator, const Price& orderPrice, std::string& info, Price& topPrice);//should be called only when the security is locked for info
void WINAPI TU_GetMmidSizeAsString(const Quote* quote, std::string& info);//should be called only when the security is locked for info
const char* WINAPI TU_GetAlertTypeName(const unsigned char alertType);
const char* WINAPI TU_GetAlertTypeTooltip(const unsigned char alertType);

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
void WINAPI TU_MultiBookIteratorUpdateEntitlements(TakionIterator* multiBookIterator);
//void WINAPI TU_MultiBookIteratorSetExtensionEntitlements(TakionIterator* multiBookIterator, unsigned int extEntitlements);
const Quote* WINAPI TU_MultiBookIteratorGetNextQuoteAndBook(TakionIterator* multiBookIterator, unsigned char& bookId);

bool WINAPI TU_MultiBookIteratorHasSizeForPrice(TakionIterator* multiBookIterator, const Price& price, const unsigned int& size, const bool& includePrice);
unsigned int WINAPI TU_MultiBookIteratorGetSizeForSpecificPrice(TakionIterator* multiBookIterator, const Price& price);

TakionIterator* WINAPI TU_CreateMmAggregatedIterator(bool bid, bool sortBySize, bool hideSlowQuotes, const unsigned int* lineCount, unsigned int exchangeMask, unsigned int attributionMask, const unsigned char* bookSortRank, const Security* stock = NULL, bool oddSize = false);
//const Quote* WINAPI TU_GetMmAggregatedNextQuote(TakionIterator* mmAggregatedIterator);
void WINAPI TU_MmAggregatedIteratorSetSecurity(TakionIterator* mmAggregatedIterator, const Security* stock);
bool WINAPI TU_MmAggregatedIteratorSecurityRefreshed(TakionIterator* mmAggregatedIterator, const Security* stock);
bool WINAPI TU_MmAggregatedIteratorSetBookFilter(TakionIterator* mmAggregatedIterator, const unsigned int* lineCount, unsigned int exchangeMask);
bool WINAPI TU_MmAggregatedIteratorSetAttributionMask(TakionIterator* multiBookIterator, unsigned int attributionMask);
bool WINAPI TU_MmAggregatedIteratorSetSortBySize(TakionIterator* mmAggregatedIterator, bool sortBySize);
bool WINAPI TU_MmAggregatedIteratorSetHideSlowQuotes(TakionIterator* multiBookIterator, bool hide);
bool WINAPI TU_MmAggregatedIteratorSetBookSortRank(TakionIterator* mmAggregatedIterator, const unsigned char* bookSortRank);
void WINAPI TU_MmAggregatedIteratorUpdateEntitlements(TakionIterator* mmAggregatedIterator);
//void WINAPI TU_MmAggregatedIteratorSetExtensionEntitlements(TakionIterator* mmAggregatedIterator, unsigned int extEntitlements);

TakionIterator* WINAPI TU_CreateMultiPrintIterator(unsigned int printFilter = AllMarketCenterFilter, bool printShowOddLot = true, unsigned int bookFilter = ((1 << ECNBOOK_COUNT) - 1) & ~(1 << BOOK_LEVEL2), bool ecnExecShowOddLot = true, const Security* stock = NULL);
const Trade* WINAPI TU_GetMultiPrintNextTrade(TakionIterator* multiPrintIterator);
void WINAPI TU_MultiPrintIteratorSetSecurity(TakionIterator* multiPrintIterator, const Security* stock);
bool WINAPI TU_MultiPrintIteratorSetBookFilter(TakionIterator* multiPrintIterator, unsigned int bookFilter, bool ecnExecShowOddLot);
bool WINAPI TU_MultiPrintIteratorSetPrintFilter(TakionIterator* multiPrintIterator, unsigned int printFilter, bool printShowOddLot);
void WINAPI TU_MultiPrintIteratorUpdateAllEntitlements(TakionIterator* multiPrintIterator);
bool WINAPI TU_MultiPrintIteratorUpdateBookEntitlements(TakionIterator* multiPrintIterator);
bool WINAPI TU_MultiPrintIteratorUpdatePrintEntitlements(TakionIterator* multiPrintIterator);

unsigned short WINAPI TU_GetUserOrderTypeCount();
const std::string& WINAPI TU_GetUserOrderType(unsigned short i);
unsigned short WINAPI TU_AddUserOrderType(const char* orderTypeName);
void WINAPI TU_SetUserOrderType(unsigned short i, const char* orderString);
TakionIterator* WINAPI TU_CreateUserOrderTypeIterator();
const std::string* WINAPI TU_GetNextUserOrderType(TakionIterator* iterator);

TakionIterator* WINAPI TU_CreatePositionPendingOrderIterator(const Position* position, bool buy);
TakionIterator* WINAPI TU_CreatePositionBuyPendingOrderIterator(const Position* position);
TakionIterator* WINAPI TU_CreatePositionSellPendingOrderIterator(const Position* position);

TakionIterator* WINAPI TU_CreatePositionBuyQuoteOrderIterator(const Position* position);
TakionIterator* WINAPI TU_CreatePositionSellQuoteOrderIterator(const Position* position);

const Order* WINAPI TU_GetNextPositionPendingOrder(TakionIterator* iterator, bool buy);
const Order* WINAPI TU_GetNextPositionBuyPendingOrder(TakionIterator* iterator);
const Order* WINAPI TU_GetNextPositionSellPendingOrder(TakionIterator* iterator);

unsigned int WINAPI TU_GetExpandedEntitlementBookFilter();
unsigned int WINAPI TU_GetAggregatedEntitlementBookFilter();

bool WINAPI TU_IsBookEntitled(unsigned char id, bool aggregated);
bool WINAPI TU_IsBookEntitledByFlag(unsigned int flag, bool aggregated);
bool WINAPI TU_IsAggregatedBookEntitled(unsigned char id);
bool WINAPI TU_IsExpandedBookEntitled(unsigned char id);
bool WINAPI TU_IsAggregatedBookEntitledByFlag(unsigned int flag);
bool WINAPI TU_IsExpandedBookEntitledByFlag(unsigned int flag);
unsigned int WINAPI TU_GetBookEntitlementLineCount(unsigned char id);
bool WINAPI TU_IsLevel1QuotesEntitled(bool nasdaq);
bool WINAPI TU_IsPrintsEntitled(bool nasdaq);
/*
unsigned int WINAPI TU_GetExtensionExpandedEntitlementBookFilter();
unsigned int WINAPI TU_GetExtensionAggregatedEntitlementBookFilter();
bool WINAPI TU_IsExtensionBookEntitled(unsigned char id, bool aggregated);
bool WINAPI TU_IsExtensionAggregatedBookEntitled(unsigned char id);
bool WINAPI TU_IsExtensionExpandedBookEntitled(unsigned char id);
unsigned int WINAPI TU_GetExtensionBookEntitlementLineCount(unsigned char id);
*/
bool WINAPI TU_IsExtensionLevel1QuotesEntitled(bool nasdaq);
bool WINAPI TU_IsExtensionPrintsEntitled(bool nasdaq);

#ifndef TAKION_NO_OPTIONS
bool WINAPI TU_IsOptionsEntitled();
bool WINAPI TU_IsExtensionOptionsEntitled();
#endif

//bool WINAPI TU_IsExtensionL2();

unsigned int WINAPI TU_GetExtensionEntitlementBookFilter();
bool WINAPI TU_IsExtensionBookEntitled(const unsigned char& id);
bool WINAPI TU_IsExtensionBookEntitledByFlag(const unsigned int& flag);

void WINAPI TU_SetMainWnd(HWND hwnd);
bool WINAPI TU_ExecuteCommand(const char* commandName, bool post);

enum InventoryMode : unsigned char
{
	IM_NON_INVENTORY,
	IM_INVENTORY,
	IM_DEFAULT,//Same as in the MainBar

	IM_Count
};

bool WINAPI TU_ExecuteCommandForSecurity(const char* commandName,
	bool post,
	const Security* security,
	Account* account,
	const Position* position,
	unsigned int sendId,
	unsigned int tierSize,
	int count,
	bool closeout,
	bool closeOnly,
	bool passiveOnly,
	bool blockAggressiveOrders,
	unsigned char inventoryMode);

const std::string& WINAPI TU_GetTriggerTypeLabel(unsigned char triggerType);
const std::string& WINAPI TU_GetTriggerTypeStr(unsigned char triggerType);
const std::string& WINAPI TU_GetTriggerTypeDescription(unsigned char triggerType);

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
	PB_OPEN_PRICE,
	PB_MH_HIGH,
	PB_MH_LOW,
	PB_AVG_POSITION_COST,
	PB_CUSTOM,
	PB_IMB_EX_NEAR,

	PB_Count
};

void WINAPI TU_GetBasePrice(unsigned char priceBase, Price& price, const Security* security, const Price& positionPrice, const Price& positionCost, const Price& insideBid, const Price& insideAsk, const Price& ecnBid, const Price& ecnAsk, const Price& lastPrint, char side);
void WINAPI TU_GetBasePriceProper(unsigned char priceBase, Price& price, const Security* security, const Price& positionPrice, const Price& positionCost, const Price& insideBid, const Price& insideAsk, const Price& ecnBid, const Price& ecnAsk, const Price& lastTrade, char side);
const char* WINAPI TU_GetPriceBaseName(unsigned char priceBase);

void WINAPI TU_GetOrderErrorMessage(unsigned char errorCode, std::string& errorMessage);
void WINAPI TU_GetCancelErrorMessage(unsigned char errorCode, std::string& errorMessage);

EmailDll* WINAPI TU_GetEmailDll();
bool WINAPI TU_IsEmailDllCompatible();

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

	TT_SECURITY_PE_PRINT,

	TT_NONE,

	TT_SECURITY_ECN_BID_SIZE_ACC_GREATER,
	TT_SECURITY_ECN_ASK_SIZE_ACC_GREATER,
	TT_SECURITY_ECN_ANY_SIZE_ACC_GREATER,
	TT_SECURITY_ECN_BID_SIZE_ACC_LESS,
	TT_SECURITY_ECN_ASK_SIZE_ACC_LESS,
	TT_SECURITY_ECN_ANY_SIZE_ACC_LESS,

	TT_SECURITY_ECN_BID_SIZE_QUOTE_GREATER,
	TT_SECURITY_ECN_ASK_SIZE_QUOTE_GREATER,
	TT_SECURITY_ECN_ANY_SIZE_QUOTE_GREATER,
	TT_SECURITY_ECN_BID_SIZE_QUOTE_LESS,
	TT_SECURITY_ECN_ASK_SIZE_QUOTE_LESS,
	TT_SECURITY_ECN_ANY_SIZE_QUOTE_LESS,

	TT_NEWS,

	TT_IMB_NQ_POSITIVE_GREATER,
	TT_IMB_NQ_NEGATIVE_GREATER,
	TT_IMB_NQ_ANY_GREATER,
	TT_IMB_NQ_POSITIVE_LESS,
	TT_IMB_NQ_NEGATIVE_LESS,
	TT_IMB_NQ_ANY_LESS,

	TT_Count
};

//#define L1_SIZE

enum AlertType : unsigned char
{
	AT_SECURITY_PRINT,
	AT_SECURITY_BID,
	AT_SECURITY_ASK,
	AT_SECURITY_VOLUME,
	AT_TIME,
	AT_INDEX,
	AT_SECURITY_IMBALANCE,
	AT_NEWS,
	AT_SECURITY_L2_BID_SIZE,
	AT_SECURITY_L2_ASK_SIZE,
	AT_BORROW_SIZE_AVAILABLE,
	AT_IMB_NY_REFERENCE_PRICE,
#ifdef L1_SIZE
	AT_SECURITY_L1_BID_SIZE,
	AT_SECURITY_L1_ASK_SIZE,
#endif
	AT_COUNT
};

enum AlertStatus : unsigned char
{
	AS_LIVE,
	AS_TRIGGERED,

	AS_COUNT
};

enum AlertSymbolInvalid : unsigned char
{
	ASI_VALID,
	ASI_INVALID,

	ASI_COUNT
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
	virtual __int64 GetModifierValue() const{return 0;}
	virtual __int64 GetValueFrom() const{return 0;}
	virtual __int64 GetValueTriggered() const{return GetValue();}
	virtual void SetValue(__int64 value) = 0;
	virtual void SetModifierValue(__int64 value){}
	virtual void SetValueFrom(__int64 value){}
	virtual unsigned int GetDateTriggered() const{return 0;}
	virtual bool SetDateTriggered(unsigned int dateTriggered){return false;}
	
	const unsigned int& GetExpirationDate() const{return m_expirationDate;}
	bool SetExpirationDate(const unsigned int& date){if(m_expirationDate != date){m_expirationDate = date; return true;} return false;}

	const unsigned int& GetTimeTriggered() const{return m_timeTriggered;}
	bool SetTimeTriggered(const unsigned int& t){if(m_timeTriggered != t){m_timeTriggered = t; return true;} return false;}

	const unsigned int& GetDateCreated() const{return m_dateCreated;}
	bool SetDateCreated(const unsigned int& d){if(m_dateCreated != d){m_dateCreated = d; return true;} return false;}

	const unsigned int& GetTimeCreated() const{return m_timeCreated;}
	bool SetTimeCreated(const unsigned int& t){if(m_timeCreated != t){m_timeCreated = t; return true;} return false;}

	const COLORREF& GetColor() const{return m_color;}
	bool SetColor(const COLORREF& color){if(m_color != color){m_color = color; return true;} return false;}

	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
//	const std::string& GetSymbol() const{return m_symbol;}
#ifndef TAKION_NO_OPTIONS
	const unsigned __int64& GetOptionBlock() const{return m_optionBlock;}
#endif

	const std::string& GetNote() const{return m_note;}
	bool SetNote(const std::string& note)
	{
		if(note != m_note)
		{
			m_note = note;
			return true;
		}
		return false;
	}

	bool operator==(const Alert& other) const
	{
//		return m_symbol == other.m_symbol
		return m_numericSymbol == other.m_numericSymbol
			&& GetAlertType() == other.GetAlertType()
			&& GetValue() == other.GetValue()
			&& GetModifierValue() == other.GetModifierValue()
			&& m_timeTriggered < other.m_timeTriggered;
	}
	bool operator<(const Alert& other) const
	{
//		return m_symbol != other.m_symbol ? m_symbol < other.m_symbol:
		return m_numericSymbol != other.m_numericSymbol ? U_CompareUIntAsString(m_numericSymbol, other.m_numericSymbol) < 0:
			GetAlertType() != other.GetAlertType() ? GetAlertType() < other.GetAlertType():
			GetValue() != other.GetValue() ? GetValue() < other.GetValue():
			GetModifierValue() != other.GetModifierValue() ? GetModifierValue() < other.GetModifierValue():
			m_timeTriggered < other.m_timeTriggered;
	}
	bool isSame(const Alert& other) const
	{
		return operator==(other)
			&& m_color == other.m_color
			&& m_expirationDate == other.m_expirationDate
			&& m_note == other.m_note
			&& m_popup == other.m_popup
			&& m_timeTriggered == other.m_timeTriggered;
	}
	virtual bool isRenewable() const{return true;}
	virtual void GetValueAsString(std::string& str) const{}
	virtual void GetDisplayValueAsString(std::string& str) const{GetValueAsString(str);}
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
	virtual bool AlwaysInitialize() const{return false;}
	virtual bool Initialize(){return false;}
	const bool& isInitialized() const{return m_initialized;}
	void SetInitialized(const bool& initialized){m_initialized = initialized;}
	const bool& isPopup() const{return m_popup;}
	bool SetPopup(const bool& popup)
	{
		if(popup != m_popup)
		{
			m_popup = popup;
			return true;
		}
		return false;
	}
	virtual const Price* GetPrice() const{return NULL;}
	virtual const Price* GetPriceFrom() const{return NULL;}
//	virtual const Price* GetPriceToForRenewal() const{return NULL;}
	virtual bool GetValueFromForRenewal(__int64& value) const{return false;}
	virtual const unsigned __int64* GetVolumePtr() const{return NULL;}
	virtual const unsigned __int64* GetVolumePtrFrom() const{return NULL;}
	virtual const unsigned int* GetSizePtr() const{return NULL;}
	virtual const unsigned int* GetSizeFromPtr() const{return NULL;}
	virtual const unsigned int* GetTimePtr() const{return NULL;}
	virtual const int* GetImbalancePtr() const{return NULL;}
	virtual const int* GetImbalanceFromPtr() const{return NULL;}
	virtual const SignedPrice* GetIndexValue() const{return NULL;}
	virtual const SignedPrice* GetIndexValueFrom() const{return NULL;}
	const Price& GetPriceOrZero() const{const Price* price = GetPrice(); return price ? *price : Price::priceZero;}
	const Price& GetPriceFromOrZero() const{const Price* price = GetPriceFrom(); return price ? *price : Price::priceZero;}
	const unsigned __int64& GetVolumeOrZero() const{const unsigned __int64* volume = GetVolumePtr(); return volume ? *volume : volumeZero;}
	const unsigned __int64& GetVolumeFromOrZero() const{const unsigned __int64* volume = GetVolumePtrFrom(); return volume ? *volume : volumeZero;}
	const int& GetImbalanceOrZero() const{const int* imbalance = GetImbalancePtr(); return imbalance ? *imbalance : imbalanceZero;}
	const int& GetImbalanceFromOrZero() const{const int* imbalance = GetImbalanceFromPtr(); return imbalance ? *imbalance : imbalanceZero;}
	const unsigned int& GetSizeOrZero() const{const unsigned int* size = GetSizePtr(); return size ? *size : timeZero;}
	const unsigned int& GetSizeFromOrZero() const{const unsigned int* size = GetSizeFromPtr(); return size ? *size : timeZero;}
	const unsigned int& GetTimeOrZero() const{const unsigned int* time = GetTimePtr(); return time ? *time : timeZero;}
	const SignedPrice& GetIndexValueOrZero() const{const SignedPrice* price = GetIndexValue(); return price ? *price : SignedPrice::signedPriceZero;}
	const SignedPrice& GetIndexValueFromOrZero() const{const SignedPrice* price = GetIndexValueFrom(); return price ? *price : SignedPrice::signedPriceZero;}
	const bool& isSymbolInvalid() const{return m_symbolInvalid;}
	const bool& isLoaded() const{return m_loaded;}
//	const bool& isTriggered() const{return m_triggered;}
protected:
	Alert(const unsigned __int64& numericSymbol,//const char* symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		const char* const& note,
		const unsigned int& timeTriggered,
		const unsigned int& dateCreated,
		const unsigned int& timeCreated,
		const bool& initialized,
		const bool& popup = true,
		const COLORREF& color = 255,
		const unsigned int& expirationDate = 0):
		m_numericSymbol(numericSymbol),
#ifndef TAKION_NO_OPTIONS
		m_optionBlock(optionBlock),
#endif
//		m_symbol(symbol),
		m_note(note),
		m_color(color),
		m_expirationDate(expirationDate),
		m_timeTriggered(timeTriggered),
		m_dateCreated(dateCreated),
		m_timeCreated(timeCreated),
		m_initialized(initialized),
		m_popup(popup),
		m_symbolInvalid(false),
		m_loaded(true)
//		m_triggered(false)
	{}
	unsigned __int64 m_numericSymbol;
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
#endif
	std::string m_note;
	COLORREF m_color;
	unsigned int m_expirationDate;
	unsigned int m_timeTriggered;
	unsigned int m_dateCreated;
	unsigned int m_timeCreated;
	bool m_initialized;
	bool m_popup;
	static const unsigned __int64 volumeZero;
	static const unsigned int timeZero;
	static const int imbalanceZero;
	bool m_symbolInvalid;
	bool m_loaded;
};

class TU_API AlertFinder : public Alert
{
public:
	AlertFinder(const Alert& alert):
		Alert(alert),
		m_value(alert.GetValue()),
		m_modifierValue(alert.GetModifierValue()),
		m_type(alert.GetAlertType())
	{
	}
	AlertFinder(const unsigned __int64& numericSymbol,//const char* symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		const char* const& note,
		const unsigned int& timeTriggered,
		const unsigned int& dateCreated,
		const unsigned int& timeCreated,
		const __int64& value,
		const __int64& modifierValue,
		const bool& initialized,
		const bool& popup,
		const unsigned char& type,
		const COLORREF& color = 255,
		const unsigned int& expirationDate = 0):
		Alert(numericSymbol,//symbol,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
#endif
			note,
			timeTriggered,
			dateCreated,
			timeCreated,
			initialized,
			popup,
			color,
			expirationDate),
		m_value(value),
		m_modifierValue(modifierValue),
		m_type((AlertType)type)
	{
	}
	virtual AlertType GetAlertType() const override{return m_type;}
	virtual __int64 GetValue() const override{return m_value;}
	virtual __int64 GetModifierValue() const override{return m_modifierValue;}
	virtual void SetValue(__int64 value) override{m_value = value;}
	virtual void SetModifierValue(__int64 value){m_modifierValue = value;}
	void SetType(const unsigned char& type){m_type = (AlertType)type;}
//	void SetSymbol(const std::string& symbol){m_symbol = symbol;}
	void SetNumericSymbol(const unsigned __int64& numericSymbol){m_numericSymbol = numericSymbol;}
	void ValueToStr(std::string& str, const __int64& value, const __int64& modifierValue) const
	{
		switch(m_type)
		{
			case AT_SECURITY_PRINT:
//			case AT_IMB_NY_REFERENCE_PRICE:
			case AT_SECURITY_BID:
			case AT_SECURITY_ASK:
			{
				Price price;
				GetPriceFromValue(price, value);
				U_PriceToStr(str, price, 4, '\0', true, '\0', true);//, true, '\0', true);
			}
			break;

			case AT_SECURITY_VOLUME:
#ifdef L1_SIZE
			case AT_SECURITY_L1_BID_SIZE:
			case AT_SECURITY_L1_ASK_SIZE:
#endif
			case AT_SECURITY_L2_BID_SIZE:
			case AT_SECURITY_L2_ASK_SIZE:
			{
				char num[33];
				str += U_UnsignedNumberToStrWithCommas(value, num, sizeof(num));
			}
			break;

			case AT_SECURITY_IMBALANCE:
			{
				char num[33];
				str += U_SignedNumberToStrWithCommas(value, num, sizeof(num));
			}
			break;

			case AT_TIME:
			U_AppendMillisecond(str, (unsigned int)value, false);
			break;

			case AT_INDEX:
			{
				SignedPrice price;
				GetSignedPriceFromValue(price, value);
				U_SignedPriceToStr(str, price, 4, '\0', true, '\0', true);//, true, '\0', true);
			}
			break;

			case AT_BORROW_SIZE_AVAILABLE:
			{
				char num[33];
				str += U_UnsignedNumberToStrNoDecDigits(value, num, sizeof(num));
				if(modifierValue)
				{
					str += ' ';
					str += 'c';
					Price price;
					GetPriceFromValue(price, modifierValue);
					U_PriceToStr(str, price, 4, '\0', true, '\0', true);//, true, '\0', true);
				}
			}
			break;
		}
	}
	bool GetPriceValue(Price& price) const
	{
		switch(m_type)
		{
			case AT_SECURITY_PRINT:
			case AT_IMB_NY_REFERENCE_PRICE:
			case AT_SECURITY_BID:
			case AT_SECURITY_ASK:
			GetPriceFromValue(price, m_value);
			return true;

			case AT_BORROW_SIZE_AVAILABLE:
			GetPriceFromValue(price, m_modifierValue);
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

#ifdef L1_SIZE
			case AT_SECURITY_L1_BID_SIZE:
			case AT_SECURITY_L1_ASK_SIZE:
#endif
			case AT_SECURITY_L2_BID_SIZE:
			case AT_SECURITY_L2_ASK_SIZE:
			volume = m_value;
			return true;
		}
		return false;
	}

	bool GetSizeValue(unsigned int& size) const
	{
		switch(m_type)
		{
#ifdef L1_SIZE
			case AT_SECURITY_L1_BID_SIZE:
			case AT_SECURITY_L1_ASK_SIZE:
#endif
			case AT_SECURITY_L2_BID_SIZE:
			case AT_SECURITY_L2_ASK_SIZE:
			size = (unsigned int)m_value;
			return true;
		}
		return false;
	}

	bool GetImbalanceValue(__int64& imbalance) const
	{
		switch(m_type)
		{
			case AT_SECURITY_IMBALANCE:
			imbalance = m_value;
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
	virtual void GetValueAsString(std::string& str) const{ValueToStr(str, m_value, m_modifierValue);}
//	virtual void GetValueFromAsString(std::string& str) const{ValueToStr(str, GetValueFrom());}
protected:
	__int64 m_value;
	__int64 m_modifierValue;
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
	typedef StrAsNumberArray<size_t, 24 / sizeof(size_t)> NamedValueId;

	virtual ~NamedValue(){}
//	CWnd* GetWnd() const{return m_wnd;}
	void SetTop(const int& top)
	{
		if(top != m_rectValue.top)
		{
			m_rectName.top = m_rectValue.top = m_rectNameText.top = m_rectValueText.top = top;
			m_rectName.bottom = m_rectValue.bottom = m_rectNameText.bottom = m_rectValueText.bottom = m_rectName.top + m_height;
		}
	}
	void SetHeight(const int& height)
	{
		if(height != m_height)
		{
			m_height = height;
			m_rectName.bottom = m_rectValue.bottom = m_rectNameText.bottom = m_rectValueText.bottom = m_rectName.top + m_height;
		}
	}
	void SetValueLeft(const int& left){m_rectValue.left = m_rectValueText.left = left;}
	void SetGap(const int& gap)
	{
		if(gap != m_gap)
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
	void SetWidth(const int& width)
	{
		if(width != m_width)
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
	void SetValueWidthOnly(const int& width)
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

	const int& GetGap() const{return m_gap;}
	const int& GetValueOffset() const{return m_valueOffset;}
	const int& GetNameOffset() const{return m_nameOffset;}

	void SetValueOffset(const int& offset)
	{
		if(offset != m_valueOffset)
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

	virtual void SetInventoryView(const bool* inventoryView){}
	virtual bool isInventoryView() const{return false;}

	virtual void toString(std::string& str) const{}

	virtual UINT GetValueJustification() const{return DT_RIGHT;}
/*
	void Paint(CDC& dc, const RECT& rcRect)
	{
	}
*/
//	const std::string& GetNameStr() const{return m_name;}
	const char* GetNameStr() const{return m_name.GetString();}
	const NamedValueId& GetNameId() const{return m_name;}
	const std::string& GetDisplayNameStr() const{return m_displayName;}
	const std::string& GetSampleStr() const{return m_sample;}
	const std::string& GetTipStr() const{return m_tip;}
	void PaintName(CDC& dc);
	void PaintValue(CDC& dc);
	void OffsetVertical(const int& y)
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
	void SetBottom(const int& bottom)
	{
		m_rectName.bottom = m_rectValue.bottom = m_rectNameText.bottom = m_rectValueText.bottom = bottom;
	}
	void OffsetHorizontal(const int& x)
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
	void SetTopAndHeight(const int& top, const int& height)
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

	const bool& isValid() const{return m_valid;}
	bool SetValid(bool valid);

	const bool& isFit() const{return m_fit;}
//	const bool& isInventory() const{return m_inventory;}

//	virtual bool isValuePositive() const{return false;}
//	virtual bool isValueNegative() const{return false;}
	virtual void UpdateValue(){}
	virtual void UpdateValueFirstTime(){UpdateValue();}
	const Index* const& GetIndex() const{return m_index;}
	const Security* const& GetSecurity() const{return m_security;}
	const Position* const& GetPosition() const{return m_position;}
	const Account* const& GetAccount() const{return m_account;}

	virtual const char* GetIndexSymbol() const{return NULL;}

	void SetIndex(const Index*);
	void SetSecurity(const Security*);
	void SetPosition(const Position*);
	void SetAccount(const Account*);
	ValueType GetType() const{return m_type;}
	void SetFontValue(CFont* const& font, const unsigned int& fontSize, const bool& fit){m_fontValue = font; m_fontValueSize = fontSize; m_fit = fit;}
	const unsigned int& GetFontValueSize() const{return m_fontValueSize;}
	CFont* const& GetFontValue() const{return m_fontValue;}

	const CRect& GetRectName() const{return m_rectName;}
	const CRect& GetRectValue() const{return m_rectValue;}
	const CRect& GetRectNameText() const{return m_rectNameText;}
	const CRect& GetRectValueText() const{return m_rectValueText;}
	int GetTop() const{return m_rectValue.top;}
	int GetBottom() const{return m_rectValue.bottom;}

	virtual bool SetShowSeconds(const bool& showSeconds){return false;}

	virtual bool SetDecDigits(const unsigned char& decDigits){return false;}
	virtual bool SetTruncate(const bool& truncate){return false;}
	virtual bool SetCommaPrice(const bool& comma){return false;}
	virtual bool SetCommaSize(const bool& comma){return false;}
	virtual bool SetSizeInShares(const bool& sizeInShares){return false;}

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
	static bool DivideMoneyByPrice(Money& value, const Price& price)
	{
		unsigned __int64 dollars = (price * 10000).GetDollars();
		if(dollars)
		{
			value *= 1000000;
			value /= dollars;
			return true;
		}
		else
		{
			dollars = (price * 1000000).GetDollars();
			if(dollars)
			{
				value *= 100000000;
				value /= dollars;
				return true;
			}
		}
		return false;
	}
	static bool DivideMoneyBySignedPrice(Money& value, const SignedPrice& price)
	{
		__int64 dollars = (price * 10000).GetDollars();
		if(dollars)
		{
			value *= 1000000;
			value /= dollars;
			return true;
		}
		else
		{
			dollars = (price * 1000000).GetDollars();
			if(dollars)
			{
				value *= 100000000;
				value /= dollars;
				return true;
			}
		}
		return false;
	}
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
//	std::string m_name;
	NamedValueId m_name;
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
//	bool m_inventory;
};

class TU_API NamedValueCollection
{
public:
	virtual ~NamedValueCollection(){DestroyValues();}
	typedef std::vector<NamedValue*> NamedValueVector;
#if (_MSC_VER > 1600)
	typedef std::unordered_set<NamedValue*> NamedValueSet;
#else
	typedef std::hash_set<NamedValue*> NamedValueSet;
#endif
	CWnd* GetWnd() const{return m_wnd;}
	void InvalidateWndRect(const RECT& rect){if(m_wnd && m_wnd->m_hWnd)::InvalidateRect(m_wnd->m_hWnd, &rect, FALSE);}
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
	const COLORREF& GetNameColor() const{return m_nameColor;}
	const COLORREF& GetNameInventoryColor() const{return m_nameInventoryColor;}
	const COLORREF& GetValueColorNeutral() const{return m_valueColorNeutral;}
	const COLORREF& GetValueColorPositive() const{return m_valueColorPositive;}
	const COLORREF& GetValueColorNegative() const{return m_valueColorNegative;}
	const COLORREF& GetValueColorPositiveBg() const{return m_valueColorPositiveBg;}
	const COLORREF& GetValueColorNegativeBg() const{return m_valueColorNegativeBg;}
	const COLORREF& GetValueColorPositiveBgText() const{return m_valueColorPositiveBgText;}
	const COLORREF& GetValueColorNegativeBgText() const{return m_valueColorNegativeBgText;}
	const COLORREF& GetValueColorWarning() const{return m_valueColorWarning;}
	const COLORREF& GetValueColorInvalid() const{return m_valueColorInvalid;}
	const COLORREF& GetValueColorStockAdr() const{return m_valueColorStockAdr;}
/*
	const bool& isInventoryView() const{return m_inventoryView;}
	void SetInventoryView(const bool& inventoryView)
	{
		if(inventoryView != m_inventoryView)
		{
			m_inventoryView = inventoryView;
			InvalidateNames();
		}
	}
*/
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
	void SetNameColor(const COLORREF& color)
	{
		if(color != m_nameColor)
		{
			m_nameColor = color;
			InvalidateNames();
		}
	}
	void SetNameInventoryColor(const COLORREF& color)
	{
		if(color != m_nameInventoryColor)
		{
			m_nameInventoryColor = color;
//			if(m_inventoryView)
			InvalidateNames();
		}
	}
	void SetValueColorNeutral(const COLORREF& color)
	{
		if(color != m_valueColorNeutral)
		{
			m_valueColorNeutral = color;
			InvalidateValues();
		}
	}

	void SetValueColorPositive(const COLORREF& color)
	{
		if(color != m_valueColorPositive)
		{
			m_valueColorPositive = color;
			InvalidateValues();
		}
	}

	void SetValueColorNegative(const COLORREF& color)
	{
		if(color != m_valueColorNegative)
		{
			m_valueColorNegative = color;
			InvalidateValues();
		}
	}

	void SetValueColorPositiveBg(const COLORREF& color)
	{
		if(color != m_valueColorPositiveBg)
		{
			m_valueColorPositiveBg = color;
			InvalidateValues();
		}
	}

	void SetValueColorNegativeBg(const COLORREF& color)
	{
		if(color != m_valueColorNegativeBg)
		{
			m_valueColorNegativeBg = color;
			InvalidateValues();
		}
	}

	void SetValueColorPositiveBgText(const COLORREF& color)
	{
		if(color != m_valueColorPositiveBgText)
		{
			m_valueColorPositiveBgText = color;
			InvalidateValues();
		}
	}

	void SetValueColorNegativeBgText(const COLORREF& color)
	{
		if(color != m_valueColorNegativeBgText)
		{
			m_valueColorNegativeBgText = color;
			InvalidateValues();
		}
	}

	void SetValueColorWarning(const COLORREF& color)
	{
		if(color != m_valueColorWarning)
		{
			m_valueColorWarning = color;
			InvalidateValues();
		}
	}

	void SetValueColorInvalid(const COLORREF& color)
	{
		if(color != m_valueColorInvalid)
		{
			m_valueColorInvalid = color;
			InvalidateValues();
		}
	}

	void SetValueColorStockAdr(const COLORREF& color)
	{
		if(color != m_valueColorStockAdr)
		{
			m_valueColorStockAdr = color;
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
	void SetTop(const int& top, const bool& force = false)
	{
		if(top != m_rect.top || force)
		{
			OffsetVertical(0, top - m_rect.top);
			m_rect.top = top;
		}
	}
	void SetLeftOnly(const int& left, const bool& force = false)
	{
		if(left != m_rect.left || force)
		{
			OffsetHorizontalLeftOnly(left);
			m_rect.left = left;
		}
	}
	void SetLeft(const int& left, const bool& force = false)
	{
		if(left != m_rect.left || force)
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
	bool SetSizeInShares(const bool& sizeInShares)
	{
		if(sizeInShares != m_sizeInShares)
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
	bool SetDecDigits(const unsigned char& decDigits)
	{
		if(decDigits != m_decDigits)
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
	bool SetTruncate(const bool& truncate)
	{
		if(truncate != m_truncate)
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
	bool SetCommaPrice(const bool& comma)
	{
		if(comma != m_commaPrice)
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
	bool SetCommaSize(const bool& comma)
	{
		if(comma != m_commaSize)
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

	const Security* const& GetSecurity() const{return m_security;}
	const Position* const& GetPosition() const{return m_position;}
	const Account* const& GetAccount() const{return m_account;}

	void SetSecurity(const Security* const& security)
	{
		if(security != m_security)
		{
			m_security = security;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetSecurity(security);
			}
		}
	}

	void SetAccount(const Account* const&  account)
	{
		if(account != m_account)
		{
			m_account = account;
			for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
			{
				(*it)->SetAccount(account);
			}
		}
	}

	void SetPosition(const Position* const& position)
	{
		if(position != m_position)
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
	void UpdateValues(const ValueType& valueType)
	{
		NamedValueSet* valueSet = GetNamedValueSet(valueType);
		if(valueSet)
		{
			NamedValue* namedValue;
			for(NamedValueSet::iterator it = valueSet->begin(), itend = valueSet->end(); it != itend; ++it)
			{
				namedValue = *it;
				if(namedValue->GetType() == valueType)
				{
					namedValue->UpdateValue();
				}
			}
		}
	}

	void UpdateValues(const char* name)
	{
		NamedValue* namedValue;
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			namedValue = *it;
			if(!strcmp(namedValue->GetNameStr(), name))
			{
				namedValue->UpdateValue();
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

//	const int& GetValueWidth() const{return m_valueWidth;}
	const int& GetGap() const{return m_gap;}
	const int& GetValueOffset() const{return m_valueOffset;}
	const int& GetNameOffset() const{return m_nameOffset;}

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

	void SetGap(const int& gap)
	{
		if(gap != m_gap)
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
	NamedValueCollection(CWnd* const& wnd,
		const FontDescription& fontValueDescription,
		CFont* const& fontName,
		const int& gap,
//		int cellHeight,
		const COLORREF& nameColor = RGB(255, 255, 0),
		const COLORREF& valueColorNeutral = RGB(255, 255, 255),
		const COLORREF& valueColorPositive = RGB(128, 255, 128),
		const COLORREF& valueColorNegative = RGB(255, 128, 128),
		const COLORREF& valueColorPositiveBg = RGB(128, 255, 128),
		const COLORREF& valueColorNegativeBg = RGB(255, 128, 128),
		const COLORREF& valueColorPositiveBgText = RGB(0, 255, 0),
		const COLORREF& valueColorNegativeBgText = RGB(255, 0, 0),
		const COLORREF& valueColorWarning = RGB(255, 255, 0),
		const COLORREF& valueColorInvalid = RGB(255, 0, 255),
		const COLORREF& valueColorStockAdr = RGB(128, 0, 0),
		const COLORREF& nameInventoryColor = RGB(255, 0, 255)):

		m_wnd(wnd),
//		m_bgColor(bgColor),
		m_nameColor(nameColor),
		m_nameInventoryColor(nameInventoryColor),
		m_valueColorNeutral(valueColorNeutral),
		m_valueColorPositive(valueColorPositive),
		m_valueColorNegative(valueColorNegative),
		m_valueColorPositiveBg(valueColorPositiveBg),
		m_valueColorNegativeBg(valueColorNegativeBg),
		m_valueColorPositiveBgText(valueColorPositiveBgText),
		m_valueColorNegativeBgText(valueColorNegativeBgText),
		m_valueColorWarning(valueColorWarning),
		m_valueColorInvalid(valueColorInvalid),
		m_valueColorStockAdr(valueColorStockAdr),
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
//		m_inventoryView(false),
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
	COLORREF m_nameInventoryColor;
	COLORREF m_valueColorNeutral;
	COLORREF m_valueColorPositive;
	COLORREF m_valueColorNegative;
	COLORREF m_valueColorPositiveBg;
	COLORREF m_valueColorNegativeBg;
	COLORREF m_valueColorPositiveBgText;
	COLORREF m_valueColorNegativeBgText;
	COLORREF m_valueColorWarning;
	COLORREF m_valueColorInvalid;
	COLORREF m_valueColorStockAdr;
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
//	bool m_inventoryView;
	const Security* m_security;
	const Position* m_position;
	const Account* m_account;
};

class TU_API NamedValueCollectionVertical : public NamedValueCollection
{
public:
//	NamedValueCollection(CWnd* wnd, COLORREF bgColor = 0, COLORREF nameColor = RGB(255, 255, 0), COLORREF valueColor = RGB(255, 255, 255)):
	NamedValueCollectionVertical(CWnd* const& wnd,
		const FontDescription& fontValueDescription,
		CFont* const& fontName,
		const int& gap,
		const int& cellHeight,
		const COLORREF& nameColor = RGB(255, 255, 0),
		const COLORREF& valueColorNeutral = RGB(255, 255, 255),
		const COLORREF& valueColorPositive = RGB(128, 255, 128),
		const COLORREF& valueColorNegative = RGB(255, 128, 128),
		const COLORREF& valueColorPositiveBg = RGB(128, 255, 128),
		const COLORREF& valueColorNegativeBg = RGB(255, 128, 128),
		const COLORREF& valueColorPositiveBgText = RGB(255, 255, 255),
		const COLORREF& valueColorNegativeBgText = RGB(255, 255, 255),
		const COLORREF& nameInventoryColor = RGB(255, 0, 255)):

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
			valueColorNegativeBgText,
			nameInventoryColor),
		m_cellHeight(cellHeight),
		m_lastCellBottom(m_rect.top),
		m_valueWidth(0)
	{
		FontNameChanged();
	}

	virtual void InitNamedValue(NamedValue& value) override;
	virtual void AddValue(NamedValue* value) override;
	virtual void InsertValue(unsigned int index, NamedValue* value) override;
//	virtual NamedValue* RemoveValue(const std::string& name) override;
//	virtual NamedValue* RemoveValueAt(unsigned int at) override;

	virtual void Paint(CDC& dc, const RECT& rcRect) override;
	void PaintNames(CDC& dc, const RECT& rcRect);
	void PaintValues(CDC& dc, const RECT& rcRect);
	virtual void InvalidateNames() override;
	virtual void InvalidateValues() override;
	virtual void ClearValues() override;
	virtual bool RemoveLastValues(unsigned int leaveTopValuesCount) override;

	virtual void OffsetVertical(NamedValueVector::iterator it, int y) override
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
	virtual void OffsetVertical(unsigned int startIndex, int y) override
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
	virtual void OffsetHorizontalLeftOnly(int x) override
	{
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			(*it)->SetValueLeft(x);
		}
	}
	virtual void OffsetHorizontal(int x) override
	{
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			(*it)->OffsetHorizontal(x);
		}
	}
	virtual void SetWidth(int width, bool force = false) override
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
	void SetCellHeight(const int& height, const bool& force = false)
	{
		if(height != m_cellHeight || force)
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
	const int& GetValueWidth() const{return m_valueWidth;}
	void SetValueWidth(int width, const bool& force = false)
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
	const int& GetLastCellBottom() const{return m_lastCellBottom;}
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
	NamedValueCollectionHorizontal(CWnd* const& wnd,
		const FontDescription& fontValueDescription,
		CFont* const& fontName,
		CFont* const& fontValue,
		const unsigned int& fontSize,
		const bool& fit,
		const int& gap,
//		int cellHeight,
		const COLORREF& nameColor = RGB(255, 255, 0),
		const COLORREF& valueColorNeutral = RGB(255, 255, 255),
		const COLORREF& valueColorPositive = RGB(128, 255, 128),
		const COLORREF& valueColorNegative = RGB(255, 128, 128),
		const COLORREF& valueColorPositiveBg = RGB(128, 255, 128),
		const COLORREF& valueColorNegativeBg = RGB(255, 128, 128),
		const COLORREF& valueColorPositiveBgText = RGB(255, 255, 255),
		const COLORREF& valueColorNegativeBgText = RGB(255, 255, 255),
		const COLORREF& nameInventoryColor = RGB(255, 0, 255)):

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
			valueColorNegativeBgText,
			nameInventoryColor),
		m_fontValue(fontValue),
		m_fontSize(fontSize),
		m_fit(fit)

//		m_cellHeight(cellHeight),
//		m_lastCellBottom(m_rect.top),
//		m_valueWidth(0)
	{
		FontNameChanged();
	}

	virtual bool isVertical() const override{return false;}

	virtual void AddValue(NamedValue* value) override;
	virtual void InsertValue(unsigned int index, NamedValue* value) override;
//	virtual NamedValue* RemoveValue(const std::string& name) override;

	virtual void Paint(CDC& dc, const RECT& rcRect) override;
	virtual void InvalidateNames() override;
	virtual void InvalidateValues() override;
//	void PaintNames(CDC& dc, const RECT& rcRect);
//	void PaintValues(CDC& dc, const RECT& rcRect);
//	virtual void ClearValues();

	void OffsetTop(const int& y)
	{
		m_rect.top += y;
		m_rect.bottom += y;
		OffsetVertical(0, y);
	}

	virtual void OffsetVertical(NamedValueVector::iterator it, int y) override
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
	virtual void OffsetVertical(unsigned int startIndex, int y) override
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
	virtual void OffsetHorizontal(int x) override
	{
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			(*it)->OffsetHorizontal(x);
		}
	}
	virtual void OffsetHorizontalLeftOnly(int x) override
	{
		//TBD
/*
		for(NamedValueVector::iterator it = m_namedValueBegin; it != m_namedValueEnd; ++it)
		{
			(*it)->OffsetHorizontal(x);
		}
*/
	}
	virtual void SetWidth(int width, bool force = false) override
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

	virtual bool SetValueOffset(int offset, bool force = false) override;

	virtual void SetBottom(int bottom) override;
	void SetFontValue(CFont* font, unsigned int fontSize, bool fit);
	void Arrange(CDC* dc);
	virtual UINT GetValueJustification(const NamedValue* nv) const override{return DT_LEFT;}
	virtual UINT GetNameJustification() const override{return DT_RIGHT;}
	virtual UINT GetValueVerticalJustification() const override{return DT_TOP;}
	virtual UINT GetNameVerticalJustification() const override{return DT_TOP;}
protected:
	virtual NamedValue* RemoveValue(NamedValueVector::iterator it) override;
	virtual void FontNameChanged() override;
	virtual void InitNamedValue(NamedValue& value) override;
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
		if(value != m_value)
		{
			m_value = value;
			m_parent->InvalidateWndRect(m_rectValue);
		}
	}
	void SetValue(const T& value, const bool& forceRepaint)
	{
		if(value != m_value)
		{
			m_value = value;
			m_parent->InvalidateWndRect(m_rectValue);
		}
		else if(forceRepaint)
		{
			m_parent->InvalidateWndRect(m_rectValue);
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
	virtual void toString(std::string& str) const override{str = m_value;}
protected:
	NamedValueString(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample, tip, displayName, parent)
	{}
};

class TU_API NamedValueCharPtr : public NamedValueType<const char*>
{
public:
	virtual void toString(std::string& str) const override{str = m_value;}
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
	virtual void toString(std::string& str) const override{str.clear(); if(m_value != m_emptyValue)U_AppendPrintableCharIfValid(str, m_value);}//if(m_value && m_value != m_emptyValue)str += m_value;}
	virtual COLORREF GetValueColor() const override{return m_value == m_negativeValue ? m_parent->GetValueColorNegative() : NamedValueType::GetValueColor();}
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
	virtual void toString(std::string& str) const override;
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
	virtual void toString(std::string& str) const override;
protected:
	NamedValueUCharAsChar(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUChar(type, name, sample, tip, displayName, parent)
	{
	}
};

class TU_API NamedValueBool : public NamedValueType<bool>
{
public:
	virtual void toString(std::string& str) const override;
	virtual COLORREF GetValueColor() const override;
protected:
	NamedValueBool(ValueType type, const char* name, const char* sample, const char* tip, const char* yesValue = NULL, const char* noValue = NULL, bool useColor = false, bool reverse = false, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueType(type, name, sample ? sample : "Yes", tip, displayName, parent),
		m_yesValue(yesValue ? yesValue : "Yes"),
		m_noValue(noValue ? noValue : "No"),
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
	NamedValueNumberWithComma(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool useComma = true):
		NamedValueType(type, name, sample, tip, displayName, parent),
		m_useComma(useComma),
		m_comma(useComma && defaultCommaSize)
	{
		m_value = 0;
	}
	virtual bool SetCommaSize(const bool& comma) override
	{
		if(m_useComma && (comma != m_comma))
		{
			m_comma = comma;
			m_parent->InvalidateWndRect(m_rectValueText);
			return true;
		}
		return false;
	}
	virtual const bool& isCommaSize() const override{return m_comma;}
protected:
	bool m_useComma;
	bool m_comma;
};

class TU_API NamedValueUInt : public NamedValueNumberWithComma<unsigned int>
{
public:
	virtual void toString(std::string& str) const override;
protected:
	NamedValueUInt(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool useComma = true):
		NamedValueNumberWithComma(type, name, sample, tip, displayName, parent, useComma){}
};

class TU_API NamedValueLONG : public NamedValueNumberWithComma<LONG>
{
public:
	virtual void toString(std::string& str) const override;
protected:
	NamedValueLONG(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool useComma = true):
		NamedValueNumberWithComma(type, name, sample, tip, displayName, parent, useComma){}
};

class TU_API NamedValueUIntZeroEmpty : public NamedValueUInt
{
public:
	virtual void toString(std::string& str) const override{if(m_value)NamedValueUInt::toString(str);}
protected:
	NamedValueUIntZeroEmpty(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool useComma = true):
		NamedValueUInt(type, name, sample, tip, displayName, parent, useComma)
	{
	}
};

class TU_API ValueUIntRef : public NamedValueUInt
{
public:
	ValueUIntRef(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, const VType* ref = NULL, bool useComma = true):
		NamedValueUInt(type, name, sample, tip, displayName, parent, useComma),
		m_ref(ref),
		m_zero(0)
	{
	}
	virtual const VType& GetObjectValue() const override{return m_ref ? *m_ref : m_zero;}
	virtual NamedValue* Clone() const override;
	virtual void SetRef(const void* ref) override;
protected:
	const VType* m_ref;
	VType m_zero;
};

class TU_API ValueBoolRef : public NamedValueBool
{
public:
	ValueBoolRef(ValueType type, const char* name, const char* sample, const char* tip, const char* yesValue = NULL, const char* noValue = NULL, bool useColor = false, bool reverse = false, const char* displayName = NULL, NamedValueCollection* parent = NULL, const VType* ref = NULL):
		NamedValueBool(type, name, sample, tip, yesValue, noValue, useColor, reverse, displayName, parent),
		m_ref(ref),
		m_zero(false)
	{
	}
	virtual const VType& GetObjectValue() const override {return m_ref ? *m_ref : m_zero;}
	virtual NamedValue* Clone() const override;
	virtual void SetRef(const void* ref) override;
protected:
	const VType* m_ref;
	VType m_zero;
};

class TU_API NamedValueConnectCount : public NamedValueUInt
{
public:
	typedef bool (WINAPI *FunctionConnected)();
	typedef unsigned int (WINAPI *FunctionValue)();
	NamedValueConnectCount(ValueType type, const char* name, FunctionConnected functionConnected, FunctionValue functionValue, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(type, name, sample, tip, displayName, parent),
		m_functionConnected(functionConnected),
		m_functionValue(functionValue),
		m_connectedBkColor(0xFFFFFFFF),//unloaded
		m_connectedFgColor(0xFFFFFFFF),
		m_disconnectedBkColor(0xFFFFFFFF),
		m_disconnectedFgColor(0xFFFFFFFF),
		m_connected(false)
	{
	}
	virtual NamedValue* Clone() const;
	const bool& isConnected() const{return m_connected;}
	virtual COLORREF GetBgColor() const
	{
		return m_connected ? m_connectedBkColor : m_disconnectedBkColor;
	}
	virtual COLORREF GetValueColor() const
	{
		return m_connected ? m_connectedFgColor : m_disconnectedFgColor;
	}
/*
	void SetLoadedBkColor(const COLORREF& color)
	{
		if(color != m_loadedBkColor)
		{
			m_loadedBkColor = color;
			if(m_loaded)m_parent->InvalidateWndRect(m_rectValue);
		}
	}
	void SetLoadedFgColor(const COLORREF& color)
	{
		if(color != m_loadedFgColor)
		{
			m_loadedFgColor = color;
			if(m_loaded)m_parent->InvalidateWndRect(m_rectValue);
		}
	}
*/
	virtual bool isUseConnectedColor() const{return m_connected;}
	void SetConnectedBkColor(const COLORREF& color)
	{
		if(color != m_connectedBkColor)
		{
			m_connectedBkColor = color;
//			if(!m_loaded && m_connected)m_parent->InvalidateWndRect(m_rectValue);
			if(isUseConnectedColor())m_parent->InvalidateWndRect(m_rectValue);
		}
	}

	void SetConnectedFgColor(const COLORREF& color)
	{
		if(color != m_connectedFgColor)
		{
			m_connectedFgColor = color;
//			if(!m_loaded && m_connected)m_parent->InvalidateWndRect(m_rectValue);
			if(isUseConnectedColor())m_parent->InvalidateWndRect(m_rectValue);
		}
	}

	void SetDisconnectedBkColor(const COLORREF& color)
	{
		if(color != m_disconnectedBkColor)
		{
			m_disconnectedBkColor = color;
			if(!m_connected)m_parent->InvalidateWndRect(m_rectValue);
		}
	}
	void SetDisconnectedFgColor(const COLORREF& color)
	{
		if(color != m_disconnectedFgColor)
		{
			m_disconnectedFgColor = color;
			if(!m_connected)m_parent->InvalidateWndRect(m_rectValue);
		}
	}

	virtual void UpdateValue() override
	{
		bool changed = false;
		const unsigned int count = m_functionValue();
		if(count != m_value)
		{
			m_value = count;
			changed = true;
		}
		if(UpdateConnectionState())
		{
			changed = true;
		}
		if(changed)m_parent->InvalidateWndRect(m_rectValue);
	}

protected:
	virtual bool UpdateConnectionState()
	{
		bool changed = false;
/*
		const bool loaded = m_functionLoaded();//TD_IsMarketSorterLoaded();
		if(loaded != m_loaded)
		{
			m_loaded = loaded;
			changed = true;
		}
*/
		const bool connected = m_functionConnected();
		if(connected != m_connected)
		{
			m_connected = connected;
			changed = true;
		}
		return changed;
	}
	FunctionConnected m_functionConnected;
	FunctionValue m_functionValue;
	COLORREF m_connectedBkColor;
	COLORREF m_connectedFgColor;
	COLORREF m_disconnectedBkColor;
	COLORREF m_disconnectedFgColor;
	bool m_connected;
};

class TU_API NamedValueLoadCount : public NamedValueConnectCount
{
public:
	NamedValueLoadCount(ValueType type, const char* name, FunctionConnected functionConnected, FunctionConnected functionLoaded, FunctionValue functionValue, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueConnectCount(type, name, functionConnected, functionValue, sample, tip, displayName, parent),
		m_functionLoaded(functionLoaded),
		m_loadedBkColor(0xFFFFFFFF),
		m_loadedFgColor(0xFFFFFFFF),
/*
		m_unloadedBkColor(0xFFFFFFFF),
		m_unloadedFgColor(0xFFFFFFFF),
		m_disconnectedBkColor(0xFFFFFFFF),
		m_disconnectedFgColor(0xFFFFFFFF),
*/
//		m_connected(false),
		m_loaded(false)
	{
	}
	virtual NamedValue* Clone() const override;
	bool isLoaded() const{return m_loaded;}
	bool isConnected() const{return m_connected;}
	virtual COLORREF GetBgColor() const override
	{
		return m_connected ? m_loaded ? m_loadedBkColor : m_connectedBkColor : m_disconnectedBkColor;
	}
	virtual COLORREF GetValueColor() const override
	{
		return m_connected ? m_loaded ? m_loadedFgColor : m_connectedFgColor : m_disconnectedFgColor;
	}
	void SetLoadedBkColor(const COLORREF& color)
	{
		if(color != m_loadedBkColor)
		{
			m_loadedBkColor = color;
			if(m_loaded)m_parent->InvalidateWndRect(m_rectValue);
		}
	}
	void SetLoadedFgColor(const COLORREF& color)
	{
		if(color != m_loadedFgColor)
		{
			m_loadedFgColor = color;
			if(m_loaded)m_parent->InvalidateWndRect(m_rectValue);
		}
	}
	virtual bool isUseConnectedColor() const override{return !m_loaded && m_connected;}
/*
	void SetUnloadedBkColor(const COLORREF& color)
	{
		if(color != m_unloadedBkColor)
		{
			m_unloadedBkColor = color;
			if(!m_loaded && m_connected)m_parent->InvalidateWndRect(m_rectValue);
		}
	}
	void SetUnloadedFgColor(const COLORREF& color)
	{
		if(color != m_unloadedFgColor)
		{
			m_unloadedFgColor = color;
			if(!m_loaded && m_connected)m_parent->InvalidateWndRect(m_rectValue);
		}
	}
	void SetDisconnectedBkColor(const COLORREF& color)
	{
		if(color != m_disconnectedBkColor)
		{
			m_disconnectedBkColor = color;
			if(!m_connected)m_parent->InvalidateWndRect(m_rectValue);
		}
	}
	void SetDisconnectedFgColor(const COLORREF& color)
	{
		if(color != m_disconnectedFgColor)
		{
			m_disconnectedFgColor = color;
			if(!m_connected)m_parent->InvalidateWndRect(m_rectValue);
		}
	}
*/
protected:
	virtual bool UpdateConnectionState() override
	{
		bool changed = false;
		const bool loaded = m_functionLoaded();
		if(loaded != m_loaded)
		{
			m_loaded = loaded;
			changed = true;
		}
		if(NamedValueConnectCount::UpdateConnectionState())
		{
			changed = true;
		}
		return changed;
	}

	FunctionConnected m_functionLoaded;

	COLORREF m_loadedBkColor;
	COLORREF m_loadedFgColor;
/*
	COLORREF m_unloadedBkColor;
	COLORREF m_unloadedFgColor;
	COLORREF m_disconnectedBkColor;
	COLORREF m_disconnectedFgColor;
	bool m_connected;
*/
	bool m_loaded;
};

class TU_API NamedValueTime : public NamedValueUInt
{
public:
	NamedValueTime(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool showSeconds = true):
		NamedValueUInt(type, name, sample, tip, displayName, parent, false),
		m_showSeconds(showSeconds)
	{}
	virtual void toString(std::string& str) const override;
	virtual NamedValue* Clone() const override;
	virtual bool SetShowSeconds(const bool& showSeconds) override
	{
		if(showSeconds != m_showSeconds)
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
			m_parent->InvalidateWndRect(m_rectValueText);
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
	virtual const VType& GetObjectValue() const override{return m_ref ? *m_ref : m_zero;}
	virtual NamedValue* Clone() const override;
	virtual void SetRef(const void* ref) override;
protected:
	const VType* m_ref;
	VType m_zero;
};

class TU_API NamedValueDate : public NamedValueUInt
{
public:
	NamedValueDate(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool monthName = true, bool fullYear = false):
		NamedValueUInt(type, name, sample, tip, displayName, parent, false),
		m_monthName(monthName),
		m_fullYear(fullYear)
	{}
	virtual void toString(std::string& str) const override;
	virtual NamedValue* Clone() const override;
protected:
	bool m_monthName;
	bool m_fullYear;
};

class TU_API NamedValueShiftFullYearDate : public NamedValueDate
{
public:
	NamedValueShiftFullYearDate(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool monthName = true, bool fullYear = false):
		NamedValueDate(type, name, sample, tip, displayName, parent, monthName, fullYear)
	{}
	virtual void toString(std::string& str) const override;
	virtual NamedValue* Clone() const override;
};

class TU_API NamedValueUShort : public NamedValueType<unsigned short>
{
public:
	virtual void toString(std::string& str) const override;
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
	virtual void toString(std::string& str) const override;
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return m_ref ? *m_ref : m_zero;}
	virtual void SetRef(const void* ref) override;
protected:
	const VType* m_ref;
	VType m_zero;
};

class TU_API NamedValueInt : public NamedValueNumberWithComma<int>
{
public:
	virtual void toString(std::string& str) const override;
	virtual COLORREF GetValueColor() const override;
protected:
	NamedValueInt(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool useComma = true):
		NamedValueNumberWithComma(type, name, sample, tip, displayName, parent, useComma){}
};

class TU_API NamedValueUInt64 : public NamedValueNumberWithComma<unsigned __int64>
{
public:
	NamedValueUInt64(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool useComma = true):
		NamedValueNumberWithComma(type, name, sample, tip, displayName, parent, useComma){}
	virtual void toString(std::string& str) const override;
	virtual NamedValue* Clone() const override;
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
	virtual bool SetDecDigits(const unsigned char& decDigits) override
	{
		if(decDigits != m_decDigits)
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
			m_parent->InvalidateWndRect(m_rectValueText);
//			m_parent->GetWnd()->InvalidateRect(&m_rectValueText, FALSE);
			return true;
		}
		return false;
	}
	virtual bool SetTruncate(const bool& truncate) override
	{
		if(truncate != m_truncate)
		{
			m_truncate = truncate;
			m_parent->InvalidateWndRect(m_rectValueText);
			return true;
		}
		return false;
	}
	virtual bool SetCommaPrice(const bool& comma) override
	{
		if(comma != m_comma)
		{
			m_comma = comma;
			m_parent->InvalidateWndRect(m_rectValueText);
			return true;
		}
		return false;
	}
	virtual const unsigned char& GetDecDigits() const override{return m_decDigits;}
	virtual const bool& isTruncate() const override{return m_truncate;}
	virtual const bool& isCommaPrice() const override{return m_comma;}
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
	virtual NamedValue* Clone() const override;
	virtual void toString(std::string& str) const override;
};

class TU_API ColoredNamedValuePrice : public NamedValuePrice
{
public:
	ColoredNamedValuePrice(ValueType type, COLORREF bkColor, COLORREF fgColor, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePrice(type, name, sample, tip, displayName, parent),
		m_bkColor(bkColor),
		m_fgColor(fgColor)
	{}
	virtual NamedValue* Clone() const override;
	void SetBkColor(const COLORREF& color){m_bkColor = color;}
	void SetFgColor(const COLORREF& color){m_fgColor = color;}
	virtual COLORREF GetBgColor() const override{return m_bkColor;}
	virtual COLORREF GetValueColor() const override{return m_fgColor;}
protected:
	COLORREF m_bkColor;
	COLORREF m_fgColor;
};

class TU_API NamedValuePriceAsUInt64 : public NamedValueMonetary<unsigned __int64>
{
public:
	virtual void toString(std::string& str) const override;
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
	virtual void toString(std::string& str) const override;
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
	virtual void toString(std::string& str) const override;
protected:
	NamedValuePriceAsUIntZeroEmpty(ValueType type, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePriceAsUInt(type, name, sample, tip, displayName, parent)
	{
	}
};

class TU_API NamedValueSignedPrice : public NamedValueMonetary<SignedPrice>
{
public:
	virtual void toString(std::string& str) const override;
	virtual COLORREF GetValueColor() const override;
protected:
	NamedValueSignedPrice(ValueType type, bool valueColorCoded, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMonetary(type, name, sample, tip, displayName, parent),
		m_valueColorCoded(valueColorCoded)
	{}
	bool m_valueColorCoded;
};

class TU_API NamedValueSignedPriceAsInt : public NamedValueMonetary<int>
{
public:
	virtual void toString(std::string& str) const override;
	virtual COLORREF GetValueColor() const override;
protected:
	NamedValueSignedPriceAsInt(ValueType type, bool valueColorCoded, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMonetary(type, name, sample, tip, displayName, parent),
		m_valueColorCoded(valueColorCoded)
	{}
	bool m_valueColorCoded;
};

class TU_API NamedValueMoney : public NamedValueMonetary<Money>
{
public:
	virtual void toString(std::string& str) const override;
	virtual COLORREF GetValueColor() const override;
protected:
	NamedValueMoney(ValueType type, bool valueColorCoded, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMonetary(type, name, sample, tip, displayName, parent),
		m_valueColorCoded(valueColorCoded)
	{}
	bool m_valueColorCoded;
};

class TU_API NamedValueMoneyPercent : public NamedValueMoney
{
public:
	virtual void toString(std::string& str) const override
	{
		NamedValueMoney::toString(str);
		str += '%';
	}
protected:
	NamedValueMoneyPercent(ValueType type, bool valueColorCoded, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		NamedValueMoney(type, valueColorCoded, name, sample, tip, displayName, parent)
	{}
};

class TU_API SecurityValueMoney : public NamedValueMoney
{
public:
	typedef const VType& (Security::*MoneyFunction)() const;
	SecurityValueMoney(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, valueColorCoded, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_moneyFunction)();}
protected:
	MoneyFunction m_moneyFunction;
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_priceFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual void toString(std::string& str) const override
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
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)SetValue((m_security->*m_priceFunction)());
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_priceFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_priceFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)SetValue((m_security->*m_priceFunction)());
	}
protected:
	PriceFunction m_priceFunction;
};

class TU_API SecurityValueSignedPrice : public NamedValueSignedPrice
{
public:
	typedef const VType& (Security::*PriceFunction)() const;
	SecurityValueSignedPrice(const char* name, bool valueColorCoded, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_SECURITY, valueColorCoded, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API SecurityValueSignedPricePercent : public SecurityValueSignedPrice
{
public:
	SecurityValueSignedPricePercent(const char* name, bool valueColorCoded, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValueSignedPrice(name, valueColorCoded, priceFunction, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void toString(std::string& str) const override
	{
		SecurityValueSignedPrice::toString(str);
		str += '%';
	}
};

class TU_API SecurityValueColoredPercent : public SecurityValueSignedPrice
{
public:
	SecurityValueColoredPercent(const char* name, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValueSignedPrice(name, false, priceFunction, sample, tip, displayName, parent)
	{
	}
	virtual void toString(std::string& str) const override
	{
		SecurityValueSignedPrice::toString(str);
		str += '%';
	}
	virtual NamedValue* Clone() const override;
	virtual COLORREF GetBgColor() const override
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
	virtual COLORREF GetValueColor() const override
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
//	virtual const VType& GetObjectValue() const{return Price::priceZero;}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const unsigned char& level1 = m_security->GetLastTradeLevel1();
			const bool force = level1 != m_level1;
			if(force)m_level1 = level1;
			SetValue((m_security->*m_uintFunction)(), force);
		}
	}
	virtual COLORREF GetBgColor() const override
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
	virtual COLORREF GetValueColor() const override
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
	unsigned char m_level1;
};

class TU_API IndexValueSignedPrice : public NamedValueSignedPrice
{
public:
	typedef const VType& (Index::*SignedPriceFunction)() const;
	IndexValueSignedPrice(const char* name, bool valueColorCoded, SignedPriceFunction signedPriceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_INDEX, valueColorCoded, name, sample, tip, displayName, parent),
		m_signedPriceFunction(signedPriceFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_index->*m_signedPriceFunction)();}
protected:
	SignedPriceFunction m_signedPriceFunction;
};

class TU_API IndexLastValue : public IndexValueSignedPrice
{
public:
	IndexLastValue(const char* indexSymbol, bool valueColorCoded, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		IndexValueSignedPrice(name ? name : indexSymbol, valueColorCoded, &Index::GetValue, sample, tip, displayName, parent),
		m_diff(0)
	{
	}
//	virtual const VType& GetObjectValue() const{return Price::priceZero;}
	virtual NamedValue* Clone() const override;
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
	virtual COLORREF GetValueColor() const override
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
			m_parent->InvalidateWndRect(m_rectValue);
		}
	}
*/
	virtual void UpdateValueFirstTime() override
	{
		UpdateValue();
		m_diff = 0;
	}

	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const VType& value = GetObjectValue();
			if(value != m_value)
			{
				m_diff = m_value < value ? 1 : -1;
				m_value = value;
				m_parent->InvalidateWndRect(m_rectValue);
			}
			else if(m_diff)
			{
				m_diff = 0;
				m_parent->InvalidateWndRect(m_rectValue);
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_uint64Function)();}
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
	virtual void toString(std::string& str) const override;
	virtual NamedValue* Clone() const override;
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_uintFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_uintFunction)();}
protected:
	UIntFunction m_uintFunction;
};

class TU_API SecurityValueShiftFullYearDate : public NamedValueShiftFullYearDate
{
public:
	typedef const VType& (Security::*UIntFunction)() const;
	SecurityValueShiftFullYearDate(ValueType type, const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool monthName = true, bool fullYear = false):
		NamedValueShiftFullYearDate(type, name, sample, tip, displayName, parent, monthName, fullYear),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_uintFunction)();}
	virtual COLORREF GetValueColor() const override
	{
		if(m_value)
		{
			const unsigned int todaysDate = TL_GetTodaysDateInFullShiftFormat();
			if(m_value <= todaysDate)
			{
				return m_value == todaysDate ? m_parent->GetValueColorWarning() : m_parent->GetValueColorNegative();
			}
		}
		return m_parent->GetValueColorNeutral();
	}
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
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)SetValue((m_security->*m_uintFunction)());
	}
protected:
	UIntFunction m_uintFunction;
};

class TU_API SecurityValueLONGVal : public NamedValueLONG
{
public:
	typedef VType (Security::*LONGFunction)() const;
	SecurityValueLONGVal(ValueType type, const char* name, LONGFunction longFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueLONG(type, name, sample, tip, displayName, parent),
		m_longFunction(longFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)SetValue((m_security->*m_longFunction)());
	}
protected:
	LONGFunction m_longFunction;
};

class TU_API SecurityValueDateVal : public SecurityValueUIntVal
{
public:
	SecurityValueDateVal(ValueType type, const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValueUIntVal(type, name, uintFunction, sample, tip, displayName, parent)
	{
	}
	virtual void toString(std::string& str) const override;
	virtual NamedValue* Clone() const override;
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_intFunction)();}
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
	virtual void toString(std::string& str) const override
	{
		char num[33];
		str = U_UnsignedNumberToStrNoDecDigits(m_sizeInShares ? m_value : m_value / 100, num, sizeof(num));
	}

	virtual NamedValue* Clone() const override;
	
	virtual bool SetSizeInShares(const bool& sizeInShares) override
	{
		if(sizeInShares != m_sizeInShares)
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
			m_parent->InvalidateWndRect(m_rectValue);
			return true;
		}
		return false;
	}
	virtual const bool& isSizeInShares() const override{return m_sizeInShares;}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_uintFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_ushortFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_shortFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_stringFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_charFunction)();}
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
	virtual COLORREF GetValueColor() const override;
	virtual NamedValue* Clone() const override;
};

class TU_API SecurityValueType : public SecurityValueChar
{
public:
	SecurityValueType(NamedValueCollection* parent = NULL):
		SecurityValueChar("Type", &Security::GetType, "W", "Security Type", NULL, parent)
//		m_colorADR(RGB(128, 0, 0))
	{
	}
	virtual COLORREF GetBgColor() const override;
	virtual NamedValue* Clone() const override;
//	void SetBkAdrColor(const COLORREF& color){m_colorADR = color;}
//protected:
//	COLORREF m_colorADR;
};
/*
class TU_API SecurityValueRpi : public SecurityValueChar
{
public:
	SecurityValueRpi(NamedValueCollection* parent = NULL):
		SecurityValueChar("Rpi", &Security::GetRpiIndicator, "2", "RPI Indicator", NULL, parent, '0')
	{
	}
//	virtual COLORREF GetValueColor() const;
	virtual NamedValue* Clone() const override;
};
*/
class TU_API SecurityValueUChar : public NamedValueUChar
{
public:
	typedef const VType& (Security::*UCharFunction)() const;
	SecurityValueUChar(const char* name, UCharFunction ucharFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUChar(NVT_SECURITY, name, sample, tip, displayName, parent),
		m_ucharFunction(ucharFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_ucharFunction)();}
protected:
	UCharFunction m_ucharFunction;
};

class TU_API SecurityExchange : public SecurityValueUInt
{
public:
	SecurityExchange():SecurityValueUInt(NVT_SECURITY, "Exch", &Security::GetPrimaryExchangeNumericName, "WWWW", "Security Primary Exchange"){}
	virtual NamedValue* Clone() const;
	virtual void toString(std::string& str) const;
};

class TU_API SecurityTick : public SecurityValueUChar
{
public:
	SecurityTick():SecurityValueUChar("Tick", &Security::GetTick, "W", "Security Bid Tick"){}
	virtual NamedValue* Clone() const override;
	virtual void toString(std::string& str) const override
	{
		switch(m_value)
		{
			case UpTick:
			str = "U";
			break;

			case DownTick:
			str = "D";
			break;

			default:
			str = "U";
			break;
		}
	}
};

class TU_API SecurityRelativeVolume : public NamedValueMoney
{
public:
	SecurityRelativeVolume(NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, false, "RelVolume", "99.9999", "(390 / CurrentMarketMinute) * (MarketHoursVolume / AverageDailyVolume)", NULL, parent),
		m_volume(0),
		m_averageDailyVolume(0),
		m_currentMinute(0)
	{}
	bool isValueEmpty() const{return m_currentMinute <= 569 || !m_averageDailyVolume;}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueMoney::toString(str);
		}
	}
	virtual void UpdateValue() override;
	virtual NamedValue* Clone() const override;
protected:
	unsigned __int64 m_volume;
	unsigned __int64 m_averageDailyVolume;
	unsigned int m_currentMinute;
};

#ifndef TAKION_NO_OPTIONS
class TU_API NamedValueSecurityCallPut : public NamedValueChar
{
public:
	NamedValueSecurityCallPut(NamedValueCollection* parent = NULL):NamedValueChar(NVT_SECURITY, "C/P", "C", "Option Call / Put", NULL, parent){}
	virtual void toString(std::string& str) const override
	{
		if(m_value)str += m_value;
	}
	virtual void UpdateValue() override
	{
		if(m_security)
		{
			const OptionInfo* optionInfo = m_security->GetOptionInfo();
			SetValue(optionInfo ? optionInfo->isCall() ? 'C' : 'P' : '\0');
		}
	}
	virtual NamedValue* Clone() const override;
};

class TU_API NamedValueSecuritySuffix : public NamedValueChar
{
public:
	NamedValueSecuritySuffix(NamedValueCollection* parent = NULL):NamedValueChar(NVT_SECURITY, "Suffix", "W", "Option Suffix", NULL, parent){}
	virtual void toString(std::string& str) const override
	{
		if(m_value)str += m_value;
	}
	virtual void UpdateValue() override
	{
		if(m_security)
		{
			const OptionInfo* optionInfo = m_security->GetOptionInfo();
			SetValue(optionInfo ? optionInfo->GetSuffix() : '\0');
		}
	}
	virtual NamedValue* Clone() const override;
};

class TU_API NamedValueSecurityOptionType : public NamedValueUShort
{
public:
	NamedValueSecurityOptionType(NamedValueCollection* parent = NULL):NamedValueUShort(NVT_SECURITY, "OptType", "WM", "Option Type", NULL, parent){}
	virtual void toString(std::string& str) const override
	{
		U_AppendUnsignedNumberAsString(str, m_value);
	}
	virtual void UpdateValue() override
	{
		if(m_security)
		{
			const OptionInfo* optionInfo = m_security->GetOptionInfo();
			SetValue(optionInfo ? optionInfo->GetOptionType() : 0);
		}
	}
	virtual NamedValue* Clone() const override;
};
#endif

class TU_API NamedValueSecurityIsLoaded : public NamedValueBool
{
public:
	NamedValueSecurityIsLoaded():NamedValueBool(NVT_SECURITY, "Loaded", NULL, "Security is loaded")
	{
		m_value = false;
	}
//	virtual const VType& GetObjectValue() const{return m_value;}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue(m_security->isLoaded());
		}
	}
	virtual COLORREF GetValueColor() const override;
	virtual NamedValue* Clone() const override;
};

class TU_API SecurityValueBool : public NamedValueBool
{
public:
	typedef const VType& (Security::*BoolFunction)() const;
	SecurityValueBool(const char* name, BoolFunction boolFunction, bool reverseColor, const char* sample, const char* tip, const char* yesValue = NULL, const char* noValue = NULL, bool useColor = true, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueBool(NVT_SECURITY, name, sample, tip, yesValue, noValue, useColor, reverseColor, displayName, parent),
		m_boolFunction(boolFunction)
	{
	}
	virtual NamedValue* Clone() const override;
//	virtual COLORREF GetValueColor() const;
	virtual const VType& GetObjectValue() const override{return (m_security->*m_boolFunction)();}
protected:
	BoolFunction m_boolFunction;
};

class TU_API SecurityValueBoolVal : public NamedValueBool
{
public:
	typedef VType (Security::*BoolFunction)() const;
	SecurityValueBoolVal(const char* name, BoolFunction boolFunction, bool reverseColor, const char* sample, const char* tip, const char* yesValue = NULL, const char* noValue = NULL, bool useColor = true, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		NamedValueBool(NVT_SECURITY, name, sample, tip, yesValue, noValue, useColor, reverseColor, displayName, parent),
		m_boolFunction(boolFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)SetValue((m_security->*m_boolFunction)());
	}
protected:
	BoolFunction m_boolFunction;
};

class TU_API SecurityValueCharVal : public NamedValueChar
{
public:
	typedef VType (Security::*CharFunction)() const;
	SecurityValueCharVal(const char* name, CharFunction charFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, char emptyValue = '\0', char negativeValue = '\0'):
		NamedValueChar(NVT_SECURITY, name, sample, tip, displayName, parent, emptyValue, negativeValue),
		m_charFunction(charFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)SetValue((m_security->*m_charFunction)());
	}
protected:
	CharFunction m_charFunction;
};


//class TU_API NamedValueSecurityHtb : public NamedValueBool
class TU_API NamedValueSecurityHtb : public NamedValueUCharAsChar
{
public:
//	NamedValueSecurityHtb(const unsigned char& ordinal, const unsigned char& slOrdinal, NamedValueCollection* parent = NULL):
	NamedValueSecurityHtb(const unsigned char& slOrdinal, NamedValueCollection* parent = NULL):
		NamedValueUCharAsChar(NVT_SECURITY, "HTB", "H", "Hard to Borrow", NULL, parent),
//		m_ordinal(ordinal),
		m_slOrdinal(slOrdinal),
		m_borrowSize(0),
		m_valueValid(false)
	{}
	virtual bool DependsOnAccount() const override{return true;}
	virtual void UpdateValue() override
	{
		bool force = false;
		if(m_security)
		{
			const unsigned int* borrowSize = m_security->GetBorrowSize(m_slOrdinal);
			if(borrowSize)
			{
				if(!m_valueValid)
				{
					force = true;
					m_valueValid = true;
//					m_parent->InvalidateWndRect(m_rectValue);
				}
				const unsigned int bs = *borrowSize;
				if(bs != m_borrowSize)
				{
					force = true;
					m_borrowSize = bs;
//					m_parent->InvalidateWndRect(m_rectValue);
				}
			}
			else
			{
				if(m_valueValid)
				{
					force = true;
					m_borrowSize = 0;
					m_valueValid = false;
//					m_parent->InvalidateWndRect(m_rectValue);
				}
			}
//			SetValue(m_security->isHTB(m_ordinal), force);
			SetValue(m_security->isHTB(m_slOrdinal), force);
		}
		else
		{
			if(m_valueValid)
			{
				force = true;
				m_borrowSize = 0;
				m_valueValid = false;
//				m_parent->InvalidateWndRect(m_rectValue);
			}
			SetValue(0, force);
		}
	}
	virtual COLORREF GetValueColor() const override;
	virtual NamedValue* Clone() const override;
protected:
//	void UpdateColor();
//	virtual void OnParentSet();

//	const unsigned char& m_ordinal;
	const unsigned char& m_slOrdinal;
	unsigned int m_borrowSize;
	bool m_valueValid;
//	COLORREF m_color;
};

class TU_API NamedValueSecurityBorrowPrice : public NamedValuePrice
{
public:
	NamedValueSecurityBorrowPrice(const unsigned char& ordinal):
		NamedValuePrice(NVT_SECURITY, "$Borrow", "99.9999", "Borrow Price in cents", "cBorrow"),
		m_ordinal(ordinal),
		m_valueValid(false)
	{}
//	NamedValueSecurityBorrowPrice(const NamedValueSecurityBorrowPrice& other):NamedValuePrice(other),m_ordinal(other.m_ordinal),m_valueValid(other.m_valueValid){}
	virtual bool DependsOnAccount() const override{return true;}
	virtual void UpdateValue() override
	{
		if(m_security && m_account)
		{
//			const Price* price = m_security->GetBorrowPrice(m_ordinal);
			const unsigned int* price = m_security->GetCompactBorrowPrice(m_ordinal);
			if(price)
			{
				const bool force = !m_valueValid;
				m_valueValid = true;
				const unsigned char discountFlag = m_security->GetBorrowDiscountFlag(m_ordinal);
//				SetValue(m_account && !discountFlag ? *price * m_account->GetBorrowPriceMultiplier() : *price, force);
				Price p(*price);
				if(m_account && !discountFlag)p = p * m_account->GetBorrowPriceMultiplier();
				SetValue(p, force);
			}
			else if(m_valueValid)
			{
				m_valueValid = false;
				SetValue(Price::priceZero, true);
			}
		}
		else if(m_valueValid)
		{
			m_valueValid = false;
			SetValue(Price::priceZero, true);
		}
	}
	virtual NamedValue* Clone() const;
	virtual void toString(std::string& str) const override
	{
		if(m_valueValid)
		{
			str += 'c';
			NamedValuePrice::toString(str);
		}
	}
protected:
	const unsigned char& m_ordinal;
	bool m_valueValid;
};

class TU_API NamedValueSecurityBeta : public NamedValueSignedPrice
{
public:
	NamedValueSecurityBeta(const unsigned char& ordinal):
		NamedValueSignedPrice(NVT_SECURITY, true, "Beta", "100.00", "Stock's Beta"),
		m_ordinal(ordinal),
		m_valueValid(false)
	{}
//	NamedValueSecurityBorrowPrice(const NamedValueSecurityBorrowPrice& other):NamedValuePrice(other),m_ordinal(other.m_ordinal),m_valueValid(other.m_valueValid){}
	virtual bool DependsOnAccount() const override{return true;}
	virtual void UpdateValue() override
	{
		if(m_security)// && m_account)
		{
//			const SignedPrice* price = m_security->GetBeta(m_ordinal);
			const int* price = m_security->GetCompactBeta(m_ordinal);
			if(price)
			{
				const bool force = !m_valueValid;
				m_valueValid = true;
				SetValue(SignedPrice(*price), force);
			}
			else if(m_valueValid)
			{
				m_valueValid = false;
				SetValue(SignedPrice(StockLoanInfo::defaultCompactBeta), true);
			}
		}
		else if(m_valueValid)
		{
			m_valueValid = false;
			SetValue(SignedPrice(StockLoanInfo::defaultCompactBeta), true);
		}
	}
	virtual NamedValue* Clone() const;

	virtual void toString(std::string& str) const override
	{
		if(m_valueValid)
		{
			NamedValueSignedPrice::toString(str);
		}
	}

protected:
	const unsigned char& m_ordinal;
	bool m_valueValid;
};

class TU_API NamedValueSecurityMargin : public NamedValueUChar
{
public:
	NamedValueSecurityMargin(const unsigned char& ordinal):
		NamedValueUChar(NVT_SECURITY, "Margin", "0.99", "Overnight House Margin Requirement"),
		m_ordinal(ordinal),
		m_valueValid(false)
	{}
//	NamedValueSecurityBorrowPrice(const NamedValueSecurityBorrowPrice& other):NamedValuePrice(other),m_ordinal(other.m_ordinal),m_valueValid(other.m_valueValid){}
	virtual bool DependsOnAccount() const override{return true;}
	virtual void UpdateValue() override
	{
		if(m_security)// && m_account)
		{
			const unsigned char* percent = m_security->GetMargin(m_ordinal);
			if(percent)
			{
				const bool force = !m_valueValid;
				m_valueValid = true;
				SetValue(*percent, force);
			}
			else if(m_valueValid)
			{
				m_valueValid = false;
				SetValue(100, true);
			}
		}
		else if(m_valueValid)
		{
			m_valueValid = false;
			SetValue(100, true);
		}
	}
	virtual NamedValue* Clone() const;

	virtual void toString(std::string& str) const override
	{
		if(m_valueValid)
		{
			toStringAsWholePercent(m_value, str);
		}
	}

protected:
	const unsigned char& m_ordinal;
	bool m_valueValid;
};

class TU_API NamedValueSecurityHtbTimestamp : public NamedValueTime
{
public:
	NamedValueSecurityHtbTimestamp(const unsigned char& ordinal):
		NamedValueTime(NVT_SECURITY, "HtbTimestamp", "12:12:12", "Time of last HTB status change", NULL, NULL, true),
		m_ordinal(ordinal),
		m_valueValid(false)
	{}
//	NamedValueSecurityBorrowPrice(const NamedValueSecurityBorrowPrice& other):NamedValuePrice(other),m_ordinal(other.m_ordinal),m_valueValid(other.m_valueValid){}
	virtual bool DependsOnAccount() const override{return true;}
	virtual void UpdateValue() override
	{
		if(m_security)// && m_account)
		{
			const unsigned int* timestamp = m_security->GetTimestampHtb(m_ordinal);
			if(timestamp)
			{
				const bool force = !m_valueValid;
				m_valueValid = true;
				SetValue(*timestamp, force);
			}
			else if(m_valueValid)
			{
				m_valueValid = false;
				SetValue(0, true);
			}
		}
		else if(m_valueValid)
		{
			m_valueValid = false;
			SetValue(0, true);
		}
	}
	virtual NamedValue* Clone() const;

	virtual void toString(std::string& str) const override
	{
		if(m_valueValid && m_value)
		{
			NamedValueTime::toString(str);
		}
	}

protected:
	const unsigned char& m_ordinal;
	bool m_valueValid;
};

class TU_API NamedValueSecuritySplit : public NamedValueUInt
{
public:
	NamedValueSecuritySplit():NamedValueUInt(NVT_SECURITY, "Split", "20/20", "Security Split", NULL, NULL, false)
	{
		m_value = (1 << 16) | 1;
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_security->GetSplitNumerator()) << 16 | m_security->GetSplitDenominator());
		}
	}
	virtual void toString(std::string& str) const override;
	virtual COLORREF GetValueColor() const override;
	virtual NamedValue* Clone() const override;
};

class TU_API SecurityValuePriceDiff : public NamedValueSignedPrice
{
public:
	typedef const Price& (Security::*PriceFunction)() const;
	SecurityValuePriceDiff(const char* name, bool valueColorCoded, PriceFunction priceFunction, PriceFunction priceFunction2, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_SECURITY, valueColorCoded, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction),
		m_priceFunction2(priceFunction2),
		m_canBeNegative(canBeNegative)
	{
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue(SignedPrice((m_security->*m_priceFunction)()) - SignedPrice((m_security->*m_priceFunction2)()));
		}
	}
	virtual NamedValue* Clone() const override;
	virtual COLORREF GetValueColor() const override;
protected:
	PriceFunction m_priceFunction;
	PriceFunction m_priceFunction2;
	bool m_canBeNegative;
};

class TU_API SecurityValuePriceDiffNoZero : public SecurityValuePriceDiff
{
public:
	SecurityValuePriceDiffNoZero(const char* name, bool valueColorCoded, PriceFunction priceFunction, PriceFunction priceFunction2, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		SecurityValuePriceDiff(name, valueColorCoded, priceFunction, priceFunction2, canBeNegative, sample, tip, displayName, parent)
	{
	}
	bool isValueEmpty() const{return m_price1.isZero() || m_price2.isZero();}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			SecurityValuePriceDiff::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const Price price1 = (m_security->*m_priceFunction)();
			const Price price2 = (m_security->*m_priceFunction2)();
			if(price1 != m_price1 || price2 != m_price2)
			{
				SignedPrice val;
				const bool wasEmpty = isValueEmpty();
				m_price1 = price1;
				m_price2 = price2;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty)
				{
					val = SignedPrice(price1) - SignedPrice(price2);
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
	}
	virtual NamedValue* Clone() const;
protected:
	Price m_price1;
	Price m_price2;
};

////
class TU_API PositionSecurityValuePriceDiff : public NamedValueSignedPrice
{
public:
	typedef const Price& (Position::*PositionPriceFunction)(const bool& inventoryView) const;
	typedef const Price& (Security::*SecurityPriceFunction)() const;
	PositionSecurityValuePriceDiff(const char* name, const bool* inventoryView, bool valueColorCoded, PositionPriceFunction positionPriceFunction, SecurityPriceFunction securityPriceFunction, bool reverseForShort, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_POSITION, valueColorCoded, name, sample, tip, displayName, parent),
		m_positionPriceFunction(positionPriceFunction),
		m_securityPriceFunction(securityPriceFunction),
		m_inventoryView(inventoryView),
		m_reverseForShort(reverseForShort),
		m_positionSize(0)
	{
	}
	unsigned char CalculateDifference(SignedPrice& diff)
	{
		if(m_valid && m_security)
		{
			const bool wasEmpty = isValueEmpty();
			const bool inventoryView = m_inventoryView != NULL && *m_inventoryView;
			m_positionSize = m_position->GetSizeInv(inventoryView);
			m_positionPrice = (m_position->*m_positionPriceFunction)(inventoryView);
			m_securityPrice = (m_security->*m_securityPriceFunction)();
			if(!isValueEmpty())
			{
				diff = m_reverseForShort && m_positionSize < 0 ? m_securityPrice - m_positionPrice : m_positionPrice - m_securityPrice;
				return wasEmpty ? 2 : 1;
			}
			else if(!wasEmpty)
			{
				diff.SetZero();
				return 2;
			}
		}
		else// if(m_positionSize || !m_positionPrice.isZero() || !m_securityPrice.isZero())
		{
			m_positionSize = 0;// m_position->GetSizeInv(inventoryView);
			if(!m_positionPrice.isZero())
			{
				m_positionPrice.SetZero();
				if(!m_securityPrice.isZero())
				{
					m_securityPrice.SetZero();
					return 2;
				}
			}
			m_securityPrice.SetZero();
		}
		return 0;
	}
	bool isValueEmpty() const{return m_positionPrice.isZero() || m_securityPrice.isZero();}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueSignedPrice::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		SignedPrice diff;
		const unsigned char ret = CalculateDifference(diff);
		if(ret)
		{
			SetValue(diff, ret == 2);
		}
//		else SetValue(SignedPrice::signedPriceZero, true);
	}
	virtual NamedValue* Clone() const override;
	virtual COLORREF GetValueColor() const override
	{
		return m_valueColorCoded ?
			m_value.isPositive() ? m_parent->GetValueColorPositive():
			m_value.isNegative() ? m_parent->GetValueColorNegative():
			m_parent->GetValueColorNeutral():

			m_positionSize > 0 ? m_parent->GetValueColorPositive():
			m_positionSize < 0 ? m_parent->GetValueColorNegative():
			m_parent->GetValueColorNeutral();
	}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	PositionPriceFunction m_positionPriceFunction;
	SecurityPriceFunction m_securityPriceFunction;
	const bool* m_inventoryView;
	bool m_reverseForShort;
	int m_positionSize;
	Price m_positionPrice;
	Price m_securityPrice;
};

class TU_API PositionSecurityValuePriceDiffPercent : public PositionSecurityValuePriceDiff
{
public:
	PositionSecurityValuePriceDiffPercent(const char* name, const bool* inventoryView, bool valueColorCoded, PositionPriceFunction positionPriceFunction, SecurityPriceFunction securityPriceFunction, bool reverseForShort, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionSecurityValuePriceDiff(name, inventoryView, valueColorCoded, positionPriceFunction, securityPriceFunction, reverseForShort, sample, tip, displayName, parent)
	{
	}
	virtual void UpdateValue()
	{
		SignedPrice diff;
		const unsigned char ret = CalculateDifference(diff);
		if(ret)
		{
			SetValue(m_securityPrice.GetPercentChange(diff), ret == 2);
		}
//		if(CalculateDifference(diff))SetValue(m_securityPrice.GetPercentChange(diff));
//		else SetValue(SignedPrice::signedPriceZero);
	}
	virtual void toString(std::string& str) const override
	{
//		PositionSecurityValuePriceDiff::toString(str);
//		str += '%';
		if(!isValueEmpty())
		{
			NamedValueSignedPrice::toString(str);
			str += '%';
		}
	}
	virtual NamedValue* Clone() const override;
};

////
class TU_API PositionSecurityValueUIntDivision : public NamedValuePrice
{
public:
	typedef const unsigned int& (Position::*PositionUIntFunction)(const bool& inventoryView) const;
	typedef const unsigned int& (Security::*SecurityUIntFunction)() const;
	PositionSecurityValueUIntDivision(const char* name, const bool* inventoryView, PositionUIntFunction positionUIntFunction, SecurityUIntFunction securityUIntFunction, const unsigned int& multiplier, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePrice(NVT_POSITION, name, sample, tip, displayName, parent),
		m_positionUIntFunction(positionUIntFunction),
		m_securityUIntFunction(securityUIntFunction),
		m_inventoryView(inventoryView),
		m_multiplier(multiplier ? multiplier : 1),
		m_positionValue(0),
		m_securityValue(0)
	{
	}
	virtual const unsigned int& GetSecurityObjectValue() const
	{
		return (m_security->*m_securityUIntFunction)();
//		const unsigned int& value = (m_security->*m_uintSecurityFunction)();
//		return value == 0xFFFFFFFF ? (m_security->*m_uintSecurityAlternateFunction)() : value;
	}
	unsigned char CalculateDivision(Price& division)
	{
		if(m_valid && m_security)
		{
			const bool wasEmpty = isValueEmpty();
			const bool inventoryView = m_inventoryView != NULL && *m_inventoryView;
			m_positionValue = (m_position->*m_positionUIntFunction)(inventoryView);
//			m_securityValue = (m_security->*m_securityUIntFunction)();
			m_securityValue = GetSecurityObjectValue();
			if(!isValueEmpty())
			{
				division.SetValue(m_positionValue, 0);
				division /= m_securityValue * m_multiplier;
				return wasEmpty ? 2 : 1;
			}
			else if(!wasEmpty)
			{
				division.SetZero();
				return 2;
			}
		}
		else
		{
			unsigned char count = 0;
			if(m_positionValue)
			{
				m_positionValue = 0;
				if(m_securityValue)
				{
					m_securityValue = 0;
					division.SetZero();
					return 2;
				}
			}
			m_securityValue = 0;
		}
		return 0;
	}
	bool isValueEmpty() const{return !m_positionValue || !m_securityValue;}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValuePrice::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		Price division;
		if(CalculateDivision(division))SetValue(division);
		else SetValue(Price::priceZero);
	}
	virtual NamedValue* Clone() const override;
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	PositionUIntFunction m_positionUIntFunction;
	SecurityUIntFunction m_securityUIntFunction;
	const bool* m_inventoryView;
	unsigned int m_multiplier;
	unsigned int m_positionValue;
	unsigned int m_securityValue;
};

class TU_API PositionSecurityValueUIntAlternateDivision : public PositionSecurityValueUIntDivision
{
public:
	PositionSecurityValueUIntAlternateDivision(const char* name, const bool* inventoryView, PositionUIntFunction positionUIntFunction, SecurityUIntFunction securityUIntFunction, SecurityUIntFunction securityUIntAlternateFunction, const unsigned int& multiplier, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionSecurityValueUIntDivision(name, inventoryView, positionUIntFunction, securityUIntFunction, multiplier, sample, tip, displayName, parent),
		m_securityUIntAlternateFunction(securityUIntAlternateFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const unsigned int& GetSecurityObjectValue() const override
	{
		const unsigned int& value = (m_security->*m_securityUIntFunction)();
		return value == 0xFFFFFFFF ? (m_security->*m_securityUIntAlternateFunction)() : value;
	}
protected:
	SecurityUIntFunction m_securityUIntAlternateFunction;
};

class TU_API SecurityIntByUIntPlusIntDivisionPositiveNv : public NamedValueMoney
{
public:
	typedef const int& (Security::*IntFunction)() const;
	typedef const unsigned int& (Security::*UIntFunction)() const;
	SecurityIntByUIntPlusIntDivisionPositiveNv(const char* name, IntFunction intFunction, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, false, name, sample, tip, displayName, parent),
		m_intFunction(intFunction),
		m_uintFunction(uintFunction),
		m_numerator(0),
		m_denominator(0)
	{
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			int numerator = (m_security->*m_intFunction)();
			const unsigned int denominator = (m_security->*m_uintFunction)();
			if(numerator != m_numerator || denominator != m_denominator)
			{
				m_numerator = numerator;
				m_denominator = denominator;
				Money val;
				if(numerator)
				{
					if(denominator)
					{
						if(numerator < 0)numerator = -numerator;
						val.SetValue(numerator * 100, 0);
						val /= (numerator + (__int64)denominator);
					}
					else
					{
						val.SetValue(100, 0);
					}
				}
				SetValue(val);
			}
		}
	}
	virtual NamedValue* Clone() const override;
protected:
	IntFunction m_intFunction;
	UIntFunction m_uintFunction;
	int m_numerator;
	unsigned int m_denominator;
};

class TU_API SecurityPriceAndPriceAsUIntDiff : public NamedValueSignedPrice
{
public:
	typedef const unsigned int& (Security::*PriceAsUIntFunction)() const;
	typedef const Price& (Security::*PriceFunction)() const;
	SecurityPriceAndPriceAsUIntDiff(const char* name, bool absValue, bool reversed, PriceAsUIntFunction priceAsUIntFunction, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_SECURITY, !absValue, name, sample, tip, displayName, parent),
		m_priceAsUIntFunction(priceAsUIntFunction),
		m_priceFunction(priceFunction),
		m_priceAsUInt(0),
		m_absValue(absValue),
		m_reversed(reversed)
	{
	}
	bool isValueEmpty() const{return !m_priceAsUInt || m_price.isZero();}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueSignedPrice::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			unsigned int priceAsUInt = (m_security->*m_priceAsUIntFunction)();
			const Price price = (m_security->*m_priceFunction)();
			if(priceAsUInt != m_priceAsUInt || price != m_price)
			{
				SignedPrice val;
				const bool wasEmpty = isValueEmpty();
				m_priceAsUInt = priceAsUInt;
				m_price = price;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty)
				{
					Price p(priceAsUInt);
					val = (m_absValue ? price < p : !m_reversed) ? p - price : price - p;
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
	}
	virtual NamedValue* Clone() const override;
protected:
	PriceAsUIntFunction m_priceAsUIntFunction;
	PriceFunction m_priceFunction;
	unsigned int m_priceAsUInt;
	Price m_price;
	bool m_absValue;
	bool m_reversed;
};

class TU_API SecurityPriceAndPriceAsUIntDiffPercent : public NamedValueMoney
{
public:
	typedef const unsigned int& (Security::*PriceAsUIntFunction)() const;
	typedef const Price& (Security::*PriceFunction)() const;
	SecurityPriceAndPriceAsUIntDiffPercent(const char* name, bool absValue, bool reversed, PriceAsUIntFunction priceAsUIntFunction, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, !absValue, name, sample, tip, displayName, parent),
		m_priceAsUIntFunction(priceAsUIntFunction),
		m_priceFunction(priceFunction),
		m_priceAsUInt(0),
		m_absValue(absValue),
		m_reversed(reversed)
	{
	}
	bool isValueEmpty() const{return !m_priceAsUInt || m_price.isZero();}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueMoney::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const unsigned int priceAsUInt = (m_security->*m_priceAsUIntFunction)();
			const Price price = (m_security->*m_priceFunction)();
			if(priceAsUInt != m_priceAsUInt || price != m_price)
			{
				Money val;
				const bool wasEmpty = isValueEmpty();
				m_priceAsUInt = priceAsUInt;
				m_price = price;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty)
				{
					Price p(priceAsUInt);
					val = Money((m_absValue ? price < p : !m_reversed) ? p - price : price - p);
					DivideMoneyByPrice(val, p);
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
	}
	virtual NamedValue* Clone() const override;
protected:
	PriceAsUIntFunction m_priceAsUIntFunction;
	PriceFunction m_priceFunction;
	unsigned int m_priceAsUInt;
	Price m_price;
	bool m_absValue;
	bool m_reversed;
};

class TU_API SecurityPriceAndPriceAsUIntLesserDiff : public NamedValueSignedPrice
{
public:
	typedef const unsigned int& (Security::*PriceAsUIntFunction)() const;
	typedef const Price& (Security::*PriceFunction)() const;
	SecurityPriceAndPriceAsUIntLesserDiff(const char* name, bool absValue, PriceAsUIntFunction priceAsUIntFunctionBetween, PriceFunction priceFunctionLow, PriceFunction priceFunctionHigh, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_SECURITY, !absValue, name, sample, tip, displayName, parent),
		m_priceAsUIntFunctionBetween(priceAsUIntFunctionBetween),
		m_priceFunctionLow(priceFunctionLow),
		m_priceFunctionHigh(priceFunctionHigh),
		m_priceAsUInt(0),
		m_absValue(absValue)
	{
	}
	bool isValueEmpty() const{return !m_priceAsUInt || m_priceHigh.isZero() && m_priceLow.isZero();}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueSignedPrice::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const unsigned int priceAsUInt = (m_security->*m_priceAsUIntFunctionBetween)();
			const Price priceLow = (m_security->*m_priceFunctionLow)();
			const Price priceHigh = (m_security->*m_priceFunctionHigh)();
			if(priceAsUInt != m_priceAsUInt || priceLow != m_priceLow || priceHigh != m_priceHigh)
			{
				SignedPrice val;
				const bool wasEmpty = isValueEmpty();
				m_priceAsUInt = priceAsUInt;
				m_priceLow = priceLow;
				m_priceHigh = priceHigh;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty)
				{
					Price p(priceAsUInt);
					if(m_absValue)
					{
						if(priceLow.isZero())val = priceHigh < p ? p - priceHigh : priceHigh - p;
						else if(priceHigh.isZero())val = p < priceLow ? priceLow - p : p - priceLow;
						else
						{
							val = priceHigh < p ? p - priceHigh : priceHigh - p;
							SignedPrice low = p < priceLow ? priceLow - p : p - priceLow;
							if(low < val)val = low;
						}
					}
					else
					{
						if(priceLow.isZero())val = priceHigh - p;
						else if(priceHigh.isZero())val = p - priceLow;
						else
						{
							val = priceHigh - p;
							SignedPrice low = p - priceLow;
							if(low < val)val = low;
						}
					}
/*
					if(priceLow.isZero())
					{
						val = m_absValue && priceHigh < p ? p - priceHigh : priceHigh - p;
					}
					else if(priceHigh.isZero())
					{
						val = m_absValue && p < priceLow ? priceLow - p : p - priceLow;
					}
					else
					{
						val = m_absValue && priceHigh < p ? p - priceHigh : priceHigh - p;
						SignedPrice low = m_absValue && p < priceLow ? priceLow - p : p - priceLow;
						if(low < val)val = low;
					}
*/
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
/*
		if(m_valid)
		{
			SignedPrice val;
			const unsigned int& priceAsUInt = (m_security->*m_priceAsUIntFunctionBetween)();
			if(priceAsUInt)
			{
				Price p(priceAsUInt);
				const Price& priceLow = (m_security->*m_priceFunctionLow)();
				const Price& priceHigh = (m_security->*m_priceFunctionHigh)();
				if(priceLow.isZero())
				{
					if(!priceHigh.isZero())
					{
						val = m_absValue && priceHigh < p ? p - priceHigh : priceHigh - p;
					}
				}
				else if(priceHigh.isZero())
				{
					val = m_absValue && p < priceLow ? priceLow - p : p - priceLow;
				}
				else
				{
					val = m_absValue && priceHigh < p ? p - priceHigh : priceHigh - p;
					SignedPrice low = m_absValue && p < priceLow ? priceLow - p : p - priceLow;
					if(low < val)val = low;
				}
			}
			SetValue(val);
		}
*/
	}
	virtual NamedValue* Clone() const override;
protected:
	PriceAsUIntFunction m_priceAsUIntFunctionBetween;
	PriceFunction m_priceFunctionLow;
	PriceFunction m_priceFunctionHigh;
	Price m_priceLow;
	Price m_priceHigh;
	unsigned int m_priceAsUInt;
	bool m_absValue;
};

class TU_API SecurityPriceAndPriceAsUIntLesserDiffPercent : public NamedValueMoney
{
public:
	typedef const unsigned int& (Security::*PriceAsUIntFunction)() const;
	typedef const Price& (Security::*PriceFunction)() const;
	SecurityPriceAndPriceAsUIntLesserDiffPercent(const char* name, bool absValue, PriceAsUIntFunction priceAsUIntFunctionBetween, PriceFunction priceFunctionLow, PriceFunction priceFunctionHigh, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, !absValue, name, sample, tip, displayName, parent),
		m_priceAsUIntFunctionBetween(priceAsUIntFunctionBetween),
		m_priceFunctionLow(priceFunctionLow),
		m_priceFunctionHigh(priceFunctionHigh),
		m_priceAsUInt(0),
		m_absValue(absValue)
	{
	}
	bool isValueEmpty() const{return !m_priceAsUInt || m_priceHigh.isZero() && m_priceLow.isZero();}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueMoney::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const unsigned int priceAsUInt = (m_security->*m_priceAsUIntFunctionBetween)();
			const Price priceLow = (m_security->*m_priceFunctionLow)();
			const Price priceHigh = (m_security->*m_priceFunctionHigh)();
			if(priceAsUInt != m_priceAsUInt || priceLow != m_priceLow || priceHigh != m_priceHigh)
			{
				Money val;
				const bool wasEmpty = isValueEmpty();
				m_priceAsUInt = priceAsUInt;
				m_priceLow = priceLow;
				m_priceHigh = priceHigh;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty)
				{
					SignedPrice diff;
					Price p(priceAsUInt);
					if(m_absValue)
					{
						if(priceLow.isZero())diff = priceHigh < p ? p - priceHigh : priceHigh - p;
						else if(priceHigh.isZero())diff = p < priceLow ? priceLow - p : p - priceLow;
						else
						{
							diff = priceHigh < p ? p - priceHigh : priceHigh - p;
							SignedPrice low = p < priceLow ? priceLow - p : p - priceLow;
							if(low < diff)diff = low;
						}
					}
					else
					{
						if(priceLow.isZero())diff = priceHigh - p;
						else if(priceHigh.isZero())diff = p - priceLow;
						else
						{
							diff = priceHigh - p;
							SignedPrice low = p - priceLow;
							if(low < diff)diff = low;
						}
					}
					if(!diff.isZero())
					{
						val = Money(diff);
						DivideMoneyByPrice(val, p);
					}
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
/*
			Money val;
			const unsigned int& priceAsUInt = (m_security->*m_priceAsUIntFunctionBetween)();
			if(priceAsUInt)
			{
				SignedPrice diff;
				Price p(priceAsUInt);
				const Price& priceLow = (m_security->*m_priceFunctionLow)();
				const Price& priceHigh = (m_security->*m_priceFunctionHigh)();
				if(priceLow.isZero())
				{
					if(!priceHigh.isZero())
					{
						diff = m_absValue && priceHigh < p ? p - priceHigh : priceHigh - p;
					}
				}
				else if(priceHigh.isZero())
				{
					diff = m_absValue && p < priceLow ? priceLow - p : p - priceLow;
				}
				else
				{
					diff = m_absValue && priceHigh < p ? p - priceHigh : priceHigh - p;
					SignedPrice low = m_absValue && p < priceLow ? priceLow - p : p - priceLow;
					if(low < diff)diff = low;
				}
				if(!diff.isZero())
				{
					val = Money(diff);
					DivideMoneyByPrice(val, p);
				}
			}
			SetValue(val);
*/
		}
	}
	virtual NamedValue* Clone() const override;
protected:
	PriceAsUIntFunction m_priceAsUIntFunctionBetween;
	PriceFunction m_priceFunctionLow;
	PriceFunction m_priceFunctionHigh;
	Price m_priceLow;
	Price m_priceHigh;
	unsigned int m_priceAsUInt;
	bool m_absValue;
};

class TU_API SecurityPriceDiffByPriceAsUIntDivisionNv : public NamedValueMoney//Percent
{
public:
	typedef const unsigned int& (Security::*PriceAsUIntFunction)() const;
	typedef const Price& (Security::*PriceFunction)() const;
	SecurityPriceDiffByPriceAsUIntDivisionNv(const char* name, bool absValue, PriceAsUIntFunction priceAsUIntFunction, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, !absValue, name, sample, tip, displayName, parent),
		m_priceAsUIntFunction(priceAsUIntFunction),
		m_priceFunction(priceFunction),
		m_priceAsUInt(0),
		m_absValue(absValue)
	{
	}
	bool isValueEmpty() const{return !m_priceAsUInt || m_denominator.isZero();}

	virtual void toString(std::string& str) const override
	{
		if(m_priceAsUInt && !m_denominator.isZero())
		{
			NamedValueMoney::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
/*
			Money val;
			const unsigned int& priceAsUInt = (m_security->*m_priceAsUIntFunction)();
			const Price& price = (m_security->*m_priceFunction)();
			if(priceAsUInt != 0 && !price.isZero())
			{
				Price p(priceAsUInt);
				val = Money(price < p || !m_absValue ? p - price : price - p);
				DivideMoneyByPrice(val, price);
			}
*/
			const unsigned int priceAsUInt = (m_security->*m_priceAsUIntFunction)();
			const Price price = (m_security->*m_priceFunction)();
			if(priceAsUInt != m_priceAsUInt || price != m_denominator)
			{
				Money val;
				const bool wasEmpty = isValueEmpty();
				m_priceAsUInt = priceAsUInt;
				m_denominator = price;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty)
				{
					Price p(m_priceAsUInt);
					val = Money(m_denominator < p || !m_absValue ? p - m_denominator : m_denominator - p);
					DivideMoneyByPrice(val, m_denominator);
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
	}
	virtual NamedValue* Clone() const override;
protected:
	PriceAsUIntFunction m_priceAsUIntFunction;
	PriceFunction m_priceFunction;
	unsigned int m_priceAsUInt;
	Price m_denominator;
	bool m_absValue;
};

class TU_API SecurityValueMoneyDividedByUInt64 : public NamedValueMoney
{
public:
	typedef const Money& (Security::*MoneyFunction)() const;
	typedef const unsigned __int64& (Security::*UInt64Function)() const;
	SecurityValueMoneyDividedByUInt64(const char* name, MoneyFunction moneyFunction, UInt64Function uint64Function, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, canBeNegative, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction),
		m_uint64Function(uint64Function),
		m_number(0),
		m_canBeNegative(canBeNegative)
	{
	}
	bool isValueEmpty() const{return !m_number;}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueMoney::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const unsigned __int64 number = (m_security->*m_uint64Function)();
			const Money money = (m_security->*m_moneyFunction)();
			if(number != m_number || money != m_money)
			{
				Money val;
				const bool wasEmpty = isValueEmpty();
				m_number = number;
				m_money = money;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty)
				{
					val = money;
					if(!m_canBeNegative && val.isNegative())
					{
						val = -val;
					}
					val /= number;
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
	}
	virtual NamedValue* Clone() const override;
//	virtual COLORREF GetValueColor() const;
protected:
	MoneyFunction m_moneyFunction;
	UInt64Function m_uint64Function;
	Money m_money;
	unsigned __int64 m_number;
	bool m_canBeNegative;
};

class TU_API SecurityValueIntDividedByUInt64 : public NamedValueMoney
{
public:
	typedef const int& (Security::*IntFunction)() const;
	typedef const unsigned __int64& (Security::*UInt64Function)() const;
	SecurityValueIntDividedByUInt64(const char* name, IntFunction intFunction, UInt64Function uint64Function, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, canBeNegative, name, sample, tip, displayName, parent),
		m_intFunction(intFunction),
		m_uint64Function(uint64Function),
		m_numerator(0),
		m_denominator(0),
		m_canBeNegative(canBeNegative)
	{
	}
	bool isValueEmpty() const{return !m_denominator;}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueMoney::toString(str);
			str += '%';
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const unsigned __int64 denominator = (m_security->*m_uint64Function)();
			int numerator = (m_security->*m_intFunction)();
			if(numerator != m_numerator || denominator != m_denominator)
			{
				Money val;
				const bool wasEmpty = isValueEmpty();
				m_denominator = denominator;
				m_numerator = numerator;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty && numerator)
				{
					if(!m_canBeNegative && numerator < 0)numerator = -numerator;
					val = Money(numerator * 100, 0);
					val /= denominator;
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
	}
	virtual NamedValue* Clone() const override;
//	virtual COLORREF GetValueColor() const;
protected:
	IntFunction m_intFunction;
	UInt64Function m_uint64Function;
	int m_numerator;
	unsigned __int64 m_denominator;
	bool m_canBeNegative;
};

class TU_API SecurityValueIntByIntDivisionFraction : public NamedValueMoney
{
public:
	typedef const int& (Security::*IntFunction)() const;
	SecurityValueIntByIntDivisionFraction(const char* name, IntFunction intFunction, IntFunction intFunction2, bool canBeNegative, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_SECURITY, canBeNegative, name, sample, tip, displayName, parent),
		m_intFunction(intFunction),
		m_intFunction2(intFunction2),
		m_numerator(0),
		m_denominator(0),
		m_canBeNegative(canBeNegative)
	{
	}
	bool isValueEmpty() const{return !m_denominator;}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueMoney::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			int denominator = (m_security->*m_intFunction2)();
			int numerator = (m_security->*m_intFunction)();
			if(numerator != m_numerator || denominator != m_denominator)
			{
				Money val;
				const bool wasEmpty = isValueEmpty();
				m_denominator = denominator;
				m_numerator = numerator;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty && numerator)
				{
					if(!m_canBeNegative)
					{
						if(numerator < 0)numerator = -numerator;
						if(denominator < 0)denominator = -denominator;
					}
					val = Money(numerator, 0);
					val /= denominator;
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
	}
/*
	virtual void toString(std::string& str) const override
	{
		NamedValueMoney::toString(str);
		str += '%';
	}
*/
	virtual NamedValue* Clone() const override;
//	virtual COLORREF GetValueColor() const;
protected:
	IntFunction m_intFunction;
	IntFunction m_intFunction2;
	int m_numerator;
	int m_denominator;
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
		m_uintFunction(uintFunction),
		m_number(0),
		m_price(0)
//		m_canBeNegative(canBeNegative)
	{
	}
	bool isValueEmpty() const{return !m_number || !m_price || m_money.isZero();}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueMoney::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const Money money = (m_security->*m_moneyFunction)();
			const unsigned __int64 number = (m_security->*m_uint64Function)();
			const unsigned int price = (m_security->*m_uintFunction)();
			if (money != m_money || number != m_number || price != m_price)
			{
				Money val;
				const bool wasEmpty = isValueEmpty();
				m_money = money;
				m_number = number;
				m_price = price;
				const bool nowEmpty = isValueEmpty();
				if (!nowEmpty)
				{
					val = Money(price) - money / number;
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
/*
			unsigned __int64 number = (m_security->*m_uint64Function)();
			unsigned int price = (m_security->*m_uintFunction)();
			Money money = (m_security->*m_moneyFunction)();
//			SetValue(number && price && !money.isZero() ? Money(price) - money.operator/(number) : Money(0, 0));
			SetValue(number && price && !money.isZero() ? Money(price) - money / number : Money(0, 0));
*/
		}
	}
	virtual NamedValue* Clone() const override;
//	virtual COLORREF GetValueColor() const override;
protected:
	MoneyFunction m_moneyFunction;
	UInt64Function m_uint64Function;
	UIntFunction m_uintFunction;
	Money m_money;
	unsigned __int64 m_number;
	unsigned int m_price;
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
		m_uintFunction(uintFunction),
		m_number(0),
		m_price(0)
//		m_canBeNegative(canBeNegative)
	{
	}
	bool isValueEmpty() const{return !m_number || !m_price || m_money.isZero();}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueMoney::toString(str);
			str += '%';
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const Money money = (m_security->*m_moneyFunction)();
			const unsigned __int64 number = (m_security->*m_uint64Function)();
			const unsigned int price = (m_security->*m_uintFunction)();
			if(money != m_money || number != m_number || price != m_price)
			{
				Money val;
				const bool wasEmpty = isValueEmpty();
				m_money = money;
				m_number = number;
				m_price = price;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty)
				{
					val = money / number;
					val = val.GetPercentChange(Money(price) - val);
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
/*
		if(m_valid)
		{
			unsigned __int64 number = (m_security->*m_uint64Function)();
			unsigned int price = (m_security->*m_uintFunction)();
			Money money = (m_security->*m_moneyFunction)();
			if(number && price && !money.isZero())
			{
				Money vwap = money / number;
				SetValue(vwap.GetPercentChange(Money(price) - vwap));
			}
			else
			{
				return SetValue(Money(0, 0));
			}
		}
*/
	}
	virtual NamedValue* Clone() const override;
//	virtual COLORREF GetValueColor() const override;
protected:
	MoneyFunction m_moneyFunction;
	UInt64Function m_uint64Function;
	UIntFunction m_uintFunction;
	Money m_money;
	unsigned __int64 m_number;
	unsigned int m_price;
//	bool m_canBeNegative;
};

class TU_API NamedValueSecurityPercentChange : public NamedValueSignedPrice
{
public:
	typedef const SignedPrice& (Security::*ChangeFunction)() const;
	typedef const Price& (Security::*BaseFunction)() const;
	NamedValueSecurityPercentChange(const char* name, bool valueColorCoded, ChangeFunction changeFunction, BaseFunction baseFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
//		NamedValueSignedPrice(ValueType type, bool valueColorCoded, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
//		NamedValueSignedPrice(NVT_SECURITY, true, "%Net", "-99.999%", "% Net Change (from Yesterday's Close)")
		NamedValueSignedPrice(NVT_SECURITY, valueColorCoded, name, sample, tip, displayName, parent),
		m_changeFunction(changeFunction),
		m_baseFunction(baseFunction)
	{
	}
//	NamedValueSecurityPercentChange(const NamedValueSecurityPercentChange& other):NamedValueSignedPrice(other){}
	bool isValueEmpty() const{return m_baseValue.isZero();}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueSignedPrice::toString(str);
			str += '%';
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const Price& baseValue = (m_security->*m_baseFunction)();
			const SignedPrice& netChange = (m_security->*m_changeFunction)();
			if(netChange != m_netChange || baseValue != m_baseValue)
			{
				SignedPrice val;
				const bool wasEmpty = isValueEmpty();
				m_netChange = netChange;
				m_baseValue = baseValue;
				const bool nowEmpty = isValueEmpty();
//				SetValue(m_security->GetClosePrice().GetPercentChange(m_netChange));
				if(!nowEmpty && !netChange.isZero())
				{
					val = baseValue.GetPercentChange(netChange);
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
	}
	virtual NamedValue* Clone() const override;
protected:
	ChangeFunction m_changeFunction;
	BaseFunction m_baseFunction;
	SignedPrice m_netChange;
	Price m_baseValue;
};
/*
class TU_API NamedValueSecurityNitePercentChange : public NamedValueSignedPrice
{
public:
	NamedValueSecurityNitePercentChange():NamedValueSignedPrice(NVT_SECURITY, true, "%Nite", "-99.999%", "% Nite Change (difference between the Open price and Yesterday's Close price)")
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
*/
/*
class TU_API NamedValueSecurityOpenPercentChange : public NamedValueSignedPrice
{
public:
	NamedValueSecurityOpenPercentChange():NamedValueSignedPrice(NVT_SECURITY, true, "%NetOpen", "-99.999%", "% Net Open Change (from Today's Open)")
	{
	}
//	NamedValueSecurityOpenPercentChange(const NamedValueSecurityOpenPercentChange& other):NamedValueSignedPrice(other){}
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
*/
/*
class TU_API NamedValueSecurityQOpenPercentChange : public NamedValueSignedPrice
{
public:
	NamedValueSecurityQOpenPercentChange():NamedValueSignedPrice(NVT_SECURITY, true, "%QNetOpen", "-99.999%", "% Net Open Change (from Today's Open, initialized by real opening print with sale condition O or Q))")
	{
	}
//	NamedValueSecurityQOpenPercentChange(const NamedValueSecurityQOpenPercentChange& other):NamedValueSignedPrice(other){}
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
*/
/*
class TU_API NamedValueSecurityTClosePercentChange : public NamedValueSignedPrice
{
public:
	NamedValueSecurityTClosePercentChange():NamedValueSignedPrice(NVT_SECURITY, true, "%NetTClose", "-99.999%", "% Net Todays Close Change (from Today's Close)")
	{
	}
//	NamedValueSecurityTClosePercentChange(const NamedValueSecurityTClosePercentChange& other):NamedValueSignedPrice(other){}
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
*/
class TU_API NamedValueSecuritySpread : public NamedValueSignedPrice
{
public:
	NamedValueSecuritySpread():
		NamedValueSignedPrice(NVT_SECURITY, true, "Spread", "-99.999", "Level1 Spread (Ask - Bid)"),
		m_bidAsUInt(0),
		m_askAsUInt(0)
	{
	}
//	NamedValueSecuritySpread(const NamedValueSecuritySpread& other):NamedValueSignedPrice(other){}
	bool isValueEmpty() const{return !m_bidAsUInt || !m_askAsUInt;}
	virtual void toString(std::string& str) const override
	{
		if(!isValueEmpty())
		{
			NamedValueSignedPrice::toString(str);
		}
	}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const unsigned int bidAsUInt = m_security->GetL1Bid();
			const unsigned int askAsUInt = m_security->GetL1Ask();
			if(bidAsUInt != m_bidAsUInt || askAsUInt != m_askAsUInt)
			{
				SignedPrice val;
				const bool wasEmpty = isValueEmpty();
				m_bidAsUInt = bidAsUInt;
				m_askAsUInt = askAsUInt;
				const bool nowEmpty = isValueEmpty();
				if(!nowEmpty)
				{
					val = SignedPrice(askAsUInt) - SignedPrice(bidAsUInt);
				}
				SetValue(val, wasEmpty != nowEmpty);
			}
		}
	}
	virtual NamedValue* Clone() const override;
protected:
	unsigned int m_bidAsUInt;
	unsigned int m_askAsUInt;
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override {return (m_position->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API PositionValueInventoryPrice : public NamedValuePrice
{
public:
	typedef const VType& (Position::*PriceFunction)(const bool& inventoryView) const;
	PositionValueInventoryPrice(const char* name, const bool* inventoryView, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValuePrice(NVT_POSITION, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction),
		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_position->*m_priceFunction)(m_inventoryView && *m_inventoryView);}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	PriceFunction m_priceFunction;
	const bool* m_inventoryView;
};

class TU_API PositionValueColoredPrice : public PositionValuePrice
{
public:
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			bool force = false;
			const Money& pnl = GetPnl();
			if(m_pnl != pnl)
			{
				if(m_pnl.isPositive() != pnl.isPositive() || m_pnl.isNegative() != pnl.isNegative())
				{
					force = true;
//					m_parent->InvalidateWndRect(m_rectValue);
				}
				m_pnl = pnl;
			}
			SetValue((m_position->*m_priceFunction)(), force);
		}
	}
	virtual COLORREF GetValueColor() const override
	{
		return m_colored ?
			m_pnl.isPositive() ? m_parent->GetValueColorPositive():
			m_pnl.isNegative() ? m_parent->GetValueColorNegative():
			m_parent->GetValueColorNeutral():
			m_parent->GetValueColorNeutral();
	}
//	virtual const VType& GetObjectValue() const{return (m_position->*m_priceFunction)();}
	virtual Money GetPnl() const = 0;
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

class TU_API PositionValueInventoryColoredPrice : public PositionValueInventoryPrice
{
public:
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			bool force = false;
			const Money& pnl = GetPnl();
			if(m_pnl != pnl)
			{
				if(m_pnl.isPositive() != pnl.isPositive() || m_pnl.isNegative() != pnl.isNegative())
				{
					force = true;
//					m_parent->InvalidateWndRect(m_rectValue);
				}
				m_pnl = pnl;
			}
			SetValue((m_position->*m_priceFunction)(m_inventoryView && *m_inventoryView), force);
		}
	}
	virtual COLORREF GetValueColor() const override
	{
		return m_colored ?
			m_pnl.isPositive() ? m_parent->GetValueColorPositive():
			m_pnl.isNegative() ? m_parent->GetValueColorNegative():
			m_parent->GetValueColorNeutral():
			m_parent->GetValueColorNeutral();
	}
//	virtual const VType& GetObjectValue() const{return (m_position->*m_priceFunction)();}
	virtual Money GetPnl() const = 0;
protected:
	PositionValueInventoryColoredPrice(bool colored, const char* name, const bool* inventoryView, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueInventoryPrice(name, inventoryView, &Position::GetAveragePriceInv, sample, tip, displayName, parent),
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
	virtual Money GetPnl() const override{return m_position->GetOpenPnlPrint();}
	virtual NamedValue* Clone() const override;
};

class TU_API PositionValueColoredPriceNbboPrint : public PositionValueColoredPrice
{
public:
	PositionValueColoredPriceNbboPrint(bool colored, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueColoredPrice(colored, name, sample, tip, displayName, parent)
	{
	}
	virtual Money GetPnl() const override{return m_position->GetOpenPnlNbboPrint();}
	virtual NamedValue* Clone() const override;
};

class TU_API PositionValueColoredPriceLevel1 : public PositionValueColoredPrice
{
public:
	PositionValueColoredPriceLevel1(bool colored, const char* name, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueColoredPrice(colored, name, sample, tip, displayName, parent)
	{
	}
	virtual Money GetPnl() const override{return m_position->GetOpenPnlLevel1();}
	virtual NamedValue* Clone() const override;
};

////
class TU_API PositionValueInventoryColoredPricePrint : public PositionValueInventoryColoredPrice
{
public:
	PositionValueInventoryColoredPricePrint(bool colored, const char* name, const bool* inventoryView, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueInventoryColoredPrice(colored, name, inventoryView, sample, tip, displayName, parent)
	{
	}
	virtual Money GetPnl() const override{return m_position->GetOpenPnlPrint();}
	virtual NamedValue* Clone() const override;
};

class TU_API PositionValueInventoryColoredPriceNbboPrint : public PositionValueInventoryColoredPrice
{
public:
	PositionValueInventoryColoredPriceNbboPrint(bool colored, const char* name, const bool* inventoryView, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueInventoryColoredPrice(colored, name, inventoryView, sample, tip, displayName, parent)
	{
	}
	virtual Money GetPnl() const override{return m_position->GetOpenPnlNbboPrint();}
	virtual NamedValue* Clone() const override;
};

class TU_API PositionValueInventoryColoredPriceLevel1 : public PositionValueInventoryColoredPrice
{
public:
	PositionValueInventoryColoredPriceLevel1(bool colored, const char* name, const bool* inventoryView, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueInventoryColoredPrice(colored, name, inventoryView, sample, tip, displayName, parent)
	{
	}
	virtual Money GetPnl() const override{return m_position->GetOpenPnlLevel1();}
	virtual NamedValue* Clone() const override;
};

////

class TU_API PositionValueSignedPrice : public NamedValueSignedPrice
{
public:
	typedef const VType& (Position::*PriceFunction)() const;
	PositionValueSignedPrice(const char* name, bool valueColorCoded, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_POSITION, valueColorCoded, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_position->*m_priceFunction)();}
protected:
	PriceFunction m_priceFunction;
};

class TU_API PositionValueInventorySignedPrice : public NamedValueSignedPrice
{
public:
	typedef const VType& (Position::*PriceFunction)(const bool& inventoryView) const;
	PositionValueInventorySignedPrice(const char* name, bool valueColorCoded, const bool* inventoryView, PriceFunction priceFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueSignedPrice(NVT_POSITION, valueColorCoded, name, sample, tip, displayName, parent),
		m_priceFunction(priceFunction),
		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_position->*m_priceFunction)(m_inventoryView && *m_inventoryView);}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	PriceFunction m_priceFunction;
	const bool* m_inventoryView;
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_position->*m_moneyFunction)();}
protected:
	MoneyFunction m_moneyFunction;
};

class TU_API PositionValueInventoryMoney : public NamedValueMoney
{
public:
	typedef const VType& (Position::*MoneyFunction)(const bool& inventoryView) const;
	PositionValueInventoryMoney(bool valueColorCoded, const char* name, const bool* inventoryView, MoneyFunction moneyFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_POSITION, valueColorCoded, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction),
		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_position->*m_moneyFunction)(m_inventoryView && *m_inventoryView);}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	MoneyFunction m_moneyFunction;
	const bool* m_inventoryView;
};

class TU_API PositionValueInventoryVMoney : public NamedValueMoney
{
public:
	typedef VType (Position::*MoneyFunction)(const bool& inventoryView) const;
	PositionValueInventoryVMoney(bool valueColorCoded, const char* name, const bool* inventoryView, MoneyFunction moneyFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_POSITION, valueColorCoded, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction),
		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
//	virtual const VType& GetObjectValue() const override{return (m_position->*m_moneyFunction)(m_inventoryView && *m_inventoryView);}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_position->*m_moneyFunction)(m_inventoryView && *m_inventoryView));
		}
	}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	MoneyFunction m_moneyFunction;
	const bool* m_inventoryView;
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_position->*m_uintFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_position->*m_boolFunction)();}
protected:
	BoolFunction m_boolFunction;
};

class TU_API PositionValueCount : public NamedValueUInt
{
public:
	typedef unsigned int (Position::*CountFunction)() const;
	PositionValueCount(const char* name, CountFunction countFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(NVT_POSITION, name, sample, tip, displayName, parent),
		m_countFunction(countFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
//			unsigned int count = (m_account->*m_countFunction)();
			SetValue((m_position->*m_countFunction)());
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

class TU_API PositionValueInt : public NamedValueInt
{
public:
	typedef const VType& (Position::*IntFunction)() const;
	PositionValueInt(const char* name, IntFunction intFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueInt(NVT_POSITION, name, sample, tip, displayName, parent),
		m_intFunction(intFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override {return (m_position->*m_intFunction)();}
protected:
	IntFunction m_intFunction;
};

class TU_API PositionValueIntVal : public NamedValueInt
{
public:
	typedef VType (Position::*IntFunction)() const;
	PositionValueIntVal(const char* name, IntFunction intFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueInt(NVT_POSITION, name, sample, tip, displayName, parent),
		m_intFunction(intFunction)
	{
	}
	virtual NamedValue* Clone() const override;
//	virtual const VType& GetObjectValue() const{return (m_position->*m_intFunction)();}
	virtual VType GetVal() const{return (m_position->*m_intFunction)();}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue(GetVal());
		}
	}
protected:
	IntFunction m_intFunction;
};

class TU_API PositionValueIntSign : public PositionValueIntVal
{
public:
	static const VType zero;
	static const VType one;
	static const VType minusOne;
	PositionValueIntSign(const char* name, IntFunction intFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueIntVal(name, intFunction, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const override;

	virtual VType GetVal() const override
	{
		const VType& val = (m_position->*m_intFunction)();
		return val > 0 ? one:
			val < 0 ? minusOne:
			zero;
	}
};

class TU_API PositionValueIntSignConditional : public PositionValueIntSign
{
public:
	PositionValueIntSignConditional(const char* name, IntFunction intFunction, const bool& useValue, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueIntSign(name, intFunction, sample, tip, displayName, parent),
		m_useValue(useValue)
	{
	}
	virtual NamedValue* Clone() const override;

//	virtual const VType& GetObjectValue() const
//	{
//		return m_useValue ? PositionValueInt::GetObjectValue() : PositionValueIntSign::GetObjectValue();
//	}

	virtual VType GetVal() const override
	{
		return m_useValue ? PositionValueIntVal::GetVal() : PositionValueIntSign::GetVal();
	}
protected:
	const bool& m_useValue;
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_position->*m_uintFunction)();}
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
	virtual NamedValue* Clone() const override;
//	virtual const VType& GetObjectValue() const{return (m_position->*m_uintFunction)();}
	virtual void UpdateValue() override
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
	virtual NamedValue* Clone() const override;
//	virtual const VType& GetObjectValue() const{return (m_position->*m_moneyFunction)();}
	virtual void UpdateValue() override
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
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
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
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_position->*m_moneyFunction)() + (m_position->*m_moneyFunction2)() - (m_position->*m_moneyFunction3)());
		}
	}
};

class TU_API PositionValueMoneyV : public NamedValueMoney
{
public:
	typedef VType (Position::*MoneyFunction)() const;
	PositionValueMoneyV(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_POSITION, valueColorCoded, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_position->*m_moneyFunction)());
		}
	}
protected:
	MoneyFunction m_moneyFunction;
};

class TU_API PositionValueMoney2V : public PositionValueMoneyV
{
public:
	PositionValueMoney2V(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueMoneyV(valueColorCoded, name, moneyFunction, sample, tip, displayName, parent),
		m_moneyFunction2(moneyFunction2)
	{
	}
	virtual NamedValue* Clone() const override;
//	virtual const VType& GetObjectValue() const{return (m_position->*m_moneyFunction)();}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_position->*m_moneyFunction)() + (m_position->*m_moneyFunction2)());
		}
	}
protected:
	MoneyFunction m_moneyFunction2;
};

class TU_API PositionValueMoney3V : public PositionValueMoney2V
{
public:
	PositionValueMoney3V(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		PositionValueMoney2V(valueColorCoded, name, moneyFunction, moneyFunction2, sample, tip, displayName, parent),
		m_moneyFunction3(moneyFunction3)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if (m_valid)
		{
			SetValue((m_position->*m_moneyFunction)() + (m_position->*m_moneyFunction2)() + (m_position->*m_moneyFunction3)());
		}
	}
protected:
	MoneyFunction m_moneyFunction3;
};

class TU_API PositionValueMoney3MinusV : public PositionValueMoney3V
{
public:
	PositionValueMoney3MinusV(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueMoney3V(valueColorCoded, name, moneyFunction, moneyFunction2, moneyFunction3, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
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
	virtual NamedValue* Clone() const override;
//	virtual COLORREF GetValueColor() const;
	virtual const VType& GetObjectValue() const override{return (m_account->*m_boolFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_account->*m_charFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_account->*m_moneyFunction)();}
protected:
	MoneyFunction m_moneyFunction;
};

class TU_API AccountValueMoneyV : public NamedValueMoney
{
public:
	typedef VType (Account::*MoneyFunction)() const;
	AccountValueMoneyV(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		NamedValueMoney(NVT_ACCOUNT, valueColorCoded, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_account->*m_moneyFunction)());
		}
	}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_account->*m_priceFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_account->*m_charPtrFunction)());
		}
	}
protected:
	CharPtrFunction m_charPtrFunction;
};

class TU_API AccountValueMoneyDivision : public AccountValueMoney
{
public:
	AccountValueMoneyDivision(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyDenomonatorFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueMoney(valueColorCoded, name, moneyFunction, sample, tip, displayName, parent),
		m_moneyDenomonatorFunction(moneyDenomonatorFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const Money denominator = (m_account->*m_moneyDenomonatorFunction)();
			Money value;
			if(!denominator.isZero())
			{
				value = (m_account->*m_moneyFunction)();
				if(!value.isZero())
				{
					value.SetValue(value.GetDollars() * 10000 + value.GetDollarFraction(), 0);
					value /= denominator.GetDollars() * 10000 + denominator.GetDollarFraction();
				}
			}
			SetValue(value);
		}
	}
protected:
	MoneyFunction m_moneyDenomonatorFunction;
};

class TU_API AccountValueMoneyVDivision : public AccountValueMoneyV
{
public:
	AccountValueMoneyVDivision(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyDenomonatorFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueMoneyV(valueColorCoded, name, moneyFunction, sample, tip, displayName, parent),
		m_moneyDenomonatorFunction(moneyDenomonatorFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const Money denominator = (m_account->*m_moneyDenomonatorFunction)();
			Money value;
			if(!denominator.isZero())
			{
				value = (m_account->*m_moneyFunction)();
				if(!value.isZero())
				{
					value.SetValue(value.GetDollars() * 10000 + value.GetDollarFraction(), 0);
					value /= denominator.GetDollars() * 10000 + denominator.GetDollarFraction();
				}
			}
			SetValue(value);
		}
	}
protected:
	MoneyFunction m_moneyDenomonatorFunction;
};


class TU_API AccountValueMoney2 : public AccountValueMoney
{
public:
	AccountValueMoney2(bool valueColorCoded, const char* name, MoneyFunction moneyFunction, MoneyFunction moneyFunction2, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueMoney(valueColorCoded, name, moneyFunction, sample, tip, displayName, parent),
		m_moneyFunction2(moneyFunction2)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
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
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
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
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
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
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_account->*m_ushortFunction)();}
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
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_account->*m_uintFunction)();}
protected:
	UIntFunction m_uintFunction;
};

class TU_API AccountValueUIntV : public NamedValueUInt
{
public:
	typedef VType (Account::*UIntFunction)() const;
	AccountValueUIntV(const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(NVT_ACCOUNT, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_account->*m_uintFunction)());
		}
	}
protected:
	UIntFunction m_uintFunction;
};

class TU_API AccountValueUIntZeroEmpty : public NamedValueUIntZeroEmpty
{
public:
	typedef const VType& (Account::*UIntFunction)() const;
	AccountValueUIntZeroEmpty(const char* name, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL, bool useComma = true):
		NamedValueUIntZeroEmpty(NVT_ACCOUNT, name, sample, tip, displayName, parent, useComma),
		m_uintFunction(uintFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_account->*m_uintFunction)();}
protected:
	UIntFunction m_uintFunction;
};

class TU_API PositionValueInventoryInt : public NamedValueInt
{
public:
	typedef const VType& (Position::*IntFunction)(const bool& inventoryView) const;
	PositionValueInventoryInt(const char* name, const bool* inventoryView, IntFunction intFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueInt(NVT_POSITION, name, sample, tip, displayName, parent),
		m_intFunction(intFunction),
		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_position->*m_intFunction)(m_inventoryView && *m_inventoryView);}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	IntFunction m_intFunction;
	const bool* m_inventoryView;
};

class TU_API PositionValueInventoryIntPlusMinusUIntAdj : public PositionValueInventoryInt
{
public:
	typedef const unsigned int& (Position::*UIntFunction)() const;
	PositionValueInventoryIntPlusMinusUIntAdj(const char* name, const bool* inventoryView, IntFunction intFunction, UIntFunction uintFunctionPlus, UIntFunction uintFunctionMinus, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		PositionValueInventoryInt(name, inventoryView, intFunction, sample, tip, displayName, parent),
		m_uintFunctionPlus(uintFunctionPlus),
		m_uintFunctionMinus(uintFunctionMinus)
	{
	}
	virtual NamedValue* Clone() const override;
//	virtual const VType& GetObjectValue() const{return (m_position->*m_intFunction)(m_inventoryView && *m_inventoryView) + (int)(m_position->*m_uintFunctionPlus)() - (int)(m_position->*m_uintFunctionMinus)();}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_position->*m_intFunction)(m_inventoryView && *m_inventoryView) + (int)(m_position->*m_uintFunctionPlus)() - (int)(m_position->*m_uintFunctionMinus)());
		}
	}
protected:
	UIntFunction m_uintFunctionPlus;
	UIntFunction m_uintFunctionMinus;
};

class TU_API AccountValueInventoryMoney : public NamedValueMoney
{
public:
	typedef const VType& (Account::*InvMoneyFunction)(const bool& inventoryView) const;
	AccountValueInventoryMoney(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_ACCOUNT, valueColorCoded, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction),
		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_account->*m_moneyFunction)(m_inventoryView && *m_inventoryView);}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	InvMoneyFunction m_moneyFunction;
	const bool* m_inventoryView;
};

class TU_API AccountValueInventoryVMoney : public NamedValueMoney
{
public:
	typedef VType (Account::*InvMoneyFunction)(const bool& inventoryView) const;
	AccountValueInventoryVMoney(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueMoney(NVT_ACCOUNT, valueColorCoded, name, sample, tip, displayName, parent),
		m_moneyFunction(moneyFunction),
		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
//	virtual const VType& GetObjectValue() const override{return (m_position->*m_moneyFunction)(m_inventoryView && *m_inventoryView);}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_account->*m_moneyFunction)(m_inventoryView && *m_inventoryView));
		}
	}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	InvMoneyFunction m_moneyFunction;
	const bool* m_inventoryView;
};

class TU_API AccountValueInventoryMoneyDiff : public AccountValueInventoryMoney
{
public:
//	typedef const VType& (Account::*InvMoneyFunction)(const bool& inventoryView) const;
	typedef const VType& (Account::*MoneyFunction)() const;
	AccountValueInventoryMoneyDiff(bool valueColorCoded,
		const char* name,
		const bool* inventoryView,
		InvMoneyFunction invMoneyFunction,
		MoneyFunction moneyFunction,
		const char* sample,
		const char* tip,
		const char* displayName = NULL,
		NamedValueCollection* parent = NULL):
		AccountValueInventoryMoney(valueColorCoded, name, inventoryView, invMoneyFunction, sample, tip, displayName, parent),
//		m_invMoneyFunction(invMoneyFunction),
		m_moneyFunction2(moneyFunction)
//		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
//	virtual const VType& GetObjectValue() const{return (m_account->*m_moneyFunction)(m_inventoryView);}
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_account->*m_moneyFunction)(m_inventoryView && *m_inventoryView) - (m_account->*m_moneyFunction2)());
		}
	}
protected:
//	InvMoneyFunction m_invMoneyFunction;
	MoneyFunction m_moneyFunction2;
//	const bool& m_inventoryView;
};

class TU_API AccountValueInventoryMoney2 : public AccountValueInventoryMoney
{
public:
//	typedef const VType& (Account::*InvMoneyFunction)(const bool& inventoryView) const;
	AccountValueInventoryMoney2(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, InvMoneyFunction moneyFunction2, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		AccountValueInventoryMoney(valueColorCoded, name, inventoryView, moneyFunction, sample, tip, displayName, parent),
		m_moneyFunction2(moneyFunction2)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_moneyFunction)(inventoryView) + (m_account->*m_moneyFunction2)(inventoryView));
		}
	}
protected:
	InvMoneyFunction m_moneyFunction2;
};

class TU_API AccountValueInventoryMoney2Minus : public AccountValueInventoryMoney2
{
public:
	AccountValueInventoryMoney2Minus(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, InvMoneyFunction moneyFunction2, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		AccountValueInventoryMoney2(valueColorCoded, name, inventoryView, moneyFunction, moneyFunction2, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_moneyFunction)(inventoryView) - (m_account->*m_moneyFunction2)(inventoryView));
		}
	}
};

class TU_API AccountValueInventoryMoney3 : public AccountValueInventoryMoney2
{
public:
//	typedef const VType& (Account::*InvMoneyFunction)(const bool& inventoryView) const;
	AccountValueInventoryMoney3(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, InvMoneyFunction moneyFunction2, InvMoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		AccountValueInventoryMoney2(valueColorCoded, name, inventoryView, moneyFunction, moneyFunction2, sample, tip, displayName, parent),
		m_moneyFunction3(moneyFunction3)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_moneyFunction)(inventoryView) + (m_account->*m_moneyFunction2)(inventoryView) + (m_account->*m_moneyFunction3)(inventoryView));
		}
	}
protected:
	InvMoneyFunction m_moneyFunction3;
};

class TU_API AccountValueInventoryMoney21 : public AccountValueInventoryMoney2
{
public:
	typedef const VType& (Account::*MoneyFunction)() const;
	AccountValueInventoryMoney21(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, InvMoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		AccountValueInventoryMoney2(valueColorCoded, name, inventoryView, moneyFunction, moneyFunction2, sample, tip, displayName, parent),
		m_moneyFunction3(moneyFunction3)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_moneyFunction)(inventoryView) + (m_account->*m_moneyFunction2)(inventoryView) + (m_account->*m_moneyFunction3)());
		}
	}
protected:
	MoneyFunction m_moneyFunction3;
};

class TU_API AccountValueInventoryMoney21Minus : public AccountValueInventoryMoney21
{
public:
	AccountValueInventoryMoney21Minus(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, InvMoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		AccountValueInventoryMoney21(valueColorCoded, name, inventoryView, moneyFunction, moneyFunction2, moneyFunction3, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_moneyFunction)(inventoryView) + (m_account->*m_moneyFunction2)(inventoryView) - (m_account->*m_moneyFunction3)());
		}
	}
};

class TU_API AccountValueInventoryVMoney2 : public AccountValueInventoryVMoney
{
public:
	AccountValueInventoryVMoney2(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, InvMoneyFunction moneyFunction2, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		AccountValueInventoryVMoney(valueColorCoded, name, inventoryView, moneyFunction, sample, tip, displayName, parent),
		m_moneyFunction2(moneyFunction2)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_moneyFunction)(inventoryView) + (m_account->*m_moneyFunction2)(inventoryView));
		}
	}
protected:
	InvMoneyFunction m_moneyFunction2;
};

class TU_API AccountValueInventoryVMoney2Minus : public AccountValueInventoryVMoney2
{
public:
	AccountValueInventoryVMoney2Minus(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, InvMoneyFunction moneyFunction2, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		AccountValueInventoryVMoney2(valueColorCoded, name, inventoryView, moneyFunction, moneyFunction2, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_moneyFunction)(inventoryView) - (m_account->*m_moneyFunction2)(inventoryView));
		}
	}
};

class TU_API AccountValueInventoryVMoney21 : public AccountValueInventoryVMoney2
{
public:
	typedef VType (Account::*MoneyFunction)() const;
	AccountValueInventoryVMoney21(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, InvMoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		AccountValueInventoryVMoney2(valueColorCoded, name, inventoryView, moneyFunction, moneyFunction2, sample, tip, displayName, parent),
		m_moneyFunction3(moneyFunction3)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_moneyFunction)(inventoryView) + (m_account->*m_moneyFunction2)(inventoryView) + (m_account->*m_moneyFunction3)());
		}
	}
protected:
	MoneyFunction m_moneyFunction3;
};

class TU_API AccountValueInventoryVMoney21Minus : public AccountValueInventoryVMoney21
{
public:
	AccountValueInventoryVMoney21Minus(bool valueColorCoded, const char* name, const bool* inventoryView, InvMoneyFunction moneyFunction, InvMoneyFunction moneyFunction2, MoneyFunction moneyFunction3, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		AccountValueInventoryVMoney21(valueColorCoded, name, inventoryView, moneyFunction, moneyFunction2, moneyFunction3, sample, tip, displayName, parent)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_moneyFunction)(inventoryView) + (m_account->*m_moneyFunction2)(inventoryView) - (m_account->*m_moneyFunction3)());
		}
	}
};

class TU_API AccountValueInventoryVMoneyDiff : public AccountValueInventoryVMoney
{
public:
	typedef VType (Account::*MoneyFunction)() const;
	AccountValueInventoryVMoneyDiff(bool valueColorCoded,
		const char* name,
		const bool* inventoryView,
		InvMoneyFunction invMoneyFunction,
		MoneyFunction moneyFunction,
		const char* sample,
		const char* tip,
		const char* displayName = NULL,
		NamedValueCollection* parent = NULL):
		AccountValueInventoryVMoney(valueColorCoded, name, inventoryView, invMoneyFunction, sample, tip, displayName, parent),
//		m_invMoneyFunction(invMoneyFunction),
		m_moneyFunction2(moneyFunction)
//		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
			SetValue((m_account->*m_moneyFunction)(m_inventoryView && *m_inventoryView) - (m_account->*m_moneyFunction2)());
		}
	}
protected:
	MoneyFunction m_moneyFunction2;
};


class TU_API AccountValueInventoryUInt : public NamedValueUInt
{
public:
	typedef const VType& (Account::*UIntFunction)(const bool& inventoryView) const;
	AccountValueInventoryUInt(const char* name, const bool* inventoryView, UIntFunction uintFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(NVT_ACCOUNT, name, sample, tip, displayName, parent),
		m_uintFunction(uintFunction),
		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual const VType& GetObjectValue() const override{return (m_account->*m_uintFunction)(m_inventoryView && *m_inventoryView);}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	UIntFunction m_uintFunction;
	const bool* m_inventoryView;
};

class TU_API AccountValueCount : public NamedValueUInt
{
public:
	typedef VType (Account::*CountFunction)() const;
	AccountValueCount(const char* name, CountFunction countFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL):
		NamedValueUInt(NVT_ACCOUNT, name, sample, tip, displayName, parent),
		m_countFunction(countFunction)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
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

class TU_API AccountValueInventoryCount : public NamedValueUInt
{
public:
	typedef VType (Account::*CountFunction)(const bool& inventoryView) const;
	AccountValueInventoryCount(const char* name, const bool* inventoryView, CountFunction countFunction, const char* sample, const char* tip, const char* displayName = NULL, NamedValueCollection* parent = NULL) :
		NamedValueUInt(NVT_ACCOUNT, name, sample, tip, displayName, parent),
		m_countFunction(countFunction),
		m_inventoryView(inventoryView)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void UpdateValue() override
	{
		if(m_valid)
		{
//			const bool inventoryView = m_inventoryView && *m_inventoryView;
			SetValue((m_account->*m_countFunction)(m_inventoryView && *m_inventoryView));
		}
	}
	virtual void SetInventoryView(const bool* inventoryView) override{m_inventoryView = inventoryView;}
	virtual bool isInventoryView() const override{return m_inventoryView != NULL && *m_inventoryView;}
protected:
	CountFunction m_countFunction;
	const bool* m_inventoryView;
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
	virtual NamedValue* Clone() const override;
	virtual COLORREF GetValueColor() const override;
	virtual void toString(std::string& str) const override;
};

#ifndef TAKION_NO_OPTIONS

class TU_API AccountOptionVenue : public AccountValueUInt
{
public:
	AccountOptionVenue(const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueUInt("oVenue", &Account::GetOptionVenue, "WWWW", "Venue to send Option Orders to", displayName, parent)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void toString(std::string& str) const override;
};

#endif

class TU_API AccountLocateVenue : public AccountValueUInt
{
public:
	AccountLocateVenue(const char* displayName = NULL, NamedValueCollection* parent = NULL):
		AccountValueUInt("lVenue", &Account::GetLocateVenue, "WWWW", "Venue to send Borrow Orders to", displayName, parent)
	{
	}
	virtual NamedValue* Clone() const override;
	virtual void toString(std::string& str) const override;
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

//class RingBufferListEventNotification;

class TU_API MessageThread : public MessageThreadBase
{
protected:
	MessageThread(const char* name, int priority = 0, unsigned int waitToTerminate = INFINITE, unsigned int padSize = 0):
		MessageThreadBase(name, priority, waitToTerminate, padSize)
	{}
	virtual void Log(const char* info, const char* prefix) const;
};

////////////////////
