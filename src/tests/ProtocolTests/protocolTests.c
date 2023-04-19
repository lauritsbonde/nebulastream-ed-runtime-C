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

  const int numTests = 21;
  res.total += numTests;

  res.tests = malloc(sizeof(Test) * numTests);
  
  //INPUT message tests

  res.tests[0] = prepareInstructionTest();
  res.tests[1] = prepareExpressionTest();
  res.tests[2] = prepareMapTest();
  res.tests[3] = prepareFilterTest();
  res.tests[4] = prepareWindowTest();
  res.tests[5] = prepareOperationTestMap();
  res.tests[6] = prepareOperationTestFilter();
  res.tests[7] = prepareOperationTestWindow();
  res.tests[8] = prepareQueryTest();
  res.tests[9] = prepareMessageTest();

  res.tests[10] = instructionGetsEncoded();
  res.tests[11] = expressionGetsEncoded();
  res.tests[12] = mapGetsEncoded();
  res.tests[13] = filterGetsEncoded();
  res.tests[14] = windowGetsEncoded();
  res.tests[15] = operationGetsEncodedMap();
  res.tests[16] = operationGetsEncodedFilter();
  res.tests[17] = operationGetsEncodedWindow();
  
  res.tests[18] = messageGetsEncoded();
  res.tests[19] = messageGetsDecoded();

  //OUTPUT message tests
  res.tests[20] = outputMessageGetsEncoded();

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

Test prepareFilterTest(){
  Test test;
  test.name = "Filter is prepared to EndDeviceProtocol__FilterOperation";

  const int numberOfInstructions = 2;

  // Create a filter
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

  Filter filter;
  filter.predicate = &exp;

  // Prepare the filter
  EndDeviceProtocol__FilterOperation *preparedFilter = prepare_filter_operation(&filter);

  // check the filter has the correct number of instructions
  if(preparedFilter->n_predicate == numberOfInstructions){
    test.failed = 0;
  } else {
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected filter to have %d instructions, but had %d", numberOfInstructions, preparedFilter->n_predicate);
    test.message = msg;
  }

  return test;
}

Test prepareWindowTest(){
  Test test;
  test.name = "Window is prepared to EndDeviceProtocol__WindowOperation";

  // Create a window
  Window window;
  window.size = 10;
  window.sizeType = TIMEBASED;
  window.aggregationType = MAX;
  window.startAttribute = 1;
  window.endAttribute = 2;
  window.resultAttribute = 3;
  window.readAttribute = 4;

  // Prepare the window
  EndDeviceProtocol__WindowOperation *preparedWindow = prepare_window_operation(&window);

  if(preparedWindow->size != 10){
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected window to have size %d, but had %d", 10, preparedWindow->size);
    test.message = msg;
    return test;
  } 
  
  if(preparedWindow->sizetype != TIMEBASED){
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected window to have sizeType %d, but had %d", TIMEBASED, preparedWindow->sizetype);
    test.message = msg;
    return test;
  }
  
  if(preparedWindow->aggregationtype != MAX){
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected window to have aggregationType %d, but had %d", MAX, preparedWindow->aggregationtype);
    test.message = msg;
    return test;
  }

  if(preparedWindow->startattribute != 1){
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected window to have startAttribute %d, but had %d", 1, preparedWindow->startattribute);
    test.message = msg;
    return test;
  }

  if(preparedWindow->endattribute != 2){
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected window to have endAttribute %d, but had %d", 2, preparedWindow->endattribute);
    test.message = msg;
    return test;
  }

  if(preparedWindow->resultattribute != 3){
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected window to have resultAttribute %d, but had %d", 3, preparedWindow->resultattribute);
    test.message = msg;
    return test;
  }

  if(preparedWindow->readattribute != 4){
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected window to have readAttribute %d, but had %d", 4, preparedWindow->readattribute);
    test.message = msg;
    return test;
  }

  test.failed = 0;
  return test;
}

Test prepareOperationTestMap(){
  Test test;
  test.name = "Operation is prepared to EndDeviceProtocol__Operation (MAP)";

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

  Operation operation;
  operation.operation.map = &map;
  operation.unionCase = 1;

  // Prepare the operation
  EndDeviceProtocol__Operation *preparedOperation = prepare_operation(&operation);

  if(preparedOperation->operation_case != END_DEVICE_PROTOCOL__OPERATION__OPERATION_MAP){
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected operation to have operation_case %d, but had %d", END_DEVICE_PROTOCOL__OPERATION__OPERATION_MAP, preparedOperation->operation_case);
    test.message = msg;
    return test;
  }

  test.failed = 0;
  return test;
}

Test prepareOperationTestFilter(){
  Test test;
  test.name = "Operation is prepared to EndDeviceProtocol__Operation (FILTER)";

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

  Filter filter;
  filter.predicate = &exp;

  Operation operation;
  operation.operation.filter = &filter;
  operation.unionCase = 2;

  // Prepare the operation
  EndDeviceProtocol__Operation *preparedOperation = prepare_operation(&operation);

  if(preparedOperation->operation_case != END_DEVICE_PROTOCOL__OPERATION__OPERATION_FILTER){
    test.failed = 1;
    char* msg;
    sprintf(&msg, "Expected operation to have operation_case %d, but had %d", END_DEVICE_PROTOCOL__OPERATION__OPERATION_FILTER, preparedOperation->operation_case);
    test.message = msg;
    return test;
  }

  test.failed = 0;
  return test;
}

Test prepareOperationTestWindow(){
  Test test;
  test.name = "Operation is prepared to EndDeviceProtocol__Operation (WINDOW)";

  Window window;
  window.size = 10;
  window.sizeType = TIMEBASED;
  window.aggregationType = MAX;
  window.startAttribute = 1;
  window.endAttribute = 2;
  window.resultAttribute = 3;
  window.readAttribute = 4;

  Operation operation;
  operation.operation.window = &window;
  operation.unionCase = 3;

  // Prepare the operation
  EndDeviceProtocol__Operation *preparedOperation = prepare_operation(&operation);

  if(preparedOperation->operation_case != END_DEVICE_PROTOCOL__OPERATION__OPERATION_WINDOW){
    test.failed = 1;
    char* msg[100];
    snprintf(&msg,100, "Expected operation to have operation_case %d, but had %d", END_DEVICE_PROTOCOL__OPERATION__OPERATION_WINDOW, preparedOperation->operation_case);
    test.message = msg;
    return test;
  }

  test.failed = 0;
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

Test filterGetsEncoded(){
  Test test;
  test.name = "Filter gets encoded";

  const int numberOfInstructions = 2;

  // Create a filter
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

  Filter filter;
  filter.predicate = &exp;

  // Encode the filter
  void* encodedFilter = encode_filter_operation(&filter);

  // Check if the filter has the correct size
  test.failed = 0;
  return test;
}

Test windowGetsEncoded(){
  Test test;
  test.name = "Window gets encoded";

  Window window;
  window.size = 10;
  window.sizeType = TIMEBASED;
  window.aggregationType = MAX;
  window.startAttribute = 1;
  window.endAttribute = 2;
  window.resultAttribute = 3;
  window.readAttribute = 4;

  // Encode the window
  void* encodedWindow = encode_window_operation(&window);

  // Check if the window has the correct size
  test.failed = 0;
  return test;
}

Test operationGetsEncodedMap(){
  Test test;
  test.name = "Operation gets encoded (MAP)";

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

  Operation operation;
  operation.operation.map = &map;
  operation.unionCase = 1;

  // Encode the map
  void* encodedMap = encode_operation(&operation);

  // Check if the map has the correct size
  test.failed = 0;
  return test;
}

Test operationGetsEncodedFilter(){
  Test test;
  test.name = "Operation gets encoded (FILTER)";

  const int numberOfInstructions = 2;

  // Create a filter
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

  Filter filter;
  filter.predicate = &exp;

  Operation op;
  op.operation.filter = &filter;
  op.unionCase = 2;

  // Encode the operation
  void* encodedFilter = encode_operation(&op);

  // Check if the filter has the correct size
  test.failed = 0;
  return test;

}

Test operationGetsEncodedWindow(){
  Test test;
  test.name = "Operation gets encoded (WINDOW)";

  Window window;
  window.size = 10;
  window.sizeType = TIMEBASED;
  window.aggregationType = MAX;
  window.startAttribute = 1;
  window.endAttribute = 2;
  window.resultAttribute = 3;
  window.readAttribute = 4;

  Operation op;
  op.operation.window = &window;
  op.unionCase = 3;

  // Encode the operation
  void* encodedOperation = encode_operation(&op);

  // Check if the window has the correct size
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

  Operation operation;
  operation.operation.map = &map;
  operation.unionCase = 1;

  Query query;
  query.operations = &operation;
  query.amount = 1;

  Message message;
  message.queries = &query;
  message.amount = 1;

  // Encode the message
  uint8_t* encodedMessage = encode_message(&message);
  
  const int expectedLength = 16;

  uint8_t expected[expectedLength] = {10, 14, 10, 12, 10, 10, 10, 2, 8, 0, 10, 2, 56, 6, 16, 1};

  for(int i = 0; i < expectedLength; i++){
    if(encodedMessage[i] != expected[i]){
      test.failed = 1;
      char* msg[100];
      sprintf(&msg, "Expected: %d, got: %d\n", expected[i], encodedMessage[i]);
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

  Operation operation;
  operation.operation.map = &map;
  operation.unionCase = 1;

  Query query;
  query.operations = &operation;
  query.amount = 1;

  Message message;
  message.queries = &query;
  message.amount = 1;

  // Encode the message
  uint8_t* encodedMessage = encode_message(&message);

  // Decode the message
  Message decodedMessage = decodeMessage(encodedMessage, 16);


  int expectedQueryAmount = 1;
  int expectedOperationAmount = 1;
  int expectedInstructionAmount = 2;

  int expectedInstruction1Data = 0;
  int expectedInstruction1UnionCase = 0;

  int expectedInstruction2Data = 3;
  int expectedInstruction2UnionCase = 2;

  if(decodedMessage.amount != expectedQueryAmount) {
    test.failed = 1;
    char* msg[100];
    snprintf(&msg, 100, "Expected message to have %d queries, but had %d", expectedQueryAmount, decodedMessage.amount);
    test.message = msg[100];
    return test;
  }

  if(decodedMessage.queries->amount != expectedOperationAmount) {
    test.failed = 1;
    char* msg[100];
    snprintf(&msg, 100, "Expected query to have %d operations, but had %d", expectedOperationAmount, decodedMessage.queries->amount);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->operation.map->expression->p_size != expectedInstructionAmount) {
    test.failed = 1;
    char* msg[100];
    snprintf(&msg, "Expected operation to have %d instructions, but had %d", expectedInstructionAmount, decodedMessage.queries->operations->operation.map->expression->p_size);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->operation.map->expression->program[0].unionCase != expectedInstruction1UnionCase) {
    test.failed = 1;
    char* msg[100];
    snprintf(&msg, "Expected instruction 1 to have unionCase %d, but had %d", expectedInstruction1UnionCase, decodedMessage.queries->operations->operation.map->expression->program[0].unionCase);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->operation.map->expression->program[0].data._instruction != expectedInstruction1Data) {
    test.failed = 1;
    char* msg[100];
    snprintf(&msg, 100, "Expected instruction 1 to have data %d, but had %d", expectedInstruction1Data, decodedMessage.queries->operations->operation.map->expression->program[0].data._instruction);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->operation.map->expression->program[1].unionCase != expectedInstruction2UnionCase) {
    test.failed = 1;
    char* msg[100];
    snprintf(&msg,100, "Expected instruction 2 to have unionCase %d, but had %d", expectedInstruction2UnionCase, decodedMessage.queries->operations->operation.map->expression->program[1].unionCase);
    test.message = msg;
    return test;
  }

  if(decodedMessage.queries->operations->operation.map->expression->program[1].data._int != expectedInstruction2Data) {
    test.failed = 1;
    char* msg[100];
    snprintf(&msg, 100, "Expected instruction 2 to have data %d, but had %d", expectedInstruction2Data, decodedMessage.queries->operations->operation.map->expression->program[1].data._int);
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