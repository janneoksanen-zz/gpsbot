#ifndef HM55B_h
#define HM55B_h

#include "WProgram.h"
#include "WConstants.h"
#include "compass_pin_conf.h"
#include <math.h>

/**
 * Driver for Hitachi HM55B Compass Module
 *
 * Lib for my GPS navigating robot car project. It's heavily based
 * on code by kiilo (kiilo@kiilo.org) that was published at the Arduino site. 
 * Basically I just took his code and made an object out of it with very slight
 * modifications to make it directly compatible with the navigation library I 
 * wrote for the robot.
 *
 * @author  Janne Oksanen janne.oksanen@gmail.com
 * @see http://www.arduino.cc/playground/Main/HM55B
 * @section Licence
 * Published under GPLv2.
 */
class HM55B{

	public:
		/**
		 * Maps the pins to ones defined in the other header and resets the module.
		 */
		HM55B();
		
		/**
		 * Resets the compass module.
		 */
		void reset();
		
		/**
		 * Returns the heading
		 * @return [-PI;PI] with East being 0 and North -PI/2
		 */
		float getHeading();
		
		/**
		 * Measures the heading @a sample_size times and returns the average.
		 * @return average of @a sample_size number of measurements.
		 */
		float getStableHeading(int sample_size);
				
	private:
		int x_data;
		int y_data;
		float heading;	
		void shiftOut(int val, int bitCount);
		int shiftIn(int bitCount);
		void startMeasurementCommand();
		int readCommand();
	

};

#endif
