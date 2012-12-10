/*
 * Startup target
 */
#include <stdint.h>
#include <string.h>
#include "isr.h"

void low_level_init(void);
void main(void);

void zero_bss()
{
	extern int32_t __bss_start__;
	extern int32_t __bss_end__;

	memset( (char*)__bss_start__, 0, __bss_end__ - __bss_start__ );
}

ISR(_start)
{
	/* initialize vector table, clocks */
	low_level_init();

	/* zero BSS */
	zero_bss();

	/* call main */
	main();

	for(;;);
}
