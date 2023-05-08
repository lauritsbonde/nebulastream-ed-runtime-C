#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "EndDeviceProtocol.pb.h"
#include "operators.h"
#include "pb_encode.h"

EndDeviceProtocol_Data init_data(Instruction instr);
EndDeviceProtocol_QueryResponse init_query_response(QueryResponse query);
EndDeviceProtocol_Output* init_output(OutputMessage *_output);

bool encode_output_message(pb_ostream_t * stream, OutputMessage msg);
bool decode_output_message(pb_istream_t *stream);

#endif