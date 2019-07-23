//better description

#include "arduino.h"
#include <MemoryUsage.h>
#include "realTimer.h"
#include "loggingFunctions.h"

class diagnoticsRoutine{
  private:
    double cycleStartTime;
    double cycleEndTime;
    double cycleTime;
    int debugPrioritySetting;
    realTimer memStats;

   void printMemStats(){
    if ((Serial.available() > 0) & ( debugPrioritySetting >= 5)){
      Serial.println(F("Current state of the memory:"));
      Serial.println();
      
      MEMORY_PRINT_START
      MEMORY_PRINT_HEAPSTART
      MEMORY_PRINT_HEAPEND
      MEMORY_PRINT_STACKSTART
      MEMORY_PRINT_END
      MEMORY_PRINT_HEAPSIZE
      FREERAM_PRINT;
  
      Serial.println();
      Serial.println();
      }
    };


  
  void cycleStats(){
    //Cycle finish
    cycleEndTime = millis();
    cycleTime = cycleEndTime - cycleStartTime;
    if ((Serial.available() > 0) & ( debugPrioritySetting >= 5)){
      Serial.print(F("Cycle time: "));
      Serial.println(cycleTime);
    }
    cycleStartTime = cycleEndTime;
  };
  public:

  void init(int debugPrioritySetting){
    //Set local variables
    this->debugPrioritySetting=debugPrioritySetting;

    //Set starting variables
    cycleStartTime = 0;
    cycleEndTime = 0;
    cycleTime = 0;
    
    //Create objects
    memStats.init(20000);
  };

  void run(){
    if(memStats.check(true)){
      printMemStats();
    };
  
    //Cycle finish
    cycleStats();
  };
};
