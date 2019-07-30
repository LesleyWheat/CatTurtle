//better description

#include "arduino.h"
#include <MemoryUsage.h>
#include "realTimer.h"
#include "loggingFunctions.h"



class diagnoticsRoutine{
  private:
    String routineName = "Diagnostics";
    double cycleStartTime;
    double cycleEndTime;
    double cycleTime;
    int debugPrioritySetting;
    realTimer memStats;

    float batteryVoltage;
    int cycleCount = 0;

    byte logSize = 20;
    
    double cycleTimeSum;
    float batteryVoltageSum;

   void printMemStats(){
    debugPrint(5, routineName, 5, String("Current state of the memory----------------"));
    //debugPrint(5, routineName, 5, MEMORY_PRINT_START);
    //debugPrint(5, routineName, 5, MEMORY_PRINT_HEAPSTART);
    //debugPrint(5, routineName, 5, MEMORY_PRINT_HEAPEND);
    //debugPrint(5, routineName, 5, MEMORY_PRINT_STACKSTART);
    //debugPrint(5, routineName, 5, MEMORY_PRINT_END);
    //debugPrint(5, routineName, 5, MEMORY_PRINT_HEAPSIZE);
    //debugPrint(5, routineName, 5, FREERAM_PRINT);

    
    if ((Serial.available() > 0) & ( debugPrioritySetting >= 5)){
      //Serial.println(F("Current state of the memory:"));
      //Serial.println();
      
      MEMORY_PRINT_START
      MEMORY_PRINT_HEAPSTART
      MEMORY_PRINT_HEAPEND
      MEMORY_PRINT_STACKSTART
      MEMORY_PRINT_END
      MEMORY_PRINT_HEAPSIZE
      FREERAM_PRINT;
      
      //Serial.println();
      }

    debugPrint(5, routineName, 5, String("End current state of the memory----------------"));
    };
  

  
  void otherStats(){
    //Cycle finish
    cycleEndTime = millis();
    cycleTime = cycleEndTime - cycleStartTime;
    
    //Read into memory
    if(cycleCount == (logSize+1)){
      
      debugPrint(5, routineName, 5, String("Average cycle time: ") + String((cycleTimeSum/logSize)));
      debugPrint(5, routineName, 5, String("Average battery voltage: ") + String((batteryVoltageSum/logSize)));
      
      //Reset loop
      cycleCount =0;
      batteryVoltageSum=0;
      cycleTimeSum =0;
    }else{
      cycleCount += 1;
    }

    //Add sums
    batteryVoltageSum += batteryVoltage;
    cycleTimeSum += cycleTime;

    //End cycle
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
    memStats.init(60000);
  };

  void run(float batteryVoltage){
    //Read inputs
    this->batteryVoltage=batteryVoltage;

    
    if(memStats.check(true)){
      printMemStats();
    };
  
    //Cycle finish
    otherStats();
  };
};
