

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

