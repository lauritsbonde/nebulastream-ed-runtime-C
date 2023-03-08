#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "logger/logger.h"
#include "operators/operators.h"

//Macros
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(*arr))
#define SLEEP_SEC(t) (usleep(t * (int)pow(10, 6))) // sleep in seconds

int* mapFunction(int* arr, int size) {
  printf("Map function called\n");
  printf("Array size: %d\n", size);
  for(int i = 0; i < size; i++) {
    printf("Array element: %d, ", arr[i]);
    arr[i] = arr[i] * 2;
  }
  printf("\n");
  return arr;
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
    

    struct Map map;
    int arr[5] = {1, 2, 3, 4, 5};
    map.fun = mapFunction;
    map.arraySize = ARRAY_SIZE(arr);
    map.array = arr;

    map.array = map.fun(map.array, map.arraySize);

    printf("Map function result:\n");

    for(int i = 0; i < map.arraySize; i++) {
      printf("%d\n", map.array[i]);
    }

    //TODO: "Send" the message somewhere
    //TODO: "Receive" the message somewhere
    //TODO: Print the message content somewhere
    logger("loop", "Main loop iteration");
    SLEEP_SEC(3);
  }
  
  return 0;
}

