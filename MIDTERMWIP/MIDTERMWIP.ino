//Aaron Sanchez
// My Midterm Work In Progress 
//A Lamp using Potentiometer & Button with Arduino

// Pins 

#define LED1_PIN 5
#define LED2_PIN 10
#define LED3_PIN 11
#define BUTTON_PIN 2
#define POT_PIN 9

int buttonState = 0;
int lastButtonState = 0;
bool ledsOn = true;

void setup() {
  
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  
  pinMode(BUTTON_PIN, INPUT);

  
  Serial.begin(115200);
}

void loop() {
  //  the button state
  buttonState = digitalRead(BUTTON_PIN);

  // Check if the button is pressed
  if (buttonState == HIGH && lastButtonState == LOW) {
    // Toggle the LED state
    ledsOn = !ledsOn;
    delay(200); //delay
  }

  // Update the last button state
  lastButtonState = buttonState;

  // If LEDs are on, this adjusts brightness based on potentiometer
  if (ledsOn) {
    
    int potValue = analogRead(POT_PIN);

    
    int brightness = map(potValue, 0, 1023, 0, 255);

    // brightness for all LEDs
    analogWrite(LED1_PIN, brightness);
    analogWrite(LED2_PIN, brightness);
    analogWrite(LED3_PIN, brightness);
  } else {
    // Turn off the LEDs if they're supposed to be off
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW);
  }

  // Small delay for stability
  delay(10);
}
