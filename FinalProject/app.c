
#include "app.h"
#include "lcd.h"
#include "keypad.h"
#include "DIO.h"
#include "SysTick.h"

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom_map.h"
#include "tm4c123gh6pm.h"





// state that shows the application in which state
STATE state=INIT;

//global variables of the stopwatch that will be displayed on the LCD
uint8 sec_flag;/* the flag is set when the Systick interrupts */
uint8 seconds_1;
uint8 seconds_2;
uint8 minutes_2;
uint8 minutes_1;
uint8 hours_1 ;
uint8 hours_2 ;


//global variables used in the calculator function
uint32 num;
uint8 op;
uint32 result;
char result1[10];


//global variables of the stopwatch that will be displayed on the LCD
uint8 minTime1;
uint8 minTime2;
uint8 secTime1;
uint8 secTime2;
uint8 time_flag=0; /* the flag is set when the timer interrupts */

//The Timer0 ISR
void Timing()
{
  time_flag=1;
  
  
  
}

//SYSTICK ISR
void SysTick_Handler()
{
  sec_flag=1;
}

//ISR of the three buttons of the stopwatch "PAUSE","Resume" and "Reset"
void PRR()
{
  
  if(GPIOIntStatus(0x40004000,0x04)==0x04)
  {
    GPIOIntClear(0x40004000,0x00000004);
    SysTick_Disable();
  }
  else if(GPIOIntStatus(0x40004000,0x08)==0x08)
  {
    GPIOIntClear(0x40004000,0x00000008);
    SysTick_Enable();
  }
  else if(GPIOIntStatus(0x40004000,0x80)==0x80)
  {
    GPIOIntClear(0x40004000,0x00000080);
    seconds_1=0;
    seconds_2=0;
    minutes_1=0;
    minutes_2=0;
    hours_1=0;
    hours_2=0;
  }
}

void reverse(char s[])
{
  int i, j;
  char c;
  
  for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}


// function the converts an integer to string because The LCD displays String or Character
void itoa(int n, char s[])
{
  int i, sign;
  
  if ((sign = n) < 0)  /* record sign */
    n = -n;          /* make n positive */
  i = 0;
  do {       /* generate digits in reverse order */
    s[i++] = n % 10 + '0';   /* get next digit */
  } while ((n /= 10) > 0);     /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}








void Calc(void)
{
  
  uint32 num1;
  char res[5]="";
  char key='0';
  char testKey[2];
  testKey[0]=key;
  testKey[1]='\0';
  
  key=KEYPAD_getCalcPressedKey();
  if(state != CALC)
  {
    return;
  }
  
  
  //The While Loop to get the number from the user
  while((key>='0') && (key <='9'))
  { 
    testKey[0]=key;
    strcat(res,testKey);
    LCD_displayCharacter(key);
    Delay_MS(400);
    
    
    key=KEYPAD_getCalcPressedKey();
    if(state != CALC)
    {
      return;
    }
    
  }
  num1=atoi(res);
  
  if(key != '=')
  {
    /* The Operator and The first Num is stored in a global variables so 
    * when the calc is called again they are not cleared
    */
    num=num1;
    op=key;
    LCD_displayCharacter(key);
    Delay_MS(400);
    
    //if the key is not = ,it calls calc again to get the second number.
    Calc();
  }
  // The user is now pressed eqaul
  else
  {
    LCD_displayCharacter(key);
    //switch case on the operator to determin which operation is needed
    switch(op)
    {
    case '+':
      result=num+num1;
      itoa(result,result1);
      
      LCD_displayStringRowColumn(1,0,result1);
      Delay_MS(2000);
      break;
    case '-':
      result=num-num1;
      itoa(result,result1);
      LCD_displayStringRowColumn(1,0,result1);
      Delay_MS(2000);
      
      break;
    case '/':
      result=num/num1;
      itoa(result,result1);
      LCD_displayStringRowColumn(1,0,result1);
      Delay_MS(2000);
      break;
    case '*':
      result=num*num1;
      itoa(result,result1);
      LCD_displayStringRowColumn(1,0,result1);
      Delay_MS(2000);
      break;
      
    }
    // clear the global variables to use the Calculator again
    num=0;
    result=0;
  }
}












void Timer()
{
  // intiallize the variables
  char min1='0';
  char sec1='0';
  char min2='0';
  char sec2='0';
  
  char key_min1[2];
  key_min1[0]=min1;
  key_min1[1]='\0';
  char key_min2[2];
  key_min2[0]=min2;
  key_min2[1]='\0';
  char key_sec1[2];
  key_sec1[0]=sec1;
  key_sec1[1]='\0';
  char key_sec2[2];
  key_sec2[0]=sec2;
  key_sec2[1]='\0';
  
  //intiallize the screen for the Timer Mode
  LCD_clearScreen();
  LCD_displayString("Timer Mode");
  LCD_moveCursor(1,0);
  LCD_displayString("00:00");
  Delay_MS(1000);
  LCD_moveCursor(1,0);
  
  //Takes the Time from the User using the keypad
  min1=KEYPAD_getTimePressedKey();
  
  key_min1[0]=min1;
  LCD_displayCharacter(min1);
  if(state != TIMER)
  {
    LCD_clearScreen();
    return;
  }
  Delay_MS(400);
  min2=KEYPAD_getTimePressedKey();
  
  key_min2[0]=min2;
  LCD_displayCharacter(min2);
  if(state != TIMER)
  {
    LCD_clearScreen();
    return;
  }
  Delay_MS(400);
  LCD_displayStringRowColumn(1,2,":");
  sec1=KEYPAD_getTimePressedKey();
  
  key_sec1[0]=sec1;
  LCD_displayCharacter(sec1);
  Delay_MS(400);
  if(state != TIMER)
  {
    LCD_clearScreen();
    return;
  }
  sec2=KEYPAD_getTimePressedKey();
  
  key_sec2[0]=sec2;
  LCD_displayCharacter(sec2);
  if(state != TIMER)
  {
    LCD_clearScreen();
    return;
  }
  Delay_MS(400);
  if(state != TIMER)
  {
    LCD_clearScreen();
    return;
  }
  
  //convert the variables taken from the keypad to the globale variables
  minTime1=atoi(key_min1);
  minTime2=atoi(key_min2);
  secTime1=atoi(key_sec1);
  secTime2=atoi(key_sec2);
  LCD_clearScreen();
  LCD_displayStringRowColumn(0,0,"Timer Mode");
  //intiallize the Timer0
  Timer0_setCallBack(Timing);
  
  uint8 key =KEYPAD_getTimePressedKey();
  if(key == '#')
  {
    Timer0_Init();
  }
  
  
  
  
  
  while(state==TIMER)
    
  {
    // The falg is set when Timer0 interrupt which is every second
    if(time_flag==1)
    {
      time_flag=0;/*clear the flag*/
      
      
      
      // end of the Timer, the Red led is on for 5 seconds
      if((minTime1==0)&&(minTime2==0)&&(secTime1==0)&&(secTime2==0))
      {
        DIO_Init(PORTF,1,OUT,PULLDOWN);
        DIO_WritePin(PORTF,1,HIGH);
        Delay_MS(5000);
        DIO_WritePin(PORTF,1,LOW);
        break;
        
      }
      
      
      
      //below conditions check that there is always a remaining time to be decrement
      
      
      if((minTime2==0)&&(secTime1==0)&&(secTime2==0))
      {
        minTime1 -=1;
        minTime2=9;
        secTime2=10;
        secTime1 =5;
      }
      else if((secTime1==0) && (secTime2==0))
      {
        minTime2 -=1;
        secTime1=5;
        secTime2 =10;
      }
      else if(secTime2==0)
      {
        secTime2=10;
        secTime1 -=1;
      }
      secTime2 -=1;
      
      // convert the new value of the variables to its char variable to be displayed
      itoa(secTime1,key_sec1);
      itoa(secTime2,key_sec2);
      itoa(minTime1,key_min1);
      itoa(minTime2,key_min2);
      
    }
    
    // else the flag is not set -> display the variables on the LCD
    else
    {
      LCD_moveCursor(1,0);
      LCD_displayCharacter(key_min1[0]);
      LCD_moveCursor(1,1);
      LCD_displayCharacter(key_min2[0]);
      LCD_displayStringRowColumn(1,2,":");
      LCD_displayCharacter(key_sec1[0]);
      LCD_displayCharacter(key_sec2[0]);
      
      
    }
  }
  
  
  
  
}





void Stopwatch()
{
  LCD_clearScreen();
  
  char key_min1[2];
  key_min1[0]='0';
  key_min1[1]='\0';
  char key_min2[2];
  key_min2[0]='0';
  key_min2[1]='\0';
  char key_sec1[2];
  key_sec1[0]='0';
  key_sec1[1]='\0';
  char key_sec2[2];
  key_sec2[0]='0';
  key_sec2[1]='\0';
  char key_hour1[2];
  key_hour1[0]='0';
  key_hour1[1]='\0';
  char key_hour2[2];
  key_hour2[0]='0';
  key_hour2[1]='\0';
  
  
  
  //intiallize the global variables
  seconds_1=atoi(key_sec1);
  seconds_2=atoi(key_sec2);
  minutes_2=atoi(key_min2);
  minutes_1=atoi(key_min1);
  hours_1 =atoi(key_hour1);
  hours_2 =atoi(key_hour2);
  
  //intiallize the Systick 
  SysTick_Disable();
  SysTickPeriodSet(1000);
  //  SysTick_Enable();
  
  
  LCD_displayStringRowColumn(0,0,"Stopwatch Mode");
  
  
  //intiallize the the pins used for the interrupt and enable the interrupt in each pin
  DIO_Init(PORTA,2,IN,PULLDOWN);
  DIO_Init(PORTA,3,IN,PULLDOWN);
  DIO_Init(PORTA,7,IN,PULLDOWN);
  GPIOIntRegister(0x40004000,PRR);
  GPIOIntTypeSet(0x40004000,0x04,GPIO_FALLING_EDGE);
  GPIOIntTypeSet(0x40004000,0x08,GPIO_FALLING_EDGE);
  GPIOIntTypeSet(0x40004000,0x80,GPIO_FALLING_EDGE);
  GPIOIntEnable(0x40004000,GPIO_INT_PIN_3);
  GPIOIntEnable(0x40004000,GPIO_INT_PIN_2 );
  GPIOIntEnable(0x40004000,GPIO_INT_PIN_7 );
  
  
  
  
  
  
  while(state==STOPWATCH)
  {
    //The flag is set when the Systick intterrupt which is every second
    if(sec_flag==1){
      
      seconds_1++;
      if(seconds_1==10){
        seconds_2++;
        seconds_1=0;
      }
      
      if(seconds_2==6){
        minutes_1++;
        seconds_1=0;
        seconds_2=0;
      }
      if(minutes_1==10){
        minutes_2++;
        minutes_1=0;
      }
      if(minutes_2==6){
        hours_1++;
        minutes_1=0;
        minutes_2=0;
      }
      if(hours_2==10){
        hours_2=0;
        hours_1=0;
        minutes_1=0;
        minutes_2=0;
        seconds_1=0;
        seconds_2=0;
      }
      sec_flag=0;/*clear the flag*/
      
      
      
      
      //convert the variable into to char to be displayed on the LCD
      itoa(seconds_1,key_sec1);
      itoa(seconds_2,key_sec2);
      itoa(minutes_1,key_min1);
      itoa(minutes_2,key_min2);
      itoa(hours_1,key_hour1);
      itoa(hours_2,key_hour2);
      
    }
    
    // else the flag is not set -> display the variables on the LCD
    else{
      
      itoa(seconds_1,key_sec1);
      itoa(seconds_2,key_sec2);
      itoa(minutes_1,key_min1);
      itoa(minutes_2,key_min2);
      itoa(hours_1,key_hour1);
      itoa(hours_2,key_hour2);
      
      
      LCD_moveCursor(1,0);
      LCD_displayCharacter(key_hour2[0]);
      LCD_moveCursor(1,1);
      LCD_displayCharacter(key_hour1[0]);
      LCD_displayStringRowColumn(1,2,":");
      LCD_displayCharacter(key_min2[0]);
      LCD_displayCharacter(key_min1[0]);
      LCD_displayStringRowColumn(1,5,":");
      LCD_displayCharacter(key_sec2[0]);
      LCD_displayCharacter(key_sec1[0]);
      
      
      
    }
  }
}



