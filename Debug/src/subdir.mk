################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Files_Operations.cpp \
../src/main.cpp 

OBJS += \
./src/Files_Operations.o \
./src/main.o 

CPP_DEPS += \
./src/Files_Operations.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	/home/anael/Softwares/clang+llvm-6.0.0-x86_64-linux-gnu-ubuntu-14.04/bin/clang++ -std=c++17 -Istdc++fs -includelibc++experimental.a -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


