
// keymaps 
// special keys found here:
// https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
//

// uh oops
#define KEY_SPECIAL 0x00
#define KEY_NAV 0x00
  
// any key set to \0 will "fall through" to this one.
// "special" is for the keyboard internally, so it is never send
char leftModifiers[4][5] = {
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'KEY_BACKSPACE',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {KEY_LEFT_SHIFT, KEY_SPECIAL, KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_ESC},
};

char rightModifiers[4][5] = {
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  KEY_DELETE},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {KEY_BACKSPACE,  '\0',  '\0',  '\0',  KEY_NAV},
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
  {'H',  'J',  'K',  'L',  ':'},
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

char leftNavKeyMap[4][5] = {
  {'q',  '7',  '8',  '9',  't'},
  {'a',  '4',  '5',  '6',  'g'},
  {'z',  '1',  '2',  '3',  '0'},
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightNavKeyMap[4][5] = {
  {'y',  'u',  'i',  'o',  'p'},
  {KEY_LEFT_ARROW,  KEY_DOWN_ARROW,  KEY_UP_ARROW,  KEY_RIGHT_ARROW,  ';'},
  {'b',  'n',  'm',  ',',  '.'},
  {'\0', '\t', '\n', ' ', '\0'}
};
