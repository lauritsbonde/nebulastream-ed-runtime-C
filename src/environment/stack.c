#include "stack.h"

Stack init_stack()
{
    Stack newStack;
    newStack.top = -1;
    newStack.size = STACK_SIZE;
    return newStack;
}

void push(Stack stack, int val)
{
    if (stack.top == stack.size - 1)
    {
        resize(stack);
    }
    stack.top = stack.top + 1;
    stack.stack[stack.top] = val;
}

int pop(Stack stack)
{
    // TODO: What if stack is empty?
    return stack.stack[stack.top--];
}

// TODO: Optimal algorithm for stack resizing?
void resize(Stack stack)
{
    stack.size += 10;
    int newArray[stack.size];
    for (int i = 0; i < sizeof(stack.size); i++)
    {
        newArray[i] = stack.stack[i];
    }
}