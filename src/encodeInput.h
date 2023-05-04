#ifndef ENCODEINPUT_H
#define ENCODEINPUT_H


#include <stdlib.h>
#include <stdio.h>
#include "operators.h"
// #include "../../proto/EndDeviceProtocol.pb.h"

// An instruction corresponds to the Data type in .proto


void* encode_instruction (Instruction *instr);
void* encode_expression (Expression *exp);
void* encode_map_operation (Map *map);
void* encode_filter_operation (Filter *filter);
void* encode_window_operation (Window *window);
void* encode_operation (Operation *op);
uint8_t* encode_message (Message *message);

#endif