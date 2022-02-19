/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\adams                                            */
/*    Created:      Tue Feb 08 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2, 3, 4
// Controller1          controller
// MotorGroup5          motor_group   5, 6
// Motor9               motor         9
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "methods.h"
#include "vex.h"
#include <cmath>
#include <stdio.h>
#include <string>
using namespace vex;
// Declare variables

// Declare variables
bool done;

int multitask() {
  multiTaskRunning = true;
  println("Multitask is running");
  Motor9.spinFor(418, degrees);
  Motor9.spinFor(-425, degrees);

  while (multiTaskRunning) {
    task::sleep(20); // Sleeps for 20 Milliseconds.....
  }
  return 1;
}

void Autonomous(void) {
  autonomousRunning = true;
  done = false;
  Drivetrain.setDriveVelocity(100, percent);// Sets the velocity of all of out Motors to make sure the autonomous is fast and works properly.
  MotorGroup5.setVelocity(83.14159265359, percent);
  Motor9.setVelocity(100, percent);

  Drivetrain.driveFor(f, ( sixfeet + foot * 2.1 ) , i); // Moves mobile goal across field
  Drivetrain.turnFor(155, degrees);//Turns to prepare to move second mobile goal

  //Done moving First Goal (Goals): >> * * *

  Drivetrain.driveFor(f, ( sixfeet - 3 ) , i); // drives forward to move other mobile goal(middle goal)

  Drivetrain.turnFor( ( 155 * -1 ) , degrees); //Turns to move third goal.

  //Done moving second goal (Goals): * >> * *

  Drivetrain.driveFor(f, ( foot * 4.8 ) , i);// Moves third goal

  //Done moving third goal (Goals):  * * >> *

  Drivetrain.turnFor( ( 35.6 * -1 ), degrees);// Turns to reverse and clamp onto red goal

  //If the goals were moved successfully we would have 60 points currently

  Drivetrain.driveFor(r, sixfeet, i);//reverses
  task myTask(multitask);//Opens/Closes clamp
  Drivetrain.driveFor(f, ( sixfeet + ( foot + 6 ) ) , i );//Drives forward to red side.

  done = true;
  //Done Moving red goal to red side 

  turn(left);//Turns left to prepare to drive to balance

  Drivetrain.driveFor(f, ( sixfeet + ( foot * 2 ) ), i);
  /*
  Drives up the ramp to balance.
  Balanced!
  Red goal on the red alliance side is worth 20 points + balancing it is worth 30 points 
  20 + 30 + 60 = 110
  */


}

int main() {
  vexcodeInit();
  Controller1.Screen.clearScreen(); 
  Motor9.resetRotation();// sets Rotation to be 0 where 90 degrees is open and up; make sure to start the autonomous with the clamp closed.
  Competition.autonomous(Autonomous);
  // Since this is a skills autonomous algorithm there is no need for a driver control method
}
