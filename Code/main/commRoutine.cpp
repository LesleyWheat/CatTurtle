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
    test.init(2000);

    // start bluetooth serial port at 115200 bps:
    Serial1.begin(115200);
    // start serial port at 9600 bps:
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    
    establishContact();  // send a byte to establish contact until receiver responds
    Serial1.println("at+init\r\n");
    //Serial.println("at+init\r\n");
    delay(500);
    for (int i=0;i < 20; i++){
      Serial.print((char) Serial1.read());
    }
    Serial.println("");
    
    Serial.println("at+iac=9e8b33\r\n");
    Serial1.println("at+iac=9e8b33\r\n");
    delay(500);
    for (int i=0;i < 20; i++){
      Serial.print((char) Serial1.read());
    }
    Serial.println("");
    Serial.println("at+class=0\r\n ");
    Serial1.println("at+class=0\r\n ");
    delay(500);
    for (int i=0;i < 20; i++){
      Serial.print((char) Serial1.read());
    }
    Serial.println("");
    Serial.println("at+inqm=1,1,20");
    Serial1.println("at+inqm=1,1,20");
    delay(500);
    for (int i=0;i < 20; i++){
      Serial.print((char) Serial1.read());
    }
    Serial1.println("");
    
  };

  //main run loop
  void run(){
    if(test.check(true)){
      //debugPrint(5, routineName, 5, String("Fuzztest: ") + String(fuzzyNum(1000, 100)));
      //Serial1.println(String("Fuzztest: ") + String(fuzzyNum(1000, 100)));
      Serial1.print("At+inq\r\n");

      //byte temp= Serial1.read();


      Serial.print("I received: ");
      for (int i=0;i < 20; i++){
        Serial.print((char) Serial1.read());
      }
      
      Serial.println("");
    }
  };
};
