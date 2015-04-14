/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"


static xSemaphoreHandle MySem = NULL;


static portTASK_FUNCTION(vSlaveTask, pvParameters) {
  for(;;) {

	  if(xSemaphoreTake(MySem,50)==pdTRUE) {
		  LED3_Neg();
	  }
  }
}

static portTASK_FUNCTION(vMasterTask, pvParameters) {
  for(;;) {
    FRTOS1_vTaskDelay(500 / portTICK_RATE_MS);
        xSemaphoreGive(MySem);
  }
}

void SEM_Deinit(void) {
  /* nothing */
}

/*! \brief Initializes module */
void SEM_Init(void) {
  if (FRTOS1_xTaskCreate(vMasterTask, "Master", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  if (FRTOS1_xTaskCreate(vSlaveTask, "SLAVE", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }

  vSemaphoreCreateBinary(MySem);
  if (MySem == NULL) {
   for(;;); /* creation failed */
  }

}
#endif /* PL_HAS_SEMAPHORE */
