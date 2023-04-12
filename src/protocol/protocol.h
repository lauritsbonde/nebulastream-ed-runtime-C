#ifndef PROTOCOL_H
#define PROTOCOL_H


#include <stdlib.h>
#include "../operators/operators.h"
#include "../proto/EndDeviceProtocol.pb-c.h"

int encodeInputMessage(Message message, uint8_t *buffer);


#endif