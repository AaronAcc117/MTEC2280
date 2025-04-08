int potPin = 34;  //pin for potentiometer
int sensorValue = 0;

void setup() {
  Serial.begin(115200);  // serial
}

void loop() {
  sensorValue = analogRead(potPin);  // potentiometer value (0-4095)
  Serial.println(sensorValue);  // Send data to Processing 
  delay(50);  // delay
}
