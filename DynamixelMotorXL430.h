#ifndef DYNAMIXELMOTORXL430_H
#define DYNAMIXELMOTORXL430_H

enum DynXL430Adddress {
  XL430_ADDRESS_LED =65,
};


class DynamixelMotorXL430 : public DynamixelDevice {
  public:
    DynamixelMotorXL430(DynamixelID aId);
    void led(uint8_t aState);
};

DynamixelMotorXL430::DynamixelMotorXL430(DynamixelID aId) : 
DynamixelDevice(aId)
{}

void DynamixelMotorXL430::led(uint8_t aState) {
  write(XL430_ADDRESS_LED, aState);
}

#endif