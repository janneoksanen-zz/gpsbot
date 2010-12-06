#ifndef GPSBotConstants_h
#define GPSBotConstants_h
#include "WConstants.h"

// GPSBot Constants
#define LED_BLINK_DELAY 500        // LED blink delay
#define DRIVE_FORWARD_CYCLE 200		 // Default servo running time
#define DRIVE_STEERING_CYCLE 50		 // Default servo running time
#define BAUD_RATE   9600					 // Serial communication speed
#define WAYPOINT_1  (6213850, 'N', 2545856, 'E', "Waypoint 1")
#define WAYPOINT_2  (6213867, 'N', 2546124, 'E', "Goatse")
#define WAYPOINT_4  (6125165, 'N', 2653642, 'E', "Postilaatikko")
#define WAYPOINT_5  (6125146, 'N', 2653651, 'E', "Hikkalaatikko")
#define WAYPOINT_6  (6213706, 'N', 2545538, 'E', "Humppa")
#define DIRECTION_CHECK_TIME   10  // How often to check direction (in seconds)																						

// Number of waypoints for determinig heading
#define WAYPOINT_DISTANCE_LIMIT  10
#define GPS_ERROR_LIMIT          20
#define DIRECTION_ACCEPTABLE_TOLERANCE 0.150
#define COMPASS_CALIBRATION_FACTOR 60.0 // in degrees 

#endif
