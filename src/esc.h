#include<Arduino.h>
#include<Servo.h>

Servo motor1, motor2, motor3, motor4;

void esc_setup(){
  motor1.attach(3);
  motor2.attach(5);
  motor3.attach(6);
  motor4.attach(9);

  motor1.writeMicroseconds(1000);
  motor2.writeMicroseconds(1000);
  motor3.writeMicroseconds(1000);
  motor4.writeMicroseconds(1000);
}

void motor_pwm(int pwm1, int pwm2, int pwm3, int pwm4){
  motor1.writeMicroseconds(pwm1);
  motor2.writeMicroseconds(pwm2);
  motor3.writeMicroseconds(pwm3);
  motor4.writeMicroseconds(pwm4);
}