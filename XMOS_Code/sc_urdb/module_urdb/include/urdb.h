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

#define ETHERNET_CORE	1
#define IMU_I2C_CORE	3
#define SPI_CORE		0
#define STM32_CORE		2
#define XBEE_CORE		3
#define XTAG_UART_CORE	0
/**
 * @def PWM_CORE
 * Sets which core the PWM thread is to be run on.
 */
#define PWM_CORE		2
/**
 * @def NAVIGATION_CORE
 * Sets which core the navigation service is to be run on.
 * This service should poll the IMU, read encoders, etc.
 */
#define NAVIGATION_CORE	3

// Cores for other peripheral hardware

#define	PMOD_A_CORE		0
#define	PMOD_B_CORE		1
#define PMOD_C_CORE		2
#define UEXT_I2C_CORE	1
#define UEXT_UART_CORE	1


/**
 * @var imu_i2c_req_ch Resource ID for the I2C IO server request input chanend
 * @var imu_i2c_service_ch Resource ID for the I2C IO server request servicing chanend
 * @var spi_req_ch Resource ID for the SPI IO server request input chanend
 * @var spi_service_ch Resource ID for the SPI IO server request servicing chanend
 * @var stm32_req_ch Resource ID for the STM32 UART IO server request input chanend
 * @var stm32_service_ch Resource ID for the STM32 UART IO server request servicing chanend
 * @var pwm_chanend Resource ID for the PWM thread input chanend
 * @var navigation_chanend Resource ID for the navigation thread input chanend
 */
unsigned imu_eth_req_ch;
unsigned imu_eth_service_ch;
unsigned imu_i2c_req_ch;
unsigned imu_i2c_service_ch;
unsigned spi_req_ch;
unsigned spi_service_ch;
unsigned stm32_req_ch;
unsigned stm32_service_ch;
unsigned pwm_chanend;
unsigned navigation_chanend;
unsigned uext_i2c_req_ch;
unsigned uext_i2c_service_ch;
unsigned uext_uart_req_ch;
unsigned uext_uart_service_ch;
unsigned xbee_req_ch;
unsigned xbee_service_ch;
unsigned xtag_uart_req_ch;
unsigned xtag_uart_service_ch;



on stdcore[IMU_I2C_CORE] : struct r_i2c imu_i2c = { PORT_IMU_SCL, PORT_IMU_SDA };
// TODO: struct i2c_data_info i2c_data1; <--- in I2C server thread or here?
on stdcore[IMU_I2C_CORE] : in buffered port imu_interrupts = PORT_IMU_INTS;
on stdcore[IMU_I2C_CORE] : in buffered port compass_drdy = PORT_COMPASS_DRDY;
on stdcore[NAVIGATION_CORE] : in port encoder1 = PORT_QEI1;
on stdcore[NAVIGATION_CORE] : in port encoder2 = PORT_QEI2;
on stdcore[NAVIGATION_CORE] : in port encoder3 = PORT_QEI3;
on stdcore[NAVIGATION_CORE] : in port encoder4 = PORT_QEI4;

on stdcore[NAVIGATION_CORE] : in buffered port hbridge_diags = PORT_HBRIDGE_DIAGS;
on stdcore[NAVIGATION_CORE] : out port motordir_clr = PORT_MOTORDIR_CLR;
on stdcore[NAVIGATION_CORE] : out port motordir_clk = PORT_MOTORDIR_CLK;
on stdcore[NAVIGATION_CORE] : out port motordir_data = PORT_MOTORDIR_DATA;

on stdcore[NAVIGATION_CORE] : out port stepper_en = PORT_STEPPER_EN;
on stdcore[NAVIGATION_CORE] : out port stepper_in1= PORT_STEPPER_IN1;
on stdcore[NAVIGATION_CORE] : out port stepper_in2 = PORT_STEPPER_IN2;

on stdcore[NAVIGATION_CORE] : out port hbridge_modes = PORT_HBRIDGE_INPUTS;
on stdcore[PWM_CORE] : out buffered port:32 pwm_port = PORT_PWM;
on stdcore[STM32_CORE]: in	port stm32_clk = PORT_STM32_CLK;
on stdcore[STM32_CORE]: out buffered port:8 stm32_tx = PORT_STM32_TX;
on stdcore[STM32_CORE]: in	buffered port:8 stm32_rx = PORT_STM32_RX;
on stdcore[STM32_CORE]: clock stm32_uart_clk = XS1_CLKBLK_5;
on stdcore[UEXT_I2C_CORE] : struct r_i2c uext_i2c = { PORT_UEXT_SCL, PORT_UEXT_SDA };
on stdcore[UEXT_UART_CORE]: out	buffered port:8 uext_tx = PORT_UEXT_UART_TX;
on stdcore[UEXT_UART_CORE]: in	buffered port:8 uext_rx = PORT_UEXT_UART_RX;
on stdcore[XBEE_CORE]: out	buffered port:8 xbee_tx = PORT_XBEE_TX;
on stdcore[XBEE_CORE]: in	buffered port:8 xbee_rx = PORT_XBEE_RX;
on stdcore[XBEE_CORE]: out	port xbee_rts = PORT_XBEE_RTS;
on stdcore[XBEE_CORE]: in	buffered port xbee_cts = PORT_XBEE_CTS;
on stdcore[XTAG_UART_CORE]: out	buffered port:8 xtag_tx = PORT_USB_TX;
on stdcore[XTAG_UART_CORE]: in	buffered port:8 xtag_rx = PORT_USB_RX;

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
 * @param xbee_mode Boolean argument to run the XBEE UART I/O server. Pass one of the XBEE_MODE macros from io_servers.h.
 *
 */
void urdb_init(unsigned char xbee_mode);


#endif /* URDB_H_ */
