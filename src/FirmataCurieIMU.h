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
#define CURIE_IMU_READ_TEMP         (0x02)
#define CURIE_IMU_SHOCK_DETECT      (0x03)
#define CURIE_IMU_STEP_COUNTER      (0x04)
#define CURIE_IMU_TAP_DETECT        (0x05)
#define CURIE_IMU_READ_MOTION       (0x06)

class FirmataCurieIMU :public FirmataFeature
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
    void readTemperature();
    void enableShockDetection();
    void shockDetected();
    void enableStepCounter();
    void stepDetected();
    void enableTapDetection();
    void tapDetected();
    void readMotion();
};

#endif
