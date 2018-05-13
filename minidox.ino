const int DEBUG = true;
/* 

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

enum Side{LEFT, RIGHT};

// having these as seperate types is debatable, 
// but at this point I would like to be explicit
// about whether I am describing a key as
// pressed or unpressed, or describing what to do to a key.
enum Action{RELEASE, PRESS, TOGGLE};
enum KeyState{RELEASED, PRESSED};

KeyState actionToState(Action action) {
  switch(action){
    case RELEASE: return RELEASED;
    case PRESS: return PRESSED;
  }
}
KeyState actionToState(Action action, KeyState curState) { 
  // overload for toggle functionality
  if (action != TOGGLE) { return actionToState(action); }
  return (curState == PRESSED) ? RELEASED : PRESSED;
}

Action stateToAction(KeyState state) {
  switch(state){
    case RELEASED: return RELEASE;
    case PRESSED: return PRESS;
  }
}

// global state, should only be modified within keyboardPress
KeyState leftKeys[HEIGHT][WIDTH];
KeyState rightKeys[HEIGHT][WIDTH];

// These are read by findCharacter to determine modifier state
const KeyState* shiftKey = &leftKeys[3][2];
const KeyState* specialKey = &leftKeys[3][1];
const KeyState* controlKey = &leftKeys[3][2];
const KeyState* altKey = &leftKeys[3][3];
const KeyState* navKey = &rightKeys[3][4];

// rx and tx (only rx is used) from rightHand legacy hardware
SoftwareSerial rightHand(14, 15); // RX, TX

//struct to hold information about right hand's strings as
// they come in and are parsed
struct RightHandIncoming {
  int index = 0;
  int row;
  int column;
  KeyState keyState;
  bool ready = false;

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

      if (curState != lastState){
        keyboardPress(LEFT, row, column, TOGGLE);
      }

      leftKeys[row][column] = curState;
    }
    digitalWrite(pollingPins[row], HIGH);
  }

  // read character from rightHand, and increment lastCharIndex. 
  // on line ending, parse the buffer and reset it.
  // failures on overflow or failed parse.
  // also the order of incrementation is off by one. oops. Not my problem.
  // TODO refactor this whole thing
  if (rightHand.available() > 0) {
    char incoming = rightHand.read();
    if (DEBUG) { Serial.write(incoming); }
    if (incoming == '\n' && rightHandParser.ready) {
      // bounds checking is for people who lack faith
      keyboardPress(RIGHT, rightHandParser.row, rightHandParser.column, stateToAction(rightHandParser.keyState));
    // parse characters 2, 11, and 13
    } else if (rightHandParser.index == 0) {
      rightHandParser.keyState = (incoming == 'p') ? PRESSED : RELEASED;
      rightHandParser.ready = true; // is this isn't set, then fail this line
      if (DEBUG) { Serial.print("|| p or r?: "); Serial.println(incoming); }
    } else if (rightHandParser.index == 9) {
      rightHandParser.row = 3 - (incoming - '0'); // was upside down for some reason
      if (DEBUG) { Serial.print("|| first number:"); Serial.println(incoming); }
    } else if (rightHandParser.index == 11) {
      rightHandParser.column = incoming - '0';
      if (DEBUG) { Serial.print("|| second number:"); Serial.println(incoming); }
    }

    // increment index for string that we're parsing
    rightHandParser.index += 1;

    // not matter what happened, reset rightHandParser if we're at a newline
    if (incoming == '\n') {
        rightHandParser.index = 0;
        rightHandParser.ready = false;
    }

  }
}

// yummy arrow code ;)
void printKeyState() {
  if (DEBUG == false) {return;}
  for (int row = 0; row < HEIGHT; row++){
    for (int side = 0; side < 2; side++){
      for (int column = 0; column < WIDTH; column++){
        if (side == 0) {
          // who doesn't love some terse ternary expressions
          Serial.write(leftKeys[row][column] ? 'X' : '.');
        } else {
          Serial.write(rightKeys[row][column] ? 'X' : '.');
        }
      }
      Serial.write('\t');
    }
    Serial.write('\n');
  }
  Serial.write('\n');
}
          

char getCharacter(Side side, int row, int column){
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

// sends keypress to computer, and modifies out global state leftKeys and rightKeys
void keyboardPress(Side side, int row, int column, Action action){
  // mutate global state of keys

  // gets the right keyboard and cell within it, and sets to new value
  // SO TERSE!
  KeyState* activeKey = &((side == LEFT) ? leftKeys : rightKeys)[row][column];
  if (DEBUG){
    Serial.println("apply action {action} with current state {state}");
    Serial.print(action); Serial.println(*activeKey);
  }
  *activeKey = actionToState(action, *activeKey);

  // used global KeyState to determine shift and special
  char key = getCharacter(side, row, column);

  if (DEBUG){
    Serial.println("after:");
    printKeyState();
    Serial.print("row: "); Serial.print(row); Serial.print(" column: "); Serial.print(column);Serial.println();
    Serial.print(key); Serial.println((int) key);
    Serial.println("held keys: shift, special, conrole, alt, nav");
    Serial.print(*shiftKey); Serial.print(*specialKey); Serial.print(*controlKey); Serial.print(*altKey); Serial.print(*navKey);
    Serial.print('\n');
  }

  // send the keypress or release to PC
  // based on our updated global state
  if (*activeKey == PRESSED){
    Keyboard.press(key);
  } else { // *activeKey == RELEASED
    Keyboard.release(key);
  }
}
    
// notes on shift: it seems shift and upper/lowercase letters are independant, 
// so you could send shift+'a' or 'A'. I'm not sure how real keyboards do this
// but we'll see

// examples of printouts from rightHand:
/*
releasd: 1 3
pressed: 1 3
*/
