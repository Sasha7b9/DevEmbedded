/**
  ******************************************************************************
  * @file    Examples_LL/I2C/I2C_TwoBoards_WakeUpFromStop_IT/Inc/stm32f3xx_it.h
  * @author  MCD Application Team
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F3xx_IT_H
#define __STM32F3xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USER_BUTTON_IRQHANDLER(void);
#ifdef SLAVE_BOARD
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
#else
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
#endif /* SLAVE_BOARD */
#ifdef __cplusplus
}
#endif

#endif /* __STM32F3xx_IT_H */
