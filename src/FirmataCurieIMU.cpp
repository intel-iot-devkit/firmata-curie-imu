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
  }
  return false;
}

void FirmataCurieIMU::reset()
{
  // initialize device
  CurieIMU.begin();

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
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
}
