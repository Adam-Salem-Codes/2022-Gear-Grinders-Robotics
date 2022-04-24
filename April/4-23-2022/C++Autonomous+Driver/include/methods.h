#include "vex.h"
#include "radian.h"
vex::distanceUnits i = inches; // means the same thing as inches just faster to
                               // type i rather than inches.
vex::directionType f = forward;
vex::directionType r = reverse;
competition Competition;
bool multiTaskRunning;
bool autonomousRunning;
bool BatteryGood;
int foot = 12;
int sixfeet = 72;
const int openROT = 1;
const int closeROT = -1;
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
void turnFor(radian r){
  Drivetrain.turnFor(r.convertRadToDeg(r.getAngle()), rotationUnits::deg);
}
void turnFor(double r) {
  radian r1 = radian(r);
  Drivetrain.turnFor(r1.convertRadToDeg(r), rotationUnits::deg);
}
int openClamp() {
  Motor9.spinTo(openROT, degrees);
  while (true) {
    task::sleep(20); // Sleeps for 20 Milliseconds.....
  }
  return 1; 
}
int closeClamp(){
  Motor9.spinTo(closeROT, degrees);
  while (true) {
    task::sleep(20); // Sleeps for 20 Milliseconds.....
  }
  return 1;
}
void SystemChecks() {
  // System Checks Battery FieldControl etc ...
  println(" ********** System Checks **********");
  Brain.Screen.setCursor(1,1);
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

template <typename T>
void printlnc(T const & args) { // Prints to the controller with new line.
  Controller1.Screen.print(args);
  Controller1.Screen.newLine();
}

template <typename T>
void printc(T const & args) { //Prints to the Controller without a new line.
  Controller1.Screen.print(args);
}

template<class T, size_t N>
constexpr size_t sizeofArray(T (&)[N]) { return N; } //Gets size of array in elements

void MotorChecks() {
   //Power readout from motors useful to know when motors are stressed and loaded
    printc("Left Motor current (A): "); //Left drivetrain motor current.
    printlnc(LeftDriveSmart.current(amp) + 'A'); // Estimated 2.5A of current draw from motors (on load)
    
    printc("Right Motor current (A): ");
    printlnc(RightDriveSmart.current(amp) + 'A');// Right drivetrain motor Current.


    //Power read-outs Watts (Estimated 11 Watt power draw)
    printc("Drivetrain Left Motor Power (W)");
    printlnc(LeftDriveSmart.power(powerUnits::watt) + 'W');

    printc("Drivetrain Right Motor Power (W)");
    printlnc(RightDriveSmart.power(powerUnits::watt) + 'W');

    //Read-out of Drivetrain motor temperature measured in current (Amps)
    double rightmotorTempC = RightDriveSmart.temperature(temperatureUnits::celsius);
    double leftmotorTempC = LeftDriveSmart.temperature(temperatureUnits::celsius);

    printc("Drivetrain Left Motor Temperature (C): ");
    printlnc(leftmotorTempC + 'C');

    printc("Drivetrain Right Motor Temperature (C): ");
    printlnc(rightmotorTempC + 'C');

    //Voltage Read-out of drivetrain motors.
    printc("Voltage of Left Motor: ");
    printlnc(LeftDriveSmart.voltage());
    
    printc("Voltage of Right Motor: ");
    printlnc(RightDriveSmart.voltage());
}