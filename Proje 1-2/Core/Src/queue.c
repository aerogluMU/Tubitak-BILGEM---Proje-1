/* BEGIN Header */
/**
  ******************************************************************************
  * @file    circular_buffer.c
  * @brief   Circular buffer operations.
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
/* END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart2;
extern QUEUE_InitTypeDef queue;

/******************************************************************************/
/*           					 Queue Functions	  				          */
/******************************************************************************/

/**
  * @brief This function initialize Queue struct.
  */
void Queue_Init(QUEUE_InitTypeDef *queue, uint8_t size){
	queue->size = size;
	queue->indexData = 0;
	queue->indexQueue = 0;
	queue->queue = (DATA_InitTypeDef*)calloc(queue->size,sizeof(DATA_InitTypeDef));
	for (int i = 0; i < queue->size; i++) {
		queue->queue[i].flag = QUEUE_STATE_EMPTY;
	}
}

/**
  * @brief This function check all queues flags.
  */
void Queue_Check(QUEUE_InitTypeDef *queue){
	char string[100];
	for (int i = 0; i < QUEUE_SIZE; i++) {
		if(queue->queue[i].flag == QUEUE_STATE_FULL){
			sprintf(string, "Queue[%d] Address: %p\n",i,&(queue->queue[i]));
			HAL_UART_Transmit(&huart2, (uint8_t *)string, strlen(string), HAL_MAX_DELAY);
			//HAL_Delay(DELAY_MS);
		}
	}
}
