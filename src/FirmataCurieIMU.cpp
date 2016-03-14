/*
FirmataCurieIMU.cpp
*/

#include <ConfigurableFirmata.h>
#include "FirmataCurieIMU.h"

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
            readTemp();
            return true;
        }
        if (imuCommand == CURIE_IMU_SHOCK_DETECT)
        {
            shockDetected();
            return true;
        }
        if (imuCommand == CURIE_IMU_STEP_COUNTER)
        {
            enableStepCounter();
            return true;
        }
        if (imuCommand == CURIE_IMU_TAP_DETECT)
        {
            enableTapDetection();
            return true;
        }
        if (imuCommand == CURIE_IMU_READ_MOTION)
        {
            readMotion();
            return true;
        }
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

    // set the gyro range 2000 (+/-2000°/s)
    CurieIMU.setGyroRange(2000);

    //read temperature in celcius 
    CurieIMU.readTemp();

    //shock detected enabled
    CurieIMU.shockDetected();

    //step counter enabled
    CurieIMU.enableStepCounter();

    //tap detect enabled
    CurieIMU.enableTapDetection();

    //read motion 
    CurieIMU.readMotion();

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
void FirmataCurieIMU::readTemp()
{
    float Celcius;
    CurieIMU.readTemp(Celcius);

    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_READ_TEMP);
    Firmata.write((byte)Celcius & 0x7F);
    Firmata.write((byte)(Celcius >> 7) & 0x7F);
    Firmata.write(END_SYSEX);
}
void FirmataCurieIMU::shockDetected() 
{
    
    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_SHOCK_DETECT);
    Firmata.write(END_SYSEX);
}
void FirmataCurieIMU::enableStepCounter()
{
    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_STEP_COUNTER);
    Firmata.write(END_SYSEX);
}
void FirmataCurieIMU::enableTapDetection()
{
    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_TAP_DETECT);
    Firmata.write(END_SYSEX);
}
void FirmataCurieIMU::readMotion();
{

    int axAxis, ayAxis, azAxis, gxAxis, gyAxis, gzAxis;

    CurieIMU.readGyro(gxAxis, gyAxis, gzAxis);

    Firmata.write(START_SYSEX);
    Firmata.write(CURIE_IMU);
    Firmata.write(CURIE_IMU_READ_MOTION);
    Firmata.write((byte)gxAxis & 0x7F);
    Firmata.write((byte)(gxAxis >> 7) & 0x7F);
    Firmata.write((byte)gyAxis & 0x7F);
    Firmata.write((byte)(gyAxis >> 7) & 0x7F);
    Firmata.write((byte)gzAxis & 0x7F);
    Firmata.write((byte)(gzAxis >> 7) & 0x7F);

    Firmata.write((byte)axAxis & 0x7F);
    Firmata.write((byte)(axAxis >> 7) & 0x7F);
    Firmata.write((byte)ayAxis & 0x7F);
    Firmata.write((byte)(ayAxis >> 7) & 0x7F);
    Firmata.write((byte)azAxis & 0x7F);
    Firmata.write((byte)(azAxis >> 7) & 0x7F);
    Firmata.write(END_SYSEX);
}
