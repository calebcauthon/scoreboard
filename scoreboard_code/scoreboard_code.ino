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

char message[BUF_SIZE] = "Hello!";
bool newMessageAvailable = true;

const int buttonPinLeft = 2;
const int buttonPinRight = 3;

ButtonState leftUpButton;
ButtonState leftDownButton;
ButtonState rightUpButton;
ButtonState rightDownButton;
GoaltyGame game;

void playUpSound() {
  Serial.println("Sound!");
  // tone(8, NOTE_C4, 1000 / 4);
  // delay(100);
  // tone(8, NOTE_C5, 1000 / 4);
  // delay(100);
  // noTone(8);
}

void increaseLeftScore() {
  game.increaseLeft();
  playUpSound();
  displayCurrentScore();
}

void decreaseLeftScore() {
  game.decreaseLeft();
  displayCurrentScore();
}

void increaseRightScore() {
  game.increaseLeft();
  displayCurrentScore();
}

void decreaseRightScore() {
  game.decreaseRight();
  displayCurrentScore();
}

void displayCurrentScore() {
  displayStringOnDisplay(String(game.leftScore) + "-" + String(game.rightScore));
}

void displayStringOnDisplay(String text) {
  char scoreMessage[BUF_SIZE] = "";
  strcpy(scoreMessage, text.c_str());
  printText(0, MAX_DEVICES-1, scoreMessage);
}

void loop()
{
  leftUpButton.buttonPin = 2;
  leftUpButton.onPress(increaseLeftScore);
  leftUpButton.tick();

  leftDownButton.buttonPin = 5;
  leftDownButton.onPress(decreaseLeftScore);
  leftDownButton.tick();

  rightUpButton.buttonPin = 4;
  rightUpButton.onPress(increaseRightScore);
  rightUpButton.tick();

  rightDownButton.buttonPin = 3;
  rightDownButton.onPress(decreaseRightScore);
  rightDownButton.tick();
}

void setup()
{
  mx.begin();

  char scoreMessage[BUF_SIZE] = "0-0";
  printText(0, MAX_DEVICES-1, scoreMessage);
  Serial.begin(9600);
}
