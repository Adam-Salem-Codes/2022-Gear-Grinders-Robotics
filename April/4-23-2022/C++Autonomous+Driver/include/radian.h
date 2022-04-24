

class radian {

/*This is useful for Trig functions I might not use this class
but it's useful to have and if your copying my code and want the 
ability to turn in radians than definately copy this!
 */
public: 
  double Angle;
  double π = 3.141592653589; // How to get PI symbol hold ALT and then type 2-2-7 So ALT+227
    radian(double angle) {
      Angle = angle;
    }
     double convertDegToRad(double a) {
        return a * π / 180; // π rad = 180deg So 2π = 360deg. π/2 = 90deg
    }
    double convertRadToDeg(double a){
      return a * 180 / π;
    }
    double getAngle() {
      return Angle;
    }
};