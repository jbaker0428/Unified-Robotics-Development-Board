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


void set_data_widths()
{

	short int adc_bits, dac_bits;
	uint8_t adc_bytes, dac_bytes;

	switch(ADC_CR1_RES)
	{
		case 0:
			adc_bits = 12; break;
			adc_bytes = 2; break;
		case 1:
			adc_bits = 10; break;
			adc_bytes = 2; break;
		case 2:
			adc_bits = 8; break;
			adc_bytes = 1; break;
		case 3:
			adc_bits = 6; break;
			adc_bytes = 1; break;
		default:
			adc_bits = 12; break;
			adc_bytes = 2; break;
	}

	switch(current_dac_res)
	{
		case 0:
			dac_bits = 12; break;
			dac_bytes = 2; break;
		case 1:
			dac_bits = 8; break;
			dac_bytes = 1; break;
		default:
			dac_bits = 12; break;
			dac_bytes = 2; break;
	}
	for (int i=0; i<24; i++)
	{
		cmd_data_bits[i] = 0;
	}
	cmd_data_bits[24] = 0;
	cmd_data_bits[25] = 2;
	cmd_data_bits[26] = 8;
	cmd_data_bits[27] = 0;
	cmd_data_bits[28] = 0;
	cmd_data_bits[29] = 24;
	cmd_data_bits[30] = 24;
	cmd_data_bits[31] = 0;
	cmd_data_bits[32] = 1;
	cmd_data_bits[33] = dac_bits;
	cmd_data_bits[34] = dac_bits;
	cmd_data_bits[35] = 5;
	cmd_data_bits[36] = 17;
	cmd_data_bits[37] = 3;
	cmd_data_bits[38] = 4;
	cmd_data_bits[39] = 0;
	cmd_data_bits[40] = 8;

	for (int i=0; i<24; i++)
	{
		reply_data_bits[i] = adc_bits;
	}
	reply_data_bits[24] = 2;
	reply_data_bits[25] = 0;
	reply_data_bits[26] = 0;
	reply_data_bits[27] = 24;
	reply_data_bits[28] = 24;
	reply_data_bits[29] = 0;
	reply_data_bits[30] = 0;
	reply_data_bits[31] = 1;
	reply_data_bits[32] = 0;
	reply_data_bits[33] = 0;
	reply_data_bits[34] = 0;
	reply_data_bits[35] = 17;
	reply_data_bits[36] = 0;
	reply_data_bits[37] = 1;
	reply_data_bits[38] = 0;
	reply_data_bits[39] = 8;
	reply_data_bits[40] = 0;

	for (int i=0; i<24; i++)
	{
		cmd_data_bytes[i] = 0;
	}
	cmd_data_bytes[24] = 0;
	cmd_data_bytes[25] = 1;
	cmd_data_bytes[26] = 1;
	cmd_data_bytes[27] = 0;
	cmd_data_bytes[28] = 0;
	cmd_data_bytes[29] = 3;
	cmd_data_bytes[30] = 3;
	cmd_data_bytes[31] = 0;
	cmd_data_bytes[32] = 1;
	cmd_data_bytes[33] = dac_bytes;
	cmd_data_bytes[34] = dac_bytes;
	cmd_data_bytes[35] = 1;
	cmd_data_bytes[36] = 3;
	cmd_data_bytes[37] = 1;
	cmd_data_bytes[38] = 1;
	cmd_data_bytes[39] = 0;
	cmd_data_bytes[40] = 1;

	for (int i=0; i<24; i++)
	{
		reply_data_bytes[i] = adc_bytes;
	}
	reply_data_bytes[24] = 1;
	reply_data_bytes[25] = 0;
	reply_data_bytes[26] = 0;
	reply_data_bytes[27] = 3;
	reply_data_bytes[28] = 3;
	reply_data_bytes[29] = 0;
	reply_data_bytes[30] = 0;
	reply_data_bytes[31] = 1;
	reply_data_bytes[32] = 0;
	reply_data_bytes[33] = 0;
	reply_data_bytes[34] = 0;
	reply_data_bytes[35] = 3;
	reply_data_bytes[36] = 0;
	reply_data_bytes[37] = 1;
	reply_data_bytes[38] = 0;
	reply_data_bytes[39] = 1;
	reply_data_bytes[40] = 0;
}

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

int uart_initiate_transaction(uint8_t opcode, int tx_data)
{
	command = CMD_CMD | opcode;

	if (uart_status.active == 1)
		return -1;

	// Set status fields
	uart_status.active = 1;
	uart_status.master = 1;

	// Init TX and RX DMA
	uart_tx_enable(&command, 1);
	uart_rx_enable(&received_control_byte, 1);

	// Enable DMA
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

	USART_ClearFlag(USART1, USART_FLAG_TC);

	DMA_Cmd(XMOS_TX_DMA_CHANNEL, ENABLE);
	// TODO: Set cmd_sent in ISR in this state (active/master, TX complete interrupt)
	DMA_Cmd(XMOS_RX_DMA_CHANNEL, ENABLE);
	// TODO: Set ack_sent in ISR in this state (active/master/cmd_sent, RX complete interrupt)

	return 0;
}
