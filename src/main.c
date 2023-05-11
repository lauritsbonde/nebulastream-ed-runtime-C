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
#ifndef BOARD_NATIVE
#include "lora.h"
#include "semtech_loramac.h"
#endif

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

extern semtech_loramac_t loramac;

int main(void)
{
  ztimer_sleep(ZTIMER_SEC, 5);
  puts("NebulaStream End Decive Runtime");
  puts("=====================================");
  
  //Run Tests
  //runTests(ALL);

  // Connect lorawan and receive first message
#ifndef BOARD_NATIVE
  connect_lorawan();
#endif
  
  // Mock message: Map operation with 1 + 1 expression 
  //{0x0a, 0x18, 0x0a, 0x16, 0x0a, 0x14, 0x0a, 0x02, 0x08, 0x00, 0x0a, 0x02, 0x38, 0x02, 0x0a, 0x02, 0x08, 0x00, 0x0a, 0x02, 0x38, 0x02, 0x0a, 0x02, 0x08, 0x08};

  // Initialize global variable environment
  Env * global_env = init_env();
  
  while (1) {
    puts("Main loop iteration");
    
    // Check for received messages
    pb_istream_t istream = pb_istream_from_buffer(loramac.rx_data.payload, loramac.rx_data.payload_len);
    Message msg;
    decode_input_message(&istream, &msg);


    // Execute queries
    OutputMessage out;
    executeQueries(msg, &out, global_env);

    printf("out.responses[0].amount: %d\n", out.responses[0].amount);

    if (out.amount > 0) {
      puts("encoding and sending output");
      uint8_t buffer[256];
      pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));
      encode_output_message(&ostream, &out);
      send_message(buffer, (uint8_t)256);
    }

    uint8_t test[5];
    send_message(test, (uint8_t) 5);

    ztimer_sleep(ZTIMER_SEC, 5);
  }
  

  return 0;
}
