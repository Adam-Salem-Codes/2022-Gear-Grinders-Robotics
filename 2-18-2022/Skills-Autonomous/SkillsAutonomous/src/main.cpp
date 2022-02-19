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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <stdio.h>
#include <string>
using namespace vex;
distanceUnits i = inches; // means the same thing as inches just faster to
                               // type i rather than inches.
directionType f = forward;
competition Competition;
bool multiTaskRunning;
bool autonomousRunning;
int foot = 12;
int sixfeet = 72;

void turn(turnType dir) { Drivetrain.turnFor(dir, 90, degrees); }
void drive(double dist) { Drivetrain.driveFor(f, dist, i); }
void println(const char *args) {Brain.Screen.print(args);Brain.Screen.newLine();}
int multitask() {
  multiTaskRunning = true; // sets the boolean to true because the
  println("Multitask is running");
  MotorGroup5.spinFor(1, msec);
  while (multiTaskRunning) {
    task::sleep(20); // Sleeps for 20 Milliseconds.....
  }
  return 1;
}

void Autonomous(void) {
  autonomousRunning = true;
  MotorGroup5.setVelocity(83.14159265359, percent);
  drive(sixfeet);
  turn(left);
  drive(20);
  turn(left);
  drive(sixfeet - 24);
  MotorGroup5.spinFor(1.5, sec);
  Drivetrain.turnFor(20, degrees);
  task myTask(multitask);
  drive(foot * 3.5);
}

int main() {
  vexcodeInit();
  Drivetrain.setDriveVelocity(100, percent);
  Competition.autonomous(Autonomous);
}

