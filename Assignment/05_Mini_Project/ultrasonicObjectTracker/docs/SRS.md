# Software Requirements Specification
## Bare-Metal Register-Level Radar-Style Object Tracker

**Version:** 1.0
**Target Hardware:** Arduino UNO (ATmega328P), bare-metal AVR
**Author:** Nandhu Binoy
**Course:** Entri Elevate — Embedded Software Engineering, Mini Project

---

## 1. Purpose

This document specifies the functional and non-functional requirements for a bare-metal
AVR firmware system that performs servo-swept ultrasonic ranging, associates detections
into persistent tracks, estimates target range/velocity via a lightweight filter, and
reports structured telemetry over UART — without reliance on Arduino abstraction
libraries (`Servo.h`, `pulseIn()`, `Serial.print()`, HAL, or RTOS).

## 2. Scope

**In scope:**
- Register-level driver development for Timer1 (servo PWM + echo capture), USART0
  (telemetry), ADC (auxiliary channel demo)
- A minimal detection → association → track-state-estimation pipeline
- Structured, checksummed UART telemetry protocol
- Host-side unit testing of the tracking/filtering logic

**Out of scope (deferred to future extension):**
- Multi-sensor fusion (camera/ToF)
- Machine learning / classification
- RTOS or dynamic memory management
- Communication beyond point-to-point UART (no wireless, no networking)

## 3. Definitions

| Term | Meaning |
|---|---|
| Track | A persistent estimate of one target's range/bearing/velocity over time |
| Detection | A single range measurement at a given servo bearing, above threshold |
| Association | Matching a new detection to an existing track (or creating a new one) |
| Gate | Distance threshold used to decide if a detection belongs to a track |
| ICU | Input Capture Unit (Timer1 peripheral used to timestamp echo edges) |

## 4. System Overview

```
   [SG90 Servo] <--- PWM (Timer1, OC1A) ---   [ATmega328P]
   [HC-SR04]    ---> Trigger (GPIO)        ---   |
                <--- Echo (ICP1 capture)   ---   |
   [Potentiometer/LDR] --> ADC0                  |
                                                  |--> UART0 (TX) --> [PC / Serial console]
```

Main loop / scheduler sweeps the servo through a bearing range, triggers a ping at each
step, captures echo pulse width via interrupt, converts to range, runs it through the
detection/association/filter pipeline, and emits a telemetry packet per updated track.

## 5. Functional Requirements

| ID | Requirement |
|---|---|
| FR-1 | The system shall sweep the servo across a configurable bearing range (default 15°–165°) in configurable step increments (default 5°) using Timer1 Fast PWM, register-configured — no `Servo.h`. |
| FR-2 | The system shall trigger the HC-SR04 with a 10µs pulse per sweep step via direct GPIO register writes. |
| FR-3 | The system shall capture the echo pulse width using Timer1's Input Capture Unit (ICP1) and its associated interrupt — no `pulseIn()`. |
| FR-4 | The system shall convert captured pulse width to a range in cm using the speed-of-sound constant, in fixed-point arithmetic. |
| FR-5 | The system shall discard detections outside a valid range window (e.g., <2cm or >400cm) as sensor noise. |
| FR-6 | The system shall associate each valid detection with the nearest existing track within a gating distance, or create a new track if none qualifies. |
| FR-7 | The system shall update an associated track's range/velocity estimate using an alpha-beta (or 1D Kalman) filter. |
| FR-8 | The system shall delete a track after N (default 3) consecutive sweep cycles with no associated detection. |
| FR-9 | The system shall transmit a structured telemetry packet (sync byte, track ID, range, bearing, velocity, confidence, checksum) over USART0 (register-configured, 9600 baud default) after each track update. |
| FR-10 | The system shall sample one auxiliary ADC channel (potentiometer or LDR) periodically and include/report it independently, demonstrating direct ADMUX/ADCSRA register configuration. |
| FR-11 | The system shall use `volatile`-qualified shared state for all data written in ISR context and read in main context. |

## 6. Non-Functional Requirements

| ID | Requirement |
|---|---|
| NFR-1 | No dynamic memory allocation (`malloc`/`new`) — all track storage statically allocated (fixed-size array, max 4 tracks). |
| NFR-2 | No recursion. |
| NFR-3 | Build shall compile clean with `-Wall -Wextra -Werror -Wconversion` on avr-gcc. |
| NFR-4 | Core tracking/filtering logic (association + filter update) shall be hardware-independent and unit-testable on host (x86) via CMake. |
| NFR-5 | ISR execution time shall be bounded and minimal (timestamp capture + flag set only; heavy processing deferred to main loop). |
| NFR-6 | System shall recover gracefully from a missing echo (timeout, no hang). |

## 7. Constraints

- ATmega328P: 32KB flash, 2KB SRAM, 16MHz — track table and buffers must fit comfortably within SRAM budget (target: <512 bytes for tracker state).
- Fixed-point arithmetic preferred over floating point for filter math (deterministic timing, avoids AVR software float overhead) — decision to be finalized in design doc.
- Single UART also used for programming/debug — telemetry protocol must not conflict with bootloader use during flashing.

## 8. Acceptance Criteria

1. Firmware builds via CMake + avr-gcc toolchain file with zero warnings under NFR-3 flags.
2. Servo sweeps visibly and repeatably across configured range.
3. A single static object produces a stable track (consistent ID) across multiple sweep cycles.
4. Moving a hand toward/away from the sensor produces a visibly changing range and non-zero estimated velocity in telemetry output.
5. Removing the object causes the track to be deleted after the configured miss count, not to persist indefinitely.
6. Host-side unit tests for association/filter logic pass independently of hardware.
7. UART telemetry is correctly framed and checksum-valid, verifiable via serial terminal or simple PC-side parser.

## 9. Open Design Decisions (to resolve in Design Doc)

- Fixed-point Q format for range/velocity representation
- Exact alpha-beta gains vs. 1D Kalman gain computation (static vs. adaptive)
- Gating distance threshold value
- Telemetry packet byte layout
