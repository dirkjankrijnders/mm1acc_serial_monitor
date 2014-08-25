/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <stdio.h>

#include <mm1acc.h>
#include <uart.h>

int main(void)
{
	acc_data data;
	char buf[16];
	mm1acc_init();
	uart_init(UART_BAUD_SELECT(76800, F_CPU));
	uart_puts("mm1acc serial monitor");
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
		if (mm1acc_check(&data)) {
			sprintf(buf, "M0x%.2x - 0x%.2x %x", data.address, data.port, data.function);
			uart_puts(buf);
		}
    }
    return 0;   /* never reached */
}
