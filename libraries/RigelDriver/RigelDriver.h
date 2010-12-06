#ifndef RigelDriver_h
#define RigelDriver_h

#include "WConstants.h"
#include "SoftwareServo.h"
#include "RigelDriverConstants.h"

/**
 * This is a library for manouvering a Budget Robotics Rigel robot car. 
 * 
 * The constants are set for the servo configuration where the wheels are set as 
 * far apart as possible. The Adruino digital pins are also defined in the 
 * constants header file. This class most likely has very little value to anyone
 * but me since this is highly specific to my configuration. This file is 
 * included mainly for completeness. Depends on SoftwareServo.
 *
 * @author  Janne Oksanen janne.oksanen@gmail.com
 * @see http://www.budgetrobotics.com/shop/?cat=116
 * @see http://www.arduino.cc/playground/ComponentLib/Servo
 * 
 * @section Licence
 * Published under GPLv2.
 */
class RigelDriver {

  public:
  /**
   * Class constructor.
   *
   * Attaches all the servos to pins defined in RigelDriverConstants.h
   */
  RigelDriver();

  /**
   * Drives the car forward at full speed.
   * Will not return until all the dirve cycles are completed.
   * @param n how long
   */
  void driveForward(int n);

  /**
   * Drives the car backwards at full speed.
   * Will not return until all the dirve cycles are completed.
   * @param n how long
   */
  void driveBackwards(int n);

  /**
   * Spins the car left at full speed.
   * Will not return until all the dirve cycles are completed. How fast the car
   * turns will depend on tire grip and various constants defined in 
   * RigelDriverConstants.h
   * @param n how long
   */
  void spinLeft(int n);

  /**
   * Spins the car right at full speed.
   * Will not return until all the dirve cycles are completed. How fast the car
   * turns will depend on tire grip and various constants defined in 
   * RigelDriverConstants.h
   * @param n how long
   */
  void spinRight(int n);

  /**
   * Steers the car left by slowing down the left wheels.
   * Will not return until all the dirve cycles are completed.
   * @param n how long
   */
  void steerLeft(int n);

  /**
   * Steers the car right by slowing down the right wheels.
   * Will not return until all the dirve cycles are completed.
   * @param n how long
   */
  void steerRight(int n);


	
  private:
  int i;
  SoftwareServo LeftFront;
  SoftwareServo RightFront;
  SoftwareServo LeftBack;
  SoftwareServo RightBack;

};
#endif

