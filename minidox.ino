
/* 

This programe polls out to some 
 rightHand is some legacy serial hardware that 
 spits out the following strings when a key is pressed:
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

enum keyState{pressed, unpressed};

keyState leftKeys[HEIGHT][WIDTH];
keyState rightKeys[HEIGHT][WIDTH];

// rx and tx (only rx is used) from rightHand legacy hardware
SoftwareSerial rightHand(14, 15); // RX, TX

// read in buffer parsed everytime a newline is read
// maybe I should use string class but like, why not optimize,
// right guys?
const int bufferSize = 80;
char rightHandBuffer[bufferSize];
int lastCharIndex = 0; // maybe rolling my own queue is a bad idea

void setup() {
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

  // read in if any keys have been pressed on left (master) side
  // by turning on each column one by one, and reading in the rows
  for (int row = 0; row < HEIGHT; row++){
    digitalWrite(pollingPins[row], LOW);
    for (int column = 0; column < WIDTH; column++){
      keyState lastState = leftKeys[row][column];
      keyState curState = (digitalRead(readingPins[column]) == LOW) 
                                              ? pressed : unpressed;
      if (curState == pressed && curState != lastState){
        Serial.print("pressed: "); Serial.print(row); 
        Serial.print(' '); Serial.print(column); Serial.println(' ');
      } else if (curState == unpressed && curState != lastState){
        Serial.print("releasd: "); Serial.print(row); 
        Serial.print(' '); Serial.print(column); Serial.println(' ');
      }
      leftKeys[row][column] = curState;
    }
    digitalWrite(pollingPins[row], HIGH);
  }
}
