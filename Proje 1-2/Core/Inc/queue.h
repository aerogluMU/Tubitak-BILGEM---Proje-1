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
#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct{
	uint8_t datas[20];
	unsigned flag;
}DATA_InitTypeDef;

typedef struct{
	DATA_InitTypeDef *queue;
	uint8_t size;
	uint8_t indexQueue;
	uint8_t indexData;
}QUEUE_InitTypeDef;

typedef enum{
	QUEUE_STATE_EMPTY            		    = 0x000,
	QUEUE_STATE_FULL		             	= 0x001
} QUEUE_StateTypeDef;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define QUEUE_SIZE							16
#define DELAY_MS							1000

/* Exported functions prototypes ---------------------------------------------*/
void Queue_Init(QUEUE_InitTypeDef *queue, uint8_t size);
void Queue_Check(QUEUE_InitTypeDef *queue);
//void Queue_Fill(QUEUE_InitTypeDef *queue);

#endif /* INC_QUEUE_H_ */
