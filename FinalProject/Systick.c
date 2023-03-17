#include "SysTick.h"
#include "DIO.h"
#include <stdio.h>
#include "tm4c123gh6pm.h"




void SysTick_Disable()
{
  NVIC_ST_CTRL_R  = 0;
}




void SysTick_Enable()
{
  NVIC_ST_CTRL_R |= 0x07;
}


uint32 SysTickPeriodGet()
{

  return NVIC_ST_RELOAD_R;
  
}

void SysTickPeriodSet(uint32 Period)
{
  NVIC_ST_RELOAD_R  = (((float)(Period)/1000) * 16000000)-1;
  
}


uint32 SysTickValueGet()
{
  return NVIC_ST_CURRENT_R;
}


Bool SysTick_Is_Time_out()
{
 
  if((NVIC_ST_CTRL_R & 0x10000) ==0)
      return FALSE;

  return TRUE;     
}
