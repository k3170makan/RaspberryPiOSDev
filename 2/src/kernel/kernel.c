#include <kernel/uart.h>
#include <common/stdlib.h>

#include <stddef.h>
#include <stdint.h>


typedef enum {
	ATAG_NONE	   = 0x00000000,
	ATAG_CORE	   = 0x54410001, 
	ATAG_MEM 	   = 0x54410002,
	ATAG_VIDEOTEXT = 0x54410003,
	ATAG_RAMDISK   = 0x54410004,
	ATAG_INITRD2	= 0x54420005,
	ATAG_SERIAL		= 0x54410006,
	ATAG_REVISION  = 0x54410007,
	ATAG_VIDEOLFB  = 0x54410008,
	ATAG_CMDLINE 	= 0x54410009
} atag_tag_t;

typedef struct {
	uint32_t size;
	uint32_t start;
} mem_t;


typedef struct {
	uint32_t size;
	uint32_t start;
} initrd2_t;


typedef struct {
	char line[1];
} cmdline_t;


typedef struct {
	uint32_t tag_size;
	atag_tag_t tag_type;
	union {
		mem_t mem;
		initrd2_t initrd2;
		cmdline_t cmdline;
	};
} atag_t;

atag_t * to_next_tag(atag_t* tag){
	return ((uint32_t *) tag) + tag->tag_size;
}

/**
char[] log_atag(atag_t *atag){
	char print_line[15] = 	"[*] MEM TAG [";
	char print_end[1] = 	"]";
	return print_line + itoa(atag.mem->size) + " % " + 
	
}**/

/*function for pre-checking if we have actual atags loaded*/
void preinit_atags(atag_t * atags){
	atag_t * cur_tag = atags;
	uint32_t found_first = 0;
	uint32_t idx = 0;

	uart_puts("[--- Searching for ATAGS ---]\n");
	while (cur_tag->tag_type != ATAG_NONE ){
		if (cur_tag->tag_type == ATAG_MEM){ //0x54410002 ){

			uart_puts("\t[*] Found MEM TAG\n");
			found_first = 1;
		}	
		if (cur_tag->tag_type == ATAG_NONE){

			uart_puts("\t[*] NONE\n");
		}
		cur_tag = to_next_tag(cur_tag);
		//delay(10);
		if (!found_first){
			if (idx == 0){
				uart_puts(".\n");
			}
			else if(idx == 1){
				uart_puts("..\n");
			}
			else
				uart_puts("...\n");
			idx += 1;
			idx %= 3;
		}
	}	
}
/* kernel_main function, where it all happens!*/
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags){
	(void) r0;
	(void) r1;
	(void) atags;

	uart_init();
	uart_puts("NiOS version 0.0.01\n");
	uart_puts("Booting...\n");

	preinit_atags((atag_t*) atags);	
	uart_puts("[*] init finished...\n");
	while(1){
		uart_putc(uart_getc());
	}

}


