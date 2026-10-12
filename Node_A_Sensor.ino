#include <Wire.h>

#define GAS_PIN A0
#define TEMP_PIN A1
#define LDR_PIN A2

unsigned long lastScanTime = 0;
const unsigned long scanInterval = 500;

// Struct to hold sensor data for I2C binary payload transmission
struct SensorData {
  float gasPPM;
  float tempC;
  float lux;
} payload;

void setup() {
  Serial.begin(9600);
  
  // Configure Node A as I2C Slave on address 8
  Wire.begin(8);                
  Wire.onRequest(requestEvent); // Register event to send data when Master requests
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Non-blocking execution to prevent Tinkercad simulation lag
  if (currentMillis - lastScanTime >= scanInterval) {
    lastScanTime = currentMillis;

    // 1. TMP36 Temperature Conversion (10mV per degree with 500mV offset)
    int rawTemp = analogRead(TEMP_PIN);
    float voltageTemp = rawTemp * (5.0 / 1023.0);
    payload.tempC = (voltageTemp - 0.5) * 100.0;

    // 2. LDR Lux Estimation (Simplified proportional conversion)
    int rawLDR = analogRead(LDR_PIN);
    payload.lux = map(rawLDR, 0, 1023, 0, 10000);

    // 3. MQ-2 Gas PPM Estimation (Simplified proportional conversion)
    int rawGas = analogRead(GAS_PIN);
    payload.gasPPM = map(rawGas, 0, 1023, 200, 10000); 

    // Print for local serial debugging
    Serial.print("Temp (C): "); Serial.print(payload.tempC);
    Serial.print(" | Lux: "); Serial.print(payload.lux);
    Serial.print(" | Gas (PPM): "); Serial.println(payload.gasPPM);
  }
}

// Function executes whenever data is requested by Master (Node B)
void requestEvent() {
  // Serialize and send the byte representation of the struct payload over the I2C bus
  Wire.write((byte*)&payload, sizeof(payload)); 
}