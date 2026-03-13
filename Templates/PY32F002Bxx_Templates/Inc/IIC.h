/**
  ******************************************************************************
  * @file    IIC.h
  * @author  Dario Liu
  * @brief   Header for IIC.c file.
  *          This file contains the common defines of the application.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IIC_H
#define __IIC_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define I2C_ADDRESS      		0xAA          	   /* Local address 0xA0 */
#define I2C_SPEEDCLOCK   		100000             /* Communication speed 100K */
#define I2C_DUTYCYCLE    		I2C_DUTYCYCLE_16_9 /* Duty cycle */

#define I2C_SCL_EXTI_IRQN   EXTI2_3_IRQn

#define I2C_IRQN            I2C1_IRQn
#define I2C_GPIO            GPIOB
#define I2C_SCL             GPIO_PIN_3
#define I2C_SDA             GPIO_PIN_4

#define STATE_WRITE           1
#define STATE_READ            2
#define STATE_ADDRESS         3
#define STATE_DATA_WRITE      4
#define STATE_IDLE            0

typedef enum
{
  RW = 0,      //读写
  OR,          //只读
  OW,          //只写
}IIC_Permission;

typedef enum
{
  Reg_8bit = 0,       //8位
  Reg_16bit,          //16位
}IIC_Reg;

typedef struct 
{
  /* data */
  uint8_t         order_code;
  IIC_Permission  per;
  IIC_Reg         Reg;
  void            *IIC_data;
}IIC_BUS;

extern uint8_t I2C_state;

void IIC_Config(void);
void IIC_GPIO_Config(void);
void IIC_DISENABLE(void);
void IIC_GPIO_Idle_Config(void);
void I2C_Slave_Handler(void);

#endif /* __IIC_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
