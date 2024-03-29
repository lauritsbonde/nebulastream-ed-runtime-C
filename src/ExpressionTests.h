#ifndef EXPRESSIONTESTS_H
#define EXPRESSIONTESTS_H

#include "stack.h"
#include "environment.h"
#include "expression.h"
#include "testType.h"

void beforeEach(Expression *exp, Instruction *program, int p_size);
TestResult runExpressionTests(void);
Test testPushToStack(void);
Test testPushVarToStack(void);

Test testAnd1(void);
Test testAnd2(void);
Test testAnd3(void);

Test testNot1(void);
Test testNot2(void);
Test testNot3(void);
Test testNot4(void);

Test testLT1(void);
Test testLT2(void);

Test testGT1(void);
Test testGT2(void);

Test testEqual(void);

Test testAdd(void);

Test testSub(void);

Test testMul(void);

Test testDiv(void);

Test testMod(void);

Test testLog(void);

Test testPow(void);

Test testSqrt(void);

Test expValue(void);

Test testOr1(void);
Test testOr2(void);

Test ceilValue(void);
Test ceilValueBig(void);

Test floorValue(void);
Test floorValueBig(void);

Test roundUnderHalf(void);
Test roundOverHalf(void);

Test absoluteValue1(void);
Test absoluteValue2(void);

Test lessThanEqual1(void);
Test lessThanEqual2(void);

Test greaterThanEqual1(void);
Test greaterThanEqual2(void);


// Tests from the original test suite
Test og_test_execute_query_with_result(void);
Test og_test_execute_query_without_result(void);
Test og_test_execute_quries_single_result(void);
Test og_test_execute_quries_multiple_results(void);


#endif // EXPRESSIONTESTS_H