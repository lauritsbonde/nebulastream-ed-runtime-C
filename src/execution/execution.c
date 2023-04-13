#include "execution.h"
#include "../operators/operators.h"
#include "../expression/expression.h"
#include "../stack/stack.h"

OutputMessage* executeQueries(Message *message, int *sensorReadings){
  OutputMessage out;
  out.responses = calloc(message->amount, sizeof(QueryResponse));

  for (int i = 0; i < message->amount; i++) {
    QueryResponse result = executeQuery(&message->queries[i]);
    out.responses[i] = result;
  }

  return &out;
}

QueryResponse executeQuery(Query *query){
  QueryResponse response;
  
  return response;

}