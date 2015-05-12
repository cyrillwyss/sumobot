/*
 * FORWARDbehavior.c
 *
 *  Created on: 21.04.2015
 *      Author: Cyrill
 */

#include "FORWARDbehavior.h"
#include "FRTOS1.h"
#include "../../Common/Drive.h"

static volatile int supressed = 0;

int FORWARDTakeControl() {
	return 1;
}
void FORWARDSupress() {
	supressed = 1;
}

void FORWARDInit(void){

}

void FORWARDAction() {
	supressed = 0;


	DRV_SetSpeed(2000,2000);

	while (!supressed) {
		FRTOS1_taskYIELD();
	}
	DRV_SetSpeed(0,0);
}
