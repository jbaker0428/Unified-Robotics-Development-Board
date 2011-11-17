/**
 *	@file stm32.h
 *
 *	@date 11/9/2011
 *	@author jbaker
 */

#ifndef STM32_H_
#define STM32_H_

#include "urdb.h"

#define STM32_BIT_RATE	32000000
#define CLK_REF	100000000
#define STM32_BIT_PRD	CLK_REF / STM32_BIT_RATE

/**
 * UART transmit function based on Digikey XMOS PTM
 */
void txByte(out port TXD, int byte);
out port TXD = PORT_UART_TX;


#endif /* STM32_H_ */
