/*  GarminParser.cpp
	Trying to parse some GPS information out of Garmin Text Out mode output.
	Author:  Janne Oksanen
	Email:   janne.oksanen@gmail.com
	Published under GPLv2.
    
	Known bugs: None. If you find any please let me know.

	More info about Garmin's Text Mode:
	http://www.gpsinformation.org/dale/interface.htm#text

*/
#include "WProgram.h"
#include "GarminParser.h"

GarminParser::GarminParser(){
	// Empty constructor
}

void GarminParser::parseString(const char* s){
	parseEverything(s);
}

void GarminParser::parseEverything(const char* s){
  parseTime(s);
  parseHemisphere(s);
  parseLatitude(s);
  parseLongitude(s);
  parseError(s);
  parseAltitude(s);
  parseEWvelocity(s);
  parseNSvelocity(s);
  calculateVelocity();
  calculateHeading();
}

void GarminParser::parseTime(const char* s){
  time[0] = parseYear(s);
  time[1] = parseMonth(s);
  time[2] = parseDay(s);
  time[3] = parseHours(s);
  time[4] = parseMinutes(s);
  time[5] = parseSeconds(s);
}

int GarminParser::parseYear(const char* s){
  // first two characters
  temp1 = s[1] - 48;
  temp2 = s[2] - 48;
  return 2000 + 10*temp1 + temp2;  
}

int GarminParser::parseMonth(const char* s){
  temp1 = s[3] - 48;
  temp2 = s[4] - 48;
  return 10*temp1 + temp2;  
}

int GarminParser::parseDay(const char* s){
  temp1 = s[5] - 48;
  temp2 = s[6] - 48;
  return 10*temp1 + temp2;  
}

int GarminParser::parseHours(const char* s){
  temp1 = s[7] - 48;
  temp2 = s[8] - 48;
  return 10*temp1 + temp2;  
}

int GarminParser::parseMinutes(const char* s){
  temp1 = s[9] - 48;
  temp2 = s[10] - 48;
  return 10*temp1 + temp2;  
}

int GarminParser::parseSeconds(const char* s){
  temp1 = s[11] - 48;
  temp2 = s[12] - 48;
  return 10*temp1 + temp2;  
}

void GarminParser::parseHemisphere(const char* s){
  latHem = s[13];
  longHem = s[21];  
}

void GarminParser::parseLatitude(const char* s){
    
  longTemp  =  (s[14] - 48) * 1000000;
  longTemp +=  (s[15] - 48) * 100000;
  longTemp +=  (s[16] - 48) * (long)10000;
  longTemp +=  (s[17] - 48) * 1000;
  longTemp +=  (s[18] - 48) * 100;
  longTemp +=  (s[19] - 48) * 10;
  longTemp +=  (s[20] - 48);
  latitude = longTemp;
}

void GarminParser::parseLongitude(const char* s){
  longTemp  =  (s[22] - 48) * 10000000;
  longTemp +=  (s[23] - 48) * 1000000;
  longTemp +=  (s[24] - 48) * 100000;
  longTemp +=  (s[25] - 48) * (long)10000;
  longTemp +=  (s[26] - 48) * 1000;
  longTemp +=  (s[27] - 48) * 100;
  longTemp +=  (s[28] - 48) * 10;
  longTemp +=  (s[29] - 48);
  longitude = longTemp;
}

void GarminParser::parseError(const char* s){
  temp1  = (s[31] - 48) * 100;
  temp1 += (s[32] - 48) * 10;
  temp1 += (s[33] - 48);
  error = temp1;
}

void GarminParser::parseAltitude(const char* s){
  temp1  = (s[35] - 48) * (long)10000;
  temp1 += (s[36] - 48) * 1000;
  temp1 += (s[37] - 48) * 100;
  temp1 += (s[38] - 48) * 10;
  temp1 += (s[39] - 48);

  //Now let's check if we're above or below sea level
  if (s[34] == '-'){
    altitude = -1 * temp1;
  } else {
    altitude = temp1;  
  }
}

void GarminParser::parseEWvelocity(const char* s){
  temp1  = (s[41] - 48) * 1000;
  temp1 += (s[42] - 48) * 100;
  temp1 += (s[43] - 48) * 10;
  temp1 += (s[44] - 48);

  // Now let's determine which way we're going
  if (s[40] == 'W'){
    EWvelocity = -1 * temp1; // negative for heading West
  } else {
    EWvelocity = temp1;      // positive for heading East
  }  
}

void GarminParser::parseNSvelocity(const char* s){
  temp1  = (s[46] - 48) * 1000;
  temp1 += (s[47] - 48) * 100;
  temp1 += (s[48] - 48) * 10;
  temp1 += (s[49] - 48);

  // Now let's determine which way we're going
  if (s[45] == 'S'){
    NSvelocity = -1 * temp1; // negative for heading South
  } else {
    NSvelocity = temp1;      // positive for heading North
  }  
}

void GarminParser::calculateVelocity(){
  velocity = sqrt(sq(NSvelocity) + sq(EWvelocity)); 
}

// Calculates heading [-PI;PI] with 0 being East
void GarminParser::calculateHeading(){
  heading = atan2(NSvelocity, EWvelocity);
}

long GarminParser::getLongitude() { return longitude; }
long GarminParser::getLatitude(){ return latitude; }
char GarminParser::getLongHem(){ return longHem; }
char GarminParser::getLatHem(){ return latHem; }
int GarminParser::getError(){ return error; }
int GarminParser::getAltitude(){ return altitude; }
int GarminParser::getSpeed(){ return velocity; }
float GarminParser::getHeading(){ return heading; }
int* GarminParser::getTime(){ return time; }

