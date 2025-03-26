//Aaron Sanchez
// My Midterm Work In Progress 
//A Lamp using Potentiometer

const int led1 = 15, led2 = 6, led3 = 7, buzzer = 9, button = 4, pot = 8;

void setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(button, INPUT_PULLUP);
}

void playTone(int frequency, int duration) {
    tone(buzzer, frequency, duration);
    delay(duration);
}

void loop() {
    int brightness = analogRead(pot) / 16;
    digitalWrite(led1, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    delay(200);
    digitalWrite(led3, LOW);
    
    playTone(440, 300);
    playTone(494, 300);
    playTone(523, 300);
}
