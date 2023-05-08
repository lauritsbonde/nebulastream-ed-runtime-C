
#include "encodeInput.h"
#include "operators.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "encodeOutput.h"
#include "EndDeviceProtocol.pb.h"

EndDeviceProtocol_MapOperation *init_map_operation(Map *map){
  EndDeviceProtocol_MapOperation *storage = (EndDeviceProtocol_MapOperation *) malloc(sizeof(EndDeviceProtocol_MapOperation));
  EndDeviceProtocol_MapOperation current = EndDeviceProtocol_MapOperation_init_zero;
  
  for(int i = 0; i < map->expression->p_size; i++){
    current.function[i] = *(init_data(map->expression->program[i]));
  }
  
  current.attribute = map->attribute;
  current.function_count = map->expression->p_size;

  storage[0] = current;
  return storage;
}

EndDeviceProtocol_FilterOperation *init_filter_operation(Filter *filter) {
  EndDeviceProtocol_FilterOperation *storage = (EndDeviceProtocol_FilterOperation *) malloc(sizeof(EndDeviceProtocol_FilterOperation));
  EndDeviceProtocol_FilterOperation current = EndDeviceProtocol_FilterOperation_init_zero;
  
  for (int i = 0; i < filter->predicate->p_size; i++) {
    current.predicate[i] = *(init_data(filter->predicate->program[i]));
  }
  current.predicate_count = filter->predicate->p_size;
  
  storage[0] = current;
  return storage;
}

EndDeviceProtocol_WindowOperation *init_window_operation(Window *window){
  EndDeviceProtocol_WindowOperation *storage = (EndDeviceProtocol_WindowOperation *) malloc(sizeof(EndDeviceProtocol_WindowOperation));
  EndDeviceProtocol_WindowOperation current = EndDeviceProtocol_WindowOperation_init_zero;

  current.size = window->size;
  if(window->sizeType == TIMEBASED){
    current.sizeType = EndDeviceProtocol_WindowSizeType_TIMEBASED;
  } else if (window->sizeType == COUNTBASED){
    current.sizeType = EndDeviceProtocol_WindowSizeType_COUNTBASED;
  } else {
    printf("unknown window sizetype!\n");
  }

  if(window->aggregationType == MIN){
    current.aggregationType = EndDeviceProtocol_WindowAggregationType_MIN;
  } else if(window->aggregationType == MAX){
    current.aggregationType = EndDeviceProtocol_WindowAggregationType_MAX;
  } else if(window->aggregationType == SUM){
    current.aggregationType = EndDeviceProtocol_WindowAggregationType_SUM;
  } else if(window->aggregationType == AVG){
    current.aggregationType = EndDeviceProtocol_WindowAggregationType_AVG;
  } else if(window->aggregationType == COUNT){
    current.aggregationType = EndDeviceProtocol_WindowAggregationType_COUNT;
  } else {
    printf("Unkown window aggregation type!\n");
  }
  
  current.startAttribute = window->startAttribute;
  current.endAttribute = window->endAttribute;
  current.resultAttribute = window->resultAttribute;
  current.readAttribute = window->readAttribute;

  storage[0] = current;
  return storage;
}

EndDeviceProtocol_Operation *init_operation(Operation *op){
  EndDeviceProtocol_Operation *storage = (EndDeviceProtocol_Operation *) malloc(sizeof(EndDeviceProtocol_Operation));
  EndDeviceProtocol_Operation current = EndDeviceProtocol_Operation_init_zero;

  if(op->unionCase == 0){
    current.operation.map = *(init_map_operation(op->operation.map));
    current.which_operation = EndDeviceProtocol_Operation_map_tag;
  } else if(op->unionCase == 1){
    current.operation.filter = *(init_filter_operation(op->operation.filter));
    current.which_operation = EndDeviceProtocol_Operation_filter_tag;
  } else if(op->unionCase == 2){
    current.operation.window = *(init_window_operation(op->operation.window));
    current.which_operation = EndDeviceProtocol_Operation_window_tag;
  } else {
    printf("Unkonwn operation type!");
  }

  storage[0] = current;
  return storage;
}

EndDeviceProtocol_Query *init_query(Query *query){
  EndDeviceProtocol_Query *storage = (EndDeviceProtocol_Query *) malloc(sizeof(EndDeviceProtocol_Query));
  EndDeviceProtocol_Query current = EndDeviceProtocol_Query_init_zero;

  for(int i = 0; i < query->amount; i++){
    current.operations[i] = *(init_operation(&query->operations[i]));
  }

  current.operations_count = query->amount;

  storage[0] = current;
  return storage;
}

EndDeviceProtocol_Message *init_message(Message *msg) {
  EndDeviceProtocol_Message * storage = (EndDeviceProtocol_Message *) malloc(sizeof(EndDeviceProtocol_Message));
  EndDeviceProtocol_Message message = EndDeviceProtocol_Message_init_zero;

  for (int i = 0; i < msg->amount; i++) {
    Query q = msg->queries[i];
    message.queries[i] = *(init_query(&q));
  }

  message.queries_count = msg->amount;
  storage[0] = message;
  return storage;  
}

bool encode_message(pb_ostream_t *stream, Message message){
  bool status;
  
  EndDeviceProtocol_Message msg = *init_message(message);
  
  status = pb_encode(stream, EndDeviceProtocol_Message_fields, &msg);
  
  if (!status)
  {
    printf("Encoding failed: %s\n", PB_GET_ERROR(stream));
  }

  return status;
}

bool decode_input_message(pb_istream_t *stream) {
  EndDeviceProtocol_Message message = EndDeviceProtocol_Message_init_zero;
  
  bool status = pb_decode(stream, EndDeviceProtocol_Message_fields, &message);

  printf("Message amount: %d\n", message.queries_count);

  printf("Decoded value: %d\n", message.queries[0].operations[0].operation.map.function[4].data.instruction);
  return status;
}
