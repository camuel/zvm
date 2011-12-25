################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/sdk/rtlib/lua.c \
../src/sdk/rtlib/sqlite.c 

OBJS += \
./src/sdk/rtlib/lua.o \
./src/sdk/rtlib/sqlite.o 

C_DEPS += \
./src/sdk/rtlib/lua.d \
./src/sdk/rtlib/sqlite.d 


# Each subdirectory must supply rules for building sources it contributes
src/sdk/rtlib/%.o: ../src/sdk/rtlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DNACL_LINUX -DNACL_BLOCK_SHIFT=5 -DNACL_BUILD_SUBARCH=64 -DNACL_TARGET_SUBARCH=64 -I"/home/dazo/git/zvm/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


