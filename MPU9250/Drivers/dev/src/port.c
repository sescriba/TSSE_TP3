/**
 ******************************************************************************
 * @file    Drivers/dev/src/port.c
 * @author  Santiago Escriba
 * @brief   File with I2C communication.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "port.h"

/* Private define ------------------------------------------------------------*/
#define I2C_CLOCKSPEED 100000
#define I2C_OWNADDRESS1 0
#define I2C_TIMEOUT 0xFFFF

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef  hi2c;
I2CState_t I2C_state;
/* Exposed Function  ---------------------------------------------------------*/
/**
 * @brief  I2C Initialization
 * @param
 * 		void
 * @retval ret - Return API value
 */
retType DEV_I2CInit(void){

	//Define I2C variable configuration
	retType ret = API_OK;
	hi2c.Instance = I2C2;
	hi2c.Init.ClockSpeed = I2C_CLOCKSPEED;
	hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c.Init.OwnAddress1 = I2C_OWNADDRESS1;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	//Set configuration and initialize
	ret |= HAL_I2C_Init(&hi2c);
	I2C_state.api_state = I2C_OK;
	I2C_state.addr_step = I2C_S0;
	return ret;

}

/**
 * @brief  I2C Deinitialization
 * @param
 * 		void
 * @retval ret - Return API value
 */
retType DEV_I2CDeInit(void){

	retType ret = API_OK;

	//Deinitialize I2C communication
	ret |= HAL_I2C_DeInit(&hi2c);
	return ret;
}

/**
 * @brief  I2C Write word
 * @param
 * 		slave_addr	[I] - I2C device Slave address
 * 		pdata 		[I] - Data Buffer
 * 		size 		[I] - Data Buffer size
 * @retval ret - Return API value
 */
retType DEV_I2CWrite(uint16_t slave_addr, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(slave_addr == 0 || size == 0) return API_ERROR;
	//Send a word via I2C
	ret |= HAL_I2C_Master_Transmit_IT(&hi2c, slave_addr, pdata, size);
	if(ret != API_OK) return ret;
	return ret;
}

/**
 * @brief  I2C Read word
 * @param
 * 		slave_addr	[I] - I2C device Slave address
 * 		pdata 		[O] - Data Buffer
 * 		size 		[I] - Data Buffer size
 * @retval ret - Return API value
 */
retType DEV_I2CRead(uint16_t slave_addr, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(slave_addr == 0 || size == 0) return API_ERROR;
	//Receive a word via I2C
	ret |= HAL_I2C_Master_Receive_IT(&hi2c, slave_addr, pdata, size);
	if(ret != API_OK) return ret;
	return ret;
}

/**
 * @brief  I2C Checker if communication is ready
 * @param
 * 		slave_addr	[I] - I2C device Slave address
 * @retval ret - Return API value
 */
retType DEV_I2CIsReady(uint16_t slave_addr){

	retType ret = API_OK;

	if(slave_addr==0) return API_ERROR;
	//Check if I2C communication is ready
	ret = HAL_I2C_IsDeviceReady(&hi2c, slave_addr, 2, 1000);
	return ret;
}
