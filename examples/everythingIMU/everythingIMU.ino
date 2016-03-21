#define MAX_SERVOS  12

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

#include <DigitalInputFirmata.h>
DigitalInputFirmata digitalInput;

#include <DigitalOutputFirmata.h>
DigitalOutputFirmata digitalOutput;

#include <AnalogInputFirmata.h>
AnalogInputFirmata analogInput;

#include <AnalogOutputFirmata.h>
AnalogOutputFirmata analogOutput;

#include <AnalogWrite.h>

#include <Servo.h>
#include <ServoFirmata.h>
ServoFirmata myServo;


void systemResetCallback()
{
  // reset digital/analog output pins
  for (byte i = 0; i < TOTAL_PINS; i++) {
    if (IS_PIN_ANALOG(i)) {
        Firmata.setPinMode(i, PIN_MODE_ANALOG);
    } else if (IS_PIN_DIGITAL(i)) {
        Firmata.setPinMode(i, OUTPUT);
    }
  }
  firmataExt.reset();
}

void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);

  firmataExt.addFeature(curieIMU);
  firmataExt.addFeature(i2c);

  firmataExt.addFeature(digitalOutput);
  firmataExt.addFeature(digitalInput);

  firmataExt.addFeature(analogInput);
  firmataExt.addFeature(analogOutput);

  firmataExt.addFeature(myServo);

  Firmata.attach(SYSTEM_RESET, systemResetCallback);
  Firmata.begin(57600);

  // set reset to default config
  systemResetCallback();
}

void loop()
{
  digitalInput.report();

  while (Firmata.available()) {
    Firmata.processInput();
  }

  if (reporting.elapsed()) {
    i2c.report();
    analogInput.report();
  }
}
