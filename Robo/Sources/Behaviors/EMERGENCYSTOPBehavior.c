/*
 * EMERGENCYSTOPBehavior.c
 *
 *  Created on: 05.05.2015
 *      Author: Cyrill
 */

#include "EMERGENCYSTOPBehavior.h"
#include "../../Common/ShellQueue.h"
#include "../../Common/Drive.h"
#include "FRTOS1.h"
#include "../../Common/Accel.h"

static volatile int supressed = 0;
static volatile int active=0;
static volatile int lasEsNotDetectedTIme_MS=0;

int EMERGENCYSTOPTakeControl(void) {
	int16_t x=0;
	int16_t y=0;
	int16_t z=0;
	ACCEL_GetLastValues(&x,&y,&z);

	int currentTimeMS=FRTOS1_xTaskGetTickCount()/portTICK_RATE_MS;
	if(z<0)
	{
		if(lasEsNotDetectedTIme_MS+100<currentTimeMS)
		{
			active=1;
		}
	}
	else{
		lasEsNotDetectedTIme_MS=currentTimeMS;
	}

	return active;
}
void EMERGENCYSTOPSupress(void) {
	supressed = 1;

}

static void Finalize(void) {
	DRV_SetSpeed(0, 0);
}

void EMERGENCYSTOPAction(void) {
	supressed = 0;

	SQUEUE_SendString("Emergency Stop!\r\n");
	DRV_SetSpeed(0, 0);
	while (!supressed && EMERGENCYSTOPTakeControl()) {
			FRTOS1_vTaskDelay(1 / portTICK_RATE_MS);
	}
	Finalize();
}

void EMERGENCYInit(void){
	active=0;
}
