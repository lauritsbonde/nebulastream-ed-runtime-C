#include "protocol.h"

int hasMsg(char* name, char* msg){
  return 0;
}

int* decodeDataMsg(int* buf, char** instructions){
  for(int i = 0; i < 5; i++){
    buf[i] = i;
  };
  return buf;
}