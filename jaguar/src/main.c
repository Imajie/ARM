#include "common.h"
#include "uart.h"
#include "tss.h"
#include "jaguar.h"

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


#define DELAY 500000

#define NONE	(0)
#define RED		(1<<0)
#define GREEN	(1<<1)
#define BLUE	(1<<2)

#define IS_SET(x,y)	(((x)&(y)) == (y))

#define P	( 0x00008000 )		
#define I	( 0x00000000 )
#define D	( 0x00000000 )

int main( void )
{
	int i;

	uart_init(CPU_UART, 115200);
	uart_init(JAG_UART, 115200);

	init_gpio();
	init_jaguar();

	__enable_interrupts();
	for( i=0; i<DELAY; i++) ;

	uart_putstr( CPU_UART, "Initialization Complete\r\n" );

	jaguar_motor_config( 1, ENCODER_PPR, 141 );

	jaguar_control_mode_enable( SPEED_CONTROL, 1, 1 );
	jaguar_control_mode_setPID( SPEED_CONTROL, 1, P, I, D );
	jaguar_control_mode_reference( SPEED_CONTROL, 1, QUAD_ENCODER );

	jaguar_control_mode_set( SPEED_CONTROL, 1, 60<<16 );

	while( 1 )
	{
		char c;
		c = uart_getchar( CPU_UART ) - '0';

		if( c >= 0 && c <= 9 )
		{
			jaguar_voltage_control_set( 1, ((32768 * c) / 9));
		}
		else
		{
			jaguar_voltage_control_set( 1, 0 );
		}
	}

	return 0;
}
