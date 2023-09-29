/************************************************************************************************
Copyright (c) 2023, Santiago Escribá <escribasan@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/**
 * requerimientos
 * - El driver debe setear sus registros de inicializacion via I2C
 * - Una escritura via I2C debe ser valida y retornar 0
 * - Una lectura via I2C debe ser valida y retornar 0
 * - Una lectura del Giroscopo debe ser valida y estar en el formato X Y Z
 * - una lectura del acelerometro debe ser valida y estar en el formato X Y Z
 * - Una lectura de la temperatura debe ser valida y estar en grados celsius
 * - 
*/

/** @file
 ** @brief Archivo de test de un Driver de control de un MPU9250
 **/

/* === Headers files inclusions =============================================================== */

#include "unity.h"
#include "mock_port.h"
#include "mpu9250.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

//El driver debe setear sus registros de inicializacion via I2C
void test_iniciar_error(void){
    retType ret = API_OK;

    DEV_I2CIsReady_ExpectAndReturn((0x68<<1), API_ERROR);
    ret = APP_MPU9250Init();

    TEST_ASSERT_EQUAL(API_ERROR, ret);
}

//El driver debe setear sus registros de inicializacion via I2C
void test_iniciar_ok(void){
    retType ret = API_OK;
    I2CStates_t expected_state = I2C_OK;
    uint8_t expected_value[6][2] =  {{MPU9250_PWR_MGMT_1, 0x0},
                                    {MPU9250_PWR_MGMT_1, 0x1},
                                    {MPU9250_GYRO_CONFIG, 0x18},
                                    {MPU9250_CONFIG_AD, 0x7},
                                    {MPU9250_ACCEL_CONFIG_1, 0x18},
                                    {MPU9250_ACCEL_CONFIG_2, 0x7}};

    DEV_I2CGetState_IgnoreAndReturn(expected_state);
    DEV_I2CIsReady_ExpectAndReturn(MPU9250_SLAVEADDR, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[0][0]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[0][1]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[1][0]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[1][1]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[2][0]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[2][1]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[3][0]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[3][1]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[4][0]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[4][1]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[5][0]}, 1, 1, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[5][1]}, 1, 1, API_OK);

    ret = APP_MPU9250Init();

    TEST_ASSERT_EQUAL(API_OK, ret);
}

//Una lectura del Giroscopo debe ser valida y estar en el formato X Y Z
void test_leer_gyro(void){
    retType ret = API_OK;
    axis_t gyro;
    I2CStates_t expected_state = I2C_OK;
    uint8_t expected_value[3][2] =  {{MPU9250_GYRO_XOUT_H, 0x0},
                                    {MPU9250_GYRO_YOUT_H, 0x0},
                                    {MPU9250_GYRO_ZOUT_H, 0x0},};

    DEV_I2CGetState_IgnoreAndReturn(expected_state);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[0][0]}, 1, 1, API_OK);
    DEV_I2CRead_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[0][1]}, 1, 2, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[1][0]}, 1, 1, API_OK);
    DEV_I2CRead_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[1][1]}, 1, 2, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[2][0]}, 1, 1, API_OK);
    DEV_I2CRead_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[2][1]}, 1, 2, API_OK);

    ret = APP_MPU9250ReadGyro(&gyro);
    TEST_ASSERT_EQUAL(API_OK, ret);
    TEST_ASSERT_EQUAL(gyro.x, 0);
    TEST_ASSERT_EQUAL(gyro.y, 0);
    TEST_ASSERT_EQUAL(gyro.z, 0);
}

//Una lectura del acelerometro debe ser valida y estar en el formato X Y Z
void test_leer_accl(void){
    retType ret = API_OK;
    axis_t accl;
    I2CStates_t expected_state = I2C_OK;
    uint8_t expected_value[3][2] =  {{MPU9250_ACCEL_XOUT_H, 0x0},
                                    {MPU9250_ACCEL_YOUT_H, 0x0},
                                    {MPU9250_ACCEL_ZOUT_H, 0x0},};

    DEV_I2CGetState_IgnoreAndReturn(expected_state);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[0][0]}, 1, 1, API_OK);
    DEV_I2CRead_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[0][1]}, 1, 2, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[1][0]}, 1, 1, API_OK);
    DEV_I2CRead_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[1][1]}, 1, 2, API_OK);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[2][0]}, 1, 1, API_OK);
    DEV_I2CRead_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[2][1]}, 1, 2, API_OK);

    ret = APP_MPU9250ReadAccl(&accl);
    TEST_ASSERT_EQUAL(API_OK, ret);
    TEST_ASSERT_EQUAL(accl.x, 0);
    TEST_ASSERT_EQUAL(accl.y, 0);
    TEST_ASSERT_EQUAL(accl.z, 0);
}

//Una lectura de la temperatura debe ser valida y estar en grados celsius
void test_leer_temp(void){
    retType ret = API_OK;
    float temp;
    I2CStates_t expected_state = I2C_OK;
    uint8_t expected_value[1][2] =  {{MPU9250_TEMP_OUT_H, 0x0},};

    DEV_I2CGetState_IgnoreAndReturn(expected_state);
    DEV_I2CWrite_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[0][0]}, 1, 1, API_OK);
    DEV_I2CRead_ExpectWithArrayAndReturn(MPU9250_SLAVEADDR,(uint8_t[1]){expected_value[0][1]}, 1, 2, API_OK);

    ret = APP_MPU9250ReadTemp(&temp);
    TEST_ASSERT_EQUAL(API_OK, ret);
    TEST_ASSERT_EQUAL(temp, 21);
}
/* === End of documentation ==================================================================== */