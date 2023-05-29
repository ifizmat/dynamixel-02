#include "DynamixelMotorXL430.h"

DynamixelMotorXL430::DynamixelMotorXL430(DynamixelID aId) : 
DynamixelDevice(aId)
{  id = aId; }

void DynamixelMotorXL430::led(uint8_t aState) {
  write(XL430_ADDRESS_LED, aState);
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

void DynamixelMotorXL430::torqueEnable(bool aTorque) {
	write(XL430_ADDRESS_ENABLE_TORQUE, uint8_t(aTorque?1:0));
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

void DynamixelMotorXL430::operatingMode(DynXL430OperatingMode aMode) {
  write(XL430_ADDRESS_OPERATING_MODE, aMode);
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

//bool DynamixelMotorXL430::isMoving() {
uint8_t DynamixelMotorXL430::isMoving() {  
  const uint8_t dataSize = 1;
  uint8_t status;
  uint8_t *data = new uint8_t[dataSize];
  status = DxlMaster.read(this->id, XL430_ADDRESS_MOVING, dataSize, data);
  if (DYN_STATUS_OK != status) {
    return status;
  }
  //return ((bool)data[0]?true:false);
  return data[0];
}
