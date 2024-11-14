#include <Arduino.h>

int channel_to_angle(int channel){
    int angle;
    channel < 1400 ? angle = map(channel, 1400, 1000, 0, -30):
    channel > 1600 ? angle = map(channel, 1600, 2000, 0, 30):
    angle = 0;

    return angle;
}