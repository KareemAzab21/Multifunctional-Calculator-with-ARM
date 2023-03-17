#ifndef TIMER0_H_
#define TIMER0_H_








/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/





/*
 * Description: Initialize the timer0 and enable it interrupt
 */
void Timer0_Init(void);




/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void));

#endif