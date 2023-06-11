#include <DxlMaster.h>
#include <Dynamixel.h>
#include <DynamixelConsole.h>
#include <DynamixelDevice.h>
#include <DynamixelInterface.h>
#include <DynamixelInterfaceArduinoImpl.h>
#include <DynamixelMotor.h>

#include "DynamixelMotorXL430.h"

#define DYN_BAUDRATE 57600
#define SERIAL_BAUDRATE 9600
#define ID_MOTOR_FORWARD_LEFT  1
#define ID_MOTOR_FORWARD_RIGHT 2
#define NUMBER_WHEELS 2

DynamixelMotorXL430 xl430ForwardLeft(ID_MOTOR_FORWARD_LEFT);
DynamixelMotorXL430 xl430ForwardRight(ID_MOTOR_FORWARD_RIGHT);
uint8_t idWheels[NUMBER_WHEELS] = {
                                    ID_MOTOR_FORWARD_LEFT,
                                    ID_MOTOR_FORWARD_RIGHT
                                  };

uint8_t status = 0;
int32_t pos = 0;
int32_t velocity = 64;

void setup() {
  DxlMaster.begin(DYN_BAUDRATE);
  Serial.begin(SERIAL_BAUDRATE);

  status = xl430ForwardLeft.init();
  Serial.println(String("Forward Left Motor XL430 init: ") + status);
  
  status = xl430ForwardRight.init();
  Serial.println(String("Forward Right Motor XL430 init: ") + status);
  
  xl430ForwardLeft.torqueOff();
  delay(100);
  xl430ForwardLeft.jointMode();
  delay(100);
  xl430ForwardLeft.torqueOn();
  delay(100);
  xl430ForwardLeft.profileVelocity(velocity);
  delay(100);

  xl430ForwardRight.torqueOff();
  delay(100);
  xl430ForwardRight.jointMode();
  delay(100);
  xl430ForwardRight.torqueOn();
  delay(100);
  xl430ForwardRight.profileVelocity(velocity);
  delay(100);


  pos = 2048;
  xl430ForwardLeft.syncGoalPosition(pos);
  delay(100);
  xl430ForwardRight.syncGoalPosition(pos);
  delay(100);

  DxlMaster.action(idWheels);
//  DxlMaster.action(BROADCAST_ID);
//  DxlMaster.action(ID_MOTOR_FORWARD_LEFT);
//  DxlMaster.action(ID_MOTOR_FORWARD_RIGHT);
//  delay(5000);
  delay(100);
  while (xl430ForwardLeft.isMoving()) {
	  ;
  }

  pos = 0;
  xl430ForwardLeft.syncGoalPosition(pos);
  delay(100);
  xl430ForwardRight.syncGoalPosition(pos);
  delay(100);

  DxlMaster.action(idWheels);
//  DxlMaster.action(BROADCAST_ID);
//  DxlMaster.action(ID_MOTOR_FORWARD_LEFT);
//  DxlMaster.action(ID_MOTOR_FORWARD_RIGHT);
//  delay(5000);
  delay(100);
  while (xl430ForwardLeft.isMoving()) {
	  ;
  }


}

void loop() {
  Serial.println("Test loop...");
  xl430ForwardLeft.ledOn();
  delay(100);
  xl430ForwardRight.ledOn();
  delay(1300);
  xl430ForwardLeft.ledOff();
  delay(100);
  xl430ForwardRight.ledOff();
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
/*
void xl430_test3() {
//  xl430_test1();
  xl430.torqueOff();
  delay(100);
  xl430.jointMode();
//  while (!xl430.ping()) {;}
  delay(100);
  xl430.torqueOn();
  delay(100);
  velocity = 32;
  Serial.println(String("Set velocity: ") + velocity);
  xl430.profileVelocity(32);
  delay(100);
  pos = 4095;
  Serial.println(String("Set position: ") + pos);
  xl430.goalPosition(pos);
  delay(3000);
  while(xl430.isMoving())
  {delay(1);}
  pos = 0;
  Serial.println(String("Set position: ") + pos);
  xl430.goalPosition(pos);
  delay(100);
  while(xl430.isMoving())
  {
    delay(200);
	Serial.println("Test while isMoving...");
  }
  
	
	
}

void xl430_test2() {
  // pass	
	
}

void xl430_test1() {
  Serial.println(String("Is Moving: ") + xl430.isMoving());
  Serial.println(String("Motor XL430 torque: ") + xl430.isTorqueOn());
  xl430.torqueOn();
  delay(100);
  Serial.println(String("Motor XL430 torque: ") + xl430.isTorqueOn());
  xl430.torqueOff();
  delay(100);
  Serial.println(String("Motor XL430 torque: ") + xl430.isTorqueOn());
  //xl430.operatingMode(4);
  delay(100);
  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());
  xl430.jointMode();
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
  Serial.println(String("Motor XL430 torque: ") + xl430.isTorqueOn());

  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());
  xl430.wheelMode();
  delay(100);
  Serial.println(String("Motor XL430 Operating Mode: ") + xl430.operatingModeStatus());

  xl430.torqueOn();
  delay(100);
  Serial.println(String("Motor XL430 torque: ") + xl430.isTorqueOn());

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


  uint32_t velocity = 256;
  status = xl430.regWrite(XL430_ADDRESS_GOAL_VELOCITY, velocity);
  //status = xl430.regWrite(XL430_ADDRESS_GOAL_VELOCITY, (uint32_t)128);
  delay(100);
  Serial.println(String("regWrite velocity 128 status: ") + status);
  Serial.println("Delay 5000 ms...");
  delay(5000);
  Serial.println("Action! Velocity = 128");
  xl430.action();
  delay(6000);
  
  status = xl430.regWrite(XL430_ADDRESS_GOAL_VELOCITY, (uint32_t)0);
  delay(100);
  Serial.println(String("regWrite velocity 0 status: ") + status);
  Serial.println("Delay 5000 ms...");
  delay(5000);
  Serial.println("Action! Velocity = 0");
  xl430.action();
  delay(100);
}
*/