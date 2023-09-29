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

//MPU9250 Register set
#define MPU9250_SLAVEADDR 0xD0 //(0x68<<0x1)
#define MPU9250_PWR_MGMT_1 0x6B
#define MPU9250_CONFIG_AD 0x1A
#define MPU9250_GYRO_CONFIG 0x1B
#define MPU9250_ACCEL_CONFIG_1 0x1C
#define MPU9250_ACCEL_CONFIG_2 0x1D
#define MPU9250_ACCEL_XOUT_H 0x3B
#define MPU9250_ACCEL_XOUT_L 0x3C
#define MPU9250_ACCEL_YOUT_H 0x3D
#define MPU9250_ACCEL_YOUT_L 0x3E
#define MPU9250_ACCEL_ZOUT_H 0x3F
#define MPU9250_ACCEL_ZOUT_L 0x40
#define MPU9250_TEMP_OUT_H 0x41
#define MPU9250_TEMP_OUT_L 0x42
#define MPU9250_GYRO_XOUT_H 0x43
#define MPU9250_GYRO_XOUT_L 0x44
#define MPU9250_GYRO_YOUT_H 0x45
#define MPU9250_GYRO_YOUT_L 0x46
#define MPU9250_GYRO_ZOUT_H 0x47
#define MPU9250_GYRO_ZOUT_L 0x48
#define MPU9250_INIT_REGISTERS 6
#define MPU9250_GYRO_ACCL_REGISTERS 3

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
