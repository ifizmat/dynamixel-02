#include "DynamixelMotorXL430.h"

DynamixelMotorXL430::DynamixelMotorXL430(DynamixelID aId) : 
DynamixelDevice(aId)
{}

void DynamixelMotorXL430::led(uint8_t aState) {
  write(XL430_ADDRESS_LED, aState);
}

bool DynamixelMotorXL430::torqueStatus() {
  uint8_t status;
  read(XL430_ADDRESS_ENABLE_TORQUE, status);
  return (status?true:false);
}

void DynamixelMotorXL430::torqueEnable(bool aTorque) {
	write(XL430_ADDRESS_ENABLE_TORQUE, uint8_t(aTorque?1:0));
}
