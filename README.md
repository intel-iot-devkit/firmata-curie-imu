# FirmataCurieIMU
Firmata wrapper for the CurieIMU library on the Arduino101

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
 * 3 x axis, integer
 * 4 y axis, integer
 * 5 z axis, integer
 * 6 END_SYSEX                  (0xF7)
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
 * 3 x axis, integer
 * 4 y axis, integer
 * 5 z axis, integer
 * 6 END_SYSEX                  (0xF7)
 * -----------------------------------------------------
 */
```
