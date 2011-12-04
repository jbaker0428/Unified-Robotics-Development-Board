/*
 * urdb_xmos.c
 *
 *  Created on: Nov 28, 2011
 *      Author: Joe
 */

#include "urdb_stm32.h"
#include <stm32l1xx_usart.h>

USART_InitTypeDef USART_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
DMA_InitTypeDef  DMA_InitStructure;

uint8_t received_control_byte;

struct
{
	unsigned int active:1;		// Transaction in progress
	unsigned int master:1;		// The "master" is the device that initiated
	unsigned int cmd_sent:1;	// Has a CMD control byte been sent/received?
	unsigned int ack_sent:1;	// Has an ACK reply byte been sent/received?
	unsigned int error:2;
	// error: 0 = OK, 1 = multiple CMD's, 2 = sent CMD, got a CMD back, 3 = wrong/surprise ACK byte
	unsigned int tx_en:1;		// TX enable
	unsigned int rx_en:1;		// RX enable
} uart_status;


void uart_clk_out_init(void)
{
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/* GPIOA and GPIOB clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = XMOS_TIM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(XMOS_TIM_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(XMOS_TIM_PORT, XMOS_TIM_SRC, GPIO_AF_TIM3);

	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

void uart_gpio_init(void)
{
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	// TX
	GPIO_InitStructure.GPIO_Pin = XMOS_TX_PIN;
	GPIO_Init(XMOS_TX_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(XMOS_TX_PORT, XMOS_TX_SRC, GPIO_AF_USART1);

	// RX
	GPIO_InitStructure.GPIO_Pin = XMOS_RX_PIN;
	GPIO_Init(XMOS_RX_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(XMOS_RX_PORT, XMOS_RX_SRC, GPIO_AF_USART1);

}

void uart_dma_init(void)
{
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_ADDRESS;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
}

void xmos_uart_init(void)
{
	uart_status.ack_sent = 0;
	uart_status.active = 0;
	uart_status.cmd_sent = 0;
	uart_status.master = 0;
	RCC_AHBPeriphClockCmd(DMA1_CLK, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	uart_clk_out_init();

	/* USARTx configured as follows:
	        - BaudRate = 32,000,000 baud
	        - Word Length = 8 Bits
	        - One Stop Bit
	        - No parity
	        - Hardware flow control disabled (RTS and CTS signals)
	        - Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 32000000;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	uart_dma_init();

	USART_Cmd(USART1, ENABLE);
}

void uart_idle(void)
{
	// Clear status fields
	uart_status.active = 0;
	uart_status.master = 0;
	uart_status.cmd_sent = 0;
	uart_status.ack_sent = 0;
	uart_status.error = 0;
	received_control_byte = 0;

	// Disable TX if it's not already
	if(uart_status.tx_en == 1)
	{
		uart_tx_disable();	// Clears uart_status.tx_en
	}
	// Enable RX + interrupt
	uart_rx_enable(&received_control_byte, 1);	// Sets uart_status.rx_en
}


