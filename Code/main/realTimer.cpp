//better description

#include "arduino.h"


class realTimer{
  private:
    double accum;
    double lastCheck;
    double enable;
    double targetTime;


  public:
    
    init(double setTime){
      targetTime = setTime;
      accum = 0;
      lastCheck= millis();
    }
  
    bool check(bool condition){
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
        return true;
      }else{
        return false;
      }
    }
};
