// TakionData.h : main header file for the TakionData DLL

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef TD_EXPORTS
#define TD_API __declspec(dllexport)
#else
#define TD_API __declspec(dllimport)
#endif

const char* const TakionDataHeaderVersion = "1.0.1.214";

//#define TAKION_EXCEPTION
//class RingBufferListEventNotification;

#include <TakionUtilsApi.h>
#include <TakionLogApi.h>
//#include <TakionMemoryApi.h>

//#define UPDATE_PRINT_MESSAGE
const unsigned int qstkNum = 0x4B545351;//*(unsigned int*)"QSTK";

enum MessageIds : unsigned short
{
    M_SYSTEM_EVENT = 1,//MARKET_DATA_START + 1,

    // Book related messages
    M_BOOK_NEW_QUOTE,
    M_BOOK_MODIFY_QUOTE,
    M_BOOK_DELETE_QUOTE,
    M_BOOK_ORDER_EXECUTED,
    M_BOOK_ORDER_EXECUTED_WITH_PRICE,
    M_BOOK_ORDER_CANCELED,
    M_BOOK_TRADE,
    M_BOOK_CROSS_TRADE,

    // Stock related messages
    M_STOCK_DIRECTORY,
    M_STOCK_TRADING_ACTION,
    M_STOCK_IMBALANCE_INDICATOR,

    // Refresh request and response
    M_REQ_REFRESH_SYMBOL,
    M_RESP_REFRESH_SYMBOL,

    // Used internaly to notify Aggregated Book
//    M_QUOTE_SIZE_CHANGE,
    M_RESET_BOOK = 16,

    // Level1
    M_LEVEL1,

    // Trades
    M_TRADE_REPORT,
    M_TRADE_CANCEL_ERROR,
    M_TRADE_CORRECTION,

    // HACK for Blizzard
//    M_TRADE_BLIZZARD,
    
	M_REQ_UNSUBSCRIBE_SYMBOL = 22,

	M_RESET_SYMBOL,

	M_EOD_SUMMARY_REPORT,
	M_SHORT_SALE_INDICATORS,
	M_DIVIDENDS_AND_SPLITS,
	M_PREVIOUS_DAY_CLOSE,
	M_RESET_IMBALANCES,

	M_PMI,
	M_LRP,
	M_T_TIME,
	M_RPI,

	M_AGGREGATED_PRINT,

	M_LULD,
//	M_REQ_KICK,

// Should be last enum member
    MARKET_DATA_END,

    SM_M_SYSTEM_EVENT = 201,//MARKET_DATA_START + 1,

    // Book related messages
    SM_M_BOOK_NEW_QUOTE = 202,
    SM_M_BOOK_MODIFY_QUOTE,
    SM_M_BOOK_DELETE_QUOTE,
    SM_M_BOOK_ORDER_EXECUTED,
    SM_M_BOOK_ORDER_EXECUTED_WITH_PRICE,
    SM_M_BOOK_ORDER_CANCELED,
    SM_M_BOOK_TRADE,
    SM_M_BOOK_CROSS_TRADE,

    // Stock related messages
    SM_M_STOCK_DIRECTORY,
    SM_M_STOCK_TRADING_ACTION,
    SM_M_STOCK_IMBALANCE_INDICATOR,

    // Refresh request and response
//    M_REQ_REFRESH_SYMBOL,
    SM_M_RESP_REFRESH_SYMBOL = 214,

    // Used internaly to notify Aggregated Book
//    SM_M_QUOTE_SIZE_CHANGE,
    SM_M_RESET_BOOK = 216,

    // Level1
    SM_M_LEVEL1 = 217,

    // Trades
    SM_M_TRADE_REPORT,
    SM_M_TRADE_CANCEL_ERROR,
    SM_M_TRADE_CORRECTION,

    // HACK for Blizzard
//    M_TRADE_BLIZZARD,
    
//	SM_M_REQ_UNSUBSCRIBE_SYMBOL = 222,

	SM_M_RESET_SYMBOL = 223,

	SM_M_EOD_SUMMARY_REPORT,
	SM_M_SHORT_SALE_INDICATORS,
	SM_M_DIVIDENDS_AND_SPLITS,
	SM_M_PREVIOUS_DAY_CLOSE,
	SM_M_RESET_IMBALANCES,

	SM_M_PMI,
	SM_M_LRP,
	SM_M_T_TIME,
	SM_M_RPI,

	SM_M_AGGREGATED_PRINT,

	SM_M_LULD,

// Should be last enum member
    SYMBOL_MAPPING_MD_END,

//MarketSorter messages
	M_MS_LEVEL1_SHORT = 501,
	M_MS_LEVEL1_LONG,
	M_MS_TRADE_REPORT_SHORT,
	M_MS_TRADE_REPORT_LONG,
	M_MS_IMBALANCE_SHORT,
	M_MS_IMBALANCE_LONG,
	M_MS_TRADE_CORRECTION,
	M_MS_TRADE_CANCEL_ERROR,
	M_MS_EOD_SUMMARY_REPORT,
	M_MS_SHORT_SALE_INDICATORS,
	M_MS_DIVIDENDS_AND_SPLITS,
	M_MS_PREVIOUS_DAY_CLOSE,
	M_MS_STOCK_TRADING_ACTION,
	M_MS_RESET_IMBALANCES,

	M_MS_PMI,
	M_MS_LRP,
	M_MS_T_TIME,
	M_MS_RPI,	// Should be last enum member
	M_MS_AGGREGATED_PRINT_SHORT,
	M_MS_AGGREGATED_PRINT_LONG,

	M_MS_LULD,

	MARKET_SORTER_END,
/////////////////////////
//MarketSorter messages
	SM_MS_LEVEL1_SHORT = 601,
	SM_MS_LEVEL1_LONG,
	SM_MS_TRADE_REPORT_SHORT,
	SM_MS_TRADE_REPORT_LONG,
	SM_MS_IMBALANCE_SHORT,
	SM_MS_IMBALANCE_LONG,
	SM_MS_TRADE_CORRECTION,
	SM_MS_TRADE_CANCEL_ERROR,
	SM_MS_EOD_SUMMARY_REPORT,
	SM_MS_SHORT_SALE_INDICATORS,
	SM_MS_DIVIDENDS_AND_SPLITS,
	SM_MS_PREVIOUS_DAY_CLOSE,
	SM_MS_STOCK_TRADING_ACTION,
	SM_MS_RESET_IMBALANCES,

	SM_MS_PMI,
	SM_MS_LRP,
	SM_MS_T_TIME,
	SM_MS_RPI,

	SM_MS_AGGREGATED_PRINT_SHORT,
	SM_MS_AGGREGATED_PRINT_LONG,

	SM_MS_LULD,

	SYMBOL_MAPPING_MS_END,// Should be last enum member
/////////////////////////
	M_REQ_CHART = 701,
	M_RESP_CHART,
	M_NEW_TICK,
	M_TICK_CORRECTION,
		
	SM_REQ_CHART = 751,
	SM_RESP_CHART = 752,
	SM_NEW_TICK,
	SM_TICK_CORRECTION,

	M_INDEX = 802,// Index Update, includes only last
	M_REQ_REFRESH_INDEX,// Refresh request and response
	M_RESP_REFRESH_INDEX,
	M_REQ_INDEX_CHART,// Index Chart Messages
	M_RESP_INDEX_CHART,

	// Should be last enum member
//	CHARTS_END,
	M_INDEX_NEW_TICK,

	M_REQ_MD_LOGON = 1001,
	M_RESP_MD_LOGON,
	M_REQ_PUBLIC_KEY,
	M_RESP_PUBLIC_KEY,

	M_HEARTBEAT = 2001,
	M_DISCONNECT,
	M_TEXT,

//#define TS_MESSAGE_START				10000
	TS_LOGIN_REQ						= 10001,
	TS_LOGIN_REJECT,
	TS_LOGIN_RESP,
	TS_LOGOUT_REQ,
	TS_ACCOUNT_RISK_PROFILE,
	TS_NEW_ACCOUNT,
	TS_ACCOUNT_POSITION_REQ,
	TS_ACCOUNT_POSITION,
	TS_ACCOUNT_POSITION_RESP,
	TS_ACCOUNT_RECOVERY_FULL_REQ,
	TS_ACCOUNT_RECOVERY_QUICK_REQ,
	TS_ACCOUNT_RECOVERY_RESP,
	TS_ORDER,
	TS_ORDER_ACK,
	TS_ORDER_UPDATE,
	TS_ORDER_REJECT,
	TS_ORDER_REPORT,
	TS_ORDER_CANCEL_REQ,
	TS_ORDER_REPLACE_REQ,
	TS_ORDER_CANCEL_ACK,
	TS_ORDER_KILL,
	TS_ORDER_REPLACE_ACK,
	TS_ORDER_REPLACED,
	TS_CANCEL_REJECT,
	TS_ACCOUNT_EXEC_HISTORY_REQ,
	TS_ACCOUNT_EXEC_HISTORY_COMPLETE,
	TS_ACCOUNT_ORDER_HISTORY_REQ,
	TS_ACCOUNT_ORDER_HISTORY_COMPLETE,

#ifdef FIRM_VALUES
	TS_FIRM_POSITION_SUBSCRIBE_REQ,
	TS_FIRM_POSITION_UPDATE,
	TS_FIRM_POSITION_UNSUBSCRIBE_REQ,
	TS_FIRM_ENFORCEMENT,
	TS_FIRM_POSITION_REJECT,
	TS_SET_UNTRADEABLE_STATUS,
	TS_UNTRADEABLE_STATUS_UPDATE,
#endif
	M_TR_HTB_LOCATE_INFO				= 12001,
	M_TR_HTB_REQ_SYMBOL_LIST,//			= 12002,
	M_TR_HTB_RESP_SYMBOL_LIST,//			= 12003,
	M_TR_ETB_REQ_SYMBOL_LIST,//			= 12004,
	M_TR_ETB_RESP_SYMBOL_LIST,
	M_TR_HTB_REQ_LOCATE_INFO,
	M_TR_HTB_RESP_LOCATE_INFO,

	M_REQ_PRINTS = 14001,
	M_RESP_PRINTS,
	M_REQ_CANDLE_HISTORICAL_DATA,
	M_RESP_CANDLE_HISTORICAL_DATA,
	M_REQ_CANDLE_INTRADAY_DATA,
	M_RESP_CANDLE_INTRADAY_DATA,
#ifndef TAKION_NO_OPTIONS
	M_OPT_LEVEL2 = 15001,
	M_OPT_LEVEL1,
	M_OPT_TRADE_REPORT,
	M_OPT_OPEN_INTEREST,
	M_REQ_OPT_REFRESH_SYMBOL,
	M_RESP_OPT_REFRESH_SYMBOL,
	M_REQ_OPT_UNSUBSCRIBE_SYMBOL,
	M_OPT_RESET_SYMBOL,
	M_OPT_EOD_SUMMARY_REPORT,
	M_OPT_PREVIOUS_DAY_CLOSE,
//Single Option
	M_REQ_REFRESH_OPTION,
	M_RESP_REFRESH_OPTION,
	M_REQ_UNSUBSCRIBE_OPTION,

	MARKET_DATA_OPTIONS_END,
#endif
	TM_CONNECTED						= 64001,
	TM_DISCONNECTED,
	TM_STARTED_TO_CONNECT,
	TM_FAILED_TO_CONNECT,
	TM_CONNECTION_DESTROYED,

//	TM_EXIT_THREAD,

	TM_THREAD_MD_ENTITLEMENTS_CHANGED,
	TM_THREAD_BOOK_CLEANUP,

	TM_STOCK_INVALID,
	TM_STOCK_REFRESHED,
	TM_EQUITY_REFRESHED,
	TM_EQUITY_UPDATE,
	TM_EQUITY_IMBALANCE_UPDATE,
//	TM_EQUITY_ADD_PRINT_LONG,
//	TM_EQUITY_ADD_PRINT_SHORT,
	TM_STOCK_OPENED,
	TM_STOCK_CLOSED,

	TM_STOCK_UPDATE_LEVEL2,
	TM_STOCK_UPDATE_LEVEL1,
//#ifdef UPDATE_PRINT_MESSAGE
	TM_STOCK_ADD_PRINT,
	TM_STOCK_ADD_BOOK_EXECUTION,
//#endif
	TM_STOCK_DELETE,

	TM_POSITION_UPDATE,
	TM_POSITION_NEW,
	TM_POSITION_OPEN_PNL_LEVEL1,
	TM_POSITION_OPEN_PNL_PRINT,
	TM_POSITION_OPEN_PNL_TCLOSE,

	TM_EQUITY_NEW,

	TM_DELETE_ALL_ACCOUNTS,
	TM_ACCOUNT_DELETE,

	TM_NEW_EQUITY,
	TM_NEW_ACCOUNT,
	TM_NEW_POSITION,
	TM_NEW_ORDER,
	TM_NEW_EXECUTION,
	TM_DEAD_ORDER,

//	TM_ADD_POSITION_TO_SECURITY,

	TM_UPDATED_POSITION,
	TM_EXECUTED_POSITION,
	TM_UPDATED_ORDER,
	TM_UPDATED_ACCOUNT,
	TM_UPDATED_ACCOUNT_AND_POSITION,
	TM_UPDATED_EQUITY,

	TM_ORDER_UPDATE,
	TM_ORDER_NEW,
	TM_ORDER_ERROR,
	TM_ORDER_DELETE,

	TM_EXECUTION_NEW,

	TM_ACCOUNT_UPDATE,

	TM_SEND_SWIPE_ORDER,
	TM_SEND_ORDER_ALGORITHM,
	TM_ORDER_ALGORITHM_CANCEL,

	TM_ORDER_TO_CANCEL,
	TM_CANCEL_ERROR,

	TM_ORDER_STUCK,

	TM_TIER_SIZE_CHANGED_OBSOLETE,

	TM_CONNECTION_OBJECT,

	TM_MARKET_SORTER_LOADED,
	TM_MARKET_SORTER_CHUNK_LOADED,

	TM_STOCK_RESET_IMBALANCES,
	TM_EQUITY_RESET_IMBALANCES,

	TM_MS_TRADE_LONG_INTERNAL,
	TM_MS_TRADE_SHORT_INTERNAL,

	TM_EQUITY_CHART_LOADED,
	TM_EQUITY_NEW_MINUTE,

//	TM_EQUITY_HISTORICAL_CHART_LOADED,
//	TM_EQUITY_HISTORICAL_INTRADAY_CHART_LOADED,

	TM_STOCK_HTB,
	TM_EQUITY_HTB,

	TM_STOCK_BORROW_PRICE,
	TM_EQUITY_BORROW_PRICE,

	TM_MARKET_STATUS,

	TM_QUOTE_MOVE,

//	TM_CUSTOM_INTERNAL,

//	TM_CUSTOM_EXTERNAL,

	TM_NEXT_DAY_STARTED,

	TM_DEFAULT_COMMISSION_FEE,
	TM_ACCOUNT_CONSTRAINTS,

	TM_MARKET_SORTER_CLEANUP,

	TM_DATA_THREAD_BUFFER_OVERFLOW,

	TM_INDEX_NEW,
	TM_INDEX_REFRESHED,
	TM_INDEX_UPDATE,
	TM_INDEX_CHART_LOADED,
	TM_NEW_INDEX,
	TM_UPDATED_INDEX,
	TM_MARKET_SORTER_INDEXES_LOADED,
	TM_MARKET_SORTER_INDEX_CHUNK_LOADED,
	TM_INDEX_NEW_MINUTE,

	TM_EQUITY_NEW_DAY,
	TM_INDEX_NEW_DAY,

	TM_INDEX_NEW_SERVER_MINUTE,

	TM_MARKET_SORTER_STOCK_CHARTS_LOADED,
	TM_MARKET_SORTER_INDEX_CHARTS_LOADED,

	TM_ACCOUNT_COMMAND_DESTROY_CANCELED_ORDER,

	TM_ACCOUNT_COMMAND_PHANTOM_SHARES,
	TM_ACCOUNT_COMMAND_ALL_PHANTOM,

	TM_POSITION_SECURITY_INITIALIZED,
	TM_POSITION_SECURITY_UPDATED,
	TM_POSITION_PHANTOM_SHARES_CHANGED,

	TM_CHART_CANDLE_UPDATED,

	M_HISTORICAL_CHART_PACK_LOADED,
	M_HISTORICAL_CHART_DELETE,

	TM_SYMBOL_TYPED,

	TM_POSITION_BORROW_PRICE,
	TM_POSITION_HTB,

	TM_SET_STOCK_TIER_SIZE,
	TM_SET_EQUITY_TIER_SIZE,

	TM_ACCOUNT_CHECK_LOSS,

	TM_AUTO_ACTION,

	TM_ACCOUNT_SECURITY_UPDATE_FOR_ALGO,
	TM_ACCOUNT_ALGO_MAIN_THREAD_NOTIFICATION,

	TM_POSITION_COST,

	TM_REMOVE_QUOTE,

	TM_POSITION_REMOVE_DELAYED_ORDERS,

	TM_ACCOUNT_BORROW_TO_COVER_OVERNIGHT,
	TM_POSITION_BORROW_TO_COVER_OVERNIGHT,
	TM_POSITION_CANCEL_DELAYED_ILLEGAL_ORDERS,
	TM_POSITION_RESTRICTED,

	TM_SYSTEM_TIME_CHANGED,

	TM_STOCK_UPDATE_HEADLINES,
	TM_STRING_UPDATE_HEADLINES,
	TM_HEADLINE,
//	TM_NEWS_STORY,
	TM_UPDATE_LAST_NEWS_STORY,
	TM_NEWS_STORY_CONTENTS,

	TM_NEWS_PROFILES_LOADED,

	TM_STOCK_NEWS_HISTORIC_SEARCH_DONE,
	TM_STRING_NEWS_HISTORIC_SEARCH_DONE,

	TM_ACCOUNT_REMOVE_DELAYED_ORDERS,

	TM_ACCOUNT_WAIT_MS_CLEANUP,

	TM_DATA_CORRUPTION,

	TM_HARD_BP_HIT,

	TM_EQUITY_OPENED,
	TM_EQUITY_CLOSED,
	TM_EQUITY_YEST_CLOSE_PRICE_CHANGED,

	TM_EQUITY_NEW_TIME_FRAME,

#ifdef FIRM_VALUES
	TM_ACCOUNT_UPDATE_FIRM_ENFORCEMENT,
	TM_NEW_FIRM_POSITION,
	TM_FIRM_POSITION_NEW,
	TM_UPDATED_FIRM_POSITION,
	TM_FIRM_POSITION_UPDATE,
	TM_POSITION_FIRM_LOADED,
	TM_SYMBOL_CHECK_UNTRADEABLE,
	TM_UNTRADEABLE_LIST_LOADED,
	TM_ALL_UNTRADEABLE_LISTS_LOADED,
#endif
#ifndef TAKION_NO_OPTIONS
	TM_UNDERLIER_INVALID,
	TM_UNDERLIER_REFRESHED,
	TM_OPTION_UPDATE_LEVEL2,
	TM_OPTION_UPDATE_LEVEL1,
	TM_OPTION_REFRESHED,
	TM_OPTION_INVALID,

	TM_UNDERLIER_DELETE,
	TM_UNDERLIER_NEW_DAY,
	TM_OPTION_ADD_TO_UNDERLIER,
	TM_OPTION_SET_UNDERLIER_POSITION,
#endif
};

class TMsgRemoveQuote : public Message
{
public:
	TMsgRemoveQuote(const unsigned __int64& symbol, bool side, EcnBookId bookId, unsigned int mmid, unsigned int dollarsFrom, unsigned int dollarFractionFrom, unsigned int dollarsTo, unsigned int dollarFractionTo):
		Message(TM_REMOVE_QUOTE, sizeof(TMsgRemoveQuote)),
		m_symbol(symbol),
		m_mmid(mmid),
		m_dollarsFrom(dollarsFrom),
		m_dollarFractionFrom(dollarFractionFrom),
		m_dollarsTo(dollarsTo),
		m_dollarFractionTo(dollarFractionTo),
		m_side(side),
		m_bookId(bookId)
	{}
	unsigned __int64 m_symbol;
	unsigned int m_mmid;
	unsigned int m_dollarsFrom;
	unsigned int m_dollarFractionFrom;
	unsigned int m_dollarsTo;
	unsigned int m_dollarFractionTo;
	bool m_side;
	EcnBookId m_bookId;
};

class TMessageTime : public Message
{
public:
	unsigned int m_time;
protected:
	TMessageTime(unsigned int time, unsigned short type, unsigned short length):
		Message(type, length),
		m_time(time ? time : TL_GetCurrentMillisecond())
	{
	}
};

class TSmMessageSymbol : public Message
{
public:
	unsigned short m_symbol;
protected:
	TSmMessageSymbol(unsigned short symbol, unsigned short type, unsigned short length):
		Message(type, length),
		m_symbol(symbol)
	{
	}
};

class TSmMessageTimeSymbol : public TMessageTime
{
public:
	unsigned short m_symbol;
protected:
	TSmMessageTimeSymbol(unsigned short symbol, unsigned int time, unsigned short type, unsigned short length):
		TMessageTime(time, type, length),
		m_symbol(symbol)
	{
	}
};

enum TradeReportFlags : unsigned char
{
	NoPriceChanges		= 0,
	LastPriceChanged	= 1,
	LowPriceChanged		= 2,
	HighPriceChanged	= 4,
	TradeThroughExempt	= 8,
};

#define MAX_SRORDID_SIZE		16
#define MAX_ACCOUNT_SIZE		16
#define MAX_IP_ADDRESS_SIZE		16			// *AK*
#define MAX_FIRM_ID_SIZE		5			// *AK*
#define MAX_TRADER_ID_SIZE		5			// *AK*
#define MAX_MMID_SIZE			5			// *AK*
#define MAX_MARKET_REFERENCE_ID	24			// *AK*
#define MAX_USERNAME_SIZE		12
#define MAX_PASSWORD_SIZE		12
#define MAX_USER_TITLE_SIZE		16
#define	MAX_TRADER_SIZE			16
#define MAX_SYMBOL_SIZE			8
#define MAX_RESULT_TEXT_SIZE 256

typedef char Symbol[MAX_SYMBOL_SIZE];

class MsgQuote
{
public:
	MsgQuote(unsigned __int64 referenceNumber,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned int size,
		unsigned int mmid,
		unsigned int millisecond,
		unsigned char bookID,//	: 8;
		unsigned char quoteCondition,//	: 8;
		unsigned short flags)://		: 24;
		m_referenceNumber(referenceNumber),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_mmid(mmid),
		m_millisecond(millisecond),
		m_bookID(bookID),
		m_quoteCondition(quoteCondition),
		m_flags(flags)
	{
	}

	unsigned __int64	m_referenceNumber;
	unsigned int		m_priceDollars;
	unsigned int		m_priceFraction;
	unsigned int		m_size;
	unsigned int		m_mmid;
	unsigned int		m_millisecond;
	unsigned char		m_bookID;//	: 8;
	unsigned char		m_quoteCondition;//	: 8;
	unsigned short		m_flags;//		: 24;

	enum Flags : unsigned short
	{
		SizeChanged			= 0x01,
		PriceChanged		= 0x02,
		ConditionChanged	= 0x04,
		RetailInterest		= 0x08,
		LULDNonExecutable	= 0x10,
	};
};

enum TradeSide : unsigned char
{
	Buy				= 0x00,
	Sell			= 0x01,
	ShortSell		= 0x02,
	ShortSellExempt	= 0x03,
};

////////////////
class TSmMsgBookNewQuote : public TSmMessageSymbol
{
public:
	TSmMsgBookNewQuote(unsigned short symbol = 0,
		unsigned char side = Buy,
		unsigned __int64 referenceNumber = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned int size = 0,
		unsigned int mmid = 0,
		unsigned int millisecond = 0,
		unsigned char bookID = 0,//	: 8;
		unsigned char quoteCondition = 0,//	: 8;
		unsigned short flags = 0)://		: 24;
		TSmMessageSymbol(symbol, SM_M_BOOK_NEW_QUOTE, sizeof(TSmMsgBookNewQuote)),
		m_side(side),
		m_quote(referenceNumber, priceDollars, priceFraction, size, mmid, millisecond, bookID, quoteCondition, flags)
	{}
	unsigned char m_side;
	MsgQuote m_quote;
};

class TSmMsgBookModifyQuote : public TSmMessageSymbol
{
public:
	TSmMsgBookModifyQuote(unsigned short symbol = 0,
		unsigned char side = Buy,
		unsigned __int64 referenceNumber = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned int size = 0,
		unsigned int mmid = 0,
		unsigned int millisecond = 0,
		unsigned char bookID = 0,//	: 8;
		unsigned char quoteCondition = 0,//	: 8;
		unsigned short flags = 0)://		: 24;
		TSmMessageSymbol(symbol, SM_M_BOOK_MODIFY_QUOTE, sizeof(TSmMsgBookModifyQuote)),
		m_side(side),
		m_quote(referenceNumber, priceDollars, priceFraction, size, mmid, millisecond, bookID, quoteCondition, flags)
	{}
	unsigned char m_side;
	MsgQuote m_quote;
};

class TSmMsgBookDeleteQuote : public TMessageTime
{
public:
	TSmMsgBookDeleteQuote(unsigned short symbol = 0,
		unsigned int millisecond = 0,
		unsigned __int64 referenceNumber = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_DELETE_QUOTE, sizeof(TSmMsgBookDeleteQuote)),
		m_referenceNumber(referenceNumber),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID)
		{}
	unsigned __int64 m_referenceNumber;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TSmMsgBookOrderExecuted : public TMessageTime
{
public:
	TSmMsgBookOrderExecuted(unsigned short symbol = 0,
		unsigned int millisecond = 0,
		unsigned __int64 referenceNumber = 0,
		unsigned __int64 matchNumber = 0,
		unsigned int shares = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_ORDER_EXECUTED, sizeof(TSmMsgBookOrderExecuted)),
		m_referenceNumber(referenceNumber),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID)
	{}
	unsigned __int64 m_referenceNumber;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TSmMsgBookOrderExecutedWithPrice : public TMessageTime
{
public:
	TSmMsgBookOrderExecutedWithPrice(unsigned short symbol = 0,
		unsigned int millisecond = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned __int64 referenceNumber = 0,
		unsigned __int64 matchNumber = 0,
		unsigned int shares = 0,
		unsigned int remainingShares = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0,
		bool bPrintable = false):
		TMessageTime(millisecond, SM_M_BOOK_ORDER_EXECUTED_WITH_PRICE, sizeof(TSmMsgBookOrderExecutedWithPrice)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_referenceNumber(referenceNumber),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_remainingShares(remainingShares),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID),
		m_bPrintable(bPrintable)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned __int64 m_referenceNumber;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned int m_remainingShares;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
	bool m_bPrintable;
};

class TSmMsgBookOrderCanceled : public TMessageTime
{
public:
	TSmMsgBookOrderCanceled(unsigned short symbol = 0,
		unsigned int millisecond = 0,
		unsigned __int64 referenceNumber = 0,
		unsigned int shares = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_ORDER_CANCELED, sizeof(TSmMsgBookOrderCanceled)),
		m_referenceNumber(referenceNumber),
		m_shares(shares),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID)
	{}
	unsigned __int64 m_referenceNumber;
	unsigned int m_shares;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TSmMsgBookTrade : public TMessageTime
{
public:
	TSmMsgBookTrade(unsigned short symbol = 0,
		unsigned int millisecond = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned __int64 matchNumber = 0,
		unsigned int shares = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_TRADE, sizeof(TSmMsgBookTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
//	unsigned __int64 m_referenceNumber;//??
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TSmMsgBookCrossTrade : public TMessageTime
{
public:
	TSmMsgBookCrossTrade(unsigned short symbol = 0,
		unsigned int millisecond = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned __int64 matchNumber = 0,
		unsigned int shares = 0,
		char crossType = 0,
		unsigned char bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_CROSS_TRADE, sizeof(TSmMsgBookCrossTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_symbol(symbol),
		m_crossType(crossType),
		m_bookID(bookID)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned short m_symbol;
	char m_crossType;
	unsigned char m_bookID;
};

class TSmMsgStockDirectory : public TMessageTime
{
public:
	TSmMsgStockDirectory(unsigned short symbol,
		unsigned int time,
		unsigned long roundLotSize,
		bool roundLotsOnly,
		char marketCategory,
		char financialStatusIndicator):
		TMessageTime(time, SM_M_STOCK_DIRECTORY, sizeof(TSmMsgStockDirectory)),
		m_roundLotSize(roundLotSize),
		m_symbol(symbol),
		m_roundLotsOnly(roundLotsOnly),
		m_marketCategory(marketCategory),
		m_financialStatusIndicator(financialStatusIndicator)
	{}
	unsigned long m_roundLotSize;
	unsigned short m_symbol;
	bool m_roundLotsOnly;
	char m_marketCategory;
	char m_financialStatusIndicator;
};

class TSmMsgStockTradingActionBase : public TSmMessageTimeSymbol
{
public:
	char m_tradingState;
	char m_tradingActionReason[4];
protected:
	TSmMsgStockTradingActionBase(unsigned short symbol,
		unsigned int time,
		char tradingState,
		unsigned int tradingActionReason,
		unsigned short type,
		unsigned short length):
		TSmMessageTimeSymbol(symbol, time, type, length),
		m_tradingState(tradingState)
	{
		*(unsigned int*)m_tradingActionReason = tradingActionReason;
	}
};

class TSmMsgStockTradingAction : public TSmMsgStockTradingActionBase
{
public:
	TSmMsgStockTradingAction(unsigned short symbol,
		unsigned int time,
		char tradingState,
		unsigned int tradingActionReason):
		TSmMsgStockTradingActionBase(symbol,
			time,
			tradingState,
			tradingActionReason,
			SM_M_STOCK_TRADING_ACTION,
			sizeof(TSmMsgStockTradingAction))
	{
	}
};

class TSmMsgResetSymbol: public TSmMessageSymbol
{
public:
	TSmMsgResetSymbol(unsigned short symbol, unsigned char bookId = AllBooks):TSmMessageSymbol(symbol, SM_M_RESET_SYMBOL, sizeof(TSmMsgResetSymbol)), m_bookId(bookId){}
    unsigned char m_bookId;
};

class TSmMsgResetBook: public Message
{
public:
	TSmMsgResetBook(unsigned char bookId = AllBooks):Message(SM_M_RESET_BOOK, sizeof(TSmMsgResetBook)),m_bookId(bookId){}
    unsigned char m_bookId;
};

class TSmMsgImbalance : public TSmMessageSymbol
{
public:
	TSmMsgImbalance(unsigned short symbol,
		unsigned int farPriceDollar,
		unsigned int farPriceFraction,
		unsigned int nearPriceDollar,
		unsigned int nearPriceFraction,
		unsigned int currentReferencePriceDollar,
		unsigned int currentReferencePriceFraction,
		unsigned int pairedShares,
		unsigned int imbalanceShares,
		unsigned int marketImbalanceShares,
		unsigned int time,
		unsigned int auctionTime,
		char imbalanceDirection,
		char crossType,
		char priceVariationIndicator,
		unsigned char bookId,
		bool regulatory):
	
		TSmMessageSymbol(symbol, SM_M_STOCK_IMBALANCE_INDICATOR, sizeof(TSmMsgImbalance)),
		m_farPriceDollar(farPriceDollar),
		m_farPriceFraction(farPriceFraction),
		m_nearPriceDollar(nearPriceDollar),
		m_nearPriceFraction(nearPriceFraction),
		m_currentReferencePriceDollar(currentReferencePriceDollar),
		m_currentReferencePriceFraction(currentReferencePriceFraction),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0)
	{}
	unsigned int m_farPriceDollar;
	unsigned int m_farPriceFraction;
	unsigned int m_nearPriceDollar;
	unsigned int m_nearPriceFraction;
	unsigned int m_currentReferencePriceDollar;
	unsigned int m_currentReferencePriceFraction;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;
};

class TSmMsgLevel1: public TMessageTime
{
public:
	TSmMsgLevel1(unsigned short symbol,
		unsigned int time,
		unsigned int bidDollars,
		unsigned int bidFraction,
		unsigned int askDollars,
		unsigned int askFraction,
		unsigned int bidSize,
		unsigned int askSize,
		char primaryListingMarket,
		char bidMarketCenter,
		char askMarketCenter,
		char quoteCondition):
		TMessageTime(time, SM_M_LEVEL1, sizeof(TSmMsgLevel1)),
		m_bidDollars(bidDollars),
		m_bidFraction(bidFraction),
		m_askDollars(askDollars),
		m_askFraction(askFraction),
		m_bidSize(bidSize),
		m_askSize(askSize),
		m_symbol(symbol),
		m_primaryListingMarket(primaryListingMarket),
		m_bidMarketCenter(bidMarketCenter),
		m_askMarketCenter(askMarketCenter),
		m_quoteCondition(quoteCondition)
	{}
	unsigned int m_bidDollars;
	unsigned int m_bidFraction;
	unsigned int m_askDollars;
	unsigned int m_askFraction;
	unsigned int m_bidSize;
	unsigned int m_askSize;
	unsigned short m_symbol;
	char m_primaryListingMarket;
	char m_bidMarketCenter;
	char m_askMarketCenter;
	char m_quoteCondition;
};

class TSmMsgTrade: public TMessageTime
{
public:
	TSmMsgTrade(unsigned short symbol,
		unsigned int time,
		unsigned __int64 referenceNumber,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned int size,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		char marketCenterID,
		char primaryListingMarket,
		unsigned char flags):
		TMessageTime(time, SM_M_TRADE_REPORT, sizeof(TSmMsgTrade)),
		m_referenceNumber(referenceNumber),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_symbol(symbol),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_saleConditions;
		*cursor = saleCondition1;
		*++cursor = saleCondition2;
		*++cursor = saleCondition3;
		*++cursor = saleCondition4;
	}
	unsigned __int64 m_referenceNumber;
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned short m_symbol;
	char m_saleConditions[4];
	char m_marketCenterID;
	char m_primaryListingMarket;
	unsigned char m_flags;
};

class TSmMsgTradeErrorBase: public TMessageTime
{
public:
	unsigned __int64 m_originalReferenceNumber;
	unsigned int m_originalPriceDollars;
	unsigned int m_originalPriceFraction;
	unsigned int m_originalSize;
	char m_originalSaleConditions[4];

	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned __int64 m_volume;

	unsigned short m_symbol;
	char m_marketCenterID;
	char m_primaryListingMarket;
	char m_flags;
protected:
	TSmMsgTradeErrorBase(unsigned short symbol,
		unsigned int time,
		unsigned __int64 originalReferenceNumber,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int originalSize,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags,

		unsigned short type,
		unsigned short length):
		TMessageTime(time, type, length),
		m_originalReferenceNumber(originalReferenceNumber),
		m_originalPriceDollars(originalPriceDollars),
		m_originalPriceFraction(originalPriceFraction),
		m_originalSize(originalSize),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_volume(volume),
		m_symbol(symbol),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_originalSaleConditions;
		*cursor = originalSaleCondition1;
		*++cursor = originalSaleCondition2;
		*++cursor = originalSaleCondition3;
		*++cursor = originalSaleCondition4;
	}
};

class TSmMsgTradeError: public TSmMsgTradeErrorBase
{
public:
	TSmMsgTradeError(unsigned short symbol,
		unsigned int time,
		unsigned __int64 originalReferenceNumber,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int originalSize,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags):
		TSmMsgTradeErrorBase(symbol,
			time,
			originalReferenceNumber,
			originalPriceDollars,
			originalPriceFraction,
			originalSize,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			SM_M_TRADE_CANCEL_ERROR,
			sizeof(TSmMsgTradeError))
	{}
};

class TSmMsgTradeCorrectionBase: public TMessageTime
{
public:
	unsigned int m_originalPriceDollars;
	unsigned int m_originalPriceFraction;
	unsigned int m_correctedPriceDollars;
	unsigned int m_correctedPriceFraction;
	unsigned int m_originalSize;
	unsigned int m_correctedSize;
	unsigned __int64 m_originalReferenceNumber;
	unsigned __int64 m_correctedReferenceNumber;
	char m_originalSaleConditions[4];
	char m_correctedSaleConditions[4];
	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned __int64 m_volume;
	unsigned short m_symbol;
	char m_marketCenterID;
	char m_primaryListingMarket;
	char m_flags;
protected:
//	TMsgTradeCorrectionBase(const char* symbol, unsigned int time, unsigned short type, unsigned short length):TMessageTimeSymbol(symbol, time, type, length){}
	TSmMsgTradeCorrectionBase(unsigned short symbol,
		unsigned int time,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int correctedPriceDollars,
		unsigned int correctedPriceFraction,
		unsigned int originalSize,
		unsigned int correctedSize,
		unsigned __int64 originalReferenceNumber,
		unsigned __int64 correctedReferenceNumber,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,
		char correctedSaleCondition1,
		char correctedSaleCondition2,
		char correctedSaleCondition3,
		char correctedSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags,

		unsigned short type,
		unsigned short length):
		TMessageTime(time, type, length),
		m_originalPriceDollars(originalPriceDollars),
		m_originalPriceFraction(originalPriceFraction),
		m_correctedPriceDollars(correctedPriceDollars),
		m_correctedPriceFraction(correctedPriceFraction),
		m_originalSize(originalSize),
		m_correctedSize(correctedSize),
		m_originalReferenceNumber(originalReferenceNumber),
		m_correctedReferenceNumber(correctedReferenceNumber),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_volume(volume),
		m_symbol(symbol),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_originalSaleConditions;
		*cursor = originalSaleCondition1;
		*++cursor = originalSaleCondition2;
		*++cursor = originalSaleCondition3;
		*++cursor = originalSaleCondition4;

		cursor = m_correctedSaleConditions;
		*cursor = correctedSaleCondition1;
		*++cursor = correctedSaleCondition2;
		*++cursor = correctedSaleCondition3;
		*++cursor = correctedSaleCondition4;
	}
};

class TSmMsgTradeCorrection: public TSmMsgTradeCorrectionBase
{
public:
	TSmMsgTradeCorrection(unsigned short symbol,
		unsigned int time,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int correctedPriceDollars,
		unsigned int correctedPriceFraction,
		unsigned int originalSize,
		unsigned int correctedSize,
		unsigned __int64 originalReferenceNumber,
		unsigned __int64 correctedReferenceNumber,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,
		char correctedSaleCondition1,
		char correctedSaleCondition2,
		char correctedSaleCondition3,
		char correctedSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags):
		TSmMsgTradeCorrectionBase(symbol,
			time,
			originalPriceDollars,
			originalPriceFraction,
			correctedPriceDollars,
			correctedPriceFraction,
			originalSize,
			correctedSize,
			originalReferenceNumber,
			correctedReferenceNumber,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,
			correctedSaleCondition1,
			correctedSaleCondition2,
			correctedSaleCondition3,
			correctedSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			SM_M_TRADE_CORRECTION,
			sizeof(TSmMsgTradeCorrection))
	{}
};

class TSmMsgEndOfDaySummaryReportBase : public TMessageTime
{
public:
	unsigned int m_todaysClosePriceDollar;
	unsigned int m_todaysClosePriceFraction;
    unsigned __int64 m_volume;
	unsigned short m_symbol;
protected:
    TSmMsgEndOfDaySummaryReportBase(unsigned short symbol,
		unsigned int time,
		unsigned int todaysClosePriceDollar,
		unsigned int todaysClosePriceFraction,
		unsigned __int64 volume,
		unsigned short type,
		unsigned short length):
		
		TMessageTime(time, type, length),
		m_todaysClosePriceDollar(todaysClosePriceDollar),
		m_todaysClosePriceFraction(todaysClosePriceFraction),
		m_volume(volume),
		m_symbol(symbol)
    {}
};

class TSmMsgEndOfDaySummaryReport : public TSmMsgEndOfDaySummaryReportBase
{
public:
    TSmMsgEndOfDaySummaryReport(unsigned short symbol,
		unsigned int time,
		unsigned int todaysClosePriceDollar,
		unsigned int todaysClosePriceFraction,
		unsigned __int64 volume):
		
		TSmMsgEndOfDaySummaryReportBase(symbol,
			time,
			todaysClosePriceDollar,
			todaysClosePriceFraction,
			volume,
			SM_M_EOD_SUMMARY_REPORT,
			sizeof(TSmMsgEndOfDaySummaryReport))
    {}
};

class TSmMsgShortSaleIndicatorsBase : public TSmMessageTimeSymbol
{
public:
	char m_shortSaleThresholdIndicator;//'Y', 'N'
	char m_regSHOTestIndicator;//'0', '1', '2'
protected:
    TSmMsgShortSaleIndicatorsBase(unsigned short symbol,
		unsigned int time,
		char shortSaleThresholdIndicator,
		char regSHOTestIndicator,
		unsigned short type,
		unsigned short length):

		TSmMessageTimeSymbol(symbol, time, type, length),
        m_shortSaleThresholdIndicator(shortSaleThresholdIndicator),
        m_regSHOTestIndicator(regSHOTestIndicator)
    {}

};

class TSmMsgShortSaleIndicators : public TSmMsgShortSaleIndicatorsBase
{
public:
    TSmMsgShortSaleIndicators(unsigned short symbol,
		unsigned int time,
		char shortSaleThresholdIndicator,
		char regSHOTestIndicator):

		TSmMsgShortSaleIndicatorsBase(symbol, time, shortSaleThresholdIndicator, regSHOTestIndicator, SM_M_SHORT_SALE_INDICATORS, sizeof(TSmMsgShortSaleIndicators))
    {}
};

class TSmMsgPmiBase : public TMessageTime
{
public:
	unsigned int m_bidDollar;
	unsigned int m_bidFraction;
	unsigned int m_askDollar;
	unsigned int m_askFraction;
	unsigned short m_symbol;
	unsigned char m_securityStatus;
	unsigned char m_adjustment;
protected:
	TSmMsgPmiBase(unsigned short symbol,
		unsigned int time,
		unsigned int bidDollar,
		unsigned int bidFraction,
		unsigned int askDollar,
		unsigned int askFraction,
		unsigned char securityStatus,
		unsigned char adjustment,
		unsigned short type,
		unsigned short length):
		TMessageTime(time, type, length),
		m_bidDollar(bidDollar),
		m_bidFraction(bidFraction),
		m_askDollar(askDollar),
		m_askFraction(askFraction),
		m_symbol(symbol),
        m_securityStatus(securityStatus),
        m_adjustment(adjustment)
    {
	}
};

class TSmMsgPmi : public TSmMsgPmiBase
{
public:
    TSmMsgPmi(unsigned short symbol,
		unsigned int time,
		unsigned int bidDollar,
		unsigned int bidFraction,
		unsigned int askDollar,
		unsigned int askFraction,
		unsigned char securityStatus,
		unsigned char adjustment):
		TSmMsgPmiBase(symbol,
			time,
			bidDollar,
			bidFraction,
			askDollar,
			askFraction,
			securityStatus,
			adjustment,
			SM_M_PMI,
			sizeof(TSmMsgPmi))
    {}
};

class TSmMsgLrpBase : public TMessageTime
{
public:
	unsigned int m_lowDollar;
	unsigned int m_lowFraction;
	unsigned int m_highDollar;
	unsigned int m_highFraction;
	unsigned short m_symbol;
	unsigned char m_changeIndicator;
protected:
	TSmMsgLrpBase(unsigned short symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator,
		unsigned short type,
		unsigned short length):
		TMessageTime(time, type, length),
		m_lowDollar(lowDollar),
		m_lowFraction(lowFraction),
		m_highDollar(highDollar),
		m_highFraction(highFraction),
		m_symbol(symbol),
        m_changeIndicator(changeIndicator)
    {
	}
};

class TSmMsgLrp : public TSmMsgLrpBase
{
public:
    TSmMsgLrp(unsigned short symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator):
		TSmMsgLrpBase(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			changeIndicator,
			SM_M_LRP,
			sizeof(TSmMsgLrp))
    {}
};

class TSmMsgLuld : public TSmMsgLrpBase
{
public:
    TSmMsgLuld(unsigned short symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator):
		TSmMsgLrpBase(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			changeIndicator,
			SM_M_LULD,
			sizeof(TSmMsgLuld))
    {}
};

class TSmMsgTradeTimeBase : public TMessageTime
{
public:
	unsigned int m_tradeTime;
	unsigned short m_symbol;
protected:
	TSmMsgTradeTimeBase(unsigned short symbol,
		unsigned int time,
		unsigned int tradeTime,
		unsigned short type,
		unsigned short length):
		TMessageTime(time, type, length),
		m_symbol(symbol),
		m_tradeTime(tradeTime)
    {
	}
};

class TSmMsgTradeTime : public TSmMsgTradeTimeBase
{
public:
    TSmMsgTradeTime(unsigned short symbol,
		unsigned int time,
		unsigned int tradeTime):
		TSmMsgTradeTimeBase(symbol, time, tradeTime, SM_M_T_TIME, sizeof(TSmMsgTradeTime))
    {}
};

class TSmMsgRpiBase : public TSmMessageTimeSymbol
{
public:
	char m_indicator;
protected:
	TSmMsgRpiBase(unsigned short symbol,
		unsigned int time,
		char indicator,
		unsigned short type,
		unsigned short length):
		TSmMessageTimeSymbol(symbol, time, type, length),
		m_indicator(indicator)
    {
	}
};

class TSmMsgRpi : public TSmMsgRpiBase
{
public:
    TSmMsgRpi(unsigned short symbol,
		unsigned int time,
		unsigned char indicator):
		TSmMsgRpiBase(symbol, time, indicator, SM_M_RPI, sizeof(TSmMsgRpi))
    {}
};

class TSmMsgDividendsAndSplitsBase : public TMessageTime
{
public:
	unsigned int m_dividendDollar;
	unsigned int m_dividendFraction;
	unsigned short m_symbol;
    unsigned short m_splitNumerator;
    unsigned short m_splitDenominator;
	char m_exDivDate[sizeof(unsigned int) + 1];
protected:
    TSmMsgDividendsAndSplitsBase(unsigned short symbol,
		unsigned int time,
		unsigned int dividendDollar,
		unsigned int dividendFraction,
	    unsigned short splitNumerator,
		unsigned short splitDenominator,
		unsigned int exDivDate,
		unsigned short type,
		unsigned short length):
		TMessageTime(time, type, length),
		m_dividendDollar(dividendDollar),
		m_dividendFraction(dividendFraction),
		m_symbol(symbol),
        m_splitNumerator(splitNumerator),
        m_splitDenominator(splitDenominator)
    {
		*(unsigned int*)m_exDivDate = exDivDate;
		m_exDivDate[sizeof(unsigned int)] = '\0';
	}
};

class TSmMsgDividendsAndSplits : public TSmMsgDividendsAndSplitsBase
{
public:
    TSmMsgDividendsAndSplits(unsigned short symbol,
		unsigned int time,
		unsigned int dividendDollar,
		unsigned int dividendFraction,
	    unsigned short splitNumerator,
		unsigned short splitDenominator,
		unsigned int exDivDate):
		TSmMsgDividendsAndSplitsBase(symbol,
			time,
			dividendDollar,
			dividendFraction,
			splitNumerator,
			splitDenominator,
			exDivDate,
			SM_M_DIVIDENDS_AND_SPLITS,
			sizeof(TSmMsgDividendsAndSplits))
    {}
};

class TSmMsgPreviousDayCloseBase : public TMessageTime
{
public:
	unsigned int m_closePriceDollar;
	unsigned int m_closePriceFraction;
	unsigned short m_symbol;
protected:
    TSmMsgPreviousDayCloseBase(unsigned short symbol,
		unsigned int time,
		unsigned int closePriceDollar,
		unsigned int closePriceFraction,
		unsigned short type,
		unsigned short length):
		TMessageTime(time, type, length),
		m_closePriceDollar(closePriceDollar),
		m_closePriceFraction(closePriceFraction),
		m_symbol(symbol)
    {}
};

class TSmMsgPreviousDayClose : public TSmMsgPreviousDayCloseBase
{
public:
    TSmMsgPreviousDayClose(unsigned short symbol,
		unsigned int time,
		unsigned int closePriceDollar,
		unsigned int closePriceFraction):
		TSmMsgPreviousDayCloseBase(symbol,
			time,
			closePriceDollar,
			closePriceFraction,
			SM_M_PREVIOUS_DAY_CLOSE,
			sizeof(TSmMsgPreviousDayClose))
    {}
};

class TSmMsgRespRefreshSymbol : public Message
{
public:
	TSmMsgRespRefreshSymbol(unsigned short dataSize,
		unsigned int requestId,
		const char* symbol,
		unsigned short symbolIndex,
		unsigned char steps,
		unsigned char flags,
		unsigned char bookID,
		char marketStatus):
		Message(SM_M_RESP_REFRESH_SYMBOL, dataSize),
		m_requestID(requestId),
		m_symbolIndex(symbolIndex),
		m_steps(steps),
		m_flags(flags),
		m_bookID(bookID),
		m_marketStatus(marketStatus)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}

	unsigned int m_requestID;
	Symbol m_symbol;
	unsigned short m_symbolIndex;
	unsigned char m_steps;
	unsigned char m_flags;
	unsigned char m_bookID;
	char m_marketStatus;
};

class TSmMsgSystemEvent : public Message
{
public:
	TSmMsgSystemEvent(unsigned char eventCode, unsigned char source):Message(SM_M_SYSTEM_EVENT, sizeof(TSmMsgSystemEvent)), m_eventCode(eventCode), m_source(source){}
	unsigned char m_eventCode;
	unsigned char m_source;
};

class TSmMsgResetImbalances : public Message
{
public:
	TSmMsgResetImbalances():Message(SM_M_RESET_IMBALANCES, sizeof(TSmMsgResetImbalances)){}
};

////////////////
class TSmMsgMsLevel1Short: public Message
{
public:
	TSmMsgMsLevel1Short(unsigned short symbol,
		unsigned int price,
		unsigned char side,
		char quoteCondition):
		Message(SM_MS_LEVEL1_SHORT, sizeof(TSmMsgMsLevel1Short)),
		m_price(price),
		m_symbol(symbol),
		m_side(side),
		m_quoteCondition(quoteCondition)
	{}
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_symbol;
	unsigned char m_side;//'B' and 'S'
	char m_quoteCondition;
};

class TSmMsgMsLevel1Long: public Message
{
public:
	TSmMsgMsLevel1Long(unsigned short symbol,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned char side,
		char quoteCondition):
		Message(SM_MS_LEVEL1_LONG, sizeof(TSmMsgMsLevel1Long)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_symbol(symbol),
		m_side(side),
		m_quoteCondition(quoteCondition)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned short m_symbol;
	unsigned char m_side;//'B' and 'S'
	char m_quoteCondition;
};

class TSmMsgMsImbalanceLong : public Message
{
public:
	TSmMsgMsImbalanceLong(unsigned short symbol,
		unsigned int farPriceDollar,
		unsigned int farPriceFraction,
		unsigned int nearPriceDollar,
		unsigned int nearPriceFraction,
		unsigned int currentReferencePriceDollar,
		unsigned int currentReferencePriceFraction,
		unsigned int pairedShares,
		unsigned int imbalanceShares,
//		unsigned int marketImbalanceShares,
		unsigned int time,
		unsigned int auctionTime,
		char imbalanceDirection,
		char crossType,
		char priceVariationIndicator,
		unsigned char bookId,
		bool regulatory):
	
		Message(SM_MS_IMBALANCE_LONG, sizeof(TSmMsgMsImbalanceLong)),
		m_farPriceDollar(farPriceDollar),
		m_farPriceFraction(farPriceFraction),
		m_nearPriceDollar(nearPriceDollar),
		m_nearPriceFraction(nearPriceFraction),
		m_currentReferencePriceDollar(currentReferencePriceDollar),
		m_currentReferencePriceFraction(currentReferencePriceFraction),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
//		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_symbol(symbol),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0)
	{}
	unsigned int m_farPriceDollar;
	unsigned int m_farPriceFraction;
	unsigned int m_nearPriceDollar;
	unsigned int m_nearPriceFraction;
	unsigned int m_currentReferencePriceDollar;
	unsigned int m_currentReferencePriceFraction;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
//	unsigned int m_marketImbalanceShares;??????
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	unsigned short m_symbol;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;//for ARCA : 1 if market imbalance, 0 if non market imbalance
};

class TSmMsgMsImbalanceShort : public Message
{
public:
	TSmMsgMsImbalanceShort(unsigned short symbol,
		unsigned int farPrice,//18 bits for dollar and 14 bits for 4 digits of fraction
		unsigned int nearPrice,//18 bits for dollar and 14 bits for 4 digits of fraction
		unsigned int currentReferencePrice,//18 bits for dollar and 14 bits for 4 digits of fraction
		unsigned int pairedShares,
		unsigned int imbalanceShares,
//		unsigned int marketImbalanceShares,
		unsigned int time,
		unsigned int auctionTime,
		char imbalanceDirection,
		char crossType,
		char priceVariationIndicator,
		unsigned char bookId,
		bool regulatory):
	
		Message(SM_MS_IMBALANCE_SHORT, sizeof(TSmMsgMsImbalanceShort)),
		m_farPrice(farPrice),
		m_nearPrice(nearPrice),
		m_currentReferencePrice(currentReferencePrice),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
//		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_symbol(symbol),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0)//for ARCA : 1 if market imbalance, 0 if non market imbalance
	{}
	unsigned int m_farPrice;
	unsigned int m_nearPrice;
	unsigned int m_currentReferencePrice;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
//	unsigned int m_marketImbalanceShares;?????
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	unsigned short m_symbol;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;//for ARCA : 1 if market imbalance, 0 if non market imbalance
};

class TSmMsgMsTradeLong: public Message
{
public:
	TSmMsgMsTradeLong(unsigned short symbol,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned int size,
		unsigned int saleCondition,
		char marketCenter):
		Message(SM_MS_TRADE_REPORT_LONG, sizeof(TSmMsgMsTradeLong)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_symbol(symbol),
		m_marketCenterID(marketCenter)
	{
		*(unsigned int*)m_saleCondition = saleCondition;
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	char m_saleCondition[4];
	unsigned short m_symbol;
	char m_marketCenterID;
};

class TSmMsgMsTradeShort: public Message
{
public:
	TSmMsgMsTradeShort(unsigned short symbol,
		unsigned int price,
		unsigned short size,
		char saleCondition,
		char marketCenter):
		Message(SM_MS_TRADE_REPORT_SHORT, sizeof(TSmMsgMsTradeShort)),
		m_symbol(symbol),
		m_price(price),
		m_size(size),
		m_saleCondition(saleCondition),
		m_marketCenterID(marketCenter)
	{}
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_symbol;
	unsigned short m_size;
	char m_saleCondition;
	char m_marketCenterID;
};

class TSmMsgMsTradeError: public TSmMsgTradeErrorBase
{
public:
	TSmMsgMsTradeError(unsigned short symbol,
		unsigned int time,
		unsigned __int64 originalReferenceNumber,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int originalSize,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags):
		TSmMsgTradeErrorBase(symbol,
			time,
			originalReferenceNumber,
			originalPriceDollars,
			originalPriceFraction,
			originalSize,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			SM_MS_TRADE_CANCEL_ERROR,
			sizeof(TSmMsgMsTradeError))
	{}
};

class TSmMsgMsTradeCorrection: public TSmMsgTradeCorrectionBase
{
public:
	TSmMsgMsTradeCorrection(unsigned short symbol,
		unsigned int time,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int correctedPriceDollars,
		unsigned int correctedPriceFraction,
		unsigned int originalSize,
		unsigned int correctedSize,
		unsigned __int64 originalReferenceNumber,
		unsigned __int64 correctedReferenceNumber,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,
		char correctedSaleCondition1,
		char correctedSaleCondition2,
		char correctedSaleCondition3,
		char correctedSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags):
		TSmMsgTradeCorrectionBase(symbol,
			time,
			originalPriceDollars,
			originalPriceFraction,
			correctedPriceDollars,
			correctedPriceFraction,
			originalSize,
			correctedSize,
			originalReferenceNumber,
			correctedReferenceNumber,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,
			correctedSaleCondition1,
			correctedSaleCondition2,
			correctedSaleCondition3,
			correctedSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			SM_MS_TRADE_CORRECTION,
			sizeof(TSmMsgMsTradeCorrection))
	{}
};

class TSmMsgMsEndOfDaySummaryReport : public TSmMsgEndOfDaySummaryReportBase
{
public:
    TSmMsgMsEndOfDaySummaryReport(unsigned short symbol,
		unsigned int time,
		unsigned int todaysClosePriceDollar,
		unsigned int todaysClosePriceFraction,
		unsigned __int64 volume):
		
		TSmMsgEndOfDaySummaryReportBase(symbol,
			time,
			todaysClosePriceDollar,
			todaysClosePriceFraction,
			volume,
			SM_MS_EOD_SUMMARY_REPORT,
			sizeof(TSmMsgMsEndOfDaySummaryReport))
    {}
};

class TSmMsgMsShortSaleIndicators : public TSmMsgShortSaleIndicatorsBase
{
public:
    TSmMsgMsShortSaleIndicators(unsigned short symbol,
		unsigned int time,
		char shortSaleThresholdIndicator,
		char regSHOTestIndicator):

		TSmMsgShortSaleIndicatorsBase(symbol,
			time,
			shortSaleThresholdIndicator,
			regSHOTestIndicator,
			SM_MS_SHORT_SALE_INDICATORS,
			sizeof(TSmMsgMsShortSaleIndicators))
    {}
};

class TSmMsgMsPmi : public TSmMsgPmiBase
{
public:
    TSmMsgMsPmi(unsigned short symbol,
		unsigned int time,
		unsigned int bidDollar,
		unsigned int bidFraction,
		unsigned int askDollar,
		unsigned int askFraction,
		unsigned char securityStatus,
		unsigned char adjustment):
		TSmMsgPmiBase(symbol,
			time,
			bidDollar,
			bidFraction,
			askDollar,
			askFraction,
			securityStatus,
			adjustment,
			SM_MS_PMI,
			sizeof(TSmMsgMsPmi))
    {}
};

class TSmMsgMsLrp : public TSmMsgLrpBase
{
public:
    TSmMsgMsLrp(unsigned short symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator):
		TSmMsgLrpBase(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			changeIndicator,
			SM_MS_LRP,
			sizeof(TSmMsgMsLrp))
    {}
};

class TSmMsgMsLuld : public TSmMsgLrpBase
{
public:
    TSmMsgMsLuld(unsigned short symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator):
		TSmMsgLrpBase(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			changeIndicator,
			SM_MS_LULD,
			sizeof(TSmMsgMsLuld))
    {}
};

class TSmMsgMsTradeTime : public TSmMsgTradeTimeBase
{
public:
    TSmMsgMsTradeTime(unsigned short symbol,
		unsigned int time,
		unsigned int tradeTime):
		TSmMsgTradeTimeBase(symbol,
			time,
			tradeTime,
			SM_MS_T_TIME,
			sizeof(TSmMsgMsTradeTime))
    {}
};

class TSmMsgMsRpi : public TSmMsgRpiBase
{
public:
    TSmMsgMsRpi(unsigned short symbol,
		unsigned int time,
		unsigned char indicator):
		TSmMsgRpiBase(symbol,
			time,
			indicator,
			SM_MS_RPI,
			sizeof(TSmMsgMsRpi))
    {}
};

class TSmMsgMsDividendsAndSplits : public TSmMsgDividendsAndSplitsBase
{
public:
    TSmMsgMsDividendsAndSplits(unsigned short symbol,
		unsigned int time,
		unsigned int dividendDollar,
		unsigned int dividendFraction,
	    unsigned short splitNumerator,
		unsigned short splitDenominator,
		unsigned int exDivDate):
		TSmMsgDividendsAndSplitsBase(symbol,
			time,
			dividendDollar,
			dividendFraction,
			splitNumerator,
			splitDenominator,
			exDivDate,
			SM_MS_DIVIDENDS_AND_SPLITS,
			sizeof(TSmMsgMsDividendsAndSplits))
    {}
};

class TSmMsgMsPreviousDayClose : public TSmMsgPreviousDayCloseBase
{
public:
    TSmMsgMsPreviousDayClose(unsigned short symbol,
		unsigned int time,
		unsigned int closePriceDollar,
		unsigned int closePriceFraction):
		TSmMsgPreviousDayCloseBase(symbol,
			time,
			closePriceDollar,
			closePriceFraction,
			SM_MS_PREVIOUS_DAY_CLOSE,
			sizeof(TSmMsgMsPreviousDayClose))
    {}
};

class TSmMsgMsStockTradingAction : public TSmMsgStockTradingActionBase
{
public:
	TSmMsgMsStockTradingAction(unsigned short symbol,
		unsigned int time,
		char tradingState,
		unsigned int tradingActionReason):
		TSmMsgStockTradingActionBase(symbol,
			time,
			tradingState,
			tradingActionReason,
			SM_MS_STOCK_TRADING_ACTION,
			sizeof(TSmMsgMsStockTradingAction))
	{
	}
};

class TSmMsgMsResetImbalances : public Message
{
public:
	TSmMsgMsResetImbalances():Message(SM_MS_RESET_IMBALANCES, sizeof(TSmMsgMsResetImbalances)){}
};

//////////////////
class TSmMsgRespChart : public Message
{
public:
	TSmMsgRespChart(unsigned short symbol,
		unsigned long requestId,
		unsigned short minute,
		unsigned char tickSize,
		unsigned short ticks,
		bool done):
		Message(SM_RESP_CHART, sizeof(TSmMsgRespChart) + (unsigned int)tickSize * ticks),
		m_requestId(requestId),
		m_symbol(symbol),
		m_minute(minute),
		m_tickSize(tickSize),
		m_done(done)
	{}
	unsigned long m_requestId;
	unsigned short	m_symbol;
	unsigned short m_minute;
	unsigned char m_tickSize;
	unsigned char m_done;
};

class TSmMsgNewTick : public TSmMessageSymbol
{
public:
//	unsigned short	m_symbol;
	unsigned short m_minute;
protected:
	TSmMsgNewTick(unsigned short symbol,
		unsigned short minute,
		unsigned short type,
		unsigned short size):
		TSmMessageSymbol(symbol, type, size),
		m_minute(minute)
	{}
};

class TSmMsgEquityNewTick : public TSmMsgNewTick
{
public:
	TSmMsgEquityNewTick(unsigned short symbol, unsigned short minute):TSmMsgNewTick(symbol, minute, SM_NEW_TICK, sizeof(TSmMsgEquityNewTick)){}
};

class TSmMsgTickCorrection : public Message
{
public:
	TSmMsgTickCorrection(unsigned short symbol,
		unsigned int volume,
		unsigned int moneyDollars,
		unsigned int moneyFraction,
		unsigned int first,
		unsigned int last,
		unsigned int high,
		unsigned int low,
		unsigned short minute):
		Message(SM_TICK_CORRECTION, sizeof(TSmMsgTickCorrection)),
		m_volume(volume),
		m_moneyDollars(moneyDollars),
		m_moneyFraction(moneyFraction),
		m_first(first),
		m_last(last),
		m_high(high),
		m_low(low),
		m_symbol(symbol),
		m_minute(minute)
	{}
	unsigned int m_volume;
	unsigned int m_moneyDollars;
	unsigned int m_moneyFraction;
	unsigned int m_first;
	unsigned int m_last;
	unsigned int m_high;
	unsigned int m_low;
	unsigned short m_symbol;
	unsigned short m_minute;
};

//////////////////
class TMsgHeartbeat : public Message
{
public:
	TMsgHeartbeat(unsigned __int64 serverTime = 0) : Message(M_HEARTBEAT, sizeof(TMsgHeartbeat)), m_reserved(0), m_serverTime(serverTime){}
 	unsigned int		m_reserved;
	unsigned __int64	m_serverTime;
};

class TMsqDisconnectServerCommand : public Message
{
public:
	TMsqDisconnectServerCommand():Message(M_DISCONNECT, sizeof(TMsqDisconnectServerCommand)), m_reserved(0), m_reserved2(0){}
	unsigned int		m_reserved;
	unsigned __int64	m_reserved2;
};

class TMsgText : public Message
{
public:
	TMsgText(const char* text):
		Message(M_TEXT, (unsigned short)(sizeof(TMsgText) + __min(strlen( text ), 1000 ) + 1)),
		m_reserved(0)
	{
		strncpy_s((char*)this + sizeof(TMsgText), 1001, text, 1000 );
		((char*)this)[m_length-1] = 0;
	}
 	unsigned int	m_reserved;
};

class TMsgDataThreadBufferOverflow : public Message
{
public:
	TMsgDataThreadBufferOverflow(unsigned int threadId, unsigned int ordinal):Message(TM_DATA_THREAD_BUFFER_OVERFLOW, sizeof(TMsgDataThreadBufferOverflow)), m_threadId(threadId), m_ordinal(ordinal){}
	unsigned int m_threadId;
	unsigned int m_ordinal;
};


class TMsgMarketSorterCleanup : public Message
{
public:
	TMsgMarketSorterCleanup():Message(TM_MARKET_SORTER_CLEANUP, sizeof(TMsgMarketSorterCleanup)){}
};

class TMsgNextDayStarted : public Message
{
public:
	TMsgNextDayStarted(unsigned int date):Message(TM_NEXT_DAY_STARTED, sizeof(TMsgNextDayStarted)), m_date(date){}
	unsigned int m_date;
};

class TMsgSystemTimeChanged : public Message
{
public:
	TMsgSystemTimeChanged(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int prevDate):Message(TM_SYSTEM_TIME_CHANGED, sizeof(TMsgSystemTimeChanged)), m_prevMillisecond(prevMillisecond), m_currentMillisecond(currentMillisecond), m_prevDate(prevDate){}
	unsigned int m_prevMillisecond;
	unsigned int m_currentMillisecond;
	unsigned int m_prevDate;
};

class TMsgMarketOpen : public Message
{
public:
	TMsgMarketOpen(bool open):Message(TM_MARKET_STATUS, sizeof(TMsgMarketOpen)), m_open(open){}
	bool m_open;
};

class TMessageSymbol : public Message
{
public:
	Symbol m_symbol;
protected:
	TMessageSymbol(const char* symbol, unsigned short type, unsigned short length):
		Message(type, length)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
	TMessageSymbol(const unsigned __int64& symbol, unsigned short type, unsigned short length):Message(type, length){*(unsigned __int64*)m_symbol = symbol;}
};

enum QuoteMoveCode : unsigned char
{
	QMC_NEW,
	QMC_JOIN,
	QMC_LEAVE,
	QMC_DROP,

	QMC_COUNT
};

class TMsgQuoteMove : public TMessageSymbol
{
public:
	TMsgQuoteMove(const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		unsigned int bid,
		unsigned int ask,
		unsigned int bidSize,
		unsigned int askSize,
		unsigned int printPrice,
		unsigned int printSize,
		unsigned int posPrice,
		int posSize,
		unsigned int lastExecPrice,
		int lastExecSize,
		unsigned int mmid,
		unsigned char code,
		bool side,
		bool longPosition):
		TMessageSymbol(symbol, TM_QUOTE_MOVE, sizeof(TMsgQuoteMove)),
#ifndef TAKION_NO_OPTIONS
		m_optionBlock(optionBlock),
#endif
		m_bid(bid),
		m_ask(ask),
		m_bidSize(bidSize),
		m_askSize(askSize),
		m_printPrice(printPrice),
		m_printSize(printSize),
		m_posPrice(posPrice),
		m_posSize(posSize),
		m_lastExecPrice(lastExecPrice),
		m_lastExecSize(lastExecSize),
		m_mmid(mmid),
		m_code(code),
		m_side(side),
		m_longPosition(longPosition)
	{}
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
#endif
	unsigned int m_bid;
	unsigned int m_ask;
	unsigned int m_bidSize;
	unsigned int m_askSize;
	unsigned int m_printPrice;
	unsigned int m_printSize;
	unsigned int m_posPrice;
	int m_posSize;
	unsigned int m_lastExecPrice;
	int m_lastExecSize;
	unsigned int m_mmid;
	unsigned char m_code;
	bool m_side;
	bool m_longPosition;
};

class TMessageSymbolMap : public Message
{
public:
	unsigned short m_symbolMap;
protected:
	TMessageSymbolMap(unsigned short symbolMap, unsigned short type, unsigned short length):Message(type, length),m_symbolMap(symbolMap){}
};

class TMessageTimeSymbol : public TMessageTime
{
public:
	Symbol m_symbol;
protected:
	TMessageTimeSymbol(const char* symbol, unsigned int time, unsigned short type, unsigned short length):
		TMessageTime(time, type, length)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
	TMessageTimeSymbol(const unsigned __int64& symbol, unsigned int time, unsigned short type, unsigned short length):TMessageTime(time, type, length){*(unsigned __int64*)m_symbol = symbol;}
};
/*
class TMsgStockLevel1 : public TMessageTimeSymbol
{
public:
	TMsgStockLevel1(const char* symbol,
		unsigned int millisecond,
		unsigned short delay,
		unsigned int dollars,
		unsigned int dollarFraction,
		unsigned int quantity,
		char marketParticipant,
		char quoteCondition,
		bool side):
		TMessageTimeSymbol(symbol, millisecond, TM_STOCK_UPDATE_LEVEL1, sizeof(TMsgStockLevel1)),
		m_dollars(dollars),
		m_dollarFraction(dollarFraction),
		m_quantity(quantity),
		delay(delay),
		m_marketParticipant(marketParticipant),
		m_quoteCondition(quoteCondition),
		m_side(side)
	{}
	TMsgStockLevel1(unsigned __int64 symbol,
		unsigned int millisecond,
		unsigned short delay,
		unsigned int dollars,
		unsigned int dollarFraction,
		unsigned int quantity,
		char marketParticipant,
		char quoteCondition,
		bool side):
		TMessageTimeSymbol(symbol, millisecond, TM_STOCK_UPDATE_LEVEL1, sizeof(TMsgStockLevel1)),
		m_dollars(dollars),
		m_dollarFraction(dollarFraction),
		m_quantity(quantity),
		delay(delay),
		m_marketParticipant(marketParticipant),
		m_quoteCondition(quoteCondition),
		m_side(side)
	{}
	unsigned int m_dollars;
	unsigned int m_dollarFraction;
	unsigned int m_quantity;
	unsigned short delay;
	char m_marketParticipant;
	char m_quoteCondition;
	bool m_side;
};
*/
class TMessageStockAddTrade : public
//#ifdef UPDATE_PRINT_MESSAGE
	TMessageTimeSymbol
/*
#else
	TMessageTime
#endif
*/
{
public:
	unsigned int m_l1Bid;
	unsigned int m_l1Ask;
	unsigned int m_dollars;
	unsigned int m_dollarFraction;
	unsigned int m_quantity;
	unsigned int m_roundLot;
	unsigned int m_mmid;
	unsigned short m_shortMmid;
	short m_delay;
	unsigned char m_source;
	unsigned char m_level1;
protected:
	TMessageStockAddTrade(
//#ifdef UPDATE_PRINT_MESSAGE
		const char* symbol,
//#endif
		const Trade& trade,
		unsigned int l1Bid,	
		unsigned int l1Ask,
		unsigned int roundLot,
		unsigned short type,
		unsigned short length):
//#ifdef UPDATE_PRINT_MESSAGE
		TMessageTimeSymbol(symbol, trade.GetMillisecond(), type, length),
//#else
//		TMessageTime(trade.GetMillisecond(), type, length),
//#endif
		m_l1Bid(l1Bid),
		m_l1Ask(l1Ask),
		m_dollars(trade.GetDollars()),
		m_dollarFraction(trade.GetDollarFraction()),
		m_quantity(trade.GetQuantity()),
		m_roundLot(roundLot),
		m_mmid(trade.GetMmid()),
		m_shortMmid(trade.GetShortMmid()),
		m_delay(trade.GetDelay()),
		m_source(trade.GetSource()),
		m_level1(trade.GetLevel1())
	{}
#ifdef UPDATE_PRINT_MESSAGE
	TMessageStockAddTrade(const unsigned __int64& symbol,
		const Trade& trade,
		unsigned int roundLot,
		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, trade.GetMillisecond(), type, length),
		m_dollars(trade.GetDollars()),
		m_dollarFraction(trade.GetDollarFraction()),
		m_quantity(trade.GetQuantity()),
		m_roundLot(roundLot),
		m_mmid(trade.GetMmid()),
		m_delay(trade.GetDelay()),
		m_source(trade.GetSource()),
		m_level1(trade.GetLevel1())
	{}
#endif
};

class TMsgStockAddPrint : public TMessageStockAddTrade
{
public:
	TMsgStockAddPrint(
//#ifdef UPDATE_PRINT_MESSAGE
		const char* symbol,
//#endif
		const NamedPrint& np,
		unsigned int l1Bid,
		unsigned int l1Ask,
		unsigned int roundLot):
		TMessageStockAddTrade(
//#ifdef UPDATE_PRINT_MESSAGE
			symbol,
//#endif
			np,
			l1Bid,	
			l1Ask,
			roundLot,
			TM_STOCK_ADD_PRINT, sizeof(TMsgStockAddPrint)),
		m_saleCondition1(np.GetSaleCondition1()),
		m_saleCondition2(np.GetSaleCondition2()),
		m_saleCondition3(np.GetSaleCondition3()),
		m_saleCondition4(np.GetSaleCondition4())
	{}
#ifdef UPDATE_PRINT_MESSAGE
	TMsgStockAddPrint(const unsigned __int64& symbol, const NamedPrint& np, unsigned int roundLot):
		TMessageStockAddTrade(symbol, np, roundLot, TM_STOCK_ADD_PRINT, sizeof(TMsgStockAddPrint)),
		m_saleCondition1(np.GetSaleCondition1()),
		m_saleCondition2(np.GetSaleCondition2()),
		m_saleCondition3(np.GetSaleCondition3()),
		m_saleCondition4(np.GetSaleCondition4())
	{}
#endif
	char m_saleCondition1;
	char m_saleCondition2;
	char m_saleCondition3;
	char m_saleCondition4;
};

class TMsgStockAddBookExecution : public TMessageStockAddTrade
{
public:
	TMsgStockAddBookExecution(
//#ifdef UPDATE_PRINT_MESSAGE
		const char* symbol,
//#endif
		const NamedBookExecution& nbe,
		unsigned int l1Bid,	
		unsigned int l1Ask,
		unsigned int roundLot):
		TMessageStockAddTrade(
//#ifdef UPDATE_PRINT_MESSAGE
			symbol,
//#endif
			nbe,
			l1Bid,	
			l1Ask,
			roundLot,
			TM_STOCK_ADD_BOOK_EXECUTION, sizeof(TMsgStockAddBookExecution)),
		m_label(nbe.GetLabel()),
		m_side(nbe.GetSide()),
		m_hidden(nbe.isHidden())
	{}
#ifdef UPDATE_PRINT_MESSAGE
	TMsgStockAddBookExecution(const unsigned __int64& symbol, const NamedBookExecution& nbe, unsigned int roundLot):
		TMessageStockAddTrade(symbol, roundLot, nbe, TM_STOCK_ADD_BOOK_EXECUTION, sizeof(TMsgStockAddBookExecution)),
		m_label(nbe.GetLabel()),
		m_side(nbe.GetSide()),
		m_hidden(nbe.isHidden())
	{}
#endif
	char m_label;
	unsigned char m_side;
	bool m_hidden;
};
//#endif

class TMessageSymbolMapUpdate : public TMessageSymbolMap
{
public:
	unsigned int m_updateOrdinal;
protected:
	TMessageSymbolMapUpdate(unsigned short code, unsigned int updateOrdinal, unsigned short type, unsigned short length):TMessageSymbolMap(code, type, length), m_updateOrdinal(updateOrdinal){}
};


class TMessageStockUpdate : public TMessageSymbol
{
public:
	unsigned int m_updateOrdinal;
protected:
	TMessageStockUpdate(const char* symbol, unsigned int updateOrdinal, unsigned short type, unsigned short length):TMessageSymbol(symbol, type, length), m_updateOrdinal(updateOrdinal){}
	TMessageStockUpdate(const unsigned __int64& symbol, unsigned int updateOrdinal, unsigned short type, unsigned short length):TMessageSymbol(symbol, type, length), m_updateOrdinal(updateOrdinal){}
};

class TMsgStockUpdateLevel2 : public TMessageStockUpdate
{
public:
	TMsgStockUpdateLevel2(const char* symbol, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_LEVEL2, sizeof(TMsgStockUpdateLevel2)){}
	TMsgStockUpdateLevel2(const unsigned __int64& symbol, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_LEVEL2, sizeof(TMsgStockUpdateLevel2)){}
};

class TMsgStockRefreshed : public TMessageStockUpdate
{
public:
	TMsgStockRefreshed(const char* symbol, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_REFRESHED, sizeof(TMsgStockRefreshed)){}
	TMsgStockRefreshed(const unsigned __int64& symbol, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_REFRESHED, sizeof(TMsgStockRefreshed)){}
};

class TMsgStockClosed : public TMessageSymbol
{
public:
	TMsgStockClosed(const char* symbol):TMessageSymbol(symbol, TM_STOCK_CLOSED, sizeof(TMsgStockClosed)){}
	TMsgStockClosed(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_CLOSED, sizeof(TMsgStockClosed)){}
};

class TMsgStockOpened : public TMessageSymbol
{
public:
	TMsgStockOpened(const char* symbol):TMessageSymbol(symbol, TM_STOCK_OPENED, sizeof(TMsgStockOpened)){}
	TMsgStockOpened(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_OPENED, sizeof(TMsgStockOpened)){}
};

class TMsgEquityClosed : public TMessageSymbolMap
{
public:
	TMsgEquityClosed(unsigned short code):TMessageSymbolMap(code, TM_EQUITY_CLOSED, sizeof(TMsgEquityClosed)){}
};

class TMsgEquityYesterdaysClosePriceChanged : public TMessageSymbolMap
{
public:
	TMsgEquityYesterdaysClosePriceChanged(unsigned short code):TMessageSymbolMap(code, TM_EQUITY_YEST_CLOSE_PRICE_CHANGED, sizeof(TMsgEquityYesterdaysClosePriceChanged)){}
};

class TMsgEquityOpened : public TMessageSymbolMap
{
public:
	TMsgEquityOpened(unsigned short code):TMessageSymbolMap(code, TM_EQUITY_OPENED, sizeof(TMsgEquityOpened)){}
};

/*in TakionUtils.h
enum SymbolType : unsigned char
{
	EST_UNKNOWN,
	EST_STOCK,
	EST_BASKET,
};
*/
class TMsgSymbolTypedInActiveCommandWindow : public TMessageSymbol
{
public:
	TMsgSymbolTypedInActiveCommandWindow(const char* symbol, unsigned char basket):TMessageSymbol(symbol, TM_SYMBOL_TYPED, sizeof(TMsgSymbolTypedInActiveCommandWindow)), m_basket(basket){}
	TMsgSymbolTypedInActiveCommandWindow(const unsigned __int64& symbol, unsigned char basket):TMessageSymbol(symbol, TM_SYMBOL_TYPED, sizeof(TMsgSymbolTypedInActiveCommandWindow)), m_basket(basket){}
	unsigned char m_basket;
};

class TMsgNewIndex : public TMessageSymbol
{
public:
	TMsgNewIndex(const char* symbol):TMessageSymbol(symbol, TM_INDEX_NEW, sizeof(TMsgNewIndex)){}
	TMsgNewIndex(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_INDEX_NEW, sizeof(TMsgNewIndex)){}
};

class TMsgIndexRefreshed : public TMessageStockUpdate
{
public:
	TMsgIndexRefreshed(const char* symbol, unsigned int updateOrdinal, bool newIndex, bool subscribeToChart):TMessageStockUpdate(symbol, updateOrdinal, TM_INDEX_REFRESHED, sizeof(TMsgIndexRefreshed)), m_newIndex(newIndex), m_subscribeToChart(subscribeToChart){}
	TMsgIndexRefreshed(const unsigned __int64& symbol, unsigned int updateOrdinal, bool newIndex, bool subscribeToChart):TMessageStockUpdate(symbol, updateOrdinal, TM_INDEX_REFRESHED, sizeof(TMsgIndexRefreshed)), m_newIndex(newIndex), m_subscribeToChart(subscribeToChart){}
	bool m_newIndex;
	bool m_subscribeToChart;
};

class TMsgIndexUpdate : public TMessageSymbolMapUpdate
{
public:
	TMsgIndexUpdate(unsigned short code, unsigned int updateOrdinal):TMessageSymbolMapUpdate(code, updateOrdinal, TM_INDEX_UPDATE, sizeof(TMsgIndexUpdate)){}
};

class TMsgIndexNewServerMinute : public TMessageSymbolMap
{
public:
	TMsgIndexNewServerMinute(unsigned short code, unsigned short minute):TMessageSymbolMap(code, TM_INDEX_NEW_SERVER_MINUTE, sizeof(TMsgIndexNewServerMinute)), m_minute(minute){}
	unsigned short m_minute;
};

class TMsgIndex : public Message
{
public:
	Index* m_index;
protected:
	TMsgIndex(Index* index, unsigned short type, unsigned short length):Message(type, length), m_index(index){}
};

class TMsgIndexObjectUpdated : public TMsgIndex
{
public:
	TMsgIndexObjectUpdated(Index* index):TMsgIndex(index, TM_UPDATED_INDEX, sizeof(TMsgIndexObjectUpdated)){}
};

class TMsgIndexObjectNew : public TMsgIndex
{
public:
	TMsgIndexObjectNew(Index* index):TMsgIndex(index, TM_NEW_INDEX, sizeof(TMsgIndexObjectNew)){}
};

class TMsgIndexChartLoaded : public TMessageSymbol
{
public:
	TMsgIndexChartLoaded(const char* symbol):TMessageSymbol(symbol, TM_INDEX_CHART_LOADED, sizeof(TMsgIndexChartLoaded)){}
	TMsgIndexChartLoaded(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_INDEX_CHART_LOADED, sizeof(TMsgIndexChartLoaded)){}
};


class TMsgNewEquity : public TMessageSymbol
{
public:
	TMsgNewEquity(const char* symbol):TMessageSymbol(symbol, TM_EQUITY_NEW, sizeof(TMsgNewEquity)){}
	TMsgNewEquity(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_EQUITY_NEW, sizeof(TMsgNewEquity)){}
};

class TMsgEquityRefreshed : public TMessageStockUpdate
{
public:
	TMsgEquityRefreshed(const char* symbol, unsigned int updateOrdinal, bool newEquity, bool subscribeToChart, bool symbolMapping):TMessageStockUpdate(symbol, updateOrdinal, TM_EQUITY_REFRESHED, sizeof(TMsgEquityRefreshed)), m_newEquity(newEquity), m_subscribeToChart(subscribeToChart), m_symbolMapping(symbolMapping){}
	TMsgEquityRefreshed(const unsigned __int64& symbol, unsigned int updateOrdinal, bool newEquity, bool subscribeToChart, bool symbolMapping):TMessageStockUpdate(symbol, updateOrdinal, TM_EQUITY_REFRESHED, sizeof(TMsgEquityRefreshed)), m_newEquity(newEquity), m_subscribeToChart(subscribeToChart), m_symbolMapping(symbolMapping){}
	bool m_newEquity;
	bool m_subscribeToChart;
	bool m_symbolMapping;
};
/*
class TMsgEquityUpdate : public TMessageStockUpdate
{
public:
	TMsgEquityUpdate(const char* symbol, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_EQUITY_UPDATE, sizeof(TMsgEquityUpdate)){}
	TMsgEquityUpdate(const unsigned __int64& symbol, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_EQUITY_UPDATE, sizeof(TMsgEquityUpdate)){}
};
*/
class TMsgEquityUpdate : public TMessageSymbolMapUpdate
{
public:
	TMsgEquityUpdate(unsigned short code, bool hasPrints, unsigned int updateOrdinal):TMessageSymbolMapUpdate(code, updateOrdinal, TM_EQUITY_UPDATE, sizeof(TMsgEquityUpdate)), m_hasPrints(hasPrints){}
	bool m_hasPrints;
};

//used instead of TMsgEquityUpdate to smooth processing of imbalance spikes in IdleProcessing
class TMsgEquityImbalanceUpdate : public TMessageSymbolMap
{
public:
	TMsgEquityImbalanceUpdate(unsigned short code):TMessageSymbolMap(code, TM_EQUITY_IMBALANCE_UPDATE, sizeof(TMsgEquityImbalanceUpdate)){}
};

class TMsgEquityChartCandleUpdated : public TMessageSymbolMap
{
public:
	TMsgEquityChartCandleUpdated(unsigned short code, unsigned short minute):TMessageSymbolMap(code, TM_CHART_CANDLE_UPDATED, sizeof(TMsgEquityChartCandleUpdated)), m_minute(minute){}
	unsigned short m_minute;
};

class TMsgEquityNewDay : public TMessageSymbolMap
{
public:
	TMsgEquityNewDay(unsigned short code):TMessageSymbolMap(code, TM_EQUITY_NEW_DAY, sizeof(TMsgEquityNewDay)){}
};

class TMsgIndexNewDay : public TMessageSymbolMap
{
public:
	TMsgIndexNewDay(unsigned short code):TMessageSymbolMap(code, TM_INDEX_NEW_DAY, sizeof(TMsgIndexNewDay)){}
};

class TMsgEquity : public Message
{
public:
	Security* m_security;
protected:
	TMsgEquity(Security* security, unsigned short type, unsigned short length):Message(type, length), m_security(security){}
};

class TMsgEquityObjectNew : public TMsgEquity
{
public:
	TMsgEquityObjectNew(Security* security):TMsgEquity(security, TM_NEW_EQUITY, sizeof(TMsgEquityObjectNew)){}
};

class TMsgEquityObjectUpdated : public TMsgEquity
{
public:
	TMsgEquityObjectUpdated(Security* security):TMsgEquity(security, TM_UPDATED_EQUITY, sizeof(TMsgEquityObjectUpdated)){}
};

class TMsgStockInvalid : public TMessageSymbol
{
public:
	TMsgStockInvalid(const char* symbol):TMessageSymbol(symbol, TM_STOCK_INVALID, sizeof(TMsgStockInvalid)){}
	TMsgStockInvalid(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_INVALID, sizeof(TMsgStockInvalid)){}
};

class TMsgAccountObject : public Message
{
public:
	char m_accountId[MAX_ACCOUNT_SIZE];
protected:
	TMsgAccountObject(const char* accountName, unsigned short type, unsigned short length):
		Message(type, length)
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountName, '\0');
	}
};

//////////////

class TMsgAccountStockPositionObject : public TMsgAccountObject
{
public:
	unsigned __int64 m_symbol;
protected:
	TMsgAccountStockPositionObject(const char* accountName, const unsigned __int64& symbol,
		unsigned short type, unsigned short length):
		TMsgAccountObject(accountName, type, length),
		m_symbol(symbol)
	{
//		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
};

class TMsgAccountPositionObject : public TMsgAccountStockPositionObject
{
public:
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
#endif
protected:
	TMsgAccountPositionObject(const char* accountName, const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		unsigned short type, unsigned short length):
		TMsgAccountStockPositionObject(accountName, symbol, type, length)
#ifndef TAKION_NO_OPTIONS
		,m_optionBlock(optionBlock)
#endif
	{
	}
};

class TMsgPositionOpenPnlUpdate : public TMsgAccountPositionObject
{
public:
	Price m_price;
protected:
	TMsgPositionOpenPnlUpdate(const char* accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& level1Price,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		unsigned short type, unsigned short length):
		TMsgAccountPositionObject(accountName, symbol,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
#endif
			type, length),
		m_price(level1Price)
	{
//		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
};

class TMsgPositionTCloseOpenPnlUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionTCloseOpenPnlUpdate(const char* accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& price
#ifndef TAKION_NO_OPTIONS
//		,unsigned char securityType
		,const unsigned __int64& optionBlock
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
#endif
			TM_POSITION_OPEN_PNL_TCLOSE, sizeof(TMsgPositionTCloseOpenPnlUpdate))
	{}
};

class TMsgPositionPrintOpenPnlUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionPrintOpenPnlUpdate(const char* accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& price, bool nbboPrint
#ifndef TAKION_NO_OPTIONS
//		, unsigned char securityType
		,const unsigned __int64& optionBlock
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
#endif
			TM_POSITION_OPEN_PNL_PRINT, sizeof(TMsgPositionPrintOpenPnlUpdate)),
		m_nbboPrint(nbboPrint)
	{}
	bool m_nbboPrint;
};

class TMsgPositionLevel1OpenPnlUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionLevel1OpenPnlUpdate(const char* accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& price, bool bid
#ifndef TAKION_NO_OPTIONS
//		, unsigned char securityType
		,const unsigned __int64& optionBlock
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
#endif
			TM_POSITION_OPEN_PNL_LEVEL1, sizeof(TMsgPositionLevel1OpenPnlUpdate)),
		m_bid(bid)
	{}
	bool m_bid;
};

class TMsgAutoAction : public TMsgAccountPositionObject
{
public:
	TMsgAutoAction(const char* accountName, const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		const Money& loss, const Money& constrain, bool close):
		TMsgAccountPositionObject(accountName, symbol,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
#endif
			TM_AUTO_ACTION, sizeof(TMsgAutoAction)),
		m_loss(loss),
		m_constraint(constrain),
		m_close(close)
	{
//		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}

//	Symbol m_symbol;
	Money m_loss;
	Money m_constraint;
	bool m_close;
};

class TMsgExecutionNew : public TMsgAccountObject
{
public:
	TMsgExecutionNew(unsigned int remainingQuantity, unsigned int executionId, unsigned char side, const char* accountName):
		TMsgAccountObject(accountName, TM_EXECUTION_NEW, sizeof(TMsgExecutionNew)), m_remainingQuantity(remainingQuantity), m_executionId(executionId), m_side(side)
	{}
	unsigned int m_remainingQuantity;
	unsigned int m_executionId;
	unsigned char m_side;
};

class TMsgOrderNew : public TMsgAccountObject
{
public:
	TMsgOrderNew(unsigned int clientId, unsigned int serverId, const char* accountName):
		TMsgAccountObject(accountName, TM_ORDER_NEW, sizeof(TMsgOrderNew)), m_clientId(clientId), m_serverId(serverId)
	{}
	unsigned int m_clientId;
	unsigned int m_serverId;
};

class TMsgPositionNew : public TMsgAccountObject
{
public:
	TMsgPositionNew(const unsigned __int64& symbol
#ifndef TAKION_NO_OPTIONS
		, unsigned __int64 optionBlock
#endif
		, const char* accountName):
		TMsgAccountObject(accountName, TM_POSITION_NEW, sizeof(TMsgPositionNew)), m_symbol(symbol)
#ifndef TAKION_NO_OPTIONS
		, m_optionBlock(optionBlock)
#endif
	{}
	unsigned __int64 m_symbol;
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
#endif
};

class TMsgStockUpdateLevel1 : public TMessageStockUpdate
{
public:
	TMsgStockUpdateLevel1(const char* symbol, bool hasPrints, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_LEVEL1, sizeof(TMsgStockUpdateLevel1)), m_hasPrints(hasPrints){}
	TMsgStockUpdateLevel1(const unsigned __int64& symbol, bool hasPrints, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_LEVEL1, sizeof(TMsgStockUpdateLevel1)), m_hasPrints(hasPrints){}
	bool m_hasPrints;
};

class TMsgStockNewsHistoricSearchDone : public TMessageSymbol
{
public:
	TMsgStockNewsHistoricSearchDone(const char* symbol, unsigned int newsCollectionId):TMessageSymbol(symbol, TM_STOCK_NEWS_HISTORIC_SEARCH_DONE, sizeof(TMsgStockNewsHistoricSearchDone)), m_newsCollectionId(newsCollectionId){}
	TMsgStockNewsHistoricSearchDone(const unsigned __int64& symbol, unsigned int newsCollectionId):TMessageSymbol(symbol, TM_STOCK_NEWS_HISTORIC_SEARCH_DONE, sizeof(TMsgStockNewsHistoricSearchDone)), m_newsCollectionId(newsCollectionId){}
	unsigned int m_newsCollectionId;
};

class TMsgStringNewsHistoricSearchDone : public Message
{
public:
	TMsgStringNewsHistoricSearchDone(const char* str, unsigned short strLength, unsigned int newsCollectionId):Message(TM_STRING_NEWS_HISTORIC_SEARCH_DONE, sizeof(TMsgStringNewsHistoricSearchDone) + strLength), m_newsCollectionId(newsCollectionId){}
	unsigned int m_newsCollectionId;
};

class TMsgStockUpdateHeadlines : public TMessageStockUpdate
{
public:
	TMsgStockUpdateHeadlines(const char* symbol, unsigned int newsCollectionId, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_HEADLINES, sizeof(TMsgStockUpdateHeadlines)), m_newsCollectionId(newsCollectionId){}
	TMsgStockUpdateHeadlines(const unsigned __int64& symbol, unsigned int newsCollectionId, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_HEADLINES, sizeof(TMsgStockUpdateHeadlines)), m_newsCollectionId(newsCollectionId){}
	unsigned int m_newsCollectionId;
};

class TMsgStringUpdateHeadlines : public Message
{
public:
	TMsgStringUpdateHeadlines(const char* str, unsigned short strLength, unsigned int newsCollectionId, unsigned int updateOrdinal):Message(TM_STRING_UPDATE_HEADLINES, sizeof(TMsgStringUpdateHeadlines) + strLength), m_updateOrdinal(updateOrdinal), m_newsCollectionId(newsCollectionId){}
	unsigned int m_updateOrdinal;
	unsigned int m_newsCollectionId;
};

class TMsgHeadline : public Message
{
public:
	TMsgHeadline(unsigned short additionalLength):Message(TM_HEADLINE, sizeof(TMsgHeadline) + additionalLength){}
};

/*
class TMsgNewsStory : public Message
{
public:
	TMsgNewsStory(unsigned int updateOrdinal, unsigned short additionalLength):Message(TM_NEWS_STORY, sizeof(TMsgNewsStory) + additionalLength), m_updateOrdinal(updateOrdinal){}
	unsigned int m_updateOrdinal;
};
*/

class TMsgUpdateLastNewsStory : public Message
{
public:
	TMsgUpdateLastNewsStory(unsigned int updateOrdinal):Message(TM_UPDATE_LAST_NEWS_STORY, sizeof(TMsgUpdateLastNewsStory)), m_updateOrdinal(updateOrdinal){}
	unsigned int m_updateOrdinal;
};

class TMsgNewsProfilesLoaded : public Message
{
public:
	TMsgNewsProfilesLoaded():Message(TM_NEWS_PROFILES_LOADED, sizeof(TMsgNewsProfilesLoaded)){}
};

class NewsResourceAsNumberArray : public StrAsNumberArray<size_t, 64 / sizeof(size_t)>
{
public:
	NewsResourceAsNumberArray():StrAsNumberArray(){}
	NewsResourceAsNumberArray(const char* str):StrAsNumberArray(str){}
	NewsResourceAsNumberArray(const char*& str, const char& del):StrAsNumberArray(str, del){}
	NewsResourceAsNumberArray(const char*& str, unsigned short length, const char& del):StrAsNumberArray(str, length, del){}
	NewsResourceAsNumberArray(unsigned short exactLength, const char* str):StrAsNumberArray(exactLength, str){}
	NewsResourceAsNumberArray(const std::string& str):StrAsNumberArray(str){}
	operator size_t() const{return m_numberArray[16 / sizeof(size_t) - 1];}
	DECLARE_NED_NEW
};

class FilterStringAsNumberArray : public StrAsVarNumberArray<size_t>
{
public:
	FilterStringAsNumberArray():StrAsVarNumberArray(){}
	FilterStringAsNumberArray(const char* str):StrAsVarNumberArray(str){}
	FilterStringAsNumberArray(const char*& str, const char& del):StrAsVarNumberArray(str, del){}
	FilterStringAsNumberArray(const char*& str, const unsigned short& length, const char& del):StrAsVarNumberArray(str, length, del){}
	FilterStringAsNumberArray(unsigned short exactLength, const char* str):StrAsVarNumberArray(exactLength, str){}
	FilterStringAsNumberArray(const std::string& str):StrAsVarNumberArray(str){}
//	operator size_t() const{return (size_t)*m_numberArray + m_length;}
	DECLARE_NED_NEW
};

class NewsStory
{
public:
//	NewsStory(const std::string& story, const std::string& resourceId, bool showChain):m_story(story),m_resourceId(resourceId),m_showChain(showChain){}
	NewsStory(const std::string& story, const NewsResourceAsNumberArray& resourceId, bool showChain):m_story(story),m_resourceId(resourceId),m_showChain(showChain){}
	const std::string& GetStory() const{return m_story;}
//	const std::string& GetResourceId() const{return m_resourceId;}
	const NewsResourceAsNumberArray& GetResourceId() const{return m_resourceId;}
	const char* GetResourceIdStr() const{return m_resourceId.GetString();}
	bool isShowChain() const{return m_showChain;}
	void SetStory(const std::string& story, const std::string& resourceId, bool showChain)
	{
		m_story = story;
		m_showChain = showChain;
	}
	DECLARE_NED_NEW
protected:
	std::string m_story;
	NewsResourceAsNumberArray m_resourceId;
	bool m_showChain;
};

class TMsgNewsStoryContents : public Message
{
public:
	TMsgNewsStoryContents(const NewsStory* newsStory):Message(TM_NEWS_STORY_CONTENTS, sizeof(TMsgNewsStoryContents)), m_newsStory(newsStory){}
	const NewsStory* m_newsStory;
};

enum SubscriptionTypes : unsigned char
{
    UpdatesOnly        = 0,
    SubscribeSymbol    = 1,
    UpdatesOnlyAll    = 0xfe,
    RefreshAll        = 0xff,
};
/*
class TMsgReqKick : public Message
{
public:
	TMsgReqKick(const char* traderId):Message(M_REQ_KICK, sizeof(TMsgReqKick))
	{
		U_CopyAndPad(m_traderId, sizeof(m_traderId), traderId, '\0');
	}
	char m_traderId[MAX_TRADER_ID_SIZE];
};
*/
class TMsgReqRefreshSymbol : public TMessageSymbol
{
public:
	TMsgReqRefreshSymbol(const char* symbol, unsigned char flags = SubscribeSymbol, unsigned char blockSize = 1, unsigned int requestID = 0):
		TMessageSymbol(symbol, M_REQ_REFRESH_SYMBOL, sizeof(TMsgReqRefreshSymbol))
		, m_flags(flags)
		, m_blockSize(blockSize)
		, m_requestID(requestID)
	{}
    unsigned char m_flags;
    unsigned char m_blockSize;
    unsigned int m_requestID;
};

class TMsgReqUnsubscribeSymbol : public TMessageSymbol
{
public:
	TMsgReqUnsubscribeSymbol(const char* symbol):TMessageSymbol(symbol, M_REQ_UNSUBSCRIBE_SYMBOL, sizeof(TMsgReqUnsubscribeSymbol)){}
};

class TMsgEndOfDaySummaryReportBase : public TMessageTimeSymbol
{
public:
	unsigned int m_todaysClosePriceDollar;
	unsigned int m_todaysClosePriceFraction;
    unsigned __int64 m_volume;
protected:
    TMsgEndOfDaySummaryReportBase(const char* symbol,
		unsigned int time,
		unsigned int todaysClosePriceDollar,
		unsigned int todaysClosePriceFraction,
		unsigned __int64 volume,
		unsigned short type,
		unsigned short length):
		
		TMessageTimeSymbol(symbol, time, type, length),
		m_todaysClosePriceDollar(todaysClosePriceDollar),
		m_todaysClosePriceFraction(todaysClosePriceFraction),
		m_volume(volume)
    {}
};

class TMsgEndOfDaySummaryReport : public TMsgEndOfDaySummaryReportBase
{
public:
    TMsgEndOfDaySummaryReport(const char* symbol,
		unsigned int time,
		unsigned int todaysClosePriceDollar,
		unsigned int todaysClosePriceFraction,
		unsigned __int64 volume):
		
		TMsgEndOfDaySummaryReportBase(symbol, time, todaysClosePriceDollar, todaysClosePriceFraction, volume, M_EOD_SUMMARY_REPORT, sizeof(TMsgEndOfDaySummaryReport))
    {}
};

class TMsgMsEndOfDaySummaryReport : public TMsgEndOfDaySummaryReportBase
{
public:
    TMsgMsEndOfDaySummaryReport(const char* symbol,
		unsigned int time,
		unsigned int todaysClosePriceDollar,
		unsigned int todaysClosePriceFraction,
		unsigned __int64 volume):
		
		TMsgEndOfDaySummaryReportBase(symbol, time, todaysClosePriceDollar, todaysClosePriceFraction, volume, M_MS_EOD_SUMMARY_REPORT, sizeof(TMsgMsEndOfDaySummaryReport))
    {}
};

class TMsgShortSaleIndicatorsBase : public TMessageTimeSymbol
{
public:
	char m_shortSaleThresholdIndicator;//'Y', 'N'
	char m_regSHOTestIndicator;//'0', '1', '2'
protected:
    TMsgShortSaleIndicatorsBase(const char* symbol,
		unsigned int time,
		char shortSaleThresholdIndicator,
		char regSHOTestIndicator,
		unsigned short type,
		unsigned short length):

		TMessageTimeSymbol(symbol, time, type, length),
        m_shortSaleThresholdIndicator(shortSaleThresholdIndicator),
        m_regSHOTestIndicator(regSHOTestIndicator)
    {}

};

class TMsgShortSaleIndicators : public TMsgShortSaleIndicatorsBase
{
public:
    TMsgShortSaleIndicators(const char* symbol,
		unsigned int time,
		char shortSaleThresholdIndicator,
		char regSHOTestIndicator):

		TMsgShortSaleIndicatorsBase(symbol, time, shortSaleThresholdIndicator, regSHOTestIndicator, M_SHORT_SALE_INDICATORS, sizeof(TMsgShortSaleIndicators))
    {}
};

class TMsgMsShortSaleIndicators : public TMsgShortSaleIndicatorsBase
{
public:
    TMsgMsShortSaleIndicators(const char* symbol,
		unsigned int time,
		char shortSaleThresholdIndicator,
		char regSHOTestIndicator):

		TMsgShortSaleIndicatorsBase(symbol, time, shortSaleThresholdIndicator, regSHOTestIndicator, M_MS_SHORT_SALE_INDICATORS, sizeof(TMsgMsShortSaleIndicators))
    {}
};

class TMsgPmiBase : public TMessageTimeSymbol
{
public:
	unsigned int m_bidDollar;
	unsigned int m_bidFraction;
	unsigned int m_askDollar;
	unsigned int m_askFraction;
	unsigned char m_securityStatus;
	unsigned char m_adjustment;
protected:
	TMsgPmiBase(const char* symbol,
		unsigned int time,
		unsigned int bidDollar,
		unsigned int bidFraction,
		unsigned int askDollar,
		unsigned int askFraction,
		unsigned char securityStatus,
		unsigned char adjustment,
		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_bidDollar(bidDollar),
		m_bidFraction(bidFraction),
		m_askDollar(askDollar),
		m_askFraction(askFraction),
        m_securityStatus(securityStatus),
        m_adjustment(adjustment)
    {
	}
};

class TMsgPmi : public TMsgPmiBase
{
public:
    TMsgPmi(const char* symbol,
		unsigned int time,
		unsigned int bidDollar,
		unsigned int bidFraction,
		unsigned int askDollar,
		unsigned int askFraction,
		unsigned char securityStatus,
		unsigned char adjustment):
		TMsgPmiBase(symbol, time, bidDollar, bidFraction, askDollar, askFraction, securityStatus, adjustment, M_PMI, sizeof(TMsgPmi))
    {}
};

class TMsgMsPmi : public TMsgPmiBase
{
public:
    TMsgMsPmi(const char* symbol,
		unsigned int time,
		unsigned int bidDollar,
		unsigned int bidFraction,
		unsigned int askDollar,
		unsigned int askFraction,
		unsigned char securityStatus,
		unsigned char adjustment):
		TMsgPmiBase(symbol, time, bidDollar, bidFraction, askDollar, askFraction, securityStatus, adjustment, M_MS_PMI, sizeof(TMsgMsPmi))
    {}
};

class TMsgLrpBase : public TMessageTimeSymbol
{
public:
	unsigned int m_lowDollar;
	unsigned int m_lowFraction;
	unsigned int m_highDollar;
	unsigned int m_highFraction;
	unsigned char m_changeIndicator;
protected:
	TMsgLrpBase(const char* symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator,
		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_lowDollar(lowDollar),
		m_lowFraction(lowFraction),
		m_highDollar(highDollar),
		m_highFraction(highFraction),
        m_changeIndicator(changeIndicator)
    {
	}
};

class TMsgLrp : public TMsgLrpBase
{
public:
    TMsgLrp(const char* symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator):
		TMsgLrpBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, changeIndicator, M_LRP, sizeof(TMsgLrp))
    {}
};

class TMsgLuld : public TMsgLrpBase
{
public:
    TMsgLuld(const char* symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator):
		TMsgLrpBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, changeIndicator, M_LULD, sizeof(TMsgLuld))
    {}
};

class TMsgMsLrp : public TMsgLrpBase
{
public:
    TMsgMsLrp(const char* symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator):
		TMsgLrpBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, changeIndicator, M_MS_LRP, sizeof(TMsgMsLrp))
    {}
};

class TMsgMsLuld : public TMsgLrpBase
{
public:
    TMsgMsLuld(const char* symbol,
		unsigned int time,
		unsigned int lowDollar,
		unsigned int lowFraction,
		unsigned int highDollar,
		unsigned int highFraction,
		unsigned char changeIndicator):
		TMsgLrpBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, changeIndicator, M_MS_LULD, sizeof(TMsgMsLuld))
    {}
};

class TMsgTradeTimeBase : public TMessageTimeSymbol
{
public:
	unsigned int m_tradeTime;
protected:
	TMsgTradeTimeBase(const char* symbol,
		unsigned int time,
		unsigned int tradeTime,
		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_tradeTime(tradeTime)
    {
	}
};

class TMsgTradeTime : public TMsgTradeTimeBase
{
public:
    TMsgTradeTime(const char* symbol,
		unsigned int time,
		unsigned int tradeTime):
		TMsgTradeTimeBase(symbol, time, tradeTime, M_T_TIME, sizeof(TMsgTradeTime))
    {}
};

class TMsgMsTradeTime : public TMsgTradeTimeBase
{
public:
    TMsgMsTradeTime(const char* symbol,
		unsigned int time,
		unsigned int tradeTime):
		TMsgTradeTimeBase(symbol, time, tradeTime, M_MS_T_TIME, sizeof(TMsgMsTradeTime))
    {}
};

class TMsgRpiBase : public TMessageTimeSymbol
{
public:
	char m_indicator;
protected:
	TMsgRpiBase(const char* symbol,
		unsigned int time,
		char indicator,
		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_indicator(indicator)
    {
	}
};

class TMsgRpi : public TMsgRpiBase
{
public:
    TMsgRpi(const char* symbol,
		unsigned int time,
		unsigned char indicator):
		TMsgRpiBase(symbol, time, indicator, M_RPI, sizeof(TMsgRpi))
    {}
};

class TMsgMsRpi : public TMsgRpiBase
{
public:
    TMsgMsRpi(const char* symbol,
		unsigned int time,
		unsigned char indicator):
		TMsgRpiBase(symbol, time, indicator, M_MS_RPI, sizeof(TMsgMsRpi))
    {}
};

enum AggregatePrintFlags : unsigned char
{
	APF_NoPriceChanges		= 0,
	APF_LastPriceChanged	= 1,
	APF_LowPriceChanged		= 2,
	APF_HighPriceChanged	= 4,
	APF_OpeningPrice		= 8,
	APF_ClosingPrice		= 0x10,
	APF_PrimaryOpeningPrice	= 0x20,
	APF_NewIntraDayTick		= 0x80,
};

class TMsgAggregatedPrint : public TMessageTimeSymbol
{
public:
	TMsgAggregatedPrint(const char* symbol,
		unsigned int time,
		unsigned int priceDollar,
		unsigned int priceFraction,
		unsigned long size,
		unsigned char flags,
		unsigned char flagsL1):
		TMessageTimeSymbol(symbol, time, M_AGGREGATED_PRINT, sizeof(TMsgAggregatedPrint)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_flags(flags),
		m_flagsL1(flagsL1)
	{}
 
	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned long m_size;
	unsigned char m_flags;
	unsigned char m_flagsL1;
};

class TSmMsgAggregatedPrint : public TMessageTime
{
public:
	TSmMsgAggregatedPrint(unsigned short symbol,
		unsigned int time,
		unsigned int priceDollar,
		unsigned int priceFraction,
		unsigned long size,
		unsigned char flags,
		unsigned char flagsL1):
		TMessageTime(time, SM_M_AGGREGATED_PRINT, sizeof(TSmMsgAggregatedPrint)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_symbol(symbol),
		m_flags(flags),
		m_flagsL1(flagsL1)
	{}
 
	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned long m_size;
	unsigned short m_symbol;
	unsigned char m_flags;
	unsigned char m_flagsL1;
};

//	TMessageSymbol(const char* symbol, unsigned short type, unsigned short length):
class TMsgMsAggregatedPrintShort : public TMessageSymbol
{
public:
	TMsgMsAggregatedPrintShort(const char* symbol,
		unsigned int price,
		unsigned short size,
		unsigned char flags):
		TMessageSymbol(symbol, M_MS_AGGREGATED_PRINT_SHORT, sizeof(TMsgMsAggregatedPrintShort)),
		m_price(price),
		m_size(size),
		m_flags(flags)
	{}

	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_size;//Up to 65535
	unsigned char m_flags;
};

class TMsgMsAggregatedPrintLong : public TMessageSymbol
{
public:
	TMsgMsAggregatedPrintLong(const char* symbol,
		unsigned int priceDollar,
		unsigned int priceFraction,
		unsigned int size,
		unsigned char flags):
		TMessageSymbol(symbol, M_MS_AGGREGATED_PRINT_LONG, sizeof(TMsgMsAggregatedPrintLong)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_flags(flags)
	{}

	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned char m_flags;
};
/*
class TSmMsgMsTradeShort: public Message
{
public:
	TSmMsgMsTradeShort(unsigned short symbol,
		unsigned int price,
		unsigned short size,
		char saleCondition,
		char marketCenter):
		Message(SM_MS_TRADE_REPORT_SHORT, sizeof(TSmMsgMsTradeShort)),
		m_symbol(symbol),
		m_price(price),
		m_size(size),
		m_saleCondition(saleCondition),
		m_marketCenterID(marketCenter)
	{}
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_symbol;
	unsigned short m_size;
	char m_saleCondition;
	char m_marketCenterID;
};
*/
class TSmMsgMsAggregatedPrintShort : public Message
{
public:
	TSmMsgMsAggregatedPrintShort(unsigned short symbol, 
		unsigned int price,
		unsigned short size,
		unsigned char flags):
		Message(SM_MS_AGGREGATED_PRINT_SHORT, sizeof(TSmMsgMsAggregatedPrintShort)),
		m_price(price),
		m_size(size),
		m_symbol(symbol),
		m_flags(flags)
	{}

	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_size;//Up to 65535
	unsigned short m_symbol;
	unsigned char m_flags;
};

class TSmMsgMsAggregatedPrintLong : public Message
{
public:
	TSmMsgMsAggregatedPrintLong(unsigned short symbol, 
		unsigned int priceDollar,
		unsigned int priceFraction,
		unsigned int size,
		unsigned char flags):
		Message(SM_MS_AGGREGATED_PRINT_LONG, sizeof(TSmMsgMsAggregatedPrintLong)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_symbol(symbol),
		m_flags(flags)
	{}

	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned short m_symbol;
	unsigned char m_flags;
};

class TMsgDividendsAndSplitsBase : public TMessageTimeSymbol
{
public:
	unsigned int m_dividendDollar;
	unsigned int m_dividendFraction;
    unsigned short m_splitNumerator;
    unsigned short m_splitDenominator;
	char m_exDivDate[sizeof(unsigned int) + 1];
protected:
    TMsgDividendsAndSplitsBase(const char* symbol,
		unsigned int time,
		unsigned int dividendDollar,
		unsigned int dividendFraction,
	    unsigned short splitNumerator,
		unsigned short splitDenominator,
		unsigned int exDivDate,
		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_dividendDollar(dividendDollar),
		m_dividendFraction(dividendFraction),
        m_splitNumerator(splitNumerator),
        m_splitDenominator(splitDenominator)
    {
		*(unsigned int*)m_exDivDate = exDivDate;
		m_exDivDate[sizeof(unsigned int)] = '\0';
	}
};

class TMsgDividendsAndSplits : public TMsgDividendsAndSplitsBase
{
public:
    TMsgDividendsAndSplits(const char* symbol,
		unsigned int time,
		unsigned int dividendDollar,
		unsigned int dividendFraction,
	    unsigned short splitNumerator,
		unsigned short splitDenominator,
		unsigned int exDivDate):
		TMsgDividendsAndSplitsBase(symbol,
			time,
			dividendDollar,
			dividendFraction,
			splitNumerator,
			splitDenominator,
			exDivDate,
			M_DIVIDENDS_AND_SPLITS,
			sizeof(TMsgDividendsAndSplits))
    {}
};

class TMsgMsDividendsAndSplits : public TMsgDividendsAndSplitsBase
{
public:
    TMsgMsDividendsAndSplits(const char* symbol,
		unsigned int time,
		unsigned int dividendDollar,
		unsigned int dividendFraction,
	    unsigned short splitNumerator,
		unsigned short splitDenominator,
		unsigned int exDivDate):
		TMsgDividendsAndSplitsBase(symbol,
			time,
			dividendDollar,
			dividendFraction,
			splitNumerator,
			splitDenominator,
			exDivDate,
			M_MS_DIVIDENDS_AND_SPLITS,
			sizeof(TMsgMsDividendsAndSplits))
    {}
};

class TMsgPreviousDayCloseBase : public TMessageTimeSymbol
{
public:
	unsigned int m_closePriceDollar;
	unsigned int m_closePriceFraction;
protected:
    TMsgPreviousDayCloseBase(const char* symbol,
		unsigned int time,
		unsigned int closePriceDollar,
		unsigned int closePriceFraction,
		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_closePriceDollar(closePriceDollar),
		m_closePriceFraction(closePriceFraction)
    {}
};

class TMsgPreviousDayClose : public TMsgPreviousDayCloseBase
{
public:
    TMsgPreviousDayClose(const char* symbol,
		unsigned int time,
		unsigned int closePriceDollar,
		unsigned int closePriceFraction):
		TMsgPreviousDayCloseBase(symbol,
			time,
			closePriceDollar,
			closePriceFraction,
			M_PREVIOUS_DAY_CLOSE,
			sizeof(TMsgPreviousDayClose))
    {}
};

class TMsgMsPreviousDayClose : public TMsgPreviousDayCloseBase
{
public:
    TMsgMsPreviousDayClose(const char* symbol,
		unsigned int time,
		unsigned int closePriceDollar,
		unsigned int closePriceFraction):
		TMsgPreviousDayCloseBase(symbol,
			time,
			closePriceDollar,
			closePriceFraction,
			M_MS_PREVIOUS_DAY_CLOSE,
			sizeof(TMsgMsPreviousDayClose))
    {}
};

class TMsgResetImbalances : public Message
{
public:
	TMsgResetImbalances():Message(M_RESET_IMBALANCES, sizeof(TMsgResetImbalances)){}
};

class TMsgMsResetImbalances : public Message
{
public:
	TMsgMsResetImbalances():Message(M_MS_RESET_IMBALANCES, sizeof(TMsgMsResetImbalances)){}
};

class TMsgSymbolOrdinalValue : public TMessageSymbol
{
public:
	unsigned short m_ordinal;
protected:
	TMsgSymbolOrdinalValue(const char* symbol, unsigned short ordinal, unsigned short type, unsigned short length):TMessageSymbol(symbol, type, length), m_ordinal(ordinal){}
	TMsgSymbolOrdinalValue(const unsigned __int64& symbol, unsigned short ordinal, unsigned short type, unsigned short length):TMessageSymbol(symbol, type, length), m_ordinal(ordinal){}
};

class TMsgSymbolOrdinalHtb : public TMsgSymbolOrdinalValue
{
public:
//	bool m_htb;
	unsigned char m_htb;
protected:
	TMsgSymbolOrdinalHtb(const char* symbol, unsigned short ordinal, unsigned char htb, unsigned short type, unsigned short length):TMsgSymbolOrdinalValue(symbol, ordinal, type, length), m_htb(htb){}
	TMsgSymbolOrdinalHtb(const unsigned __int64& symbol, unsigned short ordinal, unsigned char htb, unsigned short type, unsigned short length):TMsgSymbolOrdinalValue(symbol, ordinal, type, length), m_htb(htb){}
};

class TMsgSymbolOrdinalPrice : public TMsgSymbolOrdinalValue
{
public:
	Price m_price;
protected:
	TMsgSymbolOrdinalPrice(const char* symbol, unsigned short ordinal, const Price& price, unsigned short type, unsigned short length):TMsgSymbolOrdinalValue(symbol, ordinal, type, length), m_price(price){}
	TMsgSymbolOrdinalPrice(const unsigned __int64& symbol, unsigned short ordinal, const Price& price, unsigned short type, unsigned short length):TMsgSymbolOrdinalValue(symbol, ordinal, type, length), m_price(price){}
};

class TMsgSymbolOrdinalStockLoanInfo : public TMsgSymbolOrdinalPrice
{
public:
	unsigned int m_quantity;
	unsigned char m_discountFlag;
protected:
	TMsgSymbolOrdinalStockLoanInfo(const char* symbol, unsigned short ordinal, const Price& price, unsigned int quantity, unsigned char discountFlag, unsigned short type, unsigned short length):TMsgSymbolOrdinalPrice(symbol, ordinal, price, type, length), m_quantity(quantity), m_discountFlag(discountFlag){}
	TMsgSymbolOrdinalStockLoanInfo(const unsigned __int64& symbol, unsigned short ordinal, const Price& price, unsigned int quantity, unsigned char discountFlag, unsigned short type, unsigned short length):TMsgSymbolOrdinalPrice(symbol, ordinal, price, type, length), m_quantity(quantity),m_discountFlag(discountFlag){}
};

class TMsgStockHtb : public TMsgSymbolOrdinalHtb
{
public:
	TMsgStockHtb(const char* symbol, unsigned short ordinal, unsigned char htb):TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_STOCK_HTB, sizeof(TMsgStockHtb)){}
	TMsgStockHtb(const unsigned __int64& symbol, unsigned short ordinal, unsigned char htb):TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_STOCK_HTB, sizeof(TMsgStockHtb)){}
};

class TMsgEquityHtb : public TMsgSymbolOrdinalHtb
{
public:
	TMsgEquityHtb(const char* symbol, unsigned short ordinal, unsigned char htb):TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_EQUITY_HTB, sizeof(TMsgEquityHtb)){}
	TMsgEquityHtb(const unsigned __int64& symbol, unsigned short ordinal, unsigned char htb):TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_EQUITY_HTB, sizeof(TMsgEquityHtb)){}
};

class TMsgStockBorrowPrice : public TMsgSymbolOrdinalStockLoanInfo
{
public:
	TMsgStockBorrowPrice(const char* symbol, unsigned short ordinal, const StockLoanInfo& price):TMsgSymbolOrdinalStockLoanInfo(symbol, ordinal, price, price.GetQuantity(), price.GetDiscountFlag(), TM_STOCK_BORROW_PRICE, sizeof(TMsgStockBorrowPrice)){}
	TMsgStockBorrowPrice(const unsigned __int64& symbol, unsigned short ordinal, const StockLoanInfo& price):TMsgSymbolOrdinalStockLoanInfo(symbol, ordinal, price, price.GetQuantity(), price.GetDiscountFlag(), TM_STOCK_BORROW_PRICE, sizeof(TMsgStockBorrowPrice)){}
};

class TMsgEquityBorrowPrice : public TMsgSymbolOrdinalStockLoanInfo
{
public:
	TMsgEquityBorrowPrice(const char* symbol, unsigned short ordinal, const StockLoanInfo& price):TMsgSymbolOrdinalStockLoanInfo(symbol, ordinal, price, price.GetQuantity(), price.GetDiscountFlag(), TM_EQUITY_BORROW_PRICE, sizeof(TMsgEquityBorrowPrice)){}
	TMsgEquityBorrowPrice(const unsigned __int64& symbol, unsigned short ordinal, const StockLoanInfo& price):TMsgSymbolOrdinalStockLoanInfo(symbol, ordinal, price, price.GetQuantity(), price.GetDiscountFlag(), TM_EQUITY_BORROW_PRICE, sizeof(TMsgEquityBorrowPrice)){}
};

class TMsgPositionBorrowPrice : public TMsgSymbolOrdinalStockLoanInfo
{
public:
	TMsgPositionBorrowPrice(const char* accountId, const char* symbol, unsigned short ordinal, const StockLoanInfo& price):
		TMsgSymbolOrdinalStockLoanInfo(symbol, ordinal, price, price.GetQuantity(), price.GetDiscountFlag(), TM_POSITION_BORROW_PRICE, sizeof(TMsgPositionBorrowPrice))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0');
	}
	TMsgPositionBorrowPrice(const char* accountId, const unsigned __int64& symbol, unsigned short ordinal, const StockLoanInfo& price):
		TMsgSymbolOrdinalStockLoanInfo(symbol, ordinal, price, price.GetQuantity(), price.GetDiscountFlag(), TM_POSITION_BORROW_PRICE, sizeof(TMsgPositionBorrowPrice))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0');
	}
	char m_accountId[MAX_ACCOUNT_SIZE];
};

class TMsgPositionHtb : public TMsgSymbolOrdinalHtb
{
public:
	TMsgPositionHtb(const char* accountId, const char* symbol, unsigned short ordinal, unsigned char htb):
		TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_POSITION_HTB, sizeof(TMsgPositionHtb))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0');
	}
	TMsgPositionHtb(const char* accountId, const unsigned __int64& symbol, unsigned short ordinal, unsigned char htb):
		TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_POSITION_HTB, sizeof(TMsgPositionHtb))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0');
	}
	char m_accountId[MAX_ACCOUNT_SIZE];
};


class TMsgStockResetImbalances : public TMessageSymbol
{
public:
	TMsgStockResetImbalances(const char* symbol):TMessageSymbol(symbol, TM_STOCK_RESET_IMBALANCES, sizeof(TMsgStockResetImbalances)){}
	TMsgStockResetImbalances(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_RESET_IMBALANCES, sizeof(TMsgStockResetImbalances)){}
};

class TMsgEquityResetImbalances : public TMessageSymbol
{
public:
	TMsgEquityResetImbalances(const char* symbol):TMessageSymbol(symbol, TM_EQUITY_RESET_IMBALANCES, sizeof(TMsgEquityResetImbalances)){}
	TMsgEquityResetImbalances(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_EQUITY_RESET_IMBALANCES, sizeof(TMsgEquityResetImbalances)){}
};


class TMsgEquityChartLoaded : public TMessageSymbol
{
public:
	TMsgEquityChartLoaded(const char* symbol):TMessageSymbol(symbol, TM_EQUITY_CHART_LOADED, sizeof(TMsgEquityChartLoaded)){}
	TMsgEquityChartLoaded(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_EQUITY_CHART_LOADED, sizeof(TMsgEquityChartLoaded)){}
};

class TMsgSymbolRequestDone : public TMessageSymbol
{
public:
	unsigned int m_requestId;
	bool m_failed;
protected:
	TMsgSymbolRequestDone(const char* symbol, unsigned int requestId, bool failed, unsigned short type, unsigned short length):TMessageSymbol(symbol, type, length), m_requestId(requestId), m_failed(failed){}
	TMsgSymbolRequestDone(const unsigned __int64& symbol, unsigned int requestId, bool failed, unsigned short type, unsigned short length):TMessageSymbol(symbol, type, length), m_requestId(requestId), m_failed(failed){}
};
/*
class TMsgEquityHistoricalChartLoaded : public TMsgSymbolRequestDone
{
public:
	TMsgEquityHistoricalChartLoaded(const char* symbol, unsigned int requestId, bool failed):TMsgSymbolRequestDone(symbol, requestId, failed, TM_EQUITY_HISTORICAL_CHART_LOADED, sizeof(TMsgEquityHistoricalChartLoaded)){}
	TMsgEquityHistoricalChartLoaded(const unsigned __int64& symbol, unsigned int requestId, bool failed):TMsgSymbolRequestDone(symbol, requestId, failed, TM_EQUITY_HISTORICAL_CHART_LOADED, sizeof(TMsgEquityHistoricalChartLoaded)){}
};

class TMsgEquityHistoricalIntradayChartLoaded : public TMsgSymbolRequestDone
{
public:
	TMsgEquityHistoricalIntradayChartLoaded(const char* symbol, unsigned int requestId, bool failed):TMsgSymbolRequestDone(symbol, requestId, failed, TM_EQUITY_HISTORICAL_INTRADAY_CHART_LOADED, sizeof(TMsgEquityHistoricalChartLoaded)){}
	TMsgEquityHistoricalIntradayChartLoaded(const unsigned __int64& symbol, unsigned int requestId, bool failed):TMsgSymbolRequestDone(symbol, requestId, failed, TM_EQUITY_HISTORICAL_INTRADAY_CHART_LOADED, sizeof(TMsgEquityHistoricalChartLoaded)){}
};
*/
/*
enum BookID : unsigned char
{
	NasdaqItch		= 0x01,
	NyseArca		= 0x02,
	BATSBook		= 0x03,
	EDGABook		= 0x04,
	EDGXBook		= 0x05,
	UQDFCQSBook		= 0x06,

	AllBooks		= 0xff,
};
*/
enum StockRefreshSteps : unsigned char
{
	SRS_DESCRIPTION = 1 << 0,
	SRS_ATTRIBUTES = 1 << 1,
	SRS_LEVEL1 = 1 << 2,
	SRS_LEVEL2 = 1 << 3,
	SRS_ADDITIONAL = 1 << 4,
	SRS_PRINTS = 1 << 5,
};

enum StockRefreshStatus : unsigned char
{
	REFRESH_EndOfBlock		= 0x20,
	REFRESH_EndOfRefresh	= 0x40,
	REFRESH_RefreshFailed	= 0x80,
};

class TMsgRespRefreshSymbol : public Message
{
public:
	TMsgRespRefreshSymbol(unsigned short dataSize,
		unsigned int requestId,
		const char* symbol,
		unsigned char steps,
		unsigned char flags,
		unsigned char bookID,
		char marketStatus):
		Message(M_RESP_REFRESH_SYMBOL, dataSize),
		m_requestID(requestId),
		m_steps(steps),
		m_flags(flags),
		m_bookID(bookID),
		m_marketStatus(marketStatus)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
	unsigned int	m_requestID;
	Symbol			m_symbol;
	unsigned char	m_steps;
	unsigned char	m_flags;
	unsigned char	m_bookID;
	char m_marketStatus;
};

class TMsgIndexValue : public TMessageSymbol
{
public:
	TMsgIndexValue(const char* symbol, int whole, int fraction):
		TMessageSymbol(symbol, M_INDEX, sizeof(TMsgIndexValue)),
		m_whole(whole),
		m_fraction(fraction)
	{}
	int m_whole;
	int m_fraction;
};

class TMsgReqRefreshIndex : public TMessageSymbol
{
public:
	TMsgReqRefreshIndex(const char* symbol, unsigned char flags = SubscribeSymbol, unsigned char blockSize = 1, unsigned int requestID = 0):
		TMessageSymbol(symbol, M_REQ_REFRESH_INDEX, sizeof(TMsgReqRefreshIndex))
		, m_flags(flags)
		, m_blockSize(blockSize)
		, m_requestID(requestID)
	{}
    unsigned char m_flags;
    unsigned char m_blockSize;
    unsigned int m_requestID;
};

class TMsgRespRefreshIndex : public Message
{
public:
	TMsgRespRefreshIndex(unsigned short dataSize)
		: Message(M_RESP_REFRESH_INDEX, dataSize)
		, m_requestID( 0 )
		, m_steps( 0 )
		, m_flags( 0 )
//		, m_bookID( AllBooks )
	{}

	unsigned int	m_requestID;
	Symbol			m_symbol;
	unsigned char	m_steps;
	unsigned char	m_flags;
//	unsigned char	m_bookID;
//	char m_marketStatus;
};

class TMsgReqIndexChart : public TMessageSymbol
{
public:
	TMsgReqIndexChart(const char* symbol, unsigned long requestId = 0):TMessageSymbol(symbol, M_REQ_INDEX_CHART, sizeof(TMsgReqIndexChart)), m_requestId(requestId){}
	unsigned long m_requestId;
};

class TMsgRespIndexChart : public TMessageSymbol
{
public:
	TMsgRespIndexChart(const char* symbol, unsigned long requestId, unsigned short minute, unsigned char tickSize, unsigned short ticks, bool done):
		TMessageSymbol(symbol, M_RESP_INDEX_CHART, sizeof(TMsgRespIndexChart) + (unsigned int)tickSize * ticks),
		m_requestId(requestId),
		m_minute(minute),
		m_tickSize(tickSize),
		m_done(done)
	{}
	unsigned long m_requestId;
	unsigned short m_minute;
	unsigned char m_tickSize;
	unsigned char m_done;
};

class TMsgSystemEvent : public Message
{
public:
	TMsgSystemEvent(unsigned char eventCode, unsigned char source):Message(M_SYSTEM_EVENT, sizeof(TMsgSystemEvent)), m_eventCode(eventCode), m_source(source){}
	unsigned char m_eventCode;
	unsigned char m_source;
};

class TMsgStockDirectory : public TMessageTimeSymbol
{
public:
	TMsgStockDirectory(const char* symbol,
		unsigned int time,
		unsigned long roundLotSize,
		bool roundLotsOnly,
		char marketCategory,
		char financialStatusIndicator):
		TMessageTimeSymbol(symbol, time, M_STOCK_DIRECTORY, sizeof(TMsgStockDirectory)),
		m_roundLotSize(roundLotSize),
		m_roundLotsOnly(roundLotsOnly),
		m_marketCategory(marketCategory),
		m_financialStatusIndicator(financialStatusIndicator)
	{}
	unsigned long m_roundLotSize;
	bool m_roundLotsOnly;
	char m_marketCategory;
	char m_financialStatusIndicator;
};

class TMsgStockTradingActionBase : public TMessageTimeSymbol
{
public:
	char m_tradingState;
	char m_tradingActionReason[4];
protected:
	TMsgStockTradingActionBase(const char* symbol,
		unsigned int time,
		char tradingState,
		unsigned int tradingActionReason,
		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_tradingState(tradingState)
	{
		*(unsigned int*)m_tradingActionReason = tradingActionReason;
	}
};

class TMsgStockTradingAction : public TMsgStockTradingActionBase
{
public:
	TMsgStockTradingAction(const char* symbol,
		unsigned int time,
		char tradingState,
		unsigned int tradingActionReason):
		TMsgStockTradingActionBase(symbol,
			time,
			tradingState,
			tradingActionReason,
			M_STOCK_TRADING_ACTION,
			sizeof(TMsgStockTradingAction))
	{
	}
};

class TMsgMsStockTradingAction : public TMsgStockTradingActionBase
{
public:
	TMsgMsStockTradingAction(const char* symbol,
		unsigned int time,
		char tradingState,
		unsigned int tradingActionReason):
		TMsgStockTradingActionBase(symbol,
			time,
			tradingState,
			tradingActionReason,
			M_MS_STOCK_TRADING_ACTION,
			sizeof(TMsgMsStockTradingAction))
	{
	}
};

class ReqChartBase : public TMessageSymbol
{
public:
	unsigned long m_requestId;
	ReqChartBase(const char* symbol, unsigned short type, unsigned short length, unsigned long requestId = 0):TMessageSymbol(symbol, type, length), m_requestId(requestId){}
};

class TMsgReqChart : public ReqChartBase
{
public:
	TMsgReqChart(const char* symbol, unsigned long requestId = 0):ReqChartBase(symbol, M_REQ_CHART, sizeof(TMsgReqChart), requestId){}
};
/*
class TSmMsgReqChart : public ReqChartBase
{
public:
	TSmMsgReqChart(const char* symbol, unsigned long requestId = 0):ReqChartBase(symbol, SM_REQ_CHART, sizeof(TSmMsgReqChart), requestId){}
};
*/
class TSmMsgReqChart : public Message
{
public:
	TSmMsgReqChart(unsigned short symbol, unsigned long requestId = 0):Message(SM_REQ_CHART, sizeof(TSmMsgReqChart)), m_requestId(requestId), m_symbol(symbol){}
	unsigned long m_requestId;
	unsigned short m_symbol;
};

class MsgIndexChartPoint
{
public:
	SignedPrice m_firstPrice;
	SignedPrice m_lastPrice;
	SignedPrice m_highPrice;
	SignedPrice m_lowPrice;
};

class MsgChartPoint
{
public:
	Price m_moneySpent;
	unsigned int m_volume;
	unsigned int m_firstPrice;//18 bytes for dollars, 14 bytes for 4 digits
	unsigned int m_lastPrice;//18 bytes for dollars, 14 bytes for 4 digits
	unsigned int m_highPrice;//18 bytes for dollars, 14 bytes for 4 digits
	unsigned int m_lowPrice;//18 bytes for dollars, 14 bytes for 4 digits
};

class TMsgRespChart : public TMessageSymbol
{
public:
	TMsgRespChart(const char* symbol, unsigned long requestId, unsigned short minute, unsigned char tickSize, unsigned short ticks, bool done):
		TMessageSymbol(symbol, M_RESP_CHART, sizeof(TMsgRespChart) + (unsigned int)tickSize * ticks),
		m_requestId(requestId),
		m_minute(minute),
		m_tickSize(tickSize),
		m_done(done)
	{}
	unsigned long m_requestId;
	unsigned short m_minute;
	unsigned char m_tickSize;
	unsigned char m_done;
};

class TMsgNewTick : public TMessageSymbol
{
public:
	unsigned short m_minute;
protected:
	TMsgNewTick(const char* symbol, unsigned short minute, unsigned short type, unsigned short size):TMessageSymbol(symbol, type, size), m_minute(minute){}
};

class TMsgEquityNewTick : public TMsgNewTick
{
public:
	TMsgEquityNewTick(const char* symbol, unsigned short minute):TMsgNewTick(symbol, minute, M_NEW_TICK, sizeof(TMsgEquityNewTick)){}
};

class TMsgIndexNewTick : public TMsgNewTick
{
public:
	TMsgIndexNewTick(const char* symbol, unsigned short minute):TMsgNewTick(symbol, minute, M_INDEX_NEW_TICK, sizeof(TMsgIndexNewTick)){}
};

class TMsgTickCorrection : public TMessageSymbol
{
public:
	TMsgTickCorrection(const char* symbol,
		unsigned int volume,
		unsigned int moneyDollars,
		unsigned int moneyFraction,
		unsigned int first,
		unsigned int last,
		unsigned int high,
		unsigned int low,
		unsigned short minute):
		TMessageSymbol(symbol, M_TICK_CORRECTION, sizeof(TMsgTickCorrection)),
		m_volume(volume),
		m_moneyDollars(moneyDollars),
		m_moneyFraction(moneyFraction),
		m_first(first),
		m_last(last),
		m_high(high),
		m_low(low),
		m_minute(minute)
	{}
	unsigned int m_volume;
	unsigned int m_moneyDollars;
	unsigned int m_moneyFraction;
	unsigned int m_first;
	unsigned int m_last;
	unsigned int m_high;
	unsigned int m_low;
	unsigned short m_minute;
};

/*
class TMsgMsEquityAddPrintLong : public Message
{
public:
	TMsgMsEquityAddPrintLong(unsigned int dollars, unsigned int dollarFraction, unsigned int quantity, unsigned char source):
		Message(TM_EQUITY_ADD_PRINT_LONG, sizeof(TMsgMsEquityAddPrintLong)),
		m_dollars(dollars),
		m_dollarFraction(dollarFraction),
		m_quantity(quantity),
		m_source(source)
	{
	}
	unsigned int m_dollars;
	unsigned int m_dollarFraction;
	unsigned int m_quantity;
	unsigned char m_source;
};

class TMsgMsEquityAddPrintShort : public Message
{
public:
	TMsgMsEquityAddPrintShort(unsigned int price, unsigned short quantity, unsigned char source):
		Message(TM_EQUITY_ADD_PRINT_SHORT, sizeof(TMsgMsEquityAddPrintShort)),
		m_price(price),
		m_quantity(quantity),
		m_source(source)
	{
	}
	unsigned int m_price;//18 bytes for dollars, 14 bytes for 4 digits
	unsigned short m_quantity;
	unsigned char m_source;
};
*/
class TMsgImbalance : public TMessageSymbol
{
public:
	TMsgImbalance(const char* symbol,
		unsigned int farPriceDollar,
		unsigned int farPriceFraction,
		unsigned int nearPriceDollar,
		unsigned int nearPriceFraction,
		unsigned int currentReferencePriceDollar,
		unsigned int currentReferencePriceFraction,
		unsigned int pairedShares,
		unsigned int imbalanceShares,
		unsigned int marketImbalanceShares,
		unsigned int time,
		unsigned int auctionTime,
		char imbalanceDirection,
		char crossType,
		char priceVariationIndicator,
		unsigned char bookId,
		bool regulatory):
	
		TMessageSymbol(symbol, M_STOCK_IMBALANCE_INDICATOR, sizeof(TMsgImbalance)),
		m_farPriceDollar(farPriceDollar),
		m_farPriceFraction(farPriceFraction),
		m_nearPriceDollar(nearPriceDollar),
		m_nearPriceFraction(nearPriceFraction),
		m_currentReferencePriceDollar(currentReferencePriceDollar),
		m_currentReferencePriceFraction(currentReferencePriceFraction),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0)
	{}
	unsigned int m_farPriceDollar;
	unsigned int m_farPriceFraction;
	unsigned int m_nearPriceDollar;
	unsigned int m_nearPriceFraction;
	unsigned int m_currentReferencePriceDollar;
	unsigned int m_currentReferencePriceFraction;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;
};

class TMsgBookNewQuote : public TMessageSymbol
{
public:
	TMsgBookNewQuote(const char* symbol = "",
		unsigned char side = Buy,
		unsigned __int64 referenceNumber = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned int size = 0,
		unsigned int mmid = 0,
		unsigned int millisecond = 0,
		unsigned char bookID = 0,//	: 8;
		unsigned char quoteCondition = 0,//	: 8;
		unsigned short flags = 0)://		: 24;
		TMessageSymbol(symbol, M_BOOK_NEW_QUOTE, sizeof(TMsgBookNewQuote)),
		m_side(side),
		m_quote(referenceNumber, priceDollars, priceFraction, size, mmid, millisecond, bookID, quoteCondition, flags)
	{}
	unsigned char m_side;
	MsgQuote m_quote;
};

class TMsgBookModifyQuote : public TMessageSymbol
{
public:
	TMsgBookModifyQuote(const char* symbol = "",
		unsigned char side = Buy,
		unsigned __int64 referenceNumber = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned int size = 0,
		unsigned int mmid = 0,
		unsigned int millisecond = 0,
		unsigned char bookID = 0,//	: 8;
		unsigned char quoteCondition = 0,//	: 8;
		unsigned short flags = 0)://		: 24;
		TMessageSymbol(symbol, M_BOOK_MODIFY_QUOTE, sizeof(TMsgBookModifyQuote)),
		m_side(side),
		m_quote(referenceNumber, priceDollars, priceFraction, size, mmid, millisecond, bookID, quoteCondition, flags)
	{}
	unsigned char m_side;
	MsgQuote m_quote;
};

class TMsgBookDeleteQuote : public TMessageTimeSymbol
{
public:
	TMsgBookDeleteQuote(const char* symbol = "",
		unsigned int millisecond = 0,
		unsigned __int64 referenceNumber = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_DELETE_QUOTE, sizeof(TMsgBookDeleteQuote)),
		m_referenceNumber(referenceNumber),
		m_side(side),
		m_bookID(bookID)
		{}
	unsigned __int64	m_referenceNumber;
	unsigned char		m_side;
	unsigned char		m_bookID;
};

class TMsgBookOrderExecuted : public TMessageTimeSymbol
{
public:
	TMsgBookOrderExecuted(const char* symbol = "",
		unsigned int millisecond = 0,
		unsigned __int64 referenceNumber = 0,
		unsigned __int64 matchNumber = 0,
		unsigned int shares = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_ORDER_EXECUTED, sizeof(TMsgBookOrderExecuted)),
		m_referenceNumber(referenceNumber),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_side(side),
		m_bookID(bookID)
	{}
	unsigned __int64 m_referenceNumber;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TMsgBookOrderExecutedWithPrice : public TMessageTimeSymbol
{
public:
	TMsgBookOrderExecutedWithPrice(const char* symbol = "",
		unsigned int millisecond = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned __int64 referenceNumber = 0,
		unsigned __int64 matchNumber = 0,
		unsigned int shares = 0,
		unsigned int remainingShares = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0,
		bool bPrintable = false):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_ORDER_EXECUTED_WITH_PRICE, sizeof(TMsgBookOrderExecutedWithPrice)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_referenceNumber(referenceNumber),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_remainingShares(remainingShares),
		m_side(side),
		m_bookID(bookID),
		m_bPrintable(bPrintable)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned __int64 m_referenceNumber;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned int m_remainingShares;
	unsigned char m_side;
	unsigned char m_bookID;
	bool m_bPrintable;
};

class TMsgBookTrade : public TMessageTimeSymbol
{
public:
	TMsgBookTrade(const char* symbol = "",
		unsigned int millisecond = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned __int64 matchNumber = 0,
		unsigned int shares = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_TRADE, sizeof(TMsgBookTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_side(side),
		m_bookID(bookID)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
//	unsigned __int64 m_referenceNumber;//??
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TMsgBookCrossTrade : public TMessageTimeSymbol
{
public:
	TMsgBookCrossTrade(const char* symbol = "",
		unsigned int millisecond = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned __int64 matchNumber = 0,
		unsigned int shares = 0,
		char crossType = 0,
		unsigned char bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_CROSS_TRADE, sizeof(TMsgBookCrossTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_crossType(crossType),
		m_bookID(bookID)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	char m_crossType;
	unsigned char m_bookID;
};

class TMsgBookOrderCanceled : public TMessageTimeSymbol
{
public:
	TMsgBookOrderCanceled(const char* symbol = "",
		unsigned int millisecond = 0,
		unsigned __int64 referenceNumber = 0,
		unsigned int shares = 0,
		unsigned char side = Buy,
		unsigned char bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_ORDER_CANCELED, sizeof(TMsgBookOrderCanceled)),
		m_referenceNumber(referenceNumber),
		m_shares(shares),
		m_side(side),
		m_bookID(bookID)
	{}
	unsigned __int64 m_referenceNumber;
	unsigned int m_shares;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TMsgResetBook: public Message
{
public:
	TMsgResetBook(unsigned char bookId = AllBooks):Message(M_RESET_BOOK, sizeof(TMsgResetBook)),m_bookId(bookId){}
    unsigned char m_bookId;
};

class TMsgResetSymbol: public TMessageSymbol
{
public:
	TMsgResetSymbol(const char* symbol, unsigned char bookId = AllBooks):TMessageSymbol(symbol, M_RESET_SYMBOL, sizeof(TMsgResetSymbol)), m_bookId(bookId){}
	TMsgResetSymbol(const unsigned __int64& symbol, unsigned char bookId = AllBooks):TMessageSymbol(symbol, M_RESET_SYMBOL, sizeof(TMsgResetSymbol)), m_bookId(bookId){}
    unsigned char m_bookId;
};

class TMsgLevel1: public TMessageTimeSymbol
{
public:
	TMsgLevel1(const char* symbol,
		unsigned int time,
		unsigned int bidDollars,
		unsigned int bidFraction,
		unsigned int askDollars,
		unsigned int askFraction,
		unsigned int bidSize,
		unsigned int askSize,
		char primaryListingMarket,
		char bidMarketCenter,
		char askMarketCenter,
		char quoteCondition):
		TMessageTimeSymbol(symbol, time, M_LEVEL1, sizeof(TMsgLevel1)),
		m_bidDollars(bidDollars),
		m_bidFraction(bidFraction),
		m_askDollars(askDollars),
		m_askFraction(askFraction),
		m_bidSize(bidSize),
		m_askSize(askSize),
		m_primaryListingMarket(primaryListingMarket),
		m_bidMarketCenter(bidMarketCenter),
		m_askMarketCenter(askMarketCenter),
		m_quoteCondition(quoteCondition)
	{}
	unsigned int m_bidDollars;
	unsigned int m_bidFraction;
	unsigned int m_askDollars;
	unsigned int m_askFraction;
	unsigned int m_bidSize;
	unsigned int m_askSize;
	char m_primaryListingMarket;
	char m_bidMarketCenter;
	char m_askMarketCenter;
	char m_quoteCondition;
};

class TMsgTrade: public TMessageTimeSymbol
{
public:
	TMsgTrade(const char* symbol,
		unsigned int time,
		unsigned __int64 referenceNumber,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned int size,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		char marketCenterID,
		char primaryListingMarket,
		unsigned char flags):
		TMessageTimeSymbol(symbol, time, M_TRADE_REPORT, sizeof(TMsgTrade)),
		m_referenceNumber(referenceNumber),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_saleConditions;
		*cursor = saleCondition1;
		*++cursor = saleCondition2;
		*++cursor = saleCondition3;
		*++cursor = saleCondition4;
	}
	unsigned __int64 m_referenceNumber;
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	char m_saleConditions[4];
	char m_marketCenterID;
	char m_primaryListingMarket;
	unsigned char m_flags;
};

class TMsgMsTradeShort: public TMessageSymbol
{
public:
	TMsgMsTradeShort(const char* symbol,
		unsigned int price,
		unsigned short size,
		char saleCondition,
		char marketCenter):
		TMessageSymbol(symbol, M_MS_TRADE_REPORT_SHORT, sizeof(TMsgMsTradeShort)),
		m_price(price),
		m_size(size),
		m_saleCondition(saleCondition),
		m_marketCenterID(marketCenter)
	{}
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_size;
	char m_saleCondition;
	char m_marketCenterID;
};

class TMsgMsTradeLong: public TMessageSymbol
{
public:
	TMsgMsTradeLong(const char* symbol,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned int size,
		unsigned int saleCondition,
		char marketCenter):
		TMessageSymbol(symbol, M_MS_TRADE_REPORT_LONG, sizeof(TMsgMsTradeLong)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_marketCenterID(marketCenter)
	{
		*(unsigned int*)m_saleCondition = saleCondition;
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	char m_saleCondition[4];
	char m_marketCenterID;
};

class TMsgMsTradeLongInternal: public Message
{
public:
	TMsgMsTradeLongInternal(unsigned int bid, unsigned int ask,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned int size,
		unsigned int saleCondition,
		char marketCenter,
		unsigned char printFlags,
		bool priceApplicableToChart,
		unsigned char roundLot,
		unsigned char level1):
		Message(TM_MS_TRADE_LONG_INTERNAL, sizeof(TMsgMsTradeLongInternal)),
		m_l1Bid(bid),
		m_l1Ask(ask),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_marketCenterID(marketCenter),
		m_printFlags(printFlags),
		m_priceApplicableToChart(priceApplicableToChart),
		m_roundLot(roundLot),
		m_level1(level1)
	{
		*(unsigned int*)m_saleCondition = saleCondition;
	}
	unsigned int m_l1Bid;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned int m_l1Ask;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	char m_saleCondition[4];
	char m_marketCenterID;
	unsigned char m_printFlags;
	bool m_priceApplicableToChart;
	unsigned char m_roundLot;
	unsigned char m_level1;
};

class TMsgMsTradeShortInternal: public Message
{
public:
	TMsgMsTradeShortInternal(unsigned int bid, unsigned int ask,
		unsigned int price,
		unsigned short size,
		char saleCondition,
		char marketCenter,
		unsigned char printFlags,
		bool priceApplicableToChart,
		unsigned char roundLot,
		unsigned char level1):
		Message(TM_MS_TRADE_SHORT_INTERNAL, sizeof(TMsgMsTradeShortInternal)),
		m_l1Bid(bid),
		m_l1Ask(ask),
		m_price(price),
		m_size(size),
		m_saleCondition(saleCondition),
		m_marketCenterID(marketCenter),
		m_printFlags(printFlags),
		m_priceApplicableToChart(priceApplicableToChart),
		m_roundLot(roundLot),
		m_level1(level1)
	{}
	unsigned int m_l1Bid;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned int m_l1Ask;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_size;
	char m_saleCondition;
	char m_marketCenterID;
	unsigned char m_printFlags;
	bool m_priceApplicableToChart;
	unsigned char m_roundLot;
	unsigned char m_level1;
};

class HistoricalTrade
{
public:
	HistoricalTrade(unsigned int priceDollar,
		unsigned int priceFraction,
		unsigned int time,
		unsigned int size,
		unsigned int saleCondition,
		char marketCenter,
		unsigned char printFlags):
//		Message(TM_MS_TRADE_SHORT_INTERNAL, sizeof(TMsgMsTradeShortInternal)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_time(time),
		m_size(size),
		m_marketCenterID(marketCenter),
		m_printFlags(printFlags)
	{
		*(unsigned int*)m_saleCondition = saleCondition;
	}
	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_time;
	unsigned int m_size;
	char m_saleCondition[4];
	char m_marketCenterID;
	unsigned char m_printFlags;
};

class TMsgNewMinute: public Message
{
public:
	unsigned short m_minute;
protected:
	TMsgNewMinute(unsigned short minute, unsigned short type, unsigned short size): Message(type, size), m_minute(minute){}
};

class TMsgEquityNewMinute: public TMsgNewMinute
{
public:
	TMsgEquityNewMinute(unsigned short minute):TMsgNewMinute(minute, TM_EQUITY_NEW_MINUTE, sizeof(TMsgEquityNewMinute)){}
};

class TMsgEquityNewTimeFrame: public TMsgNewMinute
{
public:
	TMsgEquityNewTimeFrame(unsigned short timeFrame):TMsgNewMinute(timeFrame, TM_EQUITY_NEW_TIME_FRAME, sizeof(TMsgEquityNewTimeFrame)){}
//	unsigned int m_timeFrame;
};

class TMsgIndexNewMinute: public TMsgNewMinute
{
public:
	TMsgIndexNewMinute(unsigned short minute):TMsgNewMinute(minute, TM_INDEX_NEW_MINUTE, sizeof(TMsgIndexNewMinute)){}
};

class TMsgMsLevel1Short: public TMessageSymbol
{
public:
	TMsgMsLevel1Short(const char* symbol,
		unsigned int price,
		unsigned char side,
		char quoteCondition):
		TMessageSymbol(symbol, M_MS_LEVEL1_SHORT, sizeof(TMsgMsLevel1Short)),
		m_price(price),
		m_side(side),
		m_quoteCondition(quoteCondition)
	{}
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned char m_side;//'B' and 'S'
	char m_quoteCondition;
};

class TMsgMsLevel1Long: public TMessageSymbol
{
public:
	TMsgMsLevel1Long(const char* symbol,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned char side,
		char quoteCondition):
		TMessageSymbol(symbol, M_MS_LEVEL1_LONG, sizeof(TMsgMsLevel1Long)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_side(side),
		m_quoteCondition(quoteCondition)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned char m_side;//'B' and 'S'
	char m_quoteCondition;
};

class TMsgMsImbalanceLong : public TMessageSymbol
{
public:
	TMsgMsImbalanceLong(const char* symbol,
		unsigned int farPriceDollar,
		unsigned int farPriceFraction,
		unsigned int nearPriceDollar,
		unsigned int nearPriceFraction,
		unsigned int currentReferencePriceDollar,
		unsigned int currentReferencePriceFraction,
		unsigned int pairedShares,
		unsigned int imbalanceShares,
//		unsigned int marketImbalanceShares,
		unsigned int time,
		unsigned int auctionTime,
		char imbalanceDirection,
		char crossType,
		char priceVariationIndicator,
		unsigned char bookId,
		bool regulatory):
	
		TMessageSymbol(symbol, M_MS_IMBALANCE_LONG, sizeof(TMsgMsImbalanceLong)),
		m_farPriceDollar(farPriceDollar),
		m_farPriceFraction(farPriceFraction),
		m_nearPriceDollar(nearPriceDollar),
		m_nearPriceFraction(nearPriceFraction),
		m_currentReferencePriceDollar(currentReferencePriceDollar),
		m_currentReferencePriceFraction(currentReferencePriceFraction),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
//		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0)
	{}
	unsigned int m_farPriceDollar;
	unsigned int m_farPriceFraction;
	unsigned int m_nearPriceDollar;
	unsigned int m_nearPriceFraction;
	unsigned int m_currentReferencePriceDollar;
	unsigned int m_currentReferencePriceFraction;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
//	unsigned int m_marketImbalanceShares;??????
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;//for ARCA : 1 if market imbalance, 0 if non market imbalance
};

class TMsgMsImbalanceShort : public TMessageSymbol
{
public:
	TMsgMsImbalanceShort(const char* symbol,
		unsigned int farPrice,//18 bits for dollar and 14 bits for 4 digits of fraction
		unsigned int nearPrice,//18 bits for dollar and 14 bits for 4 digits of fraction
		unsigned int currentReferencePrice,//18 bits for dollar and 14 bits for 4 digits of fraction
		unsigned int pairedShares,
		unsigned int imbalanceShares,
//		unsigned int marketImbalanceShares,
		unsigned int time,
		unsigned int auctionTime,
		char imbalanceDirection,
		char crossType,
		char priceVariationIndicator,
		unsigned char bookId,
		bool regulatory):
	
		TMessageSymbol(symbol, M_MS_IMBALANCE_SHORT, sizeof(TMsgMsImbalanceShort)),
		m_farPrice(farPrice),
		m_nearPrice(nearPrice),
		m_currentReferencePrice(currentReferencePrice),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
//		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0)//for ARCA : 1 if market imbalance, 0 if non market imbalance
	{}
	unsigned int m_farPrice;
	unsigned int m_nearPrice;
	unsigned int m_currentReferencePrice;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
//	unsigned int m_marketImbalanceShares;?????
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;//for ARCA : 1 if market imbalance, 0 if non market imbalance
};

class TMsgTradeErrorBase: public TMessageTimeSymbol
{
public:
	unsigned __int64 m_originalReferenceNumber;
	unsigned int m_originalPriceDollars;
	unsigned int m_originalPriceFraction;
	unsigned int m_originalSize;
	char m_originalSaleConditions[4];

	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned __int64 m_volume;

	char m_marketCenterID;
	char m_primaryListingMarket;
	char m_flags;
protected:
	TMsgTradeErrorBase(const char* symbol,
		unsigned int time,
		unsigned __int64 originalReferenceNumber,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int originalSize,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags,

		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_originalReferenceNumber(originalReferenceNumber),
		m_originalPriceDollars(originalPriceDollars),
		m_originalPriceFraction(originalPriceFraction),
		m_originalSize(originalSize),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_volume(volume),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_originalSaleConditions;
		*cursor = originalSaleCondition1;
		*++cursor = originalSaleCondition2;
		*++cursor = originalSaleCondition3;
		*++cursor = originalSaleCondition4;
	}
};

class TMsgTradeError: public TMsgTradeErrorBase
{
public:
	TMsgTradeError(const char* symbol,
		unsigned int time,
		unsigned __int64 originalReferenceNumber,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int originalSize,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags):
		TMsgTradeErrorBase(symbol,
			time,
			originalReferenceNumber,
			originalPriceDollars,
			originalPriceFraction,
			originalSize,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			M_TRADE_CANCEL_ERROR,
			sizeof(TMsgTradeError))
	{}
};

class TMsgMsTradeError: public TMsgTradeErrorBase
{
public:
	TMsgMsTradeError(const char* symbol,
		unsigned int time,
		unsigned __int64 originalReferenceNumber,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int originalSize,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags):
		TMsgTradeErrorBase(symbol,
			time,
			originalReferenceNumber,
			originalPriceDollars,
			originalPriceFraction,
			originalSize,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			M_MS_TRADE_CANCEL_ERROR,
			sizeof(TMsgMsTradeError))
	{}
};

class TMsgTradeCorrectionBase: public TMessageTimeSymbol
{
public:
	unsigned int m_originalPriceDollars;
	unsigned int m_originalPriceFraction;
	unsigned int m_correctedPriceDollars;
	unsigned int m_correctedPriceFraction;
	unsigned int m_originalSize;
	unsigned int m_correctedSize;
	unsigned __int64 m_originalReferenceNumber;
	unsigned __int64 m_correctedReferenceNumber;
	char m_originalSaleConditions[4];
	char m_correctedSaleConditions[4];
	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned __int64 m_volume;
	char m_marketCenterID;
	char m_primaryListingMarket;
	char m_flags;
protected:
//	TMsgTradeCorrectionBase(const char* symbol, unsigned int time, unsigned short type, unsigned short length):TMessageTimeSymbol(symbol, time, type, length){}
	TMsgTradeCorrectionBase(const char* symbol,
		unsigned int time,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int correctedPriceDollars,
		unsigned int correctedPriceFraction,
		unsigned int originalSize,
		unsigned int correctedSize,
		unsigned __int64 originalReferenceNumber,
		unsigned __int64 correctedReferenceNumber,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,
		char correctedSaleCondition1,
		char correctedSaleCondition2,
		char correctedSaleCondition3,
		char correctedSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags,

		unsigned short type,
		unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_originalPriceDollars(originalPriceDollars),
		m_originalPriceFraction(originalPriceFraction),
		m_correctedPriceDollars(correctedPriceDollars),
		m_correctedPriceFraction(correctedPriceFraction),
		m_originalSize(originalSize),
		m_correctedSize(correctedSize),
		m_originalReferenceNumber(originalReferenceNumber),
		m_correctedReferenceNumber(correctedReferenceNumber),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_volume(volume),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_originalSaleConditions;
		*cursor = originalSaleCondition1;
		*++cursor = originalSaleCondition2;
		*++cursor = originalSaleCondition3;
		*++cursor = originalSaleCondition4;

		cursor = m_correctedSaleConditions;
		*cursor = correctedSaleCondition1;
		*++cursor = correctedSaleCondition2;
		*++cursor = correctedSaleCondition3;
		*++cursor = correctedSaleCondition4;
	}
};

class TMsgTradeCorrection: public TMsgTradeCorrectionBase
{
public:
	TMsgTradeCorrection(const char* symbol,
		unsigned int time,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int correctedPriceDollars,
		unsigned int correctedPriceFraction,
		unsigned int originalSize,
		unsigned int correctedSize,
		unsigned __int64 originalReferenceNumber,
		unsigned __int64 correctedReferenceNumber,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,
		char correctedSaleCondition1,
		char correctedSaleCondition2,
		char correctedSaleCondition3,
		char correctedSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags):
		TMsgTradeCorrectionBase(symbol,
			time,
			originalPriceDollars,
			originalPriceFraction,
			correctedPriceDollars,
			correctedPriceFraction,
			originalSize,
			correctedSize,
			originalReferenceNumber,
			correctedReferenceNumber,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,
			correctedSaleCondition1,
			correctedSaleCondition2,
			correctedSaleCondition3,
			correctedSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			M_TRADE_CORRECTION,
			sizeof(TMsgTradeCorrection))
	{}
};

class TMsgMsTradeCorrection: public TMsgTradeCorrectionBase
{
public:
	TMsgMsTradeCorrection(const char* symbol,
		unsigned int time,
		unsigned int originalPriceDollars,
		unsigned int originalPriceFraction,
		unsigned int correctedPriceDollars,
		unsigned int correctedPriceFraction,
		unsigned int originalSize,
		unsigned int correctedSize,
		unsigned __int64 originalReferenceNumber,
		unsigned __int64 correctedReferenceNumber,
		char originalSaleCondition1,
		char originalSaleCondition2,
		char originalSaleCondition3,
		char originalSaleCondition4,
		char correctedSaleCondition1,
		char correctedSaleCondition2,
		char correctedSaleCondition3,
		char correctedSaleCondition4,

		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned __int64 volume,

		char marketCenterID,
		char primaryListingMarket,
		char flags):
		TMsgTradeCorrectionBase(symbol,
			time,
			originalPriceDollars,
			originalPriceFraction,
			correctedPriceDollars,
			correctedPriceFraction,
			originalSize,
			correctedSize,
			originalReferenceNumber,
			correctedReferenceNumber,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,
			correctedSaleCondition1,
			correctedSaleCondition2,
			correctedSaleCondition3,
			correctedSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			M_MS_TRADE_CORRECTION,
			sizeof(TMsgMsTradeCorrection))
	{}
};

class TMsgMarketSorterLoaded : public Message
{
public:
	TMsgMarketSorterLoaded():Message(TM_MARKET_SORTER_LOADED, sizeof(TMsgMarketSorterLoaded)){}//, m_loaded(loaded){}
//	bool m_loaded;
};

class TMsgMarketSorterChunkLoaded : public Message
{
public:
	TMsgMarketSorterChunkLoaded(unsigned int requestId):Message(TM_MARKET_SORTER_CHUNK_LOADED, sizeof(TMsgMarketSorterChunkLoaded)), m_requestId(requestId){}
	unsigned int m_requestId;
};

class TMsgMarketSorterIndexesLoaded : public Message
{
public:
	TMsgMarketSorterIndexesLoaded():Message(TM_MARKET_SORTER_INDEXES_LOADED, sizeof(TMsgMarketSorterIndexesLoaded)){}//, m_loaded(loaded){}
//	bool m_loaded;
};

class TMsgMarketSorterIndexChunkLoaded : public Message
{
public:
	TMsgMarketSorterIndexChunkLoaded(unsigned int requestId):Message(TM_MARKET_SORTER_INDEX_CHUNK_LOADED, sizeof(TMsgMarketSorterIndexChunkLoaded)), m_requestId(requestId){}
	unsigned int m_requestId;
};

class TMsgMarketSorterStockChartsLoaded : public Message
{
public:
	TMsgMarketSorterStockChartsLoaded():Message(TM_MARKET_SORTER_STOCK_CHARTS_LOADED, sizeof(TMsgMarketSorterStockChartsLoaded)){}
};

class TMsgMarketSorterIndexChartsLoaded : public Message
{
public:
	TMsgMarketSorterIndexChartsLoaded():Message(TM_MARKET_SORTER_INDEX_CHARTS_LOADED, sizeof(TMsgMarketSorterIndexChartsLoaded)){}
};

///////////////////
//HistoricalPrint
class PrintData
{
public:
	PrintData(
		unsigned __int64 referenceNumber,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned int time,
		unsigned int size,
		char saleCondition1,
		char saleCondition2,
		char saleCondition3,
		char saleCondition4,
		char marketCenterId,
		char flags,
		char primaryListingMarket):
		m_referenceNumber(referenceNumber),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_time(time),
		m_size(size),
		m_saleCondition1(saleCondition1),
		m_saleCondition2(saleCondition2),
		m_saleCondition3(saleCondition3),
		m_saleCondition4(saleCondition4),
		m_marketCenterID(marketCenterId),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
	}

	unsigned __int64 m_referenceNumber;
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_time;
	unsigned int m_size;
	char m_saleCondition1;
	char m_saleCondition2;
	char m_saleCondition3;
	char m_saleCondition4;
	char m_marketCenterID;
	char m_flags;
	char m_primaryListingMarket;
};

class HistoricalTick
{
public:
	HistoricalTick(unsigned int volume = 0,
		unsigned int open = 0,
		unsigned int close = 0,
		unsigned int high = 0,
		unsigned int low = 0,
		unsigned int adjustedClose = 0,
		unsigned int date = 0):

		m_volume(volume),
		m_open(open),
		m_close(close),
		m_high(high),
		m_low(low),
		m_adjustedClose(adjustedClose),
		m_date(date)
	{
	}

	unsigned int m_volume;
	unsigned int m_open;
	unsigned int m_close;
	unsigned int m_high;
	unsigned int m_low;
	unsigned int m_adjustedClose;
	unsigned int m_date;
};


class HistoricalIntraDayTick
{
public:
	HistoricalIntraDayTick(unsigned int moneyDollar,
		unsigned int moneyFraction,
		unsigned int volume = 0,
		unsigned int first = 0,
		unsigned int last = 0,
		unsigned int high = 0,
		unsigned int low = 0,
		unsigned int minute = 0):
		
		m_moneyDollar(moneyDollar),
		m_moneyFraction(moneyFraction),
		m_volume(volume),
		m_first(first),
		m_last(last),
		m_high(high),
		m_low(low),
		m_minute(minute)
	{}

	unsigned int m_moneyDollar;
	unsigned int m_moneyFraction;
	unsigned int m_volume;
	unsigned int m_first;
	unsigned int m_last;
	unsigned int m_high;
	unsigned int m_low;
	unsigned short m_minute;
};
//////////////////////
enum HistoricalPrintResponseFlags : unsigned char
{
	More	= 0x01,
	Failed	= 0x80,
};

enum HistoricalPrintRequestFlags : unsigned char
{
	ExcludeReferencedPrint = 0x01,
};

class TMsgReqPrints : public TMessageSymbol
{
public:
	TMsgReqPrints(const char* symbol, unsigned int requestId, unsigned short minute, unsigned __int64 referenceNumber, unsigned char flags):
		TMessageSymbol(symbol, M_REQ_PRINTS, sizeof(TMsgReqPrints)),
		m_requestId(requestId),
		m_minute(minute),
		m_referenceNumber(referenceNumber),
		m_flags(flags)
	{}
	unsigned int m_requestId;
	unsigned __int64 m_referenceNumber;
	unsigned short m_minute;
	unsigned char m_flags;
};

class TMsgPrints : public TMessageSymbol
{
public:
	TMsgPrints(const char* symbol, unsigned long requestId, unsigned __int64 nextReferenceNumber, unsigned short minute, unsigned char tickSize, unsigned short ticks, unsigned char flags):
		TMessageSymbol(symbol, M_RESP_PRINTS, sizeof(TMsgPrints) + (unsigned int)tickSize * ticks),
		m_requestId(requestId),
		m_nextReferenceNumber(nextReferenceNumber),
		m_minute(minute),
		m_tickSize(tickSize),
		m_flags(flags)
	{}

	unsigned int m_requestId;
	unsigned __int64 m_nextReferenceNumber;
	unsigned short m_minute;
	unsigned char m_tickSize;
	unsigned char m_flags;
};

enum ChartHistoryFrequency : unsigned char
{
	CHF_INVALID = '\0',
	CHF_MONTH = 'm',
	CHF_WEEK = 'w',
	CHF_DAY = 'd',
	CHF_HOUR = '5',
	CHF_30MIN = '4',
	CHF_15MIN = '3',
	CHF_5MIN = '2',
	CHF_1MIN = '1',
};

class TMsgReqCandleData : public TMessageSymbol
{
public:
	unsigned int m_requestId;
	unsigned int m_startDate;
	unsigned int m_endDate;
	unsigned char m_frequency;
protected:
	TMsgReqCandleData(const char* symbol, unsigned short type, unsigned short length, unsigned int requestId, unsigned int startDate, unsigned int endDate, unsigned char frequency):
		TMessageSymbol(symbol, type, length),
		m_requestId(requestId),
		m_startDate(startDate),
		m_endDate(endDate),
		m_frequency(frequency)
	{}
};

class TMsgReqHistoricalData : public TMsgReqCandleData
{
public:
	TMsgReqHistoricalData(const char* symbol, unsigned int requestId, unsigned int startDate, unsigned int endDate, unsigned char frequency):// 'd' - daily, 'w' - weekly, 'm' - monthly
		TMsgReqCandleData(symbol, M_REQ_CANDLE_HISTORICAL_DATA, sizeof(TMsgReqHistoricalData), requestId, startDate, endDate, frequency)
	{}
};

class TMsgCandleRequestId : public TMessageSymbol
{
public:
	unsigned int m_requestId;
protected:
	TMsgCandleRequestId(const char* symbol, unsigned int requestId, unsigned short type, unsigned short length):
		TMessageSymbol(symbol, type, length),
		m_requestId(requestId)
	{}
};

class TMsgCandleHistoricalData : public TMsgCandleRequestId
{
public:
	TMsgCandleHistoricalData(const char* symbol, unsigned int requestId, unsigned char tickSize, unsigned short ticks, unsigned char primaryExchange, unsigned char flags):
		TMsgCandleRequestId(symbol, requestId, M_RESP_CANDLE_HISTORICAL_DATA, sizeof(TMsgCandleHistoricalData) + (unsigned int)tickSize * ticks),
//		m_requestId(requestId),
		m_tickSize(tickSize),
		m_flags(flags),
		m_primaryExchange(primaryExchange)
	{}

//	unsigned int m_requestId;
	unsigned char m_tickSize;
	unsigned char m_flags;
	unsigned char m_primaryExchange;
};

class TMsgReqIntradayData : public TMsgReqCandleData
{
public:
	TMsgReqIntradayData(const char* symbol, unsigned int requestId, unsigned int startDate, unsigned int endDate, unsigned char frequency)://'1' - 1 minute, '2' - 5 minutes, '3' - 15 minutes, '4' - 30 minutes, '5' - 1 hour
		TMsgReqCandleData(symbol, M_REQ_CANDLE_INTRADAY_DATA, sizeof(TMsgReqIntradayData), requestId, startDate, endDate, frequency)
	{}
};

class TMsgCandleIntradayData : public TMsgCandleRequestId
{
public:
	TMsgCandleIntradayData(const char* symbol, unsigned int requestId, unsigned int date, unsigned char tickSize, unsigned short ticks, unsigned char flags):
		TMsgCandleRequestId(symbol, requestId, M_RESP_CANDLE_INTRADAY_DATA, sizeof(TMsgCandleIntradayData) + (unsigned int)tickSize * ticks),
//		m_requestId(requestId),
		m_date(date),
		m_tickSize(tickSize),
		m_flags(flags)
//		m_primaryExchange(primaryExchange)
	{}

//	unsigned int m_requestId;
	unsigned int m_date;
	unsigned char m_tickSize;
	unsigned char m_flags;
};

#ifndef TAKION_NO_OPTIONS

class TMsgUnderlier : public Message
{
public:
	Underlier* m_underlier;
protected:
	TMsgUnderlier(Underlier* underlier, unsigned short type, unsigned short length):Message(type, length), m_underlier(underlier){}
};

class TMsgUnderlierDelete : public TMsgUnderlier
{
public:
	TMsgUnderlierDelete(Underlier* underlier):TMsgUnderlier(underlier, TM_UNDERLIER_DELETE, sizeof(TMsgUnderlierDelete)){}
};

class TMsgUnderlierNewDay : public TMessageSymbol
{
public:
	TMsgUnderlierNewDay(const char* symbol):TMessageSymbol(symbol, TM_UNDERLIER_NEW_DAY, sizeof(TMsgUnderlierNewDay)){}
	TMsgUnderlierNewDay(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_NEW_DAY, sizeof(TMsgUnderlierNewDay)){}
};

class OptionBlock
{
public:
	OptionBlock(const unsigned __int64& optionBlock = 0):
		m_optionBlock(optionBlock)
	{}

	OptionBlock(unsigned int strikePrice,
		unsigned char reserved,
		unsigned char expirationDay,
		unsigned char expirationMonth,
		unsigned char expirationYear):
		m_strikePrice(strikePrice),
		m_reserved(reserved),
		m_expirationDay(expirationDay),
		m_expirationMonth(expirationMonth),
		m_expirationYear(expirationYear)
	{
	}

	OptionBlock(const OptionBlock& other):m_optionBlock(other.m_optionBlock)
	{
	}

	OptionBlock& operator=(const OptionBlock& other)
	{
		m_optionBlock = other.m_optionBlock;
		return *this;
	}

	bool IsEmpty() const{return !m_optionBlock;}
	bool IsAny() const{return 0xffffffffffffffff == m_optionBlock;}
	void Reset(){m_optionBlock = 0;}
	void SetAny(){m_optionBlock = 0xffffffffffffffff;}
	unsigned __int64 GetExpirationBlock() const{return m_optionBlock & 0xffffff0000000000;}
	unsigned __int64 GetStrikePriceBlock() const{return m_optionBlock & 0x000000ffffffffff;}
//	bool IsCall() const{return m_expirationMonth >= 'A' && m_expirationMonth <= 'L';}
	bool IsCall() const{return m_expirationMonth < 'M';}
	bool IsPut() const{return m_expirationMonth > 'L';}

	operator unsigned __int64() const{return m_optionBlock;}
	const unsigned __int64& GetOptionBlock() const{return m_optionBlock;}
	void SetOptionBlock(const unsigned __int64& optionBlock){m_optionBlock = optionBlock;}

	bool operator==(const OptionBlock& other) const{return m_optionBlock == other.m_optionBlock;}
	bool operator!=(const OptionBlock& other) const{return m_optionBlock != other.m_optionBlock;}
	bool operator<(const OptionBlock& other) const{return m_optionBlock < other.m_optionBlock;}
	bool operator<=(const OptionBlock& other) const{return m_optionBlock <= other.m_optionBlock;}
	bool operator>(const OptionBlock& other) const{return m_optionBlock > other.m_optionBlock;}
	bool operator>=(const OptionBlock& other) const{return m_optionBlock >= other.m_optionBlock;}

	void SetStrikePrice(unsigned int price){m_strikePrice = price;}
	void SetReserved(unsigned char reserved){m_reserved = reserved;}
	void SetExpirationDay(unsigned char expirationDay){m_expirationDay = expirationDay;}
	void SetExpirationMonth(unsigned char expirationMonth){m_expirationMonth = expirationMonth;}
	void SetExpirationYear(unsigned char expirationYear){m_expirationYear = expirationYear;}

	const unsigned int& GetStrikePrice() const{return m_strikePrice;}
	const unsigned char& GetReserved() const{return m_reserved;}
	const unsigned char& GetExpirationDay() const{return m_expirationDay;}
	const unsigned char& GetExpirationMonthCode() const{return m_expirationMonth;}
	const unsigned char& GetExpirationYear() const{return m_expirationYear;}
	unsigned char GetExpirationMonth() const{return m_expirationMonth < 'M' ? m_expirationMonth - ('A' - 1) : m_expirationMonth - 'L';}
	static unsigned int GetNormalizedStrikePriceStatic(const unsigned int& strikePrice)
	{
		unsigned int dollars = strikePrice / 1000;
		return (dollars << 14) | (strikePrice * 10 - 10000 * dollars);
	}
	unsigned int GetNormalizedStrikePrice() const
	{
		unsigned int dollars = m_strikePrice / 1000;
		return (dollars << 14) | (m_strikePrice * 10 - 10000 * dollars);
	}
private:
	union
	{
		unsigned __int64 m_optionBlock;
		struct
		{
			unsigned int m_strikePrice;
			unsigned char m_reserved;
			unsigned char m_expirationDay;
			unsigned char m_expirationMonth;
			unsigned char m_expirationYear;
		};
	};
};

class TMessageOption : public TMessageTimeSymbol
{
public:
	OptionBlock	m_optionBlock;
protected:
	TMessageOption(const char* symbol, unsigned int time, const OptionBlock& optionBlock, unsigned short type, unsigned short length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_optionBlock(optionBlock)
	{}
};

class TMsgOptLevel2 : public TMessageOption
{
public:
	TMsgOptLevel2(const char* symbol = "",
		unsigned int time = 0,
		const OptionBlock& optionBlock = 0,
		unsigned int priceDollars = 0,
		unsigned int priceFraction = 0,
		unsigned int size = 0,
		unsigned char side = Buy,
		unsigned char marketCenterID = 0,
		unsigned char quoteCondition = 0,
		unsigned char flags = 0):
		TMessageOption(symbol, time, optionBlock, M_OPT_LEVEL2, sizeof(TMsgOptLevel2)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_side(side),
		m_marketCenterID(marketCenterID),
		m_quoteCondition(quoteCondition),
		m_flags(flags)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned char m_side;
	unsigned char m_marketCenterID;
	unsigned char m_quoteCondition;
	unsigned char m_flags;
};

class TMsgOptLevel1 : public TMessageOption
{
public:
	TMsgOptLevel1(const char* symbol, unsigned int time, const OptionBlock& optionBlock,
		unsigned int bidPriceDollars,
		unsigned int bidPriceFraction,
		unsigned int askPriceDollars,
		unsigned int askPriceFraction,
		unsigned int bidSize,
		unsigned int askSize,
		unsigned char bidMarketCenter,
		unsigned char askMarketCenter,
		unsigned char quoteCondition,
		unsigned char flags):
		TMessageOption(symbol, time, optionBlock, M_OPT_LEVEL1, sizeof(TMsgOptLevel1)),
		m_bidPriceDollars(bidPriceDollars),
		m_bidPriceFraction(bidPriceFraction),
		m_askPriceDollars(askPriceDollars),
		m_askPriceFraction(askPriceFraction),
		m_bidSize(bidSize),
		m_askSize(askSize),
		m_bidMarketCenter(bidMarketCenter),
		m_askMarketCenter(askMarketCenter),
		m_quoteCondition(quoteCondition),
		m_flags(flags)
	{}
	unsigned int m_bidPriceDollars;
	unsigned int m_bidPriceFraction;
	unsigned int m_askPriceDollars;
	unsigned int m_askPriceFraction;
	unsigned int m_bidSize;
	unsigned int m_askSize;
	unsigned char m_bidMarketCenter;
	unsigned char m_askMarketCenter;
	unsigned char m_quoteCondition;
	unsigned char m_flags;
};

/*Same as for stocks
enum OptTradeReportFlags : unsigned char
{
	NoPriceChanges		= 0,
	LastPriceChanged	= 1,
	LowPriceChanged		= 2,
	HighPriceChanged	= 4,
	TradeThroughExempt	= 8,
};
*/
class TMsgOptTrade : public TMessageOption
{
public:
	TMsgOptTrade(const char* symbol, unsigned int time, const OptionBlock& optionBlock,
		unsigned int priceDollars,
		unsigned int priceFraction,
		unsigned int size,
		unsigned int tradeId,
		unsigned char marketCenterId,
		unsigned char tradeCondition):
		TMessageOption(symbol, time, optionBlock, M_OPT_TRADE_REPORT, sizeof(TMsgOptTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_tradeId(tradeId),
		m_marketCenterId(marketCenterId),
		m_saleCondition(tradeCondition)
	{}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned int m_tradeId;
	unsigned char m_marketCenterId;
	unsigned char m_saleCondition;
};

class TMsgOptOpenInterest : public TMessageOption
{
public:
	TMsgOptOpenInterest(const char* symbol, unsigned int time, const OptionBlock& optionBlock, unsigned int openInterestVolume):
		TMessageOption(symbol, time, optionBlock, M_OPT_OPEN_INTEREST, sizeof(TMsgOptOpenInterest)),
		m_openInterestVolume(openInterestVolume)
	{}
	unsigned int m_openInterestVolume;
};

/*
enum SubscriptionTypes : unsigned char
{
    UpdatesOnly        = 0,
    SubscribeSymbol    = 1,
    UpdatesOnlyAll    = 0xfe,
    RefreshAll        = 0xff,
};
*/
class TMsgReqOptRefreshSymbol : public TMessageSymbol
{
public:
	TMsgReqOptRefreshSymbol(const char* symbol, unsigned char flags, unsigned char blockSize, unsigned int requestId):
		TMessageSymbol(symbol, M_REQ_OPT_REFRESH_SYMBOL, sizeof(TMsgReqOptRefreshSymbol)),
		m_flags(flags),
		m_blockSize(blockSize),
		m_requestId(requestId)
	{}
	TMsgReqOptRefreshSymbol(const unsigned __int64& symbol, unsigned char flags, unsigned char blockSize, unsigned int requestId):
		TMessageSymbol(symbol, M_REQ_OPT_REFRESH_SYMBOL, sizeof(TMsgReqOptRefreshSymbol)),
		m_flags(flags),
		m_blockSize(blockSize),
		m_requestId(requestId)
	{}
	unsigned char m_flags;
	unsigned char m_blockSize;
	unsigned int m_requestId;
};

class TMsgOptionSymbol : public TMessageSymbol
{
public:
	OptionBlock m_optionBlock;
protected:
	TMsgOptionSymbol(const char* symbol, const unsigned __int64& optionBlock, unsigned short type, unsigned short length):
		TMessageSymbol(symbol, type, length),
		m_optionBlock(optionBlock)
	{}
	TMsgOptionSymbol(const unsigned __int64& symbol, const unsigned __int64& optionBlock, unsigned short type, unsigned short length):
		TMessageSymbol(symbol, type, length),
		m_optionBlock(optionBlock)
	{}
	TMsgOptionSymbol(const unsigned __int64& symbol, const OptionBlock& optionBlock, unsigned short type, unsigned short length):
		TMessageSymbol(symbol, type, length),
		m_optionBlock(optionBlock)
	{}
};

class TMsgOptionSymbolRoot : public TMsgOptionSymbol
{
public:
	Symbol m_rootSymbol;
protected:
	TMsgOptionSymbolRoot(const char* symbol, const unsigned __int64& optionBlock, const char* rootSymbol, unsigned short type, unsigned short length):
		TMsgOptionSymbol(symbol, optionBlock, type, length)
	{
		U_CopyAndPad(m_rootSymbol, sizeof(m_rootSymbol), rootSymbol, '\0');
	}
	TMsgOptionSymbolRoot(const unsigned __int64& symbolNum, const unsigned __int64& optionBlock, const unsigned __int64& rootSymbolNum, unsigned short type, unsigned short length):
		TMsgOptionSymbol(symbolNum, optionBlock, type, length)
	{
		*(unsigned __int64*)m_rootSymbol = rootSymbolNum;
	}
	TMsgOptionSymbolRoot(const unsigned __int64& symbolNum, const OptionBlock& optionBlock, const unsigned __int64& rootSymbolNum, unsigned short type, unsigned short length):
		TMsgOptionSymbol(symbolNum, optionBlock, type, length)
	{
		*(unsigned __int64*)m_rootSymbol = rootSymbolNum;
	}
};

class TMsgReqRefreshOption : public TMsgOptionSymbolRoot
{
public:
	TMsgReqRefreshOption(const unsigned __int64& symbolNum, const unsigned __int64& optionBlock, const unsigned __int64& rootSymbolNum, unsigned int requestID = 0):
		TMsgOptionSymbolRoot(symbolNum, optionBlock, rootSymbolNum, M_REQ_REFRESH_OPTION, sizeof(TMsgReqRefreshOption)),
		m_requestID(requestID)
	{
	}
    unsigned int m_requestID;
};

class TMsgRespRefreshOption : public TMessageOption//m_time is m_requestId
{
public:
	TMsgRespRefreshOption(const char* symbol, unsigned int requestId, const OptionBlock& optionBlock, const char* rootSymbol, unsigned short dataSize, unsigned char steps, unsigned char flags):
		TMessageOption(symbol, requestId, optionBlock, M_RESP_REFRESH_OPTION, dataSize),
		m_steps(steps),
		m_flags(flags)
	{
		U_CopyAndPad(m_rootSymbol, sizeof(m_rootSymbol), rootSymbol, '\0');
	}
/*
//	bool IsEndOfRefresh() const{return REFRESH_EndOfRefresh == (REFRESH_EndOfRefresh & m_flags);}
//	bool IsEndOfBlock() const{ return REFRESH_EndOfBlock == (REFRESH_EndOfBlock & m_flags );}
//	bool IsRefreshFailed() const{ return REFRESH_RefreshFailed == (REFRESH_RefreshFailed & m_flags );}
	bool IsEndOfRefresh() const{return (REFRESH_EndOfRefresh & m_flags) != 0;}
	bool IsEndOfBlock() const{ return (REFRESH_EndOfBlock & m_flags) != 0;}
	bool IsRefreshFailed() const{ return (REFRESH_RefreshFailed & m_flags) != 0;}
*/
	Symbol m_rootSymbol;
	unsigned char m_steps;
	unsigned char m_flags;
};

class TMsgReqUnsubscribeOption : public TMsgOptionSymbolRoot
{
public:
	TMsgReqUnsubscribeOption(const unsigned __int64& symbolNum, const unsigned __int64& optionBlock, const unsigned __int64& rootSymbolNum):
		TMsgOptionSymbolRoot(symbolNum, optionBlock, rootSymbolNum, M_REQ_UNSUBSCRIBE_OPTION, sizeof(TMsgReqUnsubscribeOption))
	{}
	TMsgReqUnsubscribeOption(const unsigned __int64& symbolNum, const OptionBlock& optionBlock, const unsigned __int64& rootSymbolNum):
		TMsgOptionSymbolRoot(symbolNum, optionBlock, rootSymbolNum, M_REQ_UNSUBSCRIBE_OPTION, sizeof(TMsgReqUnsubscribeOption))
	{}
};


/*
enum StockRefreshStatus : unsigned char
{
	REFRESH_EndOfBlock		= 0x20,
	REFRESH_EndOfRefresh	= 0x40,
	REFRESH_RefreshFailed	= 0x80,
};
*/
class TMsgRespOptRefreshSymbol : public TMessageTimeSymbol//m_time is m_requestId
{
public:
	TMsgRespOptRefreshSymbol(const char* symbol, unsigned int requestId, unsigned short dataSize, unsigned char steps, unsigned char flags):
		TMessageTimeSymbol(symbol, requestId, M_RESP_OPT_REFRESH_SYMBOL, dataSize),
		m_steps(steps),
		m_flags(flags)
	{}
/*
//	bool IsEndOfRefresh() const{return REFRESH_EndOfRefresh == (REFRESH_EndOfRefresh & m_flags);}
//	bool IsEndOfBlock() const{ return REFRESH_EndOfBlock == (REFRESH_EndOfBlock & m_flags );}
//	bool IsRefreshFailed() const{ return REFRESH_RefreshFailed == (REFRESH_RefreshFailed & m_flags );}
	bool IsEndOfRefresh() const{return (REFRESH_EndOfRefresh & m_flags) != 0;}
	bool IsEndOfBlock() const{ return (REFRESH_EndOfBlock & m_flags) != 0;}
	bool IsRefreshFailed() const{ return (REFRESH_RefreshFailed & m_flags) != 0;}
*/
	unsigned char m_steps;
	unsigned char m_flags;
};

class TMsgReqOptUnsubscribeSymbol : public TMessageSymbol
{
public:
	TMsgReqOptUnsubscribeSymbol(const char* symbol):TMessageSymbol(symbol, M_REQ_OPT_UNSUBSCRIBE_SYMBOL, sizeof(TMsgReqUnsubscribeSymbol)){}
	TMsgReqOptUnsubscribeSymbol(const unsigned __int64& symbol):TMessageSymbol(symbol, M_REQ_OPT_UNSUBSCRIBE_SYMBOL, sizeof(TMsgReqUnsubscribeSymbol)){}
};

class TMsgOptResetSymbol : public TMsgOptionSymbol
{
public:
	TMsgOptResetSymbol(const char* symbol, const unsigned __int64& optionBlock):
		TMsgOptionSymbol(symbol, optionBlock, M_OPT_RESET_SYMBOL, sizeof(TMsgOptResetSymbol))
	{}
	TMsgOptResetSymbol(const unsigned __int64& symbol, const unsigned __int64& optionBlock):
		TMsgOptionSymbol(symbol, optionBlock, M_OPT_RESET_SYMBOL, sizeof(TMsgOptResetSymbol))
	{}
};

class TMsgOptEndOfDaySummaryReport : public TMessageOption
{
public:
	TMsgOptEndOfDaySummaryReport(const char* symbol, unsigned int time, const OptionBlock& optionBlock,
		unsigned int openPriceDollars,
		unsigned int openPriceFraction,
		unsigned int highPriceDollars,
		unsigned int highPriceFraction,
		unsigned int lowPriceDollars,
		unsigned int lowPriceFraction,
		unsigned int lastPriceDollars,
		unsigned int lastPriceFraction,

		int netChangeDollars,
		int netChangeFraction,
		unsigned int underlyingPriceDollars,
		unsigned int underlyingPriceFraction,
		unsigned int bidPriceDollars,
		unsigned int bidPriceFraction,
		unsigned int askPriceDollars,
		unsigned int askPriceFraction,
		unsigned int volume,
		unsigned int openInterestVolume):
		TMessageOption(symbol, time, optionBlock, M_OPT_EOD_SUMMARY_REPORT, sizeof(TMsgEndOfDaySummaryReport)),
		m_openPriceDollars(openPriceDollars),
		m_openPriceFraction(openPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),

		m_netChangeDollars(netChangeDollars),
		m_netChangeFraction(netChangeFraction),
		m_underlyingPriceDollars(underlyingPriceDollars),
		m_underlyingPriceFraction(underlyingPriceFraction),
		m_bidPriceDollars(bidPriceDollars),
		m_bidPriceFraction(bidPriceFraction),
		m_askPriceDollars(askPriceDollars),
		m_askPriceFraction(askPriceFraction),
		m_volume(volume),
		m_openInterestVolume(openInterestVolume)
	{}

	unsigned int m_openPriceDollars;
	unsigned int m_openPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;

	int m_netChangeDollars;
	int m_netChangeFraction;
	unsigned int m_underlyingPriceDollars;
	unsigned int m_underlyingPriceFraction;
	unsigned int m_bidPriceDollars;
	unsigned int m_bidPriceFraction;
	unsigned int m_askPriceDollars;
	unsigned int m_askPriceFraction;
	unsigned int m_volume;
	unsigned int m_openInterestVolume;
};

class TMsgOptPreviousDayClose : public TMessageOption
{
public:
	TMsgOptPreviousDayClose(const char* symbol, unsigned int time, const OptionBlock& optionBlock,
		unsigned int closePriceDollar,
		unsigned int closePriceFraction):
		TMessageOption(symbol, time, optionBlock, M_OPT_PREVIOUS_DAY_CLOSE, sizeof(TMsgPreviousDayClose)),
		m_closePriceDollar(closePriceDollar),
		m_closePriceFraction(closePriceFraction)
	{}
	unsigned int m_closePriceDollar;
	unsigned int m_closePriceFraction;
};

class TMsgUnderlierInvalid : public TMessageSymbol
{
public:
	TMsgUnderlierInvalid(const char* symbol):TMessageSymbol(symbol, TM_UNDERLIER_INVALID, sizeof(TMsgUnderlierInvalid)){}
	TMsgUnderlierInvalid(const unsigned __int64& symbol = 0):TMessageSymbol(symbol, TM_UNDERLIER_INVALID, sizeof(TMsgUnderlierInvalid)){}
};

class TMsgUnderlierRefreshed : public TMessageSymbol
{
public:
	TMsgUnderlierRefreshed(const char* symbol):TMessageSymbol(symbol, TM_UNDERLIER_REFRESHED, sizeof(TMsgUnderlierRefreshed)){}
	TMsgUnderlierRefreshed(const unsigned __int64& symbol = 0):TMessageSymbol(symbol, TM_UNDERLIER_REFRESHED, sizeof(TMsgUnderlierRefreshed)){}
};

class TMsgOptionUpdate : public TMessageStockUpdate
{
public:
//	OptionKey m_optionKey;
	unsigned __int64 m_optionBlock;
protected:
//	TMsgOptionUpdate(const char* symbol, const OptionKey& optionKey, unsigned int updateOrdinal, unsigned short type, unsigned short length):TMessageStockUpdate(symbol, updateOrdinal, type, length), m_optionKey(optionKey){}
//	TMsgOptionUpdate(const unsigned __int64& symbol, const OptionKey& optionKey, unsigned int updateOrdinal, unsigned short type, unsigned short length):TMessageStockUpdate(symbol, updateOrdinal, type, length), m_optionKey(optionKey){}
	TMsgOptionUpdate(const char* symbol, const unsigned __int64& optionBlock, unsigned int updateOrdinal, unsigned short type, unsigned short length):TMessageStockUpdate(symbol, updateOrdinal, type, length), m_optionBlock(optionBlock){}
	TMsgOptionUpdate(const unsigned __int64& symbol, const unsigned __int64& optionBlock, unsigned int updateOrdinal, unsigned short type, unsigned short length):TMessageStockUpdate(symbol, updateOrdinal, type, length), m_optionBlock(optionBlock){}
};

class TMsgOptionUpdateLevel2 : public TMsgOptionUpdate
{
public:
//	TMsgOptionUpdateLevel2(const char* symbol, const OptionKey& optionKey, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_UPDATE_LEVEL2, sizeof(TMsgOptionUpdateLevel2)){}
//	TMsgOptionUpdateLevel2(const unsigned __int64& symbol, const OptionKey& optionKey, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_UPDATE_LEVEL2, sizeof(TMsgOptionUpdateLevel2)){}
	TMsgOptionUpdateLevel2(const char* symbol, const unsigned __int64& optionBlock, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_UPDATE_LEVEL2, sizeof(TMsgOptionUpdateLevel2)){}
	TMsgOptionUpdateLevel2(const unsigned __int64& symbol = 0, const unsigned __int64& optionBlock = 0, unsigned int updateOrdinal = 0):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_UPDATE_LEVEL2, sizeof(TMsgOptionUpdateLevel2)){}
};

class TMsgOptionUpdateLevel1 : public TMsgOptionUpdate
{
public:
//	TMsgOptionUpdateLevel1(const char* symbol, const OptionKey& optionKey, bool hasPrints, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_UPDATE_LEVEL1, sizeof(TMsgOptionUpdateLevel1)), m_hasPrints(hasPrints){}
//	TMsgOptionUpdateLevel1(const unsigned __int64& symbol, const OptionKey& optionKey, bool hasPrints, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_UPDATE_LEVEL1, sizeof(TMsgOptionUpdateLevel1)), m_hasPrints(hasPrints){}
	TMsgOptionUpdateLevel1(const char* symbol, const unsigned __int64& optionBlock, bool hasPrints, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_UPDATE_LEVEL1, sizeof(TMsgOptionUpdateLevel1)), m_hasPrints(hasPrints){}
	TMsgOptionUpdateLevel1(const unsigned __int64& symbol = 0, const unsigned __int64& optionBlock = 0, bool hasPrints = false, unsigned int updateOrdinal = 0):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_UPDATE_LEVEL1, sizeof(TMsgOptionUpdateLevel1)), m_hasPrints(hasPrints){}
	bool m_hasPrints;
};

class TMsgOptionRefreshed : public TMsgOptionUpdate
{
public:
//	TMsgOptionRefreshed(const char* symbol, const OptionKey& optionKey, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_REFRESHED, sizeof(TMsgOptionRefreshed)){}
//	TMsgOptionRefreshed(const unsigned __int64& symbol, const OptionKey& optionKey, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_REFRESHED, sizeof(TMsgOptionRefreshed)){}
	TMsgOptionRefreshed(const char* symbol, const unsigned __int64& optionBlock, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_REFRESHED, sizeof(TMsgOptionRefreshed)){}
	TMsgOptionRefreshed(const unsigned __int64& symbol = 0, const unsigned __int64& optionBlock = 0, unsigned int updateOrdinal = 0):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_REFRESHED, sizeof(TMsgOptionRefreshed)){}
};

class TMsgOptionInvalid : public TMsgOptionSymbol
{
public:
	TMsgOptionInvalid(const char* symbol, const unsigned __int64& optionBlock):TMsgOptionSymbol(symbol, optionBlock, TM_OPTION_INVALID, sizeof(TMsgOptionInvalid)){}
	TMsgOptionInvalid(const unsigned __int64& symbol = 0, const unsigned __int64& optionBlock = 0):TMsgOptionSymbol(symbol, optionBlock, TM_OPTION_INVALID, sizeof(TMsgOptionInvalid)){}
};

#endif
//////////////////////

class TMessageConnection : public Message
{
public:
	unsigned int m_ipAddress;
	unsigned int m_ipBindAddress;
	unsigned short m_port;
	unsigned short m_bindPort;
	unsigned int m_reconnectSeconds;
	bool m_reconnectable;
	unsigned char m_connectionDataType;
	char m_connectionName[24];
protected:
	TMessageConnection(unsigned short type, unsigned short length,
		unsigned int ipAddress,
		unsigned short port,
		unsigned int ipBindAddress,
		unsigned short bindPort,
		unsigned int reconnectSeconds,
		bool reconnectable,
		unsigned char connectionDataType,
		const char* connectionName):

		Message(type, length),
		m_ipAddress(ipAddress),
		m_ipBindAddress(ipBindAddress),
		m_port(port),
		m_bindPort(bindPort),
		m_reconnectSeconds(reconnectSeconds),
		m_reconnectable(reconnectable),
		m_connectionDataType(connectionDataType)
	{
		U_CopyAndPad(m_connectionName, sizeof(m_connectionName), connectionName, '\0');
	}
};

class TMsgConnected : public TMessageConnection
{
public:
	TMsgConnected(unsigned int ipAddress,
		unsigned short port,
		unsigned int ipBindAddress,
		unsigned short bindPort,
		unsigned int reconnectSeconds,
		bool reconnectable,
		unsigned char connectionDataType,
		const char* connectionName):

		TMessageConnection(TM_CONNECTED, sizeof(TMsgConnected),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName)
	{}
};

class TMsgDisconnected : public TMessageConnection
{
public:
	TMsgDisconnected(unsigned int ipAddress,
		unsigned short port,
		unsigned int ipBindAddress,
		unsigned short bindPort,
		unsigned int reconnectSeconds,
		bool reconnectable,
		unsigned char connectionDataType,
		const char* connectionName):

		TMessageConnection(TM_DISCONNECTED, sizeof(TMsgDisconnected),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName)
	{}
};

class TMsgStartedToConnect : public TMessageConnection
{
public:
	TMsgStartedToConnect(unsigned int ipAddress,
		unsigned short port,
		unsigned int ipBindAddress,
		unsigned short bindPort,
		unsigned int reconnectSeconds,
		bool reconnectable,
		unsigned char connectionDataType,
		const char* connectionName):

		TMessageConnection(TM_STARTED_TO_CONNECT, sizeof(TMsgStartedToConnect),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName)
	{}
};

class TMsgFailedToConnect : public TMessageConnection
{
public:
	TMsgFailedToConnect(unsigned int ipAddress,
		unsigned short port,
		unsigned int ipBindAddress,
		unsigned short bindPort,
		unsigned int reconnectSeconds,
		bool reconnectable,
		unsigned char connectionDataType,
		const char* connectionName):

		TMessageConnection(TM_FAILED_TO_CONNECT, sizeof(TMsgFailedToConnect),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName)
	{}
};

class TMsgConnectionDestroyed : public TMessageConnection
{
public:
	TMsgConnectionDestroyed(unsigned int ipAddress,
		unsigned short port,
		unsigned int ipBindAddress,
		unsigned short bindPort,
		unsigned int reconnectSeconds,
		bool reconnectable,
		unsigned char connectionDataType,
		const char* connectionName):

		TMessageConnection(TM_CONNECTION_DESTROYED, sizeof(TMsgConnectionDestroyed),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName)
	{}
};

//Transaction Server messages

#define TS_STRUCTURES_MAJOR_VERSION			1
#define TS_STRUCTURES_MINOR_VERSION			0

#define ENVIRONMENT_TYPE_PRODUCTION		1
#define ENVIRONMENT_TYPE_SIMULATION		2
#define ENVIRONMENT_TYPE_STAGING		3
#define ENVIRONMENT_TYPE_DEVELOPMENT	4

#define APPLICATION_TYPE_BLAZER			1
#define APPLICATION_TYPE_API			2

// *AK*  FLAGS
#define FLAGS_TCPNoDelay					0x10000
#define FLAGS_CancelAllOrdersOnDisconnect	0x20000

// *AK* 

enum Compression
{
	NoCompression		= 0x00,
	FromClientToServer	= 0x01,
	FromServerToClient	= 0x02,
	FullCompression		= 0x03
};

class TMsgMdReqLogon : public Message
{
public:
	
	TMsgMdReqLogon(const char* userId, 
			   const char* password, 
			   const char* ipAddress, 
			   const char* appVersion, 
			   unsigned int flags = 0, 
			   bool simulation = true, 
			   unsigned int compression = NoCompression,
			   unsigned int requestId = 0):
		Message(M_REQ_MD_LOGON, sizeof(TMsgMdReqLogon))
		, m_flags( flags )
		, m_simulation( simulation )
		, m_compression( compression )
		, m_requestId( requestId )
	{
		U_CopyAndPad(m_userId, sizeof(m_userId), userId, '\0');
		U_CopyAndPad(m_password, sizeof(m_password), password, '\0');
		U_CopyAndPad(m_ipAddress, sizeof(m_ipAddress), ipAddress, '\0');
		U_CopyAndPad(m_appVersion, sizeof(m_appVersion), appVersion, '\0');
	}

	char			m_userId[5];
	char			m_password[33];
	char			m_ipAddress[33];
	char			m_appVersion[25];
	unsigned int	m_flags;
	bool			m_simulation;
	unsigned int	m_compression;
	unsigned int	m_requestId;
};

/* 
enum MdEntitlements : unsigned __int64
{
	MDE_NSDQ = 0x0000000000000001,
	MDE_ARCA = 0x0000000000000002,
	MDE_BATS = 0x0000000000000004,
	MDE_BATY = 0x0000000000000008,
	MDE_EDGA = 0x0000000000000010,
	MDE_EDGX = 0x0000000000000020,
	MDE_UQDF = 0x0000000000000040,
	MDE_UTDF = 0x0000000000000080,
	MDE_CQS  = 0x0000000000000100,
	MDE_CTS  = 0x0000000000000200,
	MDE_NYSE = 0x0000000000000400,
	MDE_AMEX = 0x0000000000000800,
};
*/
class TMsgMdLogonResponse : public Message
{
public:
	
	TMsgMdLogonResponse(const char* userId,
				const char* serverVersion,
				unsigned int flags = SUCCEEDED,
				bool reserved = true,
				unsigned int compression = NoCompression,
				unsigned int requestId = 0,
				unsigned __int64 marketDataEntitlements = 0):
		Message(M_RESP_MD_LOGON, sizeof(TMsgMdLogonResponse))
		, m_flags(flags)
		, m_reserved(reserved)
		, m_compression(compression)
		, m_requestId(requestId)
		, m_marketDataEntitlements(marketDataEntitlements)
	{
		U_CopyAndPad(m_userId, sizeof(m_userId), userId, '\0');
		U_CopyAndPad( m_serverVersion, sizeof(m_serverVersion), serverVersion, '\0');
	}

	enum
	{
		SUCCEEDED	= 0,
		TIMED_OUT,
		FAILED		= 0x80000000
	};
	
	char				m_userId[5];
	char				m_serverVersion[25];
	unsigned int		m_flags;
	bool				m_reserved;
	unsigned int		m_compression;
	unsigned int		m_requestId;
	unsigned __int64	m_marketDataEntitlements;
};

class TReqPublicKey : public Message
{
public:
	TReqPublicKey(unsigned int requestId):Message(M_REQ_PUBLIC_KEY, sizeof(TReqPublicKey)), m_requestId(requestId){}
	unsigned int m_requestId;
};

class TMsgPublicKey : public Message
{
public:
	TMsgPublicKey(unsigned int requestId, unsigned short blobSize):Message(M_RESP_PUBLIC_KEY, sizeof(TMsgPublicKey) + blobSize), m_requestId(requestId){}
	unsigned int m_requestId;
};

class TMsgReqLogon : public TMessageTime//Executor logon
{
public:
	TMsgReqLogon(
		unsigned int flags,
		unsigned int compressionType,
		const char* ipAddress,
		const char* firmId,
		const char* userName,
		const char* password,
		WORD applicationType = APPLICATION_TYPE_BLAZER,
		WORD environment = ENVIRONMENT_TYPE_PRODUCTION,
		WORD majorVersion = TS_STRUCTURES_MAJOR_VERSION,
		WORD minorVersion = TS_STRUCTURES_MINOR_VERSION):
/*
	TMsgReqLogon::TMsgReqLogon(
		unsigned int flags,
		unsigned int compressionType,
		const char* ipAddress,
		const char* firmId,
		const char* userName,
		const char* password,
		WORD applicationType,
		WORD environment,
		WORD majorVersion,
		WORD minorVersion):
*/
		TMessageTime(0, TS_LOGIN_REQ, sizeof(TMsgReqLogon)),
		MajorVersion(majorVersion),
		MinorVersion(minorVersion),
		Environment(environment),
		ApplicationType(applicationType),
	// *AK* start
		Flags(flags),
		CompressionType(compressionType)
	{
		U_CopyAndPad(IPAddress, sizeof(IPAddress), ipAddress, '\0');
		U_CopyAndPad(FirmID, sizeof(FirmID), firmId, '\0');
	//	U_CopyAndPad(UserName, sizeof(UserName), userName, '\0');
		memset(UserName, 0, sizeof(UserName));
		unsigned int userNameLen = MAX_TRADER_ID_SIZE - 1;
		if(userNameLen > sizeof(UserName))
		{
			userNameLen = sizeof(UserName);
		}
		U_CopyAndPad(UserName, userNameLen, userName, '\0');
		U_CopyAndPad(Password, sizeof(Password), password, '\0');
	}
	WORD			MajorVersion;
	WORD			MinorVersion;
	WORD			Environment;
	WORD			ApplicationType;
// *AK* start
	unsigned int	Flags;
	unsigned int	CompressionType;
	char			IPAddress[MAX_IP_ADDRESS_SIZE];
	char			FirmID[MAX_FIRM_ID_SIZE];
// *AK* end
	char			UserName[MAX_USERNAME_SIZE];
	char			Password[MAX_PASSWORD_SIZE];
};

#define LOGIN_REJECT_REASON_INVALID_USERNAME	1
#define LOGIN_REJECT_REASON_INVALID_PASSWORD	2
#define LOGIN_REJECT_REASON_INVALID_VERSION		3
#define LOGIN_REJECT_REASON_ALREADY_LOGGED_IN	4
//TS->TSClient, Sent in response to TS_LOGIN_MESSAGE request if the login is rejected

class TMsgReason : public TMessageTime
{
public:
	WORD	Reason;
	char	ReasonText[1];
protected:
	TMsgReason(WORD reason, unsigned short type, unsigned short length):TMessageTime(0, type, length), Reason(reason){*ReasonText = '\0';}
};


class TMsgLogonReject : public TMsgReason
{
public:
	TMsgLogonReject(WORD reason):TMsgReason(reason, TS_LOGIN_REJECT, sizeof(TMsgLogonReject)){}
};





//TS sends this message to TSClient in response to TS_LOGIN_MESSAGE
//Logged in user type
enum TakionUserType
{
	USER_TYPE_TRADER = 0x00000001,
	USER_TYPE_OPERATIONS = 0x00000002,
	USER_TYPE_SUPERVISOR = 0x00000004,
	USER_TYPE_FIRM_MANAGER = 0x00000008,
	USER_TYPE_AGGRESSIVE_ODD_LOTS = 0x00000010,
	USER_TYPE_WATCHER = 0x00000020,

	USER_TYPE_ALL = USER_TYPE_TRADER|USER_TYPE_OPERATIONS|USER_TYPE_SUPERVISOR|USER_TYPE_FIRM_MANAGER|USER_TYPE_AGGRESSIVE_ODD_LOTS|USER_TYPE_WATCHER
};
/*
#define	USER_TYPE_TRADER					0x00000001		// Trader
#define	USER_TYPE_OPERATIONS				0x00000002		// Operations
#define	USER_TYPE_SUPERVISOR				0x00000004		// Supervisor
#define	USER_TYPE_FIRM_MANAGER				0x00000008		// Firm Manager
#define	USER_TYPE_AGGRESSIVE_ODD_LOTS		0x00000010
#define	USER_TYPE_WATCHER					0x00000020
*/
enum TraderMiscFlags : unsigned char
{
	TMF_QVV_QSMT,
	TMF_QVV_QADD,
	TMF_QVV_QTAK,

	TMF_QSMT_SMART_SWIPE,
	TMF_QSMT_AGGRESSIVE,
	TMF_QSMT_DUMB_SWIPE,

	TMF_QSMT_ON_OPEN_CLOSE,

	TMF_QSMT_SMART_SWIPE_MH,
	TMF_QSMT_AGGRESSIVE_MH,
	TMF_QSMT_DUMB_SWIPE_MH,
	TMF_QSMT_PASSIVE = 11,
};

//TS->TSClient, Sent in response to TS_LOGIN_MESSAGE request if the login is successful
class TMsgLogonResponse : public TMessageTime
{
public:
	TMsgLogonResponse():TMessageTime(0, TS_LOGIN_RESP, sizeof(TMsgLogonResponse)){}
	WORD				NumberOfAccounts;						//This many account messages follow
	DWORD				UserType;								//Specifies the logged in user type
	unsigned __int64	MDEntitlements;							// *AK* Market Data entitlements - DWORD may not be sufficient
// *AK* start
	unsigned int		MulticastIP;							// *AK* We can use it if we are going to offer multicast for market data
	unsigned int		MulticastPort;							// *AK*
	char				TraderID[MAX_TRADER_ID_SIZE];			// Should be used in all transactions, should be 4 Capital letters
// *AK* end
	char				Title[MAX_USER_TITLE_SIZE];				//Not sure if we need this, but can be used to give a title to the GUI
	char				DefaultAccount[MAX_ACCOUNT_SIZE];		//Default account for this user
	unsigned __int64	MiscSettings;
	unsigned __int64	ServerVersion;
};

class TMsgReqLogout : public TMsgReason
{
public:
	TMsgReqLogout(WORD reason):TMsgReason(reason, TS_LOGOUT_REQ, sizeof(TMsgReqLogout)){}
};

//TS->TSClient, RM->TS, This message may be sent by either TS or a Risk Manager to TSClient upon account profile change or as a part of initally account message
class TMsgAccountRiskProfile : public TMessageTime
{
public:
	TMsgAccountRiskProfile():TMessageTime(0, TS_ACCOUNT_RISK_PROFILE, sizeof(TMsgAccountRiskProfile)){}
	char				AccountName[MAX_ACCOUNT_SIZE];
	char				UserName[MAX_TRADER_SIZE];		//The Risk Manager who might have generated this, or empty if it comes from TS intially
	double				InitialMemberContribution;
	double				FixedBP;
	double				OvernightMaxValue;//OvernightEquityMultiplier;
	double				IntradayEquityMultiplier;
	double				DailyPLLimit;
	double				MinEquityAmountAllowed;
	double				PercentEquityLossLimit;
	double				Threshold;
	DWORD				IntradayMaxPosShares;
	double				IntradayMaxPosValue;
	double				IntradayMaxLongValue;
	double				IntradayMaxShortValue;
	DWORD				OvernightMaxPosShares;
	double				OvernightMaxPosValue;
	double				OvernightMaxLongValue;
	double				OvernightMaxShortValue;
	DWORD				OrderProcessingFlags;
	DWORD				AcctProcessingFlags;
	DWORD				MaxOpenPositions;
	double				MaxSharePrice;


// *AK* begin
	// Additional fields that may be required to have
	double				MaxLoss;
	double				MaxLossPerPosition;
	double				MaxOpenLossPerPosition;
	double				MaxLossMarked;
	double				MaxTradedMoney;
	double				MinShortPrice;
	unsigned int		MaxOrderSize;
	unsigned int		MaxPendingOrdersPerPosition;
	unsigned int		MaxSharesTotal;
	unsigned int		MaxSharesTraded;
	char				FirmID[MAX_FIRM_ID_SIZE];
	char				AccountType;
	char				FirmType;
// *AK* end
	char				GroupID_LSTK[MAX_MMID_SIZE];
	double				DisplayMultiplier_LSTK;
	double				MaxOrderValue;
	double				EstBeginningDayEquity;
	char                ClearingAccountName[MAX_ACCOUNT_SIZE];

	double				MaxLossPerPositionClose;
	double				MaxLossPerAccountClose;
	double				MaxLossPerPositionSlack;
	double				MaxLossPerAccountSlack;

//	double				PNLLossHi;
//	int m_autoCloseStartDelaySecond;
//	int m_autoCloseEndDelaySecond;

//	double				OvernightMaxValue;//done by OvernightEquityMultiplier
	double				OptionBuyingPower;
	unsigned int		MaxOptionSharesTraded;
	unsigned int		MaxOptionOrderSize;
	double				MaxOptionOrderValue;
	bool				NakedOptionSellAllowed;
	bool				EnforceClearingAccountAggregation;
	unsigned int		MaxOptionContractsOpen;
};
//End Transaction Server messages

class TMsgNewAccount : public TMessageTime
{
public:
	TMsgNewAccount():TMessageTime(0, TS_NEW_ACCOUNT, sizeof(TMsgNewAccount)){}
	char							AccountName[MAX_ACCOUNT_SIZE];
	double							BuyingPower;
	DWORD							ExecutionEntitlements;				//Exchange ECN execution entitlements
	DWORD							SecurityEntitlements;				//Security entitlements
	DWORD							DefaultRoute;						//Defualt route for orders
	bool							TradingAllowed;						//Flag, whether trading on this account is allowed for specific trader, can be used for view only
	TMsgAccountRiskProfile			AccountRiskProfile;					//Risk Profiles, this message may be passed around in future to control risk during the day between Risk Manager-TS and Front end
};


class TMessageAccountRecoveryBase : public TMessageTime
{
public:
	DWORD						RequestID;
	char						AccountName[MAX_ACCOUNT_SIZE];
protected:
	TMessageAccountRecoveryBase(DWORD requestID, const char* accountName, unsigned short type, unsigned short length):
		TMessageTime(0, type, length),
		RequestID(requestID)
	{
		U_CopyAndPad(AccountName, sizeof(AccountName), accountName, '\0');
	}
};

//TSClient -> TS, Request for overnight positions
class TMsgReqOvernightPosition : public TMessageAccountRecoveryBase
{
public:
	TMsgReqOvernightPosition(DWORD requestID, const char* accountName):
		TMessageAccountRecoveryBase(requestID, accountName, TS_ACCOUNT_POSITION_REQ, sizeof(TMsgReqOvernightPosition))
	{
	}
};

//TS -> TSClient, TS send a stream of overnight position for the requested account in response to TS_ACCOUNT_OVERNIGHT_POSITION_REQUEST_MESSAGE
// *AK* Message with zero Symbol, InstrumentType, Quantity and AveragePrice can be used to indicate end of transmission instead of
// *AK* TS_ACCOUNT_OVERNIGHT_POSITION_RESPONSE_MESSAGE

class TMsgOvernightPosition : public TMessageAccountRecoveryBase
{
public:
	TMsgOvernightPosition(DWORD requestID, const char* accountName):TMessageAccountRecoveryBase(requestID, accountName, TS_ACCOUNT_POSITION, sizeof(TMsgOvernightPosition)){}

	char	Symbol[MAX_SYMBOL_SIZE];
	UCHAR	InstrumentType;

	long	Quantity;
	double	AveragePrice;

	unsigned int m_borrowedQuantity;
	double	AverageBorrowedPrice;

	unsigned __int64 m_optionBlock;
	char m_lastLocateExecutionID[MAX_MARKET_REFERENCE_ID];
};

//TS->TSClient Sent as the last message to TS_ACCOUNT_OVERNIGHT_POSITION_REQUEST_MESSAGE to indicate either an error condition or successful completion of download
class TMsgOvernightPositionLoadComplete : public TMessageAccountRecoveryBase
{
public:
	TMsgOvernightPositionLoadComplete(DWORD requestID, const char* accountName):TMessageAccountRecoveryBase(requestID, accountName, TS_ACCOUNT_POSITION_RESP, sizeof(TMsgOvernightPositionLoadComplete)){}
	DWORD	PositionCount;
	WORD	ResultCode;								//Filled in case of error
	char	ResultText[MAX_RESULT_TEXT_SIZE];		//Filled in case of error
};




#define RECOVERY_REASON_STARTING					1
#define RECOVERY_REASON_DISCONNECTED				2

class TMessageReqAccountRecovery : public TMessageAccountRecoveryBase
{
public:
	WORD						RecoveryReason;						//The reason for full recovery
protected:
	TMessageReqAccountRecovery(DWORD requestID, const char* accountName, WORD recoveryReason, unsigned short type, unsigned short length):
		TMessageAccountRecoveryBase(requestID, accountName, type, length),
		RecoveryReason(recoveryReason)
	{
	}
};

//TSClient->TS sent to recover the entire stream of account messages starting from the given sequenced number
class TMsgReqAccountFullRecovery : public TMessageReqAccountRecovery
{
public:
	TMsgReqAccountFullRecovery(DWORD requestID, const char* accountName, WORD recoveryReason, DWORD lastAccountMessageSequenuenceNumber):
		TMessageReqAccountRecovery(requestID, accountName, recoveryReason, TS_ACCOUNT_RECOVERY_FULL_REQ, sizeof(TMsgReqAccountFullRecovery)),
		LastAccountMessageSequenuenceNumber(lastAccountMessageSequenuenceNumber)
	{}
	DWORD						LastAccountMessageSequenuenceNumber;
};

//TSClient -> TS Sent to recover the current open orders and open positions
class TMsgReqAccountQuickRecovery : public TMessageReqAccountRecovery
{
public:
	TMsgReqAccountQuickRecovery(DWORD requestID, const char* accountName, WORD recoveryReason):
		TMessageReqAccountRecovery(requestID, accountName, recoveryReason, TS_ACCOUNT_RECOVERY_QUICK_REQ, sizeof(TMsgReqAccountQuickRecovery))
	{}
};

class TMsgReqExecutionHistory : public TMessageReqAccountRecovery
{
public:
	TMsgReqExecutionHistory(DWORD requestID, const char* accountName, WORD recoveryReason):
		TMessageReqAccountRecovery(requestID, accountName, recoveryReason, TS_ACCOUNT_EXEC_HISTORY_REQ, sizeof(TMsgReqExecutionHistory))
	{}
};

class TMsgHistoryComplete : public TMessageAccountRecoveryBase
{
public:
	DWORD	m_objectCount;
	WORD	m_resultCode;								//Filled in case of error
	char	m_resultText[MAX_RESULT_TEXT_SIZE];		//Filled in case of error
protected:
	TMsgHistoryComplete(DWORD requestID, const char* accountName, DWORD objectCount, WORD resultCode, unsigned short type, unsigned short length):
		TMessageAccountRecoveryBase(requestID, accountName, type, length)
	{
		memset(m_resultText, 0, sizeof(m_resultText));
	}
};

class TMsgExecutionHistoryComplete : public TMsgHistoryComplete
{
public:
	TMsgExecutionHistoryComplete(DWORD requestID, const char* accountName, DWORD objectCount, WORD resultCode):
		TMsgHistoryComplete(requestID, accountName, objectCount, resultCode, TS_ACCOUNT_EXEC_HISTORY_COMPLETE, sizeof(TMsgExecutionHistoryComplete)){}
};

class TMsgReqOrderHistory : public TMessageReqAccountRecovery
{
public:
	TMsgReqOrderHistory(DWORD requestID, const char* accountName, WORD recoveryReason):
		TMessageReqAccountRecovery(requestID, accountName, recoveryReason, TS_ACCOUNT_ORDER_HISTORY_REQ, sizeof(TMsgReqOrderHistory))
	{}
};

class TMsgOrderHistoryComplete : public TMsgHistoryComplete
{
public:
	TMsgOrderHistoryComplete(DWORD requestID, const char* accountName, DWORD objectCount, WORD resultCode):
		TMsgHistoryComplete(requestID, accountName, objectCount, resultCode, TS_ACCOUNT_ORDER_HISTORY_COMPLETE, sizeof(TMsgOrderHistoryComplete)){}
};

#ifdef FIRM_VALUES

class TMsgFirm : public Message
{
public:
//	unsigned __int64 m_clearingNamePart1;
//	unsigned __int64 m_clearingNamePart2;
//	unsigned int m_firmId;
	char m_clearingAccountName[MAX_ACCOUNT_SIZE];
	char m_firmId[MAX_FIRM_ID_SIZE];
protected:
	TMsgFirm(const char* clearingAccountName, const char* firmId, unsigned short type, unsigned short length):
		Message(type, length)
	{
		U_CopyAndPad(m_clearingAccountName, sizeof(m_clearingAccountName), clearingAccountName, '\0');
		U_CopyAndPad(m_firmId, sizeof(m_firmId), firmId, '\0');
//		AccountId accountId(clearingAccountName);
//		m_clearingNamePart1 = accountId.GetFirst();
//		m_clearingNamePart2 = accountId.GetSecond();
//		m_firmId = U_StringToUInt(firmId);
	}
	TMsgFirm(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned int& firmId, unsigned short type, unsigned short length):
		Message(type, length)
//		m_clearingNamePart1(clearingNamePart1),
//		m_clearingNamePart2(clearingNamePart2),
//		m_firmId(firmId)

	{
		*(unsigned __int64*)m_clearingAccountName = clearingNamePart1;
		*(unsigned __int64*)(m_clearingAccountName + sizeof(unsigned __int64)) = clearingNamePart2;
		*(unsigned int*)m_firmId = firmId;
		m_firmId[sizeof(unsigned int)] = '\0';
	}
};

class TMsgFirmUntradeableListLoaded : public TMsgFirm
{
public:
	TMsgFirmUntradeableListLoaded(const char* clearingAccountName, const char* firmId):
		TMsgFirm(clearingAccountName, firmId, TM_UNTRADEABLE_LIST_LOADED, sizeof(TMsgFirmUntradeableListLoaded))
	{
	}
	TMsgFirmUntradeableListLoaded(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned int& firmId):
		TMsgFirm(clearingNamePart1, clearingNamePart2, firmId, TM_UNTRADEABLE_LIST_LOADED, sizeof(TMsgFirmUntradeableListLoaded))
	{
	}
};

class TMsgAllUntradeableListsLoaded : public Message
{
public:
	TMsgAllUntradeableListsLoaded():Message(TM_ALL_UNTRADEABLE_LISTS_LOADED, sizeof(TMsgAllUntradeableListsLoaded)){}
};

class TMsgFirmPosition : public TMessageTime//Message
{
public:
	char m_clearingAccountName[MAX_ACCOUNT_SIZE];
	char m_symbol[MAX_SYMBOL_SIZE];
	char m_firmId[MAX_FIRM_ID_SIZE];
protected:
//	TMsgFirmPosition(const char* clearingAccountName, const char* symbol, const char* firmId, unsigned short type, unsigned short length):Message(type, length)
	TMsgFirmPosition(const char* clearingAccountName, const char* symbol, const char* firmId, const unsigned int& timestamp, unsigned short type, unsigned short length):TMessageTime(timestamp, type, length)
	{
		U_CopyAndPad(m_clearingAccountName, sizeof(m_clearingAccountName), clearingAccountName, '\0');
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
		U_CopyAndPad(m_firmId, sizeof(m_firmId), firmId, '\0');
	}
//	TMsgFirmPosition(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned __int64& symbol, const unsigned int& firmId, unsigned short type, unsigned short length):Message(type, length)
	TMsgFirmPosition(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned __int64& symbol, const unsigned int& firmId, const unsigned int& timestamp, unsigned short type, unsigned short length):TMessageTime(timestamp, type, length)
	{
		*(unsigned __int64*)m_clearingAccountName = clearingNamePart1;
		*(unsigned __int64*)(m_clearingAccountName + sizeof(unsigned __int64)) = clearingNamePart2;
		*(unsigned __int64*)m_symbol = symbol;
		*(unsigned int*)m_firmId = firmId;
		m_firmId[sizeof(unsigned int)] = '\0';
	}
};

//TSClient -> TS. Sent to subscribe to ClearingAccount position
class TMsgReqSubscribeFirmPosition : public TMsgFirmPosition
{
public:
	TMsgReqSubscribeFirmPosition(const char* clearingAccountName, const char* symbol, const char* firmId, const unsigned int& timestamp):TMsgFirmPosition(clearingAccountName, symbol, firmId, timestamp, TS_FIRM_POSITION_SUBSCRIBE_REQ, sizeof(TMsgReqSubscribeFirmPosition)){}
	TMsgReqSubscribeFirmPosition(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned __int64& symbol, const unsigned int& firmId, const unsigned int& timestamp):TMsgFirmPosition(clearingNamePart1, clearingNamePart2, symbol, firmId, timestamp, TS_FIRM_POSITION_SUBSCRIBE_REQ, sizeof(TMsgReqSubscribeFirmPosition)){}
};

//TS->TSClient Sent to all subscribed clients
class TMsgUpdateFirmPosition : public TMsgFirmPosition
{
public:
	TMsgUpdateFirmPosition(const char* clearingAccountName, const char* symbol, const char* firmId, int firmPosition, unsigned int firmPendingSellSharesPassive, unsigned int firmPendingSellSharesNonPassive, const unsigned int& timestamp):
		TMsgFirmPosition(clearingAccountName, symbol, firmId, timestamp, TS_FIRM_POSITION_UPDATE, sizeof(TMsgUpdateFirmPosition)),
		m_firmPosition(firmPosition),
		m_firmPendingSellSharesPassive(firmPendingSellSharesPassive),
		m_firmPendingSellSharesNonPassive(firmPendingSellSharesNonPassive)
		{}
	TMsgUpdateFirmPosition(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned __int64& symbol, const unsigned int& firmId, int firmPosition, unsigned int firmPendingSellSharesPassive, unsigned int firmPendingSellSharesNonPassive, const unsigned int& timestamp):
		TMsgFirmPosition(clearingNamePart1, clearingNamePart2, symbol, firmId, timestamp, TS_FIRM_POSITION_UPDATE, sizeof(TMsgUpdateFirmPosition)),
		m_firmPosition(firmPosition),
		m_firmPendingSellSharesPassive(firmPendingSellSharesPassive),
		m_firmPendingSellSharesNonPassive(firmPendingSellSharesNonPassive)
		{}
	int m_firmPosition;
	unsigned int m_firmPendingSellSharesPassive;
	unsigned int m_firmPendingSellSharesNonPassive;
};

//TSClient -> TS. Sent to unsubscribe from ClearingAccount position
class TMsgReqUnsubscribeFirmPosition : public TMsgFirmPosition
{
public:
	TMsgReqUnsubscribeFirmPosition(const char* clearingAccountName, const char* symbol, const char* firmId, const unsigned int& timestamp):TMsgFirmPosition(clearingAccountName, symbol, firmId, timestamp, TS_FIRM_POSITION_UNSUBSCRIBE_REQ, sizeof(TMsgReqUnsubscribeFirmPosition)){}
	TMsgReqUnsubscribeFirmPosition(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned __int64& symbol, const unsigned int& firmId, const unsigned int& timestamp):TMsgFirmPosition(clearingNamePart1, clearingNamePart2, symbol, firmId, timestamp, TS_FIRM_POSITION_UNSUBSCRIBE_REQ, sizeof(TMsgReqUnsubscribeFirmPosition)){}
};

class TMsgFirmEnforcement : public TMessageTime
{
public:
	TMsgFirmEnforcement(const char* clearingAccountName, bool enforceFirm, const unsigned int& timestamp):
		TMessageTime(timestamp, TS_FIRM_ENFORCEMENT, sizeof(TMsgFirmEnforcement)),
		m_enforceFirm(enforceFirm)
	{
		U_CopyAndPad(m_clearingAccountName, sizeof(m_clearingAccountName), clearingAccountName, '\0');
	}
	TMsgFirmEnforcement(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, bool enforceFirm, const unsigned int& timestamp):
		TMessageTime(timestamp, TS_FIRM_ENFORCEMENT, sizeof(TMsgFirmEnforcement)),
		m_enforceFirm(enforceFirm)
	{
		*(unsigned __int64*)m_clearingAccountName = clearingNamePart1;
		*(unsigned __int64*)(m_clearingAccountName + sizeof(unsigned __int64)) = clearingNamePart2;
	}
	char m_clearingAccountName[MAX_ACCOUNT_SIZE];
	bool m_enforceFirm;
};

enum FirmPositionSubscribeRejectCode : unsigned short
{
	FPS_UNKNOWN_FIRM = 1,
	FPS_UNKNOWN_CA,
	FPS_UNKNOWN_SYMBOL,

	FPS_Count
};

class TMsgFirmPositionReject : public TMsgFirmPosition
{
public:
	TMsgFirmPositionReject(const char* clearingAccountName, const char* symbol, const char* firmId, const unsigned int& timestamp, unsigned short rejectCode, const char* rejectText):
		TMsgFirmPosition(clearingAccountName, symbol, firmId, timestamp, TS_FIRM_POSITION_REJECT, sizeof(TMsgFirmPositionReject)),
		m_rejectCode(rejectCode)
	{
		if(rejectText && *rejectText)U_CopyAndPad(m_rejectText, sizeof(m_rejectText), rejectText, '\0');
		else memset(m_rejectText, 0, sizeof(m_rejectText));
	}
	TMsgFirmPositionReject(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned __int64& symbol, const unsigned int& firmId, const unsigned int& timestamp, unsigned short rejectCode, const char* rejectText):
		TMsgFirmPosition(clearingNamePart1, clearingNamePart2, symbol, firmId, timestamp, TS_FIRM_POSITION_REJECT, sizeof(TMsgFirmPositionReject)),
		m_rejectCode(rejectCode)
	{
		if(rejectText && *rejectText)U_CopyAndPad(m_rejectText, sizeof(m_rejectText), rejectText, '\0');
		else memset(m_rejectText, 0, sizeof(m_rejectText));
	}
	unsigned short m_rejectCode;
	char m_rejectText[MAX_RESULT_TEXT_SIZE];
};

//TS->TSClient Sent to all Firm's clients, Used to distribute untradeable stocks and status change
class TMsgFirmUntradeableStatusUpdate : public TMessageTime
{
public:
	TMsgFirmUntradeableStatusUpdate(const char* clearingAccountName, const char* symbol, const char* firmId, const unsigned int& timestamp, bool untradeable):
		TMessageTime(timestamp, TS_UNTRADEABLE_STATUS_UPDATE, sizeof(TMsgFirmUntradeableStatusUpdate)),
		m_untradeable(untradeable)
	{
		U_CopyAndPad(m_clearingAccountName, sizeof(m_clearingAccountName), clearingAccountName, '\0');
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
		U_CopyAndPad(m_firmId, sizeof(m_firmId), firmId, '\0');
	}
	TMsgFirmUntradeableStatusUpdate(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned __int64& symbol, const unsigned int& firmId, const unsigned int& timestamp, bool untradeable):
		TMessageTime(timestamp, TS_UNTRADEABLE_STATUS_UPDATE, sizeof(TMsgFirmUntradeableStatusUpdate)),
		m_untradeable(untradeable)
	{
		*(unsigned __int64*)m_clearingAccountName = clearingNamePart1;
		*(unsigned __int64*)(m_clearingAccountName + sizeof(unsigned __int64)) = clearingNamePart2;
		*(unsigned __int64*)m_symbol = symbol;
		*(unsigned int*)m_firmId = firmId;
		m_firmId[sizeof(unsigned int)] = '\0';
	}
	char m_clearingAccountName[MAX_ACCOUNT_SIZE];
	char m_symbol[MAX_SYMBOL_SIZE];
	char m_firmId[MAX_FIRM_ID_SIZE];
	bool m_untradeable;
};

#endif

//TS->TSClient, sent in response to TS_ACCOUNT_RECOVERY_QUICK_REQUEST_MESSAGE
class TMsgPosition : public TMessageAccountRecoveryBase
{
public:
	TMsgPosition(DWORD requestID,
		const char* accountName,
		const char* symbol,
		unsigned char instrumentType,
		long quantity,
		const Price& price,
		long overnightQuantity,
		const Price& overnightPrice,
		long currentQuantity,		//Includes overnight positions too
		const Price& currentPrice,
		unsigned int closedLongQuantity,
		const Money& closedLongCost,
		const Money& closedLongValue,

		unsigned int closedShortQuantity,
		const Money& closedShortCost,
		const Money& closedShortValue,

		unsigned int borrowedQuantity,
		const Price& borrowedPrice,

		const unsigned __int64& optionBlock,

		const char* lastLocateExecutionID
		):
		TMessageAccountRecoveryBase(requestID, accountName, TS_ACCOUNT_RECOVERY_RESP, sizeof(TMsgPosition)),
		InstrumentType(instrumentType),
		Quantity(quantity),
		AveragePrice(price.toDouble()),
		OvernightPositionQuantity(overnightQuantity),
		OvernightPositionAvgPrice(overnightPrice.toDouble()),
		CurrentPositionQuantity(currentQuantity),
		CurrentPositionAvgPrice(currentPrice.toDouble()),
		ClosedLongPositionQuantity(closedLongQuantity),
		ClosedLongPositionCost(closedLongCost.toDouble()),
		ClosedLongPositionValue(closedLongValue.toDouble()),
		ClosedShortPositionQuantity(closedShortQuantity),
		ClosedShortPositionCost(closedShortCost.toDouble()),
		ClosedShortPositionValue(closedShortValue.toDouble()),
		m_borrowedQuantity(borrowedQuantity),
		m_borrowedAvgPrice(borrowedPrice.toDouble()),

		m_optionBlock(optionBlock)
	{
		U_CopyAndPad(Symbol, sizeof(Symbol), symbol, '\0');
		U_CopyAndPad(m_lastLocateExecutionID, sizeof(m_lastLocateExecutionID), lastLocateExecutionID ? lastLocateExecutionID : "", '\0');
	}

	char	Symbol[MAX_SYMBOL_SIZE];
	UCHAR	InstrumentType;

	long	Quantity;
	double	AveragePrice;

	long	OvernightPositionQuantity;
	double	OvernightPositionAvgPrice;

	long	CurrentPositionQuantity;		//Includes overnight positions too
	double	CurrentPositionAvgPrice;

	DWORD	ClosedLongPositionQuantity;
	double	ClosedLongPositionCost;
	double	ClosedLongPositionValue;

	DWORD	ClosedShortPositionQuantity;
	double	ClosedShortPositionCost;
	double	ClosedShortPositionValue;

	unsigned int m_borrowedQuantity;
	double m_borrowedAvgPrice;

	unsigned __int64 m_optionBlock;

	char m_lastLocateExecutionID[MAX_MARKET_REFERENCE_ID];
};

//Order sides - match with FIX
#define ORDER_SIDE_BUY					'1'		// = Buy
#define ORDER_SIDE_SELL					'2'		// = Sell
#define ORDER_SIDE__BUY_MINUS			'3'		// = Buy minus
#define ORDER_SIDE_SELL_PLUS			'4'		// = Sell plus
#define ORDER_SIDE_SELL_SHORT			'5'		// = Sell short
#define ORDER_SIDE_SELL_SHORT_EXEMPT	'6'		// = Sell short exempt
#define ORDER_SIDE_UNDISCLOSED			'7'		// = Undisclosed (valid for IOI and List Order messages only)
#define ORDER_SIDE_CROSS				'8'		// = Cross (orders where counterparty is an exchange, valid for all messages except IOIs)
#define ORDER_SIDE_CROSS_SHORT			'9'		// = Cross short
#define ORDER_SIDE_SHORT_EXEMPT			'A'		//= Cross short exxmpt
#define ORDER_SIDE_AS_DEFINED			'B'		//"As Defined" (for use with multileg instruments)
#define ORDER_SIDE_OPPOSITE				'C'		// = "Opposite" (for use with multileg instruments)



// Order types - match with FIX
#define ORDER_TYPE_NULL							'0'	// Invalid or illegal order type
#define ORDER_TYPE_MARKET						'1'
#define ORDER_TYPE_LIMIT						'2'
#define ORDER_TYPE_STOP							'3'
#define ORDER_TYPE_STOP_LIMIT					'4'
#define	ORDER_TYPE_MARKET_ON_CLOSE				'5'//Deprecated (Use ORDER_TYPE_MARKET and TIF_ATC )
#define	ORDER_TYPE_WITH_OR_WITHOUT				'6'
#define	ORDER_TYPE_LIMIT_OR_BETTER				'7'//Deprecated
#define	ORDER_TYPE_LIMIT_WITH_OR_WITHOUT		'8'
#define	ORDER_TYPE_ON_BASIS						'9'
#define ORDER_TYPE_LIMIT_ON_CLOSE				'B' // Deprecated (Use ORDER_TYPE_LIMIT and TIF_ATC )
#define ORDER_TYPE_FUNARI						'I'	// Deprecated - LeveL wants this order type sent instead of ORDER_TYPE_LIMIT
#define	ORDER_TYPE_ON_PEGGED					'P'

/*
//Order TIFS - match with FIX
#define TIF_DAY						'0'		//Day (or session)
#define TIF_GTC						'1'		//Good Till Cancel (GTC)
#define TIF_OPG						'2'		//At the Opening (OPG)
#define TIF_IOC						'3'		//Immediate Or Cancel (IOC)
#define TIF_FOK						'4'		//Fill Or Kill (FOK)
#define TIF_GTX						'5'		//Good Till Crossing (GTX)
#define TIF_GTD						'6'		//Good Till Date (GTD)
#define TIF_ATC						'7'		//At the Close
//Non FIX TIFs
#define	GT_XPR						'X'	// Express
#define	GT_DAY_PLUS					'P'	// Day Plus (Day+)	//-> Added 07/26/2004.
*/

enum Subtype : DWORD
{
	ST_REGULAR_STOP,
	ST_TRAILING_STOP_BID = 1,
	ST_TRAILING_STOP_ASK,
	ST_TRAILING_STOP_MIDPOINT,
	ST_TRAILING_STOP_LAST,
	ST_SYNTHETIC_STOP_BID,
	ST_SYNTHETIC_STOP_ASK,
	ST_SYNTHETIC_STOP_MIDPOINT,
	ST_SYNTHETIC_STOP_LAST,

	ST_URGENCY_DARK    = 100,
	ST_URGENCY_LOW,
	ST_URGENCY_MEDIUM,
	ST_URGENCY_HIGH,
	ST_URGENCY_GETDONE,

	ST_CLOSE = 0x100,
};

//TODO // *AK* Yeah, it should be cleaned up
//Route codes - for TR_MSG
#define NULL_ROUTE				0x0			// Invalid or illegal system type
#define NSDQ_FIX_ROUTE			0x00000001	// NASDAQ FIX
#define IEX_ROUTE			0x00000002
#define CVGX_ROUTE				0x00000004  // ConvergEx
//#define SPEED_MID_DARK_ROUTE	0x00000004	// NASDAQ RUSH ROUTE
#define AMEX_ROUTE				0x00000008	// AMEX ROUTE
#define BATS_ROUTE				0x00000010	// BATS ROUTE
#define EDGX_ROUTE				0x00000020	// Direct Edge
#define NYSE_ROUTE				0x00000040  // NYSE ROUTE
#define ARCA_ROUTE				0x00000080  // ARCA ROUTE
//#define BTRD_ROUTE				0x00000100  // BTRD ROUTE
//#define BARX_ROUTE				0x00000100  // BARX ROUTE
//#define SPEED_FREE_DARK_ROUTE	0x00000100
//#define TRAC_ROUTE				0x00000200  // TRAC ROUTE
#define CITADEL_ROUTE			0x00000100  // Citadel ROUTE
#define UBS_ROUTE				0x00000200  // UBS ROUTE
#define NITE_ROUTE				0x00000400  // Knight route
#define GSCO_SIGMA_X_ROUTE		0x00000800//dark pool
#define CSFB_CROSSFINDER		0x00001000//dark pool
#define BATY_ROUTE				0x00002000	// BATY ROUTE

#define EDGA_ROUTE				0x00004000	// Direct EdgeA
#define NSEX_ROUTE				0x00008000	// NSX
#define CHSX_ROUTE				0x00010000	// MWSE (Chicago Stock Exchange)
//#define	CBOE_ROUTE				0x00020000	// CBOE (Chicago Board of Options Exchange) (CBSX)
#define	PHLX_ROUTE				0x00040000	// NASDAQ PHLX
#define	BOSX_ROUTE				0x00080000	// NASDAQ BOSX
#define FLOW_ROUTE				0x00100000	// LAVA FLOW Dark Pool
#define PDQ_ROUTE				0x00200000	// BNY ConvergEx - VortEx Dark Pool
#define LEVEL_ROUTE				0x00400000	// NYFIX Millennium Dark Pool
//#define NYFX_ROUTE				0x00800000	// NYFIX Broker Routing
#define ITG_ROUTE				0x00800000	// NYFIX Broker Routing
//#define NEXA_ROUTE				0x01000000  // NEXA - PTSI( Penson )
#define JPM_ROUTE				0x01000000
#define SPEED_ROUTE				0x02000000 
#define LSTK_ROUTE				0x04000000	// LOCATE STOCK
#define FI_SMART_ROUTE			0x08000000	// MANTARA Smart Routes (XWAY)
#define QED_ROUTE				0x10000000  // QED Route (internal use) - MatchServer
/*
#define RISK_ROUTE				0x10000000  // Risk Management Server (internal use)
#define DROP_COPY_ROUTE			0x20000000  // DROP COPY (internal use)
#define DB_LOGGER_ROUTE			0x40000000  // DB Logger (internal use)
#define AUTO_ROUTE				0x80000000  // AUTO ROUTE
*/

#ifndef TAKION_NO_OPTIONS
#define ISEX_ROUTE				0x00000101
#define MISE_ROUTE				0x00000102
#define C2_ROUTE				0x00000103
#define BOX_ROUTE				0x00000104
#define GEM_ROUTE				0x00000105
#define	CBOE_ROUTE_OPT			0x00000106	// CBOE - for Options Only
#endif

// Order Status
#define OS_NONPENDING			0x0			// No longer pending (canceled, filled, rejected)
#define OS_NEW					0x1			// New Order
#define OS_PENDING_CANCEL		0x2

// Tracking
#define TR_ON_CLIENT			0x0			// Order is on client
#define TR_ON_SERVER			0x1			// Order is on server
#define TR_ON_DRIVER			0x2			// Order is on venue driver
#define TR_ON_MARKET			0x3			// Order is on market

// ExecInst bit field, should be mapped to FIX values in FIX driver
#define EI_STAY_ON_OFFERSIDE			0x00000001	// '0' = Stay on offerside
#define EI_NOT_HELD						0x00000002	// '1' = Not held
#define EI_WORK							0x00000004	// '2' = Work
#define EI_GO_ALONG						0x00000008	// '3' = Go along
#define EI_OVER_THE_DAY					0x00000010	// '4' = Over the day
#define EI_HELD							0x00000020	// '5' = Held
#define EI_PARTICIPATE_DONT_INITIATE	0x00000040	// '6' = Participate don't initiate
#define EI_STRICT_SCALE					0x00000080	// '7' = Strict scale
#define EI_TRY_TO_SCALE					0x00000100	// '8' = Try to scale
#define EI_STAY_ON_BIDSIDE				0x00000200	// '9' = Stay on bidside
#define EI_NO_CROSS						0x00000400	// 'A' = No cross (cross is forbidden)
#define EI_OK_TO_CROSS					0x00000800	// 'B' = OK to cross
#define EI_CALL_FIRST					0x00001000	// 'C' = Call first
#define EI_PERCENT_OF_VOLUME			0x00002000	// 'D' = Percent of volume (indicates that the sender does not want to be all of the volume on the floor vs. a specific percentage)
#define EI_DNI							0x00004000	// 'E' = Do not increase - DNI
#define EI_DNR							0x00008000	// 'F' = Do not reduce - DNR
#define EI_AON							0x00010000	// 'G' = All or none - AON
#define EI_INSTITUTIONS_ONLY			0x00020000	// 'I' = Institutions only
#define EI_LAST_PEG						0x00040000	// 'L' = Last peg (last sale)
#define EI_MIDPRICE_PEG					0x00080000	// 'M' = Mid-price peg (midprice of inside quote)
#define EI_NON_NEGOTIABLE				0x00100000	// 'N' = Non-negotiable
#define EI_OPENING_PEG					0x00200000	// 'O' = Opening peg
#define EI_MARKET_PEG					0x00400000	// 'P' = Market peg
#define EI_PRIMARY_PEG					0x00800000	// 'R' = Primary peg (primary market - buy at bid/sell at offer)
#define EI_SUSPEND						0x01000000	// 'S' = Suspend
#define EI_INTERMARKET_SWEEP			0x02000000	// 'f' = Intermarket Sweep (BATS)
#define EI_FIXED_PEG					0x04000000	// 'T' = Fixed Peg to Local best bid or offer at time of order
#define EI_CUSTOMER_DISPLAY_INSTRUCTION	0x08000000	// 'U' = Customer Display Instruction (Rule11Ac1-1/4)
#define EI_NETTING						0x10000000	// 'V' = Netting (for Forex)
#define EI_PEG_TO_VWAP					0x20000000	// 'W' = Peg to VWAP
#define EI_IMBALANCE_ONLY				0x40000000  // 'i' = NASDAQ Imbalance Only Orders
#define EI_PEG_TO_LIMIT_PRICE			0x80000000	// 'd' = PegToLimitPrice (used by ARCA for Tracking Orders)

#define EI_PEG_MASK						( EI_LAST_PEG | EI_MIDPRICE_PEG | EI_OPENING_PEG | EI_MARKET_PEG | EI_PRIMARY_PEG | EI_FIXED_PEG | EI_PEG_TO_VWAP | EI_PEG_TO_LIMIT_PRICE )

/*
// Subtype: additional ExecInst flags
#define ST_BATS_DART					0x00000001	// 'u' = BATS+DART (BATS)
#define ST_BATS_FORCE_DART				0x00000002	// 'v' = Force DART (BATS)
#define ST_BATS_DONT_DART				0x00000004	// 'w' = Do Not DART (BATS)
*/
//RoutingInstructions
enum Routing : unsigned int
{
	RI_NONE					= 0,
	
	RI_PROACTIVE,
	RI_PROACTIVE_DMA,

	RI_BATS_ADD_LIQUIDITY_ONLY = 20,
	RI_BATS_DART,
	RI_BATS_FORCE_DART,
	RI_BATS_CYCLE,
	RI_BATS_PARALLEL_D,
	RI_BATS_TRIM,
	RI_BATS_TRIM_MINUS,
	RI_BATS_SLIM,
	RI_BATS_SLIM_PLUS,
	RI_BATS_PARALLEL_T,
	RI_BATS_PARALLEL_2D,

	RI_EDGE_ADD_LIQUIDITY_ONLY = 40,
	RI_EDGE_RDOT,
	RI_EDGE_RDOX,
	RI_EDGE_ROBA,
	RI_EDGE_ROBX,
	RI_EDGE_ROPA,
	RI_EDGE_ROLF,
	RI_EDGE_INET,
	RI_EDGE_ROUT,
	RI_EDGE_ROUD,
	RI_EDGE_ROUC,
	RI_EDGE_ROUE,
	RI_EDGE_ROUX,
	RI_EDGE_ROUQ,
	RI_EDGE_ROUZ,

	RI_ARCA_ADD_LIQUIDITY_ONLY = 70,
	RI_ARCA_PASSIVE_LIQUIDITY,

	RI_NSDQ_ADD_LIQUIDITY_ONLY = 100,
	RI_NSDQ_SCAN,
	RI_NSDQ_STGY,
	RI_NSDQ_SKIP,
	RI_NSDQ_SKNY,
	RI_NSDQ_LIST,
	RI_NSDQ_CART,
	RI_NSDQ_SAVE,
	RI_NSDQ_QSAV,
	RI_NSDQ_SOLV,
	RI_NSDQ_TFTY,
	RI_NSDQ_QTFY,
	RI_NSDQ_DOTA,
	RI_NSDQ_DOTM,
	RI_NSDQ_DOTI,
	RI_NSDQ_DOTZ,
	RI_NSDQ_MOPP,
	RI_NSDQ_DOTD,
	RI_NSDQ_DARK,
	RI_NSDQ_COST,

	RI_NYSE_CLOSING_OFFSET = 130,

	RI_NITE_FAN = 160,
	RI_NITE_FAN_AGGRESSIVE,
	RI_NITE_FAN_AGGRESSIVE_PLUS,
	RI_NITE_FAN_PASSIVE,
	RI_NITE_FAN_PASSIVE_PLUS,
	RI_NITE_COVERT,
	RI_NITE_COVERT_AGGRESSIVE,
	RI_NITE_COVERT_AGGRESSIVE_PLUS,
	RI_NITE_COVERT_PASSIVE,
	RI_NITE_COVERT_PASSIVE_PLUS,
	RI_NITE_OASIS,
	RI_NITE_SUMO_AGGRESSIVE,
	RI_NITE_SUMO_MORE_AGGRESSIVE,
	RI_NITE_SUMO_AGGRESSIVE_PLUS,
	RI_NITE_PRIMARY,
	RI_NITE_FAN_R,
	RI_NITE_FAN_R_AGGRESSIVE,
	RI_NITE_FAN_R_AGGRESSIVE_PLUS,
	RI_NITE_FAN_R_PASSIVE,
	RI_NITE_FAN_R_PASSIVE_PLUS,
	RI_NITE_ARCA_DMA,
	RI_NITE_GETCO,

	RI_NSX_ADD_LIQUIDITY_ONLY = 200,

//	RI_NEXA_MNGD = 230,
	RI_JPM_AQUA = 230,
	RI_JPM_JPMCROSS,
	RI_JPM_CUSTOM1,
	RI_JPM_CUSTOM2,
	RI_JPM_SOR_POST,
	RI_JPM_SOR_STEALTH,
	RI_JPM_SOR_CUSTOM,

	RI_BARX_VWAP = 300,
	RI_BARX_WITH_VOLUME,
	RI_BARX_TWAP,
	RI_BARX_SMARTX,
	RI_BARX_ARCA,
	RI_BARX_NSDQ,

	RI_UBS_TAPNOW = 400,

	RI_CSFB_NEUTRAL    = 500, // Peg to Midpoint (default)
	RI_CSFB_AGGRESSIVE,     // Peg to Market
	RI_CSFB_PASSIVE,     // Peg to Primary
	RI_CSFB_PATHFINDER,
	RI_CSFB_BLAST,

	RI_SIGMA_ATS    = 600,
	RI_SIGMA_X_PING,

	RI_PDQ_MIDPOINT_GET = 700,
	RI_PDQ_ARCA_VALUE,
	RI_PDQ_BATS_VALUE,
	RI_PDQ_EDGX_VALUE,
	RI_PDQ_NSDQ_VALUE,
 	RI_PDQ_SAVE1,
	RI_PDQ_SAVE2,
	RI_PDQ_SAVEWORK,
	RI_PDQ_FREE,
	RI_PDQ_ZAPP,
	RI_PDQ_DARKALL,
	RI_PDQ_FREEPAIR,
	RI_PDQ_PCBSX,
	RI_PDQ_BATY_VALUE,
	RI_PDQ_FLOW,
	RI_PDQ_PNSX,
//	RI_PDQ_NYSE_VALUE,

	RI_SPEEDROUTE_FREE_DARK = 800,
	RI_SPEEDROUTE_MIDPOINT_DARK,
	RI_SPEEDROUTE_FAN_AGGRESSIVE,

	RI_SPEEDROUTE_KROUTE = 807,

	RI_CITADEL_MERCURY_DARK	= 900,
	RI_CITADEL_MARKET_ACCESS,

	RI_CONVERGEX_NIX = 1000,	// Can be DAY, IOC, MOO, LOO, MOC, LOC, GTX, Market, Limit
	RI_CONVERGEX_VORTEX,		// Can be DAY, IOC, Market, Limit, Peg (Mid, Market, Primary)
	RI_CONVERGEX_PBOX,			// Can be IOC, Market, Limit
	RI_CONVERGEX_MILLENNIUM,	// Day orders only, Market, Limit, Peg (Open, Last, Mid, Market, Primary)
		
	RI_Count
};


//#define ORDER_STRUCTURE_MEMBER
#define ORDER_RESPONSE_FULL

#ifdef ORDER_STRUCTURE_MEMBER
class TMessageOrderHeader
#else
class TMessageOrderHeader : public TMessageTime
#endif
{
public:
	DWORD		MessageSequenceNumber;
	DWORD		ClOrdID;							//Client assigned order id, I think it is ok to have this as a number instead of string for faster search
	DWORD		ParentClOrdID;
	DWORD		SrOrdID;							// Server assigned order id, server will use a number as well
	char		AccountName[MAX_ACCOUNT_SIZE];		//Order Account Name

// *AK* start
	char		TraderID[MAX_TRADER_ID_SIZE];
	char		FirmID[MAX_FIRM_ID_SIZE];
	DWORD		AcceptedTime;						// When order was accepted by market
	DWORD		CanceledTime;						// When order has been canceled if any
	char		MarketReferenceID[MAX_MARKET_REFERENCE_ID];		// Will be filled with Venue's OrderID
	unsigned char		Tracking;							// Where order is, on server, on market, etc.
	unsigned char		Status;								// New, Partially filled, Canceled, Filled
	char		ConfirmationID[16];					// can be used for short sells. ID from liquidity finder
	ULONG		Quantity;							// Order quantity ( moved from order )
	ULONG		RemainingQuantity;					// Remaining size of the order ( moved from order )
	ULONG		CanceledQuantity;					// Canceled size of the order
// *AK* end

	char		Symbol[MAX_SYMBOL_SIZE];
	UCHAR		RealTimeOrRecovered;				//Weather this a current message or recovered message
	DWORD		Time;								//Milliseconds since midnight, when this message is generated
	DWORD		Ip;									//For Compliance

	UCHAR		Side;
	UCHAR		InstrumentType;

#ifndef ORDER_STRUCTURE_MEMBER
protected:
#endif
	TMessageOrderHeader(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,
#ifndef ORDER_STRUCTURE_MEMBER
		unsigned short type, unsigned short length,
#endif
		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_CLIENT,
		unsigned char status = OS_NEW,
		unsigned __int64 optionBlock = 0,//const char* confirmationID = "",
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
	#ifndef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, type, length),
	#endif
		MessageSequenceNumber(messageSequenceNumber),
		ClOrdID(clientOrdID),
		ParentClOrdID(parentClOrdID),
		SrOrdID(serverOrdID),
		AcceptedTime(acceptedTime),
		CanceledTime(canceledTime),
		Tracking(tracking),
		Status(status),
		Quantity(quantity),
		RemainingQuantity(remainingQuantity),
		CanceledQuantity(canceledQuantity),
		RealTimeOrRecovered(realTimeOrRecovered),
	#ifndef ORDER_STRUCTURE_MEMBER
		Time(m_time),
	#endif
		Ip(ip),
		Side(side),
		InstrumentType(instrumentType)
	{
	#ifdef ORDER_STRUCTURE_MEMBER
		Time = TL_GetCurrentMillisecond();
	#endif
		U_CopyAndPad(AccountName, sizeof(AccountName), accountName, '\0');
		U_CopyAndPad(TraderID, sizeof(TraderID), traderId, '\0');
		U_CopyAndPad(FirmID, sizeof(FirmID), firmId, '\0');
		U_CopyAndPad(MarketReferenceID, sizeof(MarketReferenceID), marketReferenceID, '\0');
//		U_CopyAndPad(ConfirmationID, sizeof(ConfirmationID), confirmationID, '\0');
		*(unsigned __int64*)ConfirmationID = optionBlock;
		*((unsigned __int64*)ConfirmationID + 1) = 0;
		U_CopyAndPad(Symbol, sizeof(Symbol), symbol, '\0');
	}
};

#ifdef ORDER_STRUCTURE_MEMBER
class TMessageOrderBase : public TMessageTime
#else
class TMessageOrderBase : public TMessageOrderHeader
#endif
//class TMsgReqOrder : public TMessageOrderHeader
{
public:
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
	DWORD		Date;							// Date for good till date orders

	UCHAR		Type;							// Order type, market, limit, etc
	UCHAR		TIF;							// TIF or Order duration 

	ULONG		MinQuantity;					// Minimum quantity to process order
												// if equals quantity, then all or nothing
	ULONG		DisplayQuantity;				// Reserve order display quantity

	UCHAR		QuantityType;					// Quantity type that generated the above qty
	UCHAR		PriceType;						// Price type that generated the above price

	DWORD		Route;							// Routes to send order to 
	DWORD		ExcludeRoutes;					// Routes to exclude when executing order.
	DWORD		DefaultRoutes;					// Single ROUTE to default to for execution.

	UCHAR		TicketCount;					// Number of orders that is part of the
												// same ticket counted down.
	USHORT		TicketID;						// Ticket ID assigned by client.

	unsigned int LastPriceDollar;						// Last bid/ask price 
	unsigned int LastPriceFraction;						// Last bid/ask price

	unsigned int BidPriceDollar;						// Latest bid price
	unsigned int BidPriceFraction;						// Latest bid price

	unsigned int AskPriceDollar;						// Latest ask price
	unsigned int AskPriceFraction;						// Latest ask price

	unsigned int LimitPriceDollar;						// Limit price
	unsigned int LimitPriceFraction;						// Limit price

	int StopPriceDollar;						// Stop price 
	int StopPriceFraction;						// Stop price 

	unsigned int AuxPriceDollar;						// For discretionary and scaled orders
	unsigned int AuxPriceFraction;						// For discretionary and scaled orders
// *AK* start
	DWORD		SubType;						// Additional Flags for Order, like type of peg...
	DWORD		ExecInst;						// Execution Instructions
	DWORD		RoutingInstructions;			// Routing Instructions to direct venue whether to route order out and where

	unsigned int DisplayPriceDollar;					// Also can be used for discretionary orders
	unsigned int DisplayPriceFraction;					// Also can be used for discretionary orders
	
	ULONG		ReserveQuantity;				// Reserve size
	ULONG		RefreshQuantity;				// Refresh size
	ULONG		DiscretionQuantity;				// Discretion size
	DWORD		ExpireTime;						// Number of milliseconds before order should expire (for TIF = '6')
	DWORD		EffectiveTime;					// When order should become active
	char		Capacity;						// Agency, principal, etc.
// *AK* end
	char		market_maker[MAX_MMID_SIZE];	// Market maker ID string, don't know whether we need it...
protected:
//	TS_ORDER_MSG_HEADER		Header;
	TMessageOrderBase(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD route,							// Routes to send order to 
		DWORD ip,

		unsigned short type, unsigned short length,

		unsigned char orderType = ORDER_TYPE_MARKET,
		unsigned int limitPriceDollar = 0,						// Limit price
		unsigned int limitPriceFraction = 0,					// Limit price

		unsigned char tifType = TIF_DAY,

		unsigned int expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		unsigned int effectiveTime = 0,					// When order should become active
//?
		char capacity = 0,						// Agency, principal, etc.

		const char* mm = "",	// Market maker ID string, don't know whether we need it...

		int stopPriceDollar = 0,						// Stop price 
		int stopPriceFraction = 0,						// Stop price 

		unsigned long minQuantity = 0,
		unsigned long displayQuantity = 0,				// Reserve order display quantity
		unsigned char quantityType = 0,					// Quantity type that generated the above qty
		unsigned long reserveQuantity = 0,				// Reserve size
		unsigned long refreshQuantity = 0,				// Refresh size
		unsigned long discretionQuantity = 0,				// Discretion size


		unsigned char priceType = 0,						// Price type that generated the above price

		unsigned int displayPriceDollar = 0,					// Also can be used for discretionary orders
		unsigned int displayPriceFraction = 0,					// Also can be used for discretionary orders

		unsigned int lastPriceDollar = 0,						// Last bid/ask price 
		unsigned int lastPriceFraction = 0,						// Last bid/ask price

		unsigned int bidPriceDollar = 0,						// Latest bid price
		unsigned int bidPriceFraction = 0,						// Latest bid price

		unsigned int askPriceDollar = 0,						// Latest ask price
		unsigned int askPriceFraction = 0,						// Latest ask price

		unsigned int auxPriceDollar = 0,						// For discretionary and scaled orders
		unsigned int auxPriceFraction = 0,						// For discretionary and scaled orders

		unsigned int date = 0,
		DWORD excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
		DWORD defaultRoutes = NULL_ROUTE,					// Single ROUTE to default to for execution.
		unsigned char ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		unsigned short ticketID = 0,						// Ticket ID assigned by client.

// *AK* start
		DWORD subType = 0,						// Additional Flags for Order, like type of peg...
		DWORD execInst = 0,						// Execution Instructions
		DWORD routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_CLIENT,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
	#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER, sizeof(TMsgReqOrder)),
		m_header(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip),
	#else
		TMessageOrderHeader(clientOrdID, traderId, accountName, firmId, 
			symbol,
			side,
			quantity,
			ip,
			type, length,
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
	#endif
		Date(date),
		Type(orderType),
		TIF(tifType),
		MinQuantity(minQuantity),
		DisplayQuantity(displayQuantity),
		QuantityType(quantityType),
		PriceType(priceType),
		Route(route),
		ExcludeRoutes(excludeRoutes),
		DefaultRoutes(defaultRoutes),
		TicketCount(ticketCount),
		TicketID(ticketID),
		LastPriceDollar(lastPriceDollar),
		LastPriceFraction(lastPriceFraction),
		BidPriceDollar(bidPriceDollar),
		BidPriceFraction(bidPriceFraction),
		AskPriceDollar(askPriceDollar),
		AskPriceFraction(askPriceFraction),
		LimitPriceDollar(limitPriceDollar),
		LimitPriceFraction(limitPriceFraction),
		StopPriceDollar(stopPriceDollar),
		StopPriceFraction(stopPriceFraction),
		AuxPriceDollar(auxPriceDollar),
		AuxPriceFraction(auxPriceFraction),
		SubType(subType),
		ExecInst(execInst),
		RoutingInstructions(routingInstructions),
		DisplayPriceDollar(displayPriceDollar),
		DisplayPriceFraction(displayPriceFraction),
		ReserveQuantity(reserveQuantity),
		RefreshQuantity(refreshQuantity),
		DiscretionQuantity(discretionQuantity),
		ExpireTime(expireTime),
		EffectiveTime(effectiveTime),
		Capacity(capacity)
	{
		U_CopyAndPad(market_maker, sizeof(market_maker) - 1, mm ? mm : "", '\0');
		market_maker[sizeof(market_maker) - 1] = '\0';
	}
};

class TMsgReqOrder : public TMessageOrderBase
{
public:
//	TS_ORDER_MSG_HEADER		Header;
	TMsgReqOrder(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD route,							// Routes to send order to 
		DWORD ip,

		unsigned char orderType = ORDER_TYPE_MARKET,
		unsigned int limitPriceDollar = 0,						// Limit price
		unsigned int limitPriceFraction = 0,					// Limit price

		unsigned char tifType = TIF_DAY,

		unsigned int expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		unsigned int effectiveTime = 0,					// When order should become active
//?
		char capacity = 0,						// Agency, principal, etc.

		const char* mm = "",	// Market maker ID string, don't know whether we need it...

		int stopPriceDollar = 0,						// Stop price 
		int stopPriceFraction = 0,						// Stop price 

		unsigned long minQuantity = 0,
		unsigned long displayQuantity = 0,				// Reserve order display quantity
		unsigned char quantityType = 0,					// Quantity type that generated the above qty
		unsigned long reserveQuantity = 0,				// Reserve size
		unsigned long refreshQuantity = 0,				// Refresh size
		unsigned long discretionQuantity = 0,				// Discretion size


		unsigned char priceType = 0,						// Price type that generated the above price

		unsigned int displayPriceDollar = 0,					// Also can be used for discretionary orders
		unsigned int displayPriceFraction = 0,					// Also can be used for discretionary orders

		unsigned int lastPriceDollar = 0,						// Last bid/ask price 
		unsigned int lastPriceFraction = 0,						// Last bid/ask price

		unsigned int bidPriceDollar = 0,						// Latest bid price
		unsigned int bidPriceFraction = 0,						// Latest bid price

		unsigned int askPriceDollar = 0,						// Latest ask price
		unsigned int askPriceFraction = 0,						// Latest ask price

		unsigned int auxPriceDollar = 0,						// For discretionary and scaled orders
		unsigned int auxPriceFraction = 0,						// For discretionary and scaled orders

		unsigned int date = 0,
		DWORD excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
		DWORD defaultRoutes = NULL_ROUTE,					// Single ROUTE to default to for execution.
		unsigned char ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		unsigned short ticketID = 0,						// Ticket ID assigned by client.

// *AK* start
		DWORD subType = 0,						// Additional Flags for Order, like type of peg...
		DWORD execInst = 0,						// Execution Instructions
		DWORD routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_CLIENT,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
	TMessageOrderBase(clientOrdID, traderId, accountName, firmId,
		symbol,
		side,
		quantity,
		route,							// Routes to send order to 
		ip,
		TS_ORDER, sizeof(TMsgReqOrder),

		orderType,
		limitPriceDollar,						// Limit price
		limitPriceFraction,					// Limit price

		tifType,

		expireTime,						// Number of milliseconds before order should expire (for TIF = '6')
		effectiveTime,					// When order should become active
//?
		capacity,						// Agency, principal, etc.

		mm,	// Market maker ID string, don't know whether we need it...

		stopPriceDollar,						// Stop price 
		stopPriceFraction,						// Stop price 

		minQuantity,
		displayQuantity,				// Reserve order display quantity
		quantityType,					// Quantity type that generated the above qty
		reserveQuantity,				// Reserve size
		refreshQuantity,				// Refresh size
		discretionQuantity,				// Discretion size


		priceType,						// Price type that generated the above price

		displayPriceDollar,					// Also can be used for discretionary orders
		displayPriceFraction,					// Also can be used for discretionary orders

		lastPriceDollar,						// Last bid/ask price 
		lastPriceFraction,						// Last bid/ask price

		bidPriceDollar,						// Latest bid price
		bidPriceFraction,						// Latest bid price

		askPriceDollar,						// Latest ask price
		askPriceFraction,						// Latest ask price

		auxPriceDollar,						// For discretionary and scaled orders
		auxPriceFraction,						// For discretionary and scaled orders

		date,
		excludeRoutes,					// Routes to exclude when executing order.
		defaultRoutes,					// Single ROUTE to default to for execution.
		ticketCount,					// Number of orders that is part of the
												// same ticket counted down.
		ticketID,						// Ticket ID assigned by client.

// *AK* start
		subType,						// Additional Flags for Order, like type of peg...
		execInst,						// Execution Instructions
		routingInstructions,			// Routing Instructions to direct venue whether to route order out and where

		messageSequenceNumber,
		serverOrdID,
		parentClOrdID,
		acceptedTime,
		canceledTime,
		marketReferenceID,
		tracking,
		status,
		optionBlock,//confirmationID,
		remainingQuantity,
		canceledQuantity,
		realTimeOrRecovered,
		instrumentType
	)
	{}
};

class TMsgOrderError : public TMessageOrderBase
{
public:
	TMsgOrderError(const TMessageOrderBase& orderBase, unsigned char errorCode, const unsigned __int64& userOrderId, const Money& moneyValue = Money(), const Money& moneyConstraint = Money(), unsigned int uintValue = 0, unsigned int uintConstraint = 0):
		TMessageOrderBase(orderBase),
		m_errorCode(errorCode),
		m_userOrderId(userOrderId),
		m_moneyValue(moneyValue),
		m_moneyConstraint(moneyConstraint),
		m_uintValue(uintValue),
		m_uintConstraint(uintConstraint)
	{
		m_type = TM_ORDER_ERROR;
		m_length = sizeof(TMsgOrderError);
	}
	unsigned char m_errorCode;
	unsigned __int64 m_userOrderId;
	Money m_moneyValue;
	Money m_moneyConstraint;
	unsigned int m_uintValue;
	unsigned int m_uintConstraint;
};

class TMsgCancelError : public TMessageOrderHeader
{
public:
	TMsgCancelError(const TMessageOrderHeader& orderHeader, unsigned char errorCode, const Money& moneyValue = Money(), const Money& moneyConstraint = Money(), unsigned int uintValue = 0, unsigned int uintConstraint = 0):
		TMessageOrderHeader(orderHeader),
		m_errorCode(errorCode),
		m_moneyValue(moneyValue),
		m_moneyConstraint(moneyConstraint),
		m_uintValue(uintValue),
		m_uintConstraint(uintConstraint)
	{
		m_type = TM_CANCEL_ERROR;
		m_length = sizeof(TMsgCancelError);
	}
	unsigned char m_errorCode;
	Money m_moneyValue;
	Money m_moneyConstraint;
	unsigned int m_uintValue;
	unsigned int m_uintConstraint;
};



#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderAck : public TMessageTime
#else
#ifdef ORDER_RESPONSE_FULL
class TMsgOrderAck : public TMessageOrderBase
#else
class TMsgOrderAck : public TMessageOrderHeader
#endif
#endif
{
public:
	TMsgOrderAck(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,

#ifdef ORDER_RESPONSE_FULL
		DWORD route,							// Routes to send order to 
#endif
		DWORD ip,

#ifdef ORDER_RESPONSE_FULL
		unsigned char orderType = ORDER_TYPE_MARKET,
		unsigned int limitPriceDollar = 0,						// Limit price
		unsigned int limitPriceFraction = 0,					// Limit price

		unsigned char tifType = TIF_DAY,

		unsigned int expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		unsigned int effectiveTime = 0,					// When order should become active
//?
		char capacity = 0,						// Agency, principal, etc.

		const char* mm = "",	// Market maker ID string, don't know whether we need it...

		int stopPriceDollar = 0,						// Stop price 
		int stopPriceFraction = 0,						// Stop price 

		unsigned long minQuantity = 0,
		unsigned long displayQuantity = 0,				// Reserve order display quantity
		unsigned char quantityType = 0,					// Quantity type that generated the above qty
		unsigned long reserveQuantity = 0,				// Reserve size
		unsigned long refreshQuantity = 0,				// Refresh size
		unsigned long discretionQuantity = 0,				// Discretion size


		unsigned char priceType = 0,						// Price type that generated the above price

		unsigned int displayPriceDollar = 0,					// Also can be used for discretionary orders
		unsigned int displayPriceFraction = 0,					// Also can be used for discretionary orders

		unsigned int lastPriceDollar = 0,						// Last bid/ask price 
		unsigned int lastPriceFraction = 0,						// Last bid/ask price

		unsigned int bidPriceDollar = 0,						// Latest bid price
		unsigned int bidPriceFraction = 0,						// Latest bid price

		unsigned int askPriceDollar = 0,						// Latest ask price
		unsigned int askPriceFraction = 0,						// Latest ask price

		unsigned int auxPriceDollar = 0,						// For discretionary and scaled orders
		unsigned int auxPriceFraction = 0,						// For discretionary and scaled orders

		unsigned int date = 0,
		DWORD excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
		DWORD defaultRoutes = NULL_ROUTE,					// Single ROUTE to default to for execution.
		unsigned char ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		unsigned short ticketID = 0,						// Ticket ID assigned by client.

// *AK* start
		DWORD subType = 0,						// Additional Flags for Order, like type of peg...
		DWORD execInst = 0,						// Execution Instructions
		DWORD routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where
#endif

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_SERVER,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_ACK, sizeof(TMsgOrderAck)),
		m_header(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip)
#else
#ifdef ORDER_RESPONSE_FULL
		TMessageOrderBase(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			route,							// Routes to send order to 
			ip,
			TS_ORDER_ACK, sizeof(TMsgOrderAck),

			orderType,
			limitPriceDollar,						// Limit price
			limitPriceFraction,					// Limit price

			tifType,

			expireTime,						// Number of milliseconds before order should expire (for TIF = '6')
			effectiveTime,					// When order should become active
	//?
			capacity,						// Agency, principal, etc.

			mm,	// Market maker ID string, don't know whether we need it...

			stopPriceDollar,						// Stop price 
			stopPriceFraction,						// Stop price 

			minQuantity,
			displayQuantity,				// Reserve order display quantity
			quantityType,					// Quantity type that generated the above qty
			reserveQuantity,				// Reserve size
			refreshQuantity,				// Refresh size
			discretionQuantity,				// Discretion size


			priceType,						// Price type that generated the above price

			displayPriceDollar,					// Also can be used for discretionary orders
			displayPriceFraction,					// Also can be used for discretionary orders

			lastPriceDollar,						// Last bid/ask price 
			lastPriceFraction,						// Last bid/ask price

			bidPriceDollar,						// Latest bid price
			bidPriceFraction,						// Latest bid price

			askPriceDollar,						// Latest ask price
			askPriceFraction,						// Latest ask price

			auxPriceDollar,						// For discretionary and scaled orders
			auxPriceFraction,						// For discretionary and scaled orders

			date,
			excludeRoutes,					// Routes to exclude when executing order.
			defaultRoutes,					// Single ROUTE to default to for execution.
			ticketCount,					// Number of orders that is part of the
													// same ticket counted down.
			ticketID,						// Ticket ID assigned by client.

	// *AK* start
			subType,						// Additional Flags for Order, like type of peg...
			execInst,						// Execution Instructions
			routingInstructions,			// Routing Instructions to direct venue whether to route order out and where

			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#else
		TMessageOrderHeader(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_ACK, sizeof(TMsgOrderAck),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#endif
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
#ifdef ORDER_RESPONSE_FULL
	TMessageOrderBase m_header;
#else
	TMessageOrderHeader m_header;
#endif
#endif
};

// *AK* start
//TS->TSClient, Sent by TS upon accepting the new order TS_ORDER_MESSAGE or any updates to old order
#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderUpdate : public TMessageTime
#else
#ifdef ORDER_RESPONSE_FULL
class TMsgOrderUpdate : public TMessageOrderBase
#else
class TMsgOrderUpdate : public TMessageOrderHeader
#endif
#endif
{
public:
	TMsgOrderUpdate(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
#ifdef ORDER_RESPONSE_FULL
		DWORD route,							// Routes to send order to 
#endif
		DWORD ip,

#ifdef ORDER_RESPONSE_FULL
		unsigned char orderType = ORDER_TYPE_MARKET,
		unsigned int limitPriceDollar = 0,						// Limit price
		unsigned int limitPriceFraction = 0,					// Limit price

		unsigned char tifType = TIF_DAY,

		unsigned int expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		unsigned int effectiveTime = 0,					// When order should become active
//?
		char capacity = 0,						// Agency, principal, etc.

		const char* mm = "",	// Market maker ID string, don't know whether we need it...

		int stopPriceDollar = 0,						// Stop price 
		int stopPriceFraction = 0,						// Stop price 

		unsigned long minQuantity = 0,
		unsigned long displayQuantity = 0,				// Reserve order display quantity
		unsigned char quantityType = 0,					// Quantity type that generated the above qty
		unsigned long reserveQuantity = 0,				// Reserve size
		unsigned long refreshQuantity = 0,				// Refresh size
		unsigned long discretionQuantity = 0,				// Discretion size


		unsigned char priceType = 0,						// Price type that generated the above price

		unsigned int displayPriceDollar = 0,					// Also can be used for discretionary orders
		unsigned int displayPriceFraction = 0,					// Also can be used for discretionary orders

		unsigned int lastPriceDollar = 0,						// Last bid/ask price 
		unsigned int lastPriceFraction = 0,						// Last bid/ask price

		unsigned int bidPriceDollar = 0,						// Latest bid price
		unsigned int bidPriceFraction = 0,						// Latest bid price

		unsigned int askPriceDollar = 0,						// Latest ask price
		unsigned int askPriceFraction = 0,						// Latest ask price

		unsigned int auxPriceDollar = 0,						// For discretionary and scaled orders
		unsigned int auxPriceFraction = 0,						// For discretionary and scaled orders

		unsigned int date = 0,
		DWORD excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
		DWORD defaultRoutes = NULL_ROUTE,					// Single ROUTE to default to for execution.
		unsigned char ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		unsigned short ticketID = 0,						// Ticket ID assigned by client.

// *AK* start
		DWORD subType = 0,						// Additional Flags for Order, like type of peg...
		DWORD execInst = 0,						// Execution Instructions
		DWORD routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where
#endif
		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_MARKET,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_UPDATE, sizeof(TMsgOrderUpdate)),
		m_header(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip)
#else
#ifdef ORDER_RESPONSE_FULL
		TMessageOrderBase(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			route,							// Routes to send order to 
			ip,
			TS_ORDER_UPDATE, sizeof(TMsgOrderUpdate),

			orderType,
			limitPriceDollar,						// Limit price
			limitPriceFraction,					// Limit price

			tifType,

			expireTime,						// Number of milliseconds before order should expire (for TIF = '6')
			effectiveTime,					// When order should become active
	//?
			capacity,						// Agency, principal, etc.

			mm,	// Market maker ID string, don't know whether we need it...

			stopPriceDollar,						// Stop price 
			stopPriceFraction,						// Stop price 

			minQuantity,
			displayQuantity,				// Reserve order display quantity
			quantityType,					// Quantity type that generated the above qty
			reserveQuantity,				// Reserve size
			refreshQuantity,				// Refresh size
			discretionQuantity,				// Discretion size


			priceType,						// Price type that generated the above price

			displayPriceDollar,					// Also can be used for discretionary orders
			displayPriceFraction,					// Also can be used for discretionary orders

			lastPriceDollar,						// Last bid/ask price 
			lastPriceFraction,						// Last bid/ask price

			bidPriceDollar,						// Latest bid price
			bidPriceFraction,						// Latest bid price

			askPriceDollar,						// Latest ask price
			askPriceFraction,						// Latest ask price

			auxPriceDollar,						// For discretionary and scaled orders
			auxPriceFraction,						// For discretionary and scaled orders

			date,
			excludeRoutes,					// Routes to exclude when executing order.
			defaultRoutes,					// Single ROUTE to default to for execution.
			ticketCount,					// Number of orders that is part of the
													// same ticket counted down.
			ticketID,						// Ticket ID assigned by client.

	// *AK* start
			subType,						// Additional Flags for Order, like type of peg...
			execInst,						// Execution Instructions
			routingInstructions,			// Routing Instructions to direct venue whether to route order out and where

			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#else
		TMessageOrderHeader(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_UPDATE, sizeof(TMsgOrderUpdate),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#endif
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
#ifdef ORDER_RESPONSE_FULL
	TMessageOrderBase m_header;
#else
	TMessageOrderHeader m_header;
#endif
#endif
};

//Order reject codes 
#define ORDER_REJECT_CODE_BAD_SYMBOL			1
#define	ORDER_REJECT_CODE_NO_OWN				2
#define ORDER_REJECT_CODE_SMALL_OWN				3
#define	ORDER_REJECT_CODE_ROUTE_UNAVAILABLE		4
#define	ORDER_REJECT_CODE_REJECTED_BY_ROUTE		5
#define	ORDER_REJECT_CODE_VALIDATION_FAILED		6
#define	ORDER_REJECT_CODE_BAD_TRADER_ID			7
#define	ORDER_REJECT_CODE_BAD_ACCOUNT			8
//TS->TSClient, Sent by TS if the new order TS_ORDER_MESSAGE is rejected


#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderReason : public TMessageTime
#else
class TMsgOrderReason : public TMessageOrderHeader
#endif
{
public:
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
	WORD					ReasonCode;			// Reject code
	char					ReasonText[1];		//	Reject String
protected:
	TMsgOrderReason(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,

		WORD reasonCode,
		unsigned short type, unsigned short length,

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_CLIENT,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, type, length),
		m_header(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip),
#else
		TMessageOrderHeader(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			type, length,
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
#endif
		ReasonCode(reasonCode)
	{
		*ReasonText = '\0';
	}
};

class TMsgOrderReject : public TMsgOrderReason
{
public:
	TMsgOrderReject(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,

		WORD rejectCode,

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_SERVER,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
		TMsgOrderReason(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			rejectCode,
			TS_ORDER_REJECT, sizeof(TMsgOrderReject),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
	{
	}
};

#define	CANCEL_REJECT_CODE_ROUTE_UNAVAILABLE	1
#define CANCEL_REJECT_TOO_LATE_TO_CANCEL		'0'
#define	CANCEL_REJECT_UNKNOWN_ORDER				'1'
#define CANCEL_REJECT_BROKER_OPTION				'2'
#define CANCEL_REJECT_ALREADY_PENDING_CANCEL	'3'

class TMsgCancelReject : public TMsgOrderReason
{
public:
	TMsgCancelReject(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,

		WORD rejectCode,

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_SERVER,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
		TMsgOrderReason(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			rejectCode,
			TS_CANCEL_REJECT, sizeof(TMsgCancelReject),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
	{
	}
};



#define	REPORT_FILLED			0x01	// Part or all of order filled
#define	REPORT_CANCELED			0x02	// Part or all of order canceled
#define	REPORT_NOFILLED			0x04	// Part or all of order not filled
#define	REPORT_REJECTED			0x08	// Part or all of order was rejected
#define	REPORT_TIMEOUT			0x10	// Order timed out
#define	REPORT_ACCEPTED			0x20	// Order accepted
#define	REPORT_BUSTED			0x40	// Execution busted
#define	REPORT_FOREIGN			0x80	// Execution foreign

#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderReport : public TMessageTime
#else
class TMsgOrderReport : public TMessageOrderHeader
#endif
{
public:
	TMsgOrderReport(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,

		WORD reportType,

		unsigned char liquidityFlag,			// 0 or 1 
		unsigned char billableFlag,			// 0 or 1 

		DWORD fillQuantity,			// # of shares filled
		DWORD nofillQuantity,			// # of shares not filled
		DWORD cancelQuantity,			// # of shares cancelled
		DWORD remainingQuantity,		// # of shares remaining in order
								
		unsigned int fillPriceDollar,				// Filled price	
		unsigned int fillPriceFraction,				// Filled price	
		const char* mmid,	// Market maker ID string - 5 bytes
		const char* executionReferenceID,	// ID assigned to execution by venue
		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_MARKET,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
//		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
	#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_REPORT, sizeof(TMsgOrderReport)),
		m_header(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip),
	#else
		TMessageOrderHeader(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_REPORT, sizeof(TMsgOrderReport),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID ,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
	#endif
		ReportType(reportType),

		LiquidityFlag(liquidityFlag),			// 0 or 1 
		BillableFlag(billableFlag),			// 0 or 1 

		FillQuantity(fillQuantity),			// # of shares filled
		NofillQuantity(nofillQuantity),			// # of shares not filled
		CancelQuantity(cancelQuantity),			// # of shares cancelled
		m_orderRemainingQuantity(remainingQuantity),		// # of shares remaining in order
								
		FillPriceDollar(fillPriceDollar),				// Filled price	
		FillPriceFraction(fillPriceFraction)				// Filled price	
	{
		U_CopyAndPad(MMID, sizeof(MMID), mmid, '\0');
		U_CopyAndPad(ExecutionReferenceID, sizeof(ExecutionReferenceID), executionReferenceID, '\0');
		*ReasonText = '\0';
	}
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
	WORD					ReportType;

	UCHAR					LiquidityFlag;			// 0 or 1 
	UCHAR					BillableFlag;			// 0 or 1 

	DWORD					FillQuantity;			// # of shares filled
	DWORD					NofillQuantity;			// # of shares not filled
	DWORD					CancelQuantity;			// # of shares cancelled
	DWORD					m_orderRemainingQuantity;		// # of shares remaining in order
								
	unsigned int			FillPriceDollar;				// Filled price	
	unsigned int			FillPriceFraction;				// Filled price	
	char					MMID[MAX_MMID_SIZE];	// Market maker ID string - 5 bytes
	char					ExecutionReferenceID[MAX_MARKET_REFERENCE_ID];	// ID assigned to execution by venue
	DWORD					Route;
	char					ReasonText[1];			// Reason msg string for rejections
};

#ifdef ORDER_STRUCTURE_MEMBER
class TMsgReqOrderCancel : public TMessageTime
#else
class TMsgReqOrderCancel : public TMessageOrderHeader
#endif
{
public:
	TMsgReqOrderCancel(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,
		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_MARKET,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_CANCEL_REQ, sizeof(TMsgReqOrderCancel)),
		m_header(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip)
#else
		TMessageOrderHeader(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_CANCEL_REQ, sizeof(TMsgReqOrderCancel),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
};

//TSClient->TS, Sent to replace an order
#ifdef ORDER_STRUCTURE_MEMBER
class TMsgReqOrderReplace : public TMessageTime
#else
class TMsgReqOrderReplace : public TMessageOrderHeader
#endif
{
public:
	TMsgReqOrderReplace(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned int oldQuantity,
		DWORD newClOrdID,
		unsigned int newQuantity,
		DWORD ip,

		unsigned char orderType = ORDER_TYPE_MARKET,

		unsigned int limitPriceDollar = 0,						// Limit price
		unsigned int limitPriceFraction = 0,					// Limit price

		int stopPriceDollar = 0,						// Stop price
		int stopPriceFraction = 0,						// Stop price

		unsigned int auxPriceDollar = 0,						// For discretionary and scaled orders
		unsigned int auxPriceFraction = 0,						// For discretionary and scaled orders

		unsigned int lastPriceDollar = 0,						// Last bid/ask price 
		unsigned int lastPriceFraction = 0,						// Last bid/ask price

		unsigned int bidPriceDollar = 0,						// Latest bid price
		unsigned int bidPriceFraction = 0,						// Latest bid price

		unsigned int askPriceDollar = 0,						// Latest ask price
		unsigned int askPriceFraction = 0,						// Latest ask price

		unsigned char tifType = TIF_DAY,

		unsigned long minQuantity = 0,
		unsigned long displayQuantity = 0,				// Reserve order display quantity

		DWORD date = 0,

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_MARKET,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_REPLACE_REQ, sizeof(TMsgReqOrderReplace)),
		m_header(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			oldQuantity,
			ip)
#else
		TMessageOrderHeader(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			oldQuantity,
			ip,
			TS_ORDER_REPLACE_REQ, sizeof(TMsgReqOrderReplace),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
		NewClOrdID(newClOrdID),
		Date(date),
		m_newType(orderType),
		m_newTIF(tifType),
		m_newQuantity(newQuantity),
		m_newMinQuantity(minQuantity),
		m_newDisplayQuantity(displayQuantity),
		m_newLimitPriceDollar(limitPriceDollar),
		m_newLimitPriceFraction(limitPriceFraction),
		m_newStopPriceDollar(stopPriceDollar),
		m_newStopPriceFraction(stopPriceFraction),
		m_newAuxPriceDollar(auxPriceDollar),
		m_newAuxPriceFraction(auxPriceFraction),
		LastPriceDollar(lastPriceDollar),
		LastPriceFraction(lastPriceFraction),
		BidPriceDollar(bidPriceDollar),
		BidPriceFraction(bidPriceFraction),
		AskPriceDollar(askPriceDollar),
		AskPriceFraction(askPriceFraction)
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
	DWORD NewClOrdID;

	DWORD Date;							// Date for good till date orders

	UCHAR m_newType;							// Order type, market, limit, etc
	UCHAR m_newTIF;							// TIF or Order duration 

	DWORD m_newQuantity;						// Order quantity
	ULONG m_newMinQuantity;					// Minimum quantity to process order
															// if equals quantity, then all or nothing
	ULONG m_newDisplayQuantity;				// Reserve order display quantity

	unsigned int m_newLimitPriceDollar;						// Limit price
	unsigned int m_newLimitPriceFraction;						// Limit price

	int m_newStopPriceDollar;						// Stop price 
	int m_newStopPriceFraction;						// Stop price 

	unsigned int m_newAuxPriceDollar;						// For discretionary and scaled orders
	unsigned int m_newAuxPriceFraction;						// For discretionary and scaled orders

	unsigned int LastPriceDollar;						// Last bid/ask price 
	unsigned int LastPriceFraction;						// Last bid/ask price

	unsigned int BidPriceDollar;						// Latest bid price
	unsigned int BidPriceFraction;						// Latest bid price

	unsigned int AskPriceDollar;						// Latest ask price
	unsigned int AskPriceFraction;						// Latest ask price
};

#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderCancelAck : public TMessageTime
#else
class TMsgOrderCancelAck : public TMessageOrderHeader
#endif
{
public:
	TMsgOrderCancelAck(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,
		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_MARKET,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_CANCEL_ACK, sizeof(TMsgOrderCancelAck)),
		m_header(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip)
#else
		TMessageOrderHeader(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_CANCEL_ACK, sizeof(TMsgOrderCancelAck),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
};

class TMsgOrderKill : public TMsgOrderReason
{
public:
	TMsgOrderKill(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,

		WORD rejectCode,

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_MARKET,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
		TMsgOrderReason(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			rejectCode,
			TS_ORDER_KILL, sizeof(TMsgOrderKill),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
	{
	}
};

#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderReplace : public TMessageTime
#else
class TMsgOrderReplace : public TMessageOrderHeader
#endif
{
public:
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
	DWORD					NewClOrdID;
protected:
	TMsgOrderReplace(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,

		DWORD newClOrdID,
		unsigned short type, unsigned short length,

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_MARKET,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, type, length),
		m_header(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip),
#else
		TMessageOrderHeader(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			type, length,
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
#endif
		NewClOrdID(newClOrdID)
	{
	}
};

class TMsgOrderReplaceAck : public TMsgOrderReplace
{
public:
	TMsgOrderReplaceAck(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD ip,

		DWORD newClOrdID,

		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_MARKET,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0
		):
		TMsgOrderReplace(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			ip,
			newClOrdID,
			TS_ORDER_REPLACE_ACK, sizeof(TMsgOrderReplaceAck),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
	{
	}
};

class TMsgOrderReplaceDone : public TMessageOrderBase//TMsgOrderReplace
{
public:
	TMsgOrderReplaceDone(DWORD clientOrdID, const char* traderId, const char* accountName, const char* firmId,
		const char* symbol,
		unsigned char side,
		unsigned long quantity,
		DWORD route,
		DWORD ip,

//		DWORD newClOrdID,
////
		unsigned char orderType = ORDER_TYPE_MARKET,
		unsigned int limitPriceDollar = 0,						// Limit price
		unsigned int limitPriceFraction = 0,					// Limit price

		unsigned char tifType = TIF_DAY,

		unsigned int expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		unsigned int effectiveTime = 0,					// When order should become active
//?
		char capacity = 0,						// Agency, principal, etc.

		const char* mm = "",	// Market maker ID string, don't know whether we need it...

		int stopPriceDollar = 0,						// Stop price 
		int stopPriceFraction = 0,						// Stop price 

		unsigned long minQuantity = 0,
		unsigned long displayQuantity = 0,				// Reserve order display quantity
		unsigned char quantityType = 0,					// Quantity type that generated the above qty
		unsigned long reserveQuantity = 0,				// Reserve size
		unsigned long refreshQuantity = 0,				// Refresh size
		unsigned long discretionQuantity = 0,				// Discretion size


		unsigned char priceType = 0,						// Price type that generated the above price

		unsigned int displayPriceDollar = 0,					// Also can be used for discretionary orders
		unsigned int displayPriceFraction = 0,					// Also can be used for discretionary orders

		unsigned int lastPriceDollar = 0,						// Last bid/ask price 
		unsigned int lastPriceFraction = 0,						// Last bid/ask price

		unsigned int bidPriceDollar = 0,						// Latest bid price
		unsigned int bidPriceFraction = 0,						// Latest bid price

		unsigned int askPriceDollar = 0,						// Latest ask price
		unsigned int askPriceFraction = 0,						// Latest ask price

		unsigned int auxPriceDollar = 0,						// For discretionary and scaled orders
		unsigned int auxPriceFraction = 0,						// For discretionary and scaled orders

		unsigned int date = 0,
		DWORD excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
		DWORD defaultRoutes = NULL_ROUTE,					// Single ROUTE to default to for execution.
		unsigned char ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		unsigned short ticketID = 0,						// Ticket ID assigned by client.

// *AK* start
		DWORD subType = 0,						// Additional Flags for Order, like type of peg...
		DWORD execInst = 0,						// Execution Instructions
		DWORD routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where
////
		DWORD messageSequenceNumber = 0,
		DWORD serverOrdID = 0,
		DWORD parentClOrdID = 0,
		DWORD acceptedTime = 0,
		DWORD canceledTime = 0,
		const char* marketReferenceID = "",
		unsigned char tracking = TR_ON_MARKET,
		unsigned char status = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 optionBlock = 0,
		unsigned long remainingQuantity = 0,
		unsigned long canceledQuantity = 0,
		unsigned char realTimeOrRecovered = 0,
		unsigned char instrumentType = 0,

		DWORD oldClOrdID = 0,
		const char* oldTraderId = "", const char* oldAccountName = "", const char* oldFirmId = "", const char* oldSymbol = "",
		unsigned char oldSide = 0,
		unsigned long oldQuantity = 0,
		DWORD oldIp = 0,

		DWORD oldMessageSequenceNumber = 0,
		DWORD oldServerOrdID = 0,
		DWORD oldParentClOrdID = 0,
		DWORD oldAcceptedTime = 0,
		DWORD oldCanceledTime = 0,
		const char* oldMarketReferenceId = "",
		unsigned char oldTracking = TR_ON_MARKET,
		unsigned char oldStatus = OS_NEW,
//		const char* confirmationID = "",
		unsigned __int64 oldOptionBlock = 0,
		unsigned long oldRemainingQuantity = 0,
		unsigned long oldCanceledQuantity = 0,
		unsigned char oldRealTimeOrRecovered = 0,
		unsigned char oldInstrumentType = 0
		):
		TMessageOrderBase(clientOrdID, traderId, accountName, firmId,
			symbol,
			side,
			quantity,
			route,
			ip,
//			newClOrdID,
			TS_ORDER_REPLACED, sizeof(TMsgOrderReplaceDone),
////
			orderType,
			limitPriceDollar,
			limitPriceFraction,

			tifType,
			expireTime,
			effectiveTime,
			capacity,
			mm,
			stopPriceDollar,
			stopPriceFraction,

			minQuantity,
			displayQuantity,
			quantityType,
			reserveQuantity,
			refreshQuantity,
			discretionQuantity,

			priceType,

			displayPriceDollar,
			displayPriceFraction,

			lastPriceDollar,
			lastPriceFraction,

			bidPriceDollar,
			bidPriceFraction,

			askPriceDollar,
			askPriceFraction,

			auxPriceDollar,
			auxPriceFraction,

			date,
			excludeRoutes,
			defaultRoutes,
			ticketCount,
			ticketID,

			subType,
			execInst,
			routingInstructions,
////
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
		m_oldMessageSequenceNumber(oldMessageSequenceNumber),
		m_oldClOrdID(oldClOrdID),							//Client assigned order id, I think it is ok to have this as a number instead of string for faster search
		m_oldParentClOrdID(oldParentClOrdID),
		m_oldSrOrdID(oldServerOrdID),						// Server assigned order id, server will use a number as well
		m_oldAcceptedTime(oldAcceptedTime),						// When order was accepted by market
		m_oldCanceledTime(oldCanceledTime),						// When order has been canceled if any
		m_oldTracking(oldTracking),							// Where order is, on server, on market, etc.,
		m_oldStatus(oldStatus),								// New, Partially filled, Canceled, Filled
		m_oldQuantity(oldQuantity),							// Order quantity ( moved from order )
		m_oldRemainingQuantity(oldRemainingQuantity),					// Remaining size of the order ( moved from order )
		m_oldCanceledQuantity(oldCanceledQuantity),					// Canceled size of the order
		m_oldRealTimeOrRecovered(oldRealTimeOrRecovered),				//Weather this a current message or recovered message
		m_oldTime(oldInstrumentType),								//Milliseconds since midnight, when this message is generated
		m_oldIp(oldIp ? oldIp : ip),									//For Compliance

		m_oldSide(oldSide ? oldSide : side),
		m_oldInstrumentType(oldInstrumentType)
	{
		U_CopyAndPad(m_oldAccountName, sizeof(m_oldAccountName), *oldAccountName ? oldAccountName : accountName, '\0');
		U_CopyAndPad(m_oldTraderID, sizeof(m_oldTraderID), *oldTraderId ? oldTraderId : traderId, '\0');
		U_CopyAndPad(m_oldFirmID, sizeof(m_oldFirmID), *oldFirmId ? oldFirmId : firmId, '\0');
		U_CopyAndPad(m_oldMarketReferenceID, sizeof(m_oldMarketReferenceID), *oldMarketReferenceId ? oldMarketReferenceId : marketReferenceID, '\0');
		*(unsigned __int64*)m_oldConfirmationID = oldOptionBlock ? oldOptionBlock : optionBlock;
		*((unsigned __int64*)m_oldConfirmationID + 1) = 0;
		U_CopyAndPad(m_oldSymbol, sizeof(m_oldSymbol), *oldSymbol ? oldSymbol : symbol, '\0');
	}
	DWORD		m_oldMessageSequenceNumber;
	DWORD		m_oldClOrdID;							//Client assigned order id, I think it is ok to have this as a number instead of string for faster search
	DWORD		m_oldParentClOrdID;
	DWORD		m_oldSrOrdID;							// Server assigned order id, server will use a number as well
	char		m_oldAccountName[MAX_ACCOUNT_SIZE];		//Order Account Name

// *AK* start
	char		m_oldTraderID[MAX_TRADER_ID_SIZE];
	char		m_oldFirmID[MAX_FIRM_ID_SIZE];
	DWORD		m_oldAcceptedTime;						// When order was accepted by market
	DWORD		m_oldCanceledTime;						// When order has been canceled if any
	char		m_oldMarketReferenceID[MAX_MARKET_REFERENCE_ID];		// Will be filled with Venue's OrderID
	UCHAR		m_oldTracking;							// Where order is, on server, on market, etc.
	UCHAR		m_oldStatus;								// New, Partially filled, Canceled, Filled
	char		m_oldConfirmationID[16];					// can be used for short sells. ID from liquidity finder
	ULONG		m_oldQuantity;							// Order quantity ( moved from order )
	ULONG		m_oldRemainingQuantity;					// Remaining size of the order ( moved from order )
	ULONG		m_oldCanceledQuantity;					// Canceled size of the order
// *AK* end

	char		m_oldSymbol[MAX_SYMBOL_SIZE];
	UCHAR		m_oldRealTimeOrRecovered;				//Weather this a current message or recovered message
	DWORD		m_oldTime;								//Milliseconds since midnight, when this message is generated
	DWORD		m_oldIp;									//For Compliance

	UCHAR		m_oldSide;
	UCHAR		m_oldInstrumentType;
};

class HtbNode
{
public:
	Symbol m_symbol;
	unsigned int m_priceToBorrowDollar;
	unsigned int m_priceToBorrowFraction;
	unsigned int m_quantity;
	unsigned char m_discountFlag;
//02/19/2014
	unsigned char m_htbType;
};

class TMsgRespHtbSymbolList : public TMessageTime
{
public:
	TMsgRespHtbSymbolList(unsigned int firmId, unsigned int requestId, unsigned short nodeSize, unsigned short nodes, bool done):
		TMessageTime(0, M_TR_HTB_RESP_SYMBOL_LIST, sizeof(TMsgRespHtbSymbolList) + nodeSize * nodes),
		m_firmId(firmId),
		m_requestId(requestId),
		m_nodeSize(nodeSize),
		m_nodes(nodes),
		m_done(done)
	{}

	unsigned int m_firmId;
	unsigned int m_requestId;
	unsigned short m_nodeSize;
	unsigned short m_nodes;
	bool m_done;
	// Followed by m_nodes of CHTBNode points
};


class TMsgReqList : public TMessageTime
{
public:
	unsigned int m_firmId;
	unsigned int m_requestId;
protected:
	TMsgReqList(unsigned int firmId, unsigned int requestId, unsigned short type, unsigned short length):
		TMessageTime(0, type, length),
		m_firmId(firmId),
		m_requestId(requestId)
	{}
};

class TMsgRespList : public TMessageTime
{
public:
	unsigned int m_firmId;
	unsigned int m_requestId;
	unsigned short m_nodeSize;
	unsigned short m_nodes;
//	bool m_done;
	// Followed by m_nodes of EtbNode points
protected:
	TMsgRespList(unsigned int firmId, unsigned int requestId, unsigned short nodeSize, unsigned short nodes, unsigned short type, unsigned short length):
		TMessageTime(0, type, length + nodeSize * nodes),
		m_firmId(firmId),
		m_requestId(requestId),
		m_nodeSize(nodeSize),
		m_nodes(nodes)
	{}
};

class TMsgRespListWithDone : public TMsgRespList
{
public:
	bool m_done;
	// Followed by m_nodes of EtbNode points
protected:
	TMsgRespListWithDone(unsigned int firmId, unsigned int requestId, unsigned short nodeSize, unsigned short nodes, bool done, unsigned short type, unsigned short length):
		TMsgRespList(firmId, requestId, nodeSize, nodes, type, length),
		m_done(done)
	{}
};

class TMsgReqHtbSymbolList : public TMsgReqList
{
public:
	TMsgReqHtbSymbolList(unsigned int firmId, unsigned int requestId):
		TMsgReqList(firmId, requestId, M_TR_HTB_REQ_SYMBOL_LIST, sizeof(TMsgReqHtbSymbolList))
	{}
};

class TMsgReqEtbSymbolList : public TMsgReqList
{
public:
	TMsgReqEtbSymbolList(unsigned int firmId, unsigned int requestId):
		TMsgReqList(firmId, requestId, M_TR_ETB_REQ_SYMBOL_LIST, sizeof(TMsgReqEtbSymbolList))
	{}
};

class EtbNode
{
public:
	Symbol m_symbol;
};

enum EtbSymbolListFlags : unsigned char
{
	EtbFirst	= 0x01,
	EtbReload	= 0x02,
};
/*
class TMsgRespEtbSymbolList : public TMessageTime
{
public:
	unsigned int m_firmId;
	unsigned int m_requestId;
	unsigned short m_nodeSize;
	unsigned short m_nodes;
	bool m_done;
	unsigned char m_flags;
	// Followed by m_nodes of EtbNode points
protected:
	TMsgRespEtbSymbolList(unsigned int firmId, unsigned int requestId, unsigned short nodeSize, unsigned short nodes, bool done, unsigned char flags):
		TMessageTime(0, M_TR_ETB_RESP_SYMBOL_LIST, sizeof(TMsgRespEtbSymbolList) + nodeSize * nodes),
		m_firmId(firmId),
		m_requestId(requestId),
		m_nodeSize(nodeSize),
		m_nodes(nodes),
		m_done(done),
		m_flags(flags)
	{}
};
*/
class TMsgRespEtbSymbolList : public TMsgRespList
{
public:
	TMsgRespEtbSymbolList(unsigned int firmId, unsigned int requestId, unsigned short nodeSize, unsigned short nodes, bool done, unsigned char flags):
		TMsgRespList(firmId, requestId, nodeSize, nodes, M_TR_ETB_RESP_SYMBOL_LIST, sizeof(TMsgRespEtbSymbolList)),
		m_done(done),
		m_flags(flags)
	{}
	bool m_done;
	unsigned char m_flags;
};

class TMsgReqLocateInfo : public TMsgReqList
{
public:
	TMsgReqLocateInfo(unsigned int firmId, unsigned int requestId):
		TMsgReqList(firmId, requestId, M_TR_HTB_REQ_LOCATE_INFO, sizeof(TMsgReqLocateInfo))
	{}
};

class BorrowNode
{
public:
	Symbol m_symbol;
	unsigned int m_priceToBorrowDollar;
	unsigned int m_priceToBorrowFraction;
	unsigned int m_quantity;
	unsigned char m_discountFlag;
//02/19/2014
	unsigned char m_htbType;
};

class TMsgRespLocateInfo : public TMsgRespListWithDone
{
public:
	TMsgRespLocateInfo(unsigned int firmId, unsigned int requestId, unsigned short nodeSize, unsigned short nodes, bool done):
		TMsgRespListWithDone(firmId, requestId, nodeSize, nodes, done, M_TR_HTB_RESP_LOCATE_INFO, sizeof(TMsgRespLocateInfo))
	{}
};
/*
class TMessageTimeSymbol : public TMessageTime
{
public:
	Symbol m_symbol;
protected:
	TMessageTimeSymbol(const char* symbol, unsigned int time, unsigned short type, unsigned short length);
	TMessageTimeSymbol(const unsigned __int64& symbol, unsigned int time, unsigned short type, unsigned short length):TMessageTime(time, type, length){*(unsigned __int64*)m_symbol = symbol;}
};
*/
class TMsgLocateInfo : public TMessageTimeSymbol
{
public:
	TMsgLocateInfo(const char* symbol, unsigned int priceDollar, unsigned int priceFraction, unsigned int size, unsigned int mmid, unsigned int discountFlag, unsigned int time):
		TMessageTimeSymbol(symbol, time, M_TR_HTB_LOCATE_INFO, sizeof(TMsgLocateInfo)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_locateMPID(mmid),
		m_discountFlag(discountFlag)
	{
//		*(unsigned int*)m_locateMPID = mmid;
//		m_locateMPID[sizeof(unsigned int)] = '\0';
	}
	
	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned int m_locateMPID;
//	char m_locateMPID[sizeof(unsigned int) + 1];
	unsigned char m_discountFlag;
};


class TMsgCommissionFee : public TMsgAccountObject
{
public:
//	TMsgCommissionFee(const char* accountName, const Money& fee);
	TMsgCommissionFee::TMsgCommissionFee(const char* accountName, const Money& fee):
		TMsgAccountObject(accountName, TM_DEFAULT_COMMISSION_FEE, sizeof(TMsgCommissionFee)),
		m_fee(fee)
	{
	}
	Money m_fee;
};

class TMsgCustomAccountConstraints : public Message
{
public:
	TMsgCustomAccountConstraints(const ConstraintCollection& constraints):Message(TM_ACCOUNT_CONSTRAINTS, sizeof(TMsgCustomAccountConstraints)), m_constraintCollection(constraints){}
	ConstraintCollection m_constraintCollection;
};

enum NewsStoryFilter : unsigned char
{
	NSF_CHILD,
	NSF_HEADLINE_ONLY,
	NSF_TEMPORARY,

	NSF_Count
};

enum NewsMetaFilter : unsigned char
{
	NMF_SYMBOLS,
	NMF_CODES,

	NMF_Count
};

class NewsHeadline// : public Observable
{
public:
	typedef std::hash_set<unsigned __int64> SymbolSet;

	NewsHeadline(const SymbolSet& symbolSet,
		const unsigned __int64& dateTime,
		const unsigned __int64& dateTimePublished,
		const unsigned __int64& numericSymbol,

		unsigned int ordinal,
		unsigned int alertTakeNumber,
		unsigned int relevance,
		unsigned int extDisplayWireId,
		unsigned short subWireId,
		unsigned char headlineType,
		bool update,
//		const std::string& resourceId,
		const NewsResourceAsNumberArray& resourceId,
		const std::string& text,
		const std::string& tickerSymbols,
//		const std::string& symbol,
		const std::string& storyCodes,
		const std::string& providerService,
		const std::string& synopsis):

		m_symbolSet(symbolSet),
		m_symbolSetEnd(m_symbolSet.end()),
		m_dateTime(dateTime),
		m_dateTimePublished(dateTimePublished),
		m_numericSymbol(numericSymbol),
		m_ordinal(ordinal),
		m_alertTakeNumber(alertTakeNumber),
		m_relevance(relevance),
		m_extDisplayWireId(extDisplayWireId),
		m_subWireId(subWireId),
		m_headlineType(headlineType),
		m_update(update),
		m_resourceId(resourceId),
		m_text(text),
		m_tickerSymbols(tickerSymbols),
		m_symbol((const char*)&m_numericSymbol),//symbol),
		m_storyCodes(storyCodes),
		m_providerService(providerService),
		m_synopsis(synopsis)
	{
	}

	const SymbolSet& GetSymbolSet() const{return m_symbolSet;}
	bool SymbolBelongs(const unsigned __int64& symbol) const{return m_symbolSet.find(symbol) != m_symbolSetEnd;}
	bool SymbolBelongs(const char* symbol) const{return m_symbolSet.find(U_StringToUInt64Term0(symbol)) != m_symbolSetEnd;}
	const unsigned __int64& GetDateTime() const{return m_dateTime;}
	const unsigned __int64& GetDateTimePublished() const{return m_dateTimePublished;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
	const unsigned int& GetOrdinal() const{return m_ordinal;}
	const unsigned int& GetAlertTakeNumber() const{return m_alertTakeNumber;}
	const unsigned int& GetRelevance() const{return m_relevance;}
	const unsigned int& GetExtDisplayWireId() const{return m_extDisplayWireId;}
	const unsigned short& GetSubWireId() const{return m_subWireId;}
	const unsigned char& GetHeadlineType() const{return m_headlineType;}
	const bool& isUpdate() const{return m_update;}
	const NewsResourceAsNumberArray& GetResourceId() const{return m_resourceId;}
	const char* GetResourceIdStr() const{return m_resourceId.GetString();}
	const std::string& GetText() const{return m_text;}
	const std::string& GetTickerSymbols() const{return m_tickerSymbols;}
	const std::string& GetSymbol() const{return m_symbol;}
	const std::string& GetStoryCodes() const{return m_storyCodes;}
	const std::string& GetProviderService() const{return m_providerService;}
	const std::string& GetSynopsis() const{return m_synopsis;}

	void SetSymbolSet(const SymbolSet& symbolSet){m_symbolSet = symbolSet;}
	void SetDateTime(const unsigned __int64& dateTime){m_dateTime = dateTime;}
	void SetDateTimePublished(const unsigned __int64& dateTimePublished){m_dateTimePublished = dateTimePublished;}
	void SetNumericSymbol(const unsigned __int64& numericSymbol){m_numericSymbol = numericSymbol; m_symbol = (const char*)&m_numericSymbol;}
	void SetAlertTakeNumber(const unsigned int& alertTakeNumber){m_alertTakeNumber = alertTakeNumber;}
	void SetRelevance(const unsigned int& relevance){m_relevance = relevance;}
	void SetExtDisplayWireId(const unsigned int& extDisplayWireId){m_extDisplayWireId = extDisplayWireId;}
	void SetSubWireId(const unsigned short& subWireId){m_subWireId = subWireId;}
	void SetHeadlineType(const unsigned char& headlineType){m_headlineType = headlineType;}
	void SetUpdate(const bool& update){m_update = update;}
//	void SetResourceId(const std::string& resourceId){m_resourceId = resourceId;}
	void SetText(const std::string& text){m_text = text;}
	void SetTickerSymbols(const std::string& tickerSymbols){m_tickerSymbols = tickerSymbols;}
//	void SetSymbol(const std::string& symbol){m_symbol = symbol;}
	void SetStoryCodes(const std::string& storyCodes){m_storyCodes = storyCodes;}
	void SetProviderService(const std::string& providerService){m_providerService = providerService;}
	void SetSynopsis(const std::string& synopsis){m_synopsis = synopsis;}

	const std::string& GetStoryText() const{return m_storyText;}
	bool isShowChain() const{return m_showChain;}

	void SetStoryText(const std::string& text, bool showChain){m_storyText = text; m_showChain = showChain;}

	bool LockInquiry() const{return m_lock.LockInquiry();}
	void LockInquiryWait() const{m_lock.LockInquiryWait();}
	void UnlockInquiry() const{m_lock.UnlockInquiry();}
	bool LockModification() const{return m_lock.LockModification();}
	void UnlockModification() const{m_lock.UnlockModification();}

	bool LockStoryInquiry() const{return m_lockStory.LockInquiry();}
	void LockStoryInquiryWait() const{m_lockStory.LockInquiryWait();}
	void UnlockStoryInquiry() const{m_lockStory.UnlockInquiry();}
	bool LockStoryModification() const{return m_lockStory.LockModification();}
	void UnlockStoryModification() const{m_lockStory.UnlockModification();}

	DECLARE_NED_NEW
protected:
	SymbolSet m_symbolSet;
	SymbolSet::const_iterator m_symbolSetEnd;
	unsigned __int64 m_dateTime;
	unsigned __int64 m_dateTimePublished;
	unsigned __int64 m_numericSymbol;
	unsigned int m_ordinal;
	unsigned int m_alertTakeNumber;
	unsigned int m_relevance;
	unsigned int m_extDisplayWireId;
	unsigned short m_subWireId;
	unsigned char m_headlineType;
	bool m_update;
	NewsResourceAsNumberArray m_resourceId;
//	std::string m_resourceId;
	std::string m_text;
	std::string m_tickerSymbols;
	std::string m_symbol;
	std::string m_storyCodes;
	std::string m_providerService;
	std::string m_synopsis;
	std::string m_storyText;
	bool m_showChain;
	TakionLock m_lock;
	TakionLock m_lockStory;
};

typedef std::set<unsigned __int64> WireSet;

#ifdef __cplusplus
extern "C"
{
#endif

//News API
typedef unsigned char (WINAPI* ApiNewsConnect)(const char* hostName,
	unsigned short port,
	const char* userName,
	const char* password,
	const char* appName,
	const char* appVersion,
	const char* companyName,
	const char* sessionData,
	const char* proxyIpAddress,
	unsigned short proxyPort,
	const char* proxyProtocolName,
	const char* proxyUserName,
	const char* proxyPassword,
	const char* newPassword);

typedef void (WINAPI* ApiNewsDisplayFilterDialog)(CWnd* receipient,
	unsigned int code,
	const WireSet& wireSet,
	unsigned int storyFilter,
	unsigned int metaFilter,
	unsigned int relevance,
	CWnd* parent,
	const CPoint& mousePoint);
typedef bool (WINAPI* ApiGetFilterDialogValues)(WireSet& wireSet,
	unsigned int& storyFilter,
	unsigned int& metaFilter,
	unsigned int& relevance);

typedef void (WINAPI* ApiNewsDisplayLimitsDialog)(CWnd* receipient,
	unsigned int code,
	unsigned short daysBack,
	unsigned short headlineCount,
	CWnd* parent,
	const CPoint& mousePoint);
typedef bool (WINAPI* ApiGetLimitsDialogValues)(unsigned short& daysBack,
	unsigned short& headlineCount);

typedef Observable* (WINAPI* ApiGetStockNewsByUInt64)(Observable* oldStockNews, const Observable* newsCollection, const unsigned __int64& symbol);
typedef Observable* (WINAPI* ApiGetStockNewsByCharPtr)(Observable* oldStockNews, const Observable* newsCollection, const char* symbol);
typedef Observable* (WINAPI* ApiGetStockNewsByString)(Observable* oldStockNews, const Observable* newsCollection, const FilterStringAsNumberArray& symbol, const std::hash_set<unsigned __int64>* stockSet);
typedef Observable* (WINAPI* ApiFindStockNewsByString)(const Observable* newsCollection, const FilterStringAsNumberArray& symbol);

typedef unsigned char (WINAPI* ApiReleaseNewsCollection)(Observable* newsCollection, Observer* observer);
typedef Observable* (WINAPI* ApiUpdateNewsCollectionFilter)(Observable* newsCollection, Observer* observer, const WireSet& wireSet, unsigned int storyFilter, unsigned int metaFilter, unsigned int relevance);
typedef bool (WINAPI* ApiGetWireInfoAt)(unsigned int at, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled);
typedef bool (WINAPI* ApiGetNextWireInfo)(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled);
typedef const std::string* (WINAPI* ApiGetNextTopicInfo)(TakionIterator* iterator, std::string* description);
typedef bool (WINAPI* ApiRequestHeadlines)(Observable* stockNews, unsigned short daysBack, unsigned short headlineCount);
typedef bool (WINAPI* ApiRequestStory)(const NewsHeadline* headline, bool showChain);
typedef const LineBufferArray* (WINAPI* ApiGetUnappliedHeadlines)(Observable* stockNews);
typedef Observable* (WINAPI* ApiFindNewsCollectionById)(unsigned int id);
typedef const NewsHeadline* (WINAPI* ApiFindHeadline)(const Observable* stockNews, const NewsResourceAsNumberArray& resourceId);

typedef unsigned int (WINAPI* ApiGetHeadlineCount)(const Observable* stockNews);
typedef TakionIterator* (WINAPI* ApiCreateHeadlineIterator)(const Observable* stockNews);
typedef const NewsHeadline* (WINAPI* ApiGetNextHeadline)(TakionIterator* iterator);
typedef const NewsStory* (WINAPI* ApiFindStoryByResourceId)(const NewsResourceAsNumberArray& resourceId);
typedef const NewsStory* (WINAPI* ApiGetStory)();

//////////////////////////////////////////////////////////////////
	
bool WINAPI TN_IsTakionNewsConnected();
Observable* WINAPI TN_GetTakionNewsObservable();
void WINAPI TN_SetTakionNewsLogFile(void* logFileHandle);

Observable* WINAPI TN_ObtainStockNewsByNum(Observable* oldStockNews, const Observable* newsCollection, const unsigned __int64& symbol);
Observable* WINAPI TN_ObtainStockNews(Observable* oldStockNews, const Observable* newsCollection, const char* symbol);
Observable* WINAPI TN_FindStockNewsByNum(const Observable* newsCollection, const unsigned __int64& symbol);

Observable* WINAPI TN_ObtainStringNews(Observable* oldStockNews, const Observable* newsCollection, const FilterStringAsNumberArray& symbol, const std::hash_set<unsigned __int64>* stockSet);
Observable* WINAPI TN_FindStringNews(const Observable* newsCollection, const FilterStringAsNumberArray& symbol);

bool WINAPI TN_DoMainThreadIdleTasks(LONG lCount);

unsigned char WINAPI TN_ReleaseNewsCollection(Observable* newsCollection, Observer* observer);
Observable* WINAPI TN_UpdateNewsCollectionFilter(Observable* newsCollection, Observer* observer, const WireSet& wireSet, unsigned int storyFilter, unsigned int metaFilter, unsigned int relevance);

unsigned int WINAPI TN_GetWireCount();//ApiGetUInt
bool WINAPI TN_GetWireInfoAt(unsigned int at, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled);
TakionIterator* WINAPI TN_CreateWireIterator();//ApiCreateIterator
bool WINAPI TN_GetNextWireInfo(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled);

const char* WINAPI TN_GetConnectionStatusInfo();
unsigned int WINAPI TN_GetAllWireCount();//ApiGetUInt
//bool WINAPI TN_GetAllWireInfoAt(unsigned int at, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled);
TakionIterator* WINAPI TN_CreateAllWireIterator();//ApiCreateIterator
bool WINAPI TN_GetNextAllWireInfo(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled);

unsigned int WINAPI TN_GetTopicCount();
TakionIterator* WINAPI TN_CreateTopicIterator();
const std::string* WINAPI TN_GetNextTopicInfo(TakionIterator* iterator, std::string* description);

void WINAPI TN_AdjustToChangedScreen(int dx, int dy);
void WINAPI TN_NewsDisplayFilterDialog(CWnd* receipient,
	unsigned int code,
	const WireSet& wireSet,
	unsigned int storyFilter,
	unsigned int metaFilter,
	unsigned int relevance,
	CWnd* parent,
	const CPoint& mousePoint);

bool WINAPI TN_NewsGetFilterDialogValues(WireSet& wireSet,
	unsigned int& storyFilter,
	unsigned int& metaFilter,
	unsigned int& relevance);

void WINAPI TN_NewsDisplayLimitsDialog(CWnd* receipient,
	unsigned int code,
	unsigned short daysBack,
	unsigned short headlineCount,
	CWnd* parent,
	const CPoint& mousePoint);

bool WINAPI TN_NewsGetLimitsDialogValues(unsigned short& daysBack,
	unsigned short& headlineCount);

unsigned char WINAPI TN_TakionNewsConnect(const char* hostName,
	unsigned short port,
	const char* userName,
	const char* password,
	const char* appName,
	const char* appVersion,
	const char* companyName,
	const char* sessionData,
	const char* proxyIpAddress,
	unsigned short proxyPort,
	const char* proxyProtocolName,
	const char* proxyUserName,
	const char* proxyPassword,
	const char* newPassword);

bool WINAPI TN_RequestHeadlines(Observable* stockNews, unsigned short daysBack, unsigned short headlineCount);
bool WINAPI TN_RequestStory(const NewsHeadline* headline, bool showChain);
const LineBufferArray* WINAPI TN_GetUnappliedHeadlines(Observable* stockNews);
Observable* WINAPI TN_FindNewsCollectionById(unsigned int id);
bool WINAPI TN_IsUpdatedHeadline(const Observable* stockNews, unsigned int updateOrdinal);
void WINAPI TN_SetUpdatedHeadline(Observable* stockNews);
void WINAPI TN_ReadNewHeadlines(Observable* stockNews);
void WINAPI TN_ReleaseNewHeadlines(Observable* stockNews);
const NewsHeadline* WINAPI TN_FindHeadline(const Observable* stockNews, const NewsResourceAsNumberArray& resourceId);
unsigned int WINAPI TN_GetHeadlineCount(const Observable* stockNews);
TakionIterator* WINAPI TN_CreateHeadlineIterator(const Observable* stockNews);
const NewsHeadline* WINAPI TN_GetNextHeadline(TakionIterator* iterator);
bool WINAPI TN_LockInquiryHeadlines(Observable* stockNews);
void WINAPI TN_LockInquiryWaitHeadlines(Observable* stockNews);
void WINAPI TN_UnlockInquiryHeadlines(Observable* stockNews);
bool WINAPI TN_IsStockNewsRequested(const Observable* stockNews);

const std::string* WINAPI TN_GetSearchStringAll();
const std::string* WINAPI TN_GetSearchStringAllUs();

const NewsStory* WINAPI TN_FindStoryByResourceId(const NewsResourceAsNumberArray& resourceId);
const NewsStory* WINAPI TN_GetLastStory();
bool WINAPI TN_LockInquiryStory();
void WINAPI TN_LockInquiryWaitStory();
void WINAPI TN_UnlockInquiryStory();
bool WINAPI TN_IsUpdatedStory(unsigned int updateOrdinal);
void WINAPI TN_SetUpdatedStory();
Observable* WINAPI TN_GetStoryObservable();

bool WINAPI TN_LockInquiryWireNameStorage();
void WINAPI TN_LockInquiryWaitWireNameStorage();
void WINAPI TN_UnlockInquiryWireNameStorage();

bool WINAPI TN_LockInquiryAllWireNameStorage();
void WINAPI TN_LockInquiryWaitAllWireNameStorage();
void WINAPI TN_UnlockInquiryAllWireNameStorage();

bool WINAPI TN_LockInquiryTopicNameStorage();
void WINAPI TN_LockInquiryWaitTopicNameStorage();
void WINAPI TN_UnlockInquiryTopicNameStorage();

void WINAPI TN_ProcessConnectionInMainThread(bool connected);

bool WINAPI TN_NewsCollectionHasProfile(const Observable* newsCollection);

///////////////////////////////////
const char* WINAPI TD_GetModuleVersionStr();
unsigned __int64 WINAPI TD_GetModuleVersionNum();
const char* WINAPI TD_GetHeaderVersion();
unsigned __int64 WINAPI TD_GetHeaderVersionNum();
const char* WINAPI TD_GetFilePathAndName();
const char* WINAPI TD_GetPlatform();
const char* WINAPI TD_GetFileDescription();
void WINAPI TD_GetDllBuildDescription(std::string& buildStr);

void WINAPI TD_Initialize(unsigned __int64 exeVersion);//, const char* argLine);//RingBufferListEventNotification* ringBuffer);
bool WINAPI TD_Terminate();
unsigned __int64 WINAPI TD_GetExeVersion();
HANDLE WINAPI TD_GetUiEvent();

void WINAPI TD_WriteToMainThread(const char* data, unsigned int length);
void WINAPI TD_WriteBuffersToMainThread(WSABUF* data, unsigned int count);
void WINAPI TD_WriteMessageToMainThread(const Message* message);
bool WINAPI TD_ProcessMainThreadData();

Observable& WINAPI TD_GetCustomInternalObservable();
Observable& WINAPI TD_GetCustomExternalObservable();
Observable& WINAPI TD_GetAdminObservable();
Observable& WINAPI TD_GetExternalCommandObservable();
Observable& WINAPI TD_GetNewAccountObservable();
Observable& WINAPI TD_GetNewPositionObservable();
Observable& WINAPI TD_GetPositionExecutedObservable();
Observable& WINAPI TD_GetNewOrderObservable();
Observable& WINAPI TD_GetOrderErrorObservable();
Observable& WINAPI TD_GetExecutionObservable();
Observable& WINAPI TD_GetNewIndexObservable();
Observable& WINAPI TD_GetNewEquityObservable();
Observable& WINAPI TD_GetQuoteMoveObservable();
Observable& WINAPI TD_GetExtensionObservable();
Observable& WINAPI TD_GetHistoricalPrintObservable();
Observable& WINAPI TD_GetHistoricalChartObservable();
Observable& WINAPI TD_GetAllPrintObservable();

//const LineBufferArray* WINAPI TD_GetUnappliedMessages();

//const char* WINAPI TD_GetDefaultTraderId();

void WINAPI TD_Log(const char* message, const char* prefix = NULL, unsigned int level = 0);


#ifdef __cplusplus
}
#endif

enum ConnectionDataType : unsigned char
{
	CDT_MARKET_DATA,
	CDT_EXECUTOR,
	CDT_MARKET_SORTER,
	CDT_HISTORICAL_PRINT,
	CDT_OPTION_MARKET_DATA,

	CDT_NEWS,

	CDT_Count,

	CDT_ReservedConnectionTypes = 64
};

class TD_API ConnectionLine
{
public:
	ConnectionLine(const char* addressName,
		unsigned short port,
		const char* bindAddressName = NULL,
		unsigned short bindPort = 0);
	ConnectionLine(const ConnectionLine& other);
	ConnectionLine& operator=(const ConnectionLine& other);
	unsigned __int64 GetIpPort() const{return m_ipport;}
	unsigned __int64 GetBindIpPort() const{return m_bindIpport;}
	const char* GetIpAddressName() const{return m_addressName.c_str();}
	const char* GetIpBindAddressName() const{return m_bindAddressName.c_str();}
	const char* GetIpAddress() const{return m_address.c_str();}
	const char* GetIpBindAddress() const{return m_bindAddress.c_str();}
	unsigned short GetPort() const{return m_port;}
	unsigned short GetBindPort() const{return m_bindPort;}

	const std::string& GetIpAddressNameStr() const{return m_addressName;}
	const std::string& GetIpBindAddressNameStr() const{return m_bindAddressName;}
	const std::string& GetIpAddressStr() const{return m_address;}
	const std::string& GetIpBindAddressStr() const{return m_bindAddress;}

	unsigned int GetIpNumAddress() const{return m_ipNumAddress;}
	unsigned int GetIpInvAddress() const{return m_ipInvAddress;}
	unsigned int GetIpNumBindAddress() const{return m_ipNumBindAddress;}
	unsigned int GetIpInvBindAddress() const{return m_ipInvBindAddress;}

	static unsigned __int64 CalculateIpPort(unsigned int ip, unsigned short port){return ((unsigned __int64)ip << 16) | (unsigned __int64)port;}
//	static unsigned int GetNumIp(const char* ip);
	static unsigned __int64 CalculateIpPort(const char* ip, unsigned short port);

	void UpdateIpPort(){m_ipport = CalculateIpPort(m_ipInvAddress, m_port); m_bindIpport = CalculateIpPort(m_ipInvBindAddress, m_bindPort);}

	bool isIdentical(const ConnectionLine& other) const{return m_ipport == other.m_ipport && m_bindIpport == other.m_bindIpport;}
	bool operator==(const ConnectionLine& other) const{return m_ipport == other.m_ipport;}// && m_bindIpport == other.m_bindIpport;}
	bool operator<(const ConnectionLine& other) const{return m_ipport < other.m_ipport;}// || m_ipport == other.m_ipport && m_bindIpport < other.m_bindIpport;}
	bool operator>(const ConnectionLine& other) const{return m_ipport > other.m_ipport;}// || m_ipport == other.m_ipport && m_bindIpport > other.m_bindIpport;}
	bool operator!=(const ConnectionLine& other) const{return !operator==(other);}
	bool operator<=(const ConnectionLine& other) const{return !operator>(other);}
	bool operator>=(const ConnectionLine& other) const{return !operator<(other);}
	void UpdatePrevious()
	{
		m_prevAddress = m_address;
		m_prevPort = m_port;
//		m_prevConnectionDataType = m_connectionDataType;
	}
	const char* GetPrevIpAddress() const{return m_prevAddress.c_str();}
	unsigned short GetPrevPort() const{return m_prevPort;}
protected:
	std::string m_addressName;

	std::string m_prevAddress;

	std::string m_bindAddressName;
	std::string m_address;
	std::string m_bindAddress;
	unsigned short m_port;
	unsigned short m_bindPort;
	unsigned short m_prevPort;

	unsigned __int64 m_ipport;
	unsigned __int64 m_bindIpport;
//	JetByteTools::Socket::CAddressIPv4 m_ipAddress;
//	JetByteTools::Socket::CAddressIPv4 m_ipBindAddress;

	unsigned int m_ipNumAddress;
	unsigned int m_ipInvAddress;
	unsigned int m_ipNumBindAddress;
	unsigned int m_ipInvBindAddress;
};

class TD_API ConnectionBase
{
public:

	virtual ~ConnectionBase(){}
	Chain<ConnectionLine>& GetConnectionLineChain(){return m_connectionLineChain;}
	const Chain<ConnectionLine>& GetConnectionLineChain() const{return m_connectionLineChain;}
	void ClearConnectionLines()
	{
//		m_connectionLineVector.clear();
//		m_ipPortSet.clear();
		m_connectionLineChain.Clear();
	}
	bool AddConnectionLine(const ConnectionLine& connectionLine)
	{
		return m_connectionLineChain.AddChainItem(connectionLine);//, true);
//		bool ret = m_ipPortSet.insert(connectionLine).second;
//		m_connectionLineVector.push_back(connectionLine);
//		return ret;
	}
	bool AddConnectionLine(const char* addressName, unsigned short port, const char* bindAddressName = NULL, unsigned short bindPort = 0)
	{
		return AddConnectionLine(ConnectionLine(addressName, port, bindAddressName, bindPort));
	}
	bool SameConnectionList(const ConnectionBase& other) const{return m_connectionLineChain.SameList(other.m_connectionLineChain);}
	bool isIntersectConnectionList(const ConnectionBase& other) const{return m_connectionLineChain.isListIntersect(other.m_connectionLineChain);}
	unsigned int GetConnectionLineCount() const{return m_connectionLineChain.GetCount();}
	void ResetConnectionLines()
	{
		m_connectionLineChain.Reset();
//		m_connectionLineChain.GetNext();
	}
	virtual const ConnectionLine* GetCurrentConnectionLine() const{return m_connectionLineChain.GetCurrent();}
	virtual ConnectionLine* GetCurrentConnectionLine(){return m_connectionLineChain.GetCurrent();}
/*
	typedef std::vector<ConnectionLine> ConnectionLineVector;
	typedef std::set<ConnectionLine> IpPortSet;
	void ClearConnectionLines(){m_connectionLineVector.clear();m_ipPortSet.clear();}
	bool AddConnectionLine(const ConnectionLine& connectionLine)
	{
		bool ret = m_ipPortSet.insert(connectionLine).second;
		m_connectionLineVector.push_back(connectionLine);
		return ret;
	}
	bool AddConnectionLine(const char* addressName, unsigned short port, const char* bindAddressName = NULL, unsigned short bindPort = 0)
	{
		return AddConnectionLine(ConnectionLine(addressName, port, bindAddressName, bindPort);
	}
*/
	void Initialize();

	const char* GetName() const{return m_connectionName.c_str();}
	const char* GetLoginId() const{return m_loginID.c_str();}
	const char* GetPassword() const{return m_password.c_str();}
	virtual const char* GetPrevIpAddress() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetPrevIpAddress() : "";
//		return m_prevAddress.c_str();
	}
	virtual unsigned short GetPrevPort() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetPrevPort() : 0;
//		return m_prevAddress.c_str();
	}
//
	virtual unsigned __int64 GetIpPort() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetIpPort() : 0;
	}
	virtual const char* GetIpAddress() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetIpAddress() : "";
	}
	virtual unsigned short GetPort() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetPort() : 0;
	}
	virtual const char* GetIpBindAddress() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetIpBindAddress() : "";
	}
	virtual unsigned short GetBindPort() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetBindPort() : 0;
	}
	virtual unsigned int GetIpNumAddress() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetIpNumAddress() : 0;
	}
	virtual unsigned int GetIpInvAddress() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetIpInvAddress() : 0;
	}

	virtual unsigned int GetIpNumBindAddress() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetIpNumBindAddress() : 0;
	}
	virtual unsigned int GetIpInvBindAddress() const
	{
		const ConnectionLine* connectionLine = GetCurrentConnectionLine();
		return connectionLine ? connectionLine->GetIpInvBindAddress() : 0;
	}

	unsigned char GetConnectionDataType() const{return m_connectionDataType;}
	void SetConnectionDataType(unsigned char connectionDataType){m_connectionDataType = connectionDataType;}
	unsigned char GetPrevConnectionDataType() const{return m_prevConnectionDataType;}
	unsigned long GetReconnectInterval() const{return m_reconnectInterval;}

	unsigned int GetBufferSizeReceiveRequested() const{return m_bufferSizeReceiveRequested;}
	unsigned int GetBufferSizeSendRequested() const{return m_bufferSizeSendRequested;}

	void SetReconnectInterval(unsigned long interval){m_reconnectInterval = interval;}

//	virtual bool SetIpAddressAndPort(const char* ip, unsigned short port) = 0;
//	virtual bool SetBindIpAddressAndPort(const char* ip = NULL, unsigned short port = 0) = 0;

//	virtual bool CopyIpAddressAndPort(const ConnectionBase& other);
//	virtual bool CopyBindIpAddressAndPort(const ConnectionBase& other);

	bool SameIpPortList(const ConnectionBase& other) const;
	bool SetIpPort(unsigned __int64 ipport);

	bool operator==(const ConnectionBase& other) const
	{
//		return m_ipport == other.m_ipport;
		return SameIpPortList(other);
	}
	bool operator!=(const ConnectionBase& other) const{return !operator==(other);}
//	bool operator<(const ConnectionBase& other) const{return m_ipport < other.m_ipport;}

	bool isSameName(const ConnectionBase& other) const{return m_connectionName == other.m_connectionName;}
	bool isSameReconnectInterval(const ConnectionBase& other) const{return m_reconnectInterval == other.m_reconnectInterval;}
	bool isIdentical(const ConnectionBase& other) const;

//	static unsigned __int64 CalculateIpPort(unsigned int ip, unsigned short port){return ((unsigned __int64)ip << 16) | (unsigned __int64)port;}

	unsigned int GetReconnectTries() const{return m_reconnectTries;}
	unsigned int GetMaxReconnectTries() const{return m_maxReconnectTries;}
	virtual unsigned int GetReconnectCount() const{return 0;}

	void SetReconnectTries(unsigned int tries){m_reconnectTries = tries;}
	void SetMaxReconnectTries(unsigned int tries){m_maxReconnectTries = tries;}
	void ResetReconnectTries(){m_reconnectTries = m_maxReconnectTries;}
	bool isReconnectable() const{return GetReconnectCount() < m_reconnectTries;}

	virtual void UpdatePrevious()
	{
		ConnectionLine* connectionLine = GetCurrentConnectionLine();
		if(connectionLine)connectionLine->UpdatePrevious();
//		m_prevAddress = m_address;
//		m_prevPort = m_port;
		m_prevConnectionDataType = m_connectionDataType;
	}

	ConnectionBase& operator=(const ConnectionBase& other);
	const ConnectionLine* CreateNextIpAddress();
protected:
	ConnectionBase(const char* connectionName,
/*
		const char* address,
		const unsigned short port,
		const char* address2,
		const unsigned short port2,
*/
		const unsigned char connectionDataType,
		unsigned int receiveBufferSize = 0xFFFFFFFF,
		unsigned int sendBufferSize = 0xFFFFFFFF,
		int reconnectInterval = 5,
		unsigned int reconnectTries = 0,
		unsigned int maxReconnectTries = 0xFFFFFFFF,
/*
		const char* bindAddress = NULL,
		unsigned short bindPort = 0,
		const char* bindAddress2 = NULL,
		unsigned short bindPort2 = 0,
*/
		const char* loginID = "",
		const char* password = "")
		: m_connectionName( connectionName )
/*
		, m_addressName( address )
		, m_addressName1( address )
		, m_addressName2( address2 )
		, m_bindAddress(bindAddress ? bindAddress : "0.0.0.0")
		, m_bindAddress1(bindAddress ? bindAddress : "0.0.0.0")
		, m_bindAddress2(bindAddress2 ? bindAddress2 : "0.0.0.0")
*/
		, m_loginID( loginID )
		, m_password( password )
/*
		, m_ipport(0)
		, m_port( port )
		, m_port1( port )
		, m_port2( port2 )
		, m_prevPort(port)
		, m_bindPort(bindPort)
		, m_bindPort1(bindPort)
		, m_bindPort2(bindPort2)
*/
		, m_connectionDataType(connectionDataType)
		, m_prevConnectionDataType(connectionDataType)
		, m_reconnectInterval( reconnectInterval )
/*
		, m_ipNumAddress(0)
		, m_ipInvAddress(0)
		, m_ipNumBindAddress(0)
		, m_ipInvBindAddress(0)
*/
		, m_bufferSizeReceiveRequested(receiveBufferSize)
		, m_bufferSizeSendRequested(sendBufferSize)
		, m_reconnectTries(reconnectTries)
		, m_maxReconnectTries(maxReconnectTries)
		, m_connectionLineChain(0xFFFFFFFF, false)
	{
		UpdatePrevious();
	}
	ConnectionBase(const ConnectionBase& other):
		m_connectionName(other.m_connectionName),
		m_loginID(other.m_loginID),
		m_password(other.m_password),
		m_connectionDataType(other.m_connectionDataType),
		m_prevConnectionDataType(other.m_connectionDataType),
		m_reconnectInterval(other.m_reconnectInterval),
		m_bufferSizeReceiveRequested(other.m_bufferSizeReceiveRequested),
		m_bufferSizeSendRequested(other.m_bufferSizeSendRequested),
		m_reconnectTries(other.m_reconnectTries),
		m_maxReconnectTries(other.m_maxReconnectTries),
		m_connectionLineChain(other.m_connectionLineChain)
	{
		ResetConnectionLines();
		CreateNextIpAddress();
		UpdatePrevious();
	}
//	void UpdateIpPort(){m_ipport = CalculateIpPort(m_ipInvAddress, m_port);}
	std::string	m_connectionName;
	std::string	m_loginID;
	std::string m_password;
/*
	std::string	m_addressName;
	std::string	m_addressName1;
	std::string	m_addressName2;
	std::string m_address;
	std::string m_prevAddress;
	std::string m_bindAddress;
	std::string m_bindAddress1;
	std::string m_bindAddress2;

	unsigned __int64 m_ipport;
	unsigned short m_port;
	unsigned short m_port1;
	unsigned short m_port2;
	unsigned short m_prevPort;
	unsigned short m_bindPort;
	unsigned short m_bindPort1;
	unsigned short m_bindPort2;

	unsigned int m_ipNumAddress;
	unsigned int m_ipInvAddress;
	unsigned int m_ipNumBindAddress;
	unsigned int m_ipInvBindAddress;
*/
	unsigned char m_connectionDataType;
	unsigned char m_prevConnectionDataType;
	unsigned long m_reconnectInterval;
	unsigned int m_bufferSizeReceiveRequested;
	unsigned int m_bufferSizeSendRequested;

	unsigned int m_reconnectTries;
	unsigned int m_maxReconnectTries;

	ThreadSafeChain<ConnectionLine> m_connectionLineChain;
//	ConnectionLineVector m_connectionLineVector;
//	IpPortSet m_ipPortSet;
};

class TD_API ActiveConnection : public ConnectionBase
{
public:
	unsigned int GetBufferSizeReceiveActual() const{return m_bufferSizeReceiveActual;}
	unsigned int GetBufferSizeSendActual() const{return m_bufferSizeSendActual;}

	bool isConnected() const{return m_bConnected;}
	bool isConnecting() const{return m_bConnecting;}
	bool isDisconnecting() const{return m_bDisconnecting;}

	unsigned short GetLocalPort() const{return m_localPort;}

	virtual unsigned int GetBytesReceived() const{return 0;}
	virtual unsigned int GetBytesSent() const{return 0;}
protected:
	ActiveConnection(const char* connectionName, 
/*
		const char* address,
		const unsigned short port,
		const char* address2,
		const unsigned short port2,
*/
		const unsigned char connectionDataType,
		unsigned int receiveBufferSize = 0xFFFFFFFF,
		unsigned int sendBufferSize = 0xFFFFFFFF,
		int reconnectSeconds = 5,
		unsigned int reconnectTries = 0,
		unsigned int maxReconnectTries = 0xFFFFFFFF,
/*
		const char* bindAddress = NULL,
		unsigned short bindPort = 0,
		const char* bindAddress2 = NULL,
		unsigned short bindPort2 = 0,
*/
		const char* loginID = "",
		const char* password = ""):

		ConnectionBase(connectionName,
/*
			address,
			port,
			address2,
			port2,
*/
			connectionDataType,
			receiveBufferSize,
			sendBufferSize,
			reconnectSeconds,
			reconnectTries,
			maxReconnectTries,
/*
			bindAddress,
			bindPort,
			bindAddress2,
			bindPort2,
*/
			loginID,
			password)
		, m_bufferSizeReceiveActual(0)
		, m_bufferSizeSendActual(0)
		, m_localPort(0)
		, m_bConnected(false)
		, m_bConnecting(false)
		, m_bDisconnecting(false)
	{
	}
	ActiveConnection(const ConnectionBase& connectionBase):
		ConnectionBase(connectionBase),
		m_bufferSizeReceiveActual(0),
		m_bufferSizeSendActual(0),
		m_localPort(0),
		m_bConnected(false),
		m_bConnecting(false),
		m_bDisconnecting(false)
	{
	}
	unsigned int m_bufferSizeReceiveActual;
	unsigned int m_bufferSizeSendActual;
	unsigned short m_localPort;
	bool m_bConnected;
	bool m_bConnecting;
	bool m_bDisconnecting;
};

class TD_API Connection : public ConnectionBase
{
public:
	Connection(const char* connectionName, 
/*
		const char* address,
		const unsigned short port,
		const char* address2,
		const unsigned short port2,
*/
		const unsigned char connectionDataType,
		unsigned int receiveBufferSize = 0xFFFFFFFF,
		unsigned int sendBufferSize = 0xFFFFFFFF,
		int reconnectSeconds = 5,
		unsigned int reconnectTries = 0,
		unsigned int maxReconnectTries = 0xFFFFFFFF,
/*
		const char* bindAddress = NULL,
		unsigned short bindPort = 0,
		const char* bindAddress2 = NULL,
		unsigned short bindPort2 = 0,
*/
		const char* loginID = "",
		const char* password = "");
//	virtual bool SetIpAddressAndPort(const char* ip, unsigned short port);
//	virtual bool SetBindIpAddressAndPort(const char* ip = NULL, unsigned short port = 0);
	Connection(const ConnectionBase& connectionBase);
};

class TMsgSecurity : public Message
{
public:
	Security* m_security;
protected:
	TMsgSecurity(Security* security, unsigned short type, unsigned short length):Message(type, length), m_security(security){}
};

class TMsgSecurityDelete : public TMsgSecurity
{
public:
	TMsgSecurityDelete(Security* security):TMsgSecurity(security, TM_STOCK_DELETE, sizeof(TMsgSecurityDelete)){}
};

class TMsgPositionSecurityInitialized : public TMsgSecurity
{
public:
	TMsgPositionSecurityInitialized(Security* security):TMsgSecurity(security, TM_POSITION_SECURITY_INITIALIZED, sizeof(TMsgPositionSecurityInitialized)){}
};

class TMsgPositionSecurityUpdated : public TMsgSecurity
{
public:
	TMsgPositionSecurityUpdated(Security* security):TMsgSecurity(security, TM_POSITION_SECURITY_UPDATED, sizeof(TMsgPositionSecurityUpdated)){}
};

class PositionPhantomSharesChanged : public Message
{
public:
	PositionPhantomSharesChanged(char phantomShares):Message(TM_POSITION_PHANTOM_SHARES_CHANGED, sizeof(PositionPhantomSharesChanged)), m_phantomShares(phantomShares){}
	char m_phantomShares;
};

class TMsgOrder : public Message
{
public:
	Order* m_order;
protected:
	TMsgOrder(Order* order, unsigned short type, unsigned short length):Message(type, length), m_order(order){}
};

class TMsgNewOrder : public TMsgOrder
{
public:
	TMsgNewOrder(Order* order):TMsgOrder(order, TM_NEW_ORDER, sizeof(TMsgNewOrder)){}
};

class TMsgDeadOrder : public TMsgOrder
{
public:
	TMsgDeadOrder(Order* order):TMsgOrder(order, TM_DEAD_ORDER, sizeof(TMsgDeadOrder)){}
};

class TMsgOrderDelete : public TMsgOrder
{
public:
	TMsgOrderDelete(Order* order):TMsgOrder(order, TM_ORDER_DELETE, sizeof(TMsgOrderDelete)){}
};

class TMsgUpdatedOrder : public TMsgOrder
{
public:
	TMsgUpdatedOrder(Order* order):TMsgOrder(order, TM_UPDATED_ORDER, sizeof(TMsgUpdatedOrder)){}
};

class TMsgExecution : public Message
{
public:
	Execution* m_execution;
protected:
	TMsgExecution(Execution* execution, unsigned short type, unsigned short length):Message(type, length), m_execution(execution){}
};

class TMsgNewExecution : public TMsgExecution
{
public:
	TMsgNewExecution(Execution* execution, unsigned int remainingQuantity):TMsgExecution(execution, TM_NEW_EXECUTION, sizeof(TMsgNewExecution)), m_remainingQuantity(remainingQuantity){}
	unsigned int m_remainingQuantity;
};

class TMsgPositionDataObject : public Message
{
public:
	const PositionData* m_position;
protected:
	TMsgPositionDataObject(const PositionData* position, unsigned short type, unsigned short length):Message(type, length), m_position(position){}
};

class TMsgPositionObject : public Message
{
public:
	const Position* m_position;
protected:
	TMsgPositionObject(const Position* position, unsigned short type, unsigned short length):Message(type, length), m_position(position){}
};

class TMsgNewPosition : public TMsgPositionObject
{
public:
	TMsgNewPosition(const Position* position):TMsgPositionObject(position, TM_NEW_POSITION, sizeof(TMsgNewPosition)){}
};
/*
class TMsgAddPositionToSecurity : public TMsgPositionObject
{
public:
	TMsgAddPositionToSecurity(Position* position, Security* security):TMsgPositionObject(position, TM_ADD_POSITION_TO_SECURITY, sizeof(TMsgAddPositionToSecurity)), m_security(security){}
	Security* m_security;
};
*/
class TMsgUpdatedPosition : public TMsgPositionDataObject
{
public:
	TMsgUpdatedPosition(const PositionData* position):TMsgPositionDataObject(position, TM_UPDATED_POSITION, sizeof(TMsgUpdatedPosition)){}
};

class TMsgExecutedPosition : public TMsgPositionObject
{
public:
	TMsgExecutedPosition(const Position* position, unsigned char positionUpdateFlags):TMsgPositionObject(position, TM_EXECUTED_POSITION, sizeof(TMsgExecutedPosition)), m_positionUpdateFlags(positionUpdateFlags){}
	unsigned char m_positionUpdateFlags;
};

class TMsgDeleteAllAccounts : public Message
{
public:
	TMsgDeleteAllAccounts():Message(TM_DELETE_ALL_ACCOUNTS, sizeof(TMsgDeleteAllAccounts)){}
};

class TMsgAccount : public Message
{
public:
	Account* m_account;
protected:
	TMsgAccount(Account* account, unsigned short type, unsigned short length):Message(type, length), m_account(account){}
};
/*
class TMsgAccountObject : public Message
{
public:
	char m_accountId[MAX_ACCOUNT_SIZE];
protected:
	TMsgAccountObject(const char* accountName, unsigned short type, unsigned short length):
		Message(type, length)
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountName, '\0');
	}
};
*/

class TMsgHardBuyingPowerHit : public TMsgAccountObject
{
public:
	TMsgHardBuyingPowerHit(const char* accountName, const Money& hardBpUsed, const Money& hardBuyingPower, bool hardBpHit):
		TMsgAccountObject(accountName, TM_HARD_BP_HIT, sizeof(TMsgHardBuyingPowerHit)),
		m_hardBpUsed(hardBpUsed),
		m_hardBuyingPower(hardBuyingPower),
		m_hardBpHit(hardBpHit)
	{
	}
	Money m_hardBpUsed;
	Money m_hardBuyingPower;
	bool m_hardBpHit;
};

class TMsgAccountDelete : public TMsgAccount
{
public:
	TMsgAccountDelete(Account* account):TMsgAccount(account, TM_ACCOUNT_DELETE, sizeof(TMsgAccountDelete)){}
};

class TMsgUpdatedAccountBase : public TMsgAccount
{
public:
	bool m_constraintsChanged;
protected:
	TMsgUpdatedAccountBase(Account* account, bool constraintsChanged, unsigned short type, unsigned short length):TMsgAccount(account, type, length), m_constraintsChanged(constraintsChanged){}
};

class TMsgUpdatedAccount : public TMsgUpdatedAccountBase
{
public:
	TMsgUpdatedAccount(Account* account, bool constraintsChanged):TMsgUpdatedAccountBase(account, constraintsChanged, TM_UPDATED_ACCOUNT, sizeof(TMsgUpdatedAccount)){}
};

class TMsgUpdatedAccountAndPosition : public TMsgUpdatedAccountBase//used for providing "info" to the Notify function
{
public:
	TMsgUpdatedAccountAndPosition(Account* account, bool constraintsChanged, const Position* position):TMsgUpdatedAccountBase(account, constraintsChanged, TM_UPDATED_ACCOUNT_AND_POSITION, sizeof(TMsgUpdatedAccountAndPosition)), m_position(position){}
	const Position* m_position;
};

class TMsgNewAccountObject : public TMsgAccount
{
public:
	TMsgNewAccountObject(Account* account):TMsgAccount(account, TM_NEW_ACCOUNT, sizeof(TMsgNewAccountObject)){}
};

class TMsgConnectionObject : public Message
{
public:
	TMsgConnectionObject(Connection* connection):Message(TM_CONNECTION_OBJECT, sizeof(TMsgConnectionObject)), m_connection(connection){}
	Connection* m_connection;
};

class TMsgSetTierSize : public TMessageSymbol//sent internally to threads
{
public:
	unsigned int m_newTierSize;
protected:
	TMsgSetTierSize(const char* symbol, unsigned int newTierSize, unsigned short type, unsigned short length):TMessageSymbol(symbol, type, length),m_newTierSize(newTierSize){}
	TMsgSetTierSize(const unsigned __int64& symbol, unsigned int newTierSize, unsigned short type, unsigned short length):TMessageSymbol(symbol, type, length),m_newTierSize(newTierSize){}
};

class TMsgSetStockTierSize : public TMsgSetTierSize//sent internally to threads
{
public:
	TMsgSetStockTierSize(const char* symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		unsigned int newTierSize):
		TMsgSetTierSize(symbol, newTierSize, TM_SET_STOCK_TIER_SIZE, sizeof(TMsgSetStockTierSize))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{}
	TMsgSetStockTierSize(const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		unsigned int newTierSize):
		TMsgSetTierSize(symbol, newTierSize, TM_SET_STOCK_TIER_SIZE, sizeof(TMsgSetStockTierSize))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{}
	unsigned __int64 m_optionKey;
};

class TMsgSetEquityTierSize : public TMsgSetTierSize//sent internally to threads
{
public:
	TMsgSetEquityTierSize(const char* symbol, unsigned int newTierSize):TMsgSetTierSize(symbol, newTierSize, TM_SET_EQUITY_TIER_SIZE, sizeof(TMsgSetStockTierSize)){}
	TMsgSetEquityTierSize(const unsigned __int64& symbol, unsigned int newTierSize):TMsgSetTierSize(symbol, newTierSize, TM_SET_EQUITY_TIER_SIZE, sizeof(TMsgSetStockTierSize)){}
};
/*
class TMsgTierSizeChanged : public Message//notification
{
public:
	TMsgTierSizeChanged(unsigned int oldTierSize, unsigned int newTierSize):Message(TM_TIER_SIZE_CHANGED, sizeof(TMsgTierSizeChanged)),m_oldTierSize(oldTierSize),m_newTierSize(newTierSize){}
	unsigned int m_oldTierSize;
	unsigned int m_newTierSize;
};
*/
enum TakionOrderAlgorithmId
{
	TOA_SMART_SWIPE = OA_COUNT,
	TOA_SPIDER_SWIPE,
	TOA_TRIGGER,
	TOA_PRE_BORROW,
	TOA_PRE_FIRM_SUBSCRIBE,
	TOA_DUMB_SWIPE,
	TOA_MEGA_SWIPE,

	TOA_COUNT
};

class TD_API TakionAlgorithm : public OrderAlgorithm
{
public:
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual void WriteOrderCancelToMainThread();

	bool isPreBorrow() const{return m_preBorrow;}
	void SetPreBorrow(bool preBorrow){m_preBorrow = preBorrow;}
	unsigned int GetSizeToBorrow() const{return m_sizeToBorrow;}
	void SetSizeToBorrow(unsigned int size){m_sizeToBorrow = size;}
	const Price& GetPreBorrowPrice() const{return m_preBorrowPrice;}//price in cents
	void SetPreBorrowPrice(const Price& preBorrowPrice){m_preBorrowPrice = preBorrowPrice;}//price in cents
protected:
	TakionAlgorithm(const Position* position,
		unsigned int traderId,
		unsigned int clientId,
		unsigned int destinationId,
		unsigned int destinationName,

		char side,

		unsigned char orderType,
		unsigned short userOrderType,
		const char* userOrderInfo,
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

//		bool proactive,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,//XX
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		const unsigned __int64& userId,// = 0);
		bool useSecurityNotification,//XX
		unsigned int preBorrowSize);

	TakionAlgorithm(const char*& fromString, bool useSecurityNotification);
//	virtual void DoSendOrder(){}

	bool GetBorrowPrice(Price& loanPrice) const;
	void DoWriteCancel(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);//from account thread
	void CancelAndReportErrorInMainThread(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);//from main thread

	bool SendBorrow();

	bool m_blockAggressiveOrders;
	bool m_preBorrow;
	Order* m_preBorrowOrder;
	Price m_preBorrowPrice;
	unsigned int m_sizeToBorrow;
	unsigned int m_sizeBorrowed;
};

class TD_API AlgorithmPreBorrow : public TakionAlgorithm
{
public:
	AlgorithmPreBorrow(const Position* position,
		unsigned int traderId,
		unsigned int clientId,
//		unsigned int clientIdOriginal,
		unsigned int destinationId,
		unsigned int destinationName,

		char side,

		unsigned char orderType,
		unsigned short userOrderType,
		const char* userOrderInfo,
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
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		const unsigned __int64& userId,
		unsigned int preBorrowSize,
		const char* isoAttachment);// = 0);
	AlgorithmPreBorrow(const AlgorithmPreBorrow& other);
	AlgorithmPreBorrow(const char*& fromString);
	virtual ~AlgorithmPreBorrow();
	AlgorithmPreBorrow& operator=(const AlgorithmPreBorrow& other);
	virtual OrderAlgorithm* CloneAlgorithm() const;
	virtual unsigned int GetAlgorithmId() const{return TOA_PRE_BORROW;}
	virtual const char* GetAlgorithmName() const{return "PreBorrow";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	DECLARE_NED_NEW
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
//	virtual void WriteOrderCancelToMainThread();
	const char* const& GetIsoAttachment() const{return m_isoAttachment;}
//	const unsigned short& GetIsoAttachmentLength() const{return m_isoAttachmentLength;}
protected:
	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL);
	void DoSendOrder();
/*
	Order* m_preBorrowOrder;
	Price m_preBorrowPrice;
	unsigned int m_sizeToBorrow;
	unsigned int m_sizeBorrowed;
*/
	char* m_isoAttachment;
//	unsigned short m_isoAttachmentLength;
};

class TD_API TakionOrderAlgorithm : public TakionAlgorithm
{
public:
	void SetUpdated();
	bool isUpdated(unsigned int updateOrdinal) const;
	unsigned int GetInvalidateOrdinalOrderAlgorithm() const{return m_invalidateOrdinalOrderAlgorithm;}
	unsigned int GetUpdateOrdinalOrderAlgorithm() const{return m_updateOrdinalOrderAlgorithm;}
	void WriteUpdateMessageToMainThread();
//	virtual void WriteOrderCancelToMainThread();
	unsigned int GetLastExecutionMillisecond() const{return m_lastExecutionMillisecond;}
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
//	virtual unsigned int GetTotalSize() const{return m_quantity;}
protected:
	TakionOrderAlgorithm(const Position* position,
//		unsigned int traderId,
//		unsigned int clientId,
		unsigned int destinationId,
		unsigned int destinationName,

		char side,

		unsigned char orderType,
		unsigned short userOrderType,
		const char* userOrderInfo,
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

//		bool proactive,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		const unsigned __int64& userId,// = 0);
		bool useSecurityNotification,
		unsigned int preBorrowSize);

	TakionOrderAlgorithm(const char*& fromString, bool useSecurityNotification);
	bool OrderExecuted(Order* order, unsigned int executionFilledQuantity, const Price& price, unsigned int lastExecutionMillisecond);
	unsigned int m_invalidateOrdinalOrderAlgorithm;
	unsigned int m_updateOrdinalOrderAlgorithm;
	unsigned int m_lastExecutionMillisecond;
/*
	bool m_preBorrow;
	Price m_preBorrowPrice;
	Order* m_preBorrowOrder;
	unsigned int m_sizeToBorrow;
	unsigned int m_sizeBorrowed;
*/
	unsigned int m_realQuantity;

	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL);
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info);//in thread
	virtual void PreBorrowDone(){}
	void DoSendOrder();
};

class TD_API AlgorithmSwipe : public TakionOrderAlgorithm
{
public:
	typedef std::set<unsigned int> UIntSet;
	typedef std::hash_map<TradedQuote, unsigned int> TradedQuoteMap;
	virtual ~AlgorithmSwipe();
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	unsigned int CalculateFloatingLimitPrice() const;
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual bool SecurityMustBeLoaded() const{return true;}
	typedef std::hash_set<unsigned int> MmidSet;
	typedef std::hash_set<Order*> OrderSet;
protected:
	AlgorithmSwipe(const Position* position,
		unsigned int destinationName,

		char side,

		unsigned short userOrderType,
		const char* userOrderInfo,
		const Price& limitPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

		unsigned short routingId,
		unsigned int routingName,

		unsigned int roundLot,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool hideSlowQuotes,

		char tifType,
		unsigned int tifMillisecond,

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

		unsigned int parentId,// = 0,
		const unsigned __int64& userId,
//		bool spider,
		bool useSecurityNotification,
		unsigned int preBorrowSize);// = 0);

	AlgorithmSwipe(const char*& fromString, bool spider);

//	void DoWriteCancel(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);
	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL);
//	bool CanGrabQuote(const MsgQuote& quote, bool bidQuote) const;
	bool CanGrabQuote(unsigned char source, unsigned char bookId, const Price& price, unsigned int mmid, unsigned char quoteCondition, bool bidQuote) const;
	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = NULL) const;
	virtual void DoSecurityUpdate();
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = NULL);
	void InitializeFloatingLimitPrice();
	virtual void StartSwiping();
	virtual void Swipe(){}
	virtual void PreBorrowDone();
	TakionIterator* m_quoteIterator;
	bool m_bypassedQuote;
	bool m_nasdaq;
	bool m_hideSlowQuotes;
//	bool m_blockAggressiveOrders;
	bool m_excludeDestinations;
	UIntSet m_destinationSet;
	UIntSet m_filterSet;
	TradedQuoteMap m_tradedQuotes;
	TradedQuoteMap m_currentOrderQuotes;
	MmidSet m_rejectedMmids;

	bool m_postRemainder;
	unsigned int m_postDestination;
	unsigned int m_postDestinationName;
	unsigned int m_postRoutingName;
	unsigned short m_postRoutingId;
	unsigned short m_postRoutingSubType;
	unsigned int m_postMnemonic;
	unsigned char m_postTifType;
	unsigned int m_postTif;
	bool m_postRemainderOnIsoViolation;

	unsigned int m_floatingLimitPriceCompact;

	OrderSet m_liveOrders;
	OrderSet::const_iterator m_liveOrdersEnd;
};

class TD_API AlgorithmSmartSwipe : public AlgorithmSwipe//TakionOrderAlgorithm
{
public:
//	typedef std::set<unsigned int> UIntSet;
//	typedef std::hash_map<TradedQuote, unsigned int> TradedQuoteMap;
	AlgorithmSmartSwipe(const Position* position,
//		unsigned int destinationId,

		char side,

		unsigned short userOrderType,
		const char* userOrderInfo,
//		unsigned char orderType,
		const Price& limitPrice,
//		const Price& level1Price,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

		unsigned short routingId,
		unsigned int routingName,

//		bool proactive,
//		bool iso,
		unsigned int roundLot,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool hideSlowQuotes,

		char tifType,
		unsigned int tifMillisecond,

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

		unsigned int parentId,// = 0,
		const unsigned __int64& userId,
		bool spider,
		unsigned int preBorrowSize);// = 0);
	AlgorithmSmartSwipe(const char*& fromString, bool spider);
//	virtual ~AlgorithmSmartSwipe();
	virtual OrderAlgorithm* CloneAlgorithm() const;
	virtual const char* GetAlgorithmName() const{return m_useSecurityNotification ? "Spider" : "SmartSwipe";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	DECLARE_NED_NEW
//	unsigned int CalculateFloatingLimitPrice() const;
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual unsigned int GetAlgorithmId() const{return m_useSecurityNotification ? TOA_SPIDER_SWIPE : TOA_SMART_SWIPE;}
//	virtual bool SecurityMustBeLoaded() const{return true;}
//	typedef std::hash_set<unsigned int> MmidSet;
protected:
//	void DoWriteCancel(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);
//	bool CanGrabQuote(const MsgQuote& quote, bool bidQuote) const;
//	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = NULL) const;
//	virtual void DoSecurityUpdate();
//	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = NULL);
//	void InitializeFloatingLimitPrice();
//	virtual void StartSwiping();
	virtual void Swipe();
//	virtual void PreBorrowDone();
//	Order* m_order;
//	Order* m_orderSplit;
//	TakionIterator* m_quoteIterator;
/*
	bool m_bypassedQuote;
	bool m_nasdaq;
	bool m_hideSlowQuotes;
	bool m_blockAggressiveOrders;
	bool m_excludeDestinations;
	UIntSet m_destinationSet;
	UIntSet m_filterSet;
	TradedQuoteMap m_tradedQuotes;
	TradedQuoteMap m_currentOrderQuotes;
	MmidSet m_rejectedMmids;
*/
//	unsigned int m_floatingLimitPriceCompact;
};

class TD_API AlgorithmDumbSwipe : public AlgorithmSwipe//TakionOrderAlgorithm
{
public:
	AlgorithmDumbSwipe(const Position* position,

		char side,

		unsigned short userOrderType,
		const char* userOrderInfo,
		const Price& limitPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

		unsigned short routingId,
		unsigned int routingName,

		unsigned int roundLot,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool hideSlowQuotes,

		char tifType,
		unsigned int tifMillisecond,

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

		unsigned int parentId,// = 0,
		const unsigned __int64& userId,
		bool spider,
		unsigned int preBorrowSize);// = 0);
	AlgorithmDumbSwipe(const char*& fromString, bool spider);
	virtual OrderAlgorithm* CloneAlgorithm() const;
//	virtual const char* GetAlgorithmName() const{return m_useSecurityNotification ? "Spider" : "SmartSwipe";}
	virtual const char* GetAlgorithmName() const{return "DumbSwipe";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	DECLARE_NED_NEW
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
//	virtual unsigned int GetAlgorithmId() const{return m_useSecurityNotification ? TOA_SPIDER_SWIPE : TOA_SMART_SWIPE;}
	virtual unsigned int GetAlgorithmId() const{return TOA_DUMB_SWIPE;}
	bool isReiterate() const{return m_reiterate;}
	void SetReiterate(bool reiterate){m_reiterate = reiterate;}
protected:
	virtual void Swipe();
	bool m_reiterate;
};

class TD_API AlgorithmMegaSwipe : public AlgorithmSwipe//TakionOrderAlgorithm
{
public:
	AlgorithmMegaSwipe(const Position* position,

		char side,

		unsigned short userOrderType,
		const char* userOrderInfo,
		const Price& limitPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

		unsigned short routingId,
		unsigned int routingName,

		unsigned int roundLot,
		bool cancelWashOrders,
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool hideSlowQuotes,

		char tifType,
		unsigned int tifMillisecond,

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

		unsigned int parentId,// = 0,
		const unsigned __int64& userId,
		bool spider,
		unsigned int preBorrowSize);// = 0);
	AlgorithmMegaSwipe(const char*& fromString, bool spider);
	virtual OrderAlgorithm* CloneAlgorithm() const;
	virtual const char* GetAlgorithmName() const{return "MegaSwipe";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	DECLARE_NED_NEW
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual unsigned int GetAlgorithmId() const{return TOA_MEGA_SWIPE;}
	virtual unsigned int GetAlgorithmQuantity() const{return m_quantity * m_orderToSendCount;}
protected:
	virtual void Swipe();
	unsigned int m_orderToSendCount;
};

class TD_API AlgorithmTrigger : public TakionOrderAlgorithm
{
public:
	AlgorithmTrigger(const Position* position,
		char side,
		unsigned short userOrderType,
		const char* userOrderInfo,
//		unsigned char orderType,
		const SignedPrice& stopPrice,
		char tifType,
		unsigned int tifMillisecond,
		unsigned int tierSize,
		unsigned int parentId,// = 0,
		const unsigned __int64& userId,
		unsigned char triggerType,
		bool mustSubscribe,
		bool resetPrintSize,
		unsigned __int64 printSize,
		bool closeOnly,
		bool passiveOnly,
		int count,
		const char* commandName);
	AlgorithmTrigger(const char*& fromString);
	virtual ~AlgorithmTrigger();
	static const char* const triggerVenue;
	virtual OrderAlgorithm* CloneAlgorithm() const;
	virtual const char* GetAlgorithmName() const{return "Trigger";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	DECLARE_NED_NEW
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual unsigned int GetAlgorithmId() const{return TOA_TRIGGER;}
	virtual bool SecurityMustBeLoaded() const{return true;}
	virtual bool isQuantityValid() const{return true;}
	virtual bool isPriceValid() const;
	virtual void ProcessMainThreadNotification(unsigned short code);
	bool isConditionAlreadyMet(Money& condition) const;
	virtual bool HasPrice() const;
	virtual bool HasSize() const;
	bool MustWatchLevel2() const;
//	bool QuoteGreaterApplies(const MsgQuote& quote, bool bid) const;
	bool QuoteGreaterApplies(unsigned char bookId, const Price& quotePrice, bool bid) const;
	bool QuoteLessApplies(unsigned char bookId, bool bid) const;
	bool isFollowPosition() const;
	bool PositionApplies(int executionSize) const;
	unsigned char CalculateRiPercent(Money& percent) const;//0 - condition already met; 1 - not met; 2: check value 'percent' to find out if met.
	unsigned char CalculateNyseImbalance(int& imbalance) const;//0 - condition already met; 1 - not met; 2: check value 'percent' to find out if met.
	unsigned char isRiPercenAlreadyMet(Money& percent) const;//0 - not the right type; 1 - not met; 2 - met; 3 - not applicable
	unsigned char isNyseImbalanceAlreadyMet(int& imbalance) const;//0 - not the right type; 1 - not met; 2 - met; 3 - not applicable
//	virtual unsigned int GetTotalSize() const{return m_printSize > 0xFFFFFFFF ? 0xFFFFFFFF : (unsigned int)m_printSize;}
	virtual const std::string& GetStopOrderTypeStr() const;
	virtual const std::string& GetStopOrderBaseStr() const;
	virtual unsigned int GetAlgorithmQuantity() const{return m_printSize > 0xFFFFFFFF ? 0xFFFFFFFF : (unsigned int)m_printSize;}
protected:
	virtual void NullifySecurity();
	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL);
	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = NULL) const;
	virtual void DoSecurityUpdate();
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = NULL);

//	bool TriggerByLastNbboPrint();
	bool TriggerByPrice(const Price& price, unsigned int printSize);

//	bool Done(const Price& price, unsigned printSize);
	bool Done(unsigned printSize);

	unsigned char m_triggerType;
	bool m_mustSubscribe;

	int m_count;
	bool m_closeOnly;
	bool m_passiveOnly;

	std::string m_commandName;

	std::string m_symbol;
	Price m_priceTo;
	Price m_priceFrom;
	bool m_initialized;
	bool m_done;

	bool m_inPrice;

	bool m_resetPrintSize;
	unsigned __int64 m_printSize;
	unsigned __int64 m_accumulatedPrintSize;

	mutable int m_prevIntValue;//for imbalnces
	mutable Money m_prevMoneyValue;//for imbalnce percentages

//	Position* m_position;
	const Book* m_book;

	Observable* m_newEquityObservable;
};

class TD_API AlgorithmOrderReplacer : public OrderReplacer
{
public:
	AlgorithmOrderReplacer(const Position* position,
		unsigned int orderToReplaceClientId,
		unsigned int traderId,
		unsigned int clientId,
//		unsigned int clientIdOriginal,
		unsigned int destinationId,
		unsigned int destinationName,

		char side,

		unsigned char orderType,
		unsigned short userOrderType,
		const char* userOrderInfo,
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
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool proAts,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		const unsigned __int64& userId);// = 0);
//	AlgorithmSmartSwipe(const AlgorithmSmartSwipe& other):OrderAlgorithm(other){}
	AlgorithmOrderReplacer(const char*& fromString);
//	virtual ~AlgorithmOrderReplacer();
	virtual OrderAlgorithm* CloneAlgorithm() const;
//	virtual const char* GetAlgorithmName() const{return "Replacer";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	DECLARE_NED_NEW
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
//	virtual unsigned int GetAlgorithmId() const{return OA_ORDER_REPLACER;}
//	typedef std::hash_set<unsigned int> MmidSet;
	virtual void WriteOrderCancelToMainThread();
protected:
	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL);
	virtual void DoSendReplacement();
};

class TD_API ClientExtensionDll : public ExtensionDll
{
public:
	static const unsigned int validExtensionCode = 1;
	ClientExtensionDll(const char* absolutePath):ExtensionDll(absolutePath){}
	ClientExtensionDll(const char* name, const char* path):ExtensionDll(name, path){}
	virtual unsigned int GetValidExtensionCode() const{return validExtensionCode;}
protected:
};

class TD_API NewsDll : public BaseExtensionDll//, public Observable
{
public:
	virtual ~NewsDll();
	virtual bool Unload();
	virtual bool Load();
	unsigned char Connect(const char* hostName,
		unsigned short port,
		const char* userName,
		const char* password,
		const char* appName,
		const char* appVersion,
		const char* companyName,
		const char* sessionData,
		const char* proxyIpAddress,
		unsigned short proxyPort,
		const char* proxyProtocolName,
		const char* proxyUserName,
		const char* proxyPassword,
		const char* newPassword) const;
	bool isConnected() const{return m_IsNewsConnectedFunction && m_IsNewsConnectedFunction();}
//	void AddObserver(Observer* observer);
	Observable* GetObservable() const{return m_NewsGetObservableFunction ? m_NewsGetObservableFunction() : NULL;}
	void SetLogFile(void* logFileHandle) const{if(m_NewsSetLogFileFunction)m_NewsSetLogFileFunction(logFileHandle);}
	Observable* GetStockNews(Observable* oldStockNews, const Observable* newsCollection, const unsigned __int64& symbol) const{return m_NewsGetStockNewsByNum ? m_NewsGetStockNewsByNum(oldStockNews, newsCollection, symbol) : NULL;}
	Observable* GetStockNews(Observable* oldStockNews, const Observable* newsCollection, const char* symbol) const{return m_NewsGetStockNewsByCharPtr ? m_NewsGetStockNewsByCharPtr(oldStockNews, newsCollection, symbol) : NULL;}
	Observable* FindStockNews(const Observable* newsCollection, const unsigned __int64& symbol) const{return m_NewsFindStockNewsByNum ? m_NewsFindStockNewsByNum(newsCollection, symbol) : NULL;}
	Observable* GetStringNews(Observable* oldStockNews, const Observable* newsCollection, const FilterStringAsNumberArray& str, const std::hash_set<unsigned __int64>* stockSet) const{return m_NewsGetStringNews ? m_NewsGetStringNews(oldStockNews, newsCollection, str, stockSet) : NULL;}
	Observable* FindStringNews(const Observable* newsCollection, const FilterStringAsNumberArray& str) const{return m_NewsFindStringNews ? m_NewsFindStringNews(newsCollection, str) : NULL;}
	bool DoIdle(LONG count) const{return m_NewsDoIdle && m_NewsDoIdle(count);}
	unsigned char ReleaseNewsCollection(Observable* newsCollection, Observer* observer) const{return m_NewsReleaseNewsCollection ? m_NewsReleaseNewsCollection(newsCollection, observer) : 0;}
	Observable* UpdateNewsCollectionFilter(Observable* newsCollection, Observer* observer, const WireSet& wireSet, unsigned int storyFilter, unsigned int metaFilter, unsigned int relevance) const{return m_NewsUpdateNewsCollectionFilter ? m_NewsUpdateNewsCollectionFilter(newsCollection, observer, wireSet, storyFilter, metaFilter, relevance) : NULL;}

	unsigned int GetWireCount() const{return m_NewsGetWireCount ? m_NewsGetWireCount() : 0;}
	bool GetWireInfoAt(unsigned int at, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled) const{return m_NewsGetWireInfoAt && m_NewsGetWireInfoAt(at, description, id, subid, subwire, entitled);}
	TakionIterator* CreateWireIterator() const{return m_NewsCreateWireIterator ? m_NewsCreateWireIterator() : NULL;}
	bool GetNextWireInfo(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled) const{return m_NewsGetNextWireInfo && m_NewsGetNextWireInfo(iterator, description, id, subid, subwire, entitled);}

	const char* GetConnectionStatusInfo() const{return m_NewsGetConnectionStatusInfo ? m_NewsGetConnectionStatusInfo() : "";}
	unsigned int GetAllWireCount() const{return m_NewsGetAllWireCount ? m_NewsGetAllWireCount() : 0;}
//	bool GetAllWireInfoAt(unsigned int at, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled) const{return m_NewsGetAllWireInfoAt && m_NewsGetAllWireInfoAt(at, description, id, subid, subwire, entitled);}
	TakionIterator* CreateAllWireIterator() const{return m_NewsCreateAllWireIterator ? m_NewsCreateAllWireIterator() : NULL;}
	bool GetNextAllWireInfo(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, bool& subwire, bool& entitled) const{return m_NewsGetNextAllWireInfo && m_NewsGetNextAllWireInfo(iterator, description, id, subid, subwire, entitled);}

	unsigned int GetTopicCount() const{return m_NewsGetTopicCount ? m_NewsGetTopicCount() : 0;}
	TakionIterator* CreateTopicIterator() const{return m_NewsCreateTopicIterator ? m_NewsCreateTopicIterator() : NULL;}
	const std::string* GetNextTopicInfo(TakionIterator* iterator, std::string* description) const{return m_NewsGetNextTopicInfo ? m_NewsGetNextTopicInfo(iterator, description) : NULL;}

	void AdjustToChangedScreen(int dx, int dy) const{if(m_NewsAdjustToChangedScreen)m_NewsAdjustToChangedScreen(dx, dy);}

	void DisplayFilterDialog(CWnd* receipient,
		unsigned int code,
		const WireSet& wireSet,
		unsigned int storyFilter,
		unsigned int metaFilter,
		unsigned int relevance,
		CWnd* parent,
		const CPoint& mousePoint) const;
	bool GetFilterDialogValues(WireSet& wireSet,
		unsigned int& storyFilter,
		unsigned int& metaFilter,
		unsigned int& relevance) const;
	
	void DisplayLimitsDialog(CWnd* receipient,
		unsigned int code,
		unsigned short daysBack,
		unsigned short headlineCount,
		CWnd* parent,
		const CPoint& mousePoint) const;
	bool GetLimitsDialogValues(unsigned short& daysBack,
		unsigned short& headlineCount) const;
	
	bool RequestHeadlines(Observable* stockNews, unsigned short daysBack, unsigned short headlineCount) const{return m_NewsRequestHeadlines && m_NewsRequestHeadlines(stockNews, daysBack, headlineCount);}
	bool RequestStory(const NewsHeadline* headline, bool showChain) const{return m_NewsRequestStory && m_NewsRequestStory(headline, showChain);}

	const LineBufferArray* GetUnappliedHeadlines(Observable* stockNews) const{return m_NewsGetUnappliedHeadlines ? m_NewsGetUnappliedHeadlines(stockNews) : NULL;}
	Observable* FindNewsCollectionById(unsigned int id) const{return m_NewsFindNewsCollectionById ? m_NewsFindNewsCollectionById(id) : NULL;}
	bool isUpdatedHeadline(Observable* stockNews, unsigned int updateOrdinal) const{return m_NewsIsUpdatedHeadline && m_NewsIsUpdatedHeadline(stockNews, updateOrdinal);}
	void SetUpdatedHeadline(Observable* stockNews) const{if(m_NewsSetUpdatedHeadline)m_NewsSetUpdatedHeadline(stockNews);}
	void ReadNewHeadlines(Observable* stockNews) const{if(m_NewsReadNewHeadlines)m_NewsReadNewHeadlines(stockNews);}
	void ReleaseNewHeadlines(Observable* stockNews) const{if(m_NewsReleaseNewHeadlines)m_NewsReleaseNewHeadlines(stockNews);}
	const NewsHeadline* FindHeadline(const Observable* stockNews, const NewsResourceAsNumberArray& resourceId) const{return m_NewsFindHeadline ? m_NewsFindHeadline(stockNews, resourceId) : NULL;}

	unsigned int GetHeadlineCount(const Observable* stockNews) const{return m_NewsGetHeadlineCount ? m_NewsGetHeadlineCount(stockNews) : 0;}
	TakionIterator* CreateHeadlineIterator(const Observable* stockNews) const{return m_NewsCreateHeadlineIterator ? m_NewsCreateHeadlineIterator(stockNews) : NULL;}
	const NewsHeadline* GetNextHeadline(TakionIterator* iterator) const{return m_NewsGetNextHeadline ? m_NewsGetNextHeadline(iterator) : NULL;}

	bool LockInquiryHeadlines(Observable* stockNews)const{return m_NewsLockInquiryHeadlines && m_NewsLockInquiryHeadlines(stockNews);}
	void LockInquiryWaitHeadlines(Observable* stockNews)const{if(m_NewsLockInquiryWaitHeadlines)m_NewsLockInquiryWaitHeadlines(stockNews);}
	void UnlockInquiryHeadlines(Observable* stockNews)const{if(m_NewsUnlockInquiryHeadlines)m_NewsUnlockInquiryHeadlines(stockNews);}

	bool isStockNewsRequested(const Observable* stockNews) const{return !m_NewsIsStockNewsRequested || m_NewsIsStockNewsRequested(stockNews);}
	const std::string* GetSearchStringAll() const{return m_NewsGetSearchStringAll ? m_NewsGetSearchStringAll() : NULL;}
	const std::string* GetSearchStringAllUs() const{return m_NewsGetSearchStringAllUs ? m_NewsGetSearchStringAllUs() : NULL;}

	const NewsStory* FindStoryByResourceId(const NewsResourceAsNumberArray& resourceId) const{return m_NewsFindStoryByResourceId ? m_NewsFindStoryByResourceId(resourceId) : NULL;}
	const NewsStory* GetLastStory() const{return m_NewsGetLastStory ? m_NewsGetLastStory() : NULL;}
	bool LockInquiryStory()const{return m_NewsLockInquiryStory && m_NewsLockInquiryStory();}
	void LockInquiryWaitStory()const{if(m_NewsLockInquiryWaitStory)m_NewsLockInquiryWaitStory();}
	void UnlockInquiryStory()const{if(m_NewsUnlockInquiryStory)m_NewsUnlockInquiryStory();}
	bool isUpdatedStory(unsigned int updateOrdinal) const{return m_NewsIsUpdatedStory && m_NewsIsUpdatedStory(updateOrdinal);}
	void SetUpdatedStory() const{if(m_NewsSetUpdatedStory)m_NewsSetUpdatedStory();}
	Observable* GetStoryObservable() const{return m_NewsGetStoryObservable ? m_NewsGetStoryObservable() : NULL;}

	bool LockInquiryWireNameStorage()const{return m_NewsLockInquiryWireNameStorage && m_NewsLockInquiryWireNameStorage();}
	void LockInquiryWaitWireNameStorage()const{if(m_NewsLockInquiryWaitWireNameStorage)m_NewsLockInquiryWaitWireNameStorage();}
	void UnlockInquiryWireNameStorage()const{if(m_NewsUnlockInquiryWireNameStorage)m_NewsUnlockInquiryWireNameStorage();}

	bool LockInquiryAllWireNameStorage()const{return m_NewsLockInquiryAllWireNameStorage && m_NewsLockInquiryAllWireNameStorage();}
	void LockInquiryWaitAllWireNameStorage()const{if(m_NewsLockInquiryWaitAllWireNameStorage)m_NewsLockInquiryWaitAllWireNameStorage();}
	void UnlockInquiryAllWireNameStorage()const{if(m_NewsUnlockInquiryAllWireNameStorage)m_NewsUnlockInquiryAllWireNameStorage();}

	bool LockInquiryTopicNameStorage()const{return m_NewsLockInquiryTopicNameStorage && m_NewsLockInquiryTopicNameStorage();}
	void LockInquiryWaitTopicNameStorage()const{if(m_NewsLockInquiryWaitTopicNameStorage)m_NewsLockInquiryWaitTopicNameStorage();}
	void UnlockInquiryTopicNameStorage()const{if(m_NewsUnlockInquiryTopicNameStorage)m_NewsUnlockInquiryTopicNameStorage();}

	void ProcessConnectionInMainThread(bool connected) const{if(m_NewsProcessConnectionInMainThread)m_NewsProcessConnectionInMainThread(connected);}
	bool NewsCollectionHasProfile(const Observable* newsCollection) const{return !m_NewsCollectionHasProfile || m_NewsCollectionHasProfile(newsCollection);}
protected:
	NewsDll(const char* absolutePath);
	NewsDll(const char* name, const char* path);
	virtual bool DoLoad();
	virtual void Reset()
	{
		BaseExtensionDll::Reset();
		NullifyFunctions();
	}
	void NullifyFunctions();
	bool AdditionalUnload();
	ApiNewsConnect m_NewsConnectFunction;
	ApiIs m_IsNewsConnectedFunction;
	ApiGetObservable m_NewsGetObservableFunction;
	ApiVoidPtr m_NewsSetLogFileFunction;
	ApiGetStockNewsByUInt64 m_NewsGetStockNewsByNum;
	ApiGetStockNewsByCharPtr m_NewsGetStockNewsByCharPtr;
	ApiGetObservableUInt64 m_NewsFindStockNewsByNum;
	ApiGetStockNewsByString m_NewsGetStringNews;
	ApiFindStockNewsByString m_NewsFindStringNews;
	ApiIsLong m_NewsDoIdle;
//	ApiObtainNewsCollection m_NewsObtainNewsCollection;
	ApiReleaseNewsCollection m_NewsReleaseNewsCollection;
	ApiUpdateNewsCollectionFilter m_NewsUpdateNewsCollectionFilter;

	ApiGetUInt m_NewsGetWireCount;
	ApiGetWireInfoAt m_NewsGetWireInfoAt;
	ApiCreateIterator m_NewsCreateWireIterator;
	ApiGetNextWireInfo m_NewsGetNextWireInfo;

	ApiGetString m_NewsGetConnectionStatusInfo;
	ApiGetUInt m_NewsGetAllWireCount;
//	ApiGetWireInfoAt m_NewsGetAllWireInfoAt;
	ApiCreateIterator m_NewsCreateAllWireIterator;
	ApiGetNextWireInfo m_NewsGetNextAllWireInfo;

	ApiGetUInt m_NewsGetTopicCount;
	ApiCreateIterator m_NewsCreateTopicIterator;
	ApiGetNextTopicInfo m_NewsGetNextTopicInfo;
	ApiIntInt m_NewsAdjustToChangedScreen;
	ApiNewsDisplayFilterDialog m_NewsDisplayFilterDialog;
	ApiGetFilterDialogValues m_NewsGetFilterDialogValues;
	ApiNewsDisplayLimitsDialog m_NewsDisplayLimitsDialog;
	ApiGetLimitsDialogValues m_NewsGetLimitsDialogValues;
	ApiRequestHeadlines m_NewsRequestHeadlines;
	ApiRequestStory m_NewsRequestStory;
	ApiGetUnappliedHeadlines m_NewsGetUnappliedHeadlines;
	ApiFindNewsCollectionById m_NewsFindNewsCollectionById;
	ApiIsObservableUInt m_NewsIsUpdatedHeadline;
	ApiObservable m_NewsSetUpdatedHeadline;
	ApiObservable m_NewsReadNewHeadlines;
	ApiObservable m_NewsReleaseNewHeadlines;
	ApiFindHeadline m_NewsFindHeadline;
	ApiGetHeadlineCount m_NewsGetHeadlineCount;
	ApiCreateHeadlineIterator m_NewsCreateHeadlineIterator;
	ApiGetNextHeadline m_NewsGetNextHeadline;
	ApiIsObservable m_NewsLockInquiryHeadlines;
	ApiObservable m_NewsLockInquiryWaitHeadlines;
	ApiObservable m_NewsUnlockInquiryHeadlines;
	ApiIsObservableConst m_NewsIsStockNewsRequested;
	ApiGetStdString m_NewsGetSearchStringAll;
	ApiGetStdString m_NewsGetSearchStringAllUs;

	ApiFindStoryByResourceId m_NewsFindStoryByResourceId;
	ApiGetStory m_NewsGetLastStory;
	ApiIs m_NewsLockInquiryStory;
	ApiVoid m_NewsLockInquiryWaitStory;
	ApiVoid m_NewsUnlockInquiryStory;
	ApiIsUInt m_NewsIsUpdatedStory;
	ApiVoid m_NewsSetUpdatedStory;
	ApiGetObservable m_NewsGetStoryObservable;

	ApiIs m_NewsLockInquiryWireNameStorage;
	ApiVoid m_NewsLockInquiryWaitWireNameStorage;
	ApiVoid m_NewsUnlockInquiryWireNameStorage;

	ApiIs m_NewsLockInquiryAllWireNameStorage;
	ApiVoid m_NewsLockInquiryWaitAllWireNameStorage;
	ApiVoid m_NewsUnlockInquiryAllWireNameStorage;

	ApiIs m_NewsLockInquiryTopicNameStorage;
	ApiVoid m_NewsLockInquiryWaitTopicNameStorage;
	ApiVoid m_NewsUnlockInquiryTopicNameStorage;

	ApiBool m_NewsProcessConnectionInMainThread;
	ApiIsObservableConst m_NewsCollectionHasProfile;
};

class TD_API IndexDescription
{
public:
	IndexDescription(const char* symbol, const char* description, const char* valueTemplate, const char* netTemplate):
		m_symbol(symbol),
		m_description(description ? description : ""),
		m_valueTemplate(valueTemplate),
		m_netTemplate(netTemplate),
		m_numericSymbol(U_StringToUInt64Term0(symbol))
	{
	}
	IndexDescription():m_numericSymbol(0){}
	const std::string& GetSymbol() const{return m_symbol;}
	const std::string& GetDescription() const{return m_description;}
	const std::string& GetValueTemplate() const{return m_valueTemplate;}
	const std::string& GetNetTemplate() const{return m_netTemplate;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
protected:
	std::string m_symbol;
	std::string m_description;
	std::string m_valueTemplate;
	std::string m_netTemplate;
	unsigned __int64 m_numericSymbol;
};

class TD_API TierPriceRange
{
public:
	TierPriceRange(const Price& from, const Price& to, unsigned int tierSize):
		m_from(from),
		m_to(to),
		m_tierSize(tierSize)
	{}
	const Price& GetFrom() const{return m_from;}
	const Price& GetTo() const{return m_to;}
	const unsigned int& GetTierSize() const{return m_tierSize;}
	
	bool operator==(const TierPriceRange& other) const
	{
		return m_from == other.m_from && m_to == other.m_to && m_tierSize == other.m_tierSize;
	}
	bool operator!=(const TierPriceRange& other) const{return !operator==(other);}
	bool Belongs(const Price& price) const{return m_from < price && price <= m_to;}
protected:
	Price m_from;
	Price m_to;
	unsigned int m_tierSize;
};

class TD_API TierPriceRangeCollection
{
public:
	typedef std::vector<TierPriceRange> TierPriceRangeVector;
	TierPriceRangeCollection(unsigned int defaultTierSize = 0):
		m_defaultTierSize(defaultTierSize)
	{}
	const unsigned int& GetDefaultTierSize() const{return m_defaultTierSize;}
	const TierPriceRangeVector& GetTierPriceRangeVector() const{return m_tierPriceRangeVector;}

	void SetDefaultTierSize(unsigned int defaultTierSize){m_defaultTierSize = defaultTierSize;}
	void AddTierPriceRange(const Price& from, const Price& to, unsigned int tierSize)
	{
		m_tierPriceRangeVector.push_back(TierPriceRange(from, to, tierSize));
	}
	void ClearPriceRanges(){m_tierPriceRangeVector.clear();}
	bool operator==(const TierPriceRangeCollection& other) const
	{
		if(m_defaultTierSize != other.m_defaultTierSize || m_tierPriceRangeVector.size() != other.m_tierPriceRangeVector.size())
		{
			return false;
		}
		if(!m_tierPriceRangeVector.empty())
		{
			TierPriceRangeVector::const_iterator it = m_tierPriceRangeVector.begin(), itend = m_tierPriceRangeVector.end(), itOther = other.m_tierPriceRangeVector.begin(), itOtherEnd = other.m_tierPriceRangeVector.end();
			for(; it != itend && itOther != itOtherEnd; ++it, ++itOther)
			{
				if(*it != *itOther)
				{
					return false;
				}
			}
			return it == itend && itOther == itOtherEnd;
		}
		return true;
	}
	bool operator!=(const TierPriceRangeCollection& other) const{return !operator==(other);}
	const unsigned int& GetTierSize(const Price& price) const
	{
		if(!m_tierPriceRangeVector.empty())
		{
			for(TierPriceRangeVector::const_iterator it = m_tierPriceRangeVector.begin(), itend = m_tierPriceRangeVector.end(); it != itend; ++it)
			{
				if(it->Belongs(price))
				{
					return it->GetTierSize();
				}
			}
		}
		return m_defaultTierSize;
	}
protected:
	TierPriceRangeVector m_tierPriceRangeVector;
	unsigned int m_defaultTierSize;
};


class TD_API HistoricalChartParams
{
public:
	HistoricalChartParams(const unsigned int& todaysDate, bool dayCount = false, const unsigned int& historyDate = 0, const unsigned char& historyFrequency = CHF_INVALID):
		m_todaysDate(0),//20130315
//		m_todaysHistoryFormatDate(0),
		m_dayCount(dayCount ? historyDate ? historyDate : 1 : 0),
		m_calculatedDayCount(m_dayCount ? m_dayCount : 0),
		m_historyDate(dayCount ? 0 : historyDate),
		m_historyLastLoadedDate(0),
		m_historyFrequency(CHF_INVALID),
		m_historyFrequencyToUse(CHF_INVALID),
		m_newWeek(false),
		m_newMonth(false),
		m_minuteDelta(0),
		m_minuteDeltaToUse(0),
		m_nodesPerDate(0),
		m_nodesPerDateToUse(0),
		m_marketNodesPerDate(0),
		m_marketNodesPerDateToUse(0),
		m_todayNodesPerDate(0),
		m_todayNodesPerDateToUse(0),
		m_todayMarketNodesPerDate(0),
		m_todayMarketNodesPerDateToUse(0)
	{
		SetTodaysDate(todaysDate);
		if(m_dayCount)
		{
			SetHistoryDateByDayCount();
		}
		else if(historyDate && historyDate < m_todaysDate)
		{
			m_calculatedDayCount = TL_BusinessDateDiffByFormattedDates(historyDate, m_todaysDate);
		}
		SetHistoryFrequency(historyFrequency);
	}
	const unsigned int& GetTodaysDate() const{return m_todaysDate;}
//	const unsigned int& GetTodaysHistoryFormatDate() const{return m_todaysHistoryFormatDate;}
	const unsigned int& GetDayCount() const{return m_dayCount;}
	const unsigned int& GetCalculatedDayCount() const{return m_calculatedDayCount;}
	const unsigned int& GetHistoryDate() const{return m_historyDate;}
	const unsigned int& GetHistoryLastLoadedDate() const{return m_historyLastLoadedDate;}
	const unsigned char& GetHistoryFrequency() const{return m_historyFrequency;}
	const unsigned char& GetHistoryFrequencyToUse() const{return m_historyFrequencyToUse;}
	bool SetTodaysDate(const unsigned int& todaysDate)
	{
		if(m_todaysDate != todaysDate)//20130315
		{
			m_todaysDate = todaysDate;
			if(m_dayCount)
			{
				SetHistoryDateByDayCount();
			}
			UpdateNewMonthWeek();
			return true;
		}
		return false;
	}

	bool SetHistoryLastLoadedDate(const unsigned int& historyLastLoadedDate)
	{
		if(m_historyLastLoadedDate != historyLastLoadedDate)
		{
			m_historyLastLoadedDate = historyLastLoadedDate;
			UpdateNewMonthWeek();
			return true;
		}
		return false;
	}

	bool SetHistoryDateByDayCount()
	{
		if(m_dayCount)
		{
			m_calculatedDayCount = m_dayCount;
			if(m_todaysDate)
			{
				unsigned short todayYear, todayMonth, todayDay;
				U_GetDateTokens(m_todaysDate, todayYear, todayMonth, todayDay);
				unsigned int y = todayYear;
				unsigned int m = todayMonth;
				unsigned int d = todayDay;
				TL_DateSubtractBusinessDays(y, m, d, m_dayCount);
				return SetHistoryDate(U_CombineTokensIntoDate((unsigned short)y, (unsigned short)m, (unsigned short)d));
			}
		}
		return false;
	}
	bool SetDayCount(bool dayCount, const unsigned int& historyDate)
	{
		if(dayCount)
		{
			unsigned int hd = historyDate ? historyDate : 1;
			if(m_dayCount != hd)
			{
				m_dayCount = hd;
				return SetHistoryDateByDayCount();
			}
		}
		else
		{
			m_dayCount = 0;
			m_calculatedDayCount = TL_BusinessDateDiffByFormattedDates(historyDate, m_todaysDate);
			return SetHistoryDate(historyDate);
		}
		return false;
	}
	bool SetHistoryDate(const unsigned int& historyDate)
	{
		if(m_historyDate != historyDate)
		{
			m_historyDate = historyDate;
			return true;
		}
		return false;
	}

	bool SetHistoryFrequency(const unsigned char& historyFrequency)
	{
		if(m_historyFrequencyToUse != historyFrequency)
		{
			m_historyFrequencyToUse = m_historyFrequency = historyFrequency;
			switch(m_historyFrequency)
			{
				case CHF_HOUR:
				m_historyFrequency = CHF_30MIN;
				m_minuteDeltaToUse = 60;
				m_minuteDelta = 30;

				m_nodesPerDateToUse = 16;
				m_nodesPerDate = 32;
				m_marketNodesPerDateToUse = 7;
				m_marketNodesPerDate = 13;
				break;

				case CHF_30MIN:
				m_minuteDeltaToUse = m_minuteDelta = 30;
				m_nodesPerDateToUse = m_nodesPerDate = 32;
				m_marketNodesPerDateToUse = m_marketNodesPerDate = 13;
				break;

				case CHF_15MIN:
				m_minuteDeltaToUse = m_minuteDelta = 15;
				m_nodesPerDateToUse = m_nodesPerDate = 64;
				m_marketNodesPerDateToUse = m_marketNodesPerDate = 26;
				break;

				case CHF_5MIN:
				m_minuteDeltaToUse = m_minuteDelta = 5;
				m_nodesPerDateToUse = m_nodesPerDate = 192;
				m_marketNodesPerDateToUse = m_marketNodesPerDate = 78;
				break;

				case CHF_1MIN:
				m_minuteDeltaToUse = m_minuteDelta = 1;
				m_nodesPerDateToUse = m_nodesPerDate = 960;
				m_marketNodesPerDateToUse = m_marketNodesPerDate = 390;
				break;

				default:
				m_minuteDeltaToUse = m_minuteDelta = 0;
				m_nodesPerDateToUse = m_nodesPerDate = m_marketNodesPerDateToUse = m_marketNodesPerDate = 0;
				break;
			}

			UpdateTodaysNodes();
			return true;
		}
		return false;
	}
	const unsigned short& GetMinuteDelta() const{return m_minuteDelta;}
	const unsigned short& GetMinuteDeltaToUse() const{return m_minuteDeltaToUse;}
	const unsigned short& GetNodesPerDate() const{return m_nodesPerDate;}
	const unsigned short& GetNodesPerDateToUse() const{return m_nodesPerDateToUse;}
	const unsigned short& GetMarketNodesPerDate() const{return m_marketNodesPerDate;}
	const unsigned short& GetMarketNodesPerDateToUse() const{return m_marketNodesPerDateToUse;}
	const unsigned short& GetTodayNodesPerDate() const{return m_todayNodesPerDate;}
	const unsigned short& GetTodayNodesPerDateToUse() const{return m_todayNodesPerDateToUse;}
	const unsigned short& GetTodayMarketNodesPerDate() const{return m_todayMarketNodesPerDate;}
	const unsigned short& GetTodayMarketNodesPerDateToUse() const{return m_todayMarketNodesPerDateToUse;}
	bool SetParams(bool dayCount, const unsigned int& historyDate, const unsigned char& historyFrequency)
	{
//		m_dayCount = dayCount ? historyDate ? historyDate : 1 : 0;

		bool ret = SetDayCount(dayCount, historyDate);//SetHistoryDate(historyDate);
		return SetHistoryFrequency(historyFrequency) || ret;
	}
	bool SetParams(const unsigned int& todaysDate, bool dayCount, const unsigned int& historyDate, const unsigned char& historyFrequency)
	{
		bool ret = SetTodaysDate(todaysDate);
		return SetParams(dayCount, historyDate, historyFrequency) || ret;
	}
	bool isValid() const
	{
		switch(m_historyFrequency)
		{
			case CHF_MONTH:
			case CHF_WEEK:
			case CHF_DAY:
			case CHF_HOUR:
			case CHF_30MIN:
			case CHF_15MIN:
			case CHF_5MIN:
			case CHF_1MIN:
			return true;

			default:
			return false;
		}
	}
	bool operator==(const HistoricalChartParams& other) const
	{
		return m_historyDate == other.m_historyDate
			&& m_todaysDate == other.m_todaysDate
			&& m_dayCount == other.m_dayCount
			&& m_historyFrequency == other.m_historyFrequency;
	}
	bool operator!=(const HistoricalChartParams& other) const{return !operator==(other);}
	char compare(const HistoricalChartParams& other) const
	{
		return m_dayCount < other.m_dayCount ? -1:
			m_dayCount > other.m_dayCount ? 1:
			m_historyDate < other.m_historyDate ? -1:
			m_historyDate > other.m_historyDate ? 1:
			m_historyFrequency < other.m_historyFrequency ? -1:
			m_historyFrequency > other.m_historyFrequency ? 1:
			m_todaysDate < other.m_todaysDate ? -1:
			m_todaysDate > other.m_todaysDate ? 1:
			0;
	}
	bool operator<(const HistoricalChartParams& other) const
	{
		return m_dayCount != other.m_dayCount ? m_dayCount < other.m_dayCount:
			m_historyDate != other.m_historyDate ? m_historyDate < other.m_historyDate:
			m_historyFrequency != other.m_historyFrequency ? m_historyFrequency < other.m_historyFrequency:
			m_todaysDate < other.m_todaysDate;
	}
	void Reset()
	{
		m_dayCount = 0;
		m_calculatedDayCount = 0;
		m_historyDate = 0;
		m_historyFrequencyToUse = m_historyFrequency = CHF_INVALID;
		m_minuteDeltaToUse = m_minuteDelta = 0;
		m_marketNodesPerDateToUse = m_marketNodesPerDate = m_nodesPerDateToUse = m_nodesPerDate = 0;
		m_todayNodesPerDate =
		m_todayNodesPerDateToUse =
		m_todayMarketNodesPerDate =
		m_todayMarketNodesPerDateToUse = 0;
	}
protected:
	void UpdateTodaysNodes()
	{
		switch(m_historyFrequency)
		{
			case CHF_MONTH:
			m_todayNodesPerDate =
			m_todayNodesPerDateToUse =
			m_todayMarketNodesPerDate =
			m_todayMarketNodesPerDateToUse = m_newMonth ? 1 : 0;
			break;

			case CHF_WEEK:
			m_todayNodesPerDate =
			m_todayNodesPerDateToUse =
			m_todayMarketNodesPerDate =
			m_todayMarketNodesPerDateToUse = m_newWeek ? 1 : 0;
			break;

			case CHF_DAY:
			m_todayNodesPerDate =
			m_todayNodesPerDateToUse =
			m_todayMarketNodesPerDate =
			m_todayMarketNodesPerDateToUse = 1;
			break;


			default:
			m_todayNodesPerDate = m_nodesPerDate;
			m_todayNodesPerDateToUse = m_nodesPerDateToUse;
			m_todayMarketNodesPerDate = m_marketNodesPerDate;
			m_todayMarketNodesPerDateToUse = m_marketNodesPerDateToUse;
			break;
		}
	}
	void UpdateNewMonthWeek()
	{
		if(m_historyLastLoadedDate)
		{
			unsigned short year, month, day;
			U_GetDateTokens(m_historyLastLoadedDate, year, month, day);
			unsigned short todayYear, todayMonth, todayDay;
			U_GetDateTokens(m_todaysDate, todayYear, todayMonth, todayDay);
			if(m_historyLastLoadedDate < m_todaysDate)
			{
				m_newMonth = month != todayMonth;
				unsigned int todayWeekDay = TL_GetDayOfWeek(todayYear, todayMonth, todayDay);
				m_newWeek = TL_GetDayOfWeek(year, month, day) >= todayWeekDay && todayWeekDay > 0 && todayWeekDay < 6; 
			}
			else
			{
				m_newMonth = m_newWeek = false;
			}
		}
		else
		{
			m_newMonth = m_newWeek = false;
		}
		UpdateTodaysNodes();
	}
	unsigned int m_todaysDate;
//	unsigned int m_todaysHistoryFormatDate;
	unsigned int m_dayCount;
	unsigned int m_calculatedDayCount;
	unsigned int m_historyDate;
	unsigned int m_historyLastLoadedDate;
	unsigned char m_historyFrequency;
	unsigned char m_historyFrequencyToUse;
	bool m_newWeek;
	bool m_newMonth;
	unsigned short m_minuteDelta;
	unsigned short m_minuteDeltaToUse;
	unsigned short m_nodesPerDate;
	unsigned short m_nodesPerDateToUse;
	unsigned short m_marketNodesPerDate;
	unsigned short m_marketNodesPerDateToUse;

	unsigned short m_todayNodesPerDate;
	unsigned short m_todayNodesPerDateToUse;
	unsigned short m_todayMarketNodesPerDate;
	unsigned short m_todayMarketNodesPerDateToUse;
};

class TD_API HistoricalChart
{
public:
	HistoricalChart(const unsigned __int64& numericSymbol, const unsigned int& todaysDate, const bool& histPrePostMarket):
		m_historicalChartParams(todaysDate),
		m_numericSymbol(numericSymbol),
		m_historicalChartRequest(0),
		m_historicalChartLoaded(false),
		m_histPrePostMarket(histPrePostMarket),
		m_packCount(0),
		m_currentMinute(0),
		m_todaysCurrentNode(0xFFFF),
		m_todayAppended(false),
		m_historicalChartTemp(NULL),
		m_historicalChartIntradayTemp(NULL),
		m_historicalChartStartDate(0),
		m_prevHistoricalChartStartDate(0),
		m_dateLoading(0),
		m_currentLoadingMinute(0),
		m_dateCount(0)
	{}
	~HistoricalChart(){DestroyHistoricalChartTemp();}//DestroyHistoricalChartIntradayTemp();}

	unsigned int RequestHistoricalChart(const char* symbol, const HistoricalChartParams& historicalChartParams);//, unsigned int dateFrom, char frequency);
	const unsigned int& GetHistoricalChartRequest() const{return m_historicalChartRequest;}
	const bool& isHistoricalChartLoaded() const{return m_historicalChartLoaded;}

	const bool& isPrePostMarket() const{return m_histPrePostMarket;}
	bool SetPrePostMarket(bool prePostMarket);

	void AppendTodaysEmptyNodes();
	void RemoveTodaysNodes();
	void ResetTodaysNodes();
	bool FillTodaysChart(const Security* stock);

	void ClearChart()
	{
		m_historicalChart.clear();
		m_historicalChartStartDate = 0;
		m_prevHistoricalChartStartDate = 0;
		m_packCount = 0;
		m_historicalChartRequest = 0;
		m_currentMinute = 0;
		m_todaysCurrentNode = 0xFFFF;
		m_lastHistoricalPoint.Reset();
		m_dateLoading = 0;
		m_currentLoadingMinute = 0;
		m_dateCount = 0;

		DestroyHistoricalChartTemp();
	}
	void SetRequestId(const unsigned int& requesId) const
	{
		m_historicalChartRequest = requesId;
		if(m_historicalChartRequest)
		{
			m_historicalChartLoaded = false;
			m_packCount = 0;
		}
	}

	unsigned short GetHistoricalChartSize() const{return (unsigned short)m_historicalChart.size();}
//	unsigned short GetHistoricalChartSizePlusDateCount() const{return (unsigned short)m_historicalChart.size() + m_dateCount;}
	const Security::ChartPointVector& GetHistoricalChart() const{return m_historicalChart;}

	const unsigned int& GetRequestId() const{return m_historicalChartRequest;}
	const unsigned short& GetPackCount()const{return m_packCount;}

	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
	const char* GetSymbol() const{return (const char*)&m_numericSymbol;}
	const HistoricalChartParams& GetHistoricalChartParams() const{return m_historicalChartParams;}
	const unsigned short& GetNodesPerDate() const{return m_historicalChartParams.GetNodesPerDate();}
	const unsigned short& GetNodesPerDateToUse() const{return m_historicalChartParams.GetNodesPerDateToUse();}
	const unsigned short& GetMarketNodesPerDate() const{return m_historicalChartParams.GetMarketNodesPerDate();}
	const unsigned short& GetMarketNodesPerDateToUse() const{return m_historicalChartParams.GetMarketNodesPerDateToUse();}
	bool SetHistoricalChartParams(const HistoricalChartParams& other)
	{
		if(m_historicalChartParams != other)
		{
			m_historicalChartParams = other;
			return true;
		}
		return false;
	}

	void SetHistoryFrequency(const unsigned char& historyFrequency);
	void PrintServerDisconnected();
	void ProcessHistoricalChartSnapshot(const unsigned char pointSize, const unsigned short pointCount, const HistoricalTick* chartPoint, const unsigned int requestId, const unsigned char more);
	void ProcessHistoricalIntradayChartSnapshot(const unsigned char pointSize, const unsigned short pointCount, const unsigned int date, const HistoricalIntraDayTick* chartPoint, const unsigned int requestId, const unsigned char more);
	const unsigned int& GetHistoricalChartStartDate() const{return m_historicalChartStartDate;}
	const unsigned int& GetPrevHistoricalChartStartDate() const{return m_prevHistoricalChartStartDate;}
	const unsigned int& GetDayCount() const{return m_historicalChartParams.GetDayCount();}
	const unsigned int& GetCalculatedDayCount() const{return m_historicalChartParams.GetCalculatedDayCount();}
	const unsigned short& GetDateCount() const{return m_dateCount;}
	const unsigned int& GetHistoryDate() const{return m_historicalChartParams.GetHistoryDate();}
	void DoFinalizeHistoricalChart();
	bool SetCurrentMinute(unsigned short currentMinute)//, bool force)
	{
		if(m_currentMinute != currentMinute)// || force)
		{
			m_currentMinute = currentMinute;
			UpdateTodayAppended();
			return true;
		}
		return false;
	}
	bool SetTodayAppended(bool appended)
	{
		if(m_todayAppended != appended)
		{
			m_todayAppended = appended;
			UpdateTodayAppended();
			return true;
		}
		return false;
	}
	const unsigned short& GetCurrentMinute() const{return m_currentMinute;}
	const unsigned short& GetTodaysCurrentNode() const{return m_todaysCurrentNode;}
	const bool& isTodayAppended() const{return m_todayAppended;}
	bool AddPrint(const Price& price, unsigned int size, unsigned char printFlags)
	{
		if(m_todaysCurrentNode && m_todaysCurrentNode < (unsigned short)m_historicalChart.size())
		{
			m_historicalChart[m_todaysCurrentNode].AddPrint(price, size, printFlags);
			return true;
		}
		return false;
	}
/*
	void SetTodaysCurrentNode(unsigned short todaysCurrentNode)
	{
		m_todaysCurrentNode = todaysCurrentNode;
	}
*/
	bool SetParams(bool dayCount, const unsigned int& historyDate, const unsigned char& historyFrequency)
	{
		return m_historicalChartParams.SetParams(dayCount, historyDate, historyFrequency);
	}
	bool SetParams(const unsigned int& todaysDate, bool dayCount, const unsigned int& historyDate, const unsigned char& historyFrequency)
	{
		return m_historicalChartParams.SetParams(todaysDate, dayCount, historyDate, historyFrequency);
	}
	const unsigned char& GetFrequency() const{return m_historicalChartParams.GetHistoryFrequency();}
	bool operator==(const HistoricalChart& other) const{return m_historicalChartParams == other.m_historicalChartParams;}
	bool operator!=(const HistoricalChart& other) const{return !operator==(other);}
	bool operator<(const HistoricalChart& other) const{return m_historicalChartParams < other.m_historicalChartParams;}
	char compare(const HistoricalChart& other) const
	{
		char ret = U_CompareUIntAsString(m_numericSymbol, other.m_numericSymbol);
		return ret ? ret : m_historicalChartParams.compare(other.m_historicalChartParams);
	}
protected:

	void UpdateTodayAppended()
	{
		if(m_todayAppended)
		{
			UpdateCurrentMinute();
		}
		else
		{
			m_todaysCurrentNode = 0xFFFF;
		}
	}
	void UpdateCurrentMinute()
	{
		unsigned short minuteDelta = m_historicalChartParams.GetMinuteDeltaToUse();
		if(minuteDelta)
		{
			unsigned short firstMinute = m_histPrePostMarket ? 240 : 570;
			if(firstMinute <= m_currentMinute)
			{
				unsigned short lastMinute = m_histPrePostMarket ? 1200 : 960;
				if(m_currentMinute < lastMinute)
				{
					unsigned short diff = lastMinute - m_currentMinute;
					unsigned short nodeCount = diff / minuteDelta;
//04/08/2013
					if(nodeCount * minuteDelta == diff)
					{
						if(nodeCount)--nodeCount;
					}
//////
					unsigned short size = (unsigned short)m_historicalChart.size();
					if(nodeCount < size)
					{
						m_todaysCurrentNode = size - nodeCount - 1;
					}
					else
					{
						m_todaysCurrentNode = 0xFFFF;
					}
				}
				else
				{
					m_todaysCurrentNode = 0xFFFF;
				}
			}
			else
			{
				m_todaysCurrentNode = 0xFFFF;
			}
		}
		else if(m_todayAppended)
		{
			if(m_currentMinute)
			{
				unsigned short firstMinute = m_histPrePostMarket ? 240 : 570;
				if(firstMinute <= m_currentMinute)
				{
					unsigned short lastMinute = m_histPrePostMarket ? 1200 : 960;
					if(m_currentMinute < lastMinute)
					{
						m_todaysCurrentNode = (unsigned short)m_historicalChart.size();
						if(m_todaysCurrentNode)--m_todaysCurrentNode;
					}
					else
					{
						m_todaysCurrentNode = 0xFFFF;
					}
				}
				else
				{
					m_todaysCurrentNode = 0xFFFF;
				}
			}
			else
			{
				m_todaysCurrentNode = (unsigned short)m_historicalChart.size();
				if(m_todaysCurrentNode)--m_todaysCurrentNode;
			}
		}
		else
		{
			m_todaysCurrentNode = 0xFFFF;
		}
	}

	HistoricalChartParams m_historicalChartParams;

	unsigned __int64 m_numericSymbol;

	mutable unsigned int m_historicalChartRequest;
	mutable bool m_historicalChartLoaded;
	bool m_histPrePostMarket;
	mutable unsigned short m_packCount;

	unsigned short m_currentMinute;
	unsigned short m_todaysCurrentNode;
	bool m_todayAppended;

	Security::ChartPointVector m_historicalChart;
	Security::ChartPointVector* m_historicalChartTemp;
	Security::ChartPointVector* m_historicalChartIntradayTemp;
	ChartPoint m_lastHistoricalPoint;
	unsigned int m_historicalChartStartDate;
	unsigned int m_prevHistoricalChartStartDate;//to compare with m_historicalChartStartDate to find out if an additional request changed the start date.
	unsigned int m_dateLoading;
	unsigned short m_currentLoadingMinute;
	unsigned short m_dateCount;
//	TempPointVector* m_historicalChartTemp;
//	TempPointVector* m_historicalChartIntradayTemp;
	void FinalizeHistoricalChart();
	void DestroyHistoricalChartTemp();
	void DestroyHistoricalChartIntradayTemp();
};

class TD_API FrequencyChartCollection
{
public:
	typedef CMap<unsigned char, const unsigned char&, const HistoricalChart*, const HistoricalChart*> FrequencyHistoricalChartMap;
	FrequencyChartCollection(const unsigned __int64& numericSymbol):m_numericSymbol(numericSymbol){}
	~FrequencyChartCollection(){ClearAndDestroy();}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
//	const HistoricalChart* AddHistoricalChart(const HistoricalChart* chart);//returns previous chart if replaced; returns chart if not replaced; returns NULL if added without replacing
	bool AddHistoricalChart(HistoricalChart*& chart);//places previous chart in the chart argument; returns returns true if a request needs to be sent
	const HistoricalChart* RemoveHistoricalChart(unsigned char frequency);
	void RemoveAndDestroyHistoricalChart(unsigned char frequency, const HistoricalChart* replaceWith);
	void ClearAndDestroy();
	TakionIterator* CreateIterator() const;
	const HistoricalChart* FindHistoricalChart(unsigned char frequency) const
	{
		const FrequencyHistoricalChartMap::CPair* found = m_frequencyHistoricalChartMap.PLookup(frequency);
		return found ? found->value : NULL;
	}
	bool isEmpty() const{return m_frequencyHistoricalChartMap.IsEmpty() == TRUE;}
	unsigned int GetCount() const{return (unsigned int)m_frequencyHistoricalChartMap.GetCount();}
	const FrequencyHistoricalChartMap& GetFrequencyHistoricalChartMap() const{return m_frequencyHistoricalChartMap;}
protected:
	FrequencyHistoricalChartMap m_frequencyHistoricalChartMap;
	unsigned __int64 m_numericSymbol;
};

class TMessageHistoricalChart : public Message
{
public:
	const HistoricalChart* m_historicalChart;
protected:
	TMessageHistoricalChart(const HistoricalChart* historicalChart, unsigned short type, unsigned short length):Message(type, length), m_historicalChart(historicalChart){}
};

class TMsgHistoricalChartPackLoaded : public TMessageHistoricalChart
{
public:
	TMsgHistoricalChartPackLoaded(const HistoricalChart* historicalChart):TMessageHistoricalChart(historicalChart, M_HISTORICAL_CHART_PACK_LOADED, sizeof(TMsgHistoricalChartPackLoaded)){}
};

class TMsgHistoricalChartDelete : public TMessageHistoricalChart
{
public:
	TMsgHistoricalChartDelete(const HistoricalChart* historicalChart, const HistoricalChart* replaceWith):TMessageHistoricalChart(historicalChart, M_HISTORICAL_CHART_DELETE, sizeof(TMsgHistoricalChartDelete)), m_replaceWith(replaceWith){}
	const HistoricalChart* m_replaceWith;
};

#ifdef __cplusplus
extern "C"
{
#endif

const FrequencyChartCollection* WINAPI TD_FindHistoricalChartSymbol(const unsigned __int64& numericSymbol);
TakionIterator* WINAPI TD_CreateHistoricalChartSymbolIterator();
const FrequencyChartCollection* WINAPI TD_GetNextHistoricalChartSymbol(TakionIterator* iterator);
const HistoricalChart* WINAPI TD_GetNextFrequencyHistoricalChart(TakionIterator* frequencyHistoricalChartIterator);

bool WINAPI TD_AddStreamConnection(const ConnectionBase& connectionBase);
/*
bool WINAPI TD_AddStreamConnection(const char* name,
	const char* ip,
	unsigned short port,
	const char* ip2,
	unsigned short port2,
	unsigned char connectionDataType,
	unsigned int receiveBuffer = 0xFFFFFFFF,
	unsigned int sendBuffer = 0xFFFFFFFF,
	unsigned int reconnectSeconds = 5,
	unsigned int reconnectTries = 0,
	unsigned int maxReconnectTries = 0xFFFFFFFF,
	const char* bindIp = NULL,
	unsigned short bindPort = 0,
	const char* bindIp2 = NULL,
	unsigned short bindPort2 = 0,
	const char* loginId = "",
	const char* password = "");
*/

Security* WINAPI TD_ObtainStock(const char* symbol, bool subscribe);
Security* WINAPI TD_ObtainStockByNumericSymbol(const unsigned __int64& numSymbol, bool subscribe);
Security* WINAPI TD_FindStock(const char* symbol);
Security* WINAPI TD_FindStockByNumericSymbol(const unsigned __int64& numSymbol);
void WINAPI TD_ReleaseStock(const Security* stock, bool unsubscribeImmediately = false);
unsigned int WINAPI TD_GetStockCount();
unsigned int WINAPI TD_GetIdleStockCount();

#ifndef TAKION_NO_OPTIONS
void WINAPI TD_SetOptionUpdateOnIdle(bool optionUpdateOnIdle);
unsigned int WINAPI TD_GetUnderlierIdleMilliseconds();
void WINAPI TD_SetUnderlierIdleMilliseconds(unsigned int milliseconds);
Security* WINAPI TD_ObtainOption(const char* underlierSymbol, const OptionKey& key, bool subscribe);
Security* WINAPI TD_ObtainOptionByUnderlierNumericSymbol(const unsigned __int64& underlierSymbolNum, const OptionKey& key, bool subscribe);
Security* WINAPI TD_ObtainOptionByRootNumericSymbol(const unsigned __int64& rootSymbolNum, const OptionKey& key, bool subscribe);
Security* WINAPI TD_FindOption(const char* underlierSymbol, const OptionKey& key);
Security* WINAPI TD_FindOptionByNumericSymbol(const unsigned __int64& underlierSymbol, const OptionKey& key);
Security* WINAPI TD_FindOptionByOptionBlock(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock);
unsigned int WINAPI TD_GetOptionCount();
unsigned int WINAPI TD_GetIdleOptionCount();
TakionIterator* WINAPI TD_CreateOptionIterator();
Security* WINAPI TD_GetNextOption(TakionIterator* iterator);
bool WINAPI TD_SubscribeUnderlierByNumericSymbol(const unsigned __int64& symbol);
bool WINAPI TD_UnsubscribeUnderlierByNumericSymbol(const unsigned __int64& symbol);
bool WINAPI TD_SubscribeUnderlier(const char* symbol);
bool WINAPI TD_UnsubscribeUnderlier(const char* symbol);
//bool WINAPI TD_SubscribeOptionByNumericSymbol(const unsigned __int64& symbol, const OptionKey& optionKey);
//bool WINAPI TD_UnsubscribeOptionByNumericSymbol(const unsigned __int64& symbol, const OptionKey& optionKey);
//bool WINAPI TD_SubscribeOption(const char* symbol, const OptionKey& optionKey);
//bool WINAPI TD_UnsubscribeOption(const char* symbol, const OptionKey& optionKey);

Underlier* WINAPI TD_ObtainUnderlier(const char* symbol, bool subscribe);
Underlier* WINAPI TD_FindUnderlier(const char* symbol);
unsigned int WINAPI TD_GetUnderlierCount();
unsigned int WINAPI TD_GetIdleUnderlierCount();
void WINAPI TD_ReleaseUnderlier(const Underlier* underlier, bool unsubscribeImmediately = false);
TakionIterator* WINAPI TD_CreateUnderlierIterator();
Underlier* WINAPI TD_GetNextUnderlier(TakionIterator* iterator);

bool WINAPI TD_IsOptionMarketDataConnected();
bool WINAPI TD_IsOptionMarketDataLogged();

unsigned __int64 WINAPI TD_GetOptionMarketDataVersion();
const char* WINAPI TD_GetOptionMarketDataVersionStr();

unsigned char WINAPI TD_GetFlagsFromOptionBlock(const unsigned __int64& rootSymbol, const unsigned __int64& undelierSymbol, const unsigned int& optionBlock);

const Destination* WINAPI TD_GetOptionSourceDestination(const unsigned char& source);
const Destination* WINAPI TD_FindOptionDestinationByName(const char* name);
const Destination* WINAPI TD_FindOptionDestinationByNumericName(const unsigned int& name);

void WINAPI TD_AddTierSize(const char* symbol, const unsigned __int64& optionKey, unsigned int tierSize);//use object OptionKey to create the optionKey argument; 0 for stocks
void WINAPI TD_RemoveTierSize(const char* symbol, const unsigned __int64& optionKey);
const unsigned int* WINAPI TD_GetNextTierSize(TakionIterator* iterator, const char*& symbol, unsigned __int64& optionKey);
const unsigned int* WINAPI TD_FindTierSize(const char* symbol, const unsigned __int64& optionKey);

void WINAPI TD_AddNonTradableStock(const char* symbol, const unsigned __int64& optionKey, unsigned int code);
void WINAPI TD_RemoveNonTradableStock(const char* symbol, const unsigned __int64& optionKey);
const unsigned int* WINAPI TD_GetNextNonTradableStock(TakionIterator* iterator, const char*& symbol, unsigned __int64& optionKey);
const unsigned int* WINAPI TD_FindNonTradableStock(const char* symbol, const unsigned __int64& optionKey);

void WINAPI TD_AddTradableStock(const char* symbol, const unsigned __int64& optionKey, unsigned int code);
void WINAPI TD_RemoveTradableStock(const char* symbol, const unsigned __int64& optionKey);
const unsigned int* WINAPI TD_GetNextTradableStock(TakionIterator* iterator, const char*& symbol, unsigned __int64& optionKey);
const unsigned int* WINAPI TD_FindTradableStock(const char* symbol, const unsigned __int64& optionKey);

bool WINAPI TD_IsTradableStock(const char* symbol, const unsigned __int64& optionKey);

#else

void WINAPI TD_AddTierSize(const char* symbol, unsigned int tierSize);
void WINAPI TD_RemoveTierSize(const char* symbol);
const unsigned int* WINAPI TD_GetNextTierSize(TakionIterator* iterator, const char*& symbol);
const unsigned int* WINAPI TD_FindTierSize(const char* symbol);

void WINAPI TD_AddNonTradableStock(const char* symbol, unsigned int code);
void WINAPI TD_RemoveNonTradableStock(const char* symbol);
const unsigned int* WINAPI TD_GetNextNonTradableStock(TakionIterator* iterator, const char*& symbol);
const unsigned int* WINAPI TD_FindNonTradableStock(const char* symbol);

void WINAPI TD_AddTradableStock(const char* symbol, unsigned int code);
void WINAPI TD_RemoveTradableStock(const char* symbol);
const unsigned int* WINAPI TD_GetNextTradableStock(TakionIterator* iterator, const char*& symbol);
const unsigned int* WINAPI TD_FindTradableStock(const char* symbol);

bool WINAPI TD_IsTradableStock(const char* symbol);

#endif

void WINAPI TD_ClearTierSize();
TakionIterator* WINAPI TD_CreateTierSizeIterator();
void WINAPI TD_ClearNonTradableStocks();
TakionIterator* WINAPI TD_CreateNonTradableStockIterator();
unsigned int WINAPI TD_GetNonTradableStockCount();
void WINAPI TD_ClearTradableStocks();
TakionIterator* WINAPI TD_CreateTradableStockIterator();
unsigned int WINAPI TD_GetTradableStockCount();


Index* WINAPI TD_FindIndex(const char* symbol);
Index* WINAPI TD_FindIndexByNumericSymbol(const unsigned __int64& numSymbol);
Index* WINAPI TD_GetIndexByCode(unsigned short code);
unsigned int WINAPI TD_GetIndexCount();

Security* WINAPI TD_FindSortableEquity(const char* symbol);
Security* WINAPI TD_FindSortableEquityByNumericSymbol(const unsigned __int64& symbol);
Security* WINAPI TD_GetSortableEquityByCode(unsigned short code);
unsigned int WINAPI TD_GetSortableEquityCount();

unsigned int WINAPI TD_GetAccountCount();
const unsigned short& TD_GetNumberOfAccountsExpected();
const unsigned short& TD_GetNumberOfAccountsToLoad();
Account* WINAPI TD_FindAccount(const char* id);
Account* WINAPI TD_CreateAccount(const char* id, unsigned int orderProcessingFlags = 0, bool* newAccount = NULL);//works only in simulation
bool WINAPI TD_DestroyAccount(const char* id);//works only in simulation
void WINAPI TD_DestroyAllAccounts();//works only in simulation
TakionIterator* WINAPI TD_CreateAccountIterator();
Account* WINAPI TD_GetNextAccount(TakionIterator* iterator);
void WINAPI TD_LockAccountStorage();
void WINAPI TD_UnlockAccountStorage();

void WINAPI TD_LockTierSizeStorage();
void WINAPI TD_UnlockTierSizeStorage();

void WINAPI TD_SetLogFile(void* logFile);
void* WINAPI TD_GetLogFile();

unsigned int WINAPI TD_GetConnectionCount();
TakionIterator* WINAPI TD_CreateActiveConnectionIterator();
const ActiveConnection* WINAPI TD_GetNextActiveConnection(TakionIterator* iterator);

enum ConnectionResult : unsigned char
{
	CR_OK,
	CR_SAME_MARKETDATA_AND_EXECUTOR,
	CR_MARKETDATA_BINDING,
	CR_EXECUTOR_BINDING,
	CR_MARKETSORTER_BINDING,
	CR_HISTORICALPRINT_BINDING,
	CR_OPTION_MARKETDATA_BINDING,
};

enum ConnectionJob : unsigned short
{
	CR_JOB_MARKETDATA = 1,
	CR_JOB_EXECUTOR = 2,
	CR_JOB_MARKETSORTER = 4,
	CR_JOB_MARKETDATA_LOGON = 8,
	CR_JOB_EXECUTOR_LOGON = 16,
	CR_JOB_MARKETSORTER_LOGON = 32,
	CR_JOB_HISTORICALPRINT = 64,
	CR_JOB_HISTORICALPRINT_LOGON = 128,
#ifndef TAKION_NO_OPTIONS
	CR_JOB_OPTION_MARKETDATA = 256,
	CR_JOB_OPTION_MARKETDATA_LOGON = 512,
#endif
	CR_JOB_ALL_CONNECT = CR_JOB_MARKETDATA | CR_JOB_EXECUTOR | CR_JOB_MARKETSORTER | CR_JOB_HISTORICALPRINT
#ifndef TAKION_NO_OPTIONS
		| CR_JOB_OPTION_MARKETDATA
#endif
};

unsigned int WINAPI TD_ConnectToMarketDataAndExecutor(const char* traderId,
	const char* password,
	const char* firmId,
	const Connection* marketDataConnection,
	const Connection* executorConnection,
	const Connection* marketSorterConnection,
	const Connection* historicalPrintConnection,
#ifndef TAKION_NO_OPTIONS
	const Connection* optionMarketDataConnection,
#endif
	bool disconnectOnly,
	bool tryToReconnect);
void WINAPI TD_DisconnectFromMarketData();
void WINAPI TD_DisconnectFromExecutor();
void WINAPI TD_DisconnectFromMarketSorter();
void WINAPI TD_DisconnectFromHistoricalPrint();

const ActiveConnection* WINAPI TD_GetMarketDataActiveConnection();
const ActiveConnection* WINAPI TD_GetExecutorActiveConnection();
const ActiveConnection* WINAPI TD_GetMarketSorterActiveConnection();
const ActiveConnection* WINAPI TD_GetHistoricalPrintActiveConnection();

#ifndef TAKION_NO_OPTIONS
void WINAPI TD_OptionBlockToString(std::string& str, const unsigned __int64& optionBlock);
const ActiveConnection* WINAPI TD_GetOptionMarketDataActiveConnection();
const Connection* WINAPI TD_GetOptionMarketDataConnection();
void WINAPI TD_DisconnectFromOptionMarketData();
Observable* WINAPI TD_GetNewOptionObservable();
#endif

const Connection* WINAPI TD_GetMarketDataConnection();
const Connection* WINAPI TD_GetExecutorConnection();
const Connection* WINAPI TD_GetMarketSorterConnection();
const Connection* WINAPI TD_GetHistoricalPrintConnection();

bool WINAPI TD_DoMainThreadIdleTasks(LONG lCount);
unsigned int WINAPI TD_GetStockIdleMilliseconds();
void WINAPI TD_SetStockIdleMilliseconds(unsigned int milliseconds);
void WINAPI TD_SetEquityUpdateOnIdle(bool equityUpdateOnIdle);

const char* WINAPI TD_GetOrderTypeName(unsigned int orderType);

TakionIterator* WINAPI TD_CreateDestinationIterator();
const Destination* WINAPI TD_GetNextDestination(TakionIterator* iterator);
const Destination* WINAPI TD_FindDestinationByName(const char* name);
const Destination* WINAPI TD_FindDestinationByNumericName(unsigned int name);
const Destination* WINAPI TD_FindDestinationById(unsigned int id);

TakionIterator* WINAPI TD_CreateDestinationRoutingPairIterator();
const DestinationRoutingPair* WINAPI TD_GetNextDestinationRoutingPair(TakionIterator* iterator);
const DestinationRoutingPair* WINAPI TD_FindDestinationRoutingPair(const unsigned __int64& id);
const DestinationRoutingPair* WINAPI TD_FindDestinationRoutingPairByNumericName(unsigned int destinationName, unsigned int routingName);
const DestinationRoutingPair* WINAPI TD_FindDestinationRoutingPairByName(const char* destinationName, const char* routingName);

const char* WINAPI TD_GetTraderId();
bool WINAPI TD_IsSimulation();
const char* WINAPI TD_GetFirmId();

Account* WINAPI TD_GetDefaultAccount();
unsigned __int64 WINAPI TD_GetTraderIdFlags();

const Destination* WINAPI TD_GetEcnDefaultDestination(unsigned char bookId);//enum EcnBookId in TakionUtilsApi.h
const Destination* WINAPI TD_GetStockSourceDestination(unsigned char source);//enum NyseMarketCenter in TakionUtilsApi.h (minus 'A', i. e. zero based)
const Destination* WINAPI TD_GetDestinationByPrimaryExchange(char primaryExchange);//enum PrimaryExchange in TakionUtilsApi.h
unsigned int WINAPI TD_GetDestinationIdByPrimaryExchange(char primaryExchange);//enum PrimaryExchange in TakionUtilsApi.h

const Destination* WINAPI TD_GetDestinationAmex();
const Destination* WINAPI TD_GetDestinationNyse();
const Destination* WINAPI TD_GetDestinationNsdq();
const Destination* WINAPI TD_GetDestinationQsmt();
const Destination* WINAPI TD_GetDestinationArca();
const Destination* WINAPI TD_GetDestinationBats();
const Destination* WINAPI TD_GetDestinationBaty();
const Destination* WINAPI TD_GetDestinationEdga();
const Destination* WINAPI TD_GetDestinationEdgx();
const Destination* WINAPI TD_GetDestinationNite();
const Destination* WINAPI TD_GetDestinationNsex();
const Destination* WINAPI TD_GetDestinationJpm();

unsigned int WINAPI TD_RequestStockHistoricalChart(const char* symbol, unsigned int dateFrom, unsigned char frequency);
HistoricalChart* WINAPI TD_RequestAndKeepStockHistoricalChart(const char* symbol, unsigned int dateFrom, unsigned char frequency, bool includePrePostMarket);
unsigned int WINAPI TD_AddToHistoricalChart(const HistoricalChart* historicalChart, unsigned int dateFrom);

bool WINAPI TD_IsTierBoundsValid(const Price& lowTierPrice, unsigned int lowTierSize, const Price& highTierPrice, unsigned int highTierSize, unsigned int minTierSize, unsigned int maxTierSize);
bool WINAPI TD_IsCurrentTierBoundsValid();
void WINAPI TD_SetTierBounds(const TierPriceRangeCollection& tierPriceRangeCollection, const Price& lowTierPrice, unsigned int lowTierSize, const Price& highTierPrice, unsigned int highTierSize, unsigned int minTierSize, unsigned int maxTierSize);
const Price& WINAPI TD_GetLowTierPrice();
const Price& WINAPI TD_GetHighTierPrice();
unsigned int WINAPI TD_GetLowTierSize();
unsigned int WINAPI TD_GetHighTierSize();
unsigned int WINAPI TD_GetMinTierSize();
unsigned int WINAPI TD_GetMaxTierSize();
unsigned int WINAPI TD_CalculateTierSize(const Price& price, bool* fromPriceRange);

void WINAPI TD_LockStockStorage();
void WINAPI TD_UnlockStockStorage();
void WINAPI TD_LockEquityStorage();
void WINAPI TD_UnlockEquityStorage();
void WINAPI TD_LockIndexStorage();
void WINAPI TD_UnlockIndexStorage();

TakionIterator* WINAPI TD_CreateStockIterator();
Security* WINAPI TD_GetNextStock(TakionIterator* iterator);
TakionIterator* WINAPI TD_CreateEquityIterator();
Security* WINAPI TD_GetNextEquity(TakionIterator* iterator);

TakionIterator* WINAPI TD_CreateIndexIterator();
Index* WINAPI TD_GetNextIndex(TakionIterator* iterator);

bool WINAPI TD_IsMarketDataConnected();
bool WINAPI TD_IsExecutorConnected();
bool WINAPI TD_IsMarketSorterConnected();
bool WINAPI TD_IsMarketSorterLoaded();
bool WINAPI TD_IsMarketSorterIndexesLoaded();
bool WINAPI TD_IsHistoricalPrintConnected();

const unsigned int& WINAPI TD_GetUserType();

const unsigned int& WINAPI TD_GetOrderSizeAbsoluteCap();
const unsigned int& WINAPI TD_GetMaxCancelsPerSecond();

char  WINAPI TD_GetMarketStatus();
bool  WINAPI TD_IsMarketStatusInitialized();
bool  WINAPI TD_IsMarketOpen();

bool WINAPI TD_IsMovesReporting();
bool WINAPI TD_IsJoinsReporting();
void WINAPI TD_SetMovesReporting(bool report);
void WINAPI TD_SetJoinsReporting(bool report);

Account* WINAPI TD_GetCurrentAccount();
void WINAPI TD_SetCurrentAccount(Account* account);

void WINAPI TD_SetMarketSorterSubscribeToStocks(bool subscribe);
void WINAPI TD_SetMarketSorterSubscribeToIndices(bool subscribe);
bool WINAPI TD_IsMarketSorterSubscribeToStocks();
bool WINAPI TD_IsMarketSorterSubscribeToIndices();
bool WINAPI TD_IsMarketSorterStocksSubscribed();
bool WINAPI TD_IsMarketSorterIndicesSubscribed();

bool WINAPI TD_IsLoadExecutions();
void WINAPI TD_SetLoadExecutions(bool load);
bool WINAPI TD_IsCancelOnDisconnect();
void WINAPI TD_SetCancelOnDisconnect(bool cancel);

bool WINAPI TD_LoadExecutions(const Account* account);

bool WINAPI TD_IsLoadOrders();
void WINAPI TD_SetLoadOrders(bool load);
bool WINAPI TD_LoadOrders(const Account* account);

void WINAPI TD_SetChartApplicablePrintPercent(const Price& percent);
const Price& WINAPI TD_GetChartApplicablePrintPercent();

void WINAPI TD_SetBlockAggressiveOrderPriceRange(const Price& priceRange, bool percent);
bool WINAPI TD_GetBlockAggressiveOrderPriceRange(Price& price);
unsigned int WINAPI TD_GetBlockAggressiveOrderPriceRangeAsUInt();
bool WINAPI TD_IsOrderTooAggressive(char side, const Price& limitPrice, const SignedPrice& stopPrice, const Price& bidPrice, const Price& askPrice, unsigned char tifType);
bool WINAPI TD_IsOrderCrossingInsideMarket(char side, const Price& limitPrice, const SignedPrice& stopPrice, const Price& bidPrice, const Price& askPrice, unsigned char tifType);

void WINAPI TD_SetDefaultCommissionFee(const Money& commissionFee);
const Money& WINAPI TD_GetDefaultCommissionFee();

bool WINAPI TD_SetCustomAccountConstraints(const ConstraintCollection& cc);
void WINAPI TD_SetAccountCustomAccountConstraints(Account* account, const ConstraintCollection& cc);

bool WINAPI TD_IsArcaPloWhenHidden();
void WINAPI TD_SetArcaPloWhenHidden(bool arcaPlo);

bool WINAPI TD_IsNyseConvertToImbalanceOnly();
void WINAPI TD_SetNyseConvertToImbalanceOnly(bool convertToImbalanceOnly);

bool WINAPI TD_IsTradingAllowed();
void WINAPI TD_SetTradingAllowed(bool allowed);

bool WINAPI TD_IsDefaultOnlyTradingAllowed();
void WINAPI TD_SetDefaultOnlyTradingAllowed(bool defaultOnly);

RoundLotPolicy WINAPI TD_GetRoundLotPolicy();
void WINAPI TD_SetRoundLotPolicy(RoundLotPolicy policy);
bool WINAPI TD_IsCancelWashOrders();
void WINAPI TD_SetCancelWashOrders(bool cancel);

//bool WINAPI TD_IsAllowOddLotOrdersInSimulation();
//void TD_SetAllowOddLotOrdersInSimulation(bool allow);

bool WINAPI TD_IsAllowSellBorrowedInSimulation();
void WINAPI TD_SetAllowSellBorrowedInSimulation(bool allow);

bool WINAPI TD_IsQsmtInSimulation();
void WINAPI TD_SetQsmtInSimulation(bool allow);

const unsigned int& WINAPI TD_GetUserTypeLive();
const unsigned int& WINAPI TD_GetUserTypeInSimulation();
void WINAPI TD_SetUserTypeInSimulation(unsigned int userType);

#ifdef FIRM_VALUES
const bool& WINAPI TD_CanSeeFirmPositions();
#ifndef FIRM_VALUES_ALWAYS
void WINAPI TD_SetKeepFirmPositionSubscription(bool keep);
#endif
unsigned short WINAPI TD_GetAccountAggregatorCount();
unsigned short WINAPI TD_GetNumberOfAccountAggregatorUntradeableListsToLoad();
bool WINAPI TD_AreAllAccountAggregatorUntradeableListsLoaded();
const AccountAggregator* WINAPI TD_FindAccountAggregator(const AccountAggregatorId& accountAggregatorId);
TakionIterator* WINAPI TD_CreateAccountAggregatorIterator();
const AccountAggregator* WINAPI TD_GetNextAccountAggregator(TakionIterator* iterator);
void WINAPI TD_LockAccountAggregatorStorage();
void WINAPI TD_UnlockAccountAggregatorStorage();

Observable* WINAPI TD_GetNewFirmPositionObservable();

#endif

const bool& WINAPI TD_IsUserSupervisorLive();
const bool& WINAPI TD_IsUserSupervisorInSimulation();
const bool& WINAPI TD_IsUserSupervisor();

bool WINAPI TD_IsResizeToBpa();
void WINAPI TD_SetResizeToBpa(bool resizeToBpa);

unsigned char WINAPI TD_GetOversellSplitPolicy();
void WINAPI TD_SetOversellSplitPolicy(unsigned char oversellSplitPolicy);

bool WINAPI TD_IsResizeShortToBorrowed();
void WINAPI TD_SetResizeShortToBorrowed(bool resize);

bool WINAPI TD_IsRemoveDelayedOrdersOnClosePrice();
void WINAPI TD_SetRemoveDelayedOrdersOnClosePrice(bool remove);

bool WINAPI TD_IsCancelOversellInsteadOfResize();
void WINAPI TD_SetCancelOversellInsteadOfResize(bool cancel);

bool WINAPI TD_IsCancelOvershortInsteadOfResize();
void WINAPI TD_SetCancelOvershortInsteadOfResize(bool cancel);

bool WINAPI TD_IsDestroyCanceledOrders();
void WINAPI TD_SetDestroyCanceledOrders(bool destroy);
bool WINAPI TD_IsThreadDelays();
void WINAPI TD_SetThreadDelays(bool threadDelays);

unsigned char WINAPI TD_GetLevel2LogDepth();
void WINAPI TD_SetLevel2LogDepth(unsigned char depth);

void WINAPI TD_SetAllPhantomPositionsFlat();

//ActOnMaxLossMode WINAPI TD_GetActOnMaxLossMode();
//void WINAPI TD_SetActOnMaxLossMode(ActOnMaxLossMode mode);

bool  WINAPI TD_IsMarketClosedForTheDay();

TakionIterator* WINAPI TD_CreateIndexDescriptionIterator();
const IndexDescription* WINAPI TD_GetNextIndexDescription(TakionIterator* iterator);

bool WINAPI TD_SetSymbolInCommandTool(const char* symbol, bool post, unsigned int commandToolOrdinal = 0xFFFFFFFF);//commandToolOrdinal = 0xFFFFFFFF means active command tool.

unsigned __int64 WINAPI TD_GetMarketDataEntitlements();

unsigned __int64 WINAPI TD_GetMarketDataVersion();
const char* WINAPI TD_GetMarketDataVersionStr();

unsigned __int64 WINAPI TD_GetExecutorVersion();
const char* WINAPI TD_GetExecutorVersionStr();

bool WINAPI TD_IsMarketDataLogged();
bool WINAPI TD_IsExecutorLogged();

bool WINAPI TD_IsLogDefaultAccountOnly();
void WINAPI TD_SetLogDefaultAccountOnly(bool only);

bool WINAPI TD_CancelOrdersToExpire();
bool WINAPI TD_HasOrdersToExpire();
bool WINAPI TD_SetExiting(bool cancelDefaultAccountOrders, bool cancelOtherAccountOrders);
bool WINAPI TD_HasActiveNonProblematicOrdersInDefaultAccount();
bool WINAPI TD_HasActiveNonProblematicOrdersInNonDefaultAccounts();
bool WINAPI TD_DisconnectConnection(const char* ip, unsigned short port, unsigned int reconnectTries);
bool WINAPI TD_ReconnectConnection(ConnectionBase& connection);

void WINAPI TD_GetPanicCommandName(std::string& panicCommandName);
bool WINAPI TD_SetPanicCommandName(const std::string& panicCommandName);

bool WINAPI TD_IsEtbListLoaded();

bool WINAPI TD_IsQsmtRedirectTime();
bool WINAPI TD_IsQsmtPassiveRedirectTime();
bool WINAPI TD_IsBorrowOvernightTime();

bool WINAPI TD_IsDefaultAccountOnly();

void WINAPI TD_RemoveQuote(const unsigned __int64& symbol, bool side, EcnBookId bookId, unsigned int mmid, const Price& priceFrom, const Price& priceTo);

unsigned char WINAPI TD_WhichThreadCurrent();//0 - main, 1 - data, 2 - other

unsigned int WINAPI TD_GetCancelsPerSecond();
void WINAPI TD_SetCancelsPerSecond(unsigned int cancelsPerSecond);

void WINAPI TD_RequestHistoricalPrints(const char* symbol, unsigned short minute, unsigned __int64 referenceNumber, unsigned char flags, unsigned int& requestId);
bool WINAPI TD_StopHistoricalPrints(unsigned int requestId);
unsigned short WINAPI TD_GetCloseMarketMinute();
unsigned int WINAPI TD_GetCloseMarketMillisecond();

Connection* WINAPI TD_AddConnection(Connection* connection, bool tryToReconnect);
bool WINAPI TD_RemoveConnection(const Connection* connection);
bool WINAPI TD_RemoveConnectionByIpPort(const unsigned __int64& ipport);

NewsDll* WINAPI TD_GetNewsDll();

bool WINAPI TD_WriteToConnection(unsigned char dataType, const char* data, unsigned int length);
bool WINAPI TD_WriteMessageToConnection(unsigned char dataType, const Message* message);
bool WINAPI TD_WriteBuffersToConnection(unsigned char dataType, const WSABUF* cursor, unsigned int count);

const char* WINAPI TD_GetDefaultProActiveRoutingName();
unsigned int WINAPI TD_GetDefaultProActiveRoutingNumericName();

const char* WINAPI TD_GetDmaRoutingName();
unsigned int WINAPI TD_GetDmaRoutingNumericName();

const ActiveConnection* WINAPI TD_FindActiveConnection(unsigned __int64 ipport);
const ActiveConnection* WINAPI TD_FindActiveConnectionByIpPort(unsigned int ip, unsigned short port);

bool WINAPI TD_IsRoutingInstructionAddLiquidityOnly(unsigned int routingId);

void WINAPI TD_SetEquityTimeFrame(unsigned int millisecond);//0 - use 1 minute time frame
const unsigned short& WINAPI TD_GetCurrentMinute();

const unsigned int& WINAPI TD_GetLoadedTodaysStockChartCount();
const unsigned int& WINAPI TD_GetLoadedTodaysIndexChartCount();

unsigned char WINAPI TD_GetStopOrderTypeBase(unsigned char stopOrderType, unsigned char stopOrderBase);
unsigned char WINAPI TD_GetPegTypeByExecInstruction(unsigned int execInstruction);
unsigned int WINAPI TD_GetExecInstructionByPegType(unsigned char pegType);

//Message Watch
enum ExtensionRequestFilterEnum : unsigned char
{
	REQF_ORDER,
	REQF_ORDER_CANCEL,
	REQF_ORDER_REPLACE,
	REQF_STOCK_SUBSCRIBE,
	REQF_HEARTBEAT,
	REQF_LOAD_HISTORY,
	REQF_LOGON,
	REQF_PUBLIC_KEY,

	REQF_MS_SUBSCRIBE,
	REQF_MS_CHART,

	REQF_HIST_CHART,
	REQF_HIST_PRINT,

	REQF_UNDERLIER_SUBSCRIBE,
	REQF_OPTION_SUBSCRIBE,

	REQF_FIRM,

	REQF_Count,
};

enum ExtensionResponseFilterEnum : unsigned char
{
	RSPF_LOGON,

	RSPF_MD_SUBSCRIPTION,
	RSPF_MD_QUOTE,
	RSPF_MD_QUOTE_EXEC_HIDDEN,
	RSPF_MD_QUOTE_INDICATORS,
	RSPF_MD_LEVEL1,
	RSPF_MD_LEVEL2,
	RSPF_MD_PRINT,
	RSPF_MD_PRINT_CORRECTION,
	RSPF_MD_IMBALANCE,
	RSPF_MD_RESET,

	RSPF_MS_SUBSCRIPTION,
	RSPF_MS_LEVEL1,
	RSPF_MS_PRINT,
	RSPF_MS_PRINT_CORRECTION,
	RSPF_MS_IMBALANCE,
	RSPF_MS_QUOTE_INDICATORS,
	RSPF_MS_RESET,

	RSPF_MS_INDEX,

	RSPF_MS_CHART,
	RSPF_MS_CHART_CORRECTION,
	RSPF_MS_NEW_MINUTE,

	RSPF_HIST_CHART,
	RSPF_HIST_PRINT,
/*
	RSPF_ORDER_ACK,
	RSPF_ORDER_UPDATE,
	RSPF_ORDER_KILL,
	RSPF_ORDER_REJECT,
	RSPF_ORDER_EXEC,

	RSPF_CANCEL_ACK,
	RSPF_REPLACE_ACK,
	RSPF_REPLACE_DONE,
*/
	RSPF_ORDER,
	RSPF_ACCOUNT,
	RSPF_FIRM,
	RSPF_HTB,

	RSPF_Count
};

void WINAPI TD_SetExtensionRequestFilter(const HMODULE& hmodule, const unsigned int& requestFilter);
void WINAPI TD_AddRemoveExtensionRequestFilter(const HMODULE& hmodule, const unsigned int& addRequestFilter, const unsigned int& removeRequestFilter);
void WINAPI TD_SetExtensionResponseFilter(const HMODULE& hmodule, const unsigned int& responseFilter);
void WINAPI TD_AddRemoveExtensionResponseFilter(const HMODULE& hmodule, const unsigned int& addResponseFilter, const unsigned int& removeResponseFilter);

//Message Simulation
MessageThread* WINAPI TD_ObtainMessageSimulationThread();
bool WINAPI TD_ReleaseMessageSimulationThread(const MessageThread* const& messageSimulationThread);

char WINAPI TD_GetSideByServerSide(unsigned char serverSide);

#ifdef __cplusplus
}
#endif

