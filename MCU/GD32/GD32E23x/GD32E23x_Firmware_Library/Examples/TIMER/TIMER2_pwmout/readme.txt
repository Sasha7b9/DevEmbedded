/*!
    \file    readme.txt
    \brief   description of the TIMER2 PWM output demo for gd32e23x

    \version 2025-02-10, V2.3.0, firmware for GD32E23x
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

  This demo is based on the GD32E230C-EVAL-V1.1 board, it shows how to configure the 
TIMER peripheral in PWM (Pulse Width Modulation) mode.
  
  The TIMERxCLK frequency is set to systemcoreclock, the prescaler is 72 so the 
TIMER2 counter clock is 1MHz, and the PWM frequency is 62.5Hz.
  
  TIMER2 Channel0 duty cycle = (4000/ 16000)* 100  = 25%.
  TIMER2 Channel1 duty cycle = (8000/ 16000)* 100  = 50%.
  TIMER2 Channel2 duty cycle = (12000/ 16000)* 100 = 75%.

  Connect the TIMER2 pins to an oscilloscope to monitor the different waveforms:
    - TIMER2_CH0 pin(PA6)
    - TIMER2_CH1 pin(PA7)
    - TIMER2_CH2 pin(PB0)
