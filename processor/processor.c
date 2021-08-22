/*
 * processor.c
 *
 *  Created on: Apr 6, 2020
 *      Author: william
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../control/control.h"
#include "../control/pen.h"

#define F_HAS_X (1)
#define F_HAS_Y (2)
#define F_HAS_Z (4)

typedef struct {
	char cOpCode;
	uint8_t nOpCode;
	double x, y, z;
	uint8_t fl;
}command;


void processCommand(char* strCmd)
{
	command cmd = {0, 0, 0, 0, 0, 0};
	char* token = strtok(strCmd, " ");
	//читаем до конца строки или до символа комментария
	while (token != NULL && token[0] != ';')
	{
		//USE CURRENT TOKEN HERE
		//printf("'%s'\n", token);
		switch (token[0])
		{
		case 'X':
			cmd.x = strtod(token+1, NULL);
			cmd.fl |= F_HAS_X;
			break;
		case 'Y':
			cmd.y = strtod(token+1, NULL);
			cmd.fl |= F_HAS_Y;
			break;
		case 'Z':
			cmd.z = strtod(token+1, NULL);
			cmd.fl |= F_HAS_Z;
			break;
		case 'G':
			cmd.cOpCode = token[0];
			cmd.nOpCode = (uint8_t)strtol(token+1, NULL, 10);
		}
		token = strtok(NULL, " ");
	}
	//printf("%c %d %d %d %d %d", cmd.cOpCode, cmd.nOpCode, (int)cmd.x, (int)cmd.y, (int)cmd.z, (int)cmd.fl);
	//send command for execution
	if (cmd.cOpCode == 'G')
	{
		if (cmd.nOpCode == 1 || cmd.nOpCode == 0)
		{
			switch (cmd.fl & 0x07) {
				case (F_HAS_X | F_HAS_Y):
					if (cmd.nOpCode == 1)
					{
						moveDirect_mm(cmd.x, cmd.y);
					}
					else
					{
						move_mm(cmd.x, cmd.y);
					}
					break;
				case (F_HAS_X | F_HAS_Y | F_HAS_Z):
					pen_set((cmd.z < 0) ? 1 : 0);
					if (cmd.nOpCode == 1)
					{
						moveDirect_mm(cmd.x, cmd.y);
					}
					else
					{
						move_mm(cmd.x, cmd.y);
					}
					break;
				case (F_HAS_Z):
					pen_set((cmd.z < 0) ? 1 : 0);
					break;
			}
		} else if (cmd.nOpCode == 28)
		{
			//home
			pen_set(0);
			move(0, 0);
		} else if (cmd.nOpCode == 92)
		{
			//set local coords.
			point p = getPosition(); //machine coordinates by default
			//but if x or y is set:
			if (cmd.fl & F_HAS_X) p.x = cmd.x/LR_STEP_MM;
			if (cmd.fl & F_HAS_Y) p.y = cmd.y/LR_STEP_MM;
			//finally set local
			setLocalPos(p);
		}
	}
}

