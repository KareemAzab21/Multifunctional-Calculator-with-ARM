
#ifndef DIO_H
#define DIO_H


#include "types.h"


/*************************************************************
*                       DEFINITIONS
*
***************************************************************/
#define PORTA   0
#define PORTB   1
#define PORTC   2
#define PORTD   3
#define PORTE   4
#define PORTF   5
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762


/*************************************************************
*                       Types Declaration
*
***************************************************************/

//enum for the value of the pin
typedef enum
{
  LOW,HIGH
}DIO_Value; 
//enum for the direction of the pin
typedef enum
{       
  IN,OUT
}DIO_Direction;

// enum whether the pin is configured with a Pullup or Pulldown resistor
typedef enum
{
  PULLUP,PULLDOWN
}DIO_Res;

// struct for a configurable pin
typedef struct
{
  uint8 port;
  uint8 pin;
  DIO_Direction direction;
  DIO_Res resistor;
}DIO_ConfigType;




/*************************************************************
*                       FUNCTION PROTOTYPES
*
***************************************************************/
/*
 * Description :
 * Intiallize the pin
 */
void DIO_Init(uint8 port,uint8 pin,DIO_Direction direction,DIO_Res resistor);
/*
 * Description :
 * write in a given pin HIGH or LOW
 */
void DIO_WritePin(uint8 port,uint8 pin,DIO_Value value);
/*
 * Description :
 * Toggle A Given Pin
 */
void DIO_TogglePin(uint8 port, uint8 pin  );
/*
 * Description :
 * Write to a Port Data
 */
void DIO_WritePort(uint8 port,uint8 value);
/*
 * Description :
 * Read a Given Pin
 * return whether it is HIGH or LOW
 */
DIO_Value DIO_ReadPin(uint8 port, uint8 pin);
/*
 * Description :
 * a delay function by looping
 */
void Delay_MS(unsigned long long n);


#endif