#include "RTC_KL46.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_ConvertSecsToDatetime
 * Description   : converts time data from seconds to a datetime structure.
 * This function will convert time data from seconds to a datetime structure.
 *
 *END**************************************************************************/

void init_rtc(rtc_datetime_t *date)
{
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
    RTC->SR &= ~RTC_SR_TCE_MASK;
    SIM->SOPT1 &= ~SIM_SOPT1_OSC32KSEL_MASK; // RTC clock in is LPO
    SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(3);
    RTC_SetDatetime(date);
    RTC->SR |= RTC_SR_TCE_MASK;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_ConvertSecsToDatetime
 * Description   : converts time data from seconds to a datetime structure.
 * This function will convert time data from seconds to a datetime structure.
 *
 *END**************************************************************************/
void RTC_ConvertSecsToDatetime(const uint32_t * seconds, rtc_datetime_t * datetime)
{
    uint32_t x;
    uint32_t Seconds, Days, Days_in_year;
    const uint8_t *Days_in_month;

    /* Start from 1970-01-01*/
    Seconds = *seconds;
    /* days, we add 1 for the current day which is represented in the hours and seconds field */
    Days = Seconds / SECONDS_IN_A_DAY + 1;
    /* seconds left*/
    Seconds = Seconds % SECONDS_IN_A_DAY;
    /* hours*/
    datetime->hour = Seconds / SECONDS_IN_A_HOUR;
    /* seconds left*/
    Seconds = Seconds % SECONDS_IN_A_HOUR;
    /* minutes*/
    datetime->minute = Seconds / SECONDS_IN_A_MIN;
    /* seconds*/
    datetime->second = Seconds % SECONDS_IN_A_MIN;
    /* year*/
    datetime->year = YEAR_RANGE_START;
    Days_in_year = DAYS_IN_A_YEAR;

    while (Days > Days_in_year)
    {
        Days -= Days_in_year;
        datetime->year++;
        if  (datetime->year & 3U)
        {
            Days_in_year = DAYS_IN_A_YEAR;
        }
        else
        {
            Days_in_year = DAYS_IN_A_LEAP_YEAR;
        }
    }

    if (datetime->year & 3U)
    {
        Days_in_month = ULY;
    }
    else
    {
        Days_in_month = LY;
    }

    for (x = 1U; x <= 12U; x++)
    {
        if (Days <= (*(Days_in_month + x)))
        {
            datetime->month = x;
            break;
        }
        else
        {
            Days -= (*(Days_in_month + x));
        }
    }

    datetime->day = Days;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_IsDatetimeCorrectFormat
 * Description   : checks if the datetime is in correct format.
 * This function will check if the given datetime is in the correct format.
 *
 *END**************************************************************************/
int RTC_IsDatetimeCorrectFormat(const rtc_datetime_t * datetime)
{
    int result = 0;

    /* Test correctness of given parameters*/
    if ((datetime->year < YEAR_RANGE_START) || (datetime->year > YEAR_RANGE_END) ||
        (datetime->month > 12U) || (datetime->month < 1U) ||
        (datetime->day > 31U) || (datetime->day < 1U) ||
        (datetime->hour >= HOURS_IN_A_DAY) || (datetime->minute >= MINS_IN_A_HOUR) ||
        (datetime->second >= SECONDS_IN_A_MIN))
    {
        /* If not correct then error*/
        result = 0;
    }
    else
    {
        result = 1;
    }

    /* Is given year un-leap-one?*/
    /* Leap year calculation only looks for years divisible by 4 as acceptable years is limited */
    if ( result && (datetime->year & 3U))
    {
        /* Does the obtained number of days exceed number of days in the appropriate month & year?*/
        if (ULY[datetime->month] < datetime->day)
        {
            /* If yes (incorrect datetime inserted) then error*/
            result = 0;
        }
    }
    else /* Is given year leap-one?*/
    {
        /* Does the obtained number of days exceed number of days in the appropriate month & year?*/
        if (result && (LY[datetime->month] < datetime->day))
        {
            /* if yes (incorrect date inserted) then error*/
            result = 1;
        }
    }

    return 1;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_ConvertDatetimeToSecs
 * Description   : converts time data from datetime to seconds.
 * This function will convert time data from datetime to seconds.
 *
 *END**************************************************************************/
void RTC_ConvertDatetimeToSecs(const rtc_datetime_t * datetime, uint32_t * seconds)
{
    /* Compute number of days from 1970 till given year*/
    *seconds = (datetime->year - 1970U) * DAYS_IN_A_YEAR;
    /* Add leap year days */
    *seconds += ((datetime->year / 4) - (1970U / 4));
    /* Add number of days till given month*/
    *seconds += MONTH_DAYS[datetime->month];
    /* Add days in given month. We take away seconds for the current day as it is
     * represented in the hours and seconds field*/
    *seconds += (datetime->day - 1);
    /* For leap year if month less than or equal to Febraury, decrement day counter*/
    if ((!(datetime->year & 3U)) && (datetime->month <= 2U))
    {
        (*seconds)--;
    }

    *seconds = ((*seconds) * SECONDS_IN_A_DAY) + (datetime->hour * SECONDS_IN_A_HOUR) +
               (datetime->minute * SECONDS_IN_A_MIN) + datetime->second;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_SetDatetime
 * Description   : Sets the RTC date and time according to the given time struct.
 * This function will set the RTC date and time according to the given time
 * struct, if start_after_set is true, the RTC oscillator will be enabled and
 * the counter will start.
 *
 *END**************************************************************************/
int RTC_SetDatetime(rtc_datetime_t *datetime)
{
    uint32_t srcClock = 1000U;
    uint32_t seconds = 0;
    uint16_t preScaler = 0;
    uint64_t tmp = 0;

    /* Return error if the time provided is not valid */
    if (!(RTC_IsDatetimeCorrectFormat(datetime)))
    {
        return 0;
    }

    RTC_ConvertDatetimeToSecs(datetime, &seconds);

    /* As the seconds register will not increment every second, we need to adjust the value
     * programmed to the seconds register */
    tmp = (uint64_t)seconds * (uint64_t)srcClock;
    preScaler = (uint32_t)(tmp & 0x7FFFU);
    seconds = (uint32_t)(tmp >> 15U);
    
    /* Set time in seconds */
    RTC->SR &= ~RTC_SR_TCE_MASK;
    /* Set seconds counter*/
    RTC->TSR = seconds;
    /* Set time counter*/
    RTC->TPR = preScaler;
     /* Enable the counter*/
    RTC->SR |= RTC_SR_TCE_MASK;
    
    return 1;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_GetDatetime
 * Description   : Gets the actual RTC time and stores it in the given time struct.
 * This function will get the actual RTC time and stores it in the given time
 * struct.
 *
 *END**************************************************************************/
void RTC_GetDatetime(rtc_datetime_t *datetime)
{
    uint32_t seconds = 0;
    uint32_t srcClock = 1000U;
    uint32_t prescaler = 0;
    uint64_t tmp = 0;

    seconds = RTC->TSR;
    prescaler = RTC->TPR;

    tmp = (uint64_t)seconds << 15U;
    tmp |= (uint64_t)(prescaler & 0x7FFFU);
    seconds = tmp / srcClock;
    RTC_ConvertSecsToDatetime(&seconds, datetime);

}
/*******************************************************************************
 * EOF
 ******************************************************************************/

void clear_time_RTC()
{
  RTC->TSR = 0;
}

void time_alarm_RTC(uint32_t time_alarm)
{
  RTC->TAR = time_alarm;
}

void RTC_TCR(uint8_t num_CIC, uint8_t num_TCV, uint8_t num_CIR, uint8_t num_TCR)
{
  RTC->TCR &= ~RTC_TCR_TCR_MASK;
  RTC->TCR |= RTC_TCR_TCR(num_TCR);
  
  RTC->TCR &= ~RTC_TCR_CIR_MASK;
  RTC->TCR |= RTC_TCR_CIR(num_CIR);
  
  RTC->TCR &= ~RTC_TCR_TCV_MASK;
  RTC->TCR |= RTC_TCR_TCV(num_TCV);
  
  RTC->TCR &= ~RTC_TCR_CIC_MASK;
  RTC->TCR |= RTC_TCR_CIC(num_CIC); 
}

void control_pF_RTC(uint8_t pF)
{
  switch(pF)
  {
  case 2:
    RTC->CR |= RTC_CR_SC2P_MASK;
    RTC->CR &= (~RTC_CR_SC4P_MASK) & (~RTC_CR_SC8P_MASK) & (~RTC_CR_SC16P_MASK);
    break;
  case 4:
    RTC->CR |= RTC_CR_SC4P_MASK;
    RTC->CR &= (~RTC_CR_SC2P_MASK) & (~RTC_CR_SC8P_MASK) & (~RTC_CR_SC16P_MASK);
    break;
  case 8:
    RTC->CR |= RTC_CR_SC8P_MASK;
    RTC->CR &= (~RTC_CR_SC2P_MASK) & (~RTC_CR_SC4P_MASK) & (~RTC_CR_SC16P_MASK);
    break;
  case 16:
    RTC->CR |= RTC_CR_SC16P_MASK;
    RTC->CR &= (~RTC_CR_SC2P_MASK) & (~RTC_CR_SC4P_MASK) & (~RTC_CR_SC8P_MASK);
    break;
  default:
    break;
  }
}

void control_CLKO_RTC(uint8_t CLKO)
{
  if(CLKO == 1)
  {
    RTC->CR |= RTC_CR_CLKO_MASK;
  }
  else
  {
    RTC->CR &= ~RTC_CR_CLKO_MASK;  
  }
}

void control_OSCE(uint8_t OSCE)
{
  if(OSCE == 1)
  {
    RTC->CR |= RTC_CR_OSCE_MASK;
    for(int i = 0; i <= 100000; i++);
  }
  else
  {
    RTC->CR &= ~RTC_CR_OSCE_MASK;
  }
}

void control_WPS_RTC(uint8_t WPS)
{
  if(WPS == 1)
  {
    RTC->CR |= RTC_CR_WPS_MASK;
  }
  else
  {
    RTC->CR &= ~RTC_CR_WPS_MASK;
  }
}

void control_UM_RTC(uint8_t UM)
{
  if(UM == 1)
  {
    RTC->CR |= RTC_CR_UM_MASK;
  }
  else
  {
    RTC->CR &= ~RTC_CR_UM_MASK;
  }
}

void control_SUP(uint8_t SUP)
{
  if(SUP == 1)
  {
    RTC->CR |= RTC_CR_SUP_MASK;
  }
  else
  {
    RTC->CR &= ~RTC_CR_SUP_MASK;
  }
}

void control_WPE_RTC(uint8_t WPE) 
{
  if(WPE == 1)
  {
    RTC->CR |= RTC_CR_WPE_MASK;
  }
  else
  {
    RTC->CR &= ~RTC_CR_WPE_MASK;
  }
}

void control_SWR_RTC(uint8_t SWR)
{
  if(SWR == 1)
  {
    RTC->CR |= RTC_CR_SWR_MASK;
  }
  else
  {
    RTC->CR &= ~RTC_CR_SWR_MASK;
  }
}

void clear_registers_RTC()
{
  control_SWR_RTC(1);
}

void enable_RTC(uint8_t enable)
{
  if(enable == 1)
  {
    RTC->SR |= RTC_SR_TCE_MASK;
  }
  else
  {
    RTC->SR &= ~RTC_SR_TCE_MASK;
  }
}

void lock_RTC(uint8_t LRL, uint8_t SRL, uint8_t CRL, uint8_t TCL)
{
  ///////////////////////
  if(LRL == 1)
  {
    RTC->LR |= RTC_LR_LRL_MASK;
  }
  else
  {
    RTC->LR &= ~RTC_LR_LRL_MASK;
  }

  ///////////////////////
  if(SRL == 1)
  {
    RTC->LR |= RTC_LR_SRL_MASK;
  }
  else
  {
    RTC->LR &= ~RTC_LR_SRL_MASK;
  }

  ///////////////////////
  if(CRL == 1)
  {
    RTC->LR |= RTC_LR_CRL_MASK;
  }
  else
  {
    RTC->LR &= ~RTC_LR_CRL_MASK;
  }
  
  ///////////////////////
  if(TCL == 1)
  {
    RTC->LR |= RTC_LR_TCL_MASK;
  }
  else
  {
    RTC->LR &= ~RTC_LR_TCL_MASK;
  }
}

void interrupt_RTC(uint8_t WPON, uint8_t TSIE, uint8_t TAIE, uint8_t TOIE, uint8_t TIIE)
{
  ///////////////////////
  if(WPON == 1)
  {
    RTC->IER |= RTC_IER_WPON_MASK;
  }
  else
  {
    RTC->IER &= ~RTC_IER_WPON_MASK;
  }

  ///////////////////////
  if(TSIE == 1)
  {
    RTC->IER |= RTC_IER_TSIE_MASK;
  }
  else
  {
    RTC->IER &= ~RTC_IER_TSIE_MASK;
  }
  
  ///////////////////////
  if(TAIE == 1)
  {
    RTC->IER |= RTC_IER_TAIE_MASK;
  }
  else
  {
    RTC->IER &= ~RTC_IER_TAIE_MASK;
  }

  ///////////////////////
  if(TOIE == 1)
  {
    RTC->IER |= RTC_IER_TOIE_MASK;
  }
  else
  {
    RTC->IER &= ~RTC_IER_TOIE_MASK;
  }
  
  ///////////////////////
  if(TIIE == 1)
  {
    RTC->IER |= RTC_IER_TIIE_MASK;
  }
  else
  {
    RTC->IER &= ~RTC_IER_TIIE_MASK;
  }
}

uint8_t check_time_alarm_RTC()
{
  if(((RTC->SR) & RTC_SR_TAF_MASK) != 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
