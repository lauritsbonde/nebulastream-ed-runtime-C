#include <math.h>
#include "../stack/stack.h"
#include "expression.h"
#include "../operators/operators.h"

// TODO: How do we handle functions that return doubles?
// TODO: Fix linker errors with math.h functions.

void _CONST(Expression *e)
{
    // push the next value from program as data to the stack
    Number val;
    val.unionCase = e->program[++e->pc].unionCase;

    //TODO: check if 1 can be replaced with enum for instance?
    if(val.unionCase == 1){
        val.type._uint32 = e->program[e->pc].data._uint32;
    }
    else if (val.unionCase == 2){
        val.type._int = e->program[e->pc].data._int;
    }
    else if (val.unionCase == 3) {
        val.type._float = e->program[e->pc].data._float;
    }
    else if (val.unionCase == 4) {
        val.type._double = e->program[e->pc].data._double;
    }

    push(e->stack, val);
}

void _VAR(Expression *e)
{
    //TODO: check index is an int.
    int index = e->program[++e->pc].data._int;
    Number val = get_value(e->env, index);
    push(e->stack, val);
}

void _AND(Expression *e)
{
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);

    Number val;

    //Number stores all different datatypes in the same bits
    //Double is the largest datatype, so we can get all bits by "casting" to double
    //TODO: Test if this is correct
    val.type._int = l2.type._double && l1.type._double;
    val.unionCase = 2;

    push(e->stack, val);
}

void _OR(Expression *e)
{
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);
    
    Number val;

    val.type._int = l2.type._double || l1.type._double;
    val.unionCase = 2;

    push(e->stack, val);
}

void _NOT(Expression *e)
{
    Number val;
    val.type._int = !pop(e->stack).type._double;
    val.unionCase = 2;

    push(e->stack, val);
}

void _LT(Expression *e)
{
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);
    
    Number val;
    val.type._int = l1.type._double < l2.type._double;

    push(e->stack, val);
}

void _GT(Expression *e)
{
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);
    
    Number val;
    val.type._int = l1.type._double > l2.type._double;

    push(e->stack, val);
}

void _EQ(Expression *e)
{
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);
    
    Number val;
    val.type._int = l1.type._double == l2.type._double;
    
    push(e->stack, val);
}

void _ADD(Expression *e)
{
    Number val;
    
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);
    val.type._int = l1.type._double + l2.type._double;
    val.unionCase = 2;
    push(e->stack, val);
}

void _SUB(Expression *e)
{
    Number val;
    
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);
    val.type._double = l1.type._double - l2.type._double;
    val.unionCase = 4;
    push(e->stack, val);
}

void _MUL(Expression *e)
{
    Number val;
    
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);
    val.type._double = l1.type._double * l2.type._double;
    val.unionCase = 4;
    push(e->stack, val);
}

void _DIV(Expression *e)
{
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);
    
    Number val;

    double res = l1.type._double / l2.type._double;

    val.type._double = res;
    val.unionCase = 4;
    push(e->stack, val);
}

void _MOD(Expression *e)
{
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);

    if(l1.unionCase != 2 || l2.unionCase != 2){
        return; //TODO: Throw error (not int)
    }
    
    Number val;

    int res = l1.type._int % l2.type._int;

    val.type._int = res;
    val.unionCase = 2;
    
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
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);
    
    Number val;

    int res = l1.type._double <= l2.type._double;
    
    val.type._int = res;
    val.unionCase = 2;

    push(e->stack, val);
}

void _GTEQ(Expression *e)
{
    Number l2 = pop(e->stack);
    Number l1 = pop(e->stack);

    Number val;

    int res = l1.type._double >= l2.type._double;

    val.type._int = res;
    val.unionCase = 2;

    push(e->stack, val);
}

void execute_next(Expression *e)
{
    switch (e->program[e->pc].data.instruction)
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
    Number val = pop(e->stack);
    return val.type._double;
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