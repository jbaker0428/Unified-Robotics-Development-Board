/*
 * stm32.xc
 *
 *  Created on: Nov 11, 2011
 *      Author: joe
 */

#include "urdb.h"
#include "stm32.h"

void set_data_widths()
{
	int adc_bits, dac_bits;

	switch(current_adc_res)
	{
		case 0:
			adc_bits = 12; break;
		case 1:
			adc_bits = 10; break;
		case 2:
			adc_bits = 8; break;
		case 3:
			adc_bits = 6; break;
		default:
			adc_bits = 12; break;
	}

	switch(current_dac_res)
	{
		case 0:
			dac_bits = 12; break;
		case 1:
			dac_bits = 10; break;
		default:
			dac_bits = 12; break;
	}

	for (int i=0; i<24; i++)
	{
		cmd_data_widths[i] = 0;
	}
	cmd_data_widths[24] = 0;
	cmd_data_widths[25] = 2;
	cmd_data_widths[26] = 8;
	cmd_data_widths[27] = 0;
	cmd_data_widths[28] = 0;
	cmd_data_widths[29] = 24;
	cmd_data_widths[30] = 24;
	cmd_data_widths[31] = 0;
	cmd_data_widths[32] = 1;
	cmd_data_widths[33] = dac_bits;
	cmd_data_widths[34] = dac_bits;
	cmd_data_widths[35] = 6;
	cmd_data_widths[36] = 18;
	cmd_data_widths[37] = 3;
	cmd_data_widths[38] = 4;
	cmd_data_widths[39] = 0;
	cmd_data_widths[40] = 8;

	for (int i=0; i<24; i++)
	{
		reply_data_widths[i] = adc_bits;
	}
	reply_data_widths[24] = 2;
	reply_data_widths[25] = 0;
	reply_data_widths[26] = 0;
	reply_data_widths[27] = 24;
	reply_data_widths[28] = 24;
	reply_data_widths[29] = 0;
	reply_data_widths[30] = 0;
	reply_data_widths[31] = 1;
	reply_data_widths[32] = 0;
	reply_data_widths[33] = 0;
	reply_data_widths[34] = 0;
	reply_data_widths[35] = 18;
	reply_data_widths[36] = 0;
	reply_data_widths[37] = 1;
	reply_data_widths[38] = 0;
	reply_data_widths[39] = 8;
	reply_data_widths[40] = 0;
}

void stm32_uart_init()
{
	current_adc_res = 0;	// STM32 default
	current_dac_res = 0;	// STM32 default
	current_opcode = -1;
	transfer_in_progress = 0;
	configure_clock_src(stm32_uart_clk, stm32_clk);
	configure_in_port(rx, stm32_uart_clk);
	configure_out_port_no_ready(tx, stm32_uart_clk, 1);
	start_clock(stm32_uart_clk);
}

int send_message(int opcode, int data)
{
	int reply_cmd, reply_opcode, reply_data;
	if(transfer_in_progress == 1)
		return -1;	// Transfer already in progress

	transfer_in_progress = 1;
	current_opcode = opcode;
	tx_cmd(CMD_CMD, opcode);
	tx_data(data, (cmd_data_widths[opcode]+8-1)/8);	// 2nd arg converts to bytes

	// wait for rx cmd code byte, ensure it's a reply to our command
	reply_cmd = rx_byte();
	reply_opcode = reply_cmd >> 7;
	if(reply_cmd != 1 || reply_opcode != opcode)
		return -2;	// Received incorrect reply

	reply_data = rx_data((reply_data_widths[opcode]+8-1)/8);

	transfer_in_progress = 0;
	current_opcode = -1;

	return reply_data;
}

void tx_byte(int byte)
{
	partout(stm32_tx, 1, 0);	// Start bit
	stm32_tx <: byte;
	partout(stm32_tx, 1, 1);	// Stop bit
}

int rx_byte()
{
	int data;
	stm32_rx when pinseq(0) :> data;
	return data;
}

void tx_cmd(int cmd_reply, int opcode)
{
	tx_byte(cmd_reply | opcode);
}

int rx_cmd()
{

}

void tx_data(int data, int bytes_to_tx)
{
	int temp;

	for (int i=0; i<bytes_to_tx; i++)
	{
		temp = data >> 8;
		tx_byte(temp);
	}
}


int rx_data(int bytes_to_rx)
{
	int data, temp;
	for (int i=0; i<bytes_to_rx; i++)
	{
		temp = rx_byte();
		data |= temp << 8*i;
	}
	return data;
}
