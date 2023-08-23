/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    project1_uart.h
  * @brief   This file contains the special uart functions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Tubitak BILGEM.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
 ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_PROJECT1_UART_H_
#define INC_PROJECT1_UART_H_

/* Private includes ----------------------------------------------------------*/
#include <queue.h>
#include <string.h>

/* Exported types ------------------------------------------------------------*/
typedef struct{
	uint8_t flag_LedOn:1;
	uint8_t flag_LedOff:1;
	uint8_t flag_LedBlink:1;
	uint8_t flag_LedPWM:1;
	uint8_t flag_UARTCallBack:1;
	uint8_t flag_UART_LedOn:1;
	uint8_t flag_UART_LedOff:1;
	uint8_t flag_UART_LedBlink:1;
	uint8_t flag_UART_LedPWM:1;
	uint8_t flag_Parameter:1;
	uint8_t state_Led:2;
}FLAGS_STATES;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define FLAG_STATE_RESET 			0
#define FLAG_STATE_SET 				1

#define BLINK_RATE_LOW 				1000
#define BLINK_RATE_MEDIUM 			500
#define BLINK_RATE_HIGH 			200

#define STATE_LED_FIRST				0
#define STATE_LED_SECOND			1
#define STATE_LED_THIRD				2

#define TIM_MAX_VALUE				1000
#define TIM_MIN_VALUE				0

/* Exported functions prototypes ---------------------------------------------*/
void UART_Flags_Init(FLAGS_STATES *flags_States);
void UART_Flag_Check(QUEUE_InitTypeDef *queue, FLAGS_STATES *flags_States);
void UART_Parameter_Check(QUEUE_InitTypeDef *queue, FLAGS_STATES *flags_States);
void UART_Functions_Check(TIM_HandleTypeDef *htim2, FLAGS_STATES *flags_States);
int pow_num(int x, int y);

#endif /* INC_PROJECT1_UART_H_ */
