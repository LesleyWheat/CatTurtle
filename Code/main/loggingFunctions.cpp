//Used to format output messages in the console

#include "arduino.h"
#include "loggingFunctions.h"

void debugPrint(int debugPrioritySetting, String routine, int priority, String info){
  String message = " ";
  
  if (Serial1.available() > 0) {
    if(debugPrioritySetting >= priority){
      message = String("debugPrint - ") + String(priority) + " - " + String(routine) + " - " + String(info);
      Serial1.println(message);
    }
  }
}
