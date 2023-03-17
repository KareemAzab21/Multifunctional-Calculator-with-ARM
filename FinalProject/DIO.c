#include "tm4c123gh6pm.h"
#include "DIO.h"
#include "Common_Macros.h"
#include "types.h"
#include "tm4c123gh6pm.h"






void DIO_Init(uint8 port,uint8 pin,DIO_Direction direction,DIO_Res resistor){
  SET_BIT(SYSCTL_RCGCGPIO_R,port);
switch ( port){
  case PORTA:
    GPIO_PORTA_LOCK_R=0x4C4F434B;
    SET_BIT(GPIO_PORTA_CR_R, pin ); 
    SET_BIT(GPIO_PORTA_DEN_R,pin);
      if(direction)
      {
        SET_BIT(GPIO_PORTA_DIR_R, pin);
      }
      else
      {
        CLEAR_BIT(GPIO_PORTA_DIR_R, pin);
      }
      if(resistor)
      {
      SET_BIT(GPIO_PORTA_PDR_R, pin);
      }
      else
      {
      SET_BIT(GPIO_PORTA_PUR_R, pin);
      }
      
      break;
      
   case PORTB:
      GPIO_PORTB_LOCK_R=0x4C4F434B;
      SET_BIT(GPIO_PORTB_CR_R, pin );
      SET_BIT(GPIO_PORTB_DEN_R,pin);
      if(direction)
      {
        SET_BIT(GPIO_PORTB_DIR_R, pin);
      }
      else
      {
        CLEAR_BIT(GPIO_PORTB_DIR_R, pin);
      }
      if(resistor)
      {
      SET_BIT(GPIO_PORTB_PDR_R, pin);
      }
      else
      {
      SET_BIT(GPIO_PORTB_PUR_R, pin);
      }
      
      break;
      
    case PORTC:
      GPIO_PORTC_LOCK_R=0x4C4F434B;
      SET_BIT(GPIO_PORTC_CR_R, pin );
      SET_BIT(GPIO_PORTC_DEN_R,pin);
      if(pin <=3)
      {
      break;
      }
      else
      {
        if(direction)
        {
          SET_BIT(GPIO_PORTC_DIR_R,pin);
        }
        else
        {
          CLEAR_BIT(GPIO_PORTC_DIR_R, pin);
        }
      if(resistor)
      {
        SET_BIT(GPIO_PORTC_PDR_R,pin);
      }
      else
      {
        SET_BIT(GPIO_PORTC_PUR_R,pin);
      }
      
      break;
      }
    case PORTD:
      GPIO_PORTD_LOCK_R=0x4C4F434B;
      SET_BIT(GPIO_PORTD_CR_R, pin ); 
      SET_BIT(GPIO_PORTD_DEN_R,pin);
      if(direction)
      {
        SET_BIT(GPIO_PORTD_DIR_R, pin);
      }
      else
      {
        CLEAR_BIT(GPIO_PORTD_DIR_R, pin);
      }
      if(resistor)
      {
      SET_BIT(GPIO_PORTD_PDR_R, pin);
      }
      else
      {
      SET_BIT(GPIO_PORTD_PUR_R, pin);
      }
      
      break;
      
    case PORTE:
      GPIO_PORTE_LOCK_R=0x4C4F434B;
      SET_BIT(GPIO_PORTE_CR_R, pin ); 
      SET_BIT(GPIO_PORTE_DEN_R,pin);
      if(direction)
      {
        SET_BIT(GPIO_PORTE_DIR_R,pin);
      }
      else
      {
        CLEAR_BIT(GPIO_PORTE_DIR_R, pin);
       }
      if(resistor)
      {
      SET_BIT(GPIO_PORTE_PDR_R,pin);
      }
      else
      {
      SET_BIT(GPIO_PORTE_PUR_R, pin);
      }
      
      break;
      
    case PORTF:
      GPIO_PORTF_LOCK_R=0x4C4F434B;
      SET_BIT(GPIO_PORTF_CR_R, pin );
      SET_BIT(GPIO_PORTF_DEN_R,pin);
      if(direction)
      {
        SET_BIT(GPIO_PORTF_DIR_R, pin);
      }
      else
      {
        CLEAR_BIT(GPIO_PORTF_DIR_R,pin);
       }
      if(resistor)
      {
      SET_BIT(GPIO_PORTF_PDR_R, pin);
      }
      else
      {
        SET_BIT(GPIO_PORTF_PUR_R, pin);
      }
      
      break;
          
  }

}


void DIO_WritePin(uint8 port,uint8 pin,DIO_Value value)
{
  switch(port){
    case PORTA:
      if(value){SET_BIT(GPIO_PORTA_DATA_R,pin);}
      else CLEAR_BIT(GPIO_PORTA_DATA_R, pin);
      break;
      
    case PORTB:
      if(value){SET_BIT(GPIO_PORTB_DATA_R,pin);}
      else CLEAR_BIT(GPIO_PORTB_DATA_R, pin);
      break;
 
    case PORTC:
      if(value){SET_BIT(GPIO_PORTC_DATA_R,pin);}
      else CLEAR_BIT(GPIO_PORTC_DATA_R, pin);
      break;
      
    case PORTD:
      if(value){SET_BIT(GPIO_PORTD_DATA_R,pin);}
      else CLEAR_BIT(GPIO_PORTD_DATA_R, pin);
      break;

    case PORTE:
      if(value){SET_BIT(GPIO_PORTE_DATA_R,pin);}
      else CLEAR_BIT(GPIO_PORTE_DATA_R, pin);
      break;
      
    case PORTF:
      if(value){SET_BIT(GPIO_PORTF_DATA_R,pin);}
      else CLEAR_BIT(GPIO_PORTF_DATA_R, pin);
      break;
  
  }
  
}
void DIO_TogglePin(uint8 port, uint8 pin)
{
  switch(port)
  {
  case PORTA:
    TOGGLE_BIT(GPIO_PORTA_DATA_R,pin);
    break;
   case PORTB:
    TOGGLE_BIT(GPIO_PORTB_DATA_R,pin);
    break;
   case PORTC:
    TOGGLE_BIT(GPIO_PORTC_DATA_R,pin);
    break;
   case PORTD:
    TOGGLE_BIT(GPIO_PORTD_DATA_R,pin);
    break;
   case PORTE:
    TOGGLE_BIT(GPIO_PORTE_DATA_R,pin);
    break;
   case PORTF:
    TOGGLE_BIT(GPIO_PORTF_DATA_R,pin);
    break;
    
  }
}

void Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}



void DIO_WritePort(uint8 port,uint8 value){
  switch(port)
  {
    case PORTA:
      GPIO_PORTA_DATA_R=value;
      break;
    case PORTB:
      GPIO_PORTB_DATA_R=value;
      break;
    case PORTC:
      GPIO_PORTC_DATA_R=value;
      break;
    case PORTD:
      GPIO_PORTD_DATA_R=value;
      break;
    case PORTE:
      GPIO_PORTE_DATA_R=value;
      break;
    case PORTF:
      GPIO_PORTF_DATA_R=value;
      break;
    default:
      break;
    
      
  }
 
}

DIO_Value DIO_ReadPin(uint8 port, uint8 pin)
{
  DIO_Value value;
  switch(port)
  {
  case PORTA:
    if(BIT_IS_SET(GPIO_PORTA_DATA_R,pin))
    {
      value=HIGH;
    }
    else
    {
      value=LOW;
    }
    break;
   case PORTB:
    if(BIT_IS_SET(GPIO_PORTB_DATA_R,pin))
    {
      value=HIGH;
    }
    else
    {
      value=LOW;
    }
    break;
   case PORTC:
    if(BIT_IS_SET(GPIO_PORTC_DATA_R,pin))
    {
      value=HIGH;
    }
    else
    {
      value=LOW;
    }
    break;
  case PORTD:
    if(BIT_IS_SET(GPIO_PORTD_DATA_R,pin))
    {
      value=HIGH;
    }
    else
    {
      value=LOW;
    }
    break;
   case PORTE:
    if(BIT_IS_SET(GPIO_PORTE_DATA_R,pin))
    {
      value=HIGH;
    }
    else
    {
      value=LOW;
    }
    break;
  case PORTF:
    if(BIT_IS_SET(GPIO_PORTF_DATA_R,pin))
    {
      value=HIGH;
    }
    else
    {
      value=LOW;
    }
    break;
  }
 return value;
}



uint8 DIO_ReadPort(uint8 port)
{
  uint8 value;
  switch(port)
  {
  case PORTA:
    value=GPIO_PORTA_DATA_R;
    break;
 
  case PORTB:
    value=GPIO_PORTB_DATA_R;
    break;

  case PORTC:
    value=GPIO_PORTC_DATA_R;
    break;
  case PORTD:
    value=GPIO_PORTD_DATA_R;
    break;
  case PORTE:
    value=GPIO_PORTE_DATA_R;
    break;
  case PORTF:
    value=GPIO_PORTF_DATA_R;
    break;
  }
 return value;
}





