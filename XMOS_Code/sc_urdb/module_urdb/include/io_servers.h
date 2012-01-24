/*
 * io_scheduler.h
 *
 *  @date Jan 1, 2012
 *  @author jbaker
 */
#include <xccompat.h>
#include "urdb.h"
#include "xlog_fifo.h"
#include "xlog_support.h"

#ifndef IO_SERVERS_H_
#define IO_SERVERS_H_

#define XS1_CT_TX0	0x5
#define XS1_CT_TX1	0x6
#define XS1_CT_TX2	0x7
#define XS1_CT_TX3	0x8
#define XS1_CT_TX4	0x9
#define XS1_CT_RX0	0xA
#define XS1_CT_RX1	0xB
#define XS1_CT_RX2	0xC
#define XS1_CT_RX3	0xD
#define XS1_CT_RX4	0xE
#define XS1_CT_ERR	0xF

#define INITIAL_UART_DELAY 100000000
#define CUSHION_TIME 100

enum protocol {I2C, SPI, UART};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @fn void i2c_server(void)
 * @brief URDB I2C scheduler server
 * @param &req_ch Reference to variable holding the server's request channel resource ID
 * @param &service_ch Reference to variable holding the server's service channel resource ID
 */
void i2c_server(unsigned &req_ch, unsigned &service_ch);

/**
 * @fn void spi_server(void)
 * @brief URDB SPI scheduler server
 * @param &req_ch Reference to variable holding the server's request channel resource ID
 * @param &service_ch Reference to variable holding the server's service channel resource ID
 */
void spi_server(unsigned &req_ch, unsigned &service_ch);

/**
 * @fn void stm32_uart_server(void)
 * @brief URDB STM32 UART scheduler server
 * @param &req_ch Reference to variable holding the server's request channel resource ID
 * @param &service_ch Reference to variable holding the server's service channel resource ID
 */
void stm32_uart_server(unsigned &req_ch, unsigned &service_ch);

/**
 * @fn void xbee_uart_server(void)
 * @brief URDB XBee UART scheduler server
 * @param &req_ch Reference to variable holding the server's request channel resource ID
 * @param &service_ch Reference to variable holding the server's service channel resource ID
 */
void xbee_uart_server(unsigned &req_ch, unsigned &service_ch);

unsigned int set_tx_length(unsigned int ct);
unsigned int set_rx_length(unsigned int ct);

/**
 * @fn int stm32_service_request(unsigned &server, NULLABLE_REFERENCE_PARAM(unsigned, client), request_fifo_t &request_fifo, msg_fifo_t &msg_fifo)
 * @brief Services STM32 UART server requests
 * @param &req_ch Reference to variable holding the server's request channel resource ID
 * @param &service_ch Reference to variable holding the server's service channel resource ID
 * @param client_ch Resource ID of remote client chanend
 * @param request_fifo Server's request FIFO
 * @return Returns 0 if successful
 */
int stm32_service_request(unsigned &req_ch, unsigned &service_ch, NULLABLE_RESOURCE(unsigned, client_ch),
		request_fifo_t &request_fifo);

/**
 * @fn unsigned int io_client_enqueue(unsigned &server, unsigned &client, client_fifo_t &client_fifo, int data, int data_len, REFERENCE_PARAM(int, ret_data))
 * @brief Sends a request to be added to a server's queue
 * @param &server_req Reference to variable holding the server's request channel resource ID
 * @param &server_service Reference to variable holding the server's service channel resource ID
 * @param client Reference to variable holding the client's chanend resource ID
 * @param client_fifo Client's IO request bookkeeping FIFO
 * @param request Structure of type io_request_t containing IO request information
 * @return CT_ACK/CT_NACK token value returned by server
 */
unsigned int io_client_enqueue(unsigned &server_req, unsigned &server_service, unsigned &client, client_fifo_t &client_fifo,
		io_request_t &request);

/**
 * @fn void io_server_enqueue(unsigned &server, unsigned int new_req_chanend, REFERENCE_PARAM(request_fifo_t, req_fifo))
 * @brief Gets new client request and adds it to the request FIFO
 * @param &req_ch Reference to variable holding the server's request channel resource ID
 * @param &service_ch Reference to variable holding the server's service channel resource ID
 * @param new_req_chanend Resource ID of client chanend making request
 * @param req_fifo Reference to server's request FIFO
 */
void io_server_enqueue(unsigned &req_ch, unsigned &service_ch, unsigned int new_req_chanend, REFERENCE_PARAM(request_fifo_t, req_fifo));

#ifdef __cplusplus
}
#endif
#endif /* IO_SERVERS_H_ */
