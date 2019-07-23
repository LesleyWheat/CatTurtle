//better description

#include "arduino.h"
#include "realTimer.h"


    
void realTimer::init(double setTime){
  targetTime = setTime;
  accum = 0;
  lastCheck= millis();
}

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
