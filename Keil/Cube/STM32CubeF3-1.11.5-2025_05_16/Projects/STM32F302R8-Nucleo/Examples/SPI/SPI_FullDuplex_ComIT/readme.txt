/**
  @page SPI_FullDuplex_ComIT SPI Full Duplex IT example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    SPI/SPI_FullDuplex_ComIT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the SPI Full Duplex IT example.
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
  @endverbatim

@par Example Description 

Data buffer transmission/reception between two boards via SPI using Interrupt mode.

   _________________________                        _________________________
  |       ________CN7_______|                      |_______CN7__________     |
  |      |SPI3              |                      |              SPI3  |    |
  |      |                  |                      |                    |    |
  |      |(pin 1)  CLK(PC10)|______________________|(PC10)CLK  (pin 1)  |    |
  |      |                  |                      |                    |    |
  |      |(pin 2) MISO(PC11)|______________________|(PC11)MISO (pin 2)  |    |
  |      |                  |                      |                    |    |
  |      |(pin 3) MOSI(PC12)|______________________|(PC12)MOSI (pin 3)  |    |
  |      |                  |                      |                    |    |
  |      |__________________|                      |____________________|    |
  |                      GND|______________________|GND                      |
  |                         |                      |                         |
  |_STM32F3 Master _________|                      |_STM32F3 Slave __________|

HAL architecture allows user to easily change code to move to DMA or Polling 
mode. To see others communication modes please check following examples:
SPI\SPI_FullDuplex_ComDMA
SPI\SPI_FullDuplex_ComPolling

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 72 MHz.

The SPI peripheral configuration is ensured by the HAL_SPI_Init() function.
This later is calling the HAL_SPI_MspInit()function which core is implementing
the configuration of the needed SPI resources according to the used hardware (CLOCK, 
GPIO and NVIC). You may update this function to change SPI configuration.

The SPI communication is then initiated.
The HAL_SPI_TransmitReceive_IT() function allows the reception and the 
transmission of a predefined data buffer at the same time (Full Duplex Mode) 
The user can choose between Master and Slave through "#define MASTER_BOARD"
in the "main.c" file.
If the Master board is used, the "#define MASTER_BOARD" must be uncommented.
If the Slave board is used the "#define MASTER_BOARD" must be commented.

For this example the aTxBuffer is predefined and the aRxBuffer size is same as aTxBuffer.

In a first step after the user press the User push-button, SPI Master starts the
communication by sending aTxBuffer and receiving aRxBuffer through 
HAL_SPI_TransmitReceive_IT(), at the same time SPI Slave transmits aTxBuffer 
and receives aRxBuffer through HAL_SPI_TransmitReceive_IT(). 
The callback functions (HAL_SPI_TxRxCpltCallback and HAL_SPI_ErrorCallbackand) update 
the variable wTransferState used in the main function to check the transfer status.
Finally, aRxBuffer and aTxBuffer are compared through Buffercmp() in order to 
check buffers correctness.  

STM32 board's LEDs can be used to monitor the transfer status:
 - LED2 toggles quickly on master board waiting User push-button to be pressed.
 - LED2 turns ON if transmission/reception is complete and OK.
 - LED2 toggles slowly when there is a timeout or an error in transmission/reception process.   

@note SPIx instance used and associated resources can be updated in "main.h"
      file depending hardware configuration used.

@note You need to perform a reset on Slave board, then perform it on Master board
      to have the correct behaviour of this example.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - SPI/SPI_FullDuplex_ComIT/Inc/stm32f3xx_hal_conf.h    HAL configuration file
  - SPI/SPI_FullDuplex_ComIT/Inc/stm32f3xx_it.h          Interrupt handlers header file
  - SPI/SPI_FullDuplex_ComIT/Inc/main.h                  Header for main.c module  
  - SPI/SPI_FullDuplex_ComIT/Src/stm32f3xx_it.c          Interrupt handlers
  - SPI/SPI_FullDuplex_ComIT/Src/main.c                  Main program
  - SPI/SPI_FullDuplex_ComIT/Src/system_stm32f3xx.c      stm32f3xx system source file
  - SPI/SPI_FullDuplex_ComIT/Src/stm32f3xx_hal_msp.c     HAL MSP file

@par Hardware and Software environment

  - This example runs on STM32F302xx devices.

  - This example has been tested with STM32F302R8-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32F302R8-Nucleo Rev C Set-up
    - Connect Master board PC10 to Slave Board PC10 (pin 1 on CN7 connector)
    - Connect Master board PC11 to Slave Board PC11 (pin 2 on CN7 connector)
    - Connect Master board PC12 to Slave Board PC12 (pin 3 on CN7 connector)
    - Connect Master board GND  to Slave Board GND

@par How to use it ? 

In order to make the program work, you must do the following:
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
    o Uncomment "#define MASTER_BOARD" and load the project in Master Board
    o Comment "#define MASTER_BOARD" and load the project in Slave Board
 - Run the example


 */
 