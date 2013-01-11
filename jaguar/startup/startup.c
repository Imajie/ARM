/*
 * Startup target
 */
#include <stdint.h>
#include "isr.h"

void low_level_init(void);
void main(void);

void zero_bss()
{
	extern int32_t __bss_start__;
	extern int32_t __bss_end__;
	char *ptr;

	for( ptr = (char*)__bss_start__; ptr < (char*)__bss_end__; ptr++ )
	{
		*ptr = 0;
	}
}

ISR(_start)
{
	/* initialize vector table, clocks */
	low_level_init();

	/* zero BSS */
	//zero_bss();

	/* call main */
	main();

	for(;;);
}
