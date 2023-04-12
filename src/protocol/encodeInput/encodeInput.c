
#include "encodeInput.h"
#include "../../operators/operators.h"
#include "../../proto/EndDeviceProtocol.pb-c.h"

EndDeviceProtocol__Data* prepare_instruction(Instruction *instruction)
{
  EndDeviceProtocol__Data *storage = (EndDeviceProtocol__Data *) malloc(sizeof(EndDeviceProtocol__Data));
  EndDeviceProtocol__Data data = END_DEVICE_PROTOCOL__DATA__INIT;
  
  // The type of data is stored in Instruction struct
  if(instruction->unionCase == 0){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA_INSTRUCTION;
    data.instruction = instruction->data._instruction;
  } else if(instruction->unionCase == 1){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA__UINT32;
    data._float = instruction->data._uint32;
  } else if(instruction->unionCase == 2){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA__INT16;
    data._int16 = instruction->data._int;
  } else if(instruction->unionCase == 3){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA__FLOAT;
    data._float = instruction->data._float;
  } else if(instruction->unionCase == 4){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA__DOUBLE;
    data._double = instruction->data._double;
  }

  storage[0] = data;

  return storage;
}

EndDeviceProtocol__Expression* prepare_expression (Expression *exp){
  EndDeviceProtocol__Expression *storage = (EndDeviceProtocol__Expression *) malloc(sizeof(EndDeviceProtocol__Expression));

  EndDeviceProtocol__Expression expression = END_DEVICE_PROTOCOL__EXPRESSION__INIT;
  
  expression.n_instructions = exp->p_size;
  expression.instructions = calloc(exp->p_size, sizeof(EndDeviceProtocol__Data));
  
  for(int i = 0; i < exp->p_size; i++)
  {
    expression.instructions[i] = prepare_instruction(&exp->program[i]);
  }

  storage[0] = expression;

  return storage;
}

EndDeviceProtocol__MapOperation* prepare_map_operation (Map *map) {
  EndDeviceProtocol__MapOperation *storage = (EndDeviceProtocol__MapOperation *) malloc(sizeof(EndDeviceProtocol__MapOperation));
  EndDeviceProtocol__MapOperation op = END_DEVICE_PROTOCOL__MAP_OPERATION__INIT;
  
  op.function = calloc(map->expression->p_size, sizeof(EndDeviceProtocol__Data));
  op.n_function = map->expression->p_size;
  for (int i = 0; i < map->expression->p_size; i++) {
    op.function[i] = prepare_instruction(&map->expression->program[i]);
  }
  op.attribute = map->attribute;

  storage[0] = op;
  return storage;
}


// TODO: Make this work with all operations. Only Map is supported
EndDeviceProtocol__Query* prepare_query (Query *query) {
  EndDeviceProtocol__Query *storage = (EndDeviceProtocol__Query *) malloc(sizeof(EndDeviceProtocol__Query));
  EndDeviceProtocol__Query q = END_DEVICE_PROTOCOL__QUERY__INIT;

  q.operations = calloc(query->amount, sizeof(EndDeviceProtocol__MapOperation));
  q.n_operations = query->amount;
  for(int i = 0; i < query->amount; i++) {
    q.operations[i] = prepare_map_operation(&query->operations[i]);
  }

  storage[0] = q;
  return storage;
}

EndDeviceProtocol__Message* prepare_message (Message *message) {
  EndDeviceProtocol__Message *storage = (EndDeviceProtocol__Message *) malloc(sizeof(EndDeviceProtocol__Message));
  EndDeviceProtocol__Message msg = END_DEVICE_PROTOCOL__MESSAGE__INIT;

  msg.n_queries = message->amount;
  msg.queries = calloc(message->amount, sizeof(EndDeviceProtocol__Query));
  for (int i = 0; i < message->amount; i++) {
    msg.queries[i] = prepare_query(&message->queries[i]);
  }

  storage[0] = msg;
  return storage;
}

void cleanup(EndDeviceProtocol__Message *msg) {
  for (int i = 0; i < msg->n_queries; i++) {
    EndDeviceProtocol__Query *q = msg->queries[i];
    for (int j = 0; j < q->n_operations; j++) {
      EndDeviceProtocol__MapOperation *msq = q->operations[j];
      for (int k = 0; k < msq->n_function; k++){
        EndDeviceProtocol__Data *data = msq->function[k];
        free(data);
      }
      free(msq->function);
    }
    free(q->operations);
  }
  free(msg->queries);
}

uint8_t* encode_message (Message *message) {
  uint8_t *buf;
  size_t len;

  EndDeviceProtocol__Message *prepared_msg = prepare_message(message);

  len = end_device_protocol__message__get_packed_size(prepared_msg);
  buf = malloc(len);

  end_device_protocol__message__pack(prepared_msg, buf);

  cleanup(prepared_msg);

  
  return buf;
}

void* encode_instruction (Instruction *instr) {
  void *buf;
  size_t len;

  EndDeviceProtocol__Data *prepared_instr = prepare_instruction(instr);

  len = end_device_protocol__data__get_packed_size(prepared_instr);

  buf = malloc(len);

  end_device_protocol__data__pack(prepared_instr, buf);
  
  return buf;
}

void* encode_expression (Expression *exp) {
  void *buf;
  size_t len;

  EndDeviceProtocol__Expression *prepared_exp = prepare_expression(exp);

  len = end_device_protocol__expression__get_packed_size(prepared_exp);

  buf = malloc(len);

  end_device_protocol__expression__pack(prepared_exp, buf);
  
  return buf;
}

void* encode_map_operation (Map *map) {
  void *buf;
  size_t len;

  EndDeviceProtocol__MapOperation *prepared_map = prepare_map_operation(map);

  len = end_device_protocol__map_operation__get_packed_size(prepared_map);

  buf = malloc(len);

  end_device_protocol__map_operation__pack(prepared_map, buf);
  
  return buf;
}