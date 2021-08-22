/*
 * control.h
 *
 *  Created on: Apr 6, 2020
 *      Author: william
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include <stdint.h>

#define LR_STEP_MM (0.0272533163)
#define D1_MM (378)
#define D2_MM (0)

#define D1_STEPS (D1_MM/LR_STEP_MM)
#define D2_STEPS (D2_MM/LR_STEP_MM)

typedef struct {
	uint16_t x;
	uint16_t y;
}point;

void control_init(void);
void set_lr(uint16_t l, uint16_t r);
void moveAbs (uint16_t x, uint16_t y);
void move (uint16_t x, uint16_t y);
void moveDirect(uint16_t x, uint16_t y);
void move_mm(double x, double y);
void moveDirect_mm(double x, double y);
point getPosition(void);
void setLocalPos(point p);

#endif /* CONTROL_H_ */
