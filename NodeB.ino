// C++ code

#include <Wire.h>

const byte MY_ADDRESS = 8;

void setup() {
  Wire.begin(MY_ADDRESS);  // Start I2C as slave
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("Slave started at address 8");
}

void loop() {
  // Received data is handled by receiveEvent()
  delay(10);
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    int receivedNumber = Wire.read();

    Serial.print("Received: ");
    Serial.println(receivedNumber);
  }
}
