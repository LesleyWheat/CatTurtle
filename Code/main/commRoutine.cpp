//better description

#include "arduino.h"
#include "realTimer.h"
#include "loggingFunctions.h"

class commRoutine{
  private:
    int debugPrioritySetting;
    realTimer test;
    String routineName = "Comm";

    void establishContact() {
      while (Serial.available() <= 0) {
        Serial.print('A');   // send a capital A
        delay(300);
      }
      Serial.println(' ');
    }
    double fuzzyNum(double num, double sigma){
      double
        sample,
         u1, u2,
         v1, v2, s,
         z1, z2;
    
      for (;;) {
    
         /* get two uniform random numbers from 0 to .999...
          */
         u1 = (float) random(RAND_MAX) / ((float) RAND_MAX + 1);
         u2 = (float) random(RAND_MAX) / ((float) RAND_MAX + 1);
    
    
         v1 = 2.0L*u1 - 1.0L;
         v2 = 2.0L*u2 - 1.0L;
         s = v1 * v1 + v2 * v2;
    
         if (s <= 1.0L && s != 0.0L)
            break;
    
      }
    
      z1 = sqrt (-2.0L * log(s) /  s) * v1;
      z2 = sqrt (-2.0L * log(s) / s) * v2;
    
      //if (r1 != NULL) *r1 = (z1*sigma);
      //if (r2 != NULL) *r2 = (z2*sigma);
    
      sample = (z1*sigma)+ num;
      
      return sample;
    };

  public:

  void init(int debugPrioritySetting){
    //set variables
    this->debugPrioritySetting=debugPrioritySetting;

    //Starting variables

    
    //create objects
    test.init(5000);

    // start serial port at 9600 bps:
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    
    establishContact();  // send a byte to establish contact until receiver responds
  };

  void run(){
    if(test.check(true)){
      debugPrint(5, routineName, 5, String("Fuzztest: ") + String(fuzzyNum(1000, 100)));
      //Serial.println(String("Fuzztest: ") + String(fuzzyNum(1000, 100)));
    }
  };
};
