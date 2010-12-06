/*
 * File: GPSNavigator.cpp
 * 
 * Navigation component class for a GPS robot car project.
 * 
 * I wrote this lib for my GPS navigating robot car project. It was meant to be
 * used with my Waypoint and GarminParser classes and some of the design 
 * peculiarities are inherited from those classes. This class mainly calculates
 * distance and bearing to destination with the information provided.
 *
 * @author  Janne Oksanen janne.oksanen@gmail.com
 * @section LICENCE
 * Published under GPLv2.
 * @section KNOWN BUGS
 * None. If you find any please let me know.
 */


#include "GPSNavigator.h"

GPSNavigator::GPSNavigator(){	
}

void GPSNavigator::setLocation(Waypoint* loc){
  location = loc;
}

void GPSNavigator::setDestination(Waypoint* dest){
  destination = dest;
  linearizeDegrees();
}

void GPSNavigator::setRoute(GPSRoute* r){
  route = r;
  destination = route->getFirst();
  linearizeDegrees();
}

void GPSNavigator::setNSSpeed(int speed){
  NSSpeed = speed;
}

void GPSNavigator::setEWSpeed(int speed){
  EWSpeed = speed;
}

void GPSNavigator::setHeading(float head){
  heading = head;
}


float GPSNavigator::getBearing(){
  calculateBearing();
  return bearing;
}

float GPSNavigator::getDistance(){
  latDiff = toDecimalDegrees(destination->getLatitude()) - toDecimalDegrees(location->getLatitude());
  longDiff = toDecimalDegrees(destination->getLongitude()) - toDecimalDegrees(location->getLongitude());
  return sqrt(pow(latDiff * linearLatitudeDegree, 2) + pow(longDiff * linearLongitudeDegree, 2));
}

/*
 * Calculates how long a latitude degree is near the destination.
 * Used for approximating the distance to destination.
 * Must be run every time a new destination it set!
 * 
 */
void GPSNavigator::linearizeDegrees(){
  linearLongitudeDegree = (PI / 180) * cos(degToRad(toDecimalDegrees(destination->getLatitude()))) * EARTH_RADIUS;
}
/*
 * Calculates bearing [-PI;PI] with 0 being North and East being +pi/2	
 */
void GPSNavigator::calculateBearing(){
  latDiff = toDecimalDegrees(destination->getLatitude()) - toDecimalDegrees(location->getLatitude());
  longDiff = toDecimalDegrees(destination->getLongitude()) - toDecimalDegrees(location->getLongitude());
  bearing = atan2(longDiff, latDiff);
}

/*
 * Converts degrees to radians.
 * @param deg angle in degrees.
 * @return andle in radians.
 */
float GPSNavigator::degToRad(float deg){
  return (deg * PI / 180);
}


/*
 * Converts radians to degrees.
 * @param rad angle in radians.
 * @return angle in degrees.
 */
float GPSNavigator::radToDeg(float rad){
  return (rad * 180.0 / PI);
}


/*
 * Converts a @c long in @c dddmmmmmm format to float in @c ddd.ddddd.
 * The default form of storing coordinates is dddmmmmmm with an implied 
 * decimal devider after the 5th digit. This converts from that to ddd.ddddd
 * @param coordinate coordinate in long formatted @c @c dddmmmmmm.
 * @return coordinate in float formatted @c ddd.ddddd.
 */
float GPSNavigator::toDecimalDegrees(long coordinate){	
  // first we extract the full degrees from ddmm(.)mmm
  longTemp = coordinate / 100000;
  floatTemp = (float)longTemp;
  longTemp = coordinate - longTemp * 100000;
  // now we should only have mm(.)mmm left
  longTemp = longTemp *100;
  longTemp = longTemp / 60;
  // now we have (.)ddddd in longTemp
  floatTemp = floatTemp + ((float)longTemp / 100000.0);
  // If I've thought this through correctly it should now be dd.ddddd}
  return floatTemp;
}

char* GPSNavigator::getDestinationName(){
  return destination->getName();
}

void GPSNavigator::nextWaypoint(){
  setDestination(destination->getNext());
}
