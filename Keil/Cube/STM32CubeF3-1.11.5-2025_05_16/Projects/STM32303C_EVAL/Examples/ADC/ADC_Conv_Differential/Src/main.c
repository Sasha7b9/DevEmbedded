/**
  ******************************************************************************
  * @file    ADC/ADC_Conv_Differential/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to use ADC differential mode.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F3xx_HAL_Examples
  * @{
  */

/** @addtogroup ADC_TriggerMode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MIDRANGE_12BITS         2048    /* Mid-range value for a full range of 12 bits (4096 values) */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ADC handler declaration */
ADC_HandleTypeDef    AdcHandle;

/* DAC handler declaration */
DAC_HandleTypeDef    DacHandle;

/* Variable containing ADC conversions results */
__IO uint16_t   uhADCxConvertedValue = 0;

/* Variable to count number of clicks of push button on board */
uint32_t        UserButtonClickCount = 0;  /* Incremented after User Button interrupt  */

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void EXTILine9_5_Config(void);
static void ADC_Config(void);
static void DAC_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32F3xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();
   
  /* Configure the system clock to 72 MHz */
  SystemClock_Config();

  
  /*## Configuration of peripherals ##########################################*/
  /* Initialize LEDs on board */
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  
  /* initialize the User push-button in Interrupt mode */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
  
  /* Configure EXTI_Line9_5 in interrupt mode */
  EXTILine9_5_Config();  

  /* Configuration of DAC peripheral */
  DAC_Config();
  
  /* Configuration of ADC peripheral */
  ADC_Config();



  /*## Enable peripherals ####################################################*/

  /* Set DAC Channel data register: channel corresponding to ADC differential high input */
  /* DAC output set to 1/2 of full range (4095 <=> Vdda=3.3V): 2048 <=> 1.65V */
  if (HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_HIGH, DAC_ALIGN_12B_R, 2048) != HAL_OK)
  {
    /* Setting value Error */
    Error_Handler();
  }

  /* Set DAC Channel data register: channel corresponding to ADC differential low input */
  /* DAC output set to 1/4 of full range (4095 <=> Vdda=3.3V): 1023 <=> 0.825V */
  if (HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_LOW, DAC_ALIGN_12B_R, 0) != HAL_OK)
  {
    /* Setting value Error */
    Error_Handler();
  }
  
  /* Enable DAC Channel: channel corresponding to ADC differential high input */
  if (HAL_DAC_Start(&DacHandle, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_HIGH) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }
  
  /* Enable DAC Channel: channel corresponding to ADC differential low input */
  if (HAL_DAC_Start(&DacHandle, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_LOW) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }
  
  /*## Start ADC conversions #################################################*/
  /* Run the ADC calibration in differential mode */  
  if (HAL_ADCEx_Calibration_Start(&AdcHandle, ADC_DIFFERENTIAL_ENDED) != HAL_OK)
  {
    /* Start Conversation Error */
    Error_Handler();
  }
  
  /* Start ADC conversion on regular group with interruption */
  if (HAL_ADC_Start_IT(&AdcHandle) != HAL_OK)
  {
    /* Start Conversation Error */
    Error_Handler();
  }
  
  /* Infinite loop */
  while (1)
  {
    /* Set DAC voltage on channel corresponding to ADC differential low input */
    /* in function of user button clicks count.                               */
    switch (UserButtonClickCount)
    {
    default:
    case 0:
      HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_LOW, DAC_ALIGN_12B_R, 0);
      break;
    case 1:
      HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_LOW, DAC_ALIGN_12B_R, 1023);
      break;
    case 2:
      HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_LOW, DAC_ALIGN_12B_R, 2048);
      break;
    case 3:
      HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_LOW, DAC_ALIGN_12B_R, 3071);
      break;
    case 4:
      HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_LOW, DAC_ALIGN_12B_R, 4095);
      break;

    }
    
    /* ADC Differential conversion result calculation:                        */
    /*  - An offset of half of full range is added to keep the full dynamic   */
    /*    range of differential voltage.                                      */
    /*  - Channels voltage is divided by 2, resolution is lowered of 1 bit.   */
    /*  => Diff conversion result = mid-range + (channel_high-channel_low)/2  */

    /* Turn-on/off LED in function of ADC differential conversion result */
    /*  - Turn-on LED if differential voltage is positive */
    /*  - Turn-off LED if differential voltage is negative */
    if (uhADCxConvertedValue > MIDRANGE_12BITS)
    {
      BSP_LED_On(LED2);
    }
    else
    {
      BSP_LED_Off(LED2);
    }
  }
  
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV                     = 1
  *            PLLMUL                         = RCC_PLL_MUL9 (9)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }
    	
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED3 on */
  BSP_LED_On(LED3);
  while (1)
  {
  }
}

/**
  * @brief  ADC configuration
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
  ADC_ChannelConfTypeDef sConfig;

  /* Configuration of ADC2 init structure: ADC parameters and regular group */
  AdcHandle.Instance = ADCx;
  
  AdcHandle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.ScanConvMode = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
  AdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  AdcHandle.Init.LowPowerAutoWait = DISABLE;
  AdcHandle.Init.ContinuousConvMode = ENABLE;                  /* Continuous mode to have conversions kept running after 1st conversion trig */
  AdcHandle.Init.NbrOfConversion = 1;                          /* Parameter discarded because sequencer is disabled */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;              /* Parameter discarded because sequencer is disabled */
  AdcHandle.Init.NbrOfDiscConversion = 1;                      /* Parameter discarded because sequencer is disabled */
  AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;        /* Software start to trig the 1st conversion manually, without external event */
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.DMAContinuousRequests = DISABLE;
  AdcHandle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    /* ADC Initiliazation Error */
    Error_Handler();
  }
 
  /* Configuration of channel on ADC2 regular group on rank 1 */
  /* Differential mode: only the ADC channel positive has to be configured.   */
  /*                    The negative input is configured automatically        */
  /* Note: With ADC in IT mode, select sampling time and ADC clock not too    */
  /*       fast to not create an overhead situation in IRQHandler.            */
  sConfig.Channel = ADCx_CHANNEL_DIFF_HIGH;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_181CYCLES_5;
  sConfig.SingleDiff = ADC_DIFFERENTIAL_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    /* Channel Configuration Error */
    Error_Handler();
  }
  
}

/**
  * @brief  Configures EXTI Line9-5 in interrupt mode
  * @param  None
  * @retval None
  */
static void EXTILine9_5_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable clock of push button GPIO */
  __HAL_RCC_GPIOx_CLK_ENABLE();
  
  /* Configure User Button, connected to PE6 IOs in External Interrupt Mode with Falling edge trigger detection. */
  GPIO_InitStructure.Pin = KEY_BUTTON_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(KEY_BUTTON_GPIO_PORT, &GPIO_InitStructure);

  /* Enable and set EXTI Line9_5 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/**
  * @brief  DAC configuration
  * @param  None
  * @retval None
  */
static void DAC_Config(void)
{
  static DAC_ChannelConfTypeDef sConfig;

  /* Configuration of DACx peripheral */
  DacHandle.Instance = DACx;

  if (HAL_DAC_Init(&DacHandle) != HAL_OK)
  {
    /* DAC Initiliazation Error */
    Error_Handler();
  }

  /* Configuration of DACx channel 1 */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;

  if (HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_HIGH) != HAL_OK)
  {
    /* Channel configuration Error */
    Error_Handler();
  }
  
  /* Configuration of DACx channel 2 */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;

  if (HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DACx_CHANNEL_TO_ADCx_CHANNEL_DIFF_LOW) != HAL_OK)
  {
    /* Channel configuration Error */
    Error_Handler();
  }
  
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == KEY_BUTTON_PIN)
  {
    /* Manage UserButtonClickCount to increment it circularly from 0 to 4 */
    if (UserButtonClickCount < 4)
    {
      UserButtonClickCount++;
    }      
    else
    {
      UserButtonClickCount=0;
    }
    
  }
}

/**
  * @brief  Conversion complete callback in non blocking mode
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
  /* Get the converted value of regular channel */
  uhADCxConvertedValue = HAL_ADC_GetValue(AdcHandle);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */
