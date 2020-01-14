#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6); //SIM900 Tx & Rx is connected to Arduino #5 & #6

//set pins for alcohol sensor
const int AOUTpin=0;
const int DOUTpin=8;
//set pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;
//sets pins for vibration sensor
const int AOUTvib=1;
const int DOUTvib=7;

const int ledPin=13;

//defines variables alcohol
int limit;
int value;
// defines variables ultrasonic
long duration;
int distance;
//defines variables vibrations
int motionDetected = HIGH;
int sensorVal = 0;



//sets input and output
void setup() {
  //pins alcohol
  pinMode(DOUTpin, INPUT);
  //pins ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //output LED
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);

  /*Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+COPS?"); //Check if it's connected to a network
  updateSerial();
  delay(5000);
  

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"33xxxxxxxxxx\"");//international phone number
  updateSerial();
  mySerial.print("Hello World !"); //text to send
  updateSerial();
  mySerial.write(26);*/
}

/*void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
}*/

void loop()
{
  //alcohol sensor code
  value= analogRead(AOUTpin);//reads the analaog value from AOUT pin
  limit= digitalRead(DOUTpin);//reads the digital value from DOUT pin
  Serial.print("Alcohol value: ");
  Serial.print(value);//prints the alcohol value
  Serial.print(" Limit: ");
  Serial.println(limit);//prints the limit reached as either LOW or HIGH
  delay(500);
  if (limit == LOW){
    digitalWrite(ledPin, HIGH);//if limit has been reached, LED turns on
  }
  else{
      digitalWrite(ledPin, LOW);//if threshold not reached, LED remains off
  }
  
  //====================================

  //Ultrasonic sensor code
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  pinMode(echoPin, INPUT);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(500);

  if(distance < 100){
    digitalWrite(ledPin, HIGH);//if a vehicle is too close, LED turns on
  }
  else{
      digitalWrite(ledPin, LOW);
  }

  //====================================

   motionDetected = digitalRead(DOUTvib);
   sensorVal = analogRead(AOUTvib);
   Serial.print("Vibration: ");
   Serial.print(sensorVal);
   Serial.print(" Digital :");
   Serial.println(motionDetected);
   delay(500);
   if(sensorVal < 1000){
    digitalWrite(ledPin, HIGH);
   }
   else{
      digitalWrite(ledPin, LOW);
  }
}
