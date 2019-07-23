/*
  
*/

#include "realTimer.cpp"
#include "diagnoticsRoutine.cpp"

int batteryVoltage = 0;


//Objects
realTimer timer1;
diagnoticsRoutine diagnotics;
realTimer memStats;

//settings variables
int const debugPrioritySetting = 5;


// the setup function runs once when you press reset or power the board
void setup() {
  debugPrint("setup", 5, "Starting...");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  establishContact();  // send a byte to establish contact until receiver responds

  timer1.init(10000);
  memStats.init(20000);
  diagnotics.init(debugPrioritySetting);
  
  debugPrint("setup", 5, "Startup complete");
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


  if(timer1.check(true)){
    debugPrint("Main", 5, String("Fuzztest: ") + String(fuzzyNum(1000, 100)));
  }

  if(memStats.check(true)){
    diagnotics.printMemStats();
  }
  
  //Cycle finish
  diagnotics.cycleStats();
  
}

void inputs(){
  //list pins
  int BatterySensorPin = A0;
  
  //Read inputs
  batteryVoltage = analogRead(BatterySensorPin);
  
}

void control(){
  
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

void comm(){
  
}
