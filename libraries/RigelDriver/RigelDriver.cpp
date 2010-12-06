/*
	RigelDriver.cpp
	
	This is a library for manouvering a Budget Robotics Rigel robot car. The
	constants are set for the servo configuration where the wheels are set as far
	apart as possible. The Adruino digital pins are also defined in the constants
	header file.
	
	Budget Robotics Rigel product page:
	http://www.budgetrobotics.com/shop/?cat=116
	
	Author:  Janne Oksanen
	Email:   janne.oksanen@gmail.com
	Published under GPLv2.

	Known bugs: None. If you find any please let me know.
	
	Change history:
*/

#include "WProgram.h"
#include "RigelDriver.h"


RigelDriver::RigelDriver(){	
  LeftFront.attach(SERVO_PIN_LEFT_FRONT);
  RightFront.attach(SERVO_PIN_RIGHT_FRONT);
  LeftBack.attach(SERVO_PIN_LEFT_BACK);
  RightBack.attach(SERVO_PIN_RIGHT_BACK);
}

void RigelDriver::driveForward(int n){
  for (i = 0; i < n; i++){
    LeftFront.write(FULL_SPEED_FORWARD_LEFT_FRONT);
    RightFront.write(FULL_SPEED_FORWARD_RIGHT_FRONT);
    LeftBack.write(FULL_SPEED_FORWARD_LEFT_BACK);  
    RightBack.write(FULL_SPEED_FORWARD_RIGHT_BACK);
    delay(SERVO_CATCH_UP_DELAY);
    SoftwareServo::refresh();
  }
}

void RigelDriver::driveBackwards(int n){
  for (i = 0; i < n; i++){
    LeftFront.write(FULL_SPEED_BACKWARDS_LEFT_FRONT);
    RightFront.write(FULL_SPEED_BACKWARDS_RIGHT_FRONT);
    LeftBack.write(FULL_SPEED_BACKWARDS_LEFT_BACK);  
    RightBack.write(FULL_SPEED_BACKWARDS_RIGHT_BACK);
    delay(SERVO_CATCH_UP_DELAY);
    SoftwareServo::refresh();
  }
}

void RigelDriver::spinLeft(int n){
  for (i = 0; i < n; i++){
    LeftFront.write(FULL_SPEED_BACKWARDS_LEFT_FRONT);
    RightFront.write(FULL_SPEED_FORWARD_RIGHT_FRONT);
    LeftBack.write(FULL_SPEED_BACKWARDS_LEFT_BACK);  
    RightBack.write(FULL_SPEED_FORWARD_RIGHT_BACK);
    delay(SERVO_CATCH_UP_DELAY);
    SoftwareServo::refresh();
  }
}

void RigelDriver::spinRight(int n){
  for (i = 0; i < n; i++){
    LeftFront.write(FULL_SPEED_FORWARD_LEFT_FRONT);
    RightFront.write(FULL_SPEED_BACKWARDS_RIGHT_FRONT);
    LeftBack.write(FULL_SPEED_FORWARD_LEFT_BACK);  
    RightBack.write(FULL_SPEED_BACKWARDS_RIGHT_BACK);
    delay(SERVO_CATCH_UP_DELAY);
    SoftwareServo::refresh();
  }
}

void RigelDriver::steerLeft(int n){
  for (i = 0; i < n; i++){
    LeftFront.write(HALF_SPEED_FORWARD_LEFT_FRONT);
    RightFront.write(FULL_SPEED_FORWARD_RIGHT_FRONT);
    LeftBack.write(HALF_SPEED_FORWARD_LEFT_BACK);  
    RightBack.write(FULL_SPEED_FORWARD_RIGHT_BACK);
    delay(SERVO_CATCH_UP_DELAY);
    SoftwareServo::refresh();
  }
}

void RigelDriver::steerRight(int n){
  for (i = 0; i < n; i++){
    LeftFront.write(FULL_SPEED_FORWARD_LEFT_FRONT);
    RightFront.write(HALF_SPEED_FORWARD_RIGHT_FRONT);
    LeftBack.write(FULL_SPEED_FORWARD_LEFT_BACK);  
    RightBack.write(HALF_SPEED_FORWARD_RIGHT_BACK);
    delay(SERVO_CATCH_UP_DELAY);
    SoftwareServo::refresh();
  }
}

