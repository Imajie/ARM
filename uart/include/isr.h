/*
 * ISR vector define
 */
#ifndef ISR_H
#define ISR_H

/* ISR prototype */
typedef void (*const isr_func_t)(void);
typedef struct {
	uint32_t * __ptr;
	isr_func_t __fun[0x2F];
} vector_table_t;

#define ISR(name) void __attribute ((interrupt)) name(void)

#endif
