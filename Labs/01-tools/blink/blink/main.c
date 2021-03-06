/***********************************************************************
 * 
 * Blink a LED and use the function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
																				//# ... pred kompilaci
#define LED_GREEN   PB5     // AVR pin where green LED is connected				// prejmenuje PB5 
#define SHORT_DELAY 100     // Delay in miliseconds
#define DOT_DELAY 200		// Delay for dot in miliseconds
#define DASH_DELAY 400      // Delay for dash in miliseconds
#define LEN 50				// max lenght of input characters
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay func		// procesor bezi na 16 MHz 
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Variables ---------------------------------------------------------*/

/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 * Toggle one LED and use the function from the delay library.
 */

void morse(char code[LEN])	// Function for detecting dash or dot in char array and blinking correspondingly
{
	for(int i = 0; i<=LEN; i++)
	{
		if(code[i]=='-')
		{
			PORTB = PORTB ^ (1<<LED_GREEN);
			_delay_ms(DASH_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN);
			_delay_ms(DOT_DELAY);
		}
		else if(code[i]=='.')
		{
			PORTB = PORTB ^ (1<<LED_GREEN);
			_delay_ms(DOT_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN);
			_delay_ms(DOT_DELAY);
		}
		else
		{
			_delay_ms(SHORT_DELAY);
		}
	}
}

int main(void)
{
    // Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000
    DDRB = DDRB | (1<<LED_GREEN);												// data direction register B, jestli je vstupni nebo vyst. (...nahrajeme 1) port
																				//OR - nastaveni na 1... ( aby se nam neprepsaly pripadne 1 ktere tam uz jsou)
    // Set pin LOW in Data Register (LED off)
    // PORTB = PORTB and 1101 1111
    PORTB = PORTB & ~(1<<LED_GREEN);											//<< binary shift, posune se o PB5 - 5 pozic (PB5 je na 5. pinu)
																				//AND - nastaveni na nulu, negace ~
    // Infinite loop
	// blinking
	while (1)
	{
		char code[LEN] = "-..,.,..---";											// D-E-2 ...(- . .; .; . . - - -)
		morse(code);
		// Pause several miliseconds
		_delay_ms(SHORT_DELAY);

		// Invert LED in Data Register
		// PORTB = PORTB xor 0010 0000
		PORTB = PORTB ^ (1<<LED_GREEN);
	}

    // Will never reach this
    return 0;
}
/* Interrupt routines ------------------------------------------------*/
