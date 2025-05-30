/**
  @page PWR_PVD PWR Programmable Voltage Detector (PVD) example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    PWR/PWR_PVD/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the PWR Programmable Voltage Detector (PVD) example
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
How to configure the programmable voltage detector by using an external interrupt 
line. External DC supply must be used to supply Vdd.

In this example, EXTI line 16 is configured to generate an interrupt on each rising
or falling edge of the PVD output signal (which indicates that the Vdd voltage is
moving below or above the PVD threshold). As long as the voltage is above the 
target threshold (2.5V), LED2 is blinking with a 200 ms-period; when the voltage drops
below the threshold, LED2 stops blinking and remains constantly on (or appears
to be turned off if the voltage is getting really low); when the voltage moves back
above the target threshold, LED2 starts blinking again.
If LED2 is slowly blinking (1 second-period), it means that the system has generated an error.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      
@par Directory contents 

  - PWR/PWR_PVD/Inc/stm32f3xx_hal_conf.h         HAL Configuration file
  - PWR/PWR_PVD/Inc/stm32f3xx_it.h           Header for stm32f3xx_it.c
  - PWR/PWR_PVD/Inc/main.h                   Header file for main.c
  - PWR/PWR_PVD/Src/system_stm32f3xx.c       STM32F3xx system clock configuration file
  - PWR/PWR_PVD/Src/stm32f3xx_it.c           Interrupt handlers
  - PWR/PWR_PVD/Src/main.c                   Main program

@par Hardware and Software environment

  - This example runs on STM32F303xE devices
    
  - This example has been tested with STMicroelectronics STM32F303RE-Nucleo Rev C
    board and can be easily tailored to any other supported device
    and development board.

  - STM32F303RE-Nucleo Rev C Set-up
    To apply an external power supply input, the user can
    - apply the E5V input in
      * resorting to Morpho connector CN7 pin 6 (pin 8 being used as GND)
      * moving jumper JP5 on pins 2 and 3
      * removing jumper JP1
    - or apply the +3V3 input
      * when ST-LINK part of PCB is cut or SB2 and SB12 are off or moving jumper JP5 on pins 2 and 3
      * resorting V+ to Morpho connector CN7 pins 12 and 16 or Arduino connector CN6 pin 4
      * resorting GND to Morpho connector CN7 pins 20or Arduino connector CN6 pin 6
    Next,         
    - apply an external voltage on the proper connector pins as selected above
    - check the board behavior according to LED2.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example



 */
