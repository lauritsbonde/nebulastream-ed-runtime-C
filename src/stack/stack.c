#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *init_stack()
{
    Stack *stack = calloc(1, sizeof(Stack));
    stack->stack = calloc(10, sizeof(int));
    stack->size = 10;
    stack->top = -1;
    print_stack(stack);
    return stack;
}

void push(Stack *stack, int val)
{
    if (stack->top == stack->size - 1)
    {
        resize_stack(stack);
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
void resize_stack(Stack *stack)
{
    stack->size += 10;
    stack->stack = realloc(stack->stack, stack->size * sizeof(int));
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