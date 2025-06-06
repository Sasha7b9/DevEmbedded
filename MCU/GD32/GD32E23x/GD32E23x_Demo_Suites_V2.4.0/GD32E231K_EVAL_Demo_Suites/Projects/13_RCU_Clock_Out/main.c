/*!
    \file    main.c
    \brief   RCU clock out demo

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

#include "gd32e23x.h"
#include "gd32e231k_eval.h"
#include "systick.h"
#include <stdio.h>

typedef enum {
    CKOUT_SYSTEMCLOCK_CKOUT = 0,
    CKOUT_IRC8M_CKOUT,
    CKOUT_IRC28M_CKOUT,
    CKOUT_IRC40K_CKOUT,
    CKOUT_HXTAL_CKOUT,
    CKOUT_PLL_DIV2_CKOUT,
    CKOUT_COUNT
} clock_output_enum;

void all_led_init(void);
void all_led_off(void);
void clock_output_config(void);
void clock_output_select(uint8_t seq);

extern __IO uint8_t g_button_press_flag;

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    uint8_t func_seq = 0;
    uint8_t led_seq = 0;

    /* initialize the USART */
    gd_eval_com_init(EVAL_COM);

    printf("\r\n /=========== Gigadevice Clock output Demo ===========/ \r\n");
    printf("press User key to select clock output source \r\n");

    /* initialize the LEDs */
    all_led_init();
    /* initialize the clock output */
    clock_output_config();
    /* initialize the tamper key */
    gd_eval_key_init(KEY_USER, KEY_MODE_EXTI);
    /* configure the systick */
    systick_config();

    while(1) {
        if(1 == g_button_press_flag) {
            /* control the led */
            all_led_off();
            gd_eval_led_on((led_typedef_enum)led_seq);
            /* select the clock output mode */
            clock_output_select(func_seq);

            func_seq++;
            func_seq %= CKOUT_COUNT;
            led_seq++;
            led_seq %= LEDn;

            g_button_press_flag = 0;
        }
    }
}

/*!
    \brief      initialize the LEDs
    \param[in]  none
    \param[out] none
    \retval     none
*/
void all_led_init(void)
{
    gd_eval_led_init(LED1);
}

/*!
    \brief      all LEDs turn off
    \param[in]  none
    \param[out] none
    \retval     none
*/
void all_led_off(void)
{
    gd_eval_led_off(LED1);
}

/*!
    \brief      configure clock output function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void clock_output_config(void)
{
    /* peripheral clock enable */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable IRC8M */
    rcu_osci_on(RCU_IRC8M);
    if(ERROR == rcu_osci_stab_wait(RCU_IRC8M)) {
        printf("RCU_IRC8M rcu_osci_stab_wait timeout! \r\n");
        while(1);
    }

    /* enable HXTAL */
    rcu_osci_on(RCU_HXTAL);
    if(ERROR == rcu_osci_stab_wait(RCU_HXTAL)) {
        printf("RCU_HXTAL rcu_osci_stab_wait timeout! \r\n");
        while(1);
    }

    /* enable IRC28M */
    rcu_osci_on(RCU_IRC28M);
    if(ERROR == rcu_osci_stab_wait(RCU_IRC28M)) {
        printf("RCU_IRC28M rcu_osci_stab_wait timeout! \r\n");
        while(1);
    }

    /* enable IRC40K */
    rcu_osci_on(RCU_IRC40K);
    if(ERROR == rcu_osci_stab_wait(RCU_IRC40K)) {
        printf("RCU_IRC40K rcu_osci_stab_wait timeout! \r\n");
        while(1);
    }

    /* enable PLL */
    rcu_osci_on(RCU_PLL_CK);
    if(ERROR == rcu_osci_stab_wait(RCU_PLL_CK)) {
        printf("RCU_PLL_CK rcu_osci_stab_wait timeout! \r\n");
        while(1);
    }

    /* configure clock output pin */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_8);
}

/*!
    \brief      select type of clock output
    \param[in]  seq: sequence of clock output
    \param[out] none
    \retval     none
*/
void clock_output_select(uint8_t seq)
{
    switch(seq) {
    case CKOUT_SYSTEMCLOCK_CKOUT:
        rcu_ckout_config(RCU_CKOUTSRC_CKSYS, RCU_CKOUT_DIV1);
        printf("CK_OUT: system clock \r\n");
        break;
    case CKOUT_IRC8M_CKOUT:
        rcu_ckout_config(RCU_CKOUTSRC_IRC8M, RCU_CKOUT_DIV1);
        printf("CK_OUT: IRC8M \r\n");
        break;
    case CKOUT_IRC28M_CKOUT:
        rcu_ckout_config(RCU_CKOUTSRC_IRC28M, RCU_CKOUT_DIV1);
        printf("CK_OUT: IRC28M \r\n");
        break;
    case CKOUT_IRC40K_CKOUT:
        rcu_ckout_config(RCU_CKOUTSRC_IRC40K, RCU_CKOUT_DIV1);
        printf("CK_OUT: IRC40K \r\n");
        break;
    case CKOUT_HXTAL_CKOUT:
        rcu_ckout_config(RCU_CKOUTSRC_HXTAL, RCU_CKOUT_DIV1);
        printf("CK_OUT: HXTAL \r\n");
        break;
    case CKOUT_PLL_DIV2_CKOUT:
        rcu_ckout_config(RCU_CKOUTSRC_CKPLL_DIV2, RCU_CKOUT_DIV1);
        printf("CK_OUT: PLL/2 \r\n");
        break;

    default:
        printf("clock output select parameter error! \r\n");
        while(1);
    }
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
