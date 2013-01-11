/*
 * Low level initialization
 * Called before registers are setup
 *
 * This resets the vector table to one defined in RAM
 * Setup FLL
 */
#include <stdint.h>
#include "common.h"

void low_level_init( void )
{
	/* Disable watchdog */
	SIM_COPC = 0x00;

	/* Set MCG clock to FLL/PLL */
	MCG_C1 &= ~MCG_C1_CLKS(0);

	/* setup FLL for 48 MHz */
	MCG_C4 |= MCG_C4_DMX32_MASK;	// fine-tune
	MCG_C4 |= MCG_C4_DRST_DRS(1);	// mid-range = 48MHz
}
