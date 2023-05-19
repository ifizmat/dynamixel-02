#ifndef DYNAMIXELMOTORXL430_H
#define DYNAMIXELMOTORXL430_H

#include <DynamixelDevice.h>

enum DynXL430Adddress {
  XL430_ADDRESS_ENABLE_TORQUE  = 64,
  XL430_ADDRESS_LED            = 65,
};


class DynamixelMotorXL430 : public DynamixelDevice {
  public:
    DynamixelMotorXL430(DynamixelID aId);
    void led(uint8_t aState);
    bool torqueStatus();
    void torqueEnable(bool aTorque);
    uint8_t id;
};

#endif
