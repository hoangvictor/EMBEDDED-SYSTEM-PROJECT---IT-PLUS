#include "display.h"

//*******Functions's precisions********//
void display_port_init()
{
  set_up_GPIO('C' ,1);
  set_up_GPIO('C' ,2);
  set_up_GPIO('B' ,3);
  set_up_GPIO('B' ,2);
  set_up_GPIO('B' ,1);
  set_up_GPIO('B' ,0);
  set_up_GPIO('B' ,30);
  set_up_GPIO('B' ,20);
  set_up_GPIO('E' ,23);
  set_up_GPIO('E' ,22);
  set_up_GPIO('E' ,21);
  set_up_GPIO('E' ,20);
  
  GPIOC->PDDR |= (1<<1) | (1<<2);
  GPIOB->PDDR |= (1<<3) | (1<<2) | (1<<1)| (1<<0)| (1<<30)| (1<<20);
  GPIOE->PDDR |= (1<<23) | (1<<22) | (1<<21) | (1<<20);
  
  GPIOC->PCOR |= (1<<1) | (1<<2);
  GPIOB->PCOR |= (1<<3) | (1<<2) | (1<<1)| (1<<0)| (1<<30)| (1<<20);
  GPIOE->PCOR |= (1<<23) | (1<<22) | (1<<21) | (1<<20);
}

void home_screen(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{
  uint8_t check_KeyPad;
  while (1)
  {
    check_KeyPad = 0;
    RTC_GetDatetime(&date);
    Clear_Screen_LCD();  
    Write_String_LCD("DATE: ");
    Print_Number(date.day);
    Write_Char_LCD('/');
    Print_Number(date.month);
    Write_Char_LCD('/');
    Print_Number(date.year);
    
    Go_To_XY_LCD(1,0);
    Write_String_LCD("F1 |");
    
    Print_Number(date.hour);
    Write_Char_LCD(':');
    Print_Number(date.minute);
    Write_Char_LCD(':');
    Print_Number(date.second);
    
    Go_To_XY_LCD(1,12);
    Write_String_LCD("| F2");
    
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == F1)
    {
      set_cur_time(date, date_a);
    }
    else if(check_KeyPad == F2)
    {
      ports_and_alarms(date, date_a);
    }
    DELAY_DISPLAY;
  }
}

void ports_and_alarms(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{
  uint8_t check_KeyPad;
  while (1)
  {
    Clear_Screen_LCD();  
    Write_String_LCD("F1:Port settings");
    Go_To_XY_LCD(1,0);
    Write_String_LCD("F2:Alarm settings");
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == F1)
    {
      set_port(date, date_a);
    }
    else if(check_KeyPad == F2)
    {
      alarm_time(date, date_a);
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN  || check_KeyPad == ESC)
    {
      home_screen(date, date_a);
    }
    DELAY_DISPLAY;
  }
}

void set_port(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{
  uint8_t check_KeyPad;
  
INTRO:
  while (1)
  {
    Clear_Screen_LCD();  
    Write_String_LCD("Change port's");
    Go_To_XY_LCD(1,0);
    Write_String_LCD("  status    |ENT");
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ENTER)
    {
      break;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ESC)
    {
      ports_and_alarms(date, date_a);
    }
    DELAY_DISPLAY;
  }
  
  while (1)
  {
    Clear_Screen_LCD();  
    Write_String_LCD("Select to change");
    Go_To_XY_LCD(1,0);
    Write_String_LCD("port status |ENT");
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ENTER)
    {
      break;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ESC)
    {
      goto INTRO;
    }
    DELAY_DISPLAY;
  }
  
PORT_1: //PORT SELECT 1   
  while(1)
  {
    Clear_Screen_LCD();  
    Write_String_LCD("1:PTC1   2:PTC2"); 
    Go_To_XY_LCD(1,0);
    Write_String_LCD("3:PTB3   4:PTB2"); 
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC)
    {
      ports_and_alarms(date, date_a);
    }
    else if(check_KeyPad == RIGHT_BUTTON)
    {
      break;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ONE)
    {
      GPIOC->PTOR |= 1 << 1;
      goto END;
    }
    else if(check_KeyPad == TWO)
    {
      GPIOC->PTOR |= 1 << 2;
      goto END;
    }
    else if(check_KeyPad == THREE)
    {
      GPIOB->PTOR |= 1 << 3;
      goto END;
    }
    else if(check_KeyPad == FOUR)
    {
      GPIOB->PTOR |= 1 << 2;
      goto END;
    }
    DELAY_DISPLAY;
  }
  
PORT_2: //PORT SELECT 2
  while(1)
  {    
    Clear_Screen_LCD();  
    Write_String_LCD("1:PTB1   2:PTB0"); 
    Go_To_XY_LCD(1,0);
    Write_String_LCD("3:PTB30  4:PTB20"); 
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC)
    {
      goto PORT_1;
    }
    else if(check_KeyPad == RIGHT_BUTTON)
    {
      break;
    }
    else if(check_KeyPad == LEFT_BUTTON)
    {
      goto PORT_1;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ONE)
    {
      GPIOB->PTOR |= 1 << 1;
      goto END;
    }
    else if(check_KeyPad == TWO)
    {
      GPIOB->PTOR |= 1 << 0;
      goto END;
    }
    else if(check_KeyPad == THREE)
    {
      GPIOB->PTOR |= 1 << 30;
      goto END;
    }
    else if(check_KeyPad == FOUR)
    {
      GPIOB->PTOR |= 1 << 20;
      goto END;
    }
    DELAY_DISPLAY;
  }
  
//PORT SELECT 3
  while(1)
  {    
    Clear_Screen_LCD();  
    Write_String_LCD("1:PTE23  2:PTE22"); 
    Go_To_XY_LCD(1,0);
    Write_String_LCD("3:PTE21  4:PTE20"); 
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC)
    {
      goto PORT_1;
    }
    else if(check_KeyPad == LEFT_BUTTON)
    {
      goto PORT_2;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ONE)
    {
      GPIOE->PTOR |= 1 << 23;
      goto END;
    }
    else if(check_KeyPad == TWO)
    {
      GPIOE->PTOR |= 1 << 22;
      goto END;
    }
    else if(check_KeyPad == THREE)
    {
      GPIOE->PTOR |= 1 << 21;
      goto END;
    }
    else if(check_KeyPad == FOUR)
    {
      GPIOE->PTOR |= 1 << 20;
      goto END;
    }
    DELAY_DISPLAY;
  }
END:
}

void set_cur_time(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{
  uint8_t check_KeyPad; 
  
  while (1)
  {
    check_KeyPad = 0;
    Clear_Screen_LCD();  
    Write_String_LCD("F1: Set time");   
    
    Go_To_XY_LCD(1,0);
    Write_String_LCD("F2: Current time");
      
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == F1)
    {
      change_cur_time(date, date_a);
    }
    else if(check_KeyPad == F2)
    {
      current_time_F2(date, date_a);
    }
    else if(check_KeyPad == ESC || check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    DELAY_DISPLAY;
  }
}

void current_time_F2(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{  
  uint8_t check_KeyPad;
  while(1)
  {
    check_KeyPad = 0;
    RTC_GetDatetime(&date);
    Clear_Screen_LCD();  
    Write_String_LCD("DATE: ");
    Print_Number(date.day);  
    Write_Char_LCD('/');
    Print_Number(date.month);
    Write_Char_LCD('/');
    Print_Number(date.year);   
    Go_To_XY_LCD(1,0);
    Write_String_LCD("ESC | ");  
    Print_Number(date.hour);
    Write_Char_LCD(':');
    Print_Number(date.minute);
    Write_Char_LCD(':');
    Print_Number(date.second);
    
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC || check_KeyPad == ENTER)
    {
      break;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    DELAY_DISPLAY;
  }
}

void change_cur_time(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{
  uint8_t nhuan, chuc_nam, dvi_nam, chuc_thang, dvi_thang, chuc_ngay, dvi_ngay, chuc_gio, dvi_gio, chuc_phut, dvi_phut, chuc_giay, dvi_giay, check_KeyPad;
  uint16_t nam;
  
  SET_YEAR: //Set year    
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Year:"); 
      Go_To_XY_LCD(1,5);
      Write_Char_LCD('2');
      Write_Char_LCD('0');
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      chuc_nam = 10;
      num_check_Key_Pad(&chuc_nam);
      DELAY_DISPLAY;
    }while(chuc_nam > 9);
    
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Year:"); 
      Go_To_XY_LCD(1,5);
      Write_Char_LCD('2');
      Write_Char_LCD('0');
      Write_Char_LCD((char)chuc_nam + '0');
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      dvi_nam = 10;
      num_check_Key_Pad(&dvi_nam);
      DELAY_DISPLAY;
    }while(dvi_nam > 9);
    
    Display_Control_LCD(1,0,0);           
    
    nam = 2000 + chuc_nam*10 + dvi_nam;
    if(((nam % 4 == 0) && (nam % 100 != 0)) || (nam % 400 == 0))
    {
      nhuan = 1;
    }  
    else
    {
      nhuan = 0;
    }
    
    while(1)
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Year:"); 
      Go_To_XY_LCD(1,5);
      Write_Char_LCD('2');
      Write_Char_LCD('0');
      Write_Char_LCD((char)chuc_nam + '0');
      Write_Char_LCD((char)dvi_nam + '0');
      
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC)
      {
        goto SET_YEAR;
      }
      else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == LEFT_BUTTON)
      {
        set_cur_time(date, date_a);
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
      DELAY_DISPLAY;
    }
    
  SET_MONTH://Set month    
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Month:"); 
      Go_To_XY_LCD(1,7);
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      chuc_thang = 2;
      num_check_Key_Pad(&chuc_thang);
      DELAY_DISPLAY;
    }while(chuc_thang > 1);
    
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Month:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_thang + '0');
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      dvi_thang = 13;   
      num_check_Key_Pad(&dvi_thang);
      DELAY_DISPLAY;
    }while((dvi_thang + chuc_thang*10 > 12) || (dvi_thang + chuc_thang*10 < 1));
    Write_Char_LCD((char)dvi_thang + '0');
    
    Display_Control_LCD(1,0,0);   
    
    while(1)
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Month:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_thang + '0');
      Write_Char_LCD((char)dvi_thang + '0');
      
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC)
      {
        goto SET_MONTH;
      }
      else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == LEFT_BUTTON)
      {
        goto SET_YEAR;
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
      DELAY_DISPLAY;
    }
    
  SET_DAY://Set day   
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Day:"); 
      Go_To_XY_LCD(1,7);
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      chuc_ngay = 4;              
      num_check_Key_Pad(&chuc_ngay);
      DELAY_DISPLAY;
    }while(chuc_ngay > ULY[chuc_thang*10 + dvi_thang - 1]/10);

    if(nhuan == 1)
    {
      do
      {
        Clear_Screen_LCD();  
        Write_String_LCD("   Set Day:"); 
        Go_To_XY_LCD(1,7);
        Write_Char_LCD((char)chuc_ngay + '0');
        Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
        dvi_ngay = 32;      
        num_check_Key_Pad(&dvi_ngay);
        DELAY_DISPLAY;
      }while((chuc_ngay*10 + dvi_ngay > LY[chuc_thang*10 + dvi_thang]) || (chuc_ngay*10 + dvi_ngay < 1));
    }
    else
    {
      do
      {
        Clear_Screen_LCD();  
        Write_String_LCD("   Set Day:"); 
        Go_To_XY_LCD(1,7);
        Write_Char_LCD((char)chuc_ngay + '0');
        Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
        dvi_ngay = 32;    
        num_check_Key_Pad(&dvi_ngay);
        DELAY_DISPLAY;
      }while((chuc_ngay*10 + dvi_ngay > ULY[chuc_thang*10 + dvi_thang]) || (chuc_ngay*10 + dvi_ngay < 1));
    }

    Display_Control_LCD(1,0,0);   
    
    while(1)
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Day:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_ngay + '0');
      Write_Char_LCD((char)dvi_ngay + '0');
      
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC)
      {
        goto SET_DAY;
      }
      else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == LEFT_BUTTON)
      {
        goto SET_MONTH;
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
      DELAY_DISPLAY;
    }
    
  SET_HOUR://Set hour    
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Hour:"); 
      Go_To_XY_LCD(1,7);
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      chuc_gio = 3;
      num_check_Key_Pad(&chuc_gio);
      DELAY_DISPLAY;
    }while(chuc_gio > 2);
    
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Hour:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_gio + '0');
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      dvi_gio = 24;
      num_check_Key_Pad(&dvi_gio);
      DELAY_DISPLAY;
    }while(chuc_gio*10 + dvi_gio > 23);
    
    Display_Control_LCD(1,0,0);   
    
    while(1)
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Hour:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_gio + '0');
      Write_Char_LCD((char)dvi_gio + '0');
      
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC)
      {
        goto SET_HOUR;
      }
      else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == LEFT_BUTTON)
      {
        goto SET_MINUTE;
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
      DELAY_DISPLAY;
    }
    
  SET_MINUTE://Set Minute    
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Minute:"); 
      Go_To_XY_LCD(1,7);
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      chuc_phut = 6;      num_check_Key_Pad(&chuc_phut);
      DELAY_DISPLAY;
    }while(chuc_phut > 5);
    
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Minute:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_phut + '0');
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      dvi_phut = 60;
      num_check_Key_Pad(&dvi_phut);
      DELAY_DISPLAY;
    }while(chuc_phut*10 + dvi_phut > 59);
    
    Display_Control_LCD(1,0,0);   
    
    while(1)
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Minute:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_phut + '0');
      Write_Char_LCD((char)dvi_phut + '0');
      
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC)
      {
        goto SET_MINUTE;
      }
      else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == LEFT_BUTTON)
      {
        goto SET_HOUR;
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
      DELAY_DISPLAY;
    }
    
  SET_SECOND://Set Second   
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Second:"); 
      Go_To_XY_LCD(1,7);
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      chuc_giay = 6;
      num_check_Key_Pad(&chuc_giay);
      DELAY_DISPLAY;
    }while(chuc_giay > 5);
    
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Second:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_giay + '0');
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      dvi_giay = 60;
      num_check_Key_Pad(&dvi_giay);
      DELAY_DISPLAY;
    }while(chuc_giay*10 + dvi_giay > 59);
    
    Display_Control_LCD(1,0,0);   
    
    while(1)
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Second:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_giay + '0');
      Write_Char_LCD((char)dvi_giay + '0');
      
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC)
      {
        goto SET_SECOND;
      }
      else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == LEFT_BUTTON)
      {
        goto SET_MINUTE;
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
      DELAY_DISPLAY;
    }
    
    while(1)
    {
      //Print the time set up      
      Clear_Screen_LCD();  
      Write_String_LCD("SET: "); 
      
      date.day = chuc_ngay*10 + dvi_ngay;
      Print_Number(date.day);  
      
      Write_Char_LCD('/');
      date.month = chuc_thang*10 + dvi_thang;
      Print_Number(date.month );  
      
      Write_Char_LCD('/');
      date.year = nam;
      Print_Number(date.year);
      
      Go_To_XY_LCD(1,0);
      Write_String_LCD("ESC|");  
      
      date.hour = chuc_gio*10 + dvi_gio;
      Print_Number(date.hour);
      
      Write_Char_LCD(':');
      date.minute = chuc_phut*10 + dvi_phut;
      Print_Number(date.minute);
      
      Write_Char_LCD(':');
      date.second = chuc_giay*10 + dvi_giay;
      
      Print_Number(date.second);
      Write_String_LCD("|ENT"); 
      
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == ESC)
      {
        set_cur_time(date, date_a);
      }
      RTC_SetDatetime(&date);
      DELAY_DISPLAY;
    }
    
    while(1)
    {
      Clear_Screen_LCD();
      Write_String_LCD("  TIME CHANGED");
      Go_To_XY_LCD(1,0);
      Write_String_LCD(" Press 'ENTER'");
      
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ENTER)
      {
        break;
      }
      DELAY_DISPLAY;
    }
}

void alarm_time(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{
  uint8_t check_KeyPad;

  while(1)
  {
    check_KeyPad = 0;
    Clear_Screen_LCD(); 
    Write_String_LCD("F1: Create alarm");
    Go_To_XY_LCD(1,0);
    Write_String_LCD("F2: View alarm");
    
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == F1)
    {
      create_alarm(date,date_a);
    }
    else if(check_KeyPad == F2)
    {
      view_alarm(date, date_a);
    }
    else if(check_KeyPad == ESC || check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    DELAY_DISPLAY;
  }    
}

void create_alarm(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{
  uint8_t check_KeyPad, chuc_alarm, dvi_alarm, alarm_num, chuc_gio, dvi_gio, chuc_phut, dvi_phut, chuc_giay, dvi_giay;
  
Num_Alarm:      //Select Alarm (1-12)    
  chuc_alarm = 2;
  do
  {
    Clear_Screen_LCD();  
    Write_String_LCD("   Alarm(1-12):"); 
    Go_To_XY_LCD(1,7);
    Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
    num_check_Key_Pad(&chuc_alarm);
    DELAY_DISPLAY;
  }while(chuc_alarm > 1);
   
  dvi_alarm = 13;
  do
  {
    Clear_Screen_LCD();  
    Write_String_LCD("   Alarm(1-12):"); 
    Go_To_XY_LCD(1,7);
    Write_Char_LCD((char)chuc_alarm + '0');
    Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
    num_check_Key_Pad(&dvi_alarm);
    alarm_num = dvi_alarm + chuc_alarm*10;
    DELAY_DISPLAY;
  }while((alarm_num > 12) || (alarm_num < 1));
    
  Display_Control_LCD(1,0,0); 
  
  if(date_a[alarm_num - 1].status != 2 && date_a[alarm_num - 1].port != 2 && date_a[alarm_num - 1].mode != 2)
  {
    while(1)
    {
      Clear_Screen_LCD();  
      Write_String_LCD("Alarm existed"); 
      Go_To_XY_LCD(1,0);
      Write_String_LCD("Next? 1:YES 2:NO"); 
      
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC || check_KeyPad == TWO)
      {
        goto Num_Alarm;
      }
      else if(check_KeyPad == ONE)
      {
        break;
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
    DELAY_DISPLAY;
    }
  }
  
  while(1)
  {
    Clear_Screen_LCD();  
    Write_String_LCD("   Alarm(1-12):"); 
    Go_To_XY_LCD(1,7);
    Write_Char_LCD((char)chuc_alarm + '0');
    Write_Char_LCD((char)dvi_alarm + '0');
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC)
    {
      goto Num_Alarm;
    }
    else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
    {
      break;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    DELAY_DISPLAY;
  }
  
  SET_HOUR://Set hour    
    chuc_gio = 3;
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Hour:"); 
      Go_To_XY_LCD(1,7);
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      num_check_Key_Pad(&chuc_gio);
      DELAY_DISPLAY;
    }while(chuc_gio > 2);
    
    dvi_gio = 24;
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Hour:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_gio + '0');
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      num_check_Key_Pad(&dvi_gio);
      DELAY_DISPLAY;
    }while(chuc_gio*10 + dvi_gio > 23);
    Write_Char_LCD((char)dvi_gio + '0');
    
    Display_Control_LCD(1,0,0);   
    
    while(1)
    {
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC)
      {
        goto SET_HOUR;
      }
      else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == LEFT_BUTTON)
      {
        goto SET_MINUTE;
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
    }
    
  date_a[alarm_num - 1].date.hour = chuc_gio*10 + dvi_gio;
    
  SET_MINUTE:           //Set Minute    
    chuc_phut = 6;
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Minute:"); 
      Go_To_XY_LCD(1,7);
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      num_check_Key_Pad(&chuc_phut);
      DELAY_DISPLAY;
    }while(chuc_phut > 5);
    
    dvi_phut = 60;
    do
    {   
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Minute:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_phut + '0');
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      num_check_Key_Pad(&dvi_phut);
      DELAY_DISPLAY;
    }while(chuc_phut*10 + dvi_phut > 59);
    Write_Char_LCD((char)dvi_phut + '0');
    
    Display_Control_LCD(1,0,0);   
    
    while(1)
    {
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC)
      {
        goto SET_MINUTE;
      }
      else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == LEFT_BUTTON)
      {
        goto SET_HOUR;
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
    }
    
  date_a[alarm_num - 1].date.minute = chuc_phut*10 + dvi_phut;
    
  SET_SECOND://Set Second    
    chuc_giay = 6;
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Second:"); 
      Go_To_XY_LCD(1,7);
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      num_check_Key_Pad(&chuc_giay);
      DELAY_DISPLAY;
    }while(chuc_giay > 5);
    
    dvi_giay = 60;
    do
    {
      Clear_Screen_LCD();  
      Write_String_LCD("   Set Second:"); 
      Go_To_XY_LCD(1,7);
      Write_Char_LCD((char)chuc_giay + '0');
      Display_Control_LCD(1,1,1);           //Tao con tro nhap nhay
      num_check_Key_Pad(&dvi_giay);
      DELAY_DISPLAY;
    }while(chuc_giay*10 + dvi_giay > 59);
    Write_Char_LCD((char)dvi_giay + '0');
    
    Display_Control_LCD(1,0,0);   
    
    while(1)
    {
      check_KeyPad = 0;
      check_Key_Pad(&check_KeyPad);
      if(check_KeyPad == ESC)
      {
        goto SET_SECOND;
      }
      else if(check_KeyPad == RIGHT_BUTTON || check_KeyPad == ENTER)
      {
        break;
      }
      else if(check_KeyPad == LEFT_BUTTON)
      {
        goto SET_MINUTE;
      }
      else if(check_KeyPad == RETURN_HOME_SCREEN)
      {
        home_screen(date, date_a);
      }
    }
  
  date_a[alarm_num - 1].date.second = chuc_giay*10 + dvi_giay;
    
Mode_Alarm:      //Select Alarm (1-12)
  Clear_Screen_LCD();  
  Write_String_LCD("F1:mode 1 time"); 
  Go_To_XY_LCD(1,0);
  Write_String_LCD("F2:mode Everyday");
    
  while(1)
  {
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == F1)
    {
      date_a[alarm_num - 1].mode = MODE_1_TIME;
      break;
    }
    else if(check_KeyPad == F2)
    {
      date_a[alarm_num - 1].mode = MODE_EVERYDAY;
      break;
    }
  }
  
  Clear_Screen_LCD();  
  Write_String_LCD(" Mode selected"); 
  Go_To_XY_LCD(1,0);
  Write_String_LCD(" Press 'ENTER'");

  while(1)
  {
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC)
    {
      goto Mode_Alarm;
    }
    else if(check_KeyPad == ENTER)
    {
      break;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
  }
  
PORT_1:   
  while(1)
  {
    Clear_Screen_LCD();  
    Write_String_LCD("1:PTC1  2:PTC2"); 
    Go_To_XY_LCD(1,0);
    Write_String_LCD("3:PTB3  4:PTB2"); 
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC)
    {
      goto Mode_Alarm;
    }
    else if(check_KeyPad == RIGHT_BUTTON)
    {
      break;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ONE)
    {
      date_a[alarm_num - 1].port = PTC1;
      goto ENABLE;
    }
    else if(check_KeyPad == TWO)
    {
      date_a[alarm_num - 1].port = PTC2;
      goto ENABLE;
    }
    else if(check_KeyPad == THREE)
    {
      date_a[alarm_num - 1].port = PTB3;
      goto ENABLE;
    }
    else if(check_KeyPad == FOUR)
    {
      date_a[alarm_num - 1].port = PTB2;
      goto ENABLE;
    }
    DELAY_DISPLAY;
  }
  
PORT_2:
  while(1)
  {    
    Clear_Screen_LCD();  
    Write_String_LCD("1:PTB1   2:PTB0"); 
    Go_To_XY_LCD(1,0);
    Write_String_LCD("3:PTB30  4:PTB20"); 
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC)
    {
      goto PORT_1;
    }
    else if(check_KeyPad == RIGHT_BUTTON)
    {
      break;
    }
    else if(check_KeyPad == LEFT_BUTTON)
    {
      goto PORT_1;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ONE)
    {
      date_a[alarm_num - 1].port = PTB1;
      goto ENABLE;
    }
    else if(check_KeyPad == TWO)
    {
      date_a[alarm_num - 1].port = PTB0;
      goto ENABLE;
    }
    else if(check_KeyPad == THREE)
    {
      date_a[alarm_num - 1].port = PTB30;
      goto ENABLE;
    }
    else if(check_KeyPad == FOUR)
    {
      date_a[alarm_num - 1].port = PTB20;
      goto ENABLE;
    }
    DELAY_DISPLAY;
  }
  
PORT_3:
  while(1)
  {    
    Clear_Screen_LCD();  
    Write_String_LCD("1:PTE23  2:PTE22"); 
    Go_To_XY_LCD(1,0);
    Write_String_LCD("3:PTE21  4:PTE20"); 
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC)
    {
      goto PORT_1;
    }
    else if(check_KeyPad == LEFT_BUTTON)
    {
      goto PORT_2;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ONE)
    {
      date_a[alarm_num - 1].port = PTE23;
      goto ENABLE;
    }
    else if(check_KeyPad == TWO)
    {
      date_a[alarm_num - 1].port = PTE22;
      goto ENABLE;
    }
    else if(check_KeyPad == THREE)
    {
      date_a[alarm_num - 1].port = PTE21;
      goto ENABLE;
    }
    else if(check_KeyPad == FOUR)
    {
      date_a[alarm_num - 1].port = PTE20;
      goto ENABLE;
    }
    DELAY_DISPLAY;
  }
  
ENABLE:
  while(1)
  {    
    Clear_Screen_LCD();
    Write_String_LCD(" PORT SELECTED");
    Go_To_XY_LCD(1,0);
    Write_String_LCD(" Press 'ENTER'");
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ENTER)
    {
      break;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ESC)
    {
      goto PORT_1;
    }
    DELAY_DISPLAY;
  }
  
  while(1)
  {    
    Clear_Screen_LCD();
    Write_String_LCD("F1:Enable Alarm"); 
    Go_To_XY_LCD(1,0);
    Write_String_LCD("F2:Disable Alarm");
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == F1)
    {
      date_a[alarm_num - 1].status = 1;
      break;
    }
    else if(check_KeyPad == F2)
    {
      date_a[alarm_num - 1].status = 0;
      break;
    }
    else if(check_KeyPad == LEFT_BUTTON)
    {
      goto PORT_3;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    DELAY_DISPLAY;
  }
  
  while(1)
  {
    Clear_Screen_LCD();
    Write_String_LCD("ALA ");
    switch(alarm_num)
    {
    case 10:
      Write_String_LCD("10");  
      break;
    case 11:
      Write_String_LCD("11");
      break;
    case 12:
      Write_String_LCD("12");
      break;
    default:
      Write_Char_LCD((char)alarm_num + '0');
      break;
    }
    Write_String_LCD(": ");
    
    Print_Number(date_a[alarm_num - 1].date.hour);
    Write_Char_LCD(':');
    Print_Number(date_a[alarm_num - 1].date.minute);
    Write_Char_LCD(':');
    Print_Number(date_a[alarm_num - 1].date.second);
    
    Go_To_XY_LCD(1,0);
  
    switch(date_a[alarm_num - 1].mode)
    {
    case MODE_1_TIME:
      Write_String_LCD(" 1 Time ");
      break;
    case MODE_EVERYDAY:
      Write_String_LCD("Everyday ");
      break;
    }
      
    switch(date_a[alarm_num - 1].status)
    {
    case 1:
      Write_String_LCD(" ON");
      break;
    case 0:
      Write_String_LCD("OFF");
      break;
    }
    
    switch(date_a[alarm_num - 1].port)
    {
    case PTC1:
      Write_String_LCD(" C1");
      break;
    case PTC2:
      Write_String_LCD(" C2");
      break;
    case PTB3:
      Write_String_LCD(" B3");
      break;
    case PTB2:
      Write_String_LCD(" B2");
      break;
    case PTB1:
      Write_String_LCD(" B1");
      break;
    case PTB0:
      Write_String_LCD(" B0");
      break;
    case PTB30:
      Write_String_LCD(" B30");
      break;
    case PTB20:
      Write_String_LCD(" B20");
      break;
    case PTE23:
      Write_String_LCD(" E23");
      break;
    case PTE22:
      Write_String_LCD(" E22");
      break;
    case PTE21:
      Write_String_LCD(" E21");
      break;
    case PTE20:
      Write_String_LCD(" E20");
      break;
    default:
      break;      
    }
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == ESC)
    {
      goto PORT_1;
    }
    else if(check_KeyPad == ENTER)
    {
      break;
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    DELAY_DISPLAY;
  }
}

void check_alarm_time(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{
  RTC_GetDatetime(&date);
  for(int i = 0; i<=11; i++)
  {
    if(date_a[i].date.hour == date.hour && date_a[i].date.minute == date.minute && date_a[i].date.second == date.second && date_a[i].status == 1)
    {
      if(date_a[i].mode == MODE_1_TIME)
      {
        date_a[i].status = 0;
      }
      switch(date_a[i].port)
      {
      case PTC1:
        GPIOC->PTOR |= 1 << 1;
        break;
      case PTC2:
        GPIOC->PTOR |= 1 << 2;
        break; 
      case PTB3:
        GPIOB->PTOR |= 1 << 3;
        break;
      case PTB2:
        GPIOB->PTOR |= 1 << 2;
        break;
      case PTB1:
        GPIOB->PTOR |= 1 << 1;
        break;
      case PTB0:
        GPIOB->PTOR |= 1 << 0;
        break;
      case PTB30:
        GPIOB->PTOR |= 1 << 30;
        break;
      case PTB20:
        GPIOB->PTOR |= 1 << 20;
        break;
      case PTE23:
        GPIOE->PTOR |= 1 << 23;
        break;
      case PTE22:
        GPIOE->PTOR |= 1 << 22;
        break;
      case PTE21:
        GPIOE->PTOR |= 1 << 21;
        break;
      case PTE20:
        GPIOE->PTOR |= 1 << 20;
        break;
      default:
        break;
      }
      HIGH_DELAY;
    }
  }
}

void view_alarm(rtc_datetime_t date, rtc_alarmtime_t *date_a)
{
  uint8_t check_KeyPad, count;
  count = 1;

  while(1)
  {
    Clear_Screen_LCD();  
    Write_String_LCD("ALA ");
    switch(count)
    {
    case 10:
      Write_String_LCD("10");
      break;
    case 11:  
      Write_String_LCD("11");
      break;
    case 12:
      Write_String_LCD("12");
      break;
    default:
      Write_Char_LCD((char)count + '0');
      break;
    }
    Write_String_LCD(": ");
    if(date_a[count - 1].status == 2 && date_a[count - 1].port == 2 && date_a[count - 1].mode == 2)
    {
      Write_String_LCD(" NO DATA");
    }
    else
    {
      Print_Number(date_a[count - 1].date.hour);
      Write_Char_LCD(':');
      Print_Number(date_a[count - 1].date.minute);
      Write_Char_LCD(':');
      Print_Number(date_a[count - 1].date.second);

      Go_To_XY_LCD(1,0);
  
      switch(date_a[count - 1].mode)
      {
      case MODE_1_TIME:
        Write_String_LCD(" 1 Time ");
        break;
      case MODE_EVERYDAY:
        Write_String_LCD("Everyday ");
        break;
      }
      
      switch(date_a[count - 1].status)
      {
      case 1:
        Write_String_LCD(" ON");
        break;
      case 0:
        Write_String_LCD("OFF");
        break;
      }
    
      switch(date_a[count - 1].port)
      {
      case PTC1:
        Write_String_LCD(" C1");
        break;
      case PTC2:
        Write_String_LCD(" C2");
        break;
      case PTB3:
        Write_String_LCD(" B3");
        break;
      case PTB2:
        Write_String_LCD(" B2");
        break;
      case PTB1:
        Write_String_LCD(" B1");
        break;
      case PTB0:
        Write_String_LCD(" B0");
        break;
      case PTB30:
        Write_String_LCD(" B30");
        break;
      case PTB20:
        Write_String_LCD(" B20");
        break;
      case PTE23:
        Write_String_LCD(" E23");
        break;
      case PTE22:
        Write_String_LCD(" E22");
        break;
      case PTE21:
        Write_String_LCD(" E21");
        break;
      case PTE20:
        Write_String_LCD(" E20");
        break;
      default:
        break;   
      }
    }
    
    check_KeyPad = 0;
    check_Key_Pad(&check_KeyPad);
    if(check_KeyPad == LEFT_BUTTON)
    {
      count--;
      if(count < 1)
      {
        count++;
      }
    }
    else if(check_KeyPad == RIGHT_BUTTON)
    {
      count++;
      if(count > 12)
      {
        count--;
      }
    }
    else if(check_KeyPad == RETURN_HOME_SCREEN)
    {
      home_screen(date, date_a);
    }
    else if(check_KeyPad == ESC)
    {
      alarm_time(date, date_a);
    }
    DELAY_DISPLAY;
  }  
}
//***************************************//