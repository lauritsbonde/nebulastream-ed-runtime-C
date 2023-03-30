#ifndef STACK_H
#define STACK_H

#include "../operators/operators.h"
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

typedef struct _Stack
{
    int top;
    int size;
    Number *stack;
} Stack;

Stack *init_stack();
void push(Stack *stack, Number val);
Number pop(Stack *stack);
void resize_stack(Stack *stack);
void print_stack(Stack *stack);

#endif /* STACK_H */
