/**
  ******************************************************************************
  * @file    Task.c
  * @author  Dario Liu
  * @brief   Task Config
  ******************************************************************************
  * @attention
  */

/* Includes ------------------------------------------------------------------*/
#include "Config.h"
#include "IIC.h"
#include "LowPower.h"

uint32_t Lptimes = 0;
uint32_t Ms_Times = 0;
uint32_t Us_Times = 0;
uint8_t IIC_Restart = 0;
uint8_t I2C_Noack = 0;
uint8_t Stop_sta = 0;
uint8_t Slave_Run = 0;
uint32_t Catch_Time = 0;
uint32_t Sys_tick_time = 0;
uint32_t Run_Time = 0;
extern IIC_BUS iic_slave[];

void Task(void)
{
  Time_Test_Gpio();
  // Time_Test_Task();
  Slave_Run = 0;
   while (1)
  {
    // Enter_Standby_Mode();
    // FEED
    // I2C_Slave_Handler();
    
    
    if(IIC_Restart == 1)// SLEEP TO WORK
    {
      EXTI->FTSR = 0;
      IIC_DISENABLE();
      IIC_GPIO_Config();
      IIC_Config();
      IIC_Restart = 0;
    }
    // if (I2C1->SR2 & 0x06)	
    // {

    //   /* code */
    //   IIC_Restart = 1;
    // }
    // GPIOA->BRR = GPIO_PIN_1;
    if (I2C_state == STATE_IDLE)
    {
      /* code */
      if (*(uint8_t *)iic_slave[16].IIC_data == 0x22)//&& (*(uint8_t *)iic_slave[17].IIC_data == 0x33) && (*(uint8_t *)iic_slave[18].IIC_data == 0x44))
      {
        GPIOB->BSRR = GPIO_PIN_0;
      }
      else
      {
        GPIOB->BRR = GPIO_PIN_0;
      }
    }
    
    // if(Stop_sta == 1)// WORK TO SLEEP
    // {
    //   Slave_Run = 0;
    //   HAL_DBGMCU_EnableDBGMCUStopMode(); //调试专用
    //   Low_Power_Task();
    //   IIC_Restart = 1;
    //   Stop_sta = 0;
    // }
    // if(Stop_sta == 0)// RUNING
    // {
    //   Run_Time = Get_Lptim_Value();
    //   if(Tick_Calc(Run_Time,Catch_Time) > 5)
    //   {
    //     Catch_Time = Run_Time;
    //     Stop_sta = 1;
    //   }
    // }
    // IWDG->SR = 0x1
  }
}

uint32_t Tick_Calc(uint32_t time1, uint32_t time2)
{
    if (time1 >= time2)
    {
        return time1 - time2;
    }
    else
    {
        return (0xFFFFFFFFU - time2) + time1;
    }
}

void Time_Test_Gpio(void)  //gpio翻转观察时间有无正确
{
  GPIO_InitTypeDef Test_GPIO_InitConfig = {0};
  Test_GPIO_InitConfig.Pin = GPIO_PIN_0;
  Test_GPIO_InitConfig.Mode = GPIO_MODE_OUTPUT_PP;
  Test_GPIO_InitConfig.Pull = GPIO_NOPULL;
  Test_GPIO_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &Test_GPIO_InitConfig);

  // Test_GPIO_InitConfig.Pin = GPIO_PIN_1;
  // Test_GPIO_InitConfig.Mode = GPIO_MODE_OUTPUT_PP;
  // Test_GPIO_InitConfig.Pull = GPIO_NOPULL;
  // Test_GPIO_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;
  // HAL_GPIO_Init(GPIOA, &Test_GPIO_InitConfig);
}

void Time_Test_Task(void)
{
  if ((GPIOB->ODR & GPIO_PIN_0) != 0x00u)
    {
     GPIOB->BRR = (uint32_t)GPIO_PIN_0;
   }
   else
    {
     GPIOB->BSRR = (uint32_t)GPIO_PIN_0;
   }
}

uint32_t Get_Lptim_Value(void)
{
  return Lptimes;
}


uint32_t Get_Tim1_Value(void)
{
  return Ms_Times;
}

uint32_t Get_Tim14_Value(void)
{
  return Us_Times;
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
