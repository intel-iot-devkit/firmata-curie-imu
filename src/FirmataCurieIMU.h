/*
  FirmataCurieIMU.h
*/

#ifndef FirmataCurieIMU_h
#define FirmataCurieIMU_h

#include <ConfigurableFirmata.h>
#include <FirmataFeature.h>
#include <CurieIMU.h>

#define CURIE_IMU                   (0x11)

#define CURIE_IMU_READ_ACCEL        (0x00)
#define CURIE_IMU_READ_GYRO         (0x01)

class FirmataCurieIMU:public FirmataFeature
{
public:
  FirmataCurieIMU();

  // FirmataFeature interface functions. Required for any Firmata plugin.
  boolean handlePinMode(byte pin, int mode);
  void handleCapability(byte pin);
  boolean handleSysex(byte command, byte argc, byte *argv);
  void reset();

  // FirmataCurieIMU interface functions
  void readAccelerometer();
  void readGyro();
};

#endif
