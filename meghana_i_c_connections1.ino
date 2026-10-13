
#include <Wire.h>

const byte SLAVE_ADDRESS = 8;
int numberToSend = 0;

void setup() {
  Wire.begin();  // Start I2C as master
  Serial.begin(9600);
  Serial.println("Master started");
}

void loop() {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(numberToSend);
  byte error = Wire.endTransmission();

  Serial.print("Sent: ");
  Serial.print(numberToSend);

  if (error == 0) {
    Serial.println(" - delivered to slave");
  } else {
    Serial.println(" - transmission error");
  }

  numberToSend++;
  if (numberToSend > 100) {
    numberToSend = 0;
  }

  delay(1000);
}
