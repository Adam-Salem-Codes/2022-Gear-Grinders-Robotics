#include "vex.h"

vex::distanceUnits i = inches; // means the same thing as inches just faster to
                               // type i rather than inches.
vex::directionType f = forward;
vex::directionType r = reverse;
competition Competition;
bool multiTaskRunning;
bool autonomousRunning;
int foot = 12;
int sixfeet = 72;
int twelveFeet = sixfeet * 2;
void turn(turnType dir) { Drivetrain.turnFor(dir, 90, degrees); }
void drive(double dist) { Drivetrain.driveFor(f, dist, i); }
void println(const char *args) {
  Brain.Screen.print(args);
  Brain.Screen.newLine();
}
void driveFor(double distance, distanceUnits units, double velocity, velocityUnits units_v){
  Drivetrain.driveFor(distance, units, velocity, units_v);
}
void driveFor(directionType direction, double distance, distanceUnits units) {
  Drivetrain.driveFor(direction, distance, units);
}
void driveFor(double distance, distanceUnits units, double velocity){
  Drivetrain.driveFor(distance, units, velocity);
}
void printALL(const char* message){
  Brain.Screen.print(message);
  Brain.Screen.newLine();
  Controller1.Screen.print(message);
  Controller1.Screen.newLine();
}