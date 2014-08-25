/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include <mm1acc.h>
#include <uart.h>

int main(void)
{
	acc_data data;
	char buf[17];
	mm1acc_init();
	uart_init(UART_BAUD_SELECT(38400, F_CPU));
	uart_puts("mm1acc serial monitor\n");
	sei();
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
		if (mm1acc_check(&data)) {
			sprintf(buf, "M0x%.2x - 0x%.2x %x\n", data.address, data.port, data.function);
			uart_puts(buf);
		}
    }
    return 0;   /* never reached */
}
