#include <stdlib.h>
#include <stdio.h>
#include "protocolTests.h"
#include "../testType.h"
#include "../../environment/environment.h"
#include "../../protocol/encodeInput/encodeInput.h"
#include "../../protocol/decodeInput/decodeInput.h"
#include "../../protocol/encodeOutput/encodeOutput.h"

TestResult runProtocolTests(){
  TestResult res = {0,0};

  const int numTests = 11;
  res.total += numTests;

  res.tests = malloc(sizeof(Test) * numTests);
  
  //INPUT message tests

  res.tests[0] = prepareInstructionTest();
  res.tests[1] = prepareExpressionTest();
  res.tests[2] = prepareMapTest();
  res.tests[3] = prepareQueryTest();
  res.tests[4] = prepareMessageTest();

  res.tests[5] = instructionGetsEncoded();
  res.tests[6] = expressionGetsEncoded();
  res.tests[7] = mapGetsEncoded();
  
  res.tests[8] = messageGetsEncoded();
  res.tests[9] = messageGetsDecoded();

  //OUTPUT message tests
  res.tests[10] = outputMessageGetsEncoded();

  return res;
}

Test prepareInstructionTest(){
  Test test;
  test.name = "Instruction is prepared to EndDeviceProtocol__Data";

  Instruction dataInstrucion = {0, 0};
  Instruction uintInstruction = {1,1};
  Instruction intInstruction = {2,2};
  Instruction floatInstruction = {3.0,3};
  Instruction doubleInstruction = {4.0,4};
  
  Instruction *instructions[5] = {&dataInstrucion, &uintInstruction, &intInstruction, &floatInstruction, &doubleInstruction};

  EndDeviceProtocol__Data__DataCase expected[5] = {
    END_DEVICE_PROTOCOL__DATA__DATA_INSTRUCTION,
    END_DEVICE_PROTOCOL__DATA__DATA__UINT32,
    END_DEVICE_PROTOCOL__DATA__DATA__INT16,
    END_DEVICE_PROTOCOL__DATA__DATA__FLOAT,
    END_DEVICE_PROTOCOL__DATA__DATA__DOUBLE
  };

  //Names for possible error messages
  char **names = malloc(sizeof(char*) * 5);
  names[0] = "data";
  names[1] = "uint";
  names[2] = "int";
  names[3] = "float";
  names[4] = "double";

  for(int i = 0; i < 5; i++){
    EndDeviceProtocol__Data *preparedDataInstruction = prepare_instruction(instructions[i]);

    if(preparedDataInstruction->data_case == expected[i]) {
      test.failed = 0;
    } else {
      test.failed = 1;
      char* msg;
      sprintf(&msg, "Expected %s to be %d, but was %d", names[i], expected[i], preparedDataInstruction->data_case);
      test.message = msg;
    }
  }

  return test;
}

Test prepareExpressionTest(){
  Test test;
  test.name = "Expression is prepared to EndDeviceProtocol__Expression";

  const int numberOfInstructions = 2;

  //Create a program with 2 instructions
  Instruction p1[numberOfInstructions] = {
      {0, 0},
      {.data._int = 3, 2}
    };

  Env *env = init_env();
  Expression exp;
  exp.program = p1;
  exp.p_size = numberOfInstructions;
  exp.env = env;
  exp.stack = env->stack;
  

  // Prepare the expression
  EndDeviceProtocol__Expression *preparedExpression = prepare_expression(&exp);

  // Check if the expression has the correct number of instructions
  if(preparedExpression->n_instructions == numberOfInstructions){
    test.failed = 0;
  } else {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected expression to have %d instructions, but had %d", numberOfInstructions, preparedExpression->n_instructions);
    test.message = msg;
  }
  
  return test;
}

Test prepareMapTest(){
  Test test;
  test.name = "Map is prepared to EndDeviceProtocol__Map";

  const int numberOfInstructions = 2;

  // Create a map
  Instruction p1[numberOfInstructions] = {
      {0, 0},
      {.data._int = 3, 2}
    };

  Env *env = init_env();
  Expression exp;
  exp.program = p1;
  exp.p_size = numberOfInstructions;
  exp.env = env;
  exp.stack = env->stack;

  Map map;
  map.expression = &exp;
  map.attribute = 1;


  // Prepare the map
  EndDeviceProtocol__MapOperation *preparedMap = prepare_map_operation(&map);

  int hasFailed = 0;

  // check the map has the correct attribute
  if(preparedMap->attribute == 1){
    test.failed = 0;
  } else {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected map to have attribute %d, but had %d", 1, preparedMap->attribute);
    test.message = msg;
    hasFailed = 1;
  }

  // check the map has the correct number of instructions
  if(hasFailed == 0 && preparedMap->n_function == numberOfInstructions){
    test.failed = 0;
  } else {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected map to have %d instructions, but had %d", numberOfInstructions, preparedMap->n_function);
    test.message = msg;
  }

  return test;
}

Test prepareQueryTest(){
  Test test;
  test.name = "Query is prepared to EndDeviceProtocol__Query (with 1 map)";

  const int numberOfInstructions = 2;

  // Create a query
  Instruction p1[numberOfInstructions] = {
      {0, 0},
      {.data._int = 3, 2}
    };

  Env *env = init_env();
  Expression exp;
  exp.program = p1;
  exp.p_size = numberOfInstructions;
  exp.env = env;
  exp.stack = env->stack;

  Map map;
  map.expression = &exp;
  map.attribute = 1;

  Query query;
  query.operations = &map;
  query.amount = 1;

  // Prepare the query
  EndDeviceProtocol__Query *preparedQuery = prepare_query(&query);

  if(preparedQuery->n_operations == 1){
    test.failed = 0;
  } else {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected query to have %d operations, but had %d", 1, preparedQuery->n_operations);
    test.message = msg;
  }

  return test;
}

Test prepareMessageTest(){
  Test test;
  test.name = "Message is prepared to EndDeviceProtocol__Message";

  const int numberOfInstructions = 2;

  // Create a message
  Instruction p1[numberOfInstructions] = {
      {0, 0},
      {.data._int = 3, 2}
    };

  Env *env = init_env();
  Expression exp;
  exp.program = p1;
  exp.p_size = numberOfInstructions;
  exp.env = env;
  exp.stack = env->stack;


  Map map;
  map.expression = &exp;
  map.attribute = 1;

  Query query;
  query.operations = &map;
  query.amount = 1;

  Message message;
  message.queries = &query;
  message.amount = 1;

  // Prepare the message
  EndDeviceProtocol__Message *preparedMessage = prepare_message(&message);

  if(preparedMessage->n_queries == 1){
    test.failed = 0;
  } else {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected message to have %d queries, but had %d", 1, preparedMessage->n_queries);
    test.message = msg;
  }

  return test;
}

Test instructionGetsEncoded(){
  Test test;
  test.name = "Instruction gets encoded";

  Instruction instr = {0, 0};

  // Encode the instruction
  void* encoded = encode_instruction(&instr);

  // Check if the instruction has the correct size
  test.failed = 0;
  return test;
}

Test expressionGetsEncoded(){
  Test test;
  test.name = "Expression gets encoded";

  const int numberOfInstructions = 2;

  // Create a expression
  Instruction p1[numberOfInstructions] = {
      {0, 0},
      {.data._int = 3, 2}
    };

  Env *env = init_env();
  Expression exp;
  exp.program = p1;
  exp.p_size = numberOfInstructions;
  exp.env = env;
  exp.stack = env->stack;

  // Encode the expression
  void* encodedExpression = encode_expression(&exp);

  // Check if the expression has the correct size
  test.failed = 0;

  return test;
}

Test mapGetsEncoded(){
  Test test;
  test.name = "Map gets encoded";

  const int numberOfInstructions = 2;

  // Create a map
  Instruction p1[numberOfInstructions] = {
      {0, 0},
      {.data._int = 3, 2}
    };

  Env *env = init_env();
  Expression exp;
  exp.program = p1;
  exp.p_size = numberOfInstructions;
  exp.env = env;
  exp.stack = env->stack;

  Map map;
  map.expression = &exp;
  map.attribute = 1;

  // Encode the map
  void* encodedMap = encode_map_operation(&map);

  // Check if the map has the correct size
  test.failed = 0;

  return test;
}

Test messageGetsEncoded(){
  Test test;
  test.name = "Message gets encoded";

  const int numberOfInstructions = 2;

  // Create a message
  Instruction p1[numberOfInstructions] = {
      {0, 0},
      {.data._int = 3, 2}
    };

  Env *env = init_env();
  Expression exp;
  exp.program = p1;
  exp.p_size = numberOfInstructions;
  exp.env = env;
  exp.stack = env->stack;

  Map map;
  map.expression = &exp;
  map.attribute = 1;

  Query query;
  query.operations = &map;
  query.amount = 1;

  Message message;
  message.queries = &query;
  message.amount = 1;

  // Encode the message
  uint8_t* encodedMessage = encode_message(&message);
  
  const int expectedLength = 14;

  uint8_t expected[expectedLength] = {10,12,10,10,10,2,8,0,10,2,56,6,16,1};

  for(int i = 0; i < expectedLength; i++){
    if(encodedMessage[i] != expected[i]){
      test.failed = 1;
      char* msg;
      sprintf(&msg, "Expected %d at index %d, but got %d", expected[i], i, encodedMessage[i]);
      test.message = msg;
      return test;
    }
  }
  
  test.failed = 0;
  return test;
}

Test messageGetsDecoded(){
  Test test;
  test.name = "Message gets decoded";

  const int numberOfInstructions = 2;

  // Create a message
  Instruction p1[numberOfInstructions] = {
      {0, 0},
      {.data._int = 3, 2}
    };

  Env *env = init_env();
  Expression exp;
  exp.program = p1;
  exp.p_size = numberOfInstructions;
  exp.env = env;
  exp.stack = env->stack;

  Map map;
  map.expression = &exp;
  map.attribute = 1;

  Query query;
  query.operations = &map;
  query.amount = 1;

  Message message;
  message.queries = &query;
  message.amount = 1;

  // Encode the message
  uint8_t* encodedMessage = encode_message(&message);

  // Decode the message
  Message decodedMessage = decodeMessage(encodedMessage, 14);


  int expectedQueryAmount = 1;
  int expectedOperationAmount = 1;
  int expectedInstructionAmount = 2;

  int expectedInstruction1Data = 0;
  int expectedInstruction1UnionCase = 0;

  int expectedInstruction2Data = 3;
  int expectedInstruction2UnionCase = 2;

  if(decodedMessage.amount != expectedQueryAmount) {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected message to have %d queries, but had %d", expectedQueryAmount, decodedMessage.amount);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->amount != expectedOperationAmount) {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected query to have %d operations, but had %d", expectedOperationAmount, decodedMessage.queries->amount);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->expression->p_size != expectedInstructionAmount) {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected operation to have %d instructions, but had %d", expectedInstructionAmount, decodedMessage.queries->operations->expression->p_size);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->expression->program[0].unionCase != expectedInstruction1UnionCase) {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected instruction 1 to have unionCase %d, but had %d", expectedInstruction1UnionCase, decodedMessage.queries->operations->expression->program[0].unionCase);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->expression->program[0].data._instruction != expectedInstruction1Data) {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected instruction 1 to have data %d, but had %d", expectedInstruction1Data, decodedMessage.queries->operations->expression->program[0].data._instruction);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->expression->program[1].unionCase != expectedInstruction2UnionCase) {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected instruction 2 to have unionCase %d, but had %d", expectedInstruction2UnionCase, decodedMessage.queries->operations->expression->program[1].unionCase);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->expression->program[1].data._int != expectedInstruction2Data) {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected instruction 2 to have data %d, but had %d", expectedInstruction2Data, decodedMessage.queries->operations->expression->program[1].data._int);
    test.message = msg;
    return test;
  }


  // Check if the message has the correct size
  test.failed = 0;
  test.message = "Message was decoded correctly";

  return test;
}


Test outputMessageGetsEncoded(){
  Test test;
  test.name = "Output message gets encoded";

  Instruction p1[1] = {
      {.data._int = 3, 2}
    };

  QueryResponse response;
  response.id = 1;
  response.response = p1;
  response.amount = 1;

  OutputMessage message;
  message.responses = &response;
  message.amount = 1;

  // Encode the message
  uint8_t* encodedMessage = encodeOutputMessage(&message);

  const int expectedLength = 8;

  uint8_t expected[expectedLength] = {10,6,8,1,18,2,56,6};

  for(int i = 0; i < expectedLength; i++){
    if(encodedMessage[i] != expected[i]){
      test.failed = 1;
      char* msg;
      sprintf(&msg, "Expected %d at index %d, but got %d", expected[i], i, encodedMessage[i]);
      test.message = msg;
      return test;
    }
  }

  test.failed = 0;

  return test;

}