/**
 ******************************************************************************
 * @file    Drivers/dev/src/mpu9250.c
 * @author  Santiago Escriba
 * @brief   File with High Level driver for MPU9250.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "mpu9250.h"

/* Private define ------------------------------------------------------------*/

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

//Module scales
#define ACCL_SCALE (16.0*9.81/32768.0)
#define GYRO_SCALE (2000.0/32768.0)

/* Exposed variables ---------------------------------------------------------*/
extern I2CState_t I2C_state;

/* Private function prototypes -----------------------------------------------*/
static retType gyro_convert(uint16_t axis, float * paxis);
static retType accl_convert(uint16_t axis, float * paxis);
static retType temp_convert(uint16_t temp, float * ptemp);

static MPU9250Register_t MPU9250_InitValues[MPU9250_INIT_REGISTERS]= {
		{.addr = MPU9250_PWR_MGMT_1, .value = 0x0, .size = 1},
		{.addr = MPU9250_PWR_MGMT_1, .value = 0x1, .size = 1},
		{.addr = MPU9250_GYRO_CONFIG, .value = 0x18, .size = 1},
		{.addr = MPU9250_CONFIG_AD, .value = 0x7, .size = 1},
		{.addr = MPU9250_ACCEL_CONFIG_1, .value = 0x18, .size = 1},
		{.addr = MPU9250_ACCEL_CONFIG_2, .value = 0x7, .size = 1},
};
static MPU9250Register_t MPU9250_GyroValues[MPU9250_GYRO_ACCL_REGISTERS]= {
		{.addr = MPU9250_GYRO_XOUT_H, .value = 0x0, .size = 2},
		{.addr = MPU9250_GYRO_YOUT_H, .value = 0x0, .size = 2},
		{.addr = MPU9250_GYRO_ZOUT_H, .value = 0x0, .size = 2},
};
static MPU9250Register_t MPU9250_AcclValues[MPU9250_GYRO_ACCL_REGISTERS]= {
		{.addr = MPU9250_ACCEL_XOUT_H, .value = 0x0, .size = 2},
		{.addr = MPU9250_ACCEL_YOUT_H, .value = 0x0, .size = 2},
		{.addr = MPU9250_ACCEL_ZOUT_H, .value = 0x0, .size = 2},
};
/* Exposed Function  ---------------------------------------------------------*/
/**
 * @brief  MPU9250 Write word
 * @param
 * 		addr2write	[I] - MPU Slave address
 * 		pdata 		[I] - Data Buffer
 * 		size 		[I] - Data Buffer size
 * @retval ret - Return API value
 */
retType APP_MPU9250Write(uint8_t addr2write, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(size <= 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	/*
	 *  Write a word on MPU9250 device
	 *  This function returns the API state according to if a complete I2C transaction finished or not.
	 *  That means a register has been written and the peripheral is available to be used again.
	 *
	 *  There are three steps:
	 *  	- Send register address. Check I2C interruption to know if the transaction is ready.
	 *  	- Once IT happened, send data.
	 *  	- Check I2C interruption to know if the transaction is ready.
	 */
	if(I2C_state.api_state != I2C_BUSY && I2C_state.addr_step == I2C_S0){
		ret = DEV_I2CWrite(MPU9250_SLAVEADDR, &addr2write, 1);
		I2C_state.api_state = I2C_BUSY;
		I2C_state.addr_step = I2C_S1;
	}
	if(I2C_state.api_state != I2C_BUSY && I2C_state.addr_step == I2C_S1){
		ret = DEV_I2CWrite(MPU9250_SLAVEADDR, pdata, size);
		I2C_state.api_state = I2C_BUSY;
		I2C_state.addr_step = I2C_S2;
		return API_BUSY;
	}
	if(I2C_state.api_state != I2C_BUSY && I2C_state.addr_step == I2C_S2){
		I2C_state.addr_step = I2C_S0;
		return API_OK;
	}
	return API_BUSY;
}

/**
 * @brief  MPU9250 Read word
 * @param
 * 		addr2read	[I] - MPU Slave address
 * 		pdata 		[O] - Data Buffer
 * 		size 		[I] - Data Buffer size
 * @retval ret - Return API value
 */
retType APP_MPU9250Read(uint8_t addr2read, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(size == 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	/*
	 *  Read a word on MPU9250 device
	 *  This function returns the API state according to if a complete I2C transaction finished or not.
	 *  That means a register has been written and the peripheral is available to be used again.
	 *
	 *  There are three steps:
	 *  	- Send register address. Check I2C interruption to know if the transaction is ready.
	 *  	- Once IT happened, receive data.
	 *  	- Check I2C interruption to know if the transaction is ready.
	 */
	if(I2C_state.api_state != I2C_BUSY && I2C_state.addr_step == I2C_S0){
		ret = DEV_I2CWrite(MPU9250_SLAVEADDR, &addr2read, 1);
		I2C_state.api_state = I2C_BUSY;
		I2C_state.addr_step = I2C_S1;
	}
	if(I2C_state.api_state != I2C_BUSY && I2C_state.addr_step == I2C_S1){
		ret = DEV_I2CRead(MPU9250_SLAVEADDR, pdata, size);
		I2C_state.api_state = I2C_BUSY;
		I2C_state.addr_step = I2C_S2;
		return API_BUSY;
	}
	if(I2C_state.api_state != I2C_BUSY && I2C_state.addr_step == I2C_S2){
		I2C_state.addr_step = I2C_S0;
		return API_OK;
	}
	return API_BUSY;

}

/**
 * @brief  MPU9250 Initializer function
 * @param
 * 		void
 * @retval ret - Return API value
 */
retType APP_MPU9250Init(void){

	retType ret = API_OK;
	uint8_t i = 0;

	//Check if MPU communication via I2C is ready
	ret |= DEV_I2CIsReady(MPU9250_SLAVEADDR);
	if(ret != API_OK) return ret;
	//Set MPU configuration
	//General configuration: CLKSEL

	for(i=0; i < MPU9250_INIT_REGISTERS; i++){
		do{
		ret = APP_MPU9250Write(MPU9250_InitValues[i].addr, (uint8_t*)&MPU9250_InitValues[i].value, MPU9250_InitValues[i].size);
		}while(ret == API_BUSY && (I2C_state.api_state == I2C_BUSY || I2C_state.addr_step == I2C_S1));
	}
	return ret;

}

/**
 * @brief  MPU9250 Read Gyroscope value per Axis
 * @param
 * 		gyro [O] - Gyroscope structure with axes
 * @retval ret - Return API value
 */
retType APP_MPU9250ReadGyro(axis_t * gyro){

	retType ret = API_OK;
	uint8_t i = 0;
	uint16_t aux = 0;

	//Read Gyroscope values for Axes X, Y and Z
	for(i=0; i < MPU9250_GYRO_ACCL_REGISTERS; i++){
		do{
		ret = APP_MPU9250Read(MPU9250_GyroValues[i].addr, (uint8_t*)&aux, MPU9250_GyroValues[i].size);
		}while(ret == API_BUSY && (I2C_state.api_state == I2C_BUSY || I2C_state.addr_step == I2C_S1));
		MPU9250_GyroValues[i].value = aux;
	}

	//Convert to human scale Gyroscope values for Axes X, Y and Z
	ret = gyro_convert(MPU9250_GyroValues[0].value, &(gyro->x));
	ret |= gyro_convert(MPU9250_GyroValues[1].value, &(gyro->y));
	ret |= gyro_convert(MPU9250_GyroValues[2].value, &(gyro->z));
	return ret;
}

/**
 * @brief  MPU9250 Read Accelerometer value per Axis
 * @param
 * 		accl [O] - Accelerometer structure with axes
 * @retval ret - Return API value
 */
retType APP_MPU9250ReadAccl(axis_t * accl){

	retType ret = API_OK;
	uint8_t i = 0;
	uint16_t aux = 0;

	//Read Accelerometer values for Axes X, Y and Z
	for(i=0; i < MPU9250_GYRO_ACCL_REGISTERS; i++){
		do{
		ret = APP_MPU9250Read(MPU9250_AcclValues[i].addr, (uint8_t*)&aux, MPU9250_AcclValues[i].size);
		}while(ret == API_BUSY && (I2C_state.api_state == I2C_BUSY || I2C_state.addr_step == I2C_S1));
		MPU9250_AcclValues[i].value = aux;
	}

	//Convert to human scale Accelerometer values for Axes X, Y and Z
	ret = accl_convert(MPU9250_AcclValues[0].value, &(accl->x));
	ret |= accl_convert(MPU9250_AcclValues[1].value, &(accl->y));
	ret |= accl_convert(MPU9250_AcclValues[2].value, &(accl->z));
	return ret;
}

/**
 * @brief  MPU9250 Read Temperature value
 * @param
 * 		temp [O] - Temperature value
 * @retval ret - Return API value
 */
retType APP_MPU9250ReadTemp(float * temp){

	retType ret = API_OK;
	uint16_t aux_temp = 0;

	//Read Temperature value
	do{
		ret = APP_MPU9250Read(MPU9250_TEMP_OUT_H, (uint8_t*)&aux_temp, 2);
	} while(ret == API_BUSY &&(I2C_state.api_state == I2C_BUSY || I2C_state.addr_step == I2C_S1));


	//Convert to human scale Temperature value
	ret = temp_convert(aux_temp, temp);
	return ret;
}

/**
 * @brief  MPU9250 Gyroscope convert value (Intern function)
 * @param
 * 		axis  [I] - Axis value to convert
 * 		paxis [O] - Value converted
 * @retval ret - Return API value
 */
static retType gyro_convert(uint16_t axis, float * paxis){

	retType ret = API_OK;
	uint8_t aux = 0;

	//Fix big/little endian
	aux = (axis&(0xff00))>>8;
	axis = (axis&0x00ff)<<8;
	axis |= aux;
	*paxis = axis*GYRO_SCALE;
	return ret;
}

/**
 * @brief  MPU9250 Accelerometer convert value (Intern function)
 * @param
 * 		axis  [I] - Axis value to convert
 * 		paxis [O] - Value converted
 * @retval ret - Return API value
 */
static retType accl_convert(uint16_t axis, float * paxis){

	retType ret = API_OK;
	uint8_t aux = 0;

	//Fix big/little endian
	aux = (axis&(0xff00))>>8;
	axis = (axis&0x00ff)<<8;
	axis |= aux;
	*paxis = axis*ACCL_SCALE;
	return ret;
}

/**
 * @brief  MPU9250 Temperature convert value (Intern function)
 * @param
 * 		temp  [I] - Temperature value to convert
 * 		ptemp [O] - Value converted
 * @retval ret - Return API value
 */
static retType temp_convert(uint16_t temp, float * ptemp){

	retType ret = API_OK;
	uint8_t aux = 0;

	//Fix big/little endian
	aux = (temp&(0xff00))>>8;
	temp = (temp&0x00ff)<<8;
	temp |= aux;

	//Apply scale and conversion to °C
	*ptemp = (temp - 0.0)/321.0 + 21.0;
	return ret;
}
