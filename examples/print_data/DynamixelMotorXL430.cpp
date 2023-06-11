#include "DynamixelMotorXL430.h"

DynamixelMotorXL430::DynamixelMotorXL430(DynamixelID aId) : 
DynamixelDevice(aId)
{  id = aId; }

void DynamixelMotorXL430::led(uint8_t aState) {
  write(XL430_ADDRESS_LED, aState);
}

void DynamixelMotorXL430::ledOn() {
  led(1);
}

void DynamixelMotorXL430::ledOff() {
  led(0);
}

bool DynamixelMotorXL430::torqueStatus() {
  const uint8_t dataSize = 1;
  uint8_t status;
  uint8_t *data = new uint8_t[dataSize];
  status = DxlMaster.read(this->id, XL430_ADDRESS_ENABLE_TORQUE, dataSize, data);
  if (DYN_STATUS_OK != status) {
    return status;
  }
  return ((bool)data[0]?true:false);
}

bool DynamixelMotorXL430::isTorqueOn() {
  return torqueStatus();
}

void DynamixelMotorXL430::torqueEnable(bool aTorque, uint32_t timeout=100) {
  write(XL430_ADDRESS_ENABLE_TORQUE, uint8_t(aTorque?1:0));
  delay(100);
}

void DynamixelMotorXL430::torqueOn() {
  torqueEnable(true);
}

void DynamixelMotorXL430::torqueOff() {
  torqueEnable(false);
}

uint8_t DynamixelMotorXL430::operatingModeStatus() {
  const uint8_t dataSize = 1;
  uint8_t status;
  uint8_t *data = new uint8_t[dataSize];
  status = DxlMaster.read(this->id, XL430_ADDRESS_OPERATING_MODE, dataSize, data);
  if (DYN_STATUS_OK != status) {
    return status;
  }
  return ((uint8_t)data[0]);
}

void DynamixelMotorXL430::operatingMode(DynXL430OperatingMode aMode, uint32_t timeout=100) {
  write(XL430_ADDRESS_OPERATING_MODE, aMode);
  delay(100);
}

void DynamixelMotorXL430::jointMode() {
  bool isTorqueChanged = false;
  if (isTorqueOn()) {
    isTorqueChanged = true;
    torqueOff();
  }
  operatingMode(XL430_POSITION_CONTROL_MODE);
  if (isTorqueChanged) {
    torqueOn();
  }
}

void DynamixelMotorXL430::wheelMode() {
  bool isTorqueChanged = false;
  if (isTorqueOn()) {
    isTorqueChanged = true;
    torqueOff();
  }
  operatingMode(XL430_VELOCITY_CONTROL_MODE);
  if (isTorqueChanged) {
    torqueOn();
  }
}

void DynamixelMotorXL430::profileVelocity(uint32_t aVelocity) {
  write(XL430_ADDRESS_PROFILE_VELOCITY, aVelocity);  
}

void DynamixelMotorXL430::goalPosition(uint32_t aPosition) {
  write(XL430_ADDRESS_GOAL_POSITION, aPosition);  
}

void DynamixelMotorXL430::goalVelocity(uint32_t aVelocity) {
  write(XL430_ADDRESS_GOAL_VELOCITY, aVelocity);  
}

void DynamixelMotorXL430::syncGoalPosition(uint32_t aPosition) {
  regWrite(XL430_ADDRESS_GOAL_POSITION, aPosition);
}

void DynamixelMotorXL430::syncGoalVelocity(uint32_t aVelocity) {
  regWrite(XL430_ADDRESS_GOAL_VELOCITY, aVelocity);
}

bool DynamixelMotorXL430::isMoving() {
//uint8_t DynamixelMotorXL430::isMoving() {  
  const uint8_t dataSize = 1;
  uint8_t status;
  uint8_t *data = new uint8_t[dataSize];
  status = DxlMaster.read(this->id, XL430_ADDRESS_MOVING, dataSize, data);
  //if (DYN_STATUS_OK != status) {
  //  return status;
  //}
  //return ((bool)data[0]?true:false);
  return data[0];
}
