#ifndef OPERATORS_H
#define OPERATORS_H

// struct Operator {
//   int (*call) (int *func);
// };

typedef enum _ExpressionInstruction {
  CONST = 0,
  VAR = 1,
  AND = 2,
  OR = 3,
  NOT = 4,
  LT = 5,
  GT = 6,
  EQ = 7,
  ADD = 8,
  SUB = 9,
  MUL = 10,
  DIV = 11,
  MOD = 12
} ExpressionInstruction;

typedef struct _Instruction
{
  union {
    ExpressionInstruction instruction;
    uint32_t _uint32;
    int _int;
    float _float;
    double _double;
  } data;
} Instruction;

typedef struct _Expression
{
  int *instructions;
  int amount;
} Expression;

typedef struct _Map
{
  Instruction *function;
  int attribute;
  int amount;
} Map;

typedef struct _Filter
{
  Expression *predicate;
  int amount;
} Filter;

// struct Operator {
//   int* array;
//   int arraySize;
//   int* (*fun) (int* arr, int size);
// };

// TODO: Kig på at lave unions af Filter og Map

typedef struct _Operator
{
  Expression *expression;
  int amount;
} Operator;

typedef struct _Query
{
  Map *operations;
  int amount;
} Query;

typedef struct _Message
{
  Query *queries;
  int amount;
} Message;

typedef struct _QueryResponse
{
  int id;
  Instruction *response;
  int amount;
} QueryResponse;

typedef struct _OutputMessage
{
  QueryResponse responses;
} OutputMessage;

#endif