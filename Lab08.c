/*****************************************************************************
 *	    File: Lab08.c
 *  Lab Name: RS232 Communication Server
 *    Author: Dr. Greg Nordstrom
 *   Created: 12/30/17
 *  Mod Date: 3/28/19, 1/17/21
 *  Modified:
 *   ModDate:
 * 
 * Processor: ATmega128A (on the ReadyAVR board)
 *
 * This program implements a communication server. Normally the server
 * simply echoes what was sent. However, there are two cases where
 * different behavior occurs:
 *    1. Pressing the ESC causes a soft reset (redisplays the title text)
 *    2. Typing the letters 'end' contiguously displays 'Bye' and halts
 *
 *****************************************************************************/

// define CPU speed (7.3728 MHz for the ATmega128A)
#define F_CPU   7372800UL

#define CR          0x0D
#define LF          0x0A
#define ESC         0x1B

#include <avr/io.h>
#include <util/delay.h>
#include "UARTLibrary.h"  // Double quotes for local library.

#define BAUDRATE 9600 // standard values from 1200 to 115200
#define DATABITS    8 // 5-8
#define STOPBITS    1 // 1,2
#define PARITY      0 // 0=none, 1=odd, 2=even

/* Your code here.  */
DDRC = 0xFF;  // Set the Direction for all PORTA pints to be outputs
PORTC = 0xFF;  // Set the PORTA for all pins to be high (i.e. OFF)

int main(void)
{
	/* Your code here.  */
	//unsigned char count = 0;
    /* See the UARTLibrary.h for available calls.
	 *     	  // initialize the UART
	 *     	  uart_init(BAUDRATE, DATABITS, STOPBITS, PARITY);
	 *
	 *        // transmit a value (0x41) to the comm port
	 *        c = 0x41;
	 *        uart_tx(c);
	 *
	 *        // receive a byte from the comm port
	 *        c = uart_rx();
	 */

	uart_init(BAUDRATE, DATABITS, STOPBITS, PARITY);
	initial_msg();
	while(1) 
	{
		/* your loop code here */
		//unsigned char temp = uart_rx();
		//while()
		//PORTC = ~(1<<0);
		//uart_tx(temp);
		 
		
	}
	return 0;
}

void initial_msg(){
	const char blank[] = "\r\n\0";
	const char head_1[] = "RS232 Communications Server\r\n";
	const char head_2[] = "Status: Active\r\n";
	const char name[] = "James Myhill\r\n";
	const char classMsg[] = "EECE3624\r\n";
	const char date[] = "Fall 2026\r\n";
	
	unsigned char i = 0;
	while(blank[i] != '\0'){
		uart_tx(blank[i]);
		i++;
	}
	i = 0;
	while(head_1[i] != '\0'){
		uart_tx(head_1[i]);
		i++;
	}
	i = 0;
	while(head_2[i] != '\0'){
		uart_tx(head_2[i]);
		i++;
	}
	i = 0;
	while(name[i] != '\0'){
		uart_tx(name[i]);
		i++;
	}
	i = 0;
	while(date[i] != '\0'){
		uart_tx(date[i]);
		i++;
	}
	i = 0;
	while(blank[i] != '\0'){
		uart_tx(blank[i]);
		i++;
	}
}
