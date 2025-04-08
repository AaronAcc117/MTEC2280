import processing.serial.*;

Serial myPort;
int xVal, yVal, buttonVal, lightVal;
boolean useColor = false;

void setup() {
  size(600, 400);
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  background((int)map(lightVal, 0, 4095, 0, 255));

  if (useColor) {
    fill(0, 255, 0);
  } else {
    fill(255, 0, 0);
  }

  int x = (int)map(xVal, 0, 4095, 0, width);
  int y = (int)map(yVal, 0, 4095, 0, height);

  ellipse(x, y, 50, 50);
  rect(x, y, 30, 30);
  line(x, y, width, height);
}

void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n');
  if (data != null) {
    String[] parts = split(trim(data), ",");
    if (parts.length == 4) {
      xVal = int(parts[0]);
      yVal = int(parts[1]);
      buttonVal = int(parts[2]);
      lightVal = int(parts[3]);
      if (buttonVal == 0) {
        useColor = !useColor;
      }
    }
  }
}
