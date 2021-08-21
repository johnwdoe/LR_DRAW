/*
 * stepper.c
 *
 *  Created on: Oct 27, 2016
 *      Author: ikhatckevich
 */

#include "stepper.h"
#include <util/delay.h>

uint8_t stepper_do(drvCtx* drv){
	_delay_us(100);
	if (drv->curPos == drv->dstPos) return 0;
	*drv->ctlPort &= ~(drv->ctlMask/* & ~0b10101010*/); //опускаем нужный кусок порта
	if (drv->dstPos > drv->curPos){
		//move forward
		drv->curPos++;
		*drv->ctlPort |= (drv->fwdDir & 0b10101010 & drv->ctlMask);
	}else{
		//move backward
		drv->curPos--;
		*drv->ctlPort |= (~drv->fwdDir & 0b10101010 & drv->ctlMask);
	}
	//wait for direction setup time
	_delay_us(1); //minimum 200 ns
	//step pulse
	*drv->ctlPort |= (drv->ctlMask & 0b01010101);
	_delay_us(1);
	*drv->ctlPort &= ~(drv->ctlMask & 0b01010101);

	return 1;
}
