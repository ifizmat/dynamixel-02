/* Controller by Applied Robotics: AR-IoT-DXL
 * Servo by Robotis, South Korea: Dynamixel XL430-W250-T
 * https://emanual.robotis.com/docs/en/dxl/x/xl430-w250
 * https://www.robotis.us/dynamixel-xl430-w250-t
 * Lib: DxlMaster, Dynamixel Protocol 1.0
 * Software: 
 * https://appliedrobotics.ru/?page_id=633
 * Download DxlMaster_19.04.2019.zip
 * https://disk.yandex.ru/d/uftscsAynS-pEg
 */
 
#ifndef DYNAMIXELMOTORXL430_H
#define DYNAMIXELMOTORXL430_H

#include <DynamixelDevice.h>

enum DynXL430Adddress {
  XL430_ADDRESS_OPERATING_MODE   = 11,
  XL430_ADDRESS_ENABLE_TORQUE    = 64,
  XL430_ADDRESS_LED              = 65,
  XL430_ADDRESS_GOAL_VELOCITY    = 104,
  XL430_ADDRESS_PROFILE_VELOCITY = 112,
  XL430_ADDRESS_GOAL_POSITION    = 116,
  XL430_ADDRESS_MOVING           = 122,
};

enum DynXL430OperatingMode {
  XL430_VELOCITY_CONTROL_MODE = 1,
  XL430_POSITION_CONTROL_MODE = 3,
};

class DynamixelMotorXL430 : public DynamixelDevice {
  public:
    DynamixelMotorXL430(DynamixelID aId);
    bool isTorqueOn();
    void torqueOn();
    void torqueOff();
    void ledOn();
    void ledOff();
    uint8_t operatingModeStatus();
    void jointMode();
    void wheelMode();
    void profileVelocity(uint32_t aVelocity);
    void goalPosition(uint32_t aPosition);
    void goalVelocity(uint32_t aVelocity);
    void syncGoalPosition(uint32_t aPosition);
    void syncGoalVelocity(uint32_t aVelocity);
    bool isMoving();
    //uint8_t isMoving();
    uint8_t id;

  private: 
    void torqueEnable(bool aTorque, uint32_t timeout=100);
    void led(uint8_t aState);
    void operatingMode(DynXL430OperatingMode aMode, uint32_t timeout=100);
    bool torqueStatus();
};

#endif
