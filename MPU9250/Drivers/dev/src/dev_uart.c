/**
 ******************************************************************************
 * @file    Drivers/dev/src/dev_uart.c
 * @author  Santiago Escriba
 * @brief   File with UART communication.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "dev_uart.h"

/* Private define ------------------------------------------------------------*/
#define USARTx 					USART3
#define UART_BAUDRATE 			9600
#define UART_HWFLOWCTL 			UART_HWCONTROL_NONE
#define UART_MODE 				UART_MODE_TX_RX
#define UART_OVERSAMPLING 		UART_OVERSAMPLING_16
#define UART_PARITY 			UART_PARITY_ODD
#define UART_STOPBITS 			UART_STOPBITS_1
#define UART_WORDLENGTH 		UART_WORDLENGTH_8B
#define TIME_OUT 				0xFFFF

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart;

/* Exposed Function  ---------------------------------------------------------*/
/**
 * @brief  UART Write a Char
 * @param
 * 		pstring		[I] - Data Buffer
 * @retval ret - Return API value
 */
retType DEV_UARTSendChar(uint8_t * pstring){

	retType ret = API_OK;

	//Send a char via UART
	ret |= HAL_UART_Transmit(&huart, pstring, 1, TIME_OUT);

	return ret;
}

/**
 * @brief  UART Write a String
 * @param
 * 		pstring		[I] - Data Buffer
 * 		size 		[I] - Data Buffer size
 * @retval ret - Return API value
 */
retType DEV_UARTSendStringSize(uint8_t * pstring, uint16_t size){

	retType ret = API_OK;

	if(size == 0) return API_ERROR;
	//Send a word via UART
	ret |= HAL_UART_Transmit(&huart, pstring, size, TIME_OUT);

	return ret;
}

/**
 * @brief  UART Read a String
 * @param
 * 		pstring		[O] - Data Buffer
 * 		size 		[I] - Data Buffer size
 * @retval ret - Return API value
 */
retType DEV_UARTReceiveStringSize(uint8_t * pstring, uint16_t size){

	retType ret = API_OK;

	if(size == 0) return API_ERROR;
	//Receive a word via UART
	ret |= HAL_UART_Receive(&huart, pstring, size, TIME_OUT);

	return ret;
}

/**
 * @brief  UART Initializer function
 * @param
 * 		void
 * @retval ret - Return API value
 */
retType DEV_UARTInit(void){

	retType ret = API_OK;
	uint8_t str[] = "UART INITIALIZED:\n";

	//Define UART variable configuration
	huart.Instance = USARTx;
	huart.Init.BaudRate= UART_BAUDRATE;
	huart.Init.HwFlowCtl = UART_HWFLOWCTL;
	huart.Init.Mode = UART_MODE;
	huart.Init.OverSampling = UART_OVERSAMPLING;
	huart.Init.Parity = UART_PARITY;
	huart.Init.StopBits = UART_STOPBITS;
	huart.Init.WordLength = UART_WORDLENGTH;

	//Set configuration and initialize
	ret |= HAL_UART_Init(&huart);
	if(ret != API_OK) return ret;
	//Print a little msg with UART state
	else DEV_UARTSendStringSize(str, sizeof(str));
	return ret;
}
