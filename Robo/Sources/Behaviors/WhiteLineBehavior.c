/*
 * WhiteLineBehavior.c
 *
 *  Created on: 21.04.2015
 *      Author: Cyrill
 */

#include "WhiteLineBehavior.h"
#include "../../Common/Reflectance.h"
#include "../../Common/Motor.h"
#include "FRTOS1.h"

static volatile int supressed = 0;

int WHITELINETakeControl() {
	return REF_GetLineValue() > 0;
}
void WHITELINESupress() {
	supressed = 1;

}

void Finalize() {
	MOT_MotorDevice* leftMotor = MOT_GetMotorHandle(MOT_MOTOR_LEFT);
	MOT_MotorDevice* rightMotor = MOT_GetMotorHandle(MOT_MOTOR_RIGHT);

	MOT_SetSpeedPercent(leftMotor, 0);
	MOT_SetSpeedPercent(rightMotor, 0);
}

void WHITELINEAction() {
	supressed = 0;
	int counter = 0;
	MOT_MotorDevice* leftMotor = MOT_GetMotorHandle(MOT_MOTOR_LEFT);
	MOT_MotorDevice* rightMotor = MOT_GetMotorHandle(MOT_MOTOR_RIGHT);

	MOT_SetSpeedPercent(leftMotor, -20);
	MOT_SetSpeedPercent(rightMotor, -20);
	for (counter = 0; counter < 1000; counter++) {
		if (supressed) {
			Finalize();
			return;
		}
		FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}

	MOT_SetSpeedPercent(leftMotor, 20);
	MOT_SetSpeedPercent(rightMotor, -20);

	for (counter = 0; counter < 1000; counter++) {
		if (supressed) {
			Finalize();
			return;
		}
		FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}
	Finalize();
}
