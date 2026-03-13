/**
  ******************************************************************************
  * @file    Lptim.c
  * @author  Dario Liu
  * @brief   LPTIM Config
  ******************************************************************************
  * @attention
  */

/* Includes ------------------------------------------------------------------*/
#include "Lptim.h"

#ifdef LPTIM_ENABLE
/* Private variables ---------------------------------------------------------*/
LPTIM_HandleTypeDef       LPTIMConf = {0};

void Lptim_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPTIM;
  PeriphClkInit.LptimClockSelection = RCC_LPTIMCLKSOURCE_LSI;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  LPTIMConf.Instance = LPTIM1;                       	 /* LPTIM1 */
  LPTIMConf.Init.Prescaler = LPTIM_PRESCALER_DIV32; 	 /* DIV 32 */
  LPTIMConf.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;  /* UPDATE IMMEDIATE */

  HAL_LPTIM_Init(&LPTIMConf);

  HAL_NVIC_SetPriority(LPTIM1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
	
	HAL_LPTIM_SetContinue_Start_IT(&LPTIMConf, 1024);
  
}

#endif
	
/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
