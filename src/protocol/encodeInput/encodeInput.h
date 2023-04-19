#ifndef ENCODEINPUT_H
#define ENCODEINPUT_H


#include <stdlib.h>
#include <stdio.h>
#include "../../operators/operators.h"
#include "../../proto/EndDeviceProtocol.pb-c.h"

// An instruction corresponds to the Data type in .proto
EndDeviceProtocol__Data* prepare_instruction(Instruction *instruction);
EndDeviceProtocol__Expression* prepare_expression (Expression *exp);
EndDeviceProtocol__MapOperation* prepare_map_operation (Map *map);
EndDeviceProtocol__FilterOperation* prepare_filter_operation (Filter *filter);
EndDeviceProtocol__WindowOperation* prepare_window_operation (Window *window);
EndDeviceProtocol__Operation* prepare_operation (Operation *op);
EndDeviceProtocol__Query* prepare_query (Query *query);
EndDeviceProtocol__Message *prepare_message(Message *message);


void* encode_instruction (Instruction *instr);
void* encode_expression (Expression *exp);
void* encode_map_operation (Map *map);
void* encode_filter_operation (Filter *filter);
void* encode_window_operation (Window *window);
void* encode_operation (Operation *op);
uint8_t* encode_message (Message *message);

#endif