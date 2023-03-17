#ifndef APP_H_
#define APP_H_

#include <string.h>
#include "Timer0.h"



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/



// The three application modes
typedef enum
{
  INIT,CALC,TIMER,STOPWATCH
}STATE;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/



/*
 * Calculator function for the calcuator mode
 */
void Calc(void);
/*
 * Timer function for the Timer mode
 */
void Timer(void);
/*
 * Stopwatch function for the Stopwatch mode
 */
void Stopwatch(void);




#endif