/**
  ******************************************************************************
  * @file    LowPower.c
  * @author  Dario Liu
  * @brief   LowPower Task
  ******************************************************************************
  * @attention
  */

/* Includes ------------------------------------------------------------------*/
#include "LowPower.h"
#include "IIC.h"

/* Private variables ---------------------------------------------------------*/

void Low_Power_Task(void)
{
	IIC_DISENABLE();
  IIC_GPIO_Idle_Config();
  
	HAL_SuspendTick();
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
	HAL_ResumeTick();

}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
