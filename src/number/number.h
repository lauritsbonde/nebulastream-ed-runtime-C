#ifndef NUMBER_H
#define NUMBER_H

#include <stdlib.h>

typedef struct _Number {
    union {
        uint32_t _uint32; // case 1
        int _int;         // case 2
        float _float;     // case 3
        double _double;   // case 4
    } type;
    int unionCase;
} Number;

void printNumberValue(Number val);
void printNumberValueAndUcase(Number val);

#endif /* NUMBER_H */