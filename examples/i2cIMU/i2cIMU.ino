/*
  Firmata with CurieIMU + i2c
*/

#include <ConfigurableFirmata.h>
#include <FirmataExt.h>
FirmataExt firmataExt;

#include <CurieIMU.h>
#include <FirmataCurieIMU.h>
FirmataCurieIMU curieIMU;

#include <I2CFirmata.h>
I2CFirmata i2c;

#include <FirmataReporting.h>
FirmataReporting reporting;

void systemResetCallback()
{
  firmataExt.reset();
}

void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);

  firmataExt.addFeature(curieIMU);
  firmataExt.addFeature(i2c);

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

  if (reporting.elapsed()) {
    i2c.report();
  }
}
