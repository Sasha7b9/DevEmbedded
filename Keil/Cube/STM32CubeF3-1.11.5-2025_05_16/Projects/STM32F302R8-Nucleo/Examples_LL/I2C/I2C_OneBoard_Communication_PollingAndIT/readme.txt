/**
  @page I2C_OneBoard_Communication_PollingAndIT I2C example (Master Polling Mode)
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    Examples_LL/I2C/I2C_OneBoard_Communication_PollingAndIT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C_OneBoard_Communication_PollingAndIT I2C example (Master Polling Mode).
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

How to transmit data bytes from an I2C master device using polling mode 
to an I2C slave device using interrupt mode. The peripheral is initialized 
with LL unitary service functions to optimize for performance and size.

This example guides you through the different configuration steps by mean of LL API
to configure GPIO and I2C peripherals using only one STM32F302R8-Nucleo Rev C.

I2C1 Peripheral is configured in Slave mode with EXTI (Clock 400Khz, Own address 7-bit enabled).
I2C2 Peripheral is configured in Master mode (Clock 400Khz).
GPIO associated to User push-button is linked with EXTI. 

LED2 blinks quickly to wait for user-button press. 

Example execution:
Press the User push-button to initiate a write request by Master through Handle_I2C_Master() routine.
This action will generate an I2C start condition with the Slave address and a write bit condition.
When address Slave match code is received on I2C1, an ADDR interrupt occurs.
I2C1 IRQ Handler routine is then checking Address Match Code and direction Write.
This will allow Slave to enter in receiver mode and then acknowledge Master to send the bytes.
When acknowledge is received on I2C2, a TXIS event occurs.
This will allow Master to transmit a byte to the Slave.
Each time a byte is received on I2C1 (Slave), an RXNE interrupt occurs until a STOP condition.
And so each time the Slave acknowledge the byte received a TXIS event occurs on Master side.
Master auto-generate a Stop condition when size of data to transmit is achieved.

The STOP condition generate a STOP interrupt and initiate the end of reception on Slave side.
I2C1 IRQ handler and Handle_I2C_Master() routine are then clearing the STOP flag in both side.

LED2 is On if data are well received.

In case of errors, LED2 is blinking.

@par Directory contents 

  - I2C/I2C_OneBoard_Communication_PollingAndIT/Inc/stm32f3xx_it.h          Interrupt handlers header file
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Inc/main.h                  Header for main.c module
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Src/stm32f3xx_it.c          Interrupt handlers
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Src/main.c                  Main program
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Src/system_stm32f3xx.c      STM32F3xx system source file

@par Hardware and Software environment

  - This example runs on STM32F302x8 devices.
    
  - This example has been tested with STM32F302R8-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32F302R8-Nucleo Rev C Set-up
    - Connect GPIOs connected to I2C1 SCL/SDA (PB.8 and PB.9)
    to respectively SCL and SDA pins of I2C2 (PA.9 and PA.10).
      - I2C1_SCL  PB.8 (CN10, pin 3) : connected to I2C2_SCL PA.9 (CN10, pin 21) 
      - I2C1_SDA  PB.9 (CN10, pin 5) : connected to I2C2_SDA PA.10 (CN10, pin 33)

  - Launch the program. Press User push-button to initiate a write request by Master 
      then Slave receive bytes.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 */
