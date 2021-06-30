#include "LCD.h"

void GPIO_Init_LCD()
{
    set_up_GPIO('A' ,1);
    set_up_GPIO('A' ,2);
    set_up_GPIO('D' ,3);
    set_up_GPIO('A' ,12);
    set_up_GPIO('A' ,5);
    set_up_GPIO('C' ,8);
    set_up_GPIO('C' ,9);
    set_up_GPIO('A' ,13);
    set_up_GPIO('D' ,2);
    set_up_GPIO('D' ,4);
    set_up_GPIO('D' ,6);
    
    GPIOC->PDDR |= (1<<8) | (1<<9);
    GPIOA->PDDR |= (1<<1) | (1<<2) | (1<<5)| (1<<12)| (1<<13);
    GPIOD->PDDR |= (1<<2) | (1<<3) | (1<<4) | (1<<6);
}   
//********************************************************
void Delay_LCD(unsigned int t)
{
      unsigned int x;
      for(x=0; x<t; x++);
}
//********************************************************
void Wait_Busy_LCD()
{
    uint32_t nLcdBusy;
    GPIOA->PSOR |= (1<<1);
    LCD_RS_0;
    LCD_RW_1;
    PORTA->PCR[1] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    GPIOA->PDDR &= ~(1<<1);
    while(1)
    {
        LCD_EN_1;
        Delay_LCD(0);
        nLcdBusy = (GPIOA->PDIR) & (1<<1);//(PortData & 0x80);
        LCD_EN_0;
        Delay_LCD(0);
        if(nLcdBusy == 0)
        {
          break;
        }
    }
    PORTA->PCR[1] &= ~(PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
    GPIOA->PDDR |= (1<<1);
}
//********************************************************
void LCD_send(char cmd)
{
    if ((cmd & 0x80) != 0)
    {
        GPIOA->PSOR |= (1<<1);
    }
    else
    {
        GPIOA->PCOR |= (1<<1);
    }
    
    if ((cmd & 0x40) != 0)
    {
        GPIOA->PSOR |= (1<<2);
    }
    else
    {
        GPIOA->PCOR |= (1<<2);
    }
    
    if ((cmd & 0x20) != 0)
    {
        GPIOD->PSOR |= (1<<3);
    }
    else
    {
        GPIOD->PCOR |= (1<<3);
    }
    
    if ((cmd & 0x10) != 0)
    {
        GPIOA->PSOR |= (1<<12);
    }
    else
    {
        GPIOA->PCOR |= (1<<12);
    }
    
    if ((cmd & 0x08) != 0)
    {
        GPIOA->PSOR |= (1<<5);
    }
    else
    {
        GPIOA->PCOR |= (1<<5);
    }
    
    if ((cmd & 0x04) != 0)
    {
        GPIOC->PSOR |= (1<<8);
    }
    else
    {
        GPIOC->PCOR |= (1<<8);
    }
    
    if ((cmd & 0x02) != 0)
    {
        GPIOC->PSOR |= (1<<9);
    }
    else
    {
        GPIOC->PCOR |= (1<<9);
    }
    
    if ((cmd & 0x01) != 0)
    {
        GPIOA->PSOR |= (1<<13);
    }
    else
    {
        GPIOA->PCOR |= (1<<13);
    }
}
//********************************************************
void Write_Cmd_LCD(unsigned char byte)
{
    Wait_Busy_LCD();
    LCD_RS_0;
    LCD_RW_0;
    Delay_LCD(0);
    LCD_send(byte);
    LCD_EN_1;
    Delay_LCD(0);
    LCD_EN_0;
}
//********************************************************
void Function_Set_LCD(uint8_t DL, uint8_t N, uint8_t F)
{
    unsigned char cmd_function = 0x20;
    
    //BIT MODE
    if(DL == 1)
      {
        cmd_function |= 0x10;
      }
    
    //LINE NUMBER
    if(N == 1)
      {
        cmd_function |= 0x8;
      }
    
    //FONT TYPE
    if(F == 1)
      {
        cmd_function |= 0x4;
      }
    
    Write_Cmd_LCD(cmd_function);
}
//********************************************************
void Entry_Mode_LCD(uint8_t ID, uint8_t SH)
{
    unsigned char cmd_entry = 0x04;
    
    //Increment or decrement of DDRAM address (cursor or blink)
    if(ID == 1)
      {
        cmd_entry |= 0x02;
      }
    
    //Shift of entire display
    if(SH == 1)
      {
        cmd_entry |= 0x01;
      }
    
     Write_Cmd_LCD(cmd_entry);
}
//********************************************************
void Display_Control_LCD(uint8_t D, uint8_t C, uint8_t B)
{
    unsigned char cmd_display = 0x08;
    
    //Display ON / OFF control bit
    if(D == 1)
      {
        cmd_display |= 0x04;
      }
    
    //Cursor ON / OFF control bit
    if(C == 1)
      {
        cmd_display |= 0x02;
      }
    
    //Cursor Blink ON / OFF control bit
    if(B == 1)
      {
        cmd_display |= 0x01;
      }
    
     Write_Cmd_LCD(cmd_display);
}
//********************************************************
void Setup_LCD()
{
    GPIO_Init_LCD();
    Delay_LCD(150);
    Write_Cmd_LCD(0x30);
    Delay_LCD(150);
    Write_Cmd_LCD(0x30);
    Delay_LCD(150);
    Write_Cmd_LCD(0x30);
    Delay_LCD(150);
    LCD_EN_1;
    Delay_LCD(0);
    LCD_EN_0;
    
    //Write_Cmd_LCD(FUNCTION);
    Function_Set_LCD(1,1,1);
    
    //Write_Cmd_LCD(CONTROL);
    Display_Control_LCD(1,0,0);
    
    Write_Cmd_LCD(CLRSCR);
    
    //Write_Cmd_LCD(ENTRYMODE);
    Entry_Mode_LCD(1,0);
}
//********************************************************
void Write_Char_LCD(unsigned char ch)
{
    Wait_Busy_LCD();
    LCD_RS_1;
    LCD_RW_0;
    Delay_LCD(0);
    LCD_send(ch);
    LCD_EN_1;
    Delay_LCD(0);
    LCD_EN_0;
}

/*============================================================*/
void Write_String_LCD(char *str)  //Ghi mot String thay vì chi ghi tung ki tu
{
   unsigned char i = 0;
   while(str[i]!=0)    //Ghi lan luot tung ki tu cua String ra man hinh den khi gap ki tu trang
   {
      Write_Char_LCD(str[i]);
      i++;
   }
}

//********************************************************
void Print_Number(uint16_t num)
{
    char ngan,tram,chuc,donvi;
    if(num >=1000)
    {
      ngan = num/1000;
      Write_Char_LCD(ngan+'0');
    }
    if(num >=100)
    {
      tram = (num%1000)/100;
      Write_Char_LCD(tram+'0');
    }
    chuc = (num%100)/10;
    Write_Char_LCD(chuc+'0');
    donvi = num%10;
    Write_Char_LCD(donvi+'0');
}
//********************************************************
void GoHome()
{
    Write_Cmd_LCD(RETHOME);
    Delay_LCD(100);
}
//********************************************************
void Go_To_XY_LCD(unsigned char row, unsigned char col)
{
    unsigned char ac;
    ac = 0x80;
    ac = ac | ((row & 1) << 6);
    ac = ac | (col & 15);
    Write_Cmd_LCD(ac);
}
//********************************************************
void Clear_Screen_LCD()
{
    Write_Cmd_LCD(CLRSCR);
    Delay_LCD(100);
}


