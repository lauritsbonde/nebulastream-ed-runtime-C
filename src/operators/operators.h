#ifndef OPERATORS_H
#define OPERATORS_H
#endif

struct Operator {
  int (*call) (int *func);
};

struct Map {
  int* array;
  int arraySize;
  int* (*fun) (int* arr, int size);
};

struct Query {
  struct Operator operations;
  int (*equal) (int *func);
};


