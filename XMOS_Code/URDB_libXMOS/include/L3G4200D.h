/*
 * L3G4200D.h
 *
 *  Created on: Nov 17, 2011
 *      Author: joe
 */

#ifndef L3G4200D_H_
#define L3G4200D_H_

// Registers						Address		Read/write type
#define	L3G4200D_REG_WHO_AM_I		0x0F		// Read only
#define	L3G4200D_REG_CTRL_1			0x20		// Read/Write
#define	L3G4200D_REG_CTRL_2			0x21		// Read/Write
#define	L3G4200D_REG_CTRL_3			0x22		// Read/Write
#define	L3G4200D_REG_CTRL_4			0x23		// Read/Write
#define	L3G4200D_REG_CTRL_5			0x24		// Read/Write
#define	L3G4200D_REG_REFERENCE		0x25		// Read/Write
#define	L3G4200D_REG_OUT_TEMP		0x26		// Read only
#define	L3G4200D_REG_STATUS			0x27		// Read only
#define	L3G4200D_REG_OUT_X_L		0x28		// Read only
#define	L3G4200D_REG_OUT_X_H		0x29		// Read only
#define	L3G4200D_REG_OUT_Y_L		0x2A		// Read only
#define	L3G4200D_REG_OUT_Y_H		0x2B		// Read only
#define	L3G4200D_REG_OUT_Z_L		0x2C		// Read only
#define	L3G4200D_REG_OUT_Z_H		0x2D		// Read only
#define	L3G4200D_REG_FIFO_CTRL		0x2E		// Read/Write
#define	L3G4200D_REG_FIFO_SRC		0x2F		// Read only
#define	L3G4200D_REG_INT1_CFG		0x30		// Read/Write
#define	L3G4200D_REG_INT1_SRC		0x31		// Read only
#define	L3G4200D_REG_INT1_TSH_XH	0x32		// Read/Write
#define	L3G4200D_REG_INT1_TSH_XL	0x33		// Read/Write
#define	L3G4200D_REG_INT1_TSH_YH	0x34		// Read/Write
#define	L3G4200D_REG_INT1_TSH_YL	0x35		// Read/Write
#define	L3G4200D_REG_INT1_TSH_ZH	0x36		// Read/Write
#define	L3G4200D_REG_INT1_TSH_ZL	0x37		// Read/Write
#define	L3G4200D_REG_INT1_DURATION	0x38		// Read/Write

// CTRL_REG1 Register
#define CTRL_REG1_DR1		1 << 7
#define CTRL_REG1_DR0		1 << 6
#define CTRL_REG1_BW1		1 << 5
#define CTRL_REG1_BW0		1 << 4
#define CTRL_REG1_PD		1 << 3
#define CTRL_REG1_ZEN		1 << 2
#define CTRL_REG1_YEN		1 << 1
#define CTRL_REG1_XEN		1

// CTRL_REG2 Register
#define CTRL_REG2_HPM1		1 << 5
#define CTRL_REG2_HPM0		1 << 4
#define CTRL_REG2_HPCF3		1 << 3
#define CTRL_REG2_HPCF2		1 << 2
#define CTRL_REG2_HPCF1		1 << 1
#define CTRL_REG2_HPCF0		1

// CTRL_REG3 Register
#define CTRL_REG3_I1_INT1	1 << 7
#define CTRL_REG3_I1_BOOT	1 << 6
#define CTRL_REG3_H_LACTIVE	1 << 5
#define CTRL_REG3_PP_OD		1 << 4
#define CTRL_REG3_I2_DRDY	1 << 3
#define CTRL_REG3_I2_WTM	1 << 2
#define CTRL_REG3_ORUN		1 << 1
#define CTRL_REG3_EMPTY		1

// CTRL_REG4 Register
#define CTRL_REG4_BDU		1 << 7
#define CTRL_REG4_BLE		1 << 6
#define CTRL_REG4_FS1		1 << 5
#define CTRL_REG4_FS0		1 << 4
#define CTRL_REG4_ST1		1 << 2
#define CTRL_REG4_ST0		1 << 1
#define CTRL_REG4_SIM		1

// CTRL_REG5 Register
#define CTRL_REG5_BOOT		1 << 7
#define CTRL_REG5_FIFO_EN	1 << 6
#define CTRL_REG5_HPEN		1 << 4
#define CTRL_REG5_INT1_SEL1	1 << 3
#define CTRL_REG5_INT1_SEL0	1 << 2
#define CTRL_REG5_OUT_SEL1	1 << 1
#define CTRL_REG5_OUT_SEL0	1


#endif /* L3G4200D_H_ */
