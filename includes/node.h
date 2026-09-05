#include "packet.h"
#include <stdint.h>
#include <stddef.h>

typedef struct network_interface {
    uint8_t  mac_addr[6];
    uint8_t ip_addr[4];
} network_interface_t;

typedef struct node {
    uint32_t id;
    char* hostname;
    network_interface_t **interfaces;
    size_t interfaces_count;
} node_t;


node_t* create_node(size_t);
void send_packet(void* payload, size_t payload_len,uint8_t dst[4],  uint8_t src[4], packet_header_type type,node_t* node);
