cmake_minimum_required(VERSION 3.20)
project(radar_tracker_tests C)

# ---------------------------------------------------------------------------
# Host-side (native x86) unit tests for the hardware-independent tracker
# logic (src/tracker.c). Configure and build this DIRECTORY separately from
# the root project -- do NOT pass the AVR toolchain file here.
#
#   cmake -B ../build-tests -S .
#   cmake --build ../build-tests
#   ../build-tests/tracker_tests
# ---------------------------------------------------------------------------

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
#add_compile_options(-Wall -Wextra -Werror -Wconversion -Wshadow -g -fsanitize=address,undefined)
add_compile_options(-Wall -Wextra -Werror -Wconversion -Wshadow -g) # Since address sanitizer is not installed in my PC
#add_link_options(-fsanitize=address,undefined)

add_executable(tracker_tests
    test_tracker.c
    ${CMAKE_SOURCE_DIR}/../src/tracker.c
)
target_include_directories(tracker_tests PRIVATE ${CMAKE_SOURCE_DIR}/../include)

enable_testing()
add_test(NAME tracker_tests COMMAND tracker_tests)
