

// keymaps 
// special keys found here:
// https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/

  
// any key set to \0 will "fall through" to this one.
// "special" is for the keyboard internally, so it is never send
char leftModifiers[4][5] = {
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {KEY_LEFT_SHIFT, '\0', KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_ESC},
          //SPECIAL /|
};

char rightModifiers[4][5] = {
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
};

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

char rightShiftKeyMap[4][5] = {
  {'Y',  'U',  'I',  'O',  'P'},
  {'H',  'J',  'K',  'L',  ';'},
  {'B',  'N',  'M',  ',',  '.'},
  {'\0', '\t', '\n', ' ', '\0'}
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



