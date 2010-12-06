/*
	HM55B.cpp
	
	Driver for Hitachi HM55B Compass Module
	
	I wrote this lib for my GPS navigating robot car project. It's heavily based
	on code by kiilo (kiilo@kiilo.org) that was published at the Arduino site. 
	Basically I just took his code and made an object out of it with very slight
	modifications to make it directly compatible with the navigation library I 
	wrote for the robot.
	
	Author:  Janne Oksanen
	Email:   janne.oksanen@gmail.com
	Published under GPLv2.
	
	Kiilo's original code at arduino.cc:
	http://www.arduino.cc/playground/Main/HM55B
*/

#include "HM55B.h"

HM55B::HM55B(){
	int x_data = 0;
	int y_Data = 0;
  pinMode(EN_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DIO_PIN, INPUT);
  reset();
}

void HM55B::shiftOut(int val, int bitCount) {
  for(int i = bitCount; i >= 0; i--) {
    digitalWrite(CLK_PIN, LOW);
    if ((val & 1 << i) == ( 1 << i)) {
      digitalWrite(DIO_PIN, HIGH);
    } else {
      digitalWrite(DIO_PIN, LOW);
    }
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(1);
  }
}

int HM55B::shiftIn(int bitCount) {
  int shiftInResult;
  shiftInResult = 0;
  pinMode(DIO_PIN, INPUT);
  for(int i = bitCount; i >= 0; i--) {
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(1);
    if (digitalRead(DIO_PIN) == HIGH) {
      shiftInResult = (shiftInResult << 1) + 1; 
    } else {
      shiftInResult = (shiftInResult << 1) + 0;
    }
    digitalWrite(CLK_PIN, LOW);
    delayMicroseconds(1);
    }
// below is difficult to understand:
// if bit 11 is Set the value is negative
// the representation of negative values you
// have to add B11111000 in the upper Byte of
// the integer.
// see: http://en.wikipedia.org/wiki/Two%27s_complement
  if ((shiftInResult & 1 << 11) == 1 << 11) {
    shiftInResult = (B11111000 << 8) | shiftInResult; 
  }
  return shiftInResult;
}

void HM55B::reset() {
  pinMode(DIO_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
  shiftOut(B0000, 3);
  digitalWrite(EN_PIN, HIGH);
}

void HM55B::startMeasurementCommand() {
  pinMode(DIO_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
  shiftOut(B1000, 3);
  digitalWrite(EN_PIN, HIGH);
}

int HM55B::readCommand() {
  int result = 0;
  pinMode(DIO_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
  shiftOut(B1100, 3);
  result = shiftIn(3);
  return result;
}

// Returns the heading [-PI;PI] with East being 0 and North -PI/2
float HM55B::getHeading(){
  startMeasurementCommand(); // necessary!!
  delay(40); // the data is 40ms later ready
  readCommand();
  x_data = shiftIn(11); // Field strength in X
  y_data = shiftIn(11); // and Y direction
  digitalWrite(EN_PIN, HIGH); // ok deselect chip
  heading = atan2(x_data, -1 * y_data);
	return heading;
}

float HM55B::getStableHeading(int sample_size){
	float sum = 0;
	int neg_count = 0;
	float heading = 0;
	for (int i = 0; i < sample_size; i++){
		heading = getHeading();
		if (heading < 0){ 
			neg_count++;
		}
		sum = sum + fabs(heading);
	}
	if (neg_count < (sample_size / 2)){
		return sum / sample_size;
	} else {
		return -1 * sum / sample_size;
	}
}
