/*
FirmataCurieIMU.cpp
*/

#include <ConfigurableFirmata.h>
#include "FirmataCurieIMU.h"

static boolean detectShocks = false;
static boolean countSteps = false;
static boolean detectTaps = false;

static FirmataCurieIMU* current;
static void callback(void)
{
    current->eventCallback();
}

FirmataCurieIMU::FirmataCurieIMU()
{
}

// FirmataFeature interface functions. Required for any Firmata plugin.

boolean FirmataCurieIMU::handlePinMode(byte pin, int mode)
{
    return false;
}

void FirmataCurieIMU::handleCapability(byte pin)
{
}

boolean FirmataCurieIMU::handleSysex(byte command, byte argc, byte *argv)
{
    if (command == CURIE_IMU)
    {
        byte imuCommand;
        imuCommand = argv[0];

        if (imuCommand == CURIE_IMU_READ_ACCEL)
        {
            readAccelerometer();
            return true;
        }

        if (imuCommand == CURIE_IMU_READ_GYRO)
        {
            readGyro();
            return true;
        }
        if (imuCommand == CURIE_IMU_READ_TEMP)
        {
            readTemperature();
            return true;
        }
        if (imuCommand == CURIE_IMU_SHOCK_DETECT)
        {
            boolean enable = (boolean)argv[1];
            enableShockDetection(enable);
            return true;
        }
        if (imuCommand == CURIE_IMU_STEP_COUNTER)
        {
            boolean enable = (boolean)argv[1];
            enableStepCounter(enable);
            return true;
        }
        if (imuCommand == CURIE_IMU_TAP_DETECT)
        {
            boolean enable = (boolean)argv[1];
            enableTapDetection(enable);
            return true;
        }
        if (imuCommand == CURIE_IMU_READ_MOTION)
        {
            readMotion();
            return true;
        }
    }
    return false;
}

 void FirmataCurieIMU::reset()
{
    // initialize device
    CurieIMU.begin();

    // Set the accelerometer range to 2G
    CurieIMU.setAccelerometerRange(2);

    // set the gyro range 2000 (+/-2000)
    CurieIMU.setGyroRange(2000);

    //set step detection
    CurieIMU.setStepDetectionMode(CURIE_IMU_STEP_MODE_NORMAL);

    current = this;
    CurieIMU.attachInterrupt(callback);
}

// FirmataCurieIMU interface functions

void FirmataCurieIMU::readAccelerometer()
{
    int xAxis, yAxis, zAxis;

    CurieIMU.readAccelerometer(xAxis, yAxis, zAxis);

    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_READ_ACCEL);
    Firmata.write((byte)xAxis & 0x7F);
    Firmata.write((byte)(xAxis >> 7) & 0x7F);
    Firmata.write((byte)yAxis & 0x7F);
    Firmata.write((byte)(yAxis >> 7) & 0x7F);
    Firmata.write((byte)zAxis & 0x7F);
    Firmata.write((byte)(zAxis >> 7) & 0x7F);
    Firmata.write(END_SYSEX);
}

void FirmataCurieIMU::readGyro()
{
    int xAxis, yAxis, zAxis;

    CurieIMU.readGyro(xAxis, yAxis, zAxis);

    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_READ_GYRO);
    Firmata.write((byte)xAxis & 0x7F);
    Firmata.write((byte)(xAxis >> 7) & 0x7F);
    Firmata.write((byte)yAxis & 0x7F);
    Firmata.write((byte)(yAxis >> 7) & 0x7F);
    Firmata.write((byte)zAxis & 0x7F);
    Firmata.write((byte)(zAxis >> 7) & 0x7F);
    Firmata.write(END_SYSEX);
}

void FirmataCurieIMU::readTemperature()
{
    int temp = CurieIMU.readTemperature();
    byte* b = (byte*) &temp;

    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_READ_TEMP);
    Firmata.write((byte)b[0] & 0x7F);
    Firmata.write((byte)(b[0] >> 7) & 0x7F);
    Firmata.write((byte)b[1] & 0x7F);
    Firmata.write((byte)(b[1] >> 7) & 0x7F);
    Firmata.write(END_SYSEX);
}

void FirmataCurieIMU::enableShockDetection(boolean enable)
{
    if (enable) {
      CurieIMU.interrupts(CURIE_IMU_SHOCK);
    } else {
      CurieIMU.noInterrupts(CURIE_IMU_SHOCK);
    }

    detectShocks = enable;
}

void FirmataCurieIMU::shockDetected()
{
    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_SHOCK_DETECT);

    if (CurieIMU.shockDetected(X_AXIS, POSITIVE)) {
      Firmata.write(X_AXIS);
      Firmata.write(POSITIVE);
    }

    if (CurieIMU.shockDetected(X_AXIS, NEGATIVE)) {
      Firmata.write(X_AXIS);
      Firmata.write(NEGATIVE);
    }

    if (CurieIMU.shockDetected(Y_AXIS, POSITIVE)) {
      Firmata.write(Y_AXIS);
      Firmata.write(POSITIVE);
    }

    if (CurieIMU.shockDetected(Y_AXIS, NEGATIVE)) {
      Firmata.write(Y_AXIS);
      Firmata.write(NEGATIVE);
    }

    if (CurieIMU.shockDetected(Z_AXIS, POSITIVE)) {
      Firmata.write(Z_AXIS);
      Firmata.write(POSITIVE);
    }

    if (CurieIMU.shockDetected(Z_AXIS, NEGATIVE)) {
      Firmata.write(Z_AXIS);
      Firmata.write(NEGATIVE);
    }

    Firmata.write(END_SYSEX);
}

void FirmataCurieIMU::enableStepCounter(boolean enable)
{
    if (enable) {
        CurieIMU.setStepCountEnabled(true);
        CurieIMU.interrupts(CURIE_IMU_STEP);
    } else {
        CurieIMU.setStepCountEnabled(false);
        CurieIMU.noInterrupts(CURIE_IMU_STEP);
    }
    countSteps = enable;
}

void FirmataCurieIMU::stepDetected()
{
    int stepCount = CurieIMU.getStepCount();
    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_STEP_COUNTER);
    Firmata.write((byte)stepCount & 0x7F);
    Firmata.write((byte)(stepCount >> 7) & 0x7F);
    Firmata.write(END_SYSEX);
}

void FirmataCurieIMU::enableTapDetection(boolean enable)
{
  detectTaps = enable;
}

void FirmataCurieIMU::tapDetected()
{
  // TODO: implement
}

void FirmataCurieIMU::readMotion()
{
    int ax, ay, az, gx, gy, gz;

    CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_READ_MOTION);
    Firmata.write((byte)gx & 0x7F);
    Firmata.write((byte)(gx >> 7) & 0x7F);
    Firmata.write((byte)gy & 0x7F);
    Firmata.write((byte)(gy >> 7) & 0x7F);
    Firmata.write((byte)gz & 0x7F);
    Firmata.write((byte)(gz >> 7) & 0x7F);

    Firmata.write((byte)ax & 0x7F);
    Firmata.write((byte)(ax >> 7) & 0x7F);
    Firmata.write((byte)ay & 0x7F);
    Firmata.write((byte)(ay >> 7) & 0x7F);
    Firmata.write((byte)az & 0x7F);
    Firmata.write((byte)(az >> 7) & 0x7F);
    Firmata.write(END_SYSEX);
}

void FirmataCurieIMU::eventCallback()
{
    if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK) && detectShocks) {
        shockDetected();
    }
    if (CurieIMU.getInterruptStatus(CURIE_IMU_STEP) && countSteps) {
        stepDetected();
    }
}
