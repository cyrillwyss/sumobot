/*
 * mainController.c
 *
 *  Created on: 24.02.2015
 *      Author: Cyrill
 */

#include "mainController.h"
#include "LED_Green.h"
#include "WAIT1.h"


void mainController_run(void){

	while(1){
		LED_Green_NegVal();
		WAIT1_Waitms(500);
	}

}


