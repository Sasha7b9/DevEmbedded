/**
  ******************************************************************************
  * @file    COMP/COMP_AnalogWatchdog/Inc/main.h 
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
#include "stm32f3xx_hal.h"
#include "stm32303c_eval.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor COMPx instance used and associated 
   resources */
/* Definition for COMPx clock resources */
#define COMPx                           COMP1
#define COMPx_CLK_ENABLE()              __HAL_RCC_SYSCFG_CLK_ENABLE()
#define COMPx_INPUT_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define COMPx_OUTPUT_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

#define COMPx_FORCE_RESET()             __HAL_RCC_SYSCFG_FORCE_RESET()
#define COMPx_RELEASE_RESET()           __HAL_RCC_SYSCFG_RELEASE_RESET()

/* Definition for COMPx Channel Pin */
#define COMPx_INPUT_PIN                 GPIO_PIN_1
#define COMPx_OUTPUT_PIN                GPIO_PIN_0
#define COMPx_OUTPUT_AF                 GPIO_AF8_COMP1
#define COMPx_INPUT_GPIO_PORT           GPIOA 
#define COMPx_OUTPUT_GPIO_PORT          GPIOA 

/* Definition for TIMx clock resources */
#define TIMx                            TIM1
#define TIMx_CLK_ENABLE()               __HAL_RCC_TIM1_CLK_ENABLE()
#define TIMx_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()

/* Definition for TIMx Pin */
#define TIMx_PIN                        GPIO_PIN_9
#define TIMx_AF                         GPIO_AF6_TIM1
#define TIMx_GPIO_PORT                  GPIOA 

#define TIMx_FORCE_RESET()              __HAL_RCC_TIM1_FORCE_RESET()
#define TIMx_RELEASE_RESET()            __HAL_RCC_TIM1_RELEASE_RESET()
#endif /* __MAIN_H */
