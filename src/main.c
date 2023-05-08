#define LOG_LEVEL LOG_DEBUG
// Standard library includes
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Local includes
#include "stack.h"
#include "environment.h"
#include "expression.h"
#include "operators.h"
#include "number.h"
#include "encodeInput.h"
#include "encodeOutput.h"
#include "lora.h"

// RIOT includes
#include "EndDeviceProtocol.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "ztimer.h"


// Macros
//#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*arr))

int main(void)
{
  // Setup
  uint8_t buffer[1024];
  size_t message_length;
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

  Instruction i1;
  i1.data._float = 2.0f;
  i1.unionCase = 3;

  QueryResponse q1;
  q1.response = &i1;
  q1.amount = 1;
  q1.id = 2;

  OutputMessage o1;
  o1.responses = &q1;
  o1.amount = 1;

  // Encode
  bool status = encode_output_message(&stream, o1);
  message_length = stream.bytes_written;
  printf("Encode status: %d\n", status);
  printf("Success: %zu written\n", message_length);
  for (size_t i = 0; i < message_length; ++i) {
      printf("%02hhx", buffer[i]);
  }
  printf("\n");

  // Decode
  pb_istream_t istream = pb_istream_from_buffer(buffer, message_length);

  status = decode_output_message(&istream);

  printf("decode status: %d\n", status);

  return 0;
}
