//Communications module

#include "arduino.h"
#include "realTimer.h"
#include "loggingFunctions.h"

class commRoutine{
  private:
    //Declare private variables
    int debugPrioritySetting;
    realTimer test;
    String routineName = "Comm";

    //Make sure serial is active during setup
    void establishContact() {
      while (Serial1.available() <= 0) {
        Serial1.print('A');   // send a capital A
        delay(300);
      }
      Serial1.println(' ');
    }

    //Returns a number based on a normal distrubution to simulate error
    double fuzzyNum(double num, double sigma){
      double
        sample,
         u1, u2,
         v1, v2, s,
         z1, z2;
    
      for (;;) {
         // get two uniform random numbers from 0 to .999...
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

  //Set public routines for main to use
  public:

  void init(int debugPrioritySetting){
    //set variables
    this->debugPrioritySetting=debugPrioritySetting;

    //Starting variables

    
    //create objects
    test.init(5000);

    // start serial port at 115200 bps:
    Serial1.begin(115200);
    while (!Serial1) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    
    establishContact();  // send a byte to establish contact until receiver responds
  };

  //main run loop
  void run(){
    if(test.check(true)){
      debugPrint(5, routineName, 5, String("Fuzztest: ") + String(fuzzyNum(1000, 100)));
      //Serial1.println(String("Fuzztest: ") + String(fuzzyNum(1000, 100)));
    }
  };
};
