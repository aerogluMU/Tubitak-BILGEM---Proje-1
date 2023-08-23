/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    project1_uart.c
  * @brief   Special UART functions.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "project1_uart.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint32_t rxParameter = 0;

uint8_t ledOn[] = "Led On\r\n";
uint8_t ledOff[] = "Led Off\r\n";

/* Private function prototypes -----------------------------------------------*/

/* External variables --------------------------------------------------------*/
extern FLAGS_STATES flags_States;
extern TIM_HandleTypeDef htim2;
extern uint32_t delayMs;
extern uint8_t rxIndex;
extern uint8_t rxData[20];

/******************************************************************************/
/*           				 Special UART Functions 				          */
/******************************************************************************/

void UART_Flags_Init(FLAGS_STATES *flags_States){
	flags_States->flag_LedOn = FLAG_STATE_RESET;
	flags_States->flag_LedOff = FLAG_STATE_RESET;
	flags_States->flag_LedBlink = FLAG_STATE_RESET;
	flags_States->flag_LedPWM = FLAG_STATE_RESET;
	flags_States->flag_UARTCallBack = FLAG_STATE_RESET;
	flags_States->flag_UART_LedOn = FLAG_STATE_RESET;
	flags_States->flag_UART_LedOff = FLAG_STATE_RESET;
	flags_States->flag_UART_LedBlink = FLAG_STATE_RESET;
	flags_States->flag_UART_LedPWM = FLAG_STATE_RESET;
	flags_States->flag_Parameter = FLAG_STATE_RESET;
	flags_States->state_Led = STATE_LED_FIRST;
	delayMs = BLINK_RATE_LOW;
}

/**
  * @brief This function check all queues flags.
  */
void UART_Flag_Check(QUEUE_InitTypeDef *queue, FLAGS_STATES *flags_States){
	char *ledOnUART = "LedOn";
	char *ledBlinkUART = "Blink";
	char *ledOffUART = "LedOff";
	char *ledPWMUART = "LedPWM";
	char *resetAll = "ResetAll";
	if(strstr((char *)(queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas),ledBlinkUART) != NULL){
	  flags_States->flag_UART_LedBlink = FLAG_STATE_SET;
	  flags_States->flag_UART_LedOn = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedOff = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedPWM = FLAG_STATE_RESET;
	}
	else if(strstr((char *)(queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas),ledOnUART) != NULL){
	  flags_States->flag_UART_LedBlink = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedOn = FLAG_STATE_SET;
	  flags_States->flag_UART_LedOff = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedPWM = FLAG_STATE_RESET;
	}
	else if(strstr((char *)(queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas),ledOffUART) != NULL){
	  flags_States->flag_UART_LedBlink = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedOn = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedOff = FLAG_STATE_SET;
	  flags_States->flag_UART_LedPWM = FLAG_STATE_RESET;
	}
	else if(strstr((char *)(queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas),ledPWMUART) != NULL){
	  flags_States->flag_UART_LedBlink = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedOn = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedOff = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedPWM = FLAG_STATE_SET;
	}
	else if(strstr((char *)(queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas),resetAll)){
	  flags_States->flag_UART_LedBlink = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedOn = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedOff = FLAG_STATE_RESET;
	  flags_States->flag_UART_LedPWM = FLAG_STATE_RESET;
	}
}

/**
  * @brief This function initialize Circular Buffer struct.
  */
void UART_Parameter_Check(QUEUE_InitTypeDef *queue, FLAGS_STATES *flags_States){
	  if(flags_States->flag_UART_LedBlink == FLAG_STATE_SET || \
			  flags_States->flag_UART_LedPWM == FLAG_STATE_SET){
		  uint8_t count = 0;
		  rxParameter = 0;
		  for (int i = QUEUE_SIZE - 1; i >= 0; i--) {
			  if(queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas[i] == NULL || \
					  queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas[i] == '\r' || \
					  queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas[i] == '\n' || \
					  (queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas[i] > '9' && \
					  queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas[i] < '0')){
				  continue;
			  }
			  if(queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas[i] == ' '){
				  break;
			  }
			  int power = pow_num(10,count++);
			  rxParameter += (power * (queue->queue[(queue->indexQueue > 0) ? (queue->indexQueue - 1) : (QUEUE_SIZE - 1)].datas[i] - 48));
		  }
		  flags_States->flag_Parameter = FLAG_STATE_SET;
	  }
}

/**
  * @brief This function initialize Circular Buffer struct.
  */
int pow_num(int x, int y)
{
    int power = 1, i;
    for (i = 1; i <= y; ++i)
    {
        power = power * x;

    }
    return power;
}

/**
  * @brief This function initialize Circular Buffer struct.
  */
void UART_Functions_Check(TIM_HandleTypeDef *htim2, FLAGS_STATES *flags_States){
	if(flags_States->flag_UART_LedOn == FLAG_STATE_RESET && \
				  flags_States->flag_UART_LedOff == FLAG_STATE_RESET && \
				  flags_States->flag_UART_LedBlink == FLAG_STATE_RESET && \
				  flags_States->flag_UART_LedPWM == FLAG_STATE_RESET){
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(htim2,TIM_CHANNEL_1,TIM_MAX_VALUE);
		//HAL_UART_Transmit(&huart2,ledOn,sizeof(ledOn),HAL_MAX_DELAY);
		HAL_Delay(delayMs);
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(htim2,TIM_CHANNEL_1,TIM_MIN_VALUE);
		//HAL_UART_Transmit(&huart2,ledOff,sizeof(ledOff),HAL_MAX_DELAY);
		HAL_Delay(delayMs);
	}
	else if(flags_States->flag_UART_LedOn == FLAG_STATE_SET){
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(htim2,TIM_CHANNEL_1,TIM_MAX_VALUE);
		//HAL_UART_Transmit(&huart2,ledOn,sizeof(ledOn),HAL_MAX_DELAY);
	}
	else if(flags_States->flag_UART_LedOff == FLAG_STATE_SET){
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(htim2,TIM_CHANNEL_1,TIM_MIN_VALUE);
		//HAL_UART_Transmit(&huart2,ledOff,sizeof(ledOff),HAL_MAX_DELAY);
	}
	else if(flags_States->flag_UART_LedBlink == FLAG_STATE_SET){
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(htim2,TIM_CHANNEL_1,TIM_MAX_VALUE);
		//HAL_UART_Transmit(&huart2,ledOn,sizeof(ledOn),HAL_MAX_DELAY);
		HAL_Delay(rxParameter);
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(htim2,TIM_CHANNEL_1,TIM_MIN_VALUE);
		//HAL_UART_Transmit(&huart2,ledOff,sizeof(ledOff),HAL_MAX_DELAY);
		HAL_Delay(rxParameter);
	}
	else if(flags_States->flag_UART_LedPWM == FLAG_STATE_SET){
		for(int i = TIM_MIN_VALUE ; i < rxParameter ; i++){
			__HAL_TIM_SET_COMPARE(htim2,TIM_CHANNEL_1,i);
			HAL_Delay(1);
		}
		for(int i = rxParameter ; i > TIM_MIN_VALUE ; i--){
			__HAL_TIM_SET_COMPARE(htim2,TIM_CHANNEL_1,i);
			HAL_Delay(1);
		}
	}
}
