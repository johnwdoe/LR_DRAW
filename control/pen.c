/*
 * pen.c
 *
 *  Created on: Apr 6, 2020
 *      Author: william
 */

#include "pen.h"
#include <avr/io.h>
#include <util/delay.h>

void pen_init(void)
{
	DDRB |= (1<<PB1); //PWM OUT
	//init pwm 50 Hz
	TCCR1A = (1<<COM1A1 | 1<<WGM11); //clear on compare match, set at BOTTOM
	ICR1 = 20000;

	TCCR1B |= (1<<WGM13 | 1<<WGM12 | 1<<CS11); //CTC to ICR1, and start

	pen_set(0);
}
void pen_set(uint8_t v)
{
	if (v)
	{
		OCR1A = PEN_PWM_DOWN;
	} else
	{
		OCR1A = PEN_PWM_UP;
	}
	_delay_ms(PEN_TRANSITION_TIME_MS);
}


