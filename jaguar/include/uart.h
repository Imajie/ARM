/*
 * File:	uart.h
 * Author:	James Letendre
 * 
 * UART module
 */
#ifndef _UART_H_
#define _UART_H_

#define CPU_UART	0
#define JAG_UART	1


/*
 * uart_init
 *  id:		The Uart device to initialize
 *	baud:	The baud rate at which to send data
 *
 *	Initialize the target uart device
 */
void uart_init( int idx, int baud );

/*
 * uart_getchar
 * 	id:		The uart to grab char from
 * 	return:	next byte from uart
 *
 * 	Get the next byte from the uart
 */
char uart_getchar( int idx );

/*
 * uart_putchar
 *  id:		Uart to send character with
 * 	c:		character to add to send over uart
 *
 * 	Send a character over the uart
 */
void uart_putchar( int idx, const char c );

/*
 * uart_putstr
 * 	s:		The string to print
 *
 * 	Print the string over uart
 */
void uart_putstr( int idx, const char *s );

/*
 * uart_putnum
 * 	x:		The number to display
 * 	digits:	The number of digits in number
 *
 * 	Print number with "digit" digits over uart
 */
void uart_putnum( int idx, uint32_t x, uint8_t digits );
#endif
