/*
  FirmataCurieIMU.cpp
*/

#include <ConfigurableFirmata.h>
#include "FirmataCurieIMU.h"

FirmataCurieIMU::FirmataCurieIMU()
{
}

boolean FirmataCurieIMU::handlePinMode(byte pin, int mode)
{
  return false;
}

void FirmataCurieIMU::handleCapability(byte pin)
{
}

boolean FirmataCurieIMU::handleSysex(byte command, byte argc, byte *argv)
{
  return false;
}

void FirmataCurieIMU::reset()
{
}

void FirmataCurieIMU::report()
{
}
