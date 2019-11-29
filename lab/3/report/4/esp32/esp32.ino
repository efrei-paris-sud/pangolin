#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
Adafruit_BME280 bme; // I2C

//BME280 definitions
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

//the variable of arduino A0 
int x = 0;

// Include the required Wire library for I2C<br>#include <Wire.h>
void setup(void) {
  Serial.begin(9600);
  
  //status for BME280
    unsigned status;

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }

   // default settings
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
    }
  // Start the I2C Bus as Master no address needed
  Wire.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("ok");
  }


void loop() {
 /* Take a new reading */
  mpu.read();
  delay(200);
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  /* Print out all values*/
  //Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
     //Serial.println(" c");
    Serial.print(" ");
    // Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 1000.0F);
   //  Serial.println(" hPa");
    Serial.print(" ");
       //  Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.print(" ");
      /* Print out the variable resisor values address IC2 12 */ 
    int available = Wire.requestFrom(12, 2);
  
  if(available == 2)
  {
    int receivedValue = Wire.read() << 8 | Wire.read(); 
    Serial.print(receivedValue);
  }

 
   Serial.print(" ");
    /* Print out the values MPE */
  Serial.print(a.acceleration.x);
  Serial.print(" ");
  Serial.print(a.acceleration.y);
  Serial.print(" ");
  Serial.print(a.acceleration.z);
  Serial.print("  ");
  Serial.print(g.gyro.x);
  Serial.print(" ");
  Serial.print(g.gyro.y);
  Serial.print(" ");
  Serial.print(g.gyro.z);
  Serial.println("");
  
    // Serial.print("Approx. Altitude = ");
    //Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    // Serial.println(" m");

}
