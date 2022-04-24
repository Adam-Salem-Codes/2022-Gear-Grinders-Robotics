using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group MotorGroup5;
extern motor Motor9;
extern motor_group fourbarlift;
extern drivetrain Drivetrain;
extern inertial Inertial;
extern motor LeftDriveSmart;
extern motor RightDriveSmart;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );