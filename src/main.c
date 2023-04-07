#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#include "./logger/logger.h"
#include "./stack/stack.h"
#include "./environment/environment.h"
#include "./expression/expression.h"
#include "./proto/EndDeviceProtocol.pb-c.h"
#include "./protocol/protocol.h"
#include "./operators/operators.h"
#include "./protocol/EncodeInput.h"

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

    //Create a program
    Env *env = init_env();
    
    Expression exp;
    exp.env = env;
    exp.stack = env->stack;

    Instruction i1 = {0, 0};

    Instruction p[5] = {
        {0, 0},
        {2.1, 4},
        {0, 0},
        {1, 2},
        {6, 0}};

    exp.program = p;
    exp.p_size = 5;

    call(&exp);
    
    SLEEP_SEC(3);
  }
  return 0;
}
