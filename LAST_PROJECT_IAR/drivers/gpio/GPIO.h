#include <MKL46Z4.h>

/**********GPIO.h***********/

void set_up_GPIO(char GPIO_Type, uint8_t GPIO_Num);             //Cau hinh cho cac PORT tren board
void reset_GPIO();                                              //Reset hoan toan cac che do cua GPIO cua tat ca cac PORT
void set_up_GPIO_input(char GPIO_Type, uint8_t GPIO_Num);       //Cau hinh cho cac PORT tren board duoi dang INPUT

/***************************/


