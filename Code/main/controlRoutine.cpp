//better description

#include "arduino.h"
//#include "realTimer.h"

class controlRoutine{
  private:
    int debugPrioritySetting;
    float batteryVoltage;
    String routineName = "Control";
    
  public:

  void init(int debugPrioritySetting){
    //Set local variables
    this->debugPrioritySetting=debugPrioritySetting;

    //Set starting variables

    //creat objects
    
  };

  void run(float batteryVoltage){
    //Read inputs
    this->batteryVoltage=batteryVoltage;
    
  };
};
