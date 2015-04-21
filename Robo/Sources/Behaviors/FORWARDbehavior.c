/*
 * FORWARDbehavior.c
 *
 *  Created on: 21.04.2015
 *      Author: Cyrill
 */


#include "FORWARDbehavior.h"
#include "../../Common/Motor.h"


int FORWARDTakeControl(){
	return 1;
}
void FORWARDSupress(){

}

void FORWARDAction(){
	MOT_MotorDevice* leftMotor=MOT_GetMotorHandle(MOT_MOTOR_LEFT);
	MOT_MotorDevice* rightMotor=MOT_GetMotorHandle(MOT_MOTOR_RIGHT);

	MOT_SetSpeedPercent(leftMotor,20);
	MOT_SetSpeedPercent(rightMotor,20);
}
