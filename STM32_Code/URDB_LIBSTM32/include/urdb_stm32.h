/*
 * urdb_stm32.h
 *
 *  Created on: Nov 6, 2011
 *      Author: Joe
 */

#ifndef URDB_STM32_H_
#define URDB_STM32_H_

#include <core_cm3.h>
#include <stm32l1xx_adc.h>
#include <stm32l1xx_dac.h>
#include <stm32l1xx_dma.h>
#include <stm32l1xx_flash.h>
#include <stm32l1xx_gpio.h>
#include <stm32l1xx_i2c.h>
#include <stm32l1xx_iwdg.h>
#include <stm32l1xx_pwr.h>
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_rtc.h>
#include <stm32l1xx_spi.h>
#include <stm32l1xx_syscfg.h>
#include <stm32l1xx_tim.h>
#include <stm32l1xx_usart.h>
#include <stm32l1xx_wwdg.h>
#include "xmos_uart.h"

#define ARDUINO_A0_PORT		GPIO_A			// ADCIN_0 = PA0
#define ARDUINO_A0_PIN		GPIO_Pin_0		// ADCIN_0 = PA0
#define ARDUINO_A1_PORT		GPIO_A			// ADCIN_1 = PA1
#define ARDUINO_A1_PIN		GPIO_Pin_1		// ADCIN_1 = PA1
#define ARDUINO_A2_PORT		GPIO_A			// ADCIN_4 = PA4
#define ARDUINO_A2_PIN		GPIO_Pin_4		// ADCIN_4 = PA4
#define ARDUINO_A3_PORT		GPIO_A			// ADCIN_5 = PA5
#define ARDUINO_A3_PIN		GPIO_Pin_5		// ADCIN_5 = PA5
#define ARDUINO_A4_PORT		GPIO_C			// ADCIN_15 = PC5
#define ARDUINO_A4_PIN		GPIO_Pin_15		// ADCIN_15 = PC5
#define ARDUINO_A5_PORT		GPIO_C			// ADCIN_14 = PC4
#define ARDUINO_A5_PIN		GPIO_Pin_4		// ADCIN_14 = PC4

#define ARDUINO_SCL_MODE_PORT	GPIO_A		// PA7
#define ARDUINO_SCL_MODE_PIN	GPIO_Pin_7	// PA7
#define ARDUINO_SDA_MODE_PORT	GPIO_A		// PA6
#define ARDUINO_SDA_MODE_PIN	GPIO_Pin_6	// PA6
#define ARDUINO_SCL_PORT		GPIO_B		// I2C2 SCL = PB10
#define ARDUINO_SCL_PIN			GPIO_Pin_10	// I2C2 SCL = PB10
#define ARDUINO_SDA_PORT		GPIO_B		// I2C2 SDA = PB11
#define ARDUINO_SDA_PIN			GPIO_Pin_11	// I2C2 SDA = PB11

#define ARDUINO_D0_PORT		GPIO_D		// U3TX = PD8
#define ARDUINO_D0_PIN		GPIO_Pin_8	// U3TX = PD8
#define ARDUINO_D1_PORT		GPIO_D		// U3RX = PD9
#define ARDUINO_D1_PIN		GPIO_Pin_9	// U3RX = PD9
#define ARDUINO_D2_PORT		GPIO_E		// PE14
#define ARDUINO_D2_PIN		GPIO_Pin_14	// PE14
#define ARDUINO_D3_PORT		GPIO_B		// PB12
#define ARDUINO_D3_PIN		GPIO_Pin_12	// PB12
#define ARDUINO_D4_PORT		GPIO_E		// PE15
#define ARDUINO_D4_PIN		GPIO_Pin_15	// PE15
#define ARDUINO_D5_PORT		GPIO_B		// PB13
#define ARDUINO_D5_PIN		GPIO_Pin_13	// PB13
#define ARDUINO_D6_PORT		GPIO_B		// PB14
#define ARDUINO_D6_PIN		GPIO_Pin_14	// PB14
#define ARDUINO_D7_PORT		GPIO_D		// PD10
#define ARDUINO_D7_PIN		GPIO_Pin_10	// PD10
#define ARDUINO_D8_PORT		GPIO_D		// PD11
#define ARDUINO_D8_PIN		GPIO_Pin_11	// PD11
#define ARDUINO_D9_PORT		GPIO_D		// PD12
#define ARDUINO_D9_PIN		GPIO_Pin_12	// PD12
#define ARDUINO_D10_PORT	GPIO_D		// SPI2_NSS = PD0
#define ARDUINO_D10_PIN		GPIO_Pin_0	// SPI2_NSS = PD0
#define ARDUINO_D11_PORT	GPIO_B		// SPI2_MOSI = PB15
#define ARDUINO_D11_PIN		GPIO_Pin_15	// SPI2_MOSI = PB15
#define ARDUINO_D12_PORT	GPIO_D		// SPI2_MISO = PD3
#define ARDUINO_D12_PIN		GPIO_Pin_3	// SPI2_MISO = PD3
#define ARDUINO_D13_PORT	GPIO_D		// SPI2_SCK = PD1
#define ARDUINO_D13_PIN		GPIO_Pin_1	// SPI2_SCK = PD1

#define XMOS_TX_PORT	GPIO_B		// U1TX = PB6
#define XMOS_TX_PIN		GPIO_Pin_6	// U1TX = PB6
#define XMOS_RX_PORT	GPIO_B		// U1RX = PB7
#define XMOS_RX_PIN		GPIO_Pin_7	// U1RX = PB7

#define M0_ADC_PORT		GPIO_B		// ADCIN_8 = PB0
#define M0_ADC_PIN		GPIO_Pin_0	// ADCIN_8 = PB0
#define M1_ADC_PORT		GPIO_B		// ADCIN_9 = PB1
#define M1_ADC_PIN		GPIO_Pin_1	// ADCIN_9 = PB1
#define M2_ADC_PORT		GPIO_E		// ADCIN_22 = PE7
#define M2_ADC_PIN		GPIO_Pin_7	// ADCIN_22 = PE7

#define EXT_ADC_0_PORT	GPIO_C		// ADCIN_10 = PC0
#define EXT_ADC_0_PIN	GPIO_Pin_0	// ADCIN_10 = PC0
#define EXT_ADC_1_PORT	GPIO_C		// ADCIN_11 = PC1
#define EXT_ADC_1_PIN	GPIO_Pin_1	// ADCIN_11 = PC1
#define EXT_ADC_2_PORT	GPIO_C		// ADCIN_12 = PC2
#define EXT_ADC_2_PIN	GPIO_Pin_2	// ADCIN_12 = PC2
#define EXT_ADC_3_PORT	GPIO_C		// ADCIN_13 = PC3
#define EXT_ADC_3_PIN	GPIO_Pin_3	// ADCIN_13 = PC3
#endif /* URDB_STM32_H_ */
