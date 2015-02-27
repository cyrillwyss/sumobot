/*
 * mainController.c
 *
 *  Created on: 24.02.2015
 *      Author: Cyrill
 */

#include "mainController.h"
#include "LED_Green.h"
#include "LED_Red.h"
#include "LED_Blue.h"
#include "WAIT1.h"


void mainController_run(void){
	int a=0;

	while(1){
		switch(a) {
			case 0:
				LED_Red_PutVal(0);
				LED_Green_PutVal(0);
				LED_Blue_PutVal(0);
				break;
			case 1:
				LED_Red_PutVal(0);
				LED_Green_PutVal(1);
				LED_Blue_PutVal(1);
				break;
			case 2:
				LED_Red_PutVal(0);
				LED_Green_PutVal(0);
				LED_Blue_PutVal(1);
				break;
			case 3:
				LED_Red_PutVal(1);
				LED_Green_PutVal(0);
				LED_Blue_PutVal(1);
				break;
			case 4:
				LED_Red_PutVal(1);
				LED_Green_PutVal(0);
				LED_Blue_PutVal(0);
				break;
			case 5:
				LED_Red_PutVal(1);
				LED_Green_PutVal(1);
				LED_Blue_PutVal(0);
				break;
			case 6:
				LED_Red_PutVal(0);
				LED_Green_PutVal(1);
				LED_Blue_PutVal(0);
				break;
			case 7:
				LED_Red_PutVal(1);
				LED_Green_PutVal(1);
				LED_Blue_PutVal(1);
				break;
		}
		WAIT1_Waitms(200);
		a++;
		if (a == 7){
			a=0;
		}
	}
}


