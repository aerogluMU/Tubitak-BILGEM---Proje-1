/* BEGIN Header */
/**
  ******************************************************************************
  * @file    circular_buffer.h
  * @brief   This file contains the circular buffer operations.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CIRCULAR_BUFFER_H
#define __CIRCULAR_BUFFER_H

/* Private includes ----------------------------------------------------------*/
#include <queue.h>

/* Exported types ------------------------------------------------------------*/

typedef struct{
	uint8_t *data;
	uint16_t head;
	uint16_t tail;
	uint16_t num_Entries;
	uint16_t size;
}CIRCULAR_BUFFERS_InitTypeDef;

typedef enum
{
	CIRCULAR_BUFFER_STATE_EMPTY             = 0x000,
	CIRCULAR_BUFFER_STATE_FULL             	= 0x001,
	CIRCULAR_BUFFER_STATE_OK             	= 0x002,
	CIRCULAR_BUFFER_STATE_ERROR             = 0x003
} CIRCULAR_BUFFER_StateTypeDef;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define CIRCULAR_BUFFER_SIZE				512

/* Exported functions prototypes ---------------------------------------------*/

void Circular_Buffer_Init(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer, uint16_t size);
CIRCULAR_BUFFER_StateTypeDef Circular_Buffer_IsEmpty(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer);
CIRCULAR_BUFFER_StateTypeDef Circular_Buffer_IsFull(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer);
CIRCULAR_BUFFER_StateTypeDef Circular_Buffer_Queue(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer, uint8_t *value);
CIRCULAR_BUFFER_StateTypeDef Circular_Buffer_Dequeue(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer, uint8_t *data);
void Circular_Buffer_RxCpltCallback(CIRCULAR_BUFFERS_InitTypeDef *circular_buffer, QUEUE_InitTypeDef *queue);

#endif /* __CIRCULAR_BUFFER_H */
