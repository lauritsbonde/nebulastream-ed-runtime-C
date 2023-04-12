#ifndef DECODEINPUT_H
#define DECODEINPUT_H

#include "../../operators/operators.h"
#include "../../proto/EndDeviceProtocol.pb-c.h"

Instruction decodeInstructionuction(EndDeviceProtocol__Data *data);
Message decodeMessage(uint8_t * input, int size);

Instruction dataToInstructionType(EndDeviceProtocol__Data *data);
Map mapOperationToMapType(EndDeviceProtocol__MapOperation *op);
Query edpQueryToQueryType(EndDeviceProtocol__Query *query);

#endif /* DECODEINPUT_H */