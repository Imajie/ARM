/*
 * vectors.c
 *
 * defines the vector table
 *
 */
#include <stdint.h>
#include "isr.h"
#include "common.h"

ISR(default_isr)
{
	//GPIOB_PCOR |= (1<<19);
	return;
}

extern uint32_t __SP_INIT;
extern void _start( void );

void NMI_isr( void ) __attribute__ ((weak, alias("default_isr")));
void HardFault_isr( void ) __attribute__ ((weak, alias("default_isr")));
void SVCall_isr( void ) __attribute__ ((weak, alias("default_isr")));
void PendableSrvReq_isr( void ) __attribute__ ((weak, alias("default_isr")));
void SysTick_isr( void ) __attribute__ ((weak, alias("default_isr")));
void DMA0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void DMA1_isr( void ) __attribute__ ((weak, alias("default_isr")));
void DMA2_isr( void ) __attribute__ ((weak, alias("default_isr")));
void DMA3_isr( void ) __attribute__ ((weak, alias("default_isr")));
void FTFA_isr( void ) __attribute__ ((weak, alias("default_isr")));
void LVD_LVW_isr( void ) __attribute__ ((weak, alias("default_isr")));
void LLW_isr( void ) __attribute__ ((weak, alias("default_isr")));
void I2C0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void I2C1_isr( void ) __attribute__ ((weak, alias("default_isr")));
void SPI0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void SPI1_isr( void ) __attribute__ ((weak, alias("default_isr")));
void UART0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void UART1_isr( void ) __attribute__ ((weak, alias("default_isr")));
void UART2_isr( void ) __attribute__ ((weak, alias("default_isr")));
void ADC0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void CMP0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void TPM0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void TPM1_isr( void ) __attribute__ ((weak, alias("default_isr")));
void TPM2_isr( void ) __attribute__ ((weak, alias("default_isr")));
void RTC_isr( void ) __attribute__ ((weak, alias("default_isr")));
void RTC_Seconds_isr( void ) __attribute__ ((weak, alias("default_isr")));
void PIT_isr( void ) __attribute__ ((weak, alias("default_isr")));
void USB0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void DAC0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void TSI0_isr( void ) __attribute__ ((weak, alias("default_isr")));
void MCG_isr( void ) __attribute__ ((weak, alias("default_isr")));
void LPTimer_isr( void ) __attribute__ ((weak, alias("default_isr")));
void PortA_isr( void ) __attribute__ ((weak, alias("default_isr")));
void PortD_isr( void ) __attribute__ ((weak, alias("default_isr")));

/* Interrupt vector table */
__attribute__ ((section (".vectortable"))) const vector_table_t __vector_table = 
{
	/* ISR name                             	No.			Address      Name                           */
	&__SP_INIT,									/* 0x00		0x00000000   ivINT_Initial_Stack_Pointer    */
	{
		(isr_func_t)&_start,					/* 0x01		0x00000004   ivINT_Initial_Program_Counter  */
		(isr_func_t)&NMI_isr,					/* 0x02		0x00000008   ivINT_NMI                      */
		(isr_func_t)&HardFault_isr,	        	/* 0x03		0x0000000C   ivINT_Hard_Fault               */
		(isr_func_t)&default_isr,		        /* 0x04		0x00000010   ivINT_Reserved4                */
		(isr_func_t)&default_isr,		        /* 0x05		0x00000014   ivINT_Reserved5                */
		(isr_func_t)&default_isr,		        /* 0x06		0x00000018   ivINT_Reserved6                */
		(isr_func_t)&default_isr,		        /* 0x07		0x0000001C   ivINT_Reserved7                */
		(isr_func_t)&default_isr,		        /* 0x08		0x00000020   ivINT_Reserved8                */
		(isr_func_t)&default_isr,		        /* 0x09		0x00000024   ivINT_Reserved9                */
		(isr_func_t)&default_isr,		        /* 0x0A		0x00000028   ivINT_Reserved10               */
		(isr_func_t)&SVCall_isr,		        /* 0x0B		0x0000002C   ivINT_SVCall                   */
		(isr_func_t)&default_isr,		        /* 0x0C		0x00000030   ivINT_Reserved12               */
		(isr_func_t)&default_isr,		        /* 0x0D		0x00000034   ivINT_Reserved13               */
		(isr_func_t)&PendableSrvReq_isr,        /* 0x0E		0x00000038   ivINT_PendableSrvReq           */
		(isr_func_t)&SysTick_isr,		        /* 0x0F		0x0000003C   ivINT_SysTick                  */
		(isr_func_t)&DMA0_isr,			        /* 0x10		0x00000040   ivINT_DMA0                     */
		(isr_func_t)&DMA1_isr,			        /* 0x11		0x00000044   ivINT_DMA1                     */
		(isr_func_t)&DMA2_isr,			        /* 0x12		0x00000048   ivINT_DMA2                     */
		(isr_func_t)&DMA3_isr,			        /* 0x13		0x0000004C   ivINT_DMA3                     */
		(isr_func_t)&default_isr,		        /* 0x14		0x00000050   ivINT_Reserved20               */
		(isr_func_t)&FTFA_isr,			        /* 0x15		0x00000054   ivINT_FTFA                     */
		(isr_func_t)&LVD_LVW_isr,		        /* 0x16		0x00000058   ivINT_LVD_LVW                  */
		(isr_func_t)&LLW_isr,			        /* 0x17		0x0000005C   ivINT_LLW                      */
		(isr_func_t)&I2C0_isr,			        /* 0x18		0x00000060   ivINT_I2C0                     */
		(isr_func_t)&I2C1_isr,			        /* 0x19		0x00000064   ivINT_I2C1                     */
		(isr_func_t)&SPI0_isr,			        /* 0x1A		0x00000068   ivINT_SPI0                     */
		(isr_func_t)&SPI1_isr,			        /* 0x1B		0x0000006C   ivINT_SPI1                     */
		(isr_func_t)&UART0_isr,			        /* 0x1C		0x00000070   ivINT_UART0                    */
		(isr_func_t)&UART1_isr,			        /* 0x1D		0x00000074   ivINT_UART1                    */
		(isr_func_t)&UART2_isr,			        /* 0x1E		0x00000078   ivINT_UART2                    */
		(isr_func_t)&ADC0_isr,			        /* 0x1F		0x0000007C   ivINT_ADC0                     */
		(isr_func_t)&CMP0_isr,			        /* 0x20		0x00000080   ivINT_CMP0                     */
		(isr_func_t)&TPM0_isr,			        /* 0x21		0x00000084   ivINT_TPM0                     */
		(isr_func_t)&TPM1_isr,			        /* 0x22		0x00000088   ivINT_TPM1                     */
		(isr_func_t)&TPM2_isr,			        /* 0x23		0x0000008C   ivINT_TPM2                     */
		(isr_func_t)&RTC_isr,			        /* 0x24		0x00000090   ivINT_RTC                      */
		(isr_func_t)&RTC_Seconds_isr,	        /* 0x25		0x00000094   ivINT_RTC_Seconds              */
		(isr_func_t)&PIT_isr,			        /* 0x26		0x00000098   ivINT_PIT                      */
		(isr_func_t)&default_isr,		        /* 0x27		0x0000009C   ivINT_Reserved39               */
		(isr_func_t)&USB0_isr,			        /* 0x28		0x000000A0   ivINT_USB0                     */
		(isr_func_t)&DAC0_isr,			        /* 0x29		0x000000A4   ivINT_DAC0                     */
		(isr_func_t)&TSI0_isr,			        /* 0x2A		0x000000A8   ivINT_TSI0                     */
		(isr_func_t)&MCG_isr,			        /* 0x2B		0x000000AC   ivINT_MCG                      */
		(isr_func_t)&LPTimer_isr,		        /* 0x2C		0x000000B0   ivINT_LPTimer                  */
		(isr_func_t)&default_isr,		        /* 0x2D		0x000000B4   ivINT_Reserved45               */
		(isr_func_t)&PortA_isr,			        /* 0x2E		0x000000B8   ivINT_PORTA                    */
		(isr_func_t)&PortD_isr			        /* 0x2F		0x000000BC   ivINT_PORTD                    */
	}
};
