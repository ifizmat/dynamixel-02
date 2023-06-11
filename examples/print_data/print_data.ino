#include "DynamixelMotorXL430.h"

#define DYN_BAUDRATE 57600
#define SERIAL_BAUDRATE 9600

#define ID_MOTOR 1

DynamixelMotorXL430 xl430(ID_MOTOR);
uint8_t status = 0;

void setup() {
  DxlMaster.begin(DYN_BAUDRATE);
  Serial.begin(SERIAL_BAUDRATE);

  status = xl430.init();
  Serial.println(String("Motor XL430 init: ") + status);
  Serial.println(String("Motor XL430 torque: ") + xl430.isTorqueOn());
  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());
  
  xl430.jointMode();
  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());
  
  xl430.wheelMode();
  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());
  
  xl430.profileVelocity(32);
  delay(100);
  printData(ID_MOTOR, XL430_ADDRESS_PROFILE_VELOCITY, "Velocity", 4);  
  
  xl430.profileVelocity(64);
  delay(100);
  printData(ID_MOTOR, XL430_ADDRESS_PROFILE_VELOCITY, "Velocity", 4);
  
  xl430.goalVelocity((int32_t)32);
  delay(100);
  printData(ID_MOTOR, XL430_ADDRESS_GOAL_VELOCITY, "Goal Velocity", 4);  
  delay(100);
  

  xl430.torqueOn();
  Serial.println(String("Motor XL430 torque: ") + xl430.isTorqueOn());

  xl430.goalVelocity((int32_t)64);
  delay(100);
  printData(ID_MOTOR, XL430_ADDRESS_GOAL_VELOCITY, "Goal Velocity", 4);  
  delay(1000);  
}

void loop() {
  delay(50);
}

void printData(uint8_t idDevice, uint8_t address, String typeRegister, uint8_t length)
{
  uint8_t *data = new uint8_t[length];

  status = DxlMaster.read(idDevice, address, length, data);
  Serial.println(String("Status ") + typeRegister + ": " + status);
  for(uint8_t i=0; i<length; ++i)
  {
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.print("\n\r");
}
