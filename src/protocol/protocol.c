#include <stdio.h>
#include <stdlib.h>
#include "protocol.h"
#include "../operators/operators.h"
#include "../../proto/enddeviceprotocol.pb-c.h"

int hasMsg(char* name, char* msg){
  return 0;
}

int* decodeDataMsg(int* buf, char** instructions){
  for(int i = 0; i < 5; i++){
    buf[i] = i;
  };
  return buf;
}

struct Query* decodeInputMsg(uint* bufferMsg){
  printf("decodeInputMsg\n");

  EndDeviceProtocol__Query* queryMsg = end_device_protocol__data__unpack(NULL, sizeof(string), int);
  for(int i = 0; i < queryMsg->n_operations; i++){
    // struct Map map = queryMsg.operations[i];
    // printf("Operation: %d\n", map.attribute);
    printf("Query message, %s", queryMsg);
  }

  
  return NULL;
}