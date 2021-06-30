#include "GPIO.h"
#include "LCD.h"

/***********Key_Pad.h************/
//Key Pad 4x5. LINK: https://www.instructables.com/id/Arduino-4x5-Matrix-Keypad-Example-Code-and-Schemat/

//Lenh cho
#define DELAY for(int i = 0; i <= 1250000; i++)

//Cac define la cac cot 
#define Col1 (1<<18)  //Col 1
#define Col2 (1<<19)  //Col 2
#define Col3 (1<<0)   //Col 3
#define Col4 (1<<16)  //Col 4

//Cac define la cac hang
#define Row1 (1<<6)   //Row 1
#define Row2 (1<<7)   //Row 2
#define Row3 (1<<10)  //Row 3
#define Row4 (1<<11)  //Row 4
#define Row5 (1<<13)  //Row 5
  
//Cac define bat,tat cac cot 
#define Col1_ENABLE   GPIOB->PSOR |= Col1
#define Col1_DISABLE  GPIOB->PCOR |= Col1
#define Col2_ENABLE   GPIOB->PSOR |= Col2
#define Col2_DISABLE  GPIOB->PCOR |= Col2
#define Col3_ENABLE   GPIOC->PSOR |= Col3
#define Col3_DISABLE  GPIOC->PCOR |= Col3
#define Col4_ENABLE   GPIOC->PSOR |= Col4
#define Col4_DISABLE  GPIOC->PCOR |= Col4

//Cac define la ten cac nut tren KeyPad
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define ZERO 10
#define ESC 11
#define RETURN_HOME_SCREEN 12
#define ENTER 13
#define UP_BUTTON 14
#define DOWN_BUTTON 15
#define LEFT_BUTTON 16
#define RIGHT_BUTTON 17
#define F1 18
#define F2 19

void set_up_Key_Pad();                      //Cau hinh hoat dong cho KeyPad
void check_Key_Pad(uint8_t *check);         //Kiem tra cac nut bam tren KeyPad
void num_check_Key_Pad(uint8_t *num);        //Kiem tra cac nut bam la so tren KeyPad

/*******************************/