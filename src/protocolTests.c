#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "protocolTests.h"
#include "testType.h"
#include "environment.h"
#include "encodeInput.h"
#include "encodeOutput.h"
#include "pb_encode.h"
#include "pb_decode.h"

TestResult runProtocolTests(void){
  TestResult res;

  const int numTests = 5;
  res.total = numTests;
  res.passed = 0;
  res.tests = malloc(sizeof(Test) * numTests);

  res.tests[0] = data_is_initialised();
  res.tests[1] = query_is_initialised();
  res.tests[2] = output_is_initialised();
  res.tests[3] = output_messae_gets_encoded();
  res.tests[4] = output_message_gets_decoded();

  return res;
}

Test data_is_initialised(void){
  Test test;
  test.name = "data is initialised";
  test.failed = 0;
  
  // Create instructions
  Instruction exprInstruction;
  exprInstruction.data._instruction = CONST;
  exprInstruction.unionCase = 0;

  Instruction uintInstruction;
  uintInstruction.data._uint32 = 11;
  uintInstruction.unionCase = 1;

  Instruction intInstr;
  intInstr.data._int = 11;
  intInstr.unionCase = 2;

  Instruction floatInstr;
  floatInstr.data._float = 11.0f;
  floatInstr.unionCase = 3;

  Instruction doubleInstr;
  doubleInstr.data._double = 11.0;
  doubleInstr.unionCase = 4;

  EndDeviceProtocol_Data exprData = EndDeviceProtocol_Data_init_zero;
  EndDeviceProtocol_Data uintData = EndDeviceProtocol_Data_init_zero;
  EndDeviceProtocol_Data intData = EndDeviceProtocol_Data_init_zero;
  EndDeviceProtocol_Data floatData = EndDeviceProtocol_Data_init_zero;
  EndDeviceProtocol_Data doubleData = EndDeviceProtocol_Data_init_zero;

  // Prepare instructions
  init_data(exprInstruction, &exprData);
  init_data(uintInstruction, &uintData);
  init_data(intInstr, &intData);
  init_data(floatInstr, &floatData);
  init_data(doubleInstr, &doubleData);

  // Check that data is initialised
  if(exprData.data.instruction != EndDeviceProtocol_ExpressionInstructions_CONST) {
    test.failed = 1;
    test.message = "exprData.data._instruction is not CONST";
    return test;
  }

  if(uintData.data._uint32 != 11) {
    test.failed = 1;
    test.message = "uintData.data._uint is not 11";
    return test;
  }

  if(intData.data._int32 != 11) {
    test.failed = 1;
    test.message = "intData.data._int is not 11";
    return test;
  }

  if(floatData.data._float != 11.0f) {
    test.failed = 1;
    test.message = "floatData.data._float is not 11.0f";
    return test;
  }

  if(doubleData.data._double != 11.0) {
    test.failed = 1;
    test.message = "doubleData.data._double is not 11.0";
    return test;
  }

  return test;
}

Test query_is_initialised(void){
  Test test;
  test.name = "query is initialised";
  test.failed = 0;

  // Create instructions
  Instruction p[5] = {{{CONST}, 0}, {.data._int = 1, 2}, {{CONST}, 0}, {.data._int = 1, 2}, {{ADD}, 0}};

  // Create query
  QueryResponse query;
  query.id = 1;
  query.amount = 5;
  query.response = p;

  // Prepare query
  EndDeviceProtocol_Output_QueryResponse queryResponse = EndDeviceProtocol_Output_QueryResponse_init_zero;
  init_query_response(query, &queryResponse);

  // Check that query is initialised
  if(queryResponse.response_count != 5) {
    test.failed = 1;
    test.message = "queryResponse.response_count is not 5";
    return test;
  }

  if(queryResponse.response[0].data.instruction != EndDeviceProtocol_ExpressionInstructions_CONST) {
    test.failed = 1;
    test.message = "queryResponse.response[0].data.instruction is not CONST";
    return test;
  }

  if(queryResponse.response[1].data._int32 != 1) {
    test.failed = 1;
    test.message = "queryResponse.response[1].data._int32 is not 1";
    return test;
  }

  if(queryResponse.response[2].data.instruction != EndDeviceProtocol_ExpressionInstructions_CONST) {
    test.failed = 1;
    test.message = "queryResponse.response[2].data.instruction is not CONST";
    return test;
  }

  if(queryResponse.response[3].data._int32 != 1) {
    test.failed = 1;
    test.message = "queryResponse.response[3].data._int32 is not 1";
    return test;
  }

  if(queryResponse.response[4].data.instruction != EndDeviceProtocol_ExpressionInstructions_ADD) {
    test.failed = 1;
    test.message = "queryResponse.response[4].data.instruction is not ADD";
    return test;
  }

  return test;
}


Test output_is_initialised(void){
  Test test;
  test.name = "query is initialised";
  test.failed = 0;

  // Create instructions
  Instruction p[5] = {{{CONST}, 0}, {.data._int = 1, 2}, {{CONST}, 0}, {.data._int = 1, 2}, {{ADD}, 0}};

  // Create query
  QueryResponse query;
  query.id = 1;
  query.amount = 5;
  query.response = p;

  // Create Output
  OutputMessage output;
  output.amount = 1;
  output.responses = &query;

  // Prepare output
  EndDeviceProtocol_Output outputMessage = EndDeviceProtocol_Output_init_zero;
  init_output(output, &outputMessage);

  // Check that output is initialised
  if(outputMessage.responses_count != 1) {
    test.failed = 1;
    test.message = "outputMessage.response_count is not 1";
    return test;
  }

  if(outputMessage.responses[0].response_count != 5) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response_count is not 5";
    return test;
  }

  if(outputMessage.responses[0].response[0].data.instruction != EndDeviceProtocol_ExpressionInstructions_CONST) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[0].data.instruction is not CONST";
    return test;
  }

  if(outputMessage.responses[0].response[1].data._int32 != 1) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[1].data._int32 is not 1";
    return test;
  }

  if(outputMessage.responses[0].response[2].data.instruction != EndDeviceProtocol_ExpressionInstructions_CONST) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[2].data.instruction is not CONST";
    return test;
  }

  if(outputMessage.responses[0].response[3].data._int32 != 1) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[3].data._int32 is not 1";
    return test;
  }

  if(outputMessage.responses[0].response[4].data.instruction != EndDeviceProtocol_ExpressionInstructions_ADD) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[4].data.instruction is not ADD";
    return test;
  }

  return test;
}

Test output_messae_gets_encoded(void){
  Test test;
  test.name = "output message gets encoded";
  test.failed = 0;

  // Create instructions
  Instruction p[5] = {{{CONST}, 0}, {.data._int = 1, 2}, {{CONST}, 0}, {.data._int = 1, 2}, {{ADD}, 0}};

  // Create query
  QueryResponse query;
  query.id = 1;
  query.amount = 5;
  query.response = p;

  // Create Output
  OutputMessage output;
  output.amount = 1;
  output.responses = &query;

  // Encode output
  uint8_t buffer[1024];
  int message_length;
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

  bool status = encode_output_message(&stream, output);
  
  message_length = stream.bytes_written;

  // Expected bytes
  uint8_t expected[] = {0x0A, 0x16, 0x08, 0x01, 0x12, 0x02, 0x08, 0x00, 0x12, 0x02, 0x38, 0x02, 0x12, 0x02, 0x08, 0x00, 0x12, 0x02, 0x38, 0x02, 0x12, 0x02, 0x08, 0x08};

  if(!status) {
    test.failed = 1;
    test.message = "output message could not be encoded";
    return test;
  }

  for(int i = 0; i < message_length; i++) {
    if(buffer[i] != expected[i]) {
      test.failed = 1;
      test.message = "output message was not encoded correctly";
      return test;
    }
  }

  return test;
}

Test output_message_gets_decoded(void){
  Test test;
  test.name = "output message gets decoded";
  test.failed = 0;

  // Create instructions
  Instruction p[5] = {{{CONST}, 0}, {.data._int = 1, 2}, {{CONST}, 0}, {.data._int = 1, 2}, {{ADD}, 0}};

  // Create query
  QueryResponse query;
  query.id = 1;
  query.amount = 5;
  query.response = p;

  // Create Output
  OutputMessage output;
  output.amount = 1;
  output.responses = &query;

  // Encode output
  uint8_t buffer[1024];
  int message_length;
  pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));

  bool status = encode_output_message(&ostream, output);
  
  message_length = ostream.bytes_written;

  if(!status) {
    test.failed = 1;
    test.message = "output message could not be encoded";
    return test;
  }

  // Decode output
  pb_istream_t istream = pb_istream_from_buffer(buffer, message_length);
  EndDeviceProtocol_Output outputMessage = EndDeviceProtocol_Output_init_zero;

  status = decode_output_message(&istream, &outputMessage);

  if(!status) {
    test.failed = 1;
    test.message = "output message could not be decoded";
    return test;
  }

  // Check it has the correct values
  if(outputMessage.responses_count != 1) {
    test.failed = 1;
    test.message = "outputMessage.response_count is not 1";
    return test;
  }

  if(outputMessage.responses[0].response_count != 5) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response_count is not 5";
    return test;
  }

  if(outputMessage.responses[0].response[0].data.instruction != EndDeviceProtocol_ExpressionInstructions_CONST) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[0].data.instruction is not CONST";
    return test;
  }

  if(outputMessage.responses[0].response[1].data._int32 != 1) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[1].data._int32 is not 1";
    return test;
  }

  if(outputMessage.responses[0].response[2].data.instruction != EndDeviceProtocol_ExpressionInstructions_CONST) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[2].data.instruction is not CONST";
    return test;
  }

  if(outputMessage.responses[0].response[3].data._int32 != 1) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[3].data._int32 is not 1";
    return test;
  }

  if(outputMessage.responses[0].response[4].data.instruction != EndDeviceProtocol_ExpressionInstructions_ADD) {
    test.failed = 1;
    test.message = "outputMessage.response[0].response[4].data.instruction is not ADD";
    return test;
  }

  return test;
}
