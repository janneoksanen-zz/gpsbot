/*
	Waypoint.cpp
	GPS Waypoint has two characteristrics: location and name. Location
	is broken down to coordinates and hemispheres. Some sanity chechs for 
	input data will be implemented at some point in time.
	
	Author:  Janne Oksanen
	Email:   janne.oksanen@gmail.com
	Published under GPLv2.

	Known bugs: None. If you find any please let me know.

*/

#include "Waypoint.h"
			
Waypoint::Waypoint(){
  name = NULL;
  next = NULL;
  longitude = 0;
  latitude = 0;
}
	
Waypoint::Waypoint(long lat, char nsHem, long lon, char ewHem, char *n){
  name = n;
  next = NULL;
  setLongitude(lon);
  setLatitude(lat);
  setNSHemisphere(nsHem);
  setEWHemisphere(ewHem);
}
	
// Checks if the data given makes any sense at all
// the long is formatted as ddmmmmm with an implied
// decimal after the 4th digit.
bool Waypoint::isValidLatitude(long lat){
  if (lat < 0 || lat > 9000000){
    return false;
  } else {
    return true;
  }
}

// Checks if the data given makes any sense at all
// the long is formatted as dddmmmmm with an implied
// decimal after the 5th digit.
bool Waypoint::isValidLongitude(long lon){
  if (lon < 0 || lon > 18000000){
    return false;
  } else {
    return true;
  }
}			
	
void Waypoint::setLatitude(long lat){
  if (isValidLatitude(lat)){
    latitude = lat;
  }	else {
    latitude = 0;
  }
}

void Waypoint::setLongitude(long lon){
  if (isValidLongitude(lon)){
    longitude = lon;
  }	else {
    longitude = 0;
  }
}
	
void Waypoint::setNSHemisphere(char c){
  // If hem data isn't sane we assume we're around Europe
  if (c != 'N' && c != 'S'){
    NSHemisphere = 'N';
  } else {
    NSHemisphere = c;
  }
}

void Waypoint::setEWHemisphere(char c){
  // If hem data isn't sane we assume we're around Europe
  if (c != 'E' && c != 'W'){
    EWHemisphere = 'E';
  } else {
    EWHemisphere = c;
  }
}
	
long Waypoint::getLatitude(){
  return latitude;
}

long Waypoint::getLongitude(){
  return longitude;
}
	
char* Waypoint::getName(){
  return name;
}
			
char Waypoint::getNSHemisphere(){
  return NSHemisphere;
}
			
void Waypoint::setNext(Waypoint* wp){
  next = wp;
}
Waypoint* Waypoint::getNext(){
  return next;
}
