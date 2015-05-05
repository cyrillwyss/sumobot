/*
 * Platform.c
 *
 *  Created on: 02.03.2015
 *      Author: tastyger
 */

#include "Platform.h"
#include "LED.h"
#include "Mealy.h"
#include "Keys.h"
#include "Event.h"
#include "Trigger.h"
#include "Buzzer.h"
#include "RTOS.h"
#include "Shell.h"
#include "ShellQueue.h"
#include "Reflectance.h"
#include "Motor.h"
#include "MCP4728.h"
#include "QuadCalib.h"
#if PL_HAS_MOTOR_QUAD
#include "Q4CLeft.h"
#include "Q4CRight.h"
#endif
#if PL_HAS_MOTOR_TACHO
#include "Tacho.h"
#endif
#if PL_HAS_PID
#include "Pid.h"
#endif
#if PL_HAS_DRIVE
#include "Drive.h"
#endif
#if PL_HAS_ULTRASONIC
#include "Ultrasonic.h"
#endif
#if PL_HAS_ACCEL
#include "Accel.h"
#endif

void PL_Init(void) {
#if PL_HAS_MEALY
	MEALY_Init();
#endif
#if PL_HAS_LED
	LED_Init();
#endif

#if PL_HAS_EVENTS
	EVNT_Init();
#endif

#if PL_HAS_KEYS
	KEY_Init();
#endif

#if PL_HAS_TRIGGER
	TRG_Init();
#endif
#if PL_HAS_BUZZER
	BUZ_Init();
#endif
#if PL_HAS_RTOS
	RTOS_Init();
#endif
#if PL_HAS_SHELL_QUEUE
	SQUEUE_Init();
#endif
#if	PL_HAS_SHELL
	SHELL_Init();
#endif
#if PL_HAS_LINE_SENSOR
	REF_Init();
#endif
#if PL_HAS_MOTOR
	MOT_Init();
#endif
#if PL_HAS_MCP4728
	MCP4728_Init();
#endif
#if PL_HAS_MOTOR_QUAD
Q4CLeft_Init();
Q4CRight_Init();
#endif
#if PL_HAS_MOTOR_TACHO
TACHO_Init();
#endif
#if PL_HAS_PID
PID_Init();
#endif
#if PL_HAS_DRIVE
DRV_Init();
#endif
#if PL_HAS_ULTRASONIC
US_Init();
#endif
#if PL_HAS_ACCEL
ACCEL_Init();
#endif
}

void PL_Deinit(void) {

#if PL_HAS_MEALY
	MEALY_Deinit();
#endif
#if PL_HAS_LED
	LED_Deinit();
#endif

#if PL_HAS_EVENTS
	EVNT_Deinit();
#endif

#if PL_HAS_KEYS
	KEY_Deinit();
#endif

#if PL_HAS_TRIGGER
	TRG_Deinit();
#endif

#if PL_HAS_BUZZER
	BUZ_Deinit();
#endif

#if PL_HAS_RTOS
	RTOS_Deinit();
#endif

#if	PL_HAS_SHELL
	SHELL_Deinit();
#endif
#if PL_HAS_SHELL_QUEUE
	SQUEUE_Deinit();
#endif
#if PL_HAS_LINE_SENSOR
	REF_Deinit();
#endif
#if PL_HAS_MOTOR
	MOT_Deinit();
#endif
#if PL_HAS_MCP4728
	MCP4728_Deinit();
#endif
#if PL_HAS_MOTOR_QUAD
Q4CLeft_Deinit();
Q4CRight_Deinit();
#endif
#if PL_HAS_MOTOR_TACHO
TACHO_Deinit();
#endif
#if PL_HAS_PID
PID_Deinit();
#endif

#if PL_HAS_DRIVE
DRV_Deinit();
#endif
#if PL_HAS_ULTRASONIC
US_Deinit();
#endif
#if PL_HAS_ACCEL
ACCEL_Deinit();
#endif
}
