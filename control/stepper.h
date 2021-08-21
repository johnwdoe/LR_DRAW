/*
 * stepper.h
 *
 *  Created on: Oct 27, 2016
 *      Author: ikhatckevich
 *
 *  Библиотечка умеет либо шагать, либо нихуя
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdint.h>

typedef struct {
	volatile uint16_t curPos; //текущая позиция (в шагах)
	volatile uint16_t dstPos; //позиция назначения
	const uint8_t fwdDir; //значение direction, соответствующее движению оси вперед (чтоб фазы не перетыкать). 0x00 или 0xFF
	volatile uint8_t* ctlPort; //ссылка на порт (передается как &PORTx)
	const uint8_t ctlMask; //маска части порта для управления (d*, s*)
}drvCtx;

/*
 * производит один шаг к позиции назначения
 * возвращает число шагов. 0 - если уже в позиции назначения
 * */
uint8_t stepper_do(drvCtx* drv);

#endif /* STEPPER_H_ */
