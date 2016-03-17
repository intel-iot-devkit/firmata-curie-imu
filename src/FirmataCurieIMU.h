/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef FirmataCurieIMU_h
#define FirmataCurieIMU_h

#include <ConfigurableFirmata.h>
#include <FirmataFeature.h>
#include <CurieIMU.h>

#define CURIE_IMU                   (0x11)

#define CURIE_IMU_READ_ACCEL        (0x00)
#define CURIE_IMU_READ_GYRO         (0x01)
#define CURIE_IMU_READ_TEMP         (0x02)
#define CURIE_IMU_SHOCK_DETECT      (0x03)
#define CURIE_IMU_STEP_COUNTER      (0x04)
#define CURIE_IMU_TAP_DETECT        (0x05)
#define CURIE_IMU_READ_MOTION       (0x06)

class FirmataCurieIMU :public FirmataFeature
{
public:
    FirmataCurieIMU();

    // FirmataFeature interface functions. Required for any Firmata plugin.
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();

    // FirmataCurieIMU interface functions
    void readAccelerometer();
    void readGyro();
    void readTemperature();
    void readMotion();

    void enableShockDetection(boolean enable);
    static void shockDetected();

    void enableStepCounter(boolean enable);
    void stepDetected();

    void enableTapDetection(boolean enable);
    void tapDetected();

    void eventCallback(void);
};

#endif
