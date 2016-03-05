
#include <ConfigurableFirmata.h>
#include <FirmataExt.h>
#include <FirmataReporting.h>

#include <CurieIMU.h>
#include <FirmataCurieIMU.h>

FirmataExt firmataExt;
FirmataReporting reporting;
FirmataCurieIMU curieIMU;

void systemResetCallback()
{
  firmataExt.reset();
}

void setup()
{
  // TODO - pass the version of this firmware rather than the Firmata protocol
  // version. Making that change now however may break compatibility.
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);

  firmataExt.addFeature(reporting);
  firmataExt.addFeature(curieIMU);
  
  /* systemResetCallback is declared here (in ConfigurableFirmata.ino) */
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

