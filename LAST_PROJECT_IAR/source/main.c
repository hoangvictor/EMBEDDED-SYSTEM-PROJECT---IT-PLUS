
/***********MAIN CODE***********/

//Thu vien
#include <MKL46Z4.h>
#include "display.h"

void set_up_init()
{
  reset_GPIO();                 //Reset lai toan bo thanh ghi cua module GPIO
  set_up_Key_Pad();             //Cau hinh hoat dong cho ban phim
  Setup_LCD();                  //Cau hinh hoat dong cho LCD
  display_port_init();
}

//Ham main
void main()
{
  set_up_init();    
    
  rtc_datetime_t date;
  
  // Set a start date time.
  date.year   = 2019U;
  date.month  = 3U;
  date.day    = 4U;
  date.hour   = 19U;
  date.minute = 0;
  date.second = 0;
  
  rtc_alarmtime_t date_a[12];
  
  // Alarm duoc cau hinh mac dinh ban dau de kiem tra xem Alarm co ton tai hay khong.
  for(int i = 0; i <= 11; i++)
    {
      date_a[i].status = 2U;
      date_a[i].port = 2U;
      date_a[i].mode= 2U;
    }
    
  init_rtc(&date);
  
  home_screen(date, date_a);
}
/*******************************/