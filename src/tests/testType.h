#ifndef TESTTYPE_H
#define TESTTYPE_H

typedef enum {
  ALL,
  EXPRESSION,
  PROTOCOL
} TestToRun;

typedef struct _Test
{
  char *name;
  int failed;
  char* message;
} Test;

typedef struct _TestResult
{
  int total;
  int passed;
  Test *tests;
} TestResult;

#endif // TESTTYPE_H