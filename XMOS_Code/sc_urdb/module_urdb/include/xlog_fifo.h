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
	int data_fifo[XLOG_REQUEST_FIFO_LEN];
	unsigned char length_fifo[XLOG_REQUEST_FIFO_LEN];
	REFERENCE_PARAM(int, return_fifo[XLOG_REQUEST_FIFO_LEN]);	// Reference to return data var
};

#define isempty(x) (x.rdIndex == x.wrIndex)

void msg_fifo_init(REFERENCE_PARAM(msg_fifo_t, x));
void msg_fifo_push(REFERENCE_PARAM(msg_fifo_t, x), char c);
char  msg_fifo_pull(REFERENCE_PARAM(msg_fifo_t, x));

void request_fifo_init(REFERENCE_PARAM(request_fifo_t, x));
int request_fifo_push(REFERENCE_PARAM(request_fifo_t, x), unsigned int d);
unsigned int  request_fifo_pull(REFERENCE_PARAM(request_fifo_t, x));

void client_fifo_init(REFERENCE_PARAM(request_fifo_t, x));
void client_fifo_push(REFERENCE_PARAM(request_fifo_t, x), unsigned int data, unsigned char length_token, REFERENCE_PARAM(int, ret_ref));
void client_fifo_pull(REFERENCE_PARAM(request_fifo_t, x), REFERENCE_PARAM(unsigned int, data), REFERENCE_PARAM(unsigned char, length_token), REFERENCE_PARAM(int, ret_ref));

#endif //_xlog_fifo_h_
