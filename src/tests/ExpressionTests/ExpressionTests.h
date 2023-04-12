#ifndef EXPRESSIONTESTS_H
#define EXPRESSIONTESTS_H

#include "../../stack/stack.h"
#include "../../environment/environment.h"
#include "../../expression/expression.h"
#include "../testType.h"

void beforeEach(Expression *exp, Instruction *program, int p_size);
TestResult runExpressionTests();
Test testPushToStack();
Test testPushVarToStack();

Test testAnd1();
Test testAnd2();
Test testAnd3();

Test testNot1();
Test testNot2();
Test testNot3();
Test testNot4();

Test testLT1();
Test testLT2();

Test testGT1();
Test testGT2();

Test testEqual();

Test testAdd();

Test testSub();

Test testMul();

Test testDiv();

Test testMod();

Test testLog();

Test testPow();

Test testSqrt();

Test expValue();

Test testOr1();
Test testOr2();

Test ceilValue();
Test ceilValueBig();

Test floorValue();
Test floorValueBig();

Test roundUnderHalf();
Test roundOverHalf();

Test absoluteValue1();
Test absoluteValue2();

Test lessThanEqual1();
Test lessThanEqual2();

Test greaterThanEqual1();
Test greaterThanEqual2();



#endif // EXPRESSIONTESTS_H