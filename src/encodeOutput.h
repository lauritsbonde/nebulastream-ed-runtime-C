#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "EndDeviceProtocol.pb.h"
#include "operators.h"

bool QueryResponse_callback(pb_istream_t *istream, pb_ostream_t *ostream, const pb_field_iter_t *field);

#endif