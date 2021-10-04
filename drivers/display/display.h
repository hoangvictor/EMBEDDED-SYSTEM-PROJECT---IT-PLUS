#include "RTC_KL46.h"
#include "LCD.h"
#include "Key_Pad.h"

#define PTC1 20
#define PTC2 21
#define PTB3 22
#define PTB2 23
#define PTB1 24
#define PTB0 25
#define PTB30 26
#define PTB20 27
#define PTE23 28
#define PTE22 29
#define PTE21 30 
#define PTE20 31
#define MODE_1_TIME 32
#define MODE_EVERYDAY 33

#define DELAY_DISPLAY for(int i = 0; i<=500000;i++); check_alarm_time(date, date_a);
#define HIGH_DELAY for(int i = 0; i<=3500000;i++)

typedef struct RtcAlarmtime
{
  rtc_datetime_t date;
  uint8_t status;
  uint8_t port;
  uint8_t mode;
} rtc_alarmtime_t;

//*******All functions********//
void display_port_init();
void home_screen(rtc_datetime_t date, rtc_alarmtime_t date_a[]);
void ports_and_alarms(rtc_datetime_t date, rtc_alarmtime_t *date_a);
void set_port(rtc_datetime_t date, rtc_alarmtime_t *date_a);

//Current_time settings
void set_cur_time(rtc_datetime_t date, rtc_alarmtime_t date_a[]);
void current_time_F2(rtc_datetime_t date, rtc_alarmtime_t date_a[]);
void change_cur_time(rtc_datetime_t date, rtc_alarmtime_t date_a[]);

//Alarm_time settings
void alarm_time(rtc_datetime_t date, rtc_alarmtime_t date_a[]);
void create_alarm(rtc_datetime_t date, rtc_alarmtime_t date_a[]);
void view_alarm(rtc_datetime_t date, rtc_alarmtime_t date_a[]);
void check_alarm_time(rtc_datetime_t date, rtc_alarmtime_t *date_a);
//****************************//