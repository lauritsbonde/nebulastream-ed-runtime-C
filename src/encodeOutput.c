#include <stdlib.h>
#include <stdio.h>

#include "pb_encode.h"
#include "pb_decode.h"
#include "EndDeviceProtocol.pb.h"
#include "operators.h"



bool encode_output_message(pb_ostream_t * stream) {
  bool status;

  EndDeviceProtocol_Output output = EndDeviceProtocol_Output_init_zero;
  
  EndDeviceProtocol_QueryResponse qr = EndDeviceProtocol_QueryResponse_init_zero;

  EndDeviceProtocol_Data d1 = EndDeviceProtocol_Data_init_zero;
  d1.data._int16 = (int16_t) 10;
  d1.which_data = EndDeviceProtocol_Data__int16_tag;
  
  qr.id = 1;
  qr.response[0] = d1;
  qr.response_count = 1;

  output.responses[0] = qr;
  output.responses_count = 1;
  
  status = pb_encode(stream, EndDeviceProtocol_Output_fields, &output);
  
  if (!status)
  {
    printf("Encoding failed: %s\n", PB_GET_ERROR(stream));
  }

  return status;
}

bool decode_output_message(pb_istream_t *stream) {
  EndDeviceProtocol_Output output = EndDeviceProtocol_Output_init_zero;
  
  bool status = pb_decode(stream, EndDeviceProtocol_Output_fields, &output);

  printf("Decoded int16 %d\n", (int)output.responses[0].response[0].data._int16);
  return status;
}

//This is for just encoding a single Instruction/data
// bool encode_data(Instruction i, pb_ostream_t *stream){
//   size_t message_length;
//   bool status;

//   EndDeviceProtocol_Data data = EndDeviceProtocol_Data_init_zero;
//   // TODO: check the values and set the proper one!
//   data.data._int16 = i.data._int;
//   data.which_data = EndDeviceProtocol_Data__int16_tag;
//   printf("data: %d\n", i.data._int);

//   status = pb_encode(stream, EndDeviceProtocol_Data_fields, &data);
//   message_length = stream->bytes_written;

//   if(!status){
//     printf("Encoding failed: %s\n", PB_GET_ERROR(stream));
//     return false;
//   }

//   printf("Message size: %d\n", message_length);
//   return true;
// }

// typedef struct {
//   EndDeviceProtocol_Data *data;
//   int index;
//   int max_size;
// } repeated_data;

// //This is for encoding repeated Data as a submessage
// bool data_encode(pb_ostream_t *stream, const pb_field_t *field, void *const *arg) {
//   repeated_data *data = *arg;

//   if(data->index > data->max_size){
//     return false;
//   }
  
//   if (!pb_encode_tag_for_field(stream, field)) {
//     return false;
//   }

//   return pb_encode_submessage(stream, EndDeviceProtocol_Data_fields, &data->data[data->index++]);
// }

// bool encode_query_response(pb_ostream_t *stream, QueryResponse *arg) {
//   QueryResponse *_response = arg;

//   EndDeviceProtocol_Data data[_response->amount];

//   for(int i = 0; i < _response->amount; i++){
//     EndDeviceProtocol_Data current = EndDeviceProtocol_Data_init_zero;
//     // TODO: check unioncase and set the correct data and stuff
//     current.data._int16 = _response->response[i].data._int;
//     current.which_data = EndDeviceProtocol_Data__int16_tag;
//     data[i] = current;
//   }

//   repeated_data list;
//   list.data = data;
//   list.index = 0;
//   list.max_size = _response->amount;
  
//   EndDeviceProtocol_QueryResponse response = EndDeviceProtocol_QueryResponse_init_zero;
//   response.id = _response->id;
//   response.response.funcs.encode = &data_encode;
//   response.response.arg = &list;

//   return pb_encode(stream, EndDeviceProtocol_QueryResponse_fields, &response);
// }


// bool decode_data(pb_istream_t *stream, const pb_field_t *field, void **arg){
//   (void)field;
//   (void)arg;
//   printf("data, Bytes left: %zu\n", stream->bytes_left);
//   EndDeviceProtocol_Data data = EndDeviceProtocol_Data_init_zero;

//   printf("Decoding data\n");
//   printf("stream error: %s\n", PB_GET_ERROR(stream));

//   bool status = pb_decode(stream, EndDeviceProtocol_Data_fields, &data);
//   printf("stream error: %s\n", PB_GET_ERROR(stream));

//   printf("decoded data: %d\n", data.data._int16);

//   return status;
// }

// bool decode_query_response(pb_istream_t *stream) {
//   //QueryResponse _response;

//   EndDeviceProtocol_QueryResponse response = EndDeviceProtocol_QueryResponse_init_zero;
//   printf("decode, Bytes left: %zu\n", stream->bytes_left);

//   response.response.funcs.decode = &decode_data;
//   bool status = pb_decode(stream, EndDeviceProtocol_Data_fields, &response);

//   printf("stream error: %s\n", PB_GET_ERROR(stream));

//   printf("Decoded Query Response. Status: %d\n", status);

//   return status;
// }

// bool query_response_encode(pb_ostream_t *stream, const pb_field_t *field, void *const *arg){
//   struct repeated *req = *arg;
 
//   while(req->index < (int) req->max_size){
//     EndDeviceProtocol_Output_QueryResponse *qreg = ((EndDeviceProtocol_Output_QueryResponse **) req->repeated_f)[req->index];
    
//     ++req->index;

//     if(!pb_encode_tag_for_field(stream, field)){
//       return false;
//     }

//     if(!pb_encode_submessage(stream, EndDeviceProtocol_Output_QueryResponse_fields, qreg)){
//       return false;
//     }
//   }

//   return true;
// }


// bool encode_output(void){
//   unsigned char buffer[128];
//   size_t message_length;
//   bool status;

//   // printf("Amount of subqueries: %d\n", out.amount);

//   //TODO: use the OutputMessage to generate data
//   EndDeviceProtocol_Output msg = EndDeviceProtocol_Output_init_default;
//   pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof buffer);

//   EndDeviceProtocol_Data data1 = EndDeviceProtocol_Data_init_zero;
//   data1.data._int16 = 11;
//   data1.which_data = 6;
  
//   EndDeviceProtocol_Data data2 = EndDeviceProtocol_Data_init_zero;
//   data2.data._int16 = 22;
//   data2.which_data = 6;

//   EndDeviceProtocol_Data data3 = EndDeviceProtocol_Data_init_zero;
//   data3.data._int16 = 33;
//   data3.which_data = 6;
  
//   EndDeviceProtocol_Data data4 = EndDeviceProtocol_Data_init_zero;
//   data4.data._int16 = 44;
//   data4.which_data = 6;

//   EndDeviceProtocol_Data *data_1[] = {&data1, &data2};
//   EndDeviceProtocol_Data *data_2[] = {&data3, &data4};


//   struct repeated r1 = {.repeated_f = data_1, .index = 0, .max_size = 2};
//   struct repeated r2 = {.repeated_f = data_2, .index = 0, .max_size = 2};

//   EndDeviceProtocol_Output_QueryResponse queryres1 = {
//     .response = {.funcs = {.encode = data_encode}, .arg = &r1}};

//   EndDeviceProtocol_Output_QueryResponse queryres2 = {
//     .response = {.funcs = {.encode = encode_data}, .arg = &r2}};

//   EndDeviceProtocol_Output_QueryResponse *querres[] = {&queryres1, &queryres2};
//   struct repeated r3 = {.repeated_f = querres, .index=0, .max_size = 2};

//   msg.responses.funcs.encode = query_response_encode;
//   msg.responses.arg = &r3;

//   status = pb_encode(&stream, EndDeviceProtocol_Output_fields, &msg);
//   message_length = stream.bytes_written;

//   if(!status){
//     printf("Encoding failed %s\n", PB_GET_ERROR(&stream));
//     return false;
//   }

//   printf("Success: %zu written\n", message_length);
//   for (size_t i = 0; i < message_length; ++i) {
//       printf("%02hhx", buffer[i]);
//   }
//   printf("\n");

//   return true;


// }


// bool decode_one_data(uint8_t *buffer, int length){
//   EndDeviceProtocol_Data data = EndDeviceProtocol_Data_init_zero;

//   pb_istream_t stream = pb_istream_from_buffer(buffer, length);

//   bool status = pb_decode(&stream, EndDeviceProtocol_Data_fields, &data);

//   if(!status){
//     printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
//     return false;
//   }

//   printf("Decoded data value (_int16) is: %d\n", data.data._int16);
//   return true;
// }