/*	Author: Alyssa Zepeda
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #4
 *	Exercise Description:An amusement park kid ride cart has three seats, with 8-bit weight sensors connected to ports A, B, and C (measuring from 0-255 kilograms). Set PD0 to 1 if the cart's total passenger weight exceeds the maximum of 140 kg. Also, the cart must be balanced: Set port PD1 to 1 if the difference between A and C exceeds 80 kg.  The remaining 6 bits on D should display an approximation of the total combined weight.

 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0x00; PORTC = 0xFF; // Configure port C's 8 pins as inputs
	DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs, initialize to 0s
	unsigned short weight  = 0x00; 
	unsigned char A = 0x00; 
	unsigned char B = 0x00; 
	unsigned char C = 0x00; 
	unsigned char temp = 0x00; 

	while(1){
		//Read inputs
		A = PINA;
		B = PINB;
		C = PINC;

		//Get total passenger weight
		weight = A + B + C;

		//PD0=1 if weight exceeds 140kg
		if(weight > 0x8C) {
			temp = 0x01;
		}
		else {
			temp = 0x00;
		}

		//If cart difference exceeds 80kg, PD1=1
		if(((A-C) > 0x50) || ((C-A) > 0x50)) {
			temp = temp | 0x02;
		}

		//assign MSB of weight and leave bits 0 & 1 for sensors
		weight = weight >> 2;
		temp = (weight & 0xFC) | temp;
		PORTD = temp;

		
	}
	return 1;
}

