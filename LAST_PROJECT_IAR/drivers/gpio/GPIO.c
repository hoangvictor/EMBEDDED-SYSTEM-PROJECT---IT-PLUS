#include "GPIO.h"

void set_up_GPIO(char GPIO_Type, uint8_t GPIO_Num)
{
  switch(GPIO_Type)
  {
  case 'A':
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    PORTA->PCR[GPIO_Num] &= PORT_PCR_MUX_MASK;
    PORTA->PCR[GPIO_Num] |= PORT_PCR_MUX(1);
    PORTA->PCR[GPIO_Num] |= PORT_PCR_SRE_MASK;
    break;
  case 'B':
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    PORTB->PCR[GPIO_Num] &= PORT_PCR_MUX_MASK;
    PORTB->PCR[GPIO_Num] |= PORT_PCR_MUX(1);
    PORTB->PCR[GPIO_Num] |= PORT_PCR_SRE_MASK;
    break;
  case 'C':
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    PORTC->PCR[GPIO_Num] &= PORT_PCR_MUX_MASK;
    PORTC->PCR[GPIO_Num] |= PORT_PCR_MUX(1);
    PORTC->PCR[GPIO_Num] |= PORT_PCR_SRE_MASK;
    break;
  case 'D':
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
    PORTD->PCR[GPIO_Num] &= PORT_PCR_MUX_MASK;
    PORTD->PCR[GPIO_Num] |= PORT_PCR_MUX(1);
    PORTD->PCR[GPIO_Num] |= PORT_PCR_SRE_MASK;
    break;
  case 'E':
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
    PORTE->PCR[GPIO_Num] &= PORT_PCR_MUX_MASK;
    PORTE->PCR[GPIO_Num] |= PORT_PCR_MUX(1);
    PORTE->PCR[GPIO_Num] |= PORT_PCR_SRE_MASK;
    break;
  default:
    break; 
  }
}

void reset_GPIO()
{
  GPIOA -> PDDR &= ~GPIO_PDDR_PDD_MASK;
  GPIOB -> PDDR &= ~GPIO_PDDR_PDD_MASK;
  GPIOC -> PDDR &= ~GPIO_PDDR_PDD_MASK;
  GPIOD -> PDDR &= ~GPIO_PDDR_PDD_MASK;
  GPIOE -> PDDR &= ~GPIO_PDDR_PDD_MASK;
}

void set_up_GPIO_input(char GPIO_Type, uint8_t GPIO_Num)
{
  switch(GPIO_Type)
  {
  case 'A':
    PORTA->PCR[GPIO_Num] |= PORT_PCR_PE_MASK;
    PORTA->PCR[GPIO_Num] &= ~PORT_PCR_PS_MASK;
    break;
  case 'B':
    PORTB->PCR[GPIO_Num] |= PORT_PCR_PE_MASK;
    PORTB->PCR[GPIO_Num] &= ~PORT_PCR_PS_MASK;
    break;
  case 'C':
    PORTC->PCR[GPIO_Num] |= PORT_PCR_PE_MASK;
    PORTC->PCR[GPIO_Num] &= ~PORT_PCR_PS_MASK;
    break;
  case 'D':
    PORTD->PCR[GPIO_Num] |= PORT_PCR_PE_MASK;
    PORTD->PCR[GPIO_Num] &= ~PORT_PCR_PS_MASK;
    break;
  case 'E':
    PORTE->PCR[GPIO_Num] |= PORT_PCR_PE_MASK;
    PORTE->PCR[GPIO_Num] &= ~PORT_PCR_PS_MASK;
    break;
  default:
    break; 
  }
}