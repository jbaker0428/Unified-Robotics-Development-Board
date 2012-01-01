################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
XN_SRCS += \
../URDB.xn 


# Each subdirectory must supply rules for building sources it contributes
libURDB.a: ../URDB.xn $(USER_OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: Archiver'
	xmosar -r lib$@ "$<" $(USER_OBJS) $(LIBS) "../URDB.xn"
	@echo 'Finished building: $<'
	@echo ' '


