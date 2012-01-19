/**
 *	@file urdb.h
 *
 *	@date 11/9/2011
 *	@author jbaker
 */

#ifndef URDB_H_
#define URDB_H_

#include <xs1.h>
#include <platform.h>
#include <print.h>
#include <stdlib.h>
#include <syscall.h>
#include <stdio.h>
#include <xccompat.h>

// Cores for essential URDB threads

#define I2C_CORE		1
#define SPI_CORE		0
#define STM32_CORE		0
/**
 * @def PWM_CORE
 * Sets which core the PWM thread is to be run on.
 */
#define PWM_CORE		1
/**
 * @def NAVIGATION_CORE
 * Sets which core the navigation service is to be run on.
 */
#define NAVIGATION_CORE	1

// Cores for other peripheral hardware

#define GADGETEER_CORE	0
#define	PMOD_O_CORE		0
#define	PMOD_1_CORE		0
#define PMOD_2_CORE		1


/**
 * @var i2c_req_ch Resource ID for the I2C IO server request input chanend
 * @var i2c_service_ch Resource ID for the I2C IO server request servicing chanend
 * @var spi_req_ch Resource ID for the SPI IO server request input chanend
 * @var spi_service_ch Resource ID for the SPI IO server request servicing chanend
 * @var stm32_req_ch Resource ID for the STM32 UART IO server request input chanend
 * @var stm32_service_ch Resource ID for the STM32 UART IO server request servicing chanend
 * @var pwm_chanend Resource ID for the PWM thread input chanend
 * @var navigation_chanend Resource ID for the navigation thread input chanend
 */
unsigned i2c_req_ch;
unsigned i2c_service_ch;
unsigned spi_req_ch;
unsigned spi_service_ch;
unsigned stm32_req_ch;
unsigned stm32_service_ch;
unsigned pwm_chanend;
unsigned navigation_chanend;

on stdcore[PWM_CORE] : out buffered port:32 pwm_ports[] = { PORT_PWM_0, PORT_PWM_1, PORT_PWM_2, PORT_SERVO_0, PORT_SERVO_1, PORT_SERVO_2, PORT_SERVO_3, PORT_SERVO_4, PORT_SERVO_5 };
on stdcore[STM32_CORE]: in	port stm32_clk = PORT_STM32_CLK;
on stdcore[STM32_CORE]: out buffered port:8 stm32_tx = PORT_STM32_TX;
on stdcore[STM32_CORE]: in	buffered port:8 stm32_rx = PORT_STM32_RX;
on stdcore[STM32_CORE]: clock stm32_uart_clk = XS1_CLKBLK_5;

clock ref0;
clock ref1;

/**
 * @fn void urdb_init(void)
 * @brief Runs all threads related to the URDB firmware.
 *
 * The urdb_init function starts execution of all URDB firmware threads.
 * Before beginning thread execution, the chanend resources for the IO servers are allocated
 * and their resource IDs are saved to global vars.
 *
 */
void urdb_init(void);


#endif /* URDB_H_ */
