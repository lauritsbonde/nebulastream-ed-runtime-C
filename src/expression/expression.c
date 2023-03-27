#include <math.h>
#include "../stack/stack.h"
#include "expression.h"

// TODO: How do we handle functions that return doubles?
// TODO: Fix linker errors with math.h functions.
// TODO: Implement environment.

void _CONST(Expression *e)
{
    // push the next value from program as data to the stack
    int val = e->program[++e->pc];
    push(e->stack, val);
}

void _VAR(Expression *e)
{
    int index = e->program[++e->pc];
    int val = get_value(e->env, index);
    push(e->stack, val);
}

void _AND(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l2 && l1;
    push(e->stack, val);
}

void _OR(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l2 || l1;
    push(e->stack, val);
}

void _NOT(Expression *e)
{
    int val = !pop(e->stack);
    push(e->stack, val);
}

void _LT(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 < l2;
    push(e->stack, val);
}

void _GT(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 > l2;
    push(e->stack, val);
}

void _EQ(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 == l2;
    push(e->stack, val);
}

void _ADD(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 + l2;
    push(e->stack, val);
}

void _SUB(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 - l2;
    push(e->stack, val);
}

void _MUL(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 * l2;
    push(e->stack, val);
}

void _DIV(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 / l2;
    push(e->stack, val);
}

void _MOD(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 % l2;
    push(e->stack, val);
}

void _LOG(Expression *e)
{
    // int l1 = pop(e->stack);
    // int val = log(l1);
    // push(e->stack, val);
}

void _POW(Expression *e)
{
    // int l2 = pop(e->stack);
    // int l1 = pop(e->stack);
    // int val = pow(l1, l2);
    // push(e->stack, val);
}

void _SQRT(Expression *e)
{
    // int l1 = pop(e->stack);
    // int val = sqrt(l1);
    // push(e->stack, val);
}

void _EXP(Expression *e)
{
    // int l1 = pop(e->stack);
    // int val = exp(l1);
    // push(e->stack, val);
}

void _CEIL(Expression *e)
{
    // int l1 = pop(e->stack);
    // int val = ceil(l1);
    // push(e->stack, val);
}

void _FLOOR(Expression *e)
{
    // int l1 = pop(e->stack);
    // int val = floor(l1);
    // push(e->stack, val);
}

void _ROUND(Expression *e)
{
    // int l1 = pop(e->stack);
    // int val = round(l1);
    // push(e->stack, val);
}

void _ABS(Expression *e)
{
    // int l1 = pop(e->stack);
    // int val = abs(l1);
    // push(e->stack, val);
}

void _LTEQ(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 <= l2;
    push(e->stack, val);
}

void _GTEQ(Expression *e)
{
    int l2 = pop(e->stack);
    int l1 = pop(e->stack);
    int val = l1 >= l2;
    push(e->stack, val);
}

void execute_next(Expression *e)
{
    switch (e->program[e->pc])
    {
    case 0:
        _CONST(e);
        break;
    case 1:
        _VAR(e);
        break;
    case 2:
        _AND(e);
        break;
    case 3:
        _OR(e);
        break;
    case 4:
        _NOT(e);
        break;
    case 5:
        _LT(e);
        break;
    case 6:
        _GT(e);
        break;
    case 7:
        _EQ(e);
        break;
    case 8:
        _ADD(e);
        break;
    case 9:
        _SUB(e);
        break;
    case 10:
        _MUL(e);
        break;
    case 11:
        _DIV(e);
        break;
    case 12:
        _MOD(e);
        break;
    case 13:
        _LOG(e);
        break;
    case 14:
        _POW(e);
        break;
    case 15:
        _SQRT(e);
        break;
    case 16:
        _EXP(e);
        break;
    case 17:
        _CEIL(e);
        break;
    case 18:
        _FLOOR(e);
        break;
    case 19:
        _ROUND(e);
        break;
    case 20:
        _ABS(e);
        break;
    case 21:
        _LTEQ(e);
        break;
    case 22:
        _GTEQ(e);
        break;
    }
}

int call(Expression *e)
{
    e->pc = 0;
    while (e->pc < e->p_size)
    {
        execute_next(e);
        print_stack(e->stack);
        e->pc++;
    }
    int val = pop(e->stack);
    return val;
}

// Instructions:
//  Data
//      CONST = 0
//      VAR = 1
//  Logical
//      AND = 2
//      OR = 3
//      NOT = 4
//  Relational
//      LT = 5
//      GT = 6
//      EQ = 7
//  Relational expanded
//      LTEQ = 21
//      GTEQ = 22
//  Arithmetic
//      ADD = 8
//      SUB = 9
//      MUL = 10
//      DIV = 11
//      MOD = 12
//      LOG = 13
//      POW = 14
//      SQRT = 15
//      EXP = 16
//      CEIL = 17
//      FLOOR = 18
//      ROUND = 19
//      ABS = 20