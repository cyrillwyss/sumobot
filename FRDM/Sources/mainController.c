/*
 * mainController.c
 *
 *  Created on: 24.02.2015
 *      Author: Cyrill
 */

#include "mainController.h"
#include "WAIT1.h"
#include "../../Common/Led.h"

void hallo(void (*fct)(void)){
	fct();
}

void mainController_run(void) {

	hallo(25);

	int a = 0;
	LED_Init();
	while (1) {
		switch (a) {
		case 0:
			LED1_On();
			LED2_On();
			LED3_On();
			break;
		case 1:
			LED1_Off();
			LED2_On();
			LED3_On();
			break;
		case 2:
			LED1_On();
			LED2_Off();
			LED3_On();
			break;
		case 3:
			LED1_On();
			LED2_On();
			LED3_Off();
			break;
		case 4:
			LED1_Off();
			LED2_Off();
			LED3_On();
			break;
		case 5:
			LED1_On();
			LED2_Off();
			LED3_Off();
			break;
		case 6:
			LED1_Off();
			LED2_On();
			LED3_Off();
			break;
		case 7:
			LED1_Off();
			LED2_Off();
			LED3_Off();
			break;
		}
		WAIT1_Waitms(200);
		a++;
		if (a == 7) {
			a = 0;
		}
	}
}

