/**
  ******************************************************************************
  * @file    py32f002b_it.c
  * @author  MCU Application Team
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "py32f002b_it.h"
#include "Config.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern I2C_HandleTypeDef    I2cHandle;
extern LPTIM_HandleTypeDef  LPTIMConf;
extern TIM_HandleTypeDef    Tim1_Handle;
extern TIM_HandleTypeDef    Tim14_Handle;
extern uint8_t IIC_Restart;
extern uint32_t Lptimes;
extern uint32_t Ms_Times;
extern uint32_t Us_Times;
extern uint32_t Sys_tick_time;

/******************************************************************************/
/*          Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
  Sys_tick_time++;
}

/**
  * @brief This function handles I2C1 Interrupt .
  */
void I2C1_IRQHandler(void)
{
  HAL_I2C_EV_IRQHandler(&I2cHandle);
  HAL_I2C_ER_IRQHandler(&I2cHandle);
}
//#define LPTIM1_IT_ENABLE
#ifdef LPTIM1_IT_ENABLE
/**
  * @brief This function handles LPTIM interrupt.
  */
void LPTIM1_IRQHandler(void)
{
  Lptimes++;
  HAL_LPTIM_IRQHandler(&LPTIMConf);
}
#endif

/**
  * @brief This function handles EXTI interrupt.
  */
void EXTI2_3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
    IIC_Restart = 1;
}
// #define TIM1_IT_ENABLE
#ifdef TIM1_IT_ENABLE
/**
  * @brief This function handles TIM1 Interrupt.
  */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  Ms_Times++;
  HAL_TIM_IRQHandler(&Tim1_Handle);
}
#endif

// /**
//   * @brief This function handles TIM14 Interrupt.
//   */
// void TIM14_IRQHandler(void)
// {
//   Us_Times++;
//   HAL_TIM_IRQHandler(&Tim14_Handle);
// }

/******************************************************************************/
/* PY32F002B Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file.                                          */
/******************************************************************************/

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
