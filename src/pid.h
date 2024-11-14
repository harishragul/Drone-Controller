#include <Arduino.h>

struct PID
{
  int pwm1;
  int pwm2;
  int pwm3;
  int pwm4;
};

float kp = 0, kv = 0, ki = 0;

float error;
float derivative;
float integral;
float previousError;

long previousTime = 0;
float dt;

int calculate_pid(float angle, int desire_angle){
  unsigned long currentTime = millis();
  dt = (currentTime - previousTime) / 1000.0;
  previousTime = currentTime;

  error = desire_angle - angle;
  integral += error * dt;
  derivative = (error - previousError) / dt;
  float output = (kp * error) + (ki * integral) + (kv * derivative);
  return output;  
}


void get_pwm(float pitch, float roll, float desire_pitch, float desire_roll, float throttle){
  float pitch_pid = calculate_pid(pitch, desire_pitch);
  float roll_pid = calculate_pid(roll, desire_roll);
};