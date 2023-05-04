#include "execution.h"
#include "operators.h"
#include "expression.h"
#include "stack.h"

OutputMessage* executeQueries(Message *message){
  OutputMessage *out = malloc(sizeof(OutputMessage));
  out->responses = calloc(message->amount, sizeof(QueryResponse));

  for (int i = 0; i < message->amount; i++) {
    QueryResponse result = executeQuery(&message->queries[i]);
    out->responses[i] = result;
  }

  return out;
}

// QueryResponse executeQuery(Query *query){
//   QueryResponse response;
  
//   return response;

// }