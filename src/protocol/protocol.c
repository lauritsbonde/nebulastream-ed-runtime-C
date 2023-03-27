// #include <stdio.h>
// #include <stdlib.h>
// #include "protocol.h"
// #include "proto/EndDeviceProtocol.pb.h"
// #include <pb_encode.h>
// #include <pb_decode.h>
// #include "../proto/EndDeviceProtocol.pb.h"

// EndDeviceProtocol_Output encodeMessage(OutputMessage message)
// {
//     uint8_t buffer[128];
//     size_t message_length;
//     bool status;

//     pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

//     status = pb_encode(&stream, EndDeviceProtocol_Output_fields, &message);
//     message_length = stream.bytes_written;

//     if (!status)
//     {
//         printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
//     }
//     else
//     {
//         printf("Succes!");
//         for (int i = 0; i < 128; i++)
//         {
//             // TODO: "Send" the message somewhere
//             printf("%d", buffer[i]);
//         };
//         printf("\n done \n");
//     }
//     EndDeviceProtocol_Output output;
//     return output;
// }

// Message decodeInputMessage(EndDeviceProtocol_Message message)
// {
//     Message msg;
//     return msg;
// }