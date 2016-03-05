# FirmataCurieIMU
Firmata wrapper for the CurieIMU library on the Arduino101

## Installation

1. Make sure you have the following dependencies installed in the `libraries` folder for your Arduino installation:
  - [ConfigurableFirmata](https://github.com/firmata/ConfigurableFirmata)
  - [CurieIMU](https://github.com/01org/corelibs-arduino101/tree/master/libraries/CurieIMU)

2. Clone or download and copy FirmataCurieIMU into the `libraries` folder for your Arduino installation:

## How to use

Instructions on how to create a sketch that uses FirmataCurieIMU

## Firmata clients

### JavaScript

Example code that calls the FirmataCurieIMU SYSEX extended interface

## Protocol

### Read accelerometer
Query
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_ACCEL       (0x00)
 * 3 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

Response
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_ACCEL       (0x00)
 * 3 x axis, bits 0-6 (LSB)
 * 4 x axis, bits 7-13 (MSB)
 * 5 y axis, bits 0-6 (LSB)
 * 6 y axis, bits 7-13 (MSB)
 * 7 z axis, bits 0-6 (LSB)
 * 8 z axis, bits 7-13 (MSB)
 * 9 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

### Read gyro
Query
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_GYRO        (0x01)
 * 3 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

Response
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_GYRO        (0x01)
 * 3 x axis, bits 0-6 (LSB)
 * 4 x axis, bits 7-13 (MSB)
 * 5 y axis, bits 0-6 (LSB)
 * 6 y axis, bits 7-13 (MSB)
 * 7 z axis, bits 0-6 (LSB)
 * 8 z axis, bits 7-13 (MSB)
 * 9 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```
