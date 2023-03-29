#ifndef STACK_H
#define STACK_H

typedef struct _Stack
{
    int top;
    int size;
    int *stack;
} Stack;

Stack *init_stack();
void push(Stack *stack, int val);
int pop(Stack *stack);
void resize_stack(Stack *stack);
void print_stack(Stack *stack);

#endif /* STACK_H */