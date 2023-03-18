#include <stdio.h>
#include <stdlib.h>
#include "protocol.h"
#include "proto/EndDeviceProtocol.pb.h"
#include <pb_encode.h>
#include <pb_decode.h>
#include "../proto/EndDeviceProtocol.pb.h"

EndDeviceProtocol_Output encodeOutputMessage(OutputMessage message)
{
    uint8_t buffer[128]; // a buffer to hold the encoded message
    size_t message_length;
    bool status;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    // TODO: make message into a EndDeviceProtocol_Output

    status = pb_encode(&stream, EndDeviceProtocol_Output_fields, &message);
    message_length = stream.bytes_written;

    if (!status)
    {
        printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
    }
    else
    {
        printf("Succes!");
        for (int i = 0; i < 128; i++)
        {
            // TODO: "Send" the message somewhere
            printf("%d", buffer[i]);
        };
        printf("\n done \n");
    }
    EndDeviceProtocol_Output output;
    return output;
}

Message decodeInputMessage(EndDeviceProtocol_Message message)
{
    uint8_t buffer[128];
    size_t message_length;
    bool status;

    pb_istream_t in_stream = pb_istream_from_buffer(buffer, message_length);

    status = pb_decode(&in_stream, EndDeviceProtocol_MapOperation_fields, &message);

    if (!status)
    {
        printf("Decoding failed: %s\n", PB_GET_ERROR(&in_stream));
    }

    // TODO: Create message struct.

    Message msg;
    return msg;
}

EndDeviceProtocol_Message encodeInputMessage(Message message)
{
    uint8_t buffer[128]; // a buffer to hold the encoded message
    size_t message_length;
    bool status;

    EndDeviceProtocol_Message encodedMessage = EndDeviceProtocol_Message_init_zero;
    encodedMessage.queries = ;
}

bool messageCallback(pb_istream_t *istream, pb_ostream_t *ostream, const pb_field_iter_t *field)
{
    PB_UNUSED(istream);
    if (ostream != NULL && field->tag == EndDeviceProtocol_Message_queries_tag)
    {
        EndDeviceProtocol_Query queries = {};

        while (field->pData != NULL)
        {
            queries.operations =
        }
    }
}

bool queryCallback(pb_istream_t *istream, pb_ostream_t *ostream, const pb_field_iter_t *field)
{
    PB_UNUSED(istream);
    if (ostream != NULL && field->tag == EndDeviceProtocol_Query_operations_tag)
    {
        // TODO: change to operations
        EndDeviceProtocol_MapOperation mapOperation = {};

        while (field->pData != NULL)
        {
            mapOperation.operations =
        }
    }
}

bool mapCallback(pb_istream_t *istream, pb_ostream_t *ostream, const pb_field_iter_t *field)
{
    PB_UNUSED(istream);
    if (ostream != NULL && field->tag == EndDeviceProtocol_MapOperation_function_tag)
    {
        EndDeviceProtocol_Data data = {};

        while (field->pData != NULL)
        {
            if (!pb_encode_tag_for_field(ostream, field))
            {
                return false;
            }

            if (!pb_encode_submessage(ostream, EndDeviceProtocol_Data_fields, &data))
            {
                return false;
            }
        }
    }
    return true;
}

// This one should probably not be used
bool encodeData(pb_istream_t *istream, pb_ostream_t *ostream, const pb_field_iter_t *field)
{
    PB_UNUSED(istream);
    if (ostream != NULL)
    {
    }
}