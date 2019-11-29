#include <Wire.h>

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // Start the I2C Bus as Slave on address 12
  Wire.begin(12);
  Serial.println("Ok"); 
  Wire.onRequest(requestEvent);
}

// the loop routine runs over and over again forever:
void loop() {
  delay(100);        
}

  void requestEvent() {
   int sensorValue = analogRead(A0);

  uint8_t buffer[2];
  buffer[0] = sensorValue >> 8;
  buffer[1] = sensorValue & 0xff;
  Wire.write(buffer, 2);
  // print out the value you read:
  byte lowbyte = sensorValue & 0xFF;
  byte highbyte = sensorValue >> 8;
  Serial.println(sensorValue);
  
  // respond with message of 1 bytes
  // as expected by master
}
