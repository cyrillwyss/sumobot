/*
 * REMOTEBehavior.c
 *
 *  Created on: 05.05.2015
 *      Author: Cyrill
 */

#include "REMOTEBehavior.h"
#include "../../Common/ShellQueue.h"
#include "../../Common/Drive.h"
#include "FRTOS1.h"
#include "../../Common/RNETMessageHandler.h"
#include "../../Common/Reflectance.h"
#include "../../Common/Pid.h"

static volatile int supressed = 0;

#define MAXSPEED 8000
#define CALCFACTOR (MAXSPEED/128)

int REMOTETakeControl(void) {
	return RNETMH_getEnabled();
}
void REMOTESupress(void) {
	supressed = 1;
}

void REMOTEInit(void) {

}

static void Finalize(void) {
	DRV_SetSpeed(0, 0);
	//REF_setLatchStatus(1);
}

void REMOTEAction(void) {
	supressed = 0;

//	REF_setLatchStatus(0);
	SQUEUE_SendString("Remote Control Enabled...\r\n");
	while (!supressed && REMOTETakeControl()) {

		int speed = RNETMH_getSPeedVal();
		int steering = RNETMH_getSteeringVal()/3;

		int leftMotor = speed + steering;
		int rightMotor = speed - steering;
		leftMotor = CALCFACTOR * leftMotor;
		rightMotor = CALCFACTOR * rightMotor;


		DRV_SetSpeed(leftMotor, rightMotor);

		FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}
	Finalize();
}

