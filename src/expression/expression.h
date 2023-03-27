#ifndef EXPRESSION_H
#define EXPRESSION_H

typedef struct _Expression
{
    int *program;
    int p_size;
    int pc;
    Stack *stack;
} Expression;

int call(Expression *e);

#endif /* EXPRESSION_H */