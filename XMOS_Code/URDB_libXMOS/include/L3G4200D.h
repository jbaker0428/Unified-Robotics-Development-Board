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

// STATUS_REG Register
#define STATUS_REG_ZYXOR	1 << 7
#define STATUS_REG_ZOR		1 << 6
#define STATUS_REG_YOR		1 << 5
#define STATUS_REG_XOR		1 << 4
#define STATUS_REG_ZYXDA	1 << 3
#define STATUS_REG_ZDA		1 << 2
#define STATUS_REG_YDA		1 << 1
#define STATUS_REG_XDA		1

// FIFO_CTRL_REG Register
#define FIFO_CTRL_REG_FM2	1 << 7
#define FIFO_CTRL_REG_FM1	1 << 6
#define FIFO_CTRL_REG_FM0	1 << 5
#define FIFO_CTRL_REG_WTM4	1 << 4
#define FIFO_CTRL_REG_WTM3	1 << 3
#define FIFO_CTRL_REG_WTM2	1 << 2
#define FIFO_CTRL_REG_WTM1	1 << 1
#define FIFO_CTRL_REG_WTM0	1

// FIFO_SRC_REG Register
#define FIFO_SRC_REG_WTM	1 << 7
#define FIFO_SRC_REG_OVRN	1 << 6
#define FIFO_SRC_REG_EMPTY	1 << 5
#define FIFO_SRC_REG_FSS4	1 << 4
#define FIFO_SRC_REG_FSS3	1 << 3
#define FIFO_SRC_REG_FSS2	1 << 2
#define FIFO_SRC_REG_FSS1	1 << 1
#define FIFO_SRC_REG_FSS0	1

// INT1_CFG Register
#define INT1_CFG_ANDOR		1 << 7
#define INT1_CFG_LIR		1 << 6
#define INT1_CFG_ZHIE		1 << 5
#define INT1_CFG_ZLIE		1 << 4
#define INT1_CFG_YHIE		1 << 3
#define INT1_CFG_YLIE		1 << 2
#define INT1_CFG_XHIE		1 << 1
#define INT1_CFG_XLIE		1

// INT1_SRC Register
#define INT1_SRC_IA			1 << 6
#define INT1_SRC_ZH			1 << 5
#define INT1_SRC_ZL			1 << 4
#define INT1_SRC_YH			1 << 3
#define INT1_SRC_YL			1 << 2
#define INT1_SRC_XH			1 << 1
#define INT1_SRC_XL			1

// INT1_DURATION Register
#define INT1_DURATION_WAIT	1 << 7
#define INT1_DURATION_D6	1 << 6
#define INT1_DURATION_D5	1 << 5
#define INT1_DURATION_D4	1 << 4
#define INT1_DURATION_D3	1 << 3
#define INT1_DURATION_D2	1 << 2
#define INT1_DURATION_D1	1 << 1
#define INT1_DURATION_D0	1

#endif /* L3G4200D_H_ */
