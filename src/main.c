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
#include "execution.h"
#include "operators.h"
#include "number.h"
#include "encodeInput.h"
#include "encodeOutput.h"
//#include "lora.h"

#include <time.h>

//Testing
#include "runTest.h"
#include "testType.h"

// RIOT includes
#include "EndDeviceProtocol.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "ztimer.h"

void test_encode_input(void);
void test_encode_output(void);


int main(void)
{
  ztimer_sleep(ZTIMER_SEC, 1);
  puts("NebulaStream End Decive Runtime");
  puts("=====================================");
  
  //Run Tests
  runTests(ALL);

  // Connect lorawan and receive first message
  // connect_lorawan();
  // receive_message();

  // Mock message: Map operation with 1 + 1 expression 
  uint8_t message[] = {0x0a, 0x18, 0x0a, 0x16, 0x0a, 0x14, 0x0a, 0x02, 0x08, 0x00, 0x0a, 0x02, 0x38, 0x02, 0x0a, 0x02, 0x08, 0x00, 0x0a, 0x02, 0x38, 0x02, 0x0a, 0x02, 0x08, 0x08};

  // decode message
  pb_istream_t istream = pb_istream_from_buffer(message, 26);
  Message msg;
  decode_input_message(&istream, &msg);

  // Initialize global variable environment
  Env * global_env = init_env();

  // Execute queries from message
  OutputMessage out;
  executeQueries(msg, &out, global_env);

  // Verify result of the single map operation of the first query
  Instruction i = out.responses[0].response[0];
  printf("Result: %d\n", i.data._int);

  // Encode output
  uint8_t buffer[128];
  pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));

  encode_output_message(&ostream, out);
  free_output_message(&out);

  int message_length = ostream.bytes_written;
  
  // Verify that output message gets encoded
  for (int i = 0; i < message_length; ++i) {
    printf("%02hx", buffer[i]);
  }
  printf("\n");

  pb_istream_t test = pb_istream_from_buffer(buffer, message_length);
  EndDeviceProtocol_Output response = EndDeviceProtocol_Output_init_zero;
  decode_output_message(&test, &response);

  while (1) {
    puts("Main loop iteration");
    ztimer_sleep(ZTIMER_SEC, 5);
  }
  

  return 0;
}
