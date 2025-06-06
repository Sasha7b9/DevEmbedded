/*!
    \file  main.c
    \brief use the I2C bus to write and read EEPROM

    \version 2025-02-10, V2.4.0, demo for GD32E23x
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

#include <stdio.h>
#include "gd32e231k_eval.h"
#include "systick.h"
#include "i2c.h"
#include "at24cxx.h"

uint8_t count = 0;

void led_config(void);

/*!
    \brief      configure the LEDs
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_config(void)
{
    gd_eval_led_init(LED1);

    /* turn off LED1 */
    gd_eval_led_off(LED1);
}

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* configure systick */
    systick_config();

    /* configure LED1 */
    led_config();

    /* configure USART */
    gd_eval_com_init(EVAL_COM);

    printf("I2C-24C02 configured....\n\r");

    /* configure GPIO */
    gpio_config();

    /* configure I2C */
    i2c_config();

    /* initialize EEPROM */
    i2c_eeprom_init();

    printf("\r\nThe I2C is hardware interface ");
    printf("\r\nThe speed is %dK", I2C0_SPEED/1000);

    if(I2C_OK == i2c_24c02_test()) {
        while(1) {
            /* turn off LED1 */
            gd_eval_led_off(LED1);
            delay_1ms(500);

            /* turn on LED1 */
            gd_eval_led_on(LED1);
            delay_1ms(500);
        }
    }
    /* turn on LED1 */
    gd_eval_led_on(LED1);


    while(1);

}

#ifdef GD_ECLIPSE_GCC
/* retarget the C library printf function to the usart, in Eclipse GCC environment */
int __io_putchar(int ch)
{
    usart_data_transmit(EVAL_COM, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM, USART_FLAG_TBE));
    return ch;
}
#else
/* retarget the C library printf function to the usart */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM, USART_FLAG_TBE));
    return ch;
}
#endif /* GD_ECLIPSE_GCC */
