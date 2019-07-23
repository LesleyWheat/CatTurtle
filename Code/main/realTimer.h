//better description

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
