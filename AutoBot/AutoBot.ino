#include <Wire.h>

const int MPU6050_ADDR = 0x68; // MPU6050 I2C address

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to 0 (wakes up the MPU6050)
  Wire.endTransmission();
  
  Serial.println("MPU6050 initialized");
}

void loop() {
  // Read accelerometer data
  int16_t accelerometer[3];

  // Averaging over 10 samples
  for (int i = 0; i < 10; i++) {
    readSensorData(MPU6050_ADDR, 0x3B, accelerometer, 3);
    delay(10); // Add a small delay between readings
  }

  // Calculate average values
  for (int i = 0; i < 3; i++) {
    accelerometer[i] /= 10;
  }

  // Display data
  Serial.print("X: ");
  Serial.print(accelerometer[0]);
  Serial.print("\tY: ");
  Serial.print(accelerometer[1]);
  Serial.print("\tZ: ");
  Serial.println(accelerometer[2]);

  delay(100); // Adjust the delay based on your requirements
}

void readSensorData(int deviceAddress, byte regAddress, int16_t* data, int length) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.endTransmission(false);

  Wire.requestFrom(deviceAddress, length * 2, true);
  
  for (int i = 0; i < length; i++) {
    data[i] = Wire.read() << 8 | Wire.read();
  }
}
