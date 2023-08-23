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
#include "circular_buffer.h"
#include <stdlib.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           				Circular Buffer Functions				          */
/******************************************************************************/

/**
  * @brief This function initialize Circular Buffer struct.
  */
void Circular_Buffer_Init(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer, uint16_t max_size){
	circular_buffer->size = max_size;
	circular_buffer->data = (uint8_t*)calloc(circular_buffer->size,sizeof(uint8_t));
	circular_buffer->num_Entries = 0;
	circular_buffer->head = 0;
	circular_buffer->tail = 0;
}

/**
  * @brief This function check is circular buffer empty or not.
  */
CIRCULAR_BUFFER_StateTypeDef Circular_Buffer_IsEmpty(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer){
	return (circular_buffer->num_Entries == 0) ? CIRCULAR_BUFFER_STATE_EMPTY : CIRCULAR_BUFFER_STATE_FULL;
}

/**
  * @brief This function check is circular buffer full or not.
  */
CIRCULAR_BUFFER_StateTypeDef Circular_Buffer_IsFull(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer){
	return (circular_buffer->num_Entries == circular_buffer->size) ? CIRCULAR_BUFFER_STATE_FULL : CIRCULAR_BUFFER_STATE_EMPTY;
}

/**
  * @brief This function append data to circular buffer and check the tail index value.
  */
CIRCULAR_BUFFER_StateTypeDef Circular_Buffer_Queue(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer, uint8_t *value){
	if(Circular_Buffer_IsFull(circular_buffer) == CIRCULAR_BUFFER_STATE_FULL){
		return CIRCULAR_BUFFER_STATE_ERROR;
	}
	else{
		circular_buffer->data[circular_buffer->head++] = *value;
		circular_buffer->num_Entries++;
		if(circular_buffer->head >= circular_buffer->size){
			circular_buffer->head = 0;
		}
		return CIRCULAR_BUFFER_STATE_OK;
	}
}

/**
  * @brief This function read data to circular buffer and check the head index value.
  */
CIRCULAR_BUFFER_StateTypeDef Circular_Buffer_Dequeue(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer, uint8_t *data){
	if(Circular_Buffer_IsEmpty(circular_buffer) == CIRCULAR_BUFFER_STATE_EMPTY){
		return CIRCULAR_BUFFER_STATE_ERROR;
	}
	else{
		*data = circular_buffer->data[circular_buffer->tail++];
		circular_buffer->num_Entries--;
		if(circular_buffer->tail >= circular_buffer->size){
			circular_buffer->tail = 0;
		}
		return CIRCULAR_BUFFER_STATE_OK;
	}
}

/**
  * @brief This function dequeue the data to QUEUE_InitTypeDef struct.
  */
void Circular_Buffer_RxCpltCallback(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer, QUEUE_InitTypeDef *queue){
	if(circular_buffer->tail < circular_buffer->head){
		for (uint8_t i = circular_buffer->tail ; i < circular_buffer->head ; i++) {
			if(queue->indexData < 20){
				if(Circular_Buffer_Dequeue(circular_buffer, &(queue->queue[queue->indexQueue].datas[queue->indexData++])) == CIRCULAR_BUFFER_STATE_ERROR){
					Error_Handler();
				}
			}
			else{
				uint8_t tempData;
				if(Circular_Buffer_Dequeue(circular_buffer, &tempData) == CIRCULAR_BUFFER_STATE_ERROR){
					Error_Handler();
				}
			}
		}
	}
	else if(circular_buffer->tail > circular_buffer->head){
		uint8_t tempData;
		for (uint8_t i = circular_buffer->tail ; i < circular_buffer->size ; i++) {
			if(queue->indexData < 20){
				if(Circular_Buffer_Dequeue(circular_buffer, &(queue->queue[queue->indexQueue].datas[queue->indexData++])) == CIRCULAR_BUFFER_STATE_ERROR){
					Error_Handler();
				}
			}
			else{
				if(Circular_Buffer_Dequeue(circular_buffer, &tempData) == CIRCULAR_BUFFER_STATE_ERROR){
					Error_Handler();
				}
			}
		}
		for (uint8_t i = circular_buffer->tail ; i < circular_buffer->head ; i++) {
			if(queue->indexData < 20){
				if(Circular_Buffer_Dequeue(circular_buffer, &(queue->queue[queue->indexQueue].datas[queue->indexData++])) == CIRCULAR_BUFFER_STATE_ERROR){
					Error_Handler();
				}
			}
			else{
				uint8_t tempData;
				if(Circular_Buffer_Dequeue(circular_buffer, &tempData) == CIRCULAR_BUFFER_STATE_ERROR){
					Error_Handler();
				}
			}
		}
	}

	queue->queue[queue->indexQueue].flag = QUEUE_STATE_FULL;
	if(queue->indexQueue >= QUEUE_SIZE - 1){
		queue->indexQueue = 0;
	}
	else{
		queue->indexQueue++;
	}
	queue->indexData = 0;
}
