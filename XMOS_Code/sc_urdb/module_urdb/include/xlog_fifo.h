// Copyright (c) 2011, XMOS Ltd., All rights reserved
// This software is freely distributable under a derivative of the
// University of Illinois/NCSA Open Source License posted in
// LICENSE.txt and at <http://github.xcore.com/>

#ifndef _xlog_fifo_h_
#define _xlog_fifo_h_
#include <xccompat.h>
#ifdef __xlog_conf_h_exists__
#include "xlog_conf.h"
#endif

#ifndef XLOG_MSG_FIFO_LEN
#define XLOG_MSG_FIFO_LEN 256
#endif

#define XLOG_REQUEST_FIFO_LEN 32

typedef struct io_request_t {
	unsigned int data;			// Data to transmit
	unsigned char data_len;		// Number of IO bus words to transmit
	REFERENCE_PARAM(unsigned, ret_data);	// Where to save reply data
	unsigned char serviced;		// Status flag
} io_request_t;

typedef struct msg_fifo_t {
  int rdIndex;
  int wrIndex;
  char msg_fifo[XLOG_MSG_FIFO_LEN];
} msg_fifo_t;


typedef struct request_fifo_t {
  int rdIndex;
  int wrIndex;
  int request_fifo[XLOG_REQUEST_FIFO_LEN];
} request_fifo_t;

typedef struct client_fifo_t {
	int rdIndex;
	int wrIndex;
	io_request_t request_fifo[XLOG_REQUEST_FIFO_LEN];
	int server_req;		// Resource ID of server associated with the FIFO
	int server_service;		// Resource ID of server associated with the FIFO
} client_fifo_t;

#define isempty(x) (x.rdIndex == x.wrIndex)

void msg_fifo_init(REFERENCE_PARAM(msg_fifo_t, x));
void msg_fifo_push(REFERENCE_PARAM(msg_fifo_t, x), char c);
char  msg_fifo_pull(REFERENCE_PARAM(msg_fifo_t, x));

void request_fifo_init(REFERENCE_PARAM(request_fifo_t, x));
int request_fifo_push(REFERENCE_PARAM(request_fifo_t, x), unsigned int d);
unsigned int  request_fifo_pull(REFERENCE_PARAM(request_fifo_t, x));

void client_fifo_init(REFERENCE_PARAM(client_fifo_t, x), unsigned &server_req, unsigned &server_service);
void client_fifo_push(REFERENCE_PARAM(client_fifo_t, x), REFERENCE_PARAM(io_request_t, r));

void client_fifo_pull(REFERENCE_PARAM(client_fifo_t, x), REFERENCE_PARAM(io_request_t, r));

#endif //_xlog_fifo_h_
