const int LED1 = 1; //13
const int LED2 = 2; //12
const int LED3 = 3; //11
const int LED4 = 4; //10

// Declare variables
int pattern = 0;      
int brightness = 255;
int speed = 500;      // Delay time

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  if (pattern >= 4) {
    pattern = 0; // Reset pattern after 4 times
  }

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
    // Pattern 2: Alternating pattern
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
    // Pattern 3: They Blink Together
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
    for (int i = 1; i <= 4; i++) {
  digitalWrite(i, HIGH);
  delay(speed / 2);
  digitalWrite(i, LOW);
}
for (int i = 4; i >= 1; i--) {
  digitalWrite(i, HIGH);
  delay(speed / 2);
  digitalWrite(i, LOW);
}

  pattern++; 
  delay(speed); 
}


