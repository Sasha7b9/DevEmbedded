/**
  ******************************************************************************
  * @file    USB_Device/CustomHID_Standalone/Inc/stm32f3xx_it.h
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
#if defined (USE_USB_INTERRUPT_DEFAULT)
void USB_LP_CAN_RX0_IRQHandler(void);
#elif defined (USE_USB_INTERRUPT_REMAPPED)
void USB_LP_IRQHandler(void);
#endif
void EXTI9_5_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);
#ifdef __cplusplus
}
#endif

#endif /* __STM32F3xx_IT_H */
