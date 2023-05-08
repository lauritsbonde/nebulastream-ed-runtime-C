#ifndef ENCODEINPUT_H
#define ENCODEINPUT_H


#include <stdlib.h>
#include <stdio.h>
#include "EndDeviceProtocol.pb.h"
#include "operators.h"

// An instruction corresponds to the Data type in .proto
bool encode_message(pb_ostream_t *stream, Message *message);
bool decode_input_message(pb_istream_t *stream);

EndDeviceProtocol_Message * init_message(Message *msg);
EndDeviceProtocol_Query *init_query(Query *query);
EndDeviceProtocol_Operation *init_operation(Operation *op);
EndDeviceProtocol_WindowOperation *init_window_operation(Window *window);
EndDeviceProtocol_FilterOperation *init_filter_operation(Filter *filter);
EndDeviceProtocol_MapOperation *init_map_operation(Map *map);

#endif