/*
 * io_servers.xc
 *
 *  Created on: Jan 12, 2012
 *      Author: joe
 */

#include "urdb.h"
#include "io_servers.h"
#include "stm32.h"

unsigned int io_client_enqueue(unsigned &server, unsigned &client, client_fifo_t &client_fifo,
		io_request_t &request)
{
	unsigned int server_ack;

	_setChanEndDest(client, server);
	_outInt(server, client);	// Send client's resource ID
	_outCT(server, CT_END);
	_chkCTI(server, CT_END);

	// Wait for ACK from server
	server_ack = _inCT(server);
	_chkCTI(server, CT_END);

	if(server_ack == CT_ACK)
	{
		// Success, add to client FIFO
		client_fifo_push(client_fifo, request);
		return server_ack;
	}
	else if (server_ack == CT_NACK)
		return server_ack;
	else
		return -1;
}

void io_server_enqueue(unsigned &server, unsigned int new_req_chanend, REFERENCE_PARAM(request_fifo_t, req_fifo))
{
	_setChanEndDest(server, new_req_chanend);
	_chkCTI(server, CT_END);
	_outCT(server, CT_END);
	int push_success = request_fifo_push(req_fifo, new_req_chanend);

	if(push_success)
	{
		_outCT(server, CT_ACK);
		_outCT(server, CT_END);
	}
	else
	{
		_outCT(server, CT_NACK);
		_outCT(server, CT_END);
	}
}
