#include <stdlib.h>
#include <stdio.h>

#include "encodeOutput.h"
#include "pb_encode.h"
// #include "../../proto/EndDeviceProtocol.pb.h"
#include "operators.h"




// uint8_t *encodeOutputMessage(OutputMessage *msg)
// {

// }

//Encode repeated fields
// stream: Output stream to write to
// field: iterator for the field currently being encoded or decoded
// arg: pointer to the arg field in the pb_calback_t structure, which is used to pass data to the callback.
// bool (*encode)(pb_ostream_t *stream, const pb_field_iter_t *field, void * const *arg)
// {
//   return false;
// }