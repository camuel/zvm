################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/runtime/image.c \
../src/runtime/mem.c \
../src/runtime/trap.c 

OBJS += \
./src/runtime/image.o \
./src/runtime/mem.o \
./src/runtime/trap.o 

C_DEPS += \
./src/runtime/image.d \
./src/runtime/mem.d \
./src/runtime/trap.d 


# Each subdirectory must supply rules for building sources it contributes
src/runtime/%.o: ../src/runtime/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DNACL_LINUX -DNACL_BLOCK_SHIFT=5 -DNACL_BUILD_SUBARCH=64 -DNACL_TARGET_SUBARCH=64 -I"/home/dazo/git/zvm/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


