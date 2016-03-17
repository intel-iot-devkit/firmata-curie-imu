# FirmataCurieIMU
Firmata wrapper for the CurieIMU library on the Arduino101

## Installation

1. Make sure you have the following dependencies installed in the `libraries` folder for your Arduino installation:
  - [ConfigurableFirmata](https://github.com/firmata/ConfigurableFirmata)
  - [CurieIMU](https://github.com/01org/corelibs-arduino101/tree/master/libraries/CurieIMU)

2. Clone or download and copy FirmataCurieIMU into the `libraries` folder for your Arduino installation:

## How to use

The simplest possible example that connects the CurieIMU devices, but nothing else within the Firmata interface, would be as follows:

```c
#include <ConfigurableFirmata.h>
#include <FirmataExt.h>
FirmataExt firmataExt;

#include <CurieIMU.h>
#include <FirmataCurieIMU.h>
FirmataCurieIMU curieIMU;

void systemResetCallback()
{
  firmataExt.reset();
}

void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);

  firmataExt.addFeature(curieIMU);

  Firmata.attach(SYSTEM_RESET, systemResetCallback);
  Firmata.begin(57600);

  // set reset to default config
  systemResetCallback();
}

void loop()
{
  while (Firmata.available()) {
    Firmata.processInput();
  }
}

```

As with any other sketch that uses ConfigurableFirmata, you can choose to include digital, analog, i2c, or any other interface that it supports. There are several examples of sketches that use ConfigurableFirmata along with FirmataCurieIMU in the **examples** directory.

## Firmata clients

### JavaScript

Example code that calls the FirmataCurieIMU SYSEX extended interface is here:

https://github.com/intel-iot-devkit/firmata-curie-imu.js

## Protocol

### Read accelerometer
#### Query
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_ACCEL       (0x00)
 * 3 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

#### Response
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
#### Query
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_GYRO        (0x01)
 * 3 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

#### Response
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

### Read temperature
#### Query
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_TEMP        (0x02)
 * 3 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

#### Response
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_TEMP        (0x02)
 * 3 int16 temperature, byte 0, bits 0-6 (LSB)
 * 4 int16 temperature, byte 0, bits 7-13 (MSB)
 * 5 int16 temperature, byte 1, bits 0-6 (LSB)
 * 6 int16 temperature, byte 1, bits 7-13 (MSB)
 * 7 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

### Enable shock detection
#### Query
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_SHOCK_DETECT     (0x03)
 * 3 enable/disable, bit 0
 * 4 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

#### Response
```c
NONE
```

To enable shock detection, send 1 as the enable flag (byte 3). To disable shock detection, send 0 as the enable flag (byte 3).

#### Message
When shock detection is enabled, the following message will be sent each time that a shock is detected:
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_SHOCK_DETECT     (0x03)
 * 3 axis (bits 0-3)
 * 4 direction (bit 0)
 * 5 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

### Enable step counter
#### Query
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_STEP_COUNTER     (0x04)
 * 3 enable/disable, bit 0
 * 4 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

#### Response
```c
NONE
```

To enable step detection, send 1 as the enable flag (byte 3). To disable step detection, send 0 as the enable flag (byte 3).

#### Message
When step counting is enabled, the following message will be sent each time a new step is registered:
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_STEP_COUNTER     (0x04)
 * 3 step count, bits 0-6 (LSB)
 * 4 step count, bits 7-13 (MSB)
 * 5 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

### Enable tap detection
#### Query
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_TAP_DETECT       (0x05)
 * 3 enable/disable, bit 0
 * 4 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

#### Response
```c
NONE
```

To enable tap detection, send 1 as the enable flag (byte 3). To disable tap detection, send 0 as the enable flag (byte 3).

#### Message
When tap detection is enabled, the following message will be sent each time a tap is detected:
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_TAP_DETECT       (0x05)
 * 3 axis (bits 0-3)
 * 4 direction (bit 0)
 * 5 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

### Read motion sensor
#### Query
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_MOTION      (0x06)
 * 3 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```

#### Response
```c
 /* -----------------------------------------------------
 * 0 START_SYSEX                (0xF0)
 * 1 CURIE_IMU                  (0x11)
 * 2 CURIE_IMU_READ_MOTION      (0x06)
 * 3 x axis accelerometer, bits 0-6 (LSB)
 * 4 x axis accelerometer, bits 7-13 (MSB)
 * 5 y axis accelerometer, bits 0-6 (LSB)
 * 6 y axis accelerometer, bits 7-13 (MSB)
 * 7 z axis accelerometer, bits 0-6 (LSB)
 * 8 z axis accelerometer, bits 7-13 (MSB)
 * 9 x axis gyro, bits 0-6 (LSB)
 * 10 x axis gyro, bits 7-13 (MSB)
 * 11 y axis gyro, bits 0-6 (LSB)
 * 12 y axis gyro, bits 7-13 (MSB)
 * 13 z axis gyro, bits 0-6 (LSB)
 * 14 z axis gyro, bits 7-13 (MSB)
 * 15 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```
