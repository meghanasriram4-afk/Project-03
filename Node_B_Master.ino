#include <Wire.h>

// Struct MUST exactly match Node A
struct SensorData {
  float gasPPM;
  float tempC;
  float lux1;
  float lux2;
} payload;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Master needs no address
  Serial.println("Node B Master Initialized. Requesting I2C data...");
}

void loop() {
  // Request exact payload size from Slave (address 8)
  Wire.requestFrom(8, sizeof(payload));

  // Check if full struct was received
  if (Wire.available() == sizeof(payload)) {
    Wire.readBytes((byte*)&payload, sizeof(payload));

    // Print to Node B Serial Monitor to prove I2C works
    Serial.print("RECEIVED -> Temp: "); Serial.print(payload.tempC);
    Serial.print(" | Gas: "); Serial.print(payload.gasPPM);
    Serial.print(" | LDR1: "); Serial.print(payload.lux1);
    Serial.print(" | LDR2: "); Serial.println(payload.lux2);
  }
  delay(1000); 
}