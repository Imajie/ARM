/*
 * File:	uart.h
 * Author:	James Letendre
 * 
 * UART module
 */
#ifndef _UART_H_
#define _UART_H_


/*
 * uart_init
 *  id:		The Uart device to initialize
 *	baud:	The baud rate at which to send data
 *
 *	Initialize the target uart device
 */
void uart_init( int baud );

/*
 * uart_getchar
 * 	id:		The uart to grab char from
 * 	return:	next byte from uart
 *
 * 	Get the next byte from the uart
 */
char uart_getchar();

/*
 * uart_putchar
 *  id:		Uart to send character with
 * 	c:		character to add to send over uart
 *
 * 	Send a character over the uart
 */
void uart_putchar( const char c );

void uart_putstr( const char *s );

#endif
