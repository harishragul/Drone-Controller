#include <Arduino.h>

#define pin1 2
#define pin2 4
#define pin3 12
#define pin4 13

struct RC
{
  int ch1;
  int ch2;
  int ch3;
  int ch4; 
};

void rc_setup() {
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
}

RC get_channel() {
    if (!pulseIn(pin3, HIGH)) {
        return{1500, 1500, 1000, 1500};
    } else {
        return{
            pulseIn(pin1, HIGH), 
            pulseIn(pin2, HIGH),
            pulseIn(pin3, HIGH),
            pulseIn(pin4, HIGH)
        };
    }
}