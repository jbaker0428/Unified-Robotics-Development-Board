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

#define GADGETEER_CORE	0
#define	PMOD_O_CORE		0
#define	PMOD_1_CORE		0
#define	SERVO_CORE		0
#define	STM32_CORE		0

/**
 * @def NAVIGATION_CORE
 * Sets which core the navigation service is to be run on. This is the only essential URDB thread with a user-modifable core selection.
 */
#define NAVIGATION_CORE	1
#define I2C_CORE		1
#define SPI_CORE		1
#define MOTOR_CORE		1
#define PMOD_2_CORE		1

/**
 * @var i2c_chanend Resource ID for the I2C IO server input chanend
 * @var spi_chanend Resource ID for the SPI IO server input chanend
 * @var stm32_uart_chanend Resource ID for the STM32 UART IO server input chanend
 * @var servo_chanend Resource ID for the servo PWM thread input chanend
 * @var motor_chanend Resource ID for the motor PWM thread input chanend
 * @var navigation_chanend Resource ID for the navigation thread input chanend
 */
unsigned i2c_chanend;
unsigned spi_chanend;
unsigned stm32_uart_chanend;
unsigned servo_chanend;
unsigned motor_chanend;
unsigned navigation_chanend;

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
