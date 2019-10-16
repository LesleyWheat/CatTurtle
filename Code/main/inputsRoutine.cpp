//Inputs module
//read and does prelimp sampling on inputs
//contains functions for interrupts

#include "arduino.h"
#include "realTimer.h"
#include "loggingFunctions.h"
#include "miscFunctions.h"

#define encoderSamples 4

class inputsRoutine{
  private:
    //Declare private variables
    String routineName = "inputs";
    int debugPrioritySetting;

    //pins
    byte BatterySensorPin;
    byte motorEncoderA_Pin;
    byte motorEncoderB_Pin;
    
    int motorEncoderA_SamplePeriodArray [encoderSamples];
    int motorEncoderB_SamplePeriodArray [encoderSamples];
    
    int motorEncoderA_SampleArrayindex = 0;
    int motorEncoderB_SampleArrayindex = 0;
    
    int encoderA_PrevTime = 0;
    int encoderB_PrevTime = 0;

    int encoderA_period = 0;
    int encoderB_period = 0;
    
    float encoderA_RPM = 0;
    float encoderB_RPM = 0;
    
    int counter =0;
    
    //Objects
    

    //Private functions
    
  public:
    //public variables
    float batteryVoltage = 0;
    double rpmA = 0;
    double rpmB = 0;

    //public functions
    void init(int debugPrioritySetting, byte BatterySensorPin, byte motorEncoderA_Pin, byte motorEncoderB_Pin){
        //Set local variables
        this->debugPrioritySetting=debugPrioritySetting;
        this->BatterySensorPin=BatterySensorPin;
        this->motorEncoderA_Pin=motorEncoderA_Pin;
        this->motorEncoderB_Pin=motorEncoderB_Pin;
    
        //Set starting variables
        
        //Create objects
        
      };

    
    //runs in main loop
    void run(){
        //Read inputs and translate into readable format
        batteryVoltage = analogRead(BatterySensorPin)* (5.0 / 1023.0);
      
        //motorEncoderA_SamplePeriodArray [motorEncoderA_SampleArrayindex] = millis()-encoderA_PrevTime;
        if (averageArray(motorEncoderA_SamplePeriodArray, encoderSamples) < 10){
          encoderA_RPM = 0;
        }else{
          if (((millis()-encoderA_PrevTime) > (40 + motorEncoderA_SamplePeriodArray [ motorEncoderA_SampleArrayindex ])) & 
                      (motorEncoderA_SamplePeriodArray [ motorEncoderA_SampleArrayindex ] > 500)) {
            encoderA_RPM = 60.0/((millis()-encoderA_PrevTime+ averageArray(motorEncoderA_SamplePeriodArray, encoderSamples))*8.0*2/1000.0);
          }else{
            encoderA_RPM = 60.0/(averageArray(motorEncoderA_SamplePeriodArray, encoderSamples)*8.0/1000.0);
          }
        }
        

        //motorEncoderB_SamplePeriodArray [motorEncoderB_SampleArrayindex] = millis()-encoderB_PrevTime;

        if (averageArray(motorEncoderB_SamplePeriodArray, encoderSamples) < 10){
          encoderB_RPM = 0;
        }else{
          if (((millis()-encoderB_PrevTime) > (40 + motorEncoderB_SamplePeriodArray [ motorEncoderB_SampleArrayindex ])) & 
                      (motorEncoderB_SamplePeriodArray [ motorEncoderB_SampleArrayindex ] > 500)) {
            encoderB_RPM = 60.0/((millis()-encoderB_PrevTime+ averageArray(motorEncoderB_SamplePeriodArray, encoderSamples))*8.0*2/1000.0);
          }else{
            encoderB_RPM = 60.0/(averageArray(motorEncoderB_SamplePeriodArray, encoderSamples)*8.0/1000.0);
          }
        }
      
        if (counter ==0){
          //debugPrint(5, routineName, 5, String("encoderA_RPM: ") + String(encoderA_RPM)+String(", encoderB_RPM: ") + String(encoderB_RPM));
        }
        counter = (counter+1)%10;

        rpmA = encoderA_RPM;
        rpmB = encoderB_RPM;
        
      }
      
      void encoderA(){
        int motorEncoderA_voltage = digitalRead(motorEncoderA_Pin);
        
        //debugPrint(5, routineName, 5, String("motorEncoderA triggered: ") + String(motorEncoderA_voltage));
        if(motorEncoderA_voltage == 0){
          motorEncoderA_SamplePeriodArray [motorEncoderA_SampleArrayindex] = millis()-encoderA_PrevTime;
          encoderA_PrevTime = millis();
          motorEncoderA_SampleArrayindex = (motorEncoderA_SampleArrayindex +1)%encoderSamples;
          if (motorEncoderA_SampleArrayindex == 0){
            //debugPrint(5, routineName, 5, String("encode A period: ") + String(motorEncoderA_SamplePeriodArray [motorEncoderA_SampleArrayindex]));
          }
        }
      }
      
      void encoderB(){
        int motorEncoderB_voltage = digitalRead(motorEncoderB_Pin);
        
        //debugPrint(5, routineName, 5, String("motorEncoderB triggered: ") + String(motorEncoderB_voltage));
        if(motorEncoderB_voltage == 0){
          motorEncoderB_SamplePeriodArray [motorEncoderB_SampleArrayindex] = millis()-encoderB_PrevTime;
          encoderB_PrevTime = millis();
          motorEncoderB_SampleArrayindex = (motorEncoderB_SampleArrayindex +1)%encoderSamples;
          if (motorEncoderB_SampleArrayindex == 0){
            //debugPrint(5, routineName, 5, String("average encode B period: ") + String(averageArray(motorEncoderB_SamplePeriodArray, encoderSamples)));
            //debugPrint(5, routineName, 5, String("encode B period: ") + String(motorEncoderB_SamplePeriodArray [motorEncoderB_SampleArrayindex]));
          }
        }
      }
};
