#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "environment.h"
#include "expression.h"
#include "EndDeviceProtocol.pb.h"
#include "operators.h"
#include "number.h"
#include "encodeInput.h"
#include "ztimer.h"

// Macros
// #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*arr))
// #define SLEEP_SEC(t) (usleep(t * (int)pow(10, 6))) // sleep in seconds

int main(void)
{
  puts("LoRaWAN Class A low-power application");
  puts("=====================================");
  char n;
  scanf("%c", &n);

  // if (argc >= 2 && strcmp(argv[argc - 1], "test") == 0) {
  //   printf("run tests\n");
  //   TestToRun tests;
  //   if(argc == 2){
  //     tests = ALL;
  //   } else {
  //     if(strcmp(argv[2], "protocol") == 0){
  //       tests = PROTOCOL;
  //     } else if(strcmp(argv[2], "expression") == 0){
  //       tests = EXPRESSION;
  //     } else {
  //       tests = ALL;
  //     }
  //   }

  //   runTests(tests);
  //   return 0;
  // }

  // TODO: Look into running the main loop in a thread, and sleeping in low power mode with RIOT
  while (1) {
    puts("Main loop iteration");

    Env *e = init_env();

    printf("size: %d\n", e->size);

    // Construct example expression to be evaluated (5+5)
    Expression exp;
    Instruction i1 = {{CONST}, 0};
    Instruction i2 = {.data._int=5, 2};
    Instruction i3 = {{CONST}, 0};
    Instruction i4 = {.data._int=5, 2};
    Instruction i5 = {{ADD}, 0};
    Instruction program[5] = {i1, i2, i3, i4, i5};
    exp.p_size = 5;
    exp.program = program;
    exp.env = e;
    exp.stack = e->stack;

    Number res = call(&exp);
    printf("5 + 5 = %d\n",res.type._int);
    
    ztimer_sleep(ZTIMER_SEC, 5);
  }

  
  
  return 0;
}
