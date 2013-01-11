#include "common.h"
#include "uart.h"
#include "tss.h"

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

void init_PWM(void)
{
	// setup timer for PWM
	
	// set module clock to FLL
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
	// turn on TPM clock
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;

	// turn off module clock
	TPM0_SC &= ~(TPM_SC_CMOD_MASK);

	// wait for counter to turn off
	while( TPM0_SC & TPM_SC_CMOD_MASK );
	
	// set MSB, set ELSB
	TPM0_C0SC = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);

	// Set the PWM period
	TPM0_MOD = 1000;

	// Set the initial value
	TPM0_C0V = 500;

	// Clear the counter
	TPM0_CNT = 0;

	// counter increments on TPM clock, PreScale = /1
	TPM0_SC = (TPM_SC_CMOD(1) | TPM_SC_PS(0));

	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	PORTC_PCR1 = PORT_PCR_MUX(4);		// Set PTC1 to TPM0_CH0
}

#define DELAY 5000

#define NONE	(0)
#define RED		(1<<0)
#define GREEN	(1<<1)
#define BLUE	(1<<2)

#define IS_SET(x,y)	(((x)&(y)) == (y))

int main( void )
{
	int i;

	uart_init(CPU_UART, 9600);
	uart_init(JAG_UART, 115200);

	init_gpio();
	init_PWM();

	__enable_interrupts();
	for( i=0; i<DELAY; i++) ;

	uart_putstr( CPU_UART, "Initialization Complete\r\n" );

	while( 1 )
	{	
		uart_putchar( JAG_UART, 'a' );
		uart_putchar( CPU_UART, 'b' );

		for( i=0; i<DELAY; i++);
	}
	

	return 0;
}
