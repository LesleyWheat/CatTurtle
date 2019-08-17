/*
  
*/

//functions
#include "loggingFunctions.h"
#include "realTimer.h"

//Main routine files
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
byte motorOptionPin1 = 7;
byte motorOptionPin2 = 8;
byte motorPWMA = 10;
byte motorPWMB = 11;

//global variables
float batteryVoltage = 0;
byte blinkState = 0;

//gloabl settings variables
int const debugPrioritySetting = 5;

//global objects
realTimer blinkTimer;

// the setup function runs once when you press reset or power the board
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
  
  debugPrint(debugPrioritySetting, "setup", 5, "Startup complete");
}

// the loop function runs over and over again forever
void loop() {
  //local variables
  String routineName = "main";

  //Cycle startup

  //Main sequence
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

  delay(50);                       // wait for a second
  
  //Run main routines
  inputsRead();
  control.run(batteryVoltage);
  comm.run();
  diagnotics.run(batteryVoltage);
  outputWrite();
}

void inputsRead(){  
  //Read inputs
  batteryVoltage = analogRead(BatterySensorPin)* (5.0 / 1023.0);
  
}

void outputSetup(){
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
