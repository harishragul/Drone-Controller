#include <Arduino.h>
#include "imu.h"
#include "rc.h"
#include "esc.h"
#include "mapping.h"

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
  Serial.print(channel_to_angle(channel.ch1));
  Serial.print("\t");
  Serial.print(channel_to_angle(channel.ch2));
  Serial.print("\t");
  Serial.print(channel.ch3);
  Serial.print("\t");
  Serial.println(channel_to_angle(channel.ch4));

  motor_pwm(channel.ch3, channel.ch3, channel.ch3, channel.ch3);
}