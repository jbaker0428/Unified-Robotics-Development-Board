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

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

enum protocol {I2C, SPI, UART};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @fn void i2c_server(void)
 * @brief URDB I2C scheduler server
 * @param &server Reference to variable holding the server's resource ID
 */
void i2c_server(unsigned &server);

/**
 * @fn void spi_server(void)
 * @brief URDB SPI scheduler server
 * @param &server Reference to variable holding the server's resource ID
 */
void spi_server(unsigned &server);

/**
 * @fn void stm32_uart_server(void)
 * @brief URDB STM32 UART scheduler server
 * @param &server Reference to variable holding the server's resource ID
 */
void stm32_uart_server(unsigned &server);

/**
 * @fn unsigned int io_client_enqueue(unsigned &server, client_fifo_t &client_fifo, int data, int data_len, REFERENCE_PARAM(int, ret_data))
 * @brief Sends a request to be added to a server's queue
 * @param server Reference to variable holding the destination server's resource ID
 * @param client Reference to variable holding the client's chanend resource ID
 * @param client_fifo Client's IO request bookkeeping FIFO
 * @param data Data to be sent over the server's IO bus
 * @param data_len Number of words (based on IO bus word length) to be sent
 * @param ret_data Reference to variable that will hold any returned data over the IO bus
 * @return CT_ACK/CT_NACK token value returned by server
 */
unsigned int io_client_enqueue(unsigned &server, unsigned &client, client_fifo_t &client_fifo,
		int data, int data_len, REFERENCE_PARAM(int, ret_data));

#ifdef __cplusplus
}
#endif
#endif /* IO_SCHEDULER_H_ */
