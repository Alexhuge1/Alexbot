/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "fdcan.h"
#include "dm_driver.h"
#include "frame_function.h"
#include "Bmi088driver.h"


extern float gyro[], accel[], temp;
extern float pos[];//pos[0] is unused, start from pos[1]
extern float vel[];
extern float kp[];
extern float kd[];
extern float torq[];

/* USER CODE END 0 */

TIM_HandleTypeDef htim6;

/* TIM6 init function */
void MX_TIM6_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 60;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 2000;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM6)
  {
    /* TIM6 clock enable */
    __HAL_RCC_TIM6_CLK_ENABLE();

    /* TIM6 interrupt Init */
    HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM6)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM6_CLK_DISABLE();

    /* TIM6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
  }
}

/* USER CODE BEGIN 1 */

uint8_t num=1;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
		switch(num)
		{
			case 1:
				  mit_ctrl(&hfdcan2, 1, pos[1], vel[1],kp[1], kd[1], torq[1]);
				  mit_ctrl(&hfdcan2, 2, pos[2], vel[2],kp[2], kd[2], torq[2]); 
				  num++;
			break;
			case 2:
				  mit_ctrl(&hfdcan2, 3, pos[3], vel[3],kp[3], kd[3], torq[3]);
				  mit_ctrl(&hfdcan2, 4, pos[4], vel[4],kp[4], kd[4], torq[4]);
			      num++;
			break;
			case 3:
				  mit_ctrl(&hfdcan2, 5, pos[5], vel[5],kp[5], kd[5], torq[5]);
				  mit_ctrl(&hfdcan1, 6, pos[6], vel[6],kp[6], kd[6], torq[6]);
			      num++;
			break;
			case 4:
				  mit_ctrl(&hfdcan1, 7, pos[7], vel[7],kp[7], kd[7], torq[7]);
				  mit_ctrl(&hfdcan1, 8, pos[8], vel[8],kp[8], kd[8], torq[8]);
			      num++;
			break;
			case 5:
				  mit_ctrl(&hfdcan1, 9, pos[9], vel[9],kp[9], kd[9], torq[9]);
				  mit_ctrl(&hfdcan1, 10, pos[10], vel[10],kp[10], kd[10], torq[10]);
			      num++;		
			break;
			case 6:
				  BMI088_read(gyro, accel,&temp);
			//	  frame_function_upload(&huart1);
			//	  frame_function_download(&huart1);
				  num++;
			break;
			default:
				break;
		};
		if(num==7)
		{
			num=1;
		}
	}	 
}
