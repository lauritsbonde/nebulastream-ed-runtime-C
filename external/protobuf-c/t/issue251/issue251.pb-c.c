/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: t/issue251/issue251.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "t/issue251/issue251.pb-c.h"
void   two_oneofs__init
                     (TwoOneofs         *message)
{
  static const TwoOneofs init_value = TWO_ONEOFS__INIT;
  *message = init_value;
}
size_t two_oneofs__get_packed_size
                     (const TwoOneofs *message)
{
  assert(message->base.descriptor == &two_oneofs__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t two_oneofs__pack
                     (const TwoOneofs *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &two_oneofs__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t two_oneofs__pack_to_buffer
                     (const TwoOneofs *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &two_oneofs__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
TwoOneofs *
       two_oneofs__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (TwoOneofs *)
     protobuf_c_message_unpack (&two_oneofs__descriptor,
                                allocator, len, data);
}
void   two_oneofs__free_unpacked
                     (TwoOneofs *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &two_oneofs__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor two_oneofs__field_descriptors[4] =
{
  {
    "a",
    10,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BOOL,
    offsetof(TwoOneofs, first_oneof_case),
    offsetof(TwoOneofs, a),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "b",
    11,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BOOL,
    offsetof(TwoOneofs, first_oneof_case),
    offsetof(TwoOneofs, b),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "c",
    20,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BOOL,
    offsetof(TwoOneofs, second_oneof_case),
    offsetof(TwoOneofs, c),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "d",
    21,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BOOL,
    offsetof(TwoOneofs, second_oneof_case),
    offsetof(TwoOneofs, d),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned two_oneofs__field_indices_by_name[] = {
  0,   /* field[0] = a */
  1,   /* field[1] = b */
  2,   /* field[2] = c */
  3,   /* field[3] = d */
};
static const ProtobufCIntRange two_oneofs__number_ranges[2 + 1] =
{
  { 10, 0 },
  { 20, 2 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor two_oneofs__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "two_oneofs",
  "TwoOneofs",
  "TwoOneofs",
  "",
  sizeof(TwoOneofs),
  4,
  two_oneofs__field_descriptors,
  two_oneofs__field_indices_by_name,
  2,  two_oneofs__number_ranges,
  (ProtobufCMessageInit) two_oneofs__init,
  NULL,NULL,NULL    /* reserved[123] */
};