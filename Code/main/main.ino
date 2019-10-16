/*
  
*/

//Include functions
#include "loggingFunctions.h"
#include "miscFunctions.h"
#include "realTimer.h"

//Include main routines as objects
#include "inputsRoutine.cpp"
#include "controlRoutine.cpp"
#include "commRoutine.cpp"
#include "diagnoticsRoutine.cpp"

//define build variables
#define targetCycleTime 50

//Declare Objects
inputsRoutine inputs;
controlRoutine control;
commRoutine comm;
diagnoticsRoutine diagnotics;

//

//Set input pins
byte BatterySensorPin = A5;
//Left is A
byte motorEncoderA_Pin = 2;
//Right is B
byte motorEncoderB_Pin = 3;

//Set output pins
byte motorOptionPin1 = 8;
byte motorOptionPin2 = 9;
byte motorPWMA = 10;
byte motorPWMB = 11;

//global variables for main
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
  inputs.init(debugPrioritySetting, BatterySensorPin, motorEncoderA_Pin, motorEncoderB_Pin);
  control.init(debugPrioritySetting);
  comm.init(debugPrioritySetting);
  diagnotics.init(debugPrioritySetting, targetCycleTime);
  outputSetup();

  //Set pins up
  pinMode(motorEncoderA_Pin, INPUT_PULLUP);
  pinMode(motorEncoderB_Pin, INPUT_PULLUP);
  pinMode(BatterySensorPin, INPUT);

  digitalWrite(motorEncoderA_Pin,HIGH);  // enable pullup resistor
  digitalWrite(motorEncoderB_Pin,HIGH);  // enable pullup resistor

  //set interupts
  attachInterrupt(digitalPinToInterrupt(motorEncoderA_Pin), encoderA_InterProxy, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motorEncoderB_Pin), encoderB_InterProxy, CHANGE);

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
  //delay(50);
  
  //Run main routines
  inputs.run();
  control.run(inputs.batteryVoltage, inputs.rpmA, inputs.rpmB);
  comm.run();
  diagnotics.run(inputs.batteryVoltage, inputs.rpmA, inputs.rpmB);
  outputWrite();
}

void encoderA_InterProxy(){
  inputs.encoderA();
}

void encoderB_InterProxy(){
  inputs.encoderB();
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
