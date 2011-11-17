/**
 *	@file stm32.h
 *
 *	@date 11/9/2011
 *	@author jbaker
 */

#ifndef STM32_H_
#define STM32_H_

#include "urdb.h"

#define CLK_REF	100000000
#define STM32_BIT_RATE	32000000
#define STM32_BIT_PRD 	XS1_TIMER_HZ / STM32_BIT_RATE

int current_adc_res;	// 0 = 12-bit, 1 = 10-bit, 2 = 8-bit, 3 = 6-bit
int current_dac_res;	// 0 = 12-bit, 1 = 8-bit
short int cmd_data_widths[35];	// Index of array = opcode, Data in array = # of bits of data for that opcode
short int reply_data_widths[35];	// Index of array = opcode, Data in array = # of bits of data for that opcode
short int current_opcode;
short int transfer_in_progress;	// Boolean

/*
 * 			-------- COMMUNICATIONS FORMAT --------
 *
 * 		-----------------------------
 * 		| CMD/REPLY | OPCODE | DATA |
 * 		-----------------------------
 *
 * Where:
 * - CMD/REPLY is a 1-bit value. 0 = command, 1 = reply.
 *
 * - OPCODE is a 7-bit value from the defined values below.
 *
 * - DATA is the data associated with the command. Data width varies depending
 * 		on the OPCODE and CMD/REPLY values (see command table below). Note that
 * 		all data is sent in 8-bit chunks, the width values below denote what of
 * 		that is actual data vs garbage.
 *
 * 	A device initiates communication by sending a command and any associated
 * data. After receiving any data associated with the command, the receiving
 * device sends a reply with the same opcode followed by any associated data
 * requested by the device which initiated the communication. Neither device
 * shall initiate a new command until the current exchange is completed.
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

// 		Command				Opcode	Command data width	Reply data with
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
 * Populate the data_widths[] array
 */
void set_data_widths(void);

/**
 * Get ADC resolution from STM32 and update locally
 */
void get_adc_res();

/**
 * Set ADC resolution on STM32 and update locally
 */
void set_adc_res(int res);

/**
 * Get DAC resolution from STM32 and update locally
 */
void get_dac_res();

/**
 * Set DAC resolution on STM32 and update locally
 */
void set_dac_res(int res);

/**
 * Initialize the UART pins/clocks.
 */
void stm32_uart_init(void);

/**
 * Transmit a byte over the UART
 */
void tx_byte(int byte);

/**
 * Receive a byte over the UART
 */
int rx_byte(void);

/**
 * Transmits the cmd/reply and opcode block of a message.
 */
void tx_cmd(int cmd_reply, int opcode);

/**
 * Receives a new command from the STM32
 */
int rx_cmd(void);

/**
 * Transmit an arbitrary # of bytes of data over the UART
 */
void tx_data(int data, int bytes_to_tx);

/**
 * Receive an arbitrary # of bytes of data over the UART
 */
int rx_data(int bytes_to_rx);

/**
 * Initiate a complete message to the STM32
 * @return Reply data from command code
 */
int send_message(int opcode, int data);

#endif /* STM32_H_ */
