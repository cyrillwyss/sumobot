/*
 * WhiteLineBehavior.c
 *
 *  Created on: 21.04.2015
 *      Author: Cyrill
 */

#include "WhiteLineBehavior.h"
#include "../../Common/Reflectance.h"
#include "../../Common/Motor.h"




int WHITELINETakeControl()
{
	return REF_GetLineValue()>0;
}
void WHITELINESupress(){

}

void WHITELINEAction(){
	MOT_MotorDevice* leftMotor=MOT_GetMotorHandle(MOT_MOTOR_LEFT);
	MOT_MotorDevice* rightMotor=MOT_GetMotorHandle(MOT_MOTOR_RIGHT);

	MOT_SetSpeedPercent(leftMotor,0);
	MOT_SetSpeedPercent(rightMotor,0);

}
