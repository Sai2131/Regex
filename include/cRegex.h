typedef struct regex regex;

regex* compile(char* regExpr);

void firstMatch(regex* r, char* str);

void fullMatch(regex* r, char* str);

void freeRegex(regex** r);

int quickFullMatch(char* regExpr, char* str);

int quickFirstMatch(char* regExpr, char* str);

