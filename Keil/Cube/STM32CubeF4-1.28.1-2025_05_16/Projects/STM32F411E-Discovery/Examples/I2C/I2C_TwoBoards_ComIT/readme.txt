/**
  @page I2C_TwoBoards_ComIT I2C Two Boards Communication IT example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    I2C/I2C_TwoBoards_ComIT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C Two Boards IT Communication example.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
   @endverbatim

@par Example Description 

How to handle I2C data buffer transmission/reception between two boards, 
using an interrupt.

   _________________________                        _________________________
  |           ______________|                      |______________           |
  |          | I2C1         |                      |          I2C1|          |
  |          |              |                      |              |          |
  |          |      SCL(PB6)|______________________|(PB6)SCL      |          |
  |          |              |                      |              |          |
  |          |              |                      |              |          |
  |          |              |                      |              |          |
  |          |      SDA(PB9)|______________________|(PB9)SDA      |          |
  |          |              |                      |              |          |
  |          |______________|                      |______________|          |
  |      __                 |                      |      __                 |
  |     |__|                |                      |     |__|                |
  |     USER                |                      |     USER                |
  |                      GND|______________________|GND                      |
  |_STM32F4 ________________|                      |_________________STM32F4_|

This example guides you through the different configuration steps by mean of HAL API 
to ensure I2C Data buffer transmission and reception using Interrupt.
The communication is done with 2 Boards through I2C.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 84 MHz.

The I2C peripheral configuration is ensured by the HAL_I2C_Init() function.
This later is calling the HAL_I2C_MspInit()function which core is implementing
the configuration of the needed I2C resources according to the used hardware (CLOCK, 
GPIO and NVIC). You may update this function to change I2C configuration.

The I2C communication is then initiated.
The project is split in two parts the Master Board and the Slave Board
- Master Board
  The HAL_I2C_Master_Receive_IT() and the HAL_I2C_Master_Transmit_IT() functions 
  allow respectively the reception and the transmission of a predefined data buffer
  in Master mode.
- Slave Board
  The HAL_I2C_Slave_Receive_IT() and the HAL_I2C_Slave_Transmit_IT() functions 
  allow respectively the reception and the transmission of a predefined data buffer
  in Slave mode.
The user can choose between Master and Slave through "#define MASTER_BOARD"
in the "main.c" file.
If the Master board is used, the "#define MASTER_BOARD" must be uncommented.
If the Slave board is used the "#define MASTER_BOARD" must be commented.

For this example the aTxBuffer is predefined and the aRxBuffer size is same as aTxBuffer.

In a first step after the user press the User Button on the Master Board, I2C Master 
starts the communication by sending aTxBuffer through HAL_I2C_Master_Transmit_IT() to 
I2C Slave which receives aRxBuffer through HAL_I2C_Slave_Receive_IT(). 
The second step starts when the user press the User Button on the Master Board,
the I2C Slave sends aTxBuffer through HAL_I2C_Slave_Transmit_IT()
to the I2C Master which receives aRxBuffer through HAL_I2C_Master_Receive_IT().
The end of this two steps are monitored through the HAL_I2C_GetState() function
result.
Finally, aRxBuffer and aRxBuffer are compared through Buffercmp() in order to 
check buffers correctness.  

STM32 Discovery boards LEDs can be used to monitor the transfer status:
 - LED4 is ON when the transmission process is complete.
 - LED6 is ON when the reception process is complete.
 - LED5 is ON when there is an error in transmission/reception process.  

@note I2Cx instance used and associated resources can be updated in "main.h"
       file depending hardware configuration used.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Connectivity, Communication, I2C, Interrupt, Master, Slave, Transmission, Reception, Fast mode plus

@par Directory contents 

  - I2C/I2C_TwoBoards_ComIT/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - I2C/I2C_TwoBoards_ComIT/Inc/stm32f4xx_it.h          I2C interrupt handlers header file
  - I2C/I2C_TwoBoards_ComIT/Inc/main.h                  Main program header file  
  - I2C/I2C_TwoBoards_ComIT/Src/stm32f4xx_it.c          I2C interrupt handlers
  - I2C/I2C_TwoBoards_ComIT/Src/main.c                  Main program
  - I2C/I2C_TwoBoards_ComIT/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file
  - I2C/I2C_TwoBoards_ComIT/Src/stm32f4xx_hal_msp.c     HAL MSP module    


@par Hardware and Software environment

  - This example runs on STM32F411xE devices.
    
  - This example has been tested with STM32F411E-Discovery board and can be
    easily tailored to any other supported device and development board.    
      
  - STM32F411E-Discovery Set-up
    - Connect Master board PB6 to Slave Board PB6
    - Connect Master board PB9 to Slave Board PB9
    - Connect Master board GND to Slave Board GND


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
    o Uncomment "#define MASTER_BOARD" and load the project in Master Board
    o Comment "#define MASTER_BOARD" and load the project in Slave Board
 - Run the example


 */
