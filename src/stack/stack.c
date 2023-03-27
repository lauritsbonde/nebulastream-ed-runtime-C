#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void init_stack(Stack *stack, int size)
{
    stack->stack = (int *)malloc(size * sizeof(int));
    stack->size = size;
    stack->top = -1;
    print_stack(stack);
}

void push(Stack *stack, int val)
{
    if (stack->top == stack->size - 1)
    {
        resize(stack);
    }
    stack->top++;
    stack->stack[stack->top] = val;
}

int pop(Stack *stack)
{
    // TODO: What if stack is empty?
    return stack->stack[stack->top--];
}

// TODO: Optimal algorithm for stack resizing?
void resize(Stack *stack)
{
    stack->size += 10;
    realloc(stack->stack, stack->size * sizeof(int));
}

void print_stack(Stack *stack)
{
    printf("\ntop: %d\n", stack->top);
    // printf("stack size: %d\n", stack->size);
    printf("stack: [");
    for (int i = 0; i < stack->size; i++)
    {
        if (i == stack->size - 1)
        {
            printf(" %d ", stack->stack[i]);
        }
        else
        {
            printf(" %d ,", stack->stack[i]);
        }
    }
    printf("]\n\n");
}