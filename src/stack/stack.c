#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "../operators/operators.h"
#include "../number/number.h"

Stack *init_stack()
{
    Stack *stack = calloc(1, sizeof(Stack));
    stack->stack = calloc(10, sizeof(Number));
    stack->size = 10;
    stack->top = -1;
    print_stack(stack);
    return stack;
}

void push(Stack *stack, Number val)
{
    if (stack->top == stack->size - 1)
    {
        resize_stack(stack);
    }
    stack->top++;
    stack->stack[stack->top] = val;
}

Number pop(Stack *stack)
{
    // TODO: What if stack is empty?
    return stack->stack[stack->top--];
}

// TODO: Optimal algorithm for stack resizing?
void resize_stack(Stack *stack)
{
    stack->size += 10;
    stack->stack = realloc(stack->stack, stack->size * sizeof(int));
}

void print_stack(Stack *stack)
{
    //TODO: make the print stack work with Numbers
    printf("\ntop: %d\n", stack->top);
    // printf("stack size: %d\n", stack->size);
    printf("stack: [");
    for (int i = 0; i < stack->size; i++)
    {
        printNumberValue(stack->stack[i]);
        if (i != stack->size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n\n");
}
