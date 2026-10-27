/*****************************************************************************
 *	    File: USARTLibrary.c
 *  Lab Name: (Needed for Lab07 and Lab08)
 *    Author: Dr. Greg Nordstrom
 *   Created: 3/3/2019
 *  Modified: 
 *  Mod Date:
 * Processor: ATmega128A (on the ReadyAVR board)
 *
 * This is intended to be compiled as an AVR Library Project and
 * used by other programs. After compiling this code, copy the
 * libUSART1Library.a and USART1Library.h files to the project directory,
 * then add the library to the target project by R-clicking on the
 * project's Libraries directory and clicking Add Library. Also,
 * the USART1Library.h file must be #included in the project's .c file.
 *
 * NOTE: This library only works with the default USART1 port
 * on the ReadyAVR (so JP2 must have jumpers on PD3 and PD2).
 */

#include <avr/io.h>
#include "UARTLibrary.h"

// Use USART1_init to initialize the USART hardware in the AVR processor.
// The function takes the following arguments:
//    - desired baud rate (standard values from 2400 to 115200),
//    - number of databits (5-8),
//    - number of stop bits (1,2),
//    - parity (0=no parity, 1=odd parity, 2=even parity).
// No error checking is performed and the function does not return a value.
//
// For example,
//     usart1_init(9600,8,1,0);
// sets the baudrate to 9600, with 8 data bits, 1 stop bit, and no parity

#define F_OSC 7372800
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE ((F_OSC/(USART_BAUDRATE * 16UL))-1)

void uart_init(long unsigned int baudrate, unsigned char databits, unsigned char stopbits, unsigned char parity) {
    /* your code here */
	
	// set baud rate (via UBRR0 high and low registers)
    UBRR1H = (BAUD_PRESCALE >> 8);
    UBRR1L = (BAUD_PRESCALE);

	
	 // Reset USART configuration registers
	 UCSR1A = 0;
	 UCSR1B = 0;
	 UCSR1C = 0;
	 
	// set databits
    if (databits == 5)
    {
	    UCSR1B |= ~(1 << UCSZ12);
    }
    else if (databits == 6)
    {
	    UCSR1C |= (1 << UCSZ10);
	    UCSR1B |= ~(1 << UCSZ12);
    }
    else if (databits == 7)
    {
	    UCSR1C |= (1 << UCSZ11);
	    UCSR1B |= ~(1 << UCSZ12);
    }
    else if (databits == 8)
    {
	    UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10);
	    UCSR1B |= ~(1 << UCSZ12);
    }
	

	// set parity
	UCSR1C |= ~((1 << UPM11) | (1 << UPM10));

	if (parity == 1)
	{
		UCSR1C |= (1 << UPM11) | (1 << UPM10);  // Odd parity
	}
	else if (parity == 2)
	{
		UCSR1C |= (1 << UPM11);                 // Even parity
	}
	
	
    // set stopbits
    if (stopbits == 2) {
    UCSR1C |= (1 << USBS1);
    }
	
	
	// finally, enable receiver and transmitter
    UCSR1B = (1 << RXEN1)|(1 << TXEN1);
}

// This function waits for space in the USART transmit buffer. When space
// is available, the function places an unsigned character value (passed in
// as the function's only argument) in the buffer and returns. No error
// checking is performed and the function does not return a value.

void uart_tx(unsigned char data) {
    /* your code here */
	while(!(UCSR1A & (1 << UDRE1))){
		}				// wait for a character to arrive
		UDR1 = data;	// transmit data
	
}

// This function blocks until a character is received in the USART input
// buffer. Once a character arrives, it is passed back to the caller as
// an unsigned character. No error checking is performed.
unsigned char uart_rx(void) {
	/* your code here */
    while(!(UCSR1A & (1 << RXC1))){
		
		} // wait for a character to arrive
    return UDR1; // return received character to caller
}