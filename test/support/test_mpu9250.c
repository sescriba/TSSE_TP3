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
 ** @brief Archivo de test de un Driver de control para un sistema de 16 Leds
 **/

/* === Headers files inclusions =============================================================== */

#include "unity.h"
#include "Mockport.h"
#include "mpu9250.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */
retType auxiliar_DEV_I2CWrite(uint16_t slave_addr, uint8_t * pdata, uint16_t size){
    if(slave_addr == 0 || size == 0) return API_ERROR;
    else return API_OK;
}

retType auxiliar_DEV_I2CRead(uint16_t slave_addr, uint8_t * pdata, uint16_t size){
    if(slave_addr == 0 || size == 0) return API_ERROR;
    else{
        *pdata = 0xFFFF;
        return API_OK;
    }
}

retType auxiliar_DEV_I2CIsReady(uint16_t slave_addr, uint8_t * pdata, uint16_t size){
    if(slave_addr == 0) return API_ERROR;
    else return API_OK;
}

/* === Public function implementation ========================================================== */

void setUp(void){
    LedsInit(&puerto_virtual);
}

//- El driver debe setear sus registros de inicializacion via I2C
void test_iniciar(void){
    retType ret = API_OK;

    ret = APP_MPU9250Init();

    TEST_ASSERT_EQUAL(API_OK, ret);
}
/* === End of documentation ==================================================================== */