#include "WConstants.h"

#ifndef GarminParser_h
#define GarminParser_h

/** 
 * Parser for Garmin's Text Out mode serial port data.
 * 
 * More info about Garmin's Text Mode:
 * http://www.gpsinformation.org/dale/interface.htm#text
 *
 * @author  Janne Oksanen janne.oksanen@gmail.com
 * @section Licence
 * Published under GPLv2.
 * @see http://www.gpsinformation.org/dale/interface.htm#text

 */
class GarminParser {

  public:
  
    /**
     *  Empty class constructor.
     */
    GarminParser();
    
    /**
     * Parses all the data out of the string @a s.
     * This method takes in a string formatted in Garmin's own Text Out, 
     * parses the data and populates all the member variables that hold
     * the data.
     * @param s string formatted in Garmin's Text Out style.
     */
    void parseString(const char* s);
    
    /**
     * Returns last parsed longitude.
     * @return longitude as a long int formatted as dddmmmmm with an
     * implied decimal separator after the 5th digit.
     */
    long getLongitude();

    /**
     * Returns last parsed latitude.
     * @return latitude as a long int formatted as ddmmmmm with an
     * implied decimal separator after the 5th digit.
     */
    long getLatitude();
    
    /**
     * Returns the latitude hemisphere.
     * @return @c N or @c S.
     */
    char getLongHem();
    
    /**
     * Returns the longitude hemisphere.
     * @return @c E or @c W.
     */
    char getLatHem();
    
    /**
     * Returns the GPS error.
     * @return GPS error in meters.
     */
    int getError();
    
    /**
     * Returns the altitude.
     * @return altitude in meters. Negative if below sea level.
     */
    int getAltitude();

    /**
     * Returns the speed.
     * @return speed in decimeters (tenth of a meter) per second. 
     * (54 = 5.4 m/s)
     */
    int getSpeed();
    
    /**
     * Returns the heading.
     * @return heading in radians [-PI;PI] with 0 being East and -PI/2 being
     * North.
     */
    float getHeading();
    
    /**
     * Returns the time.
     * @return pointer to an array of integers containing the time as 
     * follows:
     *   - time[0] = Year
     *   - time[1] = Month
     *   - time[2] = Day
     *   - time[3] = Hours
     *   - time[4] = Minutes
     *   - time[5] = Seconds
     */
    int* getTime();
	
  private:
    int time[6];
    char longHem;          // E or W
    char latHem;           // N or S
    long longitude;        // WGS84 dddmmmmm with an implied decimal after the 5th digit
    long latitude;         // WGS84 ddmmmmm, with an implied decimal after the 4th digit
    int error;           // Horizontal position error in meters
    int altitude;        // Height above or below mean sea level in meters
    int EWvelocity;       // Horizontal velocity in the East-West direction. +1234 if going 123.4m/s towards East
    int NSvelocity;       // Horizontal velocity in the North-South direction. +1234 if going 123.4m/s towards North
    int velocity;        // Despite the name, only a positive scalar of the total speed
    float heading;         // direction of movement: 0 if facing North, pi/2 if facing East, -pi/2 facing West
    int temp1;
    int temp2;
    long longTemp;

    void parseTime(const char* s);
    void parseHemisphere(const char* s);
    void parseLatitude(const char* s);
    void parseLongitude(const char* s);
    void parseError(const char* s);
    void parseAltitude(const char* s);
    void parseEWvelocity(const char* s);
    void parseNSvelocity(const char* s);
    void calculateVelocity();
    void calculateHeading();
    void parseEverything(const char* s);
		
    int parseYear(const char* s);
    int parseMonth(const char* s);
    int parseDay(const char* s);
    int parseHours(const char* s);
    int parseMinutes(const char* s);
    int parseSeconds(const char* s);
};

#endif
