#include <stdlib.h>
#include "EncodeInput.h"
#include "../operators/operators.h"
#include "../proto/EndDeviceProtocol.pb-c.h"

EndDeviceProtocol__Data* prepare_instruction(Instruction *instruction)
{
  uint32_t len = 0;

  EndDeviceProtocol__Data *storage = (EndDeviceProtocol__Data *) malloc(sizeof(EndDeviceProtocol__Data));

  EndDeviceProtocol__Data data = END_DEVICE_PROTOCOL__DATA__INIT;
  
  // The type of data is stored in Instruction struct
  data.data_case = instruction->unionCase;
  if(instruction->unionCase == END_DEVICE_PROTOCOL__DATA__DATA__INT8){
    data._uint8 = instruction->data._int;
  }

  len = end_device_protocol__data__get_packed_size(&data);

  printf("packed size: %u\n", len);
  storage[0] = data;

  return storage;
}

// EndDeviceProtocol__Expression* prepare_expression (Expression *exp) {  
//   EndDeviceProtocol__Expression expression = END_DEVICE_PROTOCOL__EXPRESSION__INIT;
//   expression.n_instructions = exp->p_size;
//   expression.instructions = calloc(exp->p_size, sizeof(EndDeviceProtocol__Data));
  
//   for(int i = 0; i < exp->p_size; i++)
//   {
//     expression.instructions[i] = prepare_instruction(&exp->program[i]);
//   }

//   return expression;
// }

// EndDeviceProtocol__MapOperation prepare_map_operation (Map *map) {
//     EndDeviceProtocol__MapOperation op = END_DEVICE_PROTOCOL__MAP_OPERATION__INIT;
//     op.function = prepare_expression(&map->expression);
//     op.attribute = map->attribute;

//     return op;
// }

// EndDeviceProtocol__Query prepare_query (Query *query) {
//     EndDeviceProtocol__Query q = END_DEVICE_PROTOCOL__QUERY__INIT;
//     q.
// }