################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
XC_SRCS += \
../src/stm32.xc 

OBJS += \
./src/stm32.o 

XC_DEPS += \
./src/stm32.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.xc
	@echo 'Building file: $<'
	@echo 'Invoking: XC Compiler'
	xcc -O2 -g -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@ " -o $@ "$<" "../URDB.xn"
	@echo 'Finished building: $<'
	@echo ' '

src/libstm32.a: ./src/stm32.o $(USER_OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: Archiver'
	xmosar -r lib$@ "$<" $(USER_OBJS) $(LIBS) "../URDB.xn"
	@echo 'Finished building: $<'
	@echo ' '


