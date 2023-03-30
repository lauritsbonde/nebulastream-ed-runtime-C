#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../stack/stack.h"

typedef struct _Env
{
    Number *env;
    int size;
    Stack *stack;
} Env;

Env *init_env();
void clear_env(Env *env);
Number get_value(Env *env, int index);
void set_value(Env *env, int index, Number val);
void clear_stack(Env *env);
Stack *get_stack(Env *env);

#endif /* ENVIRONMENT_H */