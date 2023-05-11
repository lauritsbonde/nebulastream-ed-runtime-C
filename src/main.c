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
  // runTests(ALL);

  // Connect lorawan and receive first message
  // connect_lorawan();
  // receive_message();

  // Instruction program[5] = {{{CONST}, 0}, {.data._double = 2.3, .unionCase = 4}, {{CONST}, 0}, {.data._double = 3.4, .unionCase = 4}, {{ADD}, 0}};
  // Expression expression;
  // expression.program = program;
  // expression.p_size = 5;

  // Instruction program2[5] = {{{CONST}, 0}, {.data._int = 2, .unionCase = 2}, {{CONST}, 0}, {.data._int = 3, .unionCase = 4}, {{ADD}, 0}};
  // Expression expression2;
  // expression2.program = program2;
  // expression2.p_size = 5;

  // Instruction program3[5] = {{{CONST}, 0}, {.data._double = 2.3, .unionCase = 4}, {{CONST}, 0}, {.data._double = 3.4, .unionCase = 4}, {{ADD}, 0}};
  // Expression expression3;
  // expression3.program = program3;
  // expression3.p_size = 5;

  // Instruction program4[5] = {{{CONST}, 0}, {.data._int = 2, .unionCase = 2}, {{CONST}, 0}, {.data._int = 3, .unionCase = 4}, {{ADD}, 0}};
  // Expression expression4;
  // expression4.program = program4;
  // expression4.p_size = 5;

  // // Create map
  // Map map;
  // map.expression = &expression;
  // map.attribute = 0;

  // Filter filter;
  // filter.predicate = &expression2;

  // Map map2;
  // map2.expression = &expression3;
  // map2.attribute = 0;

  // Filter filter2;
  // filter2.predicate = &expression4;

  // // Create operation
  // Operation operation;
  // operation.operation.map = &map;
  // operation.unionCase = 0;

  // Operation operation2;
  // operation2.operation.filter = &filter;
  // operation2.unionCase = 1;

  // Operation operation3;
  // operation3.operation.map = &map2;
  // operation3.unionCase = 0;

  // Operation operation4;
  // operation4.operation.filter = &filter2;
  // operation4.unionCase = 1;

  // Operation opList[] = {operation, operation2};
  // Operation opList2[] = {operation3, operation4};

  // // Create query
  // Query query;
  // query.operations = opList;
  // query.amount = 2;

  // Query query2;
  // query2.operations = opList2;
  // query2.amount = 2;

  // Query queryList[] = {query, query2};

  // // Create message
  // Message e;
  // e.queries = queryList;
  // e.amount = 2;

  // // Create outputstream
  // uint8_t e_buffer[1024];
  // int e_length;
  // pb_ostream_t stream = pb_ostream_from_buffer(e_buffer, sizeof(e_buffer));

  // // Encode message
  // encode_message(&stream, e);
  // e_length = stream.bytes_written;

  // for (int i = 0; i < e_length; ++i) {
  //   if(i == 0){
  //     printf("{");
  //   }
  //   printf("0x%02hx", e_buffer[i]);
  //   if(i == e_length - 1){
  //     printf("}\n");
  //   } else {
  //     printf(", ");
  //   }
  // }
  // printf("\n");
  // printf("Message length: %d\n", e_length);

  // return 0;


  double averages[10];

  uint8_t testing[] = {0x0a, 0x47, 0x0a, 0x24, 0x0a, 0x22, 0x0a, 0x02, 0x08, 0x00, 0x0a, 0x09, 0x59, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x02, 0x40, 0x0a, 0x02, 0x08, 0x00, 0x0a, 0x09, 0x59, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x0b, 0x40, 0x0a, 0x02, 0x08, 0x08, 0x0a, 0x1f, 0x0a, 0x1d, 0x0a, 0x02, 0x08, 0x00, 0x0a, 0x02, 0x38, 0x04, 0x0a, 0x02, 0x08, 0x00, 0x0a, 0x09, 0x59, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x02, 0x08, 0x08, 0x10, 0x01};


  for(int i = 0; i < 10; i++){
    clock_t t = clock();

    // Decode message
    pb_istream_t istream = pb_istream_from_buffer(testing, 73);
    Message msg;
    decode_input_message(&istream, &msg);

    // Execute message
    OutputMessage out;
    executeQueries(msg, &out, init_env());

    // Calculate time taken
    t = clock() - t;
    double time_taken = ((double)t)/(1000); // in ms

    averages[i] = time_taken;
  }

  double sum = 0;
  for(int i = 0; i < 10; i++){
    sum += averages[i];
  }

  double average = sum / 10;
  printf("average time: %f", average);

  return 1;
  


  
  
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
