#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "./logger/logger.h"
#include "./stack/stack.h"
#include "./environment/environment.h"
#include "./expression/expression.h"
#include "./proto/EndDeviceProtocol.pb-c.h"
#include "./operators/operators.h"
#include "./protocol/encodeInput/encodeInput.h"
#include "./tests/runTest.h"
#include "./tests/testType.h"

// Macros
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*arr))
#define SLEEP_SEC(t) (usleep(t * (int)pow(10, 6))) // sleep in seconds

int main(int argc, char **argv)
{
  printf("LoRaWAN Class A low-power application\n");
  printf("=====================================\n");

  // TODO: Handle flags in Makefile. Not here
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


  if (argc >= 2 && strcmp(argv[argc - 1], "test") == 0) {
    printf("run tests\n");
    TestToRun tests;
    if(argc == 2){
      tests = ALL;
    } else {
      if(strcmp(argv[2], "protocol") == 0){
        tests = PROTOCOL;
      } else if(strcmp(argv[2], "expression") == 0){
        tests = EXPRESSION;
      } else {
        tests = ALL;
      }
    }

    runTests(tests);
    return 0;
  }

  // TODO: Look into running the main loop in a thread, and sleeping in low power mode with RIOT
  while (1)
  {
    printf("Main loop iteration\n");
    SLEEP_SEC(3);
  }
  
  return 0;
}
