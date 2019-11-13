int buzzer_pin = 12;

void setup()
{
    pinMode(buzzer_pin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available()>0)
    {
        int i  = Serial.parseInt();
        Serial.println(i, DEC);
        tone(buzzer_pin,i);
        
    }
}
