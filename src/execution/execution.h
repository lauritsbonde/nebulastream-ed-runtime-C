#ifndef EXECUTION_H
#define EXECUTION_H

#include "../operators/operators.h"

OutputMessage* executeQueries(Message *message, int* sensorReadings);
QueryResponse executeQuery(Query *query);

#endif // EXECUTION_H