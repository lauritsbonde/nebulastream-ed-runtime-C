#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../stack/stack.h"
#include "../../environment/environment.h"
#include "../../expression/expression.h"
#include "ExpressionTests.h"
#include "../testType.h"

void beforeEach(Expression *exp, Instruction *program, int p_size)
{
  exp->env = init_env();
  exp->stack = exp->env->stack;
  exp->program = program;
  exp->p_size = p_size;
}

void assert_int_equals(int actual, int expected, Test *test)
{
  if (actual != expected)
  {
    test->failed = 1;
    char *msg;
    sprintf(msg, "Expected %d, got %d", expected, actual);
    test->message = msg;
  }
  else
  {
    test->failed = 0;
  }
}

void assert_double_equals(double actual, double expected, Test *test)
{
  if (actual != expected)
  {
    test->failed = 1;
    char *msg;
    sprintf(msg, "Expected %f, got %f", expected, actual);
    test->message = msg;
  }
  else
  {
    test->failed = 0;
  }
}

void assert_true(int actual, Test * test) {
  if (actual) {
    test->failed = 0;
  } else {
    test->failed = 1;
    char *msg;
    sprintf(msg, "Expected True, got %d", actual);
    test->message = msg;
  }
}

void assert_false(int actual, Test *test)
{
  if (!actual)
  {
    test->failed = 0;
  } else
  {
    test->failed = 1;
    char *msg;
    sprintf(msg, "Expected False, got %d", actual);
    test->message = msg;
  }
}

TestResult runExpressionTests()
{
  printf("Testing the expression module\n");

  TestResult res = {0, 0};
  
  const int numTests = 37;
  res.total += numTests;

  Test *tests = calloc(numTests, sizeof(Test));
  tests[0] = testPushToStack();
  tests[1] = testPushVarToStack();
  tests[2] = testAnd1();
  tests[3] = testAnd2();
  tests[4] = testAnd3();
  tests[5] = testOr1();
  tests[6] = testOr2();
  tests[7] = testNot1();
  tests[8] = testNot2();
  tests[9] = testNot3();
  tests[10] = testNot4();
  tests[11] = testLT1();
  tests[12] = testLT2();
  tests[13] = testGT1();
  tests[14] = testGT2();
  tests[15] = testEqual();
  tests[16] = testAdd();
  tests[17] = testSub();
  tests[18] = testMul();
  tests[19] = testDiv();
  tests[20] = testMod();
  tests[21] = testLog();
  tests[22] = testPow();
  tests[23] = testSqrt();
  tests[24] = expValue();
  tests[25] = ceilValue();
  tests[26] = ceilValueBig();
  tests[27] = floorValue();
  tests[28] = floorValueBig();
  tests[29] = roundUnderHalf();
  tests[30] = roundOverHalf();
  tests[31] = absoluteValue1();
  tests[32] = absoluteValue2();
  tests[33] = lessThanEqual1();
  tests[34] = lessThanEqual2();
  tests[35] = greaterThanEqual1();
  tests[36] = greaterThanEqual2();


  
  for(int i = 0; i < numTests; i++) {
    if(tests[i].failed) {
      printf("Test %s failed 🚫\n", tests[i].name);
      printf("\t- %s\n", tests[i].message);
    } else {
      printf("Test %s passed ✅ \n", tests[i].name);
      res.passed++;
    }
  }
  return res;
}

// Test Adding a const to the stack
Test testPushToStack() {
  // Arrange
  Test res;
  res.name = "Push Const to Stack";
  Instruction p1[2] = {
      {0, 0},
      {.data._int = 3, 2}
    };
  Expression exp1;
  beforeEach(&exp1, p1, 2);
  
  // Act
  int actual = call(&exp1).type._int;
  int expected = 3;

  // Assert
  assert_int_equals(actual, expected, &res);
  return res;
};

// Test pushing var from env to stack
Test testPushVarToStack() {
  // Arrange
  Test res;
  res.name = "Push Var to Stack";
  Instruction p[2] = {
    {1, 0},
    {.data._int = 0, 2}
  };
  Expression exp;
  beforeEach(&exp, p, 2);
  Number val = {10, 2};
  set_value(exp.env, 0, val);

  // Act
  Number popped = call(&exp);
  int actual = popped.type._int;
  int expected = 10;
  
  // Assert
  assert_int_equals(actual, expected, &res);
  return res;
}

Test testAnd1() {
  // Arrange
  Test test;
  test.name = "1 AND 1 returns true";
  Instruction p[5] = {
    {0, 0},
    {.data._int = 1, 2},
    {0, 0},
    {.data._int = 1, 2},
    {2, 0}
  };
  Expression exp;
  beforeEach(&exp, p, 5);
  
  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_true(actual, &test);

  return test;
}

Test testAnd2() {
  // Arrange
  Test test;
  test.name = "1 AND 0 returns false";
  Instruction p[5] = {
    {0, 0},
    {.data._int = 1, 2},
    {0, 0},
    {.data._int = 0, 2},
    {2, 0}
  };
  Expression exp;
  beforeEach(&exp, p, 5);
  
  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_false(actual, &test);

  return test;
}

Test testAnd3()
{
  // Arrange
  Test test;
  test.name = "0 AND 0 returns false";
  Instruction p[5] = {
      {0, 0},
      {.data._int = 0, 2},
      {0, 0},
      {.data._int = 0, 2},
      {2, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 5);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_false(actual, &test);

  return test;
}

Test testOr1()
{
  // Arrange
  Test test;
  test.name = "1 or 0 returns true";
  Instruction p[5] = {
      {0, 0},
      {.data._int = 1, 2},
      {0, 0},
      {.data._int = 0, 2},
      {3, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 5);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_true(actual, &test);

  return test;
}

Test testOr2() {
  // Arrange
  Test test;
  test.name = "0 or 0 returns false";
  Instruction p[5] = {
      {0, 0},
      {.data._int = 0, 2},
      {0, 0},
      {.data._int = 0, 2},
      {3, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 5);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_false(actual, &test);

  return test;
}

Test testNot1() {
  // Arrange
  Test test;
  test.name = "Not 0 returns true";
  Instruction p[3] = {
      {0, 0},
      {.data._int = 0, 2},
      {4, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 3);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_true(actual, &test);

  return test;
}

Test testNot2() {
  // Arrange
  Test test;
  test.name = "Not 0.0 returns true";
  Instruction p[3] = {
      {0, 0},
      {.data._double = 0.0, 4},
      {4, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 3);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_true(actual, &test);

  return test;
}

Test testNot3()
{
  // Arrange
  Test test;
  test.name = "Not uint 5 returns false";
  Instruction p[3] = {
      {0, 0},
      {.data._uint32 = 5, 1},
      {4, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 3);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_false(actual, &test);

  return test;
}

Test testNot4()
{
  // Arrange
  Test test;
  test.name = "Not int 1 returns false";
  Instruction p[3] = {
      {0, 0},
      {.data._int = 1, 2},
      {4, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 3);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_false(actual, &test);

  return test;
}

Test testLT1() {
  // Arrange
  Test test;
  test.name = "1.0 < 5 returns true";
  Instruction p[5] = {
      {0, 0},
      {.data._double = 1.0, 4},
      {0, 0},
      {.data._int = 5, 2},
      {5, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 5);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_true(actual, &test);

  return test;
}

Test testLT2() {
  // Arrange
  Test test;
  test.name = "uint 7 < 3.4f returns false";
  Instruction p[5] = {
      {0, 0},
      {.data._uint32 = 7, 1},
      {0, 0},
      {.data._float = 3.4f, 3},
      {5, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 5);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_false(actual, &test);

  return test;
}

Test testGT1() {
  // Arrange
  Test test;
  test.name = "-3 > uint 5 returns false";

  Instruction p[5] = {
      {0, 0},
      {.data._int = -3, 2},
      {0, 0},
      {.data._uint32 = 5, 1},
      {6, 0}
  };

  Expression exp;
  beforeEach(&exp, p, 5);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_false(actual, &test);

  return test;
}

Test testGT2()
{
  // Arrange
  Test test;
  test.name = "3.14 > 0 returns true";
  Instruction p[5] = {
      {0, 0},
      {.data._double = 3.14, 4},
      {0, 0},
      {.data._int = 0, 2},
      {6, 0}};
  Expression exp;
  beforeEach(&exp, p, 5);

  // Act
  int actual = call(&exp).type._int;

  // Assert
  assert_true(actual, &test);

  return test;
}

Test testEqual(){
  Test res;
  res.name = "Equal 10 == 10";

  Instruction p1[5] = {
      {0, 0},
      {.data._int = 10, 2},
      {0, 0},
      {.data._int = 10, 2},
      {7,0}
    };
    
  Expression exp1;
  beforeEach(&exp1, p1, 5);

  // Action
  Number actual = call(&exp1);
  
  // Assert
  assert_true(actual.type._int, &res);
  return res;
}

Test testAdd(){
  Test res;
  res.name = "Add 10 + 3 = 13";

  Instruction p1[5] = {
      {0, 0},
      {.data._int = 10, 2},
      {0, 0},
      {.data._int = 3, 2},
      {8,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Action
  Number actual = call(&exp1);
  int expected = 13;
  
  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}

Test testSub(){
  Test res;
  res.name = "Sub 10 - 3 = 7";

  Instruction p1[5] = {
      {0, 0},
      {.data._int = 10, 2},
      {0, 0},
      {.data._int = 3, 2},
      {9,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Action
  Number actual = call(&exp1);
  int expected = 7;

  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;

}

Test testMul(){
  Test res;
  res.name = "Mul 10 * 3 = 30";
  
  Instruction p1[5] = {
      {0, 0},
      {.data._int = 10, 2},
      {0, 0},
      {.data._int = 3, 2},
      {10,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Action
  Number actual = call(&exp1);
  int expected = 30;

  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}

Test testDiv(){
  Test res;
  res.name = "Div 10 / 3 = 3";
  
  Instruction p1[5] = {
      {0, 0},
      {.data._int = 10, 2},
      {0, 0},
      {.data._int = 3, 2},
      {11,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Action
  Number actual = call(&exp1);
  int expected = 3;
  
  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}

Test testMod(){
  Test res;
  res.name = "Mod 10 % 3 = 1";
  
  Instruction p1[5] = {
      {0, 0},
      {.data._int = 10, 2},
      {0, 0},
      {.data._int = 3, 2},
      {12,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Action
  Number actual = call(&exp1);
  int expected = 1;
  
  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}

Test testLog(){
  Test res;
  res.name = "Log 10";
  
  Instruction p1[3] = {
      {0, 0},
      {.data._double = 10, 4},
      {13,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  double expected = log(10);
  
  // Assert
  assert_double_equals(actual.type._double, expected, &res);
  return res;
}

Test testPow(){
  Test res;
  res.name = "2 to the power of 3";

  Instruction p1[5] = {
      {0, 0},
      {.data._int = 2, 2},
      {0, 0},
      {.data._int = 3, 2},
      {14,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Action
  Number actual = call(&exp1);
  double expected = pow(2,3);
  
  // Assert
  assert_double_equals(actual.type._double, expected, &res);
  return res;
}


Test testSqrt(){
  Test res;
  res.name = "Sqrt 4 to 2";

  Instruction p1[3] = {
      {0, 0},
      {.data._int = 4, 2},
      {15,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  double expected = sqrt(4);
  
  // Assert
  assert_double_equals(actual.type._double, expected, &res);
  return res;
}


Test expValue() {
  Test res;
  res.name = "1 to the power of euler's number";

  Instruction p1[3] = {
      {0, 0},
      {.data._int = 1, 2},
      {16,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  double expected = exp(1);
  
  // Assert
  assert_double_equals(actual.type._double, expected, &res);
  return res;
}

Test ceilValue(){
  Test res;
  res.name = "Ceil 1.4 to 2";

  Instruction p1[3] = {
      {0, 0},
      {.data._double = 1.4, 4},
      {17,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  int expected = 2;
  
  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}

Test ceilValueBig(){
  Test res;
  res.name = "Ceil 1.9 to 2";

  Instruction p1[3] = {
      {0, 0},
      {.data._double = 1.9, 4},
      {17,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  int expected = 2;
  
  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}


Test floorValue(){
  Test res;
  res.name = "Floor 1.4 to 1";

  Instruction p1[3] = {
      {0, 0},
      {.data._double = 1.4, 4},
      {18,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  int expected = 1;
  
  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}

Test floorValueBig(){
  Test res;
  res.name = "Floor 1.9 to 1";

  Instruction p1[3] = {
      {0, 0},
      {.data._double = 1.9, 4},
      {18,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  int expected = 1;
  
  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}

Test roundUnderHalf(){
  Test res;
  res.name = "Round 1.4 to 1";

  Instruction p1[3] = {
      {0, 0},
      {.data._double = 1.4, 4},
      {19,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  double expected = 1;
  
  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}

Test roundOverHalf(){
  Test res;
  res.name = "Round 1.6 to 2";

  Instruction p1[3] = {
      {0, 0},
      {.data._double = 1.6, 4},
      {19,0}
    };

  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  double expected = 2;
  
  // Assert
  assert_int_equals(actual.type._int, expected, &res);
  return res;
}


Test absoluteValue1(){
  Test res;
  res.name = "Absolute value of 5";
  
  Instruction p1[3] = {
      {0, 0},
      {.data._int = 5, 2},
      {20,0}
    };
  
  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  double expected = 5;
  
  // Assert
  if(actual.type._double != expected) {
    res.failed = 1;
    char* msg;
    sprintf(msg, "Expected %lf, got %lf",expected, actual.type._double);
    res.message = msg;
  } else {
    res.failed = 0;
  }

  return res;
}

Test absoluteValue2(){
  Test res;
  res.name = "Absolute value of -5";

  Instruction p1[3] = {
      {0, 0},
      {.data._int = -5, 2},
      {20,0}
    };
  
  Expression exp1;
  beforeEach(&exp1, p1, 3);
  
  // Action
  Number actual = call(&exp1);
  double expected = 5;
  
  // Assert
  if(actual.type._double != expected) {
    res.failed = 1;
    char* msg;
    sprintf(msg, "Expected %lf, got %lf",expected, actual.type._double);
    res.message = msg;
  } else {
    res.failed = 0;
  }
  
  return res;
}

Test lessThanEqual1(){
  Test res;
  res.name = "Less than or equal (less than)";
  
  Instruction p1[5] = {
      {0, 0},
      {.data._int = 2, 2},
      {0,0},
      {.data._int = 3, 2},
      {21,0},
    };

  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Act
  Number popped = call(&exp1);
  int expected = 1;

  // Assert
  assert_int_equals(popped.type._int, expected, &res);
  return res;
}

Test lessThanEqual2(){
  Test res;
  res.name = "Less than or equal (equal)";
  Instruction p1[5] = {
      {0, 0},
      {.data._int = 3, 2},
      {0,0},
      {.data._int = 3, 2},
      {21,0},
    };
  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Action
  Number popped = call(&exp1);
  int expected = 1;

  // Assert
  assert_int_equals(popped.type._int, expected, &res);
  return res;
}


Test greaterThanEqual1(){
  Test res;
  res.name = "Greater than or equal (greater than)";
  Instruction p1[5] = {
      {0, 0},
      {.data._int = 4, 2},
      {0,0},
      {.data._int = 3, 2},
      {22,0},
    };
  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Action
  Number popped = call(&exp1);
  int expected = 1;

  // Assert
  assert_int_equals(popped.type._int, expected, &res);
  return res;
}

Test greaterThanEqual2(){
  Test res;
  res.name = "Greater than or equal (equal)";
  Instruction p1[5] = {
      {0, 0},
      {.data._int = 3, 2},
      {0,0},
      {.data._int = 3, 2},
      {22,0},
    };
  Expression exp1;
  beforeEach(&exp1, p1, 5);
  
  // Action
  Number popped = call(&exp1);
  int expected = 1;

  // Assert
  assert_int_equals(popped.type._int, expected, &res);
  return res;
}