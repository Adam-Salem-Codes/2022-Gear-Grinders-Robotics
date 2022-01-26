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
//IMPORTANT API DOCUMENTATION: https://help.vexcodingstudio.com/index.html
#include "vex.h"//including the vex header file.
#include <string>
#include <stdio.h>
using namespace vex;
vex::distanceUnits i = inches;// means the same thing as inches just faster to type i rather than inches.
vex::directionType f = forward;
bool multitaskrunning = false;//These Booleans are true when autonomous/multitask is running. Very useful for logic 
bool autonomousActive = false;
bool BatteryGood;
int foot = 12;// 12 inches = 1 foot vEx playing field is 12' x 12' (feet).
int sixfeet = 72; // six feet = half of the playing field.
competition Competition; //DO NOT REMOVE!
/* IMPORTANT TO READ: This method takes in a turnType variable (left or right) and names it dir and passes it into
the Drivetrain.turnFor method DO NOT USE IF YOU WANT TO CHANGE AMOUNT TURNED OR THE UNITS IT MEASURES IN!
*/
void turn(turnType dir) { Drivetrain.turnFor(dir , 90, degrees); }
void drive(double dist) { Drivetrain.driveFor(f, dist, i); }
void println(const char *args) { Brain.Screen.print(args); Brain.Screen.newLine();} 

int multitask() {
  multitaskrunning = true; // sets the boolean to true because the Function/Method is running. DO NOT REMOVE....
  MotorGroup5.spinFor(1.5, sec); // Puts preloads into the goal.
   while(multitaskrunning) {
    vex::task::sleep(20); // Sleeps for 20 Milliseconds....
  }
  return 1;
}

//Declaration of autonomous function/method.
void Autonomous( void ) {
  autonomousActive = true;
  vex::task myTask(multitask); 
  /* This task can run at the same time as another function/method. 
  As an example you can move the drive train and activate a conveyor belt or fork 
  lift at the same time similar to multithreading. But it executes the multitask 
  method/function so what ever's running in there will be ran at the same time as
  the autonomous function/method. keep in mind that whatever written in autonomous will be excuted at the same time.
  */
  // Start of actual autonomous code...
  drive(sixfeet);
  turn(left);
  drive(20);
  turn(left);
  drive(sixfeet - 24);
  MotorGroup5.spinFor(1.5, sec); // Puts preloads into the goal.
  vex::wait(20, msec);
  Drivetrain.turnFor(35, degrees);
  vex::wait(20, msec);
  drive(foot * 5);
  Drivetrain.turnFor(5, degrees);
  Drivetrain.driveFor(reverse, sixfeet - 24, i);
  MotorGroup5.spinFor(reverse, 1.5, seconds);

  /* Done with autonomous code for now when implementing
  other features later it will get more complex but for now this is the movement code.
  */ 
}
void DriverControl( void ) {
  autonomousActive = false;
  multitaskrunning = false; 
  Controller1.Screen.print("DRIVER CONTROL STARTED GO GO GO!!!");

  Controller1.rumble(rumblePulse);
  // This line makes the controller vibrate to let you know that the driver controls enabled.
  //nothing more to code here...
}
void SystemChecks() {
  // System Checks Battery FieldControl etc ...
  println(" ********** System Checks ********** System Checks ********** System Checks **********");
  if(Competition.isEnabled() == true) { // Checks if competition mode is enabled
        Brain.Screen.setFillColor(green);
          println("Competition Mode is Enabled Do your best out there :)");
  }
  if(Competition.isCompetitionSwitch() == true)
    println("Connected to the Competition Switch ✅");  
    else if(Competition.isCompetitionSwitch() == false)
     println("Not Connected to the Competition Switch ❌");
    
  if(Competition.isFieldControl() == true) {
    Brain.Screen.setFillColor(green);
    println("Connected to the Field Control System ✅");   
    } 
  else {
    Brain.Screen.setFillColor(red);
    println("Not Connected to the Field Control System ❌");  
    }
  // Checks if the field controller is connected to the controller.
  int Battery = Brain.Battery.capacity(); // Makes a varible / Integer that is equal to the capacity of the battery.
  if (Battery >= 80) { // Checks if the battery capacity is equal to 80% or above 80%.
  BatteryGood = true;
    Brain.Screen.setFillColor(green);
    Brain.Screen.setCursor(1,4);
    println("Battery Percent Above 80% Shouldn't need charging. ✅"); 
    
  }

  else if (Battery <= 25){ // Checks if the battery capacity is equal to 25% or below 25%.
    BatteryGood = false;
    Brain.Screen.setFillColor(red);
    Brain.Screen.setCursor(1,4);
    println("Battery NEEDS charging RIGHT NOW. ❌");
    Brain.Screen.setFillColor(white);
  }
  println(" ********** System Checks DONE!!! ********** System Checks DONE!!! ********** System Checks DONE!!! **********");
  //... End of Checks Start Code...
}

int main() {
  vexcodeInit();// Initializing Robot Configuration. DO NOT REMOVE!
  SystemChecks();
  Drivetrain.setDriveVelocity(100, percent); 
  MotorGroup5.setVelocity(100, percent);
  // These lines set the velocity of the DriveTrain to 100% so it goes it fastest.
  Brain.Screen.setFont(monoXXL);

  Competition.autonomous(Autonomous); 
  Competition.drivercontrol(DriverControl); 
}
