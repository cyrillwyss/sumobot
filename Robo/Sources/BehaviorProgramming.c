/*
 * BehaviorProgramming.c
 *
 *  Created on: 20.04.2015
 *      Author: Cyrill
 */

#include "BehaviorProgramming.h"
#include "FRTOS1.h"
#include "../../Common/ShellQueue.h"
#include "Behaviors/IDLEBehavior.h"

volatile int arbitratorRunning = 0;
volatile BehaviorT currentBehaviors[MAXBEHAVIORS + 1];
volatile int currentBehaviorCount;
volatile int currentRunningBehavior = 0;
xSemaphoreHandle semaphore;

static portTASK_FUNCTION(Arbitrator, pvParameters) {

	for (;;) {
		if (arbitratorRunning) {
			int validBehaviorFound = 0;
			for (int temp = 0; temp < currentBehaviorCount; temp++) {
				if (currentBehaviors[temp].wantsControl()) {
					validBehaviorFound = temp;
				}
			}

			if (validBehaviorFound > currentRunningBehavior) {
				currentBehaviors[currentRunningBehavior].supress();
			}
			if (currentRunningBehavior != validBehaviorFound) {
				currentRunningBehavior = validBehaviorFound;
				FRTOS1_xSemaphoreGive(semaphore);
			}
		} else {
			currentBehaviors[currentRunningBehavior].supress();
			currentRunningBehavior = 0;
		}

		FRTOS1_vTaskDelay(2 / portTICK_RATE_MS);
	}
}

static portTASK_FUNCTION(BehaviorWorker, pvParameters) {
	for (;;) {
		FRTOS1_xSemaphoreTake(semaphore, 150 / portTICK_RATE_MS);
		currentBehaviors[currentRunningBehavior].action();
	}
}

void BPsetBehaviors(BehaviorT* behaviors, int behaviorCount) {
	currentRunningBehavior = 0;
	if (behaviorCount > MAXBEHAVIORS) {
		SQUEUE_SendString("Error: too many behaviors!");

		for (;;) {
		}
	}
	for (int i = 0; i < behaviorCount; i++) {
		currentBehaviors[i + 1] = behaviors[i];
	}
	currentBehaviorCount = behaviorCount + 1;
}

void BPstartArbitrator(void) {
	currentRunningBehavior = 0;
	int i;
	for (i = 0; i < currentBehaviorCount; i++) {
		currentBehaviors[i].init();
	}
	arbitratorRunning = 1;

}

void BPstopArbitrator(void) {
	arbitratorRunning = 0;
}

void BPinit(void) {

	semaphore = FRTOS1_xSemaphoreCreateMutex();
	if (semaphore == NULL) {
		for (;;) {
		}
	}

	BehaviorT idle = { IDLEInit, IDLEAction, IDLESupress, IDLETakeControl };

	currentBehaviors[0] = idle;

	if (FRTOS1_xTaskCreate(Arbitrator, "Arbi task", configMINIMAL_STACK_SIZE,
			NULL, 5, NULL) != pdPASS) {
		for (;;) {
		}
	}
	if (FRTOS1_xTaskCreate(BehaviorWorker, "BEH work",
			configMINIMAL_STACK_SIZE, NULL, 4, NULL) != pdPASS) {
		for (;;) {
		}
	}

}

void BPdeInit(void) {
	BPstopArbitrator();
}

