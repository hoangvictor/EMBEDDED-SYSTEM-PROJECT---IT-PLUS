#include "GPIO.h"

/*************LCD.h**************/

//Cac define la cac du lieu gui cho LCD xu li
#define FUNCTION    0x38
#define CONTROL     0x0c
#define CLRSCR      0x01
#define RETHOME     0x03
#define ENTRYMODE   0x06

//Cac define la cac lenh bat hoac tat cac chan cua LCD
#define LCD_RS_0 GPIOD->PCOR |= (1<<6)
#define LCD_RS_1 GPIOD->PSOR |= (1<<6)
#define LCD_RW_0 GPIOD->PCOR |= (1<<4)
#define LCD_RW_1 GPIOD->PSOR |= (1<<4)
#define LCD_EN_0 GPIOD->PCOR |= (1<<2)
#define LCD_EN_1 GPIOD->PSOR |= (1<<2)

void GPIO_Init_LCD();                                           //Cau hinh cho cac chan tren PORT tuong ung voi cac chan cua LCD
void Delay_LCD(unsigned int t);                                 //Thoi gian cho de thuc hien lenh       
void Wait_Busy_LCD();                                           //Cho cho den khi LCD xu li xong mot lenh
void LCD_send(char cmd);                                        //Gui du lieu vao LCD
void Write_Cmd_LCD(unsigned char byte);                         //Gui lenh vao LCD
void Function_Set_LCD(uint8_t DL, uint8_t N, uint8_t F);        //Cai dat chuc nang tren LCD
void Entry_Mode_LCD(uint8_t ID, uint8_t SH);                    //Cai dat che do nhap LCD
void Display_Control_LCD(uint8_t D, uint8_t C, uint8_t B);      //Cai dat hien thi LCD
void Setup_LCD();                                               //Cau hinh cho LCD hoat dong
void Write_Char_LCD(unsigned char ch);                          //Viet va hien thi mot ki tu kieu char
void Write_String_LCD(char *str);                               //Viet va hien thi mot ki tu dang chuoi
void Print_Number(uint16_t num);                                //Viet va hien thi mot so
void GoHome();                                                  //Di chuyen con tro ve vi tri ban dau
void Go_To_XY_LCD(unsigned char row, unsigned char col);        //Dich chuyen con tro toi vi tri can thiet tren man hinh LCD
void Clear_Screen_LCD();                                        //Xoa man hinh LCD

/*******************************/