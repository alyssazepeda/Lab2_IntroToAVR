/*	Author: Alyssa Zepeda
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #2
 *	Exercise Description: Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning a car is parked in the space, of a four-space parking lot. Write a program that outputs in binary on port C the number of available spaces (Hint: declare a variable "unsigned char cntavail;" you can assign a number to a port as follows: 
PORTC = cntavail;).
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
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char cntavail = 0x00; //count of available spaces
	unsigned char s1 = 0x00; // space 1
	unsigned char s2 = 0x00; // space 2
	unsigned char s3 = 0x00; // space 3
	unsigned char s4 = 0x00; // space 4

	while(1){
		//Read inputs
		s1 = PINA & 0x01;
		s2 = PINA & 0x02;
		s3 = PINA & 0x04;
		s4 = PINA & 0x08;

		//if spaces 2, 3, or 4 are taken, shift over
		//so it can be counted as binary 1
		s2 = s2 >> 1;
		s3 = s3 >> 2;
		s4 = s4 >> 3;

		//subtract spots to get count
		cntavail = 0x04 - (s1 + s2+ s3 + s4);
		PORTC = cntavail;
	}
	return 1;
}

