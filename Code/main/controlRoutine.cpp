//better description

#include "arduino.h"
#include "realTimer.h"
#include "loggingFunctions.h"

class controlRoutine{
  private:
    int debugPrioritySetting;
    float batteryVoltage;
    String routineName = "cont";

    realTimer timerRampUp;
    byte left_setPWM;
    byte right_setPWM;
    byte left_currentPWM;
    byte right_currentPWM;
    byte testState = 0;
    realTimer timerTest;

    
    enum state{
      STANDBY = 0,
      TEST = 1
    }; 

    enum speed{
      SPEED_BRAKE = 0,
      SPEED_VERY_SLOW = 10,
      SPEED_SLOW = 25,
      SPEED_NORMAL = 40,
      SPEED_FAST = 60,
      SPEED_MAX = 100
    };

    enum direction{
      LEFT_MAX = 0,
      LEFT_HARD = 10,
      LEFT_SLIGHT = 40,
      STRAIGHT = 50,
      RIGHT_SLIGHT = 60,
      RIGHT_HARD = 90,
      RIGHT_MAX = 100
    };

    enum acceleration{
      ACCEL_MIN = 60,
      ACCEL_SLOW = 30,
      ACCEL_NORMAL = 10,
      ACCEL_FAST = 5,
      ACCEL_MAX = 2
    };

    void setMotor(byte spd, byte dir, int accelTime){
      //adebugPrint(5, routineName, 5, String("Motor set to: ") + String(spd));
      //Accel sets timer change rate
      int timerRate = (100/3.0*accelTime);
      timerRampUp.init(timerRate);
      
      //Speed sets motor PWM
      //Direction sets difference in wheel speed
      left_setPWM = (spd + (50-dir)*spd/50);
      right_setPWM = (spd + (50-(100-dir))*spd/50);
    };
    
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

      motorOptionPin1_PWM = (left_currentPWM*(255/100));
      motorOptionPin2_PWM = (right_currentPWM*(255/100));
    };
    
    void testStateMachine(){
      //
      if(timerTest.check(true)){
        //Next state
        testState = ((testState + 1)%5);

        //Set motor settings
        switch(testState){
          case 0:
            setMotor(SPEED_BRAKE, STRAIGHT, ACCEL_MIN);
            break;
          case 1:
            setMotor(SPEED_VERY_SLOW, STRAIGHT, ACCEL_MIN);
            break;
          case 2:
            setMotor(SPEED_SLOW, STRAIGHT, ACCEL_SLOW);
            break;
          case 3:
            setMotor(SPEED_NORMAL, STRAIGHT, ACCEL_NORMAL);
            break;
          case 4:
            setMotor(SPEED_VERY_SLOW, STRAIGHT, ACCEL_MIN);
            break;
          default:
            setMotor(SPEED_BRAKE, STRAIGHT, ACCEL_MIN);
        };
        
        debugPrint(5, routineName, 5, String("Test state: ") + String(testState));
        debugPrint(5, routineName, 5, String("Left speed running at: ") + String(motorOptionPin1_PWM));
        debugPrint(5, routineName, 5, String("Right speed running at: ") + String(motorOptionPin2_PWM));
        debugPrint(5, routineName, 5, String("Left set at running at: ") + String(left_setPWM));
        debugPrint(5, routineName, 5, String("Right set at running at: ") + String(right_setPWM));
      };
    };

    
  public:
    byte motorOptionPin1_PWM = 0;
    byte motorOptionPin2_PWM = 0;
    
    void init(int debugPrioritySetting){
      //Set local variables
      this->debugPrioritySetting=debugPrioritySetting;
  
      //Set starting variables
  
      //create objects
      timerTest.init(20000);
      
    };
  
    void run(float batteryVoltage){
      //Read inputs
      this->batteryVoltage=batteryVoltage;

      runMotor();
      testStateMachine();
    };
};
