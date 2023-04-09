#include <stdio.h>
#include "runTest.h"
#include "./ExpressionTests/ExpressionTests.h"
#include "../testType.h"

void runAllTests() {
    TestResult res = {0,0};
    printf("Running tests\n\n");

    TestResult expressionTestRes = runExpressionTests();
    res.total += expressionTestRes.total;
    res.passed += expressionTestRes.passed;

    printf("\n---------------------------------\n");
    printf("Result: %d/%d passed", res.passed, res.total);
    printf("\n---------------------------------\n\n");
}