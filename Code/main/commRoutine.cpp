//Communications module

#include "arduino.h"
#include "realTimer.h"
#include "loggingFunctions.h"
#include "miscFunctions.h"

class commRoutine{
  private:
    //Declare private variables
    int debugPrioritySetting;
    realTimer contactTimeout;
    realTimer test;
    
    String routineName = "Comm";

    //Make sure serial is active during setup
    void establishContact() {
      contactTimeout.init(60000);
      
      while ((Serial.available() <= 0) & (contactTimeout.check(true) == false)) {
        Serial.print('A');   // send a capital A
        delay(500);
      }
      Serial.println(' ');
    }


  //Set public routines for main to use
  public:

  void init(int debugPrioritySetting){
    //set variables
    this->debugPrioritySetting=debugPrioritySetting;

    //Starting variables

    
    //create objects

    // start bluetooth serial port at 115200 bps:
    Serial1.begin(115200);
    // start serial port at 9600 bps:
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    
    establishContact();  // send a byte to establish contact until receiver responds
  };

  //main run loop
  void run(){
    if(test.check(true)){
      //debugPrint(5, routineName, 5, String("Fuzztest: ") + String(fuzzyNum(1000, 100)));
      //Serial1.println(String("Fuzztest: ") + String(fuzzyNum(1000, 100)));
      Serial1.println(String("AT+RSSI"));
      int incomingByte = Serial1.read();
      Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
    }
  };
};
