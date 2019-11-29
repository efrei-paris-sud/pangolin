# Report Lab 4

### Photo

![Photo](photo.png?raw=true)

### Analyse

First we assign the ESP32 as the master.
The Arduino is designed as the slave, adressed at  '12'.

We create an I2C connection between :
- ESP32
- Arduino
- MPU6050
- BME280

The Arduino will read the analog answer of the variable resistor via A0 input

We can't send more than one byte with I2C so we created a buffer to send the integer value on 2 bytes.

```sh
  uint8_t buffer[2];
  buffer[0] = sensorValue >> 8;
  buffer[1] = sensorValue & 0xff;
```

Once done, we print all captors status on the console as previously.