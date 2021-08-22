/*
 * main.c
 *
 *  Created on: Apr 6, 2020
 *      Author: william
 */
#include <avr/io.h>
#include "control/control.h"
#include "control/pen.h"
#include "usartio.h"
#include "processor/processor.h"


int main(void)
{
	usartio_init();
	pen_init();
	control_init();
	//home();
	set_lr(229/LR_STEP_MM,227/LR_STEP_MM); //TODO think about this hardcode!
	printf("Ready ...\r\n");
	char strBuf[100];
	while(1)
	{
		gets(strBuf);
		//printf("Command received: %s\n", strBuf);
		processCommand(strBuf);
		printf(" ");
		//usart_putchar_printf(0xFF, NULL);

	}

	return 0;
}


