#include <Arduino.h>
#include "imu.h"
#include "rc.h"
#include "esc.h"
#include "mapping.h"
#include "pid.h"
#include "onoff.h"

void setup(){
  Serial.begin(9600);
  imu_setup();
  rc_setup();
  esc_setup();
}

void loop(){
  IMU angle = get_angle();
  RC channel = get_channel();


  Serial.print(angle.pitch);
  Serial.print("\t");
  Serial.print(angle.roll);
  Serial.print("\t");

  Serial.print(channel.ch3);
  Serial.print("\t");

  Serial.print(channel.ch4);
  Serial.println("\t");

  /*if (onoff(channel.ch3, channel.ch4)){
    PID pid = get_pwm(angle.pitch, angle.roll, -channel_to_angle(channel.ch2), -channel_to_angle(channel.ch1), channel.ch3);
    motor_pwm(pid.pwm1, pid.pwm2, pid.pwm3, pid.pwm4);
    Serial.println("1");
  } else {
    motor_pwm(1000, 1000, 1000, 1000);
    Serial.println("0");
  }*/
}