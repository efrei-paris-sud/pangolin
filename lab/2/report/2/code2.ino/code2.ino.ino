const int LDR = A0;
int valeur = 0;

void setup() {

  pinMode(LDR, INPUT); 
  Serial.begin(9600); 
}

void loop() {

  valeur = analogRead(LDR);

  Serial.print("Valeur LDR = ");
  Serial.print(valeur);
  Serial.print("   ");
  Serial.println("");
  delay(200);
}
