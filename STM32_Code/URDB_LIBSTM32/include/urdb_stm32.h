/*
 * urdb_stm32.h
 *
 *  Created on: Nov 6, 2011
 *      Author: Joe
 */

#ifndef URDB_STM32_H_
#define URDB_STM32_H_

#define ARDUINO_A0 // ADCIN_0 = PA0
#define ARDUINO_A1 // ADCIN_1 = PA1
#define ARDUINO_A2 // ADCIN_4 = PA4
#define ARDUINO_A3 // ADCIN_5 = PA5
#define ARDUINO_A4 // ADCIN_15 = PC5
#define ARDUINO_A5 // ADCIN_14 = PC4

#define ARDUINO_SCL_MODE // PA7
#define ARDUINO_SDA_MODE // PA6
#define ARDUINO_SCL // I2C2 SCL = PB10
#define ARDUINO_SDA // I2C2 SDA = PB11

#define ARDUINO_D0 // U3TX = PD8
#define ARDUINO_D1 // U3RX = PD9
#define ARDUINO_D2 // PE14
#define ARDUINO_D3 // PB12
#define ARDUINO_D4 // PE15
#define ARDUINO_D5 // PB13
#define ARDUINO_D6 // PB14
#define ARDUINO_D7 // PD10
#define ARDUINO_D8 // PD11
#define ARDUINO_D9 // PD12
#define ARDUINO_D10 // SPI2_NSS = PD0
#define ARDUINO_D11 // SPI2_MOSI = PB15
#define ARDUINO_D12 // SPI2_MISO = PD3
#define ARDUINO_D13 // SPI2_SCK = PD1

#define XMOS_TX // U1TX = PB6
#define XMOS_RX // U1RX = PB7

#define M0_ADC // ADCIN_8 = PB0
#define M1_ADC // ADCIN_9 = PB1
#define M2_ADC // ADCIN_22 = PE7

#define EXT_ADC_0 // ADCIN_10 = PC0
#define EXT_ADC_1 // ADCIN_11 = PC1
#define EXT_ADC_2 // ADCIN_12 = PC2
#define EXT_ADC_3 // ADCIN_13 = PC3
#endif /* URDB_STM32_H_ */
