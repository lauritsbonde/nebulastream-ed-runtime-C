#ifndef PROTOCOLTESTS_H
#define PROTOCOLTESTS_H

#include "testType.h"

TestResult runProtocolTests(void);

Test data_is_initialised(void);
Test query_is_initialised(void);
Test output_is_initialised(void);
Test output_messae_gets_encoded(void);
Test output_message_gets_decoded(void);

#endif // PROTOCOLTESTS_H