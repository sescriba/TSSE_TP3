/**
 ******************************************************************************
 * @file    Core/Inc/types.h
 * @author  Santiago Escriba
 * @brief   Define type for projects
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_TYPES_H_
#define INC_TYPES_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
  * @brief  retType Status structures definition
  */
typedef enum
{
  API_OK       = 0x00U,
  API_ERROR    = 0x01U,
  API_BUSY     = 0x02U,
  API_TIMEOUT  = 0x03U
}retType;

typedef bool bool_t;
typedef char char_t;
typedef uint32_t tick_t;


#endif /* INC_TYPES_H_ */
