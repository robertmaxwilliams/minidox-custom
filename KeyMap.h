
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
  {KEY_LEFT_GUI, KEY_SPECIAL, KEY_LEFT_SHIFT, KEY_LEFT_CTRL, KEY_ESC},
};

char rightModifiers[4][5] = {
  {'\0',  '\0',  '\0',  '\0',  '\0'},
  {'\0',  '\0',  '\0',  '\0',  KEY_DELETE},
  {'\0',  '\0',  '\0',  '\0',  '\0'},
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
  "hjkl;",
  "bnm,.",
  {'\0', '\0', '\0',  '\0', '\0'}
};

char leftShiftKeyMap[4][5] = {
  "QWRTY",
  "ASDFG",
  "ZXCVV",
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightShiftKeyMap[4][5] = {
  "YUIOP",
  "HJKL:",
  "BNM,.",
  {'\0', '\0', '\0',  '\0', '\0'}
};

char leftSpecialKeyMap[4][5] = {
  "!@#$%",
  "`<{[(",
  "/+_?:",
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightSpecialKeyMap[4][5] = {
  "^&*=|",
  ")]}>\'",
  "~..-\\",
  {'\0', '\0', '\0', '\0', '\0'}
};

char leftNavKeyMap[4][5] = {
  "+789/",
  "-456^",
  "*1230",
  {'\0', '\0', '\0', '\0', '\0'}
};

char rightNavKeyMap[4][5] = {
  "yuiop",
  {KEY_LEFT_ARROW,  KEY_DOWN_ARROW,  KEY_UP_ARROW,  KEY_RIGHT_ARROW,  ';'},
  "bnm,.",
  {'\0', '\0', '\0', '\0', '\0'}
};
