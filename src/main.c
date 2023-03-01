#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "logger.h"

//Macros
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(*arr))
#define SLEEP_SEC(t) (usleep(t * (int)pow(10, 6))) // sleep in seconds

int main(int argc, char **argv) {
  char* includeLogs;
  if(argc == 1){
    includeLogs = "no";
  } else {
    includeLogs = argv[1];// argv[1] is wether or not to include logs
  }
  init_logger(includeLogs); 

  while(1) {
    printf("Main loop iteration\n");
    logger("loop", "Main loop iteration");
    SLEEP_SEC(3);
  }
  
  return 0;
}

