#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors

controller Controller1 = controller(primary);
motor MotorGroup5MotorA = motor(PORT5, ratio18_1, true);
motor MotorGroup5MotorB = motor(PORT6, ratio18_1, false);
motor_group MotorGroup5 = motor_group(MotorGroup5MotorA, MotorGroup5MotorB);
motor Motor9 = motor(PORT9, ratio36_1, true);
motor fourbarliftMotorA = motor(PORT13, ratio36_1, true);
motor fourbarliftMotorB = motor(PORT12, ratio36_1, false);
motor_group fourbarlift = motor_group(fourbarliftMotorA, fourbarliftMotorB);
motor LeftDriveSmart = motor(PORT1, ratio36_1, true);
motor RightDriveSmart = motor(PORT2, ratio36_1, false);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
inertial Inertial = inertial(PORT10);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3
      // right = Axis2
      int drivetrainLeftSideSpeed = Controller1.Axis2.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
      // check the ButtonL1/ButtonL2 status to control fourbarlift
      if (Controller1.ButtonL1.pressing()) {
        fourbarlift.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        fourbarlift.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        fourbarlift.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      // check the ButtonR1/ButtonR2 status to control Motor9
      if (Controller1.ButtonR1.pressing()) {
        Motor9.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        Motor9.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        Motor9.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}