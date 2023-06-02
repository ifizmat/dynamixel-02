#include <DxlMaster.h>
#include <Dynamixel.h>
#include <DynamixelConsole.h>
#include <DynamixelDevice.h>
#include <DynamixelInterface.h>
#include <DynamixelInterfaceArduinoImpl.h>
#include <DynamixelMotor.h>

#include "DynamixelMotorXL430.h"

#define ID_ADDRESS 7
#define BAUDRATE_ADDRESS 8
#define ID_MOTOR 1


DynamixelMotorXL430 xl430(ID_MOTOR);
uint8_t status = 0;
uint8_t idReaded = 0;
uint8_t baudrateReaded = 0;

void setup() {
  DxlMaster.begin(57600);
  Serial.begin(9600);

  status = xl430.init();
  Serial.println(String("Motor XL430 init: ") + status);

  xl430_test1();

}

void loop() {

  xl430.ledOn();
  delay(1300);
  xl430.ledOff();
  delay(1300);
  
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

void xl430_test1() {
  Serial.println(String("Is Moving: ") + xl430.isMoving());
  Serial.println(String("Motor XL430 torque: ") + xl430.torqueStatus());
  xl430.torqueOn();
  delay(100);
  Serial.println(String("Motor XL430 torque: ") + xl430.torqueStatus());
  xl430.torqueOff();
  delay(100);
  Serial.println(String("Motor XL430 torque: ") + xl430.torqueStatus());
  xl430.operatingMode(4);
  delay(100);
  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());
  xl430.operatingMode(XL430_POSITION_CONTROL_MODE);
  delay(100);
  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());
  xl430.profileVelocity(32);
  delay(100);
  printData(ID_MOTOR, XL430_ADDRESS_PROFILE_VELOCITY, "Velocity", 4);  
  xl430.profileVelocity(64);
  delay(100);
  printData(ID_MOTOR, XL430_ADDRESS_PROFILE_VELOCITY, "Velocity", 4);

  Serial.println(String("Is Moving: ") + xl430.isMoving());
  xl430.torqueOn();
  delay(100);
  xl430.goalPosition(1024);
  delay(100);
  Serial.println(String("Is Moving: ") + xl430.isMoving());
  uint32_t t1 = millis();
  while (millis() - t1 < 5000) {
    Serial.println(String("Is Moving: ") + xl430.isMoving());
  } 
  //delay(5000);    
  xl430.goalPosition(0);
  delay(100);
  Serial.println(String("Is Moving: ") + xl430.isMoving());
  delay(5000);

  xl430.torqueOff();
  delay(100);
  Serial.println(String("Motor XL430 torque: ") + xl430.torqueStatus());

  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());
  xl430.operatingMode(XL430_VELOCITY_CONTROL_MODE);
  delay(100);
  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());

  xl430.torqueOn();
  delay(100);
  Serial.println(String("Motor XL430 torque: ") + xl430.torqueStatus());

  xl430.goalVelocity(32);
  delay(100);
  printData(ID_MOTOR, XL430_ADDRESS_GOAL_VELOCITY, "Goal Velocity", 4);  
  delay(5000);  

  xl430.goalVelocity(64);
  delay(100);
  printData(ID_MOTOR, XL430_ADDRESS_GOAL_VELOCITY, "Goal Velocity", 4);  
  delay(5000);  

  xl430.goalVelocity(0);
  delay(100);
  printData(ID_MOTOR, XL430_ADDRESS_GOAL_VELOCITY, "Goal Velocity", 4);  
  delay(1000);  
  xl430.regWrite(XL430_ADDRESS_GOAL_VELOCITY, (uint32_t)128);
  delay(100);
  xl430.action();
}