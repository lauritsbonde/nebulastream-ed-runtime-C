#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#include "logger/logger.h"
#include "../proto/EndDeviceProtocol.pb-c.h"
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

    // Create a map
    Map map = {
      instructions,
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
    uint8_t buffer[1024];
    int len = encodeInputMessage(message, buffer);
    printf("Encoded message length: %d\n", len);
    printf("Encoded message: ");
    for (int i = 0; i < len; i++)
    {
      printf("%d ", buffer[i]);
    }
    printf("\n");

    SLEEP_SEC(3);
  }
  return 0;
}
