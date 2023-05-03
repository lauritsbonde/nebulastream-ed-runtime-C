#ifndef PROTOCOL_H
#define PROTOCOL_H

// #include "../../proto/EndDeviceProtocol.pb.h"
#include "../../operators/operators.h"


uint8_t *encodeOutputMessage(OutputMessage *msg);

#endif