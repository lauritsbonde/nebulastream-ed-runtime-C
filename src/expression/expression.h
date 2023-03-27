#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../environment/environment.h"

typedef struct _Expression
{
    int *program;
    int p_size;
    int pc;
    Env *env;
    Stack *stack;
} Expression;

int call(Expression *e);

#endif /* EXPRESSION_H */