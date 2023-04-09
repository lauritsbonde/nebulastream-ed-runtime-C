#ifndef OPERATORS_H
#define OPERATORS_H

#include <stdlib.h>
#include "../number/number.h"

// struct Operator {
//   int (*call) (int *func);
// };



typedef struct _Stack
{
    int top;
    int size;
    Number *stack;
} Stack;

typedef struct _Env
{
    Number *env;
    int size;
    Stack *stack;
} Env;

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
  MOD = 12,
  LOG = 13,
  POW = 14,
  SQRT = 15,
  EXP = 16,
  CEIL = 17,
  FLOOR = 18,
  ROUND = 19,
  ABS = 20,
  LTEQ = 21,
  GTEQ = 22,
} ExpressionInstruction;

typedef struct _Instruction
{
  union {
    ExpressionInstruction instruction; // case 0
    uint32_t _uint32;                  // case 1
    int _int;                          // case 2
    float _float;                      // case 3
    double _double;                    // case 4
  } data;
  int unionCase;
} Instruction;

typedef struct _Expression
{
    Instruction *program;
    int p_size;
    int pc;
    Env *env;
    Stack *stack;
} Expression;


typedef struct _Map
{
  Expression *expression;
  int attribute;
  int amount;
} Map;

typedef struct _Filter
{
  Expression *predicate;
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