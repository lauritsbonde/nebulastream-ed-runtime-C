#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "EndDeviceProtocol.pb.h"
#include "operators.h"
#include "pb_encode.h"

bool encode_output_message(pb_ostream_t * stream);
bool decode_output_message(pb_istream_t *stream);

#endif