/**
 ******************************************************************************
 * @file    Drivers/dev/inc/mpu9250.h
 * @author  Santiago Escriba
 * @brief   Header for mpu9250.c
 * 			File with High Level driver for MPU9250.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DEV_INC_MPU9250_H_
#define DEV_INC_MPU9250_H_

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "port.h"

/* Exposed types -------------------------------------------------------------*/
/**
  * @brief  axis_t Axes structure definition
  */
typedef struct{
	float x;
	float y;
	float z;
}axis_t;

/**
  * @brief  MPU9250_t MPU9250 values structure definition
  */
typedef struct{
	axis_t gyro;
	axis_t accl;
	float temp;
}MPU9250_t;

/**
  * @brief  MPU9250Register_t MPU9250 registers structure definition
  */
typedef struct{
	uint8_t addr;
	uint16_t value;
	uint8_t size;
}MPU9250Register_t;

/* Exposed function prototypes -----------------------------------------------*/
retType APP_MPU9250Write(uint8_t addr2write, uint8_t * pdata, uint16_t size);
retType APP_MPU9250Read(uint8_t addr2read, uint8_t * pdata, uint16_t size);
retType APP_MPU9250Init(void);
retType APP_MPU9250ReadGyro(axis_t * gyro);
retType APP_MPU9250ReadAccl(axis_t * accl);
retType APP_MPU9250ReadTemp(float * temp);


#endif /* DEV_INC_MPU9250_H_ */
