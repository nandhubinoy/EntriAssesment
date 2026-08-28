# ---------------------------------------------------------------------------
# AVR (ATmega328P / Arduino UNO) cross-compilation toolchain file for CMake.
#
# Usage:
#   cmake -B build-avr -S . -DCMAKE_TOOLCHAIN_FILE=cmake/avr-toolchain.cmake
#   cmake --build build-avr
#
# On Windows with a standalone AVR-GCC build (e.g. blog.zakkemble.net
# avr-gcc-builds) or the Arduino IDE's bundled toolchain, also pass:
#   -G "MinGW Makefiles"
# and make sure the toolchain's bin/ directory is on PATH.
# ---------------------------------------------------------------------------

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

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

set(AVR_MCU atmega328p CACHE STRING "Target AVR MCU")
set(F_CPU 16000000UL CACHE STRING "CPU clock frequency in Hz")

set(CMAKE_C_FLAGS_INIT   "-mmcu=${AVR_MCU} -DF_CPU=${F_CPU} -Os")
set(CMAKE_CXX_FLAGS_INIT "-mmcu=${AVR_MCU} -DF_CPU=${F_CPU} -Os")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-mmcu=${AVR_MCU}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(AVR_UPLOAD_PORT "/dev/ttyUSB0" CACHE STRING "Serial port for avrdude upload")
set(AVR_UPLOAD_BAUD "115200" CACHE STRING "Bootloader baud rate for avrdude upload")
set(AVR_PROGRAMMER  "arduino" CACHE STRING "avrdude programmer type")
