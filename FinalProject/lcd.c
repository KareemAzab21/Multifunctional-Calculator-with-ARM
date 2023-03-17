#include "lcd.h"
#include "DIO.h"



void LCD_init(void)
{
	/* Configure the direction for RS, RW and E pins as output pins */
        DIO_Init(LCD_RS_PORT_ID,LCD_RS_PIN_ID,OUT,PULLDOWN);
        DIO_Init(LCD_RW_PORT_ID,LCD_RW_PIN_ID,OUT,PULLDOWN);
        DIO_Init(LCD_E_PORT_ID,LCD_E_PIN_ID,OUT,PULLDOWN);


	/* Configure the data port as output port */
	for(int i=0;i<8;i++)
        {
          DIO_Init(LCD_DATA_PORT_ID,i,OUT,PULLDOWN);
        }

	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */

	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
        LCD_sendCommand(LCD_CURSOR_ON);
}




void LCD_sendCommand(uint8 command)
{
	DIO_WritePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOW); /* Instruction Mode RS=0 */
	DIO_WritePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOW); /* write data to LCD so RW=0 */
	Delay_MS(1); /* delay for processing Tas = 50ns */
	DIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,HIGH); /* Enable LCD E=1 */
	Delay_MS(1); /* delay for processing Tpw - Tdws = 190ns */
	DIO_WritePort(LCD_DATA_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
	Delay_MS(1); /* delay for processing Tdsw = 100ns */
	DIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOW); /* Disable LCD E=0 */
	Delay_MS(1); /* delay for processing Th = 13ns */
}






void LCD_displayCharacter(uint8 data)
{
	DIO_WritePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,HIGH); /* Data Mode RS=1 */
	DIO_WritePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOW); /* write data to LCD so RW=0 */
	Delay_MS(1); /* delay for processing Tas = 50ns */
	DIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,HIGH); /* Enable LCD E=1 */
	Delay_MS(1); /* delay for processing Tpw - Tdws = 190ns */
	DIO_WritePort(LCD_DATA_PORT_ID,data); /* out the required command to the data bus B0 --> B7 */
	Delay_MS(1); /* delay for processing Tdsw = 100ns */
	DIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOW); /* Disable LCD E=0 */
	Delay_MS(1); /* delay for processing Th = 13ns */
}



void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
	/***************** Another Method ***********************
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
	*********************************************************/
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}