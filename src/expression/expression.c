// instruction definitions for stack machine
// data
const int CONST = 0;
const int VAR = 1;

// logical
const int AND = 2;
const int OR = 3;
const int NOT = 4;

// relational
const int LT = 5;
const int GT = 6;
const int EQ = 7;

// relational expanded
const int LTEQ = 21;
const int GTEQ = 22;

// arithmetic
const int ADD = 8;
const int SUB = 9;
const int MUL = 10;
const int DIV = 11;
const int MOD = 12;
const int LOG = 13;
const int POW = 14;
const int SQRT = 15;
const int EXP = 16;
const int CEIL = 17;
const int FLOOR = 18;
const int ROUND = 19;
const int ABS = 20;