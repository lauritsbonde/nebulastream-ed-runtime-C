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

  //TODO: figure out why the space needs to be allocated
  Expression *e = (Expression*)malloc(sizeof(Expression));
  e->p_size = op->n_function;
  e->program = malloc(sizeof(Instruction) * e->p_size);
  
  for(int i = 0; i < e->p_size; i++) {
    e->program[i] = dataToInstructionType(op->function[i]);
  }

  map.expression = e;
  return map;
}

Filter filterToFilterType(EndDeviceProtocol__FilterOperation *op) {
  Filter filter;
  filter.predicate = malloc(sizeof(Expression));

  //TODO: figure out why the space needs to be allocated
  Expression *e = (Expression*)malloc(sizeof(Expression));
  e->p_size = op->n_predicate;
  e->program = malloc(sizeof(Instruction) * e->p_size);
  
  for(int i = 0; i < e->p_size; i++) {
    e->program[i] = dataToInstructionType(op->predicate[i]);
  }

  filter.predicate = e;
  return filter;
}

Window windowToWindowType(EndDeviceProtocol__WindowOperation *op) {
  Window window;
  window.size = op->size;
  window.sizeType = op->sizetype;
  window.aggregationType = op->aggregationtype;
  window.startAttribute = op->startattribute;
  window.endAttribute = op->endattribute;
  window.resultAttribute = op->resultattribute;
  window.readAttribute = op->readattribute;
  return window;
}

Operation operationToOperationType(EndDeviceProtocol__Operation *op) {
  Operation operation;
  if(op->operation_case == END_DEVICE_PROTOCOL__OPERATION__OPERATION_MAP) {
    operation.unionCase = 0;
    operation.operation.map = malloc(sizeof(Map));
    operation.operation.map[0] = mapOperationToMapType(op->map);
  } else if(op->operation_case == END_DEVICE_PROTOCOL__OPERATION__OPERATION_FILTER) {
    operation.unionCase = 1;
    operation.operation.filter = malloc(sizeof(Filter));
    operation.operation.filter[0] = filterToFilterType(op->filter);
  } else if(op->operation_case == END_DEVICE_PROTOCOL__OPERATION__OPERATION_WINDOW) {
    operation.unionCase = 2;
    operation.operation.window = malloc(sizeof(Window));
    operation.operation.window[0] = windowToWindowType(op->window);
  }

  return operation;
}

Query edpQueryToQueryType(EndDeviceProtocol__Query *query){
  Query q;
  q.amount = query->n_operations;
  q.operations = malloc(sizeof(Operation) * q.amount);

  for(int i = 0; i< q.amount; i++) {
    q.operations[i] = operationToOperationType(query->operations[i]);
  }
  return q;
}