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
    uint8_t buffer[128]; // a buffer to hold the encoded message
    size_t message_length;
    bool status;

    printf("Main loop iteration\n");
    // TODO: Create a protobuf message
    EndDeviceProtocol_MapOperation map = EndDeviceProtocol_MapOperation_init_zero;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    uint32_t instr = EndDeviceProtocol_ExpressionInstructions_ADD;

    // pb_callback_t instructions = {instr};

    map.attribute = 22;
    // map.function = instr;

    status = pb_encode(&stream, EndDeviceProtocol_MapOperation_fields, &map);
    message_length = stream.bytes_written;

    if (!status)
    {
      printf("Encoding failed: %s\n", PB_GET_ESERROR(&stream));
    }
    else
    {
      printf("Succes!");
      for (int i = 0; i < 128; i++)
      {
        // TODO: "Send" the message somewhere
        printf("%d", buffer[i]);
      };
      printf("\n done \n");
    }

    // TODO: "Receive" the message somewhere
    EndDeviceProtocol_MapOperation mapout = EndDeviceProtocol_MapOperation_init_zero;
    pb_istream_t in_stream = pb_istream_from_buffer(buffer, message_length);

    status = pb_decode(&in_stream, EndDeviceProtocol_MapOperation_fields, &mapout);

    if (!status)
    {
      printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
    }
    // TODO: Print the message content somewhere
    printf("decoded message: %d \n", mapout.attribute);
    logger("loop", "Main loop iteration");
    SLEEP_SEC(3);
  }

  return 0;
}
