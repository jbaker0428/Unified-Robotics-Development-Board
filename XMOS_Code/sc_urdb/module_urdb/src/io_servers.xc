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
		int data, int data_len, REFERENCE_PARAM(int, ret_data))
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
		client_fifo_push(client_fifo, data, server, data_len, ret_data);
		return server_ack;
	}
	else if (server_ack == CT_NACK)
		return server_ack;
	else
		return -1;
}
