#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "./stack/stack.h"
#include "./environment/environment.h"
#include "./expression/expression.h"
// #include "./proto/EndDeviceProtocol.pb.h"
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
    Env *s = init_env();
    printf("%d\n",s->size);
  }
  
  return 0;
}
