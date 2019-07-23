//better description

#include "arduino.h"
#include <MemoryUsage.h>

class diagnoticsRoutine{
  private:
    double cycleStartTime;
    double cycleEndTime;
    double cycleTime;
    int debugPrioritySetting;
    
  void memoryState(){
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
  
  public:

  init(int debugPrioritySetting){
    cycleStartTime = 0;
    cycleEndTime = 0;
    cycleTime = 0;
    this->debugPrioritySetting=debugPrioritySetting;
  };

  void printMemStats(){
  if ((Serial.available() > 0) & ( debugPrioritySetting >= 5)){
      memoryState();
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
  }
};
