
#include <ConfigurableFirmata.h>
#include <FirmataExt.h>
#include <FirmataReporting.h>
#include <DigitalOutputFirmata.h>

#include <CurieIMU.h>
#include <FirmataCurieIMU.h>

FirmataExt firmataExt;
FirmataReporting reporting;
FirmataCurieIMU curieIMU;
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
  systemResetCallback();  // reset to default config
}

void loop()
{
  while (Firmata.available()) {
    Firmata.processInput();
  }

  if (reporting.elapsed()) {
    curieIMU.readAccelerometer();
  }
}
