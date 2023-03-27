#ifndef STACK_H
#define STACK_H

typedef struct _Stack
{
    int top;
    int size;
    int *stack;
} Stack;

void init_stack(Stack *stack, int size);
void push(Stack *stack, int val);
int pop(Stack *stack);
void resize(Stack *stack);
void print_stack(Stack *stack);

#endif /* STACK_H */