#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../proto/EndDeviceProtocol.pb-c.h"
#include "../../operators/operators.h"

EndDeviceProtocol__Data* prepare_instruction_output(Instruction *instruction);
EndDeviceProtocol__Output__QueryResponse* prepareQueryResponse(QueryResponse *response);
EndDeviceProtocol__Output *prepareOutput(OutputMessage *output);
uint8_t *encodeOutputMessage(OutputMessage *msg);
void outputCleanup(EndDeviceProtocol__Output *output);

#endif