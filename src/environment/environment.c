#include <stdlib.h>
#include "environment.h"
#include "../stack/stack.h"

Env *init_env()
{
    Env *env = calloc(1, sizeof(Env));
    env->env = calloc(10, sizeof(Number));
    env->size = 10;
    env->stack = init_stack();
    return env;
}

void clear_env(Env *env)
{
    for (int i = 0; i < env->size; i++)
    {
        Number number;
        number.type._int = 0;
        number.unionCase = 1;
        env->env[i] = number;
    }
}

Number get_value(Env *env, int index)
{
    return env->env[index];
}

void set_value(Env *env, int index, Number val)
{
    env->env[index] = val;
}

void clear_stack(Env *env)
{
    free(env->stack);
    env->stack = init_stack();
}

Stack *get_stack(Env *env)
{
    return env->stack;
}

// TODO: Better resizing algorithm

void resize_env(Env *env)
{
    env->size += 10;
    env->env = realloc(env->env, (env->size * sizeof(Number)));
}