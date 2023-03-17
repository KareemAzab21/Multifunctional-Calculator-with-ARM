
#include "lcd.h"
#include "DIO.h"
#include "keypad.h"
#include "app.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom_map.h"





extern STATE state;
//the ISR of the switch button
void Switch_Modes()
{
  
  if(GPIOIntStatus(0x40007000,GPIO_INT_PIN_7)==GPIO_INT_PIN_7)
  {
    GPIOIntClear(0x40007000,GPIO_INT_PIN_7);
    switch(state){
    case CALC:
      state=TIMER;
      break;
    case TIMER:
      state = STOPWATCH;
      break;
    case STOPWATCH:  
      state=CALC;
      break;
    }
  }
  
}

int main()
{
  uint8 key;
  KeyPad_Init();
  LCD_init();
  DIO_Init(PORTD,7,IN,PULLDOWN);
  GPIOIntRegister(0x40007000,Switch_Modes);
  GPIOIntTypeSet(0x40007000,GPIO_INT_PIN_7,GPIO_FALLING_EDGE);
  GPIOIntEnable(0x40007000,GPIO_INT_PIN_7);
  IntMasterEnable();
  LCD_displayString("Team 15");
  Delay_MS(3000);
  LCD_clearScreen();
  LCD_displayStringRowColumn(0,0,"Choose Your mode");
  key=KEYPAD_getPressedKey();
  LCD_clearScreen(); 
  switch(key){
  case '1':
    state=CALC;
    
    break;
  case '2':
    state=TIMER;
    
    break;
    case'3':
      state=STOPWATCH;
      
      break;
  }
  
  
  
  while(1)
  {
    switch(state)
    {
    case CALC:
      LCD_clearScreen();
      LCD_displayString("Calc Mode ON");
      Delay_MS(1000);
      
      LCD_clearScreen();
      Calc();
      
      
      break;
    case TIMER:
      Timer();
      break;
    case STOPWATCH:
      Stopwatch();
      break;
    }
  }
}


















