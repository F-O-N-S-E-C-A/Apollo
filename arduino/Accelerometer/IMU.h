#include <Wire.h>

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050
const float ACCELEROMETER_SENSITIVITY = 16384.0; // Sensitivity of the accelerometer
const float GYROSCOPE_SENSITIVITY = 131.0; // Sensitivity of the gyroscope

int16_t accelerometerX, accelerometerY, accelerometerZ;
int16_t gyroscopeX, gyroscopeY, gyroscopeZ;
float elapsedTime, currentTime, previousTime;
float filterConstant = 0.98; // Complementary filter constant
float roll = 0, pitch = 0; // Orientation angles
float gyroRoll = 0, gyroPitch = 0; // Gyroscope angles
float accelRoll = 0, accelPitch = 0; // Accelerometer angles
float rollFiltered = 0, pitchFiltered = 0; // Filtered angles
float dt; // Time interval
float translationX = 0, translationY = 0, translationZ = 0;

void setupIMU() {
  Wire.begin();        // Initialize I2C communication
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);    // PWR_MGMT_1 register
  Wire.write(0);       // Set to zero to activate the MPU-6050
  Wire.endTransmission(true);
  Serial.begin(9600);  // Initialize serial communication
}

void readAccelerometerData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);    // Starting register address for accelerometer data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);  // Request 6 bytes of data

  // Read the raw accelerometer data
  accelerometerX = Wire.read() << 8 | Wire.read();
  accelerometerY = Wire.read() << 8 | Wire.read();
  accelerometerZ = Wire.read() << 8 | Wire.read();
}

void readGyroscopeData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43);    // Starting register address for gyroscope data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);  // Request 6 bytes of data

  // Read the raw gyroscope data
  gyroscopeX = Wire.read() << 8 | Wire.read();
  gyroscopeY = Wire.read() << 8 | Wire.read();
  gyroscopeZ = Wire.read() << 8 | Wire.read();
}

void calculateOrientation() {
  // Convert raw accelerometer data to angles
  accelRoll = atan2(accelerometerY, accelerometerZ) * (180.0 / PI);
  accelPitch = atan(-accelerometerX / sqrt(accelerometerY * accelerometerY + accelerometerZ * accelerometerZ)) * (180.0 / PI);

  // Convert raw gyroscope data to angles
  elapsedTime = (currentTime - previousTime) / 1000.0; // Convert to seconds
  gyroRoll = gyroRoll + (gyroscopeX / GYROSCOPE_SENSITIVITY) * elapsedTime;
  gyroPitch = gyroPitch + (gyroscopeY / GYROSCOPE_SENSITIVITY) * elapsedTime;

  // Apply the complementary filter to combine accelerometer and gyroscope data
  roll = filterConstant * (roll + gyroRoll * elapsedTime) + (1 - filterConstant) * accelRoll;
  pitch = filterConstant * (pitch + gyroPitch * elapsedTime) + (1 - filterConstant) * accelPitch;

  // Store the current time for the next iteration
  previousTime = currentTime;
}


void printSensorData() {
  Serial.print("Accelerometer - X: ");
  Serial.print(accelerometerX);
  Serial.print("  Y: ");
  Serial.print(accelerometerY);
  Serial.print("  Z: ");
  Serial.println(accelerometerZ);

  Serial.print("Gyroscope - X: ");
  Serial.print(gyroscopeX);
  Serial.print("  Y: ");
  Serial.print(gyroscopeY);
  Serial.print("  Z: ");
  Serial.println(gyroscopeZ);

  Serial.print("Translation - X: ");
  Serial.print(translationX);
  Serial.print("  Y: ");
  Serial.print(translationY);
  Serial.print("  Z: ");
  Serial.println(translationZ);
}

void calculateTranslation(){
  // Calculate the time interval
  currentTime = millis();
  dt = (currentTime - previousTime) / 1000.0; // Convert to seconds

  // Read accelerometer and gyroscope data
  readAccelerometerData();
  readGyroscopeData();

  // Calculate the roll and pitch angles
  calculateOrientation();

  // Calculate translation using simple integration
  
  translationX = accelPitch * dt * dt;
  translationY = accelRoll * dt * dt;
  translationZ = (gyroscopeZ / GYROSCOPE_SENSITIVITY) * dt;

  // Store the current time for the next iteration
  previousTime = currentTime;
}


float* getTranslation() {
  float translation[3] = {0.0, 0.0, 0.0};
  translation[0] = translationX;
  translation[1] = translationY;
  translation[2] = translationZ;
  return translation;
}

