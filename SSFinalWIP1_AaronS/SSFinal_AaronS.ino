const int potPin = 1;       //  potentiometer
const int lightPin = 3;     //  photoresistor

void setup() {
  Serial.begin(115200);
}

void loop() {
  int potValue = analogRead(potPin);     
  int lightValue = analogRead(lightPin);

  
  potValue = potValue / 4;
  lightValue = lightValue / 4;

  Serial.print(potValue);
  Serial.print(",");
  Serial.println(lightValue);

  delay(50);
}
