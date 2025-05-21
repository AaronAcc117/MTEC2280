const int buttonPin = 4;
bool lastButtonState = HIGH;  // Assuming pull-up resistor, button unpressed = HIGH

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor
  Serial.begin(115200);
}

void loop() {
  bool currentState = digitalRead(buttonPin);
  
  // Detect button press (HIGH to LOW transition)
  if (lastButtonState == HIGH && currentState == LOW) {
    Serial.println("PRESSED");  // Send "PRESSED" message to Processing
    delay(50); // simple debounce
  }
  
  lastButtonState = currentState;
}
