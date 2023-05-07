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
#include "ztimer.h"


// Macros
//#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*arr))

int main(void)
{
  uint8_t buffer[128];
  // size_t message_length;
  bool status;

  Instruction i;
  i.data._int = 22;
  i.unionCase = 2;

  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

  // status = encode_data(i, &stream);

  // if(!status){
  //   printf("Encoding failed");
  //   return 0;
  // }

  // message_length = stream.bytes_written;

  // printf("Encoding successfull, message length: %d\n", message_length);
  
  // decode_data(buffer, message_length);

  QueryResponse query;
  query.response = &i;
  query.amount = 1;
  query.id = 1;

  status = encode_query_response(&stream, &query);

  if (!status) {
    printf("encode failed: %s\n", PB_GET_ERROR(&stream));
  }  

  message_length = stream.bytes_written;

  printf("Success: %zu written\n", message_length);
  for (size_t i = 0; i < message_length; ++i) {
      printf("%02hhx", buffer[i]);
  }
  printf("\n");

  pb_istream_t stream = pb_istream_from_buffer(buffer, length);

  decode_query_response(&stream);

  return 0;
}
