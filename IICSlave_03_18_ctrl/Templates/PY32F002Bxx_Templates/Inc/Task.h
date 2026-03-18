/**
  ******************************************************************************
  * @file    Task.h
  * @author  Dario Liu
  * @brief   Header for Task.c file.
  *          This file contains the common defines of the application.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_H
#define __TASK_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

void Task(void);
void Time_Test_Gpio(void);
void Time_Test_Task(void);
uint32_t Get_Lptim_Value(void);
uint32_t Get_Tim1_Value(void);
uint32_t Get_Tim14_Value(void);
void Lowpower_Feed(void);
uint32_t Tick_Calc(uint32_t time1, uint32_t time2);

#endif /* __TASK_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
