/**
 ******************************************************************************
 * @file    Drivers/dev/inc/port.h
 * @author  Santiago Escriba
 * @brief   Header for port.c
 * 			File with I2C communication.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DEV_INC_PORT_H_
#define DEV_INC_PORT_H_

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "stm32f4xx_hal_i2c.h"

/**
  * @brief  I2CStates_t I2C states enum
  */
typedef enum{
	I2C_OK,
	I2C_BUSY,
}I2CStates_t;

/**
  * @brief  I2CAddrStep_t I2C address states enum
  */
typedef enum{
	I2C_S0,
	I2C_S1,
	I2C_S2,
}I2CAddrStep_t;

/**
  * @brief  I2CState_t I2C states structure
  */
typedef struct{
	I2CAddrStep_t addr_step;
	I2CStates_t api_state;
}I2CState_t;


/* Exposed function prototypes -----------------------------------------------*/
retType DEV_I2CInit(void);
retType DEV_I2CDeInit(void);
retType DEV_I2CWrite(uint16_t slave_addr, uint8_t * pdata, uint16_t size);
retType DEV_I2CRead(uint16_t slave_addr, uint8_t * pdata, uint16_t size);
retType DEV_I2CIsReady(uint16_t slave_addr);


#endif /* DEV_INC_PORT_H_ */
