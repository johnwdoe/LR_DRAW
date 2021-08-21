/*
 * usartio.h
 *
 *  Created on: Jun 6, 2014
 *      Author: william
 */

#ifndef USARTIO_H_
#define USARTIO_H_

#include <stdio.h>
#define BAUD (19200)
#define _UBRR (F_CPU/16/BAUD-1)

/*FN prototypes*/
void usartio_init(void);
int usart_putchar_printf(char var, FILE *stream);
int usart_getchar_scanf(FILE *stream);
#endif /* USARTIO_H_ */
