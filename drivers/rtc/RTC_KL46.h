#include <stdint.h>
#include <MKL46Z4.h>

/* Mang chua cac ngay trong mot thang cua nam khong nhuan*/
static const uint8_t ULY[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U,
    31U,30U,31U};

/* Mang chua cac ngay trong mot thang cua nam nhuan*/
static const uint8_t LY[] = {0U, 31U, 29U, 31U, 30U, 31U, 30U, 31U, 31U, 30U,
    31U,30U,31U};

/* Number of days from begin of the non Leap-year*/
static const uint16_t MONTH_DAYS[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U,
    212U, 243U, 273U, 304U, 334U};

//Cac define
#define SECONDS_IN_A_DAY     (86400U)
#define SECONDS_IN_A_HOUR    (3600U)
#define SECONDS_IN_A_MIN     (60U)
#define MINS_IN_A_HOUR       (60U)
#define HOURS_IN_A_DAY       (24U)
#define DAYS_IN_A_YEAR       (365U)
#define DAYS_IN_A_LEAP_YEAR  (366U)
#define YEAR_RANGE_START     (1970U)
#define YEAR_RANGE_END       (2099U)

//Mang chua thoi gian cho module RTC
typedef struct RtcDatetime
{
   uint16_t year;    /*!< Range from 1970 to 2099.*/
   uint16_t month;   /*!< Range from 1 to 12.*/
   uint16_t day;     /*!< Range from 1 to 31 (depending on month).*/
   uint16_t hour;    /*!< Range from 0 to 23.*/
   uint16_t minute;  /*!< Range from 0 to 59.*/
   uint8_t second;   /*!< Range from 0 to 59.*/
} rtc_datetime_t;

void init_rtc(rtc_datetime_t *date);                       
void RTC_ConvertSecsToDatetime(const uint32_t * seconds, rtc_datetime_t * datetime);    
int RTC_IsDatetimeCorrectFormat(const rtc_datetime_t * datetime);
void RTC_ConvertDatetimeToSecs(const rtc_datetime_t * datetime, uint32_t * seconds);

int RTC_SetDatetime(rtc_datetime_t *datetime);
void RTC_GetDatetime(rtc_datetime_t *datetime);


/***********************************************/

