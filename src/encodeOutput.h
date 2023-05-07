#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "EndDeviceProtocol.pb.h"
#include "operators.h"
#include "pb_encode.h"

bool encode_data(Instruction i, pb_ostream_t *stream);
bool decode_one_data(uint8_t *buffer, int length);

bool data_encode(pb_ostream_t *stream, const pb_field_t *field, void *const *arg);
bool encode_query_response(pb_ostream_t *stream, QueryResponse *arg);

bool decode_query_response(pb_istream_t *stream);
bool decode_data(pb_istream_t *stream, const pb_field_t *field, void **arg);
// bool query_response_encode(pb_ostream_t *stream, const pb_field_t *field, void *const *arg);
// bool encode_output(void);

#endif