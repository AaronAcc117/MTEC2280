//Aaron Sanchez
// My Midterm Work In Progress 
//A Lamp using Potentiometer & Button with Arduino

// Pins 
const int potPin = A0;       // Potentiometer Input
const int buttonPin = 2;     // Button Input
const int ledPin = 9;        // PWM LED Output
const int buzzerPin = 3;     // Buzzer Output
const int redPin = 5, greenPin = 10, bluePin = 11;  LED

// Variables I need
int potValue = 0;
int brightness = 0;
int buttonState = 0;
int lastButtonState = 0;
bool mode = 0;  
unsigned long lastDebounceTime = 0; // Stores last time button state changed and there is delay
const long debounceDelay = 50;

// Red green and blue Colors array 
int colors[][3] = {
    {255, 0, 0},   // Red
    {0, 255, 0},   // Green
    {0, 0, 255},   // Blue
    {255, 0, 0},   // Red
    {0, 255, 0},   // Green
    {0, 0, 255}    // Blue
};
int colorIndex = 0;


void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // Reads the  potentiometer value and maps  brightness
    potValue = analogRead(potPin);
    brightness = map(potValue, 0, 1023, 0, 255);
    analogWrite(ledPin, brightness);

    // Button 
    int reading = digitalRead(buttonPin);
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading == LOW && buttonState == HIGH) {
            mode = !mode;
            digitalWrite(buzzerPin, HIGH);
            delay(100);
            digitalWrite(buzzerPin, LOW);
        }
    }
    buttonState = reading;

    // The LED Lighting 
    if (mode == 0) {
        analogWrite(redPin, brightness);
        analogWrite(greenPin, brightness);
        analogWrite(bluePin, brightness);
    } else {
        colorIndex = (millis() / 1000) % 6;
        analogWrite(redPin, colors[colorIndex][0]);
        analogWrite(greenPin, colors[colorIndex][1]);
        analogWrite(bluePin, colors[colorIndex][2]);
    }
    
    lastButtonState = reading;
}
