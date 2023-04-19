#ifndef PROTOCOLTESTS_H
#define PROTOCOLTESTS_H

#include "../testType.h"

TestResult runProtocolTests();

Test prepareInstructionTest();

Test prepareExpressionTest();

Test prepareMapTest();

Test prepareFilterTest();

Test prepareWindowTest();

Test prepareOperationTestMap();

Test prepareOperationTestFilter();

Test prepareOperationTestWindow();

Test prepareQueryTest();

Test prepareMessageTest();

Test instructionGetsEncoded();

Test expressionGetsEncoded();

Test mapGetsEncoded();

Test filterGetsEncoded();

Test windowGetsEncoded();

Test operationGetsEncodedMap();

Test operationGetsEncodedFilter();

Test operationGetsEncodedWindow();

Test messageGetsEncoded();

Test messageGetsDecoded();


Test outputMessageGetsEncoded();

#endif // PROTOCOLTESTS_H