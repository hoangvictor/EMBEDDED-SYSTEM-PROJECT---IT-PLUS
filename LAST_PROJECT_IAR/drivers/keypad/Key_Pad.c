#include "Key_Pad.h"
void set_up_Key_Pad()
{
  set_up_GPIO('B', 18);                //C1 - Pin 1
  set_up_GPIO('B', 19);                //C2 - Pin 2
  set_up_GPIO('C', 0);                 //C3 - Pin 3
  set_up_GPIO('C', 16);                //C4 - Pin 4
  set_up_GPIO('C', 6);                 //R1 - Pin 5
  set_up_GPIO('C', 7);                 //R2 - Pin 6
  set_up_GPIO('C', 10);                //R3 - Pin 7
  set_up_GPIO('C', 11);                //R4 - Pin 8
  set_up_GPIO('C', 13);                //R5 - Pin 9
  
  //XUAT TIN HIEU THAP CHO CAC CHAN C1,C2,C3,C4
  GPIOB->PDDR |= Col1 | Col2; 
  GPIOC->PDDR |= Col3 | Col4;
  
  GPIOB->PCOR |= Col1 | Col2; 
  GPIOC->PCOR |= Col3 | Col4;
  
  //CAC CHAN R1,R2,R3,R4,R5 DOC TIN HIEU NHAN DUOC TU CAC CHAN C1,C2,C3,C4
  set_up_GPIO_input('C', 6);
  set_up_GPIO_input('C', 7);
  set_up_GPIO_input('C', 10);
  set_up_GPIO_input('C', 11); 
  set_up_GPIO_input('C', 13); 
}

void check_Key_Pad(uint8_t *check)
{
  //C1 xuat tin hieu cao, cac chan C con lai xuat tin hieu thap
  GPIOB->PSOR |= Col1;  
  if(((GPIOC->PDIR) & Row1) == Row1)
  {    
    *check = LEFT_BUTTON;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row2) == Row2)
  {
    *check = SEVEN;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row3) == Row3)
  {
    *check = FOUR;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row4) == Row4)
  {
    *check = ONE;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row5) == Row5)
  {    
    *check = F1;
    DELAY;
    goto END;
  }
  GPIOB->PCOR |= Col1;
  
  //C2 xuat tin hieu cao, cac chan C con lai xuat tin hieu thap
  GPIOB->PSOR |= Col2;  
  if(((GPIOC->PDIR) & Row1) == Row1)
  {
    *check = ZERO;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row2) == Row2)
  {
    *check = EIGHT;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row3) == Row3)
  {
    *check = FIVE;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row4) == Row4)
  {    
    *check = TWO;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row5) == Row5)
  {    
    *check = F2;
    DELAY;
    goto END;
  }
  GPIOB->PCOR |= Col2;
  
  //C3 xuat tin hieu cao, cac chan C con lai xuat tin hieu thap
  GPIOC->PSOR |= Col3;  
  if(((GPIOC->PDIR) & Row1) == Row1)
  {
    *check = RIGHT_BUTTON;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row2) == Row2)
  {
    *check = NINE;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row3) == Row3)
  {
    *check = SIX;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row4) == Row4)
  {
    *check = THREE;
    DELAY;
    goto END;
  }
  GPIOC->PCOR |= Col3;
      
  //C4 xuat tin hieu cao, cac chan C con lai xuat tin hieu thap
  GPIOC->PSOR |= Col4;  
  if(((GPIOC->PDIR) & Row1) == Row1)
  {
    *check = ENTER;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row2) == Row2)
  {
    *check = ESC;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row3) == Row3)
  {
    *check = DOWN_BUTTON;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row4) == Row4)
  {
    *check = UP_BUTTON;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row5) == Row5)
  {
    *check = RETURN_HOME_SCREEN;
    DELAY;
    goto END;
  }
  GPIOC->PCOR |= Col4;
  
END:
}

void num_check_Key_Pad(uint8_t *num)
{
  //C1 xuat tin hieu cao, cac chan C con lai xuat tin hieu thap
  Col1_ENABLE; 
  if(((GPIOC->PDIR) & Row2) == Row2)
  {
    *num = 7;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row3) == Row3)
  {
    *num = 4;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row4) == Row4)
  {
    *num = 1;
    DELAY;
    goto END;
  }
  Col1_DISABLE;
  
  //C2 xuat tin hieu cao, cac chan C con lai xuat tin hieu thap
  Col2_ENABLE;  
  if(((GPIOC->PDIR) & Row1) == Row1)
  {
    *num = 0;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row2) == Row2)
  {
    *num = 8;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row3) == Row3)
  {
    *num = 5;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row4) == Row4)
  {    
    *num = 2;
    DELAY;
    goto END;
  }
  Col2_DISABLE;
  
  //C3 xuat tin hieu cao, cac chan C con lai xuat tin hieu thap
  Col3_ENABLE;  
  if(((GPIOC->PDIR) & Row2) == Row2)
  {
    *num = 9;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row3) == Row3)
  {
    *num = 6;
    DELAY;
    goto END;
  }
  else if(((GPIOC->PDIR) & Row4) == Row4)
  {
    *num = 3;
    DELAY;
    goto END;
  }
  Col3_DISABLE;
  
END:
}