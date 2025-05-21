/*
  Button Reaction Game
  Aaron Sanchez

    How you play :
  - This game has 5 levels of increasing button challenges:
    1) Simple reaction to red circle cue
    2) Double tap quickly after cue
    3) Press after a target delay shown on screen
    4) Fake-out: press only if "GO!" shown; don't press if "DON'T PRESS!"
    5) Rapid tap: press button as many times as possible in 3 seconds
  - Use your button (connected via serial) to interact.
  - Press button to start at instructions screen.
  - After winning, press button to restart and see instructions again.

  References:
  - Processing Serial Library Documentation: https://processing.org/reference/libraries/serial/index.html
  - Processing Delay() function usage: https://processing.org/reference/delay_.html
  - Basic Game Loop structure from Processing tutorials: https://processing.org/tutorials/pixels/
  - ChatGPT AI   helped with some  logic and debugging suggestions
*/

import processing.serial.*;

Serial myPort;

// Game variables
boolean cueShown = false;  // Indicates if the cue (red circle) is currently displayed
int cueTime;               // Timestamp when the cue appeared (used for timing reaction)
int score = 0;             // Player's cumulative score
String message = "";       // Message feedback shown on screen to player

int level = 1;             // Tracks current game level

// Level 2: Double tap variables
int firstTapTime = 0;
boolean waitingForSecondTap = false;

// Level 3: Timed press variables
int targetDelay = 0;
boolean level3Waiting = false;

// Level 4: Fake-out press variables
boolean level4Go = false;      // True if cue says "GO!", false if "DON'T PRESS!"
boolean level4Active = false;  // Is level 4 cue active and waiting for input?
boolean level4Resolved = false; // Has player responded to level 4 cue?

// Level 5: Rapid tap variables
int pressCount = 0;
int level5StartTime = 0;
boolean level5Active = false;

// Game state flags
boolean gameOver = false;      // True if game has been completed
boolean showInstructions = true; // Show instructions on start/reset

// Fonts and blinking timer for effects
PFont titleFont;
int blinkTimer = 0;
boolean blinkOn = true;

void setup() {
  size(400, 300);
  textAlign(CENTER, CENTER);
  textSize(24);

  
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 115200);
  myPort.clear();

  titleFont = createFont("Arial Black", 40);
}

void draw() {
  background(0);

  if (showInstructions) {
    fill(255);
    textSize(20);
    text("BUTTON REACTION GAME\n\n" +
         "Levels 1-5: React, double tap, timed press,\n" +
         "fake-out, and rapid taps.\n\n" +
         "Press the BUTTON to start!", width / 2, height / 2);
    return;
  }

  if (gameOver) {
    fill(255, 215, 0);
    textFont(titleFont);
    textSize(36);
    text("YOU ARE NOW A", width / 2, height / 2 - 30);
    text("BUTTON EXPERT", width / 2, height / 2 + 30);

    if (millis() - blinkTimer > 500) {
      blinkOn = !blinkOn;
      blinkTimer = millis();
    }
    if (blinkOn) {
      textSize(16);
      fill(200);
      text("Press the button to restart", width / 2, height - 40);
    }
    return;
  }

  fill(255);
  textFont(createFont("Arial", 24));
  text("Score: " + score, width / 2, 30);
  text("Level: " + level, width / 2, 60);
  text(message, width / 2, height - 40);

  // Show the red cue circle in ALL levels while cueShown is true
  if (cueShown) {
    fill(255, 0, 0);
    ellipse(width / 2, height / 2, 100, 100);
  }

  // Level 3 instruction text when waiting for timed press
  if (level == 3 && cueShown && level3Waiting) {
    textSize(18);
    fill(255);
    text("Press AFTER " + nf(targetDelay / 1000.0, 1, 2) + " seconds", width / 2, height / 2 + 80);
  }

  // Level 4 fake-out cue text
  if (level == 4 && cueShown && level4Active) {
    textSize(18);
    fill(255);
    text(level4Go ? "GO!" : "DON'T PRESS!", width / 2, height / 2 + 80);
  }

  // Level 5 rapid tap countdown and press count
  if (level == 5 && level5Active) {
    int timeLeft = 3000 - (millis() - level5StartTime);
    if (timeLeft <= 0) {
      level5Active = false;
      cueShown = false;
      message = "Time's up! Presses: " + pressCount;
      score += pressCount * 100;
      delay(1500);
      gameOver = true;
    } else {
      textSize(18);
      fill(255);
      text("Time left: " + nf(timeLeft / 1000.0, 1, 2), width / 2, height / 2 + 80);
      text("Press count: " + pressCount, width / 2, height / 2 + 110);
    }
  }

  // Level 4 timeout for fake-out if player didn't press
  if (level == 4 && level4Active && !level4Resolved && millis() - cueTime > 1500) {
    cueShown = false;
    level4Resolved = true;
    if (level4Go) {
      message = "Too slow! Missed the GO!";
    } else {
      message = "Nice! You didn’t press!";
      score += 500;
    }
    delay(1500);
    level = 5;
    startCue();
  }
}

void serialEvent(Serial port) {
  String input = port.readStringUntil('\n');
  if (input != null) {
    input = trim(input);

    // Starts my  game from instructions screen
    if (showInstructions && input.equals("PRESSED")) {
      showInstructions = false;
      score = 0;
      level = 1;
      message = "";
      startCue();
      return;
    }

    // Restart after game over
    if (gameOver && input.equals("PRESSED")) {
      score = 0;
      level = 1;
      gameOver = false;
      message = "";
      showInstructions = true; // Show instructions again
      return;
    }

    if (cueShown && input.equals("PRESSED")) {
      if (level == 1) {
        int reaction = millis() - cueTime;
        score += max(0, 1000 - reaction);
        message = "Reaction: " + reaction + " ms";
        cueShown = false;
        delay(1000);
        level = 2;
        startCue();

      } else if (level == 2) {
        if (!waitingForSecondTap) {
          firstTapTime = millis();
          waitingForSecondTap = true;
          message = "Tap again quickly!";
        } else {
          int interval = millis() - firstTapTime;
          if (interval <= 500) {
            score += 1000 - interval;
            message = "Double tap! Interval: " + interval + " ms";
            waitingForSecondTap = false;
            cueShown = false;
            delay(1000);
            level = 3;
            startCue();
          } else {
            message = "Too slow!";
            waitingForSecondTap = false;
          }
        }

      } else if (level == 3) {
        int elapsed = millis() - cueTime;
        if (elapsed >= targetDelay) {
          score += 500;
          message = "Good timing! +" + 500;
          cueShown = false;
          level3Waiting = false;
          delay(1000);
          level = 4;
          startCue();
        } else {
          message = "Too early! Wait for it...";
        }

      } else if (level == 4 && level4Active && !level4Resolved) {
        if (level4Go) {
          score += 1000;
          message = "Correct GO press!";
        } else {
          message = "Wrong! You pressed!";
        }
        level4Resolved = true;
        cueShown = false;
        delay(1000);
        level = 5;
        startCue();

      } else if (level == 5 && level5Active) {
        pressCount++;
      }
    }
  }
}

void startCue() {
  delay(int(random(2000, 4000)));

  // Reset all level-specific flags
  waitingForSecondTap = false;
  level3Waiting = false;
  level4Active = false;
  level4Resolved = false;
  level5Active = false;

  // Show cue circle for all levels (including 5)
  cueShown = true;

  cueTime = millis();

  if (level == 3) {
    targetDelay = int(random(1000, 2500));
    level3Waiting = true;
  }

  if (level == 4) {
    level4Active = true;
    level4Go = random(1) < 0.5;
  }

  if (level == 5) {
    pressCount = 0;
    level5StartTime = millis();
    level5Active = true;
  }
}
