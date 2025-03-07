const int LED1 = 7;  
const int LED2 = 6;  
const int LED3 = 5;  
const int LED4 = 4;  
const int buttonPin = 9;



int pattern = 0;       
int speed = 500;       
int buttonState = 0;   
int lastButtonState = 0; 


void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
}


void loop() {
  
  buttonState = digitalRead(buttonPin);


  
  if (buttonState == LOW && lastButtonState == HIGH) {
    pattern++;  // Move to the next pattern
    if (pattern >= 4) {
      pattern = 0; // Reset to the first pattern
    }
    delay(200); // Debounce delay to avoid multiple triggers
  }


  lastButtonState = buttonState; // Update last button


  //  different patterns
  if (pattern == 0) {
    // Pattern 1: Sequence pattern 
    digitalWrite(LED1, HIGH);
    delay(speed);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(speed);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    delay(speed);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    delay(speed);
    digitalWrite(LED4, LOW);
  }
  else if (pattern == 1) {
    // Alternates
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, HIGH);
    delay(speed);
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED4, HIGH);
    delay(speed);
    digitalWrite(LED2, LOW);
    digitalWrite(LED4, LOW);
  }
  else if (pattern == 2) {
    // They All Blink Together
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(speed);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(speed);
  }
  else {
    // next pattern
    for (int i = 7; i <= 4; i++) {
      digitalWrite(i, HIGH);
      delay(speed / 2);
      digitalWrite(i, LOW);
    }
    for (int i = 5; i >= 6; i--) {
      digitalWrite(i, HIGH);
      delay(speed / 2);
      digitalWrite(i, LOW);
    }
  }
}
