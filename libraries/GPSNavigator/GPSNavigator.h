#ifndef GPSNavigator_h
#define GPSNavigator_h

#include "WProgram.h"
#include "WConstants.h"
#include "Waypoint.h"
#include "GPSRoute.h"

/// Earth's radius in meters.
#define EARTH_RADIUS 6367449
/// Length equivalent to one degree in latitude in meters.
#define linearLatitudeDegree 110952

/**
 * Navigator object for a GPS robot car.
 *
 * I wrote this lib for my GPS navigating robot car project. It was meant to be
 * used with my Waypoint and GarminParser classes and some of the design 
 * peculiarities are inherited from those classes. This class mainly calculates
 * distance and bearing to destination with the information provided.
 *
 * @author  Janne Oksanen janne.oksanen@gmail.com
 * @section Licence
 * Published under GPLv2.
 */
class GPSNavigator {
	
  public:
    /**
     * Empty class constructor.
     */
    GPSNavigator();
		
    /**
     * Sets the current location of navigator.
     * @param loc Waypoint to be set as the current location.
     */
    void setLocation(Waypoint* loc);

    /**
     * Sets the destination for the navigator.
     * @param dest Waypoint to be set as the destination.
     */
    void setDestination(Waypoint* dest);

    /**
     * Sets the route and takes the first node as the destination.
     * @param r Route to be set as the route to navigate through.
     */
    void setRoute(GPSRoute* r);

    /**
     * Sets the North-South direction velocity component.
     * @param speed Norh-South direction speed component.
     * Positive value going towards North.
     */
    void setNSSpeed(int speed);

    /**
     * Sets the North-South direction velocity component.
     * @param speed Norh-South direction speed component.
     * Positive value going East.
     */
    void setEWSpeed(int speed);

    /**
     * Sets the current heading.
     * @param head heading.
     */
    void setHeading(float head);

    /**
     * Calculates and returns bearing to destination.
     * @return Bearing to destination as [-PI;PI] with 0 going North and +pi/2 going East
     */
    float getBearing();

    /**
     * Calculates the distance to destination in meters.
     * @return distance to destination in meters.
     */
    float getDistance();

    /**
     * Returns a @c char pointer to the destination name.
     * @return destination name.
     */
    char* getDestinationName();

    /**
     * Tells the navigator to set the next @c Waypoint in @c Route as destination.
     */
    void nextWaypoint();
			
	private:
		GPSRoute* route;
		Waypoint* destination;
		Waypoint* location;
		int NSSpeed;
		int EWSpeed;
		float heading;
		float bearing;
		void calculateBearing();
		void linearizeDegrees();
		float linearLongitudeDegree;
		float degToRad(float deg);
		float radToDeg(float rad);
		float toDecimalDegrees(long position);
		long longTemp;
		float floatTemp;
		float latDiff;
		float longDiff;
	
};

#endif
