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

    Instruction test = {.data = 2, .unionCase = 3};

    EndDeviceProtocol__Data *preparedData = prepare_instruction(&test);


    
    SLEEP_SEC(3);
  }
  return 0;
}
