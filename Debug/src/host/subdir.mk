################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/host/io.c \
../src/host/mem.c \
../src/host/proc.c \
../src/host/random.c \
../src/host/time.c 

OBJS += \
./src/host/io.o \
./src/host/mem.o \
./src/host/proc.o \
./src/host/random.o \
./src/host/time.o 

C_DEPS += \
./src/host/io.d \
./src/host/mem.d \
./src/host/proc.d \
./src/host/random.d \
./src/host/time.d 


# Each subdirectory must supply rules for building sources it contributes
src/host/%.o: ../src/host/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DNACL_LINUX -DNACL_BLOCK_SHIFT=5 -DNACL_BUILD_SUBARCH=64 -DNACL_TARGET_SUBARCH=64 -I"/home/dazo/git/zvm/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


