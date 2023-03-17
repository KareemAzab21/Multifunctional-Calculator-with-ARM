 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Team15
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                  4
#define KEYPAD_NUM_ROWS                  4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID              PORTE
#define KEYPAD_COL_PORT_ID              PORTC

#define KEYPAD_FIRST_ROW_PIN_ID           0
#define KEYPAD_FIRST_COLUMN_PIN_ID        4
 


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initiallize the Pins for the Keypad
 */
void KeyPad_Init(void);
/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);




uint8 KEYPAD_getTimePressedKey(void);




uint8 KEYPAD_getCalcPressedKey(void);
#endif /* KEYPAD_H_ */
