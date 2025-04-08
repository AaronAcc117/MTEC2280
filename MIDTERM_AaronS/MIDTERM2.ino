//Aaron Sanchez
// My Midterm Work In Progress 
// Not A lamp anymore but you still adjust brightness. A music sequence using 3 notes, LEDs match the sequence pattern and goes faster as you hold button

const int led1 = 15, led2 = 6, led3 = 7, buzzer = 9, button = 4, pot = 8;

void setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(button, INPUT_PULLUP);
}

void playTone(int frequency, int duration, int ledPin) {
    tone(buzzer, frequency, duration);   // Play the tone
    analogWrite(ledPin, 255);            // Turn on the LED with full brightness
    delay(duration);                     // Waits for the tone to play
    noTone(buzzer);                      // Stops the tone
    analogWrite(ledPin, 0);              // Turns off the LEDs
}

void loop() {
    int buttonState = digitalRead(button); 

    if (buttonState == LOW) {  // Button gets pressed
        int potValue = analogRead(pot);  
        int brightness = map(potValue, 0, 1023, 0, 255);

        // Adjust brightness of LEDs 
        analogWrite(led1, brightness);  // LED1 brightness
        analogWrite(led2, brightness);  // LED2 brightness
        analogWrite(led3, brightness);  // LED3 brightness

        // Play the tone with LEDs lighting up
        playTone(440, 300, led1);  
        playTone(494, 300, led2);  
        playTone(523, 300, led3);  
    }
    else {
        // When button is not pressed, turns off all LEDs
        analogWrite(led1, 0);
        analogWrite(led2, 0);
        analogWrite(led3, 0);
    }
}
