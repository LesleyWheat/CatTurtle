/*
  
*/

//Include functions
#include "loggingFunctions.h"
#include "realTimer.h"

//Include main routines as objects
#include "controlRoutine.cpp"
#include "commRoutine.cpp"
#include "diagnoticsRoutine.cpp"


//Declare Objects
controlRoutine control;
commRoutine comm;
diagnoticsRoutine diagnotics;


//Set input pins
int BatterySensorPin = A0;

//Set output pins
byte motorOptionPin1 = 8;
byte motorOptionPin2 = 9;
byte motorPWMA = 10;
byte motorPWMB = 11;

//global variables for main
float batteryVoltage = 0;
byte blinkState = 0;

//gloabl settings variables
int const debugPrioritySetting = 5;

//global objects for main
realTimer blinkTimer;

// the setup function runs once when you press reset or power the board
//Runs only once at setup
void setup() {
  debugPrint(debugPrioritySetting, "setup", 5, "Starting...");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  blinkTimer.init(1000);
  
  //Initalize main routines
  control.init(debugPrioritySetting);
  comm.init(debugPrioritySetting);
  diagnotics.init(debugPrioritySetting);
  outputSetup();

  //Finish setup
  debugPrint(debugPrioritySetting, "setup", 5, "Startup complete");
}

// the loop function runs over and over again forever
void loop() {
  //local variables
  String routineName = "main";

  //Cycle startup

  //Main sequence

  //Change led state to show board is running
  if(blinkState == 0){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }else{
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
  
  if(blinkTimer.check(true)){
      //Next state
      blinkState = ((blinkState + 1)%2);
      //debugPrint(5, routineName, 5, String("BlinkState: ") + String(blinkState));
  };

  // Delay so CPU doesn't run at 100% all the time
  delay(50);
  
  //Run main routines
  inputsRead();
  control.run(batteryVoltage);
  comm.run();
  diagnotics.run(batteryVoltage);
  outputWrite();
}

void inputsRead(){  
  //Read inputs and translate into readable format
  batteryVoltage = analogRead(BatterySensorPin)* (5.0 / 1023.0);
  
}

void outputSetup(){
  //Setup output pins
  pinMode(motorOptionPin1, OUTPUT);
  pinMode(motorOptionPin2, OUTPUT);
  pinMode(motorPWMA, OUTPUT);
  pinMode(motorPWMB, OUTPUT);
}


void outputWrite(){
  
  //Set outputs
  //Motor state
  analogWrite(motorOptionPin1,255);
  analogWrite(motorOptionPin2,0);
  
  //Motor PWM
  analogWrite(motorPWMA,control.motorOptionPin1_PWM);
  analogWrite(motorPWMB,control.motorOptionPin2_PWM);

  
}
