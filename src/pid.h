#include <Arduino.h>

struct PID
{
  int pwm1;
  int pwm2;
  int pwm3;
  int pwm4;
};

float kp = 0, kv = 0, ki = 0;

PID calculate_pid(float pitch, float roll, int desire_pitch, int desire_roll, int throttle){
    
}