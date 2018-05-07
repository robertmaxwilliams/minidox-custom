
/* 

This programe polls out to some 
 rightHand is some legacy serial hardware that 
 spits out the following strings when a key is PRESSED:
012345678901
releasd: 1 3
pressed: 1 3
**Notice they are followed by a newline


glossary of terms:

polling: writing one line active while others are inactive (active low in this project)
reading: reading the other axis while one line is active

in case I forget:
HEIGHT is the number of horizontal ROWS
WIDTH is the number of vertical COLUMNS

this main polling loop is done with polling as outer, reading as inner.

the keymaps are char[HEIGHT][WIDTH] stored as KeyMap[row][column]


*/
#include <SoftwareSerial.h>
#include <Keyboard.h>
#include "KeyMap.h"

const int WIDTH = 5;
const int HEIGHT = 4;

// keyboard wires randomly plugged into pins 10 to 2
const int readingCount = WIDTH; // vertical wires
const int readingPins[readingCount] = {9, 2, 3, 6, 4};
const int pollingCount = HEIGHT; //horizontal wires
const int pollingPins[pollingCount] = {10, 8, 7, 5};

enum KeyState{PRESSED, RELEASED};
enum Side{LEFT, RIGHT};
enum Action{PRESS, RELEASE};

KeyState leftKeys[HEIGHT][WIDTH];
KeyState rightKeys[HEIGHT][WIDTH];

// extra keymapping for held keys.
KeyState* shiftKey = &leftKeys[3][0];
KeyState* specialKey = &leftKeys[3][1];
KeyState* controlKey = &leftKeys[3][2];
KeyState* altKey = &leftKeys[3][3];
KeyState* navKey = &rightKeys[3][3];

// rx and tx (only rx is used) from rightHand legacy hardware
SoftwareSerial rightHand(14, 15); // RX, TX

//struct to hold information about right hand's strings as
// they come in and are parsed
struct RightHandIncoming {
  int index = 0;
  int row;
  int column;
  KeyState keyState;
}; 

RightHandIncoming rightHandParser;

void setup() {
  Keyboard.begin();
  Serial.begin(9600);
  rightHand.begin(9600);

  for (int i = 0; i < readingCount; i++){
    pinMode(readingPins[i], INPUT);
    digitalWrite(readingPins[i], HIGH); // internal pullup
  }

  for (int i = 0; i < pollingCount; i++){
    pinMode(pollingPins[i], OUTPUT);
    digitalWrite(pollingPins[i], HIGH); // active low output
  }

}

void loop() {
  // sloppily implemented trampoline concurrency, if you can call it that
  // maybe I should write this in a real language #GreenspunsTenthRule

  // read in if any keys have been PRESSED on left (master) side
  // by turning on each column one by one, and reading in the rows
  for (int row = 0; row < HEIGHT; row++){
    digitalWrite(pollingPins[row], LOW);
    for (int column = 0; column < WIDTH; column++){
      KeyState lastState = leftKeys[row][column];
      KeyState curState = (digitalRead(readingPins[column]) == LOW) 
                                              ? PRESSED : RELEASED;

      if (curState == PRESSED && curState != lastState){
        keyboardPress(LEFT, row, column, PRESS);
      } else if (curState == RELEASED && curState != lastState){
        keyboardPress(LEFT, row, column, RELEASE);
      }

      leftKeys[row][column] = curState;
    }
    digitalWrite(pollingPins[row], HIGH);
  }

  // read character from rightHand, and increment lastCharIndex. 
  // on line ending, parse the buffer and reset it.
  // failures on overflow or failed parse.
  if (rightHand.available() > 0) {
    char incoming = rightHand.read();
    Serial.write(incoming);
    if (incoming == '\n') {
      // send keystroke and reset everything
      // bounds checking is for people who lack faith
      rightKeys[rightHandParser.row][rightHandParser.column] = rightHandParser.keyState;
      Action action = (rightHandParser.keyState == PRESSED) ? PRESS : RELEASE; // trsr code == readable code
      keyboardPress(RIGHT, rightHandParser.row, rightHandParser.column, action);
      rightHandParser.index = 0;
      // parse characters 2, 11, and 13
    } else if (rightHandParser.index == 1) {
      rightHandParser.keyState = (incoming == 'p') ? PRESSED : RELEASED;
    } else if (rightHandParser.index == 10) {
      rightHandParser.row = 3 - (incoming - '0'); // was upside down for some reason
    } else if (rightHandParser.index == 12) {
      rightHandParser.column = incoming - '0';
    }

    rightHandParser.index += 1;
  }
}

char findKey(Side side, int row, int column){
  // this is a failure. Flat would make so much sense, but then my data would
  // have to be nested. I need some sort of system of flags.
  char character;
  if (side == LEFT){
    if (*shiftKey == PRESSED){
      character = leftShiftKeyMap[row][column];
    } else if (*specialKey == PRESSED){
      character = leftSpecialKeyMap[row][column];
    } else if (*navKey == PRESSED){
      character = leftNavKeyMap[row][column];
    } else {
      character = leftKeyMap[row][column];
    }
  } else { // I sure hope side == RIGHT
    if (*shiftKey == PRESSED){
      character = rightShiftKeyMap[row][column];
    } else if (*specialKey == PRESSED){
      character = rightSpecialKeyMap[row][column];
    } else if (*navKey == PRESSED){
      character = rightNavKeyMap[row][column];
    } else {
      character = rightKeyMap[row][column];
    }
  }

  if (character != '\0'){
    return character;
  }

  // if character is still '\0', then "fall through" to 
  // control characrters
  if (side == LEFT){
    return leftModifiers[row][column];
  } else { //side == RIGHT
    return rightModifiers[row][column];
  }

}

void keyboardPress(Side side, int row, int column, Action action){
  // used global KeyState to determine shift and special
  char key = findKey(side, row, column);
  Serial.print(side);Serial.print(row);Serial.print(column);Serial.println(action);
  Serial.println(key);
  if (action == PRESS){
    Keyboard.press(key);
  } else { // action == RELEASE
    Keyboard.release(key);
  }
}
    
// notes on shift: it seems shift and upper/lowercase letters are independant, 
// so you could send shift+'a' or 'A'. I'm not sure how real keyboards do this
// but we'll see
