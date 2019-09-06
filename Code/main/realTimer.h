//Creates a timer that operates on a real time check based on the arduino internal clock
//Used as an alarm or to create time based loops
//Could have over flow issues if runtime is too long

#ifndef REAL_TIMER_H
#define REAL_TIMER_H

class realTimer{
  private:
    double accum;
    double lastCheck;
    double enable;
    double targetTime;
    
  public:
    void init(double setTime);
    bool check(bool condition);
};

#endif // REAL_TIMER_H
