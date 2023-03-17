#include "Timer0.h"
#include "types.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"




/* Global variables to hold the address of the call back function in the application */
static  void (*g_callBackPtr)(void) = NULL_PTR;

void
Timer0IntHandler(void)
{
   TimerIntClear(TIMER0_BASE,TIMER_BOTH); /* Clear the flag Interrupt for Timer0*/
    if (g_callBackPtr!=NULL_PTR)
    {
	(*g_callBackPtr)();
    }
}





// initiallize the Timer0 with Tivaware Libraries and Enable the interrupt of the Timer
void Timer0_Init()
{
   //configure the Timer0
   SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
   TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
   TimerLoadSet(TIMER0_BASE, TIMER_A, 16000000-1);
   
   
   //Enable the interrupt for Timer0
   IntRegister(INT_TIMER0A,Timer0IntHandler);
   TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
   TimerEnable(TIMER0_BASE,TIMER_BOTH);
   IntEnable(INT_TIMER0A);
   
  
   
  
}





void Timer0_setCallBack(void(*a_ptr)(void))
{
  /* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
