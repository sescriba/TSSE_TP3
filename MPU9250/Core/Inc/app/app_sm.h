/**
 ******************************************************************************
 * @file    Core/Inc/app/app_sm.h
 * @author  Santiago Escriba
 * @brief   Header for app_sm.c
 * 			File with State Machine definition.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_APP_SM_H_
#define INC_APP_SM_H_

/* Includes ------------------------------------------------------------------*/
#include "mpu9250.h"
#include "dev_uart.h"
#include "port.h"
#include "string.h"
#include "dev_timer.h"
#include "types.h"
#include <stdlib.h>
#include <math.h>

/* Exposed types -------------------------------------------------------------*/
/**
  * @brief  State_t States of the SM Enum definition
  */
typedef enum{
	SM_INIT,
	SM_READGYRO,
	SM_READACCL,
	SM_READTEMP,
	SM_PRINT,
	SM_IDLE,
	SM_ERROR,
} State_t;

/* Exposed function prototypes -----------------------------------------------*/
retType APP_SMInit(void);
retType APP_SMProccess(void);


#endif /* INC_APP_SM_H_ */
