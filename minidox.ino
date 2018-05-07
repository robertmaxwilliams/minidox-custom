
/* 

This programe polls out to some 
 rightHand is some legacy serial hardware that 
 spits out the following strings when a key is PRESSED:
releasd: 1 3
PRESSED: 1 3
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

enum KeyState{PRESSED, RELEASEED};
enum Side{LEFT, RIGHT};
enum Action{PRESS, RELEASE};

KeyState leftKeys[HEIGHT][WIDTH];
KeyState rightKeys[HEIGHT][WIDTH];

// extra keymapping for held keys.
KeyState* shiftKey = &leftKeys[0][0];
KeyState* specialKey = &leftKeys[0][1];
KeyState* controlKey = &leftKeys[0][2];
KeyState* altKey = &leftKeys[0][3];

// rx and tx (only rx is used) from rightHand legacy hardware
SoftwareSerial rightHand(14, 15); // RX, TX

// read in buffer parsed everytime a newline is read
// maybe I should use string class but like, why not optimize,
// right guys?
const int bufferSize = 80;
char rightHandBuffer[bufferSize];
int lastCharIndex = 0; // maybe rolling my own queue is a bad idea

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
  // sloppily implemented trampoline concurrency, 
  // maybe I should write this in a real language #GreenspunsTenthRule

  // read in if any keys have been PRESSED on left (master) side
  // by turning on each column one by one, and reading in the rows
  for (int row = 0; row < HEIGHT; row++){
    digitalWrite(pollingPins[row], LOW);
    for (int column = 0; column < WIDTH; column++){
      KeyState lastState = leftKeys[row][column];
      KeyState curState = (digitalRead(readingPins[column]) == LOW) 
                                              ? PRESSED : RELEASEED;

      if (curState == PRESSED && curState != lastState){
        keyboardPress(LEFT, row, column, PRESS);
      } else if (curState == RELEASEED && curState != lastState){
        keyboardPress(LEFT, row, column, RELEASE);
      }

      leftKeys[row][column] = curState;
    }
    digitalWrite(pollingPins[row], HIGH);
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
    } else {
      character = leftKeyMap[row][column];
    }
  } else { // I sure hope side == RIGHT
    if (*shiftKey == PRESSED){
      character = rightShiftKeyMap[row][column];
    } else if (*specialKey == PRESSED){
      character = rightSpecialKeyMap[row][column];
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
