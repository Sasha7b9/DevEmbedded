/**
  ******************************************************************************
  * @file    SPI/SPI_FullDuplex_ComIT/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use STM32F3xx SPI HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          Interrupt transfer.
  *          The communication is done using 2 Boards.
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

/** @addtogroup SPI_FullDuplex_ComIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
enum {
	TRANSFER_WAIT,
	TRANSFER_COMPLETE,
	TRANSFER_ERROR
};

/* Private macro -------------------------------------------------------------*/
/* Uncomment this line to use the board as master, if not it is used as slave */
//#define MASTER_BOARD

/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
SPI_HandleTypeDef SpiHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = "****SPI - Two Boards communication based on Interrupt **** SPI Message ******** SPI Message ******** SPI Message ****";

/* Buffer used for reception */
uint8_t aRxBuffer[BUFFERSIZE];

/* transfer state */
__IO uint32_t wTransferState = TRANSFER_WAIT;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Error_Handler(void);
static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength);

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

  /* Configure LED1, LED2 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);

  /*##-1- Configure the SPI peripheral #######################################*/
  /* Set the SPI parameters */
  SpiHandle.Instance               = SPIx;
  SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
  SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
  SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
  SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  SpiHandle.Init.CRCPolynomial     = 7;
  SpiHandle.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;
  SpiHandle.Init.NSS               = SPI_NSS_SOFT;
  SpiHandle.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;

#ifdef MASTER_BOARD
  SpiHandle.Init.Mode = SPI_MODE_MASTER;
#else
  SpiHandle.Init.Mode = SPI_MODE_SLAVE;
#endif /* MASTER_BOARD */

  if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
#ifdef MASTER_BOARD
  /* Configure Key push-button button */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  /* Wait for Key push-button press before starting the Communication */
  while (BSP_PB_GetState(BUTTON_KEY) != GPIO_PIN_RESET)
  {
    BSP_LED_Toggle(LED1);
    HAL_Delay(100);
  }
  BSP_LED_Off(LED1);
#endif /* MASTER_BOARD */

  /*##-2- Start the Full Duplex Communication process ########################*/  
  /* While the SPI in TransmitReceive process, user can transmit data through 
     "aTxBuffer" buffer & receive data through "aRxBuffer" */
  if(HAL_SPI_TransmitReceive_IT(&SpiHandle, (uint8_t*)aTxBuffer, (uint8_t *)aRxBuffer, BUFFERSIZE) != HAL_OK)
  {
    /* Transfer error in transmission process */
    Error_Handler();
  }

  /*##-3- Wait for the end of the transfer ###################################*/  
  /*  Before starting a new communication transfer, you must wait the callback call 
      to get the transfer complete confirmation or an error detection.
      For simplicity reasons, this example is just waiting till the end of the 
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */  
  while (wTransferState == TRANSFER_WAIT)
  {
  }
  
  switch(wTransferState)
  {
    case TRANSFER_COMPLETE :
      /*##-4- Compare the sent and received buffers ##############################*/
      if(Buffercmp((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, BUFFERSIZE))
      {
        /* Processing Error */
        Error_Handler();     
      }
    break;
    default : 
      Error_Handler();
    break;
  }

  /* Infinite loop */  
  while (1)
  {
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
  *            HSE PREDIV                     = RCC_PREDIV_DIV1 (1)
  *            PLLMUL                         = RCC_PLL_MUL9 (9)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
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
    /* Initialization Error */
    while(1); 
  }
}
/**
  * @brief  TxRx Transfer completed callback.
  * @param  hspi: SPI handle
  * @note   This example shows a simple way to report end of Interrupt TxRx transfer, and 
  *         you can add your own implementation. 
  * @retval None
  */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Turn LED on: Transfer in transmission process is correct */
  BSP_LED_On(LED1);
  /* Turn LED on: Transfer in reception process is correct */
  BSP_LED_On(LED2);
  wTransferState = TRANSFER_COMPLETE;
}

/**
  * @brief  SPI error callbacks.
  * @param  hspi: SPI handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  wTransferState = TRANSFER_ERROR;
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
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 0  : pBuffer1 identical to pBuffer2
  *         >0 : pBuffer1 differs from pBuffer2
  */
static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if ((*pBuffer1) != *pBuffer2)
    {
      return BufferLength;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
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
