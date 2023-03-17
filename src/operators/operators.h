#ifndef OPERATORS_H
#define OPERATORS_H
#endif

// struct Operator {
//   int (*call) (int *func);
// };

typedef struct _Instruction
{
  int type;
} Instruction;

typedef struct _Expression
{
  int *Instruction;
} Expression;

typedef struct _Map
{
  Expression *expression;
  int attribute;
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
} Query;

typedef struct _Message
{
  Query *queries;
} Message;

typedef struct _QueryResponse
{
  int id;
  Instruction *response;
} QueryResponse;

typedef struct _OutputMessage
{
  QueryResponse responses;
} OutputMessage;
