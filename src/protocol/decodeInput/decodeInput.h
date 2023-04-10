#ifndef DECODEINPUT_H
#define DECODEINPUT_H

#include "../../operators/operators.h"
#include "../../proto/EndDeviceProtocol.pb-c.h"

Instruction decodeInstructionuction(EndDeviceProtocol__Data *data);

#endif /* DECODEINPUT_H */