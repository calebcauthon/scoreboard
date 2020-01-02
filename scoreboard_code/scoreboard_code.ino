// Use the MD_MAX72XX library to Print some text on the display
//
// Demonstrates the use of the library to print text.
//
// User can enter text on the serial monitor and this will display as a
// message on the display.

#include <MD_MAX72xx.h>
#include <SPI.h>
#include "pitches.h"
#include "GoaltyGame.h"
#include "ButtonState.h"
#include "printText.h"
#include "playSounds.h"

char message[BUF_SIZE] = "Hello!";
bool newMessageAvailable = true;

const int buttonPinLeft = 2;
const int buttonPinRight = 3;
int timeOfReset = 0;

ButtonState leftUpButton;
ButtonState leftDownButton;
ButtonState rightUpButton;
ButtonState rightDownButton;
ButtonState onOffButton;
GoaltyGame game;

void increaseLeftScore() {
  game.increaseLeft();
  displayCurrentScore();
}

void decreaseLeftScore() {
  game.decreaseLeft();
  displayCurrentScore();
}

void increaseRightScore() {
  game.increaseRight();
  displayCurrentScore();
}

void decreaseRightScore() {
  game.decreaseRight();
  displayCurrentScore();
}

void displayCurrentScore() {
  displayStringOnDisplay("  " + String(game.leftScore) + " - " + String(game.rightScore));
}

void displayStringOnDisplay(String text) {
  char scoreMessage[BUF_SIZE] = "";
  strcpy(scoreMessage, text.c_str());
  printText(0, MAX_DEVICES-1, scoreMessage);
}

bool endGameLoop = false;
void loop()
{

  if (endGameLoop) {
    playEndGameSound();
    endGameLoop = false;
  }

  if (millis() > timeOfReset && timeOfReset > 0) {
    Serial.println("RESET COMPLETE");
    timeOfReset = 0;
  } else if (timeOfReset > 0) {
    Serial.println("bail because of the reset");
    return;
  }

  onOffButton.tick();
  rightDownButton.tick();
  rightUpButton.tick();
  leftDownButton.tick();
  leftUpButton.tick();

  // Serial.println(String(digitalRead(2)) + " " + String(digitalRead(3)) + " " + String(digitalRead(4)) + " " + String(digitalRead(5)));
  if (leftUpButton.wasButtonPressed && rightUpButton.wasButtonPressed) {
    resetGame();
  }

  delay(25);
}

void onGameOver() {
  endGameLoop = true;
}

void resetGame() {
  game.reset();
  displayCurrentScore();

  timeOfReset = millis() + 2000;

  rightDownButton.reset();
  rightUpButton.reset();
  leftDownButton.reset();
  leftUpButton.reset();

  Serial.println("RESET START");
}

void setup()
{
  mx.begin();

  char scoreMessage[BUF_SIZE] = "  0 - 0";
  printText(0, MAX_DEVICES-1, scoreMessage);
  Serial.begin(9600);

  game.onGameOver(onGameOver);
  game.onScoreIncrease(playUpSound);

  leftUpButton.setPin(2);
  leftUpButton.onPress(increaseLeftScore);

  leftDownButton.setPin(3);
  leftDownButton.onPress(decreaseLeftScore);

  rightDownButton.setPin(4);
  rightDownButton.onPress(decreaseRightScore);

  rightUpButton.setPin(5);
  rightUpButton.onPress(increaseRightScore);
}
