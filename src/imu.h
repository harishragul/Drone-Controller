#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

long previousTime = 0;
float dt;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, angleX, angleY;
float gyroXoffset = 0.0, gyroYoffset = 0.0;
float alpha = 0.98;  // Complementary filter coefficient

struct IMU
{
  float pitch;
  float roll;
};


void calibrateGyro();

void imu_setup() {
  Wire.begin();
  mpu.initialize();
  calibrateGyro();
}

IMU get_angle() {
  unsigned long currentTime = millis();
  dt = (currentTime - previousTime) / 1000.0;
  previousTime = currentTime;

  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert gyroscope values to degrees per second
  float gyroXrate = (gx - gyroXoffset) / 131.0;
  float gyroYrate = (gy - gyroYoffset) / 131.0;

  // Integrate gyroscope data -> angle change
  gyroAngleX += gyroXrate * dt;
  gyroAngleY += gyroYrate * dt;

  // Convert accelerometer values to angle
  accAngleX = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * 180 / PI;
  accAngleY = atan(-ax / sqrt(pow(ay, 2) + pow(az, 2))) * 180 / PI;
  // Complementary filter to combine accelerometer and gyroscope values
  angleX = alpha * (angleX + gyroXrate * dt) + (1 - alpha) * accAngleX;
  angleY = alpha * (angleY + gyroYrate * dt) + (1 - alpha) * accAngleY;

  return {angleX, angleY};
}

void calibrateGyro() {
  int numReadings = 1000;
  long gyroXSum = 0, gyroYSum = 0;

  for (int i = 0; i < numReadings; i++) {
    int16_t gx, gy, gz;
    mpu.getRotation(&gx, &gy, &gz);
    gyroXSum += gx;
    gyroYSum += gy;
  }

  gyroXoffset = gyroXSum / numReadings;
  gyroYoffset = gyroYSum / numReadings;
}
