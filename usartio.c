/*
 * usartio.c
 *
 *  Created on: Jun 6, 2014
 *      Author: william
 */


#include "usartio.h"
#include <avr/io.h>

static FILE uart_io = FDEV_SETUP_STREAM(usart_putchar_printf, usart_getchar_scanf, _FDEV_SETUP_RW);

void usartio_init(void){
	uint16_t ubrr = _UBRR;
	UBRRH = (uint8_t)(ubrr>>8);
	UBRRL = (uint8_t)ubrr;
	UCSRB = (1<<RXEN | 1<<TXEN);
	UCSRC = (1<<URSEL | 3<<UCSZ0);
	stdout = stdin = &uart_io;
}

int usart_putchar_printf(char var, FILE *stream){
	/*if (var == '\n'){
		usart_putchar_printf('\r', stream);
	}*/
	while(!(UCSRA&(1<<UDRE)));
	UDR = var;
	return 0;
}

int usart_getchar_scanf(FILE *stream){
	// Wait for byte to be received
	while(!(UCSRA&(1<<RXC)));
	// Return received data
	return UDR;
}
