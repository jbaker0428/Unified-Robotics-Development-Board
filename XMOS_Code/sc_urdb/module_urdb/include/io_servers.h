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
 */
void i2c_server(void);

/**
 * @fn void spi_server(void)
 * @brief URDB SPI scheduler server
 */
void spi_server(void);

/**
 * @fn void stm32_uart_server(void)
 * @brief URDB STM32 UART scheduler server
 */
void stm32_uart_server(void);

#ifdef __cplusplus
}
#endif
#endif /* IO_SCHEDULER_H_ */
