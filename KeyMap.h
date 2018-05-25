
// keymaps 
// special keys found here:
// https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
//

// uh oops
#define KEY_SPECIAL 0x00
#define KEY_NAV 0x00
#define SEND_STRING 0xD1 // same as KEY_INSERT which I promise not to use
//const int SEND_STRING = 0xD1;

// any key set to \0 will "fall through" to this one.
// "special" is for the keyboard internally, so it is never send
// don't forget to update the pointers in the other files to shift and special etc
char leftModifiers[4][5] = {
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {KEY_SPECIAL, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_LEFT_GUI},
};

char rightModifiers[4][5] = {
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  KEY_ESC},
  {KEY_BACKSPACE,  '\t',  ' ',  '\n',  KEY_NAV},
};

char leftKeyMap[4][5] = {
  "qwert",
  "asdfg",
  "zxcvb",
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightKeyMap[4][5] = {
  "yuiop",
  "hjkl_",
  "nm,.\0",
  {'\0', '\0', '\0',  '\0', '\0'}
};

char leftShiftKeyMap[4][5] = {
  "QWRTY",
  "ASDFG",
  "ZXCVB",
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightShiftKeyMap[4][5] = {
  "YUIOP",
  "HJKL-",
  "NM;:\0",
  {KEY_DELETE, '\0', '\0',  '\0', '\0'}
};

char leftSpecialKeyMap[4][5] = {
  "~@#$%",
  "`{[(<",
  {SEND_STRING, SEND_STRING, SEND_STRING, '/', SEND_STRING},
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightSpecialKeyMap[4][5] = {
  "^&*|\\",
  ">)]}'.",
  "+=?\"\0",
  {'\0', '\0', '\0', '\0', '\0'}
};

char leftNavKeyMap[4][5] = {
  "+789*",
  "-456/",
  "0123=",
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightNavKeyMap[4][5] = {
  "     ",
  {KEY_LEFT_ARROW,  KEY_DOWN_ARROW,  KEY_UP_ARROW,  KEY_RIGHT_ARROW,  '\0'},
  "     ",
  {'\0', '\0', '\0', '\0', '\0'}
};
