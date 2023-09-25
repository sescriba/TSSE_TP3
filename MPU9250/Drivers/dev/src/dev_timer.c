/**
 ******************************************************************************
 * @file    Drivers/dev/src/dev_timer.c
 * @author  Santiago Escriba
 * @brief   File with count Timer definition.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "dev_timer.h"

/* Private define ------------------------------------------------------------*/
#define MAX_DELAY 30000

/* Exposed Function  ---------------------------------------------------------*/
/**
 * @brief  Timer Initialization
 * @param
 * 		timer		[I] - Timer definition
 * 		duration 	[I] - Duration of counter
 * @retval ret - Return API value
 */
retType DEV_TimerInit(ttimer_t * timer, tick_t duration){

	retType ret = API_OK;

	if(timer == 0 || duration <= 0 || duration > MAX_DELAY) return API_ERROR;
	//Initialize Timer variables
	timer->startTime = 0;
	timer->duration = duration;
	timer->running = false;
	return ret;
}

/**
 * @brief  Timer Counter
 * @param
 * 		timer		[I] - Timer definition
 * 		done	 	[O] - Time expired
 * @retval ret - Return API value
 */
retType DEV_TimerRead(ttimer_t * timer, bool_t * done){

	retType ret = API_OK;
	uint32_t time = 0;

	if(timer->running == false){	//Initialization check
		timer->startTime = HAL_GetTick();
		timer->running = true;
	}
	else{
		time = HAL_GetTick() - (timer->startTime);		//Get difference
		if(time >= timer->duration){		//Time control
			timer->running = false;
			*done = true;
			return ret;
		}
	}
	*done = false;
	return ret;
}

/**
 * @brief  Timer Reassignation
 * @param
 * 		timer		[I] - Timer definition
 * 		duration 	[I] - Duration of counter
 * @retval ret - Return API value
 */
retType DEV_TimerWrite(ttimer_t * timer, tick_t duration){

	retType ret = API_OK;

	if(duration <= 0 || duration > MAX_DELAY) return API_ERROR;
	//Rewrite duration value
	timer->duration = duration;
	return ret;
}
