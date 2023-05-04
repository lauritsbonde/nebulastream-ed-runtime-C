#ifndef EXECUTION_H
#define EXECUTION_H

#include "operators.h"

OutputMessage* executeQueries(Message *message);
QueryResponse executeQuery(Query *query);

#endif // EXECUTION_H