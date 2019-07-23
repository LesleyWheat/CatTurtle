/*
  
*/

//
#include "loggingFunctions.h"

//Main routine files
#include "controlRoutine.cpp"
#include "commRoutine.cpp"
#include "diagnoticsRoutine.cpp"


//Declare Objects
controlRoutine control;
commRoutine comm;
diagnoticsRoutine diagnotics;

//global variables
int batteryVoltage = 0;

//gloabl settings variables
int const debugPrioritySetting = 5;


// the setup function runs once when you press reset or power the board
void setup() {
  debugPrint(debugPrioritySetting, "setup", 5, "Starting...");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  //Initalize main routines
  control.init(debugPrioritySetting);
  comm.init(debugPrioritySetting);
  diagnotics.init(debugPrioritySetting);
  
  debugPrint(debugPrioritySetting, "setup", 5, "Startup complete");
}

// the loop function runs over and over again forever
void loop() {
  //local variables

  //Cycle startup

  //Main sequence
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  //Run main routines
  control.run();
  comm.run();
  diagnotics.run();
}

void inputs(){
  //list pins
  int BatterySensorPin = A0;
  
  //Read inputs
  batteryVoltage = analogRead(BatterySensorPin);
  
}

void output(){
  //list pins
  //Motor Pins
  byte motorInputPin1 = 7;
  byte motorInputPin2 = 8;
  byte motorPWMA = 13;
  byte motorPWMB = 11;

  //Set outputs

}
