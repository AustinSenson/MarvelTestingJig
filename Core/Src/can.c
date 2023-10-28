/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "can.h"
#include "main.h"

/* USER CODE BEGIN 0 */
uint8_t canData[8] = {0};

extern bool TEST_ALL_FLAG;
extern bool CAN_COMMUNICATION_FLAG;
extern bool SLAVE_COMMUNICATION_FLAG;
extern bool LTC2949_COMMUNCIATION_FLAG;
extern bool EEPROM_TEST_FLAG;
extern bool CELL_BALANCING_FLAG;
extern bool CONTACTOR_MOSFETS_CONTROL;

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 16;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_1TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
//will receive the test instructions over CAN
	CAN_RxHeaderTypeDef pRxHeader = {0};
	if (hcan == &hcan1)
		{
			HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &pRxHeader, canData);



		if(pRxHeader.StdId == LAPTOP_ID)
		{
			if(canData[0] == 1)
			{
				currentTest = TEST_ALL;
			}
			else if(canData[1] == 1)
			{
				currentTest = CAN_COMMUNICATION;
			}
			else if(canData[2] == 1)
			{
				currentTest = SLAVE_COMMUNICATION;
			}
			else if(canData[3] == 1)
			{
				currentTest = LTC2949_COMMUNICATION;
			}
			else if(canData[4] == 1)
			{
				currentTest = EEPROM_TEST;
			}
			else if(canData[5] == 1)
			{
				currentTest = CELL_BALANCING;
			}
			else if(canData[6] == 1)
			{
				currentTest = CONTACTOR_MOSFETS;
			}
		}

		if(pRxHeader.StdId == MARVEL_ID)
		{
			if(canData[0] == 1)
			{
				CAN_COMMUNICATION_FLAG = 1;
			}
			else if(canData[1] == 1)
			{
				SLAVE_COMMUNICATION_FLAG = true;
			}
			else if(canData[2] == 1)
			{
				LTC2949_COMMUNCIATION_FLAG = true;
			}
			else if(canData[3] == 1)
			{
				EEPROM_TEST_FLAG = true;
			}
//			else if(canData[4] == 1)
//			{
//				CELL_BALANCING_FLAG = true;
//			}
//			else if(canData[5] == 1)
//			{
//				CONTACTOR_MOSFETS_CONTROL = true;
//			}
		}

}





}

/* USER CODE END 1 */
