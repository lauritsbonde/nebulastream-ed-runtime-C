#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <pb_encode.h>
#include <pb_decode.h>

#include "logger/logger.h"
#include "proto/EndDeviceProtocol.pb.h"
#include "protocol/protocol.h"
#include "./operators/operators.h"

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
    printf("Main loop iteration\n");
    
    // Create a message
    // Start with data/instruction
    Instruction instructions[] = {
      {CONST, 1},
      {CONST, 2},
      {ADD}
    };

    // Create an expression
    Expression expression = {
      instructions,
      ARRAY_SIZE(instructions)
    };

    // Create a map
    Map map = {
      &expression,
      1,
      1
    };

    // Create a query
    Query query = {
      &map,
      1
    };

    // Create a message
    Message message = {
      &query,
      1
    };


    // Encode the message
    EndDeviceProtocol_Message encodedMessage = endcodeInputMessage(message);


    SLEEP_SEC(3);
  }

  return 0;
}
