import processing.serial.*;

Serial myPort; 
int sensorValue = 0;

void setup() {
  size(600, 400);
  myPort = new Serial(this, "COM5", 115200);  // COM4  ESP32 port
}

void draw() {
  int bgColor = sensorValue / 16;  // 0-4095 to 0-255
  int xPos = int(map(sensorValue, 0, 4095, 0, width));  

  background(bgColor);
  fill(255 - bgColor, 100, 255);
  ellipse(xPos, height / 2, 50, 50);  // Moving circle
}

void serialEvent(Serial myPort) {
  String input = myPort.readStringUntil('\n');
  if (input != null) {
    sensorValue = int(trim(input));
  }
}
