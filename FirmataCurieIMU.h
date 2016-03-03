/*
  FirmataCurieIMU.h
*/

#ifndef FirmataCurieIMU_h
#define FirmataCurieIMU_h

#include <ConfigurableFirmata.h>
#include <FirmataFeature.h>

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
  void report();
};

#endif
