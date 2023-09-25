/**
 ******************************************************************************
 * @file    Drivers/dev/inc/dev_uart.h
 * @author  Santiago Escriba
 * @brief   Header for dev_uart.c
 * 			File with UART communication.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DEV_INC_DEV_UART_H_
#define DEV_INC_DEV_UART_H_

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "stm32f4xx_hal_uart.h"

/* Exposed function prototypes -----------------------------------------------*/
retType DEV_UARTInit(void);
retType DEV_UARTSendChar(uint8_t * pstring);
retType DEV_UARTSendStringSize(uint8_t * pstring, uint16_t size);
retType DEV_UARTReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif /* DEV_INC_DEV_UART_H_ */
