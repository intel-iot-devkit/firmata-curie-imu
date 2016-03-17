/*
  Simple Firmata with CurieIMU + 12c
*/

#include <ConfigurableFirmata.h>
#include <FirmataExt.h>
FirmataExt firmataExt;

#include <CurieIMU.h>
#include <FirmataCurieIMU.h>
FirmataCurieIMU curieIMU;

#include <I2CFirmata.h>
I2CFirmata myI2C;

void systemResetCallback()
{
  firmataExt.reset();
}

void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);

  firmataExt.addFeature(curieIMU);
  firmataExt.addFeature(myI2C);

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
