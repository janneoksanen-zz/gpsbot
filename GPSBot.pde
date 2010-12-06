#include <HM55B.h>
#include <compass_pin_conf.h>
#include <GPSRoute.h>
#include <Waypoint.h>
#include <GarminParser.h>
#include <GPSNavigator.h>
#include <SoftwareServo.h>
#include <RigelDriver.h>
#include <GPSBotConstants.h>
#include <RigelDriverConstants.h>
#include <math.h>

//// VARS
float heading;
float bearing;
float misdirection;
RigelDriver car;
Waypoint location;
GPSNavigator navi;
GarminParser gps;
GPSRoute r;
HM55B compass;
char updateOK;
char buffer[56];
char incoming;
char i = 1;
char readOK = 0;

Waypoint wp1 WAYPOINT_1;
Waypoint wp2 WAYPOINT_6;

int readSerial(){
  i = 1;
  while (!Serial.available()){
    delay(10);  
  }
  while (Serial.read() != '@'){
    // Read until start of message
  }
  buffer[0] = '@';
  // If we found @ then we just pile the whole thing in
  // the buffer
  while( i < 55){
  // If the serial buffer is empty we wait for a bit
    if (!Serial.available()){
      delay(10);
    } else {
      incoming = Serial.read();
      buffer[i] = incoming;
      i++;
    }
  }
  buffer[55] = 0;
  Serial.flush();
  return 0;
}

int updateLocation(){
  readSerial();
  gps.parseString(buffer);
  location.setLatitude(gps.getLatitude());
  location.setLongitude(gps.getLongitude());
  location.setNSHemisphere(gps.getLatHem());
  location.setEWHemisphere(gps.getLongHem());
  navi.setLocation(&location);    
  return 0;
}


// Calculates how much off course we are. 
// If misdirection is positive you need to turn left.
// Returns float [-PI, PI] (angle in radians)
float calculateMisdirection(){

  if (heading > 0 && bearing > (heading - M_PI)){
    misdirection = bearing - heading;
    
  } else  if (heading > 0 && bearing < (heading - M_PI)){
    misdirection = (2* M_PI) + bearing - heading;
    
  } else  if (heading <= 0 && bearing > (heading + M_PI)){
    misdirection = (-2* M_PI) + bearing - heading;
    
  } else  if (heading <= 0 && bearing < (heading + M_PI)){
    misdirection = bearing - heading;
  }

  return misdirection;
}

void setup() {
  Serial.begin(BAUD_RATE);
  r.addNode(&wp2);  
  r.addNode(&wp1);
  navi.setRoute(&r);
  pinMode(13, OUTPUT);
}

void loop() {
  updateOK = updateLocation();
  if (updateOK == 0){
    // Are we there yet?
    if (navi.getDistance() < WAYPOINT_DISTANCE_LIMIT && gps.getError() < GPS_ERROR_LIMIT){
      navi.nextWaypoint();
    }
    heading = compass.getHeading();
    bearing = navi.getBearing();
    misdirection = calculateMisdirection();
    if (abs(misdirection) < DIRECTION_ACCEPTABLE_TOLERANCE){
      car.driveForward(DRIVE_FORWARD_CYCLE);
    } 
    else if (misdirection < 0){
      if (misdirection < (-1* M_PI /3)){
        car.spinRight(DRIVE_STEERING_CYCLE);
      } else {
        car.steerRight(DRIVE_FORWARD_CYCLE);    
      }
    } 
    else {
     if (misdirection > (M_PI /3)){
        car.spinLeft(DRIVE_STEERING_CYCLE);
      } 
      else {
        car.steerLeft(DRIVE_FORWARD_CYCLE);
      }
    }
  } else {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000); 
  }
}

