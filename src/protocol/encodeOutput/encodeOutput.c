#include <stdlib.h>
#include <stdio.h>
#include "encodeOutput.h"
#include "../../proto/EndDeviceProtocol.pb-c.h"
#include "../../operators/operators.h"

EndDeviceProtocol__Data* prepare_instruction_output(Instruction *instruction)
{
  EndDeviceProtocol__Data *storage = (EndDeviceProtocol__Data *) malloc(sizeof(EndDeviceProtocol__Data));
  EndDeviceProtocol__Data data = END_DEVICE_PROTOCOL__DATA__INIT;
  
  // The type of data is stored in Instruction struct
  if(instruction->unionCase == 0){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA_INSTRUCTION;
    data.instruction = instruction->data._instruction;
  } else if(instruction->unionCase == 1){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA__UINT32;
    data._float = instruction->data._uint32;
  } else if(instruction->unionCase == 2){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA__INT16;
    data._int16 = instruction->data._int;
  } else if(instruction->unionCase == 3){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA__FLOAT;
    data._float = instruction->data._float;
  } else if(instruction->unionCase == 4){
    data.data_case = END_DEVICE_PROTOCOL__DATA__DATA__DOUBLE;
    data._double = instruction->data._double;
  }

  storage[0] = data;

  return storage;
}

EndDeviceProtocol__Output__QueryResponse *prepareQueryResponse(QueryResponse *response) {
  EndDeviceProtocol__Output__QueryResponse *storage = malloc(sizeof(EndDeviceProtocol__Output__QueryResponse));
  EndDeviceProtocol__Output__QueryResponse queryResponse = END_DEVICE_PROTOCOL__OUTPUT__QUERY_RESPONSE__INIT;

  queryResponse.id = response->id;
  queryResponse.n_response = response->amount;
  queryResponse.response = malloc(response->amount * sizeof(EndDeviceProtocol__Data));
  
  for(int i = 0; i < response->amount; i++) {
    queryResponse.response[i] = prepare_instruction_output(&response->response[i]);
  }

  storage[0] = queryResponse;
  
  return storage;
}

EndDeviceProtocol__Output *prepareOutput(OutputMessage *output) {
  EndDeviceProtocol__Output *storage = malloc(sizeof(EndDeviceProtocol__Output));
  EndDeviceProtocol__Output out = END_DEVICE_PROTOCOL__OUTPUT__INIT;

  out.n_responses = output->amount;
  out.responses = malloc(output->amount * sizeof(EndDeviceProtocol__Output__QueryResponse));

  for(int i = 0; i < output->amount; i++) {
    out.responses[i] = prepareQueryResponse(&output->responses[i]);
  }

  storage[0] = out;
  
  return storage;
}

void outputCleanup(EndDeviceProtocol__Output *output)
{
  for (int i = 0; i < output->n_responses; i++)
  {
    EndDeviceProtocol__Output__QueryResponse *response = output->responses[i];
    for (int j = 0; j < response->n_response; j++)
    {
      EndDeviceProtocol__Data *data = response->response[j];
      free(data);
    }
    free(response);
  }
  free(output);
}

uint8_t *encodeOutputMessage(OutputMessage *msg)
{
  uint8_t *buf;
  size_t len;

  EndDeviceProtocol__Output *preparedOutput = prepareOutput(msg);

  len = end_device_protocol__output__get_packed_size(preparedOutput);
  buf = malloc(len);

  end_device_protocol__output__pack(preparedOutput, buf);

  outputCleanup(preparedOutput);

  return buf;
}