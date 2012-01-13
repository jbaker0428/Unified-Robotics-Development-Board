/**
 *	@file MCP23017.h
 *
 *	@date 11/22/2011
 *	@author jbaker
 */

#ifndef MCP23017_H_
#define MCP23017_H_

#define	MCP23017_ADDRESS	0x20

#define MCP23017_REG_IODIRA		0x00
#define MCP23017_REG_IODIRB		0x01
#define MCP23017_REG_IPOLA		0x02
#define MCP23017_REG_IPOLB		0x03
#define MCP23017_REG_GPINTENA	0x04
#define MCP23017_REG_GPINTENB	0x05
#define MCP23017_REG_DEFVALA	0x06
#define MCP23017_REG_DEFVALB	0x07
#define MCP23017_REG_INTCONA	0x08
#define MCP23017_REG_INTCONB	0x09
#define MCP23017_REG_IOCONA		0x0A
#define MCP23017_REG_IOCONB		0x0B
#define MCP23017_REG_GPPUA		0x0C
#define MCP23017_REG_GPPUB		0x0D
#define MCP23017_REG_INTFA		0x0E
#define MCP23017_REG_INTFB		0x0F
#define MCP23017_REG_INTCAPA	0x10
#define MCP23017_REG_INTCAPB	0x11
#define MCP23017_REG_GPIOA		0x12
#define MCP23017_REG_GPIOB		0x13
#define MCP23017_REG_OLATA		0x14
#define MCP23017_REG_OLATB		0x15


// IOCON Register
#define IOCON_BANK		1 << 7
#define IOCON_MIRROR	1 << 6
#define IOCON_SEQOP		1 << 5
#define IOCON_DISSLW	1 << 4
#define IOCON_HAEN		1 << 3
#define IOCON_ODR		1 << 2
#define IOCON_INTPOL	1 << 1

/**
 * Initialize the MCP23017 with default URDB configuration.
 * Sets IOCON_SEQOP = 1
 * Sets IODIRA = 0b01100110  = 0x66
 * Sets IPOLA = 0b01100110 = 0x66
 * Sets IODIRB = 0b00000110 = 0x06
 * Sets IPOLB = 0b00000110 = 0x06
 * Sets GPINTENA = 0b01100110  = 0x66
 * Sets GPINTENB = 0b00000110 = 0x06
 * Sets DEFVALA = 0b01100110  = 0x66
 * Sets DEFVALB = 0b00000110 = 0x06
 * Sets INTCONA = 0b01100110  = 0x66
 * Sets INTCONB = 0b00000110 = 0x06
 * @param &server Reference to variable holding the I2C server's resource ID
 */
void mcp23017_init(unsigned &server);

#endif /* MCP23017_H_ */
