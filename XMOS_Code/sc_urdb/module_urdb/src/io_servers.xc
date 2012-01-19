/*
 * io_servers.xc
 *
 *  Created on: Jan 12, 2012
 *      Author: joe
 */

#include "urdb.h"
#include "io_servers.h"
#include "stm32.h"

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

void uart_service_request(unsigned &req_ch, unsigned &service_ch, NULLABLE_REFERENCE_PARAM(unsigned, client),
		request_fifo_t &request_fifo, msg_fifo_t &msg_fifo)
{

}
