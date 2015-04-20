/*
 * BehaviorProgramming.c
 *
 *  Created on: 20.04.2015
 *      Author: Cyrill
 */

#include "BehaviorProgramming.h"
#include "FRTOS1.h"

int arbitratorRunning = 0;
BehaviorT* currentBehaviors;
int currentBehaviorCount;
int currentRunningBehavior=-1;

static portTASK_FUNCTION(Arbitrator, pvParameters) {

	int temp;
	int validBehaviorFound;
	for (;;) {
		if (arbitratorRunning) {
			validBehaviorFound=0;
			for(temp=currentBehaviors>-1?currentBehaviors:0;temp<currentBehaviorCount;temp++)
			{

			}
			if(!validBehaviorFound)
			{
				currentRunningBehavior=-1;
			}
		}

		FRTOS1_vTaskDelay(20 / portTICK_RATE_MS);
	}
}

static portTASK_FUNCTION(BehaviorWorker, pvParameters) {
	for (;;) {
			if(currentRunningBehavior>-1)
			{
				currentBehaviors[currentRunningBehavior].action();
			}
	}
}

void setBehaviors(BehaviorT* behaviors, int behaviorCount) {
	currentBehaviors = behaviors;
	currentBehaviorCount = behaviorCount;
}

void startArbitrator(void) {
	arbitratorRunning = 1;
}

void stopArbitrator(void) {
	arbitratorRunning = 0;
}

void init(void) {

	if (FRTOS1_xTaskCreate(Arbitrator, "Arbi task", configMINIMAL_STACK_SIZE,
			NULL, 1, NULL) != pdPASS) {
		for (;;) {
		}
	}
	if (FRTOS1_xTaskCreate(BehaviorWorker, "BehaviorWorker task",
			configMINIMAL_STACK_SIZE, NULL, 0, NULL) != pdPASS) {
		for (;;) {
		}
	}

}

void deInit(void) {
stopArbitrator();
}

