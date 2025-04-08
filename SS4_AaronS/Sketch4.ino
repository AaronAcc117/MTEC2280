const int potXPin = 1;
const int potYPin = 2;
const int photoPin = 3;
const int buttonPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int potX = analogRead(potXPin);
  int potY = analogRead(potYPin);
  int light = analogRead(photoPin);
  int button = digitalRead(buttonPin);

  Serial.print(potX);
  Serial.print(",");
  Serial.print(potY);
  Serial.print(",");
  Serial.print(button);
  Serial.print(",");
  Serial.println(light);

  delay(50);
}
