#include <stdlib.h>
#include <stdio.h>
#include "protocol.h"
#include "../operators/operators.h"
#include "../proto/EndDeviceProtocol.pb-c.h"


int encodeInputMessage(Message message, uint8_t *buffer)
{
  EndDeviceProtocol__Message msg = END_DEVICE_PROTOCOL__MESSAGE__INIT;
  msg.n_queries = message.amount;
  msg.queries = malloc (sizeof (Query) * msg.n_queries);
  for (int i = 0; i < msg.n_queries; i++) {

    // Create an EndDeviceProtocol__Query
    EndDeviceProtocol__Query query = END_DEVICE_PROTOCOL__QUERY__INIT;
    query.n_operations = message.queries[i].amount;
    query.operations = malloc (sizeof (Operator) * query.n_operations);

    for(int j = 0; j < query.n_operations; j++) {

      // Create an EndDeviceProtocol__Operation
      EndDeviceProtocol__Operation operation = END_DEVICE_PROTOCOL__OPERATION__INIT;
      operation.map->n_function = message.queries[i].operations->amount;
      operation.map->function = malloc (sizeof (Instruction) * operation.map->n_function);

      for(int k = 0; k < operation.map->n_function; k++) {
        // Create an EndDeviceProtocol__Instruction
        EndDeviceProtocol__Data data = END_DEVICE_PROTOCOL__DATA__INIT;
        EndDeviceProtocol__ExpressionInstructions instruction;

        if(message.queries[i].operations[j].function[k].data._int != 0){
          instruction = END_DEVICE_PROTOCOL__EXPRESSION_INSTRUCTIONS__CONST;
        } else {
          instruction = END_DEVICE_PROTOCOL__EXPRESSION_INSTRUCTIONS__SUB;
        }

        data.instruction = instruction;

        operation.map->function[k] = &data;
        
      }
      operation.map->attribute = message.queries[i].operations[j].attribute;
      query.operations[j] = &operation;
    }
    
    msg.queries[i] = &query;
  }

  size_t len = end_device_protocol__message__get_packed_size(&msg);
  end_device_protocol__message__pack(&msg, buffer);
  return len;
}
