#ifndef PROTOCOL_H
#define PROTOCOL_H
#endif

int hasMsg(char* name, char* msg);
int* decodeDataMsg(int* buf, char** instructions);
struct Query* decodeInputMsg(char* string);
