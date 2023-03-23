#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 10

typedef struct _Stack
{
    int top;
    int size;
    int stack[STACK_SIZE];
} Stack;

Stack init_stack();
void push(Stack stack, int val);
int pop(Stack stack);
void resize(Stack stack);

#endif /* STACK_H */