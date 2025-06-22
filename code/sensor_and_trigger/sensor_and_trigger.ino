#include <Wire.h>


#define MPU_ADDR 0x68  // MPU6050 I2C address
#define button 14

void setup() {
  Serial.begin(115200);
  Serial.println("Starting I2C communication with MPU6050...");
  
  pinMode(button, INPUT);
  Wire.begin(21, 22);  // SDA = 21, SCL = 22 for ESP32
  Serial.println("Wire.begin done ✅");

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Serial.print("Sending to register 0x6B (Power Management)... ");
  /*
  0x6B is the Power Management 1 register of MPU6050.
  We tell it: “Hey, we want to write something into your power control register.”
  */
  Wire.write(0x6B);
  Wire.write(0);  // Wake up command
  uint8_t status = Wire.endTransmission();
  Serial.print("I2C Transmission status: "); Serial.println(status == 0 ? "Success ✅" : "Failed ❌");

  delay(100);
}

void loop() {
  Serial.println("Requesting sensor data...");
  int buttonState = digitalRead(button);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // Start reading from register 0x3B
  Wire.endTransmission(false); // Restart for read
  
  Wire.requestFrom(MPU_ADDR, 14); // Read 14 bytes
  Serial.print("Bytes received: "); Serial.println(Wire.available());

  if (Wire.available() == 14) {
    uint8_t data[14];
    for (int i = 0; i < 14; i++) {
      data[i] = Wire.read();
    }

    // Now convert raw data to meaningful values
    int16_t ax = (data[0] << 8) | data[1];
    int16_t ay = (data[2] << 8) | data[3];
    int16_t az = (data[4] << 8) | data[5];

    Serial.println("✅ Sensor Values:");
    Serial.print("Accel X: "); Serial.println(ax);
    Serial.print("Accel Y: "); Serial.println(ay);
    Serial.print("Accel Z: "); Serial.println(az);

    float accX = ax / 16384.0; //scale factor for +-2g
    float accY = ay / 16384.0;
    float accZ = az / 16384.0;

    float totalAcc = sqrt(accX*accX + accY*accY + accZ*accZ);
    Serial.print("Total acceleration(g): ");
    Serial.println(totalAcc);

    if(totalAcc < 0.4){
      Serial.println("Possible Fall detected! Triggering alert ...");
    }
  } else {
    Serial.println("❌ Error: Did not receive expected 14 bytes.");
  }

  if(buttonState == HIGH){
    Serial.println("manual trigger pressed! Triggering alert ...");
    delay(1000); // debounce delay
  }

  Serial.println("------");
  delay(1000);  // Wait a second before next read
}
