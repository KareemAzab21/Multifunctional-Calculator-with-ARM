#ifndef SysTick_H
#define SysTick_H

#include "types.h"


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
  FALSE,TRUE
}Bool;


/*************************************************************
*                       FUNCTION PROTOTYPES
*
***************************************************************/

void SysTick_Disable(void);

void SysTick_Enable(void);

uint32 SysTickPeriodGet(void);

void SysTickPeriodSet(uint32 Period);

uint32 SysTickValueGet(void);

Bool SysTick_Is_Time_out(void);

#endif