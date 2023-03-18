#ifndef OPERATORS_H
#define OPERATORS_H

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
  int amount;
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