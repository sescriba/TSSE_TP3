/**
 ******************************************************************************
 * @file    Drivers/dev/inc/dev_timer.h
 * @author  Santiago Escriba
 * @brief   Header for dev_timer.c
 * 			File with count Timer definition.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DEV_INC_DEV_TIMER_H_
#define DEV_INC_DEV_TIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "types.h"

/* Exposed types -------------------------------------------------------------*/
/**
  * @brief  ttimer_t Timer structure definition
  */
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} ttimer_t;

/* Exposed function prototypes -----------------------------------------------*/
retType DEV_TimerInit(ttimer_t * delay, tick_t duration );
retType DEV_TimerRead(ttimer_t * delay, bool_t * done);
retType DEV_TimerWrite(ttimer_t * delay, tick_t duration );


#endif /* DEV_INC_DEV_TIMER_H_ */
