#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "protocolTests.h"
#include "testType.h"
#include "environment.h"
#include "encodeInput.h"
#include "encodeOutput.h"

TestResult runProtocolTests(void){
  TestResult res;

  const int numTests = 21;
  res.total = numTests;
  res.passed = 0;
  res.tests = malloc(sizeof(Test) * numTests);

  return res;
}
