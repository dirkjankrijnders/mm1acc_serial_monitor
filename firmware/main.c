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
#include <dcc_decode.h>

int main(void)
{
	DDRB |= (1 << PB2); // Ack
	acc_data data;
	char buf[50];
	t_message dcc_data;
	state_t state;
	unsigned char decode_state = 0;
	
	mm1acc_init();
	init_dcc_decode();
	
	uart_init(UART_BAUD_SELECT(38400, F_CPU));
	uart_puts("mm1acc serial monitor\n");
	sei();
	uint8_t	b = 0;
	uint8_t	crc = 0;
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
		if (mm1acc_check(&data) == MM1_VALID) {
			sprintf(buf, "M0x%.2x - 0x%.2x %x\n", data.address, data.port, data.function);
			uart_puts(buf);
		}
		if ((state = dccacc_check(&dcc_data)) == DCC_VALID) {
			//if (dcc_data.dcc[0] < 128) {
			if (dcc_data.dcc[0] == 0 && dcc_data.dcc[1] == 0 && dcc_data.size == 2) {
				sprintf(buf, ".");
				uart_puts(buf);
			} else {
				if ((decode_state = analyze_message(&dcc_data)) > 0) {
				sprintf(buf, "D0x%.2x - ", state);
				uart_puts(buf);
				crc = 0;
				for (b = 0;b < dcc_data.size; b++) {
					crc = (crc ^ dcc_data.dcc[b]);
					sprintf(buf, "0x%.2x ", dcc_data.dcc[b]);
					uart_puts(buf);
				}
				sprintf(buf, "0x%.2x ", crc);
				uart_puts(buf);
				if (crc == 0) {
					sprintf(buf, "r: 0x%.2x", decode_state);
				}
				uart_puts(buf);
				sprintf(buf, "\n");
/*				uint8_t	val =0x62;
				switch (dcc_data[0]) {
					case 0x78:
						// Read CV
						if ((dcc_data[2] & 0b11101000) == 0b11101000) {
							uint8_t	bit = (1 << (dcc_data[2] & 0x7));
							if ((val & bit) > 0) {
								ack();
							}
						}
						break;
						
					default:
						break;
				}*/
					uart_puts(buf);
				}
			}
		}
		
    }
    return 0;   /* never reached */
}
