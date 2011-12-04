/*
 * xmos_uart.h
 *
 *  Created on: Nov 28, 2011
 *      Author: Joe
 */

#ifndef XMOS_UART_H_
#define XMOS_UART_H_

short int cmd_data_bits[35];	// Index of array = opcode, Data in array = # of bytes of data for that opcode
short int reply_data_bits[35];
uint8_t cmd_data_bytes[35];
uint8_t reply_data_bytes[35];

uint8_t received_control_byte, command;

#define USART1_DR_ADDRESS		USART1->DR		// TODO: verify this is the correct thing to point to

#define XMOS_TX_PORT			GPIOB
#define XMOS_TX_PIN				GPIO_Pin_6
#define XMOS_TX_SRC				GPIO_PinSource6
#define XMOS_TX_DMA_CHANNEL		DMA1_Channel4
#define XMOS_TX_DMA_FLAG_TC		DMA1_FLAG_TC4
#define XMOS_TX_DMA_FLAG_GL		DMA1_FLAG_GL4

#define XMOS_RX_PORT			GPIOB
#define XMOS_RX_PIN				GPIO_Pin_7
#define XMOS_RX_SRC				GPIO_PinSource7
#define XMOS_RX_DMA_CHANNEL		DMA1_Channel5
#define XMOS_RX_DMA_FLAG_TC		DMA1_FLAG_TC5
#define XMOS_RX_DMA_FLAG_GL		DMA1_FLAG_GL5

#define DMA1_CLK				RCC_AHBPeriph_DMA1
/*
 * 			-------- COMMUNICATIONS FORMAT --------
 *
 * 		-----------------------------
 * 		| CMD/REPLY | OPCODE | DATA |
 * 		-----------------------------
 *
 * Where:
 * - CMD/REPLY is a 1-bit value. 0 = command, 1 = reply (ACK).
 *
 * - OPCODE is a 7-bit value from the defined values below.
 *
 * - DATA is the data associated with the command. Data width varies depending
 * 		on the OPCODE and CMD/REPLY values (see command table below). Note that
 * 		all data is sent in 8-bit chunks, the width values below denote what of
 * 		that is actual data vs garbage.
 *
 * 	  A device initiates communication by sending an opcode with the CMD/REPLY
 * 	flag set to 0. The receiving devices acknowledges the command by sending a
 * 	reply with the same opcode. After the ACK byte is sent, both devices begin
 * 	the transfer of data associated with the opcode. In the event of an opcode
 * 	being added in the future calling for both devices to send data, these
 * 	transfers can occur simultaenously. Neither device shall initiate a new
 * 	command until the current exchange is completed.
 *
 *	  The STM32 should set up DMA channels, buffers, etc. BEFORE sending the ACK
 *	reply byte, as the speed of the link and higher processing speed of the XMOS
 *	does not allow for time to do so after the ACK reply byte is sent.
 *
 */

// Command formatting "register"
#define CMD_CMD				0 << 7
#define CMD_REPLY			1 << 7	// 0 = command, 1 = reply
#define CMD_OPCODE_6		1 << 6
#define CMD_OPCODE_5		1 << 5
#define CMD_OPCODE_4		1 << 4
#define CMD_OPCODE_3		1 << 3
#define CMD_OPCODE_2		1 << 2
#define CMD_OPCODE_1		1 << 1
#define CMD_OPCODE_0		1

/** @defgroup UART_opcodes
  * @{
  */
// 		Command				Opcode	Command data width	Reply data width
#define CMD_GET_ADC_0		0		// 0				current_adc_res
#define CMD_GET_ADC_1		1		// 0				current_adc_res
#define CMD_GET_ADC_2		2		// 0				current_adc_res
#define CMD_GET_ADC_3		3		// 0				current_adc_res
#define CMD_GET_ADC_4		4		// 0				current_adc_res
#define CMD_GET_ADC_5		5		// 0				current_adc_res
#define CMD_GET_ADC_6		6		// 0				current_adc_res
#define CMD_GET_ADC_7		7		// 0				current_adc_res
#define CMD_GET_ADC_8		8		// 0				current_adc_res
#define CMD_GET_ADC_9		9		// 0				current_adc_res
#define CMD_GET_ADC_10		10		// 0				current_adc_res
#define CMD_GET_ADC_11		11		// 0				current_adc_res
#define CMD_GET_ADC_12		12		// 0				current_adc_res
#define CMD_GET_ADC_13		13		// 0				current_adc_res
#define CMD_GET_ADC_14		14		// 0				current_adc_res
#define CMD_GET_ADC_15		15		// 0				current_adc_res
#define CMD_GET_ADC_16		16		// 0				current_adc_res
#define CMD_GET_ADC_17		17		// 0				current_adc_res
#define CMD_GET_ADC_18		18		// 0				current_adc_res
#define CMD_GET_ADC_19		19		// 0				current_adc_res
#define CMD_GET_ADC_20		20		// 0				current_adc_res
#define CMD_GET_ADC_21		21		// 0				current_adc_res
#define CMD_GET_ADC_22		22		// 0				current_adc_res
#define CMD_GET_ADC_23		23		// 0				current_adc_res
#define CMD_GET_ADC_RES		24		// 0				2-bit
#define CMD_SET_ADC_RES		25		// 2-bit			0
#define CMD_USB_SEND		26		// 8-bit ?			0
#define CMD_GET_RTC_TIME	27		// 0				24-bit
#define CMD_GET_RTC_DATE	28		// 0				24-bit
#define CMD_SET_RTC_TIME	29		// 24-bit			0
#define CMD_SET_RTC_DATE	30		// 24-bit			0
#define CMD_GET_DAC_RES		31		// 0				1-bit
#define CMD_SET_DAC_RES		32		// 1-bit			0
#define	CMD_DAC_CH0_OUT		33		// current_dac_res	0
#define	CMD_DAC_CH1_OUT		34		// current_dac_res	0
/**
  * @}
  */

/**
 * Populate the <cmd/reply>_data_widths[] arrays
 */
void set_data_widths(void);

/**
 * Initializes TIM3_CH2 to output a 32MHz clock to the XMOS.
 */
void uart_clk_out_init(void);

/**
 * Initializes the TX/RX pins for UART1.
 */
void uart_gpio_init(void);

/**
 * Initializes channels 4 and 5 of DMA1 for UART1 TX/RX.
 */
void uart_dma_init(void);

/**
 * Initializes USART1 to URDB spec.
 */
void xmos_uart_init(void);

/**
 * Activates USART1 RX DMA channel to wait for a command code from the XMOS.
 * This is the default state when there is nothing to send and no transaction in progress.
 */
void uart_idle(void);

/**
 * Initiates a new transaction with the XMOS.
 * @param opcode Command code to send which is some value of @ref UART_opcodes
 * @param tx_data Data to transmit
 * @return 0 if success, -1 if a transaction is already in progress
 */
int uart_initiate_transaction(uint8_t opcode, int tx_data);

/**
 * Handles reply data from a master-mode transaction
 * @param opcode Initiating command code which is some value of @ref UART_opcodes
 */
void uart_handle_reply(uint8_t opcode);

/**
 * Handle commands sent by the XMOS.
 * This should be called from an RX interrupt breaks the idle state.
 * @param opcode Received command code which is some value of @ref UART_opcodes
 */
void uart_handle_command(uint8_t opcode);

/**
 * Enable the UART transmitter in DMA mode
 * @param base_adr Value to be used in DMA_InitType.DMA_MemoryBaseAddr
 * @param num_bytes Number of bytes to transmit (DMA_InitType.DMA_BufferSize)
 */
void uart_tx_enable(uint32_t base_addr, int num_bytes);

/**
 * Disable UART transmitter's DMA channel
 */
void uart_tx_disable(void);

/**
 * Enable the UART receiver in DMA mode
 * @param base_adr Value to be used in DMA_InitType.DMA_MemoryBaseAddr
 * @param num_bytes Number of bytes to receive (DMA_InitType.DMA_BufferSize)
 */
void uart_rx_enable(uint32_t base_addr, int num_bytes);

/**
 * Disable UART receiver's DMA channel
 */
void uart_rx_disable(void);

#endif /* XMOS_UART_H_ */
