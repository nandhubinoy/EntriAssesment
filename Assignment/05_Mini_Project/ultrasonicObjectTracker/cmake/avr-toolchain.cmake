# ---------------------------------------------------------------------------
# AVR (ATmega328P / Arduino UNO) cross-compilation toolchain file for CMake.
#
# Usage:
#   cmake -B build-avr -S . -DCMAKE_TOOLCHAIN_FILE=cmake/avr-toolchain.cmake
#   cmake --build build-avr
# ---------------------------------------------------------------------------

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# Skip compiler sanity checks that assume a hosted environment (no OS on AVR)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

find_program(AVR_CC  avr-gcc     REQUIRED)
find_program(AVR_CXX avr-g++)
find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_OBJDUMP avr-objdump)
find_program(AVR_SIZE    avr-size)
find_program(AVRDUDE     avrdude)

set(CMAKE_C_COMPILER   ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})
set(CMAKE_ASM_COMPILER ${AVR_CC})

# Target MCU and clock — Arduino UNO = ATmega328P @ 16MHz
set(AVR_MCU atmega328p CACHE STRING "Target AVR MCU")
set(F_CPU 16000000UL CACHE STRING "CPU clock frequency in Hz")

set(CMAKE_C_FLAGS_INIT   "-mmcu=${AVR_MCU} -DF_CPU=${F_CPU} -Os")
set(CMAKE_CXX_FLAGS_INIT "-mmcu=${AVR_MCU} -DF_CPU=${F_CPU} -Os")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-mmcu=${AVR_MCU}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Default serial port + baud for avrdude upload target (override with -D on configure)
set(AVR_UPLOAD_PORT "/dev/ttyUSB0" CACHE STRING "Serial port for avrdude upload")
set(AVR_UPLOAD_BAUD "115200" CACHE STRING "Bootloader baud rate for avrdude upload")
set(AVR_PROGRAMMER  "arduino" CACHE STRING "avrdude programmer type")