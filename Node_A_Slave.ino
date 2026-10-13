#include <Wire.h>

#define TEMP_PIN A0
#define GAS_PIN A1
#define LDR1_PIN A2
#define LDR2_PIN A3 // Tumhara dusra photoresistor

unsigned long lastScanTime = 0;
const unsigned long scanInterval = 500;

// Struct ab 4 values hold karega
struct SensorData {
  float gasPPM;
  float tempC;
  float lux;
} payload;

void setup() {
  Serial.begin(9600);
  Wire.begin(8); // Node A address is 8
  Wire.onRequest(requestEvent); 
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastScanTime >= scanInterval) {
    lastScanTime = currentMillis;

    // Read and convert all 4 sensors
    int rawTemp = analogRead(TEMP_PIN);
    payload.tempC = (rawTemp * (5.0 / 1023.0) - 0.5) * 100.0;
    
    payload.gasPPM = analogRead(GAS_PIN);
    payload.lux2 = analogRead(LDR_PIN);

    // Print to Node A Serial Monitor
    Serial.print("Temp: "); Serial.print(payload.tempC);
    Serial.print(" | Gas: "); Serial.print(payload.gasPPM);
    Serial.print(" | LDR: "); Serial.println(payload.lux);
  }
}

void requestEvent() {
  Wire.write((byte*)&payload, sizeof(payload)); 
}