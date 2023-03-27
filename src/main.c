#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "logger/logger.h"
#include "stack/stack.h"
#include "expression/expression.h"

// Macros
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*arr))
#define SLEEP_SEC(t) (usleep(t * (int)pow(10, 6))) // sleep in seconds

int main(int argc, char **argv)
{
  // Check if the flag for including logs was passed
  char *includeLogs;
  if (argc == 1)
  {
    includeLogs = "no";
  }
  else
  {
    includeLogs = argv[1]; // argv[1] is wether or not to include logs
  }
  init_logger(includeLogs);

  while (1)
  {
    printf("main loop iteration\n");
    Stack stack;
    init_stack(&stack, 10);

    Expression e;
    int p[5] = {
        0, // CONST
        1, // 1
        0, // CONST
        1, // 1
        9, // Sub
    };
    e.program = p;
    e.p_size = 5;
    e.stack = &stack;

    int res = call(&e);
    printf("result: %d \n", res);
    SLEEP_SEC(3);
  }

  return 0;
}
