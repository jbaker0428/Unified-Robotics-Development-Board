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

#define CLK_REF	100000000	// TODO : This may not be the correct value

#define GADGETEER_CORE	0
#define	PMOD_O_CORE		0
#define	PMOD_1_CORE		0
#define	SERVO_CORE		0
#define	STM32_CORE		0

#define I2C_CORE		1
#define SPI_CORE		1
#define MOTOR_CORE		1
#define PMOD_2_CORE		1

#endif /* URDB_H_ */
