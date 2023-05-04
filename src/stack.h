#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "../operators/operators.h"

Stack *init_stack(void);
void push(Stack *stack, Number val);
Number pop(Stack *stack);
void resize_stack(Stack *stack);
void print_stack(Stack *stack);

#endif /* STACK_H */
