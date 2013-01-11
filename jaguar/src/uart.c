/*
 * UART module
 *
 * James Letendre
 */
#include "common.h"
#include "uart.h"
#include "circular_buf.h"

#define UART_BUFFER_SIZE	80
#define N_UART				3

// uart data
char uart_data_rx[N_UART][UART_BUFFER_SIZE];
char uart_data_tx[N_UART][UART_BUFFER_SIZE];

// buffers
c_buffer_t uart_c_buf_rx[N_UART];
c_buffer_t uart_c_buf_tx[N_UART];

/*
 * uart_init
 *  id:		The Uart device to initialize
 *	baud:	The baud rate at which to send data
 *
 *	Initialize the target uart device
 */
void uart_init( int idx, int baud )
{
	if( idx >= N_UART || idx < 0 )
	{
		return;
	}

	// Enable the uart clock to by 48 MHz
	if( idx == 0 )
		SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);

#define SCGC4_MASK(x)	(x) == 0 ? SIM_SCGC4_UART0_MASK : \
						(x) == 1 ? SIM_SCGC4_UART1_MASK : \
						(x) == 2 ? SIM_SCGC4_UART2_MASK : 0
	SIM_SCGC4 |= SCGC4_MASK(idx);

	switch( idx )
	{
		case 0:
			SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
			
			PORTA_PCR1 = PORT_PCR_MUX(2);		// Set PTA1 to UART0_RX
			PORTA_PCR2 = PORT_PCR_MUX(2);		// Set PTA2 to UART0_TX
			break;
		case 1:
			SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

			PORTE_PCR0 = PORT_PCR_MUX(3);		// Set PTE0 to UART1_RX
			PORTE_PCR1 = PORT_PCR_MUX(3);		// Set PTE1 to UART1_TX
			break;
	}
	
	// initialize the buffer
	uart_c_buf_rx[idx] = c_buffer_init( uart_data_rx[idx], UART_BUFFER_SIZE );
	uart_c_buf_tx[idx] = c_buffer_init( uart_data_tx[idx], UART_BUFFER_SIZE );

	// set baud rate
	// (48 MHz / baud) / oversample = X
	uint16_t baud_div = (F_CPU)/(baud*(16-1));
	
	if( idx > 0 )
		baud_div /= 2;

#define BDL(x,y)	(x) == 0 ? UART0_BDL = y : \
					(x) == 1 ? UART1_BDL = y : \
					(x) == 2 ? UART2_BDL = y : 0

#define BDH(x,y)	(x) == 0 ? UART0_BDH = y : \
					(x) == 1 ? UART1_BDH = y : \
					(x) == 2 ? UART2_BDH = y : 0
	BDL(idx, (baud_div>>0) & UART_BDL_SBR_MASK);
	BDH(idx, (baud_div>>8) & UART_BDH_SBR_MASK);
	
	// default setup is for 8N1
	
	// Enable tx and rx interrupts
#define OR_C2(x,y)	(x) == 0 ? UART0_C2 |= y : \
					(x) == 1 ? UART1_C2 |= y : \
					(x) == 2 ? UART2_C2 |= y : 0
#define NAND_C2(x,y)	(x) == 0 ? UART0_C2 &= ~(y) : \
						(x) == 1 ? UART1_C2 &= ~(y) : \
						(x) == 2 ? UART2_C2 &= ~(y) : 0
	OR_C2(idx, UART_C2_TIE_MASK | UART_C2_RIE_MASK);

	// Enable tx and rx on uart
	OR_C2(idx, UART_C2_TE_MASK | UART_C2_RE_MASK);

	// enable interrupts
#define INT_UART(x)	(x) == 0 ? INT_UART0 : \
					(x) == 1 ? INT_UART1 : \
					(x) == 2 ? INT_UART2 : 0
	NVIC_IntEnable(INT_UART(idx));
}

/*
 * uart_getchar
 * 	id:		The uart to grab char from
 * 	return:	next byte from uart
 *
 * 	Get the next byte from the uart
 */
char uart_getchar( int id )
{
	char c = -1;

	if( id >= 0 && id < N_UART )
	{
		// wait for a character
		while( c_buffer_read( &uart_c_buf_rx[id], &c ) != 0 );
	}

	return c;
}

/*
 * uart_putchar
 *  id:		Uart to send character with
 * 	c:		character to add to send over uart
 *
 * 	Send a character over the uart
 */
void uart_putchar( int id, const char c )
{
	if( id >= 0 && id < N_UART )
	{
		// sending things, so wait for space to write the char
		if( id == 1 ) GPIOB_PCOR |= 1<<19;
		while( c_buffer_write( &uart_c_buf_tx[id], c ) != 0 );
		if( id == 1 ) GPIOB_PSOR |= 1<<19;

		// is the TX idle
#define S1(x)	(x) == 0 ? UART0_S1 : \
				(x) == 1 ? UART1_S1 : \
				(x) == 2 ? UART2_S1 : 0
		if( S1(id) & UART_S1_TC_MASK )
		{
			OR_C2(id, UART_C2_TIE_MASK);
		}
	}
}

void uart_putstr( int idx, const char *s )
{
	const char *ptr = s;

	if( idx >= 0 && idx < N_UART )
	{
		while( *ptr != '\0' )
			uart_putchar( idx, *ptr++ );
	}
}

/*
 * uart_putnum
 * 	x:		The number to display
 * 	digits:	The number of digits in number
 *
 * 	Print number with "digit" digits over uart
 */
void uart_putnum( int idx, uint32_t x, uint8_t digits )
{
	if( idx >= 0 && idx < N_UART )
	{
		if( digits > 0 )
		{
			// get the lowest order char
			char c = '0' + (x % 10);

			uart_putnum( idx, x/10, digits-1 );

			uart_putchar( idx, c );
		}
	}
}


void UART_isr( int idx )
{
#define GET_DATA(x)	(x) == 0 ? UART0_D : \
					(x) == 1 ? UART1_D : \
					(x) == 2 ? UART2_D : 0
#define SET_DATA(x,y)	(x) == 0 ? UART0_D = y : \
						(x) == 1 ? UART1_D = y : \
						(x) == 2 ? UART2_D = y : 0
	// check what this interrupt is for	
	
	// RX
	if( S1(idx) & UART_S1_RDRF_MASK )
	{
		char c = GET_DATA(idx);

		// we have a new byte, drop if no space
		c_buffer_write( &uart_c_buf_rx[idx], c );
	}
	
	// TX
	if( S1(idx) & UART_S1_TDRE_MASK )
	{
		// do we have a new byte to send?
		char c;
		if( c_buffer_read( &uart_c_buf_tx[idx], &c ) == 0 )
		{
			// yes, so send it
			SET_DATA(idx, c);
		}
		else
		{
			// No, so disable the TX interrupt
			NAND_C2(idx, UART_C2_TIE_MASK);
		}
	}
}

/*
 * uart ISRs
 */
void UART0_isr(void)
{
	UART_isr(0);
}

void UART1_isr(void)
{
	GPIOB_PCOR |= 1<<19;
	UART_isr(1);
	GPIOB_PCOR |= 1<<19;
}

void UART2_isr(void)
{
	UART_isr(2);
}

