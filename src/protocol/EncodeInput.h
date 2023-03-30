#ifndef ENCODEINPUT_H
#define ENCODEINPUT_H


#include <stdlib.h>
#include <stdio.h>
#include "../operators/operators.h"
#include "../proto/EndDeviceProtocol.pb-c.h"

// An instruction corresponds to the Data type in .proto
EndDeviceProtocol__Data* prepare_instruction(Instruction *instruction);
// EndDeviceProtocol__Expression prepare_expression (Expression *exp);
// EndDeviceProtocol__MapOperation prepare_map_operation (Map *map);

#endif