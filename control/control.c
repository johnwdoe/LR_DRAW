/*
 * control.c
 *
 *  Created on: Apr 6, 2020
 *      Author: william
 */

#include "control.h"
#include "stepper.h"
#include "slow_math.h"
#include <avr/io.h>

drvCtx dl = {0, 0, 0xFF, &PORTD, 0b00110000};
drvCtx dr = {0, 0, 0x00, &PORTD, 0b11000000};
point lastPos = {0, 0};

void control_init(void)
{
	DDRD |= (1<<PD4 | 1<<PD5 | 1<<PD6 | 1<<PD7); // SL, DL, SR, DR
}

void move (uint16_t x, uint16_t y)
{
	//convert x,y to l,r (all in steps)
	dl.dstPos = slow_sqrt(slow_pwr2(x) + slow_pwr2(y));
	dr.dstPos = slow_sqrt(slow_pwr2(D1_STEPS - D2_STEPS - x) + slow_pwr2(y));
	//set last position
	lastPos.x = x;
	lastPos.y = y;
	//waiting for completion
	while (stepper_do(&dl) | stepper_do(&dr));
}

void moveDirect(uint16_t x, uint16_t y)
{
	uint16_t xc = lastPos.x;
	uint16_t yc = lastPos.y;
	int16_t deltaX = (xc < x) ? x - xc : xc - x;
	int16_t deltaY = (yc < y) ? y - yc : yc - y;
	int8_t signX = (xc < x) ? 1 : -1;
	int8_t signY = (yc < y) ? 1 : -1;
	int16_t er = deltaX - deltaY;

	while(xc != x || yc != y)
	{
		move(xc, yc);
		int16_t er2 = er * 2;
		if(er2 > -deltaY)
		{
			er -= deltaY;
			xc += signX;
		}
		if(er2 < deltaX)
		{
			er += deltaX;
			yc += signY;
		}
	}
	move(x, y);
}
point getPosition(void)
{
	return lastPos;
}

void set_lr(uint16_t l, uint16_t r)
{
	dl.curPos = l;
	dr.curPos = r;
}

