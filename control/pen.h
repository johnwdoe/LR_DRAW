/*
 * pen.h
 *
 *  Created on: Apr 6, 2020
 *      Author: william
 */

#ifndef PEN_H_
#define PEN_H_

#include <stdint.h>

#define PEN_PWM_DOWN (1100)
#define PEN_PWM_UP (750)
#define PEN_TRANSITION_TIME_MS (250)

void pen_init(void);
void pen_set(uint8_t v);

#endif /* PEN_H_ */
