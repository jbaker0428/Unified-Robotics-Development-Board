/*
 * HMC5883L.h
 *
 *  Created on: Nov 11, 2011
 *      Author: joe
 */

#ifndef HMC5883L_H_
#define HMC5883L_H_

// I2C Address
#define HMC5883L_READ_ADDR			0x3D
#define HMC5883L_WRITE_ADDR			0x3C

// Registers
#define	HMC5883L_REG_CRA			0x00	// Read/Write
#define	HMC5883L_REG_CRB			0x01	// Read/Write
#define	HMC5883L_REG_MODE			0x02	// Read only
#define HMC5883L_REG_DATA_X_MSB		0x03	// Read only
#define HMC5883L_REG_DATA_X_LSB		0x04	// Read only
#define HMC5883L_REG_DATA_Z_MSB		0x05	// Read only
#define HMC5883L_REG_DATA_Z_LSB		0x06	// Read only
#define HMC5883L_REG_DATA_Y_MSB		0x07	// Read only
#define HMC5883L_REG_DATA_Y_LSB		0x08	// Read only
#define HMC5883L_REG_STATUS			0x09	// Read only
#define HMC5883L_REG_ID_A			0x0A	// Read only
#define HMC5883L_REG_ID_B			0x0B	// Read only
#define HMC5883L_REG_ID_C			0x0C	// Read only

// Configuration Register A
#define CRA_MA1	1 << 6
#define CRA_MA0	1 << 5
#define CRA_DO2	1 << 4
#define CRA_DO1	1 << 3
#define CRA_DO0	1 << 2
#define CRA_MS1 1 << 1
#define CRA_MS0	1

// Configuration Register B
#define CRB_GN2	1 << 7
#define CRB_GN1	1 << 6
#define CRB_GN0	1 << 5

// Mode Register
#define MR_MD1	1 << 1
#define MR_MD0	1

// Status Register
#define SR_LOCK	1 << 1
#define	SR_RDY	1

#endif /* HMC5883L_H_ */
