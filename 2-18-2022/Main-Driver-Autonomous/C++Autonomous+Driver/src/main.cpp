/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Adam Salem         (Monkar hasn't worked on it yet)       */
/*    Created:      Thu Dec 16 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// Drivetrain           drivetrain    1, 2, 3, 4
// BeltMotor            motor         5
// ---- END VEXCODE CONFIGURED DEVICES ----
// IMPORTANT API DOCUMENTATION: https://help.vexcodingstudio.com/index.html
#include "vex.h" //including the vex header file.
#include <stdio.h>
#include <string>
#include "methods.h"
using namespace vex;

bool multitaskrunning =
    false; // These Booleans are true when autonomous/multitask is running. Very
           // useful for logic
bool autonomousActive = false;
bool BatteryGood;
bool lr; // false is left true is right.
bool running = true;
int foot = 12;    // 12 inches = 1 foot vEx playing field is 12' x 12' (feet).
int sixfeet = 72; // six feet = half of the playing field.
competition Competition; // DO NOT REMOVE!
int SCREEN_X = 240*2;
int SCREEN_Y = 120*2;



int multitask() {
  multitaskrunning = true; // sets the boolean to true because the
                           // Function/Method is running. DO NOT REMOVE....
  while (multitaskrunning) {
    task::sleep(20); // Sleeps for 20 Milliseconds....
  }
  return 1;
}

// Declaration of autonomous function/method.
void Autonomous(void) {
  autonomousActive = true;
      /* This task can run at the same time as another function/method.
  As an example you can move the drive train and activate a conveyor belt or
  fork lift at the same time similar to multithreading. But it executes the
  multitask method/function so what ever's running in there will be ran at the
  same time as the autonomous function/method. keep in mind that whatever
  written in autonomous will be excuted at the same time.
  */
  task myTask(multitask);
  if(!lr) {//lr = left
    MotorGroup5.setVelocity(83.14159265359, percent);
    Motor9.setVelocity(100, percent);
    drive(sixfeet);
    turn(right);
    drive(20);
    turn(right);
    drive(sixfeet - 24);
    MotorGroup5.spinFor(1.5, sec); // Puts preloads into the goal.
    wait(20, msec);
    Drivetrain.turnFor(20, degrees);
    wait(20, msec);
    drive(foot * 5);
    Drivetrain.turnFor(5, degrees);
    Drivetrain.driveFor(reverse, sixfeet - 24, i);
    MotorGroup5.spinFor(reverse, 1.5, seconds);
    return;
  } 



  MotorGroup5.setVelocity(83.14159265359, percent);
  Motor9.setVelocity(100, percent);
  drive(sixfeet);
  turn(left);
  drive(20);
  turn(left);
  drive(sixfeet - 24);
  MotorGroup5.spinFor(1.5, sec); // Puts preloads into the goal.
  wait(20, msec);
  Drivetrain.turnFor(20, degrees);
  wait(20, msec);
  drive(foot * 5);
  Drivetrain.turnFor(5, degrees);
  Drivetrain.driveFor(reverse, sixfeet - 24, i);
  MotorGroup5.spinFor(reverse, 1.5, seconds);

  /* Done with autonomous code for now when implementing
  other features later it will get more complex but for now this is the movement
  code.
  */
}
void DriverControl(void) {
  autonomousActive = false;
  multitaskrunning = false;
  Motor9.setVelocity(100, percent);
  Controller1.Screen.print("DRIVER CONTROL STARTED GO GO GO!!!");

  Controller1.rumble(rumblePulse);
  // This line makes the controller vibrate to let you know that the driver
}
void SystemChecks() {
  // System Checks Battery FieldControl etc ...
  println(" ********** System Checks **********");
  if (Competition.isEnabled()) { // Checks if competition mode is enabled
    Brain.Screen.setFillColor(green);
    println("Competition Mode is Enabled Do your best out there :)");
    Brain.Screen.setFillColor(black);
  }
  if (Competition.isCompetitionSwitch())
    println("Connected to the Competition Switch ✅");
  else if (!Competition.isCompetitionSwitch())
    println("Not Connected to the Competition Switch ❌");

  if (Competition.isFieldControl()) {
    Brain.Screen.setFillColor(green);
    println("Connected to the Field Control System ✅");
    Brain.Screen.setFillColor(black);
  } else {
    Brain.Screen.setFillColor(red);
    println("Not Connected to the Field Control System ❌");
    Brain.Screen.setFillColor(black);
  }
  // Checks if the field controller is connected to the controller.
  int Battery =
      Brain.Battery.capacity(); // Makes a varible / Integer that is equal to
                                // the capacity of the battery.
  if (Battery >=
      80) { // Checks if the battery capacity is equal to 80% or above 80%.
    BatteryGood = true;
    Brain.Screen.setFillColor(green);
    println("Battery Percent Above 80% Shouldn't need charging. ✅");
    Brain.Screen.setFillColor(black);
  }

  else if (Battery <=
           25) { // Checks if the battery capacity is equal to 25% or below 25%.
    BatteryGood = false;
    Brain.Screen.setFillColor(red);
    Brain.Screen.setCursor(1, 4);
    println("Battery NEEDS charging RIGHT NOW. ❌");
    Brain.Screen.setFillColor(black);
  }
  println(" ********** System Checks DONE!!! **********");
  //... End of Checks Start Code...
}


turnType buttonInit() {
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0, 0, SCREEN_X/2, SCREEN_Y/2);
  Brain.Screen.setCursor(3, 4);
  Brain.Screen.print("LEFT");
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(SCREEN_X / 2, 0, SCREEN_X / 2, SCREEN_Y / 2);
  Brain.Screen.setCursor(32, 4);
  Brain.Screen.print("RIGHT");
    waitUntil(Brain.Screen.pressing());
    do{
      if(Brain.Screen.xPosition() < SCREEN_X / 2) {
          Brain.Screen.setFillColor(red);
          Brain.Screen.drawRectangle(0, 0, SCREEN_X, SCREEN_Y);
          return left;
       }//if
      else {
        Brain.Screen.setFillColor(blue);
        Brain.Screen.drawRectangle(0, 0, SCREEN_X, SCREEN_Y);
        return right;
      }
    }
    while(Brain.Screen.pressing()); 
    Brain.Screen.clearScreen();
}

int main() {
  vexcodeInit(); // Initializing Robot Configuration. DO NOT REMOVE!
  Drivetrain.setDriveVelocity(100, percent);
  MotorGroup5.setVelocity(100, percent);
  // These lines set the velocity of the DriveTrain to 100% so it goes it
  // fastest.
  
  if(buttonInit() == left) {
    lr = false;
  }
  else {
     lr = true;
  }
  SystemChecks();
  task::sleep(1000*2);
  Competition.autonomous(Autonomous);
  Competition.drivercontrol(DriverControl);
  while(1) {
        task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }
}
