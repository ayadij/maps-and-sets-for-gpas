################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Student_Code/Factory.cpp \
../Student_Code/School.cpp \
../Student_Code/Student.cpp 

OBJS += \
./Student_Code/Factory.o \
./Student_Code/School.o \
./Student_Code/Student.o 

CPP_DEPS += \
./Student_Code/Factory.d \
./Student_Code/School.d \
./Student_Code/Student.d 


# Each subdirectory must supply rules for building sources it contributes
Student_Code/%.o: ../Student_Code/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


