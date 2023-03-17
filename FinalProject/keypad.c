 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Kareem Ahmed Azab
 *
 *******************************************************************************/
#include "common_macros.h" 
#include "keypad.h"
#include "Dio.h"
#include "app.h"



/*Global Array that represent 4x4 Keypad*/
uint8 arr[4][4]={{'1','2','3','+'},{'4','5','6','-'},{'7','8','9','/'},{'*','0','#','='}};
extern STATE state;

   
void KeyPad_Init()
{
  //for loop that intiallizes the row pins
  for(int row = 0; row<=KEYPAD_NUM_ROWS;row++)
  {
      DIO_Init(KEYPAD_ROW_PORT_ID ,row,OUT,PULLDOWN);
  }
  //for loop that intiallizes the coloumn pins
  for(int col = 4; col<= 7;col++){

      DIO_Init(KEYPAD_COL_PORT_ID ,col,IN,PULLDOWN);
  }
  
}
   
 

 /*
 * Description :
 * Get the Keypad pressed button
 */  
   
 
uint8 KEYPAD_getPressedKey()
{
  
  while(1)
  {
    for(int i=0;i<4;i++)
    {
      DIO_WritePin(KEYPAD_ROW_PORT_ID,i,HIGH);
      for(int j=4;j<8;j++)
      {
        if(DIO_ReadPin(KEYPAD_COL_PORT_ID,j)==HIGH)
        {
          DIO_WritePin(KEYPAD_ROW_PORT_ID,i,LOW);
          return arr[i][j-4];
        }
      }
      
      DIO_WritePin(KEYPAD_ROW_PORT_ID,i,LOW);
    }
  }
 
}




uint8 KEYPAD_getCalcPressedKey()
{
  
  while(state==CALC)
  {
    for(int i=0;i<4;i++)
    {
      DIO_WritePin(KEYPAD_ROW_PORT_ID,i,HIGH);
      for(int j=4;j<8;j++)
      {
        if(DIO_ReadPin(KEYPAD_COL_PORT_ID,j)==HIGH)
        {
          DIO_WritePin(KEYPAD_ROW_PORT_ID,i,LOW);
          return arr[i][j-4];
        }
      }
      
      DIO_WritePin(KEYPAD_ROW_PORT_ID,i,LOW);
    }
  }
 
}




uint8 KEYPAD_getTimePressedKey()
{
  
  while(state==TIMER)
  {
    for(int i=0;i<4;i++)
    {
      DIO_WritePin(KEYPAD_ROW_PORT_ID,i,HIGH);
      for(int j=4;j<8;j++)
      {
        if(DIO_ReadPin(KEYPAD_COL_PORT_ID,j)==HIGH)
        {
          DIO_WritePin(KEYPAD_ROW_PORT_ID,i,LOW);
          return arr[i][j-4];
        }
      }
      
      DIO_WritePin(KEYPAD_ROW_PORT_ID,i,LOW);
    }
  }

}


