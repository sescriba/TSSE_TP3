/**
 ******************************************************************************
 * @file     Core/Src/app/app_sm.c
 * @author  Santiago Escriba
 * @brief   File with State Machine definition.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "app_sm.h"

/* Private define ------------------------------------------------------------*/
#define READ_TIME 1000

/* Private variables ---------------------------------------------------------*/
static State_t states;
static State_t new_state;
static MPU9250_t read_buff;
static ttimer_t idle;

/* Private function prototypes -----------------------------------------------*/
static retType print_string(MPU9250_t * data);
static void ftoa(float value, char_t * str);

/* Exposed Function  ---------------------------------------------------------*/
/**
 * @brief  SM Initialization
 * @param
 * 		void
 * @retval ret - Return API value
 */
retType APP_SMInit(void){

	retType ret = API_OK;

	//Initialize State Machine
	states = SM_INIT;
	//Set a timer to allow read values from device
	ret |= DEV_TimerInit(&idle, READ_TIME);
	return ret;
}

/**
 * @brief  SM Set and work according current state
 * @param
 * 		void
 * @retval ret - Return API value
 */
retType APP_SMProccess(void){

	retType ret = API_OK;
	bool_t done = false;

	switch(states){
		/*
		 * Initialization state: initialize UART and I2C communication and MPU9250
		 * After a case is ready, the SM will go to IDLE state just to wait or do other things
		 * To exit from IDLE state, have to expire a timer. Then the next state will be set
		 */
		case SM_INIT:
			ret |= DEV_UARTInit();
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			ret |= DEV_I2CInit();
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			ret |= APP_MPU9250Init();
			if(ret == API_OK){
				//Set next state to read/print information from MPU9250
				new_state = SM_READGYRO;
				//But first it will go to IDLE state, to wait or do other things
				states = SM_IDLE;
			}
			else{
				states = SM_ERROR;
				break;
			}
			break;
		//Gyroscope State: Read Gyroscope values
		case SM_READGYRO:
			ret |= APP_MPU9250ReadGyro(&read_buff.gyro);
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			new_state = SM_READACCL;
			states = SM_IDLE;
			break;
		//Accelerometer State: Read Accelerometer values
		case SM_READACCL:
			ret |= APP_MPU9250ReadAccl(&read_buff.accl);
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			new_state = SM_READTEMP;
			states = SM_IDLE;
			break;
		//Temperature State: Read Temperature value
		case SM_READTEMP:
			ret |= APP_MPU9250ReadTemp(&read_buff.temp);
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			new_state = SM_PRINT;
			states = SM_IDLE;
			break;
		//Print state: print a text via UART with values
		case SM_PRINT:
			ret |= print_string(&read_buff);
			if(ret == API_OK){
				new_state = SM_READGYRO;
				states = SM_IDLE;
			}
			break;
		//Idle state: we can do anything here
		case SM_IDLE:
			//Check read time
			ret |= DEV_TimerRead(&idle, &done);
			if(done == true){
				states = new_state;
			}
			break;
		//Error state: return error
		case SM_ERROR:
		default:
			ret = API_ERROR;
			break;
	}
	return ret;
}

/**
 * @brief  Print a string with MPU9250 information via UART
 * @param
 * 		data	[I] - MPU9250 Data to print
 * @retval ret - Return API value
 */
static retType print_string(MPU9250_t * data){

	retType ret = API_OK;
	uint8_t buff[256] = {0};
	char_t value[8] = {0};
	char_t str[] = "Data returned: ";
	char_t str_gyro[] = "\nGyroscope [°/s]: ";
	char_t str_accl[] = "\nAccelerometer [g]: ";
	char_t str_temp[] = "\nTemperature [°C]: ";
	char_t str_x[] = "\nAxis X: ";
	char_t str_y[] = "\nAxis Y: ";
	char_t str_z[] = "\nAxis Z: ";
	char_t i = 0;

	strcat((char_t *)buff, str);
	strcat((char_t *)buff, str_gyro);
	strcat((char_t *)buff, str_x);
	ftoa(data->gyro.x, value);
	strcat((char_t *)buff, value);
	strcat((char_t *)buff, str_y);
	ftoa(data->gyro.y, value);
	strcat((char_t *)buff, value);
	strcat((char_t *)buff, str_z);
	ftoa(data->gyro.z, value);
	strcat((char_t *)buff, value);

	strcat((char_t *)buff, str_accl);
	strcat((char_t *)buff, str_x);
	ftoa(data->accl.x, value);
	strcat((char_t *)buff, value);
	strcat((char_t *)buff, str_y);
	ftoa(data->accl.y, value);
	strcat((char_t *)buff, value);
	strcat((char_t *)buff, str_z);
	ftoa(data->accl.z, value);
	strcat((char_t *)buff, value);

	strcat((char_t *)buff, str_temp);
	ftoa(data->temp, value);
	strcat((char_t *)buff, value);
	strcat((char_t *)buff, "\n\n");

	for(i = 0; i<256; i++){
		if(*(buff + i) == '\0') break;
		//Print byte by byte
		DEV_UARTSendChar(buff + i);
	}
	return ret;
}

/**
 * @brief  Convert Float to ASCII
 * @param
 * 		value	[I] - Float data
 * 		str		[O] - String output
 * @retval void
 */
static void ftoa(float value, char_t * str){

	float fpart;
	uint8_t ipart;
    char_t istr[5] = {0};
    char_t dot[] = ".";
    char_t fstr[2] = {0};
    char_t vstr[8] = {0};

    ipart = (uint8_t)value;
    fpart = value - (float)ipart;
    itoa(ipart, istr, 10);
	fpart = fpart * pow(10, 2);
	itoa((uint8_t)fpart, fstr, 10);

	strcat(vstr,istr);
	strcat(vstr, dot);
	strcat(vstr, fstr);

	for(uint8_t i = 0; i < 8; i++){
		str[i] = vstr[i];
	}
}
