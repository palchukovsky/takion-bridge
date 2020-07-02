#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef TL_EXPORTS
#define TL_API __declspec(dllexport)
#else
#define TL_API __declspec(dllimport)
#endif

#ifndef _DEBUG
#define NED_MALLOC
#endif

const char* const TakionLogHeaderVersion = "1.0.1.174";

class TL_API TakionTimer
{
public:
	virtual ~TakionTimer(){}
	unsigned int GetId() const{return m_id;}
	void SetId(unsigned int id){m_id = id;}
//	unsigned int GetState() const{return m_state;}
//	void SetState(unsigned int state){m_state = state;}
	bool isOwn() const{return m_own;}
	void SetOwn(bool own){m_own = own;}
	virtual void Triggered(unsigned int count) = 0;
	virtual void Activate() = 0;
	virtual void AdjustOnTimeChange(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int prevDate){}
	virtual unsigned int Reactivate(){return 0;}
	virtual unsigned int GetTriggerCode(unsigned int reactivateCode) const{return reactivateCode;}
	virtual bool isValid() const{return true;}
	virtual unsigned int GetState() const{return 0;}
protected:
//	TakionTimer(bool own = true):m_id(0xFFFFFFFF),m_state(0),m_own(own){}
	TakionTimer(bool own = true):m_id(0xFFFFFFFF),m_own(own){}
	unsigned int m_id;
//	unsigned int m_state;
	bool m_own;
};

class TL_API TakionTimerOnce : public TakionTimer
{
public:
	unsigned int GetMilliseconds() const{return m_milliseconds;}
	virtual void Activate();
	virtual unsigned int Reactivate();
	virtual bool isValid() const{return m_milliseconds > 0;}
protected:
	TakionTimerOnce(unsigned int milliseconds, bool own = true):
		TakionTimer(own),
		m_milliseconds(milliseconds ? milliseconds : 1)
	{}
	unsigned int m_milliseconds;
};

class TL_API TakionTimerDayState : public TakionTimer
{
public:
	virtual unsigned int GetState() const{return m_state;}
	unsigned int GetStateCount() const{return m_stateCount;}
	virtual void Activate();
	virtual unsigned int Reactivate();
	virtual unsigned int GetTriggerCode(unsigned int reactivateCode) const{return m_state + 1;}
	typedef std::map<unsigned int, unsigned int> StateMap;
	const StateMap& GetStateMap() const{return m_stateMap;}
	virtual void AdjustOnTimeChange(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int prevDate);
	virtual bool isValid() const{return m_stateCount > 1;}
protected:
	TakionTimerDayState(const unsigned int* dayMillisecondArray, unsigned int stateCount, bool own = true):
		TakionTimer(own),
		m_stateMapEnd(m_stateMap.end()),
		m_stateCount(0),
		m_state(0)
	{
		for(; stateCount; --stateCount, ++dayMillisecondArray)
		{
			m_stateMap.insert(StateMap::value_type(*dayMillisecondArray, 0));
		}
		m_stateCount = (unsigned int)m_stateMap.size();
		unsigned int state = 0;
		for(StateMap::iterator it = m_stateMap.begin(); it != m_stateMapEnd; ++it, ++state)
		{
			it->second = state;
		}
		m_stateMapBegin = m_stateMap.begin();
	}
	unsigned int UpdateState();
	StateMap m_stateMap;
	StateMap::const_iterator m_stateMapEnd;
	StateMap::const_iterator m_stateMapBegin;
	unsigned int m_stateCount;
	unsigned int m_state;
};

class TL_API TakionTimerRepeat : public TakionTimer
{
public:
	unsigned int GetCycleCount() const{return m_cycleCount;}
	unsigned int GetCycle() const{return m_cycle;}
	unsigned int GetHalfCycle() const{return m_halfCycle;}
	unsigned int GetOffset() const{return m_offset;}
//	unsigned int GetAdjustFrequency() const{return m_adjustFrequency;}
//	void SetAdjustFrequency(unsigned int frequency){m_adjustFrequency = frequency;}
	virtual void Activate();
	virtual unsigned int Reactivate();
//	virtual void AdjustOnTimeChange(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int prevDate){DoActivate();}
	virtual bool isValid() const{return m_cycle > 0;}
//	void SetValues(unsigned int cycle, unsigned int offset, unsigned int adjustFrequency = 0)
	void SetValues(unsigned int cycle, unsigned int offset)
	{
//		if(adjustFrequency)m_adjustFrequency = adjustFrequency;
		if(!cycle)cycle = 1;
		offset %= cycle;
		bool changed = false;
		if(m_cycle != cycle)
		{
			m_cycle = cycle;
			m_halfCycle = m_cycle >> 1;
			changed = true;
		}
		if(m_offset != offset)
		{
			m_offset = offset;
			changed = true;
		}
		if(changed)Activate();
	}
	unsigned int CalculateCycleCount(const unsigned int& millisecond) const{return (millisecond - m_offset + m_halfCycle) / m_cycle;}
protected:
//	TakionTimerRepeat(unsigned int cycle, unsigned int offset, unsigned int adjustFrequency = 1, bool own = true):
	TakionTimerRepeat(unsigned int cycle, unsigned int offset, bool own = true):
		TakionTimer(own),
		m_cycle(cycle ? cycle : 1),
		m_halfCycle(m_cycle >> 1),
		m_offset(offset % m_cycle),
//		m_adjustFrequency(adjustFrequency),
//		m_adjustCount(0),
		m_cycleCount(0),
		m_timerSetting(0)
	{}
	unsigned int DoActivate();
	unsigned int m_cycle;
	unsigned int m_halfCycle;
	unsigned int m_offset;
//	unsigned int m_adjustFrequency;
//	unsigned int m_adjustCount;
	unsigned int m_cycleCount;
	unsigned int m_timerSetting;
};

#ifdef __cplusplus
extern "C"
{
#endif

const char* WINAPI TL_GetModuleVersionStr();
unsigned __int64 WINAPI TL_GetModuleVersionNum();
const char* WINAPI TL_GetHeaderVersion();
unsigned __int64 WINAPI TL_GetHeaderVersionNum();
const char* WINAPI TL_GetFilePathAndName();
const char* WINAPI TL_GetPlatform();
const char* WINAPI TL_GetFileDescription();
void WINAPI TL_GetDllBuildDescription(std::string& buildStr);

const TIME_ZONE_INFORMATION& WINAPI TL_GetNewYorkTimeZone();
unsigned int WINAPI TL_GetDayMillisecondFromSystemTime(const SYSTEMTIME& t);
unsigned int WINAPI TL_GetCurrentMillisecond();
unsigned int WINAPI TL_GetCurrentServerMillisecond();
void WINAPI TL_SetServerMillisecond(unsigned int serverMillisecond);
unsigned int WINAPI TL_GetCurrentTimeTokens(unsigned int& hour, unsigned int& minute, unsigned int& second);
unsigned int WINAPI TL_GetCurrentServerTimeTokens(unsigned int& hour, unsigned int& minute, unsigned int& second);
const bool& WINAPI TL_IsServerTimeInitialized();
//returns localMillisecond
unsigned int WINAPI TL_GetCurrentServerAndLocalTimeTokens(unsigned int& localHour, unsigned int& localMinute, unsigned int& localSecond, unsigned int& localMillisecond, unsigned int& serverHour, unsigned int& serverMinute, unsigned int& serverSecond, unsigned int& serverMillisecond);

bool WINAPI TL_IsLeapYear(unsigned int year);
const unsigned int* WINAPI TL_GetDaysInAllMonths(unsigned int year);
unsigned int WINAPI TL_GetDaysInMonth(unsigned int month, unsigned int year);
const unsigned int* WINAPI TL_GetDaysInAllMonthsCumulative(unsigned int year);
unsigned int WINAPI TL_GetDaysInMonthCumulative(unsigned int month, unsigned int year);
unsigned int WINAPI TL_GetDaysBetweenMonths(unsigned int month1, unsigned int month2, unsigned int year);
unsigned int WINAPI TL_GetDaysToYearStart(unsigned int year, unsigned int month, unsigned int day);
unsigned int WINAPI TL_GetDaysToYearEnd(unsigned int year, unsigned int month, unsigned int day);
unsigned int WINAPI TL_GetDaysToMonthStart(unsigned int year, unsigned int month, unsigned int& day);
unsigned int WINAPI TL_GetDaysToMonthEnd(unsigned int year, unsigned int month, unsigned int& day);
unsigned int WINAPI TL_GetDaysBetweenYears(unsigned int year1, unsigned int year2);
bool WINAPI TL_IsDateValid(unsigned int year, unsigned int month, unsigned int day);
bool WINAPI TL_IsDatePassed(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_DateAddDays(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);
void WINAPI TL_DateSubtractDays(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);
void WINAPI TL_DateAddWeeks(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int weeks);
void WINAPI TL_DateSubtractWeeks(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int weeks);
void WINAPI TL_DateAddMonths(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int months);
void WINAPI TL_DateSubtractMonths(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int months);
void WINAPI TL_DateAddBusinessDays(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);
void WINAPI TL_DateSubtractBusinessDays(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);
bool WINAPI TL_GetBusinessDateNext(unsigned int& year, unsigned int& month, unsigned int& day);
bool WINAPI TL_GetBusinessDatePrevious(unsigned int& year, unsigned int& month, unsigned int& day);
int WINAPI TL_DateDiff(unsigned int year1, unsigned int month1, unsigned int day1, unsigned int year2, unsigned int month2, unsigned int day2);
int WINAPI TL_CompareDates(unsigned int year1, unsigned int month1, unsigned int day1, unsigned int year2, unsigned int month2, unsigned int day2);
int WINAPI TL_GetDayFrom1970(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_GetDateFrom1970(unsigned int& year, unsigned int& month, unsigned int& day, int days);
unsigned int WINAPI TL_CalculateDayCountFromDate(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_CalculateDateFromDayCount(unsigned int days, unsigned int& year, unsigned int& month, unsigned int& day);
unsigned int WINAPI TL_GetDayOfWeek(unsigned int year, unsigned int month, unsigned int day);
unsigned int WINAPI TL_GetDateForDayOfWeek(unsigned int year, unsigned int month, unsigned int dayOfWeek, unsigned int ordinal);
unsigned int WINAPI TL_CalculateBusinessDayCountFromDate(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_CalculateDateFromBusinessDayCount(unsigned int businessDays, unsigned int& year, unsigned int& month, unsigned int& day);
int WINAPI TL_BusinessDateDiff(unsigned int year1, unsigned int month1, unsigned int day1, unsigned int year2, unsigned int month2, unsigned int day2);
int WINAPI TL_BusinessDateDiffByFormattedDates(unsigned int date1, unsigned int date2);
unsigned int WINAPI TL_CalculateBusinessDayCountSinceYearStart(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_CalculateDateFromYearBusinessDayCount(unsigned int businessDays, unsigned int year, unsigned int& month, unsigned int& day);

unsigned int WINAPI TL_GetHolidayCountBetweenDatesOfOneYear(unsigned int year, unsigned int month1, unsigned int day1, unsigned int month2, unsigned int day2);
unsigned int WINAPI TL_GetHolidayCountBetweenDates(unsigned int year1, unsigned int month1, unsigned int day1, unsigned int year2, unsigned int month2, unsigned int day2);

unsigned int WINAPI TL_GetTodaysDate();
unsigned int WINAPI TL_GetTodaysDayOfWeek();
unsigned int WINAPI TL_GetYear();
unsigned int WINAPI TL_GetMonth();
unsigned int WINAPI TL_GetDay();
bool WINAPI TL_IsTodayShortDay();
unsigned short WINAPI TL_GetCloseMarketMinute();
unsigned int WINAPI TL_GetCloseMarketMillisecond();
unsigned __int64 WINAPI TL_GetPerformanceFrequency();
unsigned int WINAPI TL_GetTickResolution();

unsigned int WINAPI TL_GetTimeAdjustment();
unsigned int WINAPI TL_GetTimeIncrement();
bool WINAPI TL_IsTimeAdjustmentDisabled();

const char* WINAPI TL_GetDayOfWeekName(unsigned int dayOfWeek);

//http://www.nasdaqtrader.com/Trader.aspx?id=Calendar
enum Holiday
{
	TLH_NEW_YEAR,
	TLH_MLK_DAY,
	TLH_PRESIDENTS,
	TLH_GOOD_FRIDAY,
	TLH_MEMORIAL,
	TLH_INDEPENDENCE,
	TLH_LABOR,
	TLH_THANKSGIVING,
	TLH_CHRISTMAS,

	TLH_HOLIDAY_COUNT
};

enum ShortDay
{
	TLS_BEFORE_INDEPENDENCE,
	TLS_AFTER_THANKSGIVING,
	TLS_BEFORE_CHRISTMAS,

	TLS_SHORT_DAY_COUNT
};

const char* WINAPI TL_GetHolidayName(Holiday holiday);
const char* WINAPI TL_GetShortDayName(ShortDay shortDay);

bool WINAPI TL_GetHolidayDate(Holiday holiday, unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetNewYearDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetMartinLutherKingDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetPresidentsDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetGoodFridayDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetMemorialDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetIndependenceDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetLaborDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetThanksgivingDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetChristmasDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);

Holiday WINAPI TL_IsHoliday(unsigned int year, unsigned int month, unsigned int day);

bool WINAPI TL_GetShortDayDate(ShortDay shortDay, unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetBeforeIndependenceDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetAfterThanksgivingDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetBeforeChristmasDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
ShortDay WINAPI TL_IsShortDay(unsigned int year, unsigned int month, unsigned int day);

Holiday WINAPI TL_GetNextHoliday(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
ShortDay WINAPI TL_GetNextShortDay(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);

bool WINAPI TL_IsDateNewBusinessWeek(unsigned int year, unsigned int month, unsigned int day);
bool WINAPI TL_IsDateNewBusinessMonth(unsigned int year, unsigned int month, unsigned int day);
bool WINAPI TL_IsDateNewBusinessYear(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_IsDateNewBusinessWeekMonthYear(unsigned int year, unsigned int month, unsigned int day, bool& newWeek, bool& newMonth, bool& newYear);
bool WINAPI TL_IsTodayNewBusinessWeek();
bool WINAPI TL_IsTodayNewBusinessMonth();
bool WINAPI TL_IsTodayNewBusinessYear();

void* WINAPI TL_CreateLogFile(const char* name, bool outputDate = true, const char* extension = "log", unsigned int date = 0, const char* path = NULL);
void WINAPI TL_DestroyLogFile(void* logFile);
void WINAPI TL_Log(void* logFile, const char* message, const char* prefix = NULL, unsigned int level = 0);
const char* WINAPI TL_GetLogFilePath(const void* logFile);
bool WINAPI TL_IsLogFileValid(const void* logFile);
void WINAPI TL_DestroyLogFiles();

bool WINAPI TL_ClearLogFilesBeforeDaysAgo(const char* name, unsigned int daysAgo, const char* extension = "log", const char* path = NULL);
void WINAPI TL_SetDaysToKeepLogFiles(unsigned int days);
void WINAPI TL_ClearAllObsoleteLogFiles(const std::string* except);

void WINAPI TL_SetLogFile(void* logFile);
void* WINAPI TL_GetLogFile();

void WINAPI TL_CloseAllLogFiles();
bool WINAPI TL_GetPrevLogFilePathAndName(std::string& filePathAndName);
const char* WINAPI TL_GetDateFromFileName(const char* name, unsigned int& year, unsigned int& month, unsigned int& day);
bool WINAPI TL_IsPrevLogFileExist(const char* filePathAndName);

unsigned int WINAPI TL_GetStartMillisecond();
unsigned int WINAPI TL_GetStartDate();
void WINAPI TL_GetStartDateTokens(unsigned int& year, unsigned int& month, unsigned int& day);
void WINAPI TL_GetCurrentNewYorkTime(SYSTEMTIME& nyTime);

void WINAPI TL_AdjustTimeForward(unsigned int millisecond);
void WINAPI TL_AdjustTimeBackward(unsigned int millisecond);

typedef void (WINAPI *NextDayStartedCallback)();
void WINAPI TL_RegisterNextDayStartedCallback(NextDayStartedCallback func);
void WINAPI TL_UnregisterNextDayStartedCallback(NextDayStartedCallback func);

typedef void (WINAPI *TimeChangedCallback)(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int todaysDate);
void WINAPI TL_RegisterTimeChangedCallback(TimeChangedCallback func);
void WINAPI TL_UnregisterTimeChangedCallback(TimeChangedCallback func);

bool WINAPI TL_AddTimer(TakionTimer* timer);
bool WINAPI TL_RemoveTimer(TakionTimer* timer);

unsigned int WINAPI TL_GetLogLevel(const void* logFile);
void WINAPI TL_SetLogLevel(void* logFile, unsigned int level);

bool WINAPI TL_IsLogBufferEmpty(void* logFile);
void WINAPI TL_ForceOutput(void* logFile);

bool WINAPI TL_IsInLogThread(std::string& filePath);

void WINAPI TL_DateNumToStr(unsigned int date, std::string& dateStr);
unsigned int WINAPI TL_DateStrToNum(const char* dateStr);

#ifdef __cplusplus
}
#endif

