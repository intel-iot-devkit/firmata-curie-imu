// change this to a unique name per board if running StandardFirmataBLE on multiple boards
// within the same physical space
#define FIRMATA_BLE_LOCAL_NAME "FIRMATA"

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

#ifdef _VARIANT_ARDUINO_101_X_
#include <CurieBLE.h>
#include "utility/BLEStream.h"
BLEStream stream;
#endif

#if defined(BLE_REQ) && defined(BLE_RDY) && defined(BLE_RST)
#define IS_IGNORE_BLE_PINS(p) ((p) == BLE_REQ || (p) == BLE_RDY || (p) == BLE_RST)
#endif

// min cannot be < 0x0006. Adjust max if necessary
#define FIRMATA_BLE_MIN_INTERVAL    0x0006 // 7.5ms (7.5 / 1.25)
#define FIRMATA_BLE_MAX_INTERVAL    0x0018 // 30ms (30 / 1.25)

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
  //Firmata.begin(57600);

  stream.setLocalName(FIRMATA_BLE_LOCAL_NAME);

  // set the BLE connection interval - this is the fastest interval you can read inputs
  stream.setConnectionInterval(FIRMATA_BLE_MIN_INTERVAL, FIRMATA_BLE_MAX_INTERVAL);
  // set how often the BLE TX buffer is flushed (if not full)
  stream.setFlushInterval(FIRMATA_BLE_MAX_INTERVAL);

  #ifdef BLE_REQ
    for (byte i = 0; i < TOTAL_PINS; i++) {
      if (IS_IGNORE_BLE_PINS(i)) {
        Firmata.setPinMode(i, PIN_MODE_IGNORE);
      }
    }
  #endif

  stream.begin();
  Firmata.begin(stream);

  // set reset to default config
  systemResetCallback();
}

void loop()
{
  // do not process data if no BLE connection is established
  // poll will send the TX buffer at the specified flush interval or when the buffer is full
  if (!stream.poll()) return;

  digitalInput.report();

  while (Firmata.available()) {
    Firmata.processInput();
  }

  if (reporting.elapsed()) {
    i2c.report();
    analogInput.report();
  }
}
