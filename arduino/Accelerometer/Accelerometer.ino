#include "IMU.h"

void setup() {
  setupIMU();  // Initialize the MPU-6050 sensor
  // Additional setup code
}

void loop() {
  //readAccelerometerData();  // Read accelerometer data
  //readGyroscopeData();      // Read gyroscope data
  calculateTranslation();
  //printSensorData();        // Print sensor data
  float* translation = getTranslation();
  Serial.print(translation[0]);
  Serial.print(",");
  Serial.print(translation[1]);
  Serial.print(",");
  Serial.println(translation[2]);
  delay(500);
  // Additional code
}
