#include "common.h"

#define RED_LED		(18)
#define GREEN_LED	(19)
#define BLUE_LED	(1)

#define GPIO_PIN(x)	(1<<(x))

void init_gpio( void )
{
	// Turn on clock gating to PortB - red and green, and PortD - blue
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

	// init red LED
	PORTB_PCR18 = PORT_PCR_MUX(1);		// Set PTB18 pin mux to GPIO
	GPIOB_PSOR |= GPIO_PIN(RED_LED);	// Set red LED to high initially
	GPIOB_PDDR |= GPIO_PIN(RED_LED);	// Set red LED pin to output

	// init green LED
	PORTB_PCR19 = PORT_PCR_MUX(1);		// Set PTB19 pin mux to GPIO
	GPIOB_PSOR |= GPIO_PIN(GREEN_LED);	// Set green LED to high initially
	GPIOB_PDDR |= GPIO_PIN(GREEN_LED);	// Set green LED pin to output

	// init blue LED
	PORTD_PCR1 = PORT_PCR_MUX(1);		// Set PTD1 pin mux to GPIO
	GPIOD_PSOR |= GPIO_PIN(BLUE_LED);	// Set blue LED to high initially
	GPIOD_PDDR |= GPIO_PIN(BLUE_LED);	// Set blue LED pin to output

}

#define DELAY 1000000

#define NONE	(0)
#define RED		(1<<0)
#define GREEN	(1<<1)
#define BLUE	(1<<2)

#define IS_SET(x,y)	(((x)&(y)) == (y))

int main( void )
{
	init_gpio();

	int i;
	int j = 0;
	while( 1 )
	{
		j++;
		j = j % (1<<3);

		// some delay
		for( i = 0; i < DELAY; i++ );
		
		// turn on next pattern
		if( IS_SET(j,RED) )
			GPIOB_PCOR |= GPIO_PIN(RED_LED);
		else
			GPIOB_PSOR |= GPIO_PIN(RED_LED);

		if( IS_SET(j,GREEN) )
			GPIOB_PCOR |= GPIO_PIN(GREEN_LED);
		else
			GPIOB_PSOR |= GPIO_PIN(GREEN_LED);

		if( IS_SET(j,BLUE) )
			GPIOD_PCOR |= GPIO_PIN(BLUE_LED);
		else
			GPIOD_PSOR |= GPIO_PIN(BLUE_LED);
	}

	return 0;
}
