
#include "encodeInput.h"
#include "operators.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "encodeOutput.h"
#include "EndDeviceProtocol.pb.h"

void init_map_operation(Map map, EndDeviceProtocol_MapOperation *out){
  for(int i = 0; i < map.expression->p_size; i++){
    EndDeviceProtocol_Data current = EndDeviceProtocol_Data_init_zero;
    init_data(map.expression->program[i], &current);
    out->function[i] = current;
  }
  
  out->attribute = map.attribute;
  out->function_count = map.expression->p_size;
}

void init_filter_operation(Filter filter, EndDeviceProtocol_FilterOperation *out) {
  for (int i = 0; i < filter.predicate->p_size; i++) {
    EndDeviceProtocol_Data current = EndDeviceProtocol_Data_init_zero;
    init_data(filter.predicate->program[i], &current);
    out->predicate[i] = current;
  }
  out->predicate_count = filter.predicate->p_size;
}

void init_window_operation(Window window, EndDeviceProtocol_WindowOperation *out){
  out->size = window.size;
  if(window.sizeType == TIMEBASED){
    out->sizeType = EndDeviceProtocol_WindowSizeType_TIMEBASED;
  } else if (window.sizeType == COUNTBASED){
    out->sizeType = EndDeviceProtocol_WindowSizeType_COUNTBASED;
  } else {
    printf("unknown window sizetype!\n");
  }

  if(window.aggregationType == MIN){
    out->aggregationType = EndDeviceProtocol_WindowAggregationType_MIN;
  } else if(window.aggregationType == MAX){
    out->aggregationType = EndDeviceProtocol_WindowAggregationType_MAX;
  } else if(window.aggregationType == SUM){
    out->aggregationType = EndDeviceProtocol_WindowAggregationType_SUM;
  } else if(window.aggregationType == AVG){
    out->aggregationType = EndDeviceProtocol_WindowAggregationType_AVG;
  } else if(window.aggregationType == COUNT){
    out->aggregationType = EndDeviceProtocol_WindowAggregationType_COUNT;
  } else {
    printf("Unkown window aggregation type!\n");
  }
  
  out->startAttribute = window.startAttribute;
  out->endAttribute = window.endAttribute;
  out->resultAttribute = window.resultAttribute;
  out->readAttribute = window.readAttribute;
}

void init_operation(Operation op, EndDeviceProtocol_Operation *out){
  if(op.unionCase == 0){
    EndDeviceProtocol_MapOperation current = EndDeviceProtocol_MapOperation_init_zero;
    init_map_operation(*op.operation.map, &current);
    out->operation.map = current;
    out->which_operation = EndDeviceProtocol_Operation_map_tag;
  } else if(op.unionCase == 1){
    EndDeviceProtocol_FilterOperation current = EndDeviceProtocol_FilterOperation_init_zero;
    init_filter_operation(*op.operation.filter, &current);
    out->operation.filter = current;
    out->which_operation = EndDeviceProtocol_Operation_filter_tag;
  } else if(op.unionCase == 2){
    EndDeviceProtocol_WindowOperation current = EndDeviceProtocol_WindowOperation_init_zero;
    init_window_operation(*op.operation.window, &current);
    out->operation.window = current;
    out->which_operation = EndDeviceProtocol_Operation_window_tag;
  } else {
    printf("Unkonwn operation type!");
  }
}

 void init_query(Query query, EndDeviceProtocol_Query *out){
  for(int i = 0; i < query.amount; i++){
    EndDeviceProtocol_Operation current = EndDeviceProtocol_Operation_init_zero;
    init_operation(query.operations[i], &current);
    out->operations[i] = current;
  }

  out->operations_count = query.amount;
}

void init_message(Message msg, EndDeviceProtocol_Message *out) {
  for (int i = 0; i < msg.amount; i++) {
    EndDeviceProtocol_Query current = EndDeviceProtocol_Query_init_zero;
    init_query(msg.queries[i], &current);
    out->queries[i] = current;
  }

  out->queries_count = msg.amount;
}

bool encode_message(pb_ostream_t *stream, Message message){
  bool status;

  EndDeviceProtocol_Message msg = EndDeviceProtocol_Message_init_zero;
  init_message(message, &msg);
  
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
