/**
 * urdb.xc
 *
 *  @date 1/1/2012
 *  @author jbaker
 */

#include "urdb.h"
#include "io_servers.h"
#include "xlog_support.h"

#define PWM_RESOLUTION 256
#define PWM_PERIOD (RESOLUTION*20)
#define PWM_NUM_PORTS 9
#define PWM_TIMESTEP 10

void urdb_init()
{
	// Allocate chanend resources for the IO servers/other threads and save the resource IDs
	par
	{
		on stdcore[I2C_CORE] : i2c_chanend = _getChanEnd();
		on stdcore[SPI_CORE] : spi_chanend = _getChanEnd();
		on stdcore[STM32_CORE] : stm32_uart_chanend = _getChanEnd();
		on stdcore[PWM_CORE] : pwm_chanend = _getChanEnd();
		on stdcore[NAVIGATION_CORE] : navigation_uart_chanend = _getChanEnd();
		on stdcore[0] : ref0 = XS1_CLKBLK_1;
		on stdcore[1] : ref1 = XS1_CLKBLK_1;
	}

	// Initialize ports
	on stdcore[PWM_CORE] : out buffered port:32 pwm_ports[] = { PORT_PWM_0, PORT_PWM_1, PORT_PWM_2, PORT_SERVO_0, PORT_SERVO_1, PORT_SERVO_2, PORT_SERVO_3, PORT_SERVO_4, PORT_SERVO_5 };

	// Execute all URDB threads
	par
	{
		on stdcore[I2C_CORE] : i2c_server();
		on stdcore[SPI_CORE] : spi_server();
		on stdcore[STM32_CORE] : stm32_uart_server();
		on stdcore[PWM_CORE] : pwmSingleBitPort(servo_chanend, ref1, pwm_ports,
			    PWM_NUM_PORTS, PWM_RESOLUTION, PWM_TIMESTEP, 1);
		// on stdcore[NAVIGATION_CORE] : Navigation thread
	}
}
