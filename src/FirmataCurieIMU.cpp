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
}

// FirmataCurieIMU interface functions

void FirmataCurieIMU::readAccelerometer()
{
}

void FirmataCurieIMU::readGyro()
{
}
