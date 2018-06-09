#include <kernel/uart.h>
#include <stddef.h>
#include <stdint.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags){
	(void) r0;
	(void) r1;
	(void) atags;
	
	uart_init();
	uart_puts("Hi this is Keith's raspberry pi kernel :)\r\n");
	uart_puts("Anyting you'd like to say:");
	
	while(1){
		uart_putc(uart_getc());
	}

}


