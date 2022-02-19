
#include "vex.h"

vex::distanceUnits i = inches; // means the same thing as inches just faster to
                               // type i rather than inches.
vex::directionType f = forward;

/* IMPORTANT TO READ: This method takes in a turnType variable (left or right)
and names it dir and passes it into the Drivetrain.turnFor method DO NOT USE IF
YOU WANT TO CHANGE AMOUNT TURNED OR THE UNITS IT MEASURES IN!
*/
void turn(turnType dir) { Drivetrain.turnFor(dir, 90, degrees); }
void drive(double dist) { Drivetrain.driveFor(f, dist, i); }
void println(const char *args) {
  Brain.Screen.print(args);
  Brain.Screen.newLine();
}