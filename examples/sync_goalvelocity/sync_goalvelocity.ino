#include "DynamixelMotorXL430.h"

#define DYN_BAUDRATE 57600
#define SERIAL_BAUDRATE 9600
#define ID_MOTOR_FORWARD_LEFT  1
#define ID_MOTOR_FORWARD_RIGHT 2
#define NUMBER_WHEELS 2

uint8_t idWheels[NUMBER_WHEELS] = {
                                    ID_MOTOR_FORWARD_LEFT,
                                    ID_MOTOR_FORWARD_RIGHT
                                  };

DynamixelMotorXL430 xl430ForwardLeft(ID_MOTOR_FORWARD_LEFT);
DynamixelMotorXL430 xl430ForwardRight(ID_MOTOR_FORWARD_RIGHT);

uint8_t status = 0;
int32_t velocity = 64;

void setup() {
  DxlMaster.begin(DYN_BAUDRATE);
  Serial.begin(SERIAL_BAUDRATE);
  
  status = xl430ForwardLeft.init();
  Serial.println(String("Forward Left Motor XL430 init: ") + status);
  
  status = xl430ForwardRight.init();
  Serial.println(String("Forward Right Motor XL430 init: ") + status);
  
  xl430ForwardLeft.torqueOn();
  delay(100);
  xl430ForwardLeft.wheelMode();
  delay(100);

  xl430ForwardRight.torqueOn();
  delay(100);
  xl430ForwardRight.wheelMode();
  delay(100);

  velocity = -32;
  Serial.println(String("velocity: ") + velocity);
  xl430ForwardLeft.syncGoalVelocity(velocity);
  delay(100);
  xl430ForwardRight.syncGoalVelocity(velocity);
  delay(100);
  DxlMaster.action(idWheels);
  delay(5000);

  velocity = 0;
  Serial.println(String("velocity: ") + velocity);
  xl430ForwardLeft.syncGoalVelocity(velocity);
  delay(100);
  xl430ForwardRight.syncGoalVelocity(velocity);
  delay(100);

  DxlMaster.action(idWheels);
  delay(1000);

  velocity = 32;
  Serial.println(String("velocity: ") + velocity);
  xl430ForwardLeft.syncGoalVelocity(velocity);
  delay(100);
  xl430ForwardRight.syncGoalVelocity(velocity);
  delay(100);
  DxlMaster.action(idWheels);
  delay(5000);

  velocity = 0;
  Serial.println(String("velocity: ") + velocity);
  xl430ForwardLeft.syncGoalVelocity(velocity);
  delay(100);
  xl430ForwardRight.syncGoalVelocity(velocity);
  delay(100);

  DxlMaster.action(idWheels);
  delay(1000);
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
