#include <Arduino.h>

struct PID
{
  int pwm1;
  int pwm2;
  int pwm3;
  int pwm4;
};

#define kp 1
#define kv 5
#define ki 0.01

float pitch_error;
float pitch_derivative;
float pitch_integral;
float pitch_previousError;

long pitch_previousTime = 0;
float pitch_dt;

int calculate_pitch_pid(float angle, int desire_angle){
  unsigned long pitch_currentTime = millis();
  pitch_dt = (pitch_currentTime - pitch_previousTime) / 1000.0;
  pitch_previousTime = pitch_currentTime;

  pitch_error = desire_angle - angle;
  pitch_integral += pitch_error * pitch_dt;
  pitch_derivative = (pitch_error - pitch_previousError) / pitch_dt;
  float output = (kp * pitch_error) + (ki * pitch_integral) + (kv * pitch_derivative);
  return output;  
}

float roll_error;
float roll_derivative;
float roll_integral;
float roll_previousError;

long roll_previousTime = 0;
float roll_dt;

int calculate_roll_pid(float angle, int desire_angle){
  unsigned long roll_currentTime = millis();
  roll_dt = (roll_currentTime - roll_previousTime) / 1000.0;
  roll_previousTime = roll_currentTime;

  roll_error = desire_angle - angle;
  roll_integral += roll_error * roll_dt;
  roll_derivative = (roll_error - roll_previousError) / roll_dt;
  float output = (kp * roll_error) + (ki * roll_integral) + (kv * roll_derivative);
  return output;  
}

int limit_pid(int pid){
  (pid > 400) ? pid = 400:
  (pid < -400) ? pid = -400:
  pid = pid;

  return pid;
}

int limit_pwm(int pwm){
  (pwm > 1900) ? pwm = 1900:
  (pwm < 1000) ? pwm = 1000:
  pwm = pwm;

  return pwm;
}

PID get_pwm(float pitch, float roll, float desire_pitch, float desire_roll, float throttle){
  int pitch_pid = limit_pid(calculate_pitch_pid(pitch, desire_pitch));
  int roll_pid = limit_pid(calculate_roll_pid(roll, desire_roll));

  int pwm1 = limit_pwm(throttle - pitch_pid - roll_pid);
  int pwm2 = limit_pwm(throttle - pitch_pid + roll_pid);
  int pwm3 = limit_pwm(throttle + pitch_pid + roll_pid);
  int pwm4 = limit_pwm(throttle + pitch_pid - roll_pid);

  return {pwm1, pwm2, pwm3, pwm4};
};