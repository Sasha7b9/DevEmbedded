/**
  ******************************************************************************
  * @file    TouchSensing\TouchSensing_2touchkeys\Inc\main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
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
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "tsl_user.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor TSCx/TSCx instance used and associated
   resources */
/* Definition for TSCx clock resources */
#define TSCx                                        TSC
#define TSCx_CLK_ENABLE()                           __HAL_RCC_TSC_CLK_ENABLE()
#define TSCx_TS1_IO_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOD_CLK_ENABLE()
#define TSCx_TS2_IO_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOD_CLK_ENABLE()
#define TSCx_SHIELD_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOB_CLK_ENABLE()
#define TSCx_TS1_CAPACITOR_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOD_CLK_ENABLE()
#define TSCx_TS2_CAPACITOR_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOD_CLK_ENABLE()
#define TSCx_SHIELD_CAPACITOR_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()

#define TSCx_FORCE_RESET()                          __HAL_RCC_TSC_FORCE_RESET()
#define TSCx_RELEASE_RESET()                        __HAL_RCC_TSC_RELEASE_RESET()

/* Definition for TSCx IO Pins */
#define TSCx_TS1_IO_PIN                             GPIO_PIN_13
#define TSCx_TS1_IO_GPIO_PORT                       GPIOD
#define TSCx_TS1_IO_AF                              GPIO_AF3_TSC

#define TSCx_TS2_IO_PIN                             GPIO_PIN_15
#define TSCx_TS2_IO_GPIO_PORT                       GPIOD
#define TSCx_TS2_IO_AF                              GPIO_AF3_TSC

#define TSCx_SHIELD_IO_PIN                          GPIO_PIN_12
#define TSCx_SHIELD_IO_GPIO_PORT                    GPIOB
#define TSCx_SHIELD_IO_AF                           GPIO_AF3_TSC

/* Definition for TSCx Sampling Capacitor Pins */
#define TSCx_TS1_SAMPLING_PIN                       GPIO_PIN_12
#define TSCx_TS1_SAMPLING_GPIO_PORT                 GPIOD
#define TSCx_TS1_SAMPLING_AF                        GPIO_AF3_TSC

#define TSCx_TS2_SAMPLING_PIN                       GPIO_PIN_12
#define TSCx_TS2_SAMPLING_GPIO_PORT                 GPIOD
#define TSCx_TS2_SAMPLING_AF                        GPIO_AF3_TSC

#define TSCx_SHIELD_SAMPLING_PIN                    GPIO_PIN_11
#define TSCx_SHIELD_SAMPLING_GPIO_PORT              GPIOB
#define TSCx_SHIELD_SAMPLING_AF                     GPIO_AF3_TSC

/* Definition for TSCx's NVIC */
#define TSCx_EXTI_IRQn                              EXTI2_TSC_IRQn
#define TSCx_EXTI_IRQHandler                        EXTI2_TSC_IRQHandler

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */
