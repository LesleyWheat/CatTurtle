// Alarm/warning detection and monitoring

#include "arduino.h"
//#include <MemoryUsage.h>
#include "realTimer.h"
#include "loggingFunctions.h"



class diagnoticsRoutine{
  private:
    //Declare private variables
    String routineName = "Diag";
    double cycleStartTime;
    double cycleEndTime;
    double cycleTime;
    double downTime;
    int targetCycleTime;
    int debugPrioritySetting;
    realTimer memStats;

    float batteryVoltage;
    int cycleCount = 0;

    byte logSize = 100;
    
    double cycleTimeSum;
    long downTimeSum;
    float batteryVoltageSum;

    //Print out state of memory
     void printMemStats(){
      debugPrint(5, routineName, 5, String("Current state of the memory----------------"));
      //debugPrint(5, routineName, 5, MEMORY_PRINT_START);
      //debugPrint(5, routineName, 5, MEMORY_PRINT_HEAPSTART);
      //debugPrint(5, routineName, 5, MEMORY_PRINT_HEAPEND);
      //debugPrint(5, routineName, 5, MEMORY_PRINT_STACKSTART);
      //debugPrint(5, routineName, 5, MEMORY_PRINT_END);
      //debugPrint(5, routineName, 5, MEMORY_PRINT_HEAPSIZE);
      //debugPrint(5, routineName, 5, FREERAM_PRINT);
  
      
      if ((Serial1.available() > 0) & ( debugPrioritySetting >= 5)){
        //Serial.println(F("Current state of the memory:"));
        //Serial.println();
        /*
        MEMORY_PRINT_START
        MEMORY_PRINT_HEAPSTART
        MEMORY_PRINT_HEAPEND
        MEMORY_PRINT_STACKSTART
        MEMORY_PRINT_END
        MEMORY_PRINT_HEAPSIZE
        FREERAM_PRINT;
        */
        //Serial.println();
        }
  
      debugPrint(5, routineName, 5, String("End current state of the memory----------------"));
      };
  

    //output other stats and information
    void otherStats(){
     //add delay to meet target cycle time
     int delayTime = (int)(targetCycleTime- (millis()- cycleStartTime)-0.4);
      if (millis()- cycleStartTime < targetCycleTime){
        delay(delayTime);
      }

      
      //Cycle finish
      cycleEndTime = millis();
      cycleTime = cycleEndTime - cycleStartTime;

      
      //Read into memory
      if(cycleCount == (logSize+1)){
        //Check how much extra operating time there is to meet cycle time
        float percentUse = (cycleTimeSum-downTimeSum)*100.0/(logSize*targetCycleTime);
        debugPrint(5, routineName, 5, String("Average cycle time: ") + String((cycleTimeSum/logSize))+ String(", Percent Use: ") + String(percentUse));
        debugPrint(5, routineName, 5, String("Average battery voltage: ") + String((batteryVoltageSum/logSize)));
        
        //Reset loop
        cycleCount =0;
        batteryVoltageSum=0;
        cycleTimeSum =0;
        downTimeSum =0;
      }else{
        cycleCount += 1;
      }
  
      //Add sums
      batteryVoltageSum += batteryVoltage;
      cycleTimeSum += cycleTime;
      downTimeSum += delayTime;
      
      //End cycle
      cycleStartTime = cycleEndTime;
    };
  
  public:
    
    void init(int debugPrioritySetting, int targetCycleTime){
      //Set local variables
      this->debugPrioritySetting=debugPrioritySetting;
      this->targetCycleTime=targetCycleTime;
  
      //Set starting variables
      cycleStartTime = 0;
      cycleEndTime = 0;
      cycleTime = 0;
      
      //Create objects
      memStats.init(60000);
    };

    //runs in main loop
    void run(float batteryVoltage, double rpmA, double rpmB){
      //Read inputs
      this->batteryVoltage=batteryVoltage;
  
      
      if(memStats.check(true)){
        //printMemStats();
      };
    
      //Cycle finish
      otherStats();
    };
};
