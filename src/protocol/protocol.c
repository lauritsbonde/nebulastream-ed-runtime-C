#include <stdlib.h>
#include <stdio.h>
#include "protocol.h"
#include "../operators/operators.h"
#include "../proto/EndDeviceProtocol.pb-c.h"


int encodeInputMessage(Message message, uint8_t *buffer)
{
  // EndDeviceProtocol__Message msg = END_DEVICE_PROTOCOL__MESSAGE__INIT;
  // msg.n_queries = message.amount;
  // msg.queries = malloc (sizeof (Query) * msg.n_queries);
  // printf("1\n");
  // for (int i = 0; i < msg.n_queries; i++) {
  //   printf("2 - i: %d\n", i);

  //   // Create an EndDeviceProtocol__Query
  //   EndDeviceProtocol__Query query = END_DEVICE_PROTOCOL__QUERY__INIT;
  //   query.n_operations = message.queries[i].amount;
  //   printf("3 - i: %d\n", i);
  //   query.operations = malloc (sizeof (Operator) * query.n_operations);

  //   for(int j = 0; j < query.n_operations; j++) {
  //     printf("4 - i: %d, j: %d\n", i, j);

  //     // Create an EndDeviceProtocol__Operation
  //     EndDeviceProtocol__Operation operation = END_DEVICE_PROTOCOL__OPERATION__INIT;
  //     printf("4.1 - i: %d, j: %d\n", i, j);
  //     operation.map->n_function = message.queries[i].operations->amount;
      
  //     printf("4.2 - i: %d, j: %d\n", i, j);
  //     operation.map->function = malloc (sizeof (Instruction) * operation.map->n_function);
  //     printf("5 - i: %d, j: %d\n", i, j);
  //     for(int k = 0; k < operation.map->n_function; k++) {
  //       printf("6 - i: %d, j: %d, k: %d\n", i, j, k);
  //       // Create an EndDeviceProtocol__Instruction
  //       EndDeviceProtocol__Data data = END_DEVICE_PROTOCOL__DATA__INIT;
  //       EndDeviceProtocol__ExpressionInstructions instruction;

  //       printf("7 - i: %d, j: %d, k: %d\n", i, j, k);
  //       if(message.queries[i].operations[j].expression[k].Instruction != 0){
  //         instruction = END_DEVICE_PROTOCOL__EXPRESSION_INSTRUCTIONS__CONST;
  //       } else {
  //         instruction = END_DEVICE_PROTOCOL__EXPRESSION_INSTRUCTIONS__SUB;
  //       }

  //       printf("8 - i: %d, j: %d, k: %d\n", i, j, k);

  //       data.instruction = instruction;

  //       operation.map->function[k] = &data;
        
  //       printf("9 - i: %d, j: %d, k: %d\n", i, j, k);
  //     }
  //     operation.map->attribute = message.queries[i].operations[j].attribute;
  //     query.operations[j] = &operation;
  //     printf("10 - i: %d, j: %d\n", i, j);
  //   }
    
  //   printf("11 - i: %d\n", i);
  //   msg.queries[i] = &query;
  // }

  // size_t len = end_device_protocol__message__get_packed_size(&msg);
  // end_device_protocol__message__pack(&msg, buffer);
  // return len;
  return 0;
}
