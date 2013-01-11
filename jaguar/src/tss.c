/*
 * File:	tss.c
 * Author:	James Letendre
 *
 * Touch sensor module interface
 */
#include "common.h"
#include "tss.h"
#include "uart.h"

uint16_t tss_pin9;
uint16_t tss_pin10;

uint8_t tss_cur_pin;

/*
 * tss_init
 *
 * Initialize the tss module
 */
void tss_init()
{
	//Enable clock gates
	SIM_SCGC5 |= (SIM_SCGC5_TSI_MASK) | (SIM_SCGC5_PORTB_MASK);

	// PB16 and PB17 -> TSI0_CH9 and TSI0_CH10
	PORTB_PCR16 = PORT_PCR_MUX(0);
	PORTB_PCR17 = PORT_PCR_MUX(0);

	//Configure the TSI module and enable the interrupt, SW triggered
	TSI0_GENCS |= (TSI_GENCS_ESOR_MASK				// End of Scan Interrupt
				   | TSI_GENCS_REFCHRG(4)
				   | TSI_GENCS_DVOLT(0)
				   | TSI_GENCS_EXTCHRG(6)  
				   | TSI_GENCS_PS(2)
				   | TSI_GENCS_NSCN(11)
				   | TSI_GENCS_TSIIEN_MASK 
				   | TSI_GENCS_STPE_MASK
				  );

	// Clear End of scan and Out of Range Flags
	TSI0_GENCS |= (TSI_GENCS_OUTRGF_MASK) | (TSI_GENCS_EOSF_MASK); 

	//Select Desired Channel to Scan, 9 and 10 for FRDM
	TSI0_DATA |= (TSI_DATA_TSICH(9));
	tss_cur_pin = 9;

	// Enables TSI
	TSI0_GENCS |= (TSI_GENCS_TSIEN_MASK); 

	NVIC_IntEnable( INT_TSI0 );
}


void TSI0_isr(void)
{
	// clear the interrupt
	TSI0_GENCS |= TSI_GENCS_EOSF_MASK | TSI_GENCS_OUTRGF_MASK;

	GPIOD_PCOR |= (1<<1);
	
	// swap channels
	TSI0_DATA &= ~(TSI_DATA_TSICH_MASK);
	if( tss_cur_pin == 9 )
	{
		tss_pin9 = (TSI0_DATA & TSI_DATA_TSICNT_MASK);
		tss_cur_pin = 10;
	}
	else
	{
		tss_pin10 = (TSI0_DATA & TSI_DATA_TSICNT_MASK);
		tss_cur_pin = 9;
	}
	TSI0_DATA |= TSI_DATA_TSICH(tss_cur_pin);

	// and trigger the next read
	TSI0_DATA |= TSI_DATA_SWTS_MASK;
}

