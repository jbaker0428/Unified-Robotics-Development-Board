/*
 * xmos_uart.h
 *
 *  Created on: Nov 28, 2011
 *      Author: Joe
 */

#ifndef XMOS_UART_H_
#define XMOS_UART_H_

/**
 * Initializes TIM3_CH2 to output a 32MHz clock to the XMOS.
 */
void uart_clk_out_init(void);

/**
 * Initializes USART1 to URDB spec.
 */
void xmos_uart_init(void);

#endif /* XMOS_UART_H_ */
