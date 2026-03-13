/**
  ******************************************************************************
  * @file    Tim.c
  * @author  Dario Liu
  * @brief   Tim Config
  ******************************************************************************
  * @attention
  */

/* Includes ------------------------------------------------------------------*/
#include "Tim.h"
#ifdef TIM1_ENABLE
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    Tim1_Handle;
TIM_HandleTypeDef    Tim14_Handle;
void Tim1_Config(void)//1MS
{
  /* TIM1 */
  Tim1_Handle.Instance = TIM1;
  
  /* Period = 1000 - 1 */
  Tim1_Handle.Init.Period            = 1000 - 1;

  /* Prescaler = 24 - 1 */
  Tim1_Handle.Init.Prescaler         = 24 - 1;

  /* ClockDivision = 0 */
  Tim1_Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;

  /* Counter direction = Up */
  Tim1_Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;

  /* Repetition = 0 */
  Tim1_Handle.Init.RepetitionCounter = 1 - 1;

  /* Auto-reload register not buffered */
  Tim1_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  /* Initialize TIM1 */
  HAL_TIM_Base_Init(&Tim1_Handle);
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,0);
  HAL_TIM_Base_Start_IT(&Tim1_Handle);
}

#endif

#ifdef TIM14_ENABLE
void Tim14_Config(void)//1us
{
  /* TIM1 */
  Tim14_Handle.Instance = TIM14;
  
  /* Period = 3 - 1 */
  Tim14_Handle.Init.Period            = 3 - 1;

  /* Prescaler = 8 - 1 */
  Tim14_Handle.Init.Prescaler         = 8 - 1;

  /* ClockDivision = 0 */
  Tim14_Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;

  /* Counter direction = Up */
  Tim14_Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;

  /* Repetition = 0 */
  Tim14_Handle.Init.RepetitionCounter = 1 - 1;

  /* Auto-reload register not buffered */
  Tim14_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  /* Initialize TIM1 */
  HAL_TIM_Base_Init(&Tim14_Handle);
  NVIC_EnableIRQ(TIM14_IRQn);
  NVIC_SetPriority(TIM14_IRQn,0);
  HAL_TIM_Base_Start_IT(&Tim14_Handle);
}
	#endif
/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
