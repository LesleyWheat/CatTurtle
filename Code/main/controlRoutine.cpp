//Control module

//Libraries
#include "arduino.h"
#include <AutoPID.h>

//local functions
#include "realTimer.h"
#include "loggingFunctions.h"

//pid settings and gains
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP 1
#define KI 1000
#define KD 0
    
//Class
class controlRoutine{
  private:
    //Set private variables
    int debugPrioritySetting;
    float batteryVoltage;
    double rpmA;
    double rpmB;
    String routineName = "cont";


    //Set variables for motor
    realTimer timerRampUp;
    byte left_setPWM;
    byte right_setPWM;
    int left_setRPM;
    int right_setRPM;
    byte left_currentPWM;
    byte right_currentPWM;

    double motorA_setRPM =0;
    double motorB_setRPM =0;
    double motorA_outPWM =0;
    double motorB_outPWM =0;
    byte testState = 0;
    realTimer timerTest;

    double temperature, setPoint, outputVal;
    //Set objects for pid controllers
    AutoPID *pidA;
    AutoPID *pidB;

    //Set objects for pid

    //Test state machine
    enum state{
      STANDBY = 0,
      TEST = 1
    }; 

    //Plain text settings for speed - needs calibration
    enum speed{
      SPEED_BRAKE = 0,
      SPEED_VERY_SLOW = 20,
      SPEED_SLOW = 25,
      SPEED_NORMAL = 40,
      SPEED_FAST = 60,
      SPEED_MAX = 100
    };

    //Plain text settings for direction - needs calibration
    enum direction{
      LEFT_MAX = 0,
      LEFT_HARD = 10,
      LEFT_SLIGHT = 40,
      STRAIGHT = 50,
      RIGHT_SLIGHT = 60,
      RIGHT_HARD = 90,
      RIGHT_MAX = 100
    };

    //Plain text settings for acceleration - needs calibration
    enum acceleration{
      ACCEL_MIN = 60,
      ACCEL_SLOW = 30,
      ACCEL_NORMAL = 10,
      ACCEL_FAST = 5,
      ACCEL_MAX = 2
    };

    //Set target motor values
    void setMotor(byte spd, byte dir, int accelTime){
      //debugPrint(5, routineName, 5, String("Motor set to: ") + String(spd));
      //Accel sets timer change rate
      int timerRate = (100/3.0*accelTime);
      timerRampUp.init(timerRate);
      
      //Speed sets motor PWM
      //Direction sets difference in wheel speed
      left_setPWM = (spd + (50-dir)*spd/50);
      right_setPWM = (spd + (50-(100-dir))*spd/50);
    };

    //Run motor controller to gradually reach target
    void runMotor(){
      if(timerRampUp.check(true)){
        left_currentPWM = left_currentPWM + (left_setPWM - left_currentPWM)/10 ;
        right_currentPWM = right_currentPWM + (right_setPWM - right_currentPWM)/10 ;
      
        if( (abs(left_setPWM-left_currentPWM) < 5) & (left_currentPWM > 5)){
          //debugPrint(5, routineName, 5, String("Left speed running at: ") + String(left_currentPWM));
        }
        if( (abs(right_setPWM-right_currentPWM) < 5) & (right_currentPWM > 5)){
          //debugPrint(5, routineName, 5, String("Right speed running at: ") + String(right_currentPWM));
        };
      };
      if((left_currentPWM < 20)& (left_currentPWM > 10) ){
        left_currentPWM = 20;
      }
      
      if((right_currentPWM < 20)& (right_currentPWM > 10) ){
        right_currentPWM = 20;
      }
      
      //Update PID controllers
      pidA->run();
      pidB->run();
      
      motorOptionPin1_PWM = (int)(left_currentPWM*(255.0/100));
      motorOptionPin2_PWM = (int)(right_currentPWM*(255.0/100));
    };

    //Set up tests to cycle through modes
    void testStateMachine(){
      //
      if(timerTest.check(true)){
        //Next state
        testState = ((testState + 1)%5);

        //Set motor settings
        switch(testState){
          case 0:
            setMotor(SPEED_FAST, STRAIGHT, ACCEL_NORMAL);
            break;
          case 1:
            setMotor(SPEED_BRAKE, STRAIGHT, ACCEL_NORMAL);
            break;
          case 2:
            setMotor(SPEED_FAST, STRAIGHT, ACCEL_NORMAL);
            break;
          case 3:
            setMotor(SPEED_SLOW, STRAIGHT, ACCEL_NORMAL);
            break;
          case 4:
            setMotor(SPEED_SLOW, STRAIGHT, ACCEL_MIN);
            break;
          default:
            setMotor(SPEED_BRAKE, STRAIGHT, ACCEL_MIN);
        };
        
        debugPrint(5, routineName, 5, String("Test state: ") + String(testState));
        debugPrint(5, routineName, 5, String("Left speed running at: ") + String(motorOptionPin1_PWM/255.0*100));
        debugPrint(5, routineName, 5, String("Right speed running at: ") + String(motorOptionPin2_PWM/255.0*100));
        debugPrint(5, routineName, 5, String("Left set at running at: ") + String(left_setPWM));
        debugPrint(5, routineName, 5, String("Right set at running at: ") + String(right_setPWM));
      };
    };

    
  public:
    //set public variables
    byte motorOptionPin1_PWM = 0;
    byte motorOptionPin2_PWM = 0;
    
    void init(int debugPrioritySetting){
      //Set local variables
      this->debugPrioritySetting=debugPrioritySetting;
  
      //Set starting variables
      pidA = new AutoPID(&rpmA, &motorA_setRPM, &motorA_outPWM, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
      pidB = new AutoPID(&rpmB, &motorA_setRPM, &motorB_outPWM, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

  
      //create objects
      timerTest.init(20000);
      
    };

    //Runs in main loop
    void run(float batteryVoltage, double rpmA, double rpmB){
      //Read inputs
      this->batteryVoltage=batteryVoltage;
      this->rpmA=rpmA;
      this->rpmB=rpmB;

      //Update state
      //runMotor();
      //testStateMachine();

      motorA_setRPM = 20;
      motorB_setRPM = 30;
      
      //Update PID controllers
      pidA->run();
      pidB->run();

      debugPrint(5, routineName, 5, String("rpmA: ") + String(rpmA) + String(" rpmA set: ") + String(motorA_outPWM));

      motorOptionPin1_PWM = (byte) motorA_outPWM;
      motorOptionPin2_PWM = (byte) motorB_outPWM;
    };
};
