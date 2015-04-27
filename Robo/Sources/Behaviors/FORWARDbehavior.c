/*
 * FORWARDbehavior.c
 *
 *  Created on: 21.04.2015
 *      Author: Cyrill
 */

#include "FORWARDbehavior.h"
#include "../../Common/Motor.h"
#include "FRTOS1.h"

static volatile int supressed = 0;

int FORWARDTakeControl() {
	return 1;
}
void FORWARDSupress() {
	supressed = 1;
}

void FORWARDAction() {
	supressed = 0;
	MOT_MotorDevice* leftMotor = MOT_GetMotorHandle(MOT_MOTOR_LEFT);
	MOT_MotorDevice* rightMotor = MOT_GetMotorHandle(MOT_MOTOR_RIGHT);

	MOT_SetSpeedPercent(leftMotor,20);
	MOT_SetSpeedPercent(rightMotor, 20);
	while (!supressed) {
		FRTOS1_taskYIELD();
	}
	MOT_SetSpeedPercent(leftMotor, 0);
	MOT_SetSpeedPercent(rightMotor, 0);
}
