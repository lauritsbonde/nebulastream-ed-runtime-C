#ifndef PROTOCOL_H
#define PROTOCOL_H
#endif
#include <stdlib.h>
#include "../operators/operators.h"
#include "proto/EndDeviceProtocol.pb.h"

EndDeviceProtocol_Output encodeMessage(OutputMessage message);
Message decodeInputMessage(EndDeviceProtocol_Message message);