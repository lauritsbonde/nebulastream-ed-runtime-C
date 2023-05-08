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
// #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*arr))

void test_encode_input(void);
void test_encode_output(void);


int main(void)
{
  // Setup
  puts("Test encode output");
  test_encode_output();

  puts("");
  puts("Test encode input");
  test_encode_input();

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

  status = decode_output_message(&istream);

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

  status = decode_input_message(&istream);

  printf("Decode status: %d\n", status);
}