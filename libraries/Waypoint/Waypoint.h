#ifndef Waypoint_h
#define Waypoint_h
#include "WProgram.h"
#include "WConstants.h"

/**
 * GPS Waypoint class. 
 * GPS Waypoint has two characteristrics: location and name. Location
 * is broken down to coordinates and hemispheres. Some sanity chechs for 
 * input data will be implemented at some point in time.
 *
 * @author  Janne Oksanen janne.oksanen@gmail.com
 * @section Licence
 * Published under GPLv2.
 */
class Waypoint {


  public:
    /**
     * Class constructor.
     * Sets @a latitude and @a longitude to @c 0 and @a name and @a next to @c 
     * null.
     */
    Waypoint();
    
    /**
     * Class constructor with all the data.
     * @param lon longitude in @c long @c int formatted as @c dddmmmmm
     * @param nsHem hemisphere as @c N or @c S.
     * @param lat latitude in @c long @c int formatted as @c ddmmmmm
     * @param ewHem hemisphere as @c E or @c W.
     * @param n name of the Waypoint.
     * 
     */
    Waypoint(long lon, char nsHem, long lat, char ewHem, char* n);
    
    /**
     * Sets @a longitude.
     * @param lon longitude in @c long @c int formatted as @c dddmmmmm
     */
    void setLongitude(long lon);

    /**
     * Sets @a latitude.
     * @param lat latitude in @c long @c int formatted as @c ddmmmmm
     */
    void setLatitude(long lat);
    
    /**
     * Sets name of the Waypoint.
     * @param n name.
     */
    void setName(char* n);
    
    /**
     * Sets Northern or Southern hemisphere.
     * param c Valid values @c N and @c S. If not sane then set to N.
     */
    void setNSHemisphere(char c);

    /**
     * Sets Eastern or Western hemisphere.
     * param c Valid values @c E and @c W. If not sane then set to E.
     */
    void setEWHemisphere(char c);
    
    /**
     * Returns longitude.
     * @return longitude in @c long @c int formatted as @c dddmmmmm. Implied
     * decimal separator after the 5th digit
     */
    long getLongitude();

    /**
     * Returns latitude.
     * @return latitude in @c long @c int formatted as @c ddmmmmm. Implied
     * decimal separator after the 5th digit
     */
    long getLatitude();
    
    /**
     * Returns Northern or Southern hemisphere.
     * @return @c N or @c S.
     */
    char getNSHemisphere();

    /**
     * Returns Eastern or Western hemisphere.
     * @return @c E or @c W.
     */
    char getEWHemisphere();
    
    /**
     * Returns the name of the Waypoint.
     * @return name of the Waypoint.
     */
    char* getName();
    
    /**
     * Sets next Waypoint. Used in GPSRoute, which is a linked list of 
     * Waypoints.
     * @see GPSRoute
     */
    void setNext(Waypoint* wp);
    
    /**
     * Returns next Waypoint. Used in GPSRoute, which is a linked list of 
     * Waypoints.
     * @see GPSRoute
     */
    Waypoint* getNext();

  private:
    long latitude;
    long longitude;
    char* name;
    bool isValidLongitude(long lon);
    bool isValidLatitude(long lat);
    char NSHemisphere;
    char EWHemisphere;
    Waypoint* next;
				
};
#endif
