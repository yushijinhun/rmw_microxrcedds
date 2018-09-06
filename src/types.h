#ifndef RMW_MICRORTPS_TYPES_H_
#define RMW_MICRORTPS_TYPES_H_

#include "rmw_macros.h"

#include "memory.h"

#include <rmw/types.h>

#include <micrortps/client/client.h>

#include <stddef.h>

#define MAX_TRANSPORT_MTU 512
#define MAX_HISTORY 16
#define MAX_BUFFER_SIZE MAX_TRANSPORT_MTU* MAX_HISTORY

#define MAX_NODES 1
#define MAX_PUBLISHERS_X_NODE 10
#define MAX_SUBSCRIPTIONS_X_NODE 10

RMW_MICRORTPS_DECLARE_INTERNAL_MEMORY_STRUCT(Internal_wait_set_t, rmw_wait_set_t, wait_set)

typedef struct rosidl_message_type_support_t rosidl_message_type_support_t;

typedef struct CustomSubscription
{
    bool in_use;
    mrObjectId subscriber_id;
    mrObjectId datareader_id;
    mrObjectId topic_id;
    rmw_gid_t subscription_gid;
    const char* typesupport_identifier;
    struct Item mem;
} CustomSubscription;

typedef struct CustomPublisher
{
    bool in_use;
    mrObjectId publisher_id;
    mrObjectId datawriter_id;
    mrObjectId topic_id;
    rmw_gid_t publisher_gid;
    const char* typesupport_identifier;
    const rosidl_message_type_support_t* type_support;
    struct CustomNode* custom_node;
    struct Item mem;
} CustomPublisher;

typedef struct CustomNode
{
    mrUDPTransport udp;
    mrSession session;
    mrObjectId participant_id;
    struct MemPool publisher_mem;
    struct MemPool subscription_mem;
    struct Item mem;

    CustomPublisher publisher_info[MAX_PUBLISHERS_X_NODE];
    CustomSubscription subscription_info[MAX_SUBSCRIPTIONS_X_NODE];

} CustomNode;

mrStreamId best_input;
mrStreamId reliable_input;
mrStreamId best_output;
mrStreamId reliable_output;

uint8_t input_reliable_stream_buffer[MAX_BUFFER_SIZE];
uint8_t output_best_effort_stream_buffer[MAX_BUFFER_SIZE];
uint8_t output_reliable_stream_buffer[MAX_BUFFER_SIZE];

void init_nodes_memory(struct MemPool* memory, CustomNode nodes[static MAX_NODES], size_t size);

#endif // !RMW_MICRORTPS_TYPES_H_