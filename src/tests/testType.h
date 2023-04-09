#ifndef TESTTYPE_H
#define TESTTYPE_H

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
} TestResult;

#endif // TESTTYPE_H