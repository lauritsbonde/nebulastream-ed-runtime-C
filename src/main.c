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
  ztimer_sleep(ZTIMER_SEC, 5);
  
  //Run Tests
  runTests(ALL);

  //Setup
  puts("Test encode output");
  test_encode_output();

  puts("");
  puts("Test encode input");
  test_encode_input();

  ztimer_sleep(ZTIMER_SEC, 5);

  puts("NebulaStream End Decive Runtime");
  puts("=====================================");

  // Test lorawan
  connect_lorawan();
  uint8_t msg[2] = {(uint8_t) 5, (uint8_t) 0};
  uint8_t len = (uint8_t) 2;   
  send_message(msg, len);

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

void test_encode_output(void)
{
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
  for (size_t i = 0; i < message_length; ++i)
  {
    printf("%02hhx", buffer[i]);
  }
  printf("\n");

  // Decode
  pb_istream_t istream = pb_istream_from_buffer(buffer, message_length);
  EndDeviceProtocol_Output output = EndDeviceProtocol_Output_init_zero;

  status = decode_output_message(&istream, &output);

  printf("decode status: %d\n", status);
}

void test_encode_input(void)
{
  uint8_t buffer[1024];
  size_t message_length;
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));


  Instruction p[5] = {{{CONST}, 0}, {.data._int = 1, 2}, {{CONST}, 0}, {.data._int = 1, 2}, {{ADD}, 0}};

  Expression exp;
  exp.program = p;
  exp.p_size = 5;

  Map map;
  map.expression = &exp;
  map.attribute = 1;

  Operation op;
  op.operation.map = &map;
  op.unionCase = 0;

  Operation ops[1];
  ops[0] = op;

  Query q;
  q.operations = ops;
  q.amount = 1;

  Query queries[1];
  queries[0] = q;

  Message msg;
  msg.amount = 1;
  msg.queries = queries;

  printf("%d\n", msg.queries[0].operations[0].operation.map->expression->program[4].data._instruction);
  bool status = encode_message(&stream, msg);
  message_length = stream.bytes_written;
  printf("Encode status: %d\n", status);
  printf("Success: %zu written\n", message_length);
  for (size_t i = 0; i < message_length; ++i)
  {
    printf("%02hhx", buffer[i]);
  }
  printf("\n");

  // Decode
  pb_istream_t istream = pb_istream_from_buffer(buffer, message_length);

  Message message;

  status = decode_input_message(&istream, &message);

  printf("Decode status: %d\n", status);
}