
#include <Attitude_MPU9250.h>
#include <FaBo9Axis_MPU9250.h>
#include <Wire.h>

AttitudeBasic attitude;
FaBo9Axis fabo_9axis;
void setup() {
  Serial.begin(9600);
  Serial.println("RESET");
  Serial.println();

  Serial.println("configuring device.");

  if (fabo_9axis.begin()) {
    Serial.println("configured FaBo 9Axis I2C Brick");
  } else {
    Serial.println("device error");
    while(1);
  }
}

void loop() {
  float acc[3];
  float gyro[3];
  float mag[3];
  float euler[3];
 

  fabo_9axis.readAccelXYZ(&acc[0],&acc[1],&acc[2]);
  fabo_9axis.readGyroXYZ(&gyro[0],&gyro[1],&gyro[2]);
  fabo_9axis.readMagnetXYZ(&mag[0],&mag[1],&mag[2]);

    Serial.print("ax: ");
  Serial.print(acc[0]);
  Serial.print(" acc[1]: ");
  Serial.print(acc[1]);
  Serial.print(" acc[2]: ");
  Serial.println(acc[2]);

  Serial.print("gyro[0]: ");
  Serial.print(gyro[0]);
  Serial.print(" gyro[1]: ");
  Serial.print(gyro[1]);
  Serial.print(" gyro[2]: ");
  Serial.println(gyro[2]);

  Serial.print("mag[0]: ");
  Serial.print(mag[0]);
  Serial.print(" mag[1]: ");
  Serial.print(mag[1]);
  Serial.print(" mag[2]: ");
  Serial.println(mag[2]);

  attitude.getAttitude(acc,mag,euler);
  delay(2000);
}
