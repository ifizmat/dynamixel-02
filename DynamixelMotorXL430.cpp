#include "DynamixelMotorXL430.h"

DynamixelMotorXL430::DynamixelMotorXL430(DynamixelID aId) : 
DynamixelDevice(aId)
{  id = aId; }

void DynamixelMotorXL430::led(uint8_t aState) {
  write(XL430_ADDRESS_LED, aState);
}

bool DynamixelMotorXL430::torqueStatus() {
  uint8_t status;
  uint8_t *data = new uint8_t[1];
  status = DxlMaster.read(id, XL430_ADDRESS_ENABLE_TORQUE, 1, data);
  return ((bool)data[0]?true:false);
}

void DynamixelMotorXL430::torqueEnable(bool aTorque) {
	write(XL430_ADDRESS_ENABLE_TORQUE, uint8_t(aTorque?1:0));
}
