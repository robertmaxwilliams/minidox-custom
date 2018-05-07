
/* 

This programe polls out to some 
 rightHand is some legacy serial hardware that 
 spits out the following strings when a key is pressed:
releasd: 1 3
pressed: 1 3
**Notice they are followed by a newline, parsing procedure 
is explained below.





*/
#include <SoftwareSerial.h>
#include <Keyboard.h>

// keyboard wires randomly plugged into pins 10 to 2
pollingCount = 5;
const int pollingPins[pollingCount] = [6, 5, 4, 3, 2];
readingCount = 4;
const int readingPins[readingCount] = [10, 9, 8, 7];

enum keyState{pressed unpressed};

// keymaps - \0 is used for control characters, 
// which are baked into the logic
// as {shift, special, control, alt} and {super, ..., macro mode}

char leftKeyMap[4][5] = {
  {'q',  'w',  'e',  'r',  't'},
  {'a',  's',  'd',  'f',  'g'},
  {'z',  'x',  'c',  'v',  'v'},
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightKeyMap[4][5] = {
  {'y',  'u',  'i',  'o',  'p'},
  {'h',  'j',  'k',  'l',  ';'},
  {'b',  'n',  'm',  ',',  '.'},
  {'\0', '\t', '\n', ' ', '\0'}
};

char leftShiftKeyMap[4][5] = {
  {'Q',  'W',  'R',  'T',  'T'},
  {'A',  'S',  'D',  'F',  'G'},
  {'Z',  'X',  'C',  'V',  'V'},
  {'\0', '\0', '\0', '\0', '\0'}
};


char leftSpecialKeyMap[4][5] = {
  {'`',  '!',  '@',  '#',  '!'},
  {'\0', '<',  '{',  '[',  '('},
  {'|',  '"',  '\'',  '~',  '.'},
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightSpecialKeyMap[4][5] = {
  {'%',  '^',  '&',  '*',  '='},
  {')',  ']',  '}',  '>',  '\0'},
  {'/',  '\\',  ',',  '.',  '_'},
  {'\0', '\0', '\0', '\0', '\0'}
};


// rx and tx (only rx is used) from rightHand legacy hardware
SoftwareSerial rightHand(14, 15); // RX, TX

// read in buffer parsed everytime a newline is read
// maybe I should use string class but like, why not optimize,
// right guys?
int bufferSize = 80
char[bufferSize] rightHandBuffer;
int lastCharIndex = 0; // maybe rolling my own queue is a bad idea

void setup() {
  Serial.begin(9600);
  rightHand.begin(9600);

  for (int i = 0; i < pollingCount; i++){
    pinMode(pollingPins[i], INPUT);
  }

  for (int i = 0; i < readingCount; i++){
    pinMode(readingPins[i], OUTPUT);
  }

}

void loop() {
  // sloppily implemented trampoline concurrency, 
  // maybe I should write this in a real language #GreenspunsTenthRule

  for (int column 
  

}
