#include <stdlib.h>
#include <stdio.h>

#include "pb_encode.h"
#include "pb_decode.h"
#include "EndDeviceProtocol.pb.h"
#include "operators.h"



EndDeviceProtocol_Data* init_data(Instruction instr){
  EndDeviceProtocol_Data *storage = (EndDeviceProtocol_Data*)malloc(sizeof(EndDeviceProtocol_Data));
  EndDeviceProtocol_Data res = EndDeviceProtocol_Data_init_zero;
  
  if(instr.unionCase == 0){
    ExpressionInstruction einstr = instr.data._instruction;
    if (einstr == CONST)
    {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_CONST;
    } else if (einstr == VAR){
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_VAR;

    } else if (einstr == AND) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_AND;
    } else if (einstr == OR) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_OR;
    } else if (einstr == NOT) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_NOT;
    } else if (einstr == LT) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_LT;
    } else if (einstr == GT) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_GT;
    } else if (einstr == EQ) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_EQ;
    } else if (einstr == ADD) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_ADD;
    } else if (einstr == SUB) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_SUB;
    } else if (einstr == MUL) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_MUL;
    } else if (einstr == DIV) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_DIV;
    } else if (einstr == MOD) {
      res.data.instruction = EndDeviceProtocol_ExpressionInstructions_MOD;
    } 
    // else if(einstr == LOG){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_LOG;
    // } else if(einstr == POW){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_POW;
    // } else if(einstr == SQRT){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_SQRT;
    // } else if(einstr == EXP){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_EXP;
    // } else if(einstr == CEIL){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_CEIl;
    // } else if(einstr == FLOOR){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_FLORR;
    // } else if(einstr == ROUND){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_ROUND;
    // } else if(einstr == ABS){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_ABS;
    // } else if(einstr == LTEG){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_LTEQ;
    // } else if(einstr == GTEQ){
    //   res.data.instruction = EndDeviceProtocol_ExpressionInstructions_GTEQ;
    // }
    res.which_data = EndDeviceProtocol_Data_instruction_tag;
  } else if (instr.unionCase == 1){
    res.data._uint32 = instr.data._uint32;
    res.which_data = EndDeviceProtocol_Data__int32_tag;
  } else if (instr.unionCase == 2){
    res.data._int16 = instr.data._int;
    res.which_data = EndDeviceProtocol_Data__int16_tag;
  } else if (instr.unionCase == 3){
    res.data._float = instr.data._float;
    res.which_data = EndDeviceProtocol_Data__float_tag;
  } else if (instr.unionCase == 4){
    res.data._double = instr.data._double;
    res.which_data = EndDeviceProtocol_Data__double_tag;
  } else {
    printf("Unknown unioncase!\n");
  }

  storage[0] = res;
  return storage;
}

EndDeviceProtocol_QueryResponse* init_query_response(QueryResponse query){
  EndDeviceProtocol_QueryResponse *storage = (EndDeviceProtocol_QueryResponse *) malloc(sizeof(EndDeviceProtocol_QueryResponse));
  EndDeviceProtocol_QueryResponse res = EndDeviceProtocol_QueryResponse_init_zero;

  for(int i = 0; i < query.amount; i++){
    res.response[i] = *init_data(query.response[i]);
  }

  res.response_count = query.amount;
  res.id = query.id;
  
  storage[0] = res;
  return storage;
}


EndDeviceProtocol_Output* init_output(OutputMessage _output) {
  EndDeviceProtocol_Output *storage = (EndDeviceProtocol_Output *) malloc(sizeof(EndDeviceProtocol_Output));
  EndDeviceProtocol_Output output = EndDeviceProtocol_Output_init_zero;

  for (int i = 0; i < _output.amount; i++) {
    output.responses[i] = *init_query_response(_output.responses[i]);
  }

  output.responses_count = _output.amount;
  
  storage[0] = output;
  return storage;
}

bool encode_output_message(pb_ostream_t * stream, OutputMessage msg) {
  bool status;

  EndDeviceProtocol_Output output = *init_output(msg);
  
  status = pb_encode(stream, EndDeviceProtocol_Output_fields, &output);
  
  if (!status)
  {
    printf("Encoding failed: %s\n", PB_GET_ERROR(stream));
  }

  return status;
}

bool decode_output_message(pb_istream_t *stream) {
  EndDeviceProtocol_Output output = EndDeviceProtocol_Output_init_zero;
  
  bool status = pb_decode(stream, EndDeviceProtocol_Output_fields, &output);

  printf("Decoded int16 %f\n", output.responses[0].response[0].data._float);
  return status;
}