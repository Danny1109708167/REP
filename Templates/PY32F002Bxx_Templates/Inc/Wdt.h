/**
  ******************************************************************************
  * @file    Wdt.h
  * @author  Dario Liu
  * @brief   Header for Wdt.c file.
  *          This file contains the common defines of the application.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WDT_H
#define __WDT_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define FEED  Feed();

void Wdt_Config(void);
void Feed(void);

#endif /* __WDT_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
