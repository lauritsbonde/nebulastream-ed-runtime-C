#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 10

typedef struct Stack {
    int top;
    int size;
    int stack[STACK_SIZE];
} stack;

stack init_stack();
void push(stack stack, int val);
int pop(stack stack);
void resize(stack stack);

#endif /* STACK_H */