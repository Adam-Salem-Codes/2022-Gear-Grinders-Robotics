
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// Drivetrain           drivetrain    1, 2, 3, 4
// BeltMotor            motor         5
// ---- END VEXCODE CONFIGURED DEVICES ----
// IMPORTANT API DOCUMENTATION: https://help.vexcodingstudio.com/index.html

#include "vex.h" //including the vex header file.
#include <cmath>
#include "methods.h"
#include <iostream>
using namespace std;
using namespace vex;
bool multitaskrunning =
    false; // These Booleans are true when autonomous/multitask is running. Very
           // useful for logic
bool autonomousActive = false;
bool lr; // false is left true is right.
bool running = true;
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

int checkDegrees() {
  while(true) { 
  Brain.Screen.print(Inertial.heading(degrees));
  task::sleep(500);
  }  
   
  return 1;
}
int* checkSpeed() {
  int xspeed = Inertial.acceleration(xaxis),
  yspeed = Inertial.acceleration(yaxis),
  zspeed = Inertial.acceleration(zaxis);
  
  static int speeds[] = { // This is static so I don't get a Warning from Clang
    xspeed,
    yspeed,
    zspeed
  };
  return speeds; // Array: Xspeed and then Z Speed.
}

// Declaration of autonomous function/method.
void Autonomous(void) {
  autonomousActive = true;
  
  /* This task can run at the same time as another function/method.
  As an example you can move the drive train and activate a conveyor belt or
  fork lift at the same time similar to multithreading. But it executes the
  multitask method/function so what ever's running in there will be ran at the
  same time as the autonomous function/method. keep in mind that whatever
  written in autonomous will be excuted at the same time. */
  task check(checkDegrees);
  task myTask(multitask);

  /* README: This autonomous code is current a prototype and probably doesn't work because
   I haven't gotten to test the code in weeks. So please don't steal this code it will just make
   your robot worse. :/*/
  if(!lr) {//lr = left
  
    MotorGroup5.setVelocity(83.14159265359, percent);
    Motor9.setVelocity(100, percent);
    vex::task open(openClamp);
    open.stop();
    Drivetrain.driveFor(f,  foot*34, i);
    open.resume();
    vex::task close(closeClamp);
    wait(500, msec);
    Drivetrain.driveFor(r, foot*4, i);
    return;
  } 



  MotorGroup5.setVelocity(83.14159265359, percent);
  Motor9.setVelocity(100, percent);
  MotorGroup5.setVelocity(83.14159265359, percent);
  vex::task open(openClamp);
  Drivetrain.driveFor(f, foot*4, i);
  vex::task close(closeClamp);
  wait(500, msec);
  Drivetrain.driveFor(f, foot*4, i);
  openClamp();
  /* Done with autonomous code for now when implementing
  other features later it will get more complex but for now this is the movement
  code.
  */
}
 
 
void DriverControl(void) {
  Inertial.init(5);
  Inertial.calibrate();
  Inertial.startCalibration();
  autonomousActive = false;
  multitaskrunning = false;
  Motor9.setVelocity(100, percent);
  Controller1.Screen.print("DRIVER CONTROL STARTED GO GO GO!!!");
  Controller1.rumble(rumblePulse); // This line makes the controller vibrate to let you know that the driver control is active
   
  Controller1.Screen.clearScreen();
  while(true) {
    int* speeds = checkSpeed();
    Controller1.Screen.setCursor(0, 1);
    Controller1.Screen.clearScreen();
    printc("XSpeed: ");
    printlnc(speeds[0]);
    printc("YSpeed: ");
    printlnc(speeds[1]);
    printlnc("ZSpeed: ");
    printc(speeds[2]);
    //Speed readout from Inertial Sensor.

    //Checks Drivetrain motor status and prints it to the controller (This function is in methods.h)
    MotorChecks();
  }
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
    do {
      if(Brain.Screen.xPosition() < SCREEN_X / 2) {
          Brain.Screen.setFillColor(red);
          Brain.Screen.drawRectangle(0, 0, SCREEN_X, SCREEN_Y / 2);
          return vex::left; // adding the vex:: part because clang was giving an error std::left() and vex::left.                        
       }//if
      else {
        Brain.Screen.setFillColor(blue);
        Brain.Screen.drawRectangle(0, 0, SCREEN_X, SCREEN_Y / 2);
        return vex::right;//Same thing over here.
      }
    }
    while(Brain.Screen.pressing()); 
    Brain.Screen.clearScreen();
    Brain.Screen.newLine();
}

int main() {
  vexcodeInit(); // Initializing Robot Configuration. DO NOT REMOVE!
  fourbarlift.setStopping(brakeType::hold);
  Drivetrain.setDriveVelocity(100, percent);
  MotorGroup5.setVelocity(100, percent);
  // These lines set the velocity of the DriveTrain to 100% so it goes it
  // fastest.

  buttonInit() == vex::left ? lr = false : lr = true;
  // Added ternary operator because it's clearer code than an if else statment.
  SystemChecks();
  fourbarlift.setVelocity(200, percent); 
  Drivetrain.setDriveVelocity(200, percent);
  Motor9.setVelocity(200, percent);
  Competition.autonomous(Autonomous);
  Competition.drivercontrol(DriverControl);
  while(1) {
        task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }
}
