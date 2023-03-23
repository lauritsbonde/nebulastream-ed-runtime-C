#include <math.h>;
#include "../environment/stack.h";

// instruction definitions for stack machine
// data
const int CONST = 0;
const int VAR = 1;

// logical
const int AND = 2;
const int OR = 3;
const int NOT = 4;

// relational
const int LT = 5;
const int GT = 6;
const int EQ = 7;

// relational expanded
const int LTEQ = 21;
const int GTEQ = 22;

// arithmetic
const int ADD = 8;
const int SUB = 9;
const int MUL = 10;
const int DIV = 11;
const int MOD = 12;
const int LOG = 13;
const int POW = 14;
const int SQRT = 15;
const int EXP = 16;
const int CEIL = 17;
const int FLOOR = 18;
const int ROUND = 19;
const int ABS = 20;

typedef struct _Expression
{
    int *program;
    int size;
    int pc;
    Stack stack;
} Expression;

int call(Expression e)
{
    e.pc = 0;
    while (e.pc < e.size)
    {
        execute_next(e);
        e.pc++;
    }
}

void execute_next(Expression e)
{
    switch (e.program[e.pc])
    {
    case CONST:
        _CONST(e);
        break;
    case VAR:
        _VAR(e);
        break;
    case AND:
        _AND(e);
        break;
    case OR:
        _OR(e);
        break;
    case NOT:
        _NOT(e)
        break;
    case LT:
        _LT(e);
        break;
    case GT:
        _GT(e);
        break;
    case EQ:
        _EQ(e);
        break;
    case ADD:
        _ADD(e);
        break;
    case SUB:
        _SUB(e);
        break;
    case MUL:
        _MUL(e);
        break;
    case DIV:
        _DIV(e);
        break;
    case MOD:
        _MOD(e);
        break;
    case LOG:
        _LOG(e);
        break;
    case POW:
        _POW(e);
        break;
    case SQRT:
        _SQRT(e);
        break;
    case EXP:
        _EXP(e);
        break;
    case CEIL:
        _CEIL(e);
        break;
    case FLOOR:
        _FLOOR(e);
        break;
    case ROUND:
        _ROUND(e);
        break;
    case ABS:
        _ABS(e);
        break;
    case LTEQ:
        _LTEQ(e);
        break;
    case GTEQ:
        _GTEQ(e);
        break;
    }
}

void _CONST(Expression e)
{
    // push the next value from program as data to the stack
    int val = e.program[++e.pc];
    push(e.stack, val);
}

void _VAR(Expression e)
{
    return;
}

void _AND(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l2 && l1;
    push(e.stack, val);
}

void _OR(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l2 || l1;
    push(e.stack, val);
}

void _NOT(Expression e)
{
    int val = !pop(e.stack);
    push(e.stack, val);
}

void _LT(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l1 < l2;
    push(e.stack, val);
}

void _GT(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l1 > l2;
    push(e.stack, val);
}

void _EQ(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l1 == l2;
    push(e.stack, val);
}

void _ADD(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l1 + l2;
    push(e.stack, val);
}

void _SUB(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l1 - l2;
    push(e.stack, val);
}

void _MUL(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l1 * l2;
    push(e.stack, val);
}

void _DIV(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l1 / l2;
    push(e.stack, val);
}

void _MOD(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = l1 % l2;
    push(e.stack, val);
}

void _LOG(Expression e)
{
    int l1 = pop(e.stack);
    int val = log(l1);
    push(e.stack, val);
}

void _POW(Expression e)
{
    int l2 = pop(e.stack);
    int l1 = pop(e.stack);
    int val = pow(l1, l2);
    push(e.stack, val);
}

void _SQRT(Expression e)
{
    int l1 = pop(e.stack);
    int val = sqrt(l1);
    push(e.stack, val);
}

void _EXP(Expression e)
{
    return;
}

void _CEIL(Expression e)
{
    return;
}

void _FLOOR(Expression e)
{
    return;
}

void _ROUND(Expression e)
{
    return;
}

void _ABS(Expression e)
{
    return;
}

void _LTEQ(Expression e)
{
    return;
}

void _GTEQ(Expression e)
{
    return;
}