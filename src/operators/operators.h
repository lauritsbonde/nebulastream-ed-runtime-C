#ifndef OPERATORS_H
#define OPERATORS_H
#endif

// struct Operator {
//   int (*call) (int *func);
// };

struct Instruction {
  int type;
};

struct Expression {
  int* Instruction;
};

struct Map {
  struct Expression* expression;
  int attribute;
};

struct Filter {
  struct Expression* predicate;
};

// struct Operator {
//   int* array;
//   int arraySize;
//   int* (*fun) (int* arr, int size); 
// };

//TODO: Kig på at lave unions af Filter og Map

typedef struct {
  struct Expression* expression;
} Operator;

struct Query {
  struct Map* operations;
};


