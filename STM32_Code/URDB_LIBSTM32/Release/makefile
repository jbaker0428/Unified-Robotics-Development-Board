IDIR = ../include
SDIR = ../src
OBJS = core_cm3.o misc.o stm32l1xx_adc.o stm32l1xx_comp.o stm32l1xx_crc.o stm32l1xx_dac.o stm32l1xx_dbgmcu.o stm32l1xx_dma.o \
stm32l1xx_exti.o stm32l1xx_flash_ramfunc.o stm32l1xx_flash.o stm32l1xx_gpio.o stm32l1xx_i2c.o stm32l1xx_it.o stm32l1xx_iwdg.o \
stm32l1xx_lcd.o stm32l1xx_pwr.o stm32l1xx_rcc.o stm32l1xx_rtc.o stm32l1xx_spi.o stm32l1xx_syscfg.o stm32l1xx_tim.o stm32l1xx_usart.o \
stm32l1xx_wwdg.o system_stm32l1xx.o xmos_uart.o

SOURCES = $(SDIR)/core_cm3.c $(SDIR)/misc.c $(SDIR)/stm32l1xx_adc.c $(SDIR)/stm32l1xx_comp.c $(SDIR)/stm32l1xx_crc.c \
$(SDIR)/stm32l1xx_dac.c $(SDIR)/stm32l1xx_dbgmcu.c $(SDIR)/stm32l1xx_dma.c $(SDIR)/stm32l1xx_exti.c $(SDIR)/stm32l1xx_flash_ramfunc.c \
$(SDIR)/stm32l1xx_flash.c $(SDIR)/stm32l1xx_gpio.c $(SDIR)/stm32l1xx_i2c.c $(SDIR)/stm32l1xx_it.c $(SDIR)/stm32l1xx_iwdg.c \
$(SDIR)/stm32l1xx_lcd.c $(SDIR)/stm32l1xx_pwr.c $(SDIR)/stm32l1xx_rcc.c $(SDIR)/stm32l1xx_rtc.c $(SDIR)/stm32l1xx_spi.c \
$(SDIR)/stm32l1xx_syscfg.c $(SDIR)/stm32l1xx_tim.c $(SDIR)/stm32l1xx_usart.c $(SDIR)/stm32l1xx_wwdg.c $(SDIR)/system_stm32l1xx.c \
$(SDIR)/xmos_uart.c
LIBS = -LC:\yagarto\lib
CC = arm-none-eabi-gcc.exe
AR = arm-none-eabi-ar.exe
DEBUG = -g
CFLAGS = -Wall $(DEBUG) -I$(IDIR) -IC:\yagarto\lib\gcc\arm-none-eabi\4.6.2\include -mthumb -march=armv7-m -mcpu=cortex-m3
AFLAGS = -r

all: urdb_libstm32.a

urdb_libstm32.a : $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking ARM Archiver'
	$(AR) $(AFLAGS) -o "urdb_libstm32.a" $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

%.o : $(SDIR)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking ARM Compiler'
	$(CC) -c $(CFLAGS) $< -o $@ 
	@echo 'Finished building: $<'
	@echo ' '

clean :
	\rm *.o