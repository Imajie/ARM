/*
 * UART module
 *
 * James Letendre
 */
#include "common.h"
#include "uart.h"
#include "circular_buf.h"

#define UART_BUFFER_SIZE 80

// uart data
char uart0_data_rx[UART_BUFFER_SIZE];
char uart0_data_tx[UART_BUFFER_SIZE];

// buffers
c_buffer_t uart0_c_buf_rx;
c_buffer_t uart0_c_buf_tx;

/*
 * uart_init
 *  id:		The Uart device to initialize
 *	baud:	The baud rate at which to send data
 *
 *	Initialize the target uart device
 */
void uart_init( int baud )
{
	// Enable the uart clock to by 48 MHz
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	PORTA_PCR1 = PORT_PCR_MUX(2);		// Set PTA1 to UART0_RX
	PORTA_PCR2 = PORT_PCR_MUX(2);		// Set PTA2 to UART0_TX
	
	// initialize the buffer
	uart0_c_buf_rx = c_buffer_init( uart0_data_rx, UART_BUFFER_SIZE );
	uart0_c_buf_tx = c_buffer_init( uart0_data_tx, UART_BUFFER_SIZE );

	// set baud rate
	// (48 MHz / baud) / oversample = X
	uint16_t baud_div = (F_CPU)/(baud*(16-1));

	UART0_BDL = (baud_div>>0) & UART_BDL_SBR_MASK;
	UART0_BDH = (baud_div>>8) & UART_BDH_SBR_MASK;
	
	// default setup is for 8N1
	
	// Enable tx and rx interrupts
	UART0_C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK;

	// Enable tx and rx on uart
	UART0_C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK;

	// enable interrupts
	NVIC_IntEnable(INT_UART0);
}

/*
 * uart_getchar
 * 	id:		The uart to grab char from
 * 	return:	next byte from uart
 *
 * 	Get the next byte from the uart
 */
char uart_getchar( )
{
	char c = -1;

	// wait for a character
	while( c_buffer_read( &uart0_c_buf_rx, &c ) != 0 );

	return c;
}

/*
 * uart_putchar
 *  id:		Uart to send character with
 * 	c:		character to add to send over uart
 *
 * 	Send a character over the uart
 */
void uart_putchar( const char c )
{
	// sending things, so wait for space to write the char
	while( c_buffer_write( &uart0_c_buf_tx, c ) != 0 );

	// is the TX idle
	if( UART0_S1 & UART_S1_TC_MASK )
	{
		UART0_C2 |= UART_C2_TIE_MASK;
	}
}

void uart_putstr( const char *s )
{
	const char *ptr = s;

	while( *ptr != '\0' )
		uart_putchar( *ptr++ );
}

/*
 * uart_putnum
 * 	x:		The number to display
 * 	digits:	The number of digits in number
 *
 * 	Print number with "digit" digits over uart
 */
void uart_putnum( uint32_t x, uint8_t digits )
{
	if( digits > 0 )
	{
		// get the lowest order char
		char c = '0' + (x % 10);

		uart_putnum( x/10, digits-1 );

		uart_putchar( c );
	}
}


/*
 * uart0 ISR
 */
void UART0_isr( void )
{
	// check what this interrupt is for	
	
	// RX
	if( UART0_S1 & UART_S1_RDRF_MASK )
	{
		char c = UART0_D;

		// we have a new byte, drop if no space
		c_buffer_write( &uart0_c_buf_rx, c );
	}
	
	// TX
	if( UART0_S1 & UART_S1_TDRE_MASK )
	{
		// do we have a new byte to send?
		char c;
		if( c_buffer_read( &uart0_c_buf_tx, &c ) == 0 )
		{
			// yes, so send it
			UART0_D = c;
		}
		else
		{
			// No, so disable the TX interrupt
			UART0_C2 &= ~UART_C2_TIE_MASK;
		}
	}
}
