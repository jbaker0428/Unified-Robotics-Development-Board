/*
 * io_servers.xc
 *
 *  Created on: Jan 12, 2012
 *      Author: joe
 */

#include "urdb.h"
#include "io_servers.h"
#include "stm32.h"
#include <print.h>

unsigned int io_client_enqueue(unsigned &server_req, unsigned &server_service, unsigned &client, client_fifo_t &client_fifo,
		io_request_t &request)
{
	unsigned int server_ack;

	_setChanEndDest(client, server_req);
	_outInt(client, client);	// Send client's resource ID
	_outCT(client, XS1_CT_END);
	_chkCTI(client, XS1_CT_END);

	// Wait for ACK from server
	server_ack = _inCT(client);
	_chkCTI(server_req, XS1_CT_END);

	if(server_ack == XS1_CT_ACK)
	{
		// Success, add to client FIFO
		client_fifo_push(client_fifo, request);
		return server_ack;
	}
	else if (server_ack == XS1_CT_NACK)
		return server_ack;
	else
		return -1;
}

void io_server_enqueue(unsigned &req_ch, unsigned &service_ch, unsigned int new_req_chanend, REFERENCE_PARAM(request_fifo_t, req_fifo))
{
	_setChanEndDest(req_ch, new_req_chanend);
	_chkCTI(req_ch, XS1_CT_END);
	_outCT(req_ch, XS1_CT_END);
	int push_success = request_fifo_push(req_fifo, new_req_chanend);

	if(push_success)
	{
		_outCT(req_ch, XS1_CT_ACK);
		_outCT(req_ch, XS1_CT_END);
	}
	else
	{
		_outCT(req_ch, XS1_CT_NACK);
		_outCT(req_ch, XS1_CT_END);
	}
}

void stm32_uart_server(unsigned &req_ch, unsigned &service_ch)
{
	request_fifo_t request_fifo;
	msg_fifo_t msg_fifo;
	int connected;
	chanend current_dest;

	request_fifo_init(&request_fifo);
	msg_fifo_init(&msg_fifo);

	configure_clock_src(stm32_uart_clk, stm32_clk);
	configure_in_port(rx, stm32_uart_clk);
	configure_out_port_no_ready(tx, stm32_uart_clk, 1);
	start_clock(stm32_uart_clk);

	while (1)
	{
		if (isempty(request_fifo))
			connected = 0;
		else
		{
			// set destination of client channel to remote chanend that made
			// the request
			connected = 1;
			current_dest = request_fifo_pull(&request_fifo);
			_setChanEndDest(service_ch, current_dest);
			_outInt(service_ch, service_ch);
			_outCT(service_ch, XS1_CT_END);
			_chkCTI(service_ch, XS1_CT_END);
		}

		uart_service_request(&req_ch, &service_ch, current_dest, &request_fifo, &msg_fifo);

	}
}

unsigned int set_tx_length(unsigned int ct)
{
	if(ct == XS1_CT_TX0)
		return 0;
	else if(ct == XS1_CT_TX1)
		return 1;
	else if(ct == XS1_CT_TX2)
		return 2;
	else if(ct == XS1_CT_TX3)
		return 3;
	else if(ct == XS1_CT_TX4)
		return 4;
	else
		return ct; // Error condition -- return control token for debugging
}

unsigned int set_rx_length(unsigned int ct)
{
	if(ct == XS1_CT_RX0)
		return 0;
	else if(ct == XS1_CT_RX1)
		return 1;
	else if(ct == XS1_CT_RX2)
		return 2;
	else if(ct == XS1_CT_RX3)
		return 3;
	else if(ct == XS1_CT_RX4)
		return 4;
	else
		return ct; // Error condition -- return control token for debugging
}

int uart_service_request(unsigned &req_ch, unsigned &service_ch, NULLABLE_REFERENCE_PARAM(unsigned, client),
		request_fifo_t &request_fifo, msg_fifo_t &msg_fifo)
{
	timer tx_tmr, rx_tmr;
	int len = isnull(service_ch)?0:-1;
	unsigned char tx_count = 0;
	unsigned char rx_count = 0;
	unsigned int new_client_chanend;
	unsigned int next_tx_time, next_rx_time;
	static int init = 1;

	unsigned char tx_ct = _inCT(service_ch);
	if(!(tx_ct == XS1_CT_TX0 || tx_ct == XS1_CT_TX1 || tx_ct == XS1_CT_TX2 || tx_ct == XS1_CT_TX3 || tx_ct == XS1_CT_TX4))
	{
		_outCT(service_ch, XS1_CT_ERR);
		_outCT(service_ch, XS1_CT_END);
		_chkCTI(service_ch, XS1_CT_END);
		printstrln("UART service Error 1: Bad TX length CT.");
		return 1;	// Error 1: Bad TX length CT.
	}

	unsigned int tx_length = set_tx_length(tx_ct);	// bytes
	unsigned char rx_ct = _inCT(service_ch);	// Save this for later
	if(!(rx_ct == XS1_CT_RX0 || rx_ct == XS1_CT_RX1 || rx_ct == XS1_CT_RX2 || rx_ct == XS1_CT_RX3 || rx_ct == XS1_CT_RX4))
	{
		_outCT(service_ch, XS1_CT_ERR);
		_outCT(service_ch, XS1_CT_END);
		_chkCTI(service_ch, XS1_CT_END);
		printstrln("UART service Error 2: Bad RX length CT.");
		return 2;	// Error 2: Bad RX length CT.
	}

	unsigned int rx_length = set_rx_length(rx_ct);	// bytes
	unsigned char opcode = _inToken(service_ch);
	unsigned char opcode_ack;
	unsigned int data_in;
	unsigned int data_out = _inInt(service_ch);

	_chkCTI(service_ch, XS1_CT_END);
	_outCT(service_ch, XS1_CT_END);

	if (init)
	{
		init = 0;
		tx_tmr :> next_tx_time;
		rx_tmr :> next_rx_time;
		next_tx_time += INITIAL_UART_DELAY;
		next_rx_time += INITIAL_UART_DELAY;
	}
	tx_count = 10;
	rx_count = 10;

	// Send opcode
	while(tx_count)
	{
		select
		{
			case (tx_count == 10) => tx_tmr when timerafter(next_tx_time) :> void :
				partout(stm32_tx, 1, 0);	// Start bit
				next_tx_time += STM32_BIT_PRD;
				tx_count--;
				break;
			case (tx_count == 9) => tx_tmr when timerafter(next_tx_time) :> void :
				stm32_tx <: opcode;
				next_tx_time += (8*STM32_BIT_PRD);
				tx_count = 1;
				break;
			case (tx_count == 1) => tx_tmr when timerafter(next_tx_time) :> void :
				partout(stm32_tx, 1, 1);	// Stop bit
				next_tx_time += STM32_BIT_PRD;
				tx_count--;
				break;
			case inuint_byref(req_ch, new_client_chanend) :
				io_server_enqueue(req_ch, service_ch, new_client_chanend, request_fifo);
				break;
		}
	}
	tx_count = 10;

	// Receive opcode acknowledgement
	while(rx_count)
	{
		select
		{
			case (rx_count == 10) => stm32_rx when pinseq(0) :> opcode_ack :
				next_rx_time += (8*STM32_BIT_PRD);
				rx_count = 1;
				break;
			case (rx_count == 1) => rx_tmr when timerafter(next_rx_time) :> void :
				rx_count--;
				break;
			case inuint_byref(req_ch, new_client_chanend) :
				io_server_enqueue(req_ch, service_ch, new_client_chanend, request_fifo);
				break;
		}
	}
	rx_count = 10;

	// Verify ACK
	unsigned char ack_cmd_success = (opcode_ack & 0b1000000 == 1);
	unsigned char ack_opcode_success = (opcode_ack & opcode == opcode);
	unsigned char ack_success = ack_cmd_success && ack_opcode_success;
	int num_tx = 0;
	int num_rx = 0;
	unsigned char rx_tmp, tx_tmp;

	if(!ack_success)
	{
		if(!ack_cmd_success)
		{
			_outCT(service_ch, XS1_CT_ERR);
			_outDT(service_ch, opcode_ack);
			_outCT(service_ch, XS1_CT_END);
			_chkCTI(service_ch, XS1_CT_END);
			printstrln("UART service Error 3: ACK byte had CMD/ACK bit set to CMD.");
			printstr("Command opcode sent: ");
			printuint(opcode);
			printstr(" = ");
			printhexln(opcode);
			printstr("ACK opcode received: ");
			printuint(opcode_ack);
			printstr(" = ");
			printhexln(opcode_ack);
			return 3;	// Error 3: ACK byte had CMD/ACK bit set to CMD.
		}
		if(!ack_opcode_success)
		{
			// TODO: port data_bits and data_bytes from STM32
		/*
		 * In this state, the STM32 is erroneously expecting data for the wrong opcode.
		 * To prevent protocol-related problems with future transactions, we
		 * must send/receive the number of data bytes the STM32 is expecting.
		 *
		 * Sending the data requested by the client thread is not an option, as
		 * doing so could cause unexpected behavior from the STM32 if applied
		 * to the IO pins or U15. Given that some sort of malfunction is
		 * occurring, the safest data to send in this scenario is a full packet
		 * of zeroes. This will ensure that if the command data is used for
		 * undesired actuator control, it will set those actuators to their off state.
		 */
		// TODO : Refine this error handling based on the STM32 expected opcode.
			printstrln("UART service Error 4: ACK byte had wrong opcode.");
			printstr("Command opcode sent: ");
			printuint(opcode);
			printstr(" = ");
			printhexln(opcode);
			printstr("ACK opcode received: ");
			printuint(opcode_ack);
			printstr(" = ");
			printhexln(opcode_ack);
			data_out = 0;
			tx_length = (cmd_data_widths[(opcode_ack & 0b01111111)]+8-1)/8;
			rx_length = (cmd_data_widths[(opcode_ack & 0b01111111)]+8-1)/8;
		}

	}

	else
	{
		// TX and RX as determined by the TX/RX length settings
		while(tx_length || rx_length)
		{
			select
			{
				case (rx_length && rx_count == 10) => stm32_rx when pinseq(0) :> rx_tmp :
					next_rx_time += (8*STM32_BIT_PRD);
					rx_count = 1;
					break;
				case (rx_length && rx_count == 1) => rx_tmr when timerafter(next_rx_time) :> void :
					data_in |= (rx_tmp << (num_rx*8));
					rx_length--;
					num_rx++;
					rx_count = 10;
					break;
				case (tx_length && tx_count == 10) => tx_tmr when timerafter(next_tx_time) :> void :
					tx_tmp = ((0xFF << 8*num_tx) & data_out);
					partout(stm32_tx, 1, 0);	// Start bit
					next_tx_time += STM32_BIT_PRD;
					tx_count--;
					break;
				case (tx_length && tx_count == 9) => tx_tmr when timerafter(next_tx_time) :> void :
					tx_tmp <: data_out;
					next_tx_time += (8*STM32_BIT_PRD);
					tx_count = 1;
					break;
				case (tx_length && tx_count == 1) => tx_tmr when timerafter(next_tx_time) :> void :
					partout(stm32_tx, 1, 1);	// Stop bit
					next_tx_time += STM32_BIT_PRD;
					tx_length--;
					num_tx++;
					tx_count = 10;
					break;
				case inuint_byref(req_ch, new_client_chanend) :
					io_server_enqueue(req_ch, service_ch, new_client_chanend, request_fifo);
					break;
			}
		}
		if(rx_ct == XS1_CT_RX0)
			_outCT(service_ch, XS1_CT_NACK);
		else
		{
			_outCT(service_ch, XS1_CT_ACK);
			_outInt(service_ch, data_in);
		}
		_outCT(service_ch, XS1_CT_END);
		_chkCTI(service_ch, XS1_CT_END);
	}

	return 0;
}
