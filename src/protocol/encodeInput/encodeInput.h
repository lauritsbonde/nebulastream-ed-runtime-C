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
EndDeviceProtocol__Query* prepare_query (Query *query);
EndDeviceProtocol__Message *prepare_message(Message *message);


void* encode_instruction (Instruction *instr);
void* encode_expression (Expression *exp);
void* encode_map_operation (Map *map);
uint8_t* encode_message (Message *message);

#endif