//Creates a timer that operates on a real time check based on the arduino internal clock
//Used as an alarm or to create time based loops
//Could have over flow issues if runtime is too long
//Needs to be used as object

#include "arduino.h"
#include "realTimer.h"


//Set up, store starting time and timer duration
void realTimer::init(double setTime){
  targetTime = setTime;
  accum = 0;
  lastCheck= millis();
}

//Checks if timer goes off
bool realTimer::check(bool condition){
  if(condition == 0){
    accum = 0;
    lastCheck= millis();
  }else if ((condition == 1) &  (enable == 0)){
    enable = 1;
    lastCheck=millis();
  }else if ((condition == 1) &  (enable == 1)){
    accum = accum + (millis()-lastCheck);
    lastCheck=millis();
  }

  if(accum > targetTime){
    accum = 0;
    lastCheck= millis();
    return true;
  }else{
    return false;
  }
}
