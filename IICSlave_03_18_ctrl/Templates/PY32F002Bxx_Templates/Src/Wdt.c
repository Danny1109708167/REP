/**
  ******************************************************************************
  * @file    Wdt.c
  * @author  Dario Liu
  * @brief   WDT Config
  ******************************************************************************
  * @attention
  */

/* Includes ------------------------------------------------------------------*/
#include "Wdt.h"
#ifdef IWDT_ENABLE
/* Private variables ---------------------------------------------------------*/
IWDG_HandleTypeDef   IwdgHandle;

void Wdt_Config(void)
{
  IwdgHandle.Instance = IWDG;                     /* IWDG */
  IwdgHandle.Init.Prescaler = IWDG_PRESCALER_64;  /* Prescaler DIV 64 */
  IwdgHandle.Init.Reload = (5*520);                /* IWDG Reload value 2500 */
  HAL_IWDG_Init(&IwdgHandle);

}

void Feed(void)
{
  HAL_IWDG_Refresh(&IwdgHandle);
}
#endif
	
/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
