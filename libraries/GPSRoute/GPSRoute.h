#include "WProgram.h"
#include "WConstants.h"
#include "Waypoint.h"

#ifndef GPSRoute_h
#define GPSRoute_h

/**
 * Linked list of Waypoints that represent a route.
 *
 * @author  Janne Oksanen janne.oksanen@gmail.com
 *
 * @see Waypoint
 * 
 * @section Licence
 * Published under GPLv2.
 * 
 */
class GPSRoute {

  public:
  /**
   * Class constructor. Sets count to 0 and first to null.
   */
  GPSRoute();
	
  /**
   * Returns a pointer to the first Waypoint::
   * @return pointer to the first Waypoin
   */
  Waypoint* getFirst();
	
  /**
   * Returns the number of Waypoints.
   * @return number of Waypoints.
   */
  int size();
	
  /**
   * Adds a Waypoint to the beginning to the linked list.
   */
  void addNode(Waypoint* wp);
	
  private:
  int count;
  Waypoint* first;
  Waypoint* temp;
};

#endif
