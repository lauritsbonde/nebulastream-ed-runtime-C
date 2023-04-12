#include <stdio.h>
#include "decodeInput.h"
#include "../../operators/operators.h"
#include "../../proto/EndDeviceProtocol.pb-c.h"

Instruction decodeInstructionucion(EndDeviceProtocol__Data *data) {

}

//TODO: in real life, we would not get the size
Message decodeMessage(uint8_t* input, int size) {
  EndDeviceProtocol__Message *decoded;
  decoded = end_device_protocol__message__unpack(NULL, (size_t) size, input);
  if (decoded == NULL)
  {
    printf("error unpacking incoming message\n");
    //TODO: Handle error
  }

  // Map to our own datatype
  Message msg;
  msg.amount = decoded->n_queries;
  msg.queries = calloc(msg.amount, sizeof(Query));

  for(int i = 0; i < msg.amount; i++){
    msg.queries[i] = edpQueryToQueryType(decoded->queries[i]);
  }

  // Free the memory
  end_device_protocol__message__free_unpacked(decoded, NULL);

  return msg;
} 


Instruction dataToInstructionType(EndDeviceProtocol__Data *data){
  Instruction instr;
  if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA_INSTRUCTION){ 
    instr.unionCase = 0;
    instr.data._instruction = data->instruction;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__UINT8){ // There could be some conversion problems here
    instr.unionCase = 1;
    instr.data._uint32 = data->_uint32;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__UINT16){ // There could be some conversion problems here
    instr.unionCase = 1;
    instr.data._uint32 = data->_uint32;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__UINT32){
    instr.unionCase = 1;
    instr.data._uint32 = data->_uint32;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__UINT64){ // There could be some conversion problems here
    instr.unionCase = 1;
    instr.data._uint32 = data->_uint32;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__INT8){
    instr.unionCase = 2;
    instr.data._int = data->_int8;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__INT16){
    instr.unionCase = 2;
    instr.data._int = data->_int16;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__INT32){
    instr.unionCase = 2;
    instr.data._int = data->_int32;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__INT64){
    instr.unionCase = 2;
    instr.data._int = data->_int64;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__FLOAT){
    instr.unionCase = 3;
    instr.data._float = data->_float;
    return instr;
  } else if(data->data_case == END_DEVICE_PROTOCOL__DATA__DATA__DOUBLE){
    instr.unionCase = 4;
    instr.data._double = data->_double;
    return instr;
  }

  //TODO: Handle error
  instr.unionCase = -1;
  return instr;
}

Map mapOperationToMapType(EndDeviceProtocol__MapOperation *op) {
  Map map;
  map.attribute = op->attribute;
  map.expression = malloc(sizeof(Expression));

  Expression *e;
  e->p_size = op->n_function;
  e->program = malloc(sizeof(Instruction) * e->p_size);
  
  for(int i = 0; i < e->p_size; i++) {
    e->program[i] = dataToInstructionType(op->function[i]);
  }

  map.expression = e;
  return map;
}

Query edpQueryToQueryType(EndDeviceProtocol__Query *query){
  Query q;
  q.amount = query->n_operations;
  q.operations = malloc(sizeof(Map) * q.amount);

  for(int i = 0; i< q.amount; i++) {
    q.operations[i] = mapOperationToMapType(query->operations[i]);
  }
  return q;
}