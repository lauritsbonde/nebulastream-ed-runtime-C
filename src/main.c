#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "logger/logger.h"
#include "proto/EndDeviceProtocol.pb.h"
#include <pb_encode.h>
#include <pb_decode.h>
#include "operators/operators.h"
#include "protocol/protocol.h"

//Macros
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(*arr))
#define SLEEP_SEC(t) (usleep(t * (int)pow(10, 6))) // sleep in seconds

int* mapFunction(int* arr, int size) {
  for(int i = 0; i < size; i++) {
    arr[i] = arr[i] * 2;
  }
  return arr;
}

int* filterFunction(int* arr, int size){
  int* newArr = malloc(size * sizeof(int));
  int j = 0;

  for(int i = 0; i < size; i++) {
    if(arr[i] > 7) {
      newArr[j] = arr[i];
      j++;
    }
  }

  if(j < size){
    newArr = realloc(newArr, j * sizeof(int));
  }

  return newArr;
}

int main(int argc, char **argv) {
  // Check if the flag for including logs was passed
  char* includeLogs;
  if(argc == 1){
    includeLogs = "no";
  } else {
    includeLogs = argv[1];// argv[1] is wether or not to include logs
  }
  init_logger(includeLogs); 

  while(1) {
    printf("Main loop iteration\n");
    //TODO: Create a protobuf message
    uint8_t buffer[128];
    size_t message_length;
    bool status;

    EndDeviceProtocol_MapOperation map = EndDeviceProtocol_MapOperation_init_zero;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    uint32_t instr = EndDeviceProtocol_ExpressionInstructions_ADD;
    
    pb_callback_t instructions = {instr};

    map.attribute = 1;
    map.function = instructions;

    status = pb_encode(&stream, EndDeviceProtocol_MapOperation_fields, &map);

    if(!status){
      printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
    } else {
      printf("Succes!");
      for(int i = 0; i < 128; i++){
        printf("%d", buffer[i]);
      };
      printf("\n done \n");
    }

    //TODO: "Send" the message somewhere
    //TODO: "Receive" the message somewhere
    //TODO: Print the message content somewhere
    logger("loop", "Main loop iteration");
    SLEEP_SEC(3);
  }
  
  return 0;
}

