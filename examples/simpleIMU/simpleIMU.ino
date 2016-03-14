/*
  Simple Firmata with CurieIMU + digital output
*/

#include <ConfigurableFirmata.h>
#include <FirmataExt.h>
FirmataExt firmataExt;

#include <FirmataReporting.h>
FirmataReporting reporting;

#include <CurieIMU.h>
#include <FirmataCurieIMU.h>
FirmataCurieIMU curieIMU;

#include <DigitalOutputFirmata.h>
DigitalOutputFirmata digitalOutput;

void systemResetCallback()
{
  firmataExt.reset();
}

void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);

  firmataExt.addFeature(reporting);
  firmataExt.addFeature(curieIMU);
  firmataExt.addFeature(digitalOutput);

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
    curieIMU.report();
  }
}
