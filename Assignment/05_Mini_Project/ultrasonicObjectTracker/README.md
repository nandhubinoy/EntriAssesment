# Bare-Metal Radar-Style Object Tracker

Register-level AVR firmware for the Arduino UNO (ATmega328P) implementing a
servo-swept ultrasonic ranging system with interrupt-driven timing, a
lightweight multi-target tracker, and structured UART telemetry — no
Arduino abstraction libraries (`Servo.h`, `pulseIn()`, `Serial.print()`).

See `docs/SRS.md` for full requirements. Design doc (`docs/design.md`) to follow.

## Hardware wiring

| Signal | Pin |
|---|---|
| Servo control (OC1B PWM) | D10 |
| HC-SR04 Trigger | D2 |
| HC-SR04 Echo (ICP1) | D8 |
| Aux ADC (potentiometer/LDR wiper) | A0 |
| UART (via USB/bootloader) | onboard |

> **Note:** servo signal is on **D10**, not the usual D9 — see the design
> note at the top of `src/timer.c` for why (Timer1 mode conflict between
> PWM TOP and input capture).

## Prerequisites

```bash
sudo apt-get install gcc-avr avr-libc binutils-avr avrdude cmake
```

## Build (AVR firmware)

```bash
cmake -B build-avr -S . -DCMAKE_TOOLCHAIN_FILE=cmake/avr-toolchain.cmake
cmake --build build-avr
```

Produces `build-avr/radar_tracker.elf` and `build-avr/radar_tracker.hex`,
and prints flash/SRAM usage after every build.

## Flash to hardware

```bash
cmake --build build-avr --target flash
```

Defaults assume an Arduino UNO bootloader on `/dev/ttyUSB0` at 115200 baud.
Override if needed:

```bash
cmake -B build-avr -S . -DCMAKE_TOOLCHAIN_FILE=cmake/avr-toolchain.cmake \
    -DAVR_UPLOAD_PORT=/dev/ttyACM0 -DAVR_UPLOAD_BAUD=115200
```

(On Windows, the port will look like `COM3` etc.)

## Host-side unit tests (tracker logic only, no hardware needed)

```bash
cmake -B build-tests -S tests
cmake --build build-tests
./build-tests/tracker_tests
```

Tests run under AddressSanitizer + UBSan. All logic in `src/tracker.c` is
hardware-independent by design (NFR-4) so it can be fully verified before
ever touching real hardware or noisy sensor data.

## Monitor telemetry

Connect a serial terminal (e.g. `screen /dev/ttyUSB0 9600` or the Arduino
IDE Serial Monitor) at 9600 baud. Binary telemetry packets (9 bytes: sync,
id, range, bearing, velocity, confidence, checksum — see `send_telemetry()`
in `src/main.c`) are interleaved with a plain-text `AUX:nnn` line per cycle
for the auxiliary ADC channel.

## Project status

- [x] SRS (`docs/SRS.md`)
- [x] CMake + AVR toolchain skeleton, builds clean under `-Wall -Wextra
      -Werror -Wconversion -Wshadow`
- [x] UART, Timer1 (servo PWM + echo capture), ADC drivers
- [x] Tracker core (association, alpha-beta filter, miss-aging) + host unit tests
- [ ] Design doc formalizing fixed-point format, filter gains, gate distance
- [ ] On-hardware validation against SRS acceptance criteria
- [ ] Final documentation pass
