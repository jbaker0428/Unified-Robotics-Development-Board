/**
 * urdb.xc
 *
 *  @date 1/1/2012
 *  @author jbaker
 */

#include "urdb.h"
#include "io_servers.h"
#include "xlog_support.h"

void urdb_init()
{
	// Allocate chanend resources for the IO servers/other threads and save the resource IDs
	par
	{
		on stdcore[I2C_CORE] : i2c_chanend = _getChanEnd();
		on stdcore[SPI_CORE] : spi_chanend = _getChanEnd();
		on stdcore[STM32_CORE] : stm32_uart_chanend = _getChanEnd();
		on stdcore[SERVO_CORE] : servo_chanend = _getChanEnd();
		on stdcore[MOTOR_CORE] : motor_chanend = _getChanEnd();
		on stdcore[NAVIGATION_CORE] : navigation_uart_chanend = _getChanEnd();
	}

	// Execute all URDB threads
	par
	{
		on stdcore[I2C_CORE] : i2c_server();
		on stdcore[SPI_CORE] : spi_server();
		on stdcore[STM32_CORE] : stm32_uart_server();
		// on stdcore[SERVO_CORE] : our modified pwm_singlebit_port
		// on stdcore[MOTOR_CORE] : our modified pwm_singlebit_port
		// on stdcore[NAVIGATION_CORE] : Navigation thread
	}
}
